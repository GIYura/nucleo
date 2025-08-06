#include "helper.h"

#if 0
const uint16_t a1 __attribute__((aligned(4))) = 0xAAAA;
const uint16_t b1 __attribute__((aligned(4))) = 0xBBBB;
#else
const uint16_t a1 = 0xAAAA;
const uint16_t b1 = 0xBBBB;
#endif
