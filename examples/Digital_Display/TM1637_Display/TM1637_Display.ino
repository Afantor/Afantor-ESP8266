#include "TM1637.h"

// Pin definitions for TM1637 and can be changed to other ports
//

//#define CLK D1
//#define DIO D2
#define CLK 0
#define DIO 13
TM1637 tm1637(CLK, DIO);


//
// This function is called when the device is powered-on.
//

void setup()
{  
    // Enable debug serial port.
    Serial.begin(74880);  // Set the UART speed the same as is for boot ROM
//    Serial.begin(115200); // Set standard UART speed

    // Initialize the display
    tm1637.init();

    //
    // Set the initial display intensity
    //
    tm1637.set(BRIGHT_DARKEST);
    //tm1637.set(BRIGHT_TYPICAL);

    //
    // Display "----" after the reset.
    //
    
    tm1637.display(0, 0x0f);
    tm1637.display(1, 0x0f);
    tm1637.display(2, 0x0f);
    tm1637.display(3, 0x0f);
    
    tm1637.point(true);

}

void loop()
{
    
}
