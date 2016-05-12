//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 05/2015
//****************************************************************************
// fm_timer: SysTick & Timer functions
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_timer.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

volatile timer_ticks_t timer_delayCount;
volatile uint8_t tb_100us_flag = 0;
volatile uint8_t tb_100us_timeshare = 0;
volatile uint8_t tb_1ms_flag = 0;
volatile uint8_t tb_10ms_flag = 0;
volatile uint8_t tb_100ms_flag = 0;
volatile uint8_t tb_1000ms_flag = 0;

TIM_HandleTypeDef htim7;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base);

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

//Init SysTick timer, 1ms
void init_systick_timer(void)
{
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	// SysTick_IRQn interrupt configuration
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void timer_sleep(timer_ticks_t ticks)
{
	timer_delayCount = ticks;

	// Busy wait until the SysTick decrements the counter to zero.
	while (timer_delayCount != 0u);
}

//Timebases for all the main functions:
void timebases(void)
{
	static unsigned int cnt_1ms = 0, cnt_10ms = 0;
	static unsigned int cnt_100ms = 0, cnt_1000ms = 0;

	//100us flag:
	tb_100us_flag = 1;
	tb_100us_timeshare++;
	tb_100us_timeshare %= 10;

	//1ms flag:
	cnt_1ms++;
	if (cnt_1ms >= 10)
	{
		cnt_1ms = 0;
		tb_1ms_flag = 1;
	}

	//10ms flag:
	cnt_10ms++;
	if (cnt_10ms >= 100)
	{
		cnt_10ms = 0;
		tb_10ms_flag = 1;
	}

	//100ms flag:
	cnt_100ms++;
	if (cnt_100ms >= 1000)
	{
		cnt_100ms = 0;
		tb_100ms_flag = 1;
	}

	//1s flag:
	cnt_1000ms++;
	if (cnt_1000ms >= 10000)
	{
		cnt_1000ms = 0;
		tb_1000ms_flag = 1;
	}

}



// ----------------------------------------------------------------------------

//Timer 7: 10kHz timebase
void init_timer_7(void)
{
	TIM_MasterConfigTypeDef sMasterConfig;

	htim7.Instance = TIM7;
	htim7.Init.Prescaler = 0;
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim7.Init.Period = 4200;
	HAL_TIM_Base_Init(&htim7);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig);

	HAL_TIM_Base_Start_IT(&htim7);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
	if (htim_base->Instance == TIM7)
	{
		/* USER CODE BEGIN TIM7_MspInit 0 */

		/* USER CODE END TIM7_MspInit 0 */
		/* Peripheral clock enable */
		__TIM7_CLK_ENABLE();
		/* Peripheral interrupt init*/
		HAL_NVIC_SetPriority(TIM7_IRQn, 2, 2);
		HAL_NVIC_EnableIRQ(TIM7_IRQn);
		/* USER CODE BEGIN TIM7_MspInit 1 */

		/* USER CODE END TIM7_MspInit 1 */
	}

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

	if (htim_base->Instance == TIM7)
	{
		/* USER CODE BEGIN TIM7_MspDeInit 0 */

		/* USER CODE END TIM7_MspDeInit 0 */
		/* Peripheral clock disable */
		__TIM7_CLK_DISABLE();

		/* Peripheral interrupt DeInit*/
		HAL_NVIC_DisableIRQ(TIM7_IRQn);

	}

}
