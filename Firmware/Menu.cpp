/**********************************************************************************************//**
 * @file    Menu.cpp
 * @brief   Implements MenuList and Navigator
 *************************************************************************************************/
#ifndef _MENU_CPP
#define _MENU_CPP
#include "Menu.h" 

//#####################################################################################################
// MenuItem
//#####################################################################################################
byte MenuItem::DevType(byte _DTPKey) { return DT_NONE; }
byte MenuItem::Loop() { return 0; }
int MenuItem::Command(byte _CMD, int _Value) { return CMD_RETNONE; }       ///< Command Console
byte MenuItem::ID() { return yID; }
void MenuItem::ID(byte _ID) { yID = _ID; }
//#####################################################################################################
// MenuList
//#####################################################################################################
MenuList::MenuList(const char* _CName) { CName = _CName; }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
byte MenuList::Loop() { return 0; }
const char* MenuList::Name() { if (CName==0) return "?Name?"; return CName; }
//-----------------------------------------------------------------------------------------------------
int MenuList::Command(byte _ItemID, byte _CMD, int _Value) { 
  MenuItem* Item = FirstItem;
  while ( Item != 0 ) { 
    if ( Item->ID() == _ItemID ) return Item->Command(_CMD, _Value);
  }
  return CMD_NOITEM;
}
//-----------------------------------------------------------------------------------------------------
MenuItem* MenuList::Add(MenuItem* _Item) {
  _Item->Display = &oDisplay;
  _Item->RF = &oRF;
  
  if ( _Item->SubList != 0 ) {
    _Item->SubList->PrevList = this;
    _Item->SubList->Display = &oDisplay;
    _Item->SubList->RF = &oRF;
  }
  
  if (FirstItem == 0) {
    FirstItem = _Item;
    LastItem = FirstItem;
  } else {
    LastItem->NextItem = _Item;
    LastItem->NextItem->PrevItem = LastItem;
    LastItem = LastItem->NextItem;
  }
  return _Item;
}
//-----------------------------------------------------------------------------------------------------
byte MenuList::Navigate(byte _Key, byte _Row) {              DBENTERAL(("MenuList::Navigate"),(_Key))
  if ( Display==0 ) { DBERRORL(("Display==0")) return 0; }
  //_Key = OnKey(_Key);                                           // User-Intercept
  if ( CurrItem != 0 ) _Key = CurrItem->Navigate(_Key);         // Key the current Item
  //_Key = OnRetKey(_Key);                                        // User-Intercept
  if ( _Key == KEYNONE ) return _Key;                           // If Item used Key exit

  if ( _Key == KEYUP ) {                DBINFOL(("KEYUP"))
    if (CurrItem == 0) return _Key;
    CurrItem->Selected = SEL_NONE;
    CurrItem = CurrItem->PrevItem;
    if (CurrItem != 0) CurrItem->Selected = SEL_ITEM;
    _Key = KEY_SHOWLIST;
  
  } else if ( _Key == KEYDOWN ) {       DBINFOL(("KEYDOWN"))
    if (CurrItem == 0) { 
      CurrItem = FirstItem;
      if (CurrItem != 0) CurrItem->Selected = SEL_ITEM;
    } else if (CurrItem->NextItem != 0) { 
      CurrItem->Selected = SEL_NONE;
      CurrItem = CurrItem->NextItem;
      CurrItem->Selected = SEL_ITEM;
    } 
    _Key = KEY_SHOWLIST;
    
  }
  
  if (_Key==KEY_SHOWLIST || _Key==KEY_CSHOWLIST) {            // Update the Display
    DBINFOL(("KEY_SHOWLIST"))
    if (_Key==KEY_CSHOWLIST) Display->CLEARSCREEN;
    MenuItem* pItem = 0;

      // Display List Title
      Display->TITLEFONT;                               // Title font
      Display->SETCURSOR(0, TITLECHARHEIGHT);           // Where to put List-Title
      if ( CurrItem == 0 ) Display->HIGHLIGHT;          // Highlight Title when No-Selected Item
      Display->print(Name());

      // --- Show EACH Item ---
      Display->NORMAL;
      Display->ITEMFONT;
      pItem = FirstItem; int Row = TITLECHARHEIGHT+30;
      while ( pItem != 0 ) {
        pItem->Navigate(KEY_SHOWROW, Row);
        Row = Row + ITEMCHARHEIGHT +2;
        pItem = pItem->NextItem;
      }

    return KEYNONE;
  }
  return _Key;
}
//#####################################################################################################
// NAVIGATOR
//#####################################################################################################
Navigator::Navigator() { this->Display = &oDisplay; this->RF = &oRF; }
//-----------------------------------------------------------------------------------------------------
byte Loop(byte _FinalKey) { return 0; }           ///< System Loop
//-----------------------------------------------------------------------------------------------------
byte Navigator::Navigate(byte _Key) { 

  if (!StartScreen) { DBINFOL(("Start Screen"))
    if (_Key == KEYNONE) _Key=KEY_CSHOWLIST;
    StartScreen = true;
    Display->DSP_BEGIN;
    Display->DSP_SETROTATION;
    Display->ITEMFONT;
    if (CurrList == 0) CurrList = FirstList;
    if (CurrList != 0) CurrList->Navigate(_Key);
  }
  
  if (_Key == KEYNONE || CurrList == 0) return _Key;        // Exit on NOKEY or No List
  switch (_Key) {
    case KEYRIGHT:  DBINFO(("KEYRIGHT")); break;
    case KEYLEFT:   DBINFO(("KEYLEFT")); break;
    case KEYUP:     DBINFO(("KEYUP")); break;
    case KEYDOWN:   DBINFO(("KEYDOWN")); break;
    case KEYSET:    DBINFO(("KEYSET")); break;
    case KEYOKAY:   DBINFO(("KEYOKAY")); break;
  }  
  //--------------------------------------------------------------------------
  // SEND KEY TO LIST
  //--------------------------------------------------------------------------
  //DBENTERAL(("Navigator::Navigate"),(_Key))
  if (CurrList !=0) {
    _Key = CurrList->Navigate(_Key);
  }

  //--------------------------------------------------------------------------
  // PROCESS RETURNED KEY
  //--------------------------------------------------------------------------
  if ( _Key == GOTO_SUBLIST ) {
    CurrList->CurrItem->Selected = SEL_NONE;
    CurrList = CurrList->CurrItem->SubList;
    CurrList->Navigate(KEY_CSHOWLIST);
    return KEYNONE;
  }
  if ( _Key == KEYRIGHT ) {
    if (CurrList->NextList != 0) {
      CurrList = CurrList->NextList;
      CurrList->Navigate(KEY_CSHOWLIST);
      return KEYNONE;
    }
  }
  if ( _Key == KEYLEFT ) {
    if (this->CurrList->PrevList != 0) {
      CurrList = CurrList->PrevList;
      CurrList->Navigate(KEY_CSHOWLIST);
      return KEYNONE;
    }
  }
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
MenuList* Navigator::Add(MenuList* _List) {
//-----------------------------------------------------------------------------------------------------
  _List->Display = &oDisplay;
  _List->RF = &oRF;
  if (FirstList == 0) {
    FirstList = _List;
    LastList = FirstList;
  } else {
    LastList->NextList = _List;
    LastList->NextList->PrevList = LastList;
    LastList = LastList->NextList;
  }
  return _List;
}
#endif
