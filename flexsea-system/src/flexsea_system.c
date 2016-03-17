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


//****************************************************************************
// Function(s)
//****************************************************************************

//All the functions declared as "__attribute__((weak))" in flexsea_payload.h
//have to be redefined in /flexsea-system/. For functions in use, comment the 
//generic implementation found below, and implement in your own file.
//Do the same in flexsea_system.h

void flexsea_payload_catchall(uint8_t *buf){};
void flexsea_payload_0(uint8_t *buf){};

//void flexsea_payload_10(uint8_t *buf){};	//Overloaded by rx_cmd_rgbw
void flexsea_payload_11(uint8_t *buf){};
void flexsea_payload_12(uint8_t *buf){};
void flexsea_payload_13(uint8_t *buf){};
void flexsea_payload_14(uint8_t *buf){};
void flexsea_payload_15(uint8_t *buf){};
void flexsea_payload_16(uint8_t *buf){};
void flexsea_payload_17(uint8_t *buf){};
void flexsea_payload_18(uint8_t *buf){};
void flexsea_payload_19(uint8_t *buf){};
//void flexsea_payload_20(uint8_t *buf){};	//Overloaded by rx_cmd_digital_in
void flexsea_payload_21(uint8_t *buf){};
//void flexsea_payload_22(uint8_t *buf){};	//Overloaded by rx_cmd_analog_in
void flexsea_payload_23(uint8_t *buf){};
void flexsea_payload_24(uint8_t *buf){};
void flexsea_payload_25(uint8_t *buf){};
void flexsea_payload_26(uint8_t *buf){};
void flexsea_payload_27(uint8_t *buf){};
void flexsea_payload_28(uint8_t *buf){};
void flexsea_payload_29(uint8_t *buf){};
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
