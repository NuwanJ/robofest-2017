/*
  This code runs after lifting the box
*/

//int RED = 1, GREEN = 2, BLUE = 3;

//static int reading[6];






void start(int boxColor) {
  //04/09/2017 gihanchanaka@gmail.com
  //This uses the colour reading as 1-RED,2-GREEN.3=BLUE

	Serial.println(F("I am at the start point of three arrows"));
	firstArrowFollow(boxColor);
  Serial.println(F("Let us start finding other arrows"));
	
	trailAndErrorArrowFollow_Loop(boxColor);


}



void firstArrowFollow(int boxColor) {
  Serial.println("Trying to locate the tail of the first arrow> ");

//We are assuming that the 3 arrows are infront of the robot
  while(sumOfArray(reading,6)==0){
  	goFF();
  	readSensorLine(reading);

  } 

  boolean foundTheTailfOfFirstArrow=false;

  while(!foundTheTailfOfFirstArrow){
  	turnCW(-90);
  	for(int i=0;i<18;i++){
  		turnCW(10);
  		if(getColorReading()==boxColor){
  			foundTheTailfOfFirstArrow=true;
  			Serial.println(F("Found the tail of the first arrow! "));
  			break;
  		}
  	}
  	if(!foundTheTailfOfFirstArrow){
  	 	turnCW(-90);
  		goFF();
  	}
  }
  readSensorLine(reading);
  while (sumOfArray(reading, 6) == 0) {
    goFF();
    readSensorLine(reading);
  }

  readSensorLine(reading);
  while (sumOfArray(reading, 6) != 0) {
    int weight[6] = { -3, -2, -1, 1, 2, 3};

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
    for (int i = leftZeroFrom; i >-1; i--) {
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

    if (weightedSum != 0) {
      if (weightedSum < 0) {
        goR();
        Serial.println("R");
      }
      else {
        goL();
        Serial.println("L");
      }
    }
    else {
      goF();
      Serial.println("F");

    }

    goFF();
    readSensorLine(reading);
  }


  Serial.println(F("Finished the first arrow"));
}



void trailAndErrorArrowFollow_Loop(int boxColor) {
  int arrow=1;
  while (true) {
    Serial.print(F("Trying to find the tail of arrow -- "));
    Serial.println(arrow);
    trailAndErrorArrowFollow_LoopOneArrow(boxColor);
    Serial.print(F("Finished  arrow -- "));
    Serial.println(arrow);
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

  /*
    03/09/2017 gihanchanaka@gmail.com
    Changing the function to reject other colours
  */

  

  boolean foundColor=false;

//<<<<<<<<<The part of the function to find an arrow tail>>>>>>>>>  
  while(!foundColor){

    readSensorLine(reading);
    while (sumOfArray(reading, 6) == 0) {
      motorWrite(100, 100);
      delay(100);
      readSensorLine(reading);
    }




    if(getColorReading()==boxColor){
      foundColor=true;
    }
    else{

      int weightedSum;
      weightedSum=updatedWeightedSum();
      if (weightedSum!=0) {
        if (weightedSum < 0) {
          goLF();
          if(getColorReading()==boxColor)foundColor=true;
          else{
  //******
            weightedSum=updatedWeightedSum();
            if (weightedSum!=0) {
              if (weightedSum < 0) {
                goLF();
                if(getColorReading()==boxColor)foundColor=true;
                if(!foundColor)goBR();

              }
              else {
                goRF();
                if(getColorReading()==boxColor)foundColor=true;
                if(!foundColor)goBL();
              }

            }
  //*****         
          }
          if(!foundColor)goBR();

        }
        else {
          goRF();
          if(getColorReading()==boxColor)foundColor=true;
          else{
  //******
            weightedSum=updatedWeightedSum();
            if (weightedSum!=0) {
              if (weightedSum < 0) {
                goLF();
                if(getColorReading()==boxColor)foundColor=true;
                if(!foundColor)goBR();

              }
              else {
                goRF();
                if(getColorReading()==boxColor)foundColor=true;
                if(!foundColor)goBL();
              }

            }
  //*****     
          }
          if(!foundColor)goBL();
        }
      }
    }

    if(!foundColor){
      goF();
      goF();
    }


  }

  
//<<<<<<<<<The part of the function to go along the arrow>>>>>>>>>  

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
  
  motorWrite(200, 200);
}//end of function




void trailAndErrorArrowFollow_Forward() {
  /*
    (LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)
    Weights:  3   2   1   -1   -2    -3
              R[7]
              R[8]
  */

  //Serial.print("Forward loop| weight= ");
  int weight[6] = { -3, -2, -1, 1, 2, 3};

  readSensorLine(reading);
  int weightedSum = 0;
  for (int j = 0; j < 6; j++) {
    weightedSum += reading[j] * weight[j];
  }

  //Serial.println(weightedSum);

  //LOGIC -- 1 -- Basic
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

  //Serial.print("Backward loop| weight= ");
  int weight[6] = { -3, -2, -1, 1, 2, 3};

  readSensorLine(reading);
  int weightedSum = 0;
  for (int j = 0; j < 6; j++) {
    weightedSum += reading[j] * weight[j];
  }

  //Serial.println(weightedSum);

  //LOGIC -- 1 -- Basic
  if (weightedSum != 0) {
    if (weightedSum > 0) {
      //Serial.println("Backward loop- Turn right");
      motorWrite(50, -50);
      delay(100);
    }
    else {
      //Serial.println("Backward loop- Turn left");
      motorWrite(-50, 50);
      delay(100);
    }
  }


  motorWrite(-50, -50);
  delay(100);
}






