/******************************************************************************************************************//**
 * @file    RFC.cpp
 * @brief   Ref.h
 *********************************************************************************************************************/
#ifndef _RFC_CPP
#define _RFC_CPP

#include "RFC.h"
//#####################################################################################################
RxPacket::RxPacket() {  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
byte    RxPacket::Type()      { return Bytes[PKB_TYPE]; }
int     RxPacket::FromRF()    { return word(Bytes[PKB_FROM_RFH],Bytes[PKB_FROM_RFL]); }
byte    RxPacket::Version()   { return Bytes[PKB_TODEVER]; }
byte    RxPacket::RFID()      { return Bytes[PKB_RFID]; }
int     RxPacket::SetValue()  { return word(Bytes[PKB_VALUEH],Bytes[PKB_VALUEL]); }
//-----------------------------------------------------------------------------------------------------
bool RxPacket::RxByte(byte _Byte) {
  //DBINFOAL(("RxPacket::RxByte(Byte): "),(_Byte,HEX))
  Bytes[NextIdx] = _Byte;
  NextIdx++;
  if (NextIdx==5) { if (!IsSecure()) return true; }         //End on Insecure
  if (NextIdx>5 && NextIdx>=Size) return true;            //End
  return false;
}
//-----------------------------------------------------------------------------------------------------
bool RxPacket::IsSecure() {
  int SecNet = word(Bytes[PKB_SECH],Bytes[PKB_SECL]);   //0,1
  int SecSN = SecNet&0x5555; int SecSZ = SecNet&0xAAAA; byte SN = 0; byte SZ = 0;
  for (int i=0; i<8; i++) { bitWrite(SN, i, bitRead(SecSN,i*2) ); }
  DBINFOAL(("RxPacket::IsSecure SN="),(SN,HEX))
  if ( SN != EEPROM.read(EMC_SECNET) ) { DBERRORL(("Packet Insecure")) return false; }
  for (int i=0; i<8; i++) { bitWrite(SZ, i, bitRead(SecSZ,i*2+1) ); }
  DBINFOAL(("RxPacket::IsSecure Size="),(SZ,HEX))
  Size = SZ;
  return true;
}
//-----------------------------------------------------------------------------------------------------
bool RxPacket::IsValid() {
  if ( Size==0 ) return false;
  return true;
}
//-----------------------------------------------------------------------------------------------------
int RxPacket::Value(byte _RFID) {             DBENTERAL(("RxPacket::Value(GET) RFID: "),(_RFID))
  // Check bytes for RFID then return Value
  for ( int i=PKB_RFID; i<Size; i=i+3 ) {
    if ( Bytes[i]==_RFID ) {
      DBINFOL(("RxPacket::Value(GET) RFID Found."))
      return word(Bytes[i+1],Bytes[i+2]);
    }
  }
  DBERRORL(("RxPacket::Value(GET) RFID NOT Found."))
  return VALNOTSET;
}
//-----------------------------------------------------------------------------------------------------
void RxPacket::SaveTodeConfig(int _EEAddress) {      
  DBENTERAL(("RxPacket::SaveTodeConfig(EEAddress): "),(_EEAddress))
  
  EEPROM.update(_EEAddress+EMO_TODEVER, Version() );  DBINFOAL(("Save Version: "),(Version()))

  DBINFOAL(("Byte Size: "),(Size))
  int EEAddr = _EEAddress+EMO_TODENAME;             // Start save at Name
  
  for ( int i = PKB_TODECONFIG; i<Size; i++ ) {       
    EEPROM.update(EEAddr, Bytes[i]); EEAddr++;
    if ( i>=57 ) { DBERRORL(("RxPacket::SaveTodeConfig i>=57")) break; }
  }
  
}
//#####################################################################################################
TxPacket::TxPacket(byte _SecNet, byte _Type, int _ToRF, byte _Ver, byte _DevRFID, int _Value) {
  DBINITAAL(("TxPacket::TxPacket[.,ToRF,Ver,.,.]: "),(_ToRF,HEX),(_Ver))

  // Packet-Type to Byte-Size ( Size is Byte[i]+1 )
  if      ( _Type == PKT_GETCONFIG )  { DBINFOL(("TxPacket::TxPacket PKT_GETCONFIG")) Size = 8; }
  else if ( _Type == PKT_GETVALS )    { DBINFOL(("TxPacket::TxPacket PKT_GETVALS")) Size = 9; }
  else if ( _Type == PKT_GETVAL )     { DBINFOL(("TxPacket::TxPacket PKT_GETVAL")) Size = 10; }
  else if ( _Type == PKT_SETVAL )     { DBINFOL(("TxPacket::TxPacket PKT_SETVAL")) Size = 12; }
  
  else if ( _Type == PKT_GOTCONFIG )  { DBINFOL(("TxPacket::TxPacket PKT_GOTCONFIG")) Size=PKB_TODECONFIG; }    // Start TodeConfig at Byte[9]
  else if ( _Type == PKT_GOTVALS ) { DBINFOL(("TxPacket::TxPacket PKT_GOTVALS")) Size=PKB_RFID; }               // Start Values at Byte[9]
  
  else { DBERRORAL(("UNIDENTIFIED Packet Type : "),(_Type)) return; }

  Bytes[PKB_TO_RFH] = highByte(_ToRF);    //0 
  Bytes[PKB_TO_RFL] = lowByte(_ToRF);     //1
  //Bytes[PKB_CHANNEL] set in Send()      //2
  //Bytes[PKB_SECH] = highByte(SecNet);   //3   Set in Secure()
  //Bytes[PKB_SECL] = lowByte(SecNet);    //4   Set in Secure()
  Bytes[PKB_TYPE] = _Type;                //5
  //Bytes[PKB_FROM_RFH] set in Send()     //6
  //Bytes[PKB_FROM_RFL] set in Send()     //7
  Bytes[PKB_TODEVER] = _Ver;              //8

  // ------ End of Static Sets ----------
  Bytes[PKB_RFID] = _DevRFID;             //9
  Bytes[PKB_VALUEH] = highByte(_Value);   //10
  Bytes[PKB_VALUEL] = lowByte(_Value);    //11
}
//-----------------------------------------------------------------------------------------------------
int TxPacket::Secure() {
  int i = 0; int y = 0; int Ret = 0xFFFF; byte EESec = EEPROM.read(EMC_SECNET);
  while ( i<16 ) {
    bitWrite(Ret,i,bitRead(EESec,y));i++;
    bitWrite(Ret,i,bitRead(Size,y));i++;y++;
  }
  Bytes[PKB_SECH] = highByte(Ret);     //3
  Bytes[PKB_SECL] = lowByte(Ret);      //4
  return Ret;
}
//-----------------------------------------------------------------------------------------------------
void TxPacket::AddTodeConfig(int _EEAddress) {
  DBENTERAL(("TxPacket::AddTodeConfig(EEAddress): "),(_EEAddress))
  
  int iDev = 1;
  for ( int EAdr = _EEAddress+3; EAdr<_EEAddress+AEB_TODEALLOC ; EAdr++ ) {
    
    // TodeName > Bytes
    if ( EAdr<=_EEAddress+AEB_TODEHEAD ) { 
      Bytes[Size] = EEPROM.read(EAdr);
      DBINFOAAL(("TxPacket::AddTodeConfig TodeName EAdr,Byte[i]: "),(EAdr),(Bytes[Size],HEX))
      Size++;
    } else { 
      Bytes[Size] = EEPROM.read(EAdr);
      DBINFOAL(("TxPacket::AddTodeConfig Devices Byte[i]: "),(Bytes[Size],HEX))
      Size++; iDev++; 
    }
    if ( iDev!=0 && iDev % AEB_DEVALLOC == 0 && Bytes[Size]==BNONE ) { 
      DBINFOAL(("TxPacket::AddTodeConfig END Devices: iDev%DEVALLOC "),(iDev % AEB_DEVALLOC))
      Size--; break; 
    }
    if ( Size>57 ) { DBERRORL(("TxPacket::TodeConfig Size>57")) break; }
  }
  DBINFOAL(("TxPacket::AddTodeConfig Size = "),(Size))
}
//-----------------------------------------------------------------------------------------------------
void TxPacket::AddValue(byte _RFID, int _Value) {
  Bytes[Size] = _RFID; Size++;
  Bytes[Size] = highByte(_Value); Size++;
  Bytes[Size] = lowByte(_Value); Size++;
}
//_____________________________________________________________________________________________________________________
#endif
