// Author: G.Topan
// Note: 

#include  "stdint.h"

/* initilize encoder speed read
 * return: none
*/
void Encoder_Init ( void );

/* get actual encoder counter
 * return: actual encoder counter and clear it
*/
uint32_t Encoder_GetCount ( void );

/* get actual rpm speed
 * return: actual speed in rpm
*/
uint32_t Encoder_GetRpm ( void );
