#include "PinChangeInterrupt.h"

#define BUMP_0_PIN 4
#define BUMP_1_PIN A3

int bump_pin = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("setup");

  pinMode(BUMP_0_PIN, INPUT_PULLUP);
  pinMode(BUMP_1_PIN, INPUT_PULLUP);

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(BUMP_0_PIN), bump_0_interrupt, CHANGE);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(BUMP_1_PIN), bump_1_interrupt, CHANGE);
}

void loop() {
}

void bump_0_interrupt() {
  uint8_t trigger = getPinChangeInterruptTrigger(digitalPinToPCINT(BUMP_0_PIN));
  if (trigger == RISING) {
    Serial.println("bump zero rising");
  } else if (trigger == FALLING) {
    Serial.println("bump zero falling");
  }
}

void bump_1_interrupt() {
  uint8_t trigger = getPinChangeInterruptTrigger(digitalPinToPCINT(BUMP_1_PIN));
  if (trigger == RISING) {
    Serial.println("bump one rising");
  } else if (trigger == FALLING) {
    Serial.println("bump one falling");
  }
}
