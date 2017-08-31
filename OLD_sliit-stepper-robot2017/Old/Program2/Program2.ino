#include <Servo.h>
#include <Wire.h>

#include "Adafruit_TCS34725.h"
#include "define.h"

Adafruit_TCS34725 color0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  // Integration, Grain [1,4]

void setup() {

  Serial.begin(9600);
  Serial.println(">> Begin : Prog2");

  sharpIRBegin();
  //sonarBegin();
  colorBegin();
  indicatorBegin();

}

void loop() {

  colorUpdate();
  wallUpdate();

  delay(500);

}


void colorUpdate() {
  readColor();

  if (0) {
    Serial.print(blue0);
    Serial.print(" ");
    Serial.print(red0);
    Serial.print(" ");
    Serial.print(green0);
    Serial.print(" ");
    Serial.print(colorR0);
    Serial.println(" ");
  }
}

void wallUpdate() {
  readWalls();

  if (0) {
    Serial.print(wall[LEFT_SENSOR]);
    Serial.print(wall[FRONT_SENSOR]);
    Serial.println(wall[RIGHT_SENSOR]);
  }
}

