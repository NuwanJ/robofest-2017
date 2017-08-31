
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "define.h"

SoftwareSerial mySerial(3, 2); // RX, TX
volatile int mode = BEGIN ;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  //motorsBegin();
  irSensorsBegin();
  lineFollowBegin();
  eepromBegin();

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  mode = BEGIN;
}

void test() {

  /*int k = readSensorLine(sensor_values) ;//- CENTER_EDGE_READING;
    Serial.print(irLineString);
    Serial.print("\t");
    Serial.println(k);
    delay(1000);
  */
  centerLine();
}


