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

struct strain_s strain;
uint16 adc_strain_filtered = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

//Del Sig Int:
extern volatile uint16 adc_strain;

//****************************************************************************
// Function(s)
//****************************************************************************

//Enables the peripherals associated with the strain amplifier and
//sets the default values.
//Make sure that you initialize I2C first!
void init_strain(void)
{
	//Peripherals:
	//=-=-=-=-=-=
	
	Opamp_2_Start();		//VR1
	
	VDAC8_3_Start();		//VR2 reference
	Opamp_3_Start();		//VR2 buffer
	
	AMux_2_Start();			//ADC input, VO1 & VO2
	AMux_2_Select(0);		//Starts with SG_VO2, the final output
	
	//16-bits ADC:
	ADC_DelSig_1_Start();
	ADC_DelSig_1_IRQ_Enable();
	//ADC_DelSig_1_StartConvert();
	
	//Defaults:
	//=-=-=-=-=-=
	
	strain.offset = STRAIN_DEFAULT_OFFSET;
	strain.gain = STRAIN_DEFAULT_GAIN;
	strain.oref = STRAIN_DEFAULT_OREF;	
	strain.vo1 = 0;
	strain.vo2 = 0;
	strain.filtered_strain = 0;
	strain_config(strain.offset, strain.gain, strain.oref);
}

//Configure the strain gauge amplifier
void strain_config(uint8 offs, uint8 gain, uint8 oref)
{
	uint8 i2c_init_buf[2];
	
	//Output reference:
	VDAC8_3_SetValue(oref);	
	
	//Offset:
	i2c_init_buf[0] = STRAIN_OFFSET;
	i2c_init_buf[1] = offs;		//Offset
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_init_buf, 2, I2C_1_MODE_COMPLETE_XFER);	
	CyDelayUs(100);
	
	//Second stage gain:
	i2c_init_buf[0] = STRAIN_GAIN;
	i2c_init_buf[1] = gain;		//Gain
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_init_buf, 2, I2C_1_MODE_COMPLETE_XFER);
	CyDelayUs(100);
}

//Returns the latest filtered strain measurement
uint16 strain_read(void)
{
	//ADC is auto-sampling, this function simply returns the last filtered value
	
	//return strain.filtered_strain;	//Buggy
	return adc_strain_filtered;
}

//Moving average filter:
uint16 strain_filter(void)
{
	uint32 sum = 0;
	uint8 cnt = 0;
	uint16 avg = 0;
	static uint16 vo2_buf[STRAIN_BUF_LEN];
	
	//Shift buffer and sum all but last term
	for(cnt = 1; cnt < (STRAIN_BUF_LEN); cnt++)
	{
		vo2_buf[cnt-1] = vo2_buf[cnt];
		sum += vo2_buf[cnt-1];
	}
	
	//vo2_buf[STRAIN_BUF_LEN - 1] = strain.vo2;	//Buggy, see Evernote
	vo2_buf[STRAIN_BUF_LEN - 1] = adc_strain;
	sum += vo2_buf[STRAIN_BUF_LEN - 1];
		
	//Average
	avg = (uint16)(sum >> STRAIN_SHIFT);
	
	//Store in structure:
	strain.filtered_strain = avg;
	adc_strain_filtered = avg;
	
	return avg;	
}

//Copy of the test code used in main.c to test the hardware:
void strain_test_blocking(void)
{
	//Strain Amplifier test:
	
	uint8 i2c_test_wbuf[9];
	uint8 vr1 = 0;
	uint8 ledg_state = 0;
	
	VDAC8_3_SetValue(156);	
	i2c_test_wbuf[0] = STRAIN_OFFSET;
	i2c_test_wbuf[1] = 120;	//Offset of ~ V/2
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
	CyDelay(10);
	i2c_test_wbuf[0] = STRAIN_GAIN;
	i2c_test_wbuf[1] = 10;	//Relatively small gain
	I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
	
	i2c_test_wbuf[0] = STRAIN_OFFSET;
	while(1)
	{
		vr1++;		
		i2c_test_wbuf[1] = vr1;	//Enable this line to test the offset
		I2C_1_MasterWriteBuf(I2C_POT_ADDR, (uint8 *) i2c_test_wbuf, 2, I2C_1_MODE_COMPLETE_XFER);	
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelayUs(100);
	}
}
