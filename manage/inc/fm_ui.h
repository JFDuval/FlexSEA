//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 01/2015
//****************************************************************************
// fm_ui: Deals with the 2 green LEDs, the RGB LED and the switch
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

void init_leds(void);
void init_sw1();
int read_sw1(void);
void init_switches(void);
void set_led_rgb(unsigned char r, unsigned char g, unsigned char b);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define LED0(x) HAL_GPIO_WritePin(GPIOC, 1<<1, x);
#define LED1(x) HAL_GPIO_WritePin(GPIOC, 1<<0, x);
#define LEDR(x) HAL_GPIO_WritePin(GPIOF, 1<<4, x);
#define LEDG(x) HAL_GPIO_WritePin(GPIOF, 1<<3, x);
#define LEDB(x) HAL_GPIO_WritePin(GPIOF, 1<<5, x);

#endif // UI_H_
