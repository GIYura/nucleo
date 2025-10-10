#include <stdint.h>

#include "button.h"
#include "led.h"

#include "FreeRTOS.h"
#include "task.h"

static Button_t m_button;
static Led_t m_ledGreen;

static volatile uint32_t m_idleCycleCount = 0;

static void OnButton(void)
{
    LedToggle(&m_ledGreen);
}

int main(void)
{
    if (ButtonInit(&m_button, PC_13))
    {
        ButtonRegisterPressHandler(OnButton);

        LedInit(&m_ledGreen, PA_0);

        vTaskStartScheduler();
    }

    /* NOTE: never reach here */
    for (;;);

    return 0;
}

void vApplicationIdleHook(void)
{
   m_idleCycleCount++;
}

