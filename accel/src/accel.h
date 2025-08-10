#ifndef ACCEL_H
#define ACCEL_H

#include <stdint.h>

void AccelInit(void);
void AccelGetId(uint8_t* const id);
void AccelDumpRegisters(void);

#endif /* ACCEL_H */
