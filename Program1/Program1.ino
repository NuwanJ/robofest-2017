#include <MemoryFree.h>
#include <pgmStrToRAM.h>

#include <avr/pgmspace.h>

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "define.h"



#include <Adafruit_Sensor.h>
#include "Adafruit_TCS34725.h"

SoftwareSerial mySerial(3, 2); // RX, TX

#if defined(STEPPER_MOTORS)
#include "StepperDriver.h"


StepperDriver stepper(MOTOR_STEPS);    //(MOTOR_STEPS, DIR, STEP, ENBL);
#endif

Adafruit_TCS34725 color0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);  // Integration=50, Grain [1,4]

volatile int mode = BEGIN ;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  irSensorsBegin();
  eepromBegin();
  colorBegin();
  wallSensorBegin();

  //lineFollowBegin();
  //sonarBegin();

#if defined(GEARED_MOTORS)
  motorsBegin();
#elif defined(STEPPER_MOTORS)
  stepperMotorBegin();
#endif

  pinMode(BUTTON_1, INPUT_PULLUP);
  //pinMode(BUTTON_2, INPUT_PULLUP);

  pinMode(PIN_LED, OUTPUT);
  /*
  loadEEPROM(); // loading EEPROM data
    if (isMazeSolved) { // maze has being traversed before.
    solveMaze();
    } else {
    //cleanEEPROM();
    }
    stand();
  */

  // Inform us that program is ready
  beep(2);

}

void test() {
  pick();
  delay(2000);
  drop();
  delay(2000);
  //readWalls(wall);
}

