//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// sensor_commut: Angle Sensor Motor Commutation
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "sensor_commut.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 hall_conv[6] = {5,4,6,2,3,1};

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	


//****************************************************************************
// Public Function(s)
//****************************************************************************

//Use before main while() as a basic test
void motor_stepper_test_blocking_1(int spd)
{
	uint8 hall_code_0 = 0, hall_code = 0;
	
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(spd);
	
	while(1)
	{
		hall_code_0++;
		hall_code_0 %= 6;
		hall_code = hall_conv[hall_code_0];
		
		Hall_Write(hall_code);

		
		LED_R_Write(hall_code & 0x01);
		LED_G_Write((hall_code & 0x02)>>1);
		LED_B_Write((hall_code & 0x04)>>2);
		
		CyDelay(10);
	}
}

//To test with the full stack, use this init...
void motor_stepper_test_init(int spd)
{
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(spd);	
}

//...and this runtime function
void motor_stepper_test_runtime(int div)
{
	//Call this function at 1ms intervals. The divider will
	//allow longer delays between steps.
	
	static uint8 hall_code_0 = 0, hall_code = 0;
	static int delay_cnt = 0;
	
	delay_cnt++;
	if(delay_cnt >= div)
	{
		delay_cnt = 0;
	
		hall_code_0++;
		hall_code_0 %= 6;
		hall_code = hall_conv[hall_code_0];
		
		Hall_Write(hall_code);		
	}	
}

//****************************************************************************
// Private Function(s)
//****************************************************************************
