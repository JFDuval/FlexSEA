//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// peripherals: code for the general peripheral modules
//****************************************************************************
	
#ifndef INC_PERIPH_H
#define INC_PERIPH_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_peripherals(void);
void init_tb_timers(void);
void init_i2c_0(void);
void init_i2c_1(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//EZI2C Buffer:
#define EZI2C_WBUF_SIZE			8
#define EZI2C_RBUF_SIZE			12
#define EZI2C_BUF_SIZE			(EZI2C_WBUF_SIZE + EZI2C_RBUF_SIZE)

//EZI2C Shared memory locations:
#define MEM_W_CONTROL1			0
#define MEM_W_CONTROL2			1
#define MEM_W_OFFS_CH1			2
#define MEM_W_OFFS_CH2			3
#define MEM_W_OFFS_CH3			4
#define MEM_W_OFFS_CH4			5
#define MEM_W_OFFS_CH5			6
#define MEM_W_OFFS_CH6			7
#define MEM_R_CH1_H				8
#define MEM_R_CH1_L				9
#define MEM_R_CH2_H				10
#define MEM_R_CH2_L				11
#define MEM_R_CH3_H				12
#define MEM_R_CH3_L				13
#define MEM_R_CH4_H				14
#define MEM_R_CH4_L				15
#define MEM_R_CH5_H				16
#define MEM_R_CH5_L				17
#define MEM_R_CH6_H				18
#define MEM_R_CH6_L				19

//****************************************************************************
// Shared Variable(s):
//****************************************************************************

extern uint8 ezI2Cbuf[EZI2C_BUF_SIZE];
	
#endif	//INC_PERIPH_H
	