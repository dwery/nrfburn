# nrfburn #

This hardware/software package allows full access to the flash area of the Nordic nRF24LU1+ and nRF24LE1 microcontrollers.

The programmer is based on an Atmel ATmega AVR which handles the SPI communication and access to the flash area of the Nordic nRF MCUs. It can erase, write and read the MainBlock and InfoBlock of the nRF flash.

NOTE: Flash read access is only possible if it has been allowed by the nRF InfoPage configuration.

nrfburn can be used to access the flash of "bricked" nRF24LU1+ (both versions: F16 and F32) or nRF24LE1 MCUs. You can reprogram the bootloader or write any other HEX file into the flash area.

The programmer hardware is built around an Atmel ATmega88p microcontroller, but ATmega168p or ATmega328p can be used as well. The programmer firmware uses obdev's V-USB software USB implementation for communication with the host PC. The PCB has breakout footprints compatibile with the SparkFun nRF24LU1+ breakout board, and a generic nRF24LU1+ dongle. This means that if you have the right pin headers soldered on the the programmer and the breakouts you can just plug these breakouts into the programmer to flash the nRF MCU. It is also possible to program the nRF chips in other breakout boards, but you will need some way to connect these with the programmer.

## Project directory structure ##

  * **circut** - Eagle CAD files for the AVR programmer circuit.

  * **firmware** - The AVR programmer firmware. It parses requests received from USB and executes SPI commands to access the nRF flash.

  * **host** - PC program which sends commands to the AVR programmer. Written in C++, it is cross-platform and can be compiled with gcc for Linux or Windows (MinGW).

  * **examples** - short code examples demonstrating aspects of the nRF MCUs.

nrfburn is under active development, but it is fully functional.