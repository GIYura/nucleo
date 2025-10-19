### Description

Demo project to demonstrate communication with accelerometer over SPI/I2C.

### Set up

Target: NUCLEO-F411RE
Accelerometer: ADXL345

### SPI Connection 

**NOTE:** SPI1 example

| Nucleo pin   | GPIO        | Accel pin    |
|--------------|-------------|--------------|
| CN10 (11)    | PA5 (sck)   | SCL          |
| CN10 (13)    | PA6 (miso)  | SDO          |
| CN10 (15)    | PA7 (mosi)  | SDA          |
| CN7 (28)     | PA0 (cs)    | CS           |

### I2C Connection 

**NOTE:** I2C1 example

| Nucleo pin   | GPIO        | Accel pin    |
|--------------|-------------|--------------|
| CN10 (3)     | PB8 (scl)   | SCL          |
| CN10 (5)     | PB9 (sda)   | SDA          |

**NOTE:** I2C connection requires: CS->VCC; SDO->GND (accel address 53h)

### Get started

1. Clone

```
git clone git@github.com:GIYura/nucleo.git 
```

2. Create local **.config** file based on defalut.config

3. Edit local **.config** to specify PATH

4. Compile

```
make clean
make
```

5. Run help

```
make help
```

