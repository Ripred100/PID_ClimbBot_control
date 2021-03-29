




void ENC_Disable()
{
   
   // disable GPIO interrupt on change
  detachInterrupt(ciEncoderLeftA);
  detachInterrupt(ciEncoderLeftB);
  detachInterrupt(ciEncoderRightA);
  detachInterrupt(ciEncoderRightB);
  
}


boolean ENC_ISMotorRunning()
{
  if((ENC_btLeftMotorRunningFlag) && (ENC_btLeftMotorRunningFlag))
  {
    return(1);
  }
  else
  {
     return(0);
  }
}

void ENC_CheckDistance()
{
    if(ENC_btLeftMotorRunningFlag)
  {
    if(ENC_vi32LeftOdometer == ENC_vi32LeftOdometerCompare)
    {
      
      ENC_btLeftMotorRunningFlag = false;
      ENC_btRightMotorRunningFlag = false;
      digitalWrite(ciMotorLeftA,HIGH);
      digitalWrite(ciMotorLeftB,HIGH);
      digitalWrite(ciMotorRightA,HIGH);
      digitalWrite(ciMotorRightB,HIGH);
      ledcWrite(6,255);
      ledcWrite(7,255);  //stop with braking Left motor 
      ledcWrite(5,255);
      ledcWrite(4,255);  //stop with braking Right motor 
      

    }    
  }

    if(ENC_btRightMotorRunningFlag)
  {
    if(ENC_vi32RightOdometer == ENC_vi32RightOdometerCompare)
    {
      
      ENC_btLeftMotorRunningFlag = false;
      ENC_btRightMotorRunningFlag = false;
      digitalWrite(ciMotorLeftA,HIGH);
      digitalWrite(ciMotorLeftB,HIGH);
      digitalWrite(ciMotorRightA,HIGH);
      digitalWrite(ciMotorRightB,HIGH);
      ledcWrite(6,255);
      ledcWrite(7,255);  //stop with braking Left motor 
      ledcWrite(5,255);
      ledcWrite(4,255);  //stop with braking Right motor 
      

    }
    
  }

  
}


void ENC_SetDistance(int32_t i32LeftDistance, int32_t i32RightDistance)
{
  
   ENC_vi32LeftOdometerCompare = ENC_vi32LeftOdometer + i32LeftDistance;
   ENC_vi32RightOdometerCompare = ENC_vi32RightOdometer + i32RightDistance;
   ENC_btLeftMotorRunningFlag = true;
   ENC_btRightMotorRunningFlag = true;
   ui8LeftWorkingSpeed = cui8StartingSpeed;
   ui8RightWorkingSpeed = cui8StartingSpeed;

}


void IRAM_ATTR ENC_isrLeftA()
{
   volatile static int32_t ENC_vsi32LastTime;
   volatile static int32_t ENC_vsi32ThisTime;

     if((digitalRead(ciEncoderLeftA) && digitalRead(ciEncoderLeftB)) || ((digitalRead(ciEncoderLeftA) == 0 && digitalRead(ciEncoderLeftB) == 0)))
  {
    ENC_vi32LeftOdometer += 1;
  }
  else
  {
    ENC_vi32LeftOdometer -= 1;
  }

  ENC_CheckDistance();

}

void IRAM_ATTR ENC_isrLeftB()
{
  volatile static int32_t ENC_vsi32LastTime;
  volatile static int32_t ENC_vsi32ThisTime;

  if((digitalRead(ciEncoderLeftA) && digitalRead(ciEncoderLeftB)) || ((digitalRead(ciEncoderLeftA) == 0 && digitalRead(ciEncoderLeftB) == 0)))
  {
    ENC_vi32LeftOdometer -= 1;
  }
  else
  {
    ENC_vi32LeftOdometer += 1;
  }

  ENC_CheckDistance();
}


void IRAM_ATTR ENC_isrRightA()
{
  volatile static int32_t ENC_vsi32LastTime;
  volatile static int32_t ENC_vsi32ThisTime;
  
  if((digitalRead(ciEncoderRightA) && digitalRead(ciEncoderRightB)) || ((digitalRead(ciEncoderRightA) == 0 && digitalRead(ciEncoderRightB) == 0)))
  {
    ENC_vi32RightOdometer -= 1;
  }
  else
  {
    ENC_vi32RightOdometer += 1;
  }

  ENC_CheckDistance();
}



void IRAM_ATTR ENC_isrRightB()
{
  volatile static int32_t ENC_vsi32LastTime;
  volatile static int32_t ENC_vsi32ThisTime;

    if((digitalRead(ciEncoderRightA) && digitalRead(ciEncoderRightB)) || ((digitalRead(ciEncoderRightA) == 0 && digitalRead(ciEncoderRightB) == 0)))
  {
    ENC_vi32RightOdometer += 1;
  }
  else
  {
    ENC_vi32RightOdometer -= 1;
  }

  ENC_CheckDistance();
}

void ENC_Init()
{
   //set pin modes
  pinMode(ciEncoderLeftA, INPUT_PULLUP);
  pinMode(ciEncoderLeftB, INPUT_PULLUP);
  pinMode(ciEncoderRightA, INPUT_PULLUP);
  pinMode(ciEncoderRightB, INPUT_PULLUP);

   // enable GPIO interrupt on change
  attachInterrupt(ciEncoderLeftA, ENC_isrLeftA, CHANGE);
  attachInterrupt(ciEncoderLeftB, ENC_isrLeftB, CHANGE);
  attachInterrupt(ciEncoderRightA, ENC_isrRightA, CHANGE);
  attachInterrupt(ciEncoderRightB, ENC_isrRightB, CHANGE);

  ENC_btLeftMotorRunningFlag = false;
  ENC_btRightMotorRunningFlag = false;

  


  //check to see if calibration is in eeprom and retreive
  
  
}

void ENC_ClearLeftOdometer()
{
  ENC_vi32LeftOdometer = 0;
 
}


void ENC_ClearRightOdometer()
{
  ENC_vi32RightOdometer = 0;
}
