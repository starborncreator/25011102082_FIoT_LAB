/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bme280.h"
#include <stdio.h>
#include <stdint.h>
#include "ESPLib.h"




/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

struct bme280_dev dev;
struct bme280_data comp_data;
struct bme280_settings settings;

/* Status */
int8_t rslt = BME280_OK;
volatile uint8_t sensor_ready = 0;
volatile uint8_t sensor_error = 0;

/* Measurements */
float temperature = 0.0f;  /* Celsius */
float pressure    = 0.0f;  /* hPa */
float humidity    = 0.0f;  /* % RH */


UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */
int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr);

void user_delay_us(uint32_t period, void *intf_ptr);
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  uint32_t previousTime = HAL_GetTick();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
	
	ESP8266_Init(StationMode, huart1);
			// 2. Connect to your local Wi-Fi network (Replace with your Router SSID and Password)
			ESP8266_wifiConnect("SNUC", "snu12345");
			// 3. Connect to your MQTT Broker (Replace with your Broker's IP Address)
			// 1883 is the standard unencrypted MQTT port
			ESP8266_portConnect("TCP", "broker.emqx.io", "1883");
			// 4. Configure the MQTT client connection parameters
			MQTT_InitTypeDef_t mqttSetting;
			mqttSetting.keepAlive = 60;
			mqttSetting.connectFlag = CleanSession;
			mqttSetting.clientID = "harini";
			// 5. Handshake with the MQTT broker
			MQTT_connectBroker(&mqttSetting);
	
	 static uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

    /* Configure Bosch SensorAPI */
    dev.intf_ptr = &dev_addr;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    /* Initialize sensor and load calibration data */
    rslt = bme280_init(&dev);

    if (rslt != BME280_OK)
    {
        sensor_error = 1;
        Error_Handler();
    }

    /* Sensor configuration */
    settings.osr_t = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_1X;
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.filter = BME280_FILTER_COEFF_OFF;
    settings.standby_time = BME280_STANDBY_TIME_0_5_MS;

    rslt = bme280_set_sensor_settings(
        BME280_SEL_OSR_PRESS |
        BME280_SEL_OSR_TEMP  |
        BME280_SEL_OSR_HUM   |
        BME280_SEL_FILTER   |
        BME280_SEL_STANDBY,
        &settings,
        &dev
    );

    if (rslt != BME280_OK)
    {
        sensor_error = 2;
        Error_Handler();
    }

    /* Continuous measurement mode */
    rslt = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &dev);

    if (rslt != BME280_OK)
    {
        sensor_error = 3;
        Error_Handler();
    }

    sensor_ready = 1;

    /* Allow the first measurement to complete */
    HAL_Delay(100);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  { rslt = bme280_get_sensor_data(
            BME280_ALL,
            &comp_data,
            &dev
        );

        if (rslt == BME280_OK)
        {
            /*
             * bme280_defs.h enables BME280_DOUBLE_ENABLE
             * by default in Bosch SensorAPI v3.5.1.
             *
             * Temperature: degrees Celsius
             * Pressure:    Pa -> hPa
             * Humidity:    % RH
             */
            temperature = (float)comp_data.temperature;
            pressure = (float)(comp_data.pressure / 100.0);
            humidity = (float)comp_data.humidity;

            sensor_error = 0;
        }
        else
        {
            sensor_error = 4;
        }

        HAL_Delay(1000);
				char mqttMessage[150];
				snprintf(mqttMessage, sizeof(mqttMessage),
         "Temperature: %.2f C, Pressure: %.2f hPa, Humidity: %.2f %%",
         temperature, pressure, humidity);
    
    /* USER CODE END WHILE */
	if (HAL_GetTick() - previousTime >= 1000)
    {
        previousTime = HAL_GetTick();

        MQTT_publishTopic("stm32/harini", mqttMessage, QoS0);
    }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr)
{
    uint8_t addr = *(uint8_t *)intf_ptr;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
        &hi2c1,
        (uint16_t)(addr << 1),
        reg_addr,
        I2C_MEMADD_SIZE_8BIT,
        reg_data,
        (uint16_t)len,
        1000
    );

    return (status == HAL_OK) ? BME280_OK : BME280_E_COMM_FAIL;
}

/* BME280 register write callback */
int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr)
{
    uint8_t addr = *(uint8_t *)intf_ptr;

    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(
        &hi2c1,
        (uint16_t)(addr << 1),
        reg_addr,
        I2C_MEMADD_SIZE_8BIT,
        (uint8_t *)reg_data,
        (uint16_t)len,
        1000
    );

    return (status == HAL_OK) ? BME280_OK : BME280_E_COMM_FAIL;
}

/* Bosch API delay callback */
void user_delay_us(uint32_t period, void *intf_ptr)
{
    (void)intf_ptr;

    if (period > 0U)
    {
        HAL_Delay((period + 999U) / 1000U);
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Configure voltage scaling */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /* Configure HSI and PLL */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* Configure CPU, AHB and APB clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

  /** Initializes the CPU, AHB and APB buses clocks
  */

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
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
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
