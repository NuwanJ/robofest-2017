/****************************************************************************
  Functions

  void    irSensorsBegin, sonarBegin, irSensorsOutput
  array   readLine(*sensorValues)
  String  readLineString
  int     getSonarDistance
****************************************************************************/

void irSensorsBegin() {

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(irPins[i], INPUT);
  }
  Serial.println(F(">> IRSensors : Begin..."));

}

void colorBegin() {

  if (color0.begin()) {
    // No error, can run program without problem
  } else {
    Serial.println(F(">> ColorSensor : Not Found"));
    beep(3);
  }
}

void sonarBegin() {

  /*Serial.println(">> Sonar : Begin");

    pinMode(PIN_TRIGGER, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    digitalWrite(PIN_TRIGGER, LOW);*/
}

void wallSensorBegin() {
  pinMode(PIN_LEFT_WALL_SENSOR, INPUT);
  pinMode(PIN_FRONT_WALL_SENSOR, INPUT);
  pinMode(PIN_RIGHT_WALL_SENSOR, INPUT);
}

void readWalls(int *wall) {

  wall[RIGHT_SENSOR] = digitalRead(PIN_RIGHT_WALL_SENSOR);
  wall[FRONT_SENSOR] = digitalRead(PIN_FRONT_WALL_SENSOR);
  wall[LEFT_SENSOR] = digitalRead(PIN_LEFT_WALL_SENSOR);

  mySerial.print("d");
  mySerial.print(wall[LEFT_SENSOR] + 2 * wall[FRONT_SENSOR] + 4 * wall[RIGHT_SENSOR]);
  /*
    if (mySerial.available() > 0) {
      while (mySerial.available()) {
        Serial.print((char)mySerial.read());
      }
    }
  */
}



int readSensorLine(unsigned int *sensor_values) {
  delay(10);
  
  weight = 0;
  sum = 0;
  allIn = false;
  allOut = false;
  irLineString = "";

  for (int i = 0; i < NUM_SENSORS; i++) {
    value = irSensorRead(i);

    sensor_values[i] = value;
    weight += value * (i * 10);
    sum += value;
    irLineString = (String)value + " " + irLineString;
  }

  if (sum == NUM_SENSORS) allIn = true;
  if (sum == 0) allOut = true;

  if (allOut)
  {
    if ((lastReading > RIGHT_EDGE_READING) && (CENTER_EDGE_READING - 10 > lastReading )) {        // <---***>
      lastReading = RIGHT_EDGE_READING;

    } else if ((LEFT_EDGE_READING > lastReading) && ( lastReading  > CENTER_EDGE_READING) + 10) { // <***--->
      lastReading = LEFT_EDGE_READING;

    } else if (lastReading == CENTER_EDGE_READING) {                                       // <--**-->
      lastReading = CENTER_EDGE_READING;
    }
  } else {
    lastReading = weight / sum;
  }


  //if (0)Serial.print(">> IR : "); Serial.println(irLineString);

  return lastReading;
}



void readColor() {

  delay(10);
  color0.getRawData(&raw_red, &raw_green, &raw_blue, &raw_clr);

  if (raw_green > raw_blue && raw_green > raw_red ) {
    floorColor = COLOR_GREEN;               // GREEN
  }

  else if (raw_blue > raw_red ) {
    floorColor = COLOR_BLUE;                // BLUE
  }
  else if (((raw_green - raw_blue) < RED_GB_GAP) || ((raw_blue - raw_green) < RED_GB_GAP) ) {
    floorColor = COLOR_RED;                 // RED
  }
  else {
    floorColor = COLOR_OPEN;                // NO COLOR
  }

  if (floorColor == 1)Serial.println("R");
  else if (floorColor == 2)Serial.println("G");
  else if (floorColor == 3)Serial.println("B");
  else Serial.println("None");

  if (0) {
    Serial.print(raw_blue);
    Serial.print(" ");
    Serial.print(raw_red);
    Serial.print(" ");
    Serial.print(raw_green);
    Serial.print(" ");
    Serial.print(raw_clr);
    Serial.print(" ");
    //Serial.print(color0.calculateColorTemperature(raw_red, raw_green, raw_blue) );
    //Serial.print(" ");

    Serial.print(50 * (floorColor - 2));
    Serial.println(" ");
  }

}

int irSensorRead(int num) {
  int reading = analogRead(irPins[num]);

  reading = (reading > 512);
  if (lineType == WHITE) reading = 1 - reading;

  //reading = reading; //BLACK=0, WHITE=1
  return reading;
}



int getSonarDistance() {

  /*digitalWrite(PIN_TRIGGER, HIGH);
    delayMicroseconds(20);
    digitalWrite(PIN_TRIGGER, LOW);

    duration = pulseIn(PIN_ECHO, HIGH, 30000);
    distance = duration / 58;

    if (distance > maxDistance) {
    //distance = maxDistance;
    }
    return distance;*/
}

