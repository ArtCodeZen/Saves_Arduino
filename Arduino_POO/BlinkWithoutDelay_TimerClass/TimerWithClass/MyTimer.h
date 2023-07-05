class MyTimer{
private:
  unsigned long currentTime;
  unsigned long lastTime;
  int myInterval;
public:
  MyTimer(int);
  bool updateTimer(void);
};