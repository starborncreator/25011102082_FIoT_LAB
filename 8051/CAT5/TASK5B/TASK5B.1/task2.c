#include <reg52.h>

sbit LED = P1^0;

/* PWM variables */
unsigned char pwm_count = 0;
unsigned char duty = 0;

/* Controls the time spent at each duty cycle */
unsigned int ramp_count = 0;

/* 1 = duty increasing, 0 = duty decreasing */
bit increasing = 1;


/* Timer 0 ISR */
void Timer0_ISR(void) interrupt 1
{
    /* Reload Timer 0 for approximately 100 us */
    TH0 = 0xFF;
    TL0 = 0xA4;


    /* -------- SOFTWARE PWM -------- */

    pwm_count++;

    if (pwm_count >= 10)
    {
        pwm_count = 0;
    }

    /*
       duty = 0  -> LED always OFF
       duty = 5  -> 50% duty cycle
       duty = 10 -> LED always ON
    */

    if (pwm_count < duty)
    {
        LED = 1;
    }
    else
    {
        LED = 0;
    }


    /* -------- BRIGHTNESS RAMP -------- */

    ramp_count++;

    /*
       Change duty cycle every 1000 interrupts.

       1000 × 100 us = 100 ms
    */
    if (ramp_count >= 1000)
    {
        ramp_count = 0;

        if (increasing == 1)
        {
            /* Increase brightness by 10% */
            if (duty < 10)
            {
                duty++;
            }
            else
            {
                /* Reached 100%, start decreasing */
                increasing = 0;
                duty--;
            }
        }
        else
        {
            /* Decrease brightness by 10% */
            if (duty > 0)
            {
                duty--;
            }
            else
            {
                /* Reached 0%, start increasing */
                increasing = 1;
                duty++;
            }
        }
    }
}


/* Timer 0 initialization */
void Timer0_Init(void)
{
    /* Timer 0, Mode 1, 16-bit timer */
    TMOD = 0x01;

    /* Initial reload value ˜ 100 us */
    TH0 = 0xFF;
    TL0 = 0xA4;

    /* Enable Timer 0 interrupt */
    ET0 = 1;

    /* Enable global interrupts */
    EA = 1;

    /* Start Timer 0 */
    TR0 = 1;
}


void main(void)
{
    /* Initialize LED */
    LED = 0;

    /* Initialize Timer 0 */
    Timer0_Init();

    while (1)
    {
        /* Nothing needed here */
    }
}