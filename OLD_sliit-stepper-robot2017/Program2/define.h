
#define DEBUG 0

enum {RIGHT_SENSOR,FRONT_SENSOR, LEFT_SENSOR};

#define FRONT_SENSOR_PIN A1
#define RIGHT_SENSOR_PIN A0
#define LEFT_SENSOR_PIN A2

#define PIN_COLOR_SENSOR_0 4
#define PIN_COLOR_SENSOR_1 5

#define PIN_SERVO_COLLECT 6
#define PIN_SERVO_LIFT 7

#define PIN_8 8
#define PIN_BUZZER 9
#define PIN_10 10

#define PIN_RED 11
#define PIN_GREEN 12
#define PIN_BLUE 13

int wall[] = {1, 1, 1};









/*
  // ---- For Sonar Sensors --------------------------------------------------------------
  int duration, distance = 0;
  const int trigger[] = {2, 4, 10};
  const int echo[] = {3, 5, 11};
  int dist[] = {0, 0, 0};
  const int trigDist[] = {15, 15, 15};
  const int maxDistance = 100;
*/



//
// Color Sensor Variables -----------------------------------------------------------------

uint16_t clr0, red0, green0, blue0;
enum {COLOR_OPEN, COLOR_RED, COLOR_GREEN, COLOR_BLUE};
int colorR0 = 0;

const int WHITE_THERSOLD = 1000; // **This depends with the distance from sensor to the object




#define DELAY_BUZZER 100
#define DELAY_INDICATOR 100



