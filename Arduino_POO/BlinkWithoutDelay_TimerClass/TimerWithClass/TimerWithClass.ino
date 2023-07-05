#include "MyTimer.h"
MyTimer mt(1000);
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mt.updateTimer()){ // true
    digitalWrite(13, !digitalRead(13));
  }
 
 
}
