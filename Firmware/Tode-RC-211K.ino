/******************************************************************************************************************//**
 * @file      Tode-RC-20CR.ino
 * @brief     Arduino Sketch for the Tode-RC System Implementing Ebyte E32 Transceiver.
 * @details 
 * @version   20CR [YYMD]
 * @bug       None Yet
 * @warning   Never call 'RF' object in Item Constructors
 * @copyright MIT Public License
 * @author    TGIT-TECH   original creation   2116
 **********************************************************************************************************************/
#include "lib/ABC.h"
#include "lib/ABC.cpp"
#include "Sys.h"

AnalogButtonCapture* ButtonCapture = 0;
Sys* System=0;

void setup() {
  
  pinMode(A15, INPUT_PULLUP);   // Pullup Analog Keypad-Pin

  pinMode(33, OUTPUT);
  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);       // Turn on Display Backlight
    
//#if DEBUGLEVEL>0
  Serial.begin(9600);           // This has a funny way of blanking the display (Comment out to check)
  while (!Serial) ;             // If the Serial Monitor isn't open at the time
//#endif

  Serial1.begin(9600);          // Begin Radio Communication

  ButtonCapture = new AnalogButtonCapture(/*Pin*/A15, /*Debounce*/300, /*HoldRepeat*/2000, /*BuzzPin*/46);
  ButtonCapture->StartCapture();

  System = new Sys();
  System->Navigate( NAVKEYNONE );       // Required to Start the Display on Power-Up

}

void loop() {
  System->Loop( System->Navigate( ButtonCapture->Button() ));
}
