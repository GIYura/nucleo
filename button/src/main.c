#include "button.h"
#include "led.h"

#define BUTTON_DEBOUNCE_TIME    20     /* ms */

static Button_t m_button = { "USER", .port = GPIOC, .pin = 13, .debounceTimeout = BUTTON_DEBOUNCE_TIME };
static Led_t m_led = { "WHITE", .port = GPIOB, .pin = 13, .defaultValue = 0 };

int main(void)
{
    Led_Init(&m_led);

    Button_Init(&m_button);

    Button_RegisterPressHandler(&m_button, Led_Toggle);

    while (1);

    return 0;
}
