/*
 * traffic_light.c
 *
 *  Created on: Oct 12, 2023
 *      Author: HP
 */
#include "traffic_light.h"

GPIO_TypeDef* TrafficLightLED_GPIO = GPIOA;
const short TrafficLightLED_Pin[2 * 3] = {
		RED1_Pin, AMBER1_Pin, GREEN1_Pin,
		RED2_Pin, AMBER2_Pin, GREEN2_Pin
};

//State parameter is the state we will set for 3 LEDs of traffic light.
//RED - AMBER - GREEN <=> A - B - C
//Binary of state: xxxxxABC
void WritePinLED(const short index, uint8_t state){
	HAL_GPIO_WritePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[3 * index + 2], state % 2);
	state /= 2;
	HAL_GPIO_WritePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[3 * index + 1], state % 2);
	state /= 2;
	HAL_GPIO_WritePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[3 * index], state % 2);
}

void TogglePinLED(uint8_t state){
	switch(state){
	case RED:
		HAL_GPIO_TogglePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[0]);
		HAL_GPIO_TogglePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[3 * 1 + 0]);
		break;
	case AMBER:
		HAL_GPIO_TogglePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[1]);
		HAL_GPIO_TogglePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[3 * 1 + 1]);
		break;
	case GREEN:
		HAL_GPIO_TogglePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[2]);
		HAL_GPIO_TogglePin(TrafficLightLED_GPIO, TrafficLightLED_Pin[3 * 1 + 2]);
		break;
	}
}
