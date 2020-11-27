/******************************************************************************************************************//**
   @file Devices.cpp
   @brief Device Base/Interface Class (All Devices must inherit this class)
   @authors
      TGit-Tech           2/2019       Original
 **********************************************************************************************************************/
#ifndef _DEVICES_CPP
#define _DEVICES_CPP
#include "Devices.h"

#define PINSIZE 13
const int PinsOption[13] = {   4,   5,   6,   7,   8,   10,   14,   15,   16,  18,  19,  20, 21 };
const char* PinNames[13] = {"A6", "D5", "A7", "D7", "A8", "D10", "D14", "D15", "D16", "A0", "A1", "A2", "A3"};
const byte OnOffOption[2] = {        0,   1};
const char* OnOffOptionNames[2] = {"OFF", "ON"};

//#####################################################################################################
SetNet::SetNet(const char* _Name, int _VAddr):
  MVDigitSet(_Name, 0x0000, 0xFFFF, HEX) {
    VAddr = _VAddr;
}
//-----------------------------------------------------------------------------------------------------
int SetNet::Value() {
  return (EEPROM.read(VAddr+1)<<8) + EEPROM.read(VAddr);
}
//-----------------------------------------------------------------------------------------------------
void SetNet::Value(int _Value) {
  EEPROM.put(VAddr,_Value);
}
//#####################################################################################################
AddDevice::AddDevice(const char* _CName, byte _DeviceToAdd, MenuList* _SubList=0):
  MenuName(_CName, _SubList) {
    DeviceToAdd = _DeviceToAdd;
}
//-----------------------------------------------------------------------------------------------------      
byte AddDevice::Navigate(byte _Key, byte _Row=0) {
  if ( Selected == SEL_ITEM ) {
    if ( _Key == KEYSET || _Key == KEYOKAY ) { return DeviceToAdd; }
  }
  return NNavigate(_Key,_Row);
}
//#####################################################################################################
OnOff::OnOff(int _NAddr, bool _IsLocal=false):
  MVOptions(_NAddr, AEB_DEVICENAME, OnOffOption, 2, OnOffOptionNames, _IsLocal) {
    IsLocal = _IsLocal;
}
#endif
