#define trigPin A1

int front_distance = -1;

const long sonar_interval = 500;
unsigned long previous_sonar_millis = 0;

const long debug_interval = 1000;
unsigned long previous_debug_millis = 0;


void sonar_pulse()
{
    long duration;
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(trigPin, INPUT);
    duration = pulseIn(trigPin, HIGH);
    front_distance = int((duration/2) / 29.1);
}

void write_debug()
{
    Serial.println(front_distance);
}

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    unsigned long current_millis = millis();

    if (current_millis - previous_sonar_millis >= sonar_interval) {
        sonar_pulse();
        previous_sonar_millis = current_millis;
    }
    if (current_millis - previous_debug_millis >= debug_interval) {
        write_debug();
        previous_debug_millis = current_millis;
    }
}
