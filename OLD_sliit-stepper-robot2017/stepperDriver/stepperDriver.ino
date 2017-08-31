
#include <Arduino.h>

#include "StepperDriver.h"

#define MOTOR_STEPS 200
#define MICROSTEPS 16

StepperDriver stepper(MOTOR_STEPS);    //(MOTOR_STEPS, DIR, STEP, ENBL);

#define STEPS_FOR_ROUND 430 //480

/*

  enum Direction {DIR_FORWARD, DIR_REVERSE};
  enum Mode {CONSTANT_SPEED, LINEAR_SPEED};

  BasicStepperDriver(steps,dir_pin,step_pin);

  .begin(rpm,microsteps)

  .setRPM(rpm)
  .setSpeedProfile(mode, accel,decel)

  .getRPM()
  .getCurrentRPM()

  .move(steps)
  .rotate(deg)

  .enable()
  .disable()

  .getTimeForMove(steps)
  .nextAction()

*/

void setup() {

  stepperMotorBegin();
  Serial.begin(9600);


  //Serial.println(PIN_DIR_LEFT);
}

void loop() {
  /*int a = 90;
    //square();
    motorRotate(a);
    delay(1000);
    motorRotate(-1 * a);
    delay(1000);*/

  square();
}

void square() {
  int a = 90;

  for (int i = 0; i < 4; i++) {
    motorForward(200);
    delay(500);
    motorRotate(a);
    delay(500);
  }

  delay(3000);
}

