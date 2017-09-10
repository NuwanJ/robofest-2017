//*****************************************
//06/09/2017 gihanchanaka@gmail.com
//These global variales are needed ONLY IF we are using the bottom panel as a colour sensor
int floorColorGrid[6];
int calibratedData[6][4][2];//calibratedData[sensor][color][0=min,1=max]
//*****************************************


void initialize() {
  //06/09/2017 gihanchanaka@gmail.com
  //@Harshana we have to calibrate this before using :-)

  for (int i = 0; i < 6; i++)floorColorGrid[i] = 0;

  //>>>>>>Sensor 0<<<<<<<
  //Red
  calibratedData[0][0][0] = 0; //min
  calibratedData[0][0][1] = 0; //max

  //Green
  calibratedData[0][1][0] = 0; //min
  calibratedData[0][1][1] = 0; //max

  //Blue
  calibratedData[0][2][0] = 0; //min
  calibratedData[0][2][1] = 0; //max

  //>>>>>>Sensor 0 over<<<<<

  //>>>>>>Sensor 1<<<<<<<
  //Red
  calibratedData[1][0][0] = 0; //min
  calibratedData[1][0][1] = 0; //max

  //Green
  calibratedData[1][1][0] = 0; //min
  calibratedData[1][1][1] = 0; //max

  //Blue
  calibratedData[1][2][0] = 0; //min
  calibratedData[1][2][1] = 0; //max

  //>>>>>>Sensor 1 over<<<<<

  //>>>>>>Sensor 2<<<<<<<
  //Red
  calibratedData[2][0][0] = 0; //min
  calibratedData[2][0][1] = 0; //max

  //Green
  calibratedData[2][1][0] = 0; //min
  calibratedData[2][1][1] = 0; //max

  //Blue
  calibratedData[2][2][0] = 0; //min
  calibratedData[2][2][1] = 0; //max

  //>>>>>>Sensor 2 over<<<<<

  //>>>>>>Sensor 3<<<<<<<
  //Red
  calibratedData[3][0][0] = 0; //min
  calibratedData[3][0][1] = 0; //max

  //Green
  calibratedData[3][1][0] = 0; //min
  calibratedData[3][1][1] = 0; //max

  //Blue
  calibratedData[3][2][0] = 0; //min
  calibratedData[3][2][1] = 0; //max

  //>>>>>>Sensor 3 over<<<<<

  //>>>>>>Sensor 4<<<<<<<
  //Red
  calibratedData[4][0][0] = 0; //min
  calibratedData[4][0][1] = 0; //max

  //Green
  calibratedData[4][1][0] = 0; //min
  calibratedData[4][1][1] = 0; //max

  //Blue
  calibratedData[4][2][0] = 0; //min
  calibratedData[4][2][1] = 0; //max

  //>>>>>>Sensor 4 over<<<<<

  //>>>>>>Sensor 5<<<<<<<
  //Red
  calibratedData[5][0][0] = 0; //min
  calibratedData[5][0][1] = 0; //max

  //Green
  calibratedData[5][1][0] = 0; //min
  calibratedData[5][1][1] = 0; //max

  //Blue
  calibratedData[5][2][0] = 0; //min
  calibratedData[5][2][1] = 0; //max

  //>>>>>>Sensor 5 over<<<<<
}



void readFloorColorGrid() {
  //06/09/2017 gihanchanaka@gmail.com
  //This function updates the global variable "floorColorGrid"
  //0---No color detected
  //1-- Red
  //2-- Green
  //3-- Blue

  for (int i = 0; i < 6; i++)floorColorGrid[i] = 0;

  for (int s = 0; s < 6; s++) {
    int thisReading = 0;
    for (int x = 0; x < 5; x++)thisReading += analogReadForLDR(s);
    thisReading /= 5;
    for (int c = 0; c < 3; c++) {
      if (calibratedData[s][c][0] <= thisReading and calibratedData[s][c][0] >= thisReading) {
        floorColorGrid[s] = c + 1;
        break;
      }
    }
  }
}


void firstArrowFollow(int boxColor) {
  readFloorColorGrid();
  Serial.print("Box color = ");
  Serial.println(boxColor);
  Serial.print("Color reading: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(" ");
    Serial.print(floorColorGrid[i]);
  }
  Serial.print("  W=");
  int ws = weightedSumColor(boxColor);
  Serial.println(ws);

  if (ws < 0)goL();
  if (ws > 0)goR();
  if (ws == 0)goF();
  goF();
}

void trailAndErrorArrowFollow_LoopOneArrow(int boxColor){
  //We dont need this
}

int weightedSumColor(int boxColor) {
  int w[6] = { -3, -2, -1, 1, 2, 3};
  int sum = 0;
  for (int i = 0; i < 6; i++)if (floorColorGrid[i] == boxColor)sum += w[i];
  return w;
}


int analogReadForLDR(int i) {
  //06/09/2017
  //To be implemented
  delay(1);
  return analogRead(irPins[i]);
}

