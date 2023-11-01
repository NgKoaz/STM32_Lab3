/*
 * input_processing.c
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#include "input_processing.h"

ButtonState buttonState[NO_OF_BUTTON];

int general_counter;
int modbtn_counter;

void Input_Processing_Init(void)
{
	buttonState[SET_BTN] = RELEASED;
	buttonState[MOD_BTN] = RELEASED;
	buttonState[SEL_BTN] = RELEASED;

	general_counter = 1;
	modbtn_counter = DURATION_FOR_INCREASE / CYCLE;
}

void IncreaseOne(uint8_t* duration){
	(*duration) = (*duration) + 1 > 99 ? 0 : (*duration) + 1;
}
void FSM_IncreasingValue(void){
	switch(runState){
	case NORMAL_MODE:
		break;
	case MODIFY_DURATION_RED_MODE:
		IncreaseOne(&temp_duRed);
		break;
	case MODIFY_DURATION_AMBER_MODE:
		IncreaseOne(&temp_duAmber);
		break;
	case MODIFY_DURATION_GREEN_MODE:
		IncreaseOne(&temp_duGreen);
		break;
	}
}
void FSM_ChangingMode(void){
	//Turn off all LEDs.
	WritePinLED(0, ~RED | ~AMBER | ~GREEN);
	WritePinLED(1, ~RED | ~AMBER | ~GREEN);
	switch(runState){
	case NORMAL_MODE:
		runState = MODIFY_DURATION_RED_MODE;
		general_counter = HALF_SECOND / CYCLE;;
		temp_duRed = durationRed;
		break;
	case MODIFY_DURATION_RED_MODE:
		runState = MODIFY_DURATION_AMBER_MODE;
		general_counter = HALF_SECOND / CYCLE;;
		temp_duAmber = durationAmber;
		break;
	case MODIFY_DURATION_AMBER_MODE:
		runState = MODIFY_DURATION_GREEN_MODE;
		general_counter = HALF_SECOND / CYCLE;;
		temp_duGreen = durationGreen;
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
		durationRed = temp_duRed;
		break;
	case MODIFY_DURATION_AMBER_MODE:
		durationAmber = temp_duAmber;
		break;
	case MODIFY_DURATION_GREEN_MODE:
		durationGreen = temp_duGreen;
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
	if (buttonState[MOD_BTN] == PRESSED_MORE_THAN_ONE_SECOND) {
		modbtn_counter--;
		if (modbtn_counter <= 0) {
			modbtn_counter = DURATION_FOR_INCREASE / CYCLE;
			FSM_IncreasingValue();
		}
	} else {
		modbtn_counter = DURATION_FOR_INCREASE / CYCLE;
	}
}
void FSM_ProcessingSelectModeButton(void){
	FSM_ForInputProcessing(FSM_ChangingMode, SEL_BTN);
}


void FSM_TrafficLight(const short index){
	light_counter[index]--;
	switch (ledState[index]){
	case RED:
		//Display Red LED.
		WritePinLED(index, RED);
		//After amount of time, it will switch to Green.
		if (light_counter[index] <= 0) {
			light_counter[index] = durationGreen * SECOND / CYCLE;
			ledState[index] = GREEN;
		}
		break;

	case AMBER:
		//Display Amber LED.
		WritePinLED(index, AMBER);
		//After amount of time, it will switch to Red.
		if (light_counter[index] <= 0) {
			light_counter[index] = durationRed * SECOND / CYCLE;
			ledState[index] = RED;
		}
		break;

	case GREEN:
		//Display Green LED.
		WritePinLED(index, GREEN);
		//After amount of time, it will switch to Amber.
		if (light_counter[index] <= 0) {
			light_counter[index] = durationAmber * SECOND / CYCLE;
			ledState[index] = AMBER;
		}
		break;
	}
}

void FSM_ForProcessingState(void){
	switch (runState){
	case NORMAL_MODE:
		FSM_TrafficLight(0);
		FSM_TrafficLight(1);
		break;
	case MODIFY_DURATION_RED_MODE:
		//Blinking Red LED in 0.5s
		general_counter--;
		if (general_counter <= 0) {
			general_counter = HALF_SECOND / CYCLE;
			TogglePinLED(RED);
		}
		break;
	case MODIFY_DURATION_AMBER_MODE:
		//Blinking Amber LED in 0.5s
		general_counter--;
		if (general_counter <= 0) {
			general_counter = HALF_SECOND / CYCLE;
			TogglePinLED(AMBER);
		}
		break;
	case MODIFY_DURATION_GREEN_MODE:
		//Blinking Green LED in 0.5s
		general_counter--;
		if (general_counter <= 0) {
			general_counter = HALF_SECOND / CYCLE;
			TogglePinLED(GREEN);
		}
		break;
	}
}
