#include <stdint.h>

/*
 * 0 - MPU disable
 * 1 - MPU enabled
 * */
#define USE_MPU 1

#include "mpu.h"

#if 1
/* NOTE: enabling MPU may lead to Hard Fault.
By default, MPU is disabled.

| value                | section    | MPU disabled | MPU enabled  |
|----------------------|------------|------------- |--------------|
| const global         | .rodata    | no effect    | hard fault   |
| static const global  | .rodata    | no effect    | hard fault   |
| static const local   | .rodata    | no effect    | hard fault   |
| const local          | stack      | changed (UB) | changed (UB) |
*/
#if 1
const uint16_t value = 10;
#endif

#if 0
static const uint16_t value = 10;
#endif

int main(void)
{
#if USE_MPU
    MPU_Config();
#endif

#if 1
    static const uint16_t value = 10;
#endif

    uint16_t* p = (uint16_t*)&value;
    *p = 20;

    return 0;
}
#endif

#if 0
N1256 6.7.3 Type qualifiers
Conclusion: If an attempt is made to modify an object defined with a const-qualified type through use
of an lvalue with non-const-qualified type, the behavior is undefined. If an attempt is
made to refer to an object defined with a volatile-qualified type through use of an lvalue
with non-volatile-qualified type, the behavior is undefined.
#endif

