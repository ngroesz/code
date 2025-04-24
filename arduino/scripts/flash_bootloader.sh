avrdude -v -v -patmega328p -cstk500v2 -P/dev/ttyACM2 -Uflash:w:/usr/share/arduino/hardware/arduino/bootloaders/optiboot/optiboot_atmega328.hex:i  -Ulock:w:0x0F:m
