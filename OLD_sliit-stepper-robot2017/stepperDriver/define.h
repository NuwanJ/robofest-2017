
boolean debug = 0;

#define NUM_SENSORS 6

#define BLACK 0
#define WHITE 1

#define LEFT 4
#define RIGHT 6

#define rightMotor1 7
#define rightMotor2 8
#define rightMotorPWM 9

#define leftMotor1 12
#define leftMotor2 11
#define leftMotorPWM 10

#define BUTTON_1 4
#define BUTTON_2 5
#define BUTTON_3 6 // Not working. Need to check

int buttonStatus = 1;

// Mode eNum
enum {BEGIN, LINE_FOLLOW, STOP, TEST, MAZE_RUN, MAZE_RUN_ADVANCED, PICKING_BOX, BLUETOOTH};

// EEPROM eNum
enum {eP, eI, eD, eMax, eBase, eDebug};


//----------------------------------------------------------------------------------------------
// IR Sensors Array - LineFollowing variables

#define RIGHT_EDGE_READING 0
#define LEFT_EDGE_READING (NUM_SENSORS - 1) * 10
#define CENTER_EDGE_READING (NUM_SENSORS - 1) * 5

unsigned int sensor_values[NUM_SENSORS];
const unsigned int irPins[] = {14, 15, 16, 19, 20, 21};
const unsigned int midPin = 18;

boolean allOut = 0;
boolean allIn = 0;
boolean lineType = BLACK;

String irLineString = "000000";
int lastReading = CENTER_EDGE_READING;
int weight = 0, sum = 0, value = 0;

//----------------------------------------------------------------------------------------------
// Line Following variables

float kP = 0, kD = 0, kI = 0;

int pos = CENTER_EDGE_READING;
int error = 0;
int lastError = 0;


//----------------------------------------------------------------------------------------------
// Color Sensor variables

enum {COLOR_OPEN, COLOR_RED, COLOR_GREEN, COLOR_BLUE};
int color = 0;


//----------------------------------------------------------------------------------------------
// Motor Control variables

int leftSpd = 0, rightSpd = 0;
const double slowFactor = 1;
const double speedFactor = 1;

int maxSpeed = 200;
int baseSpeed = 150;

int drift = 0;




//------------------------------------------------------------------------
//These variables are defined for the maze traversal

enum {RIGHT_SENSOR, FRONT_SENSOR, LEFT_SENSOR};
int wall[] = {1, 1, 1};

int maze[6][6];
int isMazeSolved = 0;
int mazeCounter = 0;
int posX = 0, posY = 0;
int dir[4][2] = { {0, -1}, {0, 1}, {1, 0}, { -1, 0}};

int maze_THERSOLD_FOR_WALL = 10; //in cm

int maze_forwardStepTime = 1;
int maze_forwardStepSpeed = 180;

int maze_turnLeft_RightMotorSpeed;
int maze_turnLeft_LeftMotorSpeed = -1 * maze_turnLeft_RightMotorSpeed;
int maze_turnLeft_Time;

int maze_turnRight_LeftMotorSpeed;
int maze_turnRight_RightMotorSpeed = -1 * maze_turnRight_LeftMotorSpeed;
int maze_turnRight_Time;

int maze_turnBack_LeftMotorSpeed;
int maze_turnBack_RightMotorSpeed = -1 * maze_turnBack_LeftMotorSpeed;
int maze_turnBack_Time;
//-------------------------------------------------------------------------


