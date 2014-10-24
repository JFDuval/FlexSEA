//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocole
//****************************************************************************

#ifndef INC_FLEXSEA_COMM_H
#define INC_FLEXSEA_COMM_H

//****************************************************************************
// Include(s)
//****************************************************************************

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Prototype(s):
//****************************************************************************

unsigned char comm_gen_str(unsigned char payload[], unsigned char bytes);
unsigned char comm_decode_str(void);
void comm_clear_rx_buffer(void);
void comm_update_rx_buffer(unsigned char last_byte);
void comm_build_input_buffer(void);
void comm_clear_str_payload(void);
void comm_test_functions(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//I'm using chars because it's visual and also because they have high decimal
//values. Do not change!
#define HEADER  'a'
#define FOOTER  'z'
#define ESCAPE  'e'

#endif
