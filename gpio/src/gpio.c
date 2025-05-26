#include <assert.h>

#include "gpio.h"

void GpioInit(  Gpio_t* obj,
                PIN_NAMES pinName,
                PIN_MODES mode,
                PIN_TYPES type,
                PIN_SPEEDS speed,
                PIN_CONFIGS config,
                uint32_t value)
{
    assert(obj != NULL);

    if (pinName == NC)
    {
        return;
    }

    obj->pinName = pinName;

    if ((obj->pinName & 0xF0) == 0x00)
    {
        obj->port = PORTA;
        GPIO_CLOCK_ENABLE_PORTA;
    }
    else if ((obj->pinName & 0xF0) == 0x10)
    {
        obj->port = PORTB;
        GPIO_CLOCK_ENABLE_PORTB;
    }
    else if ((obj->pinName & 0xF0) == 0x20)
    {
        obj->port = PORTC;
        GPIO_CLOCK_ENABLE_PORTC;
    }
    else if ((obj->pinName & 0xF0) == 0x30)
    {
        obj->port = PORTD;
        GPIO_CLOCK_ENABLE_PORTD;
    }
    else if ((obj->pinName & 0xF0) == 0x40)
    {
        obj->port = PORTE;
        GPIO_CLOCK_ENABLE_PORTE;
    }
    else if ((obj->pinName & 0xF0) == 0x50)
    {
        obj->port = PORTH;
        GPIO_CLOCK_ENABLE_PORTH;
    }
    else
    {
        assert(0);
    }

    obj->port->OSPEEDR |= (speed << (obj->pinName * 2));
    obj->port->PUPDR |= (type << (obj->pinName * 2));
    obj->port->MODER |= (mode << (obj->pinName * 2));

    if (mode == PIN_MODE_ALTERNATE)
    {
        if (obj->pinName <= 7)
        {
            obj->port->AFR[0] |= (value << (obj->pinName * 4));
        }
        else
        {
            obj->port->AFR[1] |= (value << (obj->pinName * 4));
        }
    }

    if (mode == PIN_MODE_OUTPUT)
    {
        obj->port->OTYPER = (config << (obj->pinName * 2));

        if (value == PIN_STATE_LOW)
        {
            obj->port->BSRR = (1 << (obj->pinName + 16));
        }
        else
        {
            obj->port->BSRR = (1 << (obj->pinName));
        }
    }
}

void GpioWrite(Gpio_t* obj, uint32_t value)
{
    assert(obj != NULL);

    if (obj->pinName == NC)
    {
        return;
    }

    if (value == 0)
    {
        obj->port->BSRR = (1 << (obj->pinName + 16));
    }
    else
    {
        obj->port->BSRR = (1 << (obj->pinName));
    }
}

uint32_t GpioRead(Gpio_t* obj)
{
    assert(obj != NULL);

    uint16_t value = obj->port->IDR;

    value &= (1 << (obj->pinName));

    return value ? 1 : 0;
}

/*TODO:*/
void GpioToogle(Gpio_t* obj)
{
    assert(obj != NULL);

    obj->port->ODR ^= (1 << (obj->pinName));
}

