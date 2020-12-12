/**********************************************************************************************//**
 * @file    DevLib.h
 * @brief   Library that implements generic Device Control structures and IO-HDW Board Options.
 *************************************************************************************************/
#ifndef _DEVLIB_H
#define _DEVLIB_H

#include "Constants.h"
#include "MenuLib.h"
#include <EEPROM.h>

// Digitas Bit
//  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0   [DIO]
//  63  62  61  60  59  58  57  56  55  54  53  52  51  50  49  48  47  46  45  44  43  42  41  40  39  38  37  36  35  34  33  32  [AIO]
//                                                                                              72  71  70  69  68  67  66  65  64  [XIO]  
static unsigned long DIO_UsedPins = 0x0;    ///< Bit-Marked assigned pins
static unsigned long AIO_UsedPins = 0x0;    ///< Bit-Marked assigned pins
static byte XIO_UsedPins = 0x0;             ///< Bit-Marked assigned pins

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
 * @class   PinSelect
 * @brief   **ITEM** adds \ref IOHDW specific On-Display Pick-A-Pin to MenuValue.
 *************************************************************************************************/
class PinSelect : public MenuValue {
  public:
    PinSelect(const char* _CName, byte _IOHDW = IOHDW_WING, bool _NameSettable = false);
    
    virtual byte    Navigate(byte _Key, byte _Row=0) override;    ///< Keypad Navigate by \ref KEY
    virtual byte    ValueNav(byte _Key, byte _Row=0) override;   ///< Value Navigate
    virtual int     Value();                                      ///< GET Item Value
    virtual void    Value(int _Value);                            ///< SET Item Value
    
  private:
    byte IOHDW = 0;
    int Pin = -1; 
    int SetTo = -1;
    int ChangeSetTo(byte _Key);
    unsigned long DIOWing_Pins = 0x00000000;    // P31[31] to P0[0] None of D0 to D30 is available
    unsigned long AIOWing_Pins = 0xAA002002;    // P63[31] to D32[0] need D45, A1, A3, A5, A7, A9
    byte XIOWing_Pins = 0x0A;                   // P72[31] to P64[0] need A11, A13
    
};
/**********************************************************************************************//**
 * @class   DeviceValue
 * @brief   **ITEM** adds \ref IOHDW specific On-Display Pick-A-Pin to MenuValue.
 *************************************************************************************************/
class DeviceValue : public MenuValue {
  public:
    DeviceValue(int _EETargetTode, byte _DevID);

  protected:
    bool          IsLocal=false;
    int           EEDevAddr = -1;
    int           EETargetTode = -1;
    byte          DevID = -1;
    MenuList*     Settings;
    MenuValue*    IOPin;
};
/*
 * SETTINGS
 *  Device Name
 *  OUT PIN (Drive)
 *  IN PIN (Feedback)
 *  LOCAL SERVICE ROUTINES
 *  LOCAL CALCULATORS?
 *  
 */
#endif
