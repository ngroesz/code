// the simplest possible motor driver, using a shift register
// just make the motors go forward and backward, operating on a delay


// there is some possible bug in this code wherein it takes several loops for the motor to start working?
// i am not sure what could cause this ... some bad initialization of shift register?

#include "constants.h"
#include "pins.h"

void setup() {
    Serial.begin(115200);

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

    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\n"));
}

void loop() {
    // forward
    Serial.println("forward");
    analogWrite(TURRET_MOTOR_PWM_PIN, 255);
    digitalWrite(MOTOR_ENABLE_PIN, 1);
    write_motor_code(CONTROL_CODE_TURRET_MOTOR_FORWARD);
    delay(5000);

    // stop
    Serial.println("stop");
    digitalWrite(MOTOR_ENABLE_PIN, 0);
    write_motor_code(0);
    delay(1000);

    // reverse
    Serial.println("reverse");
    digitalWrite(MOTOR_ENABLE_PIN, 1);
    write_motor_code(CONTROL_CODE_TURRET_MOTOR_REVERSE);
    delay(5000);


    // stop
    Serial.println("stop");
    digitalWrite(MOTOR_ENABLE_PIN, 0);
    write_motor_code(0);
    delay(1000);
}

void write_motor_code(const unsigned char & control_code) {
    Serial.print("Writing motor control code ");
    Serial.println(control_code);
    digitalWrite(SHIFT_CLEAR_PIN, LOW);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, control_code);
    digitalWrite(SHIFT_CLEAR_PIN, HIGH);
}
