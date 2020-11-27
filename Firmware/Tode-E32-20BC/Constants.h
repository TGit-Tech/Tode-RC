/******************************************************************************************************************//**
 * @file Constants.h
 * @brief Constants to be included in all files
 **********************************************************************************************************************/
#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include<Arduino.h>

#define E32ADDR       0x0000
#define DEBUG         0
#define FIRMWARE      "Build    20FM"

/******************************************************************************//**
 * @defgroup KEY Navigate() Keys
 * @{
 *********************************************************************************/
// 0x[F]-Key Presses
#define KEYRIGHT      0xFE
#define KEYLEFT       0xFD
#define KEYUP         0xFC
#define KEYDOWN       0xFB
#define KEYSET        0xFA
#define KEYOKAY       0xF9
#define KEYPRESSMIN   0xF0

// 0x[E]xit
#define KEYNONE       0xEF

// 0x[D]isplay Control
#define KEY_CSHOWLIST 0xDF    ///< [C]lear & Show MenuList on Display
#define KEY_SHOWLIST  0xDE    ///< Show MenuList on Display
#define KEY_CSHOWSET  0xDD    ///< [C]lear & Show the Name[SET]Tool on Display
#define KEY_SHOWSET   0xDC    ///< Show the Name[SET]Tool on Display
#define KEY_SHOWROW   0xDB    ///< Show a single List-Row on the Display

// 0x[C]ommand Control
#define GOTO_SUBLIST  0xCF
#define EXIT_SET      0xCE
#define EXIT_SAVESET  0xCD

// 0x[B] Device Types
#define DT_ONOFF      0xBF    ///< On/Off Switching Device
#define DT_PRESS      0xBE    ///< Pressure Device
#define DT_TEMP       0xBD    ///< Temperature Device
#define DT_DIST       0xBC    ///< Distance Sensing Device
///@}
/******************************************************************************//**
 * @defgroup SEL Item-Element 'Selected'
 * @{
 *********************************************************************************/
#define SEL_NONE      0       ///< The Item has no Selected components
#define SEL_ITEM      1       ///< The Item is Selected in a List
#define SEL_VALUE     2       ///< The Value is Selected in a List
#define SEL_SETVALUE  3       ///< The Value is Selected & being Set in a List
#define SEL_SETNAME   4       ///< The Name is Selected & being Set with the SetNameTool
///@}
/******************************************************************************//**
 * @defgroup SS Set Selected
 * @{
 *********************************************************************************/
#define SS_TITLE        44
#define SS_POSITION     45
#define SS_BACK         46
#define SS_SPACE        47
#define SS_SAVE         93
///@}
/******************************************************************************//**
 * @defgroup AEB [A]llocation of [E]EPROM in [B]yte-Size
 * @{
 *********************************************************************************/
#define AEB_MAX 10          ///< Maximum Default Allocation for Char[]'s
#define AEB_SIZE 1
#define AEB_VER 1
//#define AEB_TODEUID 1
#define AEB_TODENAME 10     ///< TodeName Size to be (9)Chars + NULL
#define AEB_DEVICENAME 7    ///< Device Names to be (6)Chars + NULL
///@}
/******************************************************************************//**
 * @defgroup EMC [E]EPROM [M]emory [C]onstants
 * @{
 *********************************************************************************/
#define EMC_SECNET      0     ///< [0][1] 2-Byte Secure Network 0xFF FF
#define EMC_THISTODE    2     ///< Start of ThisTode Constant Location
#define EMC_REMTODES    50    ///< Start of Remote Todes Configuration
///@}
/******************************************************************************//**
 * @defgroup EMO [E]EPROM [M]emory [O]ffsets
 * @{
 *********************************************************************************/
#define EMO_TODESIZE 0        //[0]         1-Byte Tode Size      (0~255)
#define EMO_RFADDR 1          //[1][2]      2-Byte E32 Address    0xFF.FF
#define EMO_TODEVER 3         //[3]         1-Byte Config Version (0~255)
#define EMO_TODENAME 4        //[4]...[13]  10-Byte Tode Name
#define EMO_1STDEVICE 14      //[14]        1st Device on Tode
//[DEV]ice
#define EMO_DEVSIZE 0         //[0]         1-Byte Device Size
#define EMO_DEVTYPE 1         //[1]         1-Byte Device Type
#define EMO_DEVNAME 2         //[2]...[8]   7-Byte Device Name (AEB_DEVICENAME[7])
#define EMO_DEVPIN 9          //[9]         1-Byte Device Master Pin (For Identifier)
// LOCAL ONLY DEV TYPES SPECIFIC
#define EMO_DEVPIN2 10
///@}
//----------------------------------------------------------------------------------
// [D]E[B]UG Macros
//----------------------------------------------------------------------------------
#if DEBUG>0 // DEBUG Level-1: Include ERROR
#define DBERRORAL(x,y) Serial.print(F("!ERROR!-"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBERRORA(x,y) Serial.print(F("!ERROR!-"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBERROR(x) Serial.print(F("!ERROR!-"));Serial.print((F(x)));
#define DBERRORL(x) Serial.print(F("!ERROR!-"));Serial.println((F(x)));
#else
#define DBERRORAL(x,y)
#define DBERRORA(x,y)
#define DBERROR(x)
#define DBERRORL(x)
#endif
#if DEBUG>1 // DEBUG Level-2; Constructors
#define DBINITAL(x,y) Serial.print(F("@"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBINITA(x,y) Serial.print(F("@"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBINIT(x) Serial.print(F("@"));Serial.print((F(x)));
#define DBINITL(x) Serial.print(F("@"));Serial.println((F(x)));
#else
#define DBINITAL(x,y)
#define DBINITA(x,y)
#define DBINIT(x)
#define DBINITL(x)
#endif
#if DEBUG>2 // DEBUG Level-3; Include INFO
#define DBINFOAL(x,y) Serial.print(F("..."));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBINFOA(x,y) Serial.print(F("..."));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBINFOL(x) Serial.print(F("..."));Serial.println((F(x)));
#define DBINFO(x) Serial.print(F("..."));Serial.print((F(x)));
#else
#define DBINFOAL(x,y)
#define DBINFOA(x,y)
#define DBINFOL(x)
#define DBINFO(x)
#endif
#if DEBUG>3 // DEBUG Level-4; Include ENTER
#define DBENTERAL(x,y) Serial.print(F("#"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBENTERA(x,y) Serial.print(F("#"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBENTERL(x) Serial.print(F("#"));Serial.println((F(x)));
#define DBENTER(x) Serial.print(F("#"));Serial.print((F(x)));
#else
#define DBENTERAL(x,y)
#define DBENTERA(x,y)
#define DBENTERL(x)
#define DBENTER(x)
#endif
#endif
