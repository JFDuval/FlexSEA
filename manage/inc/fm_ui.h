//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// fm_ui: Deals with the 4 green LEDs, the RGB LED and the 2 switches
//****************************************************************************

#ifndef UI_H_
#define UI_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_led0();
void init_led1();
void init_led2();
void init_led3();
void init_ledr();
void init_ledg();
void init_ledb();
void init_sw1();
int read_sw1(void);
void init_sw2();
int read_sw2(void);
void init_led_outputs(void);
void init_switch_inputs(void);
void set_led_bank(unsigned char leds_state);
void set_led_rgb(unsigned char r, unsigned char g, unsigned char b);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define LED0(x) HAL_GPIO_WritePin(GPIOE, 1<<8, x);
#define LED1(x) HAL_GPIO_WritePin(GPIOE, 1<<7, x);
#define LED2(x) HAL_GPIO_WritePin(GPIOG, 1<<1, x);
#define LED3(x) HAL_GPIO_WritePin(GPIOG, 1<<0, x);
#define LEDR(x) HAL_GPIO_WritePin(GPIOE, 1<<15, x);
#define LEDG(x) HAL_GPIO_WritePin(GPIOE, 1<<14, x);
#define LEDB(x) HAL_GPIO_WritePin(GPIOE, 1<<13, x);

#endif // UI_H_
