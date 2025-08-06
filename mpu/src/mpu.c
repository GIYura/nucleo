#include "mpu.h"

#include "stm32f411xe.h"

void MPU_Config(void)
{
    /* Disable MPU */
    MPU->CTRL = 0;

    /* Enable MemManage fault */
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

    /* Select region number (#0) */
    MPU->RNR = 0;

    /* Region base address (flash start address) */
    MPU->RBAR = 0x08000000;

    /* Region Attribute and Size Register */
    MPU->RASR = (0x0 << MPU_RASR_XN_Pos) |      // Execution of an instruction fetched from this region permitted
                (0x06 << MPU_RASR_AP_Pos) |     // Privileged and unprivileged read-only
                (0x0 << MPU_RASR_TEX_Pos) |     //
                (0x1 << MPU_RASR_C_Pos) |
                (0x1 << MPU_RASR_B_Pos) |       // Outer and inner write-back, no write allocate
                (0x0 << MPU_RASR_S_Pos) |       // no sharable
                (0x12 << MPU_RASR_SIZE_Pos) |   // 2^(0x12 + 1) = 0x80000 (512 kB)
                (1 << MPU_RASR_ENABLE_Pos);     // When the MPU is enabled, this region is enabled

    /* Enable MPU and enable privileged access */
    MPU->CTRL = MPU_CTRL_ENABLE_Msk | MPU_CTRL_PRIVDEFENA_Msk;

    /* Data sync barrier */
    __DSB();

    /* Instruction sync barrier */
    __ISB();
}
