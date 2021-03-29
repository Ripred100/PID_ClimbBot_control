

unsigned int EC_GetCurrentEvent()
{
  return EC_uiCurrentEvent;
}


boolean EC_IsEventInProgress()
{
  if(EC_GetCurrentEvent() == 0)
  {
    return ENC_ISMotorRunning();
  }
  
}


void EC_DriveEventHandler()
{
  
  CR1_ulMotorTimerNow = millis();
  if(CR1_ulMotorTimerNow - CR1_ulMotorTimerPrevious >= CR1_ciMotorRunTime && !(EC_IsEventInProgress()))
  {
    CR1_ulMotorTimerPrevious = CR1_ulMotorTimerNow;

    
    
  }
  
}


void EC_MainEventHandler()
{

  switch(EC_GetCurrentEvent())
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
