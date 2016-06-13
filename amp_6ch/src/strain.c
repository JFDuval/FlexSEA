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
#include "cyapicallbacks.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

volatile uint16 adc_delsig_dma_array[STRAIN_BUF_LEN];
struct strain_s strain[STRAIN_CHANNELS];

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static void dma_2_config(void);
static void init_adc_delsig_dma_array(void);

//****************************************************************************
// Puvblic Function(s)
//****************************************************************************

//Enables the peripherals associated with the strain amplifier and
//sets the default values.
//Make sure that you initialize I2C1 first!
void init_strain(void)
{
	int i = 0, j = 0;
	
	//Array prep:
	//=-=-=-=-=-=
	init_adc_delsig_dma_array();
	
	//Peripherals:
	//=-=-=-=-=-=
	
	//16-bits ADC:
	ADC_DelSig_1_Start();
	//ADC_DelSig_1_IRQ_Enable();
	dma_2_config();
	isr_delsig_StartEx(isr_delsig_Interrupt_InterruptCallback);
	
	//Defaults:
	//=-=-=-=-=-=
	for(i = 0; i < STRAIN_CHANNELS; i++)
	{
		strain[i].offset = STRAIN_DEFAULT_OFFSET;

		for(j = 0; j < STRAIN_BUF_LEN; j++)
		{
			strain[i].strain_raw[j] = 0;
		}
		strain[i].strain_filtered = 0;
		strain_config(i, strain[i].offset);
	}
	
	ADC_DelSig_1_StartConvert();
}

//Configure the strain gauge amplifier
//6-ch, 2 per digital pot. 
void strain_config(uint8 ch, uint8 offs)
{
	uint8 i2c_init_buf[2];
	uint8 addr = 0;
	
	//Assign addresses
	switch(ch)
	{
		case 0:
			i2c_init_buf[0] = STRAIN_OFFSET_A;
			addr = I2C_POT_ADDR_CH1;
			break;
		case 1:
			i2c_init_buf[0] = STRAIN_OFFSET_B;
			addr = I2C_POT_ADDR_CH1;
			break;
		case 2:
			i2c_init_buf[0] = STRAIN_OFFSET_A;
			addr = I2C_POT_ADDR_CH2;
			break;
		case 3:
			i2c_init_buf[0] = STRAIN_OFFSET_B;
			addr = I2C_POT_ADDR_CH2;
			break;
		case 4:
			i2c_init_buf[0] = STRAIN_OFFSET_A;
			addr = I2C_POT_ADDR_CH3;
			break;
		case 5:
			i2c_init_buf[0] = STRAIN_OFFSET_B;
			addr = I2C_POT_ADDR_CH3;
			break;
		default:
			return;
			break;
	}
	
	//Offset:
	i2c_init_buf[1] = offs;		//Offset
	I2C_1_MasterWriteBuf(addr, (uint8 *) i2c_init_buf, 2, I2C_1_MODE_COMPLETE_XFER);	
	CyDelayUs(100);
}

//Returns the latest filtered strain measurement
uint16 strain_read(uint8 ch)
{
	//ADC is auto-sampling, this function simply returns the last filtered value
	
	return strain[ch].strain_filtered;
}

//Moving average filter:
void strain_filter(void)
{
	uint i = 0;
	uint32 sum = 0;
	uint8 cnt = 0;
	uint16 avg = 0;
	
	//Average for each channel:
	for(i = 0; i < STRAIN_CHANNELS; i++)
	{
		//Zero variables:
		sum = 0;
		avg = 0;
		
		//Shift buffer and sum all but last term
		for(cnt = 0; cnt < STRAIN_BUF_LEN; cnt++)
		{
			sum += strain[i].strain_raw[cnt];
		}
			
		//Average
		avg = (uint16)(sum >> STRAIN_SHIFT);
		
		//Store in structure:
		strain[i].strain_filtered = avg;
		//strain_filtered = avg;
	}
}

//Copy latest filtered values to the EZI2C structure
void strain_to_ezi2c(void)
{
	ezI2Cbuf[MEM_R_CH1_H] = (uint8)((strain[0].strain_filtered >> 8) & 0xFF);
	ezI2Cbuf[MEM_R_CH1_L] = (uint8)((strain[0].strain_filtered) & 0xFF);
	
	ezI2Cbuf[MEM_R_CH2_H] = (uint8)((strain[1].strain_filtered >> 8) & 0xFF);
	ezI2Cbuf[MEM_R_CH2_L] = (uint8)((strain[1].strain_filtered) & 0xFF);
	
	ezI2Cbuf[MEM_R_CH3_H] = (uint8)((strain[2].strain_filtered >> 8) & 0xFF);
	ezI2Cbuf[MEM_R_CH3_L] = (uint8)((strain[2].strain_filtered) & 0xFF);
	
	ezI2Cbuf[MEM_R_CH4_H] = (uint8)((strain[3].strain_filtered >> 8) & 0xFF);
	ezI2Cbuf[MEM_R_CH4_L] = (uint8)((strain[3].strain_filtered) & 0xFF);
	
	ezI2Cbuf[MEM_R_CH5_H] = (uint8)((strain[4].strain_filtered >> 8) & 0xFF);
	ezI2Cbuf[MEM_R_CH5_L] = (uint8)((strain[4].strain_filtered) & 0xFF);
	
	ezI2Cbuf[MEM_R_CH6_H] = (uint8)((strain[5].strain_filtered >> 8) & 0xFF);
	ezI2Cbuf[MEM_R_CH6_L] = (uint8)((strain[5].strain_filtered) & 0xFF);
}

/*
//With DMA transfers we get a full buffer (6 bytes) per interrupt
//Note: we take 6 samples and ignore the first 2. This is a workaround, as the first 2 values are often contaminated.
uint16 strain_filter_dma(void)
{
	uint32 sum = 0;
	uint8 cnt = 0;
	uint16 avg = 0;
	
	//Sum all the terms
	for(cnt = 2; cnt < STRAIN_BUF_LEN; cnt++)
	{
		sum += adc_delsig_dma_array[cnt];
	}
	
	//Average
	avg = (uint16)(sum >> STRAIN_SHIFT);
	
	//Store in structure:
	strain.filtered_strain = avg;
	adc_strain_filtered = avg;
	
	return avg;	
}
*/

/*
//Copy of the test code used in main.c to test the hardware:
void strain_test_blocking(void)
{
	//Strain Amplifier test:
	
	uint8 i2c_test_wbuf[9];
	uint8 vr1 = 0;
	uint8 ledg_state = 0;
	
	i2c_test_wbuf[0] = STRAIN_OFFSET;
	i2c_test_wbuf[1] = 127;	//Offset of ~ V/2
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
		
		CyDelayUs(1000);
	}
}
*/

//****************************************************************************
// Private Function(s)
//****************************************************************************

//DMA for Delta Sigma ADC.
static void dma_2_config(void)
{
	/* Variable declarations for DMA_2 */
	/* Move these variable declarations to the top of the function */
	uint8 DMA_2_Chan;
	uint8 DMA_2_TD[STRAIN_CHANNELS];

	/* DMA Configuration for DMA_2 */
	#define DMA_2_BYTES_PER_BURST 		2
	#define DMA_2_REQUEST_PER_BURST 	1
	#define DMA_2_SRC_BASE 				(CYDEV_PERIPH_BASE)
	#define DMA_2_DST_BASE 				(CYDEV_SRAM_BASE)
	
	DMA_2_Chan = DMA_2_DmaInitialize(DMA_2_BYTES_PER_BURST, DMA_2_REQUEST_PER_BURST, 
	    HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));
	DMA_2_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_2_TD[0], DMA2_BYTES_PER_XFER, DMA_2_TD[0], DMA_2__TD_TERMOUT_EN | TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)ADC_DelSig_1_DEC_SAMP_PTR), LO16((uint32)adc_delsig_dma_array));
	CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
	CyDmaChEnable(DMA_2_Chan, 1);
}

//Fills the array with zeros
static void init_adc_delsig_dma_array(void)
{
	int i = 0, j = 0;
	
	//For each channel
	for(i = 0; i < STRAIN_CHANNELS; i++)
	{
		//For each sample
		//for(j = 0; j < STRAIN_BUF_LEN; j++)
		{
			//adc_delsig_dma_array[i][j] = 0;
			adc_delsig_dma_array[i] = 0;
		}
	}
}
