
#include "TinyIRReceiver.hpp"

#include "ir_codes.h"

#define IR_RECEIVE_PIN 2
//#define USE_CALLBACK_FOR_TINY_RECEIVER

void setup() {
  Serial.begin(115200);

  Serial.println("Initalizing ...");
  if (!initPCIInterruptForTinyReceiver()) {
    Serial.println("could not initialize IR");
  }
  Serial.println("Finished with initalization.");
}

void loop() {
  if (TinyReceiverDecode()) {
    Serial.print(F("Address=0x"));
    Serial.print(TinyIRReceiverData.Address, HEX);
    Serial.print(' ');
    Serial.print(F("Command=0x"));
    Serial.print(TinyIRReceiverData.Command, HEX);
    Serial.println();
    if (TinyIRReceiverData.Flags != IRDATA_FLAGS_IS_REPEAT && TinyIRReceiverData.Flags != IRDATA_FLAGS_PARITY_FAILED) {
      switch(TinyIRReceiverData.Command) {
        case IR_CODE_ONE:
          Serial.println("One");
          break;
        case IR_CODE_TWO:
          Serial.println("Two");
          break;
        case IR_CODE_THREE:
          Serial.println("Three");
          break;
        case IR_CODE_FOUR:
          Serial.println("Four");
          break;
        case IR_CODE_FIVE:
          Serial.println("Five");
          break;
        case IR_CODE_SIX:
          Serial.println("Six");
          break;
        case IR_CODE_SEVEN:
          Serial.println("Seven");
          break;
        case IR_CODE_EIGHT:
          Serial.println("Eight");
          break;
        case IR_CODE_NINE:
          Serial.println("Nine");
          break;
        case IR_CODE_ZERO:
          Serial.println("Zero");
          break;
        case IR_CODE_ASTERISK:
          Serial.println("Asterisk");
          break;
        case IR_CODE_POUND:
          Serial.println("Pound");
          break;
        case IR_CODE_LEFT:
          Serial.println("Left");
          break;
        case IR_CODE_RIGHT:
          Serial.println("Right");
          break;
        case IR_CODE_UP:
          Serial.println("Up");
          break;
        case IR_CODE_DOWN:
          Serial.println("Down");
          break;
        case IR_CODE_OK:
          Serial.println("OK");
          break;
        default:
          Serial.print("Unrecognized code ");
          Serial.println(TinyIRReceiverData.Command);
          break;
      }
    }
  }
}

//void handleReceivedTinyIRData() {
//  Serial.println("interrupt called");
//  printTinyReceiverResultMinimal(&Serial);
//}
