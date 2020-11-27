/**********************************************************************************************//**
   @file Tode.h
   @brief Tode Class.
   <PRE>
    Lets discuss this class with lots of details and explain everything here??
    DOES|                             SPACES              WORK |
   </PRE>
   @authors
      2019-12-16  TGit-Tech   Origin
 *************************************************************************************************/
#ifndef _TODE_H
#define _TODE_H


#include "Constants.h"
#include "Devices.h"

/**********************************************************************************************//**
    @class  Tode Tode.h
    @brief  Represents a Tode Device.

    - EEPROM Organization ( see EE_ in Constants.h )
      + byte[0] = Tode Size in bytes
      + byte[1] = Version
      + byte[2] = UID
      + byte[3~12] = Tode Name 9-Chars + NULL
      + byte[14] = 1st Device Size

    @todo   IF ThisTode Size < 50 then Remote Tode's start at 50, else 100
 *************************************************************************************************/
class Tode : public MenuList {
  public:
    Tode(int _TodeAddr);
    virtual const char* Name() override;
    /***********************************************************************************//**
       @brief Adds a Device to the Tode
       @param _DT_Type              - The Constants.h Device Type definition
       @return  Pointer to the Parameter List for the added Device.
       @note    Allocates EEPROM memory; Do not use for auto-loading devices.
     **************************************************************************************/
    virtual MenuList*   AddDevice(int _DT_Type);

    int UID();
    virtual int         EndAddr() { return TodeEndAddr; }
    virtual int         EAddr() { return TodeAddr; }
    virtual int         RFAddr();
    virtual void        RFAddr(int _RFAddr);
    virtual void        SendRF_Config(int _RFTarget);
    
    
    MenuName*           TodeName=0;
    
  private:
    void      ELoadConfig();        ///< Load Tode Configuration from EEPROM
    int       TodeAddr = -1;        ///< The EEPROM Address of the Tode
    int       TodeEndAddr = -1;     ///< The last EEPROM Address of the Tode
    int       ConfigVer = -1;       ///< The Configuration Version of the Tode

};
#endif
