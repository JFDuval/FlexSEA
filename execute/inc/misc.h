//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 09/2015
//****************************************************************************
// misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************
	
#ifndef INC_MISC_H
#define INC_MISC_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Shared variable(s)
//****************************************************************************	
	
extern uint8 i2c_last_request;
	
extern volatile uint8 t1_100us_flag;
extern volatile uint8 t1_time_share, t1_new_value;
	
extern uint8 adc_sar1_flag;	
extern volatile uint8 data_ready_485_1;
extern volatile uint8 data_ready_usb;
extern volatile uint8 adc_delsig_flag;

	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void timing_test_blocking(void);
void init_sine_gen(void);
uint16 output_sine(void);
uint16 output_arb(void);
void test_current_tracking_blocking(void);
void assign_i2c_data(uint8 *newdata);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Current controller tracking test:

#define PI						3.14159265
#define STEPS					50
#define STEP					(PI/STEPS)
#define DELAY					100

//ISR reading of the IMU & Safety-CoP:									
#define I2C_RQ_GYRO				1	
#define I2C_RQ_ACCEL			2
#define I2C_RQ_SAFETY			3							
	
#endif	//INC_MISC_H
	