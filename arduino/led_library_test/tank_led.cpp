#include <Arduino.h>

#include "tank_led.h"

void TankLed::setup(const uint8_t led_pins[])
{
  for(uint8_t led_index = 0; led_index < LED_COUNT; ++led_index) {
    _initialize_led(_leds[led_index], led_pins[led_index]);
  }
}

void TankLed::loop()
{
  _current_millis = millis();

  print_state();
  for(uint8_t led_index = 0; led_index < LED_COUNT; ++led_index) {
    if (_leds[led_index].state == led_blinking) {
      _update_led(_leds[led_index]);
    }
  }
}

void TankLed::print_state()
{
  for(uint8_t led_index = 0; led_index < LED_COUNT; ++led_index) {
    Led led = _leds[led_index];
    Serial.print("LED ");
    Serial.print(led_index);
    Serial.print(" state: ");
    Serial.print(led.state);
    Serial.print(" current_blink_index: ");
    Serial.println(led.current_blink_index);
  }
}

// TODO: I'm not sure if it's necessary to put the actual logic into the private function
void TankLed::on(uint8_t led_index) { _led_on(_leds[led_index]); }
void TankLed::off(uint8_t led_index) { _led_off(_leds[led_index]); }

void TankLed::toggle(uint8_t led_index)
{
  if (_leds[led_index].state == led_on) {
    off(led_index);
  } else {
    on(led_index);
  }
}

void TankLed::all_on()
{
  for(uint8_t led_index = 0; led_index < LED_COUNT; ++led_index) {
    on(led_index);
  }
}

void TankLed::all_off()
{
  for(uint8_t led_index = 0; led_index < LED_COUNT; ++led_index) {
    off(led_index);
  }
}

void TankLed::set_blinks(uint8_t led_index, const uint16_t blinks[], const uint8_t blink_count)
{
  Serial.print("set_blinks on led_index: ");
  Serial.println(led_index);
  Led& led_to_update = _leds[led_index];

  Serial.print("set state on led ");
  Serial.print(led_index);
  Serial.print(" to ");
  Serial.println(led_blinking);
  led_to_update.state = led_blinking;
  led_to_update.blink_count = blink_count > MAX_BLINK_COUNT ? MAX_BLINK_COUNT : blink_count;
  for (uint8_t i = 0; i < led_to_update.blink_count; ++i) {
    led_to_update.blinks[i] = blinks[i];
  }
  led_to_update.current_blink_index = -1;
  led_to_update.next_blink_change = 0;

  print_state();
}

void TankLed::_initialize_led(struct Led & _led, const uint8_t led_pin)
{
  _led.led_pin = led_pin;
  _led.state = led_off;
  _led.blink_count = 0;
  pinMode(_led.led_pin, OUTPUT);
  digitalWrite(_led.led_pin, HIGH);
}

void TankLed::_led_on(struct Led & _led)
{
  Serial.println("this been called");
  _led.state = led_on;
  digitalWrite(_led.led_pin, LOW);
}

void TankLed::_led_off(struct Led & _led)
{
  Serial.println("this been called");
  _led.state = led_off;
  digitalWrite(_led.led_pin, HIGH);
}

void TankLed::_update_led(struct Led & _led)
{
  if (_current_millis > _led.next_blink_change) {
    ++_led.current_blink_index;
    if (_led.current_blink_index == _led.blink_count) {
      _led.current_blink_index = 0;
    }
    if(_led.current_blink_index % 2 == 0) {
      Serial.println("led turn on");
      // turn the LED on
      digitalWrite(_led.led_pin, LOW);
    } else {
      Serial.println("led turn off");
      // turn the LED off
      digitalWrite(_led.led_pin, HIGH);
   }
   _led.next_blink_change = _current_millis + _led.blinks[_led.current_blink_index];
  }
}
