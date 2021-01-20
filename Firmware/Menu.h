/******************************************************************************************************************//**
 * @file    Menu.h
 * @brief   Abstract Base Classes for Menu Structure hierarchy
 *          - Top-Level Navigator of MenuList (s)
 *          - MenuList of MenuItem (s)
 *          - MenuItem
 *********************************************************************************************************************/
#ifndef _MENU_H
#define _MENU_H

#include "lib/ABC.h"
#include "Disp.h"
#include <EEPROM.h>
#include "E32.h"

/******************************************************************************//**
 * @defgroup NAV Navigate() Constants
 * @{
 *********************************************************************************/
  /******************************************************************************//**
  * @defgroup NAVKEY Keypad Navigate() Constants
  * @{
  *********************************************************************************/
  // 0x[F]-Key Presses
  #define NAVKEYNONE        0xFF
  #define NAVKEYRIGHT       0xFE
  #define NAVKEYLEFT        0xFD
  #define NAVKEYUP          0xFC
  #define NAVKEYDOWN        0xFB
  #define NAVKEYSET         0xFA
  #define NAVKEYOKAY        0xF9
  #define KEYPRESSmiN       0xF0
  ///@}
  /******************************************************************************//**
  * @defgroup NAVDSP Display Navigate() Constants
  * @{
  *********************************************************************************/
  // 0x[D]isplay Control
  #define NAVDSPNEWLIST     0xDF    ///< [C]lear & Show MenuList on Display
  #define NAVDSPLIST        0xDE    ///< Show MenuList on Display
  #define NAVDSPNEWNAMESET  0xDD    ///< [C]lear & Show the Name[SET]Tool on Display
  #define NAVDSPNAMESET     0xDC    ///< Show the Name[SET]Tool on Display
  #define NAVDSPROW         0xDB    ///< Show a single List-Row on the Display
  ///@}
  /******************************************************************************//**
  * @defgroup NAVCMD Command Navigate() Constants
  * @{
  *********************************************************************************/  
  // 0x[C]ommand Control
  #define NAVGOTOSUBLIST    0xCF    ///< Activated in NavName() of MenuName
  #define NAVEXITNAMESET    0xCE
  #define NAVSAVENAMESET    0xCD
  #define NAVGETREMVALS     0xCC
  #define NAVDELTODE        0xCB
  //#define NAVRFPCCONNGO     0xCB    ///< Loop the Radio PC Connection
  //#define NAVRFPCCONNSTOP   0xCA    ///< Stop Looping the Radio PC Connection
  ///@}
///@}
/******************************************************************************//**
 * @defgroup SEL Item-Element 'NavSelected'
 * @{
 *********************************************************************************/
#define SEL_NONE      0       ///< The Item is NOT NavSelected in a List
#define SEL_NAME      1       ///< NAME element is NavSelected in a List
#define SEL_VALUE     2       ///< VALUE element is NavSelected in a List
#define SEL_SETNAME   3       ///< The NAME element is being Set
#define SEL_SETVALUE  4       ///< The VALUE element is being Set in a List
///@}
class MenuList;
/******************************************************************************************************************//**
 * @class   MenuItem
 * @brief   **ITEM** Menu-Item Base Class ie *Interface*.
 *          1.  Object 'Display' is available in every Item assigned by Constructor.
 *          Each Item-Type can rely on 'Display' being defined but each Item must contain
 *          its own implementation of Navigate() and corresponding Display methods.
 *          
 *********************************************************************************************************************/
class MenuItem {
  friend class MenuList;
  friend class Navigator;
  
  public:
    MenuItem();
    virtual byte    Navigate(byte _Key);                      ///< Keypad Navigate by \ref KEY
    virtual void    Show(byte _XPos=0, byte _YPos=0);         ///< Display the Item
    virtual byte    Loop();                                   ///< System loop()
            byte    NavSelected = SEL_NONE;                   ///< Display focus point
            byte    RFID = 0xFF;                              ///< RFID of Item for RxTx
    MenuList*       SubList = 0;                              ///< Item links->to a Link-List
  
  protected:
    DSPCLASS*       Display = 0;                              ///< Display Object Pointer
    RFCLASS*        RF = 0;
    byte            XPos=0, YPos=0;
    
  private:
    MenuItem*       NextItem = 0;                             ///< Item link->to Next Item Link-List-Pointer
    MenuItem*       PrevItem = 0;                             ///< Item link->to Prev Item Link-List-Pointer
    
};
/******************************************************************************************************************//**
 * @class  MenuList
 * @brief  **LIST** of Menu-Item (s) which can carry a *List Name*.
 *********************************************************************************************************************/
class MenuList {
  friend class Navigator;
  
  public:
    MenuList(const char* _CTitle=0);                          ///< NEW List optional Title Name
    
    virtual byte          Navigate(byte _Key);                ///< Keypad Navigate by \ref KEY
    virtual MenuItem*     Add(MenuItem* _Item);               ///< ADD MenuItem to the MenuList
    virtual void          Del(MenuItem* _Item);               ///< DEL MenuItem from the MenuList
    virtual byte          Loop();                             ///< System loop()
            
    virtual const char*   Title();                            ///< GET List Title/Name
            byte          RFID = 0xFF;
    
    MenuList*     NextList = 0;
    MenuList*     PrevList = 0;
      
  protected:
    RFCLASS*        RF = 0;
    DSPCLASS*       Display = 0;

    MenuItem*       FirstItem = 0;
    MenuItem*       LastItem = 0;
    MenuItem*       CurrItem = 0;
  
  private:
    const char*     CTitle = 0;
    
};
/******************************************************************************************************************//**
 * @class  Navigator
 * @brief  **LIST of LISTS** Top-Level Navigator of multiple MenuList (s).
 *          Navigation is preformed by sending keypad pressed to the Top-Level Navigator.  The key
 *          will undergo a round-robin calling sequence to List-Navigate then Item-Navigate 
 *          objects.  If the object has \ref SEL the key is used by said object and a returning
 *          *command-type* non-keypad key is returned.  See \ref KEY
 *********************************************************************************************************************/
class Navigator {
  
  public:
    Navigator();                                  ///< Constructor sets Display = oDisplay
    virtual byte        Navigate(byte _Key);      ///< Keypad Navigate by \ref KEY
    virtual MenuList*   Add(MenuList* _List);     ///< ADD MenuList to the Navigator
    virtual void        Del(MenuList* _List);
    virtual byte        Loop(byte _FinalKey);     ///< System loop()

  protected:
    MenuList*     FirstList = 0;
    MenuList*     LastList = 0;
    MenuList*     CurrList = 0;
    RFCLASS*      RF = 0;
    DSPCLASS*     Display = 0;
     
  private:
    bool          StartScreen=false;              ///< Initialize Screen ONCE
    
    
};
//_____________________________________________________________________________________________________________________
#endif
