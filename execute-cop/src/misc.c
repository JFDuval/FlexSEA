//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************

//Note: It's a sign that code is misplaced when this file gets long.


//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "misc.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 flag_tb10ms = 0, flag_tb_1ms = 0;
uint16 led_period = LED_PERIOD_NORM;

//****************************************************************************
// Public Function(s)
//****************************************************************************

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
	Control_Reg_2_Write(250);
	isr_wdclk_Start();
	
	//Safety code:
	init_safety();
}
