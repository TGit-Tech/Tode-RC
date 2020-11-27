/************************************************************************//**
   @file AnalogButtonCapture.h
   @brief Class to capture an analog button press from a analog button board.
          Optionally uses Pin-Change Interrupts
   @authors
      TGit-Tech        12/2019       Original
 ******************************************************************************/
#ifndef _ANALOGBUTTONCAPTURE_H
#define _ANALOGBUTTONCAPTURE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include "Constants.h"

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
