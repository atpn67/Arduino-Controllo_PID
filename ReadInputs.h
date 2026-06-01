// Author: G.Topan
// Note:

#include  "stdint.h"

/* initilize the setpoint read using an analog trimmer
 * initVal [in] pwm setpoint init value range 0..255
 * return: none
*/
bool RdInputs_Init ( uint32_t initVal );

/* read analog data and converts it to a pwm value
 * to be called periodically at cycle time
 * return: none
*/
bool RdInputs_Update ();

/* get actual requested setpoint
 * return: actual setpoint in range 0..255
*/
uint32_t RdInputs_SetPoint ();

/* get actual requested setpoint
 * return: actual rpm setpoint in range 0..1200
*/
uint32_t RdInputs_SpeedSetPoint ();

/* get actual requested duty cycle
 * return: actual setpoint duty cycle
*/
float RdInputs_GetDuty ();

/* get push Button status
 * to be called periodically as fast as possible
 * return: push button status
*/
int RdInputs_GetBtnStatus ();

/* returns a counter of the number of time the push Button 
 * has been pressed and released
 * return: push button press counter
*/
int RdInputs_GetBtnPushCount ();

/* clear the counter of the number of time the push Button 
 * has been pressed and released
 * return: none
*/
void RdInputs_CltBtnPushCount ();

