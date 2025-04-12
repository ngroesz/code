// test encoder input
// as well, this is a test of the PinChangeInterrupt library
// this code uses software interrupts to execute callback functions

#include "PinChangeInterrupt.h"

// choose a valid PinChangeInterrupt pin of your Arduino board
#define ENCODER_PIN 2

volatile long count = 0;

void setup()
{
  // start serial debug output
  Serial.begin(115200);
  Serial.println(F("setup"));

  // set pins to input with a pullup
  pinMode(ENCODER_PIN, INPUT_PULLUP);

  // attach the new PinChangeInterrupts and enable event functions below
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENCODER_PIN), encoder_interrupt, CHANGE);
}

void loop() {
  delay(1000);
  Serial.print("count: ");
  Serial.println(count);
}

void encoder_interrupt(void) {
  count++;
}
