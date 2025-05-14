#include <stddef.h>

#include "button.h"

static ButtonEventHandler m_onButton = NULL;

static volatile bool m_buttonDebouncePending = false;

static void DebounceTimer_Init(uint32_t timeoutMs);
static void DebounceTimer_Start(void);

void Button_Init(const Button_t* const button)
{
    if (button->port == GPIOA)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    }
    else if (button->port == GPIOB)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    }
    else if (button->port == GPIOC)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    }
    else if (button->port == GPIOD)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    }
    else if (button->port == GPIOE)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    }
    else if (button->port == GPIOH)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    }
    else
    {
        return;
    }

    /* System configuration controller clock enabled */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* set gpio as input */
    button->port->MODER &= ~(0x03 << button->pin * 2);

    /* pull-up enabled */
    button->port->PUPDR &= ~(0x03 << (button->pin * 2));
    button->port->PUPDR |= (0x01 << (button->pin * 2));

    DebounceTimer_Init(button->debounceTimeout);
}

void Button_RegisterPressHandler(const Button_t* const button, ButtonEventHandler callback)
{
    /* set EXTI13 on PC13 */
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

    /* Interrupt request from line 13 is not masked */
    EXTI->IMR |= EXTI_IMR_IM13;

    /* Falling trigger enabled (for Event and Interrupt) for input line */
    EXTI->FTSR |= EXTI_FTSR_TR13;

    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 2);

    m_onButton = callback;
}

static void DebounceTimer_Init(uint32_t timeoutMs)
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

static void DebounceTimer_Start(void)
{
    TIM2->CNT = 0;

    /* Counter enabled */
    TIM2->CR1 |= TIM_CR1_CEN;
}

void EXTI15_10_IRQHandler(void)
{
    /* selected trigger request occurred */
    if (EXTI->PR & EXTI_PR_PR13)
    {
        /*read-clear-write-1 */
        EXTI->PR = EXTI_PR_PR13;

        if (!m_buttonDebouncePending)
        {
            m_buttonDebouncePending = true;

            DebounceTimer_Start();
        }
    }
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
            (*m_onButton)(NULL);
        }
        m_buttonDebouncePending = false;
    }
}

