//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_adc: Analog to digital converter
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_adc.h"
#include "fm_adc.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

ADC_HandleTypeDef hadc1;
ADC_ChannelConfTypeDef sConfig;
ADC_MultiModeTypeDef multimode;

unsigned int adc_results[ADC_CHANNELS];
unsigned int adc_filtered_results[ADC_CHANNELS];

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

void init_adc1(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//Enable peripheral and GPIO clocks
    __ADC1_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();

    //AN0 to AN7 are on PA0 to PA7
	//AN0 & 1: 1/10kHz LPF
	//AN3 & 3: 1/10kHz LPF, 1<G<10
	//AN4 & 5: Buffered
	//AN6 & 7: Resistive dividers, buffered

    //Config inputs:
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //ADC1 config: (ToDo: test & optimize, use DMA and multiple conversions)
    //===========

    //Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION12b;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.NbrOfDiscConversion = 1;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = EOC_SINGLE_CONV;
    HAL_ADC_Init(&hadc1);

    //Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    //Configure the ADC multi-mode
    multimode.Mode = ADC_MODE_INDEPENDENT;
    multimode.TwoSamplingDelay = ADC_TWOSAMPLINGDELAY_5CYCLES;
    HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode);
}

unsigned int adc_conv(void)
{
	unsigned int result = 0;

	HAL_ADC_Start(&hadc1);
	while(HAL_ADC_PollForConversion(&hadc1, 5000) != HAL_OK);
	result = HAL_ADC_GetValue(&hadc1);

	return result;
}

