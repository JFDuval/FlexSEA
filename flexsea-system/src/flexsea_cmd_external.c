//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// flexsea_cmd_external: External/Expansion connector
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

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

//****************************************************************************
// Function(s)
//****************************************************************************

/*
//Transmission of a DIGITAL_IN command
uint32_t tx_cmd_digital_in(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_DIGITAL_IN);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply
	
		buf[P_CMD1] = CMD_W(CMD_DIGITAL_IN);

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		ToDo!
		
		//Arguments:
		buf[P_DATA1 + 0] = read_digital_inputs();
		

		bytes = P_DATA1 + 1;     //Bytes is always last+1

		#else

		bytes = 0;

		#endif	//BOARD_TYPE_FLEXSEA_APPLICATION
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a DIGITAL_IN command
void rx_cmd_digital_in(uint8_t *buf)
{
	uint32_t numb = 0;
	int8_t tmp_val1 = 0, tmp_val2 = 0, tmp_val3 = 0, tmp_val4 = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

        #ifdef BOARD_TYPE_FLEXSEA_APPLICATION
		
		numb = tx_cmd_digital_in(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		//numb = COMM_STR_BUF_LEN;    //Fixed length for now
		flexsea_send_serial_master(0, comm_str_485, numb+1);
		
		//ToDo: the reply should be managed elsewhere!
		
		#endif	//BOARD_TYPE_FLEXSEA_APPLICATION
		
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		//[...]

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request
			
			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			
			ToDo!
				
			//As a test, we use Interface to read from Application
			tmp_val1 = buf[P_DATA1 + 0];
			
				
			#endif //BOARD_TYPE_FLEXSEA_INTERFACE
		}
		else
		{
			//Master is writing a value to this board
			
			//Can't write to digital inputs - nop()

		}
	}
}

//Transmission of an ANALOG_IN command
uint32_t tx_cmd_analog_in(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len)
{
	uint32_t bytes = 0;
	uint8_t tmp0 = 0, tmp1 = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_ANALOG_IN);

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply
	
		buf[P_CMD1] = CMD_W(CMD_ANALOG_IN);

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
		ToDo!

		//Arguments:
		uint16_to_bytes((uint16_t)adc_res[0], &tmp0, &tmp1);
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)adc_res[1], &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)adc_res[2], &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;
		uint16_to_bytes((uint16_t)adc_res[3], &tmp0, &tmp1);
		buf[P_DATA1 + 6] = tmp0;
		buf[P_DATA1 + 7] = tmp1;

		bytes = P_DATA1 + 8;     //Bytes is always last+1

		#else

		bytes = 0;

		#endif	//BOARD_TYPE_FLEXSEA_APPLICATION
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of an ANALOG_IN command
void rx_cmd_analog_in(uint8_t *buf)
{
	uint32_t numb = 0;
	int16_t tmp_val1 = 0, tmp_val2 = 0, tmp_val3 = 0, tmp_val4 = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master, prepare a reply:

        #ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
		numb = tx_cmd_analog_in(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		//numb = COMM_STR_BUF_LEN;    //Fixed length for now
		flexsea_send_serial_master(0, comm_str_485, numb+1);
		
		//ToDo: the reply should be managed elsewhere!
		
		#endif	//BOARD_TYPE_FLEXSEA_APPLICATION
		
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		//Decode data:
		//[...]

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request
			
			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
			
			ToDo!
				
			//As a test, we use Interface to read from Application
			tmp_val1 = (int16)BYTES_TO_UINT16(buf[P_DATA1 + 0], buf[P_DATA1 + 1]);
			tmp_val2 = (int16)BYTES_TO_UINT16(buf[P_DATA1 + 2], buf[P_DATA1 + 3]);
			tmp_val3 = (int16)BYTES_TO_UINT16(buf[P_DATA1 + 4], buf[P_DATA1 + 5]);
			tmp_val4 = (int16)BYTES_TO_UINT16(buf[P_DATA1 + 6], buf[P_DATA1 + 7]);
			sdata_app_adc_res[0] = tmp_val1;
			sdata_app_adc_res[1] = tmp_val2;
			sdata_app_adc_res[2] = tmp_val3;
			sdata_app_adc_res[3] = tmp_val4;
			
				
			#endif //BOARD_TYPE_FLEXSEA_INTERFACE
		}
		else
		{
			//Master is writing a value to this board
			
			//Can't write to digital inputs - nop()

		}
	}
}
*/

//Transmission of a PWRO command
uint32_t tx_cmd_exp_pwro(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t pwro_pwm)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		//No arguments needed to read the clutch state

		//Arguments:
		//...

		bytes = P_DATA1 + 0;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply

		buf[P_CMD1] = CMD_W(CMD_PWRO);

		//Arguments:
		buf[P_DATA1 + 0] = pwro_pwm;

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

//Reception of a PWRO command
void rx_cmd_exp_clutch(uint8_t *buf)
{
	uint32_t numb = 0;

	#if((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	//Structure pointer. Points to exec1 by default.
	struct execute_s *exec_s_ptr = &exec1;

	//Point to the appropriate structure:
	if(buf[P_XID] == FLEXSEA_EXECUTE_1)
	{
		exec_s_ptr = &exec1;
	}
	else if(buf[P_XID] == FLEXSEA_EXECUTE_2)
	{
		exec_s_ptr = &exec2;
	}

	#endif	//((defined BOARD_TYPE_FLEXSEA_MANAGE) || (defined BOARD_TYPE_FLEXSEA_PLAN))

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		//===================

		numb = tx_cmd_exp_pwro(buf[P_XID], CMD_WRITE, tmp_payload_xmit, \
									PAYLOAD_BUF_LEN, read_pwro());
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		numb = COMM_STR_BUF_LEN;	//Fixed length for now to accomodate the DMA

		//Notify the code that a buffer is ready to be transmitted:
		//xmit_flag_1 = 1;
		
		//(for now, send it)
		rs485_puts(comm_str_485, (numb));

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

			exec_s_ptr->pwro = buf[P_DATA1+0];

			#endif	//BOARD_TYPE_FLEXSEA_MANAGE

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			pwro_output(buf[P_DATA1+0]);

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

#ifdef __cplusplus
}
#endif
