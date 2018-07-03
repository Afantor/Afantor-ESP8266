//
//  Author:Frankie.Chu
//  Date:9 April,2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//  Author: Bc. Jan Grulich, jan@grulich.eu
//  Date: 9 April,2017
//  Note: Corrected the CLK and DIO sequecing and timing to match the TM1637 spec.
//        Reduced the CLK and DIO speed to let TM1637 work safely at 5V supply.
//
/*******************************************************************************/
#include "TM1637.h"
// #include <Arduino.h>

static int8_t TubeTab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x58,0x5c,0x54,0x00,0x40}; //0~9,A,c,o,n, ,-                        

TM1637::TM1637(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT); // set the CLK output
  pinMode(Datapin,OUTPUT); // set DIO output
  digitalWrite(Clkpin,HIGH); // default CLK HIGH
  digitalWrite(Datapin,HIGH); // default DIO HIGH
}

void TM1637::init(void)
{
  clearDisplay();
}

void TM1637::writeByte(int8_t wr_data)
{
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW); // Lock the DIO input latch for data change
    delayMicroseconds(2);
    if(wr_data & 0x01)digitalWrite(Datapin,HIGH); //LSB first
    else digitalWrite(Datapin,LOW);
    delayMicroseconds(2);
    wr_data >>= 1;      
    digitalWrite(Clkpin,HIGH); // Write data at rising edge of the CLK pin
    delayMicroseconds(5);  
  }
  
  digitalWrite(Clkpin,LOW); //wait for the ACK = TM1637 pulls the DIO LOW
//  delayMicroseconds(5);
  digitalWrite(Datapin,HIGH);
  delayMicroseconds(1);
  pinMode(Datapin,INPUT);
//  delayMicroseconds(2);
  while(digitalRead(Datapin)) // DIO read for the ACK signal
  { 
    count1 +=1;
    if(count1 == 200)
    {
     digitalWrite(Datapin,LOW);
     pinMode(Datapin,OUTPUT);
     delayMicroseconds(1);
     count1 =0;
    }
    pinMode(Datapin,INPUT);
  }

  digitalWrite(Clkpin,HIGH); // 9-th byte clock pulse
  delayMicroseconds(5);
  digitalWrite(Clkpin,LOW); // TM1637 releases the DIO pin after ACK
  delayMicroseconds(1);
  digitalWrite(Datapin,LOW);
  pinMode(Datapin,OUTPUT);
}

//send start signal to TM1637
void TM1637::start(void)
{
  digitalWrite(Datapin,LOW); 
  delayMicroseconds(3);
} 

//End of transmission
void TM1637::stop(void)
{
  digitalWrite(Clkpin,HIGH);
  delayMicroseconds(3);
  digitalWrite(Datapin,HIGH); 
  delayMicroseconds(5);
}

/*
//display function.Write to full-screen.
void TM1637::display(int8_t DispData[])
{
  int8_t SegData[4];
  uint8_t i;
  for(i = 0;i < 4;i ++)
  {
    SegData[i] = DispData[i];
  }
  coding(SegData);
  start();
  writeByte(ADDR_AUTO);
  stop();

  start();
  writeByte(Cmd_SetAddr);
  for(i=0;i < 4;i ++)
  {
    writeByte(SegData[i]);
  }
  stop();

  start();
  writeByte(Cmd_DispCtrl);
  stop();
}
*/

//******************************************
void TM1637::display(uint8_t BitAddr,int8_t DispData)
{
  int8_t SegData;
  SegData = coding(DispData);
  start();
  writeByte(ADDR_FIXED);
  stop();

  start();
  writeByte(BitAddr|0xc0);
  writeByte(SegData);
  stop();

  start();
  writeByte(Cmd_DispCtrl);
  stop();
}

void TM1637::clearDisplay(void)
{
  display(0x00,0x7f);
  display(0x01,0x7f);
  display(0x02,0x7f);
  display(0x03,0x7f);  
}

//To take effect the next time it displays.
void TM1637::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

//Whether to light the clock point ":".
//To take effect the next time it displays.
void TM1637::point(boolean PointFlag)
{
  _PointFlag = PointFlag;
}

/*
void TM1637::coding(int8_t DispData[])
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  for(uint8_t i = 0;i < 4;i ++)
  {
    if(DispData[i] == 0x7f)DispData[i] = 0x00;
    else DispData[i] = TubeTab[DispData[i]] + PointData;
  }
}
*/

int8_t TM1637::coding(int8_t DispData)
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  if(DispData == 0x7f) DispData = 0x00 + PointData; //The bit digital tube off
  else DispData = TubeTab[DispData] + PointData;
  return DispData;
}
