// Example of using the PVision library for interaction with the Pixart sensor on a WiiMote
// This work was derived from Kako's excellent Japanese website
// http://www.kako.com/neta/2007-001/2007-001.html

// Steve Hobley 2009 - www.stephenhobley.com

#include <Wire.h>
#include <PVision.h>

PVision ircam;
byte result;
unsigned long last_camera_read = 0;
#define CAMERA_READ_DELAY 100

void setup()
{
  Serial.begin(115200);
  Serial.println(F("setup " __FILE__ " from " __DATE__ "\r\n"));

  ircam.init();
  Serial.println("camera initalized");
}

void loop()
{
  unsigned long current_millis = millis();
  if (last_camera_read + CAMERA_READ_DELAY < current_millis) {
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
    last_camera_read = current_millis;
  }
}
