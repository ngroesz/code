// turret test - maybe delete this if I turn this into a sketch using tank library

// there is some possible bug in this code wherein it takes several loops for the motor to start working?
// i am not sure what could cause this ... some bad initialization of shift register?

#include <Wire.h>

#include "constants.h"
#include "pins.h"

#define CAMERA_READ_DELAY 100
#define CAMERA_MIDDLE_X 500
#define CAMERA_MOVE_THRESHOLD 50

PVision ircam;
byte result;
unsigned long last_camera_read = 0;
volatile long turret_encoder_count = 0;
uint8_t motor_direction = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\n"));

  digitalWrite(TURRET_MOTOR_PWM_PIN, 0);
  digitalWrite(MOTOR_ENABLE_PIN, 0);
  digitalWrite(SHIFT_CLEAR_PIN, 0);
  digitalWrite(SHIFT_CLOCK_PIN, 0);
  digitalWrite(SHIFT_DATA_PIN, 0);

  pinMode(TURRET_MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  pinMode(SHIFT_CLEAR_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);
  pinMode(SHIFT_DATA_PIN, OUTPUT);

  // set pins to input with a pullup
  pinMode(ENCODER_PIN, INPUT_PULLUP);

  // attach the new PinChangeInterrupts and enable event functions below
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENCODER_PIN), encoder_interrupt, RISING);

  ircam.init();
  Serial.println("camera initalized");
}

void loop() {
  unsigned long current_millis = millis();

  if (last_camera_read + CAMERA_READ_DELAY < current_millis) {
    result = ircam.read();
    if (result & BLOB1)
    {
      Serial.print("BLOB1 detected. X:");
      Serial.print(ircam.Blob1.X);
      Serial.print(" Y:");
      Serial.print(ircam.Blob1.Y);
      Serial.print(" Size:");
      Serial.println(ircam.Blob1.Size);
    }
    last_camera_read = current_millis;

    if (ircam.Blob1.X < CAMERA_MIDDLE_X - CAMERA_MOVE_THRESHOLD && motor_direction != 1) {
      Serial.println("left");
      analogWrite(TURRET_MOTOR_PWM_PIN, 0);
      digitalWrite(MOTOR_ENABLE_PIN, 0);
      write_motor_code(CONTROL_CODE_TURRET_MOTOR_FORWARD);
      delay(1500);
      analogWrite(TURRET_MOTOR_PWM_PIN, 255);
      digitalWrite(MOTOR_ENABLE_PIN, 1);
      motor_direction = 1;
    } else if (ircam.Blob1.X > CAMERA_MIDDLE_X + CAMERA_MOVE_THRESHOLD && motor_direction != 2) {
      Serial.println("right");
      analogWrite(TURRET_MOTOR_PWM_PIN, 0);
      digitalWrite(MOTOR_ENABLE_PIN, 0);
      write_motor_code(CONTROL_CODE_TURRET_MOTOR_REVERSE);
      delay(1500);
      analogWrite(TURRET_MOTOR_PWM_PIN, 255);
      digitalWrite(MOTOR_ENABLE_PIN, 1);
      motor_direction = 2;
    }
  }
}

void write_motor_code(const unsigned char & control_code) {
  Serial.print("Writing motor control code ");
  Serial.println(control_code);
  digitalWrite(SHIFT_CLEAR_PIN, LOW);
  shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, control_code);
  digitalWrite(SHIFT_CLEAR_PIN, HIGH);
}

void encoder_interrupt(void) {
  if (motor_direction == 1) {
    count++;
  } else if (motor_direction == 2) {
    count--;
  }
}
