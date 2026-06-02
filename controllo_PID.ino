// Author: G.Topan
// Note:

#include "Encoder.h"
#include "ReadInputs.h"
#include "CShowData2Lcd.h"
#include "AppCommon.h"

// CONSTANTS:
#define FSM_MAX_STEPS   4

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
  // read inputs value
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
  Serial.println("PWM Motor control started.");
}

void loop()
{
  static uint32_t loopCount = 0;

  tCurr_ms= millis();

  if (tCurr_ms >= tNext_ms)
  {
    // cycle @ CYCLE_TIME_MS
    loopCount++;

    task_100ms();

    // refresh LCD content
    if (loopCount % NUM_LOOP_LCD == 0)
    {
      oLcdShow.setRpmSetpoint( RdInputs_SpeedSetPoint() );
      oLcdShow.setCurrSpeedFast( Encoder_GetRpm() );
      oLcdShow.setCurrSpeedSlow( Encoder_GetRpmSlow() );
      oLcdShow.setCurrPwmDuty( RdInputs_GetDuty() );

      oLcdShow.refresh(true);
    }

    if (loopCount % NUM_LOOP_1S == 0)
    {
      task_1000ms();
    }

    // do LED blinking
    if (loopCount % NUM_LOOP_LED == 0)
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

// task @ 100 ms
void task_100ms()
{
  uint32_t rpmVal;

  // command motor speed
  analogWrite(PIN_PWM_OUT, RdInputs_SetPoint());

  // update encoder counter
  Encoder_GetCount();
  rpmVal = Encoder_GetRpm();

  // get new setpoint value and push button status
  RdInputs_Update();
}

// task @ 1000 ms
void task_1000ms()
{
  int stepNum;
  stepNum = LCDUpdateSelData();

  // TODO: completare
#if 0
  uint32_t tmpVal = RdInputs_SetPoint();
  float dutyVal = RdInputs_GetDuty();
  float rpmSpeed = Encoder_GetRpm();

  Serial.print("setpoint: ");
  Serial.print(tmpVal, DEC);
  Serial.print("  Set Duty: ");
  Serial.print(dutyVal, 1);
  Serial.print("  velocità: ");
  Serial.println(rpmSpeed, 1);
#endif

  stepNum++;
  Serial.print("FSM step ");
  Serial.print(RdInputs_GetBtnStatus(), DEC);
  Serial.print("  ");
  Serial.println(stepNum, DEC);
}

/* update LCD selected data
 * return: current step 0 .. 4
*/ 
int LCDUpdateSelData()
{
  int fsmStep = (RdInputs_GetBtnPushCount() % FSM_MAX_STEPS);

  switch ( fsmStep ) {
    default:
    case 0:
      oLcdShow.selectData(SELDATA_SETP_RPMFCURR);
      break;

    case 1:
      oLcdShow.selectData(SELDATA_SETP_RPMSCURR);
      break;

    case 2:
      oLcdShow.selectData(SELDATA_SETP_PWMDUTY);
      break;

    case 3:
      oLcdShow.selectData(SELDATA_RPMF_PWMDUTY);
      break;
  }

  return fsmStep;
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
