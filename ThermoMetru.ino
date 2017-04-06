
#include "SevSeg.h"


float tempC;
int reading;
int tempPin = 0;
SevSeg sevseg; //Instantiate a seven segment controller object
int outputpin= 0;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  byte numDigits = 3;   
  byte digitPins[] = {2, 3, 4};
  byte segmentPins[] = {5,6,7,8,9,10,11};
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}

void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;
  reading = analogRead(tempPin);
  tempC = reading / 9.31;
  int temp_seg = (int)(tempC *10 );
 // Serial.println(tempC);
  
  if (millis() >= timer) {
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    timer += 100; 
    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(temp_seg, 1);
    Serial.println(tempC);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
