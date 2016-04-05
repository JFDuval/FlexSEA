//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// flexsea_cmd_control: commands specific to the motor & control
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea_system.h"
#include "../inc/flexsea_cmd_control.h"

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

//Transmission of a CTRL_MODE command
uint32_t tx_cmd_ctrl_mode(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t ctrl)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_MODE);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_MODE);

		//Arguments:
		buf[P_DATA1] = ctrl;

		bytes = P_DATA1 + 1;     //Bytes is always last+1
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

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_mode(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, ctrl.active_ctrl);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		controller = buf[P_DATA1];
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

//Transmission of a CTRL_I command
uint32_t tx_cmd_ctrl_i(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t wanted, int16_t measured)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_I);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_I);

		//Arguments:
		uint16_to_bytes(measured, &tmp0, &tmp1);
		buf[P_DATA1] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes(wanted, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;

		bytes = P_DATA1 + 4;     //Bytes is always last+1
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

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_i(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.current.actual_val, ctrl.current.setpoint_val);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485, (numb));

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_measured_current = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1], buf[P_DATA1+1]));
		tmp_wanted_current = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+2], buf[P_DATA1+3]));
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

//Transmission of a CTRL_O command
uint32_t tx_cmd_ctrl_o(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t open_spd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_O);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_O);

		//Arguments:
		uint16_to_bytes(open_spd, &tmp0, &tmp1);
		buf[P_DATA1] = tmp0;
		buf[P_DATA1 + 1] = tmp1;

		bytes = P_DATA1 + 2;     //Bytes is always last+1
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

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_o(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.pwm);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_open_spd = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1], buf[P_DATA1+1]));
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

//Transmission of a CTRL_P command
uint32_t tx_cmd_ctrl_p(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int32_t pos, int32_t posi, int32_t posf, int32_t spdm, int32_t acc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_P);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_P);

		//Arguments:
		uint32_to_bytes((uint32_t)pos, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		buf[P_DATA1 + 2] = tmp2;
		buf[P_DATA1 + 3] = tmp3;
		uint32_to_bytes((uint32_t)posi, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;
		buf[P_DATA1 + 6] = tmp2;
		buf[P_DATA1 + 7] = tmp3;
		uint32_to_bytes((uint32_t)posf, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 8] = tmp0;
		buf[P_DATA1 + 9] = tmp1;
		buf[P_DATA1 + 10] = tmp2;
		buf[P_DATA1 + 11] = tmp3;
		uint32_to_bytes((uint32_t)spdm, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 12] = tmp0;
		buf[P_DATA1 + 13] = tmp1;
		buf[P_DATA1 + 14] = tmp2;
		buf[P_DATA1 + 15] = tmp3;
		uint32_to_bytes((uint32_t)acc, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 16] = tmp0;
		buf[P_DATA1 + 17] = tmp1;
		buf[P_DATA1 + 18] = tmp2;
		buf[P_DATA1 + 19] = tmp3;

		bytes = P_DATA1 + 20;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_P command
void rx_cmd_ctrl_p(uint8_t *buf)
{
	uint32_t numb = 0;
	int32_t tmp_pos = 0, tmp_posi = 0, tmp_posf = 0, tmp_spdm = 0, tmp_acc = 0;
	int16_t tmp_z_k = 0, tmp_z_b = 0, tmp_z_i = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_p(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.position.pos, ctrl.position.posi, ctrl.position.posf, ctrl.position.spdm, ctrl.position.acc);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_pos = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 0], buf[P_DATA1 + 1], buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_posi = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 4], buf[P_DATA1 + 5], buf[P_DATA1 + 6], buf[P_DATA1 + 7]));
		tmp_posf = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 8], buf[P_DATA1 + 9], buf[P_DATA1 + 10], buf[P_DATA1 + 11]));
		tmp_spdm = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 12], buf[P_DATA1 + 13], buf[P_DATA1 + 14], buf[P_DATA1 + 15]));
		tmp_acc = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1 + 16], buf[P_DATA1 + 17], buf[P_DATA1 + 18], buf[P_DATA1 + 19]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.position.pos = tmp_pos;
			exec1.ctrl.position.posi = tmp_posi;
			exec1.ctrl.position.posf = tmp_posf;
			exec1.ctrl.position.spdm = tmp_spdm;
			exec1.ctrl.position.acc = tmp_acc;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			//ctrl.position.pos = tmp_pos;
			ctrl.position.posi = tmp_posi;
			ctrl.position.posf = tmp_posf;
			ctrl.position.spdm = tmp_spdm;
			ctrl.position.acc = tmp_acc;

			if(ctrl.active_ctrl == CTRL_POSITION)
			{
				steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);
			}
			else if(ctrl.active_ctrl == CTRL_IMPEDANCE)
			{
				//Backup gains
				tmp_z_k = ctrl.impedance.gain.Z_K;
				tmp_z_b = ctrl.impedance.gain.Z_B;
				tmp_z_i = ctrl.impedance.gain.Z_I;

				//Zero them
				ctrl.impedance.gain.Z_K = 0;
				ctrl.impedance.gain.Z_B = 0;
				ctrl.impedance.gain.Z_I = 0;

				//New trajectory
				steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);

				//Restore gains
				ctrl.impedance.gain.Z_K = tmp_z_k;
				ctrl.impedance.gain.Z_B = tmp_z_b;
				ctrl.impedance.gain.Z_I = tmp_z_i;
			}


			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmission of a CTRL_I_G command
uint32_t tx_cmd_ctrl_i_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_I_G);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_I_G);

		//Arguments:
		uint16_to_bytes((uint16_t)kp, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)ki, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)kd, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;


		bytes = P_DATA1 + 6;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_I_G command
void rx_cmd_ctrl_i_g(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_kp = 0, tmp_ki = 0, tmp_kd = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_i_g(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.current.gain.I_KP, ctrl.current.gain.I_KI, ctrl.current.gain.I_KD);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_kp = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]));
		tmp_ki = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_kd = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.current.gain.I_KP = tmp_kp;
			exec1.ctrl.current.gain.I_KI = tmp_ki;
			exec1.ctrl.current.gain.I_KD = tmp_kd;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			ctrl.current.gain.I_KP = tmp_kp;
			ctrl.current.gain.I_KI = tmp_ki;
			ctrl.current.gain.I_KD = tmp_kd;
			//ToDo: do we need to call something?

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmission of a CTRL_P_G command
uint32_t tx_cmd_ctrl_p_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_P_G);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_P_G);

		//Arguments:
		uint16_to_bytes((uint16_t)kp, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)ki, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)kd, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;


		bytes = P_DATA1 + 6;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_P_G command
void rx_cmd_ctrl_p_g(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_kp = 0, tmp_ki = 0, tmp_kd = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_p_g(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.position.gain.P_KP, ctrl.position.gain.P_KI, ctrl.position.gain.P_KD);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_kp = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]));
		tmp_ki = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_kd = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.position.gain.I_KP = tmp_kp;
			exec1.ctrl.position.gain.I_KI = tmp_ki;
			exec1.ctrl.position.gain.I_KD = tmp_kd;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			ctrl.position.gain.P_KP = tmp_kp;
			ctrl.position.gain.P_KI = tmp_ki;
			ctrl.position.gain.P_KD = tmp_kd;
			//ToDo: do we need to call something?

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmission of a CTRL_Z_G command
uint32_t tx_cmd_ctrl_z_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t zk, int16_t zb, int16_t zi)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_CTRL_Z_G);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_CTRL_Z_G);

		//Arguments:
		uint16_to_bytes((uint16_t)zk, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)zb, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)zi, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;


		bytes = P_DATA1 + 6;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a CTRL_Z_G command
void rx_cmd_ctrl_z_g(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_zk = 0, tmp_zb = 0, tmp_zi = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_ctrl_z_g(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
			ctrl.impedance.gain.Z_K, ctrl.impedance.gain.Z_B, ctrl.impedance.gain.Z_I);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		tmp_zk = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]));
		tmp_zb = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]));
		tmp_zi = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]));
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			//No code (yet), you shouldn't be here...
			flexsea_error(SE_CMD_NOT_PROGRAMMED);
			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store value:
			exec1.ctrl.impedance.gain.Z_K = tmp_zk;
			exec1.ctrl.impedance.gain.Z_B = tmp_zb;
			exec1.ctrl.impedance.gain.Z_I = tmp_zi;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Store value:
			ctrl.impedance.gain.Z_K = tmp_zk;
			ctrl.impedance.gain.Z_B = tmp_zb;
			ctrl.impedance.gain.Z_I = tmp_zi;
			//ToDo: do we need to call something?

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

#ifdef __cplusplus
}
#endif
