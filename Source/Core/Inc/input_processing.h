/*
 * input_processing.h
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "global.h"

#define SECOND 					1000
#define HALF_SECOND 			500
#define DURATION_FOR_INCREASE 	200
#define CYCLE DURATION_FOR_EACH_READING

extern int general_counter;

void Input_Processing_Init(void);

void FSM_ProcessingSetValueButton(void);
void FSM_ProcessingModifyButton(void);
void FSM_ProcessingSelectModeButton(void);

//change display
void FSM_ForProcessingState(void);


#endif /* INC_INPUT_PROCESSING_H_ */
