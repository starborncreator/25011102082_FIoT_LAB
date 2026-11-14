#include <reg52.h>

unsigned char pwm_count = 0;
unsigned char duty = 0;
unsigned char fade_count = 0;
unsigned char fade_direction = 1;

unsigned char waveform_mode = 1;
unsigned char wave_tick = 0;

sbit LED = P1^0;
sbit OUTPUT = P1^1;

/* Timer 0: LED fading, approximately 100 us tick */
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0xA4;

    LED = (pwm_count < duty) ? 1 : 0;

    pwm_count++;
    if (pwm_count >= 10)
    {
        pwm_count = 0;
        fade_count++;

        if (fade_count >= 100)
        {
            fade_count = 0;

            if (fade_direction)
            {
                if (duty < 10)
                    duty++;
                else
                    fade_direction = 0;
            }
            else
            {
                if (duty > 0)
                    duty--;
                else
                    fade_direction = 1;
            }
        }
    }
}

/* Keypad on P2 */
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

/* Timer 1: 1 ms time base */
void timer1_ISR(void) interrupt 3
{
    TH1 = 0xFC;
    TL1 = 0x66;

    switch (waveform_mode)
    {
        case 1: /* Square wave: 101010... */
            OUTPUT = !OUTPUT;
            break;

        case 2: /* 11110000 repeated: 50% duty cycle */
            OUTPUT = (wave_tick < 4) ? 1 : 0;
            wave_tick++;
            if (wave_tick >= 8)
                wave_tick = 0;
            break;

        case 3: /* Pulse train: 10000000 repeated */
            OUTPUT = (wave_tick == 0) ? 1 : 0;
            wave_tick++;
            if (wave_tick >= 8)
                wave_tick = 0;
            break;

        case 4: /* 1010101010, 10 silent ticks, 1010101010 */
            if (wave_tick < 10)
                OUTPUT = ((wave_tick % 2) == 0) ? 1 : 0;
            else if (wave_tick < 20)
                OUTPUT = 0;
            else
                OUTPUT = (((wave_tick - 20) % 2) == 0) ? 1 : 0;

            wave_tick++;
            if (wave_tick >= 30)
                wave_tick = 0;
            break;

        default:
            OUTPUT = 0;
            wave_tick = 0;
            break;
    }
}

void main(void)
{
    int key;
    int last_key = -1;

    LED = 0;
    OUTPUT = 0;
    TMOD = 0x11;

    TH0 = 0xFF;
    TL0 = 0xA4;
    TH1 = 0xFC;
    TL1 = 0x66;

    ET0 = 1;
    ET1 = 1;
    EA = 1;
    TR0 = 1;
    TR1 = 1;

    while (1)
    {
        key = keypad_scan();

        if (key == -1)
            last_key = -1;
        else if (key != last_key)
        {
            last_key = key;
            if (key >= 1 && key <= 4)
            {
                waveform_mode = (unsigned char)key;
                wave_tick = 0;
                OUTPUT = 0;
            }
        }
    }
}
