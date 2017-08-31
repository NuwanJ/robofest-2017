

void pick() {
  mySerial.print("g");
}

void drop() {
  mySerial.print("h");
}

boolean readColor() {

  mySerial.println("i");

  while (mySerial.available()) {
    color = mySerial.read() - '0';     // 0-No 1-Red 2-Green 3-Blue
    if (color >= 0 && color <= 3) {
      //correct
      
    } else {
      color = -1;
      Serial.println("Error: Color reading");
    }
  }
  return 1;

}

int readWalls() {
  mySerial.println('a');

  while (mySerial.available()) {
    byte val = mySerial.read() - '0';

    if (val >= 0 && val <= 7) {
      wall[0] = bitRead(val, 0);
      wall[1] = bitRead(val, 1);
      wall[2] = bitRead(val, 2);
    }
  }
  return 1;
}




