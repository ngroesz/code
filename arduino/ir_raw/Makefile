BOARD = arduino:avr:uno
PATH = $(PWD)
#PORT = /dev/ttyUSB0
# my attempt to automatically detect port
PORT = "/dev/ttyUSB0"
#$(eval PORT=$(shell sh -c "arduino-cli board list | grep arduino:avr" | awk '{print $$1}'))

.PHONY:
compile:
	/usr/local/bin/arduino-cli compile -b $(BOARD) $(PATH)

upload:
	/usr/local/bin/arduino-cli upload -b $(BOARD) -p $(PORT) $(PATH)

