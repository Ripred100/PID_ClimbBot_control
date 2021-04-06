

void CLM_Init(){
    // set the pin modes and initial rotation direction of motor

  pinMode(ciClimbLimitSwitch, INPUT_PULLUP);

  ledcAttachPin(ciClimbA, 2);
  ledcAttachPin(ciClimbB, 3);

  ledcSetup(2, 20000, 8); // 20mS PWM, 8-bit resolution
  ledcSetup(3, 20000, 8);
  
}


void IRAM_ATTR ClimbUpdate() {
    ClimbTickCount++;

    if(ClimbTickCount == 6){
    ClimbRevolutionCount ++;
    ClimbTickCount = 0;
  }
  //third if statement if revCounter = maxRev stop motor, and then change direction of rotation to degin the descent of robot
  if(ClimbRevolutionCount == maxRev){

    //stop motor
          ledcWrite(3,0);
          ledcWrite(2,0);

  delay(200);
   //go down
          ledcWrite(2,100);
          ledcWrite(3,0);
  delay(500);

  ledcWrite(2,0);
  ledcWrite(3,0);
          
}
}
