/**********************************************************************************************//**
 * @file    MenuLib.h
 * @brief   Library to expand MenuItem class for specific usage.
 *          Adds the *SetNameTool* class.
 *************************************************************************************************/
#ifndef _MENULIB_H
#define _MENULIB_H

#include "Menu.h"
/**********************************************************************************************//**
 * @class   SetNameTool
 * @brief   On-Demand initialized Tool-Object for setting Textual Names on a seperate screen.
 *************************************************************************************************/
class SetNameTool {
  public:
    SetNameTool(DSPCLASS* _Display, const char* _Title, byte _Size);
    virtual byte  Navigate(byte _Key, byte _Row=0);
    char          SetToName[AEB_MAX];                                 ///< Set-To Array[] Variable
  private:
    DSPCLASS*     Display=0;
    byte          Type=0;
    byte          Size=0;
    const char*   Title=0;
    int           SetTo = SS_TITLE;         ///< Set-To Integer Variable
    byte          SetIdx = 0;               ///< Set-To Array[] current Index
};
/**********************************************************************************************//**
 * @class   MenuName
 * @brief   **ITEM** adds *NAME* to MenuItem stored in either MEM or EEPROM determined by Constructor.
 *************************************************************************************************/
class MenuName : public MenuItem {
  public:
    MenuName(const char* _CName, MenuList* _SubList=0);                                   ///< MEM Name Constructor
    MenuName(int _NAddr, byte _NSize, bool _NameSettable=false, const char* _TLine=0);    ///< EEPROM Name Constructor

    //_TLine is used by Tode Name Set for a Named-Name

    virtual byte          Navigate(byte _Key, byte _Row=0);     ///< Keypad Navigate by \ref KEY
    virtual const char*   Name();                               ///< GET Item Name
    virtual void          Name(const char* _Name);              ///< SET Item Name
    
  protected:
    virtual byte          NameNav(byte _Key, byte _Row=0);      ///< NAME Navigate
    
  private:
    const char*           TLine = 0;
    const char*           CName = 0;            ///< Constant "Name" pointer
    char                  FName[AEB_MAX];       ///< C-Style Name Char[] for Name set/get.
    bool                  NameSettable = false;    ///< NAME Settable?
    int                   NAddr = -1;           ///< NAME is at EEPROM Addr...
    byte                  NSize = 0;            ///< NAME is byte-size in EEPROM
    SetNameTool*          SetName = 0;          ///< SetNameTool object pointer
};
/**********************************************************************************************//**
 * @class   MenuNameKey
 * @brief   **ITEM** injects \ref KEY when KEYOKAY is pressed on Name (Used to add devices).
 *************************************************************************************************/
class MenuNameKey : public MenuName {
  public:
    MenuNameKey(const char* _CName, byte _NameKey, MenuList* _SubList=0);

    virtual byte          Navigate(byte _Key, byte _Row=0) override;     ///< Keypad Navigate by \ref KEY
    
  private:
    byte                  NameKey = KEYNONE;
};
/**********************************************************************************************//**
 * @class   MenuValue
 * @brief   **ITEM** adds *VALUE* to MenuName for a Name->Value Pair + Number-Naming ability.
 *************************************************************************************************/
class MenuValue : public MenuName {
  public:
    MenuValue(const char* _CName, int _VNumBase = DEC);                                   ///< CONST Name Constructor
    MenuValue(int _NAddr, byte _NSize, bool _NameSettable=false, int _VNumBase = DEC);    ///< EEPROM Name Constructor

    virtual byte          Navigate(byte _Key, byte _Row=0) override;      ///< Keypad Navigate by \ref KEY
    virtual int           Value();                                        ///< GET Item Value
    virtual void          Value(int _Value);                              ///< SET Item Value
  
  protected:
    virtual byte          ValueNav(byte _Key, byte _Row=0);               ///< Value Navigate
    int                   VNumBase=DEC;                                   ///< Value Number-Base
    virtual void          ValueRange(int _RangeMin, int _RangeMax);       ///< Value Range

    struct NumberName     { int Number = -1; const char* Name = 0; NumberName* Next = 0; };   ///< Text-Name Numbers
    virtual void          SetNumberName(int _Value, const char* _NName);                      ///< Set a Text-Name for certain NUMBERS
    virtual const char*   GetNumberName(int _Value);                                          ///< Search if a Number has a Text-Name

  private:
    const char*           Units = 0;
    int                   ValRangeMax = 32767;
    int                   ValRangeMin = -1;
    NumberName*           FirstNumberName = 0;    ///< Link-List pointer for NumberName
    NumberName*           CurrNumberName = 0;     ///< Link-List pointer for NumberName
};
/**********************************************************************************************//**
 * @class   MVDigitSet
 * @brief   **ITEM** adds On-Display *Per-Digit* SET feature to MenuValue.
 *************************************************************************************************/
class MVDigitSet : public MenuValue {
  public:
    MVDigitSet(const char* _CName, int _RangeMin=0x0000, int _RangeMax=0xFFFF, int _VNumBase = DEC);
    MVDigitSet(int _NAddr, byte _NSize, bool _NameSettable=false, int _RangeMin=0x0000, int _RangeMax=0xFFFF, int _VNumBase = DEC);
    
  protected:
    virtual byte  ValueNav(byte _Key, byte _Row=0) override;           ///< Value Navigate
    
  private:
    int           RangeMin=0;
    int           RangeMax=0;
    byte          DigPos=0;
    int           SetTo=0;
};
#endif
