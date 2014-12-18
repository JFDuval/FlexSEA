//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_ui: Deals with the 2 green LEDs, the RGB LED and the switch
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

#define LED0_PORT_NUMBER               (2)
#define LED0_PIN_NUMBER                (1)
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

#define LED1_PORT_NUMBER               (2)
#define LED1_PIN_NUMBER                (0)
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

#define LEDR_PORT_NUMBER               (5)
#define LEDR_PIN_NUMBER                (4)
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

#define LEDB_PORT_NUMBER               (5)
#define LEDB_PIN_NUMBER                (3)
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

#define LEDG_PORT_NUMBER               (5)
#define LEDG_PIN_NUMBER                (5)
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

#define SW1_PORT_NUMBER               (4)
#define SW1_PIN_NUMBER                (3)
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
	return HAL_GPIO_ReadPin(GPIOE, 1<<3);
}

void init_led_outputs(void)
{
	  init_led0();
	  init_led1();
	  init_led_r();
	  init_led_g();
	  init_led_b();
}

void init_switch_inputs(void)
{
	init_sw1();
}

void set_led_bank(unsigned char leds_state)
{
	LED0(leds_state & 0x01);
	LED1((leds_state >> 1) & 0x01);
}

void set_led_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	//No fading, we use 1 or 0 for now:

	LEDR(r & 0x01);
	LEDG(g & 0x01);
	LEDB(b & 0x01);
}
