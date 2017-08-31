
//dir_state = (steps >= 0) ? HIGH : LOW;

void stepperMotorBegin() {

  // Setting pinModes
  pinMode(PIN_EN_LEFT, OUTPUT);
  pinMode(PIN_EN_RIGHT, OUTPUT);

  pinMode(PIN_DIR_LEFT, OUTPUT);
  pinMode(PIN_DIR_RIGHT, OUTPUT);

  pinMode(PIN_STEP, OUTPUT);

  // Initial values
  digitalWrite(PIN_DIR_LEFT, HIGH);
  digitalWrite(PIN_DIR_RIGHT, HIGH);
  digitalWrite(PIN_STEP, LOW);


  stepper.begin(60, MICROSTEPS);
  stepper.setSpeedProfile(CONSTANT_SPEED, 500, 500);    //LINEAR_SPEED
}

void motorForward(int steps) {
  motorWrite(steps, 1, 1);
}

void motorBackward(int steps) {
  motorWrite(steps, -1, -1);
}


void motorRotate(double angle) {

  //double steps = STEPS_FOR_ROUND * (double)(angle / 360);
  //
  int steps = STEPS_FOR_ROUND * (double)(angle / 360);
  Serial.println(steps);

  
  if (steps > 0) {
    // CW
    motorWrite(steps, 1, -1);
  } else {
    // CCW
    motorWrite(steps, -1, 1);
  }
}

long motorWrite(int steps, int left, int right) {
  stepper.enable();
  // Motor Enable : Done by library
  /*digitalWrite(PIN_EN_LEFT, (left != 0));
    digitalWrite(PIN_EN_RIGHT, (right != 0));*/

  digitalWrite(PIN_DIR_LEFT, (left == 1));
  digitalWrite(PIN_DIR_RIGHT, (right == 1));

  stepper.move(steps * MICROSTEPS);
  delay(50);
  stepper.disable();
  return 1;

  //stepper.getTimeForMove(steps);

}

