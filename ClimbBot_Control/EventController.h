
unsigned int _DriveIndex = 0;




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
  
}


void EC_DriveEventHandler()
{
  
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
        MOT_SetDriveDirection(0);
        ENC_SetDistance(200,200);
        _DriveIndex = 1;
      break;
      }
      case 1:
      {
        MOT_SetDriveDirection(3);
        ENC_SetDistance(-200,200);  
        _DriveIndex = 2;
      break;
      }
      case 2:
      {
        MOT_SetDriveDirection(2);
        ENC_SetDistance(200,-200);
        _DriveIndex = 3;
      break;
      }
      case 3:
      {
        MOT_SetDriveDirection(1);
        ENC_SetDistance(-200,-200);
        _DriveIndex = 4;

        EC_uiCurrentEvent = 1;
      break;
      }
      
      

    }

  }
  
}

void EC_ServoEventHandler(){
  
}


void EC_MainEventHandler()
{

  switch(EC_GetCurrentEventID())
  {
    case 0: // Driving
    {
      EC_DriveEventHandler();
      break;
    }
    case 1: // Servo actuating
    {
      break;
    }
    case 2: // Climbing
    {
      break;
    }

  }
  
}


void EC_Init()
{
  EC_uiCurrentEvent = 0;
}
