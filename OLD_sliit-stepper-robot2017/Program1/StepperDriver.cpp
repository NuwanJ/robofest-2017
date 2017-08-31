
#include "StepperDriver.h"

StepperDriver::StepperDriver(short steps)
  : motor_steps(steps)
{}

StepperDriver::StepperDriver(short steps, short dir_pin, short step_pin)
  : motor_steps(steps), dir_pin(dir_pin), step_pin(step_pin)
{}


StepperDriver::StepperDriver(short steps, short dir_pin, short step_pin, short enable_pin)
  : motor_steps(steps), dir_pin(dir_pin), step_pin(step_pin), enable_pin(enable_pin)
{}

void StepperDriver::begin(short rpm, short microsteps) {
  //pinMode(dir_pin, OUTPUT);
  //digitalWrite(dir_pin, HIGH);
  //pinMode(step_pin, OUTPUT);
  //digitalWrite(step_pin, LOW);

  /*if IS_CONNECTED(enable_pin) {
    pinMode(enable_pin, OUTPUT);
    digitalWrite(enable_pin, HIGH); // disable
    }*/

  this->rpm = rpm;
  setMicrostep(microsteps);

  enable();
}

void StepperDriver::setRPM(short rpm) {
  if (this->rpm == 0) {       // begin() has not been called (old 1.0 code)
    begin(rpm, microsteps);
  }
  this->rpm = rpm;
}

short StepperDriver::setMicrostep(short microsteps) {
  for (short ms = 1; ms <= getMaxMicrostep(); ms <<= 1) {
    if (microsteps == ms) {
      this->microsteps = microsteps;
      break;
    }
  }
  return this->microsteps;
}

/*
   Set speed profile - CONSTANT_SPEED, LINEAR_SPEED (accelerated)
   accel and decel are given in [full steps/s^2]
*/
void StepperDriver::setSpeedProfile(Mode mode, short accel, short decel) {
  this->mode = mode;
  this->accel = accel;
  this->decel = decel;
}

void StepperDriver::move(long steps) {
  long next_event;
  startMove(steps);
  do {
    next_event = nextAction();
    microWaitUntil(micros() + next_event);
  } while (next_event);
}

void StepperDriver::rotate(long deg) {
  move(calcStepsForRotation(deg));
}
/*
   Move the motor with sub-degree precision.
   Note that using this function even once will add 1K to your program size
   due to inclusion of float support.
*/
void StepperDriver::rotate(double deg) {
  move(calcStepsForRotation(deg));
}

void StepperDriver::startMove(long steps) {
  long speed;
  //dir_state = (steps >= 0) ? HIGH : LOW;
  step_state = LOW;
  steps_remaining = abs(steps);
  step_count = 0;
  switch (mode) {
    case LINEAR_SPEED:
      // speed is in [steps/s]
      speed = rpm * motor_steps / 60;
      // how many steps from 0 to target rpm
      steps_to_cruise = speed * speed * microsteps / (2 * accel);
      // how many steps from 0 til we need to begin slowing down
      steps_to_brake = steps_remaining * decel / (accel + decel);
      if (steps_to_cruise < steps_to_brake) {
        // will reach max speed before needing to brake
        steps_to_brake = steps_to_cruise * accel / decel;
      } else {
        // cannot reach max speed, will need to brake early
        steps_to_cruise = steps_to_brake;
        steps_to_brake = steps_remaining - steps_to_cruise;
      }
      // Initial pulse (c0) including error correction factor 0.676 [us]
      step_pulse = (1e+6) * 0.676 * sqrt(2.0f / (accel * microsteps));
      break;
    case CONSTANT_SPEED:
    default:
      step_pulse = STEP_PULSE(rpm, motor_steps, microsteps);
  }
}
/*
   Return calculated time to complete the given move
*/
long StepperDriver::getTimeForMove(long steps) {
  long t;
  switch (mode) {
    case LINEAR_SPEED:
      startMove(steps);
      t = sqrt(2 * steps_to_cruise / accel) +
          (steps_remaining - steps_to_cruise - steps_to_brake) * STEP_PULSE(rpm, motor_steps, microsteps) +
          sqrt(2 * steps_to_brake / decel);
      break;
    case CONSTANT_SPEED:
    default:
      t = STEP_PULSE(rpm, motor_steps, microsteps);
  }
  return t;
}
/*
   Move the motor an integer number of degrees (360 = full rotation)
   This has poor precision for small amounts, since step is usually 1.8deg
*/
void StepperDriver::startRotate(long deg) {
  startMove(calcStepsForRotation(deg));
}
/*
   Move the motor with sub-degree precision.
   Note that calling this function will increase program size substantially
   due to inclusion of float support.
*/
void StepperDriver::startRotate(double deg) {
  startMove(calcStepsForRotation(deg));
}

/*
   calculate the interval til the next pulse
*/
void StepperDriver::calcStepPulse(void) {
  // remainder to be fed into successive steps to increase accuracy (Atmel DOC8017)
  static long rest;

  if (steps_remaining <= 0) { // this should not happen, but avoids strange calculations
    return;
  }

  steps_remaining--;
  step_count++;

  // if constant speed
  if (mode == LINEAR_SPEED) {
    if (step_count <= steps_to_cruise) {
      if (step_count == 1) {    // first step, initialize rest
        rest = 0;
      }
      /*
         accelerating
      */
      step_pulse = step_pulse - (2 * step_pulse + rest) / (4 * step_count + 1);
      rest = (step_count < steps_to_cruise) ? (2 * step_pulse + rest) % (4 * step_count + 1) : 0;
    } else if (steps_remaining > steps_to_brake) {
      /*
         cruising (no speed changes)
      */
    } else {
      /*
         decelerating
      */
      step_pulse = step_pulse - (2 * step_pulse + rest) / (-4 * steps_remaining + 1);
      rest = (2 * step_pulse + rest) % (-4 * steps_remaining + 1);
    }
  }
}
/*
   Toggle step and return time until next change is needed (micros)
*/
long StepperDriver::nextAction(void) {
  if (steps_remaining > 0) {
    /*
       DIR pin is sampled on rising STEP edge, so it is set first
    */
    //digitalWrite(dir_pin, dir_state);
    if (step_state == LOW) {
      step_state = HIGH;
    } else {
      step_state = LOW;
    }
    digitalWrite(step_pin, step_state);
    unsigned m = micros();
    if (step_state == LOW) {
      calcStepPulse();
    }
    m = micros() - m;
    /*
       We currently try to do a 50% duty cycle so it's easy to see.
       Other option is step_high_min, pulse_duration-step_high_min.
    */
    return (step_state == LOW) ? step_pulse - step_high_min - m : step_high_min;
  } else {
    return 0; // end of move
  }
}

/*
   Enable/Disable the motor by setting a digital flag
*/
void StepperDriver::enable(void) {
  digitalWrite(PIN_EN_LEFT, LOW);
  digitalWrite(PIN_EN_RIGHT, LOW);

}

void StepperDriver::disable(void) {
  digitalWrite(PIN_EN_LEFT, HIGH);
  digitalWrite(PIN_EN_RIGHT, HIGH);
}

short StepperDriver::getMaxMicrostep() {
  return StepperDriver::MAX_MICROSTEP;
}
