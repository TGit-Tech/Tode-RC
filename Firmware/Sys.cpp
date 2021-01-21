/******************************************************************************************************************//**
 * @file Sys.cpp
 * @brief Ref.h
 *********************************************************************************************************************/
#ifndef _MAIN_CPP
#define _MAIN_CPP
#include "Sys.h"

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
//#####################################################################################################################
Sys::Sys():
  Navigator() {                                                                                   DBINITL(("Sys::Sys"))

  RF = new E32Radio(/*M0*/22, /*M1*/20, /*TX*/18, /*RX*/19, /*AUX*/21);   // Initialize RF
  SetupMenu = this->Add(new MenuList("Setup"));                           // Setup
  ThisTode = this->NewTode(0);                                            // Create ThisTode adds to 'this'
    
  RF->Mode(E32_SLEEPMODE);
  DBINFOAL(("Sys::Sys Radio Address: "), (RF->Address(),HEX))
  DBINFOAL(("Sys::Sys Radio Freq[mhz]: "), (RF->Frequency()))
  DBINFOAL(("Sys::Sys Radio Power[db]: "), (RF->TxPower()))
  RF->Mode(E32_NORMMODE);
  
  BuildSetupMenu();

  // Get ThisTode RFAddr if not same as RF's Update EEPROM
  if ( RF->Address() != ThisTode->RFAddr() ) { 
    DBINFOAL(("Sys::Sys RF->RadioAddress() != ThisTode->RFAddr()"),(ThisTode->RFAddr(),HEX))
    ThisTode->RFAddr(RF->Address()); 
  } else { DBINFOL(("Sys::Sys RF->Address() == ThisTode->RFAddr()")) }

  // Load Todes from EEPROM
  for ( int i=1; i<AEB_MAXTODES; i++ ) {
    if ( EEPROM.read(i*AEB_TODEALLOC) != BNONE ) {  
      DBINFOAL(("Sys::Sys Tode@EEPROM: "),(i*AEB_TODEALLOC)) 
      //this->NewTode(i);
      DelTodesList->Add(new MenuName(this->NewTode(i)->Title(), NAVDELTODE));  // Need List of Lists or use Name?
      
    } else { DBINFOAL(("Sys::Sys NoTode@EEPROM: "),(i*AEB_TODEALLOC)) }
  }
  
  DBINFOAL(("*** Free Memory *** = "),(freeMemory()))
  
}
//-----------------------------------------------------------------------------------------------------
MenuList* Sys::NewTode(byte _Index) {                     DBENTERAL(("Sys::NewTode(Index): "),(_Index))
  if ( _Index>AEB_MAXTODES ) { DBERRORAL(("Sys::NewTode(Index): Index>AEB_MAXTODES"),(_Index)) return 0; }
  if ( TodesPtr[_Index]!=0 ) { DBERRORAL(("Sys::NewTode(Index): TodesPtr[_Index]!=0"),(_Index)) return 0; }
  TodesPtr[_Index] = this->Add(new Tode(_Index));
  TodesPtr[_Index]->EELoadDevices();                  // Have to call after Add for RF
  return TodesPtr[_Index];
}
//-----------------------------------------------------------------------------------------------------
byte Sys::NewTode() {                                                     DBENTERL(("Sys::NewTode()"))
  // Find a Free Index
  byte i=1; while ( i<10 && TodesPtr[i] != 0 ) { i++; }
  if ( i==10 ) { DBERROR (("Sys::NewTode() OUT OF TODE MEM")) return BNONE; }
  NewTode(i);
  return i;
}
//---------------------------------------------------------------------------------------------------------------------
Tode* Sys::RFTode(unsigned int RFAddress, bool Create) {  DBENTERAAL(("Sys::RFTode(GET,CREATE): "),(RFAddress,HEX),(Create))
  
  int FreeIndex = 10;
  for ( int idx=0; idx<10; idx++ ) {                  // Search for Tode
    if ( TodesPtr[idx]!=0 ) { 
      if ( TodesPtr[idx]->RFAddr() == RFAddress ) return TodesPtr[idx]; 
    } else {
      if ( idx < FreeIndex ) FreeIndex = idx;
    }
  }
  // Nothing Found - then Create it at 'FreeIndex'
  if ( Create ) {
    if ( FreeIndex>=AEB_MAXTODES ) { DBERRORAL(("Sys::RFTode FreeIndex>=AEB_MAXTODES"),(FreeIndex)) return 0; }
    TodesPtr[FreeIndex] = this->Add(new Tode(FreeIndex));
    DBINFOAL(("Sys::RFTode *NEW* Tode(): "),(FreeIndex))
    TodesPtr[FreeIndex]->RFAddr(RFAddress);                 // Write the RFAddress
    return TodesPtr[FreeIndex];
  }
  return 0;
}
//-----------------------------------------------------------------------------------------------------
// WARNING! : In order to preserve internal object Items/List must be added in hierarcy order.
//-----------------------------------------------------------------------------------------------------
void Sys::BuildSetupMenu() {

  // 1. TodeName
  //MenuEEValue(const char* _CName, int _EEValAddress, byte _ValueType)
  ThisTode->TodeName = SetupMenu->Add(new MenuName(ThisTode->EEAddress()+EMO_TODENAME, true));  // 1. TodeName

  // 2. Radio . RadioSettings
  RadioSettings = new MenuList("Radio");
  SetupMenu->Add(new MenuName("Radio", RadioSettings));                                         // RADIO - Add supplies RF
  RadioSettings->Add(new MenuEEValue("SecNet", EMC_SECNET, VTRW+VTBYTE+VTHEX+VTDIG));
  RadioSettings->Add(new RadioAddress());
  RadioSettings->Add(new RadioFrequency());
  RadioSettings->Add(new RadioTxPower());
  RFPCConn = RadioSettings->Add(new RadioPCConn());

  // 3. Del Device
  if (ThisTode==0) { DBERRORL(("Sys::BuildSetupMenu ThisTode==0")) }                            // 2.2 ThisTode Devices
  else {
    SetupMenu->Add(new MenuName("Devices", DeviceList = new MenuList("Del Device")));                                                                                        
    for ( int i=0; i<30; i++ ) {                                                                //    *doesn't exit nameset*
      if ( ThisTode->Devices[i]!=0 ) { DeviceList->Add(ThisTode->Devices[i]); }                 //    Add DeviceList
    }
  }

  // 4. Del Todes
  SetupMenu->Add(new MenuName("Todes", DelTodesList = new MenuList("Del Tode")));
  
  // 5. Add Device
  //SetupMenu->Add(new MenuName("Devices", DeviceList = new MenuList("Devices")));                // 2. Devices
  SetupMenu->Add(new MenuName("Add Device", AddDeviceList = new MenuList("Add Device")));      // 2.1 Add Device
  AddDeviceList->Add(new MenuName("OnOff",     DT_RW_ONOFF));                                   //  2.1.1 OnOff
  AddDeviceList->Add(new MenuName("Pressure",  DT_RO_PRESS));                                   //  2.1.2 Pressure
  AddDeviceList->Add(new MenuName("Temp",      DT_RO_TEMP));                                    //  2.1.3 Temp
  AddDeviceList->Add(new MenuName("Distance",  DT_RO_DIST));                                    //  2.1.4 Distance

  // 6. Add Tode
  SetupMenu->Add(AddATode = new AddTode());

  // 7. IO-Hdw
  SetupMenu->Add(ThisTode->Hardware);                                                           // 2. IO-HDW (Created in ThisTode)

  // 8. Firmware
  SetupMenu->Add(new MenuName(FIRMWARE));                                                       // FIRMWARE

}
//-----------------------------------------------------------------------------------------------------
byte Sys::Loop(byte _FinalKey) {

  RFLoop();
  
  // [Specific] -----------------------------------------------
  if ( _FinalKey==0xFF ) return _FinalKey;
  DBINFOAL(("Sys::Loop SPECIFIC FinalKey = "),(_FinalKey,HEX))
  // Should we call Loop() in Every Tode?
  
  // Add Device (KEYS in miDev.h)
    //#define DT_RW_ONOFF   0x7E    ///< On/Off Switching Device
    //#define DT_RO_ONOFF   0x7D    ///< On/Off Monitoring Device
    //#define DT_RO_PRESS   0x7C    ///< Pressure Device
    //#define DT_RO_TEMP    0x7B    ///< Temperature Device
    //#define DT_RO_DIST    0x7A    ///< Distance Sensing Device

  if ( 0x7A <= _FinalKey && _FinalKey <= 0x7E ) {
    int BeforeMEM = freeMemory();
    //DeviceList->Add( ThisTode->NewDevice(_FinalKey) );  // Add the Requested Device

    int AfterMEM = freeMemory();
    DBINFOAL(("Object Size (kb)-> "), (BeforeMEM-AfterMEM))
    DBINFOAL(("Free Memory (kb)-> "), (AfterMEM))
  
    // return to Devices List
    this->Navigate( NAVKEYLEFT );
    return BNONE;
  }
  
}
//-----------------------------------------------------------------------------------------------------
void Sys::RFLoop() {
  // Receive RF Data
  if ( RF==0 ) { DBERRORL(("Sys::RFLoop RF==0")) return 0; }
  if ( RFPCConn!=0 ) { if ( RFPCConn->Value()==1 ) { RFPCConn->Loop(); return;} }   // Loop for Radio->PC Connection 
                                                                                    // Normal Conn Down 
  if ( RF->PacketAvailable() ) { 
    
    if ( RF->Packet->Type() == PKT_GETCONFIG ) {
      DBINFOL(("Sys::RFLoop RF->Packet->Type() == PKT_GETCONFIG"))
      
      //TxPacket(byte _SecNet, byte _Type, int _ToRF, byte _Ver=BNONE, byte _DevRFID=BNONE, int _Value = INONE)
      TxPacket Pkt(EEPROM.read(EMC_SECNET), PKT_GOTCONFIG, RF->Packet->FromRF(), ThisTode->Version() );
      Pkt.AddTodeConfig( ThisTode->EEAddress() );
      RF->Send(&Pkt);
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    } else if ( RF->Packet->Type() == PKT_GOTCONFIG ) {
      
      Tode* td = RFTode( RF->Packet->FromRF(), true );
      DBINFOAL(("Sys::RFLoop PKT_GOTCONFIG for TodeIndex: "),(td->TodeIndex))
      RF->Packet->SaveTodeConfig( td->EEAddress() );
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    } else if ( RF->Packet->Type() == PKT_SETVAL ) {
      DBINFOL(("Sys::RFLoop RF->Packet->Type() == PKT_SETVAL"))
      
      // RF command a Value Set on This Tode
      // 1. Check Version
      if ( ThisTode == 0 ) { DBERRORL(("Sys::RFLoop PKT_SETVAL ThisTode == 0")) return; }
      if ( ThisTode->Version() != RF->Packet->Version() ) {
          DBERRORAAL(("Sys::RFLoop PKT_SETVAL ThisTode->Version() != RF->Packet->Version(): "),
                                             (ThisTode->Version()), (RF->Packet->Version()))
          return;
      }
      // 2. Get Device by RFID & Set the Value
      int rfid = RF->Packet->RFID();
      if ( 0>rfid || rfid>=AEB_MAXDEVICES ) { DBERRORAL(("Sys::RFLoop PKT_SETVAL 0>rfid || rfid>=AEB_MAXDEVICES: "),(rfid)) return; }
      Device* dev = ThisTode->Devices[RF->Packet->RFID()];
      if ( dev==0 ) { DBERRORL(("Sys::RFLoop PKT_SETVAL dev==0")) return; }
      DBINFOAL(("Sys::RFLoop PKT_SETVAL dev->Value(SET): "),(RF->Packet->SetValue()))
      dev->Value(RF->Packet->SetValue());
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    } else if ( RF->Packet->Type() == PKT_GETVALS ) {
      DBINFOL(("Sys::RFLoop RF->Packet->Type() == PKT_GETVALS"))
      if ( ThisTode == 0 ) { DBERRORL(("Sys::RFLoop PKT_GETVALS ThisTode == 0")) return; }
      
      // 1. Append every ThisTode Device Value to Packet and Send
      TxPacket Pkt(EEPROM.read(EMC_SECNET), PKT_GOTVALS, RF->Packet->FromRF(), ThisTode->Version() );
      for ( int i=0; i<AEB_MAXDEVICES; i++ ) {
        if ( ThisTode->Devices[i]!=0 ) {
          if ( ThisTode->Devices[i]->RFID<AEB_MAXDEVICES ) {
            Pkt.AddValue(ThisTode->Devices[i]->RFID, ThisTode->Devices[i]->Value() ); }
        }
      }
      RF->Send(&Pkt);
    //'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    } else if ( RF->Packet->Type() == PKT_GOTVALS ) {
      DBINFOL(("Sys::RFLoop RF->Packet->Type() == PKT_GOTVALS"))

      // 1.  Which Tode are these values for?
      Tode* td = RFTode( RF->Packet->FromRF() );
      if ( td==0 ) { DBERRORL(("Sys::RFLoop PKT_GOTVALS NO-TODE td==0: ")) return; }      
      // 2.  Record the Values in the Devices
      for ( int i=0; i<AEB_MAXDEVICES; i++ ) {
        if ( td->Devices[i]!=0 ) {
          td->Devices[i]->RxValue( RF->Packet->Value( td->Devices[i]->RFID ) );
          DBINFOAL(("Sys::RFLoop PKT_GOTVALS RxValue(RFID): "),(td->Devices[i]->RFID))
        }
      }
      // 3. Update the Dispaly
      Navigate( NAVDSPLIST );
    }
    
    // Delete Packet after Processing
    delete(RF->Packet); RF->Packet = 0;
  }
  
}
//_____________________________________________________________________________________________________________________
#endif
