void mazeRunAdvanced() {

  readWalls(wall);
  delay(100);

  Serial.print(">> Walls : ");
  Serial.print(wall[0]); Serial.print(wall[1]); Serial.print(wall[2]); Serial.println();

  // TODO: does not store the wall data after forward. it will written when next time this function is called. may occur an error at last position
  //finding walls making north as the reference

  if (isMazeSolved == 0) {
    mazeWalls[posX][posY] = giveBinaryWallCode();
    updateMazeWallAddress(posX, posY);
    explore();

  } else {
    executeCommand(commandNo);
    commandNo++;
  }

  Serial.print(">> X:"); Serial.print(posX); Serial.print(" Y:"); Serial.print(posY); Serial.print(" C:"); Serial.print(posCount); Serial.println();
  Serial.println(F("------------------------------------------------------------"));


}

void explore() {
  // IF YOU WANT LEFT HAND RULE PUT LEFT SENSOR CHECK AS FIRST CHECK!!!

  if (RIGHT_HAND_RULE) {
    if (!wall[RIGHT_SENSOR]) {
      maze_turnRight();
      shiftDirVector(-1);
      currentFacingDir = (currentFacingDir + 1 + 4) % 4;
    }
    else if (!wall[FRONT_SENSOR]) {
      maze_goForward();
    }
    else if (!wall[LEFT_SENSOR]) {
      maze_turnLeft();
      currentFacingDir = (currentFacingDir - 1 + 4) % 4;
      shiftDirVector(1);
    }
    else {
      maze_turnBack();
      currentFacingDir = (currentFacingDir + 2 + 4) % 4;
      shiftDirVector(-2);
    }
  } else {
    if (!wall[LEFT_SENSOR]) {
      maze_turnLeft();
      currentFacingDir = (currentFacingDir - 1 + 4) % 4;
      shiftDirVector(1);
    }
    else if (!wall[FRONT_SENSOR]) {
      maze_goForward();
    }
    else if (!wall[RIGHT_SENSOR]) {
      maze_turnRight();
      shiftDirVector(-1);
      currentFacingDir = (currentFacingDir + 1 + 4) % 4;
    }
    else {
      maze_turnBack();
      currentFacingDir = (currentFacingDir + 2 + 4) % 4;
      shiftDirVector(-2);
    }
  }
  // store the last position as the last valid position in the maze
  //finalXPosition = posX; finalYPosition = posY;  // ##########################################################################################

  // rgo forward
  posX += dir[1][0];
  posY += dir[1][1];

  //check if the robo is out from the maze and change the mode to box picking thingy

  //if (posX < 0 or posX > 5 or posY < 0 or posY > 5) {
  if (posX == finalXPosition && posY == finalYPosition) {
    mode = PICK_BOX; // TODO: change this to correct mode
    isMazeSolved = 1;
    saveEEPROM();
  } else {
    //store the count number in the maze position
    maze[posX][posY] = posCount;
    //save the count position in EEPROM
    updateMazeAddress(posX, posY);

    posCount++;
  }
}

int giveBinaryWallCode() {
  int binaryWallCode[4];
  if (currentFacingDir == 0) {
    binaryWallCode[0] = wall[FRONT_SENSOR];
    binaryWallCode[1] = wall[RIGHT_SENSOR];
    binaryWallCode[2] = 0;
    binaryWallCode[3] = wall[LEFT_SENSOR];
  } else if (currentFacingDir == 1) {
    binaryWallCode[0] = wall[LEFT_SENSOR];
    binaryWallCode[1] = wall[FRONT_SENSOR];
    binaryWallCode[2] = wall[RIGHT_SENSOR];
    binaryWallCode[3] = 0;
  } else if (currentFacingDir == 2) {
    binaryWallCode[0] = 0;
    binaryWallCode[1] = wall[LEFT_SENSOR];
    binaryWallCode[2] = wall[FRONT_SENSOR];
    binaryWallCode[3] = wall[RIGHT_SENSOR];
  } else {
    binaryWallCode[0] = wall[RIGHT_SENSOR];
    binaryWallCode[1] = 0;
    binaryWallCode[2] = wall[LEFT_SENSOR];
    binaryWallCode[3] = wall[FRONT_SENSOR];
  }
  //encrypting walls as int
  return binaryWallCode[0] * 8 + binaryWallCode[1] * 4 + binaryWallCode[2] * 2 + binaryWallCode[3];

}

void shiftDirVector(int c) {
  int tempDir[4][2];
  for (int i = 0; i < 4; i++) {
    tempDir[i][0] = dir[(i + 4 + c) % 4][0];
    tempDir[i][1] = dir[(i + 4 + c) % 4][1];
  }
  for (int i = 0; i < 4; i++) {
    dir[i][0] = tempDir[i][0];
    dir[i][1] = tempDir[i][1];
  }
}
void executeCommand(int i) {
  // check if the box is there in front. before executing this function
  Serial.println(solvedCommandQueue[i]);
  if (solvedCommandQueue[i] == 3) { // these values need to chage appropriately
    maze_turnLeft();
    currentFacingDir = (currentFacingDir + 4 - 1)%4;
  } else if (solvedCommandQueue[i] == 0) {
    maze_goForward();
  } else if (solvedCommandQueue[i] == 1) {
    maze_turnRight();
    currentFacingDir = (currentFacingDir + 4 + 1)%4;
  } else if (solvedCommandQueue[i] == 2) {
    maze_turnBack(); // never happens :P
  } else if (solvedCommandQueue[i] == 4) {
    mode = PICK_BOX;
  } else if (solvedCommandQueue[i] == 10) {
    // fast farward 2 cells
    motorForward(300 * 2);
  } else if (solvedCommandQueue[i] == 20) {
    // fast farward 3 cells
    motorForward(300 * 3);
  } else if (solvedCommandQueue[i] == 30) {
    // fast farward 4 cells
    motorForward(300 * 4);
  } else if (solvedCommandQueue[i] == 40) {
    // fast farward 5 cells
    motorForward(300 * 5);
  } else if (solvedCommandQueue[i] == 50) {
    // fast farward 6 cells
    motorForward(300 * 6);
  }
}

// ---- Maze drive functions ---------------------------------------------------------------------------------------------------


void maze_goForward() {

#if defined(STEPPER_MOTORS)
  if (debug)Serial.println(F("---> Move Forward"));
  motorForward(300);

#elif defined(GEARED_MOTORS)

  motorWrite(maze_forwardStepSpeed, maze_forwardStepSpeed);
  delay(maze_forwardStepTime);
  motorStop()

#endif
}

void maze_turnLeft() {

#if defined(STEPPER_MOTORS)

  if (debug)Serial.println(F("---> Move Left"));
  motorRotate(-100);
  motorRotate(10);
  motorForward(maze_forward_Steps);

#elif defined(GEARED_MOTORS)

  motorWrite(maze_turnLeft_LeftMotorSpeed, maze_turnLeft_RightMotorSpeed);
  delay(maze_turnLeft_Time);
  motorStop();

#endif

}
void maze_turnRight() {

#if defined(STEPPER_MOTORS)
  if (debug)Serial.println(F("---> Move Right"));
  motorRotate(100);
  motorRotate(-10 );
  motorForward(maze_forward_Steps);

#elif defined(GEARED_MOTORS)

  motorWrite(maze_turnRight_LeftMotorSpeed, maze_turnRight_RightMotorSpeed);
  delay(maze_turnRight_Time);
  motorStop();

#endif

}
void maze_turnBack() {

#if defined(STEPPER_MOTORS)
  if (debug)Serial.println(F("---> Move Back"));
  motorRotate(-183);
  motorRotate(10);
  motorForward(maze_forward_Steps);

#elif defined(GEARED_MOTORS)

  motorWrite(maze_turnBack_LeftMotorSpeed, maze_turnBack_RightMotorSpeed);
  delay(maze_turnBack_Time);
  motorStop();

#endif
}

// ------------------------------------------------------------------------------------------------
void printCurrentMaze() {

  Serial.print("#");
  for (int i = 0; i < 6; i++) {
    if ((mazeWalls[0][i] >> 2) % 2)
      Serial.print("####");
    else
      Serial.print("    ");
  }
  Serial.print("\n");

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if ((mazeWalls[i][j] >> 3) % 2)
        Serial.print("#");
      else
        Serial.print(" ");

      Serial.print(maze[i][j]);
      if (maze[i][j] > 99)
        Serial.print("");
      else if (maze[i][j] > 9 or maze[i][j] < 0)
        Serial.print(" ");
      else
        Serial.print("  ");

    }
    if ((mazeWalls[i][5] >> 1) % 2)
      Serial.println("#");
    else
      Serial.println(" ");


    for (int j = 0; j < 6; j++) {
      if ((mazeWalls[i][j] >> 3) % 2 or mazeWalls[i][j - 1] % 2 or (mazeWalls[i + 1][j] >> 3) % 2)
        Serial.print("#");
      else
        Serial.print(" ");
      if (mazeWalls[i][j] % 2)
        Serial.print("###");
      else
        Serial.print("   ");
    }
    Serial.print("#\n");
  }
  Serial.println(F("----------------------------"));
  Serial.print("isMaze : "); Serial.println(isMazeSolved);
  Serial.print("Position  x1: "); Serial.println(startXPosition);
  Serial.print("Position  y1: ");  Serial.println(startYPosition);
  Serial.print("Position  x2: ");  Serial.println(finalXPosition);
  Serial.print("Position  y2: ");  Serial.println(finalYPosition);


}

void printCurrentMazeWalls() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      Serial.print(mazeWalls[i][j]);
      if (mazeWalls[i][j] > 99)
        Serial.print(" ");
      else if (mazeWalls[i][j] > 9 or mazeWalls[i][j] < 0)
        Serial.print("  ");
      else
        Serial.print("   ");

    }
    Serial.print("\n");
  }
  Serial.println(F("----------------------------"));
}




int path[] = {FRONT, LEFT, RIGHT, RIGHT, LEFT, FRONT, FRONT, LEFT, FRONT, BACK, FRONT, RIGHT, FRONT,
              RIGHT, RIGHT, LEFT, FRONT, RIGHT, BACK, FRONT, FRONT, FRONT, LEFT, RIGHT, RIGHT, FRONT,
              RIGHT, FRONT, FRONT, FRONT, FRONT, BACK, FRONT, FRONT, RIGHT, FRONT
             };


int lenIndex = sizeof(path);
int curIndex = 0;

void mazeOption1() {

  if (curIndex < lenIndex) {
    if (path[curIndex] == FRONT) maze_goForward();
    else if (path[curIndex] == LEFT) maze_turnLeft();
    else if (path[curIndex] == RIGHT) maze_turnRight();
    else if (path[curIndex] == BACK) maze_turnBack();

    curIndex++;
  }
  else {
    mode = PICK_BOX;
    delay(10000);
  }
  delay(100);

}

