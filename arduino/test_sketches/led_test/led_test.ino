#define LED_PIN_1 4
#define LED_PIN_2 A3
#define LED_PIN_3 6
#define LED_PIN_4 A0

#include "tank_led.h"

TankLED tank_led;

void setup()
{
    tank_led.setup(
        LED_PIN_1,
        LED_PIN_2,
        LED_PIN_3,
        LED_PIN_4
    );
    tank_led.led_1_set_state((const uint16_t[]){500, 500}, 2);
    tank_led.led_2_set_state((const uint16_t[]){500, 500}, 2);
    tank_led.led_3_set_state((const uint16_t[]){500, 500}, 2);
    tank_led.led_4_set_state((const uint16_t[]){500, 500}, 2);
}

void loop()
{
    tank_led.loop();
}
