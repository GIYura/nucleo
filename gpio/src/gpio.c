#include <assert.h>
#include <stddef.h>

#include "gpio.h"

void GpioInit(  Gpio_t* const obj,
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
    obj->pinIndex = (obj->pinName & 0x0F);

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

    obj->port->OSPEEDR |= (speed << (obj->pinIndex * 2));
    obj->port->PUPDR |= (type << (obj->pinIndex * 2));
    obj->port->MODER |= (mode << (obj->pinIndex * 2));

    if (mode == PIN_MODE_ALTERNATE)
    {
        if (obj->pinIndex <= 7)
        {
            obj->port->AFR[0] |= (value << (obj->pinIndex * 4));
        }
        else
        {
            obj->port->AFR[1] |= (value << (obj->pinIndex * 4));
        }
    }

    if (mode == PIN_MODE_OUTPUT)
    {
        obj->port->OTYPER = (config << (obj->pinIndex));

        if (value == PIN_STATE_LOW)
        {
            obj->port->BSRR = (1 << (obj->pinIndex + 16));
        }
        else
        {
            obj->port->BSRR = (1 << (obj->pinIndex));
        }
    }
}

void GpioWrite(const Gpio_t* const obj, uint32_t value)
{
    assert(obj != NULL);

    if (obj->pinName == NC)
    {
        return;
    }

    if (value == 0)
    {
        obj->port->BSRR = (1 << (obj->pinIndex + 16));
    }
    else
    {
        obj->port->BSRR = (1 << (obj->pinIndex));
    }
}

uint32_t GpioRead(const Gpio_t* const obj)
{
    assert(obj != NULL);

    uint16_t value = obj->port->IDR;

    value &= (1 << (obj->pinIndex));

    return value ? 1 : 0;
}

void GpioToogle(const Gpio_t* const obj)
{
    assert(obj != NULL);

    uint32_t odr = (obj->port->ODR);

    if (odr & (1 << obj->pinIndex))
    {
        obj->port->BSRR = (1 << (obj->pinIndex + 16));
    }
    else
    {
        obj->port->BSRR = (1 << (obj->pinIndex));
    }
}

void GpioSetInterrupt(Gpio_t* obj, PIN_IRQ_MODES irqMode, PIN_IRQ_PRIORITIES irqPriority, GpioIrqHandler* handler)
{
    /*TODO:*/
    if (obj->pinName == NC)
    {
        return;
    }

    assert(handler != NULL);

    IRQn_Type irqNumber = EXTI0_IRQn;
    uint32_t priority = 0;

    obj->irqHandler = handler;

    switch (irqMode)
    {
        case PIN_IRQ_RISING:

            break;

        case PIN_IRQ_FALING:

            break;

        case PIN_IRQ_RISING_FALING:

            break;

        default:
            break;
    }

    switch (irqPriority)
    {
        case PIN_IRQ_PRIORITY_LOW:

            break;

        case PIN_IRQ_PRIORITY_MEDIUM:

            break;

        case PIN_IRQ_PRIORITY_HIGH:

            break;
        default:
            break;
    }

    switch (obj->pinIndex)
    {
        case 0:
            irqNumber = EXTI0_IRQn;
            break;

        case 1:
            irqNumber = EXTI1_IRQn;
            break;

        case 2:
            irqNumber = EXTI2_IRQn;
            break;

        case 3:
            irqNumber = EXTI4_IRQn;
            break;

        case 4:
            irqNumber = EXTI4_IRQn;
            break;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            irqNumber = EXTI9_5_IRQn;
            break;

        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            irqNumber = EXTI15_10_IRQn;
            break;

        default:
            break;
    }


    NVIC_SetPriority(irqNumber, priority);
    NVIC_EnableIRQ(irqNumber);
}

