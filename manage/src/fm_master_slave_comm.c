//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
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

uint8_t tmp_rx_command_spi[PAYLOAD_BUF_LEN];
uint8_t tmp_rx_command_485_1[PAYLOAD_BUF_LEN];
uint8_t tmp_rx_command_485_2[PAYLOAD_BUF_LEN];

struct slave_comm_s slaves_485_1, slaves_485_2;

//****************************************************************************
// External variable(s)
//****************************************************************************

//flexsea_payload.c:
extern uint8_t receive_485_1, receive_485_2;
extern unsigned char xmit_flag_1, xmit_flag_2;
extern uint8_t comm_str_xmit_1[COMM_STR_BUF_LEN], comm_str_xmit_2[COMM_STR_BUF_LEN];
extern uint8_t cmd_xmit_1, cmd_xmit_2;

//FlexSEA:
extern unsigned char payload_str[];
extern unsigned char comm_str[COMM_STR_BUF_LEN];

//flexsea_local.c:
extern uint8_t cmd_ready_spi;
extern uint8_t cmd_ready_485_1;
extern uint8_t cmd_ready_485_2;

//flexsea_comm.c:
extern uint8_t rx_command_spi[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
extern uint8_t rx_command_485_1[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
extern uint8_t rx_command_485_2[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Manage can be in slave_comm_mode = TRANSPARENT or slave_comm_mode = AUTOSAMPLING
//TRANSPARENT: Manage routes communication between the Master and the Slaves. All
//	the timings come from the Master (Manage routes as fast as possible)
//AUTOSAMPLING: Manage will do periodic Write/Read to n slaves and update a local structure
//	Master can Write/Read to that structure at any point. The timing of the communications with
//	the Master doesn't influence the timing of the communications between Manage and its slave(s)
//	other than the fact that a new packet from Master will have priority for the next slot.
//The 2 slave busses can have a different slave_comm_mode.

//Prepares the structures:
void init_master_slave_comm(void)
{
	//Port #1:
	slaves_485_1.mode = SC_TRANSPARENT;
	slaves_485_1.port = PORT_RS485_1;
	slaves_485_1.xmit.flag = 0;
	slaves_485_1.xmit.length = COMM_STR_BUF_LEN;
	slaves_485_1.xmit.cmd = 0;
	slaves_485_1.xmit.listen = 0;
	slaves_485_1.autosample.flag = 0;
	slaves_485_1.autosample.length = COMM_STR_BUF_LEN;
	slaves_485_1.autosample.cmd = 0;
	slaves_485_1.autosample.listen = 0;

	//Port #2:
	slaves_485_2.mode = SC_TRANSPARENT;
	slaves_485_2.port = PORT_RS485_1;
	slaves_485_2.xmit.flag = 0;
	slaves_485_2.xmit.length = COMM_STR_BUF_LEN;
	slaves_485_2.xmit.cmd = 0;
	slaves_485_2.xmit.listen = 0;
	slaves_485_2.autosample.flag = 0;
	slaves_485_2.autosample.length = COMM_STR_BUF_LEN;
	slaves_485_2.autosample.cmd = 0;
	slaves_485_2.autosample.listen = 0;
}

//ToDo terrible code, redo!

//This function gets called at a much higher frequency than the slave communication to
//make sure that we don't add delays in Transparent mode. autosample_trig will clock the
//autosampling state machine(s)
uint16_t slave_comm(uint8_t *autosample_trig)
{
	static uint16_t cnt = 0;
	uint8_t bytes = 0, bytes2 = 0;

	//Slave bus #1:
	//=============

	if(slaves_485_1.mode == SC_TRANSPARENT)
	{
		//In Transparent mode we do our best to route packets as fast as possible

		//New data ready to be transmitted?
		if(slaves_485_1.xmit.flag == 1)
		{
			//Transmit data:
			write_to_slave_xmit(&slaves_485_1);

	        //We are done, lower the flag
	        slaves_485_1.xmit.flag = 0;
		}
	}
	else if(slaves_485_1.mode == SC_AUTOSAMPLING)
	{
		//Autosampling is enabled. Will be bypassed is xmit_flag is set.

		//New data ready to be transmitted?
		if(slaves_485_1.xmit.flag == 1)
		{
			//Transmit data:
			write_to_slave_xmit(&slaves_485_1);

	        //We are done, lower the flag
	        slaves_485_1.xmit.flag = 0;
		}
		else
		{
			//No bypassing

			if(autosample_trig == 1)
			{
				//Time to send a new packet:
				slaves_485_1_autosample();

				autosample_trig = 0;
			}
		}

	}

	return 0;
/*
	if(!xmit_flag_1)
	{
		if(autosample)
		{
			//Using Special Command 1:
			bytes = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
					KEEP, 0, KEEP, 0, 0);

			//Then we package and send it out:
			bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD
			flexsea_send_serial_slave(PORT_RS485_1, comm_str, bytes2 + 1);
			receive_485_1 = 1;
		}
	}
	else
	{
		//xmit flag is high, we skip refreshing the sensors to send one packet

		flexsea_send_serial_slave(PORT_RS485_1, comm_str_xmit_1, COMM_STR_BUF_LEN);	//ToDo: this will always send the max length, not what we want.

		//ToDo: this is ugly, I need a better solution. Table with [CMD Code][R/W][Arguments]?
		//The new R/W commands will fix that
        if((cmd_xmit_1 == CMD_IMU_READ) || (cmd_xmit_1 == CMD_ENCODER_READ) || (cmd_xmit_1 == CMD_STRAIN_READ) || (cmd_xmit_1 == CMD_ANALOG_READ) \
        		|| (cmd_xmit_1 == CMD_CTRL_I_READ) || (cmd_xmit_1 == CMD_R(CMD_SPECIAL_1)))
        {
            //Place code here to deal with slave answering
        	receive_485_1 = 1;
        }

        //Lowers the flag
        xmit_flag_1 = 0;
	}

	//Slave bus #2:
	//=============

	if(!xmit_flag_2)
	{
		if(autosample)
		{
			//Using Special Command 1:
			bytes = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_2, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
					KEEP, 0, KEEP, 0, 0);

			//Then we package and send it out:
			bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD
			flexsea_send_serial_slave(PORT_RS485_2, comm_str, bytes2 + 1);
			receive_485_2 = 1;
		}
	}
	else
	{
		//xmit flag is high, we skip refreshing the sensors to send one packet

		flexsea_send_serial_slave(PORT_RS485_2, comm_str_xmit_2, COMM_STR_BUF_LEN);	//ToDo: this will always send the max length, not what we want.

		//ToDo: this is ugly, I need a better solution. Table with [CMD Code][R/W][Arguments]?
		//The new R/W commands will fix that
        if((cmd_xmit_2 == CMD_IMU_READ) || (cmd_xmit_2 == CMD_ENCODER_READ) || (cmd_xmit_2 == CMD_STRAIN_READ) || (cmd_xmit_2 == CMD_ANALOG_READ) \
        		|| (cmd_xmit_2 == CMD_CTRL_I_READ) || (cmd_xmit_2 == CMD_R(CMD_SPECIAL_1)))
        {
            //Place code here to deal with slave answering
        	receive_485_2 = 1;
        }

        //Lowers the flag
        xmit_flag_2 = 0;
	}

	return cnt;
	*/
}

//Sends a packet to RS-485, xmit mode. Sets the Listen flag if needed.
void write_to_slave_xmit(struct slave_comm_s *slave)
{
	//Transmit data:
	flexsea_send_serial_slave(slave->port, slave->xmit.str, slave->xmit.length);

	//Are we trying to read?
    if(IS_CMD_RW(slave->xmit.cmd) == READ)
    {
        //We expect an answer, start listening:
    	slave->xmit.listen = 1;
    }
}

//Sends a packet to RS-485, autosample mode. Sets the Listen flag if needed.
void write_to_slave_autosample(struct slave_comm_s *slave)
{
	//Transmit data:
	flexsea_send_serial_slave(slave->port, slave->autosample.str, slave->autosample.length);

	//Are we trying to read?
    if(IS_CMD_RW(slave->autosample.cmd) == READ)
    {
        //We expect an answer, start listening:
    	slave->autosample.listen = 1;
    }
}

//State-machine for the autosampling on bus #1
void slaves_485_1_autosample(void)
{
	/*
	static uint16_t cnt = 0;
	uint8_t bytes = 0, bytes2 = 0;

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
	*/
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

//Did we receive new commands? Can we parse them?
void parse_master_slave_commands(uint8_t *new_cmd)
{
	volatile uint32_t result = 0, i = 0;

	//Valid communication from SPI?
	if(cmd_ready_spi != 0)
	{
		cmd_ready_spi = 0;

		//Cheap trick to get first line	//ToDo: support more than 1
		for(i = 0; i < PAYLOAD_BUF_LEN; i++)
		{
			tmp_rx_command_spi[i] = rx_command_spi[0][i];
		}
		// parse the command and execute it
		result = payload_parse_str(tmp_rx_command_spi);

		//LED:
		*new_cmd = 1;
	}

	//Valid communication from RS-485 #1?
	if(cmd_ready_485_1 != 0)
	{
		cmd_ready_485_1 = 0;

		//Cheap trick to get first line	//ToDo: support more than 1
		for(i = 0; i < PAYLOAD_BUF_LEN; i++)
		{
			tmp_rx_command_485_1[i] = rx_command_485_1[0][i];
		}
		// parse the command and execute it
		result = payload_parse_str(tmp_rx_command_485_1);
	}

	//Valid communication from RS-485 #2?
	if(cmd_ready_485_2 != 0)
	{
		cmd_ready_485_2 = 0;

		//Cheap trick to get first line	//ToDo: support more than 1
		for(i = 0; i < PAYLOAD_BUF_LEN; i++)
		{
			tmp_rx_command_485_2[i] = rx_command_485_2[0][i];
		}
		// parse the command and execute it
		result = payload_parse_str(tmp_rx_command_485_2);
	}
}

//Simple test code:
void write_test_cmd_execute(uint8_t port, uint8_t slave, uint8_t value)
{
	uint32_t bytes = 0, bytes2 = 0;

	//bytes = tx_cmd_clutch_write(FLEXSEA_EXECUTE_1, value);
	bytes = tx_cmd_encoder_read(slave);
	bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD

	flexsea_send_serial_slave(port, comm_str, bytes2 + 1);
}

//Simple test code, modified for the new Special Command:
void write_test_cmd_execute2(uint8_t port, uint8_t slave, uint8_t value)
{
	uint32_t bytes = 0, bytes2 = 0;

	//controller_w (Write New Controller): KEEP/CHANGE
	//controller (New controller): ignored if ctrl_w == KEEP
	//encoder_w (Write New Encoder value): KEEP/CHANGE
	//encoder_cnt (New encoder count): ignored if encoder_w == KEEP
	//current: current controller setpoint
	bytes = tx_cmd_ctrl_special_1(slave, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, value);

	bytes2 = comm_gen_str(payload_str, bytes + 1);	//Might not need the +1, TBD

	flexsea_send_serial_slave(port, comm_str, bytes2 + 1);
}

