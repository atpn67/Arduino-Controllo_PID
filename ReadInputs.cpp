// Author: G.Topan
// Note:

#include "Arduino.h"
#include "ReadInputs.h"
#include "AppCommon.h"

// CONSTANTS:
#define MAX_PWMSET      255
#define MAX_ADC_VALUE   1023
#define ADC_TO_PWMSET   4

// LOCAL VARS:
static bool initDone = false;         // make Encoder_init only one time
static uint32_t val_trimmer;
static uint32_t pwm_setpoint;

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
  pwm_setpoint = initVal;
  val_trimmer = initVal * ADC_TO_PWMSET;
  return true;
}

bool RdInputs_Update ( void )
{
  // read starting setpoint
  val_trimmer = analogRead(PIN_TRIMMER);
  pwm_setpoint = val_trimmer/ADC_TO_PWMSET;
  return true;
}

uint32_t RdInputs_SetPoint ( void )
{
  return pwm_setpoint;
}

float RdInputs_GetDuty ( void )
{
  float retVal;
  retVal = (pwm_setpoint * 100.0) / MAX_PWMSET;
  return retVal;
}


