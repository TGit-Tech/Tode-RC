/******************************************************************************************************************//**
 * @file    Menu.cpp
 * @brief   Implements MenuList and Navigator
 *********************************************************************************************************************/
#ifndef _MENU_CPP
#define _MENU_CPP
#include "Menu.h" 

//#####################################################################################################################
MenuItem::MenuItem() { this->Display = &oDisplay; }
//-----------------------------------------------------------------------------------------------------
byte MenuItem::Navigate(byte _Key) { return _Key; }
//-----------------------------------------------------------------------------------------------------
byte MenuItem::Loop() { return 0; }
//-----------------------------------------------------------------------------------------------------
void MenuItem::Show(byte _XPos, byte _YPos) { if (_XPos!=0) XPos=_XPos; if (_YPos!=0) YPos=_YPos; }
//#####################################################################################################################
MenuList::MenuList(const char* _CTitle) { CTitle = _CTitle; this->Display = &oDisplay; }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
byte MenuList::Loop() { return 0; }
const char* MenuList::Title() { if (CTitle==0) return "?Name?"; return CTitle; }
//-----------------------------------------------------------------------------------------------------
MenuItem* MenuList::Add(MenuItem* _Item) {
  
  _Item->RF = this->RF;
  if ( _Item->RF == 0 ) { DBERRORL(("MenuList::Add Item->RF == 0")) }
  
  if ( _Item->SubList != 0 ) {
    _Item->SubList->PrevList = this;
    _Item->SubList->Display = &oDisplay;
    _Item->SubList->RF = this->RF;
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
void MenuList::Del(MenuItem* _Item) {

  // Find the Item in the Link-List
  MenuItem* LastItemPtr = 0;
  MenuItem* ThisItemPtr = FirstItem;
  while ( ThisItemPtr != 0 ) {
    if ( ThisItemPtr == _Item ) {
      if ( LastItemPtr == 0 ) { 
        ThisItemPtr->PrevItem = LastItemPtr;
        delete(FirstItem);                                        // Delete First Item
        FirstItem = ThisItemPtr;
      } else {
        LastItemPtr->NextItem = ThisItemPtr->NextItem;            // Last Item Skips This Item
        ThisItemPtr->NextItem->PrevItem = LastItemPtr->PrevItem;  // Next Item's Previous is LastItems Previous
        delete(ThisItemPtr);
        break;
      }
    }
    LastItemPtr = ThisItemPtr;
    ThisItemPtr = ThisItemPtr->NextItem;
  }
  
}
//-----------------------------------------------------------------------------------------------------
byte MenuList::Navigate(byte _Key) {                        DBENTERAL(("MenuList::Navigate"),(_Key,HEX))

  if ( Display==0 ) { DBERRORL(("Display==0")) return 0; }
  if ( CurrItem != 0 ) _Key = CurrItem->Navigate(_Key);         // Key the current Item
  if ( _Key == NAVKEYNONE ) return _Key;                        // If Item used Key exit
  
  if ( _Key == NAVKEYUP ) {                                 DBINFOL(("MenuList::Navigate NAVKEYUP"))
    if (CurrItem == 0) return _Key;                                             // Top of List? Exit.
    CurrItem->NavSelected = SEL_NONE; CurrItem->Show();                         // Reset Current
    CurrItem = CurrItem->PrevItem;                                              // Move to Previous
    if (CurrItem != 0) { CurrItem->NavSelected = SEL_NAME; CurrItem->Show(); }  // Show
    else {                                                                      // Refresh Title
      Display->fillRect(0,0,SCREENWIDTH,TITLECHARHEIGHT+6, (CurrItem==0)? BLUE: LIGHTGREY);
      Display->SETCURSOR(2, TITLECHARHEIGHT); Display->TXTNORM;
      Display->TITLEFONT; Display->print(Title());Display->ITEMFONT;
    }
  
  } else if ( _Key == NAVKEYDOWN ) {                        DBINFOL(("MenuList::Navigate NAVKEYDOWN"))
    if (CurrItem == 0) {                                                        // Start of List
      CurrItem = FirstItem;                                                     // Pick First Item
      if (CurrItem != 0) {                                                      // Refresh Title
        Display->fillRect(0,0,SCREENWIDTH,TITLECHARHEIGHT+6, (CurrItem==0)? BLUE: LIGHTGREY);
        Display->SETCURSOR(2, TITLECHARHEIGHT); Display->TXTNORM;
        Display->TITLEFONT; Display->print(Title());Display->ITEMFONT;
        CurrItem->NavSelected = SEL_NAME;  
        CurrItem->Show();                                                       // Show Item
      }
    } else if (CurrItem->NextItem != 0) { 
      CurrItem->NavSelected = SEL_NONE; CurrItem->Show();
      CurrItem = CurrItem->NextItem;
      CurrItem->NavSelected = SEL_NAME; CurrItem->Show();
    } 
    //_Key = NAVDSPLIST;
    
  } /* else if ( _Key == NAVKEYOKAY ) {
    if ( 1<=this->RFID && this->RFID<=9 ) {
      int RFTodeAddr = word(EEPROM.read(this->RFID*AEB_TODEALLOC+1),EEPROM.read(this->RFID*AEB_TODEALLOC));
      byte TodeVer = EEPROM.read(this->RFID*AEB_TODEALLOC+2);
      RF->Send(PKT_GETVALS, RFTodeAddr, TodeVer);
    }
    // This section needs moved OUT of Menu.cpp I think - Higher more implemented place?
  } */
  
  //------------------------------------------------------
  if (_Key==NAVDSPLIST || _Key==NAVDSPNEWLIST) {            // Update the Display
    
    if (_Key==NAVDSPNEWLIST) { Display->CLEARSCREEN; DBINFOL(("MenuList::Navigate NAVDSPNEWLIST"))} 
    else { DBINFOL(("MenuList::Navigate NAVDSPLIST")) }
    MenuItem* pItem = 0;

      // Display List Title
      Display->fillRect(0,0,SCREENWIDTH,TITLECHARHEIGHT+6, (CurrItem==0)? BLUE: LIGHTGREY);
      Display->SETCURSOR(2, TITLECHARHEIGHT); Display->TXTNORM;
      Display->TITLEFONT; Display->print(Title());Display->ITEMFONT;

      // --- Show EACH Item ---
      
      Display->ITEMFONT;
      pItem = FirstItem; byte Row = TITLECHARHEIGHT+20;
      while ( pItem != 0 ) {
        pItem->Show(0,Row);
        //pItem->Navigate(NAVDSPROW, Row);
        Row = Row + ITEMCHARHEIGHT +2;
        pItem = pItem->NextItem;
      }

    return BNONE;
  }
  return _Key;
}
//#####################################################################################################################
Navigator::Navigator() { this->Display = &oDisplay; }
//-----------------------------------------------------------------------------------------------------
byte Loop(byte _FinalKey) { return 0; }           ///< System Loop
//-----------------------------------------------------------------------------------------------------
byte Navigator::Navigate(byte _Key) { 

  if (!StartScreen) { DBINFOL(("Start Screen"))
    if (_Key == NAVKEYNONE) _Key=NAVDSPNEWLIST;
    StartScreen = true;
    Display->DSP_BEGIN;
    Display->DSP_SETROTATION;
    Display->ITEMFONT;
    if (CurrList == 0) CurrList = FirstList;
    if (CurrList != 0) CurrList->Navigate(_Key);
  }
  
  if (_Key == NAVKEYNONE || CurrList == 0) return _Key;        // Exit on NOKEY or No List
  switch (_Key) {
    case NAVKEYRIGHT:  DBINFO(("NAVKEYRIGHT")); break;
    case NAVKEYLEFT:   DBINFO(("NAVKEYLEFT")); break;
    case NAVKEYUP:     DBINFO(("NAVKEYUP")); break;
    case NAVKEYDOWN:   DBINFO(("NAVKEYDOWN")); break;
    case NAVKEYSET:    DBINFO(("NAVKEYSET")); break;
    case NAVKEYOKAY:   DBINFO(("NAVKEYOKAY")); break;
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
  if ( _Key == NAVGOTOSUBLIST ) {
    CurrList->CurrItem->NavSelected = SEL_NAME;
    CurrList = CurrList->CurrItem->SubList;
    CurrList->Navigate(NAVDSPNEWLIST);
    return BNONE;
  }
  if ( _Key == NAVKEYRIGHT ) {
    if (CurrList->NextList != 0) {
      CurrList = CurrList->NextList;
      CurrList->Navigate(NAVDSPNEWLIST);
      return BNONE;
    }
  }
  if ( _Key == NAVKEYLEFT ) {
    if (this->CurrList->PrevList != 0) {
      CurrList = CurrList->PrevList;
      CurrList->Navigate(NAVDSPNEWLIST);
      return BNONE;
    }
  }
  return _Key;
}
//-----------------------------------------------------------------------------------------------------
MenuList* Navigator::Add(MenuList* _List) {

  _List->Display = &oDisplay;
  _List->RF = this->RF;
  if ( _List->RF == 0 ) { DBERRORL(("Navigator::Add List->RF == 0")) }
  
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
//-----------------------------------------------------------------------------------------------------
void Navigator::Del(MenuList* _List) {
  
  // Find the Item in the Link-List
  MenuList* LastListPtr = 0;
  MenuList* ThisListPtr = FirstList;
  while ( ThisListPtr != 0 ) {
    if ( ThisListPtr == _List ) {
      if ( LastListPtr == 0 ) { 
        // Delete First Item
        ThisListPtr->PrevList = LastListPtr;
        delete(FirstList);
        FirstList = ThisListPtr;
      } else {
        LastListPtr->NextList = ThisListPtr->NextList;            // Last Item Skips This Item
        ThisListPtr->NextList->PrevList = LastListPtr->PrevList;  // Next Item's Previous is LastItems Previous
        delete(ThisListPtr);
        break;
      }
    }
    LastListPtr = ThisListPtr;
    ThisListPtr = ThisListPtr->NextList;
  }
}
//_____________________________________________________________________________________________________________________
#endif
