/*******************************************************************************
*
*    Projeto: Hello Word! - COMUNICAÇÃO I2C
*    Data: 30/09/2020
*            http://squids.com.br/arduino
*
*******************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const byte SCREEN_WIDTH = 128;  // OLED display width, in pixels
const byte SCREEN_HEIGHT = 64;  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
const int OLED_RESET = -1;  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();

  // Display Text "Hello Word"
}
int x = 0;
int i = 0;
void loop() {
  int val = analogRead(3);
  
  if(val >= 200 && val <= 260){
    x--;
  }
  if(val >= 290 && val <= 350){
    x++;
  }
  if(val >= 500 && val <= 520){
    if(i > 30)
      i = 0;
    else
      i++;
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(x, i);
  display.println("Valor: " + String(analogRead(3)));
  display.display();
  delay(100);

}