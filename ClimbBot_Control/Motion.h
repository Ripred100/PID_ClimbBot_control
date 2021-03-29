


void MOT_UpdateSpeed()
{

  
  
  MOT_i32EncoderError = ENC_vi32LeftOdometer - ENC_vi32RightOdometer;
  EncoderErrorChange = EncoderError - OldEncoderError;

  ProportionalFactor = EncoderError * ProportionalCoeff;
  IntegralFactor += EncoderError * IntegralCoeff;
  DerivativeFactor = EncoderErrorChange * DerivativeCoeff; 

  CorrectionFactor = ProportionalFactor + IntegralFactor + DerivativeFactor;


  MOT_WriteToMotors();

  
  
}




void MOT_Init()
{
  
  dForwardSpeed = 49152;  // max 65536, 65536*0.75 = 49152
  dReverseSpeed = 49152;
  dLeftSpeed = 39321;
  dRightSpeed = 39321;
  
  //setup PWM for motors
  ledcAttachPin(ciMotorLeftA, 7); // assign Motors pins to channels
  ledcAttachPin(ciMotorLeftB, 6);
  ledcAttachPin(ciMotorRightA, 5);
  ledcAttachPin(ciMotorRightB, 4);

  // Initialize channels 
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(7, 20000, 16); // 20mS PWM, 8-bit resolution
  ledcSetup(6, 20000, 16);
  ledcSetup(5, 20000, 16);
  ledcSetup(4, 20000, 16);
  
}

void MOT_SetDriveDirection()
{
  
}


void MOT_WriteToMotors()
{
          //Forward
          ledcWrite(6,0); //LeftBackward
          ledcWrite(7,ui16LeftWorkingSpeed - CorrectionFactor); //Left Forward
          ledcWrite(4,0); //Right Backward
          ledcWrite(5,ui16RightWorkingSpeed); //Right Forward
  
}
