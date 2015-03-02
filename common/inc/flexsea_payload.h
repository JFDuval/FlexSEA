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

uint8_t get_rid(uint8_t *pldata);
unsigned int payload_parse_str(unsigned char *cp_str);
uint8_t sent_from_a_slave(uint8_t *buf);
void prepare_empty_payload(uint8_t from, uint8_t to, uint8_t *buf, uint32_t len);
void route_to_slave(uint8_t port, uint8_t *buf, uint32_t len);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif
