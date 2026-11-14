#include <reg51.h>

/* UART Initialization */
void uart_init(void)
{
    TMOD = 0x20;     // Timer 1, Mode 2: 8-bit auto reload

    TH1 = 0xFA;      // 4800 baud for 11.0592 MHz crystal
    TL1 = 0xFA;      // Initial timer value

    SCON = 0x50;     // UART Mode 1, 8-bit, receiver enabled

    TR1 = 1;         // Start Timer 1

    ES = 1;           // Enable serial interrupt
    EA = 1;           // Enable global interrupts
}


/* UART Interrupt Service Routine */
void uart_isr(void) interrupt 4
{
    char received;

    /* Character received */
    if (RI == 1)
    {
        received = SBUF;    // Read received character
        RI = 0;             // Clear receive flag

        SBUF = received;    // Echo character back
    }

    /* Character transmitted */
    if (TI == 1)
    {
        TI = 0;             // Clear transmit flag
    }
}


/* Main Program */
void main(void)
{
    uart_init();

    while (1)
    {
        /* UART is handled by interrupts */
    }
}