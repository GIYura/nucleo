#include <stddef.h>

#include "assert.h"
#include "button.h"

#define BUTTON_DEBOUNCE_TIME    20     /* ms */

#define TIM_2_CLOCK_ENABLE      (RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN))

static ButtonEventHandler m_onButton = NULL;

static TIM_TypeDef* m_debounceTimer = TIM2;

static void OnButtonEvent(void);
static void DebounceTimerInit(TIM_TypeDef* const tim, uint32_t timeoutMs);
static void DebounceTimerStart(TIM_TypeDef* const tim);

void ButtonInit(Button_t* const button, PIN_NAMES gpioName)
{
    ASSERT(button != NULL);

    GpioInit(&button->gpio, gpioName, PIN_MODE_INPUT, PIN_TYPE_PULL_UP, PIN_SPEED_HIGH, PIN_CONFIG_PUSH_PULL, 1);

    GpioSetInterrupt(&button->gpio, PIN_IRQ_FALING, PIN_IRQ_PRIORITY_HIGH, OnButtonEvent);

    DebounceTimerInit(m_debounceTimer, BUTTON_DEBOUNCE_TIME);
}

void ButtonRegisterPressHandler(ButtonEventHandler callback)
{
    m_onButton = callback;
}

static void OnButtonEvent(void)
{
    DebounceTimerStart(m_debounceTimer);
}

static void DebounceTimerInit(TIM_TypeDef* const tim, uint32_t timeoutMs)
{
    TIM_2_CLOCK_ENABLE;

    /* Prescaler value 16 Mhz / 16 = 1 khz (1 ms) */
    tim->PSC = 16000 - 1;

    /* Auto-reload value */
    tim->ARR = timeoutMs - 1;

    /* One-pulse mode */
    tim->CR1 |= TIM_CR1_OPM;

    /* Update interrupt enabled */
    tim->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 1);
}

static void DebounceTimerStart(TIM_TypeDef* const tim)
{
    tim->CNT = 0;

    /* Counter enabled */
    tim->CR1 |= TIM_CR1_CEN;
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
