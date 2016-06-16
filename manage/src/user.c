//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// user: User Projects & Functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "user.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//MIT Ankle 2-DoF:
#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)

struct ankle2dof_s ankle2dof_left, ankle2dof_right;

#endif	//PROJECT_ANKLE_2DOF

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Initialization function - call once in main.c, before while()
void init_user(void)
{	
	//RIC/NU Knee:
	#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)
	init_ricnu_knee();
	#endif	//PROJECT_RICNU_KNEE
	
	//MIT Ankle 2-DoF:
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
	init_ankle_2dof();
	#endif	//PROJECT_ANKLE_2DOF
	
	//MIT d'Arbeloff Dual-Speed Dual-Motor:
	#if(ACTIVE_PROJECT == PROJECT_DSDM)
	init_dsdm();
	#endif	//PROJECT_DSDM  
}

//Call this function in one of the main while time slots.
void user_fsm_1(void)
{
	
	//RIC/NU Knee code
	#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	ricnu_knee_fsm();						
	#endif	//PROJECT_RICNU_KNEE

	//MIT Ankle 2-DoF:
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
	ankle_2dof_fsm_1();
	#endif	//PROJECT_ANKLE_2DOF
	
	//MIT d'Arbeloff Dual-Speed Dual-Motor:
	#if(ACTIVE_PROJECT == PROJECT_DSDM)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	dsdm_fsm();						
	#endif	//PROJECT_DSDM	
}

//Optional second FSM
//Call this function in one of the main while time slots.
void user_fsm_2(void)
{
	//MIT Ankle 2-DoF:
	#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
	ankle_2dof_fsm_2();
	#endif	//PROJECT_ANKLE_2DOF
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

