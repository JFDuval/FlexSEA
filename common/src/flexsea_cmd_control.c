//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_cmd_control: Control Commands
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea.h"
#include "flexsea_local.h"
//#include "flexsea_cmd_control.h"

//Plan boards only:
#ifdef BOARD_TYPE_FLEXSEA_PLAN
//...
#endif	//BOARD_TYPE_FLEXSEA_PLAN

//Manage boards only:
#ifdef BOARD_TYPE_FLEXSEA_MANAGE
//...
#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//Execute boards only:
#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
#include "main.h"
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Will change this, but for now the payloads will be stored in:
unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Transmission of a CTRL_I command
uint32_t tx_cmd_ctrl_i(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t wanted, int16_t measured)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[CP_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[CP_CMD1] = CMD_R(CMD_CTRL_I);

		bytes = CP_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[CP_CMD1] = CMD_W(CMD_CTRL_I);

		//Arguments:
		uint16_to_bytes(measured, &tmp0, &tmp1);
		buf[CP_DATA1] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;
		uint16_to_bytes(wanted, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;

		bytes = CP_DATA1 + 4;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_I command
void rx_cmd_ctrl_i(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_wanted_current = 0, tmp_measured_current = 0;

	if(IS_CMD_RW(buf[CP_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_i(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.current.actual_val, ctrl.current.setpoint_val);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485_1, (numb));

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[CP_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_measured_current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1+1]));
		tmp_wanted_current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE

			//Store value:
			exec1.current = tmp_measured_current;

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			#ifdef USE_PRINTF
			printf("Received CMD_CTRL_I_READ_REPLY. Wanted = %i, Measured = %i.\n", tmp_wanted_current, tmp_measured_current);
			#endif	//USE_PRINTF

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Only change the setpoint if we are in current control mode:	
			if(ctrl.active_ctrl == CTRL_CURRENT)
			{
				ctrl.current.setpoint_val = tmp_wanted_current;
			}

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

/*
void test_cmd_ctrl_i(void)
{
	//First, we generate a TX Write:
	tx_cmd_ctrl_i(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, -333, 666);

	//Minimalist parsing:
	if(CMD_7BITS(tmp_payload_xmit[CP_CMD1]) == CMD_CTRL_I)
	{
		//Decode it:
		rx_cmd_ctrl_i(tmp_payload_xmit);
	}
}
*/

//Transmission of a CTRL_MODE command
uint32_t tx_cmd_ctrl_mode(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t ctrl)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[CP_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[CP_CMD1] = CMD_R(CMD_CTRL_MODE);

		bytes = CP_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[CP_CMD1] = CMD_W(CMD_CTRL_MODE);

		//Arguments:
		buf[CP_DATA1] = ctrl;

		bytes = CP_DATA1 + 1;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_MODE command
void rx_cmd_ctrl_mode(uint8_t *buf)
{
	uint8_t numb = 0, controller = 0;

	if(IS_CMD_RW(buf[CP_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_mode(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, ctrl.active_ctrl);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[CP_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		controller = buf[CP_DATA1];
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.active_ctrl = controller;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			control_strategy(controller);

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmission of a CTRL_O command
uint32_t tx_cmd_ctrl_o(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t open_spd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[CP_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[CP_CMD1] = CMD_R(CMD_CTRL_O);

		bytes = CP_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[CP_CMD1] = CMD_W(CMD_CTRL_O);

		//Arguments:
		uint16_to_bytes(open_spd, &tmp0, &tmp1);
		buf[CP_DATA1] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;

		bytes = CP_DATA1 + 2;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_O command
void rx_cmd_ctrl_o(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_open_spd = 0;

	if(IS_CMD_RW(buf[CP_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_o(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.pwm);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[CP_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_open_spd = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1+1]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE

			//Store value:
			exec1.pwm = tmp_open_spd;

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			#ifdef USE_PRINTF
			printf("Received CMD_CTRL_O. PWM DC = %i.\n", tmp_open_spd);
			#endif	//USE_PRINTF

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			if(ctrl.active_ctrl == CTRL_OPEN)
			{
				motor_open_speed_1(tmp_open_spd);
			}

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}
