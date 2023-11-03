/*
 * timer.c
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */


#include "timer.h"

uint32_t counter[NO_TIMER];
uint8_t flag[NO_TIMER];

void SetTimer(const int duration, const short index){
	counter[index] = duration / TIMER_CYCLE;
	flag[index] = 0;
}
short GetFlagTimer(const short index){
	return flag[index];
}
void timerRun(const short index){
	if (counter[index] <= 0) return;
	counter[index]--;
	if (counter[index] <= 0) {
		flag[index] = 1;
	}
}

void AllTimerRun(void){
	timerRun(READING_TIMER);
	timerRun(SCANNING_TIMER);
	timerRun(BLINKING_TIMER);
}
