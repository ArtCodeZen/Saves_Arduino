#define PIN 13

struct TimerDelay{
  unsigned long previousMillis;
  unsigned long interval;
  // constructor
  TimerDelay(int interval): previousMillis(0), interval(interval){}
  bool check(){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
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

TimerDelay myTimer(400);
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myTimer.check()){
    digitalWrite(PIN, !digitalRead(PIN));
    myTimer.updateInterval(myTimer.getCurrentInterval() - 1);
    Serial.println(myTimer.getCurrentInterval());

  }
}
