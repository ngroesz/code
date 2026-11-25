// Example of using the PVision library for interaction with the Pixart sensor on a WiiMote
// This work was derived from Kako's excellent Japanese website
// http://www.kako.com/neta/2007-001/2007-001.html

// Steve Hobley 2009 - www.stephenhobley.com

#include <Wire.h>
#include <PVision.h>
#include <VL53L0X.h>

#define IR_RECEIVE_PIN 3
#define USE_CALLBACK_FOR_TINY_RECEIVER

#include "TinyIRReceiver.hpp"

#define DISTANCE_SENSOR_ENABLED
#define DISTANCE_READ_MILLIS 500

VL53L0X sensor;

uint32_t last_distance_read_millis = 0;

bool ir_command_received;
uint16_t last_command;

void handleReceivedTinyIRData() {
    Serial.println("received ir command");
  //if (TinyIRReceiverData.Flags != IRDATA_FLAGS_IS_REPEAT && TinyIRReceiverData.Flags != IRDATA_FLAGS_PARITY_FAILED) {
  //if (TinyIRReceiverData.Flags != IRDATA_FLAGS_PARITY_FAILED) {
    ir_command_received = true;
    last_command = TinyIRReceiverData.Command;
  //}
}

void setup()
{
  Serial.begin(115200);
  Serial.println("beginning");
  Wire.begin();

#ifdef DISTANCE_SENSOR_ENABLED
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
  Serial.println("distance sensor initialized");
#endif

  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
  if (!initPCIInterruptForTinyReceiver()) {
    Serial.println(F("could not initialize IR"));
  }

  Serial.println("initialized");
}

void loop()
{
  if (millis() > last_distance_read_millis + DISTANCE_READ_MILLIS) {
    Serial.print("Distance read: " );
    Serial.println(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) { Serial.println(" TIMEOUT"); }
    last_distance_read_millis = millis();
  }

  if (ir_command_received) {
    Serial.print("IR command: ");
    Serial.println(last_command);
    ir_command_received = false;
  }
}
