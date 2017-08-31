void mazeRunAdvanced() {
  readWalls();
  // TODO: does not store the wall data after forward. it will written when next time this function is called. may occur an error at last position
  //finding walls making north as the reference
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
  int wallEncryptCode = binaryWallCode[0] * 8 + binaryWallCode[1] * 4 + binaryWallCode[2] * 2 + binaryWallCode[3];
  mazeWalls[posX][posY] = wallEncryptCode;
  updateMazeWallAddress(posX, posY);

  if (isMazeSolved == 0) {
    if (!wall[RIGHT_SENSOR]) {
      maze_turnRight();
      shiftDirVector(-1);
      currentFacingDir = (currentFacingDir + 1) % 4;
    }
    else if (!wall[FRONT_SENSOR]) {
      maze_goForward();
    }
    else if (!wall[LEFT_SENSOR]) {
      maze_turnLeft();
      currentFacingDir = (currentFacingDir - 1) % 4;
      shiftDirVector(1);
    }
    else {
      maze_turnBack();
      currentFacingDir = (currentFacingDir + 2) % 4;
      shiftDirVector(-2);
    }

    // go forward
    posX += dir[1][0];
    posY += dir[1][1];

    //store the count number in the maze position
    maze[posX][posY] = posCount;
    //save the count position in EEPROM
    updateMazeAddress(posX, posY);
    
    posCount++;

  } else {
    executeCommand(commandNo);
    commandNo++;
  }
  Serial.print(posX);
  Serial.print(" ");
  Serial.print(posY);
  Serial.print(" ");
  Serial.print(posCount);
  Serial.println(" ");
  printCurrentMaze();   // Nuwan
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


void executeCommand(int i){ 
  if (solvedCommandQueue[i] == 3){ // these values need to chage appropriately
    maze_turnLeft();
  }else if (solvedCommandQueue[i] == 0){
    maze_goForward();
  }else if (solvedCommandQueue[i] == 1){
    maze_turnRight();
  }else{
    maze_turnBack(); // never happens :P
  }
}

void printCurrentMaze() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (maze[i][j] < 10)
        Serial.print(" ");
      Serial.print(maze[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }

  Serial.println("----------------------------");

}
