#include <stddef.h>

#include "assert.h"
#include "esp8266.h"
#include "event.h"
#include "gpio.h"

typedef enum
{
    ESP_STATE_IDLE = 0,
    ESP_STATE_AT_SENT,
    ESP_STATE_GMR_SENT,
    ESP_STATE_MODE_SENT,
    ESP_STATE_APCFG_SENT,
    ESP_STATE_ENABLE_CONN,
    ESP_STATE_READY,
} ESP_STATE;

static ESP_STATE m_state = ESP_STATE_IDLE;

static Gpio_t m_gpioLedGreen;
static Gpio_t m_gpioLedYellow;

static void OnEspResponse(ESP_RESPONSE response)
{
    Event_t e;

    switch (response)
    {
    case ESP_RESPONSE_OK:
        e.type = EVENT_ESP_NEXT;
        e.context = NULL;
        EventQueue_Enqueue(&e);
        break;

    case ESP_RESPONSE_LED_ON:
        e.type = EVENT_ESP_LED_ON;
        e.context = NULL;
        EventQueue_Enqueue(&e);
        break;

    case ESP_RESPONSE_LED_OFF:
        e.type = EVENT_ESP_LED_OFF;
        e.context = NULL;
        EventQueue_Enqueue(&e);
        break;

    default:
        /* TODO: handle error state */
        break;
    }
}

int main (void)
{
    EventQueueInit();

    GpioInit(&m_gpioLedGreen, PA_5, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);
    GpioInit(&m_gpioLedYellow, PC_3, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL_UP_PULL_DOWN, PIN_SPEED_FAST, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    ESP_Init();
    ESP_RegisterResponseHandler(&OnEspResponse);

    ESP_SendCommand("AT");
    m_state = ESP_STATE_AT_SENT;

    while (1)
    {
        Event_t e;
        if (EventQueue_Dequeue(&e))
        {
            if (e.type == EVENT_ESP_NEXT)
            {
                switch (m_state)
                {
                    case ESP_STATE_AT_SENT:
                        ESP_SendCommand("AT+GMR");
                        m_state = ESP_STATE_GMR_SENT;
                        break;

                    case ESP_STATE_GMR_SENT:
                        ESP_SendCommand("AT+CWMODE_CUR=2");
                        m_state = ESP_STATE_MODE_SENT;
                        break;

                    case ESP_STATE_MODE_SENT:
                        ESP_SendCommand("AT+CWSAP_CUR=\"ST-ESP8266\",\"12345678\",5,3");
                        m_state = ESP_STATE_APCFG_SENT;
                        break;

                    case ESP_STATE_APCFG_SENT:
                        ESP_SendCommand("AT+CIPMUX=1");
                        m_state = ESP_STATE_ENABLE_CONN;
                        break;

                    case ESP_STATE_ENABLE_CONN:
                        ESP_SendCommand("AT+CIPSERVER=1,3333");
                        m_state = ESP_STATE_READY;
                        break;

                    case ESP_STATE_READY:
                        m_state = ESP_STATE_IDLE;
                        GpioWrite(&m_gpioLedGreen, 1);
                        break;

                    default:
                        break;
                }
            }
            else if (e.type == EVENT_ESP_LED_ON)
            {
                GpioWrite(&m_gpioLedYellow, 1);
            }
            else if (e.type == EVENT_ESP_LED_OFF)
            {
                GpioWrite(&m_gpioLedYellow, 0);
            }
        }
    }

    return 0;
}

