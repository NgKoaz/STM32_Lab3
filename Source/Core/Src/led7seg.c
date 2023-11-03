/*
 * led7seg.c
 *
 *  Created on: Nov 2, 2023
 *      Author: HP
 */

#include "led7seg.h"

//Set Port and Pin for databus 7seg and enable 7seg.
#define DataBus7SEG_GPIO 	GPIOB
#define EN_GPIO	 		 	GPIOB
const short DataBus7SEG_Pin[7] = {
		S7_A_Pin, S7_B_Pin, S7_C_Pin, S7_D_Pin,
		S7_E_Pin, S7_F_Pin, S7_G_Pin
};
const short EN_PIN[TOTAL_LED] = {
		EN0_Pin, EN1_Pin , EN2_Pin, EN3_Pin, EN4_Pin
};

const uint8_t b[10] = {
		1, 79, 18, 6, 76,
		36, 32, 15, 0, 4
};

//Each index of buffer corresponding to index_led.
uint8_t buffer7SEG[TOTAL_LED];

//this var is to control which led will display.
uint8_t led_index;

void LED7SEG_Init(void){
	for (short i = 0; i < TOTAL_LED; i++){
		buffer7SEG[i] = 0;
		HAL_GPIO_WritePin(EN_GPIO, EN_PIN[i], TURN_OFF);
	}
	led_index = TOTAL_LED - 1;
}


void UpdateBuffer7SEG(void){
	int first;		//This variable used for displaying two first 7SEG LEDs.
	int second;		//This variable used for displaying two second 7SEG LEDs.
	switch(runState){
	case NORMAL_MODE:
		//Take two counter of traffic light
		//After that, we will exchange time unit to second.
		//Remember, `duration * ONE_SECOND / COUNTER_CYCLE
		first = light_counter[0] / (ONE_SECOND / COUNTER_CYCLE);
		second = light_counter[1] / (ONE_SECOND / COUNTER_CYCLE);
		break;
	case MODIFY_DURATION_RED_MODE:
		first = second = adjust_duRed;
		break;
	case MODIFY_DURATION_AMBER_MODE:
		first = second = adjust_duAmber;
		break;
	case MODIFY_DURATION_GREEN_MODE:
		first = second = adjust_duGreen;
		break;
	}
	buffer7SEG[0] = first / 10;
    buffer7SEG[1] = first % 10;
    buffer7SEG[2] = second / 10;
    buffer7SEG[3] = second % 10;
    //the last index of this buffer will be assigned by runState to display mode.
	//Read enum runState in global.h
    buffer7SEG[4] = runState;
}

void UpdateDatabus7SEG(const short index){
	uint8_t num = buffer7SEG[index];
	if (num > 9 || num < 0) return;
	uint8_t temp = b[num];
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_G_Pin, temp & 0x01);
	temp >>= 1;
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_F_Pin, temp & 0x01);
	temp >>= 1;
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_E_Pin, temp & 0x01);
	temp >>= 1;
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_D_Pin, temp & 0x01);
	temp >>= 1;
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_C_Pin, temp & 0x01);
	temp >>= 1;
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_B_Pin, temp & 0x01);
	temp >>= 1;
	HAL_GPIO_WritePin(DataBus7SEG_GPIO, S7_A_Pin, temp & 0x01);
}

void Scanning7SEG(void){
	//Turn off previous LED.
	HAL_GPIO_WritePin(EN_GPIO, EN_PIN[led_index], TURN_OFF);

	//Move another LED
	led_index++;
	if (led_index >= TOTAL_LED) {
		led_index = 0;
	}

	//Update Buffer 7Seg.
	UpdateBuffer7SEG();

	//Update Databus
	UpdateDatabus7SEG(led_index);

	//Turn on current LED
	HAL_GPIO_WritePin(EN_GPIO, EN_PIN[led_index], TURN_ON);
}
