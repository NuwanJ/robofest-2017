

void loop() {
  displayLoopStatus(mode);
  
  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        beep();

        mode = FIND_ARROW;

        Serial.println(F(">> BEGIN -> ###"));
        delay(500);

      } else {
        //readWalls(wall);
        //delay(1000);
        delay(100);
      }

      break;


    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        mode = BEGIN;
        beep(2);
        Serial.println(F(">> TEST -> BEGIN"));
      } else {
        test();
      }

      break;


    //-------------------------------------------------------------------------------------------------------------- Maze run
    case MAZE_RUN:

      buttonStatus = digitalRead(BUTTON_1);
      readBoxColor();
      
      if (buttonStatus == 0 || (boxColor != 0)) { // Execute whrn button was pressed or color is not equal to 0
        mode = PICKING_BOX;
        saveEEPROM();
        Serial.println(F(">> MAZE RUN -> PICKING_BOX"));
      } else {
        mazeRunAdvanced();
      }

      break;


    //-------------------------------------------------------------------------------------------------------------- Pick the box
    case PICKING_BOX:
      //Go suitable distance back, expand arm and go suitable distance forward, now take the box
      motorWrite(50, -1, -1);
      readyToPick();
      delay(1000);                  // TODO : Must optimize the time, distance
      motorWrite(60, 1, 1);
      pick();
      delay(1000);
      mode = FIND_ARROW;
      Serial.println(F(">> PICKING_BOX -> FIND_ARROW"));
      break;


    //-------------------------------------------------------------------------------------------------------------- Find Arrow
    case FIND_ARROW:
      firstArrowFollow(COLOR_GREEN);
      break;

    case SECOND_ARROW_FOLLOW:
      trailAndErrorArrowFollow_LoopOneArrow(COLOR_GREEN);
      break;

    //-------------------------------------------------------------------------------------------------------------- Maze Option 1 : Run on pre defined maze
    case MAZE_OPTION:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        mode = BEGIN;
      } else {
        loadCommandQueueFromEEPROM();
        executeCommand(commandNo);
        commandNo++;
      }

      break;
  }

}


void displayLoopStatus(int mode){
  Serial.println("New loop iteration>>");
  Serial.print("Free memory: ");
  Serial.println(freeMemory());
  Serial.print("Mode: ");
  switch(mode){
    case BEGIN:
      Serial.println("BEGIN");
      break;
    case TEST:
      Serial.println("TEST");
      break;
    case MAZE_RUN:
      Serial.println("MAZE_RUN");
      break;
    case PICKING_BOX:
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

}
