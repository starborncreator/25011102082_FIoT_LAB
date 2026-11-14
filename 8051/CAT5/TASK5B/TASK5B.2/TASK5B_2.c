#include <reg52.h>

unsigned char pwm_count = 0;
unsigned char duty = 0;
unsigned char fade_count = 0;
unsigned char direction = 1;

unsigned int reload_value = 0xEE00;

sbit LED = P1^0;
sbit OUTPUT = P1^1;

/* Timer 0: LED fading, approximately 100 us tick */
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0xA4;

    if (pwm_count < duty)
        LED = 1;
    else
        LED = 0;

    pwm_count++;
    if (pwm_count >= 10)
    {
        pwm_count = 0;
        fade_count++;

        if (fade_count >= 100)
        {
            fade_count = 0;

            if (direction)
            {
                if (duty < 10)
                    duty++;
                else
                    direction = 0;
            }
            else
            {
                if (duty > 0)
                    duty--;
                else
                    direction = 1;
            }
        }
    }
}

/* 4x4 keypad on P2: keys 1 to 5 are used */
int keypad_scan(void)
{
    static const int keys[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 0, -1, -1},
        {-1, -1, -1, -1}
    };
    static const unsigned char rows[4] = {7, 6, 5, 4};
    static const unsigned char cols[4] = {3, 2, 1, 0};
    int r, c;

    for (r = 0; r < 4; r++)
    {
        P2 |= 0xF0;
        P2 &= ~(1 << rows[r]);

        for (c = 0; c < 4; c++)
            if ((P2 & (1 << cols[c])) == 0)
                return keys[r][c];
    }
    return -1;
}

/* Timer 1 reload values for 11.0592 MHz, classic 12-clock 8051.
   Timer interrupt toggles output, so interrupt rate is 2 x output frequency. */
void set_frequency(unsigned char key)
{
    unsigned int value;

    switch (key)
    {
        case 1: value = 0x4C00; break; /* 100 Hz */
        case 2: value = 0xDC00; break; /* 500 Hz */
        case 3: value = 0xEE00; break; /* 1 kHz */
        case 4: value = 0xF700; break; /* 2 kHz */
        case 5: value = 0xFC67; break; /* approximately 5 kHz */
        default: return;
    }

    ET1 = 0;
    reload_value = value;
    TH1 = (unsigned char)(reload_value >> 8);
    TL1 = (unsigned char)reload_value;
    ET1 = 1;
}

/* Timer 1: variable-frequency square wave */
void timer1_ISR(void) interrupt 3
{
    TH1 = (unsigned char)(reload_value >> 8);
    TL1 = (unsigned char)reload_value;
    OUTPUT = !OUTPUT;
}

void main(void)
{
    int key;
    int last_key = -1;

    LED = 0;
    OUTPUT = 0;
    TMOD = 0x11;       /* Timer 0 and Timer 1, Mode 1 */

    TH0 = 0xFF;
    TL0 = 0xA4;

    TH1 = 0xEE;
    TL1 = 0x00;        /* Default 1 kHz output */

    ET0 = 1;
    ET1 = 1;
    EA = 1;
    TR0 = 1;
    TR1 = 1;

    while (1)
    {
        key = keypad_scan();

        /* One selection per key press; release before selecting again. */
        if (key == -1)
            last_key = -1;
        else if (key != last_key)
        {
            last_key = key;
            if (key >= 1 && key <= 5)
                set_frequency((unsigned char)key);
        }
    }
}
