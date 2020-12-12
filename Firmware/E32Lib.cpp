/**********************************************************************************************//**
 * @file    E32Lib.cpp
 * @brief   Ref.h
 *************************************************************************************************/
#ifndef _E32LIB_CPP
#define _E32LIB_CPP

#include "E32Lib.h"

#define ID_MASK 0x0F    // Bytes[0] [0000 1111] ArduinoID ( 0-15 )
#define REPLY_BIT 4     // Bytes[0] [0001 0000] Reply-1, Send-0
#define RW_BIT 5        // Bytes[0] [0010 0000] Read-1, Write-0
#define DA_BIT 6        // Bytes[0] [0100 0000] Digital-1, Analog-0
#define DPIN_MASK 0x3F  // Bytes[1] [0011 1111] Digital Pins ( 0 - 63 )
#define APIN_MASK 0x7F  // Bytes[1] [0111 1111] Analog Pins ( 0 - 127 )
#define HL_BIT 6        // Bytes[1] [0100 0000] High-1, Low-0
#define END_BIT 7       // Bytes[?} [1000 0000] Any set 8th bit flags END-OF-PACKET
//#####################################################################################################
// E32Radio
//#####################################################################################################
E32Radio::E32Radio() { GetParam(); }
//-----------------------------------------------------------------------------------------------------
void E32Radio::Address(unsigned int _RFAddress) {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
}
//-----------------------------------------------------------------------------------------------------
unsigned int E32Radio::Address() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  return word(E32Param[E32ADDH], E32Param[E32ADDL]);
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::Frequency(int _RFFrequency) {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
}
//-----------------------------------------------------------------------------------------------------
int E32Radio::Frequency() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  return 410 + (E32Param[E32CHAN] & 0x1F);
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::TxPower(byte _TxPower) {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  
}
//-----------------------------------------------------------------------------------------------------
byte E32Radio::TxPower() {
  if ( E32Param[E32HEAD] != 0xC0 ) GetParam();
  if ( (E32Param[E32OPTION] & 0x03) == 0 ) { return 30; }
  else if ( (E32Param[E32OPTION] & 0x03) == 1 ) { return 27; }
  else if ( (E32Param[E32OPTION] & 0x03) == 2 ) { return 24; }
  else if ( (E32Param[E32OPTION] & 0x03) == 3 ) { return 21; }
  return 0;
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::GetParam() {
  if ( Mode() != E32_SLEEPMODE ) Mode(E32_SLEEPMODE);
  Serial1.write(0xC1);Serial1.write(0xC1);Serial1.write(0xC1);
  int ReceivedByte = -1;
  unsigned long StartMillis = millis();
  while ( millis() - StartMillis < 200 ) {
    if ( Serial1.available() ) {
      ReceivedByte++; E32Param[ReceivedByte] = Serial1.read();
      if (ReceivedByte>=5) break;
    }
  } 
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::Mode(byte _Mode) {
  if ( _Mode == E32_NORMMODE ) { digitalWrite(E32M0, LOW); digitalWrite(E32M1, LOW); }
  else if ( _Mode == E32_WAKEMODE ) { digitalWrite(E32M0, LOW); digitalWrite(E32M1, HIGH); }
  else if ( _Mode == E32_PWRSAVE ) { digitalWrite(E32M0, HIGH); digitalWrite(E32M1, LOW); }
  else if ( _Mode == E32_SLEEPMODE ) { digitalWrite(E32M0, HIGH); digitalWrite(E32M1, HIGH); }
}
//-----------------------------------------------------------------------------------------------------
byte E32Radio::Mode() {
  if ( digitalRead(E32M0) == LOW ) {
    if ( digitalRead(E32M1) == LOW ) { return E32_NORMMODE; } else { return E32_WAKEMODE; }
  } else {
    if ( digitalRead(E32M1) == LOW ) { return E32_PWRSAVE; } else { return E32_SLEEPMODE; }
  }
}
//-----------------------------------------------------------------------------------------------------
void E32Radio::Loop() {
  // Check for incoming communications
  if ( Mode() != E32_NORMMODE ) return;
 
  // Receive Bytes
  while(Serial1.available() > 0) {
    Bytes[idx] = Serial1.read();
    if ( Bytes[idx] != -1 ) {
      if ( bitRead(Bytes[idx],END_BIT) ) {
        DBINFOAL(("Packet Received @ Size: "),(idx+1))
        bitClear(Bytes[idx],END_BIT);           // Clear the END_BIT
        for(int i=(idx+1);i<4;i++) Bytes[i]=0;  // Clear unused bytes
        idx = 0;
        ProcessPacket();
        return;
      } else {
        idx++;
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------
// SendPacket()
//-----------------------------------------------------------------------------------------------------
int E32Radio::SendPacket(bool DA, bool RW, byte Pin, int Value) {
  DBINFOL(("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"));
  DBINFOL(("SendPacket()"));
  byte SBytes[4] = { 0,0,0,0 };
  if ( DA ) bitSet(SBytes[0],DA_BIT);
  if ( RW ) bitSet(SBytes[0],RW_BIT);
  SBytes[0] = SBytes[0] | (iTargetArduinoID & ID_MASK);
  
  if ( DA == DIGITAL ) {
    SBytes[1] = (Pin & DPIN_MASK);                             // 6-bit Pin for Digital
    if ( RW != READ ) bitWrite(SBytes[1],HL_BIT,(Value>0));    // Digital Write - Set H/L Bit
    bitSet(SBytes[1],END_BIT);                                 // Digital only uses 2-Bytes  
  
  } else {
    SBytes[1] = (Pin & APIN_MASK);                             // 7-bit Pin for Analog
    if ( Value > -1 ) {
      Value = ValueTo7bits(Value);                            // Conversion marks the END_BIT
      SBytes[2] = lowByte(Value);
      SBytes[3] = highByte(Value);
    } else {
      bitSet(SBytes[1],END_BIT);                               // Set END_BIT if not sending Value
    }
  }  
  
  DBINFO(("SendBytes( "));
  Serial1.write(SBytes[0]);
  Serial1.write(SBytes[1]);
  if ( SBytes[2] != 0 ) Serial1.write(SBytes[2]);
  if ( SBytes[3] != 0 ) Serial1.write(SBytes[3]);
  //DBINFO((SBytes[0],HEX));DBC;DBINFO((SBytes[1],HEX));DBC;DBINFO((SBytes[2],HEX));DBC;DBINFO((SBytes[3],HEX));DBINFOL((" )"));
  
  return ( SBytes[1] << 8 ) | SBytes[0];                        // Return Bytes 0, 1 for tracking
}

//-----------------------------------------------------------------------------------------------------
// ValueTo8bits()   ValueTo7bits()
//  - Encodes / Decodes numeric values into (2)7-bit bytes for the 14-bit 'AV' (Analog Value) Bytes
//  - This function automatically attaches the END_BIT at the appropriate location.
//-----------------------------------------------------------------------------------------------------
int E32Radio::ValueTo8bits(byte lByte, byte hByte) {
  bitClear(hByte,7);                        // Clear any End-Of-Packet flag
  bitWrite(lByte,7,bitRead(hByte,0));       // Transfer hByte<0> onto lByte<7>
  return (hByte<<7) | lByte;                // Left shift 7 overwrites lByte<7>
}
int E32Radio::ValueTo7bits(int From8BitValue) {
  byte lByte = lowByte(From8BitValue);
  byte hByte = highByte(From8BitValue);
  if ( From8BitValue > 0x3FFF ) return -1;  //  Value is too big for a 14-bit Value
  hByte = hByte << 1;                       // Make Room on hByte for bit-7 of lByte
  bitWrite(hByte,0,bitRead(lByte,7));       // Transfer lByte<7> onto hByte<0>
  if ( From8BitValue > 0x7F ) { 
    bitSet(hByte,7);        // Value > 7-bits so Set 'END_BIT' @ hByte
    bitClear(lByte,7);
  } else {
    bitSet(lByte,7);        // Value <= 7-bits so Set 'END_BIT' @ lByte
    bitClear(hByte,7);
  }
  return (hByte<<8) | lByte;        
}

//-----------------------------------------------------------------------------------------------------
// ProcessPacket()
//-----------------------------------------------------------------------------------------------------
void E32Radio::ProcessPacket() {
  DBINFO(("ProcessPacket( "));
  //DBINFO((Bytes[0],HEX));DBC;DBINFO((Bytes[1],HEX));DBC;DBINFO((Bytes[2],HEX));DBC;DBINFO((Bytes[3],HEX));
  DBINFO((" ) - "));
  
  // REPLY PACKET RECEIVED
  if ( bitRead(Bytes[0],REPLY_BIT) ) {
    DBINFOL(("Packet Type REPLY"));
    for ( int i=0;i<4;i++ ) RBytes[RBI][i] = Bytes[i];   // Put Replies in RBytes Buffer
    //DecodePacket();

  // COMMAND PACKET RECEIVED
  } else if ( (Bytes[0] & ID_MASK) == ArduinoID ) {
    
    DBINFOL(("Packet Type SEND"));
    // DIGITAL
    if ( bitRead(Bytes[0],DA_BIT) == DIGITAL ) {
      int pin = Bytes[1] & DPIN_MASK;
      if ( bitRead(Bytes[0],RW_BIT) == READ ) {           // DIGITAL - READ
        bitWrite(Bytes[1],HL_BIT,digitalRead(pin));
        
      } else {                                            // DIGITAL - WRITE
        digitalWrite(pin,bitRead(Bytes[1],HL_BIT));
      }
      bitSet(Bytes[1],END_BIT);

    // ANALOG
    } else {
      int pin = Bytes[1] & APIN_MASK;
      int val = 0;
      if ( bitRead(Bytes[0],RW_BIT) == READ ) {
        //DBINFO(("analogRead("));DBINFO((pin));DBINFOL((")"));
        if ( pin > 63 && pin < 128 ) { 
          val = ValueTo7bits(iVirtualPin[pin-64]); 
        } else { 
          val = ValueTo7bits(analogRead(pin)); 
        }
        Bytes[2] = lowByte(val);
        Bytes[3] = highByte(val);
      } else { 
        DBINFOAAL(("analogWrite"),(pin),(ValueTo8bits(Bytes[2],Bytes[3])))
        if ( pin > 63 && pin < 128 ) { 
          iVirtualPin[pin-64] = ValueTo8bits(Bytes[2],Bytes[3]); 
        } else { 
          //analogWrite(pin,ValueTo8bits(Bytes[2],Bytes[3]));
        }
      }
    }
    
    // Send out the Reply Packet
    bitSet(Bytes[0],REPLY_BIT); // Set the Reply Bit
    //DBINFO(("SendBytes( "));
    Serial1.write(Bytes[0]);
    Serial1.write(Bytes[1]);
    if ( Bytes[2] != 0 ) Serial1.write(Bytes[2]);
    if ( Bytes[3] != 0 ) Serial1.write(Bytes[3]);
    //DBINFO((Bytes[0],HEX));DBC;DBINFO((Bytes[1],HEX));DBC;DBINFO((Bytes[2],HEX));DBC;DBINFO((Bytes[3],HEX));DBINFOL((" )"));
  }   

}
//#####################################################################################################
// E32PCConn
//#####################################################################################################
E32PCConn::E32PCConn(const char* _CName, MenuList* _SubList):
  MenuName(_CName, _SubList) {



}
//-----------------------------------------------------------------------------------------------------
byte E32PCConn::NameNav(byte _Key, byte _Row) {
  
  // KEY
  if ( Selected == SEL_ITEM ) {
    if ( _Key == KEYOKAY ) {
      digitalWrite(E32M0, HIGH);
      digitalWrite(E32M1, HIGH);
      IsConnecting = true;
      Selected = SEL_LOOP;
      return KEY_CSHOWLIST;
    }
  }
  if ( Selected == SEL_LOOP ) {
    if ( _Key == KEYOKAY ) {
      digitalWrite(E32M0, LOW);
      digitalWrite(E32M1, LOW);
      IsConnecting = false;
      Selected = SEL_ITEM;
      return KEY_CSHOWLIST;
    }
  }

  // DISPLAY
  if (_Key!=KEY_SHOWROW) return _Key; //DBINFOL(("KEY_SHOWROW"))
  if ( Display==0 ) { DBERRORL(("Display==0")) return _Key; }

  Display->SETCURSOR(0, _Row);
  if ( Selected == SEL_ITEM ) Display->HIGHLIGHT; //Display->HIGHLIGHT;

  if ( Selected == SEL_LOOP ) {
    Display->print(Name());Display->print(" ..GO");
  } else {
    Display->print(Name()); 
  }

  Display->NORMAL; 
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
byte E32PCConn::Loop() {
  if (!IsConnecting) return;
  DBINFOL(("E32PCConn::Loop"))
  if ( Serial.available() ) { Serial1.write(Serial.read()); }
  if ( Serial1.available() ) { Serial.write(Serial1.read()); }
}
//#####################################################################################################
E32Freq::E32Freq(const char* _CName):
  MenuValue(_CName) {
    ValueRange(410,441);
    
}
int E32Freq::Value() {
  // Read E32 Module Frequency
  
}
void E32Freq::Value(int _Value) {
  // Write new Frequency to E32 Module
}
#endif
