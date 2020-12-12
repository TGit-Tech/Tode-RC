/************************************************************************//**
   @file AnalogButtonCapture.cpp
   @brief ref.h
   @authors
      TGit-Tech        9/2018       Original
 ******************************************************************************/
#ifndef _ANALOGBUTTONCAPTURE_CPP
#define _ANALOGBUTTONCAPTURE_CPP
#include "AnalogButtonCapture.h"

namespace ButtonISR {
int iButtonPin = 0;
unsigned long Debounce = 150;                   // Debounce button milliseconds
volatile int ButtonBuffer = KEYNONE;            // Store last button pressed for processing
volatile int Current_Button = KEYNONE;          // Stores last ISR Button
volatile unsigned long Button_Press_Time = 0;   // Tracks if button is held-down

//-------------------------------------------------------------------------------------
// Setup ISR on A0
//-------------------------------------------------------------------------------------
void EnableInterrupt() {
  DBINFOAL(("EnableInterrupt->"),(iButtonPin))
  cli();                          // disable interrupt
  if (iButtonPin == A9) {           // For Arduino UNO pin A9 (correct 19C3)
    PCMSK0 |= (1 << PCINT5);          // Use PCINT5 = PB5 pin 30.
    PCICR |= (1 << PCIE0);            // Enable (PCICR) Pin Change Interrupt Control Register (see page 91 of the Datasheet)
  } else if (iButtonPin == A15) {   // For Mega pin A15
    Serial.println("iButtonPin == A15");
    PCMSK2 |= (1 << PCINT23);         // Use PCINT23 = PK7 pin A15.
    PCICR |= (1 << PCIE2);    
  }
  sei();  //allows interrupts
}

//-------------------------------------------------------------------------------------
// ISR
// ISR Activated ButtonCheck()
// The Analog Interrupt will trigger when a button is pressed & when it is let-go
// Keypad WITH a 4.3K-ohm resistor soldered from pin A0 to GND
// Store_Button is only set to NONE by a call to retrieve the lcd.Button()
// TODO; Find a way to programically change PCINT
//-------------------------------------------------------------------------------------
ISR(PCINT2_vect) {
  if (ButtonBuffer != KEYNONE || millis() - Button_Press_Time < Debounce) return;    // Debounce Button presses

  // Capture Button Analog Value
  cli();
  //PCICR |= (0<<PCIE0);                                    // Disable (PCICR) Pin Change Interrupt
  Button_Press_Time = millis();                           // Record Press Time for Debounce
  int bpress = analogRead(iButtonPin); int temp = 0;
  for ( int cnt = 0; cnt < 10; cnt++ ) {                  // Read button 10-Times
    temp = analogRead(iButtonPin);
    if ( temp < bpress ) bpress = temp;                   // Keep smallest
  }

  // Assign Current Button
  Current_Button = KEYNONE;
  if (bpress < 500) Serial.print("ISR:");Serial.println(bpress);  // Check Button Values
  if (bpress < 18) {
    Current_Button = KEYRIGHT;
  }
  else if (bpress < 27) {
    Current_Button = KEYUP;
  }
  else if (bpress < 36) {
    Current_Button = KEYDOWN;
  }
  else if (bpress < 43) {
    Current_Button = KEYLEFT;
  }
  else if (bpress < 52) {
    Current_Button = KEYOKAY;
  }
  else if (bpress < 60) {
    Current_Button = KEYSET;
  }
  ButtonBuffer = Current_Button;
  //PCICR |= (1<<PCIE0);                                    // Enable (PCICR) Pin Change Interrupt
  sei();
}
}

// KEYRIGHT = 11, 12, 13-14, 15       #18
// KEYUP    = 20, 21, 22-23, 24       #27
// KEYDOWN  =   31, 32-33, 34         #36
// KEYLEFT  =     38, 39-40           #43
// KEYOKAY  = 45, 46, |47| 48, 49     #52
// KEYSET   =   54, 55-56, 57         #60

/*
   Constructor
*/
AnalogButtonCapture::AnalogButtonCapture(int ButtonPin, unsigned long Debounce_Button, unsigned long Button_Repeat_Held_Time) {
  ButtonISR::iButtonPin = ButtonPin;
  ButtonISR::Debounce = Debounce_Button;
  Hold_Repeat = Button_Repeat_Held_Time;
}
/*
   Start Capture
*/
void AnalogButtonCapture::StartCapture() {
  DBINFOL(("AnalogButtonCapture::StartCapture()"))
  ButtonISR::EnableInterrupt();
}
/*
   Button
*/
int AnalogButtonCapture::Button() {
  int Rtn = KEYNONE;                                         // Default return NONE
  if ( ButtonISR::ButtonBuffer != KEYNONE ) {                    // Check Button buffer for a button press
    Rtn = ButtonISR::ButtonBuffer;
    if ( BZPIN != 0 ) {
      noTone(BZPIN);
      tone(BZPIN,1200,15);
    }
    ButtonISR::ButtonBuffer = KEYNONE;                           // Clear the Buffer
  }
  return Rtn;
}

#endif
