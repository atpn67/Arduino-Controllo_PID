// Author: G.Topan
// Note:

// CONSTANTS:

// pin list
#define PIN_ENCODER   2

#define PIN_BUTTON01  3 

#define PIN_PWM_OUT   9
#define PIN_TRIMMER   0
#define PIN_LCD_RS    4
#define PIN_LCD_ENAB  6
#define PIN_LCD_D4    10
#define PIN_LCD_D5    11
#define PIN_LCD_D6    12
#define PIN_LCD_D7    13

// timeout and cycle count
#define TIME_SECOND_MS  1000  // milliseconds in a second
#define CYCLE_TIME_MS   100   // main control loop time
#define NUM_LOOP_1S     (TIME_SECOND_MS/CYCLE_TIME_MS)
#define LED_BLINK_MS    300   // onboard LED Blinking time (semiperiod)
#define NUM_LOOP_LED    (LED_BLINK_MS/CYCLE_TIME_MS)
#define LCD_REFRESH_MS  300   // LCD update time
#define NUM_LOOP_LCD    (LCD_REFRESH_MS/CYCLE_TIME_MS)
