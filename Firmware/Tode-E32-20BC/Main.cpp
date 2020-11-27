/******************************************************************************************************************//**
 * @file Main.cpp
 * @brief Top-Level System Operations Class for the Tode RF IoT Ecosystem
 *    This class includes
 *    1.  Defaults as a Link-List of External Devices (by Tode Inheritance)
 *    2.  SystemMenu Link-List of LOCAL Control (Add/Delete Devices + Add/Del Tode + SetWhatName/UID)
 **********************************************************************************************************************/
#ifndef _MAIN_CPP
#define _MAIN_CPP
#include "Main.h"

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__
int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

//#####################################################################################################
Main::Main(Tode* _ThisTode) {                                        DBINITL(("Main::Main"))
  ThisTode = _ThisTode;

  // Set ThisTode's E32-RF-Address
  EEPROM.update(EMC_THISTODE + EMO_RFADDR, lowByte(E32ADDR));
  EEPROM.update(EMC_THISTODE + EMO_RFADDR + 1, highByte(E32ADDR));

  // Build an Add Device List for the System Menu
  AddDeviceList = new MenuList("AddDevice");
  AddDeviceList->Add(new AddDevice("OnOff",     DT_ONOFF));
  AddDeviceList->Add(new AddDevice("Pressure",  DT_PRESS));
  AddDeviceList->Add(new AddDevice("Temp",      DT_TEMP));
  AddDeviceList->Add(new AddDevice("Distance",  DT_DIST));
   
  // Build the Setup System-Menu to 'Setup' the Local System.
  SystemMenu = new MenuList("Setup");
  SystemMenu->Add(new MenuName(FIRMWARE));
  SystemMenu->Add(new SetNet("SecNet", EMC_SECNET));
  ThisTode->TodeName = SystemMenu->Add(new MenuName(EMC_THISTODE+EMO_TODENAME, AEB_TODENAME, true, "Set Name"));
  SystemMenu->Add(new MenuName("Add Device", AddDeviceList));             // List of AllDevices with Pin-SetWhatability
  SystemMenu->Add(new MenuName("Del Device"));                            // List of Item Devices with Delete-Item
  SystemMenu->Add(new MenuName("Add Tode"));                              // Be a List or HEX Entry?
  SystemMenu->Add(new MenuName("Del Tode"));                              // List of Todes with Ability to Delete-List
  
  // Add the Items to the Navigator
  this->Add(SystemMenu);
  this->Add(ThisTode);
  DBINFOAL(("*** Free Memory *** = "),(freeMemory()))
}
//-----------------------------------------------------------------------------------------------------

byte Main::OnRetKey(byte _Key) {
//--------------------------------------------------------------------------------------------
  if (_Key>0xBF) return _Key;
  DBINFOAL(("*** Free Memory *** = "),(freeMemory()))

  // Add the Requested Device
  if (_Key == DT_ONOFF) {
    DBINFOL(("ThisTode->Add(new OnOff)"))
    ThisTode->AddDevice(_Key);
    /*
    MenuList* Parameters = ThisTode->AddDevice(_Key);
    if (Parameters != 0) {
      this->CurrList = Parameters;
      this->CurrList->Display();
    }
    */
    DBINFOAL(("*** Free Memory *** > "), (freeMemory()))
    return KEYNONE;
  }
  return _Key;
}
//////
#endif
