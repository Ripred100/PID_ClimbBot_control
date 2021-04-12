//Extension of MSE 2202 Western Engineering base code
//MSE 2202 Western Engineering base code: 2020 05 13 E J Porter
//Additions and adaptations done by Anuar Saenger Gomez


/*
  esp32                                           MSE-DuinoV2
  pins         description                        Brd Jumpers /Labels                                                                  User (Fill in chart with user PIN usage) 
  1             3v3                               PWR 3V3                                                                              3V3
  2             gnd                               GND                                                                                  GND
  3             GPIO15/AD2_3/T3/SD_CMD/           D15 (has connections in both 5V and 3V areas)                    
  4             GPIO2/AD2_2/T2/SD_D0              D2(has connections in both 5V and 3V areas)  /INDICATORLED ( On ESP32 board )        Heartbeat LED
  5             GPIO4/AD2_0/T0/SD_D1              D4(has connections in both 5V and 3V areas)                                          Left Motor, Channel A
  6             GPIO16/RX2                        Slide Switch S1b                                                                     IR Receiver
  7             GPIO17/TX2                        Slide Switch S2b                                                                     Left Encoder, Channel A
  8             GPIO5                             D5 (has connections in both 5V and 3V areas)                                         Left Encoder, Channel B
  9             GPIO18                            D18 (has connections in both 5V and 3V areas)                                        Left Motor, Channel B
  10            GPIO19/CTS0                       D19 (has connections in both 5V and 3V areas)                                        Right Motor, Channel A
  11            GPIO21                            D21/I2C_DA  
  12            GPIO3/RX0                         RX0
  13            GPIO1//TX0                        TX0
  14            GPIO22/RTS1                       D22/I2C_CLK
  15            GPIO23                            D23 (has connections in both 5V and 3V areas)  
  16            EN                                JP4 (Labeled - RST) for reseting ESP32
  17            GPI36/VP/AD1_0                    AD0                   
  18            GPI39/VN/AD1_3/                   AD3
  19            GPI34/AD1_6/                      AD6
  20            GPI35/AD1_7                       Potentiometer R2 / AD7
  21            GPIO32/AD1_4/T9                   Potentiometer R1 / AD4                                                               Pot 1 (R1)
  22            GPIO33/AD1_5/T8                   IMon/D33  monitor board current
  23            GPIO25/AD2_8/DAC1                 SK6812 Smart LEDs / D25                                                              Smart LEDs
  24            GPIO26/A2_9/DAC2                  Push Button PB2                                                                      Limit switch
  25            GPIO27/AD2_7/T7                   Push Button PB1                                                                      PB1
  26            GPOP14/AD2_6/T6/SD_CLK            Slide Switch S2a                                                                     Right Encoder, Channel A
  27            GPIO12/AD2_5/T5/SD_D2/            D12(has connections in both 5V and 3V areas)                                         Right Motor, Channel B
  28            GPIO13/AD2_4/T4/SD_D3/            Slide Switch S1a                                                                     Right Encoder, Channel B
  29            GND                               GND                                                                                  GND
  30            VIN                               PWR 5V t 7V                                                                          PWR 5V to 7V
*/





//Pin assignments
const int ciHeartbeatLED = 2;
const int ciPB1 = 27;     
const int ciPB2 = 26;      
const int ciPot1 = A4;    //GPIO 32  - when JP2 has jumper installed Analog pin AD4 is connected to Poteniometer R1
const int ciPot2 = A7;
const int ciIRDetector = 16; //free pin
const int ciMotorLeftA = 4;
const int ciMotorLeftB = 18;
const int ciMotorRightA = 19;
const int ciMotorRightB = 12;
const int ciEncoderLeftA = 17;
const int ciEncoderLeftB = 5;
const int ciEncoderRightA = 14;
const int ciEncoderRightB = 13;
const int ciSmartLED = 25;
const int ciStepperMotorDir = 22;
const int ciStepperMotorStep = 21;
const int ciServoTop = 15;
const int ciServoBottom = 2;
const int ciClimbA = 23;//
const int ciClimbB = 26;//
const int ciLimitSwitchLeft = 35;
const int ciLimitSwitchRight = 34;
const int ciClimbLimitSwitch = 36; //sensor pin



// SERVO FILE 
int topPos = 0;    // variable to store the servo position
int bottomPos = 180; 
int servoTop = 15; // Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 






boolean ServoLimit = false;
// SERVO FILE

// CLIMB FILE
# define maxRev 4 //change value to correct one once tested
int motorDirection = 0;
int revolutionCount = 0;
volatile int ClimbTickCount = 0;
volatile int ClimbRevolutionCount=0 ;
int lastSwitchState =0;


// CLIMB FILE


//Drive Constants
const uint8_t ci8RightTurn = 27;
const uint8_t ci8LeftTurn = 26;
const uint16_t cui16StartingSpeed = 35000;
const uint16_t cui16TurningSpeed = 40000;

//Drive Variables
int iLeftWorkingSpeed = cui16StartingSpeed;
int iRightWorkingSpeed = cui16StartingSpeed;

double dForwardSpeed;
double dReverseSpeed;
double dLeftSpeed;
double dRightSpeed;

uint16_t CR1_ui16WheelSpeed;
uint16_t CR1_ui16LeftWheelSpeed;
uint16_t CR1_ui16RightWheelSpeed;



//PID Variables (In Motion)
int CorrectionFactor = 0;

int ProportionalFactor;
int IntegralFactor;
int DerivativeFactor;
//--------------------------------------------------------------- IMPORTANT----------------- //These are the PID control Constants. Look at MOT_UpdateSpeed() for use
// Good PID explination: https://www.youtube.com/watch?v=fusr9eTceEo
int ProportionalCoeff = 1000;
int IntegralCoeff = 15;
int DerivativeCoeff = 40; 
//---------------------------------------------------------------------------------
//Drive Flags
volatile boolean btMotorTimerPriorityFlag = false; //does distance (false) or MotorRunTime (true) take priority for driving?

//Encoder Variables
 volatile int32_t ENC_vi32LeftOdometer;
 volatile int32_t ENC_vi32RightOdometer;

 volatile int32_t ENC_vi32LeftOdometerCompare;
 volatile int32_t ENC_vi32RightOdometerCompare;

 int32_t MOT_i32EncoderErrorChange;
 int32_t MOT_i32EncoderError = 0;
 int32_t MOT_i32OldEncoderError = 0;

//Encoder Flags
 volatile boolean ENC_btLeftMotorRunningFlag;
 volatile boolean ENC_btRightMotorRunningFlag;

//Main Loop variables
unsigned char CR1_ucMainTimerCaseCore1;
uint8_t CR1_ui8LimitSwitch;

unsigned long CR1_ulLastDebounceTime;
unsigned long CR1_ulLastByteTime;

unsigned long CR1_ulMainTimerPrevious;
unsigned long CR1_ulMainTimerNow;

unsigned long CR1_ulFlagTimerPrevious;
unsigned long CR1_ulFlagTimerNow;
unsigned char ucFlagStateIndex = 0;

volatile unsigned long CR1_ulMotorTimerPrevious;
unsigned long CR1_ulMotorTimerNow;
unsigned char ucNextMotorStateIndex = 1;
unsigned char ucMotorStateIndex = 0;
unsigned char ucMotorState = 0;

unsigned long CR1_ulHeartbeatTimerPrevious;
unsigned long CR1_ulHeartbeatTimerNow;

boolean btToggle = true;

int iButtonState;
int iLastButtonState = HIGH;

int iLastButtonState2 = HIGH;
int iButtonState2;

//Main loop Control flags
boolean btHeartbeat = true;
boolean btRun = false;


//Main Loop Timer utils.
const int CR1_ciMainTimer =  1000;
const int CR1_ciHeartbeatInterval = 500;
const int CR1_ciMotorRunTime = 2000;
const long CR1_clDebounceDelay = 50;
const long CR1_clReadTimeout = 220;

//Event Controller Variables
unsigned int EC_uiCurrentEvent;

//Event Controller Flags

//InputControl Flags
volatile boolean calibrating = false;




#include <ESP32Servo.h>
#include <esp_task_wdt.h>
Servo topServo;  // create servo object to control a servo
Servo bottomServo; // 16 servo objects can be created on the ESP32



#include <Adafruit_NeoPixel.h>
#include <Math.h>
#include "Servo.h"
#include "Climb.h"
#include "Encoder.h"
#include "Motion.h"
#include "InputControl.h"
#include "EventController.h"





 Adafruit_NeoPixel SmartLEDs(2, 25, NEO_GRB + NEO_KHZ400);
