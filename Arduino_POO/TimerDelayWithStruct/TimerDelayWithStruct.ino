#define PIN 13

struct TimerDelay{
  unsigned long previousMillis;
  unsigned long interval;
  // constructor
  TimerDelay(unsigned long interval): previousMillis(0), interval(interval){}
  bool check(){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      return true;
    }
    return false;
  }

};

TimerDelay myTimer(500);
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(myTimer.check()){
    digitalWrite(PIN, !digitalRead(PIN));
  }
  
}
