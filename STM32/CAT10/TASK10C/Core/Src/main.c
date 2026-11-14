
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : STM32 + ESP8266 HTTP Server
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/* UART handles */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void Error_Handler(void);

/* ============================================================
   GLOBAL VARIABLES
   ============================================================ */

#define TCP_BUFFER_SIZE     2048
#define HTTP_BUFFER_SIZE    1024

static char tcpBuffer[TCP_BUFFER_SIZE];
static size_t tcpLen = 0;

static char requestBuffer[HTTP_BUFFER_SIZE];
static size_t requestLen = 0;

/* Static webpage */
static const char webpage[] =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1'>"
    "<title>STM32 Web Server</title>"
    "</head>"
    "<body style='font-family:Arial;text-align:center;'>"
    "<h1>Hello from STM32!</h1>"
    "<p>HTTP connection successful.</p>"
    "<h2>Static Data</h2>"
    "<p>Temperature: 28 C</p>"
    "<p>Status: Working</p>"
    "</body>"
    "</html>";

/* ============================================================
   UART HELPER FUNCTIONS
   ============================================================ */

/* Send text to PuTTY using UART2 */
void UART_Send(const char *msg)
{
    HAL_UART_Transmit(&huart2,
                      (uint8_t *)msg,
                      (uint16_t)strlen(msg),
                      HAL_MAX_DELAY);
}

/* Send text to ESP8266 using UART1 */
void Wemos_Send(const char *msg)
{
    HAL_UART_Transmit(&huart1,
                      (uint8_t *)msg,
                      (uint16_t)strlen(msg),
                      HAL_MAX_DELAY);
}

/* Send an AT command and display its response */
void Send_AT_Command(const char *command)
{
    uint8_t rx;
    uint8_t received = 0;

    UART_Send("\r\n>> ");
    UART_Send(command);
    UART_Send("\r\n");

    Wemos_Send(command);
    Wemos_Send("\r\n");

    /* Read until no more response arrives */
    while (HAL_UART_Receive(&huart1, &rx, 1, 3000) == HAL_OK)
    {
        received = 1;
        HAL_UART_Transmit(&huart2, &rx, 1, HAL_MAX_DELAY);
    }

    if (!received)
    {
        UART_Send("\r\nNo response from ESP8266\r\n");
    }

    UART_Send("\r\n");
    HAL_Delay(500);
}

/* ============================================================
   HTTP RESPONSE FUNCTION
   ============================================================ */

void Send_Webpage(int id)
{
    char response[768];
    char command[48];

    /* Construct a complete HTTP response */
    int responseLen = snprintf(
        response,
        sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %u\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        (unsigned int)strlen(webpage),
        webpage
    );

    if (responseLen <= 0 ||
        responseLen >= (int)sizeof(response))
    {
        UART_Send("\r\nHTTP response size error\r\n");
        return;
    }

    /* Tell ESP8266 how many bytes to transmit */
    snprintf(command,
             sizeof(command),
             "AT+CIPSEND=%d,%d\r\n",
             id,
             responseLen);

    Wemos_Send(command);

    /* Wait for the ESP8266 '>' prompt */
    uint8_t ch;
    int promptFound = 0;

    for (int i = 0; i < 500; i++)
    {
        if (HAL_UART_Receive(&huart1, &ch, 1, 10) == HAL_OK)
        {
            if (ch == '>')
            {
                promptFound = 1;
                break;
            }
        }
    }

    if (!promptFound)
    {
        UART_Send("\r\nERROR: ESP8266 prompt timeout\r\n");
        return;
    }

    /* Send the HTTP headers and HTML body */
    HAL_UART_Transmit(&huart1,
                      (uint8_t *)response,
                      (uint16_t)responseLen,
                      5000);

    UART_Send("\r\nHTTP response transmitted\r\n");

    /* Read ESP8266 send result */
    uint8_t result[128];
    uint16_t resultLen = 0;

    HAL_UARTEx_ReceiveToIdle(&huart1,
                             result,
                             sizeof(result),
                             &resultLen,
                             1000);

    if (resultLen > 0)
    {
        HAL_UART_Transmit(&huart2,
                          result,
                          resultLen,
                          2000);
    }

    /* Close this client's TCP connection */
    snprintf(command,
             sizeof(command),
             "AT+CIPCLOSE=%d\r\n",
             id);

    Wemos_Send(command);

    HAL_Delay(200);
}

/* ============================================================
   ESP8266 +IPD AND HTTP REQUEST PROCESSING
   ============================================================ */

void Process_ESP_Data(uint8_t *data, uint16_t len)
{
    if (len == 0)
        return;

    /* Prevent receive buffer overflow */
    if (tcpLen + len >= sizeof(tcpBuffer))
    {
        tcpLen = 0;
        requestLen = 0;

        memset(tcpBuffer, 0, sizeof(tcpBuffer));
        memset(requestBuffer, 0, sizeof(requestBuffer));

        UART_Send("\r\nReceive buffer reset\r\n");
    }

    /* Append incoming UART bytes */
    memcpy(tcpBuffer + tcpLen, data, len);
    tcpLen += len;
    tcpBuffer[tcpLen] = '\0';

    while (1)
    {
        char *ipd = strstr(tcpBuffer, "+IPD,");

        if (ipd == NULL)
        {
            /*
             * Preserve the last five bytes in case the next
             * UART chunk completes a split "+IPD," prefix.
             */
            if (tcpLen > 5)
            {
                memmove(tcpBuffer,
                        tcpBuffer + tcpLen - 5,
                        5);

                tcpLen = 5;
                tcpBuffer[tcpLen] = '\0';
            }

            return;
        }

        /* Remove bytes before the +IPD header */
        size_t prefixLen = (size_t)(ipd - tcpBuffer);

        if (prefixLen > 0)
        {
            memmove(tcpBuffer,
                    ipd,
                    tcpLen - prefixLen);

            tcpLen -= prefixLen;
            tcpBuffer[tcpLen] = '\0';

            ipd = tcpBuffer;
        }

        /* Find the end of the +IPD header */
        char *colon = strchr(ipd, ':');

        if (colon == NULL)
            return;

        int id = -1;
        int dataLen = 0;
        int headerLen = 0;

        /*
         * Expected ESP8266 format:
         * +IPD,<connection ID>,<payload length>:<payload>
         */
        int parsed = sscanf(
            ipd,
            "+IPD,%d,%d:%n",
            &id,
            &dataLen,
            &headerLen
        );

        if (parsed != 2 ||
            id < 0 ||
            id > 4 ||
            dataLen <= 0 ||
            headerLen <= 0)
        {
            /* Skip malformed data and try again */
            memmove(tcpBuffer,
                    tcpBuffer + 1,
                    tcpLen - 1);

            tcpLen--;
            tcpBuffer[tcpLen] = '\0';
            continue;
        }

        size_t frameLen = (size_t)headerLen +
                          (size_t)dataLen;

        /* Wait until the entire declared payload has arrived */
        if (tcpLen < frameLen)
            return;

        char *payload = ipd + headerLen;

        /* Accumulate the HTTP request */
        if (requestLen + (size_t)dataLen >=
            sizeof(requestBuffer))
        {
            requestLen = 0;
            memset(requestBuffer, 0, sizeof(requestBuffer));
        }

        if (requestLen + (size_t)dataLen <
            sizeof(requestBuffer))
        {
            memcpy(requestBuffer + requestLen,
                   payload,
                   (size_t)dataLen);

            requestLen += (size_t)dataLen;
            requestBuffer[requestLen] = '\0';
        }

        /* Remove the processed +IPD frame */
        memmove(tcpBuffer,
                tcpBuffer + frameLen,
                tcpLen - frameLen);

        tcpLen -= frameLen;
        tcpBuffer[tcpLen] = '\0';

        /* Check whether HTTP headers are complete */
        if (strstr(requestBuffer, "\r\n\r\n") != NULL)
        {
            if (strncmp(requestBuffer, "GET ", 4) == 0)
            {
                UART_Send("\r\nBrowser request received!\r\n");

                /* Display the request on UART2 */
                UART_Send(requestBuffer);
                UART_Send("\r\n");

                Send_Webpage(id);
            }
            else
            {
                UART_Send("\r\nNon-GET request received\r\n");
            }

            /* Prepare for the next request */
            requestLen = 0;
            memset(requestBuffer, 0, sizeof(requestBuffer));
        }
    }
}

/* ============================================================
   MAIN FUNCTION
   ============================================================ */

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    HAL_Delay(1500);

    UART_Send("\r\nSTM32 + ESP8266 HTTP SERVER\r\n");
    UART_Send("Starting Wi-Fi connection...\r\n");

    /* --------------------------------------------------------
       STEP 1: Check ESP8266
       -------------------------------------------------------- */

    Send_AT_Command("AT");

    /* --------------------------------------------------------
       STEP 2: Station mode
       -------------------------------------------------------- */

    Send_AT_Command("AT+CWMODE=1");

    /* --------------------------------------------------------
       STEP 3: Enable DHCP
       -------------------------------------------------------- */

    Send_AT_Command("AT+CWDHCP=1,1");

    /* --------------------------------------------------------
       STEP 4: Connect to college Wi-Fi
       -------------------------------------------------------- */

    Send_AT_Command("AT+CWJAP=\"SNUC\",\"snu12345\"");

    /* --------------------------------------------------------
       STEP 5: Read ESP8266 IP address
       -------------------------------------------------------- */

    Send_AT_Command("AT+CIFSR");

    /* --------------------------------------------------------
       STEP 6: Check connection status
       -------------------------------------------------------- */

    Send_AT_Command("AT+CIPSTATUS");

    /* --------------------------------------------------------
       STEP 7: Enable multiple TCP connections
       -------------------------------------------------------- */

    Send_AT_Command("AT+CIPMUX=1");

    /* --------------------------------------------------------
       STEP 8: Start HTTP TCP server on port 80
       -------------------------------------------------------- */

    Send_AT_Command("AT+CIPSERVER=1,80");

    UART_Send("\r\nServer setup commands completed.\r\n");
    UART_Send("Open the ESP8266 IP using http://IP_ADDRESS/\r\n");
    UART_Send("Waiting for browser requests...\r\n");

    /* ========================================================
       INFINITE LOOP: RECEIVE BROWSER REQUESTS
       ======================================================== */

    while (1)
    {
        uint8_t incoming[256];
        uint16_t incomingLen = 0;

        HAL_StatusTypeDef status =
            HAL_UARTEx_ReceiveToIdle(&huart1,
                                     incoming,
                                     sizeof(incoming),
                                     &incomingLen,
                                     100);

        if ((status == HAL_OK || status == HAL_TIMEOUT) &&
            incomingLen > 0)
        {
            /* Show ESP8266 data on UART2/PuTTY */
            HAL_UART_Transmit(&huart2,
                              incoming,
                              incomingLen,
                              2000);

            /* Process +IPD and HTTP requests */
            Process_ESP_Data(incoming, incomingLen);
        }
    }
}

/* ============================================================
   SYSTEM CLOCK CONFIGURATION
   STM32F103 Blue Pill: 72 MHz using 8 MHz HSE
   ============================================================ */

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                            FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* ============================================================
   USART1 INITIALIZATION: ESP8266
   ============================================================ */

static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/* ============================================================
   USART2 INITIALIZATION: PC / PUTTY
   ============================================================ */

static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* ============================================================
   GPIO INITIALIZATION
   ============================================================ */

static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* ============================================================
   ERROR HANDLER
   ============================================================ */

void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    (void)file;
    (void)line;
}
#endif
