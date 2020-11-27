/**********************************************************************************************//**
 * @file    Menu.h
 * @brief   A Link-List Menu Structure; [Top-Level Navigator]<[Lists]<[Items] hierarchy.
 *************************************************************************************************/
#ifndef _MENU_H
#define _MENU_H

#include "Constants.h"
#include "Display.h"

class MenuList;
/**********************************************************************************************//**
 * @class   MenuItem
 * @brief   The Menu-Item Interface (i.e. Abstract Base Class).
 *          Each Item-Type can rely on 'Display' being defined but each Item-Type must contain
 *          its own implementation of Navigate() and corresponding Display methods.
 *************************************************************************************************/
class MenuItem {
  friend class MenuList;
  friend class Navigator;
  
  public:
    virtual byte          Navigate(byte _Key, byte _Row=0)=0;
    virtual byte          OnKey(byte _Key);
    virtual byte          OnRetKey(byte _Key); 
 
  protected:
    MenuList*     SubList = 0;              ///< Link-List Item -> Another Link-List
    DSPCLASS*     Display = 0;
    byte          Selected = SEL_NONE;
    
  private:
    MenuItem*     NextItem = 0;             ///< Link-List Next-Item pointer
    MenuItem*     PrevItem = 0;             ///< Link-List Prev-Item pointer
    
};
/**********************************************************************************************//**
 * @class  MenuList
 * @brief  
 *************************************************************************************************/
class MenuList {
  friend class Navigator;
  
  public:
    MenuList(const char* _CName=0);
    
    virtual byte        Navigate(byte _Key, byte _Row=0);
    virtual byte        OnKey(byte _Key);
    virtual byte        OnRetKey(byte _Key);
    virtual MenuItem*   Add(MenuItem* _Item);
    virtual const char* Name();
  
  protected:
    DSPCLASS*     Display = 0;
  
  private:
    const char*   CName = 0;
    MenuItem*     FirstItem = 0;
    MenuItem*     LastItem = 0;
    MenuItem*     CurrItem = 0;
    MenuList*     NextList = 0;
    MenuList*     PrevList = 0;
};
/**********************************************************************************************//**
 * @class  Navigator
 * @brief  
 *************************************************************************************************/
class Navigator {
  
  public:
    Navigator();
    virtual byte        Navigate(byte _Key);
    virtual byte        OnKey(byte _Key);
    virtual byte        OnRetKey(byte _Key);
    virtual MenuList*   Add(MenuList* _List);
    
  private:
    bool        StartScreen=false;
    DSPCLASS*   Display = 0;
    MenuList*   FirstList = 0;
    MenuList*   LastList = 0;
    MenuList*   CurrList = 0;
};
#endif
