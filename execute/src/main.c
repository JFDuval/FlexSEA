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
// Variable(s)
//****************************************************************************

//Misc. variables, used for debugging only
uint8 last_byte = 0;
int steps = 0, current_step = 0;
uint8_t tmp_rx_command_485_1[PAYLOAD_BUF_LEN];
uint8 eL0 = 0, eL1 = 0, eL2 = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Local variables:
	int16 comm_res = 0, comm_success = 0;
	uint8 last_byte = 0, uart_buf_size = 0;
	uint8 i = 0;
	unsigned char result = 0;
	unsigned char comm_str_payload1[16];
	unsigned char ledr_state = 0, ledg_state = 0, ledb_state = 0;
	uint8 toggle_wdclk = 0;	
	uint8 cmd_ready_485_1 = 0, cmd_ready_usb = 0;
	static uint8 new_cmd_led = 0;
	uint8 div2 = 0;
	uint16 safety_delay = 0;
	uint8 i2c_time_share = 0;
	
	//Power on delay with LEDs
	power_on();	     

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
	//motor_fixed_pwm_test_code_blocking(85);
	//wdclk_test_blocking();
	//timing_test_blocking();
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	//Main loop
	while(1)
	{
		if(t1_new_value == 1)
		{
			//If the time share slot changed we run the timing FSM. Refer to
			//timing.xlsx for more details. 't1_new_value' updates at 10kHz,
			//each slot at 1kHz.
			
			t1_new_value = 0;
			
			//Timing FSM:
			switch(t1_time_share)
			{
				//Case 0: I2C
				case 0:
					i2c_time_share++;
					i2c_time_share %= 4;
				
					#ifdef USE_I2C_INT
				
					//Subdivided in 4 slots.
					switch(i2c_time_share)
					{
						//Case 0.0: Accelerometer
						case 0:
						
							#ifdef USE_IMU							
							//get_accel_xyz();
							//imu_last_request = IMU_RQ_ACCEL;
							#endif 	//USE_IMU
						
							break;
						
						//Case 0.1: Gyroscope
						case 1:
							
							#ifdef USE_IMU							
							get_gyro_xyz();		
							imu_last_request = IMU_RQ_GYRO;
							#endif 	//USE_IMU
							
							break;
						
						//Case 0.2: Safety-Cop
						case 2:
							
							//safety_cop_get_status();
							
							break;
						
						//Case 0.3: Free
						case 3:
							break;
						
						default:
							break;
					}
					
					#endif //USE_I2C_INT
				
					break;
				
				//Case 1:	
				case 1:
					break;
				
				//Case 2:	
				case 2:
					break;
				
				//Case 3: Strain Gauge DelSig ADC, SAR ADC
				case 3:
					
					//Start a new conversion
					ADC_DelSig_1_StartConvert();
					
					//Filter the previous results
					strain_filter_dma();
					
					
					
					break;
				
				//Case 4: User Interface	
				case 4:
					
					//Alive LED
					alive_led();
					
					//UI RGB LED:
					
					if(safety_delay > SAFETY_DELAY)
					{
						//status_error_codes(safety_cop.status1, safety_cop.status2, &eL0, &eL1, &eL2); 
					}
					else
					{
						safety_delay++;
					}
					
					rgb_led_ui(eL0, eL1, eL2, new_cmd_led);	//ToDo add error codes
					if(new_cmd_led)
					{
						new_cmd_led = 0;
					}
					
					break;
				
				//Case 5: Quadrature encoder
				case 5:
					
					#ifdef USE_QEI1
				
					//Refresh encoder readings
					encoder_read();
						
					#endif	//USE_QEI1		
			
					break;
				
				//Case 6: P & Z controllers, 0 PWM	
				case 6:
					
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
					
					//If no controller is used the PWM should be 0:
					if(ctrl.active_ctrl == CTRL_NONE)
					{
						motor_open_speed_1(0);
					}
					
					break;
				
				case 7:
					break;
				
				//Case 8: SAR ADC filtering
				case 8:

					filter_sar_adc();
					
					break;
				
				case 9:
					break;
				
				default:
					break;
			}
			
			//The code below is executed every 100us, after the previous slot. 
			//Keep it short!
			
			//BEGIN - 10kHz Refresh
			
			//RS-485 Byte Input
			#ifdef USE_RS485			
		
			get_uart_data();
			
			if(data_ready_485_1)
			{
				data_ready_485_1 = 0;
				//Got new data in, try to decode
				cmd_ready_485_1 = unpack_payload_485_1();
			}
				
			#endif	//USE_RS485
			
			//FlexSEA Network Communication
			#ifdef USE_COMM
				
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
				if(result == PARSE_SUCCESSFUL)
				{
					//Green LED only if the ID matched and the command was known
					new_cmd_led = 1;
				}
			}
			
			//Valid communication from USB?
			if(cmd_ready_usb != 0)
			{
				//ToDo
			}
			
			#endif	//USE_COMM	
			
			//END - 10kHz Refresh
		}
		else
		{
			//Asynchronous code goes here.
			
			//WatchDog Clock (Safety-CoP)
			toggle_wdclk ^= 1;
			WDCLK_Write(toggle_wdclk);
		}
	}
	
	//Main loop - Legacy - ToDo remove eventually
	while(1)
	{
		
		/* Temporarily removing the 10 & 50ms timbases. Their code isn't used for now anyway
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
		*/
				
		#ifdef USE_USB
			
		//USB Data
		if(usb_echo_blocking())
		{
			//Got new data in 
			//Try to decode
			cmd_ready_485_1 = unpack_payload_usb();
			if(comm_res)
				comm_success = 1;

			//Toggle LEDR with new commands
			ledr_state ^= 1;
			LED_R_Write(ledr_state);
		}
			
		#endif	//USE_USB

	}
}

volatile uint8 uart_tmp_buf[RX_BUF_LEN];
void get_uart_data(void)
{
	uint32 uart_buf_size = 0, i = 0;
	uint16 tmp = 0, status = 0;
	
	uart_buf_size = UART_2_GetRxBufferSize();
	if(uart_buf_size > 0)
	{
		for(i = 0; i < uart_buf_size; i++)
		{
			//It's a shame but there is no gets function
			//uart_tmp_buf[i] = UART_2_GetChar();	//Get as many bytes as possible...
			tmp = UART_2_GetByte() & 0xFF;
			uart_tmp_buf[i] = (uint8)tmp;
			
			/*status = (tmp & 0xFF00)>>8;
			if(!status)
				uart_tmp_buf[i] = (uint8)tmp;
			else
				break;
			*/
		}
		
		//...then mass update rx_buf:
		update_rx_buf_array_485_1(uart_tmp_buf, uart_buf_size+1);
		
		data_ready_485_1++;
	}		
}
