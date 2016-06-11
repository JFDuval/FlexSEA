//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// test: Test code
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/test.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

void test_code(void)
{
	//test_code_plan_manage_comm();
	//test_code_2();
	//test_code_plan_2x_exec_comm();
	test_code_spc2_csea();
}

//PWM triangle wave
void test_code_1(void)
{
	int numb = 0;
	int32_t pwmdc = 0;
	uint8_t state = 0;

    //Initial configuration:

    //Controller = open
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_OPEN);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);  //Was comm_str_spi. ToDo is it ok?
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);    //Was comm_str_spi. ToDo is it ok?
    usleep(10000);
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_OPEN);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);  //Was comm_str_spi. ToDo is it ok?
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);    //Was comm_str_spi. ToDo is it ok?
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
    	numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, pwmdc);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);

    	//Communicate with the slave:
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);

        usleep(6000);

    }

    //Done with the experiment, drop PWM to 0:
    numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
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
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_OPEN);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
    usleep(10000);
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_OPEN);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
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
    	numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, pwmdc);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);

    	//Communicate with the slave:
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);

    	if(state == 0)
    		usleep(1750);
    	else
    		usleep(18000);

    }

    //Done with the experiment, drop PWM to 0:
    numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
}

//Plan <> Manage Communication
void test_code_plan_manage_comm(void)
{
	int numb = 0;

    printf("Plan <> Manage Communication Speed Test Code\n");

    while(!kbhit())
    {
    	//Prepare the command:
    	numb = tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, tmp_payload_xmit, PAYLOAD_BUF_LEN);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);

    	//Communicate with the slave:
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);

    	//Delay
        usleep(100000);

    }
}

//Plan <> Dual Execute Communication
void test_code_plan_2x_exec_comm(void)
{
	int numb = 0;

    printf("Plan <> Dual Execute Communication Speed Test Code\n");

    while(!kbhit())
    {
    	//Execute #1:

    	//Prepare the command:
        numb = tx_cmd_exp_pwro(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0xAA);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);

    	//Communicate with the slave:
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);

    	//Delay
        usleep(500);

        //Execute #2:

    	//Prepare the command:
        numb = tx_cmd_exp_pwro(FLEXSEA_EXECUTE_2, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0xCC);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);

    	//Communicate with the slave:
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);

    	//Delay
        usleep(500);
    }
}

//Special Command #2 - CSEA Knee test
void test_code_spc2_csea(void)
{
    int numb = 0, state = 0, rgb = 0, pwro = 0;
	int zk = 10, zi = 0;

    //Initial configuration:

    //Controller = impedance
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_IMPEDANCE);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
    usleep(10000);

    //Current gain
    numb = tx_cmd_ctrl_i_g(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 20, 25, 0);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
    usleep(10000);

    //Z gain
    numb = tx_cmd_ctrl_z_g(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, zk, zi, 0);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
    usleep(10000);


    printf("RGB via Spc2 Test\n");
    while(!kbhit())
    {
    	switch(state)
    	{
    		case 0:
    			rgb = 0;
    			break;
			case 1:
				rgb = 1;
				break;
			case 2:
				rgb = 2;
				break;
			case 3:
				rgb = 3;
				break;
			case 4:
				rgb = 4;
				break;
			default:
				rgb = 0;
				break;
    	}

    	state++;
    	if(state > 4)
    		state = 0;

    	if(state == 0)
            pwro = 255;
    	else
            pwro = 0;

        pwro = 0;
    	numb = tx_cmd_ctrl_special_2(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
                                        zk, zi, 0, rgb, pwro,\
    									KEEP, 0, 0, 0, 0);

        numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);
    	numb = COMM_STR_BUF_LEN;

    	#ifdef USE_SPI

        flexsea_spi_transmit(numb, comm_str_usb, 0);

    	//Can we decode what we received?
    	decode_spi_rx();

    	#endif

    	printf("RGB: %i.\n", rgb);
    	usleep(250000);
    }

    //Done with the experiment, drop PWM to 0:
    numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);
    numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
    flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
}

#ifdef __cplusplus
}
#endif
