/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Single_LED_Pin GPIO_PIN_5
#define Single_LED_GPIO_Port GPIOA
#define RED1_Pin GPIO_PIN_6
#define RED1_GPIO_Port GPIOA
#define AMBER1_Pin GPIO_PIN_7
#define AMBER1_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_0
#define EN0_GPIO_Port GPIOB
#define EN1_Pin GPIO_PIN_1
#define EN1_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_2
#define EN2_GPIO_Port GPIOB
#define S7_G_Pin GPIO_PIN_10
#define S7_G_GPIO_Port GPIOB
#define SEL_BTN_Pin GPIO_PIN_11
#define SEL_BTN_GPIO_Port GPIOB
#define MOD_BTN_Pin GPIO_PIN_12
#define MOD_BTN_GPIO_Port GPIOB
#define SET_BTN_Pin GPIO_PIN_13
#define SET_BTN_GPIO_Port GPIOB
#define EN4_Pin GPIO_PIN_14
#define EN4_GPIO_Port GPIOB
#define GREEN1_Pin GPIO_PIN_8
#define GREEN1_GPIO_Port GPIOA
#define RED2_Pin GPIO_PIN_9
#define RED2_GPIO_Port GPIOA
#define AMBER2_Pin GPIO_PIN_10
#define AMBER2_GPIO_Port GPIOA
#define GREEN2_Pin GPIO_PIN_11
#define GREEN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_3
#define EN3_GPIO_Port GPIOB
#define S7_A_Pin GPIO_PIN_4
#define S7_A_GPIO_Port GPIOB
#define S7_B_Pin GPIO_PIN_5
#define S7_B_GPIO_Port GPIOB
#define S7_C_Pin GPIO_PIN_6
#define S7_C_GPIO_Port GPIOB
#define S7_D_Pin GPIO_PIN_7
#define S7_D_GPIO_Port GPIOB
#define S7_E_Pin GPIO_PIN_8
#define S7_E_GPIO_Port GPIOB
#define S7_F_Pin GPIO_PIN_9
#define S7_F_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
