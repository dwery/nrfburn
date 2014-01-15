TARGET   = testRadio.ihx
CFLAGS   = --model-small -I../common
LFLAGS   = --code-loc 0x0000 --code-size 0x4000 --xram-loc 0x8000 --xram-size 0x800
ASFLAGS  = -plosgff
RELFILES = crtxinit.rel

VPATH    = ../common

main: $(TARGET)

$(TARGET): testRadio.c $(RELFILES)
	sdcc $(CFLAGS) $(LFLAGS) testRadio.c $(RELFILES) -o $(TARGET)

%.rel: %.c
	sdcc $(CFLAGS) -c $<

%.rel: %.asm
	sdas8051 $(ASFLAGS) $@ $< 

clean:
	rm --force *.ihx *.lnk *.lst *.map *.rel *.rst *.sym *.mem *.lk testRadio.asm nRF24L.asm testRadio.lk testRadio.cdb testRadio.omf

all: clean main

flash: clean main
	nrfburn -w testRadio.ihx
