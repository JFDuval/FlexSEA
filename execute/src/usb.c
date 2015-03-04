//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// usb: USB CDC
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "usb.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 buffer[BUFFER_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Initialize the USB peripheral
//Returns 0 is success, 1 if timeout (happens when the cable is unplugged)
uint8 init_usb(void)
{
	uint16 cnt = 0, flag = 0;
	
	//Start USBFS Operation with 3V operation
    USBUART_1_Start(0u, USBUART_1_3V_OPERATION);
	
	//Wait for Device to enumerate */
    //while(!USBUART_1_GetConfiguration());
	for(cnt = 0; cnt < USB_ENUM_TIMEOUT; cnt++)
	{
		if(USBUART_1_GetConfiguration())
		{
			flag = 1;
			break;
		}
		CyDelay(1);
	}

	if(flag)	
	{
	    //Enumeration is done, enable OUT endpoint for receive data from Host
	    USBUART_1_CDC_Init();	
		return 1;		//Success
	}
	
	return 0;	//Timeout	
}

//Returns chars to PC. ToDo: make it non-blocking!
uint8 usb_echo_blocking(void)
{
	static 	int16 count = 0;
	uint16 i = 0;
	
	//USB Data
	if(USBUART_1_DataIsReady() != 0u)               	//Check for input data from PC
	{   
		count = USBUART_1_GetAll(buffer);           	//Read received data and re-enable OUT endpoint
		if(count != 0u)
		{
			while(USBUART_1_CDCIsReady() == 0u);    	//Wait till component is ready to send more data to the PC
			USBUART_1_PutData(buffer, count);   		//Send data back to PC

			//Store all bytes in rx buf:			
			for(i = 0; i < count; i++)
		    {
		        comm_update_rx_buffer(buffer[i]);
		    }			
			
			return 1;	//Got byte(s)
		}
    } 
	
	return 0;	//No byte
}

//Send 4 uint16 to the terminal
int16 send_usb_packet(uint16 word1, uint16 word2, uint16 word3, uint16 word4)
{
	static uint8 cnt = 0;
	char8 packet[18];

	cnt++;
	
	packet[0] = 0xAA;	//Start byte	

	packet[2] = ((word1 & 0xFF00) >> 8);
	packet[3] = ((word1 & 0x00FF));
	
	packet[4] = ((word2 & 0xFF00) >> 8);
	packet[5] = ((word2 & 0x00FF));
	
	packet[6] = ((word3 & 0xFF00) >> 8);
	packet[7] = ((word3 & 0x00FF));
	
	packet[8] = ((word4 & 0xFF00) >> 8);
	packet[9] = ((word4 & 0x00FF));
	

	packet[15] = 0xCC;	//End byte
	packet[16] = '\n';
	packet[17] = '\0';
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)packet, 18);

	return 0;
}

//1 byte through USB - ho headers, raw data
void send_usb_int8(char payload)
{
	char8 tmp[16]; 
	tmp[0] = (payload & 0xFF);
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)tmp, 1);

	return;
}

//1 byte through USB - ho headers, raw data
void send_usb_uint8(uint8 payload)
{
	uint8 tmp[16]; 
	tmp[0] = (payload & 0xFF);
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)tmp, 1);

	return;
}

//Chops a int16 in 2 bytes and send them through USB - ho headers, raw data
//Works with Matlab
void send_usb_int16(int16 payload)
{
	int tmp = 0;
	char8 packet[4];
	
	//MSB first
	tmp = (payload >> 8) & 0xFF;
	packet[1] = (uint8) tmp;
	tmp = (payload) & 0xFF;
	packet[0] = (uint8) tmp;
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)packet, 2);

	return;
}

//Chops a int32 in 4 bytes and send them through USB - ho headers, raw data
void send_usb_int32(int payload)
{
	int tmp = 0;
	char8 packet[4];
	
	//MSB first
	tmp = (payload >> 24) & 0xFF;
	packet[0] = (uint8) tmp;
	tmp = (payload >> 16) & 0xFF;
	packet[1] = (uint8) tmp;
	tmp = (payload >> 8) & 0xFF;
	packet[2] = (uint8) tmp;
	tmp = (payload) & 0xFF;
	packet[3] = (uint8) tmp;
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)packet, 4);

	return;
}
