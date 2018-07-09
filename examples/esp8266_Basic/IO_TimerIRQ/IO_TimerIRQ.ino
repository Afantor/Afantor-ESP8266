

int PinRev = 14;
uint32_t rawCode[1024];
uint8_t rawCode_pin[1024];
int rawCodeCnt = 0;
bool printed = true;
//中断函数
uint32_t t0 = 0;
 
void interrupt_serv()
{
    rawCode_pin[rawCodeCnt] = digitalRead(PinRev);
    rawCode[rawCodeCnt] = micros();
    rawCodeCnt++;
}

void setup()
{
    Serial.begin(115200);
    delay(100);
    Serial.println("hello ESP8266 IR ,I am start");
    pinMode(PinRev, INPUT_PULLUP);//INPUT_PULLDOWN
 
    attachInterrupt(PinRev, interrupt_serv, CHANGE);
}
 
void loop()
{
    if (rawCodeCnt > 0)
    {
        if (micros() - rawCode[0] > 100000)
        {
            Serial.println("=========================================");
            for (int i = rawCodeCnt - 1; i > 0; i--)
            {
                if(rawCode[i] > rawCode[i - 1])
				{
                    rawCode[i] = rawCode[i] - rawCode[i - 1];
            	}
				else
				{
					rawCode[i] = (uint32_t)(0xffffffff-rawCode[i]) + rawCode[i - 1]; 
            	}
            }
            rawCode[0] = 0;
 
            for (int i = 0; i < rawCodeCnt; i++)
            {
                Serial.print(i);
                Serial.print( "  ");
                Serial.print(rawCode_pin[i]);
                Serial.print( "  ");
                Serial.println(rawCode[i]   );
            }
            rawCodeCnt = 0;
        }
    }
 
}