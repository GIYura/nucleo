#ifndef PWM_H
#define PWM_H

#include "gpio.h"
#include "gpio-name.h"

/* PWM gpio definition */
typedef struct
{
    Gpio_t* gpio;
} PwmGpio_t;

/* PWM config */
typedef struct
{
    uint32_t freqHz;
    uint32_t duty;
} PwmConfig_t;

/*Brief: PWM gpio initialization
 * [in] - gpio - pointer to gpio object
 * [in] - pinName - name of the pin defined in gpio-name.h
 * [out] - none
 * */
void PwmInit(PwmGpio_t* const gpio, PIN_NAMES pinName);

/*Brief: PWM config
 * [in] - config - pointer to config object
 * [out] - none
 * */
void PwmConfig(const PwmConfig_t* const config);

/*Brief: PWM start
 * [in] - none
 * [out] - none
 * */
void PwmStart(void);

/*Brief: PWM stop
 * [in] - none
 * [out] - none
 * */
void PwmStop(void);

#endif /* PWM_H */
