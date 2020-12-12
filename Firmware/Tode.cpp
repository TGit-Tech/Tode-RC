/******************************************************************************************************************//**
 * @file  Tode.cpp
 * @brief Ref.h
 **********************************************************************************************************************/
#ifndef _TODE_CPP
#define _TODE_CPP
#include "Tode.h"

//#####################################################################################################
Tode::Tode(int _TodeAddr): MenuList() {                         DBINITAL(("Tode::Tode"), (_TodeAddr))
  TodeAddr = _TodeAddr;

  if ( 0>_TodeAddr || _TodeAddr>EMC_LOCALSETTINGS-AEB_TODEALLOC ) {
    DBERRORAL(("Tode::Tode INVALID TodeAddr!"),(_TodeAddr))
  } else {
    bIsLocal = (TodeAddr == 0);
    
    // TODENAME - Setup ( re: Tode::Name() points to TodeName->Name() )
    //MenuName(int _NAddr, byte _NSize, bool _NameSettable=false, const char* _TLine=0)
    TodeName = new MenuName(TodeAddr+EMO_TODENAME, AEB_TODENAME, true, "Name");    
    
    // Load Devices (12-bytes)[ TYPE-BYTE . ID . 10-BYTE NAME ] per Tode = 360B from EEPROM
    for ( int Addr=TodeAddr+AEB_TODEHEAD; Addr<AEB_DEVALLOC*AEB_MAXDEVICES; Addr=Addr+AEB_DEVALLOC ) {
      if ( this->AddDevice(EEPROM.read(Addr), EEPROM.read(Addr+1)) == 0 ) {
        DBINFOAL(("NO Device at: "),(Addr))
      } else { DBINFOAL(("Device Found at: "),(Addr)) }
    }
  }
  
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const char* Tode::Name() {                return TodeName->Name(); }
bool Tode::IsLocal() {                    return bIsLocal; }
unsigned int Tode::RFAddr() {             return word(EEPROM.read(TodeAddr+1),EEPROM.read(TodeAddr)); }
void Tode::RFAddr(unsigned int _RFAddr) { EEPROM.put(TodeAddr,_RFAddr); }
byte Tode::ConfigVersion() {              return EEPROM.read(TodeAddr + 2); }
void Tode::ConfigVersion(byte _Version) { EEPROM.write(TodeAddr + 2,_Version); }
void Tode::FreeDeviceID(byte _ID) {       bitClear(DeviceID_UsedBitFlags, _ID); }
void Tode::UsedDeviceID(byte _ID) {       bitSet(DeviceID_UsedBitFlags, _ID); }
byte Tode::GetDeviceID() {                // return an Un-Used DeviceID
  for ( byte x=0; x<AEB_MAXDEVICES; x++ ) { if ( !bitRead(DeviceID_UsedBitFlags, x) ) return x; }
  return BNONE;
}
//------------------------------------------------------------------------------------------------------
void Tode::SendRF_Config(int _RFTarget) {
//-----------------------------------------------------------------------------------------------------
  //Serial1.print(_RFTarget);
  //Serial1.print(0x17);
  //Serial1.print(EEPROM.read(0));
//  for (int addr = 1; addr < EndAddr(); addr++) {
    //Serial1.print(EEPROM.read(addr));
  //}

}
//-----------------------------------------------------------------------------------------------------
MenuItem* Tode::AddDevice(byte _DTKey, byte _ID) {  DBENTERA(("Tode::AddDevice"),(_DTKey))
  if ( 0x7F < _DTKey || _DTKey < 0x7A ) return 0;         // Check DTKey
  if ( _ID == BNONE ) { _ID = GetDeviceID(); }            // Get an ID if one is not given
  if ( 0>_ID || _ID>AEB_MAXDEVICES ) return 0;            // Check ID

  if ( _DTKey == DT_RW_ONOFF ) { 
    //OnOff(int _EEDevAddr, int _EETargetTode, byte _DevID);
    return this->Add(new OnOff(TodeAddr, _ID));
    UsedDeviceID(_ID); 
  }
  else if ( _DTKey == DT_RO_ONOFF ) { }
  else if ( _DTKey == DT_RO_PRESS ) { }
  else if ( _DTKey == DT_RO_TEMP ) { }
  else if ( _DTKey == DT_RO_DIST ) { }
  return 0;
}
//////
#endif
