/******************************************************************************************************************//**
 * @file Main.h
 * @brief SYSTEM.  Top-Level Navigator and System Operations.
 *    - Setup Menu
 *    - Todes List
 *    - Devices List
 *    - AddDevicesList
 *    - Radio Settings ( MenuList )
 *    
 * @authors
 *    TGit-Tech          12/2019       Original
 **********************************************************************************************************************/
#ifndef _MAIN_H
#define _MAIN_H

//#include "PeerIOSerialControl.h"
#include "Constants.h"
#include "Tode.h"
#include "E32Lib.h"

/**********************************************************************************************//**
 *  @class  Main
 *  @brief  **System** Top-Level System for Setup, Todes, and ThisTode's HDW / Device Setup.
 *************************************************************************************************/
class Main : public Navigator {
  public:
    Main();

    MenuList*   SetupMenu = 0;                          ///< Setup the System Menu
    MenuList*   Devices = 0;                            ///< ThisTode Devices and Settings
    MenuList*   AddDeviceList = 0;                      ///< Add Device drivers for Adding by-menu
    E32Radio*   RFRadio = 0;
    MenuList*   RadioSettings = 0;                      ///< RF Radio Settings on Menu List
    byte        Loop(byte _FinalKey) override;          ///< Last Return key for Adding Devices
    
    
  protected:
    Tode*         ThisTode = 0;
    int           RFAddr = 0;
    int           NewTodeEEA();                 ///< Increments TODEALLOC everytime called

  private:
    E32PCConn*    E32PC = 0;
    //PeerIOSerialControl*  E32Radio = 0;
    void          SetupMenu_Init();
    void          DeviceList_Init();
    void          Radio_Init();
    int           iNewTodeEEA = 0;              ///< What EEPROM address next tode will start
};
#endif
