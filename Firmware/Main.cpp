/******************************************************************************************************************//**
 * @file Main.cpp
 * @brief Ref.h
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
// Main
//#####################################################################################################
Main::Main() {                                        DBINITL(("Main::Main"))

  // Create a ThisTode and RFRadio Object
  ThisTode = new Tode(NewTodeEEA());
  RFRadio = new E32Radio();

  DBINFOAL(("Main::Main Radio Address: "), (RFRadio->Address()))
  DBINFOAL(("Main::Main Radio Freq[mhz]: "), (RFRadio->Frequency()))
  DBINFOAL(("Main::Main Radio Power[db]: "), (RFRadio->TxPower()))
  RFRadio->Mode(E32_NORMMODE);
  
  // Build Menu's
  DeviceList_Init();
  Radio_Init();
  SetupMenu_Init();

  // Add the Lists 'this' Main.System : Navigator
  this->Add(SetupMenu);                                    ///< Navigator List #1
  this->Add(ThisTode);                                     ///< Navigator List #2

  // Get ThisTode RFAddr if not same as RFRadio's Update EEPROM
  if ( RFRadio->Address() != ThisTode->RFAddr() ) { 
    DBINFOAL(("Main::Main() RFRadio->RadioAddress() != ThisTode->RFAddr()"),(ThisTode->RFAddr()))
    ThisTode->RFAddr(RFRadio->Address()); 
  }
  
  //E32Radio = new PeerIOSerialControl(1, Serial1, Serial);
  //E32Radio->Timeout(2000);
  DBINFOAL(("*** Free Memory *** = "),(freeMemory()))
  
}
//-----------------------------------------------------------------------------------------------------
void Main::SetupMenu_Init() {
  
  SetupMenu = new MenuList("Setup");
  ThisTode->TodeName = SetupMenu->Add(new MenuName(ThisTode->EAddr()+EMO_TODENAME, AEB_TODENAME, true, "Name"));
  SetupMenu->Add(new MenuName("Devices", Devices));             // Link *AddDevice* SubList
  SetupMenu->Add(new MenuName("Todes"));                        // Be a List or HEX Entry?
  SetupMenu->Add(new MenuName("IO HDW"));
  SetupMenu->Add(new MenuName("Radio", RadioSettings));
  SetupMenu->Add(new SetNet("SecNet", EMC_SECNET));
  SetupMenu->Add(new MenuName(FIRMWARE)); 
   
}
//-----------------------------------------------------------------------------------------------------
void Main::DeviceList_Init() {
  Devices = new MenuList("Devices");
  AddDeviceList = new MenuList("Add Device");
  AddDeviceList->Add(new MenuNameKey("OnOff",     DT_RW_ONOFF));
  AddDeviceList->Add(new MenuNameKey("Pressure",  DT_RO_PRESS));
  AddDeviceList->Add(new MenuNameKey("Temp",      DT_RO_TEMP));
  AddDeviceList->Add(new MenuNameKey("Distance",  DT_RO_DIST));

  Devices->Add(new MenuName("Add Device", AddDeviceList));
}
//-----------------------------------------------------------------------------------------------------
void Main::Radio_Init() {
  RadioSettings = new MenuList("Radio");
  E32PC = RadioSettings->Add(new E32PCConn("PC Connect"));
  //RadioSettings->Add(new MenuValue("Freq"));
  //RadioSettings->Add(new MenuValue("Power"));
  //RadioSettings->Add(new MenuValue("Addr"));
  //RadioSettings->Add(new MenuValue("Cannel"));
}
//-----------------------------------------------------------------------------------------------------
byte Main::Loop(byte _FinalKey) {

  //Call Loop in every Tode
  Tode* Curr = FirstList;
  while ( Curr != 0 ) {
    Curr->Loop();
    Curr=Curr->NextList;
  }
  
  //Call System Item Loops that Need Them
  E32PC->Loop();
  RFRadio->Loop();

  // EXIT if Last Navigate Returna non-add KEY
  if (_FinalKey>0xBF) return _FinalKey;

  DBINFOL(("Main::FinalKey"))
  int BeforeMEM = freeMemory();
  Devices->Add( ThisTode->AddDevice(_FinalKey) );      // Add the Requested Device
  int AfterMEM = freeMemory();
  DBINFOAL(("Object Size (kb)-> "), (BeforeMEM-AfterMEM))
  DBINFOAL(("Free Memory (kb)-> "), (AfterMEM))
  
  // return to Devices List
  this->Navigate( KEYLEFT );
  return KEYNONE;
  
}
//-----------------------------------------------------------------------------------------------------
int Main::NewTodeEEA() {
  iNewTodeEEA = iNewTodeEEA + AEB_TODEALLOC;
  DBINFOAL(("Main::NewTodeEEA = "), (iNewTodeEEA - AEB_TODEALLOC))
  return iNewTodeEEA - AEB_TODEALLOC;
}
//////
#endif
