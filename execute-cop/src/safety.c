//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// safety: safety checks, hazard management
//****************************************************************************


//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "safety.h"

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static void init_temp_buffer(void);
static uint8 average_temp(uint8 temp);

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 flag_wdclk = 0;
uint8 temp_buffer[TEMP_BUF_SIZE];

//****************************************************************************
// Public Function(s)
//****************************************************************************

void init_safety(void)
{
	//Prepare buffer:
	init_temp_buffer();
}

//Safety limits. Returns qualitative result.
uint8 safety_temp(uint8 temp)
{
	uint8 avg_temp = 0, result = 0;
	
	//Filtered temp:
	avg_temp = average_temp(temp);
	
	//Limits:
	if(avg_temp < TEMP_ERROR)
	{
		if(avg_temp < TEMP_WARNING)
		{
			//Temperature is normal
			result = T_NORMAL;
		}
		else
		{
			//Temperature is in the WARNING zone
			result = T_WARNING;
		}
	}
	else
	{
		//Over or equal the TEMP_ERROR limit
		result = T_ERROR;
	}
	
	//Return qualitative result:
	return result;
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//Fills the buffer with 0s
static void init_temp_buffer(void)
{
	uint16 i = 0;
	
	for(i = 0; i < TEMP_BUF_SIZE; i++)
	{
		temp_buffer[i] = 0;
	}
}

// Returns the average temperature for the last TEMP_BUF_SIZE samples
static uint8 average_temp(uint8 temp)
{
	uint16 i = 0;
	static uint16 pos = 0;
	//TEMP_BUF_SIZE is 128x uint8, so a maximum of 32768. uint16 would do
	//but we will use uint32 just in case we want a bigger buffer in the future
	uint32 temp_sum = 0;
	uint8 result = 0;
	
	//Store last value:
	temp_buffer[pos] = temp;
	
	//Average:
	for(i = 0; i < TEMP_BUF_SIZE; i++)
	{
		temp_sum += temp_buffer[i];
	}
	result = (uint8)((temp_sum >> TEMP_BUF_SHIFT) & 0xFF);
	
	//Increase index:
	pos++;
	if(pos > TEMP_BUF_SIZE)
	{
		pos = 0;
	}
	
	return result;
}
