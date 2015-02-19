//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_payload: deals with the "intelligent" data packaged in a comm_str
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea.h"
#include "flexsea_local.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned char payload_str[PAYLOAD_BUF_LEN];
unsigned char test_kp = 0, test_ki = 0, test_kd = 0;
unsigned char start_listening_flag = 0;
unsigned char uart_rx_test = 0, delay = 0;

unsigned char xmit_flag = 0;
uint8_t comm_str_xmit[COMM_STR_BUF_LEN];
uint8_t cmd_xmit = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

//From flexsea_local:
extern unsigned char board_id;
extern unsigned char board_up_id;
extern unsigned char board_sub1_id;
extern unsigned char board_sub2_id;

//From flexsea_comm:
extern unsigned char comm_str[COMM_STR_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Clears payload_str (all 0)
//ToDo remove, see below
unsigned int payload_clear_str(void)
{
    int i = 0;

    for(i = 0; i < PAYLOAD_BUF_LEN; i++)
    {
        payload_str[i] = 0;
    }

    return 0;
}

//Can be used to fill a buffer of any length with any value
//ToDo might move this to another file
void fill_uint8_buf(uint8_t *buf, uint32_t len, uint8_t filler)
{
	uint32_t i = 0;

	for(i = 0; i < len; i++)
	{
		buf[i] = filler;
	}
}

//Start a new payload_str - ToDo delete, see below
unsigned int payload_build_basic_str(unsigned char to)
{
    //Start fresh:
    payload_clear_str();

    //Addresses:
    payload_str[CP_XID] = board_id;
    payload_str[CP_RID] = to;

    return 0;
}

//New version of the command above
void prepare_empty_payload(uint8_t from, uint8_t to, uint8_t *buf, uint32_t len)
{
	//Start fresh:
	fill_uint8_buf(buf, len, 0);

    //Addresses:
    buf[CP_XID] = from;
    buf[CP_RID] = to;
}

//Add a buffer at the end of a partially filled payload buffer
//void todo(void)



//Is it addressed to me? To a board "below" me? Or to my Master?
unsigned int payload_check_slave_id(unsigned char *pldata)
{
    unsigned char cp_rid = pldata[CP_RID];

    if(cp_rid == board_id)
    {
        return ID_MATCH;
    }
    else if(cp_rid == board_sub1_id)	//First "lower" board. ToDo optimize this, needs to be more general
    {
        return ID_SUB1_MATCH;
    }
    else if(cp_rid == board_sub2_id)	//Second "lower" board. ToDo optimize this, needs to be more general
    {
        return ID_SUB2_MATCH;
    }
    else if(cp_rid == board_up_id)		//Master. ToDo optimize this, needs to be more general
    {
        return ID_UP_MATCH;
    }
    else
    {
        return ID_NO_MATCH;
    }

    return ID_NO_MATCH;
}

//Returns one if it was sent from a slave, 0 otherwise
uint8_t sent_from_a_slave(uint8_t *buf)
{
	//Slaves have higher addresses than their master.
	if(buf[CP_XID] > buf[CP_RID])
	{
		//Slave
		return 1;
	}
	else
	{
		//Master
		return 0;
	}

	//Should not happen
	return 0;
}

//Decode/parse received string
//ToDo fix: for now, supports only one command per string
unsigned int payload_parse_str(unsigned char *cp_str)
{
    unsigned char cmd = 0, output = PARSE_SUCCESSFUL, numb = 0;
    unsigned int id = 0;
    uint8_t i = 0;

    //Command
    cmd = cp_str[CP_CMD1];

    //First, check ID
    id = payload_check_slave_id(cp_str);
    if(id == ID_MATCH)
    {
        //It's addressed to me. What should I do with it?
        switch(cmd)
        {
			//Old / to change:            
            case CMD_MOVE_TRAP_ABSOLUTE:
                rx_move_trap_absolute(cp_str);
                break;                      
            case CMD_SET_Z_GAINS:
                rx_set_z_gains(cp_str);
                break;
			
			//System commands:
            case CMD_ACQ_MODE_WRITE:
            	rx_cmd_acq_mode_write(cp_str);
            	break;

            //Data commands:
            case CMD_MEM_READ:
                rx_cmd_mem_read(cp_str);
                break;
            case CMD_MEM_READ_REPLY:
            	rx_cmd_mem_read_reply(cp_str, 0);
                break;
				
			//Sensor commands:
			case CMD_ENCODER_WRITE:
				rx_cmd_encoder_write(cp_str);
				break;
			case CMD_ENCODER_READ:
				rx_cmd_encoder_read(cp_str);
				break;
			case CMD_ENCODER_READ_REPLY:
				rx_cmd_encoder_read_reply(cp_str);
				break;
			case CMD_STRAIN_CONFIG:
				rx_cmd_strain_config(cp_str);
				break;
			case CMD_STRAIN_READ:
				rx_cmd_strain_read(cp_str);
				break;
			case CMD_STRAIN_READ_REPLY:
				rx_cmd_strain_read_reply(cp_str);
				break;
			case CMD_IMU_READ:
				rx_cmd_imu_read(cp_str);
				break;
			case CMD_IMU_READ_REPLY:
				rx_cmd_imu_read_reply(cp_str);
				break;
				
			//Expansion commands:
			case CMD_CLUTCH_WRITE:
                rx_cmd_clutch_write(cp_str);
                break;  
			case CMD_ANALOG_READ:
                rx_cmd_analog_read(cp_str);
                break;  
			case CMD_ANALOG_READ_REPLY:
                rx_cmd_analog_read_reply(cp_str);
                break; 
				
			//Motor commands:
			case CMD_CTRL_MODE_WRITE:
                rx_cmd_ctrl_mode_write(cp_str);
                break;
			case CMD_CTRL_I_GAINS_WRITE:
                rx_cmd_ctrl_i_gains(cp_str);
                break;	
			case CMD_CTRL_O_WRITE:
                rx_cmd_ctrl_o_write(cp_str);
                break;
            case CMD_CTRL_I_WRITE:
                rx_cmd_ctrl_i_write(cp_str);
                break;
			case CMD_CTRL_I_READ:
                rx_cmd_ctrl_i_read(cp_str);
                break;
			case CMD_CTRL_I_READ_REPLY:
                rx_cmd_ctrl_i_read_reply(cp_str);
                break;
			case CMD_CTRL_P_GAINS_WRITE:                
                rx_cmd_ctrl_p_gains_write(cp_str);
                break;
			
			//Unknown command:	
            default:
                output = PARSE_UNKNOWN_CMD;
                break;
        }

        return output;
    }
    else if((id == ID_SUB1_MATCH) || (id == ID_SUB2_MATCH))
    {
        //For one of my slaves.

        //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
        numb = comm_gen_str(cp_str, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;    //Fixed length for now

        //Synchronous sending. Hacky... copy the comm_str in a new one, comm_str_xmit.

        for(i = 0; i < COMM_STR_BUF_LEN; i++)
        {
        	comm_str_xmit[i] = comm_str[i];
        }
        cmd_xmit = cmd;
        xmit_flag = 1;

        /*
		if(id == ID_SUB1_MATCH)
		{
			flexsea_send_serial_slave(PORT_RS485_1, comm_str, numb + 1);
		}
		else if(id == ID_SUB2_MATCH)
		{
			flexsea_send_serial_slave(PORT_RS485_2, comm_str, numb + 1);
		}

		//ToDo: this is ugly, I need a better solution. Table with [CMD Code][R/W][Arguments]?
        if((cmd == CMD_IMU_READ) || (cmd == CMD_ENCODER_READ) || (cmd == CMD_STRAIN_READ) || (cmd == CMD_ANALOG_READ) || (cmd == CMD_CTRL_I_READ))
        {
            //Place code here to deal with slave answering
            start_listening_flag = 1;

        }
        */
    }
    /*
    else if(id == ID_SUB2_MATCH)
    {
    	//For one of my slaves:

    	//Repackages the payload. ToDo: would be more efficient to just resend the comm_str
    	numb = comm_gen_str(cp_str, PAYLOAD_BUF_LEN);
    	numb = COMM_STR_BUF_LEN;    //Fixed length for now
    	flexsea_send_serial(0,comm_str, numb + 1);
    }
    */
    else if(id == ID_UP_MATCH)
    {
        //For my master:

        //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
        numb = comm_gen_str(cp_str, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;    //Fixed length for now
        flexsea_send_serial_master(0, comm_str, numb);
    }
    else
    {
        return PARSE_ID_NO_MATCH;
    }

    //Shouldn't get here...
    return PARSE_DEFAULT;
}

//Use this to test the Payload functions in a terminal
void payload_local_console_test(void)
{
    unsigned char kp = 1, ki = 2, kd = 3;
    unsigned char result = 0;

#ifdef USE_PRINTF
    printf("[[Test flexsea_payload]]\n\n");
    printf("PID gains: kp = %u, ki = %u, kd = %u.\n", test_kp, test_ki, test_kd);
#endif

    //"Send" command
    tx_cmd_ctrl_p_gains_write(board_id, kp, ki, kd);

    //"Receive" command
    result = payload_parse_str(payload_str);
#ifdef USE_PRINTF
    print_parse_result(result);
#endif

#ifdef USE_PRINTF
    printf("PID gains: kp = %u, ki = %u, kd = %u.\n", test_kp, test_ki, test_kd);
#endif
}

//Print payload_str - debugging
void payload_print_str(void)
{
#ifdef USE_PRINTF
    printf("\n-----------\n");
    printf("[CP_XID]: %u\n", payload_str[CP_XID]);
    printf("[CP_RID]: %u\n", payload_str[CP_RID]);
    printf("[CP_CMDS]: %u\n", payload_str[CP_CMDS]);
    printf("[CP_CMD1]: %u\n", payload_str[CP_CMD1]);
    printf("[CP_DATA1]: %u\n", payload_str[CP_DATA1]);
    printf("[CP_DATA1 + 1]: %u\n", payload_str[CP_DATA1 + 1]);
    printf("[CP_DATA1 + 2]: %u\n", payload_str[CP_DATA1 + 2]);
    printf("[CP_DATA1 + 3]: %u\n", payload_str[CP_DATA1 + 3]);
    printf("[CP_DATA1 + 4]: %u\n", payload_str[CP_DATA1 + 4]);
    printf("[CP_DATA1 + 5]: %u\n", payload_str[CP_DATA1 + 5]);
    printf("[CP_DATA1 + 6]: %u\n", payload_str[CP_DATA1 + 6]);
    printf("[CP_DATA1 + 7]: %u\n", payload_str[CP_DATA1 + 7]);
    printf("-----------\n\n");
#endif
}
