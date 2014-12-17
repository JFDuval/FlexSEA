//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// fm_ui: Deals with the 4 green LEDs, the RGB LED and the 2 switches
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "fm_ui.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

#define LED0_PORT_NUMBER               (4)
#define LED0_PIN_NUMBER                (8)
#define LED0_ACTIVE_LOW                (0)
#define LED0_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LED0_PIN_MASK(_N)              (1 << (_N))
#define LED0_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

//LED pins
void init_led0()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LED0_RCC_MASKx(LED0_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LED0_PIN_MASK(LED0_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LED0_GPIOx(LED0_PORT_NUMBER), &GPIO_InitStructure);
}

#define LED1_PORT_NUMBER               (4)
#define LED1_PIN_NUMBER                (7)
#define LED1_ACTIVE_LOW                (0)
#define LED1_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LED1_PIN_MASK(_N)              (1 << (_N))
#define LED1_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

//LED pins
void init_led1()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LED1_RCC_MASKx(LED1_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LED1_PIN_MASK(LED1_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LED1_GPIOx(LED1_PORT_NUMBER), &GPIO_InitStructure);
}

#define LED2_PORT_NUMBER               (6)
#define LED2_PIN_NUMBER                (1)
#define LED2_ACTIVE_LOW                (0)
#define LED2_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LED2_PIN_MASK(_N)              (1 << (_N))
#define LED2_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

//LED pins
void init_led2()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LED2_RCC_MASKx(LED2_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LED2_PIN_MASK(LED2_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LED2_GPIOx(LED2_PORT_NUMBER), &GPIO_InitStructure);
}

#define LED3_PORT_NUMBER               (6)
#define LED3_PIN_NUMBER                (0)
#define LED3_ACTIVE_LOW                (0)
#define LED3_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LED3_PIN_MASK(_N)              (1 << (_N))
#define LED3_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

//LED pins
void init_led3()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LED3_RCC_MASKx(LED3_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LED3_PIN_MASK(LED3_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LED3_GPIOx(LED3_PORT_NUMBER), &GPIO_InitStructure);
}

#define LEDR_PORT_NUMBER               (4)
#define LEDR_PIN_NUMBER                (15)
#define LEDR_ACTIVE_LOW                (0)
#define LEDR_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LEDR_PIN_MASK(_N)              (1 << (_N))
#define LEDR_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))


//LED pins
void init_led_r()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LEDR_RCC_MASKx(LEDR_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LEDR_PIN_MASK(LEDR_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LEDR_GPIOx(LEDR_PORT_NUMBER), &GPIO_InitStructure);
}

#define LEDB_PORT_NUMBER               (4)
#define LEDB_PIN_NUMBER                (13)
#define LEDB_ACTIVE_LOW                (0)
#define LEDB_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LEDB_PIN_MASK(_N)              (1 << (_N))
#define LEDB_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))


//LED pins
void init_led_b()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LEDB_RCC_MASKx(LEDB_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LEDB_PIN_MASK(LEDB_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LEDR_GPIOx(LEDB_PORT_NUMBER), &GPIO_InitStructure);
}

#define LEDG_PORT_NUMBER               (4)
#define LEDG_PIN_NUMBER                (14)
#define LEDG_ACTIVE_LOW                (0)
#define LEDG_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define LEDG_PIN_MASK(_N)              (1 << (_N))
#define LEDG_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))


//LED pins
void init_led_g()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= LEDG_RCC_MASKx(LEDG_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = LEDG_PIN_MASK(LEDG_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LEDR_GPIOx(LEDG_PORT_NUMBER), &GPIO_InitStructure);
}

#define SW1_PORT_NUMBER               (5)
#define SW1_PIN_NUMBER                (12)
#define SW1_ACTIVE_LOW                (0)
#define SW1_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define SW1_PIN_MASK(_N)              (1 << (_N))
#define SW1_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

//SW1 pin
void init_sw1()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= SW1_RCC_MASKx(SW1_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = SW1_PIN_MASK(SW1_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW1_GPIOx(SW1_PORT_NUMBER), &GPIO_InitStructure);
}

int read_sw1(void)
{
	return HAL_GPIO_ReadPin(GPIOF, 1<<12);
}

#define SW2_PORT_NUMBER               (5)
#define SW2_PIN_NUMBER                (11)
#define SW2_ACTIVE_LOW                (0)
#define SW2_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define SW2_PIN_MASK(_N)              (1 << (_N))
#define SW2_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

//SW2 pin
void init_sw2()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= SW2_RCC_MASKx(SW2_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = SW2_PIN_MASK(SW2_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW2_GPIOx(SW2_PORT_NUMBER), &GPIO_InitStructure);
}

int read_sw2(void)
{
	return HAL_GPIO_ReadPin(GPIOF, 1<<11);
}

void init_led_outputs(void)
{
	  init_led0();
	  init_led1();
	  init_led2();
	  init_led3();
	  init_led_r();
	  init_led_g();
	  init_led_b();
}

void init_switch_inputs(void)
{
	init_sw1();
	init_sw2();
}

void set_led_bank(unsigned char leds_state)
{
	LED0(leds_state & 0x01);
	LED1((leds_state >> 1) & 0x01);
	LED2((leds_state >> 2) & 0x01);
	LED3((leds_state >> 3) & 0x01);
}

void set_led_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	//No fading, we use 1 or 0 for now:

	LEDR(r & 0x01);
	LEDG(g & 0x01);
	LEDB(b & 0x01);
}
