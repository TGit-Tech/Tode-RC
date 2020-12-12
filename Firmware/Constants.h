/******************************************************************************************************************//**
 * @file Constants.h
 * @brief Constants to be included in all files
 **********************************************************************************************************************/
#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include<Arduino.h>

#define DEBUG         10
#define FIRMWARE      "Firmware 20C9"

// E32 - Radio Pin Connections
#define E32M0 22
#define E32M1 20
#define E32TXD 18
#define E32RXD 19
#define E32AUX 21

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
#define BNONE         0xFF
#define KEYNONE       0xEF

// 0x[D]isplay Control
#define KEY_CSHOWLIST 0xDF    ///< [C]lear & Show MenuList on Display
#define KEY_SHOWLIST  0xDE    ///< Show MenuList on Display
#define KEY_CSHOWSET  0xDD    ///< [C]lear & Show the Name[SET]Tool on Display
#define KEY_SHOWSET   0xDC    ///< Show the Name[SET]Tool on Display
#define KEY_SHOWROW   0xDB    ///< Show a single List-Row on the Display

// 0x[C]ommand Control
#define GOTO_SUBLIST  0xCF    ///< Activated in NameNav() of MenuName
#define EXIT_SET      0xCE
#define EXIT_SAVESET  0xCD

// 0x[B]
#define DT_NONE       -1
#define DT_NOTGIVEN   -2

// 0x[B] Device Types
#define DT_NONE       0x7F    ///< MenuItem
#define DT_RW_ONOFF   0x7E    ///< On/Off Switching Device
#define DT_RO_ONOFF   0x7D    ///< On/Off Monitoring Device
#define DT_RO_PRESS   0x7C    ///< Pressure Device
#define DT_RO_TEMP    0x7B    ///< Temperature Device
#define DT_RO_DIST    0x7A    ///< Distance Sensing Device
///@}
/******************************************************************************//**
 * @defgroup DTP Device-Type Parameter
 * @{
 *********************************************************************************/
#define DTP_DEVTYPE   0xEE    ///< Return Device Type
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
#define SEL_LOOP      5
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
 * @defgroup IOHDW IO-Hardware
 * @{
 *********************************************************************************/
#define IOHDW_WING 1
///@}
/******************************************************************************//**
 * @defgroup CMD Command() Keys
 * @{
 *********************************************************************************/
#define CMD_RETNONE     0xFFFF;
#define CMD_NOITEM      0xFFFE;
///@}
/******************************************************************************//**
 * @defgroup AEB [A]llocation-Size of [E]EPROM in [B]ytes.
 *  (30) Devices (12-bytes)[ TYPE. ID. 10NAME ] per Tode  = 360B x 10Todes
 *  (10) Todes ( 13-bytes )[ RFH. RFL. VER. 10NAME ]      = +130B TOTAL: 3730
 *  LOCAL SETTINGS 3730 to 4096 = 366B / 30LocalDevices = 12B/ea
 * @{
 *********************************************************************************/
//#define AEB_VER 1

#define AEB_TODEALLOC   373       ///< Bytes to allocate for each Tode with Devices
#define AEB_TODEHEAD    13        ///< Bytes to allocate for each Tode Definition
#define AEB_DEVALLOC    12        ///< Bytes to allocate for each Device
#define AEB_MAXTODES    10        ///< Maximum Number of Todes
#define AEB_MAXDEVICES  30        ///< Maximum Number of Devices per Tode

#define AEB_MAX         10        ///< Maximum Default Allocation for Char[]'s
#define AEB_TODENAME    10        ///< TodeName Size to be (9)Chars + NULL
#define AEB_DEVICENAME  10        ///< Device Names to be (9)Chars + NULL
///@}
/******************************************************************************//**
 * @defgroup EMC [E]EPROM [M]emory [C]onstants
 * @{
 *********************************************************************************/
#define EMC_LOCALSETTINGS     3730  ///< Local Settings SecNet First at this address.
#define EMC_SECNET            3730
///@}
/******************************************************************************//**
 * @defgroup EMO [E]EPROM [M]emory [O]ffsets ( PER TODE )
 * @{
 *********************************************************************************/
#define EMO_TODERF      0     //[0][1]      2-Byte RF Address
#define EMO_TODEVER     2     //[2]         1-Byte Config Version (0~255)
#define EMO_TODENAME    3     //[3]...[12]  10-Byte Tode Name

//[DEV]ice
#define EMO_DEVTYPE     0     //[0]         1-Byte Device Type
#define EMO_DEVID       1     //[1]         1-Byte Device ID
#define EMO_DEVNAME     2     //[2]...[11]  10-Byte Device Name (AEB_DEVICENAME[10])
///@}


//----------------------------------------------------------------------------------
// [D]E[B]UG Macros  DBERROR, DBINIT, DBINFO, DBENTER   A-Arg L-Line
//----------------------------------------------------------------------------------
#if DEBUG>0 // DEBUG Level-1: Include ERROR
#define DBERRORAAL(x,y,z) Serial.print(F("!ERROR!-"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.println(F(")"));
#define DBERRORAA(x,y,z) Serial.print(F("!ERROR!-"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.print(F(")"));
#define DBERRORAL(x,y) Serial.print(F("!ERROR!-"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBERRORA(x,y) Serial.print(F("!ERROR!-"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBERRORL(x) Serial.print(F("!ERROR!-"));Serial.println((F(x)));
#define DBERROR(x) Serial.print(F("!ERROR!-"));Serial.print((F(x)));
#else
#define DBERRORAAL(x,y,z)
#define DBERRORAA(x,y,z)
#define DBERRORAL(x,y)
#define DBERRORA(x,y)
#define DBERROR(x)
#define DBERRORL(x)
#endif

#if DEBUG>1 // DEBUG Level-2; Constructors
#define DBINITAAL(x,y,z) Serial.print(F("@"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.println(F(")"));
#define DBINITAA(x,y,z) Serial.print(F("@"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.print(F(")"));
#define DBINITAL(x,y) Serial.print(F("@"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBINITA(x,y) Serial.print(F("@"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBINIT(x) Serial.print(F("@"));Serial.print((F(x)));
#define DBINITL(x) Serial.print(F("@"));Serial.println((F(x)));
#else
#define DBINITAAL(x,y,z)
#define DBINITAA(x,y,z)
#define DBINITAL(x,y)
#define DBINITA(x,y)
#define DBINIT(x)
#define DBINITL(x)
#endif

#if DEBUG>2 // DEBUG Level-3; Include INFO
#define DBINFOAAL(x,y,z) Serial.print(F("..."));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.println(F(")"));
#define DBINFOAA(x,y,z) Serial.print(F("..."));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.print(F(")"));
#define DBINFOAL(x,y) Serial.print(F("..."));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBINFOA(x,y) Serial.print(F("..."));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBINFOL(x) Serial.print(F("..."));Serial.println((F(x)));
#define DBINFO(x) Serial.print(F("..."));Serial.print((F(x)));
#else
#define DBINFOAAL(x,y,z)
#define DBINFOAA(x,y,z)
#define DBINFOAL(x,y)
#define DBINFOA(x,y)
#define DBINFOL(x)
#define DBINFO(x)
#endif

#if DEBUG>3 // DEBUG Level-4; Include ENTER
#define DBENTERAAL(x,y,z) Serial.print(F("#"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.println(F(")"));
#define DBENTERAA(x,y,z) Serial.print(F("#"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(","));Serial.print((z));Serial.print(F(")"));
#define DBENTERAL(x,y) Serial.print(F("#"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.println(F(")"));
#define DBENTERA(x,y) Serial.print(F("#"));Serial.print((F(x)));Serial.print(F("("));Serial.print((y));Serial.print(F(")"));
#define DBENTERL(x) Serial.print(F("#"));Serial.println((F(x)));
#define DBENTER(x) Serial.print(F("#"));Serial.print((F(x)));
#else
#define DBENTERAAL(x,y,z)
#define DBENTERAA(x,y,z)
#define DBENTERAL(x,y)
#define DBENTERA(x,y)
#define DBENTERL(x)
#define DBENTER(x)
#endif

#endif
