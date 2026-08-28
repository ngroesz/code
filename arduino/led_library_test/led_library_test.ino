#include "tank_led.h"

#define LED_PIN_1 6

TankLed tank_led;

unsigned long last_update_millis = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("initializing");

  uint8_t pins[] = {LED_PIN_1};
  tank_led.setup(pins);
  //tank_led.on(0);
  //tank_led.off(1);
  //tank_led.on(2);

  tank_led.set_blinks(0, (const uint16_t[]){500, 500}, 2);
  Serial.println("initialized");
}

void loop()
{
  tank_led.loop();
  //if (millis() > last_update_millis + 1000) {
  //  tank_led.loop();
  //  last_update_millis = millis();
  //}
}
