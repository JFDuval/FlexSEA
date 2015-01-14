/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "main.h"

//Variables:
extern int16 adc_res[];
extern uint8 flag_tb10ms, flag_tb_1ms;

//EZI2C:
uint8 ezI2Cbuf[EZI2C_BUF_SIZE];

//From isr_wdclk:
extern uint8 flag_wdclk;

extern uint16 led_period;

//Prepares the buffer
void init_ezI2Cbuf(void)
{
	int i = 0;
	
	//Master write: all 0
	for(i = 0; i < EZI2C_WBUF_SIZE; i++)
	{
		ezI2Cbuf[i] = 0;
	}
	//Master read: test data
	for(i = EZI2C_WBUF_SIZE; i < EZI2C_BUF_SIZE; i++)
	{
		//ezI2Cbuf[i] = i;	//Test only
		ezI2Cbuf[i] = 0;
	}
}

void init_peripherals(void)
{
	//Sequencing ADC:
	ADC_SAR_Seq_1_Start();
	ADC_SAR_Seq_1_IRQ_Enable();
	ADC_SAR_Seq_1_StartConvert();
	
	//Timer 1 (1ms timebase):
	Timer_1_Start();
	isr_t1_Start();
	
	//EZI2C:	
	I2C_1_EzI2CSetBuffer1(EZI2C_BUF_SIZE, EZI2C_WBUF_SIZE, ezI2Cbuf);
	init_ezI2Cbuf();
	I2C_1_Start();
	
	//WDCLK:
	Control_Reg_2_Write(100);	//500Hz min.
	isr_wdclk_Start();
}

//MCP9700A temperature sensor:
//MCP9700A: Vout = Tc * Ta + V0C, Ta = (Vout - V0C)/Tc. Tc = 10mV/C, V0C = 500mV.
//500mV = (0.5/5)*2048 ~= 205. 326 - 205 = 121 ticks
//Ticks to Volts: 5/2048 = 0.0024, Volts to Celcius:  1/0.01 = 100
//Combined: 0.24 ~= 1/4 so I can shift the difference by 2 and get Celcius:
//Ta = (CH2 - 205) >> 2;
int16 read_temp(void)
{
	return ((adc_res[ADC_TEMP] - MCP_TEMP_OFFSET) >> MCP_TEMP_SHIFT);
}

//VB_SNS: Battery voltage sensing. Returns value in mV.
uint16 read_vb(void)
{
	return((uint16)adc_res[ADC_VB] * VB_GAIN);
}

//VG_SNS: Intermediate voltage sensing. Returns value in mV.
uint16 read_vg(void)
{
	uint32 tmp1 = (uint16)adc_res[ADC_VG] * VG_GAIN;
	uint32 tmp2 = tmp1 >> VG_OFFSET;
	return((uint16)tmp2);
}

//M3V3_SNS: 3V3 logic voltage sensing. Returns value in mV.
uint16 read_3v3(void)
{
	uint32 tmp1 = (uint16)adc_res[ADC_M3V3] * M3V3_GAIN;
	uint32 tmp2 = tmp1 >> M3V3_OFFSET;
	return((uint16)tmp2);
}

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

/* [] END OF FILE */
