/******************************************************************************************************************//**
   @file Devices.h
   @brief Device Support Classes.
    - EEPROM Organization of Devices
    + byte[0]   = Size
    + byte[1]   = Type
    - Device Features
    + ALL Device Constructors will WRITE their byte-size into EEPROM at 'EAddr' used later for Tode-Sizing.
   @authors
      TGit-Tech           2/2019       Original
 **********************************************************************************************************************/
#ifndef _DEVICES_H
#define _DEVICES_H
#include <EEPROM.h>

#include "Constants.h"
#include "MenuLib.h"

/**********************************************************************************************//**
 * @class   SetNet
 * @brief   On-Demand initialized Item-Object Tool used to set Textual Names on a new screen.
 *************************************************************************************************/
class SetNet : public MVDigitSet {
  public:
    SetNet(const char* _Name, int _VAddr);
    
    virtual int         Value() override;
    virtual void        Value(int _Value) override;
    
  private:
    int                 VAddr=-1;
};
/**********************************************************************************************//**
 * @class   AddDevice
 * @brief   
 *************************************************************************************************/
class AddDevice : public MenuName {
  public:
    AddDevice(const char* _CName, byte _DeviceToAdd, MenuList* _SubList=0);
   
    byte Navigate(byte _Key, byte _Row=0) override;
    
  private:
    byte      DeviceToAdd=0;
};
/**********************************************************************************************//**
 * @class   OnOffSwitch
 * @brief   On-Demand initialized Item-Object Tool used to set Textual Names on a new screen.
 *************************************************************************************************/
class OnOff : public MVOptions {
  public:
    OnOff(int _NAddr, bool _IsLocal=false);
    
    virtual int   Value();                       // Stored on Tode
    virtual void  Value(int _Value);
    virtual int   IOPin();
  private:
    bool          IsLocal=false;
    MenuItem*     OutPin = 0;
    
};
#endif
