#include "Definitions.h"


void setup() {

  
  Serial.begin(115200); 
  Adafruit_NeoPixel SmartLEDs(2, 25, NEO_GRB + NEO_KHZ400);


   //setupMotion();
   //setupStepper();
   pinMode(ciHeartbeatLED, OUTPUT);
   pinMode(ciPB1, INPUT_PULLUP);
   pinMode(ciLimitSwitch, INPUT_PULLUP);

   SmartLEDs.begin();                          // Initialize Smart LEDs object (required)
   SmartLEDs.clear();                          // Set all pixel colours to off
   SmartLEDs.show();                           // Send the updated pixel colours to the hardware

}

void loop() {
  // put your main code here, to run repeatedly:

}
