

void eepromBegin() {

  kP = (float)EEPROM.read(eP) / 10;
  kI = (float)EEPROM.read(eI) / 10;
  kD = (float)EEPROM.read(eD) / 10;

  baseSpeed = (int)EEPROM.read(eBase);
  maxSpeed = (int)EEPROM.read(eMax);
  debug =  (int)EEPROM.read(eDebug);

}

