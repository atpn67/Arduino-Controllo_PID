// Author: G.Topan
// Note:

#include "Arduino.h"
#include "AppCommon.h"
#include "CShowData2Lcd.h"

// CONDITIONAL COMPILING
#define EN_COPY2STR   1

// CONSTANTS:
#define LCD_DLY_US    50    // the value of delay time

//#define STRBUF_SIZE   (CMyLCD16x2::LCD_NUM_COLS+1)
//#define STRBUF_MAXLEN (CMyLCD16x2::LCD_NUM_COLS)

// template of LCD display output
//                     0123456789012345
#define STR_DATA01    "Rpm setPt:  0000"
#define STR_DATA02    "Rpm curF: 0000.0"
#define STR_DATA03    "Rpm curS:   00.0"
#define STR_DATA04    "Duty cur%: 000.0"

#define POS_VAL_DATA01  12
#define POS_VAL_DATA02  10
#define POS_VAL_DATA03  10
#define POS_VAL_DATA04  10

// value used by _copy2StrData() in case of errors
#define STR_VALDEF    "#.#"

// GLOBAL API:

// constructor
CShowData2Lcd::CShowData2Lcd() : CMyLCD16x2()
{
  int val = ' ';
  memset( _strData1, val, LCD_NUM_COLS );
  _strData1[STRBUF_MAXLEN] = '\0';
  memset( _strData2, val, LCD_NUM_COLS );
  _strData2[STRBUF_MAXLEN] = '\0';
  memset( _strData3, val, LCD_NUM_COLS );
  _strData3[STRBUF_MAXLEN] = '\0';
  memset( _strData4, val, LCD_NUM_COLS );
  _strData3[STRBUF_MAXLEN] = '\0';
}

void CShowData2Lcd::setup()
{
  CMyLCD16x2::setup();

  if ( !_initDone ) {
    _initDone = true;
    // init data strings
    const char * pStr = STR_DATA01;
    strncpy( _strData1, pStr, LCD_NUM_COLS );
    pStr = STR_DATA02;
    strncpy( _strData2, pStr, LCD_NUM_COLS );
    pStr = STR_DATA03;
    strncpy( _strData3, pStr, LCD_NUM_COLS );
    pStr = STR_DATA04;
    strncpy( _strData4, pStr, LCD_NUM_COLS );
  }

  // clears the LCD screen and positions the cursor in the upper-left corner
  CMyLCD16x2::clear();
  // set the cursor to column 15, line 0
  setCursor(0,0);
    
  // select data to show
  selectData( SELDATA_SETP_RPMFCURR );
  // update display output
  refresh();
}

bool CShowData2Lcd::selectData ( unsigned int data )
{
  if ( (data < SELDATA_SETP_RPMFCURR) || (data > SELDATA_RPMF_PWMDUTY) ) {
    return false;
  }
  _selData = data;
  return true;
}

bool CShowData2Lcd::refresh ( bool refreshAll )
{
  // counter of calls of this method
  static unsigned int callCount = 0;
  // local flag
  bool fRefrAll = refreshAll;

  switch ( _selData ) {

    case SELDATA_SETP_RPMSCURR:
      CMyLCD16x2::printAt(0, 0, _strData1);
      CMyLCD16x2::printAt(1, 0, _strData3);
      break;

    case SELDATA_SETP_PWMDUTY:
      CMyLCD16x2::printAt(0, 0, _strData1);
      CMyLCD16x2::printAt(1, 0, _strData4);
      break;

    case SELDATA_RPMF_PWMDUTY:
      CMyLCD16x2::printAt(0, 0, _strData2);
      CMyLCD16x2::printAt(1, 0, _strData4);
      break;

    case SELDATA_SETP_RPMFCURR:
    default:
      CMyLCD16x2::printAt(0, 0, _strData1);
      CMyLCD16x2::printAt(1, 0, _strData2);
      break;
  }

  // every 10 calls force a complete refresh
  callCount++;
  if ( (callCount % 10) == 0 ) {
    fRefrAll = true;
  }
  return CMyLCD16x2::refresh( fRefrAll );
}

void CShowData2Lcd::setRpmSetpoint ( uint32_t setp_rpm )
{
  int numdig = 4;  // number of digits for this parameter

#if EN_COPY2STR
  _copy2StrData( setp_rpm );
  strncpy( &(_strData1[POS_VAL_DATA01]), _strValue, (STRBUF_MAXLEN - POS_VAL_DATA01) );
#else
  // TODO: delete this code?
  unsigned int pos;
  uint8_t digit;

  pos = POS_VAL_DATA01;
  digit = (uint8_t)((setp_rpm/1000)%10);
  if ( digit == 0 ) {
    _strData1[pos] = ' ';
  } else {
    _strData1[pos] = digit + '0';
  }
  pos++;
  _strData1[pos] = (char)((setp_rpm/100)%10+'0');
  pos++;
  _strData1[pos] = (char)((setp_rpm/10)%10+'0');
  pos++;
  _strData1[pos] = (char)((setp_rpm%10)+'0');
#endif
}

void CShowData2Lcd::setCurrSpeedFast( float speed_rpm )
{
#if EN_COPY2STR
  _copy2StrData( speed_rpm );
  strncpy( &(_strData2[POS_VAL_DATA02]), _strValue, (STRBUF_MAXLEN - POS_VAL_DATA02) );
#else
  // TODO: delete this code?
  unsigned int pos;
  unsigned int tmpVal = speed_rpm;
  uint8_t digit;

  pos = POS_VAL_DATA02;
  digit = (uint8_t)((tmpVal/1000)%10);
  if ( digit == 0 ) {
    _strData2[pos] = ' ';
  } else {
    _strData2[pos] = digit + '0';
  }
  pos++;
  _strData2[pos] = (char)((tmpVal/100)%10+'0');
  pos++;
  _strData2[pos] = (char)((tmpVal/10)%10+'0');
  pos++;
  _strData2[pos] = (char)(tmpVal%10+'0');
  tmpVal = (speed_rpm - tmpVal) * 10.0;
  pos++;
  pos++;
  _strData2[pos] = (char)(tmpVal%10+'0');
#endif
}

void CShowData2Lcd::setCurrSpeedSlow( float speed_rpm )
{
#if EN_COPY2STR
  _copy2StrData( speed_rpm );
  strncpy( &(_strData3[POS_VAL_DATA03]), _strValue, (STRBUF_MAXLEN - POS_VAL_DATA03) );
#else
  // TODO: delete this code?
  int pos;
  unsigned int tmpVal = (unsigned int)speed_rpm;

  pos = POS_VAL_DATA03;
  _strData3[pos] = (char)((tmpVal/10)%10+'0');
  pos++;
  _strData3[pos] = (char)(tmpVal%10+'0');
  tmpVal = (speed_rpm - tmpVal) * 10.0f;
  pos++;
  _strData3[pos] = (char)(tmpVal%10+'0');
#endif
}

void CShowData2Lcd::setCurrPwmDuty ( float duty_perc )
{
  // check input value must be 0 .. 100
  if ( duty_perc > 100 ) {
    duty_perc = 100;
  }
  if ( duty_perc < 0 ) {
    duty_perc = 0;
  }

#if EN_COPY2STR
  _copy2StrData( duty_perc );
  strncpy( &(_strData4[POS_VAL_DATA04]), _strValue, (STRBUF_MAXLEN - POS_VAL_DATA04) );
#else
  // TODO: delete this code?
  int pos;
  unsigned int tmpVal;

  tmpVal = (unsigned int)duty_perc;
  pos = POS_VAL_DATA04;
  _strData4[pos] = (char)((tmpVal/100)%10+'0');
  pos++;
  _strData4[pos] = (char)((tmpVal/10)%10+'0');
  pos++;
  _strData4[pos] = (char)(tmpVal%10+'0');
  tmpVal = (duty_perc - tmpVal) * 10.0f;
  pos++;
  pos++;
  _strData4[pos] = (char)((tmpVal)%10+'0');
#endif
}

/**
 * convert given integer value to numeric characters and copy them into a string buffer
 * starting from given position 'pos' and considering 'num' digits
 * @param value [in] value to convert in numeric characters 
 * @param _strValue [out] output buffer for value converted to a string
 * @return true on succes;
*/
bool CShowData2Lcd::_copy2StrData( uint32_t value )
{
  int pos;

  pos = 0;
  if ( value > 1000 ) {
    _strValue[pos] = (uint8_t)((value/1000)%10 + '0');
  } else {
    _strValue[pos] = ' ';
  }
  pos++;
  if ( value > 100 ) {
    _strValue[pos] = (uint8_t)((value/100)%10 + '0');
  } else {
    _strValue[pos] = ' ';
  }
  pos++;
  if ( value > 10 ) {
    _strValue[pos] = (uint8_t)((value/10)%10 + '0');
  } else {
    _strValue[pos] = ' ';
  }
  pos++;
  _strValue[pos] = (char)((value%10)+'0');
  pos++;
  _strValue[pos] = '\0';

  return true;
}

/**
 * convert given float value to numeric characters with one decimal digit and copy them 
 * into a string buffer starting from given position 'pos' and considering 'num' digits
 * @param value [in] value to convert in numeric characters 
 * @param _strValue [out] output buffer for value converted to a string
 * @return true on succes;
*/
bool CShowData2Lcd::_copy2StrData( float value )
{
  int pos;
  uint32_t tmpVal = (uint32_t)value;

  _copy2StrData( tmpVal );

  // add decimal point and decimal digit
  tmpVal = ((value - tmpVal) * 10);
  pos = (STRVAL_SIZE-3);
  _strValue[pos] = '.';
  pos++;
  _strValue[pos] = (char)((tmpVal)%10+'0');
  pos++;
  _strValue[pos] = '\0';

  return true;
}

// TODO: delete this?
#if 0
void CShowData2Lcd::printCentered(const char* text) {
    int len = strlen(text);
    int pos = (LCD_NUM_COLS - len) / 2;
    setCursor(pos, 0);
    print(text);
}
#endif
