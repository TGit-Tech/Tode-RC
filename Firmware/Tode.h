/**********************************************************************************************//**
   @file Tode.h
   @brief Tode Class.
   <PRE>
    Tode class represents the 'Control' Configuration.  Any Device Settings are stored in System.
    All Radio Settings are stored in System except Radio Address.
    It is a 'MenuList' of Devices.

    System Settings will be saved at the tail of EEPROM space.
    ThisTode will be the first Tode at the start of EEPROM space.
    Subsequent Remote Tode configuration will be stored after ThisTode from start.
    We will no longer use Tode-UID but instead use RF-Addr + 15 Arduino ID from Peer.
    Pinging will occur on FFFF but be filtered by the 1-nibble Arduino ID.
   </PRE>
   @authors
      2019-12-16  TGit-Tech   Origin
 *************************************************************************************************/
#ifndef _TODE_H
#define _TODE_H

/**********************************************************************************************
    @class  Tode Tode.h
    @brief  Represents a Tode Device.
 *************************************************************************************************/

#include "Constants.h"
#include "Devices.h"

/**********************************************************************************************//**
 * @class   Tode
 * @brief   **LIST** of Devices per Tode
 *************************************************************************************************/
class Tode : public MenuList {
  public:
    Tode(int _TodeAddr);                      ///< EEPROM Address of Tode Configuration
    virtual const char*   Name() override;    ///< Points to TodeName->Name()

    int UID();
    virtual MenuItem*     AddDevice(byte _DTKey, byte _ID = BNONE); ///< Menu add Device using \ref KEY
    virtual int           EAddr() { return TodeAddr; }              ///< GET this Tode's EE Address
    virtual unsigned int  RFAddr();                                 ///< GET EEPROM RF-Address
    virtual void          RFAddr(unsigned int _RFAddr);             ///< SET EEPROM RF-Address
    virtual byte          ConfigVersion();                          ///< GET Tode's Configuration Ver
    virtual void          ConfigVersion(byte _Version);             ///< SET Tode's Configuration Ver
    virtual void          SendRF_Config(int _RFTarget);
    virtual bool          IsLocal();                                ///< GET (TodeAddr == 0) set in Constructor
    MenuName*             TodeName=0;
    
  private:
    byte            GetDeviceID();              ///< Returns next available DeviceID
    void            FreeDeviceID(byte _ID);     ///< Mark DeviceID as Un-Used
    void            UsedDeviceID(byte _ID);     ///< Mark DeviceID as Used
    
    int             TodeAddr = -1;              ///< The EEPROM Start Address of the Tode
    bool            bIsLocal = false;
    unsigned long   DeviceID_UsedBitFlags = 0;

};
#endif
