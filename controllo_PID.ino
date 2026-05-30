// Author: G.Topan
// Note: 

// CONSTANTS:

// pin list
#define PIN_ENCODER   2
#define PIN_PWM_OUT   9
#define PIN_TRIMMER   0

// timeout and cycle count
#define CYCLE_TIME_MS 100
#define NUM_LOOP_LED  3
#define NUM_LOOP_1S   10

// GLOB VARIABLES:
uint32_t tNext_ms = 0;
uint32_t tCurr_ms = 0;

uint32_t val_trimmer = 0;
uint32_t pwm_setpoint = 0;

volatile uint32_t pulse_count = 0;
uint32_t num_pulse = 0;
float speed_rpm = 0;

void setup() 
{
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  // Pin dell'encoder
  pinMode(PIN_ENCODER, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER), isr_pulse_count, RISING);

  tCurr_ms = millis();
  tNext_ms = tCurr_ms + CYCLE_TIME_MS;

  // read starting setpoint
  val_trimmer = analogRead(PIN_TRIMMER);
  pwm_setpoint = val_trimmer/4;
  //analogWrite(PIN_PWM_OUT, pwm_setpoint);
}

void loop() 
{
  static uint32_t loop_count = 0;

  tCurr_ms= millis();

  //analogWrite(PIN_PWM_OUT, pwm_setpoint);
  analogWrite(PIN_PWM_OUT, 200);

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
      doLedlink();
    }
  }
}

// commento
void task_100ms()
{
  // command motor speed
  //analogWrite(PIN_PWM_OUT, pwm_setpoint);

  // get actual motor speed
  num_pulse = pulse_count;
  pulse_count = 0;
  // speed_rpm = ((num_pulse * 60 * 1000)/(1000*12));
  //speed_rpm = ((num_pulse * 60000)/12000);
  speed_rpm = ((num_pulse * 60000)/1200);

  // get new rpm setpoint value
  val_trimmer = analogRead(PIN_TRIMMER);
  pwm_setpoint = val_trimmer/4;
}

// commento
void task_1000ms()
{
  //Serial.print("conteggio: ");
  //Serial.println(num_pulse, DEC);

  Serial.print("setpoint: ");
  Serial.println(pwm_setpoint, DEC);
  Serial.print("velocità: ");
  Serial.println(speed_rpm, 1);
}

void doLedlink()
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

void isr_pulse_count ()
{
  pulse_count++;
}
