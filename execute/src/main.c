//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// main: FlexSEA-Execute
//****************************************************************************

// FlexSEA: Flexible & Scalable Electronics Architecture

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "cyapicallbacks.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Power on delay with LEDs
	power_on();	     

	//Initialize all the peripherals
	init_peripherals();

	//Test code, use with care. Normal code might NOT run when enabled!
	//test_code_blocking();
	//test_code_non_blocking();
	
	//Project specific initialization code
	init_user();

	//Main loop
	while(1)
	{
		if(t1_new_value == 1)
		{
			//If the time share slot changed we run the timing FSM. Refer to
			//timing.xlsx for more details. 't1_new_value' updates at 10kHz,
			//each slot at 1kHz.
			
			t1_new_value = 0;
			
			//Timing FSM:
			switch(t1_time_share)
			{
				case 0:
					main_fsm_case_0();					
					break;				
				case 1:
					main_fsm_case_1();					
					break;				
				case 2:
					main_fsm_case_2();
					break;
				case 3:				
					main_fsm_case_3();					
					break;					
				case 4:
					main_fsm_case_4();				
					break;				
				case 5:
					main_fsm_case_5();			
					break;					
				case 6:
					main_fsm_case_6();						
					break;				
				case 7:					
					main_fsm_case_7();	
					break;				
				case 8:
					main_fsm_case_8();					
					break;
				case 9:
					main_fsm_case_9();	
					break;				
				default:
					break;
			}
			
			//The code below is executed every 100us, after the previous slot. 
			//Keep it short!					
			main_fsm_10kHz();			
		}
		else
		{
			//Asynchronous code goes here.
			main_fsm_asynchronous();			
		}
	}
}
