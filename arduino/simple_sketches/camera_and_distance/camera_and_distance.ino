// Example of using the PVision library for interaction with the Pixart sensor on a WiiMote
// This work was derived from Kako's excellent Japanese website
// http://www.kako.com/neta/2007-001/2007-001.html

// Steve Hobley 2009 - www.stephenhobley.com

#include <Wire.h>
#include <PVision.h>
#include <VL53L0X.h>

VL53L0X sensor;

PVision ircam;
byte result;

unsigned long last_camera_read = 0;
uint8_t camera_read_delay = 1000;

void setup()
{
  Serial.begin(115200);
  Serial.println("beginning");
  Wire.begin();
  ircam.init();

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

  if (current_millis > last_camera_read + camera_read_delay) {
    last_camera_read = current_millis;
    result = ircam.read();
    if (result & BLOB1)
    {
      Serial.print("BLOB1 detected. X:");
      Serial.print(ircam.Blob1.X);
      Serial.print(" Y:");
      Serial.print(ircam.Blob1.Y);
      Serial.print(" Size:");
      Serial.println(ircam.Blob1.Size);
    }

    if (result & BLOB2)
    {
      Serial.print("BLOB2 detected. X:");
      Serial.print(ircam.Blob2.X);
      Serial.print(" Y:");
      Serial.print(ircam.Blob2.Y);
      Serial.print(" Size:");
      Serial.println(ircam.Blob2.Size);
    }
    if (result & BLOB3)
    {
      Serial.print("BLOB3 detected. X:");
      Serial.print(ircam.Blob3.X);
      Serial.print(" Y:");
      Serial.print(ircam.Blob3.Y);
      Serial.print(" Size:");
      Serial.println(ircam.Blob3.Size);
    }
    if (result & BLOB4)
    {
      Serial.print("BLOB4 detected. X:");
      Serial.print(ircam.Blob4.X);
      Serial.print(" Y:");
      Serial.print(ircam.Blob4.Y);
      Serial.print(" Size:");
      Serial.println(ircam.Blob4.Size);
    }
    Serial.println(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) { Serial.println(" TIMEOUT"); }
  }

}
