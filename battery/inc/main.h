//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// main: FlexSEA-Execute Safety-CoP
//****************************************************************************

#ifndef MAIN_H_
#define MAIN_H_
	
//****************************************************************************
// Include(s)
//****************************************************************************

#include <project.h>
#include <stdlib.h>
#include "isr_callbacks.h"
#include "misc.h"
#include "sensors.h"
#include "comm.h"
#include "fsm.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

//****************************************************************************
// Definition(s):
//****************************************************************************

//Board Status
#define BOARD_STATUS_NA       	0
#define BOARD_STATUS_ALL_GOOD	1
#define BOARD_STATUS_ERROR      2
	
//Reassembles a uint32 from 4 bytes. b0 is the MSB.
#define BYTES_TO_UINT32(b0,b1,b2,b3)	(((uint32_t)b0 << 24) + \
										((uint32_t)b1 << 16) + \
										((uint32_t)b2 << 8) + \
										((uint32_t)b3))

//Reassembles a uint16 from 2 bytes. b0 is the MSB.
#define BYTES_TO_UINT16(b0,b1)			(((uint16_t)b0 << 8) + \
										((uint16_t)b1))
	
#endif // MAIN_H_
