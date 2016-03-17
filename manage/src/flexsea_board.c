//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_board: configuration and functions for this particular board
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "flexsea_board.h"
#include "../../flexsea-system/inc/flexsea_system.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//<FlexSEA User>
//==============
//Board architecture. Has to be changed in all the flexsea_board files!

uint8_t board_id = FLEXSEA_MANAGE_1;		//This board
uint8_t board_up_id = FLEXSEA_PLAN_1;		//This board's master

//Slave bus #1 (RS-485 #1):
//=========================
uint8_t board_sub1_id[SLAVE_BUS_1_CNT] = {FLEXSEA_EXECUTE_1, FLEXSEA_EXECUTE_3};

//Slave bus #2 (RS-485 #2):
//=========================
uint8_t board_sub2_id[SLAVE_BUS_2_CNT] = {FLEXSEA_EXECUTE_2, FLEXSEA_EXECUTE_4};

//(make sure to update SLAVE_BUS_x_CNT in flexsea_board.h!)

//===============
//</FlexSEA User>

//ToDo: This used to be in flexsea_rx_cmd... not clean. 
uint8_t read_offset = 0;

//Slave Read Buffer:
unsigned char slave_read_buffer[SLAVE_READ_BUFFER_LEN];

uint8_t bytes_ready_spi = 0;
uint8_t cmd_ready_spi = 0;

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
		puts_rs485_2(str, length);
	}
	else
	{
		//Unknown port, call flexsea_error()
		flexsea_error(SE_INVALID_SLAVE);
	}
}

void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length)
{
	// Everything is done "automatically"
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
	//We only listen if we requested a reply:
	if((slaves_485_1.xmit.listen == 1) || (slaves_485_1.autosample.listen == 1))
	{
		slaves_485_1.xmit.listen = 0;
		slaves_485_1.autosample.listen = 0;

		reception_rs485_1_blocking();	//Sets the transceiver to Receive
		//From this point on data will be received via the interrupt.
	}

	if((slaves_485_2.xmit.listen == 1) || (slaves_485_2.autosample.listen == 1))
	{
		slaves_485_2.xmit.listen = 0;
		slaves_485_2.autosample.listen = 0;

		reception_rs485_2_blocking();	//Sets the transceiver to Receive
		//From this point on data will be received via the interrupt.
	}

	//Did we receive new bytes?
	if(slaves_485_1.bytes_ready != 0)
	{
		slaves_485_1.bytes_ready = 0;
        //Got new data in, try to decode
		slaves_485_1.cmd_ready = unpack_payload_485_1();
	}

	//Did we receive new bytes?
	if(slaves_485_2.bytes_ready != 0)
	{
		slaves_485_2.bytes_ready = 0;
        //Got new data in, try to decode
		slaves_485_2.cmd_ready = unpack_payload_485_2();
	}
}

//ToDo: deprecated function?
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
	uint16_to_bytes(exec1.analog[0], &b0, &b1);
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
    prepare_empty_payload(board_id, FLEXSEA_PLAN_1, payload_str, PAYLOAD_BUF_LEN); //ToDo extract from command, not hcoded

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_MEM_READ_REPLY;

    //Copy a portion of slave_read_buffer[] in payload_str[]
    payload_str[P_DATA1] = slave_read_buffer[SRB_MANAGE_OFFSET];	//Always the offset
    for(i = 1; i < PAYLOAD_BYTES; i++)
    {
    	payload_str[P_DATA1 + i] = slave_read_buffer[base_addr + i];
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
		aTxBuffer[i] = comm_str_spi[i];
	}
}

//Everytime we receive an SPI string we transmit data
//This function prepares the data to be sent.
//ToDo delete?
void flexsea_prepare_spi_tx_buffer(uint8_t base_addr)
{
	flexsea_update_slave_read_buffer(base_addr);
	build_slave_payload(base_addr);
	comm_gen_str(payload_str, comm_str_spi, PAYLOAD_BUF_LEN);
	comm_str_to_txbuffer();
}
