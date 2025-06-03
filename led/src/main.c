#include "led.h"
#include "delay.h"

static Led_t m_ledGreenInternal;
static Led_t m_ledGreenExternal;
static Led_t m_ledYellow;
static Led_t m_ledWhite;

int main(void)
{
    LedInit(&m_ledGreenInternal, PA_5);
    LedInit(&m_ledGreenExternal, PA_0);
    LedInit(&m_ledYellow, PC_3);
    LedInit(&m_ledWhite, PB_13);

    while (1)
    {
        LedToggle(&m_ledGreenInternal);
        LedToggle(&m_ledGreenExternal);
        LedToggle(&m_ledYellow);
        LedToggle(&m_ledWhite);

        DelayMs(250);
    }

    return 0;
}
