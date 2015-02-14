//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
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
#include "main.h"
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned char read_offset = 0;

//Slave data:
unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];
unsigned char manage_1_data[SLAVE_READ_BUFFER_LEN];

#if defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

struct execute_s exec1;

#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//****************************************************************************
// External variable(s)
//****************************************************************************

extern unsigned char comm_str[COMM_STR_BUF_LEN];

//flexsea_payload:
extern unsigned char payload_str[];

#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

extern int steps;

//motor.c:
extern struct ctrl_s ctrl;
extern struct enc_s encoder;	

#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

#ifdef BOARD_TYPE_FLEXSEA_MANAGE
//main.c
extern uint8_t autosampling;
#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//****************************************************************************
// Function(s)
//****************************************************************************

void rx_cmd_ctrl_p_gains_write(uint8_t *buf)
{
    #ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint16_t tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
		
	//Rebuild 16bit data:
	tmp1 = (int16_t)(BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1+1]));
	tmp2 = (int16_t)(BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
	tmp3 = (int16_t)(BYTES_TO_UINT16(buf[CP_DATA1+4], buf[CP_DATA1+5]));
	tmp4 = (int16_t)(BYTES_TO_UINT16(buf[CP_DATA1+6], buf[CP_DATA1+7]));
		
	//ToDo Add more safety checks!
	if(tmp1 > 0)
		ctrl.position.gain.P_KP = tmp1;
	else
		ctrl.position.gain.P_KP = 0;

	if(tmp2 > 0)
		ctrl.position.gain.P_KI = tmp2;
	else
		ctrl.position.gain.P_KI = 0;

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

//ToDo *** Fix or Remove ***
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

	if(ctrl.active_ctrl == CTRL_POSITION)
	{
		steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);
	}
	else if(ctrl.active_ctrl == CTRL_IMPEDANCE)
	{
		//Backup gains
		tmp_z_k = ctrl.impedance.gain.Z_K; 
		tmp_z_b = ctrl.impedance.gain.Z_B;	
		tmp_z_i = ctrl.impedance.gain.Z_I;

		//Zero them
		ctrl.impedance.gain.Z_K = 0;
		ctrl.impedance.gain.Z_B = 0;
		ctrl.impedance.gain.Z_I = 0;
		
		//New trajectory
		steps = trapez_gen_motion_1(tmp_posi, tmp_posf, tmp_spdm, tmp_acc);
		
		//Restore gains
		ctrl.impedance.gain.Z_K = tmp_z_k;
		ctrl.impedance.gain.Z_B = tmp_z_b;
		ctrl.impedance.gain.Z_I = tmp_z_i;
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

void rx_cmd_clutch_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	clutch_output(buf[CP_DATA1]);

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

void rx_cmd_ctrl_o_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int32 tmp_mot_spd = 0;

	//Rebuild 32bit data and limit it to 16bits
    tmp_mot_spd = BYTES_TO_UINT32(	buf[CP_DATA1], buf[CP_DATA1 + 1], \
									buf[CP_DATA1 + 2], buf[CP_DATA1 + 3]);
	tmp_mot_spd &= 0xFFFF;

	if(ctrl.active_ctrl == CTRL_OPEN)
	{
		motor_open_speed_1((int16)tmp_mot_spd);
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

//Display the data received from a slave after a read request
void rx_cmd_mem_read_reply(uint8_t *buf, uint8_t verbal)
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
            //Store into structure
        	exec1.imu.x = (int16_t)BYTES_TO_UINT16(buf[CP_DATA1 + 1], buf[CP_DATA1 + 2]);
        	exec1.imu.y = (int16_t)BYTES_TO_UINT16(buf[CP_DATA1 + 3], buf[CP_DATA1 + 4]);
        	exec1.imu.z = (int16_t)BYTES_TO_UINT16(buf[CP_DATA1 + 5], buf[CP_DATA1 + 6]);

            if(verbal)
            {
                #ifdef USE_PRINTF
            	printf("Gyro X: %i\n", exec1.imu.x);
            	printf("Gyro Y: %i\n", exec1.imu.y);
            	printf("Gyro Z: %i\n", exec1.imu.z);
            	//printf("Strain: %i\n", exec1.strain);
				#endif
            }
        }
        else if(buf[CP_DATA1] == 6)
        {
        	exec1.strain = BYTES_TO_UINT16(buf[CP_DATA1 + 1], buf[CP_DATA1 + 2]);
        	exec1.analog = BYTES_TO_UINT16(buf[CP_DATA1 + 3], buf[CP_DATA1 + 4]);
        	exec1.current = (int16_t)BYTES_TO_UINT16(buf[CP_DATA1 + 5], buf[CP_DATA1 + 6]);

            if(verbal)
            {
                #ifdef USE_PRINTF
            	printf("Strain: %i\n", exec1.strain);
            	printf("Analog: %i\n", exec1.analog);
            	printf("Current: %i\n", exec1.current);
				#endif
            }

        }
        else if(buf[CP_DATA1] == 12)
        {
        	exec1.encoder = (int32_t)BYTES_TO_UINT32(buf[CP_DATA1 + 1], buf[CP_DATA1 + 2], buf[CP_DATA1 + 3], buf[CP_DATA1 + 4]);

            if(verbal)
            {
                #ifdef USE_PRINTF
            	printf("Encoder: %i\n", exec1.encoder);
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

//ToDo: currently using a simplified implementation, only using base_addr and a fixed # of bytes
void rx_cmd_mem_read(unsigned char *buf)
{
	uint8_t base_addr = buf[CP_DATA1];

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned int i = 0;
	unsigned char numb = 0;

    //ToDo: quick test. Should be a full structure.

	//ToDo minimalist test: delay then send byte(s)
	NOT_RE_Write(1);			//Disable receiver
	numb = flexsea_prepare_rs485_tx_buffer();	//Prepare data
	CyDelayUs(500);				//Wait (ToDo optimize)

	for(i = 0; i < numb; i++)
	{
		//ToDo use puts
		rs485_putc(comm_str[i]);
	}

	CyDelayUs(50);				//Wait
	NOT_RE_Write(0);			//Back to normal, enable receiver

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	//Prepare data to be sent, place it in buffer
	flexsea_prepare_spi_tx_buffer(base_addr);
	flexsea_send_serial_master(0, comm_str, 24);

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN

}

void rx_cmd_ctrl_i_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int16 tmp_current = 0;

	//Rebuild 16bit data:
    tmp_current = BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1 + 1]);

	ctrl.current.setpoint_val = tmp_current;

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

void rx_cmd_ctrl_mode_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	//Apply the new strategy
	control_strategy(buf[CP_DATA1]);

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

void rx_cmd_ctrl_i_gains(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint32_t tmp_current_gain_p = 0, tmp_current_gain_i = 0, tmp_current_gain_d = 0;

	//Rebuild 16bit data:
    tmp_current_gain_p = BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1+1]);
    tmp_current_gain_i = BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]);
    tmp_current_gain_d = BYTES_TO_UINT16(buf[CP_DATA1+4], buf[CP_DATA1+5]);

    //Update variables:
    ctrl.current.gain.I_KP = tmp_current_gain_p;
    ctrl.current.gain.I_KI = tmp_current_gain_i;
    ctrl.current.gain.I_KD = tmp_current_gain_d;

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

//ToDo *** Fix or Remove ***
void rx_set_z_gains(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned char tmp_z_gain_k = 0, tmp_z_gain_b = 0, tmp_z_gain_i = 0;

	//Rebuild 16bit data:
    tmp_z_gain_k = (buf[CP_DATA1] << 8) + buf[CP_DATA1 + 1];
    tmp_z_gain_b = (buf[CP_DATA1 + 2] << 8) + buf[CP_DATA1 + 3];
    tmp_z_gain_i = (buf[CP_DATA1 + 4] << 8) + buf[CP_DATA1 + 5];

    //Update variables:
    ctrl.impedance.gain.Z_K = tmp_z_gain_k;
    ctrl.impedance.gain.Z_B = tmp_z_gain_b;
    ctrl.impedance.gain.Z_I = tmp_z_gain_i;

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

/*
//Template:
void rx_cmd_xxx(unsigned char *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}
*/

//Write value to encoder
void rx_cmd_encoder_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int32 tmp = (int32)BYTES_TO_UINT32(buf[CP_DATA1], buf[CP_DATA1+1], \
				buf[CP_DATA1+2], buf[CP_DATA1+3]);
	
	encoder_write(tmp);	
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//Write strain configuration
void rx_cmd_strain_config(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	strain_config(buf[CP_DATA1], buf[CP_DATA1+1], buf[CP_DATA1]+2);
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//
void rx_cmd_encoder_read(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_encoder_read_reply(buf[CP_XID], encoder_read());
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	
	//Send it out:
	rs485_puts(comm_str, (numb+1));	
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//
void rx_cmd_strain_read(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_strain_read_reply(buf[CP_XID], strain_read());
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	
	//Send it out:
	rs485_puts(comm_str, (numb+1));			
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//
void rx_cmd_imu_read(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_imu_read_reply(buf[CP_XID], buf[CP_DATA1], buf[CP_DATA1+1]);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	
	//Send it out:
	rs485_puts(comm_str, (numb+1));	
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//
void rx_cmd_analog_read(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_analog_read_reply(buf[CP_XID], buf[CP_DATA1], buf[CP_DATA1+1]);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	
	//Send it out:
	rs485_puts(comm_str, (numb+1));			
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_analog_read_reply(buf[CP_XID], buf[CP_DATA1], buf[CP_DATA1+1]);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);

	//Send it out: //ToDo *******
	//Prepare data to be sent, place it in buffer
	//flexsea_prepare_spi_tx_buffer();
	flexsea_send_serial_master(0, comm_str, 24);

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

//
void rx_cmd_ctrl_i_read(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_ctrl_i_read_reply(buf[CP_XID], (ctrl.current.actual_val - CURRENT_ZERO), ctrl.current.setpoint_val);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	
	//Send it out:
	rs485_puts(comm_str, (numb+1));			
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

// ***
// ToDo I need a lot of very similar functions for the code. Should functions like rx_cmd_encoder_read_reply() exist? Or should I know that it's a reply because it's coming from my slave?
// I'll explicitly code them for now, because it's a brainless task, but I need to think about a simpler/better solution.
// ***

//
void rx_cmd_encoder_read_reply(uint8_t *buf)
{
	int32_t tmp_enc = 0;

	//Decode the reply we received:
	tmp_enc = (int32_t) (BYTES_TO_UINT32(buf[CP_DATA1], buf[CP_DATA1+1], buf[CP_DATA1+2], buf[CP_DATA1+3]));
	//ToDo store that value somewhere useful

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	//No code (yet), you shouldn't be here...
	flexsea_error(SE_CMD_NOT_PROGRAMMED);

	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	exec1.encoder = tmp_enc;

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN

	#ifdef USE_PRINTF
	printf("Received CMD_ENCODER_READ_REPLY: %i.\n", tmp_enc);
	#endif	//USE_PRINTF

	//ToDo do something more useful that a printf

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_cmd_imu_read_reply(uint8_t *buf)
{
	int16_t tmp_gyro_x = 0, tmp_gyro_y = 0, tmp_gyro_z = 0;

	//Decode the reply we received:
	tmp_gyro_x = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+1], buf[CP_DATA1+2]));
	tmp_gyro_y = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+3], buf[CP_DATA1+4]));
	tmp_gyro_z = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+5], buf[CP_DATA1+6]));
	//ToDo store that value somewhere useful
	//ToDo: we need to check the base address and assign the bytes to the right variables

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	exec1.imu.x = tmp_gyro_x;
	exec1.imu.y = tmp_gyro_y;
	exec1.imu.z = tmp_gyro_z;

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN

	#ifdef USE_PRINTF
	printf("Received CMD_IMU_READ_REPLY (gyro): \nx = %i\ny = %i\nz = %i.\n\n", tmp_gyro_x, tmp_gyro_y, tmp_gyro_z);
	#endif	//USE_PRINTF

	//ToDo do something more useful that a printf

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_cmd_strain_read_reply(uint8_t *buf)
{
	uint16_t tmp_strain = 0;

	//Decode the reply we received:
	tmp_strain = (BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1+1]));
	//ToDo store that value somewhere useful

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	exec1.strain = tmp_strain;

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN

	#ifdef USE_PRINTF
	printf("Received CMD_STRAIN_READ_REPLY: %i.\n", tmp_strain);
	#endif	//USE_PRINTF

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_cmd_analog_read_reply(uint8_t *buf)
{
	uint16_t tmp_analog = 0;

	//Decode the reply we received:
	tmp_analog = (BYTES_TO_UINT16(buf[CP_DATA1+1], buf[CP_DATA1+2]));
	//ToDo store that value somewhere useful
	//ToDo: we need to check the base address and assign the bytes to the right variables

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	exec1.analog = tmp_analog;

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN

	#ifdef USE_PRINTF
	printf("Received CMD_ANALOG_READ_REPLY. Analog 0 = %i.\n", tmp_analog);
	#endif	//USE_PRINTF

	//ToDo do something more useful that a printf

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_cmd_ctrl_i_read_reply(uint8_t *buf)
{
	int16_t tmp_wanted_current = 0, tmp_measured_current = 0;

	//Decode the reply we received:
	tmp_measured_current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1], buf[CP_DATA1+1]));
	tmp_wanted_current = (int16_t) (BYTES_TO_UINT16(buf[CP_DATA1+2], buf[CP_DATA1+3]));
	//ToDo store that value somewhere useful

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	exec1.current = tmp_measured_current;

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN


	#ifdef USE_PRINTF
	printf("Received CMD_CTRL_I_READ_REPLY. Wanted = %i, Measured = %i.\n", tmp_wanted_current, tmp_measured_current);
	#endif	//USE_PRINTF

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

void rx_cmd_acq_mode_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	autosampling = buf[CP_DATA1];

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}
