/**********************************************************************************************//**
 * @file    DevLib.cpp
 * @brief   Ref.h
 *************************************************************************************************/
#ifndef _DEVLIB_CPP
#define _DEVLIB_CPP

#include "DevLib.h"

//#####################################################################################################
// PinSelect
//#####################################################################################################
PinSelect::PinSelect(const char* _CName, byte _IOHDW, bool _NameSettable):
  MenuValue(_CName) {
    IOHDW = _IOHDW;
    if ( IOHDW == IOHDW_WING ) {
      SetNumberName(57, "A3");
      SetNumberName(59, "A5");
      SetNumberName(61, "A7");
      SetNumberName(63, "A9");
      SetNumberName(65, "A11");
      SetNumberName(67, "A13");
    }
}
//-----------------------------------------------------------------------------------------------------
int PinSelect::Value() { return Pin; }
void PinSelect::Value(int _Value) { Pin = _Value; }
//-----------------------------------------------------------------------------------------------------
byte PinSelect::Navigate(byte _Key, byte _Row) {    //DBENTERAAL(("PinSelect::Navigate"),(_Key),(_Row))
  if ( Selected==SEL_ITEM ) {
    if (_Key==KEYRIGHT) { Selected=SEL_VALUE; return KEY_SHOWLIST; }
  } else if (Selected==SEL_VALUE) {
    if (_Key==KEYLEFT) { Selected=SEL_ITEM; return KEY_SHOWLIST; }
  }

  // Navigate Name & Value
  _Key = NameNav(_Key,_Row);
  _Key = ValueNav(_Key,_Row);
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
byte PinSelect::ValueNav(byte _Key, byte _Row=0) {   DBENTERAAL(("PinSelect::VNavigate"),(_Key),(_Row))
  if (_Key<KEYPRESSMIN && _Key!=KEY_SHOWROW) return _Key;
  if ( Display==0 ) { DBERRORL(("Display==0")) return _Key; }
  const char* ValueName;
  
  // KEY
  if (_Key != KEY_SHOWROW ) {
    if ( Selected==SEL_VALUE && _Key==KEYSET ) {
      Selected = SEL_SETVALUE;
      SetTo = Value();
      return KEY_SHOWLIST;
    } else if ( Selected==SEL_SETVALUE ) {
      if (_Key==KEYUP || _Key==KEYDOWN) { ChangeSetTo(_Key); }
      else if (_Key==KEYLEFT) { Selected = SEL_ITEM; }
      else if (_Key==KEYSET) { Value(SetTo); Selected=SEL_ITEM; }
      return KEY_CSHOWLIST;
    }

  // DISPLAY
  } else {
    Display->SETCURSOR(VALCOL, _Row);
    if ( Selected != SEL_SETVALUE ) {
      if ( Selected == SEL_VALUE) Display->HIGHLIGHT;
      ValueName = GetNumberName(Value());
      if ( ValueName==0 ) { Display->print(Value(),VNumBase); } else { Display->print(ValueName); }
    } else {
      Display->HIGHLIGHT;
      ValueName = GetNumberName(SetTo);
      if ( ValueName != 0 ) { Display->print(ValueName); } else { Display->print(SetTo,VNumBase); }
    }
    Display->NORMAL;
    return KEYNONE;
  }
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
int PinSelect::ChangeSetTo(byte _Key) {   DBENTERAL(("PinSelect::NextPin"),(SetTo))
  if (_Key!=KEYUP && _Key!=KEYDOWN) return SetTo;

  bool PinOkay = false;
  while (!PinOkay) {
    if (_Key==KEYUP) { SetTo++; } else { SetTo--; }
    if ( SetTo>=0 && SetTo<=31 ) { 
      if ( IOHDW == IOHDW_WING ) { if (bitRead(DIOWing_Pins,SetTo)) PinOkay = true; }
    } else if ( SetTo>=32 && SetTo<=63 ) { 
      if ( IOHDW == IOHDW_WING ) { if (bitRead(AIOWing_Pins,SetTo-32)) PinOkay = true; }
    } else if ( SetTo>=64 && SetTo<=72 ) { 
      if ( IOHDW == IOHDW_WING ) { if (bitRead(XIOWing_Pins,SetTo-64)) PinOkay = true; }
    }
    
    if (SetTo>70) { SetTo = -1; break; }
    if (SetTo<-1) { SetTo = -1; break; }
  }
  return SetTo;
}

//#####################################################################################################
SetNet::SetNet(const char* _Name, int _VAddr):
  MVDigitSet(_Name, 0x0000, 0xFFFF, HEX) {
    VAddr = _VAddr;
}
//-----------------------------------------------------------------------------------------------------
int SetNet::Value() {
  return EEPROM.read(EMC_SECNET);
}
//-----------------------------------------------------------------------------------------------------
void SetNet::Value(int _Value) {
  EEPROM.write(EMC_SECNET,byte(_Value));
}
//#####################################################################################################
// DeviceValue
//#####################################################################################################
DeviceValue::DeviceValue(int _EETargetTode, byte _DevID):
  MenuValue(_DevID*AEB_DEVALLOC + _EETargetTode+AEB_TODEHEAD +2, AEB_DEVICENAME, true, DEC)  {
    EEDevAddr = _DevID*AEB_DEVALLOC + _EETargetTode+AEB_TODEHEAD; // Calculates Device EEA
    IsLocal = (_EETargetTode == 0);
    EETargetTode = _EETargetTode;
    DevID = _DevID;
}
//-----------------------------------------------------------------------------------------------------
#endif
