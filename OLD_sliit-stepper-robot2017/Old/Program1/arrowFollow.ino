

void centerLine() {

  pos = readSensorLine(sensor_values);
  error = (pos - CENTER_EDGE_READING);

  if (debug == true) {
    //Serial.println(irLineString);
  }

  //Temp
  /*if (abs(error) < 20 && ~allOut) {
    motorWrite(80, 80);
    delay(100);
    motorStop();
    }*/

  if (error != lastError) { // error != lastError

    //PID Calculating
    int motorSpeed = calculateMazePID(error);

    //Assigning motor speeds
    int rightMotorSpeed =  motorSpeed;
    int leftMotorSpeed = motorSpeed;

    //Remapping motor speed
    motorWrite(-1 * leftMotorSpeed, rightMotorSpeed);


    Serial.print(-1 * leftMotorSpeed);
    Serial.print(" ");
    Serial.println(rightMotorSpeed);
    //delay(20);
    lastError = error;
  }

}


int calculateMazePID(int error) {

  int P = error * 5;
  int I = ((I) + (error * 1)) * 0;
  int D = (error - lastError) * 0.5;

  lastError = error;

  return error;
  /*if (abs(P + I + D) >= 80  )return (P + I + D);
    else return ((error) / abs(error)) * 80;*/
}

