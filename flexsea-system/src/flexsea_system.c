//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// flexsea_system: configuration and functions for this particular system
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/flexsea_system.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//Slave data:
unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];
unsigned char manage_1_data[SLAVE_READ_BUFFER_LEN];

#if defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

struct execute_s exec1, exec2, exec3, exec4;
struct ricnu_s ricnu_1;
struct manage_s manag1;
struct strain_s strain[6];
struct in_control_s in_control_1;

#endif	//BOARD_TYPE_FLEXSEA_MANAGE

//****************************************************************************
// Function(s)
//****************************************************************************

//All the functions declared as "__attribute__((weak))" in flexsea_payload.h
//have to be redefined in /flexsea-system/. For functions in use, comment the 
//generic implementation found below, and implement in your own file.
//Do the same in flexsea_system.h

//0-9:
void flexsea_payload_catchall(uint8_t *buf){};
void flexsea_payload_0(uint8_t *buf){};			//CMD_NULL
//void flexsea_payload_1(uint8_t *buf){};		//CMD_TEST
void flexsea_payload_2(uint8_t *buf){};
void flexsea_payload_3(uint8_t *buf){};
void flexsea_payload_4(uint8_t *buf){};
void flexsea_payload_5(uint8_t *buf){};
void flexsea_payload_6(uint8_t *buf){};
void flexsea_payload_7(uint8_t *buf){};
void flexsea_payload_8(uint8_t *buf){};
void flexsea_payload_9(uint8_t *buf){};

//10-19:
void flexsea_payload_10(uint8_t *buf){};		//CMD_PING
void flexsea_payload_11(uint8_t *buf){};		//CMD_STATUS
void flexsea_payload_12(uint8_t *buf){};		//CMD_RESET
void flexsea_payload_13(uint8_t *buf){};		//CMD_ACK
void flexsea_payload_14(uint8_t *buf){};
void flexsea_payload_15(uint8_t *buf){};
void flexsea_payload_16(uint8_t *buf){};
void flexsea_payload_17(uint8_t *buf){};
void flexsea_payload_18(uint8_t *buf){};
void flexsea_payload_19(uint8_t *buf){};

//20-29:
//void flexsea_payload_20(uint8_t *buf){};		//CMD_MEM
//void flexsea_payload_21(uint8_t *buf){};		//CMD_ACQUI
//void flexsea_payload_22(uint8_t *buf){};		//CMD_READ_ALL
void flexsea_payload_23(uint8_t *buf){};
void flexsea_payload_24(uint8_t *buf){};
void flexsea_payload_25(uint8_t *buf){};
void flexsea_payload_26(uint8_t *buf){};
void flexsea_payload_27(uint8_t *buf){};
void flexsea_payload_28(uint8_t *buf){};
void flexsea_payload_29(uint8_t *buf){};

//30-39: 
void flexsea_payload_30(uint8_t *buf){};
void flexsea_payload_31(uint8_t *buf){};
void flexsea_payload_32(uint8_t *buf){};
void flexsea_payload_33(uint8_t *buf){};
void flexsea_payload_34(uint8_t *buf){};
void flexsea_payload_35(uint8_t *buf){};
void flexsea_payload_36(uint8_t *buf){};
void flexsea_payload_37(uint8_t *buf){};
void flexsea_payload_38(uint8_t *buf){};
void flexsea_payload_39(uint8_t *buf){};

//40-49:
//void flexsea_payload_40(uint8_t *buf){};		//CMD_TEMP
//void flexsea_payload_41(uint8_t *buf){};		//CMD_SWITCH
//void flexsea_payload_42(uint8_t *buf){};		//CMD_IMU
//void flexsea_payload_43(uint8_t *buf){};		//CMD_ENCODER
//void flexsea_payload_44(uint8_t *buf){};		//CMD_STRAIN
//void flexsea_payload_45(uint8_t *buf){};		//CMD_STRAIN_CONFIG
//void flexsea_payload_46(uint8_t *buf){};		//CMD_VOLT
//void flexsea_payload_47(uint8_t *buf){};		//CMD_BATT
void flexsea_payload_48(uint8_t *buf){};
void flexsea_payload_49(uint8_t *buf){};

//50-59: 
void flexsea_payload_50(uint8_t *buf){};
void flexsea_payload_51(uint8_t *buf){};
void flexsea_payload_52(uint8_t *buf){};
void flexsea_payload_53(uint8_t *buf){};
void flexsea_payload_54(uint8_t *buf){};
void flexsea_payload_55(uint8_t *buf){};
void flexsea_payload_56(uint8_t *buf){};
void flexsea_payload_57(uint8_t *buf){};
void flexsea_payload_58(uint8_t *buf){};
void flexsea_payload_59(uint8_t *buf){};

//60-69: 
//void flexsea_payload_60(uint8_t *buf){};		//CMD_POWER_OUT
//void flexsea_payload_61(uint8_t *buf){};		//CMD_PWRO
void flexsea_payload_62(uint8_t *buf){};		//CMD_ADV_ANA_CONFIG
void flexsea_payload_63(uint8_t *buf){};		//CMD_ANALOG
void flexsea_payload_64(uint8_t *buf){};		//CMD_DIGITAL
void flexsea_payload_65(uint8_t *buf){};		//CMD_DIGITAL_CONFIG
void flexsea_payload_66(uint8_t *buf){};		//CMD_EXP_PERIPH_CONFIG
void flexsea_payload_67(uint8_t *buf){};
void flexsea_payload_68(uint8_t *buf){};
void flexsea_payload_69(uint8_t *buf){};

//70-79: 
void flexsea_payload_70(uint8_t *buf){};
void flexsea_payload_71(uint8_t *buf){};
void flexsea_payload_72(uint8_t *buf){};
void flexsea_payload_73(uint8_t *buf){};
void flexsea_payload_74(uint8_t *buf){};
void flexsea_payload_75(uint8_t *buf){};
void flexsea_payload_76(uint8_t *buf){};
void flexsea_payload_77(uint8_t *buf){};
void flexsea_payload_78(uint8_t *buf){};
void flexsea_payload_79(uint8_t *buf){};

//80-89: 
//void flexsea_payload_80(uint8_t *buf){};		//CMD_CTRL_MODE
//void flexsea_payload_81(uint8_t *buf){};		//CMD_CTRL_X_G
//void flexsea_payload_82(uint8_t *buf){};		//CMD_CTRL_I_G
//void flexsea_payload_83(uint8_t *buf){};		//CMD_CTRL_P_G
//void flexsea_payload_84(uint8_t *buf){};		//CMD_CTRL_Z_G
//void flexsea_payload_85(uint8_t *buf){};		//CMD_CTRL_O
//void flexsea_payload_86(uint8_t *buf){};		//CMD_CTRL_I
//void flexsea_payload_87(uint8_t *buf){};		//CMD_CTRL_P
void flexsea_payload_88(uint8_t *buf){};
void flexsea_payload_89(uint8_t *buf){};

//90-99: 
void flexsea_payload_90(uint8_t *buf){};
void flexsea_payload_91(uint8_t *buf){};
void flexsea_payload_92(uint8_t *buf){};
void flexsea_payload_93(uint8_t *buf){};
void flexsea_payload_94(uint8_t *buf){};
void flexsea_payload_95(uint8_t *buf){};
void flexsea_payload_96(uint8_t *buf){};
void flexsea_payload_97(uint8_t *buf){};
void flexsea_payload_98(uint8_t *buf){};
void flexsea_payload_99(uint8_t *buf){};

//100-109: 
//void flexsea_payload_100(uint8_t *buf){};		//ShuoBot Exo
//void flexsea_payload_101(uint8_t *buf){};		//CSEA Knee
//void flexsea_payload_102(uint8_t *buf){};		//Current controller tuning
void flexsea_payload_103(uint8_t *buf){};
void flexsea_payload_104(uint8_t *buf){};
//void flexsea_payload_105(uint8_t *buf){};		//CMD_READ_ALL_RICNU
void flexsea_payload_106(uint8_t *buf){};
void flexsea_payload_107(uint8_t *buf){};
void flexsea_payload_108(uint8_t *buf){};
void flexsea_payload_109(uint8_t *buf){};

//110-119: 
void flexsea_payload_110(uint8_t *buf){};
void flexsea_payload_111(uint8_t *buf){};
void flexsea_payload_112(uint8_t *buf){};
void flexsea_payload_113(uint8_t *buf){};
void flexsea_payload_114(uint8_t *buf){};
void flexsea_payload_115(uint8_t *buf){};
void flexsea_payload_116(uint8_t *buf){};
void flexsea_payload_117(uint8_t *buf){};
void flexsea_payload_118(uint8_t *buf){};
void flexsea_payload_119(uint8_t *buf){};

//120-129: 
//void flexsea_payload_120(uint8_t *buf){};	//Dual ShuoBot
void flexsea_payload_121(uint8_t *buf){};
void flexsea_payload_122(uint8_t *buf){};
void flexsea_payload_123(uint8_t *buf){};
void flexsea_payload_124(uint8_t *buf){};
void flexsea_payload_125(uint8_t *buf){};
void flexsea_payload_126(uint8_t *buf){};
void flexsea_payload_127(uint8_t *buf){};
