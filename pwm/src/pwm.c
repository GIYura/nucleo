#include "pwm.h"

/*
 * NOTE: Table 9. Alternate function mapping
 * GPIO PA9 TIM1_CH2 AF01
 * */

void Pwm_Init(const Pwm_t* const pwm)
{
    /* Enable GPIOA and TIM1 clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    /* PA 9 AF mode */
    pwm->port->MODER &= ~(3 << (pwm->pin * 2));
    pwm->port->MODER |= (2 << (pwm->pin * 2));

    /* GPIO alternate function AF1 */
    pwm->port->AFR[1] &= ~(0xF << ((pwm->pin - 8) * 4));
    pwm->port->AFR[1] |=  (1 << ((pwm->pin - 8) * 4));

    TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
    TIM1->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);  /* PWM mode 1 */
    TIM1->CCMR1 |= TIM_CCMR1_OC2PE;            /* Output Compare 2 preload enable */

    TIM1->CCER |= TIM_CCER_CC2E;   /* Capture/Compare 2 output enable */

    TIM1->BDTR |= TIM_BDTR_MOE;    /* Main output enable */
    TIM1->CR1 |= TIM_CR1_ARPE;     /* Auto-reload preload enable */
    TIM1->EGR |= TIM_EGR_UG;       /* Update generation */
}

void Pwm_Config(const PwmConfig_t* const config)
{
    /* TIM1 settings for PWM */
    TIM1->PSC = 16 - 1;                 /* Prescaler: 16 МHz / 16 = 1 МHz */
    TIM1->ARR = config->periodMs - 1;   /* Period: 1000 -> freq 1 кHz */

    TIM1->CCR2 = (config->periodMs * config->duty) / 100;
}

void Pwm_Start(void)
{
    TIM1->CR1 |= TIM_CR1_CEN;
}

void Pwm_Stop(void)
{
    TIM1->CR1 &= ~TIM_CR1_CEN;
}
