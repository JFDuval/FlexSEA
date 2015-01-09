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

#include <project.h>
#include "flexsea_local.h"
#include "misc.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

char name[] = "FlexSEA-Execute";
char version[] = "0.0";
char date[] = "08/01/2014";

//Board ID (this board) -  - pick from Board list in /common/inc/flexsea.h
unsigned char board_id = FLEXSEA_EXECUTE_1;
unsigned char board_up_id = FLEXSEA_MANAGE_1;
unsigned char board_sub1_id = FLEXSEA_DEFAULT;
unsigned char board_sub2_id = FLEXSEA_DEFAULT;

//Control strategy:
unsigned char controller = CTRL_NONE;	//No controller enabled

//Slave Read Buffer:
unsigned char slave_read_buffer[SLAVE_READ_BUFFER_LEN];

//****************************************************************************
// External variable(s)
//****************************************************************************

//flexsea_payload:
extern unsigned char payload_str[];

//ADC
extern volatile uint16 adc1_result_avg8;
extern unsigned int adc1_res[ADC1_CHANNELS][ADC1_BUF_LEN];
extern unsigned int adc1_res_filtered[ADC1_CHANNELS];

extern unsigned char read_offset;

//****************************************************************************
// Function(s)
//****************************************************************************

//Wrapper for the specific serial functions. Useful to keep flexsea_network
//platform independent (for example, we don't need need puts_rs485() for Plan)
//ToDo rename to flexsea_send_serial_slave()
void flexsea_send_serial(unsigned char port, unsigned char *str, unsigned char length)
{
	//Redirects to RS-485:
	//ToDo: port check?
	//puts_rs485_1(str, length);
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
	slave_read_buffer[SRB_EXECUTE_STATUS] = controller;			
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
    payload_build_basic_str(FLEXSEA_PLAN_1);	//ToDo extract from command, not hcoded

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_REPLY;

    //Copy a portion of slave_read_buffer[] in payload_str[]
    payload_str[CP_DATA1] = slave_read_buffer[SRB_EXECUTE_OFFSET];	//Always the offset
    for(i = 1; i < PAYLOAD_BYTES; i++)
    {
    	payload_str[CP_DATA1 + i] = slave_read_buffer[base_addr + i];
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
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	
	return (numb + 1);
}