// Author: G.Topan
// Note: 

#include  "stdint.h"

/* initilize the setpoint read using an analog trimmer
 * initVal [in] pwm setpoint init value range 0..255
 * return: none
*/
void RdSetpoint_Init ( uint32_t initVal );

/* read analog data and converts it to a pwm value
 * to be called periodically at cycle time 
 * return: none
*/
void RdSetpoint_Update ( void );

/* get actual requested setpoint
 * return: actual setpoint in range 0..255
*/
uint32_t RdSetpoint_Get ( void );

/* get actual requested duty cycle
 * return: actual setpoint duty cycle
*/
float RdSetpoint_GetDuty ( void );
