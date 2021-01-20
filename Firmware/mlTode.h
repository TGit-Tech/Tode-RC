/******************************************************************************************************************//**
 * @file    mlTode.h
 * @brief   **LIST** Extends MenuList for a Tode and it's Devices(s)
 *********************************************************************************************************************/
#ifndef _MLTODE_H
#define _MLTODE_H

#include "miDev.h"
/******************************************************************************************************************//**
 * @class   Tode
 * @brief   **LIST** of Devices per Tode
 *********************************************************************************************************************/
class AddTode : public MenuValue {
  public:
    AddTode();
    virtual int           Value();                                        ///< GET Item Value
    virtual void          Value(int _Value);                              ///< SET Item Value
};
/******************************************************************************************************************//**
 * @class   Tode
 * @brief   **LIST** of Devices per Tode
 *********************************************************************************************************************/
class Tode : public MenuList {
  public:
    Tode(byte _TodeIndex);                                      ///< EEPROM Address of Tode Configuration
    
    virtual const char*   Title() override;                     ///< Points to TodeName->Name()

    virtual MenuItem*     NewDevice(byte _DTKey);               ///< Creates & Adds a New Device
    virtual MenuItem*     AddDevice(byte _DTKey, byte _RFID);   ///< Menu add Device using \ref KEY
    virtual void          EELoadDevices();
    
    virtual unsigned int  RFAddr();                             ///< GET EEPROM RF-Address
    virtual void          RFAddr(unsigned int _RFAddr);         ///< SET EEPROM RF-Address
    virtual byte          Version();                            ///< GET Tode's Configuration Ver
    virtual void          Version(byte _Version);               ///< SET Tode's Configuration Ver
    virtual bool          IsLocal();                            ///< GET (EEAddress == 0) set in Constructor
    virtual int           EEAddress();                          ///< GET EEPROM Address of This Tode (Calc by TodeIndex)
            byte          TodeIndex = BNONE;
            
    MenuName*             TodeName=0;                           ///< TodeName Menu-Item
    Device*               Devices[AEB_MAXDEVICES] = {0};        ///< Device Pointers - Index is RFID
    HdwSelect*            Hardware = 0;                         ///< This Tode's Hardware Attached Menu-Item
    
    
  protected:
    
    
  private:
    bool            bIsLocal = false;
    byte            yVersion = 0;

};
//_____________________________________________________________________________________________________________________
#endif
