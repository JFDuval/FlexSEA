//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// flexsea_cmd_external: External/Expansion Commands
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
// Variable(s)
//****************************************************************************

//Will change this, but for now the payloads will be stored in:
unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Transmission of a CLUTCH command
uint32_t tx_cmd_exp_clutch(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t clutch)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[CP_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		//No arguments needed to read the clutch state

		//Arguments:
		//...

		bytes = CP_DATA1 + 0;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply

		buf[CP_CMD1] = CMD_W(CMD_CLUTCH);

		//Arguments:
		buf[CP_DATA1 + 0] = clutch;

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

//Reception of a CLUTCH command
void rx_cmd_exp_clutch(uint8_t *buf)
{
	uint32_t numb = 0;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Structure pointer. Points to exec1 by default.
	struct execute_s *exec_s_ptr = &exec1;

	//Point to the appropriate structure:
	if(buf[CP_XID] == FLEXSEA_EXECUTE_1)
	{
		exec_s_ptr = &exec1;
	}
	else if(buf[CP_XID] == FLEXSEA_EXECUTE_2)
	{
		exec_s_ptr = &exec2;
	}

	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	if(IS_CMD_RW(buf[CP_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		//===================

		numb = tx_cmd_exp_clutch(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, \
									PAYLOAD_BUF_LEN, read_clutch());
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485_1, (numb));

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
	else if(IS_CMD_RW(buf[CP_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store values:

			exec_s_ptr->clutch = buf[CP_DATA1+0];

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			clutch_output(buf[CP_DATA1+0]);

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

