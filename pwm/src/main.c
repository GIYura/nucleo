#include "pwm.h"

#define DUTY_MAX        18
#define DUTY_DEFAULT    50      /* % */
#define FREQ_DEFAULT    5000   /* Hz */

static Pwm_t m_pwm = { .port = GPIOA, .pin = 9 };
static PwmConfig_t m_pwmConfig = { .freqHz = FREQ_DEFAULT, .duty = DUTY_DEFAULT };

static uint8_t m_duty[DUTY_MAX] = { 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95 };
static uint8_t m_dutyIndex = 0;

volatile static uint32_t m_ticks = 0;

void SysTick_Handler(void)
{
    m_ticks++;
}

static void DelayMs(uint32_t ms)
{
    uint32_t start = m_ticks;

    while ((m_ticks - start) < ms);
}

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000);

    Pwm_Init(&m_pwm);

    Pwm_Config(&m_pwmConfig);

    Pwm_Start();

    while (1)
    {
        m_pwmConfig.duty = m_duty[m_dutyIndex];
        m_dutyIndex = (m_dutyIndex + 1) % DUTY_MAX;
        Pwm_Config(&m_pwmConfig);

        DelayMs(200);
    }

    return 0;
}
