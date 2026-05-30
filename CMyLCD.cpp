// Author: G.Topan
// Note: 

#include "Arduino.h"
#include "AppCommon.h"
#include "CMyLCD.h"

// CONSTANTS:
//#define LCD_NUM_ROWS  16
//#define LCD_NUM_COLS  2
#define   LCD_DLY_US    50    // the value of delay time

// template of LCD display output
//                       1234567890123456
#define   ROW_STR_01    "Rpm setp:  0000 "
#define   ROW_STR_02    "Rpm curF: 000.0 "
#define   ROW_STR_03    "Rpm curS:  00.0 "
#define   ROW_STR_04    "Duty cur: 000.0%"

// GLOBAL API:

// constructor
CMyLCD::CMyLCD() : LiquidCrystal(PIN_LCD_RS, PIN_LCD_ENAB, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7)
{
  int val = ' ';
  memset( _strData1, val, LCD_NUM_COLS );
  _strData1[LCD_NUM_COLS] = '\0';
  memset( _strData2, val, LCD_NUM_COLS );
  _strData2[LCD_NUM_COLS] = '\0';
  memset( _strData3, val, LCD_NUM_COLS );
  _strData3[LCD_NUM_COLS] = '\0';
  //this->begin(LCD_NUM_ROWS, LCD_NUM_COLS);  
}

void CMyLCD::setup()
{
  // set up the LCD's number of columns and rows: 
  begin(LCD_NUM_COLS, LCD_NUM_ROWS);
  // clears the LCD screen and positions the cursor in the upper-left corner 
  clear();         
  // set the cursor to column 15, line 0
  setCursor(0,0);

  // init data strings
  const char * pStr = ROW_STR_01;
  strncpy( _strData1, pStr, LCD_NUM_COLS );
  pStr = ROW_STR_02;
  strncpy( _strData2, pStr, LCD_NUM_COLS );
  pStr = ROW_STR_03;
  strncpy( _strData3, pStr, LCD_NUM_COLS );
  pStr = ROW_STR_04;
  strncpy( _strData4, pStr, LCD_NUM_COLS );
  // select data to show
  selectData( SELDATA_SETP_RPMFCURR );
  // update display output
  update();
}

bool CMyLCD::selectData ( unsigned int data )
{
  if ( (data < SELDATA_SETP_RPMFCURR) || (data > SELDATA_RPMF_PWMDUTY) ) {
    return false;
  }
  _selData = data;
  return true;
}

void CMyLCD::update ( void )
{
  // to be completed!
  switch ( _selData ) {
    default:
      ;
  }

  /*

   lcd.setCursor(0,1);           //Set the cursor to column 15, line 1
   for (int positionCounter3 = 0; positionCounter3 < 26; positionCounter3++)
   {
     lcd.print(array2[positionCounter3]);  // Print a message to the LCD.
     delay(tim);                 //Wait for 250 microseconds
   }

  */
}

void CMyLCD::setRpmSetpoint ( uint32_t setp_rpm )
{
  _strData1[11] = (char)((setp_rpm/1000)%10+'0');
  _strData1[12] = (char)((setp_rpm/100)%10+'0');
  _strData1[13] = (char)((setp_rpm/10)%10+'0');
  _strData1[14] = (char)((setp_rpm%10)+'0');
}

void CMyLCD::setCurrSpeedFast( float speed_rpm )
{
  unsigned int tmpVal = speed_rpm; 
  _strData1[10] = (char)((tmpVal/1000)%10+'0');
  _strData1[11] = (char)((tmpVal/100)%10+'0');
  _strData1[12] = (char)((tmpVal/10)%10+'0');
  tmpVal = (speed_rpm - tmpVal) * 10.0;
  _strData1[14] = (char)((tmpVal)%10+'0');
}

void CMyLCD::setCurrSpeedSlow( float speed_rpm )
{
  unsigned int tmpVal = speed_rpm; 
  //_strData1[10] = (char)((tmpVal/1000)%10+'0');
  _strData1[11] = (char)((tmpVal/100)%10+'0');
  _strData1[12] = (char)((tmpVal/10)%10+'0');
  tmpVal = (speed_rpm - tmpVal) * 10.0;
  _strData1[14] = (char)((tmpVal)%10+'0');
}

void CMyLCD::setCurrPwmDuty ( float duty_perc )
{
  unsigned int tmpVal;

  // check input value must be 0 .. 100
  if ( duty_perc > 100 ) {
    duty_perc = 100;
  } 
  if ( duty_perc < 0 ) {
    duty_perc = 0;
  }

  tmpVal = duty_perc;
  _strData1[10] = (char)((tmpVal/1000)%10+'0');
  _strData1[11] = (char)((tmpVal/100)%10+'0');
  _strData1[12] = (char)((tmpVal/10)%10+'0');
  tmpVal = (duty_perc - tmpVal) * 10.0;
  _strData1[14] = (char)((tmpVal)%10+'0');
}

// TODO: delete this?
/*
void CMyLCD::printCentered(const char* text) {
    int len = strlen(text);
    int pos = (LCD_NUM_COLS - len) / 2;
    setCursor(pos, 0);
    print(text);
}
*/

