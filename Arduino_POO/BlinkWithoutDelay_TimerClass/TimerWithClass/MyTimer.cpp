#include "MyTimer.h"
#include "Arduino.h"
MyTimer::MyTimer(int myInterval) : myInterval(myInterval){
  currentTime = lastTime = 0;
}
bool MyTimer::updateTimer(){
  currentTime = millis();
  if(currentTime - lastTime >= myInterval ){
    // update lastTime
    lastTime = currentTime;
    // match
    return true;

  }
  // nothing to do
  return false;
}