
/****************************************************************************
  Functions

  lineFollowingBegin()
  int, calculatePID()

****************************************************************************/

void lineFollowBegin() {
  //lineType = BLACK;
}

void lineFollow() {
  /*
    pos = readSensorLine(sensor_values);
    error = (pos - CENTER_EDGE_READING);

    if (debug == true) {
      Serial.println(irLineString);
    }

    if (error != lastError) {

      //PID Calculating
      int motorSpeed = calculatePID(error);

      //Assigning motor speeds
      int rightMotorSpeed = baseSpeed + motorSpeed;
      int leftMotorSpeed = baseSpeed - motorSpeed;

      //Remapping motor speed
      //motorWrite(leftMotorSpeed, rightMotorSpeed);

      lastError = error;
    }
  */
}
int calculatePID(int error) {
  /*
    int P = error * kP;
    int I = I + (error * kI);
    int D = (error - lastError) * kD;

    lastError = error;

    return (P + I + D);
  */
}




