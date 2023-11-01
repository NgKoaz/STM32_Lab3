/*
 * global.c
 *
 *  Created on: Oct 15, 2023
 *      Author: HP
 */
#include "global.h"

RunState runState;
LEDState ledState[2];
int light_counter[2];


uint8_t durationRed;
uint8_t durationAmber;
uint8_t durationGreen;

uint8_t temp_duRed;
uint8_t temp_duAmber;
uint8_t temp_duGreen;

void Traffic_Light_Reset(void){
	runState = NORMAL_MODE;

	ledState[0] = RED;
	light_counter[0] = durationRed * SECOND / CYCLE;

	ledState[1] = GREEN;
	light_counter[1] = durationGreen * SECOND / CYCLE;
}

void Global_Init(void){
	durationRed = DURATION_RED_DEFAULT;
	durationAmber = DURATION_AMBER_DEFAULT;
	durationGreen = DURATION_GREEN_DEFAULT;

	Traffic_Light_Reset();
}
