/******************************************************************************************************************//**
 * @file    Tode-E32-20JO.ino
 * @brief   Arduino Sketch for the Tode-RC System Implementing Ebyte E32 Transceiver
 **********************************************************************************************************************/
#include "AnalogButtonCapture.h"
#include "Main.h"

AnalogButtonCapture AButton(A15, 300);
Main* System=0;

void setup() {
  pinMode(A15, INPUT_PULLUP);  //Keypad-Pin
  Serial1.begin(9600);
  Serial.begin(9600);
#if DEBUG>0
  Serial.begin(9600); // This has a funny way of blanking the display (Comment out to check)
  while (!Serial) ;   // If the Serial Monitor isn't open at the time
#endif
  AButton.StartCapture();
  
  System = new Main();
  System->Navigate( KEYNONE );

  pinMode(48, OUTPUT);
  digitalWrite(48, HIGH);     // Turn on Backlight

  //  M0, M1  - E32 - Operating Modes
  //  0   0   - NORMAL OPERATION
  //  1   0   - WAKE UP
  //  0   1   - POWER SAVE ( NO TRANSMIT, AIR-AWAKE )
  //  1   1   - SLEEP (COMMAND MODE)
  pinMode(E32M0, OUTPUT);
  pinMode(E32M1, OUTPUT);
  pinMode(E32AUX, INPUT);


  
}

void loop() {
  System->Loop(System->Navigate( AButton.Button() ));
  
}
