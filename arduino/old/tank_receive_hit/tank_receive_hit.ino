#include <IRremote.h>

const int ir_receive_pin = 8;
const int led_pin = 12;

IRrecv irrecv(ir_receive_pin);
decode_results results;

const long blink_interval = 1000;
unsigned long previous_blink_millis = 0;
boolean blink_active = false;


void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn();
    pinMode(led_pin, OUTPUT);
}

void loop()
{
    unsigned long current_millis = millis();
    if (irrecv.decode(&results)) {
        Serial.println(results.value);
        if (results.value == 1924960634)  {
            digitalWrite(led_pin, HIGH);
            blink_active = true;
            previous_blink_millis = current_millis;
        }
        irrecv.resume();
    }

    if (blink_active && current_millis > previous_blink_millis + blink_interval) {
        digitalWrite(led_pin, LOW);
    }
}
