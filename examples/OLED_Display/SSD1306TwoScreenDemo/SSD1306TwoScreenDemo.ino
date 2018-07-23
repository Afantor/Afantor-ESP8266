/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 by Afantor.
 *
 */

// Include the correct display library
// For a connection via I2C using Wire include
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include "images.h"

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, 12, 4);
SSD1306Wire  display2(0x3c, D1, D2);

void setup() 
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    
    // Initialising the UI will init the display too.
    display.init();
    display2.init();
    
    // This will make sure that multiple instances of a display driver
    // running on different ports will work together transparently
    display.setI2cAutoInit(true);
    display2.setI2cAutoInit(true);
    
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    
    display2.flipScreenVertically();
    display2.setFont(ArialMT_Plain_10);
    display2.setTextAlignment(TEXT_ALIGN_LEFT);

}

void loop() 
{
    display.clear();
    display.drawString(0, 0, "Hello world: " + String(millis()));
    display.display();
    
    display2.clear();
    display2.drawString(0, 0, "Hello world: " + String(millis()));
    display2.display();
    
    delay(10);
}
