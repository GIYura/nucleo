#include <stdint.h>

#include "button.h"

static Button_t m_button;

static uint32_t m_buttonPressCounter = 0;

static void OnButton(void)
{
    ++m_buttonPressCounter;
}

int main(void)
{
    ButtonInit(&m_button, PC_13);
    ButtonRegisterPressHandler(OnButton);

    while (1);

    return 0;
}
