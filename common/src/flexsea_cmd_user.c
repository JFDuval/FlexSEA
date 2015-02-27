//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_cmd_control: User Commands
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
extern uint8_t xmit_flag;

#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

//motor.c:
extern struct ctrl_s ctrl;
extern struct enc_s encoder;	
extern struct imu_s imu;
	
extern unsigned char comm_str[COMM_STR_BUF_LEN];

#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

#ifdef BOARD_TYPE_FLEXSEA_MANAGE

struct execute_s exec1;

#endif	//BOARD_TYPE_FLEXSEA_MANAGE

#ifdef BOARD_TYPE_FLEXSEA_PLAN

struct execute_s exec1;

#endif	//BOARD_TYPE_FLEXSEA_PLAN

//****************************************************************************
// Function(s)
//****************************************************************************

//Transmission of a CTRL_SPECIAL_1 command
//Arguments are only for data that the user will change at runtime.
//controller_w (Write New Controller): KEEP/CHANGE
//controller (New controller): ignored if ctrl_w == KEEP
//encoder_w (Write New Encoder value): KEEP/CHANGE
//encoder_cnt (New encoder count): ignored if encoder_w == KEEP
//current: current controller setpoint
uint32_t tx_cmd_ctrl_special_1(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t controller_w, uint8_t controller, uint8_t encoder_w, int32_t encoder, \
								int16_t current)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[CP_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)	
	{
		//In that case Read also includes a bunch of writing. We keep the Read keyword as 
		//it will get us a reply.
		
		buf[CP_CMD1] = CMD_R(CMD_SPECIAL_1);
		
		//Arguments:
		buf[CP_DATA1] = controller_w;
		buf[CP_DATA1 + 1] = controller;
		uint16_to_bytes((uint16_t)current, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		buf[CP_DATA1 + 4] = encoder_w;
		uint32_to_bytes((uint32_t)encoder, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 5] = tmp0;
		buf[CP_DATA1 + 6] = tmp1;
		buf[CP_DATA1 + 7] = tmp2;
		buf[CP_DATA1 + 8] = tmp3;

		bytes = CP_DATA1 + 9;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply
		
		buf[CP_CMD1] = CMD_W(CMD_SPECIAL_1);
		
		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Arguments:
		uint16_to_bytes((uint16_t)imu.gyro.x, &tmp0, &tmp1);
		buf[CP_DATA1] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)imu.gyro.y, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)imu.gyro.z, &tmp0, &tmp1);
		buf[CP_DATA1 + 4] = tmp0;
		buf[CP_DATA1 + 5] = tmp1;
		
		uint16_to_bytes(strain_read(), &tmp0, &tmp1);
		buf[CP_DATA1 + 6] = tmp0;
		buf[CP_DATA1 + 7] = tmp1;
		
		uint16_to_bytes(read_analog(0), &tmp0, &tmp1);
		buf[CP_DATA1 + 8] = tmp0;
		buf[CP_DATA1 + 9] = tmp1;
		
		uint32_to_bytes((uint32_t)encoder_read(), &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 10] = tmp0;
		buf[CP_DATA1 + 11] = tmp1;
		buf[CP_DATA1 + 12] = tmp2;
		buf[CP_DATA1 + 13] = tmp3;
		
		uint16_to_bytes((uint16_t)(ctrl.current.actual_val - CURRENT_ZERO), &tmp0, &tmp1);
		buf[CP_DATA1 + 14] = tmp0;
		buf[CP_DATA1 + 15] = tmp1;

		bytes = CP_DATA1 + 16;     //Bytes is always last+1
		
		#else
		
		bytes = 0;
		
		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CMD_SPECIAL_1 command
void rx_cmd_special_1(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_wanted_current = 0;
	int32_t tmp_enc = 0;

	if(IS_CMD_RW(buf[CP_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			
		//Decode its data:
		//===============
		
		//Controller:	
		if(buf[CP_DATA1] == CHANGE)
		{
			//User wants to change the type of controller:
			control_strategy(buf[CP_DATA1]);
		}
		
		//Current:
		tmp_wanted_current = BYTES_TO_UINT16(buf[CP_DATA1 + 2], buf[CP_DATA1 + 3]);
		ctrl.current.setpoint_val = tmp_wanted_current;
		
		//Encoder:
		if(buf[CP_DATA1 + 4] == CHANGE)
		{
			//User wants to overwrite the encoder:
			int32 tmp_enc = (int32)BYTES_TO_UINT32(buf[CP_DATA1 + 5], buf[CP_DATA1 + 6], \
													buf[CP_DATA1 + 7], buf[CP_DATA1 + 8]);	
			encoder_write(tmp_enc);	
		}

		//Generate the reply:
		//===================
		
		numb = tx_cmd_ctrl_special_1(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, \
									PAYLOAD_BUF_LEN, KEEP, 0, KEEP, 0, 0);		
		numb = comm_gen_str(tmp_payload_xmit, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//Notify the code that a buffer is ready to be transmitted:
		xmit_flag = 1;
		
		//(for now, send it)
		rs485_puts(comm_str, (numb));	

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
				
			exec1.imu.x = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+0], buf[CP_DATA1+1]));
			exec1.imu.y = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
			exec1.imu.z = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+4], buf[CP_DATA1+5]));
			
			exec1.strain = (BYTES_TO_UINT16(buf[CP_DATA1+6], buf[CP_DATA1+7]));
			exec1.analog = (BYTES_TO_UINT16(buf[CP_DATA1+8], buf[CP_DATA1+9]));
	
			exec1.encoder = (int32_t) (BYTES_TO_UINT32(buf[CP_DATA1+10], buf[CP_DATA1+11], \
										buf[CP_DATA1+12], buf[CP_DATA1+13]));
			
			exec1.current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+14], buf[CP_DATA1+15]));

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

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
