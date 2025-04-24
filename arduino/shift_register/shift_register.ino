#define SER 12
#define CLK 11
#define CLEAR 13


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

void display_number(int n)
{
    digitalWrite(CLEAR, LOW);
    digitalWrite(CLEAR, HIGH);
    shift_bit(0);
    shift_bit(0);
    shift_bit(0);
    shift_bit(0);
    while(n > 0) {
        shift_bit(n % 2);
        n = n / 2;
    }
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
}

void forward()
{
    digitalWrite(CLEAR, LOW);
    digitalWrite(CLEAR, HIGH);
    shift_bit(0);
    shift_bit(0);
    shift_bit(0);
    shift_bit(0);

    shift_bit(0);
    shift_bit(1);
    shift_bit(0);
    shift_bit(1);
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
}

void reverse()
{
    digitalWrite(CLEAR, LOW);
    digitalWrite(CLEAR, HIGH);
    shift_bit(0);
    shift_bit(0);
    shift_bit(0);
    shift_bit(0);

    shift_bit(1);
    shift_bit(0);
    shift_bit(1);
    shift_bit(0);
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
}

void setup()
{
    Serial.begin(9600);
    pinMode(SER, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(CLEAR, OUTPUT);
    digitalWrite(CLEAR, LOW);
    digitalWrite(CLEAR, HIGH);
}

void loop()
{
    //for (int i = 0; i <= 15; ++i) {
    //    display_number(i);
    //    delay(1000);
    //}
    forward();
    delay(1000);
    reverse();
    delay(1000);
    //display_number(15);
    //delay(1000);
}

