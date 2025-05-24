#define PWM_PIN 3
#define MOTOR_1_PIN 1
#define MOTOR_2_PIN 2
#define STANDBY_PIN 0

void setup() {
  Serial.begin(115200);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(MOTOR_1_PIN, OUTPUT);
  pinMode(MOTOR_2_PIN, OUTPUT);
  pinMode(STANDBY_PIN, OUTPUT);
  digitalWrite(STANDBY_PIN, LOW);
  Serial.println("initialized");
}

void loop() {
  digitalWrite(STANDBY_PIN, HIGH);
  digitalWrite(PWM_PIN, HIGH);
  digitalWrite(MOTOR_1_PIN, LOW);
  digitalWrite(MOTOR_2_PIN, HIGH);

  delay(5000);
  Serial.println("loop");
}

