/*
 * input_processing.h
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "global.h"

//After we hold modify button more than 1s,
//it will increase after this milisecond.
#define INCREASING_PERIOD 	100

typedef enum{
	RELEASED,
	PRESSED,
	PRESSED_MORE_THAN_ONE_SECOND
} ButtonState;

void Input_Processing_Init(void);

void FSM_ProcessingSetValueButton(void);
void FSM_ProcessingModifyButton(void);
void FSM_ProcessingSelectModeButton(void);

//change display
void FSM_ForStateProcessing(void);


#endif /* INC_INPUT_PROCESSING_H_ */
