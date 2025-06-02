#include <stdint.h>

#include "button.h"

static uint32_t m_buttonPressCounter = 0;

static void OnButton(void)
{
    ++m_buttonPressCounter;
}

int main(void)
{
    ButtonInit(BUTTON_INTERNAL, PC_13);
    ButtonRegisterPressHandler(OnButton);

    while (1);

    return 0;
}
