#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

unsigned long last_read = 0;
unsigned long read_delay = 500;

void setup()
{
  Serial.begin(115200);
  Serial.println("beginning");
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();

  Serial.println("initialized");
}

void loop()
{
  unsigned long current_millis = millis();

  if (current_millis > last_read + read_delay) {
    last_read = current_millis;
    Serial.println(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) { Serial.println(" TIMEOUT"); }
  }

}
