//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval & Luke Mooney
// jfduval@mit.edu & lmooney@mit.edu
// 05/2015
//****************************************************************************
// exo: ExoBoot functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "exo.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//Filters:
int32 aFilt[FILT_PARAM_SIZE], bFilt[FILT_PARAM_SIZE];

//Luke, whenever possible move these variables in functions (not as global)
//By default, I'm using int32. You might want something different.
int32 curpos = 0, curspd = 0, curacc = 0, power = 0, gyrosum = 0, gyrozero = 0;
int32 gyrozerosum = 0, maxPFpower = 0, maxCPFang = 0, GmaxPFang = 0;
int32 maxesttor = 0, gSWGang = 0, gCPFang = 0, nopull = 0, shankang = 0;
int32 esttor = 0;
//Add your "setCommand" variables here

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static void exo_refresh_values(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Call this function once in main.c, just before the while()
void init_exo(void)
{
	//Init filters:
	aFilt[0] = FILT_A0; aFilt[1] = FILT_A1; aFilt[2] = FILT_A2; 
	bFilt[0] = FILT_B0; bFilt[1] = FILT_B1; bFilt[2] = FILT_B2; 
	
	//Default values for all the variables:
	curpos = 0;				//current encoder position of motor
	curspd = 0;				//Current speed of the motor
	curacc = 0;				//Current acceleration of the motor
	power = 0;				//Power of the motor
	gyrosum = 0;			//Sum of gyros used to filter signal
//int32 gyrozero = getvalue(_AI,6);	//First gyro value
	//What's get value? ToDo fix that
	gyrozerosum = 0;		//Sum of gyroscope during zeroing
	maxPFpower = -1;		//Maximum motor power during PF
	maxCPFang = 0;			//Maximum PF angle during controlled PF of one step
	GmaxPFang = 0;			//The maximum PF angle during controlled PF of all time
	maxesttor = 0;			//The maximum estimated torque during PF
	gSWGang = 10*clkang;	//The global angle the exo returns to during swing
	gCPFang = 4*clkang;		//The amount of PF during controlled PF
	nopull = 1;				//A variable to determine if the user pulled on the string during swing
	shankang = 0;			//The angle of shank as integrated by the gyro and zeroed at heel strike
	
	//FlexSEA-Execute setup:
	ctrl.active_ctrl = CTRL_OPEN;	//Open controller
	Coast_Brake_Write(1);			//Brake (rather than Coast)
	motor_open_speed_1(0);			//0% PWM
}

//ExoBoot Finite State Machine.
//Call this function in one of the main while time slots.
void exo_fsm(void)
{
	static uint8 state = 0;
	
	//Before going to a state we refresh values:
	exo_refresh_values();
	
	switch(state)
	{
		case 0:
			//Put some code here...
			state++;
			break;
		case 1:
			state++;	//State doesn't have to increment, you can jump (state = 3) too.
			break;
		case 2:
			state = 0;	//Looping back to the start
			break;
		default:
			//Handle exceptions here
			break;
	}
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//Note: 'static' makes them private; they can only called from functions in this
//file. It's safer than making everything global.

//Here's an example function:
static void exo_refresh_values(void)
{
/*		curacc = (getvalue(_abspeed,1)-curspd)*105/(time-time0) 'motor accl in rad/s^2
	//Can I guess that it translates as "curacc = (_abspeed-curspd)*105/(time-time0); ?
		curpos = getvalue(_abcntr,1) 'get the encoder position (clicks)
		curspd = getvalue(_abspeed,1) 'get the encoder velocity (RPM)
		estcur = (getvalue(_P)*Bv-curspd*10000/346)*259/100'10000x estimated motor current *259/100 = 1/.386
		esttor = (estcur/362-33*curacc/10000)*effic/100 '1000x eestimated motor torque
		*/ 
		power = esttor*curspd/9550;		//Watts
}
//That function can be called from the FSM.

