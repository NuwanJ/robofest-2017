

void BFS(int* distance) {
  mazeWalls[5][5] += 1; // back wall is always there in firstcell!!!!!!!!!!!!!!!!!!!!!!!!!!
  //edges are defined as walls in mazeWalls
  //nodes are defined as cells in maze
  int queue[36]; // can this be larger than 36??????? since there are loops????
  int queueP = 0; //points to the last element in the queue
  
  int visited[36];
  //initilialize queue with -1
  //initialize visited with 0;
  //initialize distance with 255;
  for (int i = 0; i < 36; i++) {
    visited[i] = 0; queue[i] = -1; distance[i] = 255;
  }

  queue[queueP] = 35; //starting from (5,5)
  distance[queue[0]] = 0; // start distance is 0
  
  int currentCell;
  int edges;
  int isWall;
  int depth = 0;
  
  while (1) {
    if (queueP < 0){
      finalXPosition = currentCell/6; finalYPosition = currentCell%6;
      break;
    }
    currentCell = pop(queue,36);
    Serial.print("-----------------------------------------------------------\nChecking cell ");
    Serial.println(currentCell);
    if (visited[currentCell]) {
      queueP--;
      continue;
    }

    visited[currentCell] = 1;
    edges = mazeWalls[currentCell / 6][currentCell % 6];
    queueP--;

    if (edges == -1) continue;

    depth += 1;
    
    Serial.print("Going to Cell ");
    Serial.println(currentCell);
    Serial.print("walls ");
    Serial.println(edges, BIN);
    for (int j = 0; j < 4; j++) {
      isWall = edges % 2;
      edges = edges >> 1;
      if (isWall)
        continue;
      
      queueP++;
      switch (j) {
        case 0: //No wall at south
          if (currentCell+6>35){queueP=-1; Serial.println("Out of the maze from south");continue;}
          if (visited[currentCell + 6]) {queueP--;continue;}
          queue[queueP] = currentCell + 6; distance[queue[queueP]] = distance[currentCell] + 1;break;
        case 1: //No wall at east
          if ((currentCell+1)&6==0){queueP=-1; Serial.println("Out of the maze from east");continue;}
          if (visited[currentCell + 1]) {queueP--;continue;}
          queue[queueP] = currentCell + 1; distance[queue[queueP]] = distance[currentCell] + 1;break;
        case 2: //No wall at north
          if (currentCell-6<0){queueP=-1; Serial.println("Out of the maze from north");continue;}
          if (visited[currentCell - 6]) {queueP--;continue;}
          queue[queueP] = currentCell - 6; distance[queue[queueP]] = distance[currentCell] + 1;break;
        case 3: //No wall at west
          if (currentCell%6==0){queueP=-1; Serial.println("Out of the maze from west");continue;}
          if (visited[currentCell - 1]) {queueP--; continue;}
          queue[queueP] = currentCell - 1; distance[queue[queueP]] = distance[currentCell] + 1;break;
      
      }
      
    }
    //printArr(distance, 36);
  }

  Serial.print("Optimum number of steps ");
  Serial.println(distance[currentCell]);

}


void DFS(int* exittime) {
  
  int queue[36]; // can this be larger than 36??????? since there are loops????
  int queueP = 0; //points to the last element in the queue

  
  int visited[36];
  //initilialize queue with -1
  //initialize visited with 0;
  //initialize distance with 255;
  for (int i = 0; i < 36; i++) {
    visited[i] = 0; queue[i] = -1; exittime[i] = 0;
  }

  queue[queueP] = 35; //starting from (5,5)

  int currentCell;
  int edges;
  int isWall;
  int extime = 0;
  
  while (1) {
    if (queueP < 0)
      break;
    currentCell = queue[queueP];
    Serial.print("-----------------------------------------------------------\nChecking cell ");
    Serial.println(currentCell);
    if (visited[currentCell]) {
      queueP--;
      continue;
    }

    visited[currentCell] = 1;
    edges = mazeWalls[currentCell / 6][currentCell % 6];
    queueP--;

    if (edges == -1) continue;

    extime += 1;
    exittime[currentCell] = extime;
    Serial.print("Going to Cell ");
    Serial.println(currentCell);
    
    for (int j = 0; j < 4; j++) {
      isWall = edges % 2;
      edges = edges >> 1;
      if (isWall)
        continue;
      
      queueP++;
      switch (j) {
        case 0: //No wall at south
          if (currentCell+6>35){queueP=-1; Serial.println("Out of the maze from south");continue;}
          if (visited[currentCell + 6]) {queueP--;continue;}
          queue[queueP] = currentCell + 6; break;
        case 1: //No wall at east
          if ((currentCell+1)&6==0){queueP=-1; Serial.println("Out of the maze from east");continue;}
          if (visited[currentCell + 1]) {queueP--;continue;}
          queue[queueP] = currentCell + 1; break;
        case 2: //No wall at north
          if (currentCell-6<0){queueP=-1; Serial.println("Out of the maze from north");continue;}
          if (visited[currentCell - 6]) {queueP--;continue;}
          queue[queueP] = currentCell - 6; break;
        case 3: //No wall at west
          if (currentCell%6==0){queueP=-1; Serial.println("Out of the maze from west");continue;}
          if (visited[currentCell - 1]) {queueP--; continue;}
          queue[queueP] = currentCell - 1; break;
      
      }
      
    }
    //printArr(exittime,36);
  }

}

int pop(int*arr, int n){
  int x = arr[0];
  for (int i=0;i<n-1;i++){
   arr[i] = arr[i+1];
  }
  return x;
}

void printArr(int* arr, int n){
  for (int i=0;i<n;i++){
    Serial.print(arr[i]);
    Serial.print(" ");
    if ((i+1)%6==0) Serial.println("");
  }
  Serial.println("");
}

