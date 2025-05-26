#ifndef GPIO_H
#define GPIO_H

#include "stm32f411xe.h"

#include "gpio-name.h"

/* Port names */
#define PORTA   GPIOA
#define PORTB   GPIOB
#define PORTC   GPIOC
#define PORTD   GPIOD
#define PORTE   GPIOE
#define PORTH   GPIOH

/* port clock enable */
#define GPIO_CLOCK_ENABLE_PORTA (RCC->AHB1ENR |= (1 << 0))
#define GPIO_CLOCK_ENABLE_PORTB (RCC->AHB1ENR |= (1 << 1))
#define GPIO_CLOCK_ENABLE_PORTC (RCC->AHB1ENR |= (1 << 2))
#define GPIO_CLOCK_ENABLE_PORTD (RCC->AHB1ENR |= (1 << 3))
#define GPIO_CLOCK_ENABLE_PORTE (RCC->AHB1ENR |= (1 << 4))
#define GPIO_CLOCK_ENABLE_PORTH (RCC->AHB1ENR |= (1 << 7))

typedef enum
{
    PIN_STATE_LOW = 0,
    PIN_STATE_HIGH
} PIN_STATES;

/* Pin modes */
typedef enum
{
    PIN_MODE_INPUT = 0,
    PIN_MODE_OUTPUT,
    PIN_MODE_ALTERNATE,
    PIN_MODE_ANALOG,
} PIN_MODES;

/* Pin pull-up/pull-down */
typedef enum
{
    PIN_CONFIG_PUSH_PULL = 0,
    PIN_CONFIG_OPEN_DRAIN,
} PIN_CONFIGS;

/* Pin type */
typedef enum
{
    PIN_TYPE_NO_PULL_UP_PULL_DOWN = 0,
    PIN_TYPE_PULL_UP,
    PIN_TYPE_PULL_DOWN,
} PIN_TYPES;

/* Pin speed */
typedef enum
{
    PIN_SPEED_LOW = 0,
    PIN_SPEED_MEDIUM,
    PIN_SPEED_FAST,
    PIN_SPEED_HIGH,
} PIN_SPEEDS;

/* pin IRQ mode */
typedef enum
{
    PIN_NO_IRQ = 0,
    PIN_IRQ_RISING_EDGE,
    PIN_IRQ_FALLING_EDGE,
    PIN_IRQ_RISING_FALLING_EDGE
} PIN_IRQ_MODES;

/* pin IRQ priority */
typedef enum
{
    PIN_IRQ_VERY_LOW_PRIORITY = 0,
    PIN_IRQ_LOW_PRIORITY,
    PIN_IRQ_MEDIUM_PRIORITY,
    PIN_IRQ_HIGH_PRIORITY,
    PIN_IRQ_VERY_HIGH_PRIORITY
} PIN_IRQ_PRIORITIES;

typedef struct
{
    GPIO_TypeDef* port;
    PIN_NAMES pinName;
    PIN_MODES mode;
    PIN_TYPES type;
    PIN_SPEEDS speed;
    PIN_CONFIGS config;
    uint32_t altFunc;
} Gpio_t;

void GpioInit(  Gpio_t* obj,
                PIN_NAMES pinName,
                PIN_MODES mode,
                PIN_TYPES type,
                PIN_SPEEDS speed,
                PIN_CONFIGS config,
                uint32_t value);

void GpioWrite(Gpio_t* obj, uint32_t value);
uint32_t GpioRead(Gpio_t* obj);
void GpioToogle(Gpio_t* obj);

#endif /* GPIO_H */
