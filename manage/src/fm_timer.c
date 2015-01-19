//
// This file is part of the GNU ARM Eclipse Plug-ins project.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "fm_timer.h"
#include "cortexm/ExceptionHandlers.h"
#include "main.h"

// ----------------------------------------------------------------------------

// Forward declarations.

void timer_tick (void);

// ----------------------------------------------------------------------------

volatile timer_ticks_t timer_delayCount;
volatile unsigned char systick_1ms_flag = 0;
volatile unsigned char systick_10ms_flag = 0;
volatile unsigned char systick_100ms_flag = 0;
volatile unsigned char systick_1000ms_flag = 0;

// ----------------------------------------------------------------------------

void init_systick_timer(void)
{
  // Use SysTick as reference for the delay loops.
  SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);
}

void timer_sleep (timer_ticks_t ticks)
{
  timer_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (timer_delayCount != 0u)
    ;
}

//System Timer: function called every 1ms
void timer_tick (void)
{
	static unsigned char cnt_10ms = 0, cnt_100ms = 0, cnt_1000ms = 0;
	
	//1ms flag:
	systick_1ms_flag = 1;

	//10ms flag:
	cnt_10ms++;
	if(cnt_10ms >= 10)
	{
		cnt_10ms = 0;
		systick_10ms_flag = 1;
	}

	//100ms flag:
	cnt_100ms++;
	if(cnt_100ms >= 100)
	{
		cnt_100ms = 0;
		systick_100ms_flag = 1;
	}
	
	//1s flag:
	cnt_1000ms++;
	if(cnt_1000ms >= 1000)
	{
		cnt_1000ms = 0;
		systick_1000ms_flag = 1;
	}	

  // Decrement to zero the counter used by the delay routine.
  if (timer_delayCount != 0u)
    {
      --timer_delayCount;
    }
}

// ----- SysTick_Handler() ----------------------------------------------------

void SysTick_Handler (void)
{
	timer_tick ();
}

// ----------------------------------------------------------------------------
