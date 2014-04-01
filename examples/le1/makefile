TARGET   = test_le1.ihx
CFLAGS   = --model-small -I../../mcu-lib -DNRF24LE1
LFLAGS   = --code-loc 0x0000 --code-size 0x4000 --xram-loc 0x0000 --xram-size 0x400
ASFLAGS  = -plosgff
RELFILES = test_le1.rel nRF24L.rel crtxinit.rel nrfutils.rel

VPATH   = ../../mcu-lib

main: $(TARGET)

$(TARGET): $(RELFILES)
	sdcc $(CFLAGS) $(LFLAGS) $(RELFILES) -o $(TARGET)

%.rel: %.c
	sdcc $(CFLAGS) -c $<

%.rel: %.asm
	sdas8051 $(ASFLAGS) $@ $< 

clean:
	rm --force *.ihx *.lnk *.lst *.map *.rel *.rst *.sym *.mem *.lk *.asm test_le1.lk test_le1.cdb test_le1.omf

all: clean main

flash: clean main
	nrfburn -w test_le1.ihx
