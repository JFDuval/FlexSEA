/*******************************************************************************
* File Name: ADC_SAR_2_INT.c
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

#include "ADC_SAR_2.h"



/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

#include "main.h"

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
        #ifdef ADC_SAR_2_ISR_INTERRUPT_CALLBACK
            ADC_SAR_2_ISR_InterruptCallback();
        #endif /* ADC_SAR_2_ISR_INTERRUPT_CALLBACK */          

        
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */
		
		/*
			unsigned int last_adc = 0;
			
			//Read last ADC value
			last_adc = ADC_SAR_2_GetResult16();
			ctrl.current.actual_val = last_adc - CURRENT_ZERO;	
			//Used by the current controller, 0 centered.
				
			if((ctrl.active_ctrl == CTRL_CURRENT) || (ctrl.active_ctrl == CTRL_IMPEDANCE))
			{
				//Current controller
				motor_current_pid(ctrl.current.setpoint_val, ctrl.current.actual_val);
			}
		*/
	
          /* `#END`  */
    }

#endif   /* End ADC_SAR_2_IRQ_REMOVE */

/* [] END OF FILE */
