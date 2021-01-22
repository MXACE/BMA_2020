#ifndef _MOTOR_C_
#define _MOTOR_C_

#include "main.h"
extern TIM_HandleTypeDef htim4;

void Servo_init(void);
void Servo_angle(uint16_t angle);

void Stepper_Init(void);
void Stepper_Deinit(void);
void Stepper_sleep(uint8_t sleep);
void Stepper_Step(void);
void Stepper_Dir(uint8_t dir);
void Stepper_StepSize(float fsize);

char readReed(char ReedNumber);
char reedSensor(char SensorNumber);
char reedSensorAll(void);

void Stepper_GOHOME(void);
void Stepper_Goto(char target);

#endif
