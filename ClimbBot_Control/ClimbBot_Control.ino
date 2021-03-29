//Extension of MSE 2202 Western Engineering base code
//MSE 2202 Western Engineering base code: 2020 05 13 E J Porter
//Additions and adaptations done by Anuar Saenger Gomez 2021, 03 29


#include "Definitions.h"


void setup() {

  
  Serial.begin(115200); 
 


   //setupMotion();
   //setupStepper();
   ENC_Init();
   pinMode(ciHeartbeatLED, OUTPUT);
   pinMode(ciPB1, INPUT_PULLUP);
   pinMode(ciLimitSwitch, INPUT_PULLUP);

   SmartLEDs.begin();                          // Initialize Smart LEDs object (required)
   SmartLEDs.clear();                          // Set all pixel colours to off
   SmartLEDs.show();                           // Send the updated pixel colours to the hardware

}

void loop() {
  // put your main code here, to run repeatedly:
  IC_CheckButtonUpdate();

  SmartLEDs.setPixelColor(0, 25, 0, ENC_vi32LeftOdometer%25);
  SmartLEDs.setPixelColor(1, 25, 0, ENC_vi32RightOdometer%25);
  Serial.println("Left : " + String(ENC_vi32LeftOdometer));
  Serial.println("Right : " + String(ENC_vi32RightOdometer));
  SmartLEDs.show();


  // Heartbeat LED
 CR1_ulHeartbeatTimerNow = millis();
 if(CR1_ulHeartbeatTimerNow - CR1_ulHeartbeatTimerPrevious >= CR1_ciHeartbeatInterval)
 {
    CR1_ulHeartbeatTimerPrevious = CR1_ulHeartbeatTimerNow;
    btHeartbeat = !btHeartbeat;
    digitalWrite(ciHeartbeatLED, btHeartbeat);
   // Serial.println((vui32test2 - vui32test1)* 3 );
 }

}
