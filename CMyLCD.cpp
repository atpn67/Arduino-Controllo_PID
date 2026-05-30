// Author: G.Topan
// Note: 

#include "Arduino.h"
#include "AppCommon.h"
#include "CMyLCD.h"

// CONSTANTS:
#define LCD_NUM_ROWS  16
#define LCD_NUM_COLS  2

// GLOBAL API:

///*
// constructor
CMyLCD::CMyLCD() : LiquidCrystal(PIN_LCD_RS, PIN_LCD_ENAB, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7)
{
  // to be completed
  //this->begin(LCD_NUM_ROWS, LCD_NUM_COLS);  
}

void CMyLCD::init()
{
  // set up the LCD's number of columns and rows: 
  this->begin(LCD_NUM_ROWS, LCD_NUM_COLS);  
}

void CMyLCD::printCentered(const char* text) {
    int len = strlen(text);
    int pos = (16 - len) / 2;
    setCursor(pos, 0);
    print(text);
}

void CMyLCD::api1 ( void )
{

}

void CMyLCD::api2 ( void )
{

}
