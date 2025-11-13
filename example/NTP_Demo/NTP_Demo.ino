/*
Arduino V2.3.6
ESP32 V3.1.1
NTPClient V3.2.1
ESP8266 and ESP32 OLED driver for SSD1306 displays V4.6.1
*/

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "SSD1306Wire.h"  

const char* ssid = "Makerfabs";
const char* password = "20160704";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 28800, 60000);

SSD1306Wire display(0x3c, 4, 5);//SDA-->4;SCL-->5

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");

    timeClient.begin();
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void loop()
{
    timeClient.update();
    Serial.println(timeClient.getFormattedTime());
    display.clear();
    display.drawString(0, 5, "MaESP ESP32");
    display.drawString(0, 20, "NTP Time DEMO");
    display.drawString(0, 40, timeClient.getFormattedTime());
    display.display();
    delay(1000);
}

void gettime()
{
  timeClient.update();
  int hour = timeClient.getHours();   // 获取小时
  int min = timeClient.getMinutes(); // 获取分钟
  int sec = timeClient.getSeconds(); // 获取秒
  Serial.print("hour:");
  Serial.println(hour);
  Serial.print("min:");
  Serial.println(min);
  Serial.print("sec:");
  Serial.println(sec);
}