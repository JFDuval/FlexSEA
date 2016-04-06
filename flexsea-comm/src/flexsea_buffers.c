//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// Adapted for MorphLab - 02/2016
//****************************************************************************
// flexsea_buffers: everything related to the reception buffers
//****************************************************************************

//This code currently supports 4 buffers, with generic names. Enable the buffers
//you need in flexsea_board, and overload function names with preprocessor
//statements.

//All those #ifdef make it dense, but they are required to minimize memory
//on smaller microcontrollers.

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include "../inc/flexsea.h"
#include "flexsea_system.h"
#include "flexsea_board.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//Reception buffers - generic names:

#ifdef ENABLE_FLEXSEA_BUF_1
uint8_t rx_buf_1[RX_BUF_LEN];
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
uint8_t rx_buf_2[RX_BUF_LEN];
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
uint8_t rx_buf_3[RX_BUF_LEN];
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
uint8_t rx_buf_4[RX_BUF_LEN];
#endif	//ENABLE_FLEXSEA_BUF_4

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//For all the buffers:
static void update_rx_buf_byte(uint8_t *buf, uint32_t *idx, uint8_t new_byte);
static void update_rx_buf_array(uint8_t *buf, uint32_t *idx, uint8_t *new_data, uint32_t len);

//Specific:
#ifdef ENABLE_FLEXSEA_BUF_1
static void update_rx_buf_1(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
static void update_rx_buf_2(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
static void update_rx_buf_3(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
static void update_rx_buf_4(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_4

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
        update_rx_buf_1(UPDATE_BYTE, byte, array, 1);
		byte++;
	}
}

//Add one byte to the FIFO buffer
//Do not call that function directly, call update_rx_buf_byte_n() where n is your communication port/buffer name
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
//Do not call that function directly, call update_rx_buf_array_n() where n is your communication port/buffer name
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

#ifdef ENABLE_FLEXSEA_BUF_1

//Wraps update_rx_buf_byte()/update_rx_buf_array() for buffer #1. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_1() or update_rx_buf_array_1()
static void update_rx_buf_1(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_1 = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_1, &idx_1, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_1, &idx_1, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

#endif	//ENABLE_FLEXSEA_BUF_1

#ifdef ENABLE_FLEXSEA_BUF_2

//Wraps update_rx_buf_byte()/update_rx_buf_array() for buffer #2. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_2() or update_rx_buf_array_2()
static void update_rx_buf_2(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_2 = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_2, &idx_2, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_2, &idx_2, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

#endif	//ENABLE_FLEXSEA_BUF_2

#ifdef ENABLE_FLEXSEA_BUF_3

//Wraps update_rx_buf_byte()/update_rx_buf_array() for buffer #3. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_3() or update_rx_buf_array_3()
static void update_rx_buf_3(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_3 = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_3, &idx_3, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_3, &idx_3, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

#endif	//ENABLE_FLEXSEA_BUF_3

#ifdef ENABLE_FLEXSEA_BUF_4

//Wraps update_rx_buf_byte()/update_rx_buf_array() for buffer #4. Keeps track of the index.
//Do not use directly, call update_rx_buf_byte_4() or update_rx_buf_array_4()
static void update_rx_buf_usb(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len)
{
	static uint32_t idx_4 = 0;

	if(byte_array == UPDATE_BYTE)
	{
		//Updating buffer with one byte
		update_rx_buf_byte(rx_buf_4, &idx_4, new_byte);
	}
	else if(byte_array == UPDATE_ARRAY)
	{
		//Updating buffer with an array
		update_rx_buf_array(rx_buf_4, &idx_4, new_array, len);
	}
	else
	{
		//Error
		//flexsea_error(0);	ToDo
	}
}

#endif	//ENABLE_FLEXSEA_BUF_4

//****************************************************************************
// Public Function(s)
//****************************************************************************

#ifdef ENABLE_FLEXSEA_BUF_1

//Add one byte to buffer #1
void update_rx_buf_byte_1(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_1(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to buffer #1
void update_rx_buf_array_1(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_1(UPDATE_ARRAY, 0, new_array, len);
}
	
#endif	//ENABLE_FLEXSEA_BUF_1

#ifdef ENABLE_FLEXSEA_BUF_2

//Add one byte to buffer #2
void update_rx_buf_byte_2(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_2(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to buffer #2
void update_rx_buf_array_2(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_2(UPDATE_ARRAY, 0, new_array, len);
}

#endif	//ENABLE_FLEXSEA_BUF_2

#ifdef ENABLE_FLEXSEA_BUF_3

//Add one byte to buffer #3
void update_rx_buf_byte_3(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_3(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to buffer #3
void update_rx_buf_array_3(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_3(UPDATE_ARRAY, 0, new_array, len);
}

#endif	//ENABLE_FLEXSEA_BUF_3

#ifdef ENABLE_FLEXSEA_BUF_4

//Add one byte to buffer #4
void update_rx_buf_byte_4(uint8_t new_byte)
{
	uint8_t empty_array[1] = {0};
	update_rx_buf_4(UPDATE_BYTE, new_byte, empty_array, 0);
}

//Add an array of bytes to buffer #4
void update_rx_buf_array_4(uint8_t *new_array, uint32_t len)
{
	update_rx_buf_4(UPDATE_ARRAY, 0, new_array, len);
}

#endif	//ENABLE_FLEXSEA_BUF_4

#ifdef __cplusplus
}
#endif
