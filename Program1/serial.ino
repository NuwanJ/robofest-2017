
//TODO: Need well defined communication protocol

void serialEvent() {

  while (Serial.available()) {

    digitalWrite(13, HIGH);

    int r = Serial.read();
    char inChar = (char)r;

    if (inChar == 'b') {
      byte val = 0;
      debug = ! debug;
      EEPROM.update(debug, debug);
      Serial.print(F(">> Print\t:")); Serial.println(debug);
    }

    else if (inChar == 'p') {
      loadEEPROM();
      printCurrentMaze();
      printCurrentMazeWalls();

    }
    else if (inChar == 'c') {
      cleanEEPROM();
      Serial.println(F(">> Maze cleaned"));
    }

    else if (inChar == 'q') {
      readSensorLine(sensor_values);
      Serial.println(irLineString);
    }
    else if (inChar == 's') {
      /*
        Serial.print("Kp\t:"); Serial.println(kP * 10);
        Serial.print("Ki\t:"); Serial.println(kI * 10);
        Serial.print("Kd\t:"); Serial.println(kD * 10);
        Serial.print("Base\t:" ); Serial.println(baseSpeed);
        Serial.print("Max\t:"); Serial.println(maxSpeed);
        Serial.print("Debug\t:"); Serial.println(debug);
      */
    }

    else if (inChar == 't') {
      //readWalls(wall);
      readBoxColor();
      //mySerial.print("j");


      if (mySerial.available() > 0) {
        while (mySerial.available()) {
          Serial.print((char)mySerial.read());
        }
      }


    } else if (inChar == 'z') {
      char rOrd;
      int spdArr[5];
      double spd = 0, val = 0;
      int valArr[5];
      Serial.println("Rotate - r, Distance - d, Exit - x\nspeed a10s steps q200w   eg: zra10sq100w");

      while (Serial.available()) {
        int r = Serial.read();
        rOrd = (char)r;
        if (rOrd == 'x' or rOrd == 'r' or rOrd == 'd') break;
      }
      if (rOrd == 'x') break;
      int i;
      while (Serial.available()) {
        int r = Serial.read();
        if ((char) r == 'a') {
          i = 0;
        } else if ((char) r == 's') {
          break;
        } else if ((char) r >= '0' and (char)r <= '9') {
          spdArr[i] = r - '0';
          i++;
        }
      }
      for (int j = i - 1; j > -1; j--) {
        spd += spdArr[i - 1 - j] * pow(10, j);
      }


      while (Serial.available()) {
        int r = Serial.read();
        if ((char) r == 'q') {
          i = 0;
        } else if ((char) r == 'w') {
          break;
        } else if ((char) r >= '0' and (char)r <= '9') {
          valArr[i] = r - '0';
          i++;
        }
      }
      val = 0;
      for (int j = i - 1; j > -1; j--) {
        val += valArr[i - 1 - j] * pow(10, j);
      }
      stepsToRotate(round(spd), val);
      testAndGetData(rOrd, spd, val);
    }
    else if (mode == BLUETOOTH) {

#if defined(STEPPER_MOTORS)
      if  (inChar == '8')motorWrite(100, 1, 1);
      else if (inChar == '2')motorWrite(100, -1, -1);
      else if (inChar == '4')motorWrite(100, 1, -1);
      else if (inChar == '6')motorWrite(100, -1, 1);

#elif defined(GEARED_MOTORS)
      if  (inChar == '8')motorWrite(baseSpeed, baseSpeed);
      else if (inChar == '2')motorWrite(-1 * baseSpeed, -1 * baseSpeed);
      else if (inChar == '4')motorWrite(baseSpeed, -1 * baseSpeed);
      else if (inChar == '6')motorWrite(-1 * baseSpeed, baseSpeed);
#endif
    }


    digitalWrite(13, LOW);
  }
}


void readBoxColor() {
  mySerial.print("j");
  delay(10);
  while (mySerial.available() > 0) {
    int x = Serial.read() - '0';
    //Serial.print(">> Reply: "); Serial.println(x);

    if (x >= 0 && x < 4) {
      boxColor = x;
      break;
    } else if (x == -49) {
      break;
    }
  }
  //return boxColor;
}
void stand() {
  mySerial.print("f");
  Serial.println(F(">> Stand:Complete"));
}

void readyToPick() {
  mySerial.print("e");
  Serial.println(F(">> Stand:readyToPick"));
}

void pick() {
  mySerial.print("g");
  Serial.println(F(">> Pick:Complete"));
}

void drop() {
  mySerial.print("h");
  Serial.println(F(">> Drop:Complete"));
}

void beep() {
  mySerial.print("k");

}

void beep(int k) {
  for (k; k > 0; k--)mySerial.print("k");
}


