// Author: G.Topan
// Note:

#ifndef CSHOWDATA2LCD_H
#define CSHOWDATA2LCD_H

#include "stdint.h"
#include "CMyLcd16x2.h"

// values to be used with API CShowData2Lcd::selectData()
enum {
    SELDATA_SETP_RPMFCURR = 1,
    SELDATA_SETP_RPMSCURR,
    SELDATA_SETP_PWMDUTY,
    SELDATA_RPMF_PWMDUTY,
} ESelData;

class CShowData2Lcd : public CMyLCD16x2
{
public:
    CShowData2Lcd();
    virtual ~CShowData2Lcd() {};

    // initilize LCD display and clear it
    void setup();

    /* select data to show on display
     * data [in] see enum ???
     * return true on success
     *        false on errors
    */
    bool selectData ( unsigned int data );

    /* update display output with selected data
     * use selectData() to select data to show
     * return none
    */
    bool refresh();

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
    char _strData1[CMyLCD16x2::LCD_NUM_COLS+1];
    char _strData2[CMyLCD16x2::LCD_NUM_COLS+1];
    char _strData3[CMyLCD16x2::LCD_NUM_COLS+1];
    char _strData4[CMyLCD16x2::LCD_NUM_COLS+1];
    // store selection of data to show
    unsigned int _selData;
};

#endif // CSHOWDATA2LCD_H
