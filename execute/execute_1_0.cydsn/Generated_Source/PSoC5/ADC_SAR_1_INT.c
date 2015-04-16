/*******************************************************************************
* File Name: ADC_SAR_1_INT.c
* Version 3.0
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_SAR_1.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

#include <project.h>
#include "main.h"
#include "misc.h"

volatile uint16 adc1_result = 0;
volatile uint16 adc1_result_avg8 = 0;

/* `#END`  */


#if(ADC_SAR_1_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ADC_SAR_1_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( ADC_SAR_1_ISR )
    {
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */
		
		/*
		static uint8 toggle = 1;
		adc1_result = ADC_SAR_1_GetResult16();
		
		//Average
		adc1_result_avg8 = adc_avg8(adc1_result);

		//ADC frequency test
		toggle^=1;
		//EXP1_Write(toggle);
		*/
		
		static unsigned char cnt = 0;
		static unsigned char ch = 0;
	
		//Store last value
		adc1_res[ch][cnt] = ADC_SAR_1_GetResult16();
		
		//Increment counter
		cnt++;
		//Time to switch channel?
		if(cnt >= ADC1_BUF_LEN)
		{
			cnt = 0;
			
			if(ch >= ADC1_CHANNELS)
				ch = 0;
			else
				ch++;

			//Refresh MUX:
			ADC_SAR_1_StopConvert();
			AMux_1_Select(ch);				
			
			adc_sar1_flag = 1;
		}	
		
		ADC_SAR_1_StartConvert();
		
          /* `#END`  */

    }

#endif   /* End ADC_SAR_1_IRQ_REMOVE */

/* [] END OF FILE */
