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

//****************************************************************************
// Function(s)
//****************************************************************************

//Send new PID gains to slave
unsigned int tx_set_pid_gains(unsigned char slave, unsigned int kp, unsigned int ki, unsigned int kd)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_PID_GAINS;

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
unsigned int tx_set_clutch(unsigned char slave, unsigned char clutch_state)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_CLUTCH;

    //Parameters:
    payload_str[CP_CMD1 + 1] = clutch_state;

    //At this point the string is ready to be packaged in comm_str
    return 5;
}

//Send open speed command
unsigned int tx_set_open_spd(unsigned char slave, int open_spd)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_OPEN_SPEED;

    //Parameters:
    payload_str[CP_DATA1] = (unsigned char)((open_spd >> 8) & 0xFF);
    payload_str[CP_DATA1 + 1] = (unsigned char)(open_spd & 0xFF);

    //At this point the string is ready to be packaged in comm_str
#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
#endif // ENABLE_TERMINAL_DEBUG
    return 6;
}

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

//Set LED state
unsigned int tx_set_leds(unsigned char slave, unsigned char bank, unsigned char rgb, unsigned char r, unsigned char g, unsigned char b)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_LEDS;

    //Parameters:
    payload_str[CP_DATA1] = bank;
    payload_str[CP_DATA1 + 1] = rgb;
    payload_str[CP_DATA1 + 2] = r;
    payload_str[CP_DATA1 + 3] = g;
    payload_str[CP_DATA1 + 4] = b;

    //At this point the string is ready to be packaged in comm_str
    return 9;
}

//Read from slave, starting at offset
unsigned int tx_read(unsigned char slave, unsigned char offset)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_READ;

    //Parameters:
    payload_str[CP_DATA1] = offset;

    //At this point the string is ready to be packaged in comm_str
    return 5;
}

//Send current command
unsigned int tx_set_current(unsigned char slave, int curr)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_CURRENT;

    //Parameters:
    payload_str[CP_DATA1] = (unsigned char)((curr >> 8) & 0xFF);
    payload_str[CP_DATA1 + 1] = (unsigned char)(curr & 0xFF);

    //At this point the string is ready to be packaged in comm_str
#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
#endif // ENABLE_TERMINAL_DEBUG
    return 6;
}

//Send current command
unsigned int tx_set_control(unsigned char slave, unsigned char ctrl)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_CONTROL;

    //Parameters:
    payload_str[CP_DATA1] = ctrl;

    //At this point the string is ready to be packaged in comm_str
#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
#endif // ENABLE_TERMINAL_DEBUG
    return 5;
}

//Send Current gain command
unsigned int tx_set_current_gains(unsigned char slave, int c_p, int c_i, int c_d)
{
    //Fresh string:
    payload_build_basic_str(slave);

    //Command:
    payload_str[CP_CMDS] = 1;                     //1 command in string
    payload_str[CP_CMD1] = CMD_SET_CURRENT_GAINS;

    //Parameters:
    payload_str[CP_DATA1] = (unsigned char)((c_p >> 8) & 0xFF);
    payload_str[CP_DATA1 + 1] = (unsigned char)(c_p & 0xFF);
    payload_str[CP_DATA1 + 2] = (unsigned char)((c_i >> 8) & 0xFF);
    payload_str[CP_DATA1 + 3] = (unsigned char)(c_i & 0xFF);
    payload_str[CP_DATA1 + 4] = (unsigned char)((c_d >> 8) & 0xFF);
    payload_str[CP_DATA1 + 5] = (unsigned char)(c_d & 0xFF);

    //At this point the string is ready to be packaged in comm_str
#ifdef ENABLE_TERMINAL_DEBUG
    payload_print_str();
#endif // ENABLE_TERMINAL_DEBUG
    return 10;
}

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
