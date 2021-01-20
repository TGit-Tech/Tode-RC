/******************************************************************************************************************//**
 * @file E32.cpp
 * @brief Ref.h
 *********************************************************************************************************************/
#ifndef _E32_CPP
#define _E32_CPP

#include "E32.h"
/*
 * [0][1] - To
 * [2]    - Channel
 * [3][4] - SecNet + Size
 * [5]    - [H]Size + PacketType
 * [6][7] - From
 * [8]    - Version    (9-Bytes)
 */
//#####################################################################################################################
E32Radio::E32Radio(byte _PinM0, byte _PinM1, byte _PinTX, byte _PinRX, byte _PinAUX):
  RadioI() {
    DBINITL(("E32Radio::E32Radio"))
    PinM0 = _PinM0; PinM1 = _PinM1; PinTX = _PinTX; PinRX = _PinRX; PinAUX = _PinAUX;
    if ( PinM0 != 0 ) pinMode(PinM0, OUTPUT); 
    if ( PinM1 != 0 ) pinMode(PinM1, OUTPUT);
    if ( PinAUX != 0 ) pinMode(PinAUX, INPUT_PULLUP);
}
//---------------------------------------------------------------------------------------------------------------------
void E32Radio::Address(unsigned int _RFAddress) {
  byte CurrentMode = Mode();
  if ( CurrentMode != E32_SLEEPMODE ) Mode(E32_SLEEPMODE);
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  E32Param[E32ADDH] = highByte(_RFAddress);
  E32Param[E32ADDL] = lowByte(_RFAddress);
  SetParam();
  Mode(CurrentMode);    // Return to last Mode RF was set to.
}
//-----------------------------------------------------------------------------------------------------
unsigned int E32Radio::Address() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  return word(E32Param[E32ADDH], E32Param[E32ADDL]);
}
//-----------------------------------------------------------------------------------------------------
// E32 - 'Channel' corresponds to 00H to 1FH and assigns 410 to 441MHz 
// Each (1)Channel is (1)MHz adjust [1F=31].  Default is 17H(23DEC) + 410 = 433.
//-----------------------------------------------------------------------------------------------------
void E32Radio::Frequency(int _RFFrequency) {
  if ( 410 > _RFFrequency || _RFFrequency > 441 ) return;         // Check Boundaries
  byte CurrentMode = Mode();                                      // Set & Return to Current Mode
  if ( CurrentMode != E32_SLEEPMODE ) Mode(E32_SLEEPMODE);        // Enter Sleep-Mode
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();                    // Get Parameters
  E32Param[E32CHAN] = _RFFrequency-410;                           // Set Frequency in Parameters
  SetParam();                                                     // Write Parameters
  Mode(CurrentMode);                                              // Return to Current Mode
}
//---------------------------------------------------------------------------------------------------------------------
int E32Radio::Frequency() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();                    // Get Parameters
  return 410 + (E32Param[E32CHAN] & 0x1F);                        // Return Channel in MHz form
}
//-----------------------------------------------------------------------------------------------------
byte E32Radio::Channel() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();                    // Get Parameters
  return (E32Param[E32CHAN] & 0x1F);                              // Return Channel in Channel form
}
//---------------------------------------------------------------------------------------------------------------------
void E32Radio::TxPower(byte _TxPower) {
  if ( _TxPower > 3 ) return;                                     // Check Boundaries
  byte CurrentMode = Mode();                                      // Set & Return to Current Mode
  if ( CurrentMode != E32_SLEEPMODE ) Mode(E32_SLEEPMODE);        // Enter Sleep-Mode
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();                    // Get Parameters
  E32Param[E32OPTION] &= 0xFC;                                    // 0 - previous setting ( bits 0 & 1 )
  E32Param[E32OPTION] += _TxPower;                                // Set Frequency in Parameters
  SetParam();                                                     // Write Parameters
  Mode(CurrentMode);                                              // Return to Current Mode
}
//-----------------------------------------------------------------------------------------------------
byte E32Radio::TxPower() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  return (E32Param[E32OPTION] & 0x03);
  //if ( (E32Param[E32OPTION] & 0x03) == 0 ) { return 30; }
  //else if ( (E32Param[E32OPTION] & 0x03) == 1 ) { return 27; }
  //else if ( (E32Param[E32OPTION] & 0x03) == 2 ) { return 24; }
  //else if ( (E32Param[E32OPTION] & 0x03) == 3 ) { return 21; }
  //return 0;
}
//---------------------------------------------------------------------------------------------------------------------
void E32Radio::GetParam() {                                           //DBENTERL(("E32Radio::GetParam"))
  byte CurrentMode = Mode();
  if ( CurrentMode != E32_SLEEPMODE ) Mode(E32_SLEEPMODE);
  Serial1.write(0xC1);Serial1.write(0xC1);Serial1.write(0xC1);
  int ReceivedByte = -1;
  unsigned long StartMillis = millis();
  while ( millis() - StartMillis < 200 ) {
    if ( Serial1.available() ) {
      ReceivedByte++; E32Param[ReceivedByte] = Serial1.read();
      //DBINFOAL(("ReceivedByte : "),(E32Param[ReceivedByte]))
      if (ReceivedByte>=5) break;
    }
  }
  Mode(CurrentMode);    // Return to last Mode RF was set to.
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::SetParam() {                                           DBENTERL(("E32Radio::SetParam"))
  byte CurrentMode = Mode();
  if ( CurrentMode != E32_SLEEPMODE ) Mode(E32_SLEEPMODE);
  Serial1.write(0xC0);      //#define E32HEAD       0
  Serial1.write(E32Param[E32ADDH]);
  Serial1.write(E32Param[E32ADDL]);
  Serial1.write(E32Param[E32SPEED]);
  Serial1.write(E32Param[E32CHAN]);
  Serial1.write(E32Param[E32OPTION]);
  Mode(CurrentMode);    // Return to last Mode RF was set to.
}
//---------------------------------------------------------------------------------------------------------------------
void E32Radio::Mode(byte _Mode) {
  if ( _Mode == E32_NORMMODE ) { digitalWrite(PinM0, LOW); digitalWrite(PinM1, LOW); }
  else if ( _Mode == E32_WAKEMODE ) { digitalWrite(PinM0, LOW); digitalWrite(PinM1, HIGH); }
  else if ( _Mode == E32_PWRSAVE ) { digitalWrite(PinM0, HIGH); digitalWrite(PinM1, LOW); }
  else if ( _Mode == E32_SLEEPMODE ) { digitalWrite(PinM0, HIGH); digitalWrite(PinM1, HIGH); }
}
//-----------------------------------------------------------------------------------------------------
byte E32Radio::Mode() {
  if ( digitalRead(PinM0) == LOW ) {
    if ( digitalRead(PinM1) == LOW ) { return E32_NORMMODE; } else { return E32_WAKEMODE; }
  } else {
    if ( digitalRead(PinM1) == LOW ) { return E32_PWRSAVE; } else { return E32_SLEEPMODE; }
  }
}
//---------------------------------------------------------------------------------------------------------------------
bool E32Radio::PacketAvailable() {                                        // Check for incoming communications
  
  if ( Serial1.available() == 0 ) return 0;                               // Check if data exists
  if ( Mode() != E32_NORMMODE ) return 0;                                 // Check Radio is receiving RF-data
  if ( Packet != 0 ) {                                                    // Expire Packet build after 1-Second
    if ( millis() - Packet->PacketStartTimeMS > 1000 ) { 
      delete Packet; Packet = 0; }
  }
  if ( Packet == 0 ) {                                                    // Create new packet if needed
    Packet = new RxPacket();                   
    Packet->PacketStartTimeMS = millis();
  }

  while ( Serial1.available() ) {                                         // Read RF Data
    if ( Packet->RxByte(Serial1.read()) ) {                               // Returns True when packet size reached
      if ( !Packet->IsValid() ) {
        DBINFOL(("E32Radio::PacketAvailable NOT VALID")) 
        delete(Packet); Packet=0; return false;                           // Return 'false' for InValid Packet
      }
      DBINFOL(("E32Radio::PacketAvailable Packet->IsValid"))
      return true;                                                        // Return 'true' for Valid Packet
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::Send(TxPacket* Tx) {
  DBENTERAL(("E32Radio::Send(Tx): "),(int(Tx),HEX))
  
  // Prep & Check
  if ( Tx == 0 ) return;
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  if ( Mode() != E32_NORMMODE ) { DBERRORAL(("E32Radio::Send(Tx) Radio in Mode : "),(Mode())) return; }
  unsigned int FromRF = Address();                                                    //This RF Address
  if ( FromRF == 0xFFFF ) { DBERRORL(("E32Radio::Send(Tx) FromRF=0xFFFF")) return; }
  
  // Set FromRF
  Tx->Bytes[PKB_FROM_RFH] = highByte(FromRF);
  Tx->Bytes[PKB_FROM_RFL] = lowByte(FromRF);
  // Set Channel
  Tx->Bytes[PKB_CHANNEL] = Channel();
  Tx->Secure();

  DBINFOL(("vvvvv E32Radio::Send Serial1.write(Tx) vvvvvvvvvvv"))
  for ( int i=0; i<Tx->Size; i++ ) { DBENTERA((" "),(Tx->Bytes[i],HEX)) }
  DBINFOL((" "))
  
  // Send the Bytes
  // The Below line inside while() loop made the Communications go down.  Not sure the reason; perhaps monitor print time lag?
  // DBINFOAAL(("E32Radio::Send Serial1.write(Tx->Bytes(i)): "),(i),(Tx->Bytes[i],HEX))
  int i = 0;
  while (i<Tx->Size) { 
    Serial1.write(Tx->Bytes[i]); 
    i++; 
  }

}
//_____________________________________________________________________________________________________________________
#endif
