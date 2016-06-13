//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_rx_cmd: how do we deal with the commands we received?
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

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
#include "motor.h"
#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t read_offset = 0;

//Slave data:
unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];
unsigned char manage_1_data[SLAVE_READ_BUFFER_LEN];

#if defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

struct execute_s exec1, exec2, exec3, exec4;
struct manage_s manag1;

#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//****************************************************************************
// Function(s)
//****************************************************************************

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
    if(buf[P_XID] == FLEXSEA_MANAGE_1)
    {
        if(buf[P_DATA1] == 0)
        {
            //Store into structure
        	exec1.imu.x = (int16_t)BYTES_TO_UINT16(buf[P_DATA1 + 1], buf[P_DATA1 + 2]);
        	exec1.imu.y = (int16_t)BYTES_TO_UINT16(buf[P_DATA1 + 3], buf[P_DATA1 + 4]);
        	exec1.imu.z = (int16_t)BYTES_TO_UINT16(buf[P_DATA1 + 5], buf[P_DATA1 + 6]);

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
        else if(buf[P_DATA1] == 6)
        {
        	exec1.strain = BYTES_TO_UINT16(buf[P_DATA1 + 1], buf[P_DATA1 + 2]);
        	exec1.analog[0] = BYTES_TO_UINT16(buf[P_DATA1 + 3], buf[P_DATA1 + 4]);
        	exec1.current = (int16_t)BYTES_TO_UINT16(buf[P_DATA1 + 5], buf[P_DATA1 + 6]);

            if(verbal)
            {
                #ifdef USE_PRINTF
            	printf("Strain: %i\n", exec1.strain);
            	printf("Analog: %i\n", exec1.analog[0]);
            	printf("Current: %i\n", exec1.current);
				#endif
            }

        }
        else if(buf[P_DATA1] == 12)
        {
        	exec1.encoder = (int32_t)BYTES_TO_UINT32(buf[P_DATA1 + 1], buf[P_DATA1 + 2], buf[P_DATA1 + 3], buf[P_DATA1 + 4]);

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
            printf("Offset != 0 (%i), code too dumb to deal with that shit.\n", buf[P_DATA1]);
            #endif
        }
    }
    else if((buf[P_XID] == FLEXSEA_EXECUTE_1) || (buf[P_XID] == FLEXSEA_EXECUTE_2))
    {
        if(buf[P_DATA1] == 0)
        {
            //Store into array:
            execute_1_data[SRB_EXECUTE_OFFSET] = buf[P_DATA1];
            execute_1_data[SRB_EXECUTE_STATUS] = buf[P_DATA1 + 1];
            execute_1_data[SRB_EXECUTE_ENC1_MSB] = buf[P_DATA1 + 2];
            execute_1_data[SRB_EXECUTE_ENC1_LSB] = buf[P_DATA1 + 3];
            execute_1_data[SRB_EXECUTE_AN0_MSB] = buf[P_DATA1 + 4];
            execute_1_data[SRB_EXECUTE_AN0_LSB] = buf[P_DATA1 + 5];
            execute_1_data[SRB_EXECUTE_AN1_MSB] = buf[P_DATA1 + 6];
            execute_1_data[SRB_EXECUTE_AN1_LSB] = buf[P_DATA1 + 7];

            if(verbal)
            {
                execute_num = buf[P_XID] - 39;   //Trick based on the fact that the code for FLEXSEA_EXECUTE_1 is 40

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
        else if(buf[P_DATA1] == 7)
        {
            //Store into array:

            execute_1_data[SRB_EXECUTE_CURRENT_MSB] = buf[P_DATA1 + 1];
            execute_1_data[SRB_EXECUTE_CURRENT_LSB] = buf[P_DATA1 + 2];

            if(verbal)
            {
                execute_num = buf[P_XID] - 39;   //Trick based on the fact that the code for FLEXSEA_EXECUTE_1 is 40

                #ifdef USE_PRINTF
                printf("\nReading from FLEXSEA_EXECUTE_%i:\n", execute_num);
                printf("Current: %i\n", (execute_1_data[SRB_EXECUTE_CURRENT_MSB]<<8) + execute_1_data[SRB_EXECUTE_CURRENT_LSB]);
                #endif

            }
        }
        else
        {
            #ifdef USE_PRINTF
            printf("Offset != 0 (%i), code too dumb to deal with that shit.\n", buf[P_DATA1]);
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
	uint8_t base_addr = buf[P_DATA1];

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	unsigned int i = 0;
	unsigned char numb = 0;

    //ToDo: quick test. Should be a full structure.		

	numb = flexsea_prepare_rs485_tx_buffer();	//Prepare data
	rs485_puts(comm_str_485_1, numb);


	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	//Prepare data to be sent, place it in buffer
	flexsea_prepare_spi_tx_buffer(base_addr);
	flexsea_send_serial_master(0, comm_str_spi, COMM_STR_BUF_LEN);

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN
	//No code (yet), you shouldn't be here...
	flexsea_error(0);
	#endif	//BOARD_TYPE_FLEXSEA_PLAN

}

//Write value to encoder
void rx_cmd_encoder_write(uint8_t *buf)
{
	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

	int32 tmp = (int32)BYTES_TO_UINT32(buf[P_DATA1], buf[P_DATA1+1], \
				buf[P_DATA1+2], buf[P_DATA1+3]);
	
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

	strain_config(buf[P_DATA1], buf[P_DATA1+1], buf[P_DATA1]+2);
		
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
	tx_cmd_encoder_read_reply(buf[P_XID], encoder_read());
	numb = comm_gen_str(payload_str, comm_str_485_1, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;	//Fixed length for now
	
	//Send it out:
	rs485_puts(comm_str_485_1, (numb));	
		
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
	tx_cmd_strain_read_reply(buf[P_XID], strain_read());
	numb = comm_gen_str(payload_str, comm_str_485_1, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;	//Fixed length for now
	
	//Send it out:
	rs485_puts(comm_str_485_1, (numb));			
		
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
	tx_cmd_imu_read_reply(buf[P_XID], buf[P_DATA1], buf[P_DATA1+1]);
	numb = comm_gen_str(payload_str, comm_str_485_1, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;	//Fixed length for now
	
	//Send it out:
	rs485_puts(comm_str_485_1, (numb));	
		
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
	tx_cmd_analog_read_reply(buf[P_XID], buf[P_DATA1], buf[P_DATA1+1]);
	numb = comm_gen_str(payload_str, comm_str_485_1, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;	//Fixed length for now
	
	//Send it out:
	rs485_puts(comm_str_485_1, (numb));			
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	uint8_t numb = 0;

	//Generate the reply:
	tx_cmd_analog_read_reply(buf[P_XID], buf[P_DATA1], buf[P_DATA1+1]);
	numb = comm_gen_str(payload_str, comm_str_spi, PAYLOAD_BUF_LEN);

	//Send it out: //ToDo *******
	//Prepare data to be sent, place it in buffer
	//flexsea_prepare_spi_tx_buffer();
	flexsea_send_serial_master(0, comm_str_spi, COMM_STR_BUF_LEN);

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
	tmp_enc = (int32_t) (BYTES_TO_UINT32(buf[P_DATA1], buf[P_DATA1+1], buf[P_DATA1+2], buf[P_DATA1+3]));
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
	tmp_gyro_x = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+1], buf[P_DATA1+2]));
	tmp_gyro_y = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+3], buf[P_DATA1+4]));
	tmp_gyro_z = (int16_t) (BYTES_TO_UINT16(buf[P_DATA1+5], buf[P_DATA1+6]));
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
	tmp_strain = (BYTES_TO_UINT16(buf[P_DATA1], buf[P_DATA1+1]));
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
	tmp_analog = (BYTES_TO_UINT16(buf[P_DATA1+1], buf[P_DATA1+2]));
	//ToDo store that value somewhere useful
	//ToDo: we need to check the base address and assign the bytes to the right variables

	#ifdef BOARD_TYPE_FLEXSEA_EXECUTE
		
	#endif	//BOARD_TYPE_FLEXSEA_EXECUTE

	#ifdef BOARD_TYPE_FLEXSEA_MANAGE

	exec1.analog[0] = tmp_analog;

	#endif	//BOARD_TYPE_FLEXSEA_MANAGE

	#ifdef BOARD_TYPE_FLEXSEA_PLAN

	#ifdef USE_PRINTF
	printf("Received CMD_ANALOG_READ_REPLY. Analog 0 = %i.\n", tmp_analog);
	#endif	//USE_PRINTF

	//ToDo do something more useful that a printf

	#endif	//BOARD_TYPE_FLEXSEA_PLAN
}

#ifdef __cplusplus
}
#endif
