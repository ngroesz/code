#include <IRremote.h>

#include "pitches.h"

IRsend irsend;

const int led_pin =  13;
const int speaker_pin = 8;

const long sound_interval = 1000;
unsigned long previous_sound_millis = 0;
boolean sound_playing = false;

const long fire_interval = 5000;
unsigned long previous_fire_millis = 0;

void setup()
{
    pinMode(led_pin, OUTPUT);
}

void play_fire_sound()
{
    tone(speaker_pin, NOTE_C4, 100);
    sound_playing = true;
    previous_sound_millis = millis();
}

void fire()
{
    int khz = 38;

    unsigned int irSignal[] = {7200, 700, 500, 1650, 1500, 650, 550, 1650, 1500, 650, 550};

    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);
    play_fire_sound();
}

void loop() {
    unsigned long current_millis = millis();

    if (current_millis > previous_fire_millis + fire_interval) {
        fire();
        previous_fire_millis = current_millis;
    }

    if (sound_playing && current_millis > previous_sound_millis + sound_interval) {
        noTone(speaker_pin);
        sound_playing = false;
    }
}
