unsigned int MOT_DriveDirection = 0; // 0-Forward, 1-Backward, 2-Right, 3-Left.

class PID{
  private:
  int integralConst;
  int proportionalConst;
  int derivativeConst;

  int integralFactor;
  int proportionalFactor;
  int derivativeFactor;


  int error;
  int errorChange;
  int prevError;

  int leftForwardDirection;
  int rightForwardDirection;

  public:

  char PIDName[10];

  PID(int Kp, int Ki, int Kd, int leftForward, int rightForward){
    integralConst = Ki;
    proportionalConst = Kp;
    derivativeConst = Kd;
    leftForwardDirection = leftForward;
    rightForwardDirection = rightForward;
    
    
  }

   int updatePID(int leftOdometer, int rightOdometer){

      this->error = (leftOdometer*this->leftForwardDirection) - (rightOdometer*this->rightForwardDirection);
      this->errorChange = this->error - this->prevError; //When Derivative is negative, The error is converging

  this->proportionalFactor = this->error * this->proportionalConst; //Positive when Left is faster
  this->integralFactor += this->error * this->integralConst; //"Integral" of proportional 
  this->derivativeFactor = this->errorChange * this->derivativeConst; //negative when left is faster, but slowing down. 

  this->prevError = this->error;

  return  (this->proportionalFactor + this->integralFactor + this->derivativeFactor);
  }

  
  
  
};
//Initializing all PID profile objects 
extern  PID PIDForward(1000, 10, 60, 1, 1);

extern  PID PIDBackward(1000, 15, 40, -1, -1);

extern  PID PIDRight(1000, 15, 40, 1, -1);

extern  PID PIDLeft(1000, 15, 40, -1, 1);


extern PID *CurrentPID = &PIDForward;


void MOT_Init()
{
  strcpy (PIDRight.PIDName,"right");
  strcpy (PIDLeft.PIDName,"left");
  strcpy (PIDBackward.PIDName,"backward");
  strcpy (PIDForward.PIDName,"forward");
  
  dForwardSpeed = 0;  // max 65536, 65536*0.75 = 49152
  dReverseSpeed = 0;
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

void MOT_SetDriveDirection(unsigned int dir) //sets 
{
  MOT_DriveDirection = dir;

  switch(dir)
  {
    case 0:
    {
      //Serial.println("Going forward");
      ////Serial.println("left OD" + ENC_vi32LeftOdometer);
      CurrentPID = &PIDForward;
      break;
    }
    case 1:
    {
      //Serial.println("Going backward");
      CurrentPID = &PIDBackward;
      break;
    }
    case 2:
    {
      //Serial.println("Going right");
      CurrentPID = &PIDRight;
      break;
    }
    case 3:
    {
      //Serial.println("Going left");
      CurrentPID = &PIDLeft;
      break;
    }
  }

}


int MOT_CalculateError(){
  CorrectionFactor = CurrentPID->updatePID(ENC_vi32LeftOdometer, ENC_vi32RightOdometer);
}

uint16_t MOT_GetAdjustedSpeed(int wheelID)
{



  
  if(wheelID == 0)//left wheel
  {
    if((iLeftWorkingSpeed - (CorrectionFactor/2)) <= 65535 && (iLeftWorkingSpeed - (CorrectionFactor/2)) >= 0 )
    {
          return (iLeftWorkingSpeed - (CorrectionFactor/2));
    }
    else if((iLeftWorkingSpeed - (CorrectionFactor/2)) > 65535)
    {
      return 65535;
    }
    else
    {
      return 0;
    }

  }
  else if(wheelID == 1)//right wheel
  {
    if((iRightWorkingSpeed + (CorrectionFactor/2)) <= 65535 && (iRightWorkingSpeed + (CorrectionFactor/2)) >= 0 )
    {
          return (iRightWorkingSpeed + (CorrectionFactor/2));
    }
    else if((iRightWorkingSpeed + (CorrectionFactor/2)) > 65535)
    {
      return 65535;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return cui16StartingSpeed;
  }

  
}


void MOT_WriteToMotors()
{

                  
  //Serial.print("Updating Speed with PID profile: ");
  //Serial.print((*CurrentPID).PIDName);
  //Serial.print("\n");


  
                MOT_CalculateError();
          uint16_t leftAdjustedSpeed = MOT_GetAdjustedSpeed(0);
          Serial.println(leftAdjustedSpeed);
          uint16_t rightAdjustedSpeed = MOT_GetAdjustedSpeed(1);
          Serial.println(rightAdjustedSpeed);
          Serial.println(MOT_DriveDirection);

        
          switch(MOT_DriveDirection){

            case 0: // forward
            {
                      //Forward
              ledcWrite(6,0); //LeftBackward
              ledcWrite(7,leftAdjustedSpeed); //Left Forward
              ledcWrite(4,0); //Right Backward 
              ledcWrite(5,rightAdjustedSpeed); //Right Forward
              break;
            }
            case 1: // Backward
            {
              break;
              ledcWrite(6,leftAdjustedSpeed); //LeftBackward
              ledcWrite(7,0); //Left Forward
              ledcWrite(4,rightAdjustedSpeed); //Right Backward
              ledcWrite(5,0); //Right Forward
              break;
            }
            case 2: //Right turn
            {
              ledcWrite(6,0); //LeftBackward
              ledcWrite(7,leftAdjustedSpeed); //Left Forward
              ledcWrite(4,rightAdjustedSpeed); //Right Backward
              ledcWrite(5,0); //Right Forward
              break;
            }
            case 3: //Left Turn
            {
              ledcWrite(6,leftAdjustedSpeed + 5000); //LeftBackward
              ledcWrite(7,0); //Left Forward
              ledcWrite(4,0); //Right Backward
              ledcWrite(5,rightAdjustedSpeed + 5000); //Right Forward
              break;
            }
          }
  

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
