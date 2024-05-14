#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"        // WiFi Configuration (WiFi name and Password)
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include <ESPping.h>
const char *ssid = "Wokwi-GUEST";
const char *password = "";
const unsigned char bitcoinIcon[] PROGMEM = {
    0x00, 0x7e, 0x00, 0x03, 0xff, 0xc0, 0x07, 0x81, 0xe0, 0x0e, 0x00, 0x70, 0x18, 0x28, 0x18, 0x30,
    0x28, 0x0c, 0x70, 0xfc, 0x0e, 0x60, 0xfe, 0x06, 0x60, 0xc7, 0x06, 0xc0, 0xc3, 0x03, 0xc0, 0xc7,
    0x03, 0xc0, 0xfe, 0x03, 0xc0, 0xff, 0x03, 0xc0, 0xc3, 0x83, 0xc0, 0xc1, 0x83, 0x60, 0xc3, 0x86,
    0x60, 0xff, 0x06, 0x70, 0xfe, 0x0e, 0x30, 0x28, 0x0c, 0x18, 0x28, 0x18, 0x0e, 0x00, 0x70, 0x07,
    0x81, 0xe0, 0x03, 0xff, 0xc0, 0x00, 0x7e, 0x00};

String lastPrice;
const int pin35 = 35;
const int pin26 = 26;
const int pin27=27;

void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  pinMode(pin26, OUTPUT);
  display.println("Connecting to WiFi...");
  display.display();
  Serial.begin(115200);
  Serial.println("Initializing WiFi...");

  WiFi.begin("Wokwi-GUEST", "");

  Serial.print("\nConnection");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(pin26, OUTPUT);
    delay(500);
    Serial.print(".");
  }
  display.print("\nConnection OK, IP: ");
  display.print(WiFi.localIP());
  display.print(" Gateway: ");
  display.println(WiFi.gatewayIP());
  display.display();
  bool ret = Ping.ping("portal.comnet.ec");
  display.print("portal.comnet.ec : ");
  display.print(ret ? "OK" : "KO");
  display.display();
}

void loop()
{

  /*if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Getting current data...");



    delay(1250);
  }*/
}

void printCenter(const String buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
  display.setCursor((x - w / 2) + (128 / 2), y);
  display.print(buf);
}