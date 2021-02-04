#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include "time.h"
#include "SPI.h"
#include <WiFi.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        21 // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 12 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

#define MAKEPYTHON_ESP32_SDA 4
#define MAKEPYTHON_ESP32_SCL 5
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//WIFI
const char *ssid = "Makerfabs";
const char *password = "20160704";

//NTP time

const char *ntpServer = "120.25.108.11";
const long gmtOffset_sec = 8 * 60 * 60; //China+8
const int daylightOffset_sec = 0;

struct tm timeinfo;

void setup() {

    Wire.begin(MAKEPYTHON_ESP32_SDA, MAKEPYTHON_ESP32_SCL);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();

    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");
    
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println(F("Alread get npt time."));
    

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  if (!getLocalTime(&timeinfo))
      {
          Serial.println("Failed to obtain time");
          return;
      }
  int hour = timeinfo.tm_hour;
  int min = timeinfo.tm_min;
  int sec = timeinfo.tm_sec;
  int day = timeinfo.tm_mday;
  int mon = timeinfo.tm_mon + 1;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // Draw white text    
  display.setCursor(0, 0); // Start at top-left corner
  if(mon<10)
  display.print("0");
  display.print(mon);
  display.print(".");
  if(day<10)
  display.print("0");
  display.print(day);
  display.setTextSize(3);
  display.setCursor(20, 20);
  if(hour<10)
  display.print("0");
  display.print(hour);
  display.print(":");
  if(min<10)
  display.print("0");
  display.print(min);
  display.setTextSize(2);
  display.setCursor(100, 44);
  display.print(sec);
  display.display();
  
  
  int hour_d = hour%12;
  int min_d = min/5;
  int min_r = min%5;
  //if(sec_d>11)  sec_d = 0; 
  
  pixels.setPixelColor(hour_d, pixels.Color(0, 7, 0));
  pixels.setPixelColor(min_d, pixels.Color(min_r*5+1, 0, (5-min_r)*5));
  pixels.show();
  delay(999);
  
  /*for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 100, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }*/
}
