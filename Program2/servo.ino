

#define PICK_ON 160
#define PICK_OFF 40

#define GRAB_UP 30
#define GRAB_DOWN 100   /// 90 Nuwan

void pickBox() {

  attachServos();
  pick.write(PICK_ON);
  delay(1000);
  grab.write(GRAB_UP);
  delay(500);
  detachServos();
  //Serial.println(">> Pick : Complete");

}

void  readyToPick() {
  attachServos();
  pick.write(PICK_OFF);
  delay(1000);
  grab.write(GRAB_DOWN);
  delay(1000);
  detachServos();
  //Serial.println(">> readyToPick : Complete");
}

void dropBox() {
  attachServos();
  grab.write(GRAB_DOWN);
  delay(1000);
  pick.write(PICK_OFF);
  delay(500);
  detachServos();
  //Serial.println(">> Drop : Complete");
}

void stand() {
  attachServos();
  grab.write(30);
  delay(500);
  pick.write(PICK_ON);
  delay(1000);
  detachServos();
  //Serial.println(">> stand : Complete");
}

void attachServos() {
  pick.attach(PIN_PICK_COLLECT);
  grab.attach(PIN_SERVO_LIFT);
}

void detachServos() {
  pick.detach();
  grab.detach();
}


