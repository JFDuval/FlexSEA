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
extern volatile uint8 data_ready_485;
extern volatile uint8 data_ready_usb;
extern volatile uint8 adc_delsig_flag;

extern uint16 last_as5047_word;	
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void test_current_tracking_blocking(void);
void test_pwm_pulse_blocking(void);
void assign_i2c_data(uint8 *newdata);
void csea_knee_up_down_test_demo(void);
uint8 timebase_1s(void);

void timing_test_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//ISR reading of I2C0 sensors (IMU, Strain Gauge, AS5048B, etc.):									
#define I2C_RQ_GYRO				1	
#define I2C_RQ_ACCEL			2
#define I2C_RQ_AS5048B			3
#define I2C_RQ_EXT_STRAIN		4

#define SDELAY	5
	
#endif	//INC_MISC_H
	