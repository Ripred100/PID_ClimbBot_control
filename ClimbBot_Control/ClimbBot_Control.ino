//Extension of MSE 2202 Western Engineering base code
//MSE 2202 Western Engineering base code: 2020 05 13 E J Porter
//Additions and adaptations done by Anuar Saenger Gomez 2021, 03 29


#include "Definitions.h"


void setup() {

  
  Serial.begin(9600); 
 


   MOT_Init();
   SERV_Init();
   ENC_Init();
   CLM_Init();
   EC_Init();

   pinMode(ciPB1, INPUT_PULLUP);
   //pinMode(ciPB2, INPUT_PULLUP);


   SmartLEDs.begin();                          // Initialize Smart LEDs object (required)
   SmartLEDs.clear();                          // Set all pixel colours to off
   SmartLEDs.show();                           // Send the updated pixel colours to the hardware



}

void loop() {
  // Code that runs outside of main switch case loop
  IC_CheckButtonUpdate();
  //IC_CheckButtonUpdate2();


  CR1_ulMainTimerNow = micros();
 if(CR1_ulMainTimerNow - CR1_ulMainTimerPrevious >= CR1_ciMainTimer)
 {
   
   CR1_ulMainTimerPrevious = CR1_ulMainTimerNow;
    
   switch(CR1_ucMainTimerCaseCore1)  //10 Cases, each taking 0.1ms aproximately. We can use this timing to calibrate PWM 
   {
    case 0: //Driving switch case
    {
      if(btRun)
      {
        Serial.println("main event handler");
        EC_MainEventHandler();
      }

    

      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 1:
    {
//      if(calibrating == 1)
//      {
//        Serial.println("Calibrating loop thing");
//        //MOT_UpdateSpeed();
//      }
//      if(!btRun && !calibrating)
//      {
//      ledcWrite(6,65535);
//      ledcWrite(7,65535);  //stop with braking Left motor 
//      ledcWrite(5,65535);
//      ledcWrite(4,65535);  //stop with braking Right motor 
//      }
      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 2:
    {

      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 3:
    {

      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 4:
    {

      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 5:
    {

      
    
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 6:
    {

      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 7:
    {

      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 8:
    {
      
        CR1_ucMainTimerCaseCore1 += 1;
      break;
    }
//----------------------------------------------------------------------------------
    case 9:
    {
      if(ENC_vi32LeftOdometer > 0)
    {
        SmartLEDs.setPixelColor(0, 0, 0, abs(ENC_vi32LeftOdometer)%50);
    }
    else
    {
      SmartLEDs.setPixelColor(0, abs(ENC_vi32LeftOdometer)%50, 0, 0);
    }
    

      if(ENC_vi32RightOdometer > 0)
    {
        SmartLEDs.setPixelColor(1, 0, 0, abs(ENC_vi32RightOdometer)%50);
    }
    else
    {
      SmartLEDs.setPixelColor(1, abs(ENC_vi32LeftOdometer)%50, 0, 0);
    }
    
    

        Serial.println("Left : " + String(ENC_vi32LeftOdometer));
        Serial.println("Right : " + String(ENC_vi32RightOdometer));
//        Serial.println("Correction : " + String(CorrectionFactor));
        SmartLEDs.show();

        CR1_ucMainTimerCaseCore1 = 0;
      break;
    }
//----------------------------------------------------------------------------------
   }




  // Heartbeat LED
// CR1_ulHeartbeatTimerNow = millis();
// if(CR1_ulHeartbeatTimerNow - CR1_ulHeartbeatTimerPrevious >= CR1_ciHeartbeatInterval)
// {
//    CR1_ulHeartbeatTimerPrevious = CR1_ulHeartbeatTimerNow;
//    btHeartbeat = !btHeartbeat;
//    digitalWrite(ciHeartbeatLED, btHeartbeat);
//   // Serial.println((vui32test2 - vui32test1)* 3 );
// }

}
}
