//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_buffers: everything related to the reception buffers
//****************************************************************************


//****************************************************************************
// Include(s)
//****************************************************************************

#include "../inc/flexsea.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t rx_buf_spi[RX_BUF_LEN];
uint8_t rx_buf_485_1[RX_BUF_LEN];
uint8_t rx_buf_485_2[RX_BUF_LEN];
uint8_t rx_buf_usb[RX_BUF_LEN];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static void update_rx_buf_byte(uint8_t *buf, uint32_t *idx, uint8_t new_byte);
static void update_rx_buf_array(uint8_t *buf, uint32_t *idx, uint8_t *new_data, uint32_t len);
static void update_rx_buf_spi(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
static void update_rx_buf_485_1(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
static void update_rx_buf_485_2(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
static void update_rx_buf_usb(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);

//****************************************************************************
// Private function(s)
//****************************************************************************

void test_upd(void)
{
	uint8_t byte = 1;
	uint8_t array[RX_BUF_LEN];
	uint32_t idx = 0;
	
	while(1)
	{
		update_rx_buf_byte(array, &idx, byte);
		update_rx_buf_485_1(UPDATE_BYTE, byte, array, 1);
		byte++;
	}
}


//Add one byte to the FIFO buffer
//Do not call that function directly, call update_rx_buf_byte_n() where n is your communication port.
static void update_rx_buf_byte(uint8_t *buf, uint32_t *idx, uint8_t new_byte)
{
	uint32_t i = 0;

	if((*idx) < RX_BUF_LEN)
	{
		//Buffer isn't full yet, no need to discard "old" bytes
		buf[(*idx)] = new_byte;
		(*idx)++;
	}
	else
	{
		//Shift buffer to clear one spot
		for(i = 1; i < RX_BUF_LEN; i++)
		{
			buf[i-1] = buf[i];
		}
		//Add last byte to the buffer
		buf[RX_BUF_LEN-1] = new_byte;
	}

	//buf[] is now up to date
}

//Add 'len' bytes from the 'new_data' array to the FIFO buffer
//Do not call that function directly, call update_rx_buf_array_n() where n is your communication port.
static void update_rx_buf_array(uint8_t *buf, uint32_t *idx, uint8_t *new_data, uint32_t len)
{
	uint32_t i = 0, cnt = 0, remaining = 0;

	if((*idx) < RX_BUF_LEN)
	{
		//Buffer isn't full yet, no need to discard "old" bytes yet

		while(((*idx) + len) < RX_BUF_LEN)
		{
			//As long as we did not over fill it we keep adding bytes and increasing the index
			buf[(*idx)] = new_data[cnt];
			(*idx)++;
			cnt++;	//Number of bytes we could add before shifting old data
		}

		if((cnt + 1) == len)
		{
			//All the bytes were added without requiring shifting, exit
			return;
		}
		else
		{
			//We need to shift and add 'remaining' bytes:
			remaining = len - (cnt + 1);
		}
	}
	else
	{
		//Buffer was already full when we started
		remaining = len;
	}

	if(remaining != 0)
	{
		//Shift buffer to clear 'remaining' spots
		for(i = remaining; i < (RX_BUF_LEN) ; i++)
		{
			buf[i-remaining] = buf[i];
		}

		//Then add the new data bytes at the end of the buffer:
		for(i = (RX_BUF_LEN - remaining); i < RX_BUF_LEN; i++)
		{
			buf[i] = new_data[cnt];
			cnt++;
		}
	}
}

//Wraps update_rx_buf_byte()/update_rx_buf_array() for the SPI peripheral. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_spi() or update_rx_buf_array_spi()
static void update_rx_buf_spi(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_spi = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_spi, &idx_spi, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_spi, &idx_spi, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

//Wraps update_rx_buf_byte()/update_rx_buf_array() for the RS-485 #1 peripheral. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_485_1() or update_rx_buf_array_485_1()
static void update_rx_buf_485_1(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_485_1 = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_485_1, &idx_485_1, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_485_1, &idx_485_1, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

//Wraps update_rx_buf_byte()/update_rx_buf_array() for the RS-485 #2 peripheral. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_485_2() or update_rx_buf_array_485_2()
static void update_rx_buf_485_2(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_485_2 = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_485_2, &idx_485_2, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_485_2, &idx_485_2, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

//Wraps update_rx_buf_byte()/update_rx_buf_array() for the USB peripheral. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_usb() or update_rx_buf_array_usb()
static void update_rx_buf_usb(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_usb = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_usb, &idx_usb, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_usb, &idx_usb, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Add one byte to the SPI RX buffer
void update_rx_buf_byte_spi(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_spi(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to the SPI RX buffer
void update_rx_buf_array_spi(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_spi(UPDATE_ARRAY, 0, new_array, len);
}

//Add one byte to the RS-485 #1 RX buffer
void update_rx_buf_byte_485_1(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_485_1(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to the RS-485 #1 RX buffer
void update_rx_buf_array_485_1(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_485_1(UPDATE_ARRAY, 0, new_array, len);
}

//Add one byte to the RS-485 #2 RX buffer
void update_rx_buf_byte_485_2(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_485_2(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to the RS-485 #2 RX buffer
void update_rx_buf_array_485_2(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_485_2(UPDATE_ARRAY, 0, new_array, len);
}

//Add one byte to the USB RX buffer
void update_rx_buf_byte_usb(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_usb(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to the USB RX buffer
void update_rx_buf_array_usb(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_usb(UPDATE_ARRAY, 0, new_array, len);
}
