/**
 *
 * \par Description
 * This file is a drive for Me Buzzer device, The Me Buzzer inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * \par Method List:
 *
 *    1. void Buzzer::setpin(int pin);
 *	  2. void Buzzer::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void Buzzer::tone(uint16_t frequency, uint32_t duration)
 *	  4. void Buzzer::noTone(int pin);
 *	  5. void Buzzer::noTone();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * forfish         2015/11/09     1.0.0            Add description
 * </pre>
 *
 * @example BuzzerTest.ino
 * @example MbotBuzzerTest.ino
 * @example MbotBuzzerTest2.ino
 */
#include "Buzzer.h"

uint8_t buzzer_pin;

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * \param[in]
 *   switchPin - arduino port for buzzer detect pin.
 */
Buzzer::Buzzer(int pin)
{
  buzzer_pin = pin;
}

/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset the buzzer available pin by its arduino port.
 * \param[in]
 *    pin - arduino port for buzzer detect pin.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void Buzzer::setpin(int pin)
{
  buzzer_pin = pin;
}

/**
 * \par Function
 *    tone
 * \par Description
 *    Playing the tones.
 * \param[in]
 *    pin - Which pin on board that buzzer is connecting to.
 * \param[in]
 *    frequency - The speed of buzzer's tone play.
 * \param[in]
 *    duration - Time of a tone play.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    Frequency (in hertz) and duration (in milliseconds).
 */
void Buzzer::tone(int pin, uint16_t frequency, uint32_t duration)
{
  buzzer_pin = pin;
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
    wdt_reset();
  }
}

/**
 * \par Function
 *    tone
 * \par Description
 *    Playing the tones.
 * \param[in]
 *    frequency - The speed of buzzer's tone play.
 * \param[in]
 *    duration - Time of a tone play.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    Frequency (in hertz) and duration (in milliseconds).
 */
void Buzzer::tone(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
    wdt_reset();
  }
}

/**
 * \par Function
 *    noTone
 * \par Description
 *    Do not playing the tones.
 * \param[in]
 *    pin - Which pin on board that buzzer is connecting to.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    None
 */
void Buzzer::noTone(int pin)
{
  buzzer_pin = pin;
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}

/**
 * \par Function
 *    noTone
 * \par Description
 *    Do not playing the tones.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    None
 */
void Buzzer::noTone()
{
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}