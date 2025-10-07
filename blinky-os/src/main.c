#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "gpio-name.h"
#include "assert.h"

typedef struct
{
    Led_t* led;
    uint32_t periodMs;
} LedConfig_t;

static Led_t m_ledGreen;
static Led_t m_ledYellow;

static LedConfig_t m_ledG = { .led = &m_ledGreen, .periodMs = 500 };
static LedConfig_t m_ledY = { .led = &m_ledYellow, .periodMs = 100 };

static volatile uint32_t m_idleCycleCount = 0;

static void LedBlinkTask(void *pvParams)
{
    LedConfig_t* param = (LedConfig_t*)pvParams;

    for (;;)
    {
        LedToggle(param->led);

        vTaskDelay(param->periodMs / portTICK_RATE_MS);
    }
}

#if 0
/* Idle task memory (mandatory on static memory allocation) */
static StaticTask_t xIdleTCB;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
static StaticTask_t tcb1;
static StackType_t stack1[256];
static StaticTask_t tcb2;
static StackType_t stack2[256];

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTCB, StackType_t** ppxIdleStack, uint32_t* pulIdleStackSize)
{
    *ppxIdleTCB = &xIdleTCB;
    *ppxIdleStack = xIdleStack;
    *pulIdleStackSize = configMINIMAL_STACK_SIZE;
}
#endif

int main(void)
{
    SystemInit();
/* optional */
    SystemCoreClockUpdate();
    NVIC_SetPriorityGrouping(0);

    LedInit(&m_ledGreen, PA_0);
    LedInit(&m_ledYellow, PC_3);

#if 0
/* NOTE: used for static allocated functions */
    xTaskCreateStatic(LedBlinkTask, "GREEN", 256, &m_ledG, 1, stack1, &tcb1);
    xTaskCreateStatic(LedBlinkTask, "YELLOW", 256, &m_ledY, 1, stack2, &tcb2);
#endif

    BaseType_t t1 = xTaskCreate(LedBlinkTask, "Green", configMINIMAL_STACK_SIZE, &m_ledG, 1, NULL);
    BaseType_t t2 = xTaskCreate(LedBlinkTask, "Yellow", configMINIMAL_STACK_SIZE, &m_ledY, 1, NULL);

    if (t1 == pdTRUE && t2 == pdTRUE)
    {
        vTaskStartScheduler();
    }

    for(;;);
    /* never reach here */
}

void vApplicationIdleHook(void)
{
   m_idleCycleCount++;
}

#if 0
NOTE: used for debug only

/* stack overflow hook */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask; (void)pcTaskName;

    __asm volatile("bkpt 5");

    for(;;);
}
#endif

#if 0
/* NOTE:
 * Commands to explore .elf file
 * These handlers should be re-defined as aliases
 * */
arm-none-eabi-nm .elf | grep SVC_Handler
arm-none-eabi-nm .elf | grep PendSV_Handler
arm-none-eabi-nm .elf | grep SysTick_Handler
#endif

