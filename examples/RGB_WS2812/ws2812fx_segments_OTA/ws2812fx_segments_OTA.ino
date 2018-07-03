/*
  WS2812FX segmented led strip demo.
*/

#include "WS2812FX.h"
#include <ArduinoOTA.h>

#define LED_PIN   13  // digital pin used to drive the LED strip
#define LED_COUNT 13  // number of LEDs on the strip

#define WIFI_SSID "xxxxxxxx"     // WiFi network
#define WIFI_PASSWORD "xxxxxxxx" // WiFi network password

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
    Serial.begin(115200);
    Serial.println("\r\n");
  
    // init WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.mode(WIFI_STA);
  
    Serial.print("Connecting to " WIFI_SSID);
    while(WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    Serial.print("\nServer IP is ");
    Serial.println(WiFi.localIP());
  
    /* init OTA */
    // Port defaults to 8266
    // ArduinoOTA.setPort(8266);
  
    // Hostname defaults to esp8266-[ChipID]
    // ArduinoOTA.setHostname("myesp8266");
  
    // No authentication by default
    // ArduinoOTA.setPassword((const char *)"123");
  
    ArduinoOTA.onStart([]() 
    {
      Serial.println("OTA start");
    });
    ArduinoOTA.onEnd([]() 
    {
      Serial.println("\nOTA end");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) 
    {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) 
    {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
  
    ws2812fx.init();
    ws2812fx.setBrightness(127);
  
    // parameters: index, start, stop, mode, color, speed, reverse
    ws2812fx.setSegment(0, 0, 29, 9, (const uint32_t[]) {0xff0000, 0x000000, 0x000000}, 1000, false);
    ws2812fx.start();
}

void loop() 
{
    ws2812fx.service();
    ArduinoOTA.handle();
}
