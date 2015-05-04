//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_local: configuration and functions for this particular board
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "flexsea_local.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//Board ID (this board) -  - pick from Board list in /common/inc/flexsea.h
uint8 board_id = FLEXSEA_EXECUTE_2;
uint8 board_up_id = FLEXSEA_MANAGE_1;
uint8 board_sub1_id[SLAVE_BUS_1_CNT];
uint8 board_sub2_id[SLAVE_BUS_2_CNT];

//Slave Read Buffer:
unsigned char slave_read_buffer[SLAVE_READ_BUFFER_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Wrapper for the specific serial functions. Useful to keep flexsea_network
//platform independent (for example, we don't need need puts_rs485() for Plan)
void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length)
{
	//...
}

void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length)
{
	//...
}

//Fill the buffer with 0s
void flexsea_clear_slave_read_buffer(void)
{
	int i;

	for(i = 0; i < SLAVE_READ_BUFFER_LEN; i++)
	{
		slave_read_buffer[i] = 0;
	}
}

//Packages data in one unified array: slave_read_buffer[]
void flexsea_update_slave_read_buffer(unsigned char read_offset)
{
	//ToDo: this should be in a separated function, but for now here it is:
	int16 enc1 = 0;
	
	enc1 = (int16) ((QuadDec_1_GetCounter() >> 2) & 0xFFFF);	//Send as 16bits
	//End of ToDo comment

	//Offset, Status and Digital IOs:
	//ToDo fix: all harcoded for now, except Hall
	slave_read_buffer[SRB_EXECUTE_OFFSET] = read_offset;
	slave_read_buffer[SRB_EXECUTE_STATUS] = ctrl.active_ctrl;			
	slave_read_buffer[SRB_EXECUTE_ENC1_MSB] = (enc1 & 0xFF00)>>8;
	slave_read_buffer[SRB_EXECUTE_ENC1_LSB] = (enc1 & 0x00FF);
	slave_read_buffer[SRB_EXECUTE_AN0_MSB] = ((adc1_res_filtered[0] & 0x0F00) >> 8);
	slave_read_buffer[SRB_EXECUTE_AN0_LSB] = (adc1_res_filtered[0] & 0xFF);
	slave_read_buffer[SRB_EXECUTE_AN1_MSB] = ((adc1_res_filtered[1] & 0x0F00) >> 8);
	slave_read_buffer[SRB_EXECUTE_AN1_LSB] = (adc1_res_filtered[1] & 0xFF);
	slave_read_buffer[SRB_EXECUTE_CURRENT_MSB] = 0x02;	//ToDo
	slave_read_buffer[SRB_EXECUTE_CURRENT_LSB] = 0x9A;

	//...
}

void build_slave_payload(unsigned char base_addr)
{
	unsigned char i = 0;

    //Fresh string:
    prepare_empty_payload(board_id, FLEXSEA_PLAN_1, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = CMD_MEM_READ_REPLY;

    //Copy a portion of slave_read_buffer[] in payload_str[]
    payload_str[P_DATA1] = slave_read_buffer[SRB_EXECUTE_OFFSET];	//Always the offset
    for(i = 1; i < PAYLOAD_BYTES; i++)
    {
    	payload_str[P_DATA1 + i] = slave_read_buffer[base_addr + i];
    }

    return;
}

//When we receive a Read request we need to transmit data
//This function prepares the data to be sent.
unsigned char flexsea_prepare_rs485_tx_buffer(void)
{
	unsigned char numb = 0;
	
	flexsea_update_slave_read_buffer(read_offset);
	build_slave_payload(read_offset);
	numb = comm_gen_str(payload_str, comm_str_485_1, PAYLOAD_BUF_LEN);
	
	return (numb + 1);
}