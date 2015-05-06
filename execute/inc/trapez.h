//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 05/2015
//****************************************************************************
// trapez: trapezoidal trajectory generation
//****************************************************************************

#ifndef TRAPEZ_H_
#define TRAPEZ_H_

//****************************************************************************
// Include(s):
//****************************************************************************

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

long long trapez_gen_motion_1(long long pos_i, long long pos_f, long long spd_max, long long a);
long long trapez_get_pos(long long max_steps);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define TRAPEZ_DT           	0.001		//Trapezoidal timebase. Has to match hardware!
#define TRAPEZ_ONE_OVER_DT  	1000
#define SPD_FACTOR          	10000		//Scaling for integer
#define ACC_FACTOR          	10000

#endif // TRAPEZ_H_
