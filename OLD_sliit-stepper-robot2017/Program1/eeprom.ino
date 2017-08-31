

void eepromBegin() {

  kP = (float)EEPROM.read(eP) / 10;
  kI = (float)EEPROM.read(eI) / 10;
  kD = (float)EEPROM.read(eD) / 10;

  //baseSpeed = (int)EEPROM.read(eBase);
  //maxSpeed = (int)EEPROM.read(eMax);
  //debug =  (int)EEPROM.read(eDebug);

}

void saveEEPROM() {

  int addr = 9;
  EEPROM.update(addr, isMazeSolved);
  addr += 1;

  // saving the maze
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      EEPROM.update(addr, maze[i][j]);
      addr += 1;
    }
  }

}

void updateMazeAddress(int i,int j){
  EEPROM.update(10+((i*6)+j), maze[i][j]);
}

void updateMazeWallAddress(int i,int j){
  EEPROM.update(50+((i*6)+j), mazeWalls[i][j]);
}
void loadEEPROM() {
  
  int addr = 9;
  isMazeSolved = EEPROM.read(addr);
  addr += 1;
  if (1) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        maze[i][j] = EEPROM.read(addr);
        if (maze[i][j] == 255) maze[i][j] = 0;
        addr += 1;
      }
    }
  }
}

void cleanEEPROM() {
  
  int addr = 9;
  EEPROM.update(addr, 0);
  addr += 1;
  if (1) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        EEPROM.update(addr, 0);
        addr += 1;
      }
    }
  }
}

