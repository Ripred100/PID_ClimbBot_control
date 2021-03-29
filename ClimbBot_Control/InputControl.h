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
       ENC_ClearLeftOdometer();
       ENC_ClearRightOdometer();
       btRun = !btRun;
        Serial.println(btRun);
       // if stopping, reset motor states and stop motors
       if(!btRun)
       {
          ENC_btLeftMotorRunningFlag = false;
          ENC_btRightMotorRunningFlag = false;
          ucNextMotorStateIndex = 1;
          ucMotorStateIndex = 0; 
          ucMotorState = 0;
          //move(0);  TO DO !!!!!
       }
      
     }
   }
 }
 iLastButtonState = iButtonValue;             // store button state

 }
