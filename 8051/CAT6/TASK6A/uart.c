
#include <reg51.h>

void uart_init(void)
{
    TMOD = 0x20;       // Timer 1, Mode 2

    TH1 = 0xFA;        // 4800 baud (assuming 11.0592 MHz)
    TL1 = 0xFA;

    SCON = 0x50;       // UART Mode 1, receiver enabled

    TR1 = 1;           // Start Timer 1
}

void uart_tx(unsigned char ch)
{
    SBUF = ch;         // Put character into SBUF

    while (TI == 0);   // Wait for transmission

    TI = 0;            // Clear transmit flag
}

void uart_string(char *str)
{
    while (*str != '\0')
    {
        uart_tx(*str);
        str++;
    }
}

void main(void)
{
    uart_init();

    while (1)
    {
        uart_string("Hello from 8051\r\n");
    }
}
