/******************************************************************************************************************//**
 * @file  Tode.cpp
 * @brief See Tode.h for details
 **********************************************************************************************************************/
#ifndef _TODE_CPP
#define _TODE_CPP
#include "Tode.h"

//#####################################################################################################
Tode::Tode(int _TodeAddr): MenuList() {                         DBINITAL(("Tode::Tode"), (_TodeAddr))
  TodeAddr = _TodeAddr;
  ELoadConfig();
}
//-----------------------------------------------------------------------------------------------------
const char* Tode::Name() { return TodeName->Name(); }
//-----------------------------------------------------------------------------------------------------
void Tode::ELoadConfig() {
  // Engineering Tools
  // for ( int b = 0; b < EEPROM.length(); b++) { EEPROM.update(b,0xFF); } DBINFOL(("CLEAN EEPROM"))
  // EEPROM.update(0,EMO_1STDEVICE-1);DBINFOL(("RESETTING EEPROM"))

  int TSize = EEPROM.read(TodeAddr);                // Read in Tode-Size
  TodeEndAddr = TodeAddr + TSize;                   // SetTode-Block-Ending
  ConfigVer = EEPROM.read(TodeAddr + EMO_TODEVER);  // Read in Tode-Config Version
  
////////////////////////////////////////////////////
#if DEBUG>4 // Level-5 DEBUG (SHOW TODE EEPROM DATA)
  Serial.print("TodeAddr:    ");Serial.println(TodeAddr);
  Serial.print("TodeSize:    ");Serial.println(TSize);
  Serial.print("TodeEndAddr: ");Serial.println(TodeEndAddr);
  Serial.print("ConfigVer:   ");Serial.println(ConfigVer);
#endif
#if DEBUG>5 // Level-6 DEBUG (DUMP EEPROM)
  int Rb = 0;
  for ( int b = 0; b < TSize; b++) {
    if ( b!=0 && b % 10 == 0) Serial.println("");
    Rb = EEPROM.read(b);
    Serial.print("(");if (b<10) Serial.print("0"); if (b<100) Serial.print("0");
    Serial.print(b);Serial.print(")");Serial.print("x");
    if (Rb < 15) Serial.print("0"); Serial.print(Rb, HEX); Serial.print("=");
    if (Rb < 10) Serial.print("0"); if (Rb < 100) Serial.print("0"); Serial.print(Rb); Serial.print("=");
    if (Rb > 31 && Rb < 127) { Serial.print(char(Rb)); } else { Serial.print("?"); }; Serial.print(" "); 
  } Serial.println("");
#endif
////////////////////////////////////////////////////

  if ( TSize == 0xFF || TSize < EMO_1STDEVICE || TSize > 100 ) {
    DBERRORL(("EEPROM TodeSize Failure or No Devices"));
  } else {
    int DevAddr = TodeAddr + EMO_1STDEVICE;            // Start at 1st Device
    int DevSize = 0;                                    // Working Variable

    while (DevAddr < TodeEndAddr) {                      // Stop @ End of Tode-Block //(12<12)=No-Devices
      DevSize = EEPROM.read(DevAddr + EMO_DEVSIZE);      // Device Size is offset + 0
      switch (EEPROM.read(DevAddr + EMO_DEVTYPE)) {      // Device Type is offset + 1
/*
        case DT_ONOFF:
          DBINFOAL(("DT_ONOFF@"), (DevAddr));
          //Add(new OnOff( DevAddr, (TodeAddr == 0), true));
          break;
        default:
          DBINFOAL(("DT UNSUPPORTED@"), (DevAddr));
          break;*/
                
      }
      DevAddr = DevAddr + DevSize;                      // GoTo Next Device
    }
  }

  if (TodeAddr == EMC_THISTODE) {

  }
}
//------------------------------------------------------------------------------------------------------
MenuList* Tode::AddDevice(int _DT_Type) {

/*
  if (_DT_Type == DT_ONOFF) {
    OnOff* pItem = new OnOff( TodeEndAddr, (TodeAddr == 0));
    Add(pItem);
    TodeEndAddr = TodeEndAddr + EEPROM.read(TodeEndAddr);          // 'new' writes device size into eeprom
    EEPROM.update(TodeAddr + EMO_TODESIZE, TodeEndAddr);        // Update the Tode Size

    ConfigVer++; if (ConfigVer > 255) ConfigVer = 0;            // Change Tode Version
    EEPROM.update(TodeAddr + EMO_TODEVER, ConfigVer);          // Update Tode Version

    return pItem->SubList;
  }
  */
}//-----------------------------------------------------------------------------------------------------
void Tode::SendRF_Config(int _RFTarget) {
//-----------------------------------------------------------------------------------------------------
  Serial1.print(_RFTarget);
  Serial1.print(0x17);
  Serial1.print(EEPROM.read(0));
  for (int addr = 1; addr < EndAddr(); addr++) {
    Serial1.print(EEPROM.read(addr));
  }

}//-----------------------------------------------------------------------------------------------------
int Tode::RFAddr() {
//-----------------------------------------------------------------------------------------------------
  return EEPROM.read(TodeAddr+EMO_RFADDR);
}
void Tode::RFAddr(int _RFAddr) {
  return EEPROM.update(TodeAddr+EMO_RFADDR, _RFAddr);
}//-----------------------------------------------------------------------------------------------------

//////
#endif
