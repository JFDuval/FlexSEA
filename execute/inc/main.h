//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (JF) Duval
// jfduval@media.mit.edu
// 06/2016
//****************************************************************************
// main: FlexSEA-Execute
//****************************************************************************

#ifndef MAIN_H_
#define MAIN_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include <project.h>
#include <DieTemp_1.h>
#include <math.h>
#include "stdio.h"
#include "main_fsm.h"
#include "serial.h"
#include "i2c.h"
#include "motor.h"
#include "misc.h"
#include "ui.h"
#include "trapez.h"
#include "imu.h"
#include "analog.h"
#include "usb.h"
#include "strain.h"
#include "safety.h"
#include "peripherals.h"
#include "control.h"
#include "sensor_commut.h"
#include "ext_input.h"
#include "ext_output.h"
#include "gen_waveform.h"
#include "demo.h"
#include "user.h"	//Contains all the user_x.h includes
#include "flexsea_board.h"
#include "../../flexsea-system/inc/flexsea_system.h"	
#include "../../flexsea-comm/inc/flexsea.h"	

//****************************************************************************
// Shared variable(s)
//****************************************************************************
	
extern int steps;
extern uint16 angle;

//****************************************************************************
// Prototype(s):
//****************************************************************************

int main(void);

#if defined (__GNUC__)
    asm (".global _printf_float");
#endif

//****************************************************************************
// Definition(s):
//****************************************************************************

//List of encoders that can be used by controllers (position, impedance),
//and for commutation:
#define ENC_NONE				0	//No encoder
#define ENC_HALL				1	//Hall effect (motor commutation)
#define ENC_QUADRATURE			2	//Optical or magnetic, AB/I inputs on QEI1
#define ENC_ANALOG				3	//Potentiometer (or other), on ext. analog in.
#define ENC_AS5047				4	//16-bit Magnetic Position Sensor, SPI
#define ENC_AS5048B				5	//14-bit Magnetic Position Sensor, I2C
//(later you'll assign what encoder is used by the controllers, for motor
// commutation, and which one is displayed in the GUI)

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

#define ACTIVE_PROJECT			PROJECT_DSDM
#define ACTIVE_SUBPROJECT		SUBPROJECT_A

//Step 2) Customize the enabled/disabled sub-modules:
//===================================================

//Barebone FlexSEA-Execute project - no external peripherals.
#if(ACTIVE_PROJECT == PROJECT_BAREBONE)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_QEI
	#define USE_TRAPEZ
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	#define USE_STRAIN			//Requires USE_I2C_1
	
	//Motor type & direction:
	#define MOTOR_TYPE		MOTOR_BRUSHLESS
	#define PWM_SIGN		1
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		DISABLED
	
	//Encoders:
	#define ENC_CONTROL		ENC_QUADRATURE
	#define ENC_COMMUT		ENC_HALL
	#define ENC_DISPLAY		ENC_QUADRATURE	
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_BAREBONE

//Exoboot
#if(ACTIVE_PROJECT == PROJECT_EXOCUTE)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_QEI
	#define USE_TRAPEZ
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	#define USE_STRAIN			//Requires USE_I2C_1
	
	//Motor type & direction:
	#define MOTOR_TYPE		MOTOR_BRUSHLESS
	#define PWM_SIGN		1
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		DISABLED

	//Encoders:
	#define ENC_CONTROL		ENC_QUADRATURE
	#define ENC_COMMUT		ENC_HALL
	#define ENC_DISPLAY		ENC_CONTROL
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_EXOCUTE

//CSEA Knee
#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_QEI
	#define USE_TRAPEZ
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	//#define USE_STRAIN		//Requires USE_I2C_1
	
	//Motor type & direction:
	#define MOTOR_TYPE		MOTOR_BRUSHLESS
	#define PWM_SIGN		1
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		ENABLED

	//Encoders:
	#define ENC_CONTROL		ENC_ANALOG
	#define ENC_COMMUT		ENC_HALL
	#define ENC_DISPLAY		ENC_CONTROL	
	
	//Project specific definitions:
	#define CSEA_FULL_FLEX_RAW		580		//Raw value
	#define CSEA_FULL_EXT_RAW		2840	//Raw value
	#define CSEA_FULL_FLEX			2260
	#define CSEA_FULL_EXT			0
	#define CSEA_MARGIN				300
	#define CSEA_MOTION_TIME		3500
	
	//Control encoder function:
	#define CTRL_ENC_FCT(x) (-((int16)x - CSEA_FULL_EXT_RAW))
	
#endif	//PROJECT_CSEA_KNEE

//RIC/NU Knee
#if(ACTIVE_PROJECT == PROJECT_RICNU_KNEE)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	//#define USE_QEI
	#define USE_TRAPEZ
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	//#define USE_STRAIN		//Requires USE_I2C_1
	#define USE_AS5047			//16-bit Position Sensor, SPI
	#define USE_SPI_COMMUT		//
	//#define USE_MINM_RGB		//External RGB LED. Requires USE_I2C_0.
	#define USE_EXT_I2C_STRAIN	//External Strain Amplifier, on I2C0
	#define USE_AS5048B			//14-bit Position Sensor, on I2C0
	
	//Motor type & direction:
	#define MOTOR_TYPE		MOTOR_BRUSHLESS
	#define PWM_SIGN		1
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		ENABLED

	//Encoders:
	#define ENC_CONTROL		ENC_AS5048B
	#define ENC_COMMUT		ENC_AS5047
	#define ENC_DISPLAY		ENC_CONTROL	
	
	//Control encoder function:
	#define CTRL_ENC_FCT(x) (14000 - x)	//ToDo make better
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_RICNU_KNEE

//MIT 2-DoF Ankle
#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	//#define USE_QEI
	#define USE_TRAPEZ
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	//#define USE_STRAIN		//Requires USE_I2C_1
	#define USE_AS5047			//16-bit Position Sensor, SPI
	#define USE_SPI_COMMUT		//
	
	//Motor type:
	#define MOTOR_TYPE		MOTOR_BRUSHLESS
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		ENABLED

	//Encoders:
	#define ENC_CONTROL		ENC_AS5047
	#define ENC_COMMUT		ENC_AS5047
	#define ENC_DISPLAY		ENC_CONTROL	
	
	//Subproject A: Left actuator
	#if(ACTIVE_SUBPROJECT == SUBPROJECT_A)
		
		//Control encoder function:
		#define CTRL_ENC_FCT(x) (x)	//ToDo
		#define PWM_SIGN		1
		
		//...
		
	#endif	//SUBPROJECT_A
	
	//Subproject B: Right actuator
	#if(ACTIVE_SUBPROJECT == SUBPROJECT_B)
		
		//Control encoder function:
		#define CTRL_ENC_FCT(x) (x)	//ToDo
		#define PWM_SIGN		-1
		
		//...
		
	#endif	//SUBPROJECT_B
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_ANKLE_2DOF

//MIT d'Arbeloff Dual-Speed Dual-Motor
#if(ACTIVE_PROJECT == PROJECT_DSDM)
	
	//Enable/Disable sub-modules:
	#define USE_RS485
	#define USE_USB
	#define USE_COMM			//Requires USE_RS485 and/or USE_USB
	#define USE_QEI
	#define USE_TRAPEZ
	#define USE_I2C_0			//3V3, IMU & Expansion.
	#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
	#define USE_IMU				//Requires USE_I2C_0
	//#define USE_STRAIN			//Requires USE_I2C_1
	
	//Motor type & direction:
	#define MOTOR_TYPE		MOTOR_BRUSHED
	
	//Runtime finite state machine (FSM):
	#define RUNTIME_FSM		DISABLED

	//Encoders:
	#define ENC_CONTROL		ENC_QUADRATURE
	#define ENC_COMMUT		ENC_NONE		//Brushed, no encoder
	#define ENC_DISPLAY		ENC_CONTROL
	
	//Subproject A: Fast actuator
	#if(ACTIVE_SUBPROJECT == SUBPROJECT_A)
		
		//Control encoder function:
		#define CTRL_ENC_FCT(x) (x)	//ToDo
		#define PWM_SIGN		1
		
		//...
		
	#endif	//SUBPROJECT_A
	
	//Subproject B: Slow actuator
	#if(ACTIVE_SUBPROJECT == SUBPROJECT_B)
		
		//Control encoder function:
		#define CTRL_ENC_FCT(x) (x)	//ToDo
		#define PWM_SIGN		1
		
		//...
		
	#endif	//SUBPROJECT_B	
	
	//Project specific definitions:
	//...
	
#endif	//PROJECT_DSDM

#endif // MAIN_H_
