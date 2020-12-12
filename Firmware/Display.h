/**********************************************************************************************//**
 * @file    Display.h
 * @brief   Itemize various Display differences
 *************************************************************************************************/
#ifndef _DISPLAY_H
#define _DISPLAY_H

//Uncomment the Display Type (Pins identified in Object-Intializer)
#define ADAFRUIT_GFX

//######################################################################
#if defined(ADAFRUIT_GFX)
//######################################################################
#include <SPI.h>
#include <Adafruit_GFX.h>

#include <Adafruit_ST7735.h>
#include <MyFonts/OneSlot9pt7b.h>             //Problems? https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
#include <MyFonts/DroidSansMono9pt7b.h>
//#include <MyFonts/Roboto_Mono_Bold_14.h>
//#include <Fonts/FreeSansBold9pt7b.h>

//---[ OBJECT ]---------------------------------------------------------
//static Adafruit_ST7735 oDisplay = Adafruit_ST7735(45, 49, 21);          //TFT-PINS (cs, dc(rs)(cd), rst)
static Adafruit_ST7735 oDisplay = Adafruit_ST7735(49, 47, 23);            //TFT(cs, dc(rs)(cd), rst)
#define DSPCLASS Adafruit_ST7735

/******************************************************************************//**
 * @defgroup DSPCOLORS Display Colors
 *           In Display.h
 * @{
 *********************************************************************************/
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
///@}
/******************************************************************************//**
 * @defgroup DSPSETTINGS Display Settings
 *           In Display.h
 * @{
 *********************************************************************************/
//---[ ASSIGNMENTS ]----------------------------------------------------
#define VALCOL 72             // Pixel Column In-Row Value Starts at
#define SCREENWIDTH 128
#define SCREENHEIGHT 160
#define ITEMCHARWIDTH 7       // Was 6 ( includes post char spacing )
#define ITEMCHARHEIGHT 14     // Was 13
#define TITLECHARHEIGHT 13
//---[ COMMANDS ]-------------------------------------------------------
#define DSP_BEGIN initR(INITR_BLACKTAB)
#define DSP_SETROTATION setRotation(2)
#define CLEARSCREEN fillScreen(0x0000)
#define TITLEFONT setFont(&DroidSansMono9pt7b)
#define ITEMFONT setFont(&OneSlot9pt7b)
#define SETCURSOR setCursor
//---[ FORMAT ]---------------------------------------------------------
#define HIGHLIGHT setTextColor(GREENYELLOW)
#define NORMAL setTextColor(WHITE, RED)
///@}
#endif
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



//######################################################################
#if defined(U8G2LIB)
//######################################################################
#include <U8g2lib.h>
static U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R3, U8X8_PIN_NONE);
#endif
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



//######################################################################
#endif
