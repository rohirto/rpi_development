//For building dynamically lin the library 
// $ gcc lgpio_ex.c -llgpio
//Documentation https://abyz.me.uk/lg/lgpio.html

#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>

int h, i;

int main(void)
{
    h = lgGpiochipOpen(4);
    lgGpioClaimOutput(h, 0, 17, 0);
    while (1)
    {
        lgGpioWrite(h, 17, 0);
        lguSleep(1);
        lgGpioWrite(h, 17, 1);
        lguSleep(1);
    }
    return EXIT_SUCCESS;
}