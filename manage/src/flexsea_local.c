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
char version[] = "0.1";
char date[] = "01/19/2015";

//Board ID (this board) -  - pick from Board list in /common/inc/flexsea.h
unsigned char board_id = FLEXSEA_MANAGE_1;
unsigned char board_up_id = FLEXSEA_PLAN_1;
unsigned char board_sub1_id = FLEXSEA_EXECUTE_1;
unsigned char board_sub2_id = FLEXSEA_EXECUTE_2;

//Slave Read Buffer:
unsigned char slave_read_buffer[SLAVE_READ_BUFFER_LEN];

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
//main:
extern int comm_res, comm_success;

extern unsigned char read_offset;
unsigned char start_listening_flag;

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
		flexsea_error(0);	//ToDo error code
	}
}

void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length)
{
	//comm_str was already generated, now we place it in the buffer:
	comm_str_to_txbuffer();
	// transmit over SPI using interrupts
	if(HAL_SPI_Transmit_IT(&spi4_handle, aTxBuffer, RX_BUF_LEN) != HAL_OK)
	{
		// Transfer error in transmission process
		Error_Handler();
	}
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
	// i'm not sure what to do here now that all reception is done by interrupt
}

void flexsea_start_receiving_from_master(void)
{
	// start receive over SPI
	if (HAL_SPI_GetState(&spi4_handle) == HAL_SPI_STATE_READY)
	{
		if(HAL_Start_SPI_Receiving_IT(&spi4_handle, aRxBuffer, RX_BUF_LEN) != HAL_OK)
		{
			// Transfer error in transmission process
			Error_Handler();
		}
	}
}

//Receive data from a slave
void flexsea_receive_from_slave(void)
{
	static unsigned char uart_rx_test = 0;
	unsigned int delay = 0;

	//We only listen if we requested a reply:
	if(start_listening_flag)
	{
		start_listening_flag = 0;

		for(delay = 0; delay < 5000; delay++);		//Short delay
		//Sets the transceiver to Receive:
		uart_rx_test = getc_rs485_1_blocking();
		//From this point on data will be received via the interrupt.
	}
}
//send IMU data.
#if SEND_IMU == 1
void flexsea_update_slave_read_buffer(unsigned char read_offset) {
	// function to send fresh imu data over to the plan board. for testing.
	// data convention: AXL AXH AYL AYH AZL AZH GXL GXH GYL GYH GZL GZH
    //  (LSB first, XYZ order, accel first when sending all data)
	 imu_data_set imu_data_mode = GYRO_ONLY;
	  //all of the data we want.
	  uint16_t a_x = get_accel_x();
	  uint16_t a_y = get_accel_y();
	  uint16_t a_z = get_accel_z();
	  uint16_t g_x = get_gyro_x();
	  uint16_t g_y = get_gyro_y();
	  uint16_t g_z = get_gyro_z();

	  //how many bytes are going to be in our string?
	  uint8_t num_data_bytes = 0;

	  //num bytes in generated comm_str
	  unsigned char gen_bytes = 0;

	  //switch on the kinds of data we want.
	  // right shifting/casting is so that we can turn the
	  // 16 bit numbers into 8 bit chunks for transmission.
	  switch(imu_data_mode) {
		  case ACCEL_ONLY:
			  num_data_bytes = 6;
			  slave_read_buffer[0] = (uint8_t) a_x;
			  slave_read_buffer[1] = (uint8_t) (a_x >> 8);
			  slave_read_buffer[2] = (uint8_t) a_y;
			  slave_read_buffer[3] = (uint8_t) (a_y >> 8);
			  slave_read_buffer[4] = (uint8_t) a_z;
			  slave_read_buffer[5] = (uint8_t) (a_z >> 8);
			  break;
		  case GYRO_ONLY:
			  num_data_bytes = 6;
			  slave_read_buffer[0] = (uint8_t) g_x;
			  slave_read_buffer[1] = (uint8_t) (g_x >> 8);
			  slave_read_buffer[2] = (uint8_t) g_y;
			  slave_read_buffer[3] = (uint8_t) (g_y >> 8);
			  slave_read_buffer[4] = (uint8_t) g_z;
			  slave_read_buffer[5] = (uint8_t) (g_z >> 8);
			  break;
		  case ALL:
			  num_data_bytes = 12;
			  slave_read_buffer[0] = (uint8_t) a_x;
			  slave_read_buffer[1] = (uint8_t) (a_x >> 8);
			  slave_read_buffer[2] = (uint8_t) a_y;
			  slave_read_buffer[3] = (uint8_t) (a_y >> 8);
			  slave_read_buffer[4] = (uint8_t) a_z;
			  slave_read_buffer[5] = (uint8_t) (a_z >> 8);
			  slave_read_buffer[6] = (uint8_t) g_x;
			  slave_read_buffer[7] = (uint8_t) (g_x >> 8);
			  slave_read_buffer[8] = (uint8_t) g_y;
			  slave_read_buffer[9] = (uint8_t) (g_y >> 8);
			  slave_read_buffer[10] = (uint8_t) g_z;
			  slave_read_buffer[11] = (uint8_t) (g_z >> 8);
			  break;
	  }
	return;
}
#else
//Packages data in one unified array: slave_read_buffer[]
void flexsea_update_slave_read_buffer(unsigned char read_offset)
{
	//ToDo: this should be in a separated function, but for now here it is:
	unsigned char tmp_dio = 0;
	unsigned char tmp_switches = 0;

	tmp_dio = read_dio_inputs(0);
	tmp_switches = (read_sw1() & 0x01);

	//End of ToDo comment

	//Offset, Status and Digital IOs:
	slave_read_buffer[SRB_MANAGE_OFFSET] = read_offset;
	slave_read_buffer[SRB_MANAGE_STATUS] = tmp_switches;
	slave_read_buffer[SRB_MANAGE_DIGITAL_IO_B1] = tmp_dio;
	slave_read_buffer[SRB_MANAGE_DIGITAL_IO_B2] = 0xEE;	//Fixed value for debugging. ToDo remove.

	//Analog: - All hardcoded for now (ToDo)
	slave_read_buffer[SRB_MANAGE_AN0_MSB] = 0x08;
	slave_read_buffer[SRB_MANAGE_AN0_LSB] = 0x00;
	slave_read_buffer[SRB_MANAGE_AN1_MSB] = 0x02;
	slave_read_buffer[SRB_MANAGE_AN1_LSB] = 0x9A;
	slave_read_buffer[SRB_MANAGE_AN2_MSB] = 5;
	slave_read_buffer[SRB_MANAGE_AN2_LSB] = 6;
	slave_read_buffer[SRB_MANAGE_AN3_MSB] = 7;
	slave_read_buffer[SRB_MANAGE_AN3_LSB] = 8;
	slave_read_buffer[SRB_MANAGE_AN4_MSB] = 9;
	slave_read_buffer[SRB_MANAGE_AN4_LSB] = 10;
	slave_read_buffer[SRB_MANAGE_AN5_MSB] = 11;
	slave_read_buffer[SRB_MANAGE_AN5_LSB] = 12;
	slave_read_buffer[SRB_MANAGE_AN6_MSB] = 13;
	slave_read_buffer[SRB_MANAGE_AN6_LSB] = 14;
	slave_read_buffer[SRB_MANAGE_AN7_MSB] = 15;
	slave_read_buffer[SRB_MANAGE_AN7_LSB] = 16;
}
#endif

void build_slave_payload(unsigned char base_addr)
{
	unsigned char i = 0;

    //Fresh string:
    payload_build_basic_str(FLEXSEA_PLAN_1);	//ToDo extract from command, not hcoded

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_REPLY;

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
void flexsea_prepare_spi_tx_buffer(void)
{
	flexsea_update_slave_read_buffer(read_offset);
	build_slave_payload(read_offset);
	comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	comm_str_to_txbuffer();
}
