#ifndef TRAPEZ_H_
#define TRAPEZ_H_

//typedef unsigned int uint32;
//typedef int int32;

//Prototypes:
int trapez_compute_params(int pos_i, int pos_f, int spd_max, int a);
int trapez_gen_motion_1(int pos_i, int pos_f, int spd_max, int a);
//void trapez_plot_all(void);
//void trapez_get_all(int* pos, int* spd, int* acc);
int trapez_get_pos(int max_steps);
int absolute(int val);

//Common definitions:
#define TRAPEZ_DT           0.01     //Trapezoidal timebase. Has to match hardware!
#define TRAPEZ_ONE_OVER_DT  100
#define SPD_FACTOR          1000     //Scaling for integer
#define ACC_FACTOR          10000

#endif // TRAPEZ_H_
