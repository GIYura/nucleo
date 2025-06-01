#include "led.h"
#include "delay.h"

int main(void)
{
    LedInit(LED_GREEN, PA_5);
    LedInit(LED_GREEN_EXT, PA_0);
    LedInit(LED_YELLOW, PC_3);
    LedInit(LED_WHITE, PB_13);

    while (1)
    {
        LedToggle(LED_GREEN);
        LedToggle(LED_YELLOW);
        LedToggle(LED_WHITE);
        LedToggle(LED_GREEN_EXT);

        DelayMs(250);
    }

    return 0;
}
