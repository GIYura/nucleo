#include "pwm.h"

static Pwm_t m_pwm = { .port = GPIOA, .pin = 9 };
static PwmConfig_t m_pwmConfig = { .periodMs = 1000, .duty = 30 };

int main(void)
{
    Pwm_Init(&m_pwm);

    Pwm_Config(&m_pwmConfig);

    Pwm_Start();

    while (1);

    return 0;
}
