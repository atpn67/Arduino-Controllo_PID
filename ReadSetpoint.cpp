// Author: G.Topan
// Note: 

#include "Arduino.h"
#include "ReadSetpoint.h"
#include "AppCommon.h"

// CONSTANTS:
#define MAX_PWMSET      255
#define ADC_TO_PWMSET   4

// LOCAL VARS:
static uint32_t val_trimmer;
static uint32_t pwm_setpoint;


void RdSetpoint_Init ( uint32_t initVal )
{
  // nothing to do to initialize an analog input
  if ( initVal > MAX_PWMSET ) {
    initVal = MAX_PWMSET;
  }
  pwm_setpoint = initVal;
  val_trimmer = initVal * ADC_TO_PWMSET;
}

void RdSetpoint_Update ( void )
{
  // read starting setpoint
  val_trimmer = analogRead(PIN_TRIMMER);
  pwm_setpoint = val_trimmer/ADC_TO_PWMSET;
}

uint32_t RdSetpoint_Get ( void )
{
  return pwm_setpoint;
}

float RdSetpoint_GetDuty ( void )
{
  float retVal;
  retVal = (pwm_setpoint * 100.0) / MAX_PWMSET;
  return retVal;
}


