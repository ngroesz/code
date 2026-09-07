#define IR_RECEIVE_PIN 3

#include <IRremote.hpp>


void setup()
{
  Serial.begin(115200);
  delay(200);

  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
  IrReceiver.begin(IR_RECEIVE_PIN, false);
}

void loop()
{
  if (IrReceiver.decode()) {  // Grab an IR code
        Serial.println();
        IrReceiver.printIRSendUsage(&Serial);
        Serial.println();
        Serial.println(F("Raw result in internal ticks (50 us) - with leading gap"));
        IrReceiver.printIRResultRawFormatted(&Serial, false); // Output the results in RAW format
        Serial.println(F("Raw result in microseconds - with leading gap"));
        IrReceiver.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
        Serial.println();                               // blank line between entries

        IrReceiver.resume();
  }
}
