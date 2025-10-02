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

static LedConfig_t m_ledG = { .led = &m_ledGreen, .periodMs = 250 };
static LedConfig_t m_ledY = { .led = &m_ledYellow, .periodMs = 100 };

static void LedBlinkTask(void *pvParams)
{
    LedConfig_t* param = (LedConfig_t*)pvParams;

    for (;;)
    {
        LedToggle(param->led);

        vTaskDelay(param->periodMs / portTICK_RATE_MS);
    }
}

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

int main(void)
{
    SystemInit();
/* optional */
    SystemCoreClockUpdate();
    NVIC_SetPriorityGrouping(0);

    LedInit(&m_ledGreen, PA_0);
    LedInit(&m_ledYellow, PC_3);

    xTaskCreateStatic(LedBlinkTask, "GREEN", 256, &m_ledG, 1, stack1, &tcb1);
    xTaskCreateStatic(LedBlinkTask, "YELLOW", 256, &m_ledY, 1, stack2, &tcb2);

    vTaskStartScheduler();

    for(;;);
    /* never reach here */
}

/* stack overflow hook */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask; (void)pcTaskName;

    __asm volatile("bkpt 5");

    for(;;);
}

#if 0
arm-none-eabi-nm led.elf | grep SVC_Handler
arm-none-eabi-nm led.elf | grep PendSV_Handler
arm-none-eabi-nm led.elf | grep SysTick_Handler
#endif

