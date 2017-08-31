//String inputString = "";        // a string to hold incoming data
//String cmd2 = "";
//boolean stringComplete = false;  // whether the string is complete


void serialEvent() {

  while (Serial.available()) {
    digitalWrite(13, HIGH);

    int r = Serial.read();
    char inChar = (char)r;

    if (inChar == 'a') {
      // Encode details as binary >> {2}{1}{0}
      Serial.print(wall[0] + 2 * wall[1] + 4 * wall[2]);
    }
    else if (inChar == 'g') {
      pickBox();
    }
    else if (inChar == 'h') {
      dropBox();
    }
    else if (inChar == 'i') {
      Serial.println((char)(colorR0 > 0));
    }
    else if (inChar == 'j') {
      Serial.println((char)('0' + colorR0));
    }
    else if (inChar == '\n') {} // Nothing to do
    else if (inChar == '\r') {} // Nothing to do
    else {
      //This is to to say there is something wrong

      Serial.write((int)inChar);
      Serial.println();
      indicatorBlink(PIN_BLUE, 3);

    }

    //Serial.println(inChar);
    digitalWrite(13, LOW);
  }

}




