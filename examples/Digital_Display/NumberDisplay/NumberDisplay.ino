
#include "DigitalDisplay.h"

#define DATA_PIN 13
#define CLK_PIN  0

DigitalDisplay disp(DATA_PIN,CLK_PIN);

uint16_t i = 0;
void setup()
{
}

void loop()
{
  if(i > 100)
  {
    i = 0;
  }
  disp.display(i++);
  delay(100);
}

