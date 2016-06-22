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
#include <math.h>

//****************************************************************************
// Variable(s)
//****************************************************************************

int16_t my_pwm = 0;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static void ankle_2dof_refresh_values(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Test!
#define A0 	(202.2+1140)
#define A1 	1302
#define A2	-39.06
#define B1 	14.76
#define B2 	-7.874
#define W	0.00223
int16_t get_ankle_trans_2(double ma) //mot_ang [deg] where mot_ang = 0 is at maximum dorsiflexion
{
   double slope = 0, transmission = 0;
   double tmp1 = 0, tmp2 = 0;

   if(ma < 0)
   {
	   ma = 0;
   }

   tmp1 = ma*W;
   tmp2 = ma*W*2;
   slope = (-W*A1*sin(tmp1) + W*B1*cos(tmp1) - 2*W*A2*sin(tmp2) + 2*W*B2*cos(tmp2));
   transmission = ((double)(-1000.0/slope));

   if(transmission > 3000)
   {
	   return 3000;
   }
   else
   {
	   return (int16_t)transmission;
   }

   return 0;
}

//Call this function once in main.c, just before the while()
void init_ankle_2dof(void)
{	
	//ToDo...  
}

//Ankle 2-DoF Finite State Machine.
//Call this function in one of the main while time slots.
void ankle_2dof_fsm_1(void)
{
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
    static uint32_t time = 0;
    static uint8_t state = 0;
    double myvar1 = 0.0, myvar2 = 0.0;
	
    //Increment time (1 tick = 1ms)
    time++;
    
	//Before going to a state we refresh values:
	ankle_2dof_refresh_values();
	
	//Nothing programmed yet...
	switch(state)
	{
		case 0:
			//my_pwm = 0;
			my_pwm = (int16_t)user_data.w[0];
			if(time > 1500)
			{
				time = 0;
				state = 1;
			}
            break;
		case 1:
			//my_pwm = 100;
			my_pwm = (int16_t)user_data.w[1];
			if(time > 1500)
			{
				time = 0;
				state = 0;
			}
            break;
        case 2:
        	myvar1 = 27.0*32;
        	myvar2 = cos(myvar1);
        	myvar1 = get_ankle_trans_2(5.78);
            break;
        default:
			//Handle exceptions here
			break;
	}
	#endif	//ACTIVE_PROJECT == PROJECT_ANKLE_2DOF
}



//Second state machine for the Ankle project
//Deals with the communication between Manage and 2x Execute, on the same RS-485 bus
//This function is called at 1kHz
void ankle_2dof_fsm_2(void)
{
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)

	static uint8_t ex_refresh_fsm_state = 0;
	static uint32_t timer = 0;
	int tx_byte = 0, commstrlen = 0;
	unsigned char test_payload[PAYLOAD_BUF_LEN];

	//This FSM talks to the slaves at 250Hz each
	switch(ex_refresh_fsm_state)
	{
		case 0:		//Power-up
			if(timer < 7000)
			{
				//We wait 7s before sending the first commands
				LED1(0);
				timer++;
			}
			else
			{
				//Ready to start transmitting
				LED1(1);
				ex_refresh_fsm_state = 1;
			}
			break;
		case 1:	//Communicating with Execute #1

			tx_byte = tx_cmd_ctrl_special_5(FLEXSEA_EXECUTE_1, CMD_READ, test_payload, PAYLOAD_BUF_LEN, 0, 1, 0, my_pwm);
			 commstrlen = comm_gen_str(test_payload, comm_str_485_1, tx_byte);
			 commstrlen = COMM_STR_BUF_LEN;
			 flexsea_send_serial_slave(PORT_RS485_1, comm_str_485_1, commstrlen);

			 slaves_485_1.xmit.listen = 1;
			ex_refresh_fsm_state++;
			break;
		case 2:
			//Skipping one cycle
			ex_refresh_fsm_state++;
			break;
		case 3:	//Communicating with Execute #2

			tx_byte = tx_cmd_ctrl_special_5(FLEXSEA_EXECUTE_2, CMD_READ, test_payload, PAYLOAD_BUF_LEN, 0, 1, 0, my_pwm);
			 commstrlen = comm_gen_str(test_payload, comm_str_485_2, tx_byte);
			 commstrlen = COMM_STR_BUF_LEN;
			 flexsea_send_serial_slave(PORT_RS485_2, comm_str_485_2, commstrlen);

			 slaves_485_2.xmit.listen = 1;
			ex_refresh_fsm_state++;
			break;
		case 4:
			//Skipping one cycle
			ex_refresh_fsm_state = 1;
			break;
	}

	#endif	//ACTIVE_PROJECT == PROJECT_ANKLE_2DOF
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//Note: 'static' makes them private; they can only called from functions in this
//file. It's safer than making everything global.

//Here's an example function:
static void ankle_2dof_refresh_values(void)
{
	//Test code:
	static uint8_t var = 0;
	user_data.r[0] = var++;
	user_data.r[1] = user_data.w[1];
	user_data.r[2] = -1999;
	user_data.r[3] = 123456789;
}
//That function can be called from the FSM.


