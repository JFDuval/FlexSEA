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

extern volatile struct ctrl_s ctrl;
extern struct enc_s encoder;
	
//****************************************************************************
// Prototype(s):
//****************************************************************************	

void motor_open_speed_1(int16 pwm_duty);
void motor_open_speed_2(int16 pwm_duty, int sign);
int8 serial_motor_speed(int8 letter);
int32 motor_position_pid(int32 wanted_pos, int32 actual_pos);
int32 motor_current_pid(int32 wanted_curr, int32 measured_curr);
extern inline int32 motor_current_pid_2(int32 wanted_curr, int32 measured_curr);
void control_strategy(unsigned char strat);
int motor_impedance_encoder(int wanted_pos, int new_enc_count);
void init_motor(void);
void init_motor_data_structure(void);
void motor_fixed_pwm_test_code_blocking(int spd);
int32 encoder_read(void);
void encoder_write(int32 enc);

//****************************************************************************
// Definition(s):
//****************************************************************************	

//PWM limits
#define MAX_PWM					760					//760 is 96% of 800			
#define MIN_PWM					-MAX_PWM
#define DEADTIME				55					//Make sure that it matched the hardware setting!
#define PWM1DC(pwm1)			MAX(pwm1, DEADTIME)
#define PWM2DC(pwm1)			MAX(((pwm1 - DEADTIME)>>1), 10)
	
//Position controller
#define POS_PWM_LIMIT			760				//96%
#define MAX_CUMULATIVE_ERROR	1000
#define GAIN_P					0					//Default value - will change at runtime
#define GAIN_I					0					//Idem
#define GAIN_D					0					//Idem
	
//Current controller
#define CURRENT_ZERO			((int32)2155)		//Should be calibrated board by board
#define CURRENT_SPAN			((int32)1850)		//Variation from zero (technically, that's SPAN/2)
#define CURRENT_POS_LIMIT		CURRENT_SPAN
#define CURRENT_NEG_LIMIT		(-CURRENT_SPAN)

//Impedance controller
#define B1 						2898195LL 			// 3rd order Butterworth filter numerator constants
#define B2 						8694584LL
#define B3 						8694584LL
#define B4 						2898195LL
#define A1 						1000000000LL 		// 3rd order Butterworth filter denominator constants
#define A2 						-2374094744LL
#define A3  					1929355669LL
#define A4 						-532075368LL

#define QUAD1_INIT				10000

//Nickname for the controller gains:
#define I_KP					g0
#define I_KI					g1
#define I_KD					g2
#define P_KP					g0
#define P_KI					g1
#define P_KD					g2
#define Z_K						g0
#define Z_B						g1
#define Z_I						g2

//****************************************************************************
// Structure(s)
//****************************************************************************	

	
#endif	//INC_MOTOR_H
	