#include <stddef.h>
#include <stdint.h>

#include "gpio.h"
#include "gpio-name.h"

#if 0
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
#endif

extern const GpioOps_t g_GpioOps;

static GpioHandle_t m_ledGreen = { .ops = &g_GpioOps };
static GpioHandle_t m_ledYellow = { .ops = &g_GpioOps };
static GpioHandle_t m_ledRed = { .ops = &g_GpioOps };

static GpioHandle_t m_ledGreenExt = { .ops = &g_GpioOps };

static uint32_t m_counter = 1;

int main (void)
{
#if 0
    m_ledGreen.ops->open(&m_ledGreen, PA_5, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);
    m_ledYellow.ops->open(&m_ledYellow, PC_3, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, PIN_STATE_LOW);

    while (1)
    {
        m_ledGreen.ops->toggle(&m_ledGreen);
        m_ledYellow.ops->toggle(&m_ledYellow);

        for(int i = 0; i < 100000; i++);
    }
#endif

#if 1
    m_ledGreen.ops->open(&m_ledGreen, PIN_GPIOA1_3, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, 0);
    m_ledYellow.ops->open(&m_ledYellow, PIN_GPIOA1_2, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, 0);
    m_ledRed.ops->open(&m_ledRed, PIN_GPIOA1_1, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, 0);

    m_ledGreenExt.ops->open(&m_ledGreenExt, PIN_GPIOA2_1, PIN_MODE_OUTPUT, PIN_TYPE_NO_PULL, PIN_STRENGTH_HIGH, PIN_CONFIG_PUSH_PULL, 0);

    while (1)
    {
        m_counter++;

        m_ledGreen.ops->toggle(&m_ledGreen);
        m_ledYellow.ops->toggle(&m_ledYellow);
        m_ledRed.ops->toggle(&m_ledRed);

        m_ledGreenExt.ops->toggle(&m_ledGreenExt);

        for(int i = 0; i < 500000; i++);
    }
#endif

#if 0
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
#endif
    return 0;
}

