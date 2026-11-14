#include <reg52.h>

unsigned char timer_count = 0;
unsigned char step_interval = 10; /* 10 x 10 ms = 100 ms */
unsigned char step_index = 0;
unsigned char direction = 0;     /* 0 = forward, 1 = reverse */

unsigned char code step_sequence[4] = {
    0x08, 0x04, 0x02, 0x01
};

/* Keypad on P2:
   1 = slow, 2 = medium, 3 = fast, 4 = change direction */
int keypad_scan(void)
{
    static const int keys[4][4] = {
        {1, 2, 3, 4},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
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

/* Output the next full-step pattern on P1.0-P1.3 */
void step_motor(void)
{
    if (direction == 0)
        step_index = (step_index + 1) % 4;
    else
        step_index = (step_index + 3) % 4;

    P1 = (P1 & 0xF0) | step_sequence[step_index];
}

/* Timer 0 interrupt: approximately 10 ms */
void timer0_ISR(void) interrupt 1
{
    TH0 = 0xDC;
    TL0 = 0x00;

    timer_count++;
    if (timer_count >= step_interval)
    {
        timer_count = 0;
        step_motor();
    }
}

void timer0_init(void)
{
    TMOD = 0x01;
    TH0 = 0xDC;
    TL0 = 0x00;

    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void set_control(int key)
{
    switch (key)
    {
        case 1: step_interval = 10; break; /* Slow: 100 ms/step */
        case 2: step_interval = 5;  break; /* Medium: 50 ms/step */
        case 3: step_interval = 1;  break; /* Fast: 10 ms/step */
        case 4: direction = !direction; break;
        default: break;
    }
}

void main(void)
{
    int key;
    int last_key = -1;

    P1 = 0x08; /* Initial motor phase */
    timer0_init();

    while (1)
    {
        key = keypad_scan();

        if (key == -1)
            last_key = -1;
        else if (key != last_key)
        {
            last_key = key;
            if (key >= 1 && key <= 4)
                set_control(key);
        }
    }
}
