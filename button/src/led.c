#include "led.h"

static Led_t m_led;

void Led_Init(const Led_t* const led)
{
    /* enable corresponding GPIO clock */
    if (led->port == GPIOA)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    }
    else if (led->port == GPIOB)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    }
    else if (led->port == GPIOC)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    }
    else if (led->port == GPIOD)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    }
    else if (led->port == GPIOE)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    }
    else if (led->port == GPIOH)
    {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    }
    else
    {
        return;
    }

    /* reset mode control bits */
    led->port->MODER &= ~(0x03 << (led->pin * 2));

    /* set gpio as output */
    led->port->MODER |= (1 << (led->pin * 2));

    /* no pull-up/down */
    led->port->PUPDR &= ~(0x03 << (led->pin * 2));

    /* set default value */
    if (led->defaultValue)
    {
        led->port->ODR |= (1 << led->pin);
    }
    else
    {
        led->port->ODR &= ~(1 << led->pin);
    }

    m_led.port = led->port;
    m_led.pin = led->pin;
}

void Led_On(const Led_t* const led)
{
    led->port->ODR |= (1 << led->pin);
}

void Led_Off(const Led_t* const led)
{
    led->port->ODR &= ~(1 << led->pin);
}

void Led_Toggle(void* context)
{
    m_led.port->ODR ^= (1 << m_led.pin);
}
