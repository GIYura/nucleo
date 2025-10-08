#include <stddef.h>

#include "assert.h"
#include "button.h"

#define BUTTON_DEBOUNCE_TIME    20     /* ms */

static Gpio_t m_button;

static ButtonEventHandler m_onButton = NULL;

static void OnButtonEvent(void);
static void DebounceTimerInit(uint32_t timeoutMs);
static void DebounceTimerStart(void);

void ButtonInit(Button_t* button, PIN_NAMES gpioName)
{
    ASSERT(button != NULL);

    button->gpio = &m_button;

    GpioInit(button->gpio, gpioName, PIN_MODE_INPUT, PIN_TYPE_PULL_UP, PIN_SPEED_HIGH, PIN_CONFIG_PUSH_PULL, 1);

    GpioSetInterrupt(button->gpio, PIN_IRQ_FALING, PIN_IRQ_PRIORITY_HIGH, OnButtonEvent);

    DebounceTimerInit(BUTTON_DEBOUNCE_TIME);
}

void ButtonRegisterPressHandler(ButtonEventHandler callback)
{
    m_onButton = callback;
}

static void OnButtonEvent(void)
{
    DebounceTimerStart();
}

static void DebounceTimerInit(uint32_t timeoutMs)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* Prescaler value 16 Mhz / 16 = 1 khz (1 ms) */
    TIM2->PSC = 16000 - 1;

    /* Auto-reload value */
    TIM2->ARR = timeoutMs - 1;

    /* One-pulse mode */
    TIM2->CR1 |= TIM_CR1_OPM;

    /* Update interrupt enabled */
    TIM2->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 1);
}

static void DebounceTimerStart(void)
{
    TIM2->CNT = 0;

    /* Counter enabled */
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler(void)
{
    /* Update interrupt pending */
    if (TIM2->SR & TIM_SR_UIF)
    {
        /* read-clear-write-0 */
        TIM2->SR &= ~TIM_SR_UIF;

        if (m_onButton != NULL)
        {
            (*m_onButton)();
        }
    }
}
