

uint8_t LEDpin = D6;
 
/* By default PWM frequency is 1000Hz and we are using same 
   for this application hence no need to set.

analogWrite(pin, dutycycle)：在指定的引脚上启用软件PWM。占空比在0到PWMRANGE之间，默认为1023。

analogWrite(pin, 0)：禁用指定引脚上的PWM。

analogWriteRange(new_range)：该功能用于改变PWM范围（占空比）。

analogWriteFreq(new_frequency)：默认PWM频率为1kHz。调用此功能可将其更改为新频率.PWM频率范围为1 - 1000hz。

*/
 
void setup()
{
  	Serial.begin(9600);
  	analogWrite(LEDpin, 512);  /* set initial 50% duty cycle */
}
 
void loop()
{
  	uint16_t dutycycle =  analogRead(A0); /* read continuous POT and set PWM duty cycle according */
  	if(dutycycle > 1023) 
  		dutycycle = 1023;/* limit dutycycle to 1023 if POT read cross it */
  	Serial.print("Duty Cycle: "); 
  	Serial.println(dutycycle);
  	analogWrite(LEDpin, dutycycle);
  	delay(100);
}
 