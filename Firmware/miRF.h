/******************************************************************************************************************//**
 * @file    miRF.h
 * @brief   **ITEM** Extends miLib.h for the 'Radio' Menu Items
 *********************************************************************************************************************/
#ifndef _miRF_H
#define _miRF_H

#include "miLib.h"
#include "lib/EEMap.h"
/******************************************************************************************************************//**
 * @class   RadioAddress
 * @brief   On-Demand initialized Item-Object Tool used to set Textual Names on a new screen.
 *********************************************************************************************************************/
class RadioAddress : public MenuValue {
  public:
    RadioAddress();
    virtual int         Value() override;
    virtual void        Value(int _Value) override;
};
/******************************************************************************************************************//**
 * @class   RadioFrequency
 * @brief   Radio Frequency Setting.
 *          Default Parameters: C0.00.00.1A.17.44
 *                              C  AH.AL.SP.CH.OPTION
 *          Current Parameters:   .00.00.1A.17.C7     ( Then set address to : 1234 )
 *********************************************************************************************************************/
class RadioFrequency : public MenuValue {
  public:
    RadioFrequency();
    
    virtual int         Value() override;
    virtual void        Value(int _Value) override;
};
/******************************************************************************************************************//**
 * @class   RadioTxPower
 * @brief   Radio Tx Power Setting.
 *********************************************************************************************************************/
class RadioTxPower : public MenuValue {
  public:
    RadioTxPower();
    virtual int         Value() override;
    virtual void        Value(int _Value) override;
};
/******************************************************************************************************************//**
 * @class   RadioPCConn
 * @brief   On-Demand Connect RF-Radio Serial to Arduino USB Serial.
 *********************************************************************************************************************/
class RadioPCConn : public MenuValue {
  public:
    RadioPCConn();
    virtual int         Value() override;
    virtual void        Value(int _Value) override;
    virtual byte        Loop() override;
};
//_____________________________________________________________________________________________________________________
#endif
