TARGET   = testRadio.ihx
CFLAGS   = --model-small -I../../mcu-lib -DNRF24LU1
LFLAGS   = --code-loc 0x0000 --code-size 0x4000 --xram-loc 0x8000 --xram-size 0x800
ASFLAGS  = -plosgff
RELFILES = testRadio.rel nrfutils.rel nRF24L.rel nrfdbg.rel crtxinit.rel

VPATH    = ../../mcu-lib

$(TARGET): $(RELFILES)
	sdcc $(CFLAGS) $(LFLAGS) $(RELFILES) -o $(TARGET)

%.rel: %.c
	sdcc $(CFLAGS) -c $<

%.rel: %.asm
	sdas8051 $(ASFLAGS) $@ $< 

clean:
	rm --force *.ihx *.lnk *.lst *.map *.rel *.rst *.sym *.mem *.lk *.asm *.lk *.cdb *.omf

all: clean $(TARGET)

flash: clean $(TARGET)
	nrfburn -w $(TARGET)
