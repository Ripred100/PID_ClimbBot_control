


void setupMotion ()
{
  
  dManualSpeed = 0;
  dForwardSpeed = 250;  // max 255; min ~150 before motor stall
  dReverseSpeed = 250;
  dLeftSpeed = 170;
  dRightSpeed = 170;
  
  //setup PWM for motors
  ledcAttachPin(ciMotorLeftA, 7); // assign Motors pins to channels
  ledcAttachPin(ciMotorLeftB, 6);
  ledcAttachPin(ciMotorRightA, 5);
  ledcAttachPin(ciMotorRightB, 4);

  // Initialize channels 
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(7, 20000, 8); // 20mS PWM, 8-bit resolution
  ledcSetup(6, 20000, 8);
  ledcSetup(5, 20000, 8);
  ledcSetup(4, 20000, 8);
  
   ucMotion_Direction = 0;
   ucMotion_Speed = 0;
}
