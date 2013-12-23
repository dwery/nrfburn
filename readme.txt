This hardware/software package allows full access to the flash area of the Nordic nRF24LU1+ and nRF24LE1 microcontrollers.

The programmer is based on an Atmel ATmega AVR which handles the SPI communication and access to the flash area of the Nordic nRF MCUs. It can erase, write and read the MainBlock and InfoBlock of the nRF flash.

NOTE: Flash read access is only possible if it has been allowed by the nRF InfoPage configuration.

nrfburn can be used to access the flash of "bricked" nRF24LU1+ (both versions: F16 and F32) or nRF24LE1 MCUs. You can reprogram the bootloader or write any other HEX file into the flash area.

Tha programmer hardware is built around an Atmel ATmega88p microcontroller, but ATmega168p or ATmega328p can be used as well. The programmer firmware uses V-USB for communication with the PC. The PCB has breakout footprints compatibile with the SparkFun nRF24LU1+ breakout board, and a generic nRF24LU1+ dongle. This means that you can just plug these breakouts into the programmer to flash the nRF MCU.

Project modules:

AVR circut - Eagle CAD files for the AVR programmer circuit.

firmware - The AVR programmer firmware. It parses requests received from USB and executes SPI commands to access the nRF flash.

nrfburn - PC software which sends commands to the AVR programmer. Written in C++, it is cross-platform and can be compiled with gcc for Linux or Windows (MinGW).


nrfburn is still under active development, and parts of it are not working. It has not yet been tested with nRF24LE1 and problems are expected.
