#define SER 8
#define CLK 12
#define CLEAR 13
#define M0_PWM 9
#define M1_PWM 10
#define MOTOR_ENABLE 5

void shift_bit(int bit)
{
    digitalWrite(CLK, LOW);
    if (bit == 0) {
        digitalWrite(SER, LOW);
    } else {
        digitalWrite(SER, HIGH);
    }
    digitalWrite(CLK, HIGH);
}

void write_control_code(unsigned char control_code)
{
    char output[8];
    digitalWrite(MOTOR_ENABLE, LOW);
    digitalWrite(CLEAR, LOW);
    digitalWrite(CLEAR, HIGH);
    shift_bit(0);
    shift_bit(0);
    for (int i = 0; i < 6; ++i) {
        if (control_code % 2 == 1) {
            shift_bit(1);
        } else {
            shift_bit(0);
        }
        control_code >>= 1;
    }
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
    digitalWrite(MOTOR_ENABLE, HIGH);
    Serial.print("output: ");
    Serial.println(output);
}

void stop()
{
    write_control_code(0);
    //digitalWrite(MOTOR_ENABLE, LOW);
    //digitalWrite(CLEAR, LOW);
    //digitalWrite(CLEAR, HIGH);

    //shift_bit(0);
    //shift_bit(0);
    //shift_bit(0);
    //shift_bit(0);

    //shift_bit(0);
    //shift_bit(0);
    //shift_bit(0);
    //shift_bit(0);
    //digitalWrite(CLK, LOW);
    //digitalWrite(CLK, HIGH);
    //digitalWrite(MOTOR_ENABLE, HIGH);
}

void forward()
{
    write_control_code(21);
    //digitalWrite(MOTOR_ENABLE, LOW);
    //digitalWrite(CLEAR, LOW);
    //digitalWrite(CLEAR, HIGH);
    //shift_bit(0);
    //shift_bit(1);
    //shift_bit(0);
    //shift_bit(1);

    //shift_bit(0);
    //shift_bit(1);
    //shift_bit(0);
    //shift_bit(1);
    //digitalWrite(CLK, LOW);
    //digitalWrite(CLK, HIGH);
    //digitalWrite(MOTOR_ENABLE, HIGH);
}

void reverse()
{
    write_control_code(42);
    //digitalWrite(MOTOR_ENABLE, LOW);
    //digitalWrite(CLEAR, LOW);
    //digitalWrite(CLEAR, HIGH);
    //shift_bit(1);
    //shift_bit(0);
    //shift_bit(1);
    //shift_bit(0);

    //shift_bit(1);
    //shift_bit(0);
    //shift_bit(1);
    //shift_bit(0);
    //digitalWrite(CLK, LOW);
    //digitalWrite(CLK, HIGH);
    //digitalWrite(MOTOR_ENABLE, HIGH);
}

void setup()
{
    Serial.begin(115200);
    pinMode(SER, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(CLEAR, OUTPUT);
    pinMode(M0_PWM, OUTPUT);
    pinMode(M1_PWM, OUTPUT);
    pinMode(MOTOR_ENABLE, OUTPUT);

    digitalWrite(CLEAR, LOW);
    digitalWrite(CLEAR, HIGH);
    analogWrite(M0_PWM, 100);
    analogWrite(M1_PWM, 100);
    digitalWrite(MOTOR_ENABLE, HIGH);

    write_control_code(40);
    delay(1000);
    write_control_code(0);
}

void loop()
{
    unsigned char control_code = 0;
    control_code |= 16;
    control_code |= 4;

    write_control_code(control_code);

    delay(1000);
    write_control_code(0);
    delay(1000);

}
