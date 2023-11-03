/*
 * led7seg.h
 *
 *  Created on: Nov 2, 2023
 *      Author: HP
 */

#ifndef INC_LED7SEG_H_
#define INC_LED7SEG_H_

#include "global.h"

#define TOTAL_LED			5
#define TURN_ON				RESET
#define TURN_OFF 			SET

void LED7SEG_Init(void);

//Update databus to display the number at `index` in buffer.
void Scanning7SEG(void);

#endif /* INC_LED7SEG_H_ */
