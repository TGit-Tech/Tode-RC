/**********************************************************************************************//**
 * @file    Radio.h
 * @brief   Itemize various Radio differences
 *************************************************************************************************/
#ifndef _RADIO_H
#define _RADIO_H

#include <PeerIOSerialControl.h>
#define RFCLASS PeerIOSerialControl
//---[ OBJECT ]---------------------------------------------------------
//static Adafruit_ST7735 oDisplay = Adafruit_ST7735(45, 49, 21);          //TFT-PINS (cs, dc(rs)(cd), rst)
static RFCLASS oRF = RFCLASS(1,Serial1,Serial);



#endif
