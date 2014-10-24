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
unsigned int payload_clear_str(void)
{
    int i = 0;

    for(i = 0; i < PAYLOAD_BUF_LEN; i++)
    {
        payload_str[i] = 0;
    }

    return 0;
}

//Start a new payload_str
unsigned int payload_build_basic_str(unsigned char to)
{
    //Start fresh:
    payload_clear_str();

    //Addresses:
    payload_str[CP_XID] = board_id;
    payload_str[CP_RID] = to;

    return 0;
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

//Decode/parse received string
//ToDo fix: for now, supports only one command per string
unsigned int payload_parse_str(unsigned char *cp_str)
{
    unsigned char cmd = 0, output = PARSE_SUCCESSFUL, numb = 0;
    unsigned int id = 0;
    unsigned int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;

    //Command
    cmd = cp_str[CP_CMD1];

    //First, check ID
    id = payload_check_slave_id(cp_str);
    if(id == ID_MATCH)
    {
        //It's addressed to me, what can I do with it?
        switch(cmd)
        {
            //ToDo: I should probably always pass the whole buffer, like for read_reply
        case CMD_SET_PID_GAINS:
            //Rebuild 16bit data:
            tmp1 = (cp_str[CP_DATA1] << 8) + cp_str[CP_DATA1 + 1];
            tmp2 = (cp_str[CP_DATA1 + 2] << 8) + cp_str[CP_DATA1 + 3];
            tmp3 = (cp_str[CP_DATA1 + 4] << 8) + cp_str[CP_DATA1 + 5];
            tmp4 = (cp_str[CP_DATA1 + 6] << 8) + cp_str[CP_DATA1 + 7];
            rx_set_pid_gains(tmp1, tmp2, tmp3, tmp4);
            break;
        case CMD_MOVE_TRAP_ABSOLUTE:
            rx_move_trap_absolute(cp_str);
            break;
        case CMD_SET_CLUTCH:
            rx_set_clutch(cp_str[CP_DATA1]);
            break;
        case CMD_SET_OPEN_SPEED:
            rx_set_open_speed(cp_str);
            break;
        case CMD_SET_LEDS:
            rx_set_led(cp_str[CP_DATA1], cp_str[CP_DATA1+1], cp_str[CP_DATA1+2], cp_str[CP_DATA1+3], cp_str[CP_DATA1+4]);
            break;
        case CMD_REPLY:
            rx_read_reply(cp_str, 0);
            break;
        case CMD_READ:
            rx_read(cp_str[CP_DATA1]);
            break;
        case CMD_SET_CURRENT:
            rx_set_current(cp_str);
            break;
        case CMD_SET_CONTROL:
            rx_set_control(cp_str);
            break;
        case CMD_SET_CURRENT_GAINS:
            rx_set_current_gains(cp_str);
            break;
        case CMD_SET_Z_GAINS:
            rx_set_z_gains(cp_str);
            break;
        default:
            output = PARSE_UNKNOWN_CMD;
            break;
        }

        return output;
    }
    else if((id == ID_SUB1_MATCH) || (id == ID_SUB2_MATCH))
    {
        //For one of my slaves. For now, they can only be on 1 RS-485 bus.

        //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
        numb = comm_gen_str(cp_str, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;    //Fixed length for now
        flexsea_send_serial(0, comm_str, numb + 1);

        if(cmd == CMD_READ)
        {
            //Place code here to deal with slave answering
            start_listening_flag = 1;

        }
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
        flexsea_send_serial_master(0,comm_str, numb + 1);
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
    tx_set_pid_gains(board_id, kp, ki, kd);

    //"Receive" command
    result = payload_parse_str(payload_str);
    print_parse_result(result);

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
