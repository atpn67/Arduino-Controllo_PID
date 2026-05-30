// Author: G.Topan
// Note: 

// CONSTANTS:

// pin list
#define PIN_ENCODER   2
#define PIN_PWM       9

// timeout and cycle count
#define CYCLE_TIME_MS 100
#define NUM_LOOP_LED  3
#define NUM_LOOP_1S   10

// GLOB VARIABLES:
uint32_t tNext_ms = 0;
uint32_t tCurr_ms = 0;

volatile long pulse_count = 0;


/***


void setup() {
  pinMode(2, INPUT_PULLUP);  // Pin dell'encoder
  attachInterrupt(digitalPinToInterrupt(2), contaImpulso, RISING);
  Serial.begin(9600);
}

void loop() {
  Serial.println(impulsi);
  delay(100);
}

void contaImpulso() {
  impulsi++;
}
****/


void setup() 
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  // Pin dell'encoder
  pinMode(PIN_ENCODER, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER), isr_pulse_count, FALLING);

  tCurr_ms = millis();
  tNext_ms = tCurr_ms + CYCLE_TIME_MS;

}

void loop() 
{
  analogWrite(PIN_PWM, 127);

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
      doLedlink();
    }
  }
}

// commento
void task_100ms()
{

}

// commento
void task_1000ms()
{
  long num_pulse = pulse_count;
  pulse_count = 0;
  Serial.print("conteggio: ");
  Serial.println(num_pulse, DEC);
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
