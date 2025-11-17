### Description

Demo project to demonstrate control LED over network.

### Set up

Target: NUCLEO-F411RE
WIFI: ESP8266

### Connection 

| Nucleo pin   | GPIO        | ESP pin      |
|--------------|-------------|--------------|
| CN10 (33)    | PA10        | tx           |
| CN10 (21)    | PA9         | rx           |
| CN7 (18)     | +5V         | +5V          |
| CN7 (20)     | GND         | GND          |

| Nucleo pin   | GPIO        | LED pin      |
|--------------|-------------|--------------|
| CN7 (37)     | PC3         | +            |
| CN7 (22)     | GND         | -            |


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

### Wifi connection

NOTE: default mode:
- Access point (AP ST-ESP8266)
- password: 1234578
- TCP port: 3333

1. Load firmware to the target

2. Browse wifi network named ST-ESP8266

3. Connnect to ST-ESP8266 network

4. Run

```
ping <server ip-address>
nc -v <server ip-address> <port>
```

5. Run command

```
LED_ON
LED_OFF
```