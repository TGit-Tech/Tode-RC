/******************************************************************************************************************//**
 * @file    miDev.h
 * @brief   **ITEM** Tode Device Drivers
 * @todo
 *  - Fix PinSelect in Devices
 *********************************************************************************************************************/
#ifndef _MIDEV_H
#define _MIDEV_H

#include "miHdw.h"
#include "lib/EEMap.h"
/******************************************************************************//**
 * @defgroup DT [DT] Device-Type enumeration
 * @{
 *********************************************************************************/
// 0x[7] Device Types
#define DT_RW_ONOFF   0x7E    ///< On/Off Switching Device
#define DT_RO_ONOFF   0x7D    ///< On/Off Monitoring Device
#define DT_RO_PRESS   0x7C    ///< Pressure Device
#define DT_RO_TEMP    0x7B    ///< Temperature Device
#define DT_RO_DIST    0x7A    ///< Distance Sensing Device
///@}
/******************************************************************************************************************//**
 * @class   OnOff
 * @brief   **DEVICE** Digital On/Off *Value* Control and Local Settings; inherits MenuValue.
 *********************************************************************************************************************/
class OnOff : public Device {
  public:
    OnOff(byte _TodeIndex, byte _RFID, HdwSelect* _Hardware=0);
    
    virtual int     IOValue() override;                                           // Stored on Tode
    virtual void    IOValue(int _Value) override;
      
};
//_____________________________________________________________________________________________________________________
#endif
