//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 06/2016
//****************************************************************************
// user_csea_knee: CSEA Knee Functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "user_csea_knee.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static void csea_knee_refresh_values(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Call this function once in main.c, just before the while()
void init_csea_knee(void)
{	
	//Controller setup:
	ctrl.active_ctrl = CTRL_POSITION;	//Position controller
    motor_open_speed_1(0);				//0% PWM
	Coast_Brake_Write(1);				//Brake (regen)
	   
    //Position PID gains - initially 0
	ctrl.position.gain.P_KP = 0;
	ctrl.position.gain.P_KI = 0;
  
}

//Knee Finite State Machine.
//Call this function in one of the main while time slots.
void csea_knee_fsm(void)
{
    static uint32 time = 0;
    static uint8 state = 0;
	
    //Increment time (1 tick = 1ms)
    time++;
    
	//Before going to a state we refresh values:
	csea_knee_refresh_values();
	
	switch(state)
	{
		case 0:
			//Startup state, stay here for the first 10s.
			//User: place the knee in full extension
			if(time >= 10000)
			{
				time = 0;
				ctrl.position.gain.P_KP = 25;
				ctrl.position.gain.P_KI = 5;
				state = 1;
			}
            break;
		case 1:			
			//From knee extension to knee flexion
			if(time <= 1)
			{	
				//The first time we calculate a new trajectory
				ctrl.position.posi = ctrl.position.pos;	//Use actual position as starting point
				ctrl.position.posf = CSEA_FULL_FLEX - CSEA_MARGIN;
				ctrl.position.spdm = 1000;
				ctrl.position.acc = 1000;
	            steps = trapez_gen_motion_1(ctrl.position.pos, ctrl.position.posf, ctrl.position.spdm, ctrl.position.acc); 
			}
            else if(time >= CSEA_MOTION_TIME)
			{
				//Enough time spent for that motion, moving to next case
				time = 0;
				state = 2;
			}
            break;
        case 2:
			//From knee flexsion to knee extension
			if(time <= 1)
			{	
				//The first time we calculate a new trajectory
				ctrl.position.posi = ctrl.position.pos;	//Use actual position as starting point
				ctrl.position.posf = CSEA_FULL_EXT + CSEA_MARGIN;
				ctrl.position.spdm = 1000;
				ctrl.position.acc = 1000;
	            steps = trapez_gen_motion_1(ctrl.position.pos, ctrl.position.posf, ctrl.position.spdm, ctrl.position.acc); 
			}
            else if(time >= CSEA_MOTION_TIME)
			{
				//Enough time spent for that motion, moving to next case
				time = 0;
				state = 1;
			}
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
static void csea_knee_refresh_values(void)
{
	//...
}
//That function can be called from the FSM.
