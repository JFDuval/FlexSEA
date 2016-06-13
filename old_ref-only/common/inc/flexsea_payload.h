//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_payload: deals with the "intelligent" data packaged in a comm_str
//****************************************************************************

#ifndef INC_FX_PAYLOAD_H
#define INC_FX_PAYLOAD_H

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>
#include "flexsea.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t payload_str[PAYLOAD_BUF_LEN];

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

unsigned int payload_parse_str(unsigned char *cp_str);
uint8_t sent_from_a_slave(uint8_t *buf);
void prepare_empty_payload(uint8_t from, uint8_t to, uint8_t *buf, uint32_t len);

//****************************************************************************
// Definition(s):
//****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
