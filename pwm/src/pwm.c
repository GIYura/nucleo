#include <assert.h>
#include <stddef.h>

#include "stm32f411xe.h"
#include "pwm.h"

/*
 * NOTE: bring down TIM1 frequency to 1 MHz
 * */
#define PRESCALER_VALUE (uint32_t)(((SystemCoreClock) / 1000000) - 1)
#define TIMER_FREQUENCY (uint32_t)((SystemCoreClock) / (PRESCALER_VALUE + 1))

static Gpio_t m_gpio;

static void TimerInit(void);

void PwmInit(PwmGpio_t* const gpio, PIN_NAMES pinName)
{
    assert(gpio != NULL);

    gpio->gpio = &m_gpio;

    GpioInit(gpio->gpio, pinName, PIN_MODE_ALTERNATE, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_AF_1);

    TimerInit();
}

void PwmConfig(const PwmConfig_t* const config)
{
    assert(config->freqHz > 0);
    assert(config->duty <= 100);

    uint32_t period = 0;
    /* TIM1 settings for PWM */
    TIM1->PSC = PRESCALER_VALUE;
    period = (TIMER_FREQUENCY / config->freqHz) - 1;
    TIM1->ARR = period;

    TIM1->CCR2 = (period * config->duty) / 100;
}

void PwmStart(void)
{
    TIM1->CR1 |= TIM_CR1_CEN;
}

void PwmStop(void)
{
    TIM1->CR1 &= ~TIM_CR1_CEN;
}

static void TimerInit(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM1->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);  /* PWM mode 1 */
    TIM1->CCMR1 |= TIM_CCMR1_OC2PE;            /* Output Compare 2 preload enable */

    TIM1->CCER |= TIM_CCER_CC2E;   /* Capture/Compare 2 output enable */

    TIM1->BDTR |= TIM_BDTR_MOE;    /* Main output enable */
    TIM1->CR1 |= TIM_CR1_ARPE;     /* Auto-reload preload enable */
    TIM1->EGR |= TIM_EGR_UG;       /* Update generation */
}
