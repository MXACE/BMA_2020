#include "main.h"
#include "tlc5971.h"

extern TIM_HandleTypeDef htim4;
	
volatile uint8_t position;
	
void Servo_init()
{
	htim4.Instance->CCR1 = 42;  //30-120
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
}

void Servo_angle(uint16_t angle)
{
	uint16_t DutyCycle = 0;
	
	if(angle > 180) angle = 180;
	
	if(angle == 0) DutyCycle = 30;
	else DutyCycle = 30 + angle/2;
	 
	htim4.Instance->CCR1 = DutyCycle;  //30-120
}

void Servo_open()
{
	htim4.Instance->CCR1 = 85;
}
void Servo_close()
{
	htim4.Instance->CCR1 = 42;
}

void Stepper_Init()
{
	HAL_GPIO_WritePin(STEP_SLEEP_GPIO_Port,STEP_SLEEP_Pin,GPIO_PIN_SET);	//!SLEEP -> OFF
	HAL_GPIO_WritePin(STEP_EN_GPIO_Port,STEP_EN_Pin,GPIO_PIN_RESET);	//ENABLE -> ON
	HAL_GPIO_WritePin(STEP_RST_GPIO_Port,STEP_RST_Pin,GPIO_PIN_SET); //!RESET -> ON
}

void Stepper_Deinit()
{
	HAL_GPIO_WritePin(STEP_EN_GPIO_Port,STEP_EN_Pin,GPIO_PIN_RESET);	//ENABLE -> OFF
	HAL_GPIO_WritePin(STEP_RST_GPIO_Port,STEP_RST_Pin,GPIO_PIN_SET); //!RESET -> ON
	HAL_GPIO_WritePin(STEP_SLEEP_GPIO_Port,STEP_SLEEP_Pin,GPIO_PIN_RESET);	//!SLEEP -> ON
}

void Stepper_sleep(uint8_t sleep)
{
	if(sleep) HAL_GPIO_WritePin(STEP_SLEEP_GPIO_Port,STEP_SLEEP_Pin,GPIO_PIN_SET); //!SLEEP -> OFF
	else HAL_GPIO_WritePin(STEP_SLEEP_GPIO_Port,STEP_SLEEP_Pin,GPIO_PIN_RESET); //!SLEEP -> ON
}

volatile void Stepper_Step()
{
	//int i = 0;
	HAL_GPIO_WritePin(STEP_STEP_GPIO_Port,STEP_STEP_Pin,GPIO_PIN_SET);	//STEP -> ON
	HAL_Delay(1);
	/*for(i = 0; i!= 50000; i++)
		{
			__NOP();
		}*/
	HAL_GPIO_WritePin(STEP_STEP_GPIO_Port,STEP_STEP_Pin,GPIO_PIN_RESET); //STEP -> OFF
	HAL_Delay(1);
	//for(counter = 0; counter !=168*10000; counter++);
}

void Stepper_Dir(uint8_t dir)
{
	if(dir)	HAL_GPIO_WritePin(STEP_DIR_GPIO_Port,STEP_DIR_Pin,GPIO_PIN_SET); //DIR -> ON
	else HAL_GPIO_WritePin(STEP_DIR_GPIO_Port,STEP_DIR_Pin,GPIO_PIN_RESET); //DIR -> OFF
	HAL_Delay(100);
}

void Stepper_StepSize(float fsize)
{
	uint8_t isize = 0;
	
	if(fsize == 1) isize = 1;
	else if(fsize == 1/2) isize = 2;
	else if(fsize == 1/4) isize = 4;
	else if(fsize == 1/8) isize = 8;
	else if(fsize == 1/16) isize = 16;
	else isize = 1;
	
	switch(isize)
	{
		case 1:
			HAL_GPIO_WritePin(STEP_MS1_GPIO_Port,STEP_MS1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(STEP_MS2_GPIO_Port,STEP_MS2_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(STEP_MS3_GPIO_Port,STEP_MS3_Pin,GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(STEP_MS1_GPIO_Port,STEP_MS1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(STEP_MS2_GPIO_Port,STEP_MS2_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(STEP_MS3_GPIO_Port,STEP_MS3_Pin,GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(STEP_MS1_GPIO_Port,STEP_MS1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(STEP_MS2_GPIO_Port,STEP_MS2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(STEP_MS3_GPIO_Port,STEP_MS3_Pin,GPIO_PIN_RESET);
			break;
		case 8:
			HAL_GPIO_WritePin(STEP_MS1_GPIO_Port,STEP_MS1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(STEP_MS2_GPIO_Port,STEP_MS2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(STEP_MS3_GPIO_Port,STEP_MS3_Pin,GPIO_PIN_RESET);
			break;
		case 16:
			HAL_GPIO_WritePin(STEP_MS1_GPIO_Port,STEP_MS1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(STEP_MS2_GPIO_Port,STEP_MS2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(STEP_MS3_GPIO_Port,STEP_MS3_Pin,GPIO_PIN_SET);
			break;
	}
}

char readReed(uint8_t ReedNumber)
{
	switch(ReedNumber)
	{
		case 1:
			if(HAL_GPIO_ReadPin(SENSOR_1_GPIO_Port,SENSOR_1_Pin))
			{
				return 1;
			}
			break;
			
		case 2:
			if(HAL_GPIO_ReadPin(SENSOR_2_GPIO_Port,SENSOR_2_Pin))
			{
				return 1;
			}
			break;
			
		case 3:
			if(HAL_GPIO_ReadPin(SENSOR_3_GPIO_Port,SENSOR_3_Pin))
			{
				return 1;
			}
			break;
			
		case 4:
			if(HAL_GPIO_ReadPin(SENSOR_4_GPIO_Port,SENSOR_4_Pin))
			{
				return 1;
			}
			break;
			
		case 5:
			if(HAL_GPIO_ReadPin(SENSOR_5_GPIO_Port,SENSOR_5_Pin))
			{
				return 1;
			}
			break;
			
		case 6:
			if(HAL_GPIO_ReadPin(SENSOR_6_GPIO_Port,SENSOR_6_Pin))
			{
				return 1;
			}
			break;
	}
	return 0;
}

char reedSensor(uint8_t SensorNumber)
{
	switch(SensorNumber)
	{
		case 1:
			if(HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port,SENSOR_9_Pin))
			{
				return 1;
			}
			break;
			
		case 2:
			if(HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port,SENSOR_10_Pin))
			{
				return 1;
			}
			break;
	}
	return 0;
}
char reedSensorAll(void)
{
	if(HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port,SENSOR_9_Pin))	return 1;
	else if(HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port,SENSOR_10_Pin)) return 1;
	else return 0;
}

void Stepper_GOHOME(void)
{
	int counter = 0;
	//volatile static int counter = 0;
	//while(!readReed(target) && !reedSensorAll())
	//while(!reedSensorAll())
	Stepper_Dir(1);
	while(!HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port,SENSOR_10_Pin))
	{
		Stepper_Step();
		//counter++;
	}

	HAL_Delay(100);

	Stepper_Dir(0);
	for(counter = 0 ; counter != 10; counter++)
	{
		Stepper_Step();
	}
	//counter = counter;
	position = 0;
}

// 3cm -> 145 steps
void Stepper_Goto(uint8_t target)
{
	//position = 1;
	int counter = 0;
	
	if(target > 6) target = 6;
	if(target < 0) target = 1;

	if(position == 0)
	{
		Stepper_Dir(0);
		int counter = 0;
		
		while(!HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port,SENSOR_9_Pin) &&
					!HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port,SENSOR_10_Pin) &&
					!(counter == 15))
		{
			Stepper_Step();
			counter++;
		}
		position = 1;
		HAL_Delay(1000);
		counter = 0;
	}
	//145
	if(target < position)
	{
		Stepper_Dir(1);
		
		while(!HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port,SENSOR_9_Pin) &&
					!HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port,SENSOR_10_Pin) &&
					!(counter == 150* (position - target)))
		{
			Stepper_Step();
			counter++;
		}
	}
	
	else if(target > position)
	{
		Stepper_Dir(0);
		
		while(!HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port,SENSOR_9_Pin) &&
					!HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port,SENSOR_10_Pin) &&
					(counter != (150 * (target - position))))
		{
			Stepper_Step();
			counter++;
		}
	}
	position = target;
}

void StepperGetMagnet(void)
{
	Stepper_Goto(6);
	magnet(1);
	HAL_Delay(500);
	//Stepper_StepSize(1/2);
	HAL_Delay(100);
	Stepper_Goto(1);
}
