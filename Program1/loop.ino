int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);
      //readColor();

      if (buttonStatus == 0 ) {
        beep();
        stand();

        mode = MAZE_OPTION;// PICK_BOX; //FIND_ARROW;

        Serial.println(F(">> BEGIN -> ###"));
        //delay(500);

      } else {
        //readWalls(wall);
        //delay(1000);
        delay(50);
      }

      break;


    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      buttonStatus = digitalRead(BUTTON_1);

      debugProcedure() ;

      if (buttonStatus == 0 ) {
        mode = BEGIN;
        beep(2);
        Serial.println(F(">> TEST -> BEGIN"));
      } else {
        //test();
      }

      break;


    //-------------------------------------------------------------------------------------------------------------- Maze run
    case MAZE_RUN:

      mazeRunAdvanced();
      break;


    //-------------------------------------------------------------------------------------------------------------- Pick the box
    case PICK_BOX:

      //Go suitable distance back, expand arm and go suitable distance forward, now take the box
      motorWrite(50, -1, -1);       // Going out from maze towards box
      readyToPick();
      delay(1000);                  // TODO : Must optimize the time, distance Important !!!
      drop();
      delay(1000);
      motorWrite(100, 1, 1);
      boxColorReading = readBoxColor();
      delay(1000);
      pick();
      delay(1000);
      motorWrite(120, -1, -1);
      delay(500);
      mode = FIND_ARROW;
      beep();
      Serial.println(F(">> PICKING_BOX -> FIND_ARROW"));
      break;


    //-------------------------------------------------------------------------------------------------------------- Find Arrow
    case FIND_ARROW:

      // Set speed profile to linear speed with default values
      //stepper.setSpeedProfile(LINEAR_SPEED, 500, 2000);    //TODO: LINEAR_SPEED | CONSTANT_SPEED   500,2000

      firstArrowFollow(boxColorReading);
      break;

    case SECOND_ARROW_FOLLOW:
      trailAndErrorArrowFollow_LoopOneArrow(boxColorReading);
      break;


    //-------------------------------------------------------------------------------------------------------------- Drop box
    case DROP_BOX:
      drop();
      beep(3);
      Serial.println(F(">> Task is completed"));
      mode = BEGIN;
      break;

    //-------------------------------------------------------------------------------------------------------------- End of the program





    //-------------------------------------------------------------------------------------------------------------- Maze Option 1 : Run on pre defined maze
    case MAZE_OPTION:

      mazeOption1();
      /*buttonStatus = digitalRead(BUTTON_1);

        if (buttonStatus == 0 ) {
        mode = BEGIN;
        } else {
        loadCommandQueueFromEEPROM();
        executeCommand(commandNo);
        commandNo++;
        }*/
      break;
  }
}


void displayLoopStatus(int mode) {
  /*Serial.println("New loop iteration>>");
    Serial.print("Free memory: ");
    Serial.println(freeMemory());
    Serial.print("Mode: ");*/

  if (mode != oldMode) {
    oldMode = mode;
    Serial.println(F("--------------------------------------------------"));
    switch (mode) {
      case BEGIN:
        Serial.println("BEGIN");
        break;
      case TEST:
        Serial.println("TEST");
        break;
      case MAZE_RUN:
        Serial.println("MAZE_RUN");
        break;
      case PICK_BOX:
        Serial.println("PICKING_BOX");
        break;
      case FIND_ARROW:
        Serial.println("FIND ARROW");
        break;
      case SECOND_ARROW_FOLLOW:
        Serial.println("SECOND_ARROW_FOLLOW");
        break;
      case MAZE_OPTION:
        Serial.println("MAZE_OPTION");
        break;
    }
    Serial.println(F("--------------------------------------------------"));
  }
}



void debugProcedure() {
  //06/09/2017 gihanchanaka@gmail.com

  beep();

  //Go forward 1 feet
  motorWrite(200, 1, 1);
  delay(1000);
  motorWrite(200, -1, -1);
  delay(1000);

  //Take 2 clock wise 90 deg turns
  turnCW(90);

  //Take 2 anti cock wise 90 deg turns
  turnCW(-90);

  //Go backward 1 feet
  goB();
  delay(1000);
  goBB();
  delay(1000);

  //print wall readings (3 times with 4 sec delays)
  for (int j = 0; j < 3; j++) {
    readWalls(wall);
    for (int i = 0; i < 3; i++) {
      Serial.print(wall[i]);
      Serial.print(" ");
    }
    Serial.println();
    delay(2000);
  }

  //Print LDR readings (3 times with 4 sec delays)
  for (int j = 0; j < 3; j++) {
    readSensorLine(reading);
    for (int i = 0; i < 6; i++) {
      Serial.print(reading[i]);
      Serial.print(" ");
    }
    Serial.print("Weighted sum= ");
    Serial.print(updatedWeightedSum());
    Serial.println();
    delay(4000);
  }

  beep();

  //Print colour readings (3 times with 4 sec delays)
  for (int j = 0; j < 3; j++) {
    Serial.print("Floor = ");
    printColor(getColorReading());
    Serial.print(" Box= ");
    readBoxColor();
    printColor(boxColor);
    Serial.println("");
    delay(4000);
  }


  beep(3);
}


void printColor(int c) {
  //06/09/2017 gihanchanaka@gmail.com
  if (c == 1) Serial.print("R");
  if (c == 2) Serial.print("G");
  if (c == 3) Serial.print("B");
  if (c<1 or c>3) Serial.print("N");
}


