#define PIN_OUT 3
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(3, OUTPUT);
}
int value = 0;
void loop() {
  String sData = "";
  // put your main code here, to run repeatedly:  
  sData = Serial.readString(); // ler a string
  
  if(sData.length() > 0){
    value = sData.toInt();
    analogWrite(PIN_OUT, value);
    Serial.println("valor: " + String(value));
  }

}
