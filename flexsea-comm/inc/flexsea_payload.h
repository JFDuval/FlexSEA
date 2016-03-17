//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
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

__attribute__((weak)) void flexsea_payload_catchall(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_0(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_1(uint8_t *buf);

__attribute__((weak)) void flexsea_payload_10(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_11(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_12(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_13(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_14(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_15(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_16(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_17(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_18(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_19(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_20(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_21(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_22(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_23(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_24(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_25(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_26(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_27(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_28(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_29(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_30(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_31(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_32(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_33(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_34(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_35(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_36(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_37(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_38(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_39(uint8_t *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
