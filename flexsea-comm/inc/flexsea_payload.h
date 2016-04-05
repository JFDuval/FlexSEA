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

//0-9:
__attribute__((weak)) void flexsea_payload_catchall(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_0(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_1(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_2(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_3(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_4(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_5(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_6(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_7(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_8(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_9(uint8_t *buf);

//10-19:
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

//20-29:
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

//30-39:
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

//40-49:
__attribute__((weak)) void flexsea_payload_40(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_41(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_42(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_43(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_44(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_45(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_46(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_47(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_48(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_49(uint8_t *buf);

//50-59: 
__attribute__((weak)) void flexsea_payload_50(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_51(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_52(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_53(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_54(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_55(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_56(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_57(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_58(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_59(uint8_t *buf);

//60-69: 
__attribute__((weak)) void flexsea_payload_60(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_61(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_62(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_63(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_64(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_65(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_66(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_67(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_68(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_69(uint8_t *buf);

//70-79: 
__attribute__((weak)) void flexsea_payload_70(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_71(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_72(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_73(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_74(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_75(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_76(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_77(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_78(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_79(uint8_t *buf);

//80-89: 
__attribute__((weak)) void flexsea_payload_80(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_81(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_82(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_83(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_84(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_85(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_86(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_87(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_88(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_89(uint8_t *buf);

//90-99: 
__attribute__((weak)) void flexsea_payload_90(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_91(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_92(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_93(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_94(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_95(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_96(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_97(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_98(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_99(uint8_t *buf);

//100-109: 
__attribute__((weak)) void flexsea_payload_100(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_101(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_102(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_103(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_104(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_105(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_106(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_107(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_108(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_109(uint8_t *buf);

//110-119: 
__attribute__((weak)) void flexsea_payload_110(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_111(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_112(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_113(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_114(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_115(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_116(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_117(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_118(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_119(uint8_t *buf);

//120-129: 
__attribute__((weak)) void flexsea_payload_120(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_121(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_122(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_123(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_124(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_125(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_126(uint8_t *buf);
__attribute__((weak)) void flexsea_payload_127(uint8_t *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
