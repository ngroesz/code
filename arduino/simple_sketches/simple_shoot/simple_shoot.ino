#include <Arduino.h>

#define IR_SEND_PIN 3
#include "TinyIRSender.hpp"

#include "ir_codes.h"

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    while (!Serial)
        ; // Wait for Serial to become available. Is optimized away for some cores.

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TINYIR));
    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}

uint8_t sAddress = 0x0;
uint8_t sCommand = IR_CODE_SELECT;

void loop() {
    /*
     * Print current send values
     */
    Serial.println();
    Serial.print(F("Send now:"));
    Serial.print(F(" address=0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" command=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(" repeats="));

    // Send with NEC
    // NEC uses 8 bit address and 8 bit command each with 8 bit inverted parity checks
    // However, sendNEC will accept 16 bit address and commands too (but remove the parity checks)
    Serial.println(F("Send NEC with 8 bit address and command"));
    Serial.flush();
    sendNEC(IR_SEND_PIN, sAddress, sCommand, 0);

    delay(1000);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}
