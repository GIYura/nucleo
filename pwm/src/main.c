#include "pwm.h"
#include "delay.h"

#define DUTY_MAX        18
#define DUTY_DEFAULT    50      /* % */
#define FREQ_DEFAULT    1000    /* Hz */

static PwmGpio_t m_pwm;
static PwmConfig_t m_pwmConfig = { .freqHz = FREQ_DEFAULT, .duty = DUTY_DEFAULT };

static uint8_t m_duty[DUTY_MAX] = { 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95 };
static uint8_t m_dutyIndex = 0;

int main(void)
{
    PwmInit(&m_pwm, PA_9);

    PwmConfig(&m_pwmConfig);

    PwmStart();

    while (1)
    {
        m_pwmConfig.duty = m_duty[m_dutyIndex];
        m_dutyIndex = (m_dutyIndex + 1) % DUTY_MAX;

        PwmConfig(&m_pwmConfig);

        DelayMs(200);
    }

    return 0;
}
