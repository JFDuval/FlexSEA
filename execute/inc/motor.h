//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// motor: motor control functions
//****************************************************************************
	
#ifndef INC_MOTOR_H
#define INC_MOTOR_H

//****************************************************************************
// Include(s)
//****************************************************************************		
	
#include "main.h"
	
//****************************************************************************
// Shared variable(s)
//****************************************************************************

//****************************************************************************
// Prototype(s):
//****************************************************************************	

void init_motor(void);	
void motor_open_speed_1(int16 pwm_duty);
void motor_open_speed_2(int16 pwm_duty, int sign);

void motor_fixed_pwm_test_code_blocking(int spd);
void motor_fixed_pwm_test_code_non_blocking(int spd);

int8 serial_motor_speed(int8 letter);

//****************************************************************************
// Definition(s):
//****************************************************************************	

//PWM limits
#define MAX_PWM					760					//760 is 96% of 800			
#define MIN_PWM					-MAX_PWM
#define P1_DEADTIME				40					//Make sure that it matches the hardware setting!
#define PWM1DC(x)				MAX(x, (P1_DEADTIME+2))
#define PWM2DC(x)				MAX(((x - P1_DEADTIME)>>1), 10)
	
//****************************************************************************
// Structure(s)
//****************************************************************************	

	
#endif	//INC_MOTOR_H
	