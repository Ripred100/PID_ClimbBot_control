
void IC_CheckButtonUpdate2(){
  int iButtonValue2 = digitalRead(ciPB2);
  if (iButtonValue2 != iLastButtonState2)
  {
    //Serial.println("Button 2 pressed");
    CR1_ulLastDebounceTime = millis();
  }

  if ((millis() - CR1_ulLastDebounceTime) > CR1_clDebounceDelay) {
    if(iButtonValue2 != iButtonState2){
      iButtonState2 = iButtonValue2;

      if(iButtonState2 == LOW){
        calibrating = true;
        
        MOT_SetDriveDirection(0);
        ENC_SetDistance(500,500);
      }
    }
  }

  iLastButtonState2 = iButtonValue2;
}



void IC_CheckButtonUpdate(){
 
 int iButtonValue = digitalRead(ciPB1);       // read value of push button 1
  if (iButtonValue != iLastButtonState) {      // if value has changed
     CR1_ulLastDebounceTime = millis();        // reset the debouncing timer
  }

  if ((millis() - CR1_ulLastDebounceTime) > CR1_clDebounceDelay) {
    if (iButtonValue != iButtonState) {        // if the button state has changed
    iButtonState = iButtonValue;               // update current button state

     // only toggle the run condition if the new button state is LOW
     if (iButtonState == LOW)
     {
       ENC_ClearENC_vi32LeftOdometer();
       ENC_ClearENC_vi32RightOdometer();
       btRun = !btRun;
        //Serial.println(btRun);
       // if stopping, reset motor states and stop motors
       if(!btRun)
       {
          ENC_btLeftMotorRunningFlag = false;
          ENC_btRightMotorRunningFlag = false;
          ucNextMotorStateIndex = 1;
          ucMotorStateIndex = 0; 
          ucMotorState = 0;

      ledcWrite(6,65535);
      ledcWrite(7,65535);  //stop with braking Left motor 
      ledcWrite(5,65535);
      ledcWrite(4,65535);  //stop with braking Right motor 
       }
      
     }
   }
 }
 iLastButtonState = iButtonValue;             // store button state

 }
