/*
  This code runs after lifting the box
*/

//int RED = 1, GREEN = 2, BLUE = 3;

#include <math.h>    // (no semicolon)
static int reading[6];


void start_old(int boxColor) {
  //This uses the colour reading as 1-RED,2-GREEN.3=BLUE

  int directions = 5;
  int gap = 15; //degrees
  int steps = 5;
  int stepSize = 40; //mm

  Serial.println("Starting the arrow finding algo");
  Serial.print(directions);
  Serial.print(" directions will be checked with ");
  Serial.print(gap);
  Serial.print(" deg betweeen two directions.");
  Serial.println("");
  Serial.print(steps);
  Serial.print(" steps of length ");
  Serial.print(stepSize);
  Serial.print("cm ");

  int reading[directions][steps];

  turnCW(-1 * gap * (directions - 1) / 2);

  for (int d = 0; d < directions; d++) {
    for (int s = 0; s < steps; s++) {
      reading[d][s] = 0;
      if (getColorReading() == boxColor) {
        reading[d][s]++;
      }
      if (s != steps - 1) {
        goFoward(stepSize);
      }
    }

    for (int s = 0; s < steps; s++) {
      if (getColorReading() == boxColor) {
        reading[d][s]++;
      }
      if (s != steps - 1) {
        goFoward(-stepSize);
      }
    }
    Serial.print("Direction ");
    Serial.print(d);
    Serial.print(" of ");
    Serial.print(directions);
    Serial.print(" complete");
    Serial.println("");
    turnCW(gap);
  }

  Serial.println("The matrix of readings:");
  Serial.println("Row= step, Col=Direction");
  for (int s = steps - 1; s > -1; s--) {
    Serial.print("Step ");
    Serial.print(s);
    Serial.print("-- ");
    for (int d = 0; d < directions; d++) {
      Serial.print(reading[d][s]);
      Serial.print(" ");
    }
    Serial.println("");
  }


  turnCW(-1 * gap * (directions - 1) / 2);
  //NOW WE ARE AT THE CENTER AGAIN!
  goFoward(10);
  goFoward(-100);


  int arcSum[steps];

  for (int s = steps - 1; s > -1; s--) {
    arcSum[s] = 0;
    for (int d = 0; d < directions; d++) {
      arcSum[s] += reading[d][s];
    }
    Serial.print("Arc sum (");
    Serial.print(s);
    Serial.print(")= ");
    Serial.print(arcSum[s]);
    Serial.println("");
  }


  //Trying to find the starting point of the arrow
  //We use polar coordinates asuming our current position to be the origin
  int startR = 0;
  float startTheta = 0.0;

  for (int s = 0; s < steps; s++) {
    if (arcSum[s] != 0) {
      startR = s;
      break;
    }
  }

  Serial.print("Serial theta as an index--->");
  Serial.print(startTheta);
  Serial.println("");

  for (int d = 0; d < directions; d++) {
    startTheta += (reading[d][startR] * d);
  }

  Serial.print("Debug print-- startThetaSum= ");
  Serial.print(startTheta);
  Serial.println("");
  startTheta /= (float)arcSum[startR];

  startTheta -= (directions / 2);
  startTheta *= gap;

  Serial.println("The starting point of the arrow is: ");
  Serial.print("startR= ");
  Serial.print(startR);
  Serial.print("startTheta = ");
  Serial.print(startTheta);
  Serial.println("");

  //Going to the starting point of the arrow
  turnCW(startTheta);
  goFoward(startR * stepSize);


  //Trying to find the angle
  int totalReadingSum = 0;
  for (int s = 0; s < steps; s++) {
    totalReadingSum += arcSum[s];
  }


  float angleToTurn = 0;
  for (int d = 0; d < directions; d++) {
    for (int s = 0; s < steps; s++) {
      if (reading[d][s] != 0) {
        float theta = gap * (d - (directions / 2));
        float deltaY = startR * sin(startTheta) - s * sin(theta);
        float deltaX = s * cos(theta) - startR * cos(startTheta);
        float angle = atan(deltaY / deltaX) * (180.0 / 3.14);

        angleToTurn += angle * reading[d][s];
      }
    }
  }

  angleToTurn /= totalReadingSum;

  Serial.print("The angle to move forward: ");
  Serial.print(angleToTurn);
  Serial.print(" deg");
  Serial.println("");


  //Turning the angle and moving forward
  turnCW(angleToTurn);
  goFoward(100);



}


void start(int boxColor) {
  //This uses the colour reading as 1-RED,2-GREEN.3=BLUE

  int directions = 5;
  int gap = 15; //degrees
  int steps = 5;
  int stepSize = 40; //mm

  Serial.println("Starting the arrow finding algo");
  Serial.print(directions);
  Serial.print(" directions will be checked with ");
  Serial.print(gap);
  Serial.print(" deg betweeen two directions.");
  Serial.println("");
  Serial.print(steps);
  Serial.print(" steps of length ");
  Serial.print(stepSize);
  Serial.print("cm ");

  turnCW(-1 * gap * (directions - 1) / 2);
  int startR = 0;
  float startTheta = 0.0;
  boolean br = false;
  for (int d = 0; d < directions; d++) {
    for (int s = 0; s < steps; s++) {
      if (getColorReading() == boxColor) {
        startTheta = d;
        startR = s;
        br = true;
        break;
      }
      if (s != steps - 1) {
        goFoward(stepSize);
      }
    }
    if (br)break;

    goFoward(-stepSize * (steps - 1));
    turnCW(gap);


  }
  goFoward(10);
  trailAndErrorArrowFollow_Loop();


}







void trailAndErrorArrowFollow_Loop() {
  while (true) {
    trailAndErrorArrowFollow_LoopOneArrow();
  }
}

void trailAndErrorArrowFollow_LoopOneArrow() {
  Serial.begin(9600);
  Serial.println("Starting");
  /*
    31/08/2017
    We have to test this function by keeping the robot POINTED AT AN ARROW
    You should not keep the robot on an arrow
  */
  //BLOCK 1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  readSensorLine(reading);
  while (sumOfArray(reading, 6) == 0) {
    motorWrite(100, 100);
    delay(100);
    readSensorLine(reading);
  }



  readSensorLine(reading);
  while (sumOfArray(reading, 6) != 0) {
    trailAndErrorArrowFollow_Forward();
    readSensorLine(reading);
  }

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //BLOCK 2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  motorWrite(-100, -100);
  delay(100);
  readSensorLine(reading);
  while (sumOfArray(reading, 6) != 0) {

    motorWrite(-100, -100);
    delay(100);
    readSensorLine(reading);
  }


  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.

  //BLOCK 1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  readSensorLine(reading);
  while (sumOfArray(reading, 6) == 0) {
    motorWrite(100, 100);
    delay(100);
    readSensorLine(reading);
  }



  readSensorLine(reading);

  while (sumOfArray(reading, 6) != 0) {
    trailAndErrorArrowFollow_Forward();
    readSensorLine(reading);
  }

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}




void trailAndErrorArrowFollow_Forward() {
  /*
    (LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)
    Weights:  3   2   1   -1   -2    -3
              R[7]
              R[8]
  */

  Serial.print("Forward loop| weight= ");
  int weight[6] = { -3, -2, -1, 1, 2, 3};

  readSensorLine(reading);
  int weightedSum = 0;
  for (int j = 0; j < 6; j++) {
    weightedSum += reading[j] * weight[j];
  }

  Serial.println(weightedSum);

  //LOGIC -- 1 -- Basic
  if (weightedSum != 0) {
    if (weightedSum < 0) {
      Serial.println("Forward loop- Turn right");
      motorWrite(100, -100);
      delay(100);
    }
    else {
      Serial.println("Forward loop- Turn left");
      motorWrite(-100, 100);
      delay(100);
    }
  }


  motorWrite(100, 100);
  delay(100);
}


void trailAndErrorArrowFollow_Backward() {
  /*
    (LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)
    Weights:  3   2   1   -1   -2    -3
              R[7]
              R[8]
  */

  Serial.print("Backward loop| weight= ");
  int weight[6] = { -3, -2, -1, 1, 2, 3};

  readSensorLine(reading);
  int weightedSum = 0;
  for (int j = 0; j < 6; j++) {
    weightedSum += reading[j] * weight[j];
  }

  Serial.println(weightedSum);

  //LOGIC -- 1 -- Basic
  if (weightedSum != 0) {
    if (weightedSum > 0) {
      Serial.println("Backward loop- Turn right");
      motorWrite(50, -50);
      delay(100);
    }
    else {
      Serial.println("Backward loop- Turn left");
      motorWrite(-50, 50);
      delay(100);
    }
  }


  motorWrite(-50, -50);
  delay(100);
}






