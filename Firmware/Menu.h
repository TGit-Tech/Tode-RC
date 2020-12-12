/**********************************************************************************************//**
 * @file    Menu.h
 * @brief   Abstract Base Classes for Menu Structure hierarchy
 *          - Top-Level Navigator of MenuList (s)
 *          - MenuList of MenuItem (s)
 *          - MenuItem
 *************************************************************************************************/
#ifndef _MENU_H
#define _MENU_H

#include "Constants.h"
#include "Display.h"
#include "Radio.h"

class MenuList;
/**********************************************************************************************//**
 * @class   MenuItem
 * @brief   **ITEM** Menu-Item Base Class ie *Interface*.
 *          1.  Object 'Display' is available in every Item assigned by Constructor.
 *          Each Item-Type can rely on 'Display' being defined but each Item must contain
 *          its own implementation of Navigate() and corresponding Display methods.
 *          
 *************************************************************************************************/
class MenuItem {
  friend class MenuList;
  friend class Navigator;
  
  public:
    virtual byte          Navigate(byte _Key, byte _Row=0)=0;   ///< Keypad Navigate by \ref KEY
    virtual int           Command(byte _CMD, int _Value);       ///< Item Command Console
    virtual byte          DevType(byte _DTPKey = DTP_DEVTYPE);  ///< Device-Type Parameters
    virtual byte          Loop();                               ///< System loop()
    virtual byte          ID();                                 ///< GET Numeric Item ID
    virtual void          ID(byte _ID);                         ///< SET Numeric Item ID
 
  protected:
    MenuList*     SubList = 0;              ///< Item links->to a Link-List
    DSPCLASS*     Display = 0;              ///< Display Object Pointer
    RFCLASS*      RF = 0;                   ///< RF-Radio Object Pointer
    byte          Selected = SEL_NONE;      ///< Display focus point
    
  private:
    byte          yID = BNONE;              ///< Numerical identify each item
    MenuItem*     NextItem = 0;             ///< Item link->to Next Item Link-List-Pointer
    MenuItem*     PrevItem = 0;             ///< Item link->to Prev Item Link-List-Pointer
    
};
/**********************************************************************************************//**
 * @class  MenuList
 * @brief  **LIST** of Menu-Item (s) which can carry a *List Name*.
 *************************************************************************************************/
class MenuList {
  friend class Navigator;
  
  public:
    MenuList(const char* _CName=0);                         ///< NEW List optional Name
    
    virtual byte        Navigate(byte _Key, byte _Row=0);             ///< Keypad Navigate by \ref KEY
    virtual int         Command(byte _ItemID, byte _CMD, int _Value); ///< Command Console
    virtual MenuItem*   Add(MenuItem* _Item);                         ///< ADD MenuItem to the MenuList
    virtual const char* Name();                             ///< GET List Name
    virtual byte        Loop();                             ///< System loop()
    MenuList*     NextList = 0;
    MenuList*     PrevList = 0;
      
  protected:
    DSPCLASS*     Display = 0;
    RFCLASS*      RF = 0;
    MenuItem*     FirstItem = 0;
    MenuItem*     LastItem = 0;
    MenuItem*     CurrItem = 0;

  private:
    const char*   CName = 0;
};
/**********************************************************************************************//**
 * @class  Navigator
 * @brief  **LIST of LISTS** Top-Level Navigator of multiple MenuList (s).
 *          Navigation is preformed by sending keypad pressed to the Top-Level Navigator.  The key
 *          will undergo a round-robin calling sequence to List-Navigate then Item-Navigate 
 *          objects.  If the object has \ref SEL the key is used by said object and a returning
 *          *command-type* non-keypad key is returned.  See \ref KEY
 *************************************************************************************************/
class Navigator {
  
  public:
    Navigator();                                  ///< Constructor sets Display = oDisplay
    virtual byte        Navigate(byte _Key);      ///< Keypad Navigate by \ref KEY
    virtual MenuList*   Add(MenuList* _List);     ///< ADD MenuList to the Navigator
    virtual byte        Loop(byte _FinalKey);     ///< System loop()

  protected:
    MenuList*   FirstList = 0;
    MenuList*   LastList = 0;
    MenuList*   CurrList = 0;
     
  private:
    bool        StartScreen=false;
    DSPCLASS*   Display = 0;
    RFCLASS*    RF = 0;
};
#endif
