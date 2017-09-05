
void testAndGetData(char rOrd, double spd, double steps) {
  Serial.print(rOrd == 'r' ? "Rotation " : "Distance ");
  Serial.print(spd);
  Serial.print(" ");
  Serial.println(steps);

  //stepper.begin(spd, MICROSTEPS);
  stepper.setRPM(spd);

  if (rOrd == 'r') {
    motorWrite(steps, 1, -1);
  } else if (rOrd == 'd') {
    motorWrite(steps, 1, 1);
  }
  //stepper.begin(200, MICROSTEPS);
    stepper.setRPM(200);
}



int giveTheIndexOf(int* arr, int value, int n) {
  for (int i = 0; i < n; i++) {
    if (arr[i] >= value) {
      return i;
    }
  }
  Serial.println("OPTION NOT IN THE ARRAY");
}



int stepsToRotate(int spd, double angle) {
  int steps = 0;
  int spdIndex = 0;
  spdIndex = giveTheIndexOf(speedOptions, spd, noOfSpeedOptions);
  int dir;
  if (angle < 0) {
    dir = -1; angle = -1 * angle;
  } else {
    dir = 1;
  }
  int angleIndex;
  for (int i = 0; i < noOfRotateOptions; i++) {
    if (pgm_read_word_near(&(angleRotated[spdIndex][i])) >= angle) {
      angleIndex = i;
      break;
    }
  }
  // LINEAR INTERPOLATION
  // y = Y_n-1 + (x - X_n-1)*tanz     tanz = (Y_n - Y_n-1)/(X_n - X_n-1)
  double tanz = (pgm_read_word_near(&(stepsGiven_Rotate[angleIndex])) - pgm_read_word_near(&(stepsGiven_Rotate[angleIndex - 1]))) / (double)(pgm_read_word_near(&(angleRotated[spdIndex][angleIndex])) - pgm_read_word_near(&(angleRotated[spdIndex][angleIndex - 1])));

  steps = pgm_read_word_near(&(stepsGiven_Rotate[angleIndex - 1])) + (angle - pgm_read_word_near(&(angleRotated[spdIndex][angleIndex - 1]))) * tanz;
  return dir * steps;
}





int stepsToForward(int spd, float distance) {
  int steps = 0;
  int spdIndex = 0;
  spdIndex = giveTheIndexOf(speedOptions, spd, noOfSpeedOptions);

  int distanceIndex;
  for (int i = 0; i < noOfDistanceOptions; i++) {
    if (pgm_read_word_near(&(distanceWentFoarward[spdIndex][i])) >= distance) {
      distanceIndex = i;
      break;
    }
  }

  // LINEAR INTERPOLATION
  // y = Y_n-1 + (x - X_n-1)*tanz     tanz = (Y_n - Y_n-1)/(X_n - X_n-1)
  float tanz = (pgm_read_word_near(&(stepsGiven_Distance[distanceIndex])) - pgm_read_word_near(&(stepsGiven_Distance[distanceIndex - 1]))) / (double)(pgm_read_word_near(&(distanceWentFoarward[spdIndex][distanceIndex])) - pgm_read_word_near(&(distanceWentFoarward[spdIndex][distanceIndex - 1])));

  steps = pgm_read_word_near(&(stepsGiven_Distance[distanceIndex - 1])) + (distance - pgm_read_word_near(&(distanceWentFoarward[spdIndex][distanceIndex - 1]))) * tanz;
  return steps;
}
