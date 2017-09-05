/*
	04/09/2017 gihanchanaka@gmail.com
	These are the utilities for the arrow following part


	I am putting all the functions here instead of keeping a copy in every file
*/

int sign(int x) {
  if (x > 0)return 1;
  if (x < 0)return -1;
  return 0;
}


void turnCW(int degrees) {
  //I am assuming that this function can turn the robot clockwise to 10 degrees
  motorRotate(degrees);
}

void goFoward(int mm) {
  if (mm > 0) {
    motorWrite(mm * 10, mm * 10);
  } else {
    motorWrite(mm * -10 , mm * -10);
  }
}

int getColorReading() {
  //This function can get the colour reading as 1-RED,2-GREEn.3=BLUE
  // TODO
  readColor();
  Serial.print("Color = ");
  if (floorColor == 1)Serial.println("R");
  else if (floorColor == 2)Serial.println("G");
  else if (floorColor == 3)Serial.println("B");
  else Serial.println("None");
  return floorColor;

}

int sumOfArray(int ar[], int n) {
  int sum = 0;
  for (int i = 0; i < n; i++)sum += ar[i];
  return sum;
}

void goF() {
  //03/09/2017 go forward
  motorWrite(100, 100);
  delay(100);
}

void goFF() {
  //Go forward 2 steps
  motorWrite(200, 200);
  delay(100);
}


void goL() {
  //03/09/2017 turn left
  motorWrite(-100, 100);
  delay(100);
}

void goR() {
  //03/09/2017  turn right
  motorWrite(100, -100);
  delay(100);
}

void goB() {
  //03/09/2017 go back
  motorWrite(-100, -100);
  delay(100);
}


void goLF() {
  //03/09/2017 turn left and go forward
  goL();
  goF();
}

void goRF() {
  //03/09/2017 turn right and go forward
  goR();
  goF();
}

void goBR() {
  //go back and turn right
  goB();
  goR();
}

void goBL() {
  //go back and turn left
  goB();
  goL();
}

void goFF() {
  goF();
  goF();
}

void goBB() {
  goB();
  goB();
}

int updatedWeightedSum() {
  //03/09/2017
  int weight[6] = { -3, -2, -1, 1, 2, 3};
  readSensorLine(reading);
  int weightedSum = 0;
  for (int j = 0; j < 6; j++) weightedSum += reading[j] * weight[j];
  return weightedSum;
}
