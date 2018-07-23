
int frequency = 1000; //以Hz为单位指定
int buzzPin = 16; 
int timeOn = 1000; //以毫秒为单位指定
int timeOff = 1000; //以毫秒为单位指定

void setup() 
{
  	pinMode(buzzPin, OUTPUT);     // Initialize the Buzzer_PIN pin as an output
}

void loop()
{
	tone(buzzPin, frequency);
	delay(timeOn);
	noTone(buzzPin);
	delay(timeOff);
}