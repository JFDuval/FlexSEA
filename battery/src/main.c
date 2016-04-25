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

uint8 err_v_3v3 = 0, err_v_vg = 0, err_v_vb = 0;
uint8 err_wdclk = 0, err_temp = 0, err_discon = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

int main()
{
	uint8 i2c_flag = 0;
	uint16 tmp_volt_3v3 = 0, tmp_volt_vg = 0, tmp_volt_vb = 0;
	uint16 extend_error_pulse = 0;
	uint8 togg_eled = 0;
	
	//Initialize and start peripherals:
    init_peripherals();
	
	//Enable global interrupts
	CyGlobalIntEnable;
	
	//Quick test: LED Green when ON
	LED_B_Write(1);
	
	//Test: latch output:
	SW_PSOC_Write(1);
	
    while(1)
    {
		//Update sensor data every 10ms, call safety functions:
		if(flag_tb10ms)
		{
			flag_tb10ms = 0;
			
/*
			//Update shared memory:
			
			tmp_volt_vb = read_vb();
			ezI2Cbuf[MEM_R_VB_SNS_MSB] = (uint8)((tmp_volt_vb & 0xFF00) >> 8);
			ezI2Cbuf[MEM_R_VB_SNS_LSB] = (uint8)(tmp_volt_vb & 0x00FF);
			
			tmp_volt_vg = read_vg();
			ezI2Cbuf[MEM_R_VG_SNS_MSB] = (uint8)((tmp_volt_vg & 0xFF00) >> 8);
			ezI2Cbuf[MEM_R_VG_SNS_LSB] = (uint8)(tmp_volt_vg & 0x00FF);
			
			tmp_volt_3v3 = read_3v3();
			ezI2Cbuf[MEM_R_3V3_SNS_MSB] = (uint8)((tmp_volt_3v3 & 0xFF00) >> 8);
			ezI2Cbuf[MEM_R_3V3_SNS_LSB] = (uint8)(tmp_volt_3v3 & 0x00FF);
			
			ezI2Cbuf[MEM_R_TEMPERATURE] = read_temp();
			
			//ezI2Cbuf[MEM_R_STATUS1]  = STATUS1_GOOD;
			
			//Safety functions:
			
			err_temp = safety_temp(ezI2Cbuf[MEM_R_TEMPERATURE]);
			err_v_3v3 = safety_volt(tmp_volt_3v3, M_3V3_LOW, M_3V3_HIGH);
			err_v_vg = safety_volt(tmp_volt_vg, M_VG_LOW, M_VG_HIGH);
			err_v_vb = safety_volt(tmp_volt_vb, M_VB_LOW, M_VB_HIGH);
			err_discon = safety_disconnection(tmp_volt_vb);
			ezI2Cbuf[MEM_R_STATUS1] = CMB_FLAGS_STATUS1(err_wdclk, err_discon, err_temp, err_v_vb, err_v_vg);
			ezI2Cbuf[MEM_R_STATUS2] = CMB_FLAGS_STATUS2(err_v_3v3);
*/
		}
		
		if(flag_tb_1ms)
		{
			flag_tb_1ms = 0;
			
		}
		
		//EZI2C Write complete
        if (0u != (I2C_1_EzI2CGetActivity() & I2C_1_EZI2C_STATUS_WRITE1))
        {
			//...
			i2c_flag = 1;
			i2c_flag = 0;			
        }
    }
}
