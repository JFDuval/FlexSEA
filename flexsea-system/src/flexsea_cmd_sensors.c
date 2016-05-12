//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// flexsea_cmd_sensors: commands specific sensors
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

//Strain Amplifier boards only:
#ifdef BOARD_TYPE_FLEXSEA_STRAIN_AMP
#include "main.h"
#endif	//BOARD_TYPE_FLEXSEA_STRAIN_AMP

//****************************************************************************
// Variable(s)
//****************************************************************************

//Will change this, but for now the payloads will be stored in:
unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Transmission of a SWITCH command: Read Manage's onboard switch
uint32_t tx_cmd_switch(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len)
{
	uint32_t bytes = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_SWITCH);

		//Arguments:
		//(none)

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		//In that case Write is only used for the Reply

		buf[P_CMD1] = CMD_W(CMD_SWITCH);

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//Arguments:
		buf[P_DATA1 + 0] = read_sw1();

		bytes = P_DATA1 + 1;     //Bytes is always last+1

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

//Reception of a CMD_SWITCH command
void rx_cmd_switch(uint8_t *buf)
{
	uint32_t numb = 0;
	uint8_t tmp_sw = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

		//Generate the reply:
		//===================

		numb = tx_cmd_switch(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
		numb = COMM_STR_BUF_LEN;    //Fixed length for now
		//(the SPI driver will grab comm_str_spi directly)
		//flexsea_send_serial_master(0, comm_str, numb);

		#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			printf("Received data\n");//ToDo remove
			manag1.sw1 = buf[P_DATA1];

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

		}
	}
}

//Transmission of an ENCODER command.
uint32_t tx_cmd_encoder(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int32_t enc)
{
	uint32_t bytes = 0;
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_ENCODER);

		//Arguments:
		//(none)

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_ENCODER);

		uint32_to_bytes((uint32_t)enc, &tmp0, &tmp1, &tmp2, &tmp3);

		//Arguments:
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		buf[P_DATA1 + 2] = tmp2;
		buf[P_DATA1 + 3] = tmp3;

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

//Reception of an ENCODER command
void rx_cmd_encoder(uint8_t *buf)
{
	uint32_t numb = 0;
	int32_t tmp = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		//===================

		numb = tx_cmd_encoder(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, encoder_read());
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		numb = COMM_STR_BUF_LEN;    //Fixed length for now
		rs485_puts(comm_str_485, numb);

		#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			tmp = (int32_t)BYTES_TO_UINT32(buf[P_DATA1], buf[P_DATA1+1], buf[P_DATA1+2], buf[P_DATA1+3]);

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			_USE_PRINTF("Encoder = %i.\n", tmp);

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			encoder_write(tmp);

			#endif

		}
	}
}

//Transmission of a STRAIN command.
//ToDo: add support for gains & offsets
uint32_t tx_cmd_strain(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len)
{
	uint32_t bytes = 0;
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

	//Fresh payload string:
	prepare_empty_payload(board_id, receiver, buf, len);

	//Command:
	buf[P_CMDS] = 1;                     //1 command in string

	if(cmd_type == CMD_READ)
	{
		buf[P_CMD1] = CMD_R(CMD_STRAIN);

		//Arguments:
		//(none)

		bytes = P_CMD1 + 1;     //Bytes is always last+1
	}
	else if(cmd_type == CMD_WRITE)
	{
		buf[P_CMD1] = CMD_W(CMD_STRAIN);

		//ToDo gains & offsets
		
		#ifdef BOARD_TYPE_FLEXSEA_STRAIN_AMP
			
		//Arguments:	
		uint16_to_bytes((uint16_t)strain[0].strain_filtered, &tmp0, &tmp1);		
		buf[P_DATA1 + 0] = tmp0;
		buf[P_DATA1 + 1] = tmp1;
		uint16_to_bytes((uint16_t)strain[1].strain_filtered, &tmp0, &tmp1);
		buf[P_DATA1 + 2] = tmp0;
		buf[P_DATA1 + 3] = tmp1;
		uint16_to_bytes((uint16_t)strain[2].strain_filtered, &tmp0, &tmp1);
		buf[P_DATA1 + 4] = tmp0;
		buf[P_DATA1 + 5] = tmp1;
		uint16_to_bytes((uint16_t)strain[3].strain_filtered, &tmp0, &tmp1);
		buf[P_DATA1 + 6] = tmp0;
		buf[P_DATA1 + 7] = tmp1;
		uint16_to_bytes((uint16_t)strain[4].strain_filtered, &tmp0, &tmp1);
		buf[P_DATA1 + 8] = tmp0;
		buf[P_DATA1 + 9] = tmp1;
		uint16_to_bytes((uint16_t)strain[5].strain_filtered, &tmp0, &tmp1);
		buf[P_DATA1 + 10] = tmp0;
		buf[P_DATA1 + 11] = tmp1;
		
		#endif 	//BOARD_TYPE_FLEXSEA_STRAIN_AMP

		bytes = P_DATA1 + 12;     //Bytes is always last+1
	}
	else
	{
		//Invalid
		flexsea_error(SE_INVALID_READ_TYPE);
		bytes = 0;
	}

	return bytes;
}

//Reception of a STRAIN command
void rx_cmd_strain(uint8_t *buf)
{
	uint32_t numb = 0;
	int32_t tmp = 0;

	if(IS_CMD_RW(buf[P_CMD1]) == READ)
	{
		//Received a Read command from our master.

		#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		//Generate the reply:
		//===================

		//ToDo...

		#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
		
		#ifdef BOARD_TYPE_FLEXSEA_STRAIN_AMP
			
		//Generate the reply:
		//===================

		numb = tx_cmd_strain(buf[P_XID], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN);
		numb = comm_gen_str(tmp_payload_xmit, comm_str_485, numb);
		numb = COMM_STR_BUF_LEN;    //Fixed length for now
		//rs485_puts(comm_str_485, numb);	
		
		#ifdef USE_USB
		usb_puts(comm_str_485, (numb));	
		#endif
			
		#endif 	//BOARD_TYPE_FLEXSEA_STRAIN_AMP
	}
	else if(IS_CMD_RW(buf[P_CMD1]) == WRITE)
	{
		//Two options: from Master of from slave (a read reply)

		if(sent_from_a_slave(buf))
		{
			//We received a reply to our read request

			strain[0].strain_filtered = (uint16_t)BYTES_TO_UINT16(buf[P_DATA1], buf[P_DATA1+1]);
			strain[1].strain_filtered = (uint16_t)BYTES_TO_UINT16(buf[P_DATA1+2], buf[P_DATA1+3]);
			strain[2].strain_filtered = (uint16_t)BYTES_TO_UINT16(buf[P_DATA1+4], buf[P_DATA1+5]);
			strain[3].strain_filtered = (uint16_t)BYTES_TO_UINT16(buf[P_DATA1+6], buf[P_DATA1+7]);
			strain[4].strain_filtered = (uint16_t)BYTES_TO_UINT16(buf[P_DATA1+8], buf[P_DATA1+9]);
			strain[5].strain_filtered = (uint16_t)BYTES_TO_UINT16(buf[P_DATA1+10], buf[P_DATA1+11]);
			//ToDo get all channels, and do something

			#ifdef BOARD_TYPE_FLEXSEA_PLAN

			_USE_PRINTF("Strain[0] = %i.\n", strain[0].strain_filtered);

			#endif	//BOARD_TYPE_FLEXSEA_PLAN
		}
		else
		{
			//Master is writing a value to this board

			#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

			encoder_write(tmp);

			#endif	//BOARD_TYPE_FLEXSEA_EXECUTE
			
			#ifdef BOARD_TYPE_FLEXSEA_STRAIN_AMP

			//ToDo

			#endif	//BOARD_TYPE_FLEXSEA_STRAIN_AMP

		}
	}
}

#ifdef __cplusplus
}
#endif
