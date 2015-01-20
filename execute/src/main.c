//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// main: FlexSEA-Execute
//****************************************************************************

// FlexSEA: Flexible & Scalable Electronics Architecture

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

#ifdef USE_USB
	#warning "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
	#warning "USB Enabled - Make sure that you connect a cable!"
	#warning "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
#endif

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Misc. variables, used for debugging only
//unsigned int pid_kp = 0, pid_ki = 0, pid_kd = 0;
uint8 active_error = 0;
uint8 last_byte = 0;
int32 enccount = 0;
static unsigned char test_val = 1; // for testing die temp read times
int steps = 0, current_step = 0, pos = 0;
uint16 psoc4_vb_sns = 0, psoc4_vg_sns = 0, psoc4_3v3_sns = 0;
uint8 psoc4_temperature = 0, psoc4_status1 = 0;

//ToDo update (different ADC)
#ifdef MIT_KNEE
#define KNEE_DOWN	3000
#define KNEE_UP		1000
#define WPOS_STEP	1	
int16 wpos = KNEE_DOWN;
int16 last_wpos = KNEE_DOWN;
#endif
#ifdef MIT_ANKLE
int16 wpos = 7750;
#endif

//****************************************************************************
// External variable(s)
//****************************************************************************

//ADC
extern volatile uint16 adc1_result;
extern volatile uint16 adc1_result_avg8;
extern unsigned char adc_sar1_flag;
extern unsigned int adc_res_filtered[ADC1_CHANNELS];

//FlexSEA Network
extern unsigned char payload_str[];
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];

//Timer(s)
extern volatile uint8 t1_1ms_flag;
extern volatile uint8 t2_10ms_flag;
extern volatile uint8 t2_50ms_flag;

extern volatile unsigned char uart2_flag;
extern int16 sumoferrors;
extern int gain_p, gain_i;

extern unsigned char controller;

extern int debug_var;

//****************************************************************************
// Function(s)
//****************************************************************************

//Update the global variables from the array
void decode_psoc4_values(uint8 *psoc4_data)
{
	psoc4_vb_sns = (psoc4_data[MEM_R_VB_SNS_MSB] << 8) + psoc4_data[MEM_R_VB_SNS_LSB];
	psoc4_vg_sns = (psoc4_data[MEM_R_VG_SNS_MSB] << 8) + psoc4_data[MEM_R_VG_SNS_LSB];
	psoc4_3v3_sns = (psoc4_data[MEM_R_3V3_SNS_MSB] << 8) + psoc4_data[MEM_R_3V3_SNS_LSB];
	psoc4_temperature = psoc4_data[MEM_R_TEMPERATURE];
	psoc4_status1 = psoc4_data[MEM_R_STATUS1];
}
	
int main()
{
	//Local variables:
	uint8 usb_success = 0;
	uint16 cnt = 0;	
	uint8 toggle = 0;
	static cystatus dietmp = 0;
	int16 tmp = 0, comm_res = 0, comm_success = 0;
	uint16 mot_pos = 0;
	uint8 good_commands = 0;
	uint8 last_byte = 0, uart_buf_size = 0;
	uint8 i = 0;
	int16 pos_cmd = KNEE_DOWN;
	int usb_data_test = 0;
	int trapez_wpos = KNEE_DOWN;
	unsigned char result = 0;
	unsigned char comm_str_payload1[16];
	unsigned char ledr_state = 0, ledg_state = 0, ledb_state = 0;
	int32 usb_value = 0;
	int16 imu_accel_x = 0;
	uint8 i2c_test_wbuf[9] = {0,10,20,30,40,50,60,70,80};
	uint8 i2c_test_rbuf[24];
	uint8 toggle_wdclk = 0;
	uint8 vr1 = 0;

   	//Enable Global Interrupts
    CyGlobalIntEnable;        

	//All the peripherals but USB
	init_peripherals();
	
	#ifdef USE_I2C
	//Set RGB LED - Starts Green
	i2c_write_minm_rgb(SET_RGB, 0, 255, 0);
	#endif //USE_I2C
	
	#ifdef USE_USB
	//USB peripheral
	usb_success = init_usb();
	if(usb_success)
	{
		LED_B_Write(0);
	}
	else
	{
		LED_B_Write(1);
	}
	#endif
	
	//Give all the peripherals time to boot
	CyDelay(100);	//ToDo less time
	
	#ifdef USE_DIETEMP
	// First DieTemp reading is always inaccurate -- throw out the first one
	dietmp = DieTemp_1_GetTemp(&tmp);
	EXP2_Write(test_val);	// DieTemp_Start() is not-blocking; use interrupt
							// to query the process manually
	#endif
	
	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();
	
	//Starts with the knee down, 0 gain.
	control_strategy(CTRL_NONE);
	//pos = KNEE_DOWN;
	//steps = trapez_gen_motion_1(KNEE_DOWN, KNEE_DOWN, 1, 1);
	
	/*
	//Strain Amplifier test:
	VDAC8_3_SetValue(156);	
	i2c_test_wbuf[0] = MCP4661_REG_RAM_W1;
	i2c_test_wbuf[1] = 120;	//Offset of ~ V/2
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
	CyDelay(10);
	i2c_test_wbuf[0] = MCP4661_REG_RAM_W0;
	i2c_test_wbuf[1] = 10;	//Relatively small gain
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
	while(1)
	{
		vr1++;
			
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(1);
	}
	*/
	
	/*
	//WDCLK test code
	while(1)
	{
		toggle_wdclk ^= 1;
		WDCLK_Write(toggle_wdclk);
		CyDelayUs(500);
	}
	*/
	
	/*
	//PSoC 4 <=> PSoC 5 I2C Test code
	while(1)
	{
		//Write to slave:
		//I2C_1_MasterWriteBuf(0x11, (uint8 *) i2c_test_wbuf, 9, I2C_1_MODE_COMPLETE_XFER);
		
		//Read from slave:
		i2c_test_wbuf[0] = 0;
		I2C_1_MasterWriteBuf(0x11, (uint8 *) i2c_test_wbuf, 1, I2C_1_MODE_COMPLETE_XFER);	//Write offset
		CyDelayUs(500);
		I2C_1_MasterReadBuf(0x11, i2c_test_rbuf, 24, I2C_1_MODE_COMPLETE_XFER);
		CyDelayUs(500);
		decode_psoc4_values(i2c_test_rbuf);
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(250);	
	}
	*/
	
	/*
	//IMU test code
	while(1)
	{
		imu_accel_x = get_accel_x();
		send_usb_int16(imu_accel_x);
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(75);		
	}
	*/
	
	/*
	//ToDo Debug only - fixed PWM
	controller = CTRL_OPEN;
	//PWM_1_WriteCompare(250);	
	motor_open_speed_1(800);
	PWM_2_WriteCompare(240);
	double var1 = 0, var2 = 0, var3 = 0;
	uint8 cnt1 = 0, cnt2 = 100;
	while(1)
	{
		cnt1++; cnt2++;
		var1 = (double)((3.14159 * cnt1) / cnt2);
		var2 = (double)(16576.3 - 17.36*var1);
		var3 = sqrt(var2) * pow(var1,1.27);
		
		LED_R_Write(H1_Read());
		LED_G_Write(H2_Read());
		LED_B_Write(H3_Read());
		
		#ifdef USE_QEI1
				
		//Refresh encoder readings
		enccount = QuadDec_1_GetCounter();
				
		#endif	//USE_QEI1
	}
	*/
	
	//Main loop
	while(1)
	{
		//1ms timebase for PID controller
		if(t1_1ms_flag)
		{
			t1_1ms_flag = 0;
			
			#ifdef USE_QEI1
				
				//Refresh encoder readings
				enccount = QuadDec_1_GetCounter();
				
			#endif	//USE_QEI1
			
			#ifdef MIT_KNEE		
				
				#ifdef USE_TRAPEZ	
				
					if(controller == CTRL_POSITION)
					{
						//motor_position_pi_analog(pos, (int)adc_res_filtered[0]);				//Knee - w/ trapez
						motor_position_pi_encoder(pos, enccount);
						//ToDo confirm that it works with the increased resolution
					}
					else if(controller == CTRL_IMPEDANCE)
					{
						//Impedance controller
						motor_impedance_encoder(pos, enccount);
					}
				
				#endif	//USE_TRAPEZ	
				
			#endif		//MIT_KNEE		
			
			#ifdef MIT_ANKLE
				
				motor_position_pi_encoder(wpos, enccount);				//Ankle
				
			#endif		//MIT_ANKLE
			
			//If no controller is used the PWM should be 0:
			if(controller == CTRL_NONE)
			{
				motor_open_speed_1(0);
			}			
		}
		
		//10ms timebase for trajectory generation 
		//ToDo Move it to 1ms in the future (trapez.c will need to be updated first)
		if(t2_10ms_flag)
		{
			t2_10ms_flag = 0;
			
			#ifdef USE_TRAPEZ	
				
				if((controller == CTRL_POSITION) || (controller == CTRL_IMPEDANCE))
				{	
					//Trapezoidal trajectories (can be used for both Position & Impedance)				
					pos = trapez_get_pos(steps);	//New setpoint
				}
			
			#endif	//USE_TRAPEZ	
		}
		
		//50ms timebase for safety checks, etc
		if(t2_50ms_flag)
		{
			t2_50ms_flag = 0;
			
			#ifdef USE_DIETEMP
				
				//Die temperature too high?
				dietmp = DieTemp_1_Query(&tmp);
				//active_error = 1;	//ToDo Tests
				if(dietmp == CYRET_SUCCESS)
				{
					DieTemp_1_Start(); 		// start next temp reading
					//test_val = ~test_val; 	// for testing -- scope to get average
					//EXP2_Write(test_val);   // successful read times
					if(tmp > MAX_DIE_TEMP)
	 					active_error = 1;
					else
						active_error = 0;
				} 
				else if(dietmp == (CYRET_TIMEOUT))
				{
					DieTemp_1_Start(); 		// start next temp reading
				}
			
			#endif	//USE_DIETEMP	
			
			#ifdef USE_USB
			//USB debugging
			//usb_value += 1000;
			//send_usb_int16(debug_var);
			//send_usb_int16((int16) ((QuadDec_1_GetCounter() >> 2) & 0xFFFF));	
			#endif
		}
		
		#ifdef USE_USB
			
			//USB Data
			if(usb_echo_blocking())
			{
				//Got new data in 
				//Try to decode
				comm_res = comm_decode_str();
				if(comm_res)
					comm_success = 1;
				
				//Toggle LED0 with new commands
				ledr_state ^= 1;
				LED_R_Write(ledr_state);
			}
			
		#endif	//USE_USB
		
		//RS-485 Byte Input
		#ifdef USE_RS485
			
			//UART2 (RS485)
			if(uart2_flag)
			{
				uart2_flag = 0;
			}
			
			uart_buf_size = UART_2_GetRxBufferSize();
			if(uart_buf_size)
			{
				for(i = 0; i < uart_buf_size; i++)
				{
					last_byte = UART_2_GetChar();
					comm_update_rx_buffer(last_byte);
				}
				
				//Got new data in, try to decode
				comm_res = comm_decode_str();
				if(comm_res)
				{
					comm_res = 0;
					comm_success = 1;
				}
			}
			
		#endif	//USE_RS485
		
		//FlexSEA Network Communication
		#ifdef USE_COMM
			
			//We received a communication string
			if(comm_success)
			{
				comm_success = 0;
				good_commands++;
				
				//Cheap trick to get first line
				for(i = 0; i < 16; i++)
				{
					comm_str_payload1[i] = comm_str_payload[0][i];
				}
				
				//payload_parse_str() calls the functions (if valid)
				result = payload_parse_str(comm_str_payload1);
				
				//Toggle LED1 with new commands
				ledb_state ^= 1;
				LED_B_Write(ledb_state);
			}
		
		#endif	//USE_COMM
		
		//ADC results ready to be filtered?
		if(adc_sar1_flag)
		{
			adc_sar1_flag = 0;
			filter_adc();
		}
		
		//WatchDog Clock
		toggle_wdclk ^= 1;
		WDCLK_Write(toggle_wdclk);
	}
}
