//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 09/2015
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

//Timers:
volatile uint8 t1_100us_flag = 0;
volatile uint8 t1_time_share = 0, t1_new_value = 0;

//ADC:
uint8 adc_sar1_flag = 0;
volatile uint8 adc_delsig_flag = 0;

//UART:
volatile uint8 data_ready_485 = 0;

//USB:
volatile uint8 data_ready_usb = 0;

//AS5047 Magnetic Encoder:
uint16 last_as5047_word = 0;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************


//****************************************************************************
// Public Function(s)
//****************************************************************************

//Call this function in the 1kHz FSM. It will return 1 every second.
uint8 timebase_1s(void)
{
	static uint16 time = 0;
	
	time++;
	if(time >= 999)
	{
		time = 0;
		return 1;
	}
	
	return 0;
}

void test_code_blocking(void)
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//Blocking Test code - enable one and only one for special 
	//debugging. Normal code WILL NOT EXECUTE when this is enabled!
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//strain_test_blocking();
	//safety_cop_comm_test_blocking();
	//imu_test_code_blocking();
	//motor_fixed_pwm_test_code_blocking(200);
	//wdclk_test_blocking();
	//timing_test_blocking();
	//test_current_tracking_blocking();
	//test_pwm_pulse_blocking();
	//test_uart_dma_xmit();
	//motor_cancel_damping_test_code_blocking();
	//csea_knee_up_down_test_demo();
	//motor_stepper_test_blocking_1(80);
	//test_pwro_output_blocking();
	//strain_amp_6ch_test_code_blocking();
	//as5047_test_code_blocking();
	//as5048b_test_code_blocking();
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=	
}

void test_code_non_blocking(void)
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Non-Blocking Test code
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	#ifdef USE_SPI_COMMUT		
	motor_stepper_test_init(0);
	//Note: deadtime is 55, small PWM values won't make it move.
	//Starting at 0, GUI will change that when it wants.	
	#endif	//USE_SPI_COMMUT	
	//motor_fixed_pwm_test_code_non_blocking(125);
	//pwro_output(245);	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=		
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//****************************************************************************
// Test Function(s) - Use with care!
//****************************************************************************

//****************************************************************************
// Deprecated Function(s)
//****************************************************************************

//Important: this code relies on external pins that are mapped to other functions!
//rewrite or delete

//How long does it take to run X function? Use this code and a scope to find out.
void timing_test_blocking(void)
{
	//Disable Global Interrupts
    CyGlobalIntDisable; 
	
	while(1)
	{
		//Synch sequence
		/*
		EXP9_Write(1);
		EXP8_Write(0);
		EXP8_Write(1);
		EXP8_Write(0);
		EXP8_Write(1);
		EXP8_Write(0);
		*/
		
		CyDelayUs(SDELAY);
		
		//Motor current PID
		//EXP8_Write(1);
		motor_current_pid(ctrl.current.setpoint_val, ctrl.current.actual_val);
		//EXP8_Write(0);
		
		//Motor current PID #2
		//EXP8_Write(1);
		motor_current_pid_2(ctrl.current.setpoint_val, ctrl.current.actual_val);
		//EXP8_Write(0);
		
		//Exit sequence:
		//EXP9_Write(0);
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
