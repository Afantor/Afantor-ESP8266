/**
 */
#include "LEDMatrix.h"

#define DATA_PIN 13
#define CLK_PIN  0

#define BUTTON0_PIN 16
#define BUTTON0_PIN 0

LEDMatrix ledMx(CLK_PIN,DATA_PIN);

void setup()
{
  ledMx.setBrightness(6);
  ledMx.setColorIndex(1);
  pinMode(BUTTON0_PIN, INPUT);
  pinMode(BUTTON1_PIN, INPUT);
}

char *s = "ABC";

void loop()
{
	if(digitalRead(BUTTON0_PIN)==0)
	{
	    ledMx.showClock(12,03,1);
  		// delay(2000);
	}
  	if(digitalRead(BUTTON1_PIN)==0)
	{
	    ledMx.drawStr(0,7,s);
  		// delay(2000);
	}
  	ledMx.showNum(1.23);
}