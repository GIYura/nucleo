#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f411xe.h"

static uint8_t m_buffer[] = {
        0xaa,
        0xbb, 0xcc,
        0x12, 0x34, 0x56, 0x78
};

/*
NOTE:
*/
#if 0
typedef struct __attribute__((packed))
{
    uint8_t opCode;
    uint16_t param1;
    uint32_t param2;
} Packet_t;
#else
/*
NOTE:
*/
typedef struct
{
    uint8_t opCode;
    uint16_t param1;
    uint32_t param2;
} Packet_t;
#endif

/*
NOTE:
NOTE:
*/
static Packet_t packet = { .opCode = 0x11, .param1 = 0x2233, .param2 = 0x12345678 };

#if 0
ID021621 B3.2.8 Configuration and Control Register, CCR
UNALIGN_TRP, bit[3]
Controls the trapping of unaligned word or halfword accesses:
- 0 Trapping disabled.
- 1 Trapping enabled.
Unaligned load-store multiples and word or halfword exclusive accesses always fault.
#endif
static void UnalignTrapConfig(bool enable)
{
    if (enable)
    {
        SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    }
    else
    {
        SCB->CCR &= ~SCB_CCR_UNALIGN_TRP_Msk;
    }

    __DSB();
    __ISB();
}

int main(void)
{
/*
NOTE:
*/
#if 0
    UnalignTrapConfig(true);
#else
/*
NOTE:
*/
    UnalignTrapConfig(false);
#endif

    memset(&packet, 0, sizeof(Packet_t));

/*
 * CASE 1
*/
#if 0
    uint8_t size = sizeof(Packet_t);

    uint8_t* dst = (uint8_t*)&packet;
    for (uint8_t i = 0; i < size; i++)
    {
        dst[i] = m_buffer[i];
    }
#endif

/*
 * CASE 2
*/
#if 0
    uint8_t opCode = m_buffer[0];
    uint16_t param1 = (m_buffer[2] << 8) | (m_buffer[1] << 0);
    uint32_t param2 = (m_buffer[6] << 24) | (m_buffer[5] << 16) | (m_buffer[4] << 8) | (m_buffer[3] << 0);

    memcpy(&packet.opCode, &opCode, sizeof(uint8_t));
    memcpy(&packet.param1, &param1, sizeof(uint16_t));
    memcpy(&packet.param2, &param2, sizeof(uint32_t));

#endif

/*
 * CASE 3
*/
#if 0
    packet.opCode = (uint8_t)m_buffer[0];

    packet.param1 = ((uint16_t)m_buffer[2] << 8) |
                    (uint16_t)m_buffer[1];

    packet.param2 = ((uint32_t)m_buffer[6] << 24) |
                    ((uint32_t)m_buffer[5] << 16) |
                    ((uint32_t)m_buffer[4] << 8) |
                    (uint32_t)m_buffer[3];
#endif

/*
 * CASE 4
*/
#if 0
    memcpy(&packet.opCode, &m_buffer[0], sizeof(packet.opCode));
    memcpy(&packet.param1, &m_buffer[1], sizeof(packet.param1));
    memcpy(&packet.param2, &m_buffer[3], sizeof(packet.param2));
#endif

    while (1);

    return 0;
}

/*
 * CONCLUSION:
*/
