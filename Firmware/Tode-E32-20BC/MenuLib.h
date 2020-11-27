/**********************************************************************************************//**
 * @file    MenuLib.h
 * @brief   [M]enu [L]ibrary
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
    char          SetToName[AEB_MAX];      ///< Set-To Array[] Variable
  private:
    DSPCLASS*          Display=0;
    byte          Type=0;
    byte          Size=0;
    const char*   Title=0;
    int           SetTo = SS_TITLE;         ///< Set-To Integer Variable
    byte          SetIdx = 0;               ///< Set-To Array[] current Index
};
/**********************************************************************************************//**
 * @class   MenuName
 * @brief   Constructor call determines if Name is stored in RAM or EEPROM
 *************************************************************************************************/
class MenuName : public MenuItem {
  public:
    MenuName(const char* _CName, MenuList* _SubList=0);
    MenuName(int _NAddr, byte _NSize, bool _NSettable=false, const char* _TLine=0);

    virtual byte          Navigate(byte _Key, byte _Row=0);
    virtual const char*   Name();
    virtual void          Name(const char* _Name);
    
  protected:
    virtual byte          NNavigate(byte _Key, byte _Row=0);
    
  private:
    const char*           TLine = 0;
    const char*           CName = 0;
    char                  FName[AEB_MAX];       // C-Style Name Char[] for Name set/get.
    bool                  NSettable = false;
    int                   NAddr = -1;
    byte                  NSize = 0;
    SetNameTool*          SetName = 0;
};
/**********************************************************************************************//**
 * @class   MenuValue
 * @brief   Read-Only Value
 *************************************************************************************************/
class MenuValue : public MenuName {
  public:
    MenuValue(const char* _CName, int _VNumBase = DEC);
    MenuValue(int _NAddr, byte _NSize, bool _NSettable=false, int _VNumBase = DEC);

    virtual byte          Navigate(byte _Key, byte _Row=0) override;
    virtual int           Value();
    virtual void          Value(int _Value);
  
  protected:
    virtual byte          VNavigate(byte _Key, byte _Row=0);
    int                   VNumBase=DEC;
};
/**********************************************************************************************//**
 * @class   MVDigitSet
 * @brief   [M]enu[V]alue with a per Digit Value Set
 *************************************************************************************************/
class MVDigitSet : public MenuValue {
  public:
    MVDigitSet(const char* _CName, int _RangeMin=0x0000, int _RangeMax=0xFFFF, int _VNumBase = DEC);
    MVDigitSet(int _NAddr, byte _NSize, bool _NSettable=false, int _RangeMin=0x0000, int _RangeMax=0xFFFF, int _VNumBase = DEC);
    
  protected:
    virtual byte  VNavigate(byte _Key, byte _Row=0) override;
    
  private:
    int           RangeMin=0;
    int           RangeMax=0;
    byte          DigPos=0;
    int           SetTo=0;
};

/**********************************************************************************************//**
 * @class   MVOptions
 * @brief   [M]enu[V]alue with a Pick-An-Option Value Set
 *************************************************************************************************/
class MVOptions : public MenuValue {
  public:
    MVOptions(const char* _CName, const byte _Options[], const byte _OptionsSize, const char* _OptionNames[] = 0, bool _NSettable=false);
    MVOptions(int _NAddr, byte _NSize, const byte _Options[], const byte _OptionsSize, const char* _OptionNames[] = 0, bool _NSettable=false);
    
  protected:
    virtual byte  VNavigate(byte _Key, byte _Row=0) override;
  private:
    byte          SetTo=0;                  ///< The Current selected 'SetTo' option index
    byte          ValOptIdx=0xFF;           ///< The Currently selected option Index
    byte*         Options = 0;              ///< Array of choosable Value-Options[]
    byte          OptionsSize = 0;          ///< Array[Size] of either/both Options[] & OptionNames[]
    const char**  OptionNames = 0;          ///< Corresponding Text Name for choosable Value-Options[]  
};
#endif
