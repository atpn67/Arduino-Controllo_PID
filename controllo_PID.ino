// Author: G.Topan
// Note:

#include "Encoder.h"
#include "ReadSetpoint.h"
#include "CShowData2Lcd.h"
#include "AppCommon.h"

// CONSTANTS:

// pin list
#define PIN_ENCODER   2
#define PIN_PWM_OUT   9
#define PIN_TRIMMER   0

// timeout and cycle count
#define CYCLE_TIME_MS 100
#define NUM_LOOP_LED  3
#define NUM_LOOP_1S   10

#define ADC_TO_PWMSET 4

// GLOBAL VARS:
uint32_t tNext_ms = 0;
uint32_t tCurr_ms = 0;

CShowData2Lcd oLcdShow;

void setup()
{
  Serial.begin(115200);

  // init Hw
  Encoder_Init();
  RdSetpoint_Init(0);
  // read starting setpoint
  RdSetpoint_Update();
  // init LCD class
  oLcdShow.setup();

  // init onboard LED output
  pinMode(LED_BUILTIN, OUTPUT);
  // init cycle time variables
  tCurr_ms = millis();
  tNext_ms = tCurr_ms + CYCLE_TIME_MS;

  // start PWM output
  analogWrite(PIN_PWM_OUT, RdSetpoint_Get());
}

void loop()
{
  static uint32_t loop_count = 0;

  tCurr_ms= millis();

  if (tCurr_ms >= tNext_ms)
  {
    tNext_ms += CYCLE_TIME_MS;
    loop_count++;

    task_100ms();

    if(loop_count % NUM_LOOP_1S == 0)
    {
      task_1000ms();
    }

    if(loop_count % NUM_LOOP_LED == 0)
    {
      doLedBlink();
    }
  }
}

// commento
void task_100ms()
{
  uint32_t rpmVal;

  // command motor speed
  analogWrite(PIN_PWM_OUT, RdSetpoint_Get());

  Encoder_GetCount();
  rpmVal = Encoder_GetRpm();

  // get new rpm setpoint value
  RdSetpoint_Update();
}

// commento
void task_1000ms()
{
  uint32_t tmpVal = RdSetpoint_Get();
  float dutyVal = RdSetpoint_GetDuty();
  uint32_t rpmSpeed = Encoder_GetRpm();

  //Serial.print("conteggio: ");
  //Serial.println(num_pulse, DEC);
  Serial.print("setpoint: ");
  Serial.print(tmpVal, DEC);
  Serial.print("  Set Duty: ");
  Serial.print(dutyVal, 1);
  Serial.print("  velocità: ");
  Serial.println(rpmSpeed, 1);
}

void doLedBlink()
{
  static bool led_status = HIGH;

  if (led_status == LOW)
  {
    led_status = HIGH;
  } else
  {
    led_status = LOW;
  }
  digitalWrite(LED_BUILTIN, led_status);
}
