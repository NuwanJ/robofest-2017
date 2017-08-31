
void loop() {

  switch (mode) {
    case TEST:

      buttonStatus = digitalRead(BUTTON_1);
      //Serial.println(buttonStatus);

      if (buttonStatus == 0 ) {
        mode = BEGIN;
        delay(500);
        Serial.println(">> Mode : MazeRun");
        //mode = MAZE_RUN; //MAZE_RUN_ADVANCED;
      } else {
        test();
      }

      break;

    case BEGIN:
      buttonStatus = digitalRead(BUTTON_2);

      if (buttonStatus == 0 ) {

        /*pos = CENTER_EDGE_READING;
        error = 0;
        lastError = 0;*/

        mode = TEST;
        Serial.println(">> Mode : Test");
        delay(500);
        //mode = MAZE_RUN; //MAZE_RUN_ADVANCED;
      }

      break;


    case MAZE_RUN:
      readWalls();
      readColor();

      if (color != COLOR_OPEN) {
        mode = PICKING_BOX;
      } else {
        mazeRun();
      }

      break;


    case MAZE_RUN_ADVANCED:
      readWalls();
      readColor();

      if (color != COLOR_OPEN) {
        if (isMazeSolved == 0 ) {
          isMazeSolved = 1;
        }
        mode = PICKING_BOX;
        break;
      }
      mazeRunAdvanced();
      break;
  }

}
