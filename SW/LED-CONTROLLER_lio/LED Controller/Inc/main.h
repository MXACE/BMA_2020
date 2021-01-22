/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define JOGPAD_MID_Pin GPIO_PIN_2
#define JOGPAD_MID_GPIO_Port GPIOE
#define JOGPAD_BOTTOM_Pin GPIO_PIN_3
#define JOGPAD_BOTTOM_GPIO_Port GPIOE
#define JOGPAD_RIGHT_Pin GPIO_PIN_4
#define JOGPAD_RIGHT_GPIO_Port GPIOE
#define JOGPAD_LEFT_Pin GPIO_PIN_5
#define JOGPAD_LEFT_GPIO_Port GPIOE
#define JOGPAD_TOP_Pin GPIO_PIN_6
#define JOGPAD_TOP_GPIO_Port GPIOE
#define SUPPLY_COM_Pin GPIO_PIN_1
#define SUPPLY_COM_GPIO_Port GPIOC
#define SUPPLY_SUPPLY_Pin GPIO_PIN_2
#define SUPPLY_SUPPLY_GPIO_Port GPIOC
#define OLED_RST_Pin GPIO_PIN_3
#define OLED_RST_GPIO_Port GPIOA
#define OLED_DC_Pin GPIO_PIN_4
#define OLED_DC_GPIO_Port GPIOA
#define OLED_SCK_Pin GPIO_PIN_5
#define OLED_SCK_GPIO_Port GPIOA
#define OLED_CS_Pin GPIO_PIN_6
#define OLED_CS_GPIO_Port GPIOA
#define OLED_DATA_Pin GPIO_PIN_7
#define OLED_DATA_GPIO_Port GPIOA
#define SELECT_DRIVER_Pin GPIO_PIN_0
#define SELECT_DRIVER_GPIO_Port GPIOB
#define DC_FAULT_Pin GPIO_PIN_1
#define DC_FAULT_GPIO_Port GPIOB
#define DC_SLEEP_Pin GPIO_PIN_2
#define DC_SLEEP_GPIO_Port GPIOB
#define DC_MODE_Pin GPIO_PIN_7
#define DC_MODE_GPIO_Port GPIOE
#define DC_PHASE_Pin GPIO_PIN_8
#define DC_PHASE_GPIO_Port GPIOE
#define DC_PWM_Pin GPIO_PIN_9
#define DC_PWM_GPIO_Port GPIOE
#define STEP_SLEEP_Pin GPIO_PIN_10
#define STEP_SLEEP_GPIO_Port GPIOE
#define STEP_STEP_Pin GPIO_PIN_11
#define STEP_STEP_GPIO_Port GPIOE
#define STEP_MS3_Pin GPIO_PIN_12
#define STEP_MS3_GPIO_Port GPIOE
#define STEP_MS2_Pin GPIO_PIN_13
#define STEP_MS2_GPIO_Port GPIOE
#define STEP_MS1_Pin GPIO_PIN_14
#define STEP_MS1_GPIO_Port GPIOE
#define STEP_DIR_Pin GPIO_PIN_15
#define STEP_DIR_GPIO_Port GPIOE
#define STEP_EN_Pin GPIO_PIN_10
#define STEP_EN_GPIO_Port GPIOB
#define STEP_RST_Pin GPIO_PIN_11
#define STEP_RST_GPIO_Port GPIOB
#define SENSOR_1_Pin GPIO_PIN_12
#define SENSOR_1_GPIO_Port GPIOB
#define SENSOR_2_Pin GPIO_PIN_13
#define SENSOR_2_GPIO_Port GPIOB
#define SENSOR_3_Pin GPIO_PIN_14
#define SENSOR_3_GPIO_Port GPIOB
#define SENSOR_4_Pin GPIO_PIN_15
#define SENSOR_4_GPIO_Port GPIOB
#define SENSOR_5_Pin GPIO_PIN_8
#define SENSOR_5_GPIO_Port GPIOD
#define SENSOR_6_Pin GPIO_PIN_9
#define SENSOR_6_GPIO_Port GPIOD
#define SERVO_PWM_Pin GPIO_PIN_12
#define SERVO_PWM_GPIO_Port GPIOD
#define SENSOR_9_Pin GPIO_PIN_13
#define SENSOR_9_GPIO_Port GPIOD
#define SENSOR_10_Pin GPIO_PIN_14
#define SENSOR_10_GPIO_Port GPIOD
#define MAGNET_Pin GPIO_PIN_15
#define MAGNET_GPIO_Port GPIOD
#define RGB_PWM_Pin GPIO_PIN_6
#define RGB_PWM_GPIO_Port GPIOC
#define RGB_DATA_Pin GPIO_PIN_7
#define RGB_DATA_GPIO_Port GPIOC
#define BUTTON_1_Pin GPIO_PIN_15
#define BUTTON_1_GPIO_Port GPIOA
#define BUTTON_2_Pin GPIO_PIN_10
#define BUTTON_2_GPIO_Port GPIOC
#define BUTTON_3_Pin GPIO_PIN_11
#define BUTTON_3_GPIO_Port GPIOC
#define BUTTON_4_Pin GPIO_PIN_12
#define BUTTON_4_GPIO_Port GPIOC
#define BUTTON_5_Pin GPIO_PIN_0
#define BUTTON_5_GPIO_Port GPIOD
#define BUTTON_6_Pin GPIO_PIN_1
#define BUTTON_6_GPIO_Port GPIOD
#define COMTX_Pin GPIO_PIN_6
#define COMTX_GPIO_Port GPIOB
#define COMRX_Pin GPIO_PIN_7
#define COMRX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
