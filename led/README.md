### Description

LED blinky

### Set up

Target: NUCLEO-F411RE

### Connection 

| Nucleo pin   | GPIO   | LED    |
|--------------|--------|--------|
| CN7 (37)     | PC3    | Yellow |
| CN10 (30)    | PB13   | White  |
| Build-in     | PA5    | Green  |

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

