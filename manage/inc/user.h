//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// user: User Projects & Functions
//****************************************************************************

//Note: this file needs significant work! Use with care, it's mostly
//		a copy of Execute's user.h

#ifndef INC_USER_H
#define INC_USER_H

//****************************************************************************
// Include(s)
//****************************************************************************		
	
#include "main.h"
#include "user_ricnu_knee.h"
#include "user_ankle_2dof.h"
#include "user_dsdm.h"
//Add your project specific user_x.h file here
	
//****************************************************************************
// Shared variable(s)
//****************************************************************************

//MIT Ankle 2-DoF:
#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)

extern struct ankle2dof_s ankle2dof_left, ankle2dof_right;

#endif	//PROJECT_ANKLE_2DOF

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************	

void init_user(void);
void user_fsm_1(void);
void user_fsm_2(void);

//****************************************************************************
// Definition(s):
//****************************************************************************	

//List of projects:
#define PROJECT_BAREBONE		0	//Barebone Execute, default option.
#define PROJECT_EXOCUTE			1	//ExoBoot, everything running on Execute
#define PROJECT_CSEA_KNEE		2	//CSEA Knee + FlexSEA
#define PROJECT_RICNU_KNEE		3	//RIC/NU Knee
#define PROJECT_ANKLE_2DOF		4	//Biomechatronics 2-DOF Ankle
#define PROJECT_DSDM			5	//MIT d'Arbeloff Dual-Speed Dual-Motor

//List of sub-projects:
#define SUBPROJECT_NONE			0
#define SUBPROJECT_A			1
#define SUBPROJECT_B			2
//(ex.: the 2-DoF ankle has 2 Execute. They both use PROJECT_2DOF_ANKLE, and each
// 		of them has a sub-project for specific configs)

//Step 1) Select active project (from list):
//==========================================

#define ACTIVE_PROJECT			PROJECT_ANKLE_2DOF
#define ACTIVE_SUBPROJECT		SUBPROJECT_NONE

//Step 2) Customize the enabled/disabled sub-modules:
//===================================================

//Barebone FlexSEA-Manage project - no external peripherals.
#if(ACTIVE_PROJECT == PROJECT_BAREBONE)
	
	//Enable/Disable sub-modules:
	/* ToDo see what drivers I have, and mod this code:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	*/
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		DISABLED
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_BAREBONE

//CSEA Knee
#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)
//...
#endif	//PROJECT_CSEA_KNEE

//RIC/NU Knee
#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)
//...
#endif	//PROJECT_RICNU_KNEE

//MIT 2-DoF Ankle
#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	//#define USE_TRAPEZ
	//#define USE_I2C_0			//3V3, IMU & Expansion.
	//#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	//#define USE_IMU			//Requires USE_I2C_0
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM1		ENABLED
	#define RUNTIME_FSM2		ENABLED
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_ANKLE_2DOF

//MIT d'Arbeloff Dual-Speed Dual-Motor
#if(ACTIVE_PROJECT == PROJECT_DSDM)
//...
#endif	//PROJECT_DSDM

//****************************************************************************
// Structure(s)
//****************************************************************************	

struct ankle2dof_s
{
	uint8_t r_w;					//Read/write values
	uint8_t ctrl;					//Controller
	uint8_t ctrl_change;			//KEEP or CHANGE
	uint8_t ctrl_o;					//Open speed
	uint8_t ctrl_i;					//Current
	struct gains_s ctrl_i_gains;	//Current controller gains
};
	
#endif	//INC_USER_H
	
