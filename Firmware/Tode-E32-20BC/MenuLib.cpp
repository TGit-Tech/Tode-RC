/**********************************************************************************************//**
 * @file    MenuLib.cpp
 * @brief   [M]enu [L]ibrary
 *************************************************************************************************/
#ifndef _MENULIB_CPP
#define _MENULIB_CPP

#include "MenuLib.h" 
#include <EEPROM.h>
//#####################################################################################################
MenuName::MenuName(const char* _CName, MenuList* _SubList) { CName = _CName; SubList = _SubList; }
//-----------------------------------------------------------------------------------------------------
MenuName::MenuName(int _NAddr, byte _NSize, bool _NSettable, const char* _TLine) { 
  NAddr = _NAddr; NSize = _NSize; NSettable = _NSettable; TLine = _TLine; }
//-----------------------------------------------------------------------------------------------------
byte MenuName::Navigate(byte _Key, byte _Row=0) { 
  return NNavigate(_Key,_Row); 
}  
//-----------------------------------------------------------------------------------------------------
byte MenuName::NNavigate(byte _Key, byte _Row=0) {      //DBENTERA(("MenuName::NNavigate"),(_Key))
  
  // KEY
  if ( Selected == SEL_ITEM ) {
    if ( _Key == KEYSET && NSettable ) Selected = SEL_SETNAME;
    if ( _Key == KEYOKAY && SubList != 0 ) return GOTO_SUBLIST;
  }
  if ( Selected == SEL_SETNAME ) {
    if ( SetName != 0 ) { _Key = SetName->Navigate(_Key); }
    else {
      SetName = new SetNameTool(Display, "Set Name", NSize);
      Name(); // Load Name into FName[]
      for (byte i=0; i<AEB_MAX; i++) { SetName->SetToName[i]=FName[i]; }
      SetName->Navigate(KEY_CSHOWSET);
    }
    if ( _Key==EXIT_SET || _Key==EXIT_SAVESET ) {
      if ( _Key==EXIT_SAVESET ) Name(SetName->SetToName);
      Selected = SEL_ITEM;
      SetName = 0;
      return KEY_CSHOWLIST;
    }
  }

  // DISPLAY
  if (_Key!=KEY_SHOWROW) return _Key; //DBINFOL(("KEY_SHOWROW"))
  if ( Display==0 ) { DBERRORL(("Display==0")) return _Key; }

  Display->SETCURSOR(0, _Row);
  if ( Selected == SEL_ITEM ) Display->HIGHLIGHT; //Display->HIGHLIGHT;
  if ( TLine != 0 ) { Display->print(TLine); } else { Display->print(Name()); }
  Display->NORMAL; 
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
const char* MenuName::Name() {
  if ( CName != 0 ) return CName;
  if ( NAddr < 0 ) { DBERRORL(("NAddr<0")) return; }

  for (byte i=0; i<AEB_MAX; i++) {
    if ( i < NSize ) { 
      FName[i]=EEPROM.read(NAddr+i); 
      if ( 127 <=FName[i]||FName[i]<= 31 ) FName[i]='\0';
    } else { FName[i]='\0'; }
  }
  return FName;
}
//-----------------------------------------------------------------------------------------------------
void MenuName::Name(const char* _Name) {
  if ( CName != 0 ) { CName = _Name; return; }
  if ( NAddr < 0 ) { DBERRORL(("NAddr<0")) return; }

  //Name Set - Recorded Addr 6~15 is 9 characters
  bool charmark=false;
  for (int i=AEB_MAX-1; i>=0; i--) {
    if ( i < NSize ) {
      if ( i < strlen(_Name) ) {

        // Trim all trailing spaces and NULL terminate anything non-ASCII
        if (charmark) { if (_Name[i]==32) EEPROM.update(NAddr+i,_Name[i]); }
        if ( 33 <=_Name[i]&&_Name[i]<= 126 ) { charmark=true;EEPROM.update(NAddr+i,_Name[i]); }
        else { EEPROM.update(NAddr+i, '\0'); }
        
      } else { EEPROM.update(NAddr+i, '\0'); }
    } else { EEPROM.update(NAddr+i, '\0'); }
  }
}
//#####################################################################################################
SetNameTool::SetNameTool(DSPCLASS* _Display, const char* _Title, byte _Size) {
  Display = _Display;
  Size = _Size;
  Title = _Title;
}
//-----------------------------------------------------------------------------------------------------
byte SetNameTool::Navigate(byte _Key, byte _Row) {
  if ( Display==0 ) { DBERRORL(("Display==0")) return 0; }

  // KEY
  if ( _Key == KEYUP ) {
    if ( SetTo<48 || SetTo>92 ) { SetTo--; }
    else if (48<= SetTo && SetTo <= 56) { SetTo=SS_SPACE; }     // Top Row UP->SPACE
    else { SetTo = SetTo -9; }
    _Key = KEY_SHOWSET;
    
  } else if ( _Key == KEYDOWN ) {
    if ( SetTo<SS_BACK ) { SetTo++; }
    else if ( SS_BACK <=SetTo&&SetTo<= SS_SPACE ) { SetTo=48; }
    else if ( SetTo>=84 && SetTo <= 92) { SetTo=SS_SAVE; }        // Bottom Row DOWN->SAVE
    else { SetTo = SetTo +9; }
    _Key = KEY_SHOWSET;
      
  } else if ( _Key == KEYRIGHT ) {
    if ( SetTo==SS_POSITION ) { SetIdx++; }
    else { SetTo++; }
    _Key = KEY_SHOWSET;
      
  } else if ( _Key == KEYLEFT ) {
    if ( SetTo==SS_POSITION ) { SetIdx--; }
    else if (SetTo==SS_TITLE) { return EXIT_SET; }
    SetTo--;_Key = KEY_SHOWSET;
      
  } else if ( _Key == KEYSET || _Key == KEYOKAY ) {
    if ( 65 <= SetTo && SetTo <= 90 ) {
      if (_Key==KEYOKAY) {SetToName[SetIdx] = char(SetTo + 32);} // Use lower-case
      else { SetToName[SetIdx] = char(SetTo); }
      SetIdx++;
    } else if ( SetTo==SS_SPACE ) { SetToName[SetIdx] = ' '; SetIdx++; }
    else if ( SetTo==SS_SAVE ) { return EXIT_SAVESET; }
    else if ( SetTo==SS_BACK ) { SetToName[SetIdx]=' '; SetIdx--; }
    _Key = KEY_SHOWSET;
  }
  if (SetTo<SS_TITLE) SetTo = SS_SAVE;
  if (SetTo>SS_SAVE) SetTo=SS_TITLE;
  if (SetIdx>Size-1) SetIdx=Size-1;

  // DISPLAY
  if (_Key == KEY_SHOWSET || _Key==KEY_CSHOWSET) {
    if (_Key==KEY_CSHOWSET) Display->fillScreen(0x0000);

      // Title
      Display->TITLEFONT;
      if ( SetTo == SS_TITLE ) Display->HIGHLIGHT;
      Display->SETCURSOR(0, 12);
      if (Title == 0) { Display->print("?Title?"); } else { Display->print(Title); }
      Display->NORMAL;

     // SetToName
      Display->ITEMFONT;
      Display->SETCURSOR(0, 25);
      for (int i=0; i<Size; i++) {
        if ( 32> SetToName[i]||SetToName[i] >126 ) SetToName[i]=' ';
        if ( i!=SetIdx ) { Display->print(SetToName[i]); }
        else {//i==SetIdx
          if (SetTo==SS_POSITION) Display->HIGHLIGHT;
          Display->print(SetToName[i]);Display->NORMAL;
        }
      }
      // Cursor Position
      Display->SETCURSOR(SetIdx*ITEMCHARWIDTH, 38);Display->print("^");

      // Special Line
      Display->SETCURSOR(0,45);
      if (SetTo==SS_BACK) Display->HIGHLIGHT;
      Display->print("<<");Display->NORMAL;Display->print(" ");
      if (SetTo==SS_SPACE) Display->HIGHLIGHT;
      Display->print("Sp");Display->NORMAL;
      
      // Alphabet
      int col = 0; int row = 55;
      for ( char c = 48; c <= 92; c++ ) {
        Display->SETCURSOR(col, row);
        if ( SetTo == c ) Display->HIGHLIGHT;
        Display->print(c);Display->NORMAL;
        col = col + ITEMCHARWIDTH + 2;
        if (col > SCREENWIDTH - ITEMCHARWIDTH) { col = 0; row = row + ITEMCHARHEIGHT + 2; }
      }
        
      if ( SetTo == SS_SAVE ) Display->HIGHLIGHT;
      Display->SETCURSOR(40,121);Display->print("Save");Display->NORMAL;
      
    return KEYNONE;
  }
  return _Key;
}
//#####################################################################################################
MenuValue::MenuValue(const char* _CName, int _VNumBase = DEC):
  MenuName(_CName) { VNumBase = _VNumBase; }
//-----------------------------------------------------------------------------------------------------
MenuValue::MenuValue(int _NAddr, byte _NSize, bool _NSettable=false, int _VNumBase = DEC):
  MenuName(_NAddr, _NSize, _NSettable) { VNumBase = _VNumBase; }
//-----------------------------------------------------------------------------------------------------
byte MenuValue::Navigate(byte _Key, byte _Row) {          //DBENTERAL(("MenuValue::Navigate"),(_Key))
  if ( Selected==SEL_ITEM ) {
    if (_Key==KEYRIGHT) { Selected=SEL_VALUE; return KEY_SHOWLIST; }
  } else if (Selected==SEL_VALUE) {
    if (_Key==KEYLEFT) { Selected=SEL_ITEM; return KEY_SHOWLIST; }
  }

  // Navigate Name & Value
  _Key = NNavigate(_Key,_Row);
  _Key = VNavigate(_Key,_Row);
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
byte MenuValue::VNavigate(byte _Key, byte _Row=0) {         //DBENTERA(("MenuValue::VNavigate"),(_Key))
  if ( Display==0 ) { DBERRORL(("Display==0")) return _Key; }
  
  Display->SETCURSOR(VALCOL, _Row);
  if ( Selected == SEL_VALUE ) Display->HIGHLIGHT;
  Display->print(Value(),VNumBase);Display->NORMAL;  
  return _Key;
}
//#####################################################################################################
MVDigitSet::MVDigitSet(const char* _CName, int _RangeMin, int _RangeMax, int _VNumBase):
  MenuValue(_CName, _VNumBase) {
    RangeMin = _RangeMin;
    RangeMax = _RangeMax;
}
//-----------------------------------------------------------------------------------------------------
MVDigitSet::MVDigitSet(int _NAddr, byte _NSize, bool _NSettable, int _RangeMin, int _RangeMax, int _VNumBase):
  MenuValue(_NAddr, _NSize, _NSettable, _VNumBase) {
    RangeMin = _RangeMin;
    RangeMax = _RangeMax;  
}
//-----------------------------------------------------------------------------------------------------
byte MVDigitSet::VNavigate(byte _Key, byte _Row) {
  if ( Display==0 ) { DBERRORL(("Display==0")) return _Key; }

  // KEY
  if (_Key != KEY_SHOWROW ) {
    if ( Selected==SEL_VALUE && _Key==KEYSET ) {
      Selected = SEL_SETVALUE;
      SetTo = Value();
      return KEY_SHOWLIST;
    } else if ( Selected==SEL_SETVALUE ) {
      if (_Key==KEYUP) { SetTo = SetTo - pow(VNumBase,DigPos); }
      else if (_Key==KEYDOWN) { SetTo = SetTo + pow(VNumBase,DigPos); }
      else if (_Key==KEYRIGHT) { if (DigPos>0) DigPos--; }
      else if (_Key==KEYLEFT) { if (DigPos>=3) { Selected=SEL_ITEM; DigPos=0; } else { DigPos++; } }
      else if (_Key==KEYSET) { Value(SetTo); Selected=SEL_ITEM; }
      return KEY_CSHOWLIST;
    }

  // DISPLAY (GFX Prints over OLD ROW - WHY?)
  } else {
    if ( Selected == SEL_SETVALUE ) {
      uint16_t Val=SetTo; int Col=VALCOL+(4*ITEMCHARWIDTH);
      DBINFOAL(("SEL_SETVALUE"),(Val))
      if (SetTo==0) { Display->print(SetTo); }
      else {  // Have to print in reverse order
        for (byte i=0; i<4; i++) {
          Display->SETCURSOR(Col, _Row);
          if (DigPos==i) Display->HIGHLIGHT;
          Display->print(Val%VNumBase,VNumBase);
          Col=Col-(ITEMCHARWIDTH+2);Val /= VNumBase;
          Display->NORMAL;
        }
      }
    } else {
      if ( Selected == SEL_VALUE ) Display->HIGHLIGHT;
      Display->SETCURSOR(VALCOL, _Row);
      if ( VNumBase == HEX ) { Display->print(uint16_t(Value()), VNumBase); }   // Show Hex as unsigned
      else { Display->print(Value(), VNumBase); }
    }
    Display->NORMAL;
    return KEYNONE;
  }
  return _Key;
}
//#####################################################################################################
MVOptions::MVOptions(const char* _CName, const byte _Options[], const byte _OptionsSize, const char* _OptionNames[], bool _NSettable):
  MenuValue(_CName) {
    Options = _Options;
    OptionsSize = _OptionsSize;
    OptionNames = _OptionNames;
}
//-----------------------------------------------------------------------------------------------------
MVOptions::MVOptions(int _NAddr, byte _NSize, const byte _Options[], const byte _OptionsSize, const char* _OptionNames[], bool _NSettable):
  MenuValue(_NAddr, _NSize, _NSettable) {
    Options = _Options;
    OptionsSize = _OptionsSize;
    OptionNames = _OptionNames;    
}
//-----------------------------------------------------------------------------------------------------
byte MVOptions::VNavigate(byte _Key, byte _Row) {
  if (_Key<KEYPRESSMIN && _Key!=KEY_SHOWROW) return _Key;
  if ( Display==0 ) { DBERRORL(("Display==0")) return _Key; }

  // KEY
  if (Selected==SEL_SETVALUE) {
    if (_Key==KEYUP) { SetTo++; }
    else if (_Key==KEYDOWN) { SetTo--; }
    if (SetTo>OptionsSize) SetTo=0;
    return KEY_SHOWLIST;
  }

  // DISPLAY
  if (_Key==KEY_SHOWROW) {
    Display->SETCURSOR(41, _Row);
    if ( Selected != SEL_SETVALUE ) {
      // Check that Value has correct Option Index
      byte Val=byte(Value());
      if ( ValOptIdx>OptionsSize ) { ValOptIdx=0xFF; }
      else {
        if ( Val != Options[ValOptIdx] ) { ValOptIdx=0xFF;
          for (byte i=0; i<=OptionsSize; i++) { 
            if ( Options[i] == Val ) { ValOptIdx=i; exit; } }
        }
      }
      // Display
      if ( Selected == SEL_VALUE) Display->HIGHLIGHT;
      if ( ValOptIdx==0xFF ) { Display->print("?NO?"); }
      else if ( OptionNames == 0 ) { Display->print(Options[ValOptIdx]); }
      else { Display->print(OptionNames[ValOptIdx]); }
      Display->NORMAL;
    } else {
      Display->HIGHLIGHT;
      if ( OptionNames == 0 ) { Display->print(Options[SetTo]); }
      else { Display->print(OptionNames[SetTo]); }
      Display->NORMAL;      
    }
    return KEYNONE;
  }
  return _Key;
}
#endif
