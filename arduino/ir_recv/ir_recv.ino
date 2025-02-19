
#include "TinyIRReceiver.hpp"

#define IR_RECEIVE_PIN 3
#define USE_CALLBACK_FOR_TINY_RECEIVER
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
        if (TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT) {
            Serial.print(F(" Repeat"));
        }
        if (TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED) {
            Serial.print(F(" Parity failed"));
        }
        Serial.println();
    }


}

void handleReceivedTinyIRData() {
    Serial.println("interrupt called");
    printTinyReceiverResultMinimal(&Serial);
}
