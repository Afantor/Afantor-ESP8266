
#define LED_PIN 16
#define BUTTON_PIN 0

void setup() 
{
  	pinMode(LED_PIN, OUTPUT);     // Initialize the LED_PIN pin as an output
  	pinMode(BUTTON_PIN, INPUT);
}

// the loop function runs over and over again forever
void loop() 
{
	if(digitalRead(BUTTON_PIN)==0)
	{
	     digitalWrite(LED_PIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
	}
	else
	{
  		digitalWrite(LED_PIN, HIGH);  // Turn the LED off by making the voltage HIGH		
	}
  	delay(10);                      // Wait for a second

}