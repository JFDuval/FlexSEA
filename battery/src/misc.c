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

uint8 flag_tb_1ms = 0;
//uint8 flag_tb10ms = 0;
uint16 led_period = LED_PERIOD_NORM;
uint8 led_mode = LED_MODE_PWM;

//****************************************************************************
// Public Function(s)
//****************************************************************************

void init_peripherals(void)
{
    //Timer 1 (1ms timebase):
	Timer_1_Start();
	isr_t1_StartEx(isr_t1_Interrupt_Callback);
    
	//Sequencing ADC:
	ADC_SAR_Seq_1_Start();
	ADC_SAR_Seq_1_IRQ_StartEx(ADC_SAR_Seq_1_ISR_Callback);
	ADC_SAR_Seq_1_StartConvert();	
	 
	//IDAC:
	IDAC_1_Start();
    Opamp_0_Start();
    Opamp_1_Start();

    //PWM_1 (Green LED)
    PWM_1_Start();
    PWM_1_WriteCompare(0);  //Off
    
    //PWM_2 (Red LED)
    PWM_2_Start();
    PWM_2_WriteCompare(0);  //Off
    
    //LEDs start at 0:
    LED_B_Write(0);
    
	//EZI2C:	
	I2C_1_EzI2CSetBuffer1(EZI2C_BUF_SIZE, EZI2C_WBUF_SIZE, ezI2Cbuf);
	init_ezI2Cbuf();
	I2C_1_Start();
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