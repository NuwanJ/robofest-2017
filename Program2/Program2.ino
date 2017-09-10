#include <Servo.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
//#include <Adafruit_HMC5883_U.h>
#include "Adafruit_TCS34725.h"
#include "define.h"

Adafruit_TCS34725 color0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]
//Adafruit_HMC5883_Unified compass = Adafruit_HMC5883_Unified(12345);

Servo pick, grab;

void setup() {

  Serial.begin(9600);
  Serial.println(">> Begin : Prog2");

  //compassBegin();
  //sharpIRBegin();
  //sonarBegin();
  //colorBegin();
  indicatorBegin();

}

/*
  ---- Beeps -------------------------------------------------
  1
  2
  3
  4 beeps --> Color Sensor not attached
  5
*/

void loop() {

  //readColor();
  delay(100);
  //readWalls(wall);
  //readCompass();



}

