TARGET  = nrfavr
DEVICE  = atmega88p
F_CPU   = 12000000

AVRDUDE = avrdude -c dragon_isp -P usb -p $(DEVICE)
#AVRDUDE = avrdude -c stk500v2 -P avrdoper -p $(DEVICE)

VPATH = usbdrv:../mcu-lib

CFLAGS	= -I. -Wall -Os -Iusbdrv -I../mcu-lib -flto
LFLAGS  = -Wl,--relax -flto
#LFLAGS += -u vfprintf -lprintf_min

COMPILE = avr-gcc -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) $(CFLAGS)

OBJECTS = main.o avrdbg.o prg_spi.o prg_parse.o usb.o usbdrv.o usbdrvasm.o

hex: $(TARGET).hex

$(TARGET).hex: $(OBJECTS)
	$(COMPILE) -o $(TARGET).elf $(OBJECTS) $(LFLAGS)
	rm -f $(TARGET).hex $(TARGET).eep.hex
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-size -C --mcu=$(DEVICE) $(TARGET).elf

flash: all $(TARGET).hex
	$(AVRDUDE) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)

read_fuse:
	$(AVRDUDE) -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h

# $(COMPILE) -S -fverbose-asm $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.o:
	$(COMPILE) -c $< -o $@

all: clean $(TARGET).hex
