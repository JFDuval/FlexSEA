//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// motor: motor control functions
//****************************************************************************

//Note: Any control function that's not open loop is in control.c/h
//		This file only has open loop controllers (PWM, pulse, etc)

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "motor.h"
#include "analog.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//Initializes all the variable
void init_motor(void)
{
	//PWM1: BLDC
	PWM_1_Start();
	PWM_1_WriteCompare1(0);			//Start at 0%
	PWM_1_WriteCompare2(PWM2DC(0));	
	
	//Default is Brake mode:
	Coast_Brake_Write(1);
	
	//ADC2: Motor current
	ADC_SAR_2_Start();
	adc_sar2_dma_config();
	isr_sar2_dma_Start();
	
	//VDAC8: OpAmp VREF
	VDAC8_1_Start();
	
	//Analog amplifiers & multiplexer(s):
	Opamp_1_Start();
	
	//Quadrature 1: Motor shaft encoder
	#ifdef USE_QEI
	init_qei();
	#endif	//USE_QEI
	
	//When using Brushed, fixed Hall code:
	#if(MOTOR_TYPE == MOTOR_BRUSHED)
	Use_Hall_Write(HALL_VIRTUAL);
	Virtual_Hall_Write(0b110); 
	#endif	//MOTOR_TYPE == MOTOR_BRUSHED
}

//Controls motor PWM duty cycle
//Sign of 'pwm_duty' determines rotation direction
void motor_open_speed_1(int16 pwm_duty)
{
	int16 pdc = 0;
	uint16 tmp = 0;
	
	//Clip PWM to valid range
	if(pwm_duty >= MAX_PWM)
		pdc = MAX_PWM;
	else if(pwm_duty <= MIN_PWM)
		pdc = MIN_PWM;
	else
		pdc = pwm_duty;
	
	//User defined sign:
	pdc = pdc * PWM_SIGN;
	
	//Save value to structure:
	ctrl.pwm = pdc;
	
	//Change direction according to sign
	if(pdc < 0)
	{
		pdc = -pdc;	//Make it positive
		MotorDirection_Write(0);
		in_control.mot_dir = 0;
	}
	else
	{
		MotorDirection_Write(1);
		in_control.mot_dir = 1;
	}
	
	//Write duty cycle to PWM module
	tmp = PWM1DC((uint16)pdc);
	PWM_1_WriteCompare1(tmp);
	PWM_1_WriteCompare2(PWM2DC(tmp));	//Can't be 0 or the ADC won't trigger
	in_control.pwm = pdc;
}

//Controls motor PWM duty cycle
//Manual sign (-1 or 1, everything else will set the PWM at 0)
void motor_open_speed_2(int16 pwm_duty, int sign)
{
	int16 pdc = 0;
	
	//Clip PWM to valid range (0 - Maximum)
	if(pwm_duty >= MAX_PWM)
		pdc = MAX_PWM;
	else if(pwm_duty <= 0)
		pdc = 0;
	else
		pdc = pwm_duty;
	
	//User defined sign:
	sign = sign * PWM_SIGN;
	
	//Change direction according to sign
	if(sign == -1)
	{
		MotorDirection_Write(0);
		in_control.mot_dir = 0;
	}
	else if(sign == 1)
	{
		MotorDirection_Write(1);
		in_control.mot_dir = 0;
	}
	else
	{
		//Invalid sign, forces PWM to 0
		pdc = 0;
	}
	
	//Write duty cycle to PWM module
	pdc = PWM1DC(pdc);
	PWM_1_WriteCompare1(pdc);
	PWM_1_WriteCompare2(PWM2DC(pdc));	//Can't be 0 or the ADC won't trigger
	in_control.pwm = pdc;
}

//****************************************************************************
// Test Function(s) - Use with care!
//****************************************************************************

//Sends a constant PWM. Blocking.
void motor_fixed_pwm_test_code_blocking(int spd)
{
	uint8 toggle_wdclk = 0;	
	
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(spd);
	
	while(1)
	{	
		LED_R_Write(EX1_Read());
		LED_G_Write(EX2_Read());
		LED_B_Write(EX3_Read());
		
		//WatchDog Clock (Safety-CoP)
		toggle_wdclk ^= 1;
		WDCLK_Write(toggle_wdclk);
		
		refresh_enc_control();
	}
}

//Sends a constant PWM. Non-Blocking.
void motor_fixed_pwm_test_code_non_blocking(int spd)
{
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(spd);	
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
		LED_R_Write(EX1_Read());
		LED_G_Write(EX2_Read());
		LED_B_Write(EX3_Read());
		
		val = output_step();
		motor_open_speed_1(val);
	}
}

//****************************************************************************
// Deprecated Function(s)
//****************************************************************************

//Second version of the serial interface, now with sign
//'x' clears the encoder count
__attribute__((deprecated)) int8 serial_motor_speed(int8 letter)
{
	static int8 step = 0;
	
	//'x' clears the encoder count
	if(letter == 'x')
	{
		QuadDec_1_SetCounter(0);
	}
	
	//Increase with s
	if(letter == 's')
		step++;
	if(letter == 'd')
		step--;

	//Step to do
	if(step >= 16)
		step = 0;		
	if(step <= -16)
		step = 0;

	//Set duty cycle
	motor_open_speed_1(200*step);
	
	//Return value to be displayed
	return(step + '0');
}
