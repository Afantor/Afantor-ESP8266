/**
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
 */
#ifndef Buzzer_H
#define Buzzer_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

/**
 * Class: Buzzer
 * \par Description
 * Declaration of Class Buzzer.
 */
class Buzzer
{
public:
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * \param[in]
 *   switchPin - arduino port for buzzer detect pin.
*/
  Buzzer(int pin);
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
  void setpin(int pin);

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
  void tone(int pin, uint16_t frequency, uint32_t duration);

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
  void tone(uint16_t frequency, uint32_t duration = 0);

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
  void noTone(int pin);

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
  void noTone();
};
#endif
