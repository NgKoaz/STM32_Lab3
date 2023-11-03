/*
 * timer.h
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

//Number of timer
#define NO_TIMER 							3

//Index of each timer
#define READING_TIMER 						0
#define SCANNING_TIMER						1
#define BLINKING_TIMER						2

#define READING_PERIOD 						10
#define SCANNING_PERIOD 					10
#define BLINKING_PERIOD						500

#define ONE_SECOND 							1000
#define HALF_SECOND 						500

#define TIMER_CYCLE 10


//Just use the index and duration is defined above.
void SetTimer(const int duration, const short index);
short GetFlagTimer(const short index);
void AllTimerRun(void);

#endif /* INC_TIMER_H_ */
