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
	//test_code_plan_manage_comm();
	test_code_2();
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
    numb = comm_gen_str(payload_str, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
    usleep(10000);
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    numb = comm_gen_str(payload_str, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
    usleep(10000);

    printf("Ramping up...\n");
    while(!kbhit())
    {
    	switch(state)
    	{
    		case 0:
    			//Ramp up
    			pwmdc += TC_PWM_STEP;
    			if(pwmdc >= TC_MAX_PWM)
    			{
    				printf("Reached the positive maximum\n");
    				pwmdc = TC_MAX_PWM;
    				state = 1;
    			}
    			else
    			{
    				state = 0;
    			}
    			break;
    		case 1:
				//Ramp up
				pwmdc -= TC_PWM_STEP;
				if(pwmdc <= -TC_MAX_PWM)
				{
					printf("Reached the negative maximum\n");
					pwmdc = -TC_MAX_PWM;
					state = 0;
				}
				else
				{
					state = 1;
				}
				break;
    		/*
    		case 1:
    			//Ramp down
    			pwmdc -= (4*TC_PWM_STEP);
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
    		*/
    	}

    	//Prepare the command:
    	numb = tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, pwmdc);
    	numb = comm_gen_str(payload_str, numb);

    	//Communicate with the slave:
    	flexsea_send_serial_slave(PORT_SPI, comm_str, numb);

        usleep(6000);

    }

    //Done with the experiment, drop PWM to 0:
    numb = tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, 0);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
}

//Motor driver stress test: fast ramp-up, slow ramp-down
//(Kepco power supply isn't too happy with regen current)
void test_code_2(void)
{
	int numb = 0;
	int32_t pwmdc = 0;
	uint8_t state = 0;

    //Initial configuration:

    //Controller = open
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    numb = comm_gen_str(payload_str, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
    usleep(10000);
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    numb = comm_gen_str(payload_str, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str, numb);
    usleep(10000);

    printf("Motor Stress Test\n");
    while(!kbhit())
    {
    	switch(state)
    	{
    		case 0:
    			//Ramp up
    			pwmdc += TC_PWM_STEP;
    			if(pwmdc >= TC_MAX_PWM)
    			{
    				printf("Reached the positive maximum\n");
    				pwmdc = TC_MAX_PWM;
    				state = 1;
    			}
    			else
    			{
    				state = 0;
    			}
    			break;
    		case 1:
				//Ramp up
				pwmdc -= TC_PWM_STEP;
				if(pwmdc <= 0)
				{
					printf("Reached the minimum\n");
					pwmdc = 0;
					state = 0;
				}
				else
				{
					state = 1;
				}
				break;
    	}

    	//Prepare the command:
    	numb = tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, pwmdc);
    	numb = comm_gen_str(payload_str, numb);

    	//Communicate with the slave:
    	flexsea_send_serial_slave(PORT_SPI, comm_str, numb);

    	if(state == 0)
    		usleep(1750);
    	else
    		usleep(18000);

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
