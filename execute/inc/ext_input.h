//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// ext_input: External Input Devices/Sensors
//****************************************************************************
	
#ifndef INC_EXT_IN_H
#define INC_EXT_IN_H

//****************************************************************************
// Include(s)
//****************************************************************************		
	
#include "main.h"
	
//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern struct enc_s encoder;	
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************	

void init_qei(void);
int32 encoder_read(void);
void encoder_write(int32 enc);
void init_as5047(void);
uint16 as5047_read_single(uint16 reg);

void as5047_test_code_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************	

#define QUAD1_INIT				0	//Initial value, quadrature encoder

//AS5047 Magnetic encoder:

	//Registers:
#define AS5047_REG_NOP           0
#define AS5047_REG_ERRFL         0x0001
#define AS5047_REG_PROG          0x0003
#define AS5047_REG_DIAAGC        0x3FFC
#define AS5047_REG_MAG           0x3FFD
#define AS5047_REG_ANGLEUNC      0x3FFE
#define AS5047_REG_ANGLECOM      0x3FFF

	//Commands & parity:	
#define AS5047_READ              0x4000     //OR it with your word
#define AS5047_WRITE             0xBFFF     //AND it with your word
#define PARITY_0                 0x7FFF     //AND it with your word
#define PARITY_1                 0x8000     //OR it with your word
#define WORDS_IN_FRAME           7

//****************************************************************************
// Structure(s)
//****************************************************************************	

	
#endif	//INC_EXT_IN_H
	