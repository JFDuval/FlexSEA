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

extern uint16 last_as5047_word;	
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void timing_test_blocking(void);
void init_sine_gen(void);
uint16 output_sine(void);
uint16 output_arb(void);
void test_current_tracking_blocking(void);
void test_pwm_pulse_blocking(void);
void assign_i2c_data(uint8 *newdata);
void csea_knee_up_down_test_demo(void);
void as5047_test_code_blocking(void);
uint16 add_even_parity_msb(uint16 word);
uint16 as5047_read_single(uint16 reg);
void init_as5047(void);

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

//AS5047 Magnetic encoder:

#define AS5047_REG_NOP           0
#define AS5047_REG_ERRFL         0x0001
#define AS5047_REG_PROG          0x0003
#define AS5047_REG_DIAAGC        0x3FFC
#define AS5047_REG_MAG           0x3FFD
#define AS5047_REG_ANGLEUNC      0x3FFE
#define AS5047_REG_ANGLECOM      0x3FFF
#define AS5047_READ              0x4000     //OR it with your word
#define AS5047_WRITE             0xBFFF     //AND it with your word
#define PARITY_0                 0x7FFF     //AND it with your word
#define PARITY_1                 0x8000     //OR it with your word
#define WORDS_IN_FRAME           7
	
#endif	//INC_MISC_H
	