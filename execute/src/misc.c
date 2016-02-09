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

uint8 i2c_last_request = 0;

//Timers:
volatile uint8 t1_100us_flag = 0;
volatile uint8 t1_time_share = 0, t1_new_value = 0;

//ADC:
uint8 adc_sar1_flag = 0;
volatile uint8 adc_delsig_flag = 0;

//UART:
volatile uint8 data_ready_485_1 = 0;

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

//How long does it take to run X function? Use this code and a scope to find out.
#define SDELAY	5
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
		EXP8_Write(1);
		motor_current_pid(ctrl.current.setpoint_val, ctrl.current.actual_val);
		EXP8_Write(0);
		
		//Motor current PID #2
		EXP8_Write(1);
		motor_current_pid_2(ctrl.current.setpoint_val, ctrl.current.actual_val);
		EXP8_Write(0);
		
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

void init_sine_gen(void)
{
	VDAC8_2_Start();
}

uint16 output_sine(void)
{
	static double angle = 0;
	static double ret = 0;
	uint8 output = 0;
	
	//if(t1_new_value == 1)
	{	
		//t1_new_value = 0;
		
		angle += STEP;
		if(angle >= (2*PI))
			angle = 0;
		ret = sin(angle) + 1;
		
		output = (uint8)(ret*127);
		
		//Output on DAC:
		VDAC8_2_SetValue(output);
		
		CyDelayUs(DELAY);
	}	
	
	return output;
}

uint16 output_arb(void)
{
	static double angle = 0;
	static double ret = 0;
	static uint8 output = 0;
	static int16 i = 0;
	
	i++;
	
	//Slow ramp-up
	if(i < 100)
		output = i;
	
	//Fast ramp-down
	if(i >= 100 && i <= 150)
		output -= 2;
	
	//Castellation
	if(i > 150 && i <= 160)
		output = 255;
	if(i > 160 && i <= 170)
		output = 0;
	if(i > 180 && i <= 190)
		output = 255;
	if(i > 190 && i <= 200)
		output = 0;
	if(i > 200 && i <= 210)
		output = 255;

	if(i > 210)
	{
		angle += STEP;
		if(angle >= (2*PI))
		{
			angle = 0;
			i = 0;
		}
		ret = sin(angle) + 1;		
		output = (uint8)(ret*127);
	}
	
	//Output on DAC:
	VDAC8_2_SetValue(output);	
	
	CyDelayUs(DELAY);
	
	return output;
}

//Current/thermal test. 5A average, 20A pulses
//100ms every second.
uint16 output_step(void)
{
	static int16 i = 0;
	uint16 output = 0;
	
	i++;
	
	//Slow ramp-up
	if(i < 785)
		output = 420;	//1850;

	if(i >= 785 && i <= 7500)
		output = 73;	//287;
	
	if(i > 7500)
	{
		i = 0;
		output = 73;	//287;
	}
	
	//Output on DAC:
	//VDAC8_2_SetValue(output);	
	
	CyDelayUs(DELAY);
	
	return output;
}

//Use this to test the current controller
void test_current_tracking_blocking(void)
{
	init_sine_gen();
	ctrl.active_ctrl = CTRL_CURRENT;
	ctrl.current.gain.I_KP = 30;
	ctrl.current.gain.I_KI = 25;
	Coast_Brake_Write(1);	//Brake
	
	uint16 val = 0;
	while(1)
	{
		//val = output_sine();
		//val = output_arb();		
		//ctrl.current.setpoint_val = val*2 + 125;
		
		//RGB LED = Hall code:
		LED_R_Write(H1_Read());
		LED_G_Write(H2_Read());
		LED_B_Write(H3_Read());
		
		val = output_step();
		ctrl.current.setpoint_val = val;
	}
}

//Use this to send PWM pulses in open speed mode
void test_pwm_pulse_blocking(void)
{
	uint16 val = 0;
	
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(0);	
	
	while(1)
	{	
		//RGB LED = Hall code:
		LED_R_Write(H1_Read());
		LED_G_Write(H2_Read());
		LED_B_Write(H3_Read());
		
		val = output_step();
		motor_open_speed_1(val);
	}
}

//Associate data with the right structure. We need that because of the way the ISR-based
//I2C works (we always get data from the last request)
void assign_i2c_data(uint8 *newdata)
{
	uint16 tmp = 0;
	
	if(i2c_last_request == I2C_RQ_GYRO)
	{
		//Gyro X:
		tmp = ((uint16)newdata[0] << 8) | ((uint16) newdata[1]);
		imu.gyro.x = (int16)tmp;
		
		//Gyro Y:
		tmp = ((uint16)newdata[2] << 8) | ((uint16) newdata[3]);
		imu.gyro.y = (int16)tmp;
		
		//Gyro Z:
		tmp = ((uint16)newdata[4] << 8) | ((uint16) newdata[5]);
		imu.gyro.z = (int16)tmp;		
	}
	else if(i2c_last_request == I2C_RQ_ACCEL)
	{
		//Accel X:
		tmp = ((uint16)newdata[0] << 8) | ((uint16) newdata[1]);
		imu.accel.x = (int16)tmp;
		
		//Accel Y:
		tmp = ((uint16)newdata[2] << 8) | ((uint16) newdata[3]);
		imu.accel.y = (int16)tmp;
		
		//Accel Z:
		tmp = ((uint16)newdata[4] << 8) | ((uint16) newdata[5]);
		imu.accel.z = (int16)tmp;		
	}
	else if(i2c_last_request == I2C_RQ_SAFETY)
	{
		safety_cop.status1 = newdata[0];
		safety_cop.status2 = newdata[1];
	}
}

//CSEA Knee will go up and down. Trajectory calculated by Trapez, feeding a position PI.
#define CSEA_UP 		72000
#define CSEA_DOWN 		11500
#define MARGIN			375
#define SPD_UP			7000000
#define ACC_UP			4000000
#define SPD_DOWN		7000000
#define ACC_DOWN		4500000
#define TICK_TO_ANGLE	672
#define FF_GAIN			10
void csea_knee_up_down_test_demo(void)
{
	unsigned int state = 0;
	unsigned int traj_calculated = 0, steps = 0;
	int low = 0, up = 0;
	volatile int32 ff = 0;
	volatile double angle = 0.0, force = 0.0;
	volatile int32 force_int = 0, sign = 1;
	int32 wait_cycles = 0;
	int32 first = 1;
	
	ctrl.active_ctrl = CTRL_POSITION;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(0);
	
	//Position PID gains:
	ctrl.position.gain.P_KP = 22;
	ctrl.position.gain.P_KI = 5;
	
	//Starts off:
	LED_R_Write(1);
	LED_G_Write(1);
	LED_B_Write(1);
	
	while(1)
	{		
		//Refresh encoder data:
		encoder.count_last = encoder.count;	
		encoder.count = QuadDec_1_GetCounter();
		encoder.count_dif = encoder.count - encoder.count_last;
		
		ctrl.position.setp = trapez_get_pos(steps);	//New setpoint
		ctrl.position.pos = encoder.count;			//Current pos
		
		//PID:
		//motor_position_pid(ctrl.position.setp, ctrl.position.pos);
		
		//PID + Feed Forward:
		angle = (double)(((encoder.count - CSEA_DOWN)) / TICK_TO_ANGLE);
		force = 100*sin((angle*3.14)/180);
		force_int = (int32)force;
		ff = -sign*(force_int * FF_GAIN)/10;
		
		if(!first)
			motor_position_pid_ff_1(ctrl.position.setp, ctrl.position.pos, ff);

		//motor_position_pid_ff_1(ctrl.position.pos, ctrl.position.pos, ff);	//Test only
		
		//At power-up the knee is low:
		low = encoder.count;
		
		//There are 4 possible states:
		switch(state)
		{
			case 0:		//Knee is low, not moving
			
				if(!traj_calculated)
				{
					
					traj_calculated = 1;
					wait_cycles = 70;
					
					//CyDelay(250);
				}
				else
				{			
					wait_cycles--;
					if(wait_cycles <= 0)
					{
						state = 1;
						//Compute a trajectory that will bring the knee up:					
						steps = trapez_gen_motion_1(low, CSEA_UP, SPD_UP, ACC_UP);			
						ctrl.position.gain.P_KP = 22;
						ctrl.position.gain.P_KI = 5;
						first = 0;
					}
				}
			
				break;
			
			case 1: 	//Knee is rising
				
				sign = 1;	//FF
				
				if((encoder.count > (CSEA_UP - MARGIN)) && (encoder.count < (CSEA_UP + MARGIN)))
				{
					//We have reached our target, we can go to the next step
					traj_calculated = 0;
					up = encoder.count;
					state = 2;
				}
				
				LED_R_Write(1);
				LED_G_Write(0);
				
				break;
			
			case 2: 	//Knee is high, not moving
				
				if(!traj_calculated)
				{
					traj_calculated = 1;
					wait_cycles = 70;
					
					//CyDelay(250);
				}	
				else
				{			
					wait_cycles--;
					if(wait_cycles <= 0)
					{
						state = 3;
						//Compute a trajectory that will bring the knee up:
						steps = trapez_gen_motion_1(up, CSEA_DOWN, SPD_DOWN, ACC_DOWN);	
						ctrl.position.gain.P_KP = 5;
						ctrl.position.gain.P_KI = 7;
					}
				}
				
				break;
			
			case 3:		//Knee is lowering
				
				sign = 1;	//FF
				
				if((encoder.count > (CSEA_DOWN - MARGIN)) && (encoder.count < (CSEA_DOWN + MARGIN)))
				{
					//We have reached our target, we can go to the next step
					traj_calculated = 0;
					low = encoder.count;
					state = 0;
				}		
				
				LED_R_Write(0);
				LED_G_Write(1);
				
				break;
			
			default:
				break;
		}
		
		//Loop delay (otherwise we don't get a good difference)
		CyDelay(10);
	}
}

//AS4047 Test code:
//=================

uint16 spidata_mosi[WORDS_IN_FRAME] = {0,0,0,0,0,0,0};
uint16 spidata_miso[WORDS_IN_FRAME] = {0,0,0,0,0,0,0};
uint16 spidata_mosi2[WORDS_IN_FRAME];
uint8 spistatus = 0;
uint16 angleunc = 0;

void init_as5047(void)
{
	//Init SPIM module:
    SPIM_1_Start();
}

void as5047_test_code_blocking(void)
{
    uint8 i = 0;
   
    //Init SPIM module:
    SPIM_1_Start();
    CyDelay(10);   
	
    //Build the mosi packet:
    spidata_mosi[0] = add_even_parity_msb(AS5047_READ | AS5047_REG_ERRFL);
    spidata_mosi[1] = add_even_parity_msb(AS5047_READ | AS5047_REG_PROG);
    spidata_mosi[2] = add_even_parity_msb(AS5047_READ | AS5047_REG_DIAAGC);
    spidata_mosi[3] = add_even_parity_msb(AS5047_READ | AS5047_REG_MAG);
    spidata_mosi[4] = add_even_parity_msb(AS5047_READ | AS5047_REG_ANGLEUNC);
    spidata_mosi[5] = add_even_parity_msb(AS5047_READ | AS5047_REG_ANGLECOM);
    spidata_mosi[6] = add_even_parity_msb(AS5047_READ | AS5047_REG_NOP);
    
    while(1)
    {
		/*
		SPIM_1_ClearTxBuffer();
		SPIM_1_ClearRxBuffer();
        CyDelay(1);
       
        for(i = 0; i < WORDS_IN_FRAME ; i++)
        {
			spidata_mosi2[0] = spidata_mosi[i];
			SPIM_1_PutArray(spidata_mosi2, 1);
			
			CyDelayUs(15);
            spidata_miso[i] = SPIM_1_ReadRxData();
        }
        CyDelay(4);
       
        //Notes: delays only present for early debugging. Minimize/remove.
       
        //We could commutate the motor here.
		*/
		
		angleunc = as5047_read_single(AS5047_REG_ANGLEUNC);
    }
}

//Read a single word
uint16 as5047_read_single(uint16 reg)
{
	//Clear buffers to start in a known state:
	SPIM_1_ClearTxBuffer();
	SPIM_1_ClearRxBuffer();
    CyDelayUs(10);

	//Send 1st byte (reg addr)
	spidata_mosi2[0] = add_even_parity_msb(AS5047_READ | reg);
	SPIM_1_PutArray(spidata_mosi2, 1);	
	CyDelayUs(10);
    spidata_miso[0] = SPIM_1_ReadRxData();
	
	//Send 2nd byte (empty, used to read)
	spidata_mosi2[0] = add_even_parity_msb(AS5047_READ | AS5047_REG_NOP);
	SPIM_1_PutArray(spidata_mosi2, 1);	
	CyDelayUs(10);
    spidata_miso[1] = SPIM_1_ReadRxData();	
	
	//spidata_miso[1] contains the answer. Remove parity and return value
	//ToDo: ignore word if wrong parity

	last_as5047_word = (spidata_miso[1] & 0x3FFF);
	return last_as5047_word;
}

uint16 add_even_parity_msb(uint16 word)
{
	uint16 ret = 0;
	
	//__builtin_parity() returns 0 for even, 1 for odd
	// MSB = 1 when it's odd
	if(__builtin_parity((int)word))
	{
		ret = (word | PARITY_1);
	}
	else
	{
		ret = (word & PARITY_0);
	}
	
	return ret;
}

//****************************************************************************
// Private Function(s)
//****************************************************************************
