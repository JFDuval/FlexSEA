//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// main: FlexSEA-Manage
//****************************************************************************

#ifndef MAIN_H_
#define MAIN_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_spi.h"
#include "fm_master_slave_comm.h"
#include "fm_timer.h"
#include "fm_misc.h"
#include "fm_ui.h"
#include "fm_uarts.h"
#include "fm_adc.h"
#include "fm_adv_analog.h"
#include "fm_dio.h"
#include "fm_spi.h"
#include "fm_i2c.h"
#include "fm_imu.h"
#include "fm_pwr_out.h"
//#include "fm_stm32f4xx_hal_spi.h"
#include "flexsea_board.h"
#include "../../flexsea-system/inc/flexsea_system.h"
#include "../../flexsea-comm/inc/flexsea.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

int main(void);

//****************************************************************************
// Definition(s):
//****************************************************************************


#endif // MAIN_H_
