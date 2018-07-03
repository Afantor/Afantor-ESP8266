#include "WS2812FX.h"

#define LED_COUNT 13
#define LED_PIN   13

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
    Serial.begin(115200);
    
    ws2812fx.init();
    ws2812fx.setBrightness(255);
  
    // segment 0 is the builtin comet effect
    ws2812fx.setSegment(0, 0,           LED_COUNT/2 - 1, FX_MODE_COMET,  RED, 1000, false);
  
    // segment 1 is our custom effect
    ws2812fx.setCustomMode(myCustomEffect);
    ws2812fx.setSegment(1, LED_COUNT/2, LED_COUNT - 1,   FX_MODE_CUSTOM, RED, 50, false);
  
    ws2812fx.start();
}

void loop() 
{
    ws2812fx.service();
}

uint16_t myCustomEffect(void) 
{ // random chase
    WS2812FX::Segment seg = ws2812fx.getSegment(); // get the current segment
    for(uint16_t i=seg.stop; i>seg.start; i--) 
    {
        ws2812fx.setPixelColor(i, ws2812fx.getPixelColor(i-1));
    }
    uint32_t color = ws2812fx.getPixelColor(seg.start + 1);
    int r = random(6) != 0 ? (color >> 16 & 0xFF) : random(256);
    int g = random(6) != 0 ? (color >> 8  & 0xFF) : random(256);
    int b = random(6) != 0 ? (color       & 0xFF) : random(256);
    ws2812fx.setPixelColor(seg.start, r, g, b);
    return seg.speed; // return the delay until the next animation step (in msec)
}

