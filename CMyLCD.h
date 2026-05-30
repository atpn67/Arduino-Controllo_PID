// Author: G.Topan
// Note: 

#ifndef CMYLCD_H
#define CMYLCD_H

#include "stdint.h"
#include <LiquidCrystal.h>

// values to be used with API CMyLCD::selectData()
enum {
    SELDATA_SETP_RPMFCURR = 1,
    SELDATA_SETP_RPMSCURR,
    SELDATA_SETP_PWMDUTY,
    SELDATA_RPMF_PWMDUTY,
} ESelData;

class CMyLCD : public LiquidCrystal
{
private:
    // LCD size 
    static const uint8_t LCD_NUM_ROWS = 2;
    static const uint8_t LCD_NUM_COLS = 16;

public:
    CMyLCD();
    virtual ~ CMyLCD() {};

    // initilize LCD display and clear it
    void setup();

    /* select data to show on display
     * data [in] see enum ???
     * return true on success
     *        false on errors
    */
    bool selectData ( unsigned int data );

      // 
    /* update display output with selected data
     * use selectData() to select data to show
     * return none
    */
    void update();

    /* set current rpm Set Point to show on display
     * setp_rpm [in]
     * return none
    */
    void setRpmSetpoint ( uint32_t setp_rpm );

    /* set current motor spped on fast shaft to show on display
     * speed_rpm [in]
     * return none
    */
    void setCurrSpeedFast( float speed_rpm );

    /* set current motor spped on slow shaft to show on display
     * speed_rpm [in]
     * return none
    */
    void setCurrSpeedSlow( float speed_rpm );

    /* set current PWM duty cylce to show on display
     * duty_perc [in]
     * return none
    */
    void setCurrPwmDuty ( float duty_perc );

private:
    // string buffers for data to show
    char _strData1[LCD_NUM_COLS+1];
    char _strData2[LCD_NUM_COLS+1];
    char _strData3[LCD_NUM_COLS+1];
    char _strData4[LCD_NUM_COLS+1];
    // store selection of data to show
    unsigned int _selData;
};

#endif // CMYLCD_H
