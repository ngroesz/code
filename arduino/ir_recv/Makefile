BOARD = arduino:avr:uno
PATH = /home/nick/code/arduino/ir_recv
PORT = /dev/ttyACM0

.PHONY:
compile:
	/usr/local/bin/arduino-cli compile -b $(BOARD) $(PATH)

upload:
	/usr/local/bin/arduino-cli upload -b $(BOARD) -p $(PORT) $(PATH)

