/*
  This code runs after lifting the box
*/

//int RED = 1, GREEN = 2, BLUE = 3;

#include <math.h>    // (no semicolon)
//static int reading[6];


void start(int boxColor) {
  //This uses the colour reading as 1-RED,2-GREEN.3=BLUE

  const int directions = 5;
  const int gap = 15; //degrees
  const int steps = 5;
  const int stepSize = 40; //mm

  /*  Serial.println("Starting the arrow finding algo");
    Serial.print(directions);
    Serial.print(" directions will be checked with ");
    Serial.print(gap);
    Serial.print(" deg betweeen two directions.");
    Serial.println("");
    Serial.print(steps);
    Serial.print(" steps of length ");
    Serial.print(stepSize);
    Serial.print("cm ");
  */

  Serial.println("I am at the start point of three arrows");

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

    Serial.print("Going back ");
    motorWrite(stepSize * (steps - 1),-1,-1);//goFoward(-1 * stepSize * (steps - 1));
    Serial.println("Turning");
    turnCW(gap);


  }

  Serial.println("Found the first arrow starting point...");
  goFoward(10);
  firstArrowFollow();
  trailAndErrorArrowFollow_Loop(boxColor);


}



void firstArrowFollow() {
  Serial.println("Following the first arrow");
  readSensorLine(reading);
  boolean continuee=true;
  while (sumOfArray(reading, 6)!=0 ) {
    int weight[6] = { -3, -2, -1, 1, 2, 3};
    //Serial.println("Debug ###");
    readSensorLine(reading);


    //This part is to isolate the arrow:
    int leftZeroFrom = 2;
    int rightZeroFrom = 3;

    for (leftZeroFrom = 2; leftZeroFrom > -1; leftZeroFrom--) {
      if (reading[leftZeroFrom] == 0)break;
    }
    for (int i = leftZeroFrom; i > -1; i--) {
      weight[i] == 0;
    }


    for (rightZeroFrom = 3; rightZeroFrom < 6; rightZeroFrom++) {
      if (reading[leftZeroFrom] == 0)break;
    }
    for (int i = leftZeroFrom; i > -1; i--) {
      weight[i] == 0;
    }

    for (int i = rightZeroFrom; i < 6; i++) {
      weight[i] == 0;
    }
    //Isolation over
  
    int weightedSum = 0;
    for (int j = 0; j < 6; j++) {
      weightedSum += reading[j] * weight[j];
    }
    Serial.print("Weighted sum = ");
    Serial.println(weightedSum);

    if (weightedSum != 0) {
      if (weightedSum < 0) {
        //Serial.println("Forward loop- Turn right");
        motorWrite(100, -100);
        delay(100);
      }
      else {
        //Serial.println("Forward loop- Turn left");
        motorWrite(-100, 100);
        delay(100);
      }
    }
    else {
      Serial.println("*******************");
      //This is the tricky part,
      //Can this scenario ever come?

    }


    motorWrite(100, 100);
    delay(100);
    //Serial.println("^^^");
    readSensorLine(reading);
    //Serial.println("^^----^");

    if(sumOfArray(reading, 6)==0) Serial.println(":-)");
  }

  Serial.print("F");
}



void trailAndErrorArrowFollow_Loop(int boxColour) {
  int arrow = 2;
  while (true) {
//    Serial.print("Trying to find the tail of arrow -- ");
//    Serial.println(arrow);
    trailAndErrorArrowFollow_LoopOneArrow(boxColour);
//    Serial.print("Finished  arrow -- ");
//    Serial.println(arrow);
    arrow++;
  }
}

void trailAndErrorArrowFollow_LoopOneArrow(int boxColor) {
  Serial.begin(9600);
  Serial.println("Starting");
  /*
    31/08/2017
    We have to test this function by keeping the robot POINTED AT AN ARROW
    You should not keep the robot on an arrow
  */
  /*
    02/09/2018 --gihanchanaka@gmail.com
    This function has only 4 steps
    1. Go foward until u find something
    2. Try to aligh to the arrow while going forward
    3. Come back until you loose the arrow
    4. Go forward until u find the arrow
    5. Try to aligh to the arrow while going forward
  */

  readSensorLine(reading);
  while (sumOfArray(reading, 6) == 0) {
    motorWrite(100, 100);
    delay(100);
    readSensorLine(reading);
  }

  if (getColorReading() == boxColor) {
    Serial.println("Found the tail of arrow");
    readSensorLine(reading);
    while (sumOfArray(reading, 6) != 0) {
      trailAndErrorArrowFollow_Forward();
      readSensorLine(reading);
    }

    motorWrite(-100, -100);
    delay(100);
    readSensorLine(reading);
    while (sumOfArray(reading, 6) != 0) {
      motorWrite(-100, -100);
      delay(100);
      readSensorLine(reading);
    }

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
  }
  else { //If this is not the box color
    //Go a few centemetes forward
    motorWrite(200, 200);
  }




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






