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

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static void init_barebone(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Initialization function - call once in main.c, before while()
void init_user(void)
{	
	//Barebone:
	#if(ACTIVE_PROJECT == PROJECT_BAREBONE)
	init_barebone();
	#endif	//PROJECT_EXOCUTE
	
	//ExoBoots:
	#if(ACTIVE_PROJECT == PROJECT_EXOCUTE)
	init_exo();
	#endif	//PROJECT_EXOCUTE
	
	//MIT CSEA Knee:
	#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)
	init_csea_knee();
	#endif	//PROJECT_CSEA_KNEE
	
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
void user_fsm(void)
{
	//ExoBoot code
	#if(ACTIVE_PROJECT == PROJECT_EXOCUTE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	exo_fsm();							
	#endif	//PROJECT_EXOCUTE
	
	//CSEA Knee code
	#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	csea_knee_fsm();						
	#endif	//PROJECT_CSEA_KNEE
	
	//RIC/NU Knee code
	#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	ricnu_knee_fsm();						
	#endif	//PROJECT_RICNU_KNEE
	
	//MIT d'Arbeloff Dual-Speed Dual-Motor:
	#if(ACTIVE_PROJECT == PROJECT_DSDM)				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	dsdm_fsm();						
	#endif	//PROJECT_DSDM	
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

static void init_barebone(void)
{
	//Barebone:
	#if(ACTIVE_PROJECT == PROJECT_BAREBONE)
	board_id = SLAVE_ID;
	#endif	//PROJECT_EXOCUTE	
}
