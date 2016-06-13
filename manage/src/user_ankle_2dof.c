//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// user_ankle_2dof: 2-DoF Ankle Functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "user_ankle_2dof.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static void ankle_2dof_refresh_values(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Call this function once in main.c, just before the while()
void init_ankle_2dof(void)
{	
	//ToDo...  
}

//Ankle 2-DoF Finite State Machine.
//Call this function in one of the main while time slots.
void ankle_2dof_fsm(void)
{
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
    static uint32 time = 0;
    static uint8 state = 0;
	
    //Increment time (1 tick = 1ms)
    time++;
    
	//Before going to a state we refresh values:
	ankle_2dof_refresh_values();
	
	//Nothing programmed yet...
	switch(state)
	{
		case 0:
            break;
		case 1:			
            break;
        case 2:
            break;
        default:
			//Handle exceptions here
			break;
	}
	#endif
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//Note: 'static' makes them private; they can only called from functions in this
//file. It's safer than making everything global.

//Here's an example function:
static void ankle_2dof_refresh_values(void)
{
	//...
}
//That function can be called from the FSM.
