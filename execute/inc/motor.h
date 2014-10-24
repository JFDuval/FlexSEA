#ifndef INC_MOTOR_H
#define INC_MOTOR_H
	
#include <project.h>

//Common defines:

//PWM limits
#define MAX_PWM					3199
#define MIN_PWM					-MAX_PWM
	
//Position controller
#define POS_PWM_LIMIT			3000		//x%
#define MAX_CUMULATIVE_ERROR	1000
#define GAIN_P					0			//Default value - will change at runtime
#define GAIN_I					0			//Idem
#define GAIN_D					0			//Idem
	
//Current controller
#define CURRENT_ZERO			2065		//Roughly half supply ADC
#define CURRENT_SPAN			500			//Variation from zero (technically, that's SPAN/2)
#define CURRENT_POS_LIMIT		CURRENT_SPAN
#define CURRENT_NEG_LIMIT		-CURRENT_SPAN

//Impedance controller
#define B1 						2898195LL 	// 3rd order Butterworth filter numerator constants
#define B2 						8694584LL
#define B3 						8694584LL
#define B4 						2898195LL
#define A1 						1000000000LL 	// 3rd order Butterworth filter denominator constants
#define A2 						-2374094744LL
#define A3  					1929355669LL
#define A4 						-532075368LL
	
//Prototypes
void motor_open_speed_1(int16 pwm_duty);
void motor_open_speed_2(int16 pwm_duty, int sign);
int8 serial_motor_speed(int8 letter);
int motor_position_pi_encoder(int wanted_pos, int new_enc_count);
int motor_position_pi_analog(int wanted_pos, int analog_pos);
int16 int_wpos(int16 old_wpos, int16 new_wpos, uint8 reset);
int16 ramp_demo(int16 limit1, int16 limit2);
int motor_current_pid_1(int wanted_curr, int measured_curr);
void control_strategy(unsigned char strat);
int motor_impedance_encoder(int wanted_pos, int new_enc_count);
	
#endif
	