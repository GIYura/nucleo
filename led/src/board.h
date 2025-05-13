#ifndef BOARD_H
#define BOARD_H

#define LED_MAX         3

#include "led.h"

Led_t* BoardLedConfig_Get(void);

void SysTick_Handler(void);

void DelayMs(uint32_t ms);

#endif /* BOARD_H */
