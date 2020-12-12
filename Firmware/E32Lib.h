/**********************************************************************************************//**
 * @file    DevLib.h
 * @brief   Library that implements generic Device Control structures and IO-HDW Board Options.
 *    Thinking of using E32 0xFFF Address + 0xFF.F for SecNet so all Tode's same ID#.
 *        - EEPROM Organization ( see EE_ in Constants.h )
 *    + byte[0] = Tode Size in bytes    
 *    + byte[1] = Version    
 *    + byte[2] = UID    
 *    + byte[3~12] = Tode Name 9-Chars + NULL    
 *    + byte[14] = 1st Device-Type Use-Size as device driver version compatibility?    
 *        
 *************************************************************************************************/
#ifndef _E32LIB_H
#define _E32LIB_H

#include "Constants.h"
#include "MenuLib.h"

#define DIGITAL 1
#define ANALOG 0
#define READ 1
#define WRITE 0


/*********************************************//**
 * @defgroup E32MODES Ebyte E32 Radio Mode
 * @{
 ************************************************/
#define E32_NORMMODE  0
#define E32_WAKEMODE  1
#define E32_PWRSAVE   2
#define E32_SLEEPMODE 3
///@}
/*********************************************//**
 * @defgroup E32BYTES E32 Configuration Bytes
 * @{
 ************************************************/
#define E32HEAD       0
#define E32ADDH       1
#define E32ADDL       2
#define E32SPEED      3
#define E32CHAN       4
#define E32OPTION     5
///@}
/**********************************************************************************************//**
 * @class   E32Radio
 * @brief   On-Demand Connect RF-Radio Serial to Arduino USB Serial.
 *************************************************************************************************/
class E32Radio {
  public:
    E32Radio();

    virtual void          Mode(byte _Mode);                 ///< SET \ref E32MODES
    virtual byte          Mode();                           ///< GET \ref E32MODES
    virtual void          Address(unsigned int _RFAddress);
    virtual unsigned int  Address();
    virtual void          Frequency(int _RFFrequency);
    virtual int           Frequency();
    virtual void          TxPower(byte _TxPower);
    virtual byte          TxPower();
    virtual void          Loop();
            
  private:
    void      GetParam();
    byte      E32Param[6] = { 0,0,0,0,0,0 };

    int ArduinoID;
    int iTargetArduinoID;
    int BlockingTimeoutMS = 1000;

    // Add Byte-Defines
    int Bytes[4] = { 0,0,0,0 };
    byte RBytes[10][4] = { 
      {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
      {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
    int RBI = 0;                          // Reply Bytes (RBytes) index
    int idx = 0;                          // Working 'Bytes' index 
    int iVirtualPin[63];

    int SendPacket(bool DA, bool RW, byte Pin, int Value = -1);
    void ProcessPacket();
    int ValueTo8bits(byte lByte, byte hByte);
    int ValueTo7bits(int From8BitValue);
};

/**********************************************************************************************//**
 * @class   E32PCConn
 * @brief   On-Demand Connect RF-Radio Serial to Arduino USB Serial.
 *************************************************************************************************/
class E32PCConn : public MenuName {
  public:
    E32PCConn(const char* _CName, MenuList* _SubList=0);
    
    byte                  Loop() override;
    
  protected:
    virtual byte          NameNav(byte _Key, byte _Row=0) override;      ///< NAME Navigate

  private:
    bool                  IsConnecting = false;
};
/**********************************************************************************************//**
 * @class   E32Freq
 * @brief   E32 Radio Frequency Setting.
 *          E32 - 'Channel' corresponds to 00H to 1FH assigns 410 to 441MHz 
 *          Each (1) Per 1-MHz adjust [1F=31].  Default is 17H(23DEC) + 410 = 433.
 *          Default Parameters: C0.00.00.1A.17.44
 *                              C  AH.AL.SP.CH.OPTION
 *          Current Parameters:   .00.00.1A.17.C7     ( Then set address to : 1234 )
 *************************************************************************************************/
class E32Freq : public MenuValue {
  public:
    E32Freq(const char* _CName);
    
    virtual int         Value() override;
    virtual void        Value(int _Value) override;  
};

#endif
