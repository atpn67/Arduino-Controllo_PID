// Author: G.Topan
// Note:

#include <PID_v1_bc.h>
#include "Encoder.h"
#include "ReadInputs.h"
#include "CShowData2Lcd.h"
#include "AppCommon.h"

// CONDITIONAL COMPILING:
#define EN_PIDCTRL 1

// CONSTANTS:
#define FSM_MAX_STEPS   4
#define PID_MAX_PWMVAL  255
#define PID_MIN_PWMVAL  -50

// GLOBAL VARS:
uint32_t tNext_ms = 0;
uint32_t tCurr_ms = 0;

// PID parameters
double Kp = 0.10f;      // 0.25
double Ki = 0.15f;      // 0.2f
double Kd = 0.0f;
#if EN_PIDCTRL
double FF = 0.08f;      // 0.08f
#else
double FF = 0.18f;      // OK WHEN pid is disabled
#endif

// PID variables
double Setpoint;
double Input;
double Output;
int OutputFF;

CShowData2Lcd oLcdShow;
PID oPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

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

  //set PID controller
  oPID.SetOutputLimits(PID_MIN_PWMVAL, PID_MAX_PWMVAL);
  oPID.SetSampleTime(CYCLE_TIME_MS);
  //oPID.SetTunings(Kp, Ki, Kd);
  oPID.SetMode(AUTOMATIC);

  // init cycle time variables
  tCurr_ms = millis();
  tNext_ms = tCurr_ms + CYCLE_TIME_MS;

  // start PWM output off
  analogWrite(PIN_PWM_OUT, 0);
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
      float pwmDuty = (float)(OutputFF * 100.0 / 255);

      oLcdShow.setRpmSetpoint( RdInputs_SpeedSetPoint() );
      oLcdShow.setCurrPwmDuty( pwmDuty );
      oLcdShow.setCurrSpeedFast( Encoder_GetRpmFilt() );
      oLcdShow.setCurrSpeedSlow( Encoder_GetRpmSlow() );

      //oLcdShow.refresh(true);
      oLcdShow.refresh();
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
  int pwmOut;

  // update encoder counter
  Encoder_GetCount();
  rpmVal = Encoder_GetRpm();

  // PID control
  Setpoint = RdInputs_SpeedSetPoint();
  Input = Encoder_GetRpmFilt();
  oPID.Compute();

#if EN_PIDCTRL
  // output PID with feed-forward
  OutputFF = (int)(Output + (FF * Setpoint));
  if ( OutputFF > 255 ) {
    OutputFF = 255;
  }
  if ( OutputFF < 0 ) {
    OutputFF = 0;
  }
  pwmOut = OutputFF;
#else
  OutputFF = (int)(FF * RdInputs_SpeedSetPoint());
#endif
  pwmOut = OutputFF;

  // command motor speed
  analogWrite(PIN_PWM_OUT, pwmOut);

  // get new setpoint value and push button status
  RdInputs_Update();
}

// task @ 1000 ms
void task_1000ms()
{
  int stepNum;
  stepNum = LCDUpdateSelData();

// debug messages
#if 0
  stepNum++;
  Serial.print("FSM step ");
  Serial.print(RdInputs_GetBtnStatus(), DEC);
  Serial.print("  ");
  Serial.println(stepNum, DEC);
#endif

// debug messages
#if 0
  Serial.print("PID param ");
  Serial.print(Setpoint, 2);
  Serial.print("  ");
  Serial.print(Input, 2);
  Serial.print("  ");
  Serial.println((int)Output, DEC);
#endif
}

/**
 * update LCD selected data
 * @return: current step 0 .. 4
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
