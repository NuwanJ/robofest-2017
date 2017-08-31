
void pickBox() {
  /*attachServos();
  pick.write(150);
  delay(1000);
  //s = 1;
  grab.write(20);//20
  delay(500);
  detachServos();*/
  Serial.println(">> Pick : Complete");
}

void dropBox() {
  /*attachServos();
  grab.write(120);
  delay(500);
  pick.write(10);
  delay(500);
  detachServos();
  // = 0;*/
  Serial.println(">> Drop : Complete");
}

void stand() {
  /*attachServos();
  grab.write(30);
  delay(500);
  pick.write(150);
  delay(1000);
  detachServos();*/
}

void attachServos() {
  /*pick.attach(4);
  grab.attach(3);*/
}

void detachServos() {
  /*pick.detach();
  grab.detach();*/
}


