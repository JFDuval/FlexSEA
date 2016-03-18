//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_cmd_application: Application/User specific commands
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/flexsea_system.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//Will change this, but for now the payloads will be stored in:
unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//Special code for Manage:
struct spc4_s spc4_ex1, spc4_ex2;
//ToDo useful?

//****************************************************************************
// Function(s)
//****************************************************************************

//Transmission of a CTRL_SPECIAL_1 command: ShuoBot Exo
//Arguments are only for data that the user will change at runtime.
//controller_w (Write New Controller): KEEP/CHANGE
//controller (New controller): ignored if ctrl_w == KEEP
//encoder_w (Write New Encoder value): KEEP/CHANGE
//encoder_cnt (New encoder count): ignored if encoder_w == KEEP
//current: current controller setpoint
uint32_t tx_cmd_ctrl_special_1(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t controller_w, uint8_t controller, uint8_t encoder_w, int32_t encoder, \
								int16_t current, int16_t open_spd)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)	
	{
		//In that case Read also includes a bunch of writing. We keep the Read keyword as 
		//it will get us a reply.
		
		buf[P_CMD1] = CMD_R(CMD_SPC1);
		
		//Arguments:
		buf[P_DATA1] = controller_w;
		buf[P_DATA1 + 1] = controller;
		uint16_to_bytes((uint16_t)current, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		buf[P_DATA1 + 4] = encoder_w;
		uint32_to_bytes((uint32_t)encoder, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 5] = tmp0;
		buf[P_DATA1 + 6] = tmp1;
		buf[P_DATA1 + 7] = tmp2;
		buf[P_DATA1 + 8] = tmp3;
		uint16_to_bytes((uint16_t)open_spd, &tmp0, &tmp1);
		buf[P_DATA1 + 9] = tmp0;
		buf[P_DATA1 + 10] = tmp1;

		bytes = P_DATA1 + 11;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply
		
		buf[P_CMD1] = CMD_W(CMD_SPC1);
		
		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Arguments:
		uint16_to_bytes((uint16_t)imu.gyro.x, &tmp0, &tmp1);
		buf[P_DATA1] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)imu.gyro.y, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)imu.gyro.z, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;
		
		uint16_to_bytes(strain_read(), &tmp0, &tmp1);
		buf[P_DATA1 + 6] = tmp0;
		buf[P_DATA1 + 7] = tmp1;
		
		uint16_to_bytes(read_analog(0), &tmp0, &tmp1);
		buf[P_DATA1 + 8] = tmp0;
		buf[P_DATA1 + 9] = tmp1;
		
		//uint32_to_bytes((uint32_t)encoder_read(), &tmp0, &tmp1, &tmp2, &tmp3);
		uint32_to_bytes((uint32_t)QuadDec_1_GetCounter(), &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 10] = tmp0;
		buf[P_DATA1 + 11] = tmp1;
		buf[P_DATA1 + 12] = tmp2;
		buf[P_DATA1 + 13] = tmp3;
		
		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
		buf[P_DATA1 + 14] = tmp0;
		buf[P_DATA1 + 15] = tmp1;

		buf[P_DATA1 + 16] = safety_cop.status1;
		buf[P_DATA1 + 17] = safety_cop.status2;

		bytes = P_DATA1 + 18;     //Bytes is always last+1
		
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
	int16_t tmp_wanted_current = 0, tmp_open_spd = 0;
	int32_t tmp_enc = 0;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Structure pointer. Points to exec1 by default.
	struct execute_s *exec_s_ptr;

	//Point to the appropriate structure:
	if(buf[P_XID] == FLEXSEA_EXECUTE_1)
	{
		exec_s_ptr = &exec1;
	}
	else if(buf[P_XID] == FLEXSEA_EXECUTE_2)
	{
		exec_s_ptr = &exec2;
	}
	else if(buf[P_XID] == FLEXSEA_EXECUTE_3)
	{
		exec_s_ptr = &exec3;
	}
	else if(buf[P_XID] == FLEXSEA_EXECUTE_4)
	{
		exec_s_ptr = &exec4;
	}

	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			
		//Decode its data:
		//===============
		
		//Controller:	
		if(buf[P_DATA1] == CHANGE)
		{
			//User wants to change the type of controller:
			//control_strategy(buf[P_DATA1]);	//Disabled, change it manually
		}
		
		//Only change the setpoint if we are in current control mode:	
		if(ctrl.active_ctrl == CTRL_CURRENT)
		{
			tmp_wanted_current = BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]);
			ctrl.current.setpoint_val = tmp_wanted_current;
		}
		else if(ctrl.active_ctrl == CTRL_OPEN)
		{
			tmp_open_spd = BYTES_TO_UINT16(buf[P_DATA1 + 9], buf[P_DATA1 + 10]);
			motor_open_speed_1(tmp_open_spd);
		}

		//Encoder:
		if(buf[P_DATA1 + 4] == CHANGE)
		{
			//User wants to overwrite the encoder:
			int32 tmp_enc = (int32)BYTES_TO_UINT32(buf[P_DATA1 + 5], buf[P_DATA1 + 6], \
													buf[P_DATA1 + 7], buf[P_DATA1 + 8]);	
			encoder_write(tmp_enc);	
		}

		//Generate the reply:
		//===================
		
		numb = tx_cmd_ctrl_special_1(buf[P_XID], CMD_WRITE, tmp_payload_xmit, \
									PAYLOAD_BUF_LEN, KEEP, 0, KEEP, 0, 0, 0);		
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//(for now, send it)
		rs485_puts(comm_str_485_1, (numb));	
		#ifdef USE_USB
		usb_puts(comm_str_485_1, (numb));	
		#endif

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
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
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
				
			exec_s_ptr->imu.x = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+0], buf[P_DATA1+1]));
			exec_s_ptr->imu.y = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+2], buf[P_DATA1+3]));
			exec_s_ptr->imu.z = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+4], buf[P_DATA1+5]));
			
			exec_s_ptr->strain = (BYTES_TO_UINT16(buf[P_DATA1+6], buf[P_DATA1+7]));
			exec_s_ptr->analog[0] = (BYTES_TO_UINT16(buf[P_DATA1+8], buf[P_DATA1+9]));
	
			exec_s_ptr->encoder = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1+10], buf[P_DATA1+11], \
										buf[P_DATA1+12], buf[P_DATA1+13]));
			
			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+14], buf[P_DATA1+15]));

			exec_s_ptr->status1 = buf[P_DATA1+16];
			exec_s_ptr->status2 = buf[P_DATA1+17];

			#ifdef MULTIPLE_COMMANDS
			//To interface with Python:
			printf("[%i,%i,%i,%i,%i,%i,%i]\n", exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
					exec1.strain, exec1.analog[0]);
			#endif

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