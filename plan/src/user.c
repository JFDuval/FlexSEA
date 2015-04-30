//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// user: User Code Wrapper
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "user.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

void user(uint8_t user_number, uint8_t user_experiment)
{
    void (*user_fct_ptr)(uint8_t) = &user_null;

    //Map function call to user files:
    switch(user_number)
    {
		//Case 0: Default/Info
    	case 0:
    		printf("\nUser 1: ShuoBot.\n");
    		printf("User 2: CSEA Knee.\n");
    		user_fct_ptr = &user_null;
    		break;

    		//Case 1: ShuoBot
    	case 1:
    		user_fct_ptr = &shuobot;
    		break;

    		//Case 2: CSEA Knee
    	case 2:
    		user_fct_ptr = &user_null;// &csea;
    		break;

    	default:
			#ifdef USE_PRINTF
    		printf("<flexsea_user> Invalid user.\n");
    		usleep(750000);	//750ms
			#endif
    		user_fct_ptr = &user_null;
    		break;
    }

	//Call function
    user_fct_ptr(user_experiment);
}

void user_null(uint8_t exp)
{
	//Empty function
}
