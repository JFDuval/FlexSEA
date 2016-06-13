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

#ifndef INC_TIMER_H
#define INC_TIMER_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "cmsis_device.h"

//****************************************************************************
// Shared Variable(s)
//****************************************************************************

//ToDo update names, not systick anymore
extern volatile uint8_t tb_100us_flag;
extern volatile uint8_t tb_100us_timeshare;
extern volatile uint8_t tb_1ms_flag;
extern volatile uint8_t tb_10ms_flag;
extern volatile uint8_t tb_100ms_flag;
extern volatile uint8_t tb_1000ms_flag;

typedef uint32_t timer_ticks_t;

extern volatile timer_ticks_t timer_delayCount;

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

extern void init_systick_timer(void);
extern void timer_sleep (timer_ticks_t ticks);

void init_timer_7(void);
void timebases(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define TIMER_FREQUENCY_HZ (10000u)

#endif // INC_TIMER_H

