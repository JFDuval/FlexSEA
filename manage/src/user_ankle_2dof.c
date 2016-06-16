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
static void dual_execute_refresh(void);

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
void ankle_2dof_fsm_1(void)
{
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
    static uint32_t time = 0;
    static uint8_t state = 0;
	
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

	//This FSM talks to the slaves at 250hZ each
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

			tx_byte = tx_cmd_data_read_all(FLEXSEA_EXECUTE_1, CMD_READ, test_payload, PAYLOAD_BUF_LEN);
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

			tx_byte = tx_cmd_data_read_all(FLEXSEA_EXECUTE_2, CMD_READ, test_payload, PAYLOAD_BUF_LEN);
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
	//...
}
//That function can be called from the FSM.


