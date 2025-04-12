// this is for a motor not connected to a shift register
// i used this sketch to test a TB6612FNG board

#define MOTOR_PWM_PIN 9
#define MOTOR_STANDBY_PIN 4
#define MOTOR_PIN_1 2
#define MOTOR_PIN_2 3

void setup() {
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_STANDBY_PIN, OUTPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);

  digitalWrite(MOTOR_PWM_PIN, LOW);
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, LOW);
  digitalWrite(MOTOR_STANDBY_PIN, LOW);
}

void loop() {
  // forward
  digitalWrite(MOTOR_PWM_PIN, HIGH);
  digitalWrite(MOTOR_PIN_1, HIGH);
  digitalWrite(MOTOR_PIN_2, LOW);
  digitalWrite(MOTOR_STANDBY_PIN, HIGH);
  delay(5000);

  // stop
  digitalWrite(MOTOR_STANDBY_PIN, LOW);
  delay(1000);

  // reverse
  digitalWrite(MOTOR_PWM_PIN, HIGH);
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, HIGH);
  digitalWrite(MOTOR_STANDBY_PIN, HIGH);
  delay(5000);

  // stop
  digitalWrite(MOTOR_STANDBY_PIN, LOW);
  delay(1000);
}
