#include <reg52.h>

sbit LED = P1^0;       // LED connected to P2.0

unsigned int ms_count = 0;

void Timer0_ISR(void) interrupt 1
{
    // Reload Timer 0 for approximately 1 ms
    TH0 = 0xFC;
    TL0 = 0x66;

    ms_count++;

    // 1000 × 1 ms = approximately 1 second
    if (ms_count >= 1000)
    {
        ms_count = 0;
        LED = ~LED;
    }
}

void Timer0_Init(void)
{
    // Timer 0 Mode 1: 16-bit timer
    TMOD = 0x01;

    // Load initial value for approximately 1 ms
    TH0 = 0xFC;
    TL0 = 0x66;

    // Enable Timer 0 interrupt
    ET0 = 1;

    // Enable global interrupts
    EA = 1;

    // Start Timer 0
    TR0 = 1;
}

void main(void)
{
    // Initialize LED
    LED = 0;

    // Initialize Timer 0
    Timer0_Init();

    // Main program does not use any delay
    while (1)
    {
        // Other application code can run here
    }
}