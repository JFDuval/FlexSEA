//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea: Master file for the FlexSEA stack.
//****************************************************************************

// FlexSEA: Flexible & Scalable Electronics Architecture

// Naming convention:
// ================================
// - Plan: Embedded Computer
//      - Complex algorithms, data-logging, user interfaces, ...
//      - Hard/soft: BeagleBone Black running Linux. C, Python, Matlab.
// - Manage: Data acquisition and mid-level computing
//      - Connected to Plan. Gathers sensor data, connect to slaves
//      - Hard/soft: STM32F4 Cortex-M4. C.
// - Execute: smart motor driver
//      - Motion controller
//      - Hard/soft: Programmable System on Chip (PSoC). C, HDL, graphical.

// v0.0 Limitations and known bugs: ToDo Update
// ================================
// - The board config is pretty muched fixed: 1 Plan, 1 Manage, up to 2 Execute
//   (on the same RS-485 bus)
// - Only 1 command per transmission
// - STM32F4 interrupt based SPI driver isn't happy with unknown transmission
//   length so for now I'm fixing the packet length.
// - Fixed payload length: 12 bytes (allows you to send 1 command with up to
//   8 arguments (uint8) (or 4x uint16))
// - Fixed comm_str length: 24 bytes (min. to accomodate a payload where all the
//   data bytes need escaping)
// - In comm_str #OfBytes isn't escaped. Ok as long as the count is less than
//   the decimal value of the flags ('a', 'z', 'e') so max 97 bytes.
// - Data transfer could be faster with shorter ACK sequence, more than 1 command
//   per packet and no repackaging on the Manage board (straight pass-through)
//   To be optimized later.

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/flexsea.h"
#include "flexsea_local.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************

//From flexsea_local
extern unsigned char board_id;
extern unsigned char board_sub1_id;
extern unsigned char board_sub2_id;

//From flexsea_commands:
extern unsigned int pid_kp, pid_ki, pid_kd; //Test only

//From flexsea_local:
extern char name[];
extern char version[];
extern char date[];
//extern char spi_xmit[];

//From payload and comm:
extern unsigned char comm_str[];
extern unsigned char input_buffer[];    //Test only
extern unsigned char rx_buf[];
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];
extern unsigned char payload_str[];

//****************************************************************************
// Function(s)
//****************************************************************************

//Full local (console) test of Flexsea-Payload & Flexsea-Comm
void test_flexsea_network(void)
{
    unsigned char kp = 1, ki = 2, kd = 3;
    unsigned char result = 0;
    unsigned char num_strings = 0, i = 0;

#ifdef USE_PRINTF
    printf("[[Test flexsea_network]]\n\n");
#endif

#ifdef USE_PRINTF
    printf("Initial PID gains: kp = %u, ki = %u, kd = %u.\n", pid_kp, pid_ki, pid_kd);
#endif

    //Create payload string
    kp = 70;
    ki = 71;
    kd = 72;
    tx_set_pid_gains(board_id, kp, ki, kd);

    //Package it in comm_str:
    comm_gen_str(payload_str, PAYLOAD_BUF_LEN);

    //Build input buffer:
    comm_build_input_buffer();

    //Fill rx_buf:
    comm_clear_rx_buffer();
    for(i = 0; i < RX_BUF_LEN; i++)
    {
        rx_buf[i] = input_buffer[i];
    }

    //Decode
    num_strings = comm_decode_str();

#ifdef USE_PRINTF
    printf("Decoded %i strings\n", num_strings);
#endif

    for(i = 0; i < num_strings; i++)
    {
#ifdef USE_PRINTF
        printf("comm_str_payload[%i] = %s\n", i, comm_str_payload[i]);
#endif
    }

    //Now, can we parse the first one?
    result = payload_parse_str((unsigned char *)comm_str_payload);
    //print_parse_result(result);
#ifdef USE_PRINTF
    printf("Final PID gains: kp = %u, ki = %u, kd = %u (should be %i, %i & %i)\n", pid_kp, pid_ki, pid_kd, kp, ki, kd);
#endif

    if((kp = pid_kp) && (ki = pid_ki) && (kd = pid_kd))
    {
#ifdef USE_PRINTF
        printf(">>> Gains are ok, success! <<<\n");
#endif
    }
    else
    {
#ifdef USE_PRINTF
        printf(">>> Wrong gains, something is wrong! <<<\n");
#endif
    }
}

//When something goes wrong in the code it will land here:
unsigned int flexsea_error(unsigned int err_code)
{
	//ToDo something useful
	return err_code;
}
