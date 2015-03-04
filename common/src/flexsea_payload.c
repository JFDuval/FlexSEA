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
// Variable(s)
//****************************************************************************

uint8_t payload_str[PAYLOAD_BUF_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Start a new payload string
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
uint8_t get_rid(uint8_t *pldata)
{
	uint8_t cp_rid = pldata[CP_RID];
	uint8_t i = 0;

	if(cp_rid == board_id)				//This board?
	{
		return ID_MATCH;
	}
	else if(cp_rid == board_up_id)		//Master?
	{
		return ID_UP_MATCH;
	}
	else
	{
		//Can be on a slave bus, or can be invalid.

		//Search on slave bus #1:
		for(i = 0; i < SLAVE_BUS_1_CNT; i++)
		{
			if(cp_rid == board_sub1_id[i])
			{
				return ID_SUB1_MATCH;
			}
		}

		//Then on bus #2:
		for(i = 0; i < SLAVE_BUS_1_CNT; i++)
		{
			if(cp_rid == board_sub2_id[i])
			{
				return ID_SUB2_MATCH;
			}
		}
	}

	//If we end up here it's because we didn't get a match:
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

    //Command
    cmd = cp_str[CP_CMD1];

    //First, get RID code
    id = get_rid(cp_str);
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
    else if(id == ID_SUB1_MATCH)
    {
        //For a slave on bus #1:

    	route_to_slave(PORT_RS485_1, cp_str, PAYLOAD_BUF_LEN);
    	//ToDo compute length rather then sending the max
    }
    else if(id == ID_SUB2_MATCH)
    {
    	//For a slave on bus #2:

    	route_to_slave(PORT_RS485_2, cp_str, PAYLOAD_BUF_LEN);
    	//ToDo compute length rather then sending the max
    }
    else if(id == ID_UP_MATCH)
    {
        //For my master:

		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

    	//Manage is the only board that can receive a package destined to his master
			
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

//ToDo not the greatest function...
void route_to_slave(uint8_t port, uint8_t *buf, uint32_t len)
{
	uint32_t numb = 0, i = 0;
	uint8_t *comm_str_ptr = slaves_485_1.xmit.str;

    //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
    numb = comm_gen_str(buf, len);
    //numb = COMM_STR_BUF_LEN;    //Fixed length for now

    //Port specific flags and buffer:
    if(port == PORT_RS485_1)
    {
    	comm_str_ptr = slaves_485_1.xmit.str;
    	slaves_485_1.xmit.cmd = buf[CP_CMD1];
    	slaves_485_1.xmit.flag = 1;
    }
    else if(port == PORT_RS485_2)
    {
    	comm_str_ptr = slaves_485_2.xmit.str;
    	slaves_485_2.xmit.cmd = buf[CP_CMD1];
    	slaves_485_2.xmit.flag = 1;
    }

    //Copy string:
    for(i = 0; i < numb+1; i++)
    {
    	comm_str_ptr[i] = comm_str[i];
    }
}
