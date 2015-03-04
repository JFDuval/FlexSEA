//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// trapez: trapezoidal trajectory generation
//****************************************************************************

//Work based on trapez_gen_x.m, translated in C
//JFDuval 06/17/2014

//****************************************************************************
// Include(s)
//****************************************************************************

//Comment the next line to use in C with PSoC
//#define CPP_DEBUGGING

#ifdef CPP_DEBUGGING

#include <iostream>
#include <fstream>
#include <math.h>
#include "trapez.h"

using namespace std;

#else

#include "main.h"
#include "trapez.h"

#endif

//****************************************************************************
// Variable(s)
//****************************************************************************

//Common variables - careful, do not change "manually"!
int d_pos = 0, d_spd = 0, a_t = 0, a_t_discrete = 0, spd_inc = 0, acc_pos = 0, acc = 0;
int init_pos = 0, cte_spd_pos = 0, cte_spd_pos_discrete = 0;
int skip_sspeed = 0;
int pos_step = 0;
int trapez_transitions[3] = {0,0,0};
int sign = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

//Computes all the parameters for a new trapezoidal motion trajectory
//Called by trapez_gen_motion_1()
int trapez_compute_params(int pos_i, int pos_f, int spd_max, int a)
{
    int tmp = 0, i = 0;

    //Sign
    if(pos_f < pos_i)
        sign = -1;
    else
        sign = 1;

    acc = a;
    init_pos = pos_i;
    d_pos = pos_f - pos_i;                                  //Difference in position
    d_spd = spd_max ;                                       //Difference in speed
    a_t = (ACC_FACTOR*d_spd) / a;                                        //How long do we accelerate?
    a_t_discrete = a_t * TRAPEZ_ONE_OVER_DT / ACC_FACTOR;                //   (in ticks)
    //a_t_discrete = a_t; //Simplification of *100/100
    spd_inc = (sign*SPD_FACTOR*d_spd) / a_t_discrete;       //Every tick, increase spd by
    #ifdef CPP_DEBUGGING
    cout << "d_spd: " << d_spd << ", a_t_discrete: " << a_t_discrete << ", spd_inc: " << spd_inc << ", d_pos: " << d_pos << endl;
    #endif

    acc_pos = 0;
    for(i = 0; i < a_t_discrete; i++)
    {
        tmp = i*spd_inc;
        acc_pos = acc_pos + tmp;
    }
    acc_pos = acc_pos / (SPD_FACTOR * TRAPEZ_ONE_OVER_DT); //Combine terms
    #ifdef CPP_DEBUGGING
    cout << "acc_pos: " << acc_pos << ", (2x = " << (2*acc_pos) << ") " << (float)(2*acc_pos*100/d_pos) << "% of d_pos. " << endl;
    #endif

    return 0;
}

//Based on trapez_motion_2.m
//Assumes 0 initial speed
int trapez_gen_motion_1(int pos_i, int pos_f, int spd_max, int a)
{
    int abs_d_pos = 0, abs_acc_pos = 0, dual_abs_acc_pos = 0;

    //spd_max & a have to be positive
    spd_max = absolute(spd_max);
    a = absolute(a);

    //Compute parameters (in global variables)
    trapez_compute_params(pos_i, pos_f, spd_max, a);

    //Absolute values
    abs_d_pos = absolute(d_pos);
    abs_acc_pos = absolute(acc_pos);
    dual_abs_acc_pos = 2*abs_acc_pos;

    #ifdef CPP_DEBUGGING
    cout << "d_pos: " << d_pos << ", abs_d_pos: " << abs_d_pos << endl;
    cout << "1) acc_pos: " << acc_pos << ", abs_acc_pos: " << abs_acc_pos << endl;
    #endif

    //It's possible to overshoot position if the acceleration is too low.
    //In that case we should sacrifice the top speed
    if(dual_abs_acc_pos > abs_d_pos)
    {
        #ifdef CPP_DEBUGGING
        cout << "Position overshoot" << endl;
        #endif

        //New top speed:
        spd_max = sqrt(a*abs_d_pos);
        #ifdef CPP_DEBUGGING
        cout << "New spd_max: " << spd_max << endl;
        #endif

        //Redo the initial math:
        //Compute parameters (in global variables)
        trapez_compute_params(pos_i, pos_f, spd_max, a);

        //Absolute values (they probably changed)
        abs_d_pos = absolute(d_pos);
        abs_acc_pos = absolute(acc_pos);
        dual_abs_acc_pos = 2*abs_acc_pos;
    }

    //Plateau - constant speed
    #ifdef CPP_DEBUGGING
    cout << "d_pos: " << d_pos << ", abs_d_pos: " << abs_d_pos << endl;
    cout << "2) acc_pos: " << acc_pos << ", abs_acc_pos: " << abs_acc_pos << endl;
    #endif

    cte_spd_pos = abs_d_pos - (2*abs_acc_pos);
    cte_spd_pos_discrete = (cte_spd_pos/spd_max)*TRAPEZ_ONE_OVER_DT;
    #ifdef CPP_DEBUGGING
    cout << "cte_spd_pos: " << cte_spd_pos << ", cte_spd_pos_discrete: " << cte_spd_pos_discrete << endl;
    #endif
    if(cte_spd_pos_discrete < 0)
    {
        cte_spd_pos_discrete = 0;
        #ifdef CPP_DEBUGGING
        cout << "No steady speed!" << endl;
        #endif
    }

    //Transitions:
    trapez_transitions[0] = a_t_discrete;
    trapez_transitions[1] = a_t_discrete + cte_spd_pos_discrete;
    trapez_transitions[2] = 2*a_t_discrete + cte_spd_pos_discrete;
    #ifdef CPP_DEBUGGING
    cout << "tr[0]: " << trapez_transitions[0] << ", tr[1]: " << trapez_transitions[1] << ", tr[2]: " << trapez_transitions[2] << endl;
    #endif
    pos_step = 0;   //Variable used to output the current position command

    return (2*a_t_discrete + cte_spd_pos_discrete); //Returns the number of steps
}

#ifdef CPP_DEBUGGING
//This function is for debugging purposes only. It doesn't respect timing, it simply
//spits out the 3 waveforms in a txt file for Matlab visualization
void trapez_plot_all(void)
{
    int32 tmp_spd = 0, last_tmp_spd = 0, tmp_pos = 0, tmp_acc = 0;
    int32 i = 0;
    long long pos_integral = 0;

    //At this point all the parameters are computed, we can get the 3 plots

    //Open 3 text files - ToDo debug only
    ofstream txt_acc, txt_spd, txt_pos;
    txt_acc.open("acc.txt");
    txt_spd.open("spd.txt");
    txt_pos.open("pos.txt");

    //Acceleration:
    for(i = 0; i < a_t_discrete; i++)
    {
        last_tmp_spd = tmp_spd;
        tmp_spd = last_tmp_spd + spd_inc;
        pos_integral += tmp_spd;
        tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
        tmp_acc = acc;

        txt_spd << (tmp_spd / SPD_FACTOR) << ' ';
        txt_pos << tmp_pos << ' ';
        txt_acc << tmp_acc << ' ';
    }
    if(skip_sspeed == 0)
    {
        //Constant speed
        last_tmp_spd = tmp_spd;
        for(i = 0; i < cte_spd_pos_discrete; i++)
        {
            tmp_spd = last_tmp_spd;
            pos_integral += tmp_spd;
            tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
            tmp_acc = 0;

            txt_spd << (tmp_spd / SPD_FACTOR) << ' ';
            txt_pos << tmp_pos << ' ';
            txt_acc << tmp_acc << ' ';
        }
    }
    //Negative Acceleration:
    for(i = 0; i < a_t_discrete; i++)
    {
        last_tmp_spd = tmp_spd;
        tmp_spd = last_tmp_spd - spd_inc;
        pos_integral += tmp_spd;
        tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
        tmp_acc = -acc;

        txt_spd << (tmp_spd / SPD_FACTOR) << ' ';
        txt_pos << tmp_pos << ' ';
        txt_acc << tmp_acc << ' ';
    }
}
#endif

#ifdef CPP_DEBUGGING
//Runtime function - gives the next pos/spd/acc
//Debug only
void trapez_get_all(int32* pos, int32* spd, int32* acc)
{
    static int32 tmp_spd = 0, last_tmp_spd = 0, tmp_pos = 0, tmp_acc = 0;
    static long long pos_integral = 0;

    //At this point all the parameters are computed, we can get the 3 plots
    if(pos_step == 0)
    {
        tmp_spd = 0;
        last_tmp_spd = 0;
        tmp_pos = 0;
        tmp_acc = 0;
        pos_integral = init_pos;
    }

    //Acceleration:
    if(pos_step <= trapez_transitions[0])
    {
        last_tmp_spd = tmp_spd;
        tmp_spd = last_tmp_spd + spd_inc;
        pos_integral += tmp_spd;
        tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
        tmp_acc = *acc;

        //txt_spd << (tmp_spd / SPD_FACTOR) << ' ';
        *spd = (tmp_spd / SPD_FACTOR);
        cout << "In fct tmp_spd: " << *spd <<endl;
        //txt_pos << tmp_pos << ' ';
        *pos = tmp_pos;
        //txt_acc << tmp_acc << ' ';
        *acc = tmp_acc;
    }
    if(skip_sspeed == 0)
    {
        //Constant speed
        //last_tmp_spd = tmp_spd;
        if((pos_step >= trapez_transitions[0]) && (pos_step <= trapez_transitions[1]))
        {
            tmp_spd = last_tmp_spd;
            pos_integral += tmp_spd;
            tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
            //tmp_acc = 0;

            //txt_spd << (tmp_spd / SPD_FACTOR) << ' ';
            *spd = (tmp_spd / SPD_FACTOR);
            //txt_pos << tmp_pos << ' ';
            *pos = tmp_pos;
            //txt_acc << tmp_acc << ' ';
            *acc = 0;
        }
    }
    //Negative Acceleration:
    if((pos_step >= trapez_transitions[1]) && (pos_step <= trapez_transitions[2]))
    {
        last_tmp_spd = tmp_spd;
        tmp_spd = last_tmp_spd - spd_inc;
        pos_integral += tmp_spd;
        tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
        //tmp_acc = -tmp_acc;

        //txt_spd << (tmp_spd / SPD_FACTOR) << ' ';
        *spd = (tmp_spd / SPD_FACTOR);
        //txt_pos << tmp_pos << ' ';
        *pos = tmp_pos;
        //txt_acc << tmp_acc << ' ';
        *acc = -tmp_acc; //-tmp_acc;
        //cout << tmp_acc << endl;
    }

    //Ready for next one. Beware of overflows. ToDo safety
    pos_step++;
}
#endif

//Runtime function - gives the next position setpoint
int trapez_get_pos(int max_steps)
{
    static int tmp_spd = 0, last_tmp_spd = 0, tmp_pos = 0;
    int pos = 0;
    static long long pos_integral = 0;

    //At this point all the parameters are computed, we can get the 3 plots

    //First time:
    if(pos_step == 0)
    {
        tmp_spd = 0;
        last_tmp_spd = 0;
        tmp_pos = 0;
        pos_integral = 0;
        #ifdef CPP_DEBUGGING
        cout << "pos_step = 0, pos_integral = " << pos_integral << endl;
        #endif
    }

    //Acceleration:
    if(pos_step <= trapez_transitions[0])
    {
        last_tmp_spd = tmp_spd;
        tmp_spd = last_tmp_spd + spd_inc;
    }
    //if(skip_sspeed == 0)    //ToDo useful?
    {
        //Constant speed
        //last_tmp_spd = tmp_spd;
        if((pos_step >= trapez_transitions[0]) && (pos_step <= trapez_transitions[1]))
        {
            tmp_spd = last_tmp_spd;
        }
    }
    //Negative Acceleration:
    if((pos_step >= trapez_transitions[1]) && (pos_step <= trapez_transitions[2]))
    {
        last_tmp_spd = tmp_spd;
        tmp_spd = last_tmp_spd - spd_inc;
    }

    if(pos_step <= max_steps)
    {
        //Ready for next one.
        pos_step++;

        //Common math:
        pos_integral += tmp_spd;
        tmp_pos = pos_integral/(TRAPEZ_ONE_OVER_DT * SPD_FACTOR);
        pos = tmp_pos + init_pos;
        #ifdef CPP_DEBUGGING
        if(pos_step < 10)
            cout << "pos_step: " << pos_step << ", pos_integral: " << pos_integral << ", pos: " << pos << endl;
        #endif
    }
    else
    {
        pos = tmp_pos + init_pos;
    }

    //New setpoint
    return pos;
}

//Returns absolute value
int absolute(int val)
{
    if(val < 0)
        val = -val;

    return val;
}
