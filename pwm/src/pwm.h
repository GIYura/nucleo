#ifndef PWM_H
#define PWM_H

#include "stm32f411xe.h"

typedef struct
{
    GPIO_TypeDef* port;
    uint8_t pin;
} Pwm_t;

typedef struct
{
    uint32_t periodMs;
    uint32_t duty;
} PwmConfig_t;

void Pwm_Init(const Pwm_t* const pwm);
void Pwm_Config(const PwmConfig_t* const config);
void Pwm_Start(void);
void Pwm_Stop(void);

#endif /* PWM_H */
