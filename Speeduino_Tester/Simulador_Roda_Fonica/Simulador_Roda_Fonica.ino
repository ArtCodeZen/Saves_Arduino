#define VR_OUT 13

struct TimerDelay{
  unsigned long previousMicros;
  unsigned long interval;
  // constructor
  TimerDelay(unsigned long interval): previousMicros(0), interval(interval){}
  bool check(){
    unsigned long currentMicros = micros();
    if(currentMicros - previousMicros >= interval){
      previousMicros = currentMicros;
      return true;
    }
    return false;
  }
  void updateInterval(unsigned long newInterval){
    if(newInterval >= 1)
      interval = newInterval;
      

  }
  int getCurrentInterval(){
    return interval;
  }
};

void setup() {
  // put your setup code here, to run once:
  pinMode(VR_OUT, OUTPUT);
  Serial.begin(9600);

}
int rpm = 2000;
int tooths = 60;
int toothPositionRising = 0;
bool pinStatus = false;
double result  =  ((((60 * 1000.00) / rpm) / tooths) / 2.00) * 1000.00;
TimerDelay myTimer(result);
void loop() {
  // put your main code here, to run repeatedly:
  
  if(myTimer.check()){        
      pinStatus ^= 1;   
      if(pinStatus == true){
        toothPositionRising++;
        if(toothPositionRising > (tooths - 2)){
          digitalWrite(VR_OUT, LOW);
        }else{
          digitalWrite(VR_OUT, HIGH);
        }
        if(toothPositionRising >= tooths){
          toothPositionRising = 0;    // reset
        }
      }else
        digitalWrite(VR_OUT, LOW);

  }
  
}
