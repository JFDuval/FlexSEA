//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// usb: USB CDC
//****************************************************************************
	
#ifndef INC_USB_H
#define INC_USB_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

uint8 init_usb(void);
uint8 usb_echo_blocking(void);
int16 send_usb_packet(uint16 word1, uint16 word2, uint16 word3, uint16 word4);
void send_usb_int8(char payload);
void send_usb_uint8(uint8 payload);
void send_usb_int16(int16 payload);
void send_usb_int32(int payload);
	
//****************************************************************************
// Definition(s):
//****************************************************************************

#define USB_ENUM_TIMEOUT			2500	//ms
#define BUFFER_LEN					64
	
#endif	//INC_USB_H
	