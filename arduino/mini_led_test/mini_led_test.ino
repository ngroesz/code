#include "mini_led.h"
#include "ir_codes.h"

#define IR_RECEIVE_PIN 3
#define USE_CALLBACK_FOR_TINY_RECEIVER
#include "TinyIRReceiver.hpp"

MiniLed led;

bool process_ir_command = false;
uint16_t ir_command;

void setup() {
  Serial.begin(115200);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\n"));


  uint8_t pins[] = {6, 14, 9};
  led.setup(pins, 3, LOW);
  led.all_off();


  if (!initPCIInterruptForTinyReceiver()) {
    Serial.println("could not initialize IR");
  }
}

void loop() {
  led.loop();

  if (process_ir_command) {
    Serial.print("processing ir command ");
    Serial.println(ir_command);
    process_ir_command = false;

    switch (ir_command) {
      case IR_CODE_ONE:
        Serial.println("blink one");
        led.blink(0);
        break;
      case IR_CODE_TWO:
        Serial.println("blink two");
        led.blink(1);
        break;
      case IR_CODE_THREE:
        Serial.println("blink three");
        led.blink(2);
        break;
      case IR_CODE_UP:
        Serial.println("blink");
        led.blink(0);
        led.blink(1);
        led.blink(2);
        break;
      case IR_CODE_OK:
        Serial.println("all on");
        led.all_on();
        break;
      case IR_CODE_POUND:
        Serial.println("all off");
        led.all_off();
        break;
      case IR_CODE_LEFT:
        Serial.println("1 on");
        led.all_off();
        led.on(0);
        break;
      case IR_CODE_DOWN:
        Serial.println("2 on");
        led.all_off();
        led.on(1);
        break;
      case IR_CODE_RIGHT:
        Serial.println("3 on");
        led.all_off();
        led.on(2);
        break;
    }

  }
}

void handleReceivedTinyIRData() {
  if (TinyIRReceiverData.Flags != IRDATA_FLAGS_PARITY_FAILED) {
    process_ir_command = true;
    ir_command = TinyIRReceiverData.Command;
  }
}
