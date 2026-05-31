// Author: G.Topan
// Note:

#include  "stdint.h"

// CONSTANTS

// PWM motor limits
#define MOTOR_RPM_FAST_MAX  1200
#define MOTOR_RPM_FAST_MIN  200

/* initilize encoder speed read
 * return: none
*/
void Encoder_Init ( void );

/* get actual encoder counter
 * return: actual encoder counter and clear it
*/
uint32_t Encoder_GetCount ( void );

/* get actual rpm speed on fast shaft
 * return: actual fast shaft speed in rpm
*/
float Encoder_GetRpm ( void );

/* get actual rpm speed on slow shaft
 * return: actual slow shaft speed in rpm
*/
float Encoder_GetRpmSlow ( void );
