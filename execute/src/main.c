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
#include "cyapicallbacks.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

//****************************************************************************
// Variable(s)
//****************************************************************************

//Misc. variables, used for debugging only
uint8 last_byte = 0;
int steps = 0, current_step = 0;
uint8_t tmp_rx_command_485[PAYLOAD_BUF_LEN];
uint8_t tmp_rx_command_usb[PAYLOAD_BUF_LEN];
uint8 eL0 = 0, eL1 = 0, eL2 = 0;
uint16 angle = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Local variables:
	uint8 i = 0;
	uint8 minm_i2c = 0;
	unsigned char result = 0;
	uint8 toggle_wdclk = 0;	
	uint8 cmd_ready_485 = 0, cmd_ready_usb = 0;
	static uint8 new_cmd_led = 0;
	uint16 safety_delay = 0;
	uint8 i2c_time_share = 0;
	
	//Power on delay with LEDs
	power_on();	     

	//Initialize all the peripherals
	init_peripherals();
	
	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();
	
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
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Project specific initialization code
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	
	//ExoBoots:
	#if(ACTIVE_PROJECT == PROJECT_EXOCUTE)
	init_exo();
	#endif	//PROJECT_EXOCUTE
	
	//MIT CSEA Knee:
	#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)
	init_csea_knee();
	#endif	//PROJECT_CSEA_KNEE
	
	//RIC/NU Knee:
	#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)
	init_ricnu_knee();
	#endif	//PROJECT_RICNU_KNEE
	
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
				//Case 0: I2C_0
				case 0:
					i2c_time_share++;
					i2c_time_share %= 4;
				
					#ifdef USE_I2C_0 
				
					//Subdivided in 4 slots (250Hz)
					switch(i2c_time_share)
					{
						//Case 0.0: Accelerometer
						case 0:
						
							#ifdef USE_IMU							
							get_accel_xyz();
							i2c_last_request = I2C_RQ_ACCEL;
							#endif 	//USE_IMU
						
							break;
						
						//Case 0.1: Gyroscope
						case 1:
							
							#ifdef USE_IMU							
							get_gyro_xyz();		
							i2c_last_request = I2C_RQ_GYRO;
							#endif 	//USE_IMU
							
							break;
						
						//Case 0.2: AS5048B position sensor
						case 2:
							#ifdef USE_AS5048B
							get_as5048b_position();
							i2c_last_request = I2C_RQ_AS5048B;		
							#endif //USE_AS5048B
							break;
						
						//Case 0.3: MinM RGB LED & external strain amplifier
						case 3:
							
							//I2C RGB LED
							#ifdef USE_MINM_RGB
							//minm_test_code();	
							minm_i2c = update_minm_rgb();
							#else
							minm_i2c = 0;	
							#endif 	//USE_MINM_RGB
							
							//External strain gauge amplifier
							#ifdef USE_EXT_I2C_STRAIN
							if(!minm_i2c)
							{
								//If the MinM was refreshed we skip one measurement.
								get_6ch_strain();
								i2c_last_request = I2C_RQ_EXT_STRAIN;
							}
							#endif //USE_EXT_I2C_STRAIN
							
							break;
						
						default:
							break;
					}
					
					#endif //USE_I2C_INT
								
					break;
				
				//Case 1: I2C_1
				case 1:
					
					//Read from Safety Co-Processor
					#ifdef USE_I2C_1
						
					safety_cop_read_all();
					
					#endif 	//USE_I2C_1
					
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
					
					//Display temperature status on RGB	
					overtemp_error(&eL1, &eL2);					//Comment this line if safety code is problematic
					rgb_led_ui(eL0, eL1, eL2, new_cmd_led);		//ToDo add more error codes
					if(new_cmd_led)
					{
						new_cmd_led = 0;
					}
					
					break;
				
				//Case 5: Position sensors & Position setpoint
				case 5:
					
					//Read AS5047 sensor (only if it's not already read by USE_SPI_COMMUT)
					#ifndef USE_SPI_COMMUT
						#ifdef USE_AS5047						
						as5047.angle = as5047_read_single(AS5047_REG_ANGLEUNC);
						#endif	//USE_AS5047
					#endif	//USE_SPI_COMMUT
					
					//Refresh encoder readings (ENC_CONTROL only)
					refresh_enc_control();
					
					#ifdef USE_TRAPEZ	
				
					//Trapezoidal trajectories (can be used for both Position & Impedance)	
					if((ctrl.active_ctrl == CTRL_POSITION) || (ctrl.active_ctrl == CTRL_IMPEDANCE))
					{									
						ctrl.position.setp = trapez_get_pos(steps);	//New setpoint
						ctrl.impedance.setpoint_val = trapez_get_pos(steps);	//New setpoint
					}
					
					#endif	//USE_TRAPEZ	
			
					break;
				
				//Case 6: P & Z controllers, 0 PWM	
				case 6:
					
					#ifdef USE_TRAPEZ	
					
					if(ctrl.active_ctrl == CTRL_POSITION)
					{
						motor_position_pid(ctrl.position.setp, ctrl.position.pos);
					}
					else if(ctrl.active_ctrl == CTRL_IMPEDANCE)
					{
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
					
					//...
					
					break;
				
				//Case 8: SAR ADC filtering
				case 8:

					filter_sar_adc();
					
					break;
				
				//Case 9: User functions	
				case 9:
					
					//ExoBoot code - 1kHz
					#if(ACTIVE_PROJECT == PROJECT_EXOCUTE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
					exo_fsm();							
					#endif	//PROJECT_EXOCUTE
					
					//CSEA Knee code - 1kHz
					#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
					csea_knee_fsm();						
					#endif	//PROJECT_CSEA_KNEE
					
					//RIC/NU Knee code - 1kHz
					#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
					ricnu_knee_fsm();						
					#endif	//PROJECT_RICNU_KNEE
					
					//1s timebase:
					if(timebase_1s())
					{
						//Insert code that needs to run every second here
						//...
					}
					
					break;
				
				default:
					break;
			}
			
			//The code below is executed every 100us, after the previous slot. 
			//Keep it short!
			
			
			//BEGIN - 10kHz Refresh
			
			//RS-485 Byte Input
			#ifdef USE_RS485			
		
			//get_uart_data();	//Now done via DMA
			
			if(data_ready_485)
			{
				data_ready_485 = 0;
				//Got new data in, try to decode
				cmd_ready_485 = unpack_payload_485();
			}
				
			#endif	//USE_RS485
			
			//USB Byte Input
			#ifdef USE_USB			
		
			get_usb_data();
			
			if(data_ready_usb)
			{
				data_ready_usb = 0;
				//Got new data in, try to decode
				cmd_ready_usb = unpack_payload_usb();
				
				eL1 = 1;
			}

			#endif	//USE_USB
			
			//FlexSEA Network Communication
			#ifdef USE_COMM
				
			//Valid communication from RS-485?
			if(cmd_ready_485 != 0)
			{
				cmd_ready_485 = 0;
				
				//Cheap trick to get first line	//ToDo: support more than 1
				for(i = 0; i < PAYLOAD_BUF_LEN; i++)
				{
					tmp_rx_command_485[i] = rx_command_485[0][i];
				}
				
				//payload_parse_str() calls the functions (if valid)
				result = payload_parse_str(tmp_rx_command_485);
				
				//LED:
				if(result == PARSE_SUCCESSFUL)
				{
					//Green LED only if the ID matched and the command was known
					new_cmd_led = 1;
				}
				
				//Test ToDo remove
				CyDmaClearPendingDrq(DMA_3_Chan);
			}
			
			//Time to reply - RS-485?
			if(reply_ready_flag)
			{
				//We never replied in the same time slot:
				if(t1_time_share != reply_ready_timestamp)
				{
					rs485_puts(reply_ready_buf, reply_ready_len);	
				
					reply_ready_flag = 0;
				}
				
			}

			//Valid communication from USB?
			if(cmd_ready_usb != 0)
			{
				cmd_ready_usb = 0;
				
				//Cheap trick to get first line	//ToDo: support more than 1
				for(i = 0; i < PAYLOAD_BUF_LEN; i++)
				{
					tmp_rx_command_usb[i] = rx_command_usb[0][i];
				}
				
				//payload_parse_str() calls the functions (if valid)
				result = payload_parse_str(tmp_rx_command_usb);
				
				//LED:
				if(result == PARSE_SUCCESSFUL)
				{
					//Green LED only if the ID matched and the command was known
					new_cmd_led = 1;
				}
			}
			
			#endif	//USE_COMM
			
			#ifdef USE_SPI_COMMUT
			
				#if(ENC_COMMUT == ENC_AS5047)
					sensor_commut_1();
				#endif //ENC_AS5047
				
            #endif
			
		}
		else
		{
			//Asynchronous code goes here.
			
			//WatchDog Clock (Safety-CoP)
			toggle_wdclk ^= 1;
			WDCLK_Write(toggle_wdclk);
		}
	}
}
