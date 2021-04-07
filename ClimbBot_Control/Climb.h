

void CLM_Init(){
    // set the pin modes and initial rotation direction of motor

  pinMode(ciClimbLimitSwitch, INPUT_PULLUP);

  ledcAttachPin(ciClimbA, 2);
  ledcAttachPin(ciClimbB, 3);

  ledcSetup(2, 20000, 8); // 20mS PWM, 8-bit resolution
  ledcSetup(3, 20000, 8);
  
}
