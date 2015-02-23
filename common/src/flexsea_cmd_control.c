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
// External variable(s)
//****************************************************************************

extern uint8_t board_id;

#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

#ifdef BOARD_TYPE_FLEXSEA_MANAGE

#endif	//BOARD_TYPE_FLEXSEA_MANAGE

#ifdef BOARD_TYPE_FLEXSEA_PLAN

#endif	//BOARD_TYPE_FLEXSEA_PLAN

//****************************************************************************
// Function(s)
//****************************************************************************

//Transmission of a CTRL_I command
uint32_t tx_cmd_ctrl_i(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t wanted, int16_t measured)
{
	uint8_t tmp0 = 0, tmp1 = 0, bytes = 0;

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
	uint8_t numb = 0;
	int16_t tmp_wanted_current = 0, tmp_measured_current = 0;

	if(IS_CMD_RW(buf[CP_CMD1] == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_i(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			(ctrl.current.actual_val - CURRENT_ZERO), ctrl.current.setpoint_val);
		numb = comm_gen_str(payload_str, numb);

		//Notify the code that a buffer is ready to be transmitted:
		xmit_flag = 1;

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE
		//No code (yet), you shouldn't be here...
		flexsea_error(SE_CMD_NOT_PROGRAMMED);
		#endif	//BOARD_TYPE_FLEXSEA_MANAGE

		#ifdef BOARD_TYPE_FLEXSEA_PLAN
		//No code (yet), you shouldn't be here...
		flexsea_error(SE_CMD_NOT_PROGRAMMED);
		#endif	//BOARD_TYPE_FLEXSEA_PLAN
	}
	else if(IS_CMD_RW(buf[CP_CMD1] == WRITE)
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

			//ToDo call relevant functions ****

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
	}
}
