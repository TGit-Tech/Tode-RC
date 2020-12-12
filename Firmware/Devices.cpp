/******************************************************************************************************************//**
   @file    Devices.cpp
   @brief   Ref.h
   @authors
      TGit-Tech           2/2019       Original
 **********************************************************************************************************************/
#ifndef _DEVICES_CPP
#define _DEVICES_CPP
#include "Devices.h"

//#####################################################################################################
OnOff::OnOff(int _EETargetTode, byte _DevID):
  DeviceValue(_EETargetTode, _DevID)  {
    ValueRange(0,1);
    SetNumberName(0, "Off");
    SetNumberName(1, "On");
    if (IsLocal) {
      SubList = new MenuList("OnOff Setup");
      IOPin = SubList->Add(new PinSelect("Pin"));
    }
}
//-----------------------------------------------------------------------------------------------------
int OnOff::Value() {
  if ( IsLocal ) {
    if ( IOPin == 0 ) { DBERRORL(("OnOff::Value GET - IOPin==0")) return -1; }
    if ( IOPin->Value() < 0 || IOPin->Value() > 70 ) { DBERRORL(("OnOff::Value GET - IOPin OUT OF BOUNDS")) return -1; }
    //return digitalRead(IOPin->Value());
  } else {
    // Read by E32
    // Send RFAddr, Tode-Config-Ver, NetSec
    //return RF->digitalRead(DevID);
    //return -1;
  }
}
//-----------------------------------------------------------------------------------------------------
void OnOff::Value(int _Value) { 
  if ( IsLocal ) {
    if ( IOPin == 0 ) { DBERRORL(("OnOff::Value SET - IOPin==0")) return -1; }
    if ( IOPin->Value() < 0 || IOPin->Value() > 70 ) { DBERRORL(("OnOff::Value SET - IOPin OUT OF BOUNDS")) return -1; }
    digitalWrite(IOPin->Value(),_Value);
  } else {
    // Send to E32 (Need to Add TargetTode in PeerIOSerialControl)
    //RF->digitalWrite(DevID,_Value);
  }
}
#endif
