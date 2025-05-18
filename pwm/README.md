### Description

PWM generation

### Set up

Target: NUCLEO-F411RE

### Connection 

| Nucleo pin   | GPIO   | Signal |
|--------------|--------|--------|
| CN10 (21)    | PA9    | PWM    |

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

### Debug

In order to debug target run the following:

```
| Command                                 | Desription                |
|-----------------------------------------|---------------------------|
| make ocd                                | run open ocd server       |
| make gdb                                | run gdb client            |
| target remote localhost:3333            | connect to the target     |
| monitor reset init                      | reset the target          |
| monitor flash write_image erase </.elf> | flash target with .elf    |
| monitor reset halt                      | reset and halt the target |
| monitor resume                          | run the target            |
| monitor halt                            | stop the target           |  
```

### Eclipse integration

1. Run Eclipse

2. Create new empty project

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

8. Run Open ocd server
```
make ocd
```

9. In Eclipse select Debug (F11)

### Notes

[Open OCD commands](https://openocd.org/doc/html/General-Commands.html)
[Linker script](https://www.opennet.ru/docs/RUS/gnu_ld/gnuld-3.html)

