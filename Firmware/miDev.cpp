/******************************************************************************************************************//**
 * @file    miDev.cpp
 * @brief   Ref.h
 *********************************************************************************************************************/
#ifndef _MIDEV_CPP
#define _MIDEV_CPP

#include "miDev.h"
//#####################################################################################################################
OnOff::OnOff(byte _TodeIndex, byte _RFID, HdwSelect* _Hardware):
  Device(_TodeIndex, _RFID)  {                DBINITAAL(("OnOff::OnOff(TodeIndex,RFID,Hardware)"),(_TodeIndex),(_RFID))
    ValueRange(0,1);
    SetNumberName(0, "Off");
    SetNumberName(1, "On");
    if (IsLocal) {
      if ( _Hardware==0 ) { DBERRORL(("OnOff::OnOff IsLocal but Hardware==0")) return; } 
      SubList = new MenuList("OnOff Setup");
      IOPin = SubList->Add(new PinSelect("Pin",_Hardware));
    }
}
//-----------------------------------------------------------------------------------------------------
int OnOff::IOValue() {                                                 DBENTERL(("OnOff::IOValue[GET]"))
  if ( IOPin == 0 ) { DBERRORL(("OnOff::Value GET - IOPin==0")) return -1; }
  if ( IOPin->Value() < 0 || IOPin->Value() > 70 ) { DBERRORL(("OnOff::Value GET - IOPin OUT OF BOUNDS")) return -1; }
  return digitalRead(IOPin->Value());
}
//-----------------------------------------------------------------------------------------------------
void OnOff::IOValue(int _Value) {                           DBENTERAL(("OnOff::IOValue[SET]"),(_Value))

  if ( IOPin == 0 ) { DBERRORL(("OnOff::Value SET - IOPin==0")) return -1; }
  if ( IOPin->Value() < 0 || IOPin->Value() > 70 ) { DBERRORL(("OnOff::Value SET - IOPin OUT OF BOUNDS")) return -1; }
  digitalWrite(IOPin->Value(),_Value);
}
//_____________________________________________________________________________________________________________________
#endif
