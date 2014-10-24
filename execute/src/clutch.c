#include <project.h>
#include "clutch.h"

void clutch_output(uint8 value)
{
	if(value == CLUTCH_10V)
	{
		CLUTCH_10_Write(1);
		CLUTCH_24_Write(0);
	}
	else if(value == CLUTCH_24V)
	{
		CLUTCH_10_Write(0);
		CLUTCH_24_Write(1);
	}
	else
	{
		CLUTCH_10_Write(0);
		CLUTCH_24_Write(0);
	}		
}

//Call this function in t2_50ms to test
void clutch_test(void)
{
	static uint8 clutch_state = 1;
	
	//Clutch test
	clutch_state++;
	if(clutch_state >= 3)
		clutch_state = 0;

	if(clutch_state == 0)
		clutch_output(CLUTCH_OFF);
	else if(clutch_state == 1)
		clutch_output(CLUTCH_10V);
	else if(clutch_state == 2)
		clutch_output(CLUTCH_24V);	
}