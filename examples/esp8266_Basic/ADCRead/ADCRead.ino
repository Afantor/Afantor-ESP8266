
/*********************
*读取外部电压
**********************/
void setup() 
{
  	Serial.begin(9600);
}
 
void loop() 
{
  	Serial.print("ADC Value: ");
  	Serial.println(analogRead(A0));
  	delay(300);
}

/*********************
*读取系统电压
**********************/
/*

ADC_MODE(ADC_VCC);
 
void setup() 
{
  	Serial.begin(9600);
}
 
void loop()
{
  	Serial.print("System voltage(mV): ");
  	Serial.println(ESP.getVcc());
  	delay(300);
}
 
 */