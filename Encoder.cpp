// Author: G.Topan
// Note: 

#include "Arduino.h"

#include "Encoder.h"
#include "AppCommon.h"

// CONSTANTS:

// LOCAL VARS:
static volatile uint32_t pulse_count = 0;
static volatile unsigned long lastMicros = 0;
static float speed_rpm = 0;

// LOCAL FUNC:
void isr_pulse_count ();

// GLOBAL FUNCS:
void Encoder_Init ( void )
{
  // Pin dell'encoder
  pinMode(PIN_ENCODER, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER), isr_pulse_count, RISING);
}

uint32_t Encoder_GetCount ( void )
{
  uint32_t num_pulse;
  // get actual encoder cout
  num_pulse = pulse_count;
  // clear old counter
  pulse_count = 0;
  // convert to rpm speed
  // speed_rpm = ((num_pulse * 60 * 1000)/(1000*12));
  //speed_rpm = ((num_pulse * 60000)/12000);
  speed_rpm = ((num_pulse * 60000)/1200);
}
  
uint32_t Encoder_GetRpm ( void )
{
  return speed_rpm;
}

void isr_pulse_count ()
{
    // debouncing
    unsigned long now = micros();
    if (now - lastMicros > 1000) {   // 500 µs = debounce
        pulse_count++;
        lastMicros = now;
    }
}
