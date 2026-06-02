// Author: G.Topan
// Note:

#include "Arduino.h"
#include "Encoder.h"
#include "ReadInputs.h"
#include "AppCommon.h"

// CONSTANTS:
#define MAX_PWMSET      255
#define MAX_ADC_VALUE   1023
#define ADC_TO_PWMSET   4

// LOCAL VARS:
static bool initDone = false;         // make init() only one time
static uint32_t trimmerADValue;       // current A/D convertsion of the trimmer 0..1023
static uint32_t pwmSetPoint;
static uint32_t rpmSetPoint;
// push button variables
static int btn01Value = 1;
static int btn01Value_sv = 1;
static int btn01Count = 0;

bool RdInputs_Init ( uint32_t initVal )
{
  if ( !initDone ) 
  {
    initDone = true;
    // Analog Input PIN_TRIMMER
    // nothing to do to initialize an analog input

    // Button 01, inout pull-up
    pinMode(PIN_BUTTON01, INPUT);
    digitalWrite(PIN_BUTTON01, HIGH);
  }

  if ( initVal > MAX_PWMSET ) {
    initVal = MAX_PWMSET;
  }
  pwmSetPoint = initVal;
  trimmerADValue = initVal * ADC_TO_PWMSET;
  return true;
}

bool RdInputs_Update ( void )
{
  // read Trimmer A/D imput
  trimmerADValue = analogRead(PIN_TRIMMER);
  pwmSetPoint = trimmerADValue/ADC_TO_PWMSET;
  //pwmSetPoint = map( trimmerADValue, 0, MAX_ADC_VALUE, 10, MAX_PWMSET );
  // convert to a proportionale value
  rpmSetPoint = map( trimmerADValue, 0, MAX_ADC_VALUE, MOTOR_RPM_FAST_MIN, MOTOR_RPM_FAST_MAX );

  // update Push Button status and counter
  btn01Value = digitalRead(PIN_BUTTON01);
  if ( btn01Value == 0 ) {
    btn01Value_sv = btn01Value;
  } else if ( btn01Value_sv == 0 ) {
    btn01Value_sv = 1;
    btn01Count++;
  }
  return true;
}

uint32_t RdInputs_pwmSetPoint ( void )
{
  return pwmSetPoint;
}

uint32_t RdInputs_SpeedSetPoint ( void )
{
  return rpmSetPoint;
}

float RdInputs_GetDuty ( void )
{
  float retVal;
  retVal = (pwmSetPoint * 100.0) / MAX_PWMSET;
  return retVal;
}

int RdInputs_GetBtnStatus ()
{
  return btn01Value;
}

int RdInputs_GetBtnPushCount ()
{
  return btn01Count;
}

void RdInputs_CltBtnPushCount ()
{
  btn01Count = 0;
}

