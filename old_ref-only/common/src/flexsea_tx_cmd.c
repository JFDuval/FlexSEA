//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_tx_cmd: prepare commands before we send them out
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea.h"
#include "flexsea_local.h"

//Execute boards only:
#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
#include "main.h"
#include "imu.h"
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Variable(s)
//****************************************************************************

unsigned int pid_kp = 0, pid_ki = 0, pid_kd = 0;
int open_speed = 0, current = 0;
int trapeze_pos_i = 0, trapeze_pos_f = 0, trapeze_max_spd = 0, trapeze_acc = 0;
unsigned char mm_leds = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

//ToDo *** Fix or Remove ***
//Read from slave, starting at offset
uint32_t tx_cmd_mem_read(uint8_t slave, uint8_t mem, uint8_t base_addr, uint8_t bytes)
{
    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = CMD_MEM;

    //Parameters:
    payload_str[P_DATA1] = base_addr;

    //At this point the string is ready to be packaged in comm_str
    return 5;
}

//Send strain gauge amplifier configuration
uint32_t tx_cmd_strain_config(uint8_t slave, uint8_t offs, uint8_t gain, uint8_t oref)
{
    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = CMD_STRAIN_CONFIG;

    //Parameters:
    payload_str[P_DATA1] = offs;
    payload_str[P_DATA1 + 1] = gain;
    payload_str[P_DATA1 + 2] = oref;

    return 7;
}

//Send value to encoder
uint32_t tx_cmd_encoder_write(uint8_t slave, int32_t enc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_ENCODER_WRITE;
 
    //Arguments:
	uint32_to_bytes(enc, &tmp0, &tmp1, &tmp2, &tmp3);
    payload_str[P_DATA1] = tmp0;
    payload_str[P_DATA1 + 1] = tmp1;
    payload_str[P_DATA1 + 2] = tmp2;
    payload_str[P_DATA1 + 3] = tmp3;

    return 8;
}

//Request an IMU Read
uint32_t tx_cmd_imu_read(uint8_t slave, uint8_t base_addr, uint8_t bytes)
{
    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_IMU_READ;

    //Arguments:
    payload_str[P_DATA1] = base_addr;
    payload_str[P_DATA1 + 1] = bytes;

    return 6;
}

//Request an Encoder Read
uint32_t tx_cmd_encoder_read(uint8_t slave)
{
    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_ENCODER_READ;

    //Arguments:
	//(No parameters for this one)

    return 4;
}

//Request a Strain Read
uint32_t tx_cmd_strain_read(uint8_t slave)
{
    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_STRAIN_READ;

    //Arguments:
	//(No parameters for this one)

    return 4;
}

//Request an Analog Read
uint32_t tx_cmd_analog_read(uint8_t slave, uint8_t base_addr, uint8_t bytes)
{
    //Fresh string:
	prepare_empty_payload(board_id, slave, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_ANALOG_READ;

    //Arguments:
    payload_str[P_DATA1] = base_addr;
    payload_str[P_DATA1 + 1] = bytes;

    return 6;
}

//Reply to an Encoder Read request
uint32_t tx_cmd_encoder_read_reply(uint8_t master, int32_t enc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

    //Fresh string:
	prepare_empty_payload(board_id, master, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_ENCODER_READ_REPLY;
 
    //Arguments:
	uint32_to_bytes((uint32_t)enc, &tmp0, &tmp1, &tmp2, &tmp3);
    payload_str[P_DATA1] = tmp0;
    payload_str[P_DATA1 + 1] = tmp1;
    payload_str[P_DATA1 + 2] = tmp2;
    payload_str[P_DATA1 + 3] = tmp3;

    return 8;
}

//Reply to a Strain Read request
uint32_t tx_cmd_strain_read_reply(uint8_t master, uint16_t strain)
{
	uint8_t tmp0 = 0, tmp1 = 0;

    //Fresh string:
	prepare_empty_payload(board_id, master, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0; //CMD_STRAIN_READ_REPLY;
 
    //Arguments:
	uint16_to_bytes(strain, &tmp0, &tmp1);
    payload_str[P_DATA1] = tmp0;
    payload_str[P_DATA1 + 1] = tmp1;

    return 6;
}

//Reply to an IMU Read request //ToDo Incomplete
uint32_t tx_cmd_imu_read_reply(uint8_t master, uint8_t base_addr, uint8_t bytes)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	uint8_t tmp0 = 0, tmp1 = 0;

    //Fresh string:
    prepare_empty_payload(board_id, master, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0;//CMD_IMU_READ_REPLY;
 
    //Arguments:
	//ToDo ***for now we ignore the base addr and we always send the gyro values ***
	payload_str[P_DATA1] = base_addr;
	uint16_to_bytes(imu.gyro.x, &tmp0, &tmp1);
    payload_str[P_DATA1 + 1] = tmp0;
    payload_str[P_DATA1 + 2] = tmp1;
	uint16_to_bytes(imu.gyro.y, &tmp0, &tmp1);
    payload_str[P_DATA1 + 3] = tmp0;
    payload_str[P_DATA1 + 4] = tmp1;
	uint16_to_bytes(imu.gyro.z, &tmp0, &tmp1);
    payload_str[P_DATA1 + 5] = tmp0;
    payload_str[P_DATA1 + 6] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG
	
	#endif 	//BOARD_TYPE_FLEXSEA_EXECUTE
	
    return 11;
}

//Reply to an Analog Read request //ToDo Incomplete
uint32_t tx_cmd_analog_read_reply(uint8_t master, uint8_t base_addr, uint8_t bytes)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint8_t tmp0 = 0, tmp1 = 0;

    //Fresh string:
    prepare_empty_payload(board_id, master, payload_str, PAYLOAD_BUF_LEN);

    //Command:
    payload_str[P_CMDS] = 1;                     //1 command in string
    payload_str[P_CMD1] = 0;//CMD_ANALOG_READ_REPLY;
 
    //Arguments:
	//ToDo ***for now we ignore the 'bytes' and we send 1 value ***
	payload_str[P_DATA1] = base_addr;
	uint16_to_bytes(read_analog(base_addr), &tmp0, &tmp1);
    payload_str[P_DATA1 + 1] = tmp0;
    payload_str[P_DATA1 + 2] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

	#endif 	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	uint8_t tmp0 = 0, tmp1 = 0;

	//Fresh string:
	prepare_empty_payload(board_id, master, payload_str, PAYLOAD_BUF_LEN);

	//Command:
	payload_str[P_CMDS] = 1;                     //1 command in string
	payload_str[P_CMD1] = 0; //CMD_ANALOG_READ_REPLY;

	//Arguments:
	//ToDo ***for now we ignore the 'bytes' and we send 1 value ***
	payload_str[P_DATA1] = 0xAB;
	payload_str[P_DATA1 + 1] = 0xCD;
	payload_str[P_DATA1 + 2] = 0xEF;

	//At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
	payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

	#endif 	//BOARD_TYPE_FLEXSEA_MANAGE

    return 7;
}

#ifdef __cplusplus
}
#endif
