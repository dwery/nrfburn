# Introduction #

nrfburn is a set of hardware and software tools that can be used to access the flash area of Nordic Semiconductor's nRF24 family of microcontrollers. It can be used to read and write the flash area of nRF24LE1 and nRF24LU1+ (both 16 and 32 kbyte versions).

The programmer connects to the host PC through USB. It is a HID class USB device which means that drivers for Windows are not needed. Considering it is a low-speed HID device, it is relatively fast: it writes and verifies a 4 kbyte program to a 32 kbyte nRF24LU1+ in about 3 seconds.


# Programmer hardware #

The hardware is built around Atmel's ATmega88p microcontroller. It communicates with the host PC through low-speed USB using [Objective Development's firmware-only USB driver for Atmel AVR microcontrollers](http://www.obdev.at/products/vusb/index.html). The circuit is powered at 3.3V through a LM3940 voltage regulator which drops the USB's VBUS 5V down to 3.3V. This way it is possible to directly interface the AVR with the nRF through SPI without a level shifter or buffer chip.

The nRF programming interface requires 5 lines: MISO, MOSI, SCK, CSN and PROG. An optional RESET line is also present and used by the programmer, but is not necessary for correct flashing. These lines are brought out on the programmer PCB to two pin headers which are pin compatible with the [SparkFun's nRF24LU1+ breakout](https://www.sparkfun.com/products/9034) and a generic Chinese nRF24LU1+ USB dongle. Other breakouts and dongles can be interfaced to the programmer with simple wires.

Because the SparkFun nRF24LU1+ breakout also has pins P0.4 and P0.5 brought out, the programmer has LEDs connected to these two lines. This can be helpful for debugging and testing uploaded firmwares.

It is possible to power the nRF MCU directly from the programmer. Because nRF24LU1+ are powered at 5V and nRF24LE1 at 3.3V, the output voltage that is used to power the nRF must be correctly selected with a jumper. **Warning:** care must be taken to avoid damaging the nRF24LE1 by selecting to power it with 5V. This will probably destroy the chip.

# Programmer firmware #

The firmware enumerates the programmer to the PC as a HID device. The advantage of this is that no drivers are needed on Windows, but also limits the speed at which the PC and the programmer can communicate - which is normally only 800 bytes/sec for HID interrupt endpoints. To get around this the programmer uses HID feature requests to send and receive data to and from the PC. This way it is possible to achieve 4-5 kbytes/sec transfer rates. This same method was used earlier by [avrdoper](http://www.obdev.at/products/vusb/avrdoper.html).

The programmer firmware can be updated using a bootloader located in the upper 2 kilobytes of the programmer firmware. The bootloader is based on [BootloadHID](http://www.obdev.at/products/vusb/bootloadhid.html).

# PC (host) sofware #

The host software is a command line program written in C++. Except for the APIs which send and receive data through USB, the rest of the program only uses the standard C++ library. It can be compiled on Linux (tested with gcc 4.8 on Arm Linux) and on Windows using MinGW.

# Examples #

The package contains a few example projects which demonstrate how to achieve some of the more common tasks on an nRF MCU. These can be compiled with [sdcc](http://sdcc.sourceforge.net/), an open source C compiler for 8051 MCUs. At the moment, there are only a few such examples:

  * **examples/lu1/USB** - implements a standard USB keyboard on an nRF24LU1+. It only shows how to configure USB and send HID reports, RF is not implemented.
  * **examples/lu1/int0** - shows the very basics of how to implement interrupt service routines on the nRF24LU1+

The plan is to extend these with an example of a fully working wireless USB keyboard.