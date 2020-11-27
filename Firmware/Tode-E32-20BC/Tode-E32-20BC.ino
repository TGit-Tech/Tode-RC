/******************************************************************************************************************//**
 * @file    Tode-E32-20JO.ino
 * @brief   Arduino Sketch for the Tode-E32 System
 **********************************************************************************************************************/
#include "AnalogButtonCapture.h"
#include "Main.h"

AnalogButtonCapture AButton(A9, 300);
unsigned long ulDebounceT = 0;
int BPress=KEYNONE;
Main* System=0;
Tode* ThisTode=0;

void setup() {
  pinMode(A9, INPUT_PULLUP);  //Keypad-Pin
  AButton.StartCapture();

  //pinMode(49, OUTPUT);
  //pinMode(45, OUTPUT);

  /*
  pinMode(47, INPUT_PULLUP);  //KEYUP
  pinMode(44, INPUT_PULLUP);  //KEYLEFT
  pinMode(28, INPUT_PULLUP);  //KEYOKAY
  pinMode(30, INPUT_PULLUP);  //KEYSET
  pinMode(46, INPUT_PULLUP);  //KEYDOWN
  pinMode(26, INPUT_PULLUP);  //KEYRIGHT
  */

#if DEBUG>0
  //Serial.begin(9600); // This has a funny way of blanking the display (Comment out to check)
  //while (!Serial) ;   // If the Serial Monitor isn't open at the time
#endif

  ThisTode = new Tode(EMC_THISTODE);
  System = new Main(ThisTode);
  System->Navigate( KEYNONE );

  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);     // Turn on Backlight
}

void loop() {
  if (      digitalRead(47)==LOW) { BPress=KEYUP; }
  else if ( digitalRead(44)==LOW) { BPress=KEYLEFT; }
  else if ( digitalRead(28)==LOW) { BPress=KEYOKAY; }
  else if ( digitalRead(30)==LOW) { BPress=KEYSET; }
  else if ( digitalRead(46)==LOW) { BPress=KEYDOWN; }
  else if ( digitalRead(26)==LOW) { BPress=KEYRIGHT; }
  else { BPress=KEYNONE; } 
    
  if ( BPress != KEYNONE ) {
    if ( millis() - ulDebounceT > 250 )  {
      System->Navigate( BPress );
      ulDebounceT = millis();
    }
  }
  
  //System->Navigate( AButton.Button() );
}
