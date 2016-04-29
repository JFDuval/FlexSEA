//
// This file is part of the GNU ARM Eclipse Plug-ins project.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef TIMER_H_
#define TIMER_H_

#include "cmsis_device.h"

//****************************************************************************
// Shared Variable(s)
//****************************************************************************

extern volatile uint8_t systick_100us_flag;
extern volatile uint8_t systick_100us_timeshare;
extern volatile uint8_t systick_1ms_flag;
extern volatile uint8_t systick_10ms_flag;
extern volatile uint8_t systick_100ms_flag;
extern volatile uint8_t systick_1000ms_flag;

// ----------------------------------------------------------------------------

#define TIMER_FREQUENCY_HZ (10000u)

typedef uint32_t timer_ticks_t;

extern volatile timer_ticks_t timer_delayCount;

extern void init_systick_timer(void);

extern void timer_sleep (timer_ticks_t ticks);

void init_timer_7(void);
void timer_tick (void);

// ----------------------------------------------------------------------------

#endif // TIMER_H_
