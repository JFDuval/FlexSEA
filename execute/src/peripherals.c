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

uint8 uart_dma_rx_buf[96];	//ToDo #define
uint8 uart_dma_tx_buf[96];
uint8 DMA_4_Chan;
uint8 DMA_4_TD[1];

//****************************************************************************
// Function(s)
//****************************************************************************

//Initialize and enables all the peripherals
void init_peripherals(void)
{
	//Motor control variables & peripherals:
	init_motor();
	
	//Init Control:
	init_ctrl_data_structure();
	
	//Timebases:
	init_tb_timers();
	
	//UART 2 - RS-485
	init_rs485();
	
	//Analog, expansion port:
	init_analog();
	
	//Clutch:
	init_pwro();	
	
	//Enable Global Interrupts
    CyGlobalIntEnable; 
	
	//I2C0 - 3V3, IMU & Expansion
	#ifdef USE_I2C_0	
		
		init_i2c_0();
		
		//MPU-6500 IMU:
		#ifdef USE_IMU
			
		init_imu();
		CyDelay(25);
		init_imu();
		CyDelay(25);
		init_imu();
		CyDelay(25);
		
		#endif	//USE_IMU
		
		//External RGB LED:
		#ifdef USE_MINM_RGB
			
		//Set RGB LED - Starts Green
		i2c_init_minm(MINM_GREEN);
		
		#endif 	//USE_MINM_RGB
	
	#endif	//USE_I2C_0
	
	//I2C1 - 5V, Safety-CoP & strain gauge pot
	#ifdef USE_I2C_1	
		
		//I2C1 peripheral:
		init_i2c_1();
		
		//Strain amplifier:
		#ifdef USE_STRAIN
			
		init_strain();
		
		#endif	//USE_STRAIN
		
	#endif	//USE_I2C_1	
	
	//Magnetic encoder:
	#ifdef USE_AS5047		
	
	init_as5047();
	
	#endif //USE_AS5047
	
	#ifdef USE_SPI_COMMUT
	//...	
	#endif 	//USE_SPI_COMMUT
	
	//Die temperatuire measurement
	#ifdef USE_DIETEMP	
	DieTemp_1_GetTemp(&temp);
	#endif
	
	//Special color when waiting for USB (Yellow):
	set_led_rgb(1, 1, 0);
	
	//USB CDC
	#ifdef USE_USB	
	init_usb();
	#endif	//USE_USB
}

//Timebase timers init:
void init_tb_timers(void)
{
	//Timer 1: 1ms (LEDs, PID)
	Timer_1_Init();
	Timer_1_Start();
	isr_t1_Start();
}

//I2C0 - 3V3, IMU & Expansion.
void init_i2c_0(void)
{
	I2C_0_EnableInt();
	I2C_0_Start();	
}

//I2C1 - 5V, Safety-CoP & strain gauge pot
void init_i2c_1(void)
{
	I2C_1_EnableInt();
	I2C_1_Start();
}
