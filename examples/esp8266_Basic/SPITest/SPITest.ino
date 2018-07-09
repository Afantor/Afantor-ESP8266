/*
8266硬件spi demo
速度：1M
引脚
    SCK < GPIO14
    MISO < GPIO12
    MOSI   < GPIO13
    SS   < GPIO15//  用 setHwCs(true)启用
 
模式
    SPI_MODE0 0x00 - CPOL: 0  CPHA: 0
    SPI_MODE1 0x01 - CPOL: 0  CPHA: 1
    SPI_MODE2 0x10 - CPOL: 1  CPHA: 0
    SPI_MODE3 0x11 - CPOL: 1  CPHA: 1
 */
 
 
#include <SPI.h>
 
int channel;
int  level ;
 
void setup()
{ 
    //pinMode (slaveSelectPin, OUTPUT);//片选 ，用了内部控制，就不需要了
    pinMode (16, OUTPUT);//灯
 
    // initialize SPI:
    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setHwCs(true);   //由spi内部控制片选 
}
 
void loop()
{
    blinkled();
}
 
void digitalPotWrite(int address, int value)
{ 
    //digitalWrite(slaveSelectPin, LOW);  //片选 ，用了内部控制，就不需要了
    SPI.write(address);
    SPI.write(value);
    //digitalWrite(slaveSelectPin, HIGH);
}
 
void blinkled()
{
    static u32 previousMillis = 0;
    static int ledState = 0;
 
    if (millis() - previousMillis > 500)
    {
        previousMillis = millis();
        ledState = 1 - ledState;
        digitalWrite(16, ledState);
 
        digitalPotWrite(channel++, channel+1);
 
 
    }
}