
/*
   b -> debug (on|off)
   p -> print curent Maze
   c -> clean current maze
   q -> print IR sensor values
   t -> test
   z -> interpolate
   w -> readWalls
     -> bluetooth mode
*/
void serialEvent() {

  while (Serial.available()) {

    digitalWrite(13, HIGH);

    int r = Serial.read();
    char inChar = (char)r;


    //-------------------------------------------------------------------------------------------------------------- b -> debug
    if (inChar == 'b') {
      byte val = 0;
      debug = ! debug;
      EEPROM.update(debug, debug);
      Serial.print(F(">> Print\t:")); Serial.println(debug);
    }

    //-------------------------------------------------------------------------------------------------------------- p -> print curent Maze
    else if (inChar == 'p') {
      loadEEPROM();
      printCurrentMaze();
      printCurrentMazeWalls();
    }

    //-------------------------------------------------------------------------------------------------------------- w -> read Walls
    else if (inChar == 'w') {
      wall[RIGHT_SENSOR] = digitalRead(PIN_RIGHT_WALL_SENSOR);
      wall[FRONT_SENSOR] = digitalRead(PIN_FRONT_WALL_SENSOR);
      wall[LEFT_SENSOR] = digitalRead(PIN_LEFT_WALL_SENSOR);

      Serial.print(F(">> Walls :"));
      Serial.print(wall[LEFT_SENSOR]);
      Serial.print(wall[FRONT_SENSOR]);
      Serial.println(wall[RIGHT_SENSOR]);
    }

    //-------------------------------------------------------------------------------------------------------------- c -> clean current maze
    else if (inChar == 'c') {
      cleanEEPROM();
      Serial.println(F(">> Maze cleaned"));
    }

    //-------------------------------------------------------------------------------------------------------------- k -> sound buzzer
    else if (inChar == 'k') {
      beep();
      Serial.println(">> Beep...");
    }

    //-------------------------------------------------------------------------------------------------------------- q -> print IR sensor values
    else if (inChar == 'q') {
      readSensorLine(sensor_values);
      Serial.println(irLineString);
      Serial.print("Sum=");
      Serial.println(sumOfArray(sensor_values, 6));
    }

    //-------------------------------------------------------------------------------------------------------------- s -> ???
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
    else if (inChar == '*') {
      debugProcedure();
    }

    else if (inChar == 'x') {
      //Go suitable distance back, expand arm and go suitable distance forward, now take the box
      motorWrite(50, -1, -1);
      readyToPick();
      delay(2000);                  // TODO : Must optimize the time, distance
      motorWrite(80, 1, 1);
      pick();
      delay(1000);
      beep();
      Serial.println(F(">> PICKING_BOX -> FIND_ARROW"));
    }

    else if (inChar == 'y') {
      drop();
      beep(3);
      Serial.println(F(">> Task is completed"));
    }


    //-------------------------------------------------------------------------------------------------------------- t -> test
    else if (inChar == 't') {

      readColor();
      Serial.println(floorColor);

      //-------------------------------------------------------------------------------------------------------------- z -> interpolate
    } else if (inChar == 'z') {

      /*char rOrd;
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
        stepsToRotate(round(spd), val/(double)100);
        testAndGetData(rOrd, spd, (double)100);*/
    }

    //-------------------------------------------------------------------------------------------------------------- 2,4,5,6,7,8,9-> bluetooth mode
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

    else if (inChar == '+') {
      pick();
    }
    else if (inChar == '-') {
      drop();
    }

    digitalWrite(13, LOW);
  }
}







int readBoxColor() {

  while (mySerial.available()) {} // nothing
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
  boxColorReading = boxColor;

  return boxColor;
}
void stand() {
  mySerial.print("w");
  Serial.println(F(">> Stand:Complete"));
}

void readyToPick() {
  mySerial.print("q");
  Serial.println(F(">> Stand:readyToPick"));
}

void pick() {
  mySerial.print("e");
  Serial.println(F(">> Pick:Complete"));
}

void drop() {
  mySerial.print("r");
  Serial.println(F(">> Drop:Complete"));
}

void beep() {
  mySerial.print("k");
}

void beep(int k) {
  for (k; k > 0; k--)mySerial.print("k");
}

void ledBlue() {
  mySerial.print("]");
}
void ledRed() {
  mySerial.print("]");
}
void ledGreen() {
  mySerial.print("|");
}

