


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
  ledcSetup(7, 20000, 16); // 20mS PWM, 16-bit resolution
  ledcSetup(6, 20000, 16);
  ledcSetup(5, 20000, 16);
  ledcSetup(4, 20000, 16);
  
}

void MOT_SetDriveDirection()
{
  
}

uint16_t MOT_GetAdjustedSpeed(int wheelID)
{

  
  if(wheelID == 0)//left wheel
  {
    return (ui16LeftWorkingSpeed + CorrectionFactor);
  }
  else if(wheelID == 1)//right wheel
  {
    return ui16RightWorkingSpeed;
  }
  else
  {
    return cui16StartingSpeed;
  }

  
}


void MOT_WriteToMotors()
{

          uint16_t leftAdjustedSpeed = MOT_GetAdjustedSpeed(0);
          uint16_t rightAdjustedSpeed = MOT_GetAdjustedSpeed(1);

          Serial.println("Prop: " + String(ProportionalFactor) + "  Der: " + String(DerivativeFactor) + "  Integral: " + String(IntegralFactor));
  
          //Forward
          ledcWrite(6,0); //LeftBackward
          ledcWrite(7,leftAdjustedSpeed); //Left Forward
          ledcWrite(4,0); //Right Backward
          ledcWrite(5,rightAdjustedSpeed); //Right Forward
  
}

void MOT_UpdateSpeed()
{

  
  
  MOT_i32EncoderError = ENC_vi32LeftOdometer - ENC_vi32RightOdometer; //When error is positive, The left wheel is going faster
  MOT_i32EncoderErrorChange = MOT_i32EncoderError - MOT_i32OldEncoderError; //When Derivative is negative, The error is converging

  ProportionalFactor = MOT_i32EncoderError * ProportionalCoeff; //Positive when Left is faster
  IntegralFactor += MOT_i32EncoderError * IntegralCoeff; //"Integral" of proportional 
  DerivativeFactor = MOT_i32EncoderErrorChange * DerivativeCoeff; //negative when left is faster, but slowing down. 

  MOT_i32OldEncoderError = MOT_i32EncoderError;

  CorrectionFactor = ProportionalFactor + IntegralFactor + DerivativeFactor;


  MOT_WriteToMotors();

  
  
}
