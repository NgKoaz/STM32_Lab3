/*
 * input_reading.c
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#include "input_reading.h"

GPIO_TypeDef* GPIO_Port[NO_OF_BUTTON] = {
		SET_BTN_GPIO_Port,
		MOD_BTN_GPIO_Port,
		SEL_BTN_GPIO_Port
};
const short GPIO_Pin[NO_OF_BUTTON] = {
		SET_BTN_Pin,
		MOD_BTN_Pin,
		SEL_BTN_Pin
};

static GPIO_PinState filteredBuffer[NO_OF_BUTTON];
static GPIO_PinState debounceBuffer0[NO_OF_BUTTON];
static GPIO_PinState debounceBuffer1[NO_OF_BUTTON];
//static GPIO_PinState debounceBuffer2[NO_OF_BUTTON];

static uint8_t flagPressedOneSec[NO_OF_BUTTON];
static short counterPressedOneSec[NO_OF_BUTTON];

void Input_Reading_Init(void){
	for(short i = 0; i < NO_OF_BUTTON; i++){
		filteredBuffer[i] = debounceBuffer0[i] = debounceBuffer1[i] = BUTTON_RELEASED;
		flagPressedOneSec[i] = 0;
		counterPressedOneSec[i] = COUNTER_FOR_PRESSING_ONE_SEC;
	}
}

uint8_t IsIndexValid(const short index){
	return (index >= 0 && index < NO_OF_BUTTON);
}

uint8_t IsButtonPressed(const short index){
	if (!IsIndexValid(index)) return -1;
	return (filteredBuffer[index] == BUTTON_PRESSED);
}
uint8_t IsButtonPressedOneSec(const short index){
	if (!IsIndexValid(index)) return -1;
	return flagPressedOneSec[index];
}

//Just save 2 latest states instead of 3. It can make HandleIT function more lighter.
void ButtonReading(const short index){
	if (!IsIndexValid(index)) return;
	//Save 2 latest states
	//debounceBuffer2[index] = debounceBuffer1[index];
	debounceBuffer1[index] = debounceBuffer0[index];
	debounceBuffer0[index] = HAL_GPIO_ReadPin(GPIO_Port[index], GPIO_Pin[index]);

	//If all saved states equal -> filtered
	if(//debounceBuffer2[index] == debounceBuffer1[index] &&
		debounceBuffer1[index] == debounceBuffer0[index]){
		filteredBuffer[index] = debounceBuffer0[index];
		if (filteredBuffer[index] == BUTTON_PRESSED){
			counterPressedOneSec[index]--;
			if (counterPressedOneSec[index] <= 0){
				flagPressedOneSec[index] = 1;
			}
		} else {
			counterPressedOneSec[index] = COUNTER_FOR_PRESSING_ONE_SEC;
			flagPressedOneSec[index] = 0;
		}
	}
}





