/*******************************************************************************
* File Name: ADC_SAR_2_INT.c
* Version 2.10
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_SAR_2.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

#include <project.h>
#include "main.h"
extern int current_pid_setpoint, current_pid_measured;
extern unsigned char controller;

/* `#END`  */


#if(ADC_SAR_2_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ADC_SAR_2_ISR
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
    CY_ISR( ADC_SAR_2_ISR )
    {
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */
		
			unsigned int last_adc = 0;
			static unsigned char dactest = 0;
			unsigned int tmp = 0;
			
			//Read last ADC value
			last_adc = ADC_SAR_2_GetResult16();
			current_pid_measured = last_adc;	//Used by the current controller
			
			//Mirror on ADC:
			tmp = (last_adc >> 4) & 0xFF;			
			dactest = (unsigned char) tmp;
			VDAC8_2_SetValue(dactest);	
			
			if((controller == CTRL_CURRENT) || (controller == CTRL_IMPEDANCE))
			{
				//Current controller
				motor_current_pid_1(current_pid_setpoint, current_pid_measured);
				//ToDo update variables names
			}
	
          /* `#END`  */

    }

#endif   /* End ADC_SAR_2_IRQ_REMOVE */

/* [] END OF FILE */
