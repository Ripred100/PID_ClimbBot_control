

void SERV_Init()
{


 // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
//  ESP32PWM::allocateTimer(2);
//  ESP32PWM::allocateTimer(3);
  
  topServo.setPeriodHertz(50);    // standard 50 hz servo
  topServo.attach(ciServoTop, 500, 2400); // attaches the servo on pin 18 to the servo object

  bottomServo.setPeriodHertz(50);
  bottomServo.attach(ciServoBottom, 500, 2400);
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep

  pinMode(ciLimitSwitchLeft, INPUT_PULLUP);
  pinMode(ciLimitSwitchRight, INPUT_PULLUP);


          topServo.write(topPos);
        bottomServo.write(bottomPos);

}
