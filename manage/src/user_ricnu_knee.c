//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval & Luke Mooney & Elliott Rouse
// jfduval@mit.edu & lmooney@mit.edu & erouse@northwestern.edu
// 05/2016
//****************************************************************************
// knee: knee functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "user_ricnu_knee.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static void ricnu_knee_refresh_values(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Call this function once in main.c, just before the while()
void init_ricnu_knee(void)
{	

}

//Knee Finite State Machine.
//Call this function in one of the main while time slots.
void ricnu_knee_fsm(void)
{
    static uint16_t time = 0;
    static uint8_t state = 0;
    static uint16_t tmp_posi = 0;
	static uint16_t tmp_posf = 0;
	static uint16_t tmp_spdm = 0;
	static uint16_t tmp_acc = 0;
	
    //Increment time
    time++;
    
	//Before going to a state we refresh values:
	ricnu_knee_refresh_values();
	
    if (time == 0)
    {
    	/*
        state = 0;
        tmp_posi = encoder.count;
        tmp_posf = 1000;
        tmp_spdm = 10000;
        tmp_acc = 10000;
        */
    }
    
    if (time == 2000) 
    {
    	/*
        state = 1;
        tmp_posi = encoder.count;
        tmp_posf = -2000;
        tmp_spdm = 20000;
        tmp_acc = 20000;
        */
    }    
    
	switch(state)
	{
		case 0:
			/*
			//Put some code here...
            //Example: motor_open_speed_1(85);			//0% PWM
            ctrl.position.posi = tmp_posi;
			ctrl.position.posf = tmp_posf;
			ctrl.position.spdm = tmp_spdm;
			ctrl.position.acc = tmp_acc;
            steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);
			state = 2;
			*/
            break;
		case 1:
			/*
			ctrl.position.posi = tmp_posi;
			ctrl.position.posf = tmp_posf;
			ctrl.position.spdm = tmp_spdm;
			ctrl.position.acc = tmp_acc;
            steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);          
            
            time = -1000;
            state = 2;
            */
            break;
        case 2:
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
static void ricnu_knee_refresh_values(void)
{
	//...
}
//That function can be called from the FSM.
