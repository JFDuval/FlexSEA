//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// motor: motor control functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "motor.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Main data structure for all the controllers:
struct ctrl_s ctrl;

//Variables
int sumoferrors = 0;
int error = 0;
int pwm = 0;
int setpoint = 10000;

//Global motor control variables
int16 old_enc_count = 0;
//int16 new_enc_count = 0;
int16 diff_enc_count = 0;
uint8 motor_control_flag = 0;

//Current controller:
int current_pid_setpoint = 0, current_pid_measured = CURRENT_ZERO;

int debug_var = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

extern int steps, current_step, pos;
extern unsigned int adc1_res_filtered[ADC1_CHANNELS];

//****************************************************************************
// Function(s)
//****************************************************************************

//Controls motor PWM duty cycle
//Sign of 'pwm_duty' determines rotation direction
void motor_open_speed_1(int16 pwm_duty)
{
	int16 pdc = 0;
	
	//Clip PWM to valid range
	if(pwm_duty >= MAX_PWM)
		pdc = MAX_PWM;
	else if(pwm_duty <= MIN_PWM)
		pdc = MIN_PWM;
	else
		pdc = pwm_duty;
	
	//Change direction according to sign
	if(pdc < 0)
	{
		pdc = -pdc;	//Make it positive
		Control_Reg_1_Write(0);
	}
	else
	{
		Control_Reg_1_Write(1);
	}
	
	//Write duty cycle to PWM module
	PWM_1_WriteCompare(pdc);
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
	
	//Change direction according to sign
	if(sign == -1)
	{
		Control_Reg_1_Write(0);
	}
	else if(sign == 1)
	{
		Control_Reg_1_Write(1);
	}
	else
	{
		//Invalid sign, forces PWM to 0
		pdc = 0;
	}
	
	//Write duty cycle to PWM module
	PWM_1_WriteCompare(pdc);
}

//Second version of the serial interface, now with sign
//'x' clears the encoder count
int8 serial_motor_speed(int8 letter)
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

//Hold current motor position - non blocking
int motor_position_pi_encoder(int wanted_pos, int new_enc_count)
{
	int p = 0, i = 0;

	error = new_enc_count - wanted_pos;		//Actual error
	sumoferrors = sumoferrors + error;		//Cumulative error
	
	//Saturate cumulative error
	if(sumoferrors >= MAX_CUMULATIVE_ERROR)
		sumoferrors = MAX_CUMULATIVE_ERROR;
	if(sumoferrors <= -MAX_CUMULATIVE_ERROR)
		sumoferrors = -MAX_CUMULATIVE_ERROR;
	
	//Proportional term
	p = ctrl.gains.position.kp * error;
	//Integral term
	i = (ctrl.gains.position.kp * sumoferrors)/100;
	
	//Output
	pwm = -(p + i);		//
	
	//Saturates PWM to low values
	if(pwm >= POS_PWM_LIMIT)
		pwm = POS_PWM_LIMIT;
	if(pwm <= -POS_PWM_LIMIT)
		pwm = -POS_PWM_LIMIT;
	
	motor_open_speed_1(pwm);
	
	return error;
}

//Copy from motor_position_pi_encoder()
//Modified for analog absolute encoder
int motor_position_pi_analog(int wanted_pos, int analog_pos)
{
	int p = 0, i = 0;
	
	error = analog_pos - wanted_pos;		//Actual error
	sumoferrors = sumoferrors + error;		//Cumulative error
	
	//Saturate cumulative error
	if(sumoferrors >= MAX_CUMULATIVE_ERROR)
		sumoferrors = MAX_CUMULATIVE_ERROR;
	if(sumoferrors <= -MAX_CUMULATIVE_ERROR)
		sumoferrors = -MAX_CUMULATIVE_ERROR;
	
	//Proportional term
	p = (int) ctrl.gains.position.kp * error;
	//Integral term
	i = (int)(ctrl.gains.position.ki * sumoferrors)/100;
	
	//Output
	pwm = -(p + i);		//
	
	//Saturates PWM to low values
	if(pwm >= POS_PWM_LIMIT)
		pwm = POS_PWM_LIMIT;
	if(pwm <= -POS_PWM_LIMIT)
		pwm = -POS_PWM_LIMIT;
	
	motor_open_speed_1(pwm);
	
	return error;
}

//Legacy code - shouldn't be used. Use trapez instead.

//Ramps from old setpoint to new setpoint
//Set Reset = 1 the first time you change the setpoint
int16 int_wpos(int16 old_wpos, int16 new_wpos, uint8 reset)
{
	static int16 diff = 0, int_wpos = 0;
	
	if(reset)
	{
		//Starts at the old value
		int_wpos = old_wpos;
		return int_wpos;
	}
	else
	{
		if(new_wpos > old_wpos)
		{
			//We are bringing the knee down
			if(int_wpos < new_wpos)
				int_wpos++;
			else
				int_wpos = new_wpos;
		}
		else if(new_wpos < old_wpos)
		{
			//We are bringing the knee up
			if(int_wpos > new_wpos)
				int_wpos--;
			else
				int_wpos = new_wpos;
		}
	}
	
	return int_wpos;
}

//Make sure that limit 2 is higher than limit 1!
#define POS_STEP	10
int16 ramp_demo(int16 limit1, int16 limit2)
{
	static int16 pos = 0, updown = 0;
	
	//First time:
	if(pos < limit1)
		pos = limit1;
	
	if(!updown)
	{
		//Counting up
		pos = pos + POS_STEP;
		LED1_Write(0);
		
		//Flip sign when limit reached
		if(pos >= limit2)
			updown = 1;
	}
	else
	{
		//Counting down
		pos = pos - POS_STEP;
		LED1_Write(1);
		
		//Flip sign when limit reached
		if(pos <= limit1)
			updown = 0;		
	}
	
	return pos;
}

//PI Current controller
//'wanted_curr' is centered at zero and is in the ±CURRENT_SPAN range
//The sign of 'wanted_curr' will change the rotation direction, not the polarity of the current (I have no control on this)
int motor_current_pid_1(int wanted_curr, int measured_curr)
{
	int curr_p = 0, curr_i = 0;
	static int curr_sumoferrors = 0;
	int curr_error = 0;
	int curr_pwm = 0;
	int sign = 0;
	unsigned int uint_wanted_curr = 0;
	int motor_current = 0;
	
	//Clip out of range values
	if(wanted_curr >= CURRENT_POS_LIMIT)
		wanted_curr = CURRENT_POS_LIMIT;
	if(wanted_curr <= CURRENT_NEG_LIMIT)
		wanted_curr = CURRENT_NEG_LIMIT;
	
	//Sign extracted from wanted_curr:
	if(wanted_curr < 0)
	{
		sign = -1;
		uint_wanted_curr = -wanted_curr;
	}
	else
	{
		sign = 1;
		uint_wanted_curr = wanted_curr;
	}
	
	//At this point 'uint_wanted_curr' is always a positive value.
	//This is our setpoint.
	
	//From ADC value to motor current:
	if(measured_curr <= CURRENT_ZERO)
	{
		//We are driving the motor (Q1 or Q3)
		motor_current = CURRENT_ZERO - measured_curr;
	}
	else
	{
		motor_current =  measured_curr - CURRENT_ZERO;
	}
	
	//At this point 'motor_current' is always a positive value.
	//This is our measured value.
	
	//Error and integral of errors:
	curr_error = uint_wanted_curr - motor_current;			//Actual error
	curr_sumoferrors = curr_sumoferrors + curr_error;		//Cumulative error
	
	//Saturate cumulative error
	if(curr_sumoferrors >= MAX_CUMULATIVE_ERROR)
		curr_sumoferrors = MAX_CUMULATIVE_ERROR;
	if(curr_sumoferrors <= -MAX_CUMULATIVE_ERROR)
		curr_sumoferrors = -MAX_CUMULATIVE_ERROR;
	
	//Proportional term
	curr_p = (int) ctrl.gains.current.kp * curr_error;
	//Integral term
	curr_i = (int)(ctrl.gains.current.ki * curr_sumoferrors)/100;
	//Add differential term here if needed
	
	//Output
	curr_pwm = curr_p + curr_i;
	
	//Saturates PWM
	if(curr_pwm >= POS_PWM_LIMIT)
		curr_pwm = POS_PWM_LIMIT;
	if(curr_pwm <= 0)	//Should not happen
		curr_pwm = 0;
	
	//Apply PWM
	motor_open_speed_2(curr_pwm, sign);
	
	return error;
}

//Use this function to change the control strategy
void control_strategy(unsigned char strat)
{
	//By default we place the gains to 0 before we change the strategy:
					
	//"Old" PID (used for pos trapeze)
	ctrl.gains.position.kp = 0;
	ctrl.gains.position.ki = 0;
	ctrl.gains.position.kd = 0;
	//Impedance controller
	ctrl.gains.impedance.k = 0;
	ctrl.gains.impedance.b = 0;
	ctrl.gains.impedance.i = 0;
	//Current controller
	ctrl.gains.current.kp = 0;
	ctrl.gains.current.ki = 0;
	ctrl.gains.current.kd = 0;
	
	//To avoid a huge startup error on the Position-based controllers:
	if(strat == CTRL_POSITION)
	{
		pos = adc1_res_filtered[0];
		steps = trapez_gen_motion_1(pos, pos, 1, 1);
	}
	else if(strat == CTRL_IMPEDANCE)
	{
		pos = QuadDec_1_GetCounter();
		steps = trapez_gen_motion_1(pos, pos, 1, 1);
	}
	
	ctrl.active_ctrl = strat;	//controller = strat;
	
	//The user should call CMD_SET_PID_GAINS at this point.
}

// Impedance controller -- EJ Rouse, 8/11/14
// There will be filter transients for first few iterations -- maybe turn loops off for 100 ms?
// Variables created: stiffness, damping, prev_enc_count, 
int motor_impedance_encoder(int wanted_pos, int new_enc_count)
{
	// Initialize vars
	int i_k = 0, i_b = 0;	
	static long long prev_enc_count = 0, prev_vel1 = 0, prev_vel2 = 0, prev_vel3 = 0;
	static long long prev_filt1 = 0, prev_filt2 = 0, prev_filt3 = 0; 
	long long current_vel = 0, filt_vel = 0, current_val = 0;
	static int enc_t0 = 0, enc_tm1 = 0, enc_tm2 = 0, enc_tm3 = 0, enc_tm4 = 0, enc_tm5 = 0, enc_tm6 = 0, enc_tm7 = 0, enc_tm8 = 0, enc_tm9 = 0;

	error = new_enc_count - wanted_pos;		//Actual error
	
	//Current for stiffness term
	i_k = ctrl.gains.impedance.k * (error >> 12);	//The /50 places the k gain in a good integer range
	
	//Velocity measured on n cycles:
	enc_tm9 = enc_tm8; enc_tm8 = enc_tm7; enc_tm7 = enc_tm6; enc_tm6 = enc_tm5; enc_tm5 = enc_tm4; enc_tm4 = enc_tm3; enc_tm3 = enc_tm2; enc_tm2 = enc_tm1; enc_tm1 = enc_t0;
	enc_t0 = new_enc_count;
	
	//Damping term
	//Difference velocity
	//current_vel = (enc_t0 - enc_tm4);
	//debug_var = current_vel;

 	filt_vel = (57*enc_t0)/220 + (73*enc_tm1)/660 - enc_tm2/264 - (37*enc_tm3)/440 - (43*enc_tm4)/330 - (47*enc_tm5)/330 - (53*enc_tm6)/440 - (17*enc_tm7)/264 + (17*enc_tm8)/660 + (3*enc_tm9)/20; // Derivative method that estimates best fit second order polynomial and calcualtes the derivative numerically for t = 0
 	debug_var = filt_vel;
	
 	i_b = ctrl.gains.impedance.b * (filt_vel >> 5);

	//Output
	current_val = (i_k + i_b);		// Impedance command, motor current in terms of effort (A)
	
	// Changes variables for derivative filtering
	prev_enc_count = new_enc_count;
	prev_vel3 = prev_vel2;
	prev_vel2 = prev_vel1;
	prev_vel1 = current_vel;
	prev_filt3 = prev_filt2;
	prev_filt2 = prev_filt1;
	prev_filt1 = filt_vel;

	current_pid_setpoint = (int)current_val;

	return error;
}

//Initializes all the variable
void init_motor(void)
{
	//No active controller:
	ctrl.active_ctrl = CTRL_NONE;
	
	//No errors:
	ctrl.error = 0;
	ctrl.sumoferrors = 0;
	
	//Generic controller
	ctrl.gains.generic.g0 = 0;
	ctrl.gains.generic.g1 = 0;
	ctrl.gains.generic.g2 = 0;
	ctrl.gains.generic.g3 = 0;
	ctrl.gains.generic.g4 = 0;
	ctrl.gains.generic.g5 = 0;
	
	//Position controller
	ctrl.gains.position.kp = 0;
	ctrl.gains.position.ki = 0;
	ctrl.gains.position.kd = 0;
	
	//Impedance controller
	ctrl.gains.impedance.k = 0;
	ctrl.gains.impedance.b = 0;
	ctrl.gains.impedance.i = 0;
	
	//Current controller
	ctrl.gains.current.kp = 0;
	ctrl.gains.current.ki = 0;
	ctrl.gains.current.kd = 0;
}

