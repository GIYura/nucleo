### Nucleo Projects

This repository contains a collection of educational and experimental projects for the STM32F411 Nucleo board.
Each project demonstrates the use of low-level, CMSIS-based peripheral drivers — implemented without HAL or LL — to better understand how STM32 hardware works “under the hood.”

Peripheral drivers are stored in a shared submodule:
[here](https://github.com/GIYura/nucleo-shared)

### Repository Structure

| SW module name  |      Description                        |       Notes      |
|-----------------|-----------------------------------------|------------------|
| accel           | Accelerometer ADXL345 demo (SPI / I2C)  |                  |
| alignment       | Memory alignment                        |                  |
| blinky-os       | LED control over FreeRTOS               |                  |
| button          | External interrupt and debounce example |                  |
| button-os       | LED control over FreeRTOS               |                  |
| endianness      | Big/Little endian demo                  |                  |
| led             | Simple LED control via GPIO             |                  |
| led-abstraction | LED control over abstract interface     |                  |
| mpu             | MPU demo                                |                  |
| pwm             | PWM generation using TIM1               |                  |
| scripts         | Read option bytes                       |                  |
| serial          | UART logger                             |                  |
| network         | WI-FI demo (ESP8266)                    |                  |

### Build and Run

#### Prerequisites

Toolchain: ARM GCC (arm-none-eabi-gcc)

Debugger: OpenOCD

SDK: STM32CubeF4 (CMSIS + device headers)

Board: Nucleo-F411RE

**NOTE:** Ensure environment variables are set in **.config** (see **default.config** as a template):

```
GCC_PATH=<path-to->/gcc-arm-none-eabi/bin
SDK_PATH=<path-to->/STM32Cube_FW_F4_Vx.x.x
OCD_PATH=<path-to->/openocd/bin
BOARD_CFG=<path-to->/openocd/scripts/board/st_nucleo_f4.cfg
```

### Build the project

1. Clone the repository:

```
git clone git@github.com:GIYura/nucleo.git
```

2. Select one of the project directories, for example:

```
cd led/
```

3. Initialize and update the shared submodule:

```
git submodule update --init --recursive
```

4. Build the project:

```
make
```

5. To see all available build targets:

```
make help
```

### Eclipse integration

1. Run Eclipse

2. Create new empty C project

3. Import source files

4. Project->Propeties->C/C++ Build edit:
- Build command: make
- Build directory: specify path the makefile

5. Run->Debug Configuration:
- Project: specify a name
- C/C++ Application: specify path to .elf

6. Debugger:
- GDB command: specify path to gdb client
- Select Use remote target
- Debug server: Generic TCP/IP
- Protocol: remote
- Connection: localhost:3333

7. Startup
- Initialization commands: monitor reset halt
- Set breakpoint at: main
- Select Resume

8. Select Debug (F11)

