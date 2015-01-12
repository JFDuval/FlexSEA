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
extern uint8 flag_tb10ms;

void init_peripherals(void)
{
	//Sequencing ADC:
	ADC_SAR_Seq_1_Start();
	ADC_SAR_Seq_1_IRQ_Enable();
	ADC_SAR_Seq_1_StartConvert();
	
	//Timer 1 (1ms timebase):
	Timer_1_Start();
	isr_t1_Start();
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

int main()
{
	int16 temperature = 0;
	
	//Initialize and start peripherals:
    init_peripherals();
	
	// Enable global interrupts
	CyGlobalIntEnable;
	
	//PWM pass-through (ToDo program safety feature)
	Control_Reg_1_Write(1);	
	
	//Disable shorted leads
	SL_EN_Write(0);

    for(;;)
    {
		//For now we always generate the -4V5:
		SL_CLK_Write(1);
		SL_CLK_Write(0);
		
		//Update sensor data every 10ms:
		if(flag_tb10ms)
		{
			flag_tb10ms = 0;
			
			//Temperature:
			temperature = read_temp();
		}
    }
}

/* [] END OF FILE */
