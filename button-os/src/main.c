#include <stdint.h>

#include "button.h"
#include "FreeRTOS.h"
#include "task.h"

static Button_t m_button;

static uint32_t m_buttonPressCounter = 0;

static volatile uint32_t m_idleCycleCount = 0;

static void OnButton(void)
{
    ++m_buttonPressCounter;
}

int main(void)
{
    if (ButtonInit(&m_button, PC_13))
    {
        ButtonRegisterPressHandler(OnButton);
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

