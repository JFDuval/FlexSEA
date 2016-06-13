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
void rgb_led_ui(uint8_t err_l0, uint8_t err_l1, uint8_t err_l2,
		uint8_t new_comm);
void rgb_led_test_code_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define LED0(x) HAL_GPIO_WritePin(GPIOC, 1<<1, x);
#define LED1(x) HAL_GPIO_WritePin(GPIOC, 1<<0, x);
#define LEDR(x) HAL_GPIO_WritePin(GPIOF, 1<<4, x);
#define LEDG(x) HAL_GPIO_WritePin(GPIOF, 1<<3, x);
#define LEDB(x) HAL_GPIO_WritePin(GPIOF, 1<<5, x);

/*
 RGB LED:
 ========
 Green: everything's good
 Yellow: software error, close to a voltage or temperature limit
 Blue: didn't receive commands in the last 'comm_timeout' ms
 Red: error
 Flashing red: major error
 */

//Timings in ms:
#define UI_COMM_TIMEOUT			2000
#define UI_L0_TIMEOUT			1000
#define UI_L1_TIMEOUT			1000
#define UI_RED_FLASH_ON			100
#define UI_RED_FLASH_PERIOD		200

#endif // UI_H_
