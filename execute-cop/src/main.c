//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// main: FlexSEA-Execute Safety-CoP
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

int main()
{
	uint8 i2c_flag = 0;
	uint16 tmp_volt = 0;
	uint16 extend_error_pulse = 0;
	
	//Initialize and start peripherals:
    init_peripherals();
	
	// Enable global interrupts
	CyGlobalIntEnable;
	
	//PWM pass-through (ToDo program safety feature)
	Control_Reg_1_Write(1);	
	
	//Disable shorted leads
	SL_EN_Write(0);

    while(1)
    {
		//For now we always generate the -4V5:
		SL_CLK_Write(1);
		SL_CLK_Write(0);
		
		//Update sensor data every 10ms:
		if(flag_tb10ms)
		{
			flag_tb10ms = 0;
			
			//Update shared memory:
			
			tmp_volt = read_vb();
			ezI2Cbuf[MEM_R_VB_SNS_MSB] = (uint8)((tmp_volt & 0xFF00) >> 8);
			ezI2Cbuf[MEM_R_VB_SNS_LSB] = (uint8)(tmp_volt & 0x00FF);
			
			tmp_volt = read_vg();
			ezI2Cbuf[MEM_R_VG_SNS_MSB] = (uint8)((tmp_volt & 0xFF00) >> 8);
			ezI2Cbuf[MEM_R_VG_SNS_LSB] = (uint8)(tmp_volt & 0x00FF);
			
			tmp_volt = read_3v3();
			ezI2Cbuf[MEM_R_3V3_SNS_MSB] = (uint8)((tmp_volt & 0xFF00) >> 8);
			ezI2Cbuf[MEM_R_3V3_SNS_LSB] = (uint8)(tmp_volt & 0x00FF);
			
			ezI2Cbuf[MEM_R_TEMPERATURE] = read_temp();
			
			ezI2Cbuf[MEM_R_STATUS1]  = STATUS1_GOOD;
		}
		
		if(flag_tb_1ms)
		{
			flag_tb_1ms = 0;
			
			if(flag_wdclk == 1)	//Watchdog clock expired
			{
				extend_error_pulse = 1000;
				led_period = LED_PERIOD_ERROR;
				flag_wdclk = 2;	//2 means "being processed"
			}
			else
			{
				led_period = LED_PERIOD_NORM;
			}
			
			if(extend_error_pulse >= 1)
			{
				extend_error_pulse--;
			}
			else
			{
				extend_error_pulse = 0;
				flag_wdclk = 0;
			}
		}
		
		//EZI2C Write complete
        if (0u != (I2C_1_EzI2CGetActivity() & I2C_1_EZI2C_STATUS_WRITE1))
        {
			//...
			i2c_flag = 1;
			i2c_flag = 0;			
        }
		
		//Error flags:
		

    }
}
