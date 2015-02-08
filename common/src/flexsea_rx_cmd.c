//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_rx_cmd: how do we deal with the commands we received?
//****************************************************************************

// All the commands that are decoded in flexsea_payload will call functions
// hosted in that file. These function will redirect to board specific functions.

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea.h"
#include "flexsea_local.h"

//Manage boards only:
#ifdef BOARD_TYPE_FLEXSEA_MANAGE
#include "fm_ui.h"
#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//Execute boards only:
#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
#include <project.h>
#include "main.h"
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned char read_offset = 0;

//Slave data:
unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];
unsigned char manage_1_data[SLAVE_READ_BUFFER_LEN];

//****************************************************************************
// External variable(s)
//****************************************************************************

unsigned char comm_str[COMM_STR_BUF_LEN];

#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

extern int gain_p, gain_i;
extern int steps;
extern int current_pid_setpoint;
extern unsigned char controller;
extern int z_gain_k, z_gain_b, z_gain_i;

//Impedance controller:
extern int z_gain_k, z_gain_b, z_gain_i;

//Current controller:
extern int current_gain_p, current_gain_i, current_gain_d;

#endif	//BOARD_TYPE_FLEXSEA_EXECUTE


//****************************************************************************
// Function(s)
//****************************************************************************

void rx_set_pid_gains(unsigned int tmp1, unsigned int tmp2, unsigned int tmp3, unsigned int tmp4)
{
    #ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	//ToDo Add more safety checks!
	if(tmp1 > 0)
		gain_p = tmp1;
	else
		gain_p = 0;

	if(tmp2 > 0)
		gain_i = tmp2;
	else
		gain_i = 0;

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_move_trap_absolute(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int tmp_posi = 0, tmp_posf = 0, tmp_spdm = 0, tmp_acc = 0;
	int tmp_z_k = 0, tmp_z_b = 0, tmp_z_i = 0;

	//Rebuild 16bit data:
	//We can only send 16 bits but the posi & posf variables are 32 bits so we << 2
    tmp_posi = ((buf[CP_DATA1] << 8) + buf[CP_DATA1 + 1]) << 2;
    tmp_posf = ((buf[CP_DATA1 + 2] << 8) + buf[CP_DATA1 + 3]) << 2;
    tmp_spdm = (buf[CP_DATA1 + 4] << 8) + buf[CP_DATA1 + 5];
    tmp_acc = (buf[CP_DATA1 + 6] << 8) + buf[CP_DATA1 + 7];

	if(controller == CTRL_POSITION)
	{
		steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);
	}
	else if(controller == CTRL_IMPEDANCE)
	{
		//Backup gains
		tmp_z_k = z_gain_k; tmp_z_b = z_gain_b;	tmp_z_i = z_gain_i;
		//Zero them
		z_gain_k = 0; z_gain_b = 0; z_gain_i = 0; 
		//New trajectory
		steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);
		//Restore gains
		z_gain_k = tmp_z_k; z_gain_b = tmp_z_b; z_gain_i = tmp_z_i; 
	}

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_set_clutch(unsigned char cstate)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	clutch_output(cstate);

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_set_open_speed(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int16 tmp_mot_spd = 0;

	//Rebuild 16bit data:
    tmp_mot_spd = (buf[CP_DATA1] << 8) + buf[CP_DATA1 + 1];

	if(controller == CTRL_OPEN)
	{
		motor_open_speed_1(tmp_mot_spd);
	}

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_set_led(unsigned char ledbank, unsigned char rgb, unsigned char r, unsigned char g, unsigned char b)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	LED_R_Write(r);
	LED_G_Write(g);
	LED_B_Write(b);
	#ifdef USE_I2C_EXT
	i2c_write_minm_rgb(SET_RGB, r, g, b);
	#endif 	//USE_I2C_EXT

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	set_led_rgb(r, g, b);

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//Display the data received from a slave after a read request
void rx_read_reply(unsigned char *buf, unsigned int verbal)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN

	unsigned char execute_num = 99;
	unsigned int tmp0 = 0, tmp1 = 0, tmp2 = 0;

    //ToDo: quick test. Should be a full structure.
    //ToDo: my way of dealing with the offsets is terrible!
    if(buf[CP_XID] == FLEXSEA_MANAGE_1)
    {
        if(buf[CP_DATA1] == 0)
        {
            //Store into array:
            manage_1_data[SRB_MANAGE_OFFSET] = buf[CP_DATA1];
            manage_1_data[SRB_MANAGE_STATUS] = buf[CP_DATA1 + 1];
            manage_1_data[SRB_MANAGE_DIGITAL_IO_B1] = buf[CP_DATA1 + 2];
            manage_1_data[SRB_MANAGE_DIGITAL_IO_B2] = buf[CP_DATA1 + 3];
            manage_1_data[SRB_MANAGE_AN0_MSB] = buf[CP_DATA1 + 4];
            manage_1_data[SRB_MANAGE_AN0_LSB] = buf[CP_DATA1 + 5];
            manage_1_data[SRB_MANAGE_AN1_MSB] = buf[CP_DATA1 + 6];
            manage_1_data[SRB_MANAGE_AN1_LSB] = buf[CP_DATA1 + 7];

            if(verbal)
            {
                #ifdef USE_PRINTF
                 printf("\nReading from FLEXSEA_MANAGE_1:\n");
                 printf("SW1: %i, SW2: %i\n", (manage_1_data[SRB_MANAGE_STATUS]&0x01), ((manage_1_data[SRB_MANAGE_STATUS]&0x02)>>1));
                 printf("Digital IO (B1): 0x%02X\n", manage_1_data[SRB_MANAGE_DIGITAL_IO_B1]);
                 printf("Digital IO (B2): 0x%02X\n", manage_1_data[SRB_MANAGE_DIGITAL_IO_B2]);
                 printf("Analog 0: %i\n", ((manage_1_data[SRB_MANAGE_AN0_MSB] << 8) + manage_1_data[SRB_MANAGE_AN0_LSB]));
                 printf("Analog 1: %i\n", ((manage_1_data[SRB_MANAGE_AN1_MSB] << 8) + manage_1_data[SRB_MANAGE_AN1_LSB]));
                 #endif
            }
        }
        else
        {
            #ifdef USE_PRINTF
            printf("Offset != 0 (%i), code too dumb to deal with that shit.\n", buf[CP_DATA1]);
            #endif
        }
    }
    else if((buf[CP_XID] == FLEXSEA_EXECUTE_1) || (buf[CP_XID] == FLEXSEA_EXECUTE_2))
    {
        if(buf[CP_DATA1] == 0)
        {
            //Store into array:
            execute_1_data[SRB_EXECUTE_OFFSET] = buf[CP_DATA1];
            execute_1_data[SRB_EXECUTE_STATUS] = buf[CP_DATA1 + 1];
            execute_1_data[SRB_EXECUTE_ENC1_MSB] = buf[CP_DATA1 + 2];
            execute_1_data[SRB_EXECUTE_ENC1_LSB] = buf[CP_DATA1 + 3];
            execute_1_data[SRB_EXECUTE_AN0_MSB] = buf[CP_DATA1 + 4];
            execute_1_data[SRB_EXECUTE_AN0_LSB] = buf[CP_DATA1 + 5];
            execute_1_data[SRB_EXECUTE_AN1_MSB] = buf[CP_DATA1 + 6];
            execute_1_data[SRB_EXECUTE_AN1_LSB] = buf[CP_DATA1 + 7];

            if(verbal)
            {
                execute_num = buf[CP_XID] - 39;   //Trick based on the fact that the code for FLEXSEA_EXECUTE_1 is 40

                #ifdef USE_PRINTF
                printf("\nReading from FLEXSEA_EXECUTE_%i:\n", execute_num);
                printf("Status: 0x%02X\n", execute_1_data[SRB_EXECUTE_STATUS]);
                printf("Encoder #1: %i\n", (execute_1_data[SRB_EXECUTE_ENC1_MSB]<<8) + execute_1_data[SRB_EXECUTE_ENC1_LSB]);
                printf("Analog #0: %i\n", (execute_1_data[SRB_EXECUTE_AN0_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN0_LSB]);
                printf("Analog #1: %i\n", (execute_1_data[SRB_EXECUTE_AN1_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN1_LSB]);
                #endif
            }

            //For now, this is how we transfer data to Python:
            tmp0 = ((execute_1_data[SRB_EXECUTE_AN0_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN0_LSB]);
            tmp1 = ((execute_1_data[SRB_EXECUTE_AN1_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN1_LSB]);
            tmp2 = ((execute_1_data[SRB_EXECUTE_ENC1_MSB]<<8) + execute_1_data[SRB_EXECUTE_ENC1_LSB]);

            #ifdef USE_PRINTF
            printf("\nSensors: [%u, %u, %u]\n\n", tmp0,tmp1,tmp2);
            #else
            printf("%u,%u,%u", tmp0,tmp1,tmp2);
            #endif
        }
        else if(buf[CP_DATA1] == 7)
        {
            //Store into array:

            execute_1_data[SRB_EXECUTE_CURRENT_MSB] = buf[CP_DATA1 + 1];
            execute_1_data[SRB_EXECUTE_CURRENT_LSB] = buf[CP_DATA1 + 2];

            if(verbal)
            {
                execute_num = buf[CP_XID] - 39;   //Trick based on the fact that the code for FLEXSEA_EXECUTE_1 is 40

                #ifdef USE_PRINTF
                printf("\nReading from FLEXSEA_EXECUTE_%i:\n", execute_num);
                printf("Current: %i\n", (execute_1_data[SRB_EXECUTE_CURRENT_MSB]<<8) + execute_1_data[SRB_EXECUTE_CURRENT_LSB]);
                #endif

            }
        }
        else
        {
            #ifdef USE_PRINTF
            printf("Offset != 0 (%i), code too dumb to deal with that shit.\n", buf[CP_DATA1]);
            #endif
        }
    }
    else
    {
        #ifdef USE_PRINTF
        printf("Can't display data as I don't know who's sending it.\n");
        #endif
    }

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_read(unsigned char off)
{
    //Set Read offset
	read_offset = off;

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned int i = 0;
	unsigned char numb = 0;

    //ToDo: quick test. Should be a full structure.

	//ToDo minimalist test: delay then send byte(s)
	NOT_RE_Write(1);			//Disable receiver
	numb = flexsea_prepare_rs485_tx_buffer();	//Prepare data
	CyDelayUs(500);				//Wait (ToDo optimize)

	/*
	for(i = 0; i < 5; i++)
	{
		rs485_putc(0xCC);			//Send i bytes
	}
	*/
	for(i = 0; i < numb; i++)
	{
		//ToDo use string
		rs485_putc(comm_str[i]);
	}

	CyDelayUs(50);				//Wait
	NOT_RE_Write(0);			//Back to normal, enable receiver

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	//Prepare data to be sent, place it in buffer
	flexsea_prepare_spi_tx_buffer();
	flexsea_send_serial_master(0, comm_str, 24);

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN

}

void rx_set_current(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int16 tmp_current = 0;

	//Rebuild 16bit data:
    tmp_current = (buf[CP_DATA1] << 8) + buf[CP_DATA1 + 1];

	current_pid_setpoint = tmp_current;

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_set_control(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned char tmp_ctrl;

    tmp_ctrl = buf[CP_DATA1];

	//Apply the new strategy
	control_strategy(tmp_ctrl);

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_set_current_gains(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned int tmp_current_gain_p = 0, tmp_current_gain_i = 0, tmp_current_gain_d = 0;

	//Rebuild 16bit data:
    tmp_current_gain_p = (buf[CP_DATA1] << 8) + buf[CP_DATA1 + 1];
    tmp_current_gain_i = (buf[CP_DATA1 + 2] << 8) + buf[CP_DATA1 + 3];
    tmp_current_gain_d = (buf[CP_DATA1 + 4] << 8) + buf[CP_DATA1 + 5];

    //Update variables:
    current_gain_p = tmp_current_gain_p;
    current_gain_i = tmp_current_gain_i;
    current_gain_d = tmp_current_gain_d;

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_set_z_gains(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned char tmp_z_gain_k = 0, tmp_z_gain_b = 0, tmp_z_gain_i = 0;

	//Rebuild 16bit data:
    tmp_z_gain_k = (buf[CP_DATA1] << 8) + buf[CP_DATA1 + 1];
    tmp_z_gain_b = (buf[CP_DATA1 + 2] << 8) + buf[CP_DATA1 + 3];
    tmp_z_gain_i = (buf[CP_DATA1 + 4] << 8) + buf[CP_DATA1 + 5];

    //Update variables:
    z_gain_k = tmp_z_gain_k;
    z_gain_b = tmp_z_gain_b;
    z_gain_i = tmp_z_gain_i;

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}
