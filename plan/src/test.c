//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// test: Test code
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/test.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

void test_code(void)
{
	test_code_plan_manage_comm();
}

//PWM triangle wave
void test_code_1(void)
{
	int numb = 0;
	int32_t pwmdc = 0;
	uint8_t state = 0;

    //Initial configuration:

    //Controller = open
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
    usleep(10000);
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
    usleep(10000);

    printf("Ramping up...\n");
    while(!kbhit())
    {
    	switch(state)
    	{
    		case 0:
    			//Ramp up
    			pwmdc += PWM_STEP;
    			if(pwmdc >= MAX_PWM)
    			{
    				printf("Reached the positive maximum\n");
    				pwmdc = MAX_PWM;
    				state = 1;
    			}
    			else
    			{
    				state = 0;
    			}
    			break;
    		case 1:
    			//Ramp down
    			pwmdc -= (4*PWM_STEP);
    			if(pwmdc <= 0)
    			{
    				printf("Reached the minimum\n");
    				pwmdc = 0;
    				state = 2;
    			}
    			else
    			{
    				state = 1;
    			}
    			break;
    		case 2:
    			//One cycle completed, pause for a while
    			printf("One cycle completed, pause for a while\n");
    			sleep(5);

    			printf("Braking sequence in case it's still spinning...\n");
    			braking_sequence(10, 100000);
    			sleep(5);

    			printf("Ramping up...\n");
    			state = 0;
    			break;
    	}

    	//Prepare the command:
    	numb = tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, pwmdc);

    	//Communicate with the slave:
    	flexsea_send_serial_slave(PORT_SPI, comm_str, numb);

    	//800 steps to go from stop to max pos, we want this to happen in 15s
    	//15/800 = 18.75ms
        usleep(18750);

    }

    //Done with the experiment, drop PWM to 0:
    numb = tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, 0);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
}

//Plan <> Manage Communication
void test_code_plan_manage_comm(void)
{
	int numb = 0;

    printf("Plan <> Manage Communication Speed Test Code\n");

    while(!kbhit())
    {
    	//Prepare the command:
    	numb = tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);

    	//Communicate with the slave:
    	flexsea_send_serial_slave(PORT_SPI, comm_str, numb);

    	//Delay
        usleep(100);

    }
}
