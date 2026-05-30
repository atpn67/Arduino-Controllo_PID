// Author: G.Topan
// Note: 

#include "Arduino.h"
#include "AppCommon.h"
#include "CMyLCD16x2.h"

// CONSTANTS:
#define   LCD_DLY_US    50    // the value of delay time

// GLOBAL API:

// constructor
CMyLCD16x2::CMyLCD16x2() : LiquidCrystal(PIN_LCD_RS, PIN_LCD_ENAB, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7),
    _lcdBuf(nullptr), _shadowBuf(nullptr)
{
  _initDone = false;
}

bool CMyLCD16x2::setup()
{
  if ( !_initDone ) {
    _initDone = true;

    // set up the LCD's number of columns and rows: 
    LiquidCrystal::begin(LCD_NUM_COLS, LCD_NUM_ROWS);
    _cols = LCD_NUM_COLS;
    _rows = LCD_NUM_ROWS;

    int bufSize = _cols * _rows;
    _lcdBuf = new char[bufSize];
    _shadowBuf = new char[bufSize];

    memset(_lcdBuf, ' ', bufSize);
    memset(_shadowBuf, 0xFF, bufSize); // forza refresh completo  
  }
}

bool CMyLCD16x2::printAt(uint8_t col, uint8_t row, const char* text) 
{
  if ( !_initDone ) {
    // setup() not yet called
    return false;
  }
  {
    int size = _cols * _rows;
    int idx = row * _cols + col;
    int len = strlen(text);

    for (int i = 0; i < len && (idx + i) < size; i++) {
        _lcdBuf[idx + i] = text[i];
    }
  }
  return true;
}

bool CMyLCD16x2::refresh ( void )
{
  if ( !_initDone ) {
    // setup() not yet called
    return false;
  }
  {
    int size = _cols * _rows;
    
    for (int i = 0; i < size; i++) {
        if (_lcdBuf[i] != _shadowBuf[i]) {
            uint8_t row = i / _cols;
            uint8_t col = i % _cols;

            setCursor(col, row);
            write(_lcdBuf[i]);
            _shadowBuf[i] = _lcdBuf[i];
            //delayMicroseconds(LCD_DLY_US);
        }
    }
  }
  return true;
}
