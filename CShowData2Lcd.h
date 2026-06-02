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
private:
    static const int STRBUF_MAXLEN = (CMyLCD16x2::LCD_NUM_COLS);
    static const int STRBUF_SIZE = (CMyLCD16x2::LCD_NUM_COLS+1);
    static const int STRVAL_SIZE = 7;

public:
    CShowData2Lcd();
    virtual ~CShowData2Lcd() {};

    // initilize LCD display and clear it
    void setup();

    /**
     * select data to show on display
     * @param data [in] see enum ???
     * @return true on success
     *        false on errors
    */
    bool selectData ( unsigned int data );

    /**
     * update display output with selected data
     * use selectData() to select data to show
     * @param refreshAll [in]
     * @return none
    */
    bool refresh ( bool refreshAll = false );

    /**
     * set current rpm Set Point to show on display
     * @param setp_rpm [in]
     * @return none
    */
    void setRpmSetpoint ( uint32_t setp_rpm );

    /**
     * set current motor spped on fast shaft to show on display
     * @param speed_rpm [in]
     * @return none
    */
    void setCurrSpeedFast( float speed_rpm );

    /**
     * set current motor spped on slow shaft to show on display
     * @param speed_rpm [in]
     * @return none
    */
    void setCurrSpeedSlow( float speed_rpm );

    /**
     * set current PWM duty cylce to show on display
     * @param duty_perc [in]
     * @return none
    */
    void setCurrPwmDuty ( float duty_perc );

private:
    bool _copy2StrData( uint32_t value );
    bool _copy2StrData( float value );

private:
	// true when setup has been done
    bool _initDone;
    // string buffers for data to show
    char _strData1[STRBUF_SIZE];
    char _strData2[STRBUF_SIZE];
    char _strData3[STRBUF_SIZE];
    char _strData4[STRBUF_SIZE];
    // buffer used by _copy2StrData()
    char _strValue[STRVAL_SIZE];
    // store selection of data to show
    unsigned int _selData;
};

#endif // CSHOWDATA2LCD_H
