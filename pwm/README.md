### Description

PWM generation

### Set up

Target: NUCLEO-F411RE

### Connection 

| Nucleo pin   | GPIO   | Signal  |
|--------------|--------|---------|
| CN10 (21)    | PA9    | LED (+) |
| CN10 (20)    | GND    | LED (-) |

### Get started

1. Clone

```
git clone git@github.com:GIYura/nucleo.git 
```
2. Navigate to pwm directory

3. Create local **.config** file based on defalut.config

4. Edit local **.config** to specify PATH

5. Compile

```
make clean
make
```

6. Run help

```
make help
```

