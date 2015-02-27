//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// fm_misc: Slave R/W
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_master_slave_comm.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************

//flexsea_payload.c:
extern unsigned char start_listening_flag;
extern unsigned char xmit_flag;
extern uint8_t comm_str_xmit[COMM_STR_BUF_LEN];
extern uint8_t cmd_xmit;

//FlexSEA:
extern unsigned char payload_str[];
extern unsigned char comm_str[COMM_STR_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Sequentially acquire data from a slave
//Will request a new read every time it's called
//Should we include a mechanism to insert Slave commands here? I think so
uint16_t slave_comm(uint8_t slave, uint8_t port, uint8_t autosample)
{
	static uint16_t cnt = 0;
	uint8_t bytes = 0, bytes2 = 0;

	if(!xmit_flag)
	{
		if(autosample)
		{
			//Using Special Command 1:
			bytes = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
					KEEP, 0, KEEP, 0, 0);

			//Then we package and send it out:
			bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD
			flexsea_send_serial_slave(port, comm_str, bytes2 + 1);
			start_listening_flag = 1;
		}
	}
	else
	{
		//xmit flag is high, we skip refreshing the sensors to send one packet

		flexsea_send_serial_slave(port, comm_str_xmit, COMM_STR_BUF_LEN);	//ToDo: this will always send the max length, not what we want.

		//ToDo: this is ugly, I need a better solution. Table with [CMD Code][R/W][Arguments]?
		//The new R/W commands will fix that
        if((cmd_xmit == CMD_IMU_READ) || (cmd_xmit == CMD_ENCODER_READ) || (cmd_xmit == CMD_STRAIN_READ) || (cmd_xmit == CMD_ANALOG_READ) \
        		|| (cmd_xmit == CMD_CTRL_I_READ) || (cmd_xmit == CMD_R(CMD_SPECIAL_1)))
        {
            //Place code here to deal with slave answering
            start_listening_flag = 1;
        }

        //Lowers the flag
        xmit_flag = 0;
	}

	return cnt;
}

/*
//Sequentially acquire data from a slave
//Will request a new read every time it's called
//Should we include a mechanism to insert Slave commands here? I think so
uint16_t slave_comm(uint8_t slave, uint8_t port, uint8_t autosample)
{
	static uint16_t cnt = 0;
	uint8_t bytes = 0, bytes2 = 0;

	if(!xmit_flag)
	{
		if(autosample)
		{
			//We start by generating 1 read request:
			switch(cnt)
			{
				case 0:
					bytes = tx_cmd_strain_read(slave);
					cnt++;
					break;
				case 1:
					bytes = tx_cmd_encoder_read(slave);
					cnt++;
					break;
				case 2:
					bytes = tx_cmd_imu_read(slave, 0, 3);
					cnt++;
					break;
				case 3:
					bytes = tx_cmd_analog_read(slave, 0, 1);
					cnt++;
					break;
				case 4:
					bytes = tx_cmd_ctrl_i_read(slave);
					cnt = 0;	//Last command resets the counter
					break;
			}

			//Then we package and send it out:
			bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD
			flexsea_send_serial_slave(port, comm_str, bytes2 + 1);
			start_listening_flag = 1;
		}
	}
	else
	{
		//xmit flag is high, we skip refreshing the sensors to send one packet

		flexsea_send_serial_slave(port, comm_str_xmit, COMM_STR_BUF_LEN-5);	//ToDo: this will always send the max length, not what we want.

		//ToDo: this is ugly, I need a better solution. Table with [CMD Code][R/W][Arguments]?
		//The new R/W commands will fix that
        if((cmd_xmit == CMD_IMU_READ) || (cmd_xmit == CMD_ENCODER_READ) || (cmd_xmit == CMD_STRAIN_READ) || (cmd_xmit == CMD_ANALOG_READ) || (cmd_xmit == CMD_CTRL_I_READ))
        {
            //Place code here to deal with slave answering
            start_listening_flag = 1;
        }

        //Lowers the flag
        xmit_flag = 0;
	}

	return cnt;
}
*/

//Simple test code:
void write_test_cmd_execute(uint8_t port, uint8_t value)
{
	uint32_t bytes = 0, bytes2 = 0;

	//bytes = tx_cmd_clutch_write(FLEXSEA_EXECUTE_1, value);
	bytes = tx_cmd_encoder_read(FLEXSEA_EXECUTE_1);
	bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD

	flexsea_send_serial_slave(port, comm_str, bytes2 + 1);
}

//Simple test code, modified for the new Special Command:
void write_test_cmd_execute2(uint8_t port, uint8_t value)
{
	uint32_t bytes = 0, bytes2 = 0;

	//controller_w (Write New Controller): KEEP/CHANGE
	//controller (New controller): ignored if ctrl_w == KEEP
	//encoder_w (Write New Encoder value): KEEP/CHANGE
	//encoder_cnt (New encoder count): ignored if encoder_w == KEEP
	//current: current controller setpoint
	bytes = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, value);

	bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD

	flexsea_send_serial_slave(port, comm_str, bytes2 + 1);
}

