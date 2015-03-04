//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea: Master file for the FlexSEA stack.
//****************************************************************************

// FlexSEA: Flexible & Scalable Electronics Architecture

// Naming convention:
// ================================
// - Plan: Embedded Computer
//      - Complex algorithms, data-logging, user interfaces, ...
//      - Hard/soft: BeagleBone Black running Linux. C, Python, Matlab.
// - Manage: Data acquisition and mid-level computing
//      - Connected to Plan. Gathers sensor data, connect to slaves
//      - Hard/soft: STM32F4 Cortex-M4. C.
// - Execute: smart motor driver
//      - Motion controller
//      - Hard/soft: Programmable System on Chip (PSoC). C, HDL, graphical.

// v0.0 Limitations and known bugs: ToDo Update
// ================================
// - The board config is pretty muched fixed: 1 Plan, 1 Manage, up to 2 Execute
//   (on the same RS-485 bus)
// - Only 1 command per transmission
// - STM32F4 interrupt based SPI driver isn't happy with unknown transmission
//   length so for now I'm fixing the packet length.
// - Fixed payload length: 12 bytes (allows you to send 1 command with up to
//   8 arguments (uint8) (or 4x uint16))
// - Fixed comm_str length: 24 bytes (min. to accomodate a payload where all the
//   data bytes need escaping)
// - In comm_str #OfBytes isn't escaped. Ok as long as the count is less than
//   the decimal value of the flags ('a', 'z', 'e') so max 97 bytes.
// - Data transfer could be faster with shorter ACK sequence, more than 1 command
//   per packet and no repackaging on the Manage board (straight pass-through)
//   To be optimized later.

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/flexsea.h"
#include "flexsea_local.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//When something goes wrong in the code it will land here:
unsigned int flexsea_error(unsigned int err_code)
{
	//ToDo something useful
	return err_code;
}

//From 1 uint32 to 4 uint8
void uint32_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1, uint8_t *b2, uint8_t *b3)
{
	*b0 = (uint8_t) ((x >> 24) & 0xFF);
	*b1 = (uint8_t) ((x >> 16) & 0xFF);
	*b2 = (uint8_t) ((x >> 8) & 0xFF);
	*b3 = (uint8_t) (x & 0xFF);
}

//From 1 uint16 to 2 uint8
void uint16_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1)
{
	*b0 = (uint8_t) ((x >> 8) & 0xFF);
	*b1 = (uint8_t) (x & 0xFF);
}

//ToDo: look at inline functions

//Can be used to fill a buffer of any length with any value
void fill_uint8_buf(uint8_t *buf, uint32_t len, uint8_t filler)
{
	uint32_t i = 0;

	for(i = 0; i < len; i++)
	{
		buf[i] = filler;
	}
}
