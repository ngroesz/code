const int left_motor[] = {6, 9};
const int right_motor[] = {10, 11};
//const int trigger_pin = 10;

//const long sonar_interval = 500;
//unsigned long previous_sonar_millis = 0;
//
//const long debug_interval = 1000;
//unsigned long previous_debug_millis = 0;
//
//const long nav_interval = 500;
//unsigned long previous_nav_millis = 0;
//
//int front_distance = -1;
//
//void sonar_pulse()
//{
//    long duration;
//    pinMode(trigger_pin, OUTPUT);
//    digitalWrite(trigger_pin, LOW);
//    delayMicroseconds(2);
//    digitalWrite(trigger_pin, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trigger_pin, LOW);
//    pinMode(trigger_pin, INPUT);
//    duration = pulseIn(trigger_pin, HIGH);
//    front_distance = int((duration/2) / 29.1);
//}
//
//void write_debug()
//{
//    Serial.println(front_distance);
//}

void track_control(int left_track, int right_track)
{
    if (left_track > 0) {
        analogWrite(left_motor[0], left_track);
        analogWrite(left_motor[1], 0);
    } else {
        analogWrite(left_motor[0], 0);
        analogWrite(left_motor[1], abs(left_track));
    }

    if (right_track > 0) {
        analogWrite(right_motor[0], right_track);
        analogWrite(right_motor[1], 0);
    } else {
        analogWrite(right_motor[0], 0);
        analogWrite(right_motor[1], abs(right_track));
    }
}

void setup()
{
    pinMode(left_motor[0], OUTPUT);
    pinMode(left_motor[1], OUTPUT);
    pinMode(right_motor[0], OUTPUT);
    pinMode(right_motor[1], OUTPUT);

    //track_control(255, -255);
}

void loop()
{
    track_control(255, -255);
    delay(2000);
    track_control(0, 0);
    delay(2000);
    track_control(-255, 255);
    delay(2000);
//    unsigned long current_millis = millis();
//
//    if (current_millis - previous_sonar_millis >= sonar_interval) {
//        sonar_pulse();
//        previous_sonar_millis = current_millis;
//    }
//    if (current_millis - previous_debug_millis >= debug_interval) {
//        write_debug();
//        previous_debug_millis = current_millis;
//    }
//
//    if (current_millis - previous_nav_millis >= nav_interval) {
//        if (front_distance < 10) {
//            track_control(255, -255);
//        } else {
//            track_control(255, 255);
//        }
//
//        previous_nav_millis = current_millis;
//    }
}
