/*
 * input_reading.h
 *
 *  Created on: Oct 8, 2023
 *      Author: HP
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "global.h"

#define BUTTON_PRESSED GPIO_PIN_RESET
#define BUTTON_RELEASED GPIO_PIN_SET

#define COUNTER_FOR_PRESSING_ONE_SEC 1000 / DURATION_FOR_EACH_READING

#define NO_OF_BUTTON 3
#define SET_BTN 0
#define MOD_BTN 1
#define SEL_BTN 2

void Input_Reading_Init(void);
void ButtonReading(const short index);
uint8_t IsButtonPressed(const short index);
uint8_t IsButtonPressedOneSec(const short index);

#endif /* INC_INPUT_READING_H_ */
