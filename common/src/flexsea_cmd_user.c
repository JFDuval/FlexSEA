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
#include "../inc/flexsea_rx_cmd.h"

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
struct spc4_s spc4_ex1, spc4_ex2;

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
		uint16_to_bytes((uint16_t)open_spd, &tmp0, &tmp1);
		buf[CP_DATA1 + 9] = tmp0;
		buf[CP_DATA1 + 10] = tmp1;

		bytes = CP_DATA1 + 11;     //Bytes is always last+1
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
		
		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
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
	int16_t tmp_wanted_current = 0, tmp_open_spd = 0;
	int32_t tmp_enc = 0;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Structure pointer. Points to exec1 by default.
	struct execute_s *exec_s_ptr;

	//Point to the appropriate structure:
	if(buf[CP_XID] == FLEXSEA_EXECUTE_1)
	{
		exec_s_ptr = &exec1;
	}
	else if(buf[CP_XID] == FLEXSEA_EXECUTE_2)
	{
		exec_s_ptr = &exec2;
	}
	else if(buf[CP_XID] == FLEXSEA_EXECUTE_3)
	{
		exec_s_ptr = &exec3;
	}
	else if(buf[CP_XID] == FLEXSEA_EXECUTE_4)
	{
		exec_s_ptr = &exec4;
	}

	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

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
		
		//Only change the setpoint if we are in current control mode:	
		if(ctrl.active_ctrl == CTRL_CURRENT)
		{
			tmp_wanted_current = BYTES_TO_UINT16(buf[CP_DATA1 + 2], buf[CP_DATA1 + 3]);
			ctrl.current.setpoint_val = tmp_wanted_current;
		}
		else if(ctrl.active_ctrl == CTRL_OPEN)
		{
			tmp_open_spd = BYTES_TO_UINT16(buf[CP_DATA1 + 9], buf[CP_DATA1 + 10]);
			motor_open_speed_1(tmp_open_spd);
		}

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
									PAYLOAD_BUF_LEN, KEEP, 0, KEEP, 0, 0, 0);		
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

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
				
			exec_s_ptr->imu.x = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+0], buf[CP_DATA1+1]));
			exec_s_ptr->imu.y = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
			exec_s_ptr->imu.z = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+4], buf[CP_DATA1+5]));
			
			exec_s_ptr->strain = (BYTES_TO_UINT16(buf[CP_DATA1+6], buf[CP_DATA1+7]));
			exec_s_ptr->analog[0] = (BYTES_TO_UINT16(buf[CP_DATA1+8], buf[CP_DATA1+9]));
	
			exec_s_ptr->encoder = (int32_t) (BYTES_TO_UINT32(buf[CP_DATA1+10], buf[CP_DATA1+11], \
										buf[CP_DATA1+12], buf[CP_DATA1+13]));
			
			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+14], buf[CP_DATA1+15]));

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

//Transmission of a CTRL_SPECIAL_2 command: CSEA Knee
//Arguments are only for data that the user will change at runtime.
uint32_t tx_cmd_ctrl_special_2(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								int16_t z_k, int16_t z_b, int16_t z_i, uint8_t rgb, uint8_t clutch)
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

		buf[CP_CMD1] = CMD_R(CMD_SPECIAL_2);

		//Arguments:
		uint16_to_bytes((uint16_t)z_k, &tmp0, &tmp1);
		buf[CP_DATA1 + 0] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)z_b, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)z_i, &tmp0, &tmp1);
		buf[CP_DATA1 + 4] = tmp0;
		buf[CP_DATA1 + 5] = tmp1;
		buf[CP_DATA1 + 6] = rgb;
		buf[CP_DATA1 + 7] = clutch;


		bytes = CP_DATA1 + 8;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply

		buf[CP_CMD1] = CMD_W(CMD_SPECIAL_2);

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

		uint16_to_bytes(read_analog(0), &tmp0, &tmp1);
		buf[CP_DATA1 + 6] = tmp0;
		buf[CP_DATA1 + 7] = tmp1;

		uint16_to_bytes(read_analog(1), &tmp0, &tmp1);	//ToDo
		buf[CP_DATA1 + 8] = tmp0;
		buf[CP_DATA1 + 9] = tmp1;

		uint32_to_bytes((uint32_t)encoder_read(), &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 10] = tmp0;
		buf[CP_DATA1 + 11] = tmp1;
		buf[CP_DATA1 + 12] = tmp2;
		buf[CP_DATA1 + 13] = tmp3;

		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
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
void rx_cmd_special_2(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_zk = 0, tmp_zb = 0, tmp_zi = 0, tmp_current = 0;

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

		//Decode its data:
		//===============

		//Impedance gains:
		if(ctrl.active_ctrl == CTRL_IMPEDANCE)
		{
			tmp_zk = BYTES_TO_UINT16(buf[CP_DATA1 + 0], buf[CP_DATA1 + 1]);
			ctrl.impedance.gain.Z_K = tmp_zk;
			tmp_zb = BYTES_TO_UINT16(buf[CP_DATA1 + 2], buf[CP_DATA1 + 3]);
			ctrl.impedance.gain.Z_B = tmp_zb;
			tmp_zi = BYTES_TO_UINT16(buf[CP_DATA1 + 4], buf[CP_DATA1 + 5]);
			ctrl.impedance.gain.Z_I = tmp_zi;
		}

		//Clutch:
		clutch_output(buf[CP_DATA1 + 7]);

		//MinM RGB:
		minm_rgb_color = buf[CP_DATA1 + 6]; //ToDo set value that will be used in the next cycle

		//Generate the reply:
		//===================

		numb = tx_cmd_ctrl_special_2(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, \
									PAYLOAD_BUF_LEN, 0, 0, 0, 0, 0);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

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

			exec_s_ptr->imu.x = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+0], buf[CP_DATA1+1]));
			exec_s_ptr->imu.y = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
			exec_s_ptr->imu.z = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+4], buf[CP_DATA1+5]));

			exec_s_ptr->analog[0] = (BYTES_TO_UINT16(buf[CP_DATA1+6], buf[CP_DATA1+7]));
			exec_s_ptr->analog[1] = (BYTES_TO_UINT16(buf[CP_DATA1+8], buf[CP_DATA1+9]));

			exec_s_ptr->encoder = (int32_t) (BYTES_TO_UINT32(buf[CP_DATA1+10], buf[CP_DATA1+11], \
										buf[CP_DATA1+12], buf[CP_DATA1+13]));

			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+14], buf[CP_DATA1+15]));

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

//Transmission of a CTRL_SPECIAL_3 command: Current controller tuning
//Arguments are only for data that the user will change at runtime.
uint32_t tx_cmd_ctrl_special_3(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								int16_t i_kp, int16_t i_ki, int16_t i_kd, int16_t w_curr)
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

		buf[CP_CMD1] = CMD_R(CMD_SPECIAL_3);

		//Arguments:
		uint16_to_bytes((uint16_t)i_kp, &tmp0, &tmp1);
		buf[CP_DATA1 + 0] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)i_ki, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)i_kd, &tmp0, &tmp1);
		buf[CP_DATA1 + 4] = tmp0;
		buf[CP_DATA1 + 5] = tmp1;
		uint16_to_bytes((uint16_t)w_curr, &tmp0, &tmp1);
		buf[CP_DATA1 + 6] = tmp0;
		buf[CP_DATA1 + 7] = tmp1;


		bytes = CP_DATA1 + 8;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply

		buf[CP_CMD1] = CMD_W(CMD_SPECIAL_3);

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Arguments:
		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
		buf[CP_DATA1 + 0] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;
		uint32_to_bytes((uint32_t)ctrl.current.error, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		buf[CP_DATA1 + 4] = tmp2;
		buf[CP_DATA1 + 5] = tmp3;
		uint32_to_bytes((uint32_t)ctrl.current.error_sum, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 6] = tmp0;
		buf[CP_DATA1 + 7] = tmp1;
		buf[CP_DATA1 + 8] = tmp2;
		buf[CP_DATA1 + 9] = tmp3;
		uint16_to_bytes((uint16_t)ctrl.pwm, &tmp0, &tmp1);	//ToDo add to structure
		buf[CP_DATA1 + 10] = tmp0;
		buf[CP_DATA1 + 11] = tmp1;

		bytes = CP_DATA1 + 12;     //Bytes is always last+1

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

//Reception of a CMD_SPECIAL_3 command
void rx_cmd_special_3(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_kp = 0, tmp_ki = 0, tmp_kd = 0, tmp_current = 0;

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

		//Decode its data:
		//===============

		//Current gains:
		if(ctrl.active_ctrl == CTRL_CURRENT)
		{
			//Gains:
			tmp_kp = BYTES_TO_UINT16(buf[CP_DATA1 + 0], buf[CP_DATA1 + 1]);
			ctrl.current.gain.I_KP = tmp_kp;
			tmp_ki = BYTES_TO_UINT16(buf[CP_DATA1 + 2], buf[CP_DATA1 + 3]);
			ctrl.current.gain.I_KI = tmp_ki;
			tmp_kd = BYTES_TO_UINT16(buf[CP_DATA1 + 4], buf[CP_DATA1 + 5]);
			ctrl.current.gain.I_KD = tmp_kd;

			//Setpoint:
			tmp_current = (int16_t)BYTES_TO_UINT16(buf[CP_DATA1 + 6], buf[CP_DATA1 + 7]);
			ctrl.current.setpoint_val = tmp_current;
		}

		//Generate the reply:
		//===================

		numb = tx_cmd_ctrl_special_3(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, \
									PAYLOAD_BUF_LEN, 0, 0, 0, 0);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485_1, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//(for now, send it)
		rs485_puts(comm_str_485_1, numb);

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

			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+0], buf[CP_DATA1+1]));

			//ToDo decode and store errors

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

//=============

//Transmission of a CTRL_SPECIAL_4 command: Plan <> Manage, Dual ShuoBot Exo
//Special4 works in pair with Special1
//Arguments are only for data that the user will change at runtime.
//controller_w (Write New Controller): KEEP/CHANGE
//controller (New controller): ignored if ctrl_w == KEEP
//encoder_w (Write New Encoder value): KEEP/CHANGE
//encoder_cnt (New encoder count): ignored if encoder_w == KEEP
//current: current controller setpoint
uint32_t tx_cmd_ctrl_special_4(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t controller_w1, uint8_t controller1, uint8_t encoder_w1, int32_t encoder1, \
								int16_t current1, int16_t open_spd1, \
								uint8_t controller_w2, uint8_t controller2, uint8_t encoder_w2, int32_t encoder2, \
								int16_t current2, int16_t open_spd2)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	#if(defined BOARD_TYPE_FLEXSEA_MANAGE)

	//Structure pointer. Points to exec1 by default.
	struct execute_s *exec_s_ptr = &exec1;

	#endif	//(defined BOARD_TYPE_FLEXSEA_MANAGE)

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[CP_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		//In that case Read also includes a bunch of writing. We keep the Read keyword as
		//it will get us a reply.

		buf[CP_CMD1] = CMD_R(CMD_SPECIAL_4);

		//Arguments:
		buf[CP_DATA1 + 0] = controller_w1;
		buf[CP_DATA1 + 1] = controller1;
		uint16_to_bytes((uint16_t)current1, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		buf[CP_DATA1 + 4] = encoder_w1;
		uint32_to_bytes((uint32_t)encoder1, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 5] = tmp0;
		buf[CP_DATA1 + 6] = tmp1;
		buf[CP_DATA1 + 7] = tmp2;
		buf[CP_DATA1 + 8] = tmp3;
		uint16_to_bytes((uint16_t)open_spd1, &tmp0, &tmp1);
		buf[CP_DATA1 + 9] = tmp0;
		buf[CP_DATA1 + 10] = tmp1;

		buf[CP_DATA1 + 11] = controller_w2;
		buf[CP_DATA1 + 12] = controller2;
		uint16_to_bytes((uint16_t)current2, &tmp0, &tmp1);
		buf[CP_DATA1 + 13] = tmp0;
		buf[CP_DATA1 + 14] = tmp1;
		buf[CP_DATA1 + 15] = encoder_w2;
		uint32_to_bytes((uint32_t)encoder2, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 16] = tmp0;
		buf[CP_DATA1 + 17] = tmp1;
		buf[CP_DATA1 + 18] = tmp2;
		buf[CP_DATA1 + 19] = tmp3;
		uint16_to_bytes((uint16_t)open_spd2, &tmp0, &tmp1);
		buf[CP_DATA1 + 20] = tmp0;
		buf[CP_DATA1 + 21] = tmp1;

		bytes = CP_DATA1 + 22;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply

		buf[CP_CMD1] = CMD_W(CMD_SPECIAL_4);

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//Arguments - Execute #1:
		exec_s_ptr = &exec1;

		uint16_to_bytes((uint16_t)exec_s_ptr->imu.x, &tmp0, &tmp1);
		buf[CP_DATA1] = tmp0;
		buf[CP_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)exec_s_ptr->imu.y, &tmp0, &tmp1);
		buf[CP_DATA1 + 2] = tmp0;
		buf[CP_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)exec_s_ptr->imu.z, &tmp0, &tmp1);
		buf[CP_DATA1 + 4] = tmp0;
		buf[CP_DATA1 + 5] = tmp1;

		uint16_to_bytes(exec_s_ptr->strain, &tmp0, &tmp1);
		buf[CP_DATA1 + 6] = tmp0;
		buf[CP_DATA1 + 7] = tmp1;

		uint16_to_bytes(exec_s_ptr->analog[0], &tmp0, &tmp1);
		buf[CP_DATA1 + 8] = tmp0;
		buf[CP_DATA1 + 9] = tmp1;

		uint32_to_bytes((uint32_t)exec_s_ptr->encoder, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 10] = tmp0;
		buf[CP_DATA1 + 11] = tmp1;
		buf[CP_DATA1 + 12] = tmp2;
		buf[CP_DATA1 + 13] = tmp3;

		uint16_to_bytes((uint16_t)exec_s_ptr->current, &tmp0, &tmp1);
		buf[CP_DATA1 + 14] = tmp0;
		buf[CP_DATA1 + 15] = tmp1;

		//Arguments - Execute #2:
		exec_s_ptr = &exec2;

		uint16_to_bytes((uint16_t)exec_s_ptr->imu.x, &tmp0, &tmp1);
		buf[CP_DATA1 + 16] = tmp0;
		buf[CP_DATA1 + 17] = tmp1;
		uint16_to_bytes((uint16_t)exec_s_ptr->imu.y, &tmp0, &tmp1);
		buf[CP_DATA1 + 18] = tmp0;
		buf[CP_DATA1 + 19] = tmp1;
		uint16_to_bytes((uint16_t)exec_s_ptr->imu.z, &tmp0, &tmp1);
		buf[CP_DATA1 + 20] = tmp0;
		buf[CP_DATA1 + 21] = tmp1;

		uint16_to_bytes(exec_s_ptr->strain, &tmp0, &tmp1);
		buf[CP_DATA1 + 22] = tmp0;
		buf[CP_DATA1 + 23] = tmp1;

		uint16_to_bytes(exec_s_ptr->analog[0], &tmp0, &tmp1);
		buf[CP_DATA1 + 24] = tmp0;
		buf[CP_DATA1 + 25] = tmp1;

		uint32_to_bytes((uint32_t)exec_s_ptr->encoder, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[CP_DATA1 + 26] = tmp0;
		buf[CP_DATA1 + 27] = tmp1;
		buf[CP_DATA1 + 28] = tmp2;
		buf[CP_DATA1 + 29] = tmp3;

		uint16_to_bytes((uint16_t)exec_s_ptr->current, &tmp0, &tmp1);
		buf[CP_DATA1 + 30] = tmp0;
		buf[CP_DATA1 + 31] = tmp1;

		bytes = CP_DATA1 + 32;     //Bytes is always last+1

		#else

		bytes = 0;

		#endif	//BOARD_TYPE_FLEXSEA_MANAGE
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CMD_SPECIAL_4 command
void rx_cmd_special_4(uint8_t *buf)
{
	uint32_t numb = 0;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Structure pointer.
	struct execute_s *exec_s_ptr;
	struct spc4_s *spc4_s_ptr;

	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	if(IS_CMD_RW(buf[CP_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		//No code (yet), you shouldn't be here...
		flexsea_error(SE_CMD_NOT_PROGRAMMED);
		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//Decode its data:
		//===============

		spc4_s_ptr = &spc4_ex1;
		spc4_s_ptr->ctrl_w = buf[CP_DATA1 + 0];
		spc4_s_ptr->ctrl = buf[CP_DATA1 + 1];
		spc4_s_ptr->current = BYTES_TO_UINT16(buf[CP_DATA1 + 2], buf[CP_DATA1 + 3]);
		spc4_s_ptr->encoder_w = buf[CP_DATA1 + 4];
		spc4_s_ptr->encoder = (int32_t)BYTES_TO_UINT32(buf[CP_DATA1 + 5], buf[CP_DATA1 + 6], \
				buf[CP_DATA1 + 7], buf[CP_DATA1 + 8]);
		spc4_s_ptr->open_spd = BYTES_TO_UINT16(buf[CP_DATA1 + 9], buf[CP_DATA1 + 10]);

		spc4_s_ptr = &spc4_ex2;
		spc4_s_ptr->ctrl_w = buf[CP_DATA1 + 11];
		spc4_s_ptr->ctrl = buf[CP_DATA1 + 12];
		spc4_s_ptr->current = BYTES_TO_UINT16(buf[CP_DATA1 + 13], buf[CP_DATA1 + 14]);
		spc4_s_ptr->encoder_w = buf[CP_DATA1 + 15];
		spc4_s_ptr->encoder = (int32_t)BYTES_TO_UINT32(buf[CP_DATA1 + 16], buf[CP_DATA1 + 17], \
				buf[CP_DATA1 + 18], buf[CP_DATA1 + 19]);
		spc4_s_ptr->open_spd = BYTES_TO_UINT16(buf[CP_DATA1 + 20], buf[CP_DATA1 + 21]);

		//Generate the reply:
		//===================

		numb = tx_cmd_ctrl_special_4(buf[CP_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, 0, 0, \
									KEEP, 0, KEEP, 0, 0, 0);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA
		//(for now, send it)

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

			#if(defined BOARD_TYPE_FLEXSEA_PLAN)

			//Store values:

			exec_s_ptr = &exec1;
			exec_s_ptr->imu.x = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+0], buf[CP_DATA1+1]));
			exec_s_ptr->imu.y = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
			exec_s_ptr->imu.z = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+4], buf[CP_DATA1+5]));

			exec_s_ptr->strain = (BYTES_TO_UINT16(buf[CP_DATA1+6], buf[CP_DATA1+7]));
			exec_s_ptr->analog[0] = (BYTES_TO_UINT16(buf[CP_DATA1+8], buf[CP_DATA1+9]));

			exec_s_ptr->encoder = (int32_t) (BYTES_TO_UINT32(buf[CP_DATA1+10], buf[CP_DATA1+11], \
										buf[CP_DATA1+12], buf[CP_DATA1+13]));

			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+14], buf[CP_DATA1+15]));

			exec_s_ptr = &exec2;
			exec_s_ptr->imu.x = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+16], buf[CP_DATA1+17]));
			exec_s_ptr->imu.y = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+18], buf[CP_DATA1+19]));
			exec_s_ptr->imu.z = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+20], buf[CP_DATA1+21]));

			exec_s_ptr->strain = (BYTES_TO_UINT16(buf[CP_DATA1+22], buf[CP_DATA1+23]));
			exec_s_ptr->analog[0] = (BYTES_TO_UINT16(buf[CP_DATA1+24], buf[CP_DATA1+25]));

			exec_s_ptr->encoder = (int32_t) (BYTES_TO_UINT32(buf[CP_DATA1+26], buf[CP_DATA1+27], \
										buf[CP_DATA1+28], buf[CP_DATA1+29]));

			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+30], buf[CP_DATA1+31]));

			#ifdef MULTIPLE_COMMANDS
			//ToDo interface with Python

			#endif

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE
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
