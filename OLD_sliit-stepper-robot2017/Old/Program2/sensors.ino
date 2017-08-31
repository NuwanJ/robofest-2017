
void sharpIRBegin() {

  pinMode(FRONT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
  pinMode(LEFT_SENSOR_PIN, INPUT);

  Serial.println(">> ColorSensor : Begin");
}

void colorBegin() {

  if (color0.begin()) {
    Serial.println(">> ColorSensor : Begin");
  } else {
    Serial.println(">> ColorSensor : Not Found");
    //while (1); // halt!
  }
}


void readColor() {

  //color0.setInterrupt(false);  // turn on LED
  delay(60);
  color0.getRawData(&red0, &green0, &blue0, &clr0);
  //color0.setInterrupt(true);   // turn off LED

  if ((red0 > WHITE_THERSOLD) && (blue0 > WHITE_THERSOLD) && (green0 > WHITE_THERSOLD)) colorR0 = COLOR_OPEN;
  else if (red0 > green0 && red0 > blue0) colorR0 = COLOR_RED; //RED
  else if (green0 > blue0) colorR0 = COLOR_GREEN;              //GREEN
  else colorR0 = COLOR_BLUE;                                   //Blue

}

// ---- Sonar Sensor Functions -----------------------------------------------------------------------

void sonarBegin() {

  /*Serial.println(">> ColorSensor : Begin");
    for (int i = 0; i < 3; i++) {
    pinMode(trigger[i], OUTPUT);
    pinMode(echo[i], INPUT);
    digitalWrite(trigger[i], LOW);
    }*/
}

int getDistance(int sensor) {

  /*digitalWrite(trigger[sensor], HIGH);
    delayMicroseconds(20);
    digitalWrite(trigger[sensor], LOW);

    duration = pulseIn(echo[sensor], HIGH, 30000);
    distance = duration / 58;

    if (distance > maxDistance) {
    distance = maxDistance;
    }
    return distance;*/
}

boolean readWalls() {

  wall[RIGHT_SENSOR] = digitalRead(RIGHT_SENSOR_PIN);
  wall[FRONT_SENSOR] = digitalRead(FRONT_SENSOR_PIN);
  wall[LEFT_SENSOR] = digitalRead(LEFT_SENSOR_PIN);

}



