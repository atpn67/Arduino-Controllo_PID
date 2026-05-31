// Author: G.Topan
// Note:

#include "Arduino.h"
#include "Encoder.h"
#include "AppCommon.h"

// CONSTANTS:
// PWM motor constants
#define MOTOR_ENC_PPR       12      // Encoder pulse per revolution
#define MOTOR_GEAR_RATIO    48      // motor fast shaft to slow shaft reduction 
// local control constants
#define DEBOUNCE_TIME_US    500     // software debouncing min time, 500 µs debounce
#define FREQ_MS_TO_RPM      60000   // converts [1/milliseconds] = Hz*1000 to rpm

// LOCAL VARS:
static bool initDone = false;        // make Encoder_init only one time
static uint32_t timeLast_ms = 0;      // time of last Encoder_GetCount() call
static float speed_rpm = 0;           // [rpm] last computed speed
static volatile uint32_t pulse_count = 0;   // shared puls counter

// LOCAL FUNC:
void isr_pulse_count ();

// GLOBAL FUNCS:
void Encoder_Init ( void )
{
  if ( !initDone ) {
    initDone = true;
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

  // disable interrupts
  // get actual encoder couunter
  // and clear old counter
  cli();
  num_pulse = pulse_count;
  pulse_count = 0;
  sei();

  // convert counter to rpm speed if called @ 1Hz
  // speed_rpm = ((num_pulse * 60 * 1000)/(1000*12));
  // convert counter to rpm speed if called @ 10Hz = 100ms
  //speed_rpm = ((num_pulse * 60000)/1200);
  //speed_rpm = ((num_pulse * FREQ_MS_TO_RPM)/(MOTOR_ENC_PPR*100));
  // more accurate speed value, take in accout true time window
  speed_rpm = ((num_pulse * FREQ_MS_TO_RPM)/(MOTOR_ENC_PPR*timeWindow_ms));

  return num_pulse;
}

float Encoder_GetRpm ( void )
{
  return speed_rpm;
}

float Encoder_GetRpmSlow ( void )
{
  return (speed_rpm / MOTOR_GEAR_RATIO);
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
