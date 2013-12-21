This hardware/software package allows full access to the flash area of the Nordic nRF24LU1+ and nRF24LE1  microcontrollers.

The programmer is based on an Atmel ATmega AVR which handles the SPI communication and access to the flash area of the Nordic nRF MCUs. It can erase, write and read the MainBlock and InfoBlock of the nRF flash.

NOTE: Flash read access is only possible if it has been allowed by the nRF InfoPage configuration.

nrfburn can be used to access the flash of "bricked" nRF24LU1+ (both versions: F16 and F32) or nRF24LE1 MCUs. You can reprogram the bootloader or write any other HEX file into the flash area.

Tha programmer hardware is built around an Atmel ATmega88p microcontroller, but ATmega168p or ATmega328p can be used as well. The AVR is powered through a 3.3V regulator so it is not necessary to level shift between the programmer and the target nRF MCU. The programmer firmware uses V-USB software driver for communication with the PC. The PCB has breakout footprints compatibile with the SparkFun nRF24LU1+ breakout board, and the generic nRF24LU1+ breakout. This means the if you have appropriate you can just plug these breakouts into the programmer for flash the nRF MCU.

Project structure:

circut - Eagle CAD files for the AVR programmer circuit.

firmware - The AVR programmer firmware. It parses requests received the USB and executes SPI commands to access the nRF flash.

nrfburn - PC software which sends commands to the AVR programmer. Written in C++, it is cross-platform and can be compiled with gcc for Linux (Intel or ARM) or Windows.


nrfburn is still under active development, but it's already fully functional. It has not been thoroughly tested yet, but I have used it for a few nRF based projects.