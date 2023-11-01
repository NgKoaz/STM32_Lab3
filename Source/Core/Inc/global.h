/*
 * global.h
 *
 *  Created on: Oct 15, 2023
 *      Author: HP
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

//INCLUDE HERE
#include "main.h"
#include "input_reading.h"
#include "input_processing.h"
#include "timer.h"
#include "traffic_light.h"


//DEFINE HERE
#define DURATION_RED_DEFAULT 		3
#define DURATION_AMBER_DEFAULT 		1
#define DURATION_GREEN_DEFAULT 		2


//TYPEDEF HERE
typedef enum{
	RELEASED,
	PRESSED,
	PRESSED_MORE_THAN_ONE_SECOND
} ButtonState;

typedef enum {
	NORMAL_MODE = 1,
	MODIFY_DURATION_RED_MODE = 2,
	MODIFY_DURATION_AMBER_MODE = 3,
	MODIFY_DURATION_GREEN_MODE = 4
} RunState;

typedef enum {
	RED = 3,
	AMBER = 5,
	GREEN = 6
} LEDState;

//VARIABLE HERE
extern RunState runState;

extern LEDState ledState[2];
extern int light_counter[2];

extern uint8_t durationRed;
extern uint8_t durationAmber;
extern uint8_t durationGreen;

extern uint8_t temp_duRed;
extern uint8_t temp_duAmber;
extern uint8_t temp_duGreen;


//FUNCTION HERE
void Global_Init(void);
void Traffic_Light_Reset(void);

#endif /* INC_GLOBAL_H_ */
