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
// Variable(s)
//****************************************************************************

volatile int8_t tx_cnt = 0;

//Timers:
volatile uint8 t1_100us_flag = 0;
volatile uint8 t1_1ms_1_flag = 0, t1_1ms_2_flag = 0;
volatile uint8 t2_10ms_flag = 0;
volatile uint8 t2_50ms_flag = 0;	

//ADC:
uint8 adc_sar1_flag = 0;
volatile uint8 adc_delsig_flag = 0;

//UART:
volatile uint8 data_ready_485_1 = 0;

//USB:
volatile uint8 data_ready_usb = 0;

//MinM RGB:
uint8 minm_rgb_color = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

//Update the sensor structures
//Call this one in the 1ms #1 routine
void update_sensors_1(void)
{
	//IMU:
	#ifdef USE_I2C_INT
		
		#ifdef USE_IMU
			
			//get_accel_xyz();
			get_gyro_xyz();
			//We could also get temperature
			
		#endif	//USE_IMU
		
		//Safety-CoP status:
		safety_cop_get_status();
		
	#endif	//USE_I2C_INT	
}

//Update the sensor structures
//Call this one in the 1ms #2 routine
void update_sensors_2(void)
{
	//Now that the I2C isn't in use we convert the strain:
	EXP5_Write(1);
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
	uint32_t i = 0, log = 0;
	
	NOT_RE_Write(1);				//Disable Receiver
	CyDelayUs(1);					//Wait (ToDo optimize/eliminate)
	//UART_2_ClearTxBuffer();			//Flush the TX buffer
	DE_Write(1);
	CyDelayUs(1);
	tx_cnt = len;
	
	//Can we store all the bytes we want to send?
	if((UART_2_TXBUFFERSIZE - UART_2_GetTxBufferSize()) < len)
	{
		//EXP5_Write(1);
		//Buffer is overflowing, flush it:
		UART_2_ClearTxBuffer();
		//EXP5_Write(0);
	}	
	
	//Sends the bytes:
	for(i = 0; i < len; i++)
	{
		UART_2_PutChar(buf[i]);
	}	
	
	//Wait till they get out
	CyDelayUs(100);					//Wait (ToDo optimize/eliminate)
		
	//Back to normal, enable Receiver disable emitter
	DE_Write(0);
	CyDelayUs(1);
	NOT_RE_Write(0);				
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
	set_led_rgb(1,0,0);
	CyDelay(250);
	set_led_rgb(0,1,0);
	CyDelay(250);
	set_led_rgb(0,0,1);
	CyDelay(250);
	set_led_rgb(0,0,0);
	CyDelay(250);
}

void set_led_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	//No fading, we use 1 or 0 for now. Flipping the sign so x = 1 means ON

	LED_R_Write((r & 0x01)^1);
	LED_G_Write((g & 0x01)^1);
	LED_B_Write((b & 0x01)^1);
}

//Call this function every ms in main while()
void rgb_led_ui(uint8_t err_l0, uint8_t err_l1, uint8_t err_l2, uint8_t new_comm)
{
	static uint32_t cnt_comm = UI_COMM_TIMEOUT, cnt_err_l0 = 0, cnt_err_l1 = 0, cnt_flash = 0;
	static uint8_t latch_err_l2 = 0, flash_red = 0, comm_blue = 0;
	uint8_t r = 0, g = 0, b = 0;

	//Set variable for the flashing red light:
	if(cnt_flash < UI_RED_FLASH_ON)
	{
		flash_red = 1;
	}
	else
	{
		flash_red = 0;
	}

	cnt_flash++;
	if(cnt_flash >= UI_RED_FLASH_PERIOD)
	{
		cnt_flash = 0;
	}

	//New communication green/blue:
	if(new_comm)
	{
		//Received a new valid packet, resets the counter
		cnt_comm = UI_COMM_TIMEOUT;
	}

	if(cnt_comm > 0)
		cnt_comm--;

	if(!cnt_comm)
	{
		comm_blue = 1;
	}
	else
	{
		comm_blue = 0;
	}

	//From the highest priority to the lowest:
	//=======================================

	if((err_l2 == 1) || (latch_err_l2 == 1))
	{
		//Major error => flashing red

		latch_err_l2 = 1;	//Latching it, will require a reset to be normal again
		r = flash_red;
		g = 0;
		b = 0;
	}
	else
	{
		if(err_l1 == 1)
		{
			//Intermediate error => Steady Red
			r = 1;
			g = 0;
			b = 0;
		}
		else
		{
			if(err_l0 == 1)
			{
				//Software error => Steady Yellow
				r = 1;
				g = 1;
				b = 0;
			}
			else
			{
				if(comm_blue == 1)
				{
					//Communication timeout, blue
					r = 0;
					g = 0;
					b = 1;
				}
				else
				{
					//Normal, green
					r = 0;
					g = 1;
					b = 0;
				}
			}
		}
	}

	//Assign the color to the RGB LED:
	set_led_rgb(r, g, b);
}

//How long does it take to run X function? Use this code and a scope to find out.
#define SDELAY	5
void timing_test_blocking(void)
{
	//Disable Global Interrupts
    CyGlobalIntDisable; 
	
	while(1)
	{
		//Synch sequence
		EXP9_Write(1);
		EXP8_Write(0);
		EXP8_Write(1);
		EXP8_Write(0);
		EXP8_Write(1);
		EXP8_Write(0);
		
		CyDelayUs(SDELAY);
		
		//Motor current PID
		EXP8_Write(1);
		motor_current_pid(ctrl.current.setpoint_val, ctrl.current.actual_val);
		EXP8_Write(0);
		
		//Motor current PID #2
		EXP8_Write(1);
		motor_current_pid_2(ctrl.current.setpoint_val, ctrl.current.actual_val);
		EXP8_Write(0);
		
		//Exit sequence:
		EXP9_Write(0);
		CyDelayUs(10*SDELAY);
		
		/*
		
		//SAR ADC filter
		EXP8_Write(1);
		filter_adc();
		EXP8_Write(0);
		
		//DelSig ADC filter
		EXP8_Write(1);
		strain_filter_dma();
		EXP8_Write(0);
		
		//Unpack payload (no data in the buffer)
		EXP8_Write(1);
		unpack_payload_485_1();
		EXP8_Write(0);
		
		//Exit sequence:
		EXP9_Write(0);
		CyDelayUs(10*SDELAY);
		*/
		
		/*
		//Position controller
		EXP8_Write(1);
		motor_position_pid(ctrl.position.setpoint_val, ctrl.position.actual_val);
		EXP8_Write(0);
		
		CyDelayUs(SDELAY);
		
		//Impedance controller:
		EXP8_Write(1);
		motor_impedance_encoder(ctrl.impedance.setpoint_val, ctrl.impedance.actual_val);
		EXP8_Write(0);
		
		CyDelayUs(SDELAY);
		
		//RGB LED UI:
		EXP8_Write(1);
		rgb_led_ui(1, 1, 1, 1);
		EXP8_Write(0);

		//Exit sequence:
		EXP9_Write(0);
		CyDelayUs(10*SDELAY);
		*/
		
		/*
		filter_adc();
		
		strain_filter_dma();
		*/
		
		/*
		unpack_payload_485_1();
	
		//Valid communication from RS-485 #1?
		if(cmd_ready_485_1 != 0)
		{
			cmd_ready_485_1 = 0;
			
			//Cheap trick to get first line	//ToDo: support more than 1
			for(i = 0; i < PAYLOAD_BUF_LEN; i++)
			{
				tmp_rx_command_485_1[i] = rx_command_485_1[0][i];
			}
			
			//payload_parse_str() calls the functions (if valid)
			result = payload_parse_str(tmp_rx_command_485_1);
			
			//LED:
			new_cmd_led = 1;
		}
		*/
	}
	
}
