
unsigned int _DriveIndex = 0;
unsigned int _ClimbGo = 0;




unsigned int EC_GetCurrentEventID()
{
  return EC_uiCurrentEvent;
}


boolean EC_IsEventInProgress()
{
  if(EC_GetCurrentEventID() == 0)
  {
    return ENC_ISMotorRunning();
  }
  if(EC_GetCurrentEventID() == 1)
  {
    return !ServoLimit;
  }
  
}


void EC_DriveEventHandler()
{
  Serial.println("Drive event");
  
  CR1_ulMotorTimerNow = millis();
  if(EC_IsEventInProgress())
  {
    //MOT_UpdateSpeed(); offloading the PID to the calibration func. in the main loop because i still need to make PID compatible with turns.
    MOT_WriteToMotors();
    
    
  }
  else if (CR1_ulMotorTimerNow - CR1_ulMotorTimerPrevious >= CR1_ciMotorRunTime && !(EC_IsEventInProgress()))
  {
    CR1_ulMotorTimerPrevious = CR1_ulMotorTimerNow;

    switch(_DriveIndex)
    {
      case 0:
      {
        MOT_SetDriveDirection(0); // forward
        ENC_SetDistance(200,200);
        ENC_ClearOdometers();
        
        _DriveIndex = 1;
      break;
      }
      case 1:
      {
        MOT_SetDriveDirection(3); // left
        ENC_ClearOdometers();
        ENC_SetDistance(-200,200);  

        _DriveIndex = 2;
      break;
      }
      case 2:
      {
        MOT_SetDriveDirection(0); // forward
        ENC_SetDistance(200,200);
        ENC_ClearOdometers();
        
        _DriveIndex = 3;
      break;
      }
      case 3:
      {
        MOT_SetDriveDirection(1); // backward
        ENC_ClearOdometers();
        ENC_SetDistance(-200,-200);
        _DriveIndex = 4;
  
      break;
      }
      case 4:
      {
        MOT_SetDriveDirection(2); // right
        ENC_ClearOdometers();
        ENC_SetDistance(200,-200); 
        
        _DriveIndex = 5;
        break;
      }
      case 5:
      {
        MOT_SetDriveDirection(1); // backward
        ENC_ClearOdometers();
        ENC_SetDistance(-200,-200);
        _DriveIndex = 6;
        break;
      }
      default:
      {
        EC_uiCurrentEvent = 1;
        break;
      }
      
      

    }

  }
  
}

void EC_ServoEventHandler(){

        Serial.println("servo event");

  int LeftState = digitalRead(ciLimitSwitchLeft);
  int RightState = digitalRead(ciLimitSwitchRight);
  
  if(LeftState == LOW && RightState == HIGH) {
    // left motor stops, right keeps going
  } else if (LeftState == HIGH && RightState == LOW) {
    // right motor stops, left keeps going
  } else if (LeftState == LOW && RightState == LOW){
      
//        topPos += 1;
//        bottomPos -= 1;
//        topServo.write(topPos);
//        bottomServo.write(bottomPos);

      while(topPos <= 180 && bottomPos >= 0){
        topPos += 1;
        bottomPos -= 1;
        topServo.write(topPos);
        bottomServo.write(bottomPos);
        delay(10);
        Serial.println("servo actuating");
     }
             ServoLimit = true;
        EC_uiCurrentEvent = 2;
  }
//       if(topPos >= 180 && bottomPos <= 0)
//     {
//                ServoLimit = true;
//        EC_uiCurrentEvent = 2;
//     }
}

void EC_ClimbEventHandler()
{
  
      if(_ClimbGo == 0)
  {
    Serial.println("climb event");
          ledcWrite(2,0);
          ledcWrite(3,255);// attachinterrupt to the limit switch to stop it after whatever rev

          _ClimbGo = 1;
           
           //attachInterrupt(ciClimbLimitSwitch, ClimbUpdate, FALLING);
  }
}




void EC_MainEventHandler()
{

  switch(EC_uiCurrentEvent)
  {
    case 0: // Driving
    {
      EC_DriveEventHandler();
      break;
    }
    case 1: // Servo actuating
    {
      EC_ServoEventHandler();
      break;
    }
    case 2: // Climbing
    {
      EC_ClimbEventHandler();
      break;
    }

  }
  
}


void EC_Init()
{
  EC_uiCurrentEvent = 0;
}
