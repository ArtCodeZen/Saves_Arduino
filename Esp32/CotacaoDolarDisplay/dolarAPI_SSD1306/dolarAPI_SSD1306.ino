#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
// httpGET

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TP-Link_05A1";
const char* password = "19970000";

// time
#include <time.h>

// Configuração do NTP
const char* ntpServer = "pool.ntp.org"; // Servidor NTP
const long gmtOffset_sec = -10800;     // Fuso horário (-3h para Brasília)
const int daylightOffset_sec = 3600;   // Horário de verão (1h)
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 20);

  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Sincronizando com o servidor NTP...");
}
unsigned int x = 0;
void loop() {
  // Display static text
  // x++;
  // display.setCursor(0, 20);
  // display.println("Hello, world! " + String(x));
  // display.display();
  // delay(100);
  if ((WiFi.status() == WL_CONNECTED)) {  //Check the current connection status

    HTTPClient http;

    http.begin("https://olinda.bcb.gov.br/olinda/servico/PTAX/versao/v1/odata/CotacaoDolarDia(dataCotacao=@dataCotacao)?@dataCotacao=%2712-18-2024%27&$top=100&$format=json&$select=cotacaoVenda");  //Specify the URL
    int httpCode = http.GET();                                         //Make the request

    if (httpCode > 0) {  //Check for the returning code

      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end();  //Free the resources
  }
  printToday();
  delay(10000);
}

void printToday() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Falha ao obter a hora!");
        return;
    }

    // Obtendo o dia, mês e ano
    int dia = timeinfo.tm_mday;      // Dia do mês
    int mes = timeinfo.tm_mon + 1;  // Mês (0 = janeiro, então soma 1)
    int ano = timeinfo.tm_year + 1900; // Ano (desde 1900, então soma 1900)
    int hora = timeinfo.tm_hour;
    int minuto = timeinfo.tm_min;
    Serial.printf("Data de hoje: %02d/%02d/%04d\n", dia, mes, ano);
    Serial.printf("Hora: %02d:", hora);
    Serial.printf("%02d", minuto);
}