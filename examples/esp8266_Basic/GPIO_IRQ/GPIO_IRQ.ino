

uint8_t GPIO_Pin = D2;
 
void setup() 
{
 	Serial.begin(9600);
 	attachInterrupt(digitalPinToInterrupt(GPIO_Pin), IntCallback, RISING);
}
 
void loop() 
{
	
}
 
void IntCallback()
{
 	Serial.print("Stamp(ms): ");
	Serial.println(millis());
}
