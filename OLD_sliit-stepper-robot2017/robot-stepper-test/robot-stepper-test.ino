
#include <Arduino.h>
#include "StepperDriver.h"

#define MOTOR_STEPS 200
#define MICROSTEPS 16

StepperDriver stepper(MOTOR_STEPS, 5, 2, 8);    //(MOTOR_STEPS, DIR, STEP, ENBL);

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

  pinMode(6, OUTPUT);   
  stepper.begin(800, MICROSTEPS);
  stepper.setSpeedProfile(LINEAR_SPEED, 1000, 1000);

}

void loop() {

  go(250);
  delay(1000);

  go(-250);
  delay(1000);

}

void turn(int c) {
  if (c > 0) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  stepper.rotate(c);

}

void go(int c){
    if (c > 0) {
    digitalWrite(6, LOW);
  } else {
    digitalWrite(6, HIGH);
  }
  stepper.rotate(c);
}

