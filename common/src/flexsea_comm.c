//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocole
//****************************************************************************

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

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned char rx_buf[RX_BUF_LEN];          //Contains the input data
unsigned char input_buffer[RX_BUF_LEN];    //For test functions only
unsigned char comm_str_payload[PAYLOAD_BUF_LEN][COMM_STR_BUF_LEN];
unsigned char test_data[] = {'1', FOOTER, HEADER, '2', '3', HEADER}; //Test payload
unsigned char comm_str[COMM_STR_BUF_LEN], comm_str_tmp[COMM_STR_BUF_LEN];

//New RX buffers:
uint8_t rx_buf_spi[RX_BUF_LEN];
uint8_t rx_buf_485_1[RX_BUF_LEN];

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//Takes payload, adds ESCAPES, checksum, header, ...
unsigned char comm_gen_str(unsigned char payload[], unsigned char bytes)
{
    unsigned int i = 0, escapes = 0, idx = 0, total_bytes = 0;
    unsigned char checksum = 0;

    //Fill comm_str with zeros
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        comm_str[i] = '0';
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

//Decode communication string
//=============================
//This is a C version of dec_comm_str_1.m. It uses a pre-filled buffer.
//Always call comm_update_rx_buffer() before calling this function
//Returns the number of decoded strings

unsigned char comm_decode_str(void)
{
    unsigned int i = 0, j = 0, k = 0, idx = 0, h = 0;
    unsigned char bytes = 0, possible_footer = 0, possible_footer_pos = 0;
    unsigned char checksum = 0, skip = 0, payload_strings = 0;

    for(i = 0; i < (RX_BUF_LEN - 2); i++)
    {
        if(rx_buf[i] == HEADER)
        {
            //We found a header
#ifdef DEBUG_COMM_USING_PRINTF
            printf("===\n");
            printf("Found header\n");
#endif

            bytes = rx_buf[i+1];
#ifdef DEBUG_COMM_USING_PRINTF
            printf("bytes = %i\n", bytes);
#endif

            possible_footer_pos = i+3+bytes;

#ifdef DEBUG_COMM_USING_PRINTF
            printf("pos foot pos: %i\n", possible_footer_pos);
#endif

            if(possible_footer_pos <= RX_BUF_LEN)
            {
                //We have enough bytes for a full string
#ifdef DEBUG_COMM_USING_PRINTF
                printf("Enough data\n");
#endif
                possible_footer = rx_buf[possible_footer_pos];
                if(possible_footer == FOOTER)
                {
                    //Correctly framed string
#ifdef DEBUG_COMM_USING_PRINTF
                    printf("Correctly framed\n");
#endif
                    k = 0;
                    for(j = i; j <= possible_footer_pos; j++)
                    {
                        //Copy string in temp buffer
                        comm_str_tmp[k] = rx_buf[j];
                        k++;
                    }
#ifdef DEBUG_COMM_USING_PRINTF
                    printf("comm_str_tmp: %s\n",comm_str_tmp);
#endif

                    //Is the checksum OK?
                    checksum = 0;
                    for (k = 0; k < bytes; k++)
                    {
#ifdef DEBUG_COMM_USING_PRINTF
                        printf("cs b[%i] = %c\n", k, comm_str_tmp[2+k]);
#endif
                        checksum = checksum + comm_str_tmp[2+k];
                    }
#ifdef DEBUG_COMM_USING_PRINTF
                    printf("checksum: %i\n", checksum);
                    printf("Compared to: %i\n", comm_str_tmp[2+bytes]);
#endif
                    if(checksum == comm_str_tmp[2+bytes])
                    {
#ifdef DEBUG_COMM_USING_PRINTF
                        printf("Checksum matches\n");
#endif
                        //Now we de-escap and de-frame to get the payload
                        idx = 0;
                        skip = 0;
                        for(k = 2; k < (unsigned int)(2+bytes); k++)
                        {
                            if(((comm_str_tmp[k] == HEADER) || (comm_str_tmp[k] == FOOTER) || (comm_str_tmp[k] == ESCAPE)) && skip == 0)
                            {
#ifdef DEBUG_COMM_USING_PRINTF
                                printf("Skipped 1 ESC\n");
#endif
                                skip = 1;
                            }
                            else
                            {
                                skip = 0;
                                comm_str_payload[payload_strings][idx] = comm_str_tmp[k];
                                idx++;
                            }
                        }
                        //At this point we have extracted a valid string
                        payload_strings++;
                        //Remove the string to avoid double detection
                        for(h = i; h <= possible_footer_pos; h++)
                        {
                            rx_buf[h] = '0';
                        }

#ifdef DEBUG_COMM_USING_PRINTF
                        printf("payload: %s\n",comm_str_payload[payload_strings]);
#endif
                    }
                    else
                    {
#ifdef DEBUG_COMM_USING_PRINTF
                        printf("Wrong checksum\n");
#endif
                    }
                }
                else
                {
#ifdef DEBUG_COMM_USING_PRINTF
                    printf("Scrap\n");
#endif
                }
            }
            else
            {
#ifdef DEBUG_COMM_USING_PRINTF
                printf("Not enough data (too short)\n");
#endif
            }
        }
    }

    //Returns the number of decoded strings
    return payload_strings;
}

//New version of comm_decode_str
//Take a buffer as an argument
uint8_t unpack_payload(uint8_t *buf)
{
    uint32_t i = 0, j = 0, k = 0, idx = 0, h = 0;
    uint8_t bytes = 0, possible_footer = 0, possible_footer_pos = 0;
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
                    	DEBUG_PRINTF("cs b[%i] = %c\n", k, rx_buf_tmp[2+k]);

                        checksum = checksum + rx_buf_tmp[2+k];
                    }

                    DEBUG_PRINTF("checksum: %i\n", checksum);
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
                                comm_str_payload[payload_strings][idx] = rx_buf_tmp[k];
                                idx++;
                            }
                        }

                        //At this point we have extracted a valid string
                        payload_strings++;

                        //Remove the string to avoid double detection
                        for(h = i; h <= possible_footer_pos; h++)
                        {
                            buf[h] = '0';
                        }

                        DEBUG_PRINTF("payload: %s\n",comm_str_payload[payload_strings]);
                    }
                    else
                    {
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

    //Returns the number of decoded strings
    return payload_strings;
}

//Fills the comm_str_payload buffer with zeros
void comm_clear_str_payload(void)
{
    unsigned char i = 0, j = 0;

    for(i = 0; i < PAYLOAD_BUFFERS; i++)
    {
        for(j = 0; j < PAYLOAD_BUF_LEN; j++)
        {
            comm_str_payload[i][j] = '0';
        }
    }

}

//Build input buffer (testing only)
void comm_build_input_buffer(void)
{
    unsigned int i = 0;

    //Start with all zeros
    for(i = 0; i < RX_BUF_LEN; i++)
    {
        input_buffer[i] = '0';
    }
#ifdef DEBUG_COMM_USING_PRINTF
    printf("Input buffer (should be all 0s): %s\n", input_buffer);
#endif

    //Place first comm_str in buffer
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        input_buffer[i + 4] = comm_str[i];
    }

    //Place second comm_str in buffer
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        input_buffer[i + 25] = comm_str[i];
    }

#ifdef DEBUG_COMM_USING_PRINTF
    printf("Input buffer: %s\n", input_buffer);
#endif

}

//By convention rx_buf[RX_BUF_LEN-1] is the latest byte
//That function makes sure that rx_buf[] has the last x bytes
void comm_update_rx_buffer(unsigned char last_byte)
{
    static unsigned char bytes_in = 0;
    unsigned char i = 0;

    if(bytes_in < RX_BUF_LEN)
    {
        rx_buf[bytes_in] = last_byte;
        bytes_in++;
    }
    else
    {
        //Shift buffer to clear one spot
        for(i = 1; i < RX_BUF_LEN; i++)
        {
            rx_buf[i-1] = rx_buf[i];
        }
        //Add last byte to the buffer
        rx_buf[RX_BUF_LEN-1] = last_byte;
    }

    //rx_buf[] is now up to date
}

void comm_clear_rx_buffer(void)
{
    unsigned char i = 0;

    for(i = 0; i < RX_BUF_LEN; i++)
    {
        rx_buf[i] = '0';	//ToDo 0
    }
}

//Quick way to debug the comm functions with the debugger
void comm_test_functions(void)
{
    unsigned int i = 0, res = 0;

    //Clear string
    comm_clear_str_payload();

    //Build comm_str
    res = comm_gen_str(test_data, 6);

    //Feed it to the input buffer
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        comm_update_rx_buffer(comm_str[i]);
    }

    //Try to decode
    res = comm_decode_str();
}
