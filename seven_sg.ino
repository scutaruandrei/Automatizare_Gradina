
#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object
int outputpin= 0;
void setup() {
  Serial.begin(9600);
  byte numDigits = 3;   
  byte digitPins[] = {2, 3, 4};
  byte segmentPins[] = {5,6,7,8,9,10};

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(50);
}

void loop() {
  static unsigned long timer = millis();
  int rawvoltage= analogRead(outputpin);
  float millivolts= (rawvoltage/1024.0) * 5000;
  float celsius= millivolts/10;
  Serial.print(celsius);
 // sevseg.refreshDisplay(); // Must run repeatedly
 // sevseg.setNumber(celsius,3); 
  delay(100);
  }



/// END ///
