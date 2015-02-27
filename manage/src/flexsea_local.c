//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 01/2015
//****************************************************************************
// flexsea_local: configuration and functions for this particular board
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "flexsea_local.h"
#include "../../common/inc/flexsea.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

char name[] = "FlexSEA-Manage";
char version[] = "1.0";
char date[] = "02/16/2015";

//Board ID (this board) -  - pick from Board list in /common/inc/flexsea.h
unsigned char board_id = FLEXSEA_MANAGE_1;
unsigned char board_up_id = FLEXSEA_PLAN_1;
unsigned char board_sub1_id = FLEXSEA_EXECUTE_1;
unsigned char board_sub2_id = FLEXSEA_EXECUTE_2;
//ToDo: change this, it needs to be a flexible config

//Slave Read Buffer:
unsigned char slave_read_buffer[SLAVE_READ_BUFFER_LEN];

uint8_t bytes_ready_spi = 0, bytes_ready_485_1 = 0, bytes_ready_485_2 = 0;
uint8_t cmd_ready_spi = 0, cmd_ready_485_1 = 0, cmd_ready_485_2 = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

//fm_spi:
extern SPI_HandleTypeDef spi4_handle;
extern uint8_t aRxBuffer[COMM_STR_BUF_LEN];
extern uint8_t aTxBuffer[COMM_STR_BUF_LEN];
//flexsea_comm:
extern unsigned char comm_str[COMM_STR_BUF_LEN];
//flexsea_payload:
extern unsigned char payload_str[];

extern unsigned char read_offset;
unsigned char start_listening_flag;

//rx_cmd:
extern struct execute_s exec1;

//****************************************************************************
// Function(s)
//****************************************************************************

//Wrapper for the specific serial functions. Useful to keep flexsea_network
//platform independent (for example, we don't need need puts_rs485() for Plan)
void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length)
{
	if(port == PORT_RS485_1)
	{
		puts_rs485_1(str, length);
	}
	else if(port == PORT_RS485_2)
	{
		//puts_rs485_2(str, length);
	}
	else
	{
		//Unknown port, call flexsea_error()
		flexsea_error(SE_INVALID_SLAVE);
	}
}

void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length)
{
	//comm_str was already generated, now we place it in the buffer:
	//comm_str_to_txbuffer();

	/*

	// transmit over SPI using interrupts
	if(HAL_SPI_Transmit_IT(&spi4_handle, aTxBuffer, length) != HAL_OK)
	{
		// Transfer error in transmission process
		flexsea_error(SE_SEND_SERIAL_MASTER);
	}
	*/

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

void flexsea_receive_from_master(void)
{
	if(bytes_ready_spi != 0)
	{
		bytes_ready_spi = 0;
		cmd_ready_spi = unpack_payload_spi();
	}
}

void flexsea_start_receiving_from_master(void)
{
	// start receive over SPI
	if (HAL_SPI_GetState(&spi4_handle) == HAL_SPI_STATE_READY)
	{
		//if(HAL_Start_SPI_Receiving_IT(&spi4_handle, aRxBuffer, COMM_STR_BUF_LEN) != HAL_OK)
		if(HAL_SPI_TransmitReceive_IT(&spi4_handle, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, COMM_STR_BUF_LEN) != HAL_OK)
		{
			// Transfer error in transmission process
			flexsea_error(SE_RECEIVE_FROM_MASTER);
		}
	}
}

//Receive data from a slave
void flexsea_receive_from_slave(void)
{
	static volatile uint8_t uart_rx_test = 0;
	unsigned int delay = 0;

	//We only listen if we requested a reply:
	if(start_listening_flag)
	{
		start_listening_flag = 0;

		for(delay = 0; delay < 5000; delay++);		//Short delay
		//ToDo: do we need this delay? How long is it?
		//Sets the transceiver to Receive:
		uart_rx_test = getc_rs485_1_blocking();
		//From this point on data will be received via the interrupt.
		//ToDo why is it called Blocking if it's ISR based?
	}

	//Did we receive new bytes?
	if(bytes_ready_485_1 != 0)
	{
		bytes_ready_485_1 = 0;
        //Got new data in, try to decode
		cmd_ready_485_1 = unpack_payload_485_1();
	}
}

//Packages data in one unified array: slave_read_buffer[]
void flexsea_update_slave_read_buffer(unsigned char read_offset)
{
	uint8_t b0 = 0, b1 = 0, b2 = 0, b3 = 0;

	//Base address:
	slave_read_buffer[0] = read_offset;

	//IMU, 3x2 bytes:
	uint16_to_bytes((uint16_t)exec1.imu.x, &b0, &b1);
	slave_read_buffer[1] = b0;
	slave_read_buffer[2] = b1;
	uint16_to_bytes((uint16_t)exec1.imu.y, &b0, &b1);
	slave_read_buffer[3] = b0;
	slave_read_buffer[4] = b1;
	uint16_to_bytes((uint16_t)exec1.imu.z, &b0, &b1);
	slave_read_buffer[5] = b0;
	slave_read_buffer[6] = b1;

	//Strain:
	uint16_to_bytes(exec1.strain, &b0, &b1);
	slave_read_buffer[7] = b0;
	slave_read_buffer[8] = b1;

	//Analog:
	uint16_to_bytes(exec1.analog, &b0, &b1);
	slave_read_buffer[9] = b0;
	slave_read_buffer[10] = b1;

	//Current:
	uint16_to_bytes((uint16_t)exec1.current, &b0, &b1);
	slave_read_buffer[11] = b0;
	slave_read_buffer[12] = b1;

	uint32_to_bytes((uint32_t)exec1.encoder, &b0, &b1, &b2, &b3);
	slave_read_buffer[13] = b0;
	slave_read_buffer[14] = b1;
	slave_read_buffer[15] = b2;
	slave_read_buffer[16] = b3;
}

void build_slave_payload(unsigned char base_addr)
{
	unsigned char i = 0;

    //Fresh string:
    payload_build_basic_str(FLEXSEA_PLAN_1);	//ToDo extract from command, not hcoded

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_MEM_READ_REPLY;

    //Copy a portion of slave_read_buffer[] in payload_str[]
    payload_str[CP_DATA1] = slave_read_buffer[SRB_MANAGE_OFFSET];	//Always the offset
    for(i = 1; i < PAYLOAD_BYTES; i++)
    {
    	payload_str[CP_DATA1 + i] = slave_read_buffer[base_addr + i];
    }

    return;
}

//Copies the generated comm_str to the aTxBuffer
//It will be transfered the next time the master writes to us.
//ToDo generalize, use buffers as arguments
void comm_str_to_txbuffer(void)
{
	unsigned char i = 0;

	for(i = 0; i < COMM_STR_BUF_LEN; i++)
	{
		aTxBuffer[i] = comm_str[i];
	}
}

//Everytime we receive an SPI string we transmit data
//This function prepares the data to be sent.
//ToDo delete?
void flexsea_prepare_spi_tx_buffer(uint8_t base_addr)
{
	flexsea_update_slave_read_buffer(base_addr);
	build_slave_payload(base_addr);
	comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	comm_str_to_txbuffer();
}
