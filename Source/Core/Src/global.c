/*
 * global.c
 *
 *  Created on: Oct 15, 2023
 *      Author: HP
 */
#include "global.h"

RunState runState;
//We control two line vertical and horizontal
//so we need 2
LEDState ledState[2];

//Notice: these counter that have cycle is 10ms.
// (We just make sure after 10ms it will minus 1)
//So i will use COUNTER_CYCLE divide it before set value.
int light_counter[2];


uint8_t durationRed;
uint8_t durationAmber;
uint8_t durationGreen;

//These variable for adjusting duration.
uint8_t adjust_duRed;
uint8_t adjust_duAmber;
uint8_t adjust_duGreen;

void Traffic_Light_Reset(void){
	runState = NORMAL_MODE;

	ledState[0] = RED;
	light_counter[0] = durationRed * ONE_SECOND / COUNTER_CYCLE;

	ledState[1] = GREEN;
	light_counter[1] = durationGreen * ONE_SECOND / COUNTER_CYCLE;
}

void Global_Init(void){
	durationRed   = DURATION_RED_DEFAULT;
	durationAmber = DURATION_AMBER_DEFAULT;
	durationGreen = DURATION_GREEN_DEFAULT;

	Traffic_Light_Reset();
}
