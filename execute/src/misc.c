//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************

//Note: It's a sign that code is misplaced when this file gets long.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "misc.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//Update the sensor structures:
void update_sensors(void)
{
	//IMU:
	#ifdef USE_I2C_INT
		
		#ifdef USE_IMU
			
			//get_accel_xyz();
			get_gyro_xyz();
			//We could also get temperature
			
		#endif	//USE_IMU
		
	#endif	//USE_I2C_INT	
	
	//Now that the I2C isn't in use we convert the strain:
	EXP2_Write(1);	//Used to test the timing - can be removed	
	ADC_DelSig_1_StartConvert();
}

//ToDo should probably be in a different file
//Sends a single character to the UART
void rs485_putc(uint8 byte)
{
	NOT_RE_Write(1);			//Disable Receiver
	UART_2_PutChar(byte);		//Send byte
	//NOT_RE_Write(0);			//Enable Receiver
}

//Sends a string of characters to the UART
//ToDo test, optimize/remove fixed delays
void rs485_puts(uint8 *buf, uint32 len)
{
	uint32_t i = 0;
	
	NOT_RE_Write(1);				//Disable Receiver
	CyDelayUs(500);					//Wait (ToDo optimize/eliminate)
	
	//Sends the bytes:
	for(i = 0; i < len; i++)
	{
		UART_2_PutChar(buf[i]);
	}
	
	CyDelayUs(50);					//Wait (ToDo optimize/eliminate)
	NOT_RE_Write(0);				//Back to normal, enable Receiver
		
}

//Write to MinM RGB LED
void i2c_write_minm_rgb(uint8 cmd, uint8 r, uint8 g, uint8 b)
{
	uint8 minm_i2c_buf[MINM_BUF_SIZE];
	
	// Write data to the slave : address pointer
	minm_i2c_buf[0] = cmd;
	minm_i2c_buf[1] = r;
	minm_i2c_buf[2] = g;
	minm_i2c_buf[3] = b;

    I2C_2_MasterWriteBuf(I2C_SLAVE_ADDR_MINM, (uint8 *) minm_i2c_buf,
                             4, I2C_2_MODE_COMPLETE_XFER);

    while(0u == (I2C_2_MasterStatus() & I2C_2_MSTAT_WR_CMPLT))
    {
        // Wait until master complete write
    }    
  
    // Clear I2C master status 
    (void) I2C_2_MasterClearStatus();
	
	return;	
}

void alive_led(void)
{
	static uint8 toggle0 = 1, count0 = 0;
	
	//Fast blinking - Alive LED
	count0++;
	if(count0 >= ALIVE_HALF_T)
	{
		count0 = 0;
		toggle0^=1;
		//LED0_Write(toggle0);
		LED_HB_Write(toggle0);
	}
}

//Power On Delay with LEDs
void power_on(void)
{
	LED_R_Write(0); LED_G_Write(1); LED_B_Write(1); 
	CyDelay(250);
	LED_R_Write(1); LED_G_Write(1); LED_B_Write(0); 
	CyDelay(250);
	LED_R_Write(1); LED_G_Write(1); LED_B_Write(1); 
	CyDelay(250);
	LED_R_Write(1); LED_G_Write(0); LED_B_Write(1); 
	CyDelay(250);
}
