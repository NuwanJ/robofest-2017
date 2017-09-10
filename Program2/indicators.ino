

void indicatorBegin() {

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);

}


void buzzer(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(DELAY_BUZZER);
    digitalWrite(PIN_BUZZER, LOW);
    delay(DELAY_BUZZER);
  }
}

void indicatorChange(int colorId, bool st) {
  if (colorId == COLOR_RED) digitalWrite(PIN_RED, st);
  else if (colorId == COLOR_GREEN) digitalWrite(PIN_GREEN, st);
  else if (colorId == COLOR_BLUE) digitalWrite(PIN_BLUE, st);
}

void indicatorShow(int colorId) {


  digitalWrite(PIN_RED, (colorId == 1) ? HIGH : LOW);
  digitalWrite(PIN_GREEN, (colorId == 2) ? HIGH : LOW);
  digitalWrite(PIN_BLUE, (colorId == 3) ? HIGH : LOW);
}

void indicatorOn(int colorId) {
  if (colorId == COLOR_RED) digitalWrite(PIN_RED, HIGH);
  else if (colorId == COLOR_GREEN) digitalWrite(PIN_GREEN, HIGH);
  else if (colorId == COLOR_BLUE) digitalWrite(PIN_BLUE, HIGH);
}


void indicatorOff(int colorId) {
  if (colorId == COLOR_RED) digitalWrite(PIN_RED, LOW);
  else if (colorId == COLOR_GREEN) digitalWrite(PIN_GREEN, LOW);
  else if (colorId == COLOR_BLUE) digitalWrite(PIN_BLUE, LOW);
}

void indicatorBlink(int colorId, int count) {
  for (int i = 0; i < count; i++) {
    indicatorOn(colorId);
    delay(DELAY_INDICATOR);
    indicatorOff(colorId);
    delay(DELAY_INDICATOR);
  }

}

