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
uint8_t receive_485_1 = 0, receive_485_2 = 0;
unsigned char xmit_flag = 0;
uint8_t comm_str_xmit_1[COMM_STR_BUF_LEN], comm_str_xmit_2[COMM_STR_BUF_LEN];
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

//Start a new payload string
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
//Payload is the partially filled buffer, idx is the next position to use, new_data is.. well, the new bytes
//and len is the number of bytes you want to add
uint32_t append_to_payload(uint8_t *payload, uint32_t idx, uint8_t *new_data, uint32_t len)
{
	uint32_t i = 0, cnt = 0;

	//Append the new data:
	for(i = idx; i < (idx+len); i++)
	{
		payload[i] = new_data[cnt++];
	}

	//Index for the next call:
	return i;
}

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
			
			//ToDo: temporary integration of the new commands:	
			case CMD_SPECIAL_1_W:     
			case CMD_SPECIAL_1_R:    	
                rx_cmd_special_1(cp_str);
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

    	route_to_slave(cp_str, PAYLOAD_BUF_LEN);
    	//ToDo compute length rather then sending the max
    }
    /*
    else if(id == ID_SUB2_MATCH)
    {
    	//For one of my slaves:
		//...
    }
    */
    else if(id == ID_UP_MATCH)
    {
        //For my master:

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE
			
        //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
        numb = comm_gen_str(cp_str, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;    //Fixed length for now
        flexsea_send_serial_master(0, comm_str, numb);	//Was +1
		
		#endif	//BOARD_TYPE_FLEXSEA_MANAGE
    }
    else
    {
        return PARSE_ID_NO_MATCH;
    }

    //Shouldn't get here...
    return PARSE_DEFAULT;
}


void route_to_slave(uint8_t *buf, uint32_t len)
{
	uint32_t numb = 0, i = 0;

    //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
    numb = comm_gen_str(buf, len);
    //numb = COMM_STR_BUF_LEN;    //Fixed length for now

    //Copy string:
    for(i = 0; i < numb+1; i++)
    {
    	comm_str_xmit_1[i] = comm_str[i];
    }

    cmd_xmit = buf[CP_CMD1];
    xmit_flag = 1;
}
