// Author: G.Topan
// Note: 

#ifndef CMYLCD16X2_H
#define CMYLCD16X2_H

#include "stdint.h"
#include <LiquidCrystal.h>

class CMyLCD16x2 : public LiquidCrystal
{
private:
    // LCD size 
    static const uint8_t LCD_NUM_ROWS = 2;
    static const uint8_t LCD_NUM_COLS = 16;

public:
    CMyLCD16x2();
    virtual ~CMyLCD16x2 () {};

    /* initilize LCD display and clear it
     * return none
    */
    bool setup ();

    /* print starting from given cursor position
     *  row [in]
     *  col [in]
     *  text [in]
     *  return none
    */
    bool printAt ( uint8_t col, uint8_t row, const char* text );

    /* update display output only of updated characters
     * return none
    */
    bool refresh ();

private:
    bool _initDone;
    uint8_t _cols;
    uint8_t _rows;
    // LCD buffers
    char * _lcdBuf;
    char * _shadowBuf;
};

#endif // CMYLCD16X2_H
