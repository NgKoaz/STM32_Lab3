/*
 * timer.h
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define NO_OF_TIMER 						2
#define TIMER_FOR_READING 					0
#define TIMER_FOR_DISPLAYING_LED			1

#define DURATION_FOR_EACH_READING 					10
#define DURATION_FOR_EACH_DISPLAYING_LED 			10


#define TIMER_CYCLE 10

//Just use the index and duration is defined above.
void SetTimer(const int duration, const short index);
short GetFlagTimer(const short index);
void AllTimerRun(void);

#endif /* INC_TIMER_H_ */
