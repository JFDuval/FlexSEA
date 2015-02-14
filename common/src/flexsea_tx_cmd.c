//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_tx_cmd: prepare commands before we send them out
//****************************************************************************

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
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned int pid_kp = 0, pid_ki = 0, pid_kd = 0;
int open_speed = 0, current = 0;
int trapeze_pos_i = 0, trapeze_pos_f = 0, trapeze_max_spd = 0, trapeze_acc = 0;
unsigned char mm_leds = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

extern unsigned char payload_str[PAYLOAD_BUF_LEN];

#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
	
extern struct ctrl_s ctrl;
extern struct enc_s encoder;	
extern struct imu_s imu;
	
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Function(s)
//****************************************************************************

//Send new position PID gains to slave
uint32_t tx_cmd_ctrl_p_gains_write(uint8_t slave, int16_t kp, int16_t ki, int16_t kd)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_P_GAINS_WRITE;

    //Parameters:
    payload_str[CP_DATA1] = (unsigned char)((kp >> 8) & 0xFF);
    payload_str[CP_DATA1 + 1] = (unsigned char)(kp & 0xFF);
    payload_str[CP_DATA1 + 2] = (unsigned char)((ki >> 8) & 0xFF);
    payload_str[CP_DATA1 + 3] = (unsigned char)(ki & 0xFF);
    payload_str[CP_DATA1 + 4] = (unsigned char)((kd >> 8) & 0xFF);
    payload_str[CP_DATA1 + 5] = (unsigned char)(kd & 0xFF);

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 10;
}

//Set clutch state
uint32_t tx_cmd_clutch_write(uint8_t slave, uint8_t clutch_pwm)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CLUTCH_WRITE;

    //Parameters:
    payload_str[CP_DATA1 + 1] = clutch_pwm;

    //At this point the string is ready to be packaged in comm_str
    return 6;
}

//Send open loop speed command (PWM DC)
uint32_t tx_cmd_ctrl_o_write(uint8_t slave, int32_t pwmdc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
	
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_O_WRITE;

    //Arguments:
	uint32_to_bytes(pwmdc, &tmp0, &tmp1, &tmp2, &tmp3);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;
    payload_str[CP_DATA1 + 2] = tmp2;
    payload_str[CP_DATA1 + 3] = tmp3;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 8;
}

//ToDo *** Fix or Remove ***
//Send trapeze command
unsigned int tx_set_trapeze(unsigned char slave, int posi, int posf, int spdm, int acc)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_MOVE_TRAP_ABSOLUTE;

    //Parameters:
    payload_str[CP_DATA1] = (unsigned char)((posi >> 8) & 0xFF);
    payload_str[CP_DATA1 + 1] = (unsigned char)(posi & 0xFF);
    payload_str[CP_DATA1 + 2] = (unsigned char)((posf >> 8) & 0xFF);
    payload_str[CP_DATA1 + 3] = (unsigned char)(posf & 0xFF);
    payload_str[CP_DATA1 + 4] = (unsigned char)((spdm >> 8) & 0xFF);
    payload_str[CP_DATA1 + 5] = (unsigned char)(spdm & 0xFF);
    payload_str[CP_DATA1 + 6] = (unsigned char)((acc >> 8) & 0xFF);
    payload_str[CP_DATA1 + 7] = (unsigned char)(acc & 0xFF);

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 12;
}

//ToDo *** Fix or Remove ***
//Read from slave, starting at offset
uint32_t tx_cmd_mem_read(uint8_t slave, uint8_t mem, uint8_t base_addr, uint8_t bytes)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_MEM_READ;

    //Parameters:
    payload_str[CP_DATA1] = base_addr;

    //At this point the string is ready to be packaged in comm_str
    return 5;
}

//Send current command
uint32_t tx_cmd_ctrl_i_write(uint8_t slave, int16_t curr)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_I_WRITE;

    //Arguments:
	uint16_to_bytes(curr, &tmp0, &tmp1);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 6;
}

//Configure the control strategy
uint32_t tx_cmd_ctrl_mode_write(uint8_t slave, uint8_t ctrl)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_MODE_WRITE;

    //Parameters:
    payload_str[CP_DATA1] = ctrl;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 5;
}

//Send Current gain command
uint32_t tx_cmd_ctrl_i_gains_write(uint8_t slave, int16_t kp, int16_t ki, int16_t kd)
{
	uint8_t tmp0 = 0, tmp1 = 0;
	
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_I_GAINS_WRITE;

    //Arguments:
	uint16_to_bytes((uint16_t)kp, &tmp0, &tmp1);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;
	uint16_to_bytes((uint16_t)ki, &tmp0, &tmp1);
    payload_str[CP_DATA1 + 2] = tmp0;
    payload_str[CP_DATA1 + 3] = tmp1;
	uint16_to_bytes((uint16_t)kd, &tmp0, &tmp1);
    payload_str[CP_DATA1 + 4] = tmp0;
    payload_str[CP_DATA1 + 5] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 10;
}

//ToDo *** Fix or Remove ***
//Send impedance (Z) gain command
unsigned int tx_set_z_gains(unsigned char slave, int z_k, int z_b, int z_i)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_Z_GAINS;

    //Parameters:
    payload_str[CP_DATA1] = (unsigned char)((z_k >> 8) & 0xFF);
    payload_str[CP_DATA1 + 1] = (unsigned char)(z_k & 0xFF);
    payload_str[CP_DATA1 + 2] = (unsigned char)((z_b >> 8) & 0xFF);
    payload_str[CP_DATA1 + 3] = (unsigned char)(z_b & 0xFF);
    payload_str[CP_DATA1 + 4] = (unsigned char)((z_i >> 8) & 0xFF);
    payload_str[CP_DATA1 + 5] = (unsigned char)(z_i & 0xFF);

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 10;
}

//Send strain gauge amplifier configuration
uint32_t tx_cmd_strain_config(uint8_t slave, uint8_t offs, uint8_t gain, uint8_t oref)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_STRAIN_CONFIG;

    //Parameters:
    payload_str[CP_DATA1] = offs;
    payload_str[CP_DATA1 + 1] = gain;
    payload_str[CP_DATA1 + 2] = oref;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 7;
}

//Send value to encoder
uint32_t tx_cmd_encoder_write(uint8_t slave, int32_t enc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_ENCODER_WRITE;
 
    //Arguments:
	uint32_to_bytes(enc, &tmp0, &tmp1, &tmp2, &tmp3);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;
    payload_str[CP_DATA1 + 2] = tmp2;
    payload_str[CP_DATA1 + 3] = tmp3;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 8;
}

//Request an IMU Read
uint32_t tx_cmd_imu_read(uint8_t slave, uint8_t base_addr, uint8_t bytes)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_IMU_READ;

    //Arguments:
    payload_str[CP_DATA1] = base_addr;
    payload_str[CP_DATA1 + 1] = bytes;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 6;
}

//Request an Encoder Read
uint32_t tx_cmd_encoder_read(uint8_t slave)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_ENCODER_READ;

    //Arguments:
	//(No parameters for this one)

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 4;
}

//Request a Strain Read
uint32_t tx_cmd_strain_read(uint8_t slave)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_STRAIN_READ;

    //Arguments:
	//(No parameters for this one)

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 4;
}

//Request an Analog Read
uint32_t tx_cmd_analog_read(uint8_t slave, uint8_t base_addr, uint8_t bytes)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_ANALOG_READ;

    //Arguments:
    payload_str[CP_DATA1] = base_addr;
    payload_str[CP_DATA1 + 1] = bytes;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 6;
}

//Request a Ctrl Current Read
uint32_t tx_cmd_ctrl_i_read(uint8_t slave)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_I_READ;

    //Arguments:
	//(No parameters for this one)

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 4;
}

//Reply to an Encoder Read request
uint32_t tx_cmd_encoder_read_reply(uint8_t master, int32_t enc)
{
	uint8_t tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

    //Fresh string:
    payload_build_basic_str(master);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_ENCODER_READ_REPLY;
 
    //Arguments:
	uint32_to_bytes((uint32_t)enc, &tmp0, &tmp1, &tmp2, &tmp3);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;
    payload_str[CP_DATA1 + 2] = tmp2;
    payload_str[CP_DATA1 + 3] = tmp3;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 8;
}

//Reply to a Strain Read request
uint32_t tx_cmd_strain_read_reply(uint8_t master, uint16_t strain)
{
	uint8_t tmp0 = 0, tmp1 = 0;

    //Fresh string:
    payload_build_basic_str(master);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_STRAIN_READ_REPLY;
 
    //Arguments:
	uint16_to_bytes(strain, &tmp0, &tmp1);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 6;
}

//Reply to an IMU Read request //ToDo Incomplete
uint32_t tx_cmd_imu_read_reply(uint8_t master, uint8_t base_addr, uint8_t bytes)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	uint8_t tmp0 = 0, tmp1 = 0;

    //Fresh string:
    payload_build_basic_str(master);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_IMU_READ_REPLY;
 
    //Arguments:
	//ToDo ***for now we ignore the base addr and we always send the gyro values ***
	payload_str[CP_DATA1] = base_addr;
	uint16_to_bytes(imu.gyro.x, &tmp0, &tmp1);
    payload_str[CP_DATA1 + 1] = tmp0;
    payload_str[CP_DATA1 + 2] = tmp1;
	uint16_to_bytes(imu.gyro.y, &tmp0, &tmp1);
    payload_str[CP_DATA1 + 3] = tmp0;
    payload_str[CP_DATA1 + 4] = tmp1;
	uint16_to_bytes(imu.gyro.z, &tmp0, &tmp1);
    payload_str[CP_DATA1 + 5] = tmp0;
    payload_str[CP_DATA1 + 6] = tmp1;

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
    payload_build_basic_str(master);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_ANALOG_READ_REPLY;
 
    //Arguments:
	//ToDo ***for now we ignore the 'bytes' and we send 1 value ***
	payload_str[CP_DATA1] = base_addr;
	uint16_to_bytes(read_analog(base_addr), &tmp0, &tmp1);
    payload_str[CP_DATA1 + 1] = tmp0;
    payload_str[CP_DATA1 + 2] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

	#endif 	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	uint8_t tmp0 = 0, tmp1 = 0;

	//Fresh string:
	payload_build_basic_str(master);

	//Command:
	payload_str[CP_CMDS] = 1;                     //1 command in string
	payload_str[CP_CMD1] = CMD_ANALOG_READ_REPLY;

	//Arguments:
	//ToDo ***for now we ignore the 'bytes' and we send 1 value ***
	payload_str[CP_DATA1] = 0xAB;
	payload_str[CP_DATA1 + 1] = 0xCD;
	payload_str[CP_DATA1 + 2] = 0xEF;

	//At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
	payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

	#endif 	//BOARD_TYPE_FLEXSEA_MANAGE

    return 7;
}

//Reply to a Ctrl Current Read request
uint32_t tx_cmd_ctrl_i_read_reply(uint8_t master, int16_t measured, int16_t wanted)
{
	uint8_t tmp0 = 0, tmp1 = 0;

    //Fresh string:
    payload_build_basic_str(master);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CTRL_I_READ_REPLY;
 
    //Arguments:
	uint16_to_bytes(measured, &tmp0, &tmp1);
    payload_str[CP_DATA1] = tmp0;
    payload_str[CP_DATA1 + 1] = tmp1;
	uint16_to_bytes(wanted, &tmp0, &tmp1);
    payload_str[CP_DATA1 + 2] = tmp0;
    payload_str[CP_DATA1 + 3] = tmp1;

    //At this point the string is ready to be packaged in comm_str
	#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
	#endif // ENABLE_TERMINAL_DEBUG

    return 8;
}

//Set acquisition mode
uint32_t tx_cmd_acq_mode_write(uint8_t slave, uint8_t mode)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_CLUTCH_WRITE;

    //Parameters:
    payload_str[CP_DATA1 + 1] = mode;

    //At this point the string is ready to be packaged in comm_str
    return 6;
}

