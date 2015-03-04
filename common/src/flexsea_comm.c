//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocole
//****************************************************************************

// *** ToDo Update this block of comments ***

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
#include <project.h>

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t comm_str[COMM_STR_BUF_LEN], comm_str_tmp[COMM_STR_BUF_LEN];	//ToDo will be replaced

uint8_t rx_command_spi[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
uint8_t rx_command_485_1[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
uint8_t rx_command_485_2[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];

struct slave_comm_s slaves_485_1, slaves_485_2;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static uint8_t unpack_payload(uint8_t *buf, uint8_t rx_cmd[][PACKAGED_PAYLOAD_LEN]);
static void clear_rx_command(uint8_t x, uint8_t y, uint8_t rx_cmd[][PACKAGED_PAYLOAD_LEN]);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Takes payload, adds ESCAPES, checksum, header, ...
//ToDo update naming convention, think about multiple buffers
unsigned char comm_gen_str(unsigned char payload[], unsigned char bytes)
{
    unsigned int i = 0, escapes = 0, idx = 0, total_bytes = 0;
    unsigned char checksum = 0;

    //Fill comm_str with zeros
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        comm_str[i] = 0xAA; //'0';
    }
#ifdef DEBUG_COMM_USING_PRINTF
    printf("comm_str: %s\n", comm_str);
#endif

    //Fill comm_str with payload and add ESCAPE characters
    escapes = 0;
    idx = 2;
    for(i = 0; i < bytes; i++)
    {
        if ((payload[i] == HEADER) || (payload[i] == FOOTER) || (payload[i] == ESCAPE))
        {
            escapes = escapes + 1;
            comm_str[idx] = ESCAPE;
            comm_str[idx+1] = payload[i];
            idx = idx + 1;
        }
        else
        {
            comm_str[idx] = payload[i];
        }
        idx++;
    }
#ifdef DEBUG_COMM_USING_PRINTF
    printf("comm_str: %s\n", comm_str);
#endif

    total_bytes = bytes + escapes;

#ifdef DEBUG_COMM_USING_PRINTF
    printf("total_bytes: %i\n", total_bytes);
#endif

    //Checksum:
    checksum = 0;
    for (i = 0; i < total_bytes; i++)
    {
#ifdef DEBUG_COMM_USING_PRINTF
        printf("cs b[%i] = %c\n", i, comm_str[2+i]);
#endif
        checksum = checksum + comm_str[2+i];
    }
#ifdef DEBUG_COMM_USING_PRINTF
    printf("checksum: %i\n", checksum);
#endif

    //Build comm_str:
    comm_str[0] = HEADER;
    comm_str[1] = total_bytes;
    comm_str[2 + total_bytes] = checksum;
    comm_str[3 + total_bytes] = FOOTER;

    //Return the length of the valid data
    return (3 + total_bytes);
}



//To avoid sharing buffers in multiple files we use specific functions:

uint8_t unpack_payload_spi(void)
{
	return unpack_payload(rx_buf_spi, rx_command_spi);
}

uint8_t unpack_payload_485_1(void)
{
	return unpack_payload(rx_buf_485_1, rx_command_485_1);
}

uint8_t unpack_payload_485_2(void)
{
	return unpack_payload(rx_buf_485_2, rx_command_485_2);
}

/*
uint8_t unpack_payload_usb(void)
{
	return unpack_payload(rx_buf_usb, rx_command_usb);
}
*/

//Quick way to debug the comm functions with the debugger and the terminal.
//Make sure to enable the printf statements.
void test_flexsea_comm(void)
{
    uint8_t i = 0, res = 0, bytes = 0;
    //uint8_t test_data[] = {'1', '2', '3', '4', '5', '6'}; //Test payload
    //printf("test_data: >> %s <<\n", (char*) test_data);

    //We are using a command that Plan can receive to test the parser too:
    bytes = tx_cmd_ctrl_i_read_reply(FLEXSEA_PLAN_1, 100, 200);
    //(this fills payload_str[])

    DEBUG_PRINTF("bytes = %i\n", bytes);

    //Clear current payload:
    clear_rx_command(PAYLOAD_BUFFERS, PACKAGED_PAYLOAD_LEN, rx_command_spi);

    //printf("rx_command_spi[0][]: >> %s <<\n", (char*)rx_command_spi[0]);

    //Build comm_str
    res = comm_gen_str(payload_str, bytes);

    DEBUG_PRINTF("comm_str[]: >> %s <<\n", (char*)comm_str);
    DEBUG_PRINTF("res = %i\n", res);

    DEBUG_PRINTF("\nrx_buf_spi[]: >> %s <<\n", (char*)rx_buf_spi);

    //Feed it to the input buffer
    for(i = 0; i < PACKAGED_PAYLOAD_LEN; i++)
    {
        update_rx_buf_byte_spi(comm_str[i]);
    }

    DEBUG_PRINTF("rx_buf_spi[]: >> %s <<\n", (char*)rx_buf_spi);

    //Try to decode
    res = unpack_payload_spi();

    DEBUG_PRINTF("Found %i payload(s).\n", res);

    //Can we parse it?

    res = payload_parse_str(rx_command_spi[0]);

    //If it works, the console/terminal should display
    //"Received CMD_CTRL_I_READ_REPLY. Wanted = 200, Measured = 100."
}

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

                        //Remove the string to avoid double detection
                        for(h = i; h <= possible_footer_pos; h++)
                        {
                            buf[h] = 0;
                        }

                        DEBUG_PRINTF("payload: %s\n",rx_cmd[payload_strings-1]);
                    }
                    else
                    {
						EXP5_Write(1);
                    	DEBUG_PRINTF("Wrong checksum\n");
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

	EXP5_Write(0);
	
    //Returns the number of decoded strings
    return payload_strings;
}

//Empties the buffer
static void clear_rx_command(uint8_t x, uint8_t y, uint8_t rx_cmd[][PACKAGED_PAYLOAD_LEN])
{
    unsigned char i = 0, j = 0;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
        	rx_cmd[i][j] = 0;
        }
    }
}
