/*
 * led_display.h
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "global.h"

#define DataBus7SEG_GPIO 	GPIOB
#define EN_GPIO	 		 	GPIOB
#define TOTAL_LED			5
#define TURN_ON_LED			RESET
#define TURN_OFF_LED 		SET

extern uint8_t buffer7SEG[TOTAL_LED];

void LED7SEG_Init(void);

//Update databus to display the number at `index` in buffer.
void Scanning7SEG(void);

#endif /* INC_LED_DISPLAY_H_ */
