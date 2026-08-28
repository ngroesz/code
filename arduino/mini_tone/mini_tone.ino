#include "mini_tone.h"
#include "pitches.h"

#define SPEAKER_PIN 7

MiniTone mini_tone;

// death sound
//uint16_t tones[] = {NOTE_D4, 500, NOTE_CS4, 500, NOTE_C4, 500, NOTE_A3, 2000};

// ive been hit
//uint16_t tones[] = {600, 500, 600, 500, 600, 500, 600, 500};

// shots fired
uint16_t tones[] = {150, 500, 150, 500, 150, 500};

void setup() {
  Serial.begin(115200);
  mini_tone.setup(SPEAKER_PIN);
  mini_tone.play(tones, sizeof(tones) / sizeof(tones[0]));
}

void loop() {
  mini_tone.loop();
}
