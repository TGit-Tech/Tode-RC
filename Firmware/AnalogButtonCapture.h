/************************************************************************//**
   @file AnalogButtonCapture.h
   @brief Captures analog button presses from an analog keypad.
   @authors
      TGit-Tech         12/2019     Original for use on UNO pin A9
      TGit-Tech         11/2020     Updated for use with Mega-2560 Pin A15
 ******************************************************************************/
#ifndef _ANALOGBUTTONCAPTURE_H
#define _ANALOGBUTTONCAPTURE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include "Constants.h"
#define BZPIN 46            // Pin hooked to Buzzer or 0 if none

class AnalogButtonCapture {
  public:
    // Constructors for parameterized Base Class
    AnalogButtonCapture(int ButtonPin, unsigned long Debounce_Button = 150, unsigned long Button_Repeat_Held_Time = 2000);

    // Public Functions
    void StartCapture();     // Default Debounce is 150 milliseconds
    int Button();

  private:
    unsigned long Last_Button_ms = 0;
    unsigned long Debounce = 150;
    unsigned long Hold_Repeat = 2000;
    int Last_Button_Retrieved = KEYNONE;

};
#endif
