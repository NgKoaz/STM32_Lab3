/*
 * timer.c
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */


#include "timer.h"

short counter[NO_OF_TIMER];
short flagTimer[NO_OF_TIMER];

void SetTimer(const int duration, const short index){
	counter[index] = duration / TIMER_CYCLE;
	flagTimer[index] = 0;
}
short GetFlagTimer(const short index){
	return flagTimer[index];
}
void TimerRun(const short index){
	if (counter[index] <= 0) return;
	counter[index]--;
	if (counter[index] <= 0) {
		flagTimer[index] = 1;
	}
}

void AllTimerRun(void){
	TimerRun(TIMER_FOR_READING);
	TimerRun(TIMER_FOR_DISPLAYING_LED);
}
