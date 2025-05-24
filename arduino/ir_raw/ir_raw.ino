#define IR_RECEIVER_PIN 3
#define IR_RECEIVER_PORT PIND
#define IR_MAXPULSE 40000
#define IR_RESOLUTION 20
#define IR_BEGIN_MIN_LENGTH 200
#define IR_END_MIN_LENGTH 1600
#define IR_DATA_MIN_LENGTH 1200
#define IR_HIGH_PULSE_LENGTH 50
#define IR_DELAY_BETWEEN_TRANSMISSIONS_MILLIS 100
#define IR_MINIMUM_CODE_VALUE 284098560
#define IR_MAXIMUM_CODE_VALUE 284164095

int led_state = LOW;
unsigned long past_time =0;
volatile boolean ir_data_receiving;
uint16_t highpulse, lowpulse;
boolean ir_disabled = 0;
unsigned long ir_disabled_millis = 0;

void ir_receiver_interrupt()
{
    ir_data_receiving = true;
}

unsigned long read_ir_data()
{
    uint8_t current_pulse, current_bit;
    current_pulse = 0;
    unsigned long result = 0;
    boolean ir_data_begun, finished;
    ir_data_begun = finished = 0;

    while(!finished) {
        highpulse = lowpulse = 0;
        while (IR_RECEIVER_PORT & (1 << IR_RECEIVER_PIN)) {
            highpulse++;
            delayMicroseconds(IR_RESOLUTION);

            if (highpulse >= IR_MAXPULSE && current_pulse != 0) {
                finished = 1;
            }
        }
        if (!ir_data_begun) {
            if(highpulse > IR_BEGIN_MIN_LENGTH) {
                ir_data_begun = 1;
            }
        } else {
            if (highpulse > IR_END_MIN_LENGTH) {
                finished = 1;
            } else {
                if(highpulse > IR_HIGH_PULSE_LENGTH) {
                    current_bit = 1;
                } else {
                    current_bit = 0;
                }
                result = result << 1 | current_bit;
            }
        }

        while (!(IR_RECEIVER_PORT & _BV(IR_RECEIVER_PIN))) {
            lowpulse++;
            delayMicroseconds(IR_RESOLUTION);
            if (lowpulse >= IR_MAXPULSE && current_pulse != 0) {
                finished = 1;
            }
        }
        current_pulse++;
    }

    if (result >= IR_MINIMUM_CODE_VALUE && result <= IR_MAXIMUM_CODE_VALUE) {
        return result;
    } else {
        return 0;
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(IR_RECEIVER_PIN, INPUT);
    ir_data_receiving = false;
    attachInterrupt(digitalPinToInterrupt(IR_RECEIVER_PIN), ir_receiver_interrupt, LOW);
    Serial.println("ready");
}

void loop()
{
    unsigned long current_millis = millis();
    if (ir_data_receiving && !ir_disabled) {
        ir_disabled = 1;
        noInterrupts();
        ir_disabled_millis = current_millis;
        unsigned long result = read_ir_data();
        Serial.print("I got this: ");
        Serial.println(result, HEX);
        ir_data_receiving = false;
        interrupts();
    }

    if (ir_disabled && current_millis > ir_disabled_millis + IR_DELAY_BETWEEN_TRANSMISSIONS_MILLIS) {
        ir_disabled = 0;
    }
}
