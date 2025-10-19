### Description

LED blinky. LED control over abstract interface.

### Set up

Target: NUCLEO-F411RE

### Connection 

| Nucleo pin   | GPIO   | LED    |
|--------------|--------|--------|
| CN7 (37)     | PC3    | Yellow |
| CN10 (30)    | PB13   | White  |
| Build-in     | PA5    | Green  |
| CN7 (28)     | PA0    | Green  |

### Get started

1. Clone

```
git clone git@github.com:GIYura/nucleo.git 
```
2. Navigate to 'led-absrtaction' directory

3. Navigate to submodules and update:

```
git submodules update --init
```
option:

```
git submodule add <url to submodule>
```

4. Create local **.config** file based on defalut.config

5. Edit local **.config** to specify PATH

6. Compile

```
make clean
make
```

7. Run help

```
make help
```

