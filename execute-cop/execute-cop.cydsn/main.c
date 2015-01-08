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

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	Control_Reg_1_Write(1);	//PWM pass-through
	
	//Disable shorted leads
	SL_EN_Write(0);

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
		ELED_Write(1);
		SL_CLK_Write(1);
		//CyDelay(70);
		ELED_Write(0);
		SL_CLK_Write(0);
		//CyDelay(70);
    }
}

/* [] END OF FILE */
