//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// main_fsm: Contains all the case() code for the main FSM
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "main_fsm.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t slave_comm_trig = 0;
uint8_t new_cmd_led = 0;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

//****************************************************************************
// Public Function(s)
//****************************************************************************

//1kHz time slots:
//================

//Case 0: 
void main_fsm_case_0(void)
{
	slave_comm_trig = 1;

	//test_comm_rw_master_v2(systick_100us_timeshare);
}

//Case 1: 
void main_fsm_case_1(void)
{

}

//Case 2:
void main_fsm_case_2(void)
{
	//Test code 03/22/2016:

	/*

	static uint8_t xmit_toggle = 0;
	int tx_byte = 0, commstrlen = 0;
	unsigned char test_payload[PAYLOAD_BUF_LEN];

	 xmit_toggle ^= 1;	//500Hz
	 if(xmit_toggle)
	 {
	 tx_byte = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, test_payload, PAYLOAD_BUF_LEN, 0, 0, 0, 0, 0, 0);
	 commstrlen = comm_gen_str(test_payload, comm_str_485_1, tx_byte);
	 commstrlen = COMM_STR_BUF_LEN;
	 flexsea_send_serial_slave(PORT_RS485_1, comm_str_485_1, commstrlen);

	 slaves_485_1.xmit.listen = 1;
	 }
	 */
	//test_comm_rw_master_v1();
}

//Case 3: 
void main_fsm_case_3(void)
{

}

//Case 4:
void main_fsm_case_4(void)
{

}

//Case 5:
void main_fsm_case_5(void)
{
	slave_comm_trig = 2;
}

//Case 6:
void main_fsm_case_6(void)
{

}

//Case 7:
void main_fsm_case_7(void)
{
}

//Case 8: User functions
void main_fsm_case_8(void)
{
	#if(RUNTIME_FSM == ENABLED)
	user_fsm();
	#endif //RUNTIME_FSM == ENABLED
}

//Case 9: User Interface
void main_fsm_case_9(void)
{
	//UI RGB LED
	rgb_led_ui(0, 0, 0, new_cmd_led);    //ToDo add error codes
	if(new_cmd_led)
	{
		new_cmd_led = 0;
	}

	//test_comm_rw_master_v2(systick_100us_timeshare)
}

//10kHz time slot:
//================

void main_fsm_10kHz(void)
{
	//Master-Slave communications
	slave_comm(&slave_comm_trig);
}

//Asynchronous time slots:
//========================

void main_fsm_asynchronous(void)
{

}

//****************************************************************************
// Private Function(s)
//****************************************************************************

