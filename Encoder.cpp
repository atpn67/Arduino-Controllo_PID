// Author: G.Topan
// Note: 

#include "Arduino.h"

#include "Encoder.h"
#include "AppCommon.h"

// CONSTANTS:
#define DEBOUNCE_TIME_US    500       // software debouncing min time, 500 µs debounce

// LOCAL VARS:
static bool init_done = false;        // make Encoder_init only one time
static uint32_t timeLast_ms = 0;      // time of last Encoder_GetCount() call
static float speed_rpm = 0;           // [rpm] last computed speed
static volatile uint32_t pulse_count = 0;   // shared puls counter

// LOCAL FUNC:
void isr_pulse_count ();

// GLOBAL FUNCS:
void Encoder_Init ( void )
{
  if ( !init_done ) {
    init_done = true;
    // Input PIN of encoder signal
    pinMode(PIN_ENCODER, INPUT_PULLUP);
    // save actual time
    timeLast_ms = millis();
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER), isr_pulse_count, FALLING);
  }
}

uint32_t Encoder_GetCount ( void )
{
  uint32_t num_pulse = 0;
  uint32_t timeWindow_ms = (millis() - timeLast_ms);

  // get actual encoder cout
  num_pulse = pulse_count;
  // clear old counter
  pulse_count = 0;
  // convert to rpm speed
  // speed_rpm = ((num_pulse * 60 * 1000)/(1000*12));
  //speed_rpm = ((num_pulse * 60000)/1200);
  // more accurate speed value, take in accout true time window
  speed_rpm = ((num_pulse * 60000)/(12*timeWindow_ms));
}
  
uint32_t Encoder_GetRpm ( void )
{
  return speed_rpm;
}

void isr_pulse_count ()
{
    // software debouncing, count microseconds since last interrupt 
    static volatile unsigned long lastMicros = 0;   

    // debouncing
    unsigned long now = micros();
    if (now - lastMicros > DEBOUNCE_TIME_US) {   
        pulse_count++;
        lastMicros = now;
    }
}
