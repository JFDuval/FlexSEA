//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// strain: strain gauge amplifier
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "strain.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************
	
//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

void init_strain()
{
}

//Copy of the test code used in main.c to test the hardware:
void strain_test_blocking(void)
{
	//Strain Amplifier test:
	
	uint8 i2c_test_wbuf[9];
	uint8 vr1 = 0;
	uint8 ledg_state = 0;
	
	VDAC8_3_SetValue(156);	
	i2c_test_wbuf[0] = MCP4661_REG_RAM_W1;
	i2c_test_wbuf[1] = 120;	//Offset of ~ V/2
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
	CyDelay(10);
	i2c_test_wbuf[0] = MCP4661_REG_RAM_W0;
	i2c_test_wbuf[1] = 10;	//Relatively small gain
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
	while(1)
	{
		vr1++;			
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(1);
	}
}

