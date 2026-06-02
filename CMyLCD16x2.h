// Author: G.Topan
// Note:

#ifndef CMYLCD16X2_H
#define CMYLCD16X2_H

#include "stdint.h"
#include <LiquidCrystal.h>

class CMyLCD16x2 : public LiquidCrystal
{
protected:
    // LCD size
    static const uint8_t LCD_NUM_ROWS = 2;
    static const uint8_t LCD_NUM_COLS = 16;

public:
    CMyLCD16x2();
    virtual ~CMyLCD16x2 ();

    /**
     * initilize LCD display and clear it
     * @return none
    */
    bool setup ();

    /**
     * print starting from given cursor position
     *  @param row [in]
     *  @param col [in]
     *  @param text [in]
     *  @return none
    */
    bool printAt ( uint8_t row, uint8_t col, const char* text );

    void clear ();

    /**
     * update display output only of updated characters
     * @param refreshAll [in]
     * @return none
    */
    bool refresh ( bool refreshAll );

private:
    bool _initDone;
    uint8_t _cols;
    uint8_t _rows;
    // LCD buffers
    char * _lcdBuf;
    char * _shadowBuf;
};

#endif // CMYLCD16X2_H
