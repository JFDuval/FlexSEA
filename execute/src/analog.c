//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// analog: ADC configurations, read & filter functions
//****************************************************************************

//Note: this is for the analog functionality of the expansion connector
// Current sensing and strain gauge amplification are in other files.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "analog.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

int16 adc1_res[ADC1_CHANNELS][ADC1_BUF_LEN];
int16 adc1_res_filtered[ADC1_CHANNELS];

int16 adc_dma_array[ADC2_BUF_LEN];
int16 adc_sar1_dma_array[ADC1_BUF_LEN + 1];
volatile uint8 amux_ch = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

void init_analog(void)
{
	//Analog amplifiers & multiplexer(s):
	Opamp_3_Start();
	AMux_1_Start();				//Start the MUX
	
	//ADC1:
	ADC_SAR_1_Start();
	adc_sar1_dma_config();
	isr_sar1_dma_Start();
	ADC_SAR_1_StartConvert();	//Start converting
	
	//PGA:
	PGA_1_Start();
	PGA_1_Enable();
	
	//PGA Gain:
	#ifdef PROJECT_CSEA_KNEE
	PGA_1_SetGain(PGA_1_GAIN_02);	//x2
	#else
	PGA_1_SetGain(PGA_1_GAIN_01);	//x1 (buffer)
	#endif	//PROJECT_CSEA_KNEE	
}

uint16 adc_avg8(uint16 new_data)
{
	uint32 sum = 0;
	static uint16 adc_avg_buf[8] = {0,0,0,0,0,0,0,0};
	static uint8 cnt = 0;
	uint16 avg = 0;
	
	//Shift buffer and sum 7/8 terms
	for(cnt = 1; cnt < 8; cnt++)
	{
		adc_avg_buf[cnt-1] = adc_avg_buf[cnt];
		sum += adc_avg_buf[cnt-1];
	}
	adc_avg_buf[7] = new_data;
	sum += new_data;
		
	//Average
	avg = (uint16)(sum >> 3);
	
	return avg;	
}

//Filters the ADC buffer
void filter_sar_adc(void)
{
	uint16 i = 0, j = 0;
	int32 tmp[ADC1_CHANNELS];
	
	//For each channel:
	for(i = 0; i < ADC1_CHANNELS; i++)
	{
		//For each value in the channel:
		for(j = 0; j < ADC1_BUF_LEN; j++)
		{
			//Add the values
			tmp[i] += adc1_res[i][j];
		}
		
		//And divide to get mean
		adc1_res_filtered[i] = (int16) (tmp[i] >> ADC1_SHIFT);
	}
}

//Returns one filtered value
int16 read_analog(uint8 ch)
{
	if(ch < ADC1_CHANNELS)
	{
		//Valid channel, return value
		return adc1_res_filtered[ch];
	}

	//Otherwise return 0
	return 0;
}

//DMA for ADC SAR 1 transfers (Expansion, VB_SNS, etc.)
//Triggers an ISR after 9 samples
void adc_sar1_dma_config(void)
{
	/* Variable declarations for DMA_5 */
	/* Move these variable declarations to the top of the function */
	uint8 DMA_5_Chan;
	uint8 DMA_5_TD[1];

	/* DMA Configuration for DMA_1 */
	#define DMA_5_BYTES_PER_BURST 		2
	#define DMA_5_REQUEST_PER_BURST 	1
	#define DMA_5_SRC_BASE 				(CYDEV_PERIPH_BASE)
	#define DMA_5_DST_BASE 				(CYDEV_SRAM_BASE)
	
	DMA_5_Chan = DMA_5_DmaInitialize(DMA_5_BYTES_PER_BURST, DMA_5_REQUEST_PER_BURST,
	    HI16(DMA_5_SRC_BASE), HI16(DMA_5_DST_BASE));
	DMA_5_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_5_TD[0], 18, DMA_5_TD[0], DMA_5__TD_TERMOUT_EN | TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_5_TD[0], LO16((uint32)ADC_SAR_1_SAR_WRK0_PTR), LO16((uint32)adc_sar1_dma_array));
	CyDmaChSetInitialTd(DMA_5_Chan, DMA_5_TD[0]);
	CyDmaChEnable(DMA_5_Chan, 1);

}

//DMA for ADC SAR 2 transfers (motor current sensing)
//Triggers an ISR after 5 transfers
void adc_sar2_dma_config(void)
{
	/* Variable declarations for DMA_1 */
	/* Move these variable declarations to the top of the function */
	uint8 DMA_1_Chan;
	uint8 DMA_1_TD[1];

	/* DMA Configuration for DMA_1 */
	#define DMA_1_BYTES_PER_BURST 		2
	#define DMA_1_REQUEST_PER_BURST 	1
	#define DMA_1_SRC_BASE 				(CYDEV_PERIPH_BASE)
	#define DMA_1_DST_BASE 				(CYDEV_SRAM_BASE)
	
	DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
	    HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
	DMA_1_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_1_TD[0], 10, DMA_1_TD[0], DMA_1__TD_TERMOUT_EN | TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)ADC_SAR_2_SAR_WRK0_PTR), LO16((uint32)adc_dma_array));
	CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
	CyDmaChEnable(DMA_1_Chan, 1);
}
