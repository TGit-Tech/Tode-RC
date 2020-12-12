/******************************************************************************************************************//**
   @file    Devices.h
   @brief   Device Support Classes.
    - EEPROM Organization of Devices
   @authors
      TGit-Tech           2/2019       Original
 **********************************************************************************************************************/
#ifndef _DEVICES_H
#define _DEVICES_H
#include <EEPROM.h>

#include "Constants.h"
#include "DevLib.h"

/**********************************************************************************************//**
 * @class   OnOff
 * @brief   **DEVICE** Digital On/Off *Value* Control and Local Settings; inherits MenuValue.
 *************************************************************************************************/
class OnOff : public DeviceValue {
  public:
    OnOff(int _EETargetTode, byte _DevID);

    virtual int   Value() override;                       // Stored on Tode
    virtual void  Value(int _Value) override;
    //virtual byte  DevType(byte _DTPKey = DTP_DEVTYPE) override;
    
};
#endif
