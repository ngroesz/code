const int turret_motor_pins[] = {7, 8};

#define DRIVE_LEFT_PIN_1 0
#define DRIVE_LEFT_PIN_2 1
#define DRIVE_RIGHT_PIN_1 4
#define DRIVE_RIGHT_PIN_2 2

void setup()
{
    pinMode(DRIVE_LEFT_PIN_1, OUTPUT);
    pinMode(DRIVE_LEFT_PIN_2, OUTPUT);
    pinMode(DRIVE_RIGHT_PIN_1, OUTPUT);
    pinMode(DRIVE_RIGHT_PIN_2, OUTPUT);
}

void loop()
{
    digitalWrite(DRIVE_LEFT_PIN_1, LOW);
    digitalWrite(DRIVE_LEFT_PIN_2, LOW);
    digitalWrite(DRIVE_RIGHT_PIN_1, LOW);
    digitalWrite(DRIVE_RIGHT_PIN_2, LOW);
    delay(100);
    digitalWrite(DRIVE_LEFT_PIN_1, HIGH);
    digitalWrite(DRIVE_LEFT_PIN_2, LOW);
    digitalWrite(DRIVE_RIGHT_PIN_1, HIGH);
    digitalWrite(DRIVE_RIGHT_PIN_2, LOW);
    delay(10000);
    digitalWrite(DRIVE_LEFT_PIN_1, LOW);
    digitalWrite(DRIVE_LEFT_PIN_2, LOW);
    digitalWrite(DRIVE_RIGHT_PIN_1, LOW);
    digitalWrite(DRIVE_RIGHT_PIN_2, LOW);
    delay(100);
    digitalWrite(DRIVE_LEFT_PIN_1, LOW);
    digitalWrite(DRIVE_LEFT_PIN_2, HIGH);
    digitalWrite(DRIVE_RIGHT_PIN_1, LOW);
    digitalWrite(DRIVE_RIGHT_PIN_2, HIGH);
    delay(10000);

}
