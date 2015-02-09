//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// safety: Safety-CoP & safety-related functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "safety.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

struct scop safety_cop;

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//Update the global variables from the array
void decode_psoc4_values(uint8 *psoc4_data)
{
	safety_cop.v_vb = (psoc4_data[MEM_R_VB_SNS_MSB] << 8) + psoc4_data[MEM_R_VB_SNS_LSB];
	safety_cop.v_vg = (psoc4_data[MEM_R_VG_SNS_MSB] << 8) + psoc4_data[MEM_R_VG_SNS_LSB];
	safety_cop.v_3v3 = (psoc4_data[MEM_R_3V3_SNS_MSB] << 8) + psoc4_data[MEM_R_3V3_SNS_LSB];
	safety_cop.temperature = psoc4_data[MEM_R_TEMPERATURE];
	safety_cop.status1 = psoc4_data[MEM_R_STATUS1];
}

//Copy of the test code used in main.c to test the hardware:
void safety_cop_comm_test_blocking(void)
{
	//PSoC 4 <=> PSoC 5 I2C Test code
	
	uint8 i2c_test_wbuf[9];
	uint8 i2c_test_rbuf[24];
	uint8 ledg_state = 0;
	
	while(1)
	{
		//Write to slave:
		//I2C_1_MasterWriteBuf(0x11, (uint8 *) i2c_test_wbuf, 9, I2C_1_MODE_COMPLETE_XFER);
		
		//Read from slave:
		i2c_test_wbuf[0] = 0;
		I2C_1_MasterWriteBuf(0x11, (uint8 *) i2c_test_wbuf, 1, I2C_1_MODE_COMPLETE_XFER);	//Write offset
		CyDelayUs(500);
		I2C_1_MasterReadBuf(0x11, i2c_test_rbuf, 24, I2C_1_MODE_COMPLETE_XFER);
		CyDelayUs(500);
		decode_psoc4_values(i2c_test_rbuf);
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(250);	
	}
}

//Returns the die temperature.
//ToDo deal with the active_error, or replace with better code
int16 dietemp_read(void)
{
	#ifdef USE_DIETEMP

	static cystatus dietemp = 0;
	int16 temp = 0;	
	uint8 active_error = 0;
				
	//Die temperature too high?
	dietemp = DieTemp_1_Query(&temp);
	if(dietemp == CYRET_SUCCESS)
	{
		DieTemp_1_Start(); 		// start next temp reading
		if(temp > MAX_DIE_TEMP)
			active_error = 1;
		else
			active_error = 0;
	} 
	else if(dietemp == (CYRET_TIMEOUT))
	{
		DieTemp_1_Start(); 		// start next temp reading
	}
	
	return temp;
	
	#else
		
		return 0;
			
	#endif	//USE_DIETEMP		
}
