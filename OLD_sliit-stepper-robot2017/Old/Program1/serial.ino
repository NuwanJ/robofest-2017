String inputString = "";         // a string to hold incoming data
String cmd2 = "";
boolean stringComplete = false;  // whether the string is complete

void serialEvent() {

  while (Serial.available()) {

    digitalWrite(13, HIGH);

    int r = Serial.read();
    char inChar = (char)r;

    if (inChar == 'b') {
      byte val = 0;
      debug = ! debug;
      EEPROM.update(debug, debug);
      Serial.print("Print\t:"); Serial.println(debug);
    }
    else if (inChar == 's') {
      Serial.print("Kp\t:"); Serial.println(kP * 10);
      Serial.print("Ki\t:"); Serial.println(kI * 10);
      Serial.print("Kd\t:"); Serial.println(kD * 10);
      Serial.print("Base\t:" ); Serial.println(baseSpeed);
      Serial.print("Max\t:"); Serial.println(maxSpeed);
      Serial.print("Debug\t:"); Serial.println(debug);
    }
    else if (inChar == 'm') {

    }
    else if (inChar == 't') {
      /*readWalls();
        Serial.print(wall[2]);
        Serial.print(wall[1]);
        Serial.print(wall[0]);
        Serial.println();*/

      readColor();
      Serial.println(color);
    }

    else if (mode == BLUETOOTH) {
      if (inChar == '8')motorWrite(maxSpeed, maxSpeed);
      else if (inChar == '2')motorWrite(-maxSpeed, -maxSpeed);
      else if (inChar == '6')motorWrite(maxSpeed / 2, -maxSpeed / 2);
      else if (inChar == '4')motorWrite(-maxSpeed / 2, maxSpeed / 2);
      else if (inChar == '5')motorStop();
      else if (inChar == '9')motorWrite(maxSpeed / 2, 0);
      else if (inChar == '7')motorWrite(0, maxSpeed / 2);

    }
    digitalWrite(13, LOW);
  }
}


