#include "led.h"
#include "gpio.h"
#include "led-gpio.h"
#include "delay.h"

static Gpio_t m_ledGpioGreenInternal;
static Gpio_t m_ledGpioGreenExternal;
static Gpio_t m_ledGpioWhite;
static Gpio_t m_ledGpioYellow;

static LedGpioContext_t ledGreenInternalCtx = { .gpio = &m_ledGpioGreenInternal, .gpioName = PA_5 };
static LedGpioContext_t ledGreenExternalCtx = { .gpio = &m_ledGpioGreenExternal, .gpioName = PA_0 };
static LedGpioContext_t ledWhiteCtx = { .gpio = &m_ledGpioWhite, .gpioName = PB_13 };
static LedGpioContext_t ledYellowCtx = { .gpio = &m_ledGpioYellow, .gpioName = PC_3 };

static Led_t m_ledGreenInternal;
static Led_t m_ledGreenExternal;
static Led_t m_ledWhite;
static Led_t m_ledYellow;

int main(void)
{
    LedInit(&m_ledGreenInternal, &g_ledGpioDriver, &ledGreenInternalCtx);
    LedInit(&m_ledGreenExternal, &g_ledGpioDriver, &ledGreenExternalCtx);
    LedInit(&m_ledWhite, &g_ledGpioDriver, &ledWhiteCtx);
    LedInit(&m_ledYellow, &g_ledGpioDriver, &ledYellowCtx);

    while (1)
    {
        LedToggle(&m_ledGreenInternal);
        LedToggle(&m_ledGreenExternal);
        LedToggle(&m_ledWhite);
        LedToggle(&m_ledYellow);

        DelayMs(250);
    }

    return 0;
}
