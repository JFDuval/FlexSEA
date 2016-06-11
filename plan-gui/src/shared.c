//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// shared: Code shared by Test, Demo, User functions, etc.
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "shared.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

void braking_sequence(int cycles, int delay)
{
	int i = 0, numb = 0;

	for(i = 0; i < cycles; i++)
	{
		numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, -400);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
		usleep(delay);
		numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);
        numb = comm_gen_str(tmp_payload_xmit, comm_str_usb, numb);
        flexsea_send_serial_slave(PORT_SPI, comm_str_usb, numb);
		usleep(delay);
	}
}

#ifdef __cplusplus
}
#endif
