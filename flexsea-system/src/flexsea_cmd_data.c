//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// flexsea_cmd_data: Data Commands
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
#include "../inc/flexsea_cmd_data.h"

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

//Transmission of an ACQUI command
uint32_t tx_cmd_data_acqui(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t acqui)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_ACQUI);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_ACQUI);

		//Arguments:
		buf[P_DATA1] = acqui;

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

//Reception of an ACQUI command
void rx_cmd_data_acqui(uint8_t *buf)
{
	uint8_t numb = 0, sampling = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_data_acqui(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);	//Returns 0 for now
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;

		//(for now, send it)
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//Generate the reply:
		numb = tx_cmd_data_acqui(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);	//Returns 0 for now
		numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA
		//(for now, send it)

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		sampling = buf[P_DATA1];
		//ToDo store that value somewhere useful

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#if(defined BOARD_TYPE_FLEXSEA_PLAN)

			//Store value:
			manag1.sampling = sampling;

			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Nothing to do for now

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE

			//ToDo this isn't really clean:
			slaves_485_1.mode = sampling;
			slaves_485_2.mode = sampling;

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmission of a READ_ALL command
uint32_t tx_cmd_data_read_all(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_READ_ALL);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply
		
		buf[P_CMD1] = CMD_W(CMD_READ_ALL);
		
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
		
		uint16_to_bytes((uint16_t)imu.accel.x, &tmp0, &tmp1);
		buf[P_DATA1 + 6] = tmp0;
		buf[P_DATA1 + 7] = tmp1;
		uint16_to_bytes((uint16_t)imu.accel.y, &tmp0, &tmp1);
		buf[P_DATA1 + 8] = tmp0;
		buf[P_DATA1 + 9] = tmp1;
		uint16_to_bytes((uint16_t)imu.accel.z, &tmp0, &tmp1);
		buf[P_DATA1 + 10] = tmp0;
		buf[P_DATA1 + 11] = tmp1;		
		
		uint16_to_bytes(strain_read(), &tmp0, &tmp1);
		buf[P_DATA1 + 12] = tmp0;
		buf[P_DATA1 + 13] = tmp1;
		
		uint16_to_bytes(read_analog(0), &tmp0, &tmp1);
		buf[P_DATA1 + 14] = tmp0;
		buf[P_DATA1 + 15] = tmp1;
		
		//uint32_to_bytes((uint32_t)encoder_read(), &tmp0, &tmp1, &tmp2, &tmp3);
		uint32_to_bytes((uint32_t)mot_cont_angle, &tmp0, &tmp1, &tmp2, &tmp3);
		buf[P_DATA1 + 16] = tmp0;
		buf[P_DATA1 + 17] = tmp1;
		buf[P_DATA1 + 18] = tmp2;
		buf[P_DATA1 + 19] = tmp3;
		
		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
		buf[P_DATA1 + 20] = tmp0;
		buf[P_DATA1 + 21] = tmp1;

		buf[P_DATA1 + 22] = safety_cop.v_vb;
		buf[P_DATA1 + 23] = safety_cop.v_vg;
		buf[P_DATA1 + 24] = safety_cop.temperature;
		buf[P_DATA1 + 25] = safety_cop.status1;
		buf[P_DATA1 + 26] = safety_cop.status2;

		bytes = P_DATA1 + 27;     //Bytes is always last+1
		
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

//Reception of a READ_ALL command
void rx_cmd_data_read_all(uint8_t *buf)
{
	uint8_t numb = 0, sampling = 0;

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
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_data_read_all(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//Delayed response:
		rs485_reply_ready(comm_str_485, (numb));
		
		#ifdef USE_USB
		usb_puts(comm_str_485, (numb));
		#endif

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//ToDo

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		//...

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store values:
				
			exec_s_ptr->gyro.x = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+0], buf[P_DATA1+1]));
			exec_s_ptr->gyro.y = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+2], buf[P_DATA1+3]));
			exec_s_ptr->gyro.z = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+4], buf[P_DATA1+5]));
			
			exec_s_ptr->accel.x = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+6], buf[P_DATA1+7]));
			exec_s_ptr->accel.y = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+8], buf[P_DATA1+9]));
			exec_s_ptr->accel.z = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+10], buf[P_DATA1+11]));
			
			exec_s_ptr->strain = (BYTES_TO_UINT16(buf[P_DATA1+12], buf[P_DATA1+13]));
			exec_s_ptr->analog[0] = (BYTES_TO_UINT16(buf[P_DATA1+14], buf[P_DATA1+15]));
	
			exec_s_ptr->encoder = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1+16], buf[P_DATA1+17], \
										buf[P_DATA1+18], buf[P_DATA1+19]));
			
			exec_s_ptr->current = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+20], buf[P_DATA1+21]));

			exec_s_ptr->volt_batt = buf[P_DATA1+22];
			exec_s_ptr->volt_int = buf[P_DATA1+23];
			exec_s_ptr->temp = buf[P_DATA1+24];
			exec_s_ptr->status1 = buf[P_DATA1+25];
			exec_s_ptr->status2 = buf[P_DATA1+26];

			#ifdef MULTIPLE_COMMANDS
			//To interface with Python:
			printf("[%i,%i,%i,%i,%i,%i,%i]\n", exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
					exec1.strain, exec1.analog[0]);
			#endif
			
			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Nothing to do for now

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE

			//Nothing to do for now

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

//Transmission of a READ_ALL_RICNU command
uint32_t tx_cmd_data_read_all_ricnu(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_READ_ALL_RICNU);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply
		
		buf[P_CMD1] = CMD_W(CMD_READ_ALL_RICNU);
		
		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Arguments:
		uint16_to_bytes((uint16_t)imu.gyro.x, &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)imu.gyro.y, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)imu.gyro.z, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;
		
		uint16_to_bytes((uint16_t)imu.accel.x, &tmp0, &tmp1);
		buf[P_DATA1 + 6] = tmp0;
		buf[P_DATA1 + 7] = tmp1;
		uint16_to_bytes((uint16_t)imu.accel.y, &tmp0, &tmp1);
		buf[P_DATA1 + 8] = tmp0;
		buf[P_DATA1 + 9] = tmp1;
		uint16_to_bytes((uint16_t)imu.accel.z, &tmp0, &tmp1);
		buf[P_DATA1 + 10] = tmp0;
		buf[P_DATA1 + 11] = tmp1;		
		
		uint16_to_bytes((uint16_t)as5047_angle, &tmp0, &tmp1);
		buf[P_DATA1 + 12] = tmp0;
		buf[P_DATA1 + 13] = tmp1;
		
		uint16_to_bytes((uint16_t)as5048b_angle, &tmp0, &tmp1);
		buf[P_DATA1 + 14] = tmp0;
		buf[P_DATA1 + 15] = tmp1;

		uint16_to_bytes((uint16_t)ctrl.current.actual_val, &tmp0, &tmp1);
		buf[P_DATA1 + 16] = tmp0;
		buf[P_DATA1 + 17] = tmp1;

		buf[P_DATA1 + 18] = safety_cop.v_vb;
		
		uint16_to_bytes((uint16_t)ext_strain[0], &tmp0, &tmp1);
		buf[P_DATA1 + 19] = tmp0;
		buf[P_DATA1 + 20] = tmp1;
		uint16_to_bytes((uint16_t)ext_strain[1], &tmp0, &tmp1);
		buf[P_DATA1 + 21] = tmp0;
		buf[P_DATA1 + 22] = tmp1;
		uint16_to_bytes((uint16_t)ext_strain[2], &tmp0, &tmp1);
		buf[P_DATA1 + 23] = tmp0;
		buf[P_DATA1 + 24] = tmp1;
		uint16_to_bytes((uint16_t)ext_strain[3], &tmp0, &tmp1);
		buf[P_DATA1 + 25] = tmp0;
		buf[P_DATA1 + 26] = tmp1;
		uint16_to_bytes((uint16_t)ext_strain[4], &tmp0, &tmp1);
		buf[P_DATA1 + 27] = tmp0;
		buf[P_DATA1 + 28] = tmp1;
		uint16_to_bytes((uint16_t)ext_strain[5], &tmp0, &tmp1);
		buf[P_DATA1 + 29] = tmp0;
		buf[P_DATA1 + 30] = tmp1;
		
		//ToDo add user variables
		
		bytes = P_DATA1 + 31;     //Bytes is always last+1
		
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

//Reception of a READ_ALL_RICNU command
void rx_cmd_data_read_all_ricnu(uint8_t *buf)
{
	uint8_t numb = 0, sampling = 0;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Structure pointer. Points to ricnu_1 by default.
	//struct execute_s *exec_s_ptr;
	struct ricnu_s *ricnu_s_ptr = &ricnu_1;


	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
	
	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		numb = tx_cmd_data_read_all_ricnu(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//Delayed response:
		rs485_reply_ready(comm_str_485, (numb));
		
		#ifdef USE_USB
		usb_puts(comm_str_485, (numb));
		#endif

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//ToDo

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		//...

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

			//Store values:
				
			ricnu_s_ptr->ex.gyro.x = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+0], buf[P_DATA1+1]));
			ricnu_s_ptr->ex.gyro.y = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+2], buf[P_DATA1+3]));
			ricnu_s_ptr->ex.gyro.z = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+4], buf[P_DATA1+5]));
			
			ricnu_s_ptr->ex.accel.x = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+6], buf[P_DATA1+7]));
			ricnu_s_ptr->ex.accel.y = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+8], buf[P_DATA1+9]));
			ricnu_s_ptr->ex.accel.z = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+10], buf[P_DATA1+11]));
			
			ricnu_s_ptr->enc_mot = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+12], buf[P_DATA1+13]));
			ricnu_s_ptr->enc_joint = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+14], buf[P_DATA1+15]));
			
			ricnu_s_ptr->ex.current = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+16], buf[P_DATA1+17]));
			ricnu_s_ptr->ex.volt_batt = buf[P_DATA1+18];
			
			ricnu_s_ptr->ext_strain[0] = (BYTES_TO_UINT16(buf[P_DATA1+19], buf[P_DATA1+20]));
			ricnu_s_ptr->ext_strain[1] = (BYTES_TO_UINT16(buf[P_DATA1+21], buf[P_DATA1+22]));
			ricnu_s_ptr->ext_strain[2] = (BYTES_TO_UINT16(buf[P_DATA1+23], buf[P_DATA1+24]));
			ricnu_s_ptr->ext_strain[3] = (BYTES_TO_UINT16(buf[P_DATA1+25], buf[P_DATA1+26]));
			ricnu_s_ptr->ext_strain[4] = (BYTES_TO_UINT16(buf[P_DATA1+27], buf[P_DATA1+28]));
			ricnu_s_ptr->ext_strain[5] = (BYTES_TO_UINT16(buf[P_DATA1+29], buf[P_DATA1+30]));
		
			#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))
		}
		else
		{
			//Master is writing a value to this board 

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			//Nothing to do for now

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

			#ifdef BOARD_TYPE_FLEXSEA_MANAGE

			//Nothing to do for now

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		}
	}
}

#ifdef __cplusplus
}
#endif
