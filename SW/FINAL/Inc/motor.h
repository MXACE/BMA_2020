#ifndef _MOTOR_C_
#define _MOTOR_C_

#include "main.h"
extern TIM_HandleTypeDef htim4;

void Servo_init(void);
void Servo_angle(uint16_t angle);
void Servo_open(void);
void Servo_close(void);

void Stepper_Init(void);
void Stepper_Deinit(void);
void Stepper_sleep(uint8_t sleep);
volatile void Stepper_Step(void);
void Stepper_Dir(uint8_t dir);
void Stepper_StepSize(float fsize);

char readReed(uint8_t ReedNumber);
char reedSensor(uint8_t SensorNumber);
char reedSensorAll(void);

void Stepper_GOHOME(void);
void Stepper_Goto(uint8_t target);
void StepperGetMagnet(void);

#endif
