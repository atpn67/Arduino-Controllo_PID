// Author: G.Topan
// Note:

#include "Encoder.h"
#include "ReadInputs.h"
#include "CShowData2Lcd.h"
#include "AppCommon.h"

// CONSTANTS:

// GLOBAL VARS:
uint32_t tNext_ms = 0;
uint32_t tCurr_ms = 0;

CShowData2Lcd oLcdShow;

void setup()
{
  Serial.begin(115200);

  // init Hw
  Encoder_Init();
  RdInputs_Init(0);
  // read starting setpoint
  RdInputs_Update();
  // init LCD class
  oLcdShow.setup();

  // init onboard LED output
  pinMode(LED_BUILTIN, OUTPUT);
  // init cycle time variables
  tCurr_ms = millis();
  tNext_ms = tCurr_ms + CYCLE_TIME_MS;

  // start PWM output
  analogWrite(PIN_PWM_OUT, RdInputs_SetPoint());
}

void loop()
{
  static uint32_t loop_count = 0;

  tCurr_ms= millis();

  if (tCurr_ms >= tNext_ms)
  {
    // cycle @ CYCLE_TIME_MS
    loop_count++;

    task_100ms();

    if(loop_count % NUM_LOOP_1S == 0)
    {
      // cycle @ 1000 ms
      task_1000ms();
    }

    // do LED blinking
    if(loop_count % NUM_LOOP_LED == 0)
    {
      doLedBlink();
    }
    // set next cycle time
    while ( tCurr_ms >= tNext_ms ) {
      tNext_ms += CYCLE_TIME_MS;
      tCurr_ms = millis();
    }
  }
}

// commento
void task_100ms()
{
  uint32_t rpmVal;

  // command motor speed
  analogWrite(PIN_PWM_OUT, RdInputs_SetPoint());

  Encoder_GetCount();
  rpmVal = Encoder_GetRpm();

  // get new rpm setpoint value
  RdInputs_Update();
}

// commento
void task_1000ms()
{
  uint32_t tmpVal = RdInputs_SetPoint();
  float dutyVal = RdInputs_GetDuty();
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
