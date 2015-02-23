//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_payload: deals with the "intelligent" data packaged in a comm_str
//****************************************************************************

#ifndef INC_FLEXSEA_PAYLOAD_H
#define INC_FLEXSEA_PAYLOAD_H

//****************************************************************************
// Include(s)
//****************************************************************************


//****************************************************************************
// Prototype(s):
//****************************************************************************

unsigned int payload_clear_str(void);
unsigned int payload_build_basic_str(unsigned char to);
unsigned int payload_check_slave_id(unsigned char *data);
unsigned int payload_parse_str(unsigned char *cp_str);
void fill_uint8_buf(uint8_t *buf, uint32_t len, uint8_t filler);
uint8_t sent_from_a_slave(uint8_t *buf);
void prepare_empty_payload(uint8_t from, uint8_t to, uint8_t *buf, uint32_t len);
void route_to_slave(uint8_t *buf, uint32_t len);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif
