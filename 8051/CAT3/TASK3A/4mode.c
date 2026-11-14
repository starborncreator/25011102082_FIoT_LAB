#include <reg51.h>

sbit SW = P2^0;
int mode=0;
int num=0;
sbit led0 = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led3 = P1^3;

int keypress() {
    

        if(SW == 0) {
            while(SW == 0);      
            return 1;
        }
    

    return 0;
}


int intr()
{
    if(keypress())
    {
        mode = (mode + 1) % 4;
        num = 0;
        return 1;
    }

    return 0;
}


int delay()
{
    int i, j;

    for(i = 0; i < 300; i++)
    {
        for(j = 0; j < 400; j++);

        if(intr())
            return 1;
    }

    return 0;
}


void counter()
{
    int a;

    if(intr())
        return;

    a = num;

    led0 = !(a % 2);
    a /= 2;

    led1 = !(a % 2);
    a /= 2;

    led2 = !(a % 2);
    a /= 2;

    led3 = !(a % 2);

    if(delay())
        return;
}


void runningled()
{
    if(intr())
        return;

    led0 = 0;
    led1 = 1;
    led2 = 1;
    led3 = 1;

    if(delay())
        return;

    led0 = 1;
    led1 = 0;

    if(delay())
        return;

    led1 = 1;
    led2 = 0;

    if(delay())
        return;

    led2 = 1;
    led3 = 0;

    if(delay())
        return;

    led3 = 1;
}


void alternate_toggle()
{
    if(intr())
        return;

    led0 = 0;
    led1 = 1;
    led2 = 0;
    led3 = 1;

    if(delay())
        return;

    led0 = 1;
    led1 = 0;
    led2 = 1;
    led3 = 0;

    if(delay())
        return;
}


void allonoff()
{
    if(intr())
        return;

    /* ALL ON */
    led0 = 0;
    led1 = 0;
    led2 = 0;
    led3 = 0;

    if(delay())
        return;

    /* ALL OFF */
    led0 = 1;
    led1 = 1;
    led2 = 1;
    led3 = 1;

    if(delay())
        return;
}


void main()
{
    while(1)
    {
        if(intr())
            continue;

        switch(mode)
        {
            case 0:
                runningled();
                break;

            case 1:
                num++;
                counter();
                break;

            case 2:
                alternate_toggle();
                break;

            case 3:
                allonoff();
                break;
        }
    }
}