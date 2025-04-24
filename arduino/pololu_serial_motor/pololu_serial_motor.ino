/*Required connections between Arduino and qik 2s9v1:

      Arduino   qik 2s9v1
-------------------------
           5V - VCC
          GND - GND
Digital Pin 2 - TX
Digital Pin 3 - RX
Digital Pin 4 - RESET
*/

#include <SoftwareSerial.h>
#include <PololuQik.h>

PololuQik2s9v1 qik(2, 3, 4);

void setup()
{
    Serial.begin(115200);
    qik.init();
    delay(1000);
}

void loop()
{
    qik.setM0Speed(127);
    qik.setM1Speed(-127);
    delay(10000);
    qik.setM0Speed(0);
    qik.setM1Speed(0);
    delay(100);
    qik.setM0Speed(-127);
    qik.setM1Speed(127);
    delay(10000);
    qik.setM0Speed(0);
    qik.setM1Speed(0);
    delay(100);
}
