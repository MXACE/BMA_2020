/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "ssd1351.h"
#include "gfx.h"
#include "menu.h"
#include "COM.h"
#include "buttons.h"
#include "tlc5971.h"
#include "rng.h"
#include "motor.h"
#include "FLASH_SECTOR.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RNG_HandleTypeDef hrng;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RNG_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
void pin_cs(uint8_t pinstate);
void pin_dc(uint8_t pinstate);
void pin_rs(uint8_t pinstate);
void transmit_data(uint8_t *data, uint32_t len);
void user_delay_ms(uint32_t period);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char SUPPLY = 0; //COM = 0, SUPPLY = 1

//uint32_t Rx_Data[10];
char string[40];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
	char tempString[1];

	uint8_t method = 0;

	uint8_t RNG_Number[] = {0,0,0,0,0,0,0,0,0,0};

	uint16_t counter = 0;

	uint8_t BoxButtonPushed = 0;

	//uint32_t Rx_Data[10];
	//uint32_t data[] = {0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA,0xAAAAAAAA};
	uint32_t data[] = {0xAAAAAAAA,0xAAAAAAAA,0xBBBBBBBB};

	uint8_t temp;
	char i = 0;

	char rightLED = 0;
	/* 0: amount led
	 * 1: right led
	 * 2: amount motor
	 * 3: right motor
	 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_RNG_Init();
	MX_SPI1_Init();
	MX_TIM1_Init();
	MX_TIM4_Init();
	MX_USART1_UART_Init();

	/* Initialize interrupts */
	MX_NVIC_Init();
	/* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);

	//SETUP

	/*Flash_Read_Data(0x08060000, data);
	if(data[2] == 0)
	{
		data[0] = 0xAAAAAAAA;
		data[1] = 0xAAAAAAAA;
		//data[2] = 0xAAAAAAAA;
		//data[3] = 0xAAAAAAAA;
		Flash_Write_Data(0x08060000, data);
	}

	//TEMP--------------------------------------
	data[0] = 0xAAAAAAAA + 100;
	data[1] = 0xAAAAAAAA + 55;
	//data[2] = 0xAAAAAAAA + 100;
	//data[3] = 0xAAAAAAAA + 44;
	//------------------------------------------

	//data[0] += 10;

	Flash_Write_Data(0x08060000, data);
	Flash_Read_Data(0x08060000, data);
	//Convert_To_Str(Rx_Data, string);
	/* */
	//while(1);
	/*
	int c = 0;



	COM_TX("DONE\r\n");

*//*
	Stepper_Init();
	Stepper_GOHOME();
	HAL_Delay(500);
	StepperGetMagnet();
	magnet(0);
	Stepper_Deinit();
	while(1);
*/


	s_ssd1351 fnptrs_main;

	fnptrs_main.pin_cs = pin_cs;
	fnptrs_main.pin_rs = pin_rs;
	fnptrs_main.pin_dc = pin_dc;
	fnptrs_main.transmit_data = transmit_data;
	fnptrs_main.delay = user_delay_ms;

	init_oled(1,1, &fnptrs_main);

	RGB_setLED(1,30000,2000,30000);
	RGB_setLED(2,30000,2000,30000);
	RGB_setLED(3,30000,2000,30000);
	RGB_setLED(4,30000,2000,30000);
	RGB_setLED(5,30000,2000,30000);
	RGB_setLED(6,30000,2000,30000);
	RGB_setLED(7,0,0,0);
	RGB_setLED(8,0,0,0);

	RGB_Setup();
	RGB_SHOW();


	COM_TX("START\r\n");

	SetMenu(4);
	HAL_Delay(1000);

	if(HAL_GPIO_ReadPin(SUPPLY_SUPPLY_GPIO_Port,SUPPLY_SUPPLY_Pin))
	{
		SetMenu(1);
		Servo_init();
	}
	else
	{
		SetMenu(7);
	}


	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
	/* USER CODE END WHILE */
		Button_manager(ReadJogpad());

		/*if(Menu_Flags(4,0))
		{
			method = 0;
		}*/
		if(Menu_Flags(3,0))
		{
			if(Menu_Flags(0,0))
			{
				method = 1;
			}
			else if(Menu_Flags(1,0))
			{
				method = 2;
			}
			else
			{
				method = 0;
			}
		}

		BoxButtonPushed = 0;

		switch(method)
		{
		//LEDS
		case 1:

			for(i = 0; i != 8; i ++)
			{
				RGB_setLED(i,0,0,0);
			}
			for(i=0; i != 4; i++)
			{
				RGB_setLED(1,12000,0,6000);
				RGB_SHOW();
				HAL_Delay(500);

				RGB_setLED(1,0,0,0);
				RGB_SHOW();
				HAL_Delay(500);
			}
			blankscreen(colors.blue);

			for(counter = 0; counter != 50; counter ++)
			{
				RNG_Prepare(RNG_Number);
				//Wrong
				/*
				RGB_setLED(1,RNG_Number[1]*10000,RNG_Number[1]*2000,0);
				RGB_setLED(2,RNG_Number[2]*10000,RNG_Number[2]*2000,0);
				RGB_setLED(3,RNG_Number[3]*10000,RNG_Number[3]*2000,0);
				RGB_setLED(4,RNG_Number[4]*10000,RNG_Number[4]*2000,0);
				RGB_setLED(5,RNG_Number[5]*10000,RNG_Number[5]*2000,0);
				RGB_setLED(6,RNG_Number[6]*10000,RNG_Number[6]*2000,0);
				*/
				RGB_setLED(1, RNG_Number[1]*RNG_Number[8]*1000,	RNG_Number[4]*RNG_Number[3]*1000,	RNG_Number[7]*RNG_Number[6]*1000);
				RGB_setLED(2, RNG_Number[2]*RNG_Number[7]*1000,	RNG_Number[5]*RNG_Number[2]*1000,	RNG_Number[8]*RNG_Number[5]*1000);
				RGB_setLED(3, RNG_Number[3]*RNG_Number[6]*1000,	RNG_Number[6]*RNG_Number[1]*1000,	RNG_Number[9]*RNG_Number[4]*1000);
				RGB_setLED(4, RNG_Number[4]*RNG_Number[1]*1000,	RNG_Number[7]*RNG_Number[4]*1000,	RNG_Number[0]*RNG_Number[3]*1000);
				RGB_setLED(5, RNG_Number[5]*RNG_Number[9]*1000,	RNG_Number[8]*RNG_Number[5]*1000,	RNG_Number[1]*RNG_Number[2]*1000);
				RGB_setLED(6, RNG_Number[6]*RNG_Number[4]*1000,	RNG_Number[9]*RNG_Number[6]*1000,	RNG_Number[2]*RNG_Number[1]*1000);
				RGB_setLED(7,0,0,0);
				RGB_setLED(8,0,0,0);

				/*
				RGB_setLED(1,30000,1000,0);
				RGB_setLED(2,30000,1000,0);
				RGB_setLED(3,30000,1000,0);
				RGB_setLED(4,30000,1000,0);
				RGB_setLED(5,30000,1000,0);
				RGB_setLED(6,30000,1000,0);*/
				//Right
				RGB_setLED(RNG_Number[0],RNG_Number[0]*6000,RNG_Number[0]*0,RNG_Number[0]*3000);
				RGB_SHOW();
				HAL_Delay(100);

				if(!(counter >= 49))
				{
					for(i = 0; i != 10; i++)
					{
						RNG_Number[i] = 0;
					}
				}
			}
			RGB_setLED(1,10000,2000,0);
			RGB_setLED(2,10000,2000,0);
			RGB_setLED(3,10000,2000,0);
			RGB_setLED(4,10000,2000,0);
			RGB_setLED(5,10000,2000,0);
			RGB_setLED(6,10000,2000,0);
			//Right
			RGB_setLED(RNG_Number[0],10000,2000,0);
			RGB_SHOW();
			SetMenu(8);
			COM_TX("[LED]: Right: ");
			sprintf(tempString, "%i", (int)RNG_Number[0]);
			COM_TX(tempString);
			COM_TX("\r\n");

			/*
			while(!BoxButtonPushed)
			{
				for(counter = 1; counter <= 6; counter++ )
				{
					if(ReadButtons(counter))
					{
						BoxButtonPushed = 1;
						break;
					}
				}
			}*/

			while(!BoxButtonPushed)
			{
				for(counter = 1; counter <= 6; counter++ )
				{
					if(ReadButtons(counter))
					{
						BoxButtonPushed = 1;
						break;
					}
				}
			}
			COM_TX("[LED]: Guessed: ");
			sprintf(tempString, "%i", (int)counter);
			COM_TX(tempString);
			COM_TX("\r\n");

			temp = counter;
			for(counter = 1; counter <= 8; counter++ )
			{
				RGB_setLED(counter,0,0,0);
			}
			RGB_setLED(temp,0,0,30000);
			RGB_SHOW();
			HAL_Delay(3000);

			//true
			if(counter == RNG_Number[0])
			{
				RGB_setLED(counter,0,30000,0);

			}
			//wrong
			else
			{
				//uint8_t temp = counter;
				for(counter = 1; counter <= 8; counter++ )
				{
					RGB_setLED(counter,0,0,0);
				}
				RGB_setLED(temp,30000,0,0);
				RGB_setLED(RNG_Number[0],0,30000,0);
			}
			RGB_SHOW();

			/*
			if(HAL_GPIO_ReadPin(SUPPLY_SUPPLY_GPIO_Port,SUPPLY_SUPPLY_Pin))
			{
				SetMenu(1);
			}
			else
			{
				SetMenu(7);
			}*/
			Menu_Flags(0,1);
			SetMenu(2);
			method = 0;

			break;
		//MOTOR
		case 2:

			/*
			0: move 1
			1: move 2
			2: move 3
			3: move 4
			4: move 5
			5: move 6
			6: start
			7: moves
			8: drop
			*/

			RNG_Prepare(RNG_Number);
//////////////////////////////////////////
			//while(1);
//////////////////////////////////////////
			Servo_close();
			Stepper_Init();
			Stepper_StepSize(1);
			Stepper_GOHOME();
			HAL_Delay(500);
			StepperGetMagnet();
			Stepper_Deinit();

			Stepper_StepSize(1);
			HAL_Delay(100);


			for(i = 0; i != 8; i ++)
			{
				RGB_setLED(i,0,0,0);
			}
			for(i=0; i != 4; i++)
			{
				RGB_setLED(1,12000,0,6000);
				RGB_SHOW();
				HAL_Delay(500);

				RGB_setLED(1,0,0,0);
				RGB_SHOW();
				HAL_Delay(500);
			}
			blankscreen(colors.blue);

			COM_TX("[MOTOR]: Right: ");
			sprintf(tempString, "%i", (int)RNG_Number[8]);
			COM_TX(tempString);
			COM_TX("\r\n");
			Stepper_Init();
			HAL_Delay(200);
			Stepper_Goto(RNG_Number[6]);

			HAL_Delay(100);
			//for(counter = 0; counter != RNG_Number[7]; counter++ )
			for(counter = 0; counter != 6; counter++ )
			{
				Stepper_Goto(RNG_Number[counter]);
				if(RNG_Number[8] - 1  == counter)
				{
					magnet(0);
					rightLED = RNG_Number[counter];
					//HAL_Delay(1000);
				}
				HAL_Delay(300);
			}

			Stepper_Deinit();
			char c;

			for(c = 1; c!= 7; c++)
			{
				RGB_setLED(c,10000,2000,0);
			}

			RGB_setLED(7,0,0,0);
			RGB_setLED(8,0,0,0);
			RGB_SHOW();

			SetMenu(8);

			while(!BoxButtonPushed)
			{
				for(counter = 1; counter <= 6; counter++ )
				{
					if(ReadButtons(counter))
					{
						BoxButtonPushed = 1;
						break;
					}
				}
			}

			COM_TX("[MOTOR]: Guessed: ");
			sprintf(tempString, "%i", (int)counter);
			COM_TX(tempString);
			COM_TX("\r\n");

			temp = counter;
			for(counter = 1; counter <= 8; counter++ )
			{
				RGB_setLED(counter,0,0,0);
			}
			RGB_setLED(temp,0,0,30000);
			RGB_SHOW();
			HAL_Delay(3000);

			Servo_open();
			//true
			//if(temp == RNG_Number[RNG_Number[8]-1])
			if(temp == rightLED)
			{
				RGB_setLED(temp,0,30000,0);

			}
			//wrong
			else
			{
				//uint8_t temp = counter;
				for(counter = 1; counter <= 8; counter++ )
				{
					RGB_setLED(counter,0,0,0);
				}
				RGB_setLED(temp,30000,0,0);
				RGB_setLED(RNG_Number[0],0,30000,0);
			}
			RGB_SHOW();

			/*if(HAL_GPIO_ReadPin(SUPPLY_SUPPLY_GPIO_Port,SUPPLY_SUPPLY_Pin))
			{
				SetMenu(1);
			}
			else
			{
				SetMenu(7);
			}*/

			Menu_Flags(1,1);
			SetMenu(2);
			method = 0;
			break;
		default:
			break;
		}
		counter = 0;
	/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 13;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1806;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, OLED_RST_Pin|OLED_DC_Pin|OLED_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DC_SLEEP_Pin|STEP_EN_Pin|STEP_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, DC_MODE_Pin|DC_PHASE_Pin|STEP_SLEEP_Pin|STEP_STEP_Pin
                          |STEP_MS3_Pin|STEP_MS2_Pin|STEP_MS1_Pin|STEP_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MAGNET_GPIO_Port, MAGNET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RGB_PWM_Pin|RGB_DATA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : JOGPAD_MID_Pin JOGPAD_BOTTOM_Pin JOGPAD_RIGHT_Pin JOGPAD_LEFT_Pin
                           JOGPAD_TOP_Pin */
  GPIO_InitStruct.Pin = JOGPAD_MID_Pin|JOGPAD_BOTTOM_Pin|JOGPAD_RIGHT_Pin|JOGPAD_LEFT_Pin
                          |JOGPAD_TOP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SUPPLY_COM_Pin SUPPLY_SUPPLY_Pin BUTTON_2_Pin BUTTON_3_Pin
                           BUTTON_4_Pin */
  GPIO_InitStruct.Pin = SUPPLY_COM_Pin|SUPPLY_SUPPLY_Pin|BUTTON_2_Pin|BUTTON_3_Pin
                          |BUTTON_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : OLED_RST_Pin OLED_DC_Pin OLED_CS_Pin */
  GPIO_InitStruct.Pin = OLED_RST_Pin|OLED_DC_Pin|OLED_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SELECT_DRIVER_Pin DC_FAULT_Pin SENSOR_1_Pin SENSOR_2_Pin
                           SENSOR_3_Pin SENSOR_4_Pin */
  GPIO_InitStruct.Pin = SELECT_DRIVER_Pin|DC_FAULT_Pin|SENSOR_1_Pin|SENSOR_2_Pin
                          |SENSOR_3_Pin|SENSOR_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DC_SLEEP_Pin STEP_EN_Pin STEP_RST_Pin */
  GPIO_InitStruct.Pin = DC_SLEEP_Pin|STEP_EN_Pin|STEP_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DC_MODE_Pin DC_PHASE_Pin STEP_SLEEP_Pin STEP_MS3_Pin
                           STEP_MS2_Pin STEP_MS1_Pin STEP_DIR_Pin */
  GPIO_InitStruct.Pin = DC_MODE_Pin|DC_PHASE_Pin|STEP_SLEEP_Pin|STEP_MS3_Pin
                          |STEP_MS2_Pin|STEP_MS1_Pin|STEP_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : STEP_STEP_Pin */
  GPIO_InitStruct.Pin = STEP_STEP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(STEP_STEP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SENSOR_5_Pin SENSOR_6_Pin SENSOR_9_Pin SENSOR_10_Pin
                           BUTTON_5_Pin BUTTON_6_Pin */
  GPIO_InitStruct.Pin = SENSOR_5_Pin|SENSOR_6_Pin|SENSOR_9_Pin|SENSOR_10_Pin
                          |BUTTON_5_Pin|BUTTON_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : MAGNET_Pin */
  GPIO_InitStruct.Pin = MAGNET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MAGNET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RGB_PWM_Pin RGB_DATA_Pin */
  GPIO_InitStruct.Pin = RGB_PWM_Pin|RGB_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_1_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(BUTTON_1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void pin_cs(uint8_t pinstate)
{
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, pinstate);
}

void pin_dc(uint8_t pinstate)
{
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_DC_Pin, pinstate);
}

void pin_rs(uint8_t pinstate)
{
	HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_RST_Pin, pinstate);
}

void transmit_data(uint8_t *data, uint32_t len)
{
	HAL_SPI_Transmit(&hspi1, data, len, 1000);
}
void user_delay_ms(uint32_t period)
{
	HAL_Delay(period);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
