#include <project.h>
#include "../../common/inc/flexsea.h"
#include "comm.h"

//Variables:
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];

//for now: can receive motor position command only.
/*
uint8 decode_comm_str_payload(uint8 index, uint8 *cmd, uint16 *value)
{
	
}
*/

//Returns 0 is fail, pos otherwise
uint16 get_mot_pos_cmd(void)
{
	uint16 buffer = 0;
	
	if(comm_str_payload[0][0] == CMD_MOT_POS)
	{
		//Extract data
		buffer = ((uint16)comm_str_payload[0][1] << 8) + (comm_str_payload[0][2]);
		
		//Clear data
		comm_str_payload[0][0] = '0';
		comm_str_payload[0][1] = '0';
		comm_str_payload[0][2] = '0';
		
		//Return position command
		return buffer;
	}
	
	return 0;
}
