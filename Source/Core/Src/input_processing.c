/*
 * input_processing.c
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#include "input_processing.h"

ButtonState buttonState[NO_BUTTON];

//For blinking led when we switch in modify mode.
int blinking_counter;
//This counter for modify button after amount of time it increase `adjusting variable`.
int increasing_counter;

void Input_Processing_Init(void)
{
	buttonState[SET_BTN] = RELEASED;
	buttonState[MOD_BTN] = RELEASED;
	buttonState[SEL_BTN] = RELEASED;

	blinking_counter = 1;
	increasing_counter = INCREASING_PERIOD / COUNTER_CYCLE;
}

void IncreaseOne(uint8_t* duration){
	(*duration) = (*duration) + 1 > 99 ? 0 : (*duration) + 1;
}
void FSM_IncreasingValue(void){
	switch(runState){
	case NORMAL_MODE:
		break;
	case MODIFY_DURATION_RED_MODE:
		IncreaseOne(&adjust_duRed);
		break;
	case MODIFY_DURATION_AMBER_MODE:
		IncreaseOne(&adjust_duAmber);
		break;
	case MODIFY_DURATION_GREEN_MODE:
		IncreaseOne(&adjust_duGreen);
		break;
	}
}
void FSM_ChangingMode(void){
	//Turn off all LEDs.
	WritePinLED(0, ~RED | ~AMBER | ~GREEN);
	WritePinLED(1, ~RED | ~AMBER | ~GREEN);

	//Changing state and initial new value for new mode.
	switch(runState){
	case NORMAL_MODE:
		runState = MODIFY_DURATION_RED_MODE;
		blinking_counter = HALF_SECOND / COUNTER_CYCLE;
		adjust_duRed = durationRed;
		break;
	case MODIFY_DURATION_RED_MODE:
		runState = MODIFY_DURATION_AMBER_MODE;
		blinking_counter = HALF_SECOND / COUNTER_CYCLE;
		adjust_duAmber = durationAmber;
		break;
	case MODIFY_DURATION_AMBER_MODE:
		runState = MODIFY_DURATION_GREEN_MODE;
		blinking_counter = HALF_SECOND / COUNTER_CYCLE;
		adjust_duGreen = durationGreen;
		break;
	case MODIFY_DURATION_GREEN_MODE:
		runState = NORMAL_MODE;
		Traffic_Light_Reset();
		break;
	}
}
void FSM_SettingValue(void){
	switch(runState){
	case NORMAL_MODE:
		break;
	case MODIFY_DURATION_RED_MODE:
		durationRed = adjust_duRed;
		break;
	case MODIFY_DURATION_AMBER_MODE:
		durationAmber = adjust_duAmber;
		break;
	case MODIFY_DURATION_GREEN_MODE:
		durationGreen = adjust_duGreen;
		break;
	}
}

//This is abstract function. Use for those function below.
void FSM_ForInputProcessing(void (*processing) (void), const short index){
	switch(buttonState[index]){
	case RELEASED:
		if (IsButtonPressed(index)){
			buttonState[index] = PRESSED;
			(*processing)();
		}
		break;
	case PRESSED:
		if (!IsButtonPressed(index)){
			buttonState[index] = RELEASED;
		} else if (IsButtonPressedOneSec(index)){
			buttonState[index] = PRESSED_MORE_THAN_ONE_SECOND;
		}
		break;
	case PRESSED_MORE_THAN_ONE_SECOND:
		if (!IsButtonPressedOneSec(index)){
			buttonState[index] = RELEASED;
		}
		break;
	}
}
void FSM_ProcessingSetValueButton(void){
	FSM_ForInputProcessing(FSM_SettingValue, SET_BTN);
}
void FSM_ProcessingModifyButton(void){
	FSM_ForInputProcessing(FSM_IncreasingValue, MOD_BTN);
	//Handle when button hold more than one second
	//increase `adjusting value` after INCREASING_PERIOD ms
	if (buttonState[MOD_BTN] == PRESSED_MORE_THAN_ONE_SECOND) {
		increasing_counter--;
		if (increasing_counter <= 0) {
			increasing_counter = INCREASING_PERIOD / COUNTER_CYCLE;
			FSM_IncreasingValue();
		}
	} else {
		increasing_counter = INCREASING_PERIOD / COUNTER_CYCLE;
	}
}
void FSM_ProcessingSelectModeButton(void){
	FSM_ForInputProcessing(FSM_ChangingMode, SEL_BTN);
}


void FSM_TrafficLight(const short index){
	light_counter[index]--;
	switch (ledState[index]){
	case RED:
		//Display only Red LED.
		WritePinLED(index, RED);
		//After amount of time, it will switch to Green.
		if (light_counter[index] <= 0) {
			light_counter[index] = durationGreen * ONE_SECOND / COUNTER_CYCLE;
			ledState[index] = GREEN;
		}
		break;

	case AMBER:
		//Display only Amber LED.
		WritePinLED(index, AMBER);
		//After amount of time, it will switch to Red.
		if (light_counter[index] <= 0) {
			light_counter[index] = durationRed * ONE_SECOND / COUNTER_CYCLE;
			ledState[index] = RED;
		}
		break;

	case GREEN:
		//Display only Green LED.
		WritePinLED(index, GREEN);
		//After amount of time, it will switch to Amber.
		if (light_counter[index] <= 0) {
			light_counter[index] = durationAmber * ONE_SECOND / COUNTER_CYCLE;
			ledState[index] = AMBER;
		}
		break;
	}
}

void FSM_ForStateProcessing(void){
	switch (runState){
	case NORMAL_MODE:
		//Run 2 traffic light FSMs.
		FSM_TrafficLight(0);
		FSM_TrafficLight(1);
		break;
	case MODIFY_DURATION_RED_MODE:
		//Blinking Red LED in 0.5s
		blinking_counter--;
		if (blinking_counter <= 0) {
			blinking_counter = HALF_SECOND / COUNTER_CYCLE;
			TogglePinLED(RED);
		}
		break;
	case MODIFY_DURATION_AMBER_MODE:
		//Blinking Amber LED in 0.5s
		blinking_counter--;
		if (blinking_counter <= 0) {
			blinking_counter = HALF_SECOND / COUNTER_CYCLE;
			TogglePinLED(AMBER);
		}
		break;
	case MODIFY_DURATION_GREEN_MODE:
		//Blinking Green LED in 0.5s
		blinking_counter--;
		if (blinking_counter <= 0) {
			blinking_counter = HALF_SECOND / COUNTER_CYCLE;
			TogglePinLED(GREEN);
		}
		break;
	}
}
