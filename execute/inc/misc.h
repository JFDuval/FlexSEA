//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
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

extern uint8 minm_rgb_color;
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void rs485_putc(uint8 byte);
void rs485_puts(uint8 *buf, uint32 len);
void i2c_write_minm_rgb(uint8 cmd, uint8 r, uint8 g, uint8 b);
void alive_led(void);
void power_on(void);
void set_led_rgb(unsigned char r, unsigned char g, unsigned char b);
void rgb_led_ui(uint8_t err_l0, uint8_t err_l1, uint8_t err_l2, uint8_t new_comm);
void timing_test_blocking(void);
void init_sine_gen(void);
uint16 output_sine(void);
uint16 output_arb(void);
void test_current_tracking_blocking(void);
void assign_i2c_data(uint8 *newdata);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define ALIVE_HALF_T				125		//ms	

//I2C - MinM
#define MINM_BUF_SIZE				4
#define I2C_SLAVE_ADDR_MINM			0x09
#define I2C_SLAVE_ADDR_IMU			
#define SET_RGB						'n' 

/*
 RGB LED:
========
Green: everything's good
Yellow: software error, close to a voltage or temperature limit
Blue: didn't receive commands in the last 'comm_timeout' ms
Red: error
Flashing red: major error
*/

//Timings in ms:
#define UI_COMM_TIMEOUT			2000
#define UI_L0_TIMEOUT			1000
#define UI_L1_TIMEOUT			1000
#define UI_RED_FLASH_ON			100
#define UI_RED_FLASH_PERIOD		200

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
	