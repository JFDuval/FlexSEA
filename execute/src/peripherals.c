//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// peripherals: code for the general peripheral modules
//****************************************************************************

//Note:  many init_x() functions are included in other files to keep a logical
// organization. Place them here if they are not specific to one file.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "peripherals.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 clutch_pwm = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

//Initialize and enables all the peripherals
void init_peripherals(void)
{
	//Motor control variables & peripherals:
	init_motor();
	
	//Timebases:
	init_tb_timers();
	
	//UART 2 - RS-485
	init_rs485();
	
	//Analog, expansion port:
	init_analog();
	
	//Clutch:
	init_clutch();	
	
	//Enable Global Interrupts
    CyGlobalIntEnable; 
	
	//I2C1 (internal, potentiometers, Safety-CoP & IMU)
	init_i2c1();
	
	//Peripherals that depend on I2C:
	#ifdef USE_I2C_INT	
		
		//MPU-6500 IMU:
		#ifdef USE_IMU
		init_imu();
		#endif	//USE_IMU
		
		//Strain amplifier:
		#ifdef USE_STRAIN
		init_strain();
		#endif	//USE_STRAIN
		
	#endif	//USE_I2C_INT	
	
	//I2C2 (external)	
	#ifdef USE_I2C_EXT
	
	//I2C2 peripheral:
	init_i2c2();
	
	//Set RGB LED - Starts Green
	i2c_write_minm_rgb(SET_RGB, 0, 255, 0);
	
	#endif //USE_I2C_EXT
	
	// First DieTemp reading is always inaccurate -- throw out the first one
	#ifdef USE_DIETEMP	
	DieTemp_1_GetTemp(&temp);
	#endif
	
	//USB CDC
	#ifdef USE_USB	
	usb_success = init_usb();
	if(usb_success)
	{
		LED_B_Write(0);
	}
	else
	{
		LED_B_Write(1);
	}
	#endif	//USE_USB
}

//Timebase timers init:
void init_tb_timers(void)
{
	//Timer 1: 1ms (LEDs, PID)
	Timer_1_Init();
	Timer_1_Start();
	isr_t1_Start();
	
	/*
	//Timer 2: 50ms (safety)
	Timer_2_Init();
	Timer_2_Start();
	isr_t2_Start();
	*/
}

void init_rs485(void)
{
	#ifdef USE_RS485
	UART_2_Init();
	UART_2_Enable();
	UART_2_Start();		
	NOT_RE_Write(0);			//Enable RS-485 Receiver
	#endif	//USE_RS485
}

void init_i2c1(void)
{
	#ifdef USE_I2C_INT	
	/*
	I2C_1_Init();
	I2C_1_EnableInt();
	I2C_1_Enable();
	I2C_1_Start();	
	*/
	I2C_1_EnableInt();
	I2C_1_Start();	
	#endif	//USE_I2C_INT
}

void init_i2c2(void)
{
	#ifdef USE_I2C_EXT
	I2C_2_Init();
	I2C_2_Enable();
	I2C_2_Start();
	#endif	//USE_I2C_EXT	
}

//Configuration for the clutch
void init_clutch(void)
{
	//PWM2: Clutch
	PWM_2_Start();
	PWM_2_WriteCompare(0);	//Start at 0%
	//isr_pwm_Start();	
}

//PWM output for the clutch
void clutch_output(uint8 value)
{
	clutch_pwm = value;
	PWM_2_WriteCompare(clutch_pwm);
}

//Returns the PWM value of the clutch
uint8 read_clutch(void)
{
	return clutch_pwm;
}
