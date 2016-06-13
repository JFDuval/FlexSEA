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
extern struct as504x_s as5047, as5048b;
extern uint16 ext_strain[6];
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************	

void init_qei(void);
//int32 encoder_read(void);
//void encoder_write(int32 enc);
void qei_write(int32 enc);
int32 qei_read(void);
int32 refresh_enc_control(void);
int32 refresh_enc_display(void);
int16 get_analog_pos(void);
void init_as5047(void);
uint16 as5047_read_single(uint16 reg);

void as5047_test_code_blocking(void);

int strain_6ch_read(uint8 internal_reg_addr, uint8 *pData, uint16 length);
void strain_amp_6ch_test_code_blocking(void);
void strain_6ch_bytes_to_words(uint8 *buf);
void get_6ch_strain(void);

int as5048b_read(uint8 internal_reg_addr, uint8 *pData, uint16 length);
void as5048b_test_code_blocking(void);
void get_as5048b_position(void);

//****************************************************************************
// Definition(s):
//****************************************************************************	

#define QUAD1_INIT				0	//Initial value, quadrature encoder

//Sensor commutation
#define HALL_PHYSICAL			0
#define HALL_VIRTUAL			1

//AS5047 Magnetic encoder (SPI):

	//Registers:
#define AS5047_REG_NOP			0
#define AS5047_REG_ERRFL		0x0001
#define AS5047_REG_PROG			0x0003
#define AS5047_REG_DIAAGC		0x3FFC
#define AS5047_REG_MAG			0x3FFD
#define AS5047_REG_ANGLEUNC		0x3FFE
#define AS5047_REG_ANGLECOM		0x3FFF

	//Commands & parity:	
#define AS5047_READ				0x4000     //OR it with your word
#define AS5047_WRITE			0xBFFF     //AND it with your word
#define PARITY_0				0x7FFF     //AND it with your word
#define PARITY_1				0x8000     //OR it with your word
#define WORDS_IN_FRAME			7

//AS5048B Magnetic Encoder (I2C):

#define I2C_ADDR_AS5048B		0b1000000	//A1 & A2 forced low, default address
#define AD5048B_REG_AGC			250
#define AD5048B_REG_DIAG		251
#define AD5048B_REG_MAG_H		252
#define AD5048B_REG_MAG_L		253
#define AD5048B_REG_ANGLE_H		254
#define AD5048B_REG_ANGLE_L		255

//6-ch Strain Amplifier:
//(this has to match what's in amp_6_ch preipherals.h!)

#define I2C_SLAVE_ADDR_6CH		0x66	//I'm assuming this is 7bits

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
// Structure(s)
//****************************************************************************	

//AS504x Magnetic encoders:
struct as504x_s
{
	uint16_t angle_raw;		//Sensor reading
	uint16_t angle_comp;	//Sensor reading, 2/ Compensation enabled
	uint16_t angle_ctrl;	//Modified version (gain, zero). Used by controllers.
	int64_t angle_cont;		//Continuous angle (multi-turn applications). Used by controllers.
};
	
#endif	//INC_EXT_IN_H
	