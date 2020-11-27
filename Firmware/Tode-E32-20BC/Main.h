/******************************************************************************************************************//**
 * @file Main.h
 * @brief Top-Level System Operations Class for the Tode RF IoT Ecosystem
 *    This class handles
 *    1.  ThisTode
 *      a.  Allowing Adding of Defaults as a Link-List of External Devices (by Tode Inheritance)
 *    2.  SystemMenu
 *      a. Link-List of LOCAL Control (Add/Delete Devices + Add/Del Tode + SetWhatName/UID)
 * @authors
 *    TGit-Tech          12/2019       Original
 **********************************************************************************************************************/
#ifndef _MAIN_H
#define _MAIN_H

#include "Constants.h"
#include "Tode.h"
/**********************************************************************************************//**
 *  @class  Master
 *  @brief  Top-Level System Object that handles ALL Todes specifically ThisTode
 *************************************************************************************************/
class Main : public Navigator {
  public:
    Main(Tode* _ThisTode);
    
    byte OnRetKey(byte _Key) override;  // Implements Add-Device Operations
    MenuList* SystemMenu = 0;                          // The System Menu
    MenuList* AddTode = 0;

  protected:
    MenuList*     AddDeviceList = 0;      ///< A List of Addable Devices
    Tode*         ThisTode = 0;
    int           RFAddr = 0;
};
#endif
