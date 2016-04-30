//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocol
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//FlexSEA comm. prototype:
//=======================
//[HEADER][# of BYTES][DATA...][CHECKSUM][FOOTER]
//=> Number of bytes includes the ESCAPE bytes
//=> Checksum is done on the payload (data + ESCAPEs) and on the BYTES byte.

//To transmit a message:
//======================
// 1) Place the payload in an array (no header, no footer: pure data)
// 2) Call comm_gen_str(your_data_array, number_of_bytes)
// 2b) It will return the index of the last byte of the message (add 1 for the length)
// 2c) The message is in comm_str[]
// 3) Send comm_str[] (x_puts(comm_str, msg_length));

//To receive a message:
//=====================
// 1) Assuming that you have dealt with all the previous messages, call comm_str_payload();
//    to fill the buffer with zeros
// 2) Every time you receive a byte update the buffer: comm_update_rx_buffer(your_new_byte);
// 3) Call payload_str_available_in_buffer = comm_decode_str(). If you get >= 1, read the
//    comm_str_payload buffer and do something with the data!
// 4) At this point you might want to flush the read payload from rx_buf

//****************************************************************************
// Include(s)
//****************************************************************************

#include "../inc/flexsea.h"
#include "flexsea_board.h"
#include "flexsea_system.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t comm_str_tmp[COMM_STR_BUF_LEN];
#ifdef ENABLE_FLEXSEA_BUF_1
uint8_t comm_str_1[COMM_STR_BUF_LEN];
uint8_t rx_command_1[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
uint8_t comm_str_2[COMM_STR_BUF_LEN];
uint8_t rx_command_2[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
uint8_t comm_str_3[COMM_STR_BUF_LEN];
uint8_t rx_command_3[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
uint8_t comm_str_4[COMM_STR_BUF_LEN];
uint8_t rx_command_4[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_4

uint32_t cmd_valid = 0;
uint32_t cmd_bad_checksum = 0;

//ToDo: this is project specific! Eliminate or use generic names!
struct slave_comm_s slaves_485_1, slaves_485_2;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static uint8_t unpack_payload(uint8_t *buf, uint8_t rx_cmd[][PACKAGED_PAYLOAD_LEN]);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Takes payload, adds ESCAPES, checksum, header, ...
uint8_t comm_gen_str(uint8_t payload[], uint8_t *cstr, uint8_t bytes)
{
    unsigned int i = 0, escapes = 0, idx = 0, total_bytes = 0;
    unsigned char checksum = 0;

    //Fill comm_str with zeros
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
    	cstr[i] = 0xAA; //'0';
    }
    DEBUG_COMM_PRINTF("comm_str: %s\n", cstr);

    //Fill comm_str with payload and add ESCAPE characters
    escapes = 0;
    idx = 2;
    for(i = 0; i < bytes; i++)
    {
        if ((payload[i] == HEADER) || (payload[i] == FOOTER) || (payload[i] == ESCAPE))
        {
            escapes = escapes + 1;
            cstr[idx] = ESCAPE;
            cstr[idx+1] = payload[i];
            idx = idx + 1;
        }
        else
        {
        	cstr[idx] = payload[i];
        }
        idx++;
    }
    DEBUG_COMM_PRINTF("comm_str: %s\n", cstr);

    total_bytes = bytes + escapes;

    DEBUG_COMM_PRINTF("total_bytes: %i\n", total_bytes);

    //Checksum:
    checksum = 0;
    for (i = 0; i < total_bytes; i++)
    {
    	//DEBUG_COMM_PRINTF("cs b[%i] = %c\n", i, cstr[2+i]);

        checksum = checksum + cstr[2+i];
    }

    DEBUG_COMM_PRINTF("checksum: %i\n", checksum);


    //Build comm_str:
    cstr[0] = HEADER;
    cstr[1] = total_bytes;
    cstr[2 + total_bytes] = checksum;
    cstr[3 + total_bytes] = FOOTER;

    //Return the length of the valid data
    return (3 + total_bytes);
}

//To avoid sharing buffers in multiple files we use specific functions:

#ifdef ENABLE_FLEXSEA_BUF_1
uint8_t unpack_payload_1(void)
{
	return unpack_payload(rx_buf_1, rx_command_1);
}
#endif	//ENABLE_FLEXSEA_BUF_1

#ifdef ENABLE_FLEXSEA_BUF_2
uint8_t unpack_payload_2(void)
{
	return unpack_payload(rx_buf_2, rx_command_2);
}
#endif	//ENABLE_FLEXSEA_BUF_2

#ifdef ENABLE_FLEXSEA_BUF_3
uint8_t unpack_payload_3(void)
{
	return unpack_payload(rx_buf_3, rx_command_3);
}
#endif	//ENABLE_FLEXSEA_BUF_3

#ifdef ENABLE_FLEXSEA_BUF_4
uint8_t unpack_payload_4(void)
{
	return unpack_payload(rx_buf_4, rx_command_4);
}
#endif	//ENABLE_FLEXSEA_BUF_4

//****************************************************************************
// Private Function(s)
//****************************************************************************

//New version of comm_decode_str
//Take a buffer as an argument, returns the number of decoded payload packets
static uint8_t unpack_payload(uint8_t *buf, uint8_t rx_cmd[][PACKAGED_PAYLOAD_LEN])
{
    uint32_t i = 0, j = 0, k = 0, idx = 0, h = 0;
    uint32_t bytes = 0, possible_footer = 0, possible_footer_pos = 0;
    uint8_t checksum = 0, skip = 0, payload_strings = 0;
    uint8_t rx_buf_tmp[RX_BUF_LEN];

    for(i = 0; i < (RX_BUF_LEN - 2); i++)
    {
        if(buf[i] == HEADER)
        {
            //We found a header
        	DEBUG_PRINTF("===\nFound header\n");

            bytes = buf[i+1];
            DEBUG_PRINTF("bytes = %i\n", bytes);

            possible_footer_pos = i+3+bytes;

            DEBUG_PRINTF("pos foot pos: %i\n", possible_footer_pos);

            if(possible_footer_pos <= RX_BUF_LEN)
            {
                //We have enough bytes for a full string
            	DEBUG_PRINTF("Enough data\n");
                possible_footer = buf[possible_footer_pos];
                if(possible_footer == FOOTER)
                {
                    //Correctly framed string
                	DEBUG_PRINTF("Correctly framed\n");

                    k = 0;
                    for(j = i; j <= possible_footer_pos; j++)
                    {
                        //Copy string in temp buffer
                        rx_buf_tmp[k] = buf[j];
                        k++;
                    }

                    DEBUG_PRINTF("rx_buf_tmp: %s\n",rx_buf_tmp);

                    //Is the checksum OK?
                    checksum = 0;
                    for (k = 0; k < bytes; k++)
                    {
                    	//DEBUG_PRINTF("cs b[%i] = %c\n", k, rx_buf_tmp[2+k]);

                        checksum = checksum + rx_buf_tmp[2+k];
                    }

                    DEBUG_PRINTF("Computed checksum: %i\n", checksum);
                    DEBUG_PRINTF("Compared to: %i\n", rx_buf_tmp[2+bytes]);

                    if(checksum == rx_buf_tmp[2+bytes])
                    {
                    	DEBUG_PRINTF("Checksum matches\n");

                        //Now we de-escap and de-frame to get the payload
                        idx = 0;
                        skip = 0;
                        for(k = 2; k < (unsigned int)(2+bytes); k++)
                        {
                            if(((rx_buf_tmp[k] == HEADER) || (rx_buf_tmp[k] == FOOTER) || (rx_buf_tmp[k] == ESCAPE)) && skip == 0)
                            {
                            	DEBUG_PRINTF("Skipped 1 ESC\n");

                                skip = 1;
                            }
                            else
                            {
                                skip = 0;
                                rx_cmd[payload_strings][idx] = rx_buf_tmp[k];
                                idx++;
                            }
                        }

                        //At this point we have extracted a valid string
                        payload_strings++;
						cmd_valid++;

                        //Remove the string to avoid double detection
                        for(h = i; h <= possible_footer_pos; h++)
                        {
                            buf[h] = 0;
                        }

                        DEBUG_PRINTF("payload: %s\n",rx_cmd[payload_strings-1]);
                    }
                    else
                    {
                    	DEBUG_PRINTF("Wrong checksum\n");

						//Remove the string to avoid double detection
                        for(h = i; h <= possible_footer_pos; h++)
                        {
                            buf[h] = 0;
                        }

						cmd_bad_checksum++;
                    }
                }
                else
                {
                	DEBUG_PRINTF("Scrap\n");
                }
            }
            else
            {
            	DEBUG_PRINTF("Not enough data (too short)\n");
            }
        }
    }

    //Returns the number of decoded strings
    return payload_strings;
}

#ifdef __cplusplus
}
#endif
