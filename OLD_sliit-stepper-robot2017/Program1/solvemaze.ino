void solveMaze() {

  int distance[36];
  BFS(distance);
  int exittime[36];
  DFS(exittime);
  printArr(distance, 36);
  printArr(exittime, 36);
  removeConflicts(distance, exittime);
  printArr(distance, 36);
  
  findPath(distance);
  printArr(solvedCommandQueue,36);

}


void findPath(int* distance) {
  int currentFacingDir = 1; // facing north
  int pos = 35; // start position (5,5)

  int eastDist, westDist, northDist, southDist;
  int distArr[4];
  int nextIndex;
  int solvedCommandQueueIndex = 0;

  int distCount = 0; // this will count the distance from BFS and follow while incrementing
  while (1) {
    Serial.println(pos);
    if (pos/6 == finalXPosition and pos%6==finalYPosition) {
      break;
    }
    distance[pos] = 255; // since current pos will never visit again
    if (pos - 1 > -1)
      westDist = distance[pos - 1];
    else
      westDist = 255;
    if (pos - 6 > -1)
      northDist = distance[pos - 6];
    else
      northDist = 255;
    if (pos + 1 < 36)
      eastDist = distance[pos + 1];
    else
      eastDist = 255;
    if (pos + 6 < 36)
      southDist = distance[pos + 6];
    else
      southDist = 255;

    distArr[0] = westDist; distArr[1] = northDist; distArr[2] = eastDist; distArr[3] = southDist;
    
    nextIndex = -1;
    for (int i=0;i<4;i++){
      if (distArr[i] == distCount+1){
        nextIndex = i;
        break;
      }
    }

    distCount++;
    
    solvedCommandQueue[solvedCommandQueueIndex] = (-currentFacingDir + nextIndex)%4;
    solvedCommandQueueIndex++;
    currentFacingDir = nextIndex;
    switch (currentFacingDir){
      case 0:pos=pos-1;break;
      case 1:pos=pos-6;break;
      case 2:pos=pos+1;break;
      case 3:pos=pos+6;break;
    }
  }

}

void removeConflicts(int* distance, int* exittime) {
  int eastDist, westDist, northDist, southDist;
  int distArr[4];

  int eastExittime, westExittime, northExittime, southExittime;
  int exittimeArr[4];
  int posX, posY;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      posX=5-i; posY=5-j;
      if (posY + 1 >= 0 && posY + 1 < 6) {
        eastDist = distance[posX * 6 + posY + 1];   eastExittime = exittime[posX * 6 + posY + 1];
      }
      else {
        eastDist = 255;  eastExittime = 0;
      }
      if (posX - 1 >= 0 && posX - 1 < 6) {
        northDist = distance[(posX - 1) * 6 + posY]; northExittime = exittime[(posX - 1) * 6 + posY];
      }
      else {
        northDist = 255; northExittime = 0;
      }
      if (posY - 1 >= 0 && posY - 1 < 6) {
        westDist = distance[posX * 6 + posY - 1]; westExittime = exittime[posX * 6 + posY - 1];
      }
      else {
        westDist = 255; westExittime = 0;
      }
      if (posX + 1 >= 0 && posX + 1 < 6) {
        southDist = distance[(posX + 1) * 6 + posY]; southExittime = exittime[(posX + 1)*6 + posY];
      }
      else {
        southDist = 255; southExittime =0;
      }

      distArr[0] = westDist; distArr[1] = northDist; distArr[2] = eastDist; distArr[3] = southDist;
      exittimeArr[0] = westExittime; exittimeArr[1] = northExittime; exittimeArr[2] = eastExittime; exittimeArr[3] = southExittime;
      for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
          if (distArr[i] == 255 or distArr[j] == 255) continue;
          
          if (distArr[i] == distArr[j]) {
            if (exittimeArr[i] < exittimeArr[j]) { // find the best side to turn. make the unwanted path as 100. so robo will not go there.
              distArr[i] = 100;
            } else {
              distArr[j] = 100;
            }
          }
        }
      }


      for (int k = 0; k < 4; k++) {
        if (distArr[k] == 100) { // change where needed
          switch (k) {
            case 0: distance[posX * 6 + posY - 1] = 100; break;
            case 1: distance[(posX - 1) * 6 + posY] = 100; break;
            case 2: distance[posX * 6 + posY + 1] = 100; break;
            case 3: distance[(posX + 1) * 6 + posY] = 100; break;
          }
        }
      }

      
    }
  }
}

