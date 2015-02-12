//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
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
	#warning "   USB Enabled - Make sure to connect a cable!   "
	#warning "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
#endif

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Misc. variables, used for debugging only
uint8 last_byte = 0;
int steps = 0, current_step = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

//FlexSEA Network
extern unsigned char payload_str[];
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];

//Timer(s)
extern volatile uint8 t1_1ms_flag;
extern volatile uint8 t2_10ms_flag;
extern volatile uint8 t2_50ms_flag;

//ADC
extern volatile uint16 adc1_result;
extern volatile uint16 adc1_result_avg8;
extern unsigned char adc_sar1_flag;
extern unsigned int adc_res_filtered[ADC1_CHANNELS];

//RS-485:
extern volatile unsigned char uart2_flag;

//motor.c:
extern struct ctrl_s ctrl;

//peripherals.c
extern uint8 usb_success;

//DelSig ADC:
extern uint8 adc_delsig_flag;

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Local variables:
	int16 comm_res = 0, comm_success = 0;
	uint8 good_commands = 0;
	uint8 last_byte = 0, uart_buf_size = 0;
	uint8 i = 0;
	unsigned char result = 0;
	unsigned char comm_str_payload1[16];
	unsigned char ledr_state = 0, ledg_state = 0, ledb_state = 0;
	uint8 toggle_wdclk = 0;	

	//Power on delay
	CyDelay(750);
	
   	//Enable Global Interrupts
    CyGlobalIntEnable;        

	//Initialize all the peripherals
	init_peripherals();
	
	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();	
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Test code - enable one and only one for special debugging
	//Normal code WILL NOT EXECUTE when this is enabled!
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//strain_test_blocking();
	//safety_cop_comm_test_blocking();
	//imu_test_code_blocking();
	//motor_fixed_pwm_test_code_blocking(800);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	
	//RGB Off
	LED_R_Write(1); LED_G_Write(1); LED_B_Write(1); 
	
	//Main loop
	while(1)
	{
		//1ms timebase
		//ToDo confirm that it doesn't take more than 1ms to execute with all the new sensor functions
		if(t1_1ms_flag)
		{
			t1_1ms_flag = 0;
			
			EXP8_Write(1);	//Used to test the timing - can be removed	
			
			#ifdef USE_QEI1
				
				//Refresh encoder readings
				encoder_read();
				
			#endif	//USE_QEI1			
			
			#ifdef USE_TRAPEZ	
			
				if(ctrl.active_ctrl == CTRL_POSITION)
				{
					motor_position_pid(ctrl.position.setpoint_val, ctrl.position.actual_val);
				}
				else if(ctrl.active_ctrl == CTRL_IMPEDANCE)
				{
					//Impedance controller
					motor_impedance_encoder(ctrl.impedance.setpoint_val, ctrl.impedance.actual_val);
				}
			
			#endif	//USE_TRAPEZ
			
			//Refresh all the sensor data:
			update_sensors();
			
			//Alive LED
			alive_led();
			
			EXP8_Write(0);	//Used to test the timing - can be removed	
		}
		
		//10ms timebase
		if(t2_10ms_flag)
		{
			t2_10ms_flag = 0;
			
			#ifdef USE_TRAPEZ	
				
				if((ctrl.active_ctrl == CTRL_POSITION) || (ctrl.active_ctrl == CTRL_IMPEDANCE))
				{	
					//Trapezoidal trajectories (can be used for both Position & Impedance)				
					ctrl.position.setpoint_val = trapez_get_pos(steps);	//New setpoint
					//ToDo Move it to 1ms in the future (trapez.c will need to be updated first)
				}
			
			#endif	//USE_TRAPEZ	
			
			//If no controller is used the PWM should be 0:
			if(ctrl.active_ctrl == CTRL_NONE)
			{
				motor_open_speed_1(0);
			}
		}
		
		//50ms timebase for safety checks, etc
		if(t2_50ms_flag)
		{
			t2_50ms_flag = 0;
			
			dietemp_read();	//ToDo store in variable			
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
				
				//Toggle LEDR with new commands
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
			
			//We received a communication string (from RS-485 or from USB)
			if(comm_success)
			{
				comm_success = 0;
				good_commands++;	//Only used for debugging
				
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
		
		//SAR ADC results ready to be filtered?
		if(adc_sar1_flag)
		{
			adc_sar1_flag = 0;
			filter_adc();
		}
		
		//DelSig ADC results ready to be filtered?
		if(adc_delsig_flag)
		{
			adc_delsig_flag = 0;
			strain_filter();
		}
		
		//WatchDog Clock (Safety-CoP)
		toggle_wdclk ^= 1;
		WDCLK_Write(toggle_wdclk);
	}
}
