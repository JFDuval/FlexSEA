//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// safety: safety checks, hazard management
//****************************************************************************
	
#ifndef INC_SAFETY_H
#define INC_SAFETY_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"

//****************************************************************************
// Structure(s)
//****************************************************************************	
	
extern uint8 flag_wdclk;		
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_safety(void);
uint8 safety_temp(uint8 temp);
uint8 safety_volt(uint16 last_v, uint16 low, uint16 high);
uint8 safety_disconnection(uint16 last_v);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Temperature (in degree Celsius):
#define TEMP_WARNING		75
#define TEMP_ERROR			80
//based on components rated for a minimum of +85C
	
//Temperature filtering:
#define TEMP_BUF_SIZE		128		//10ms/sample, 128 = 1.28s
#define TEMP_BUF_SHIFT		7		//2^TEMP_BUF_SHIFT = TEMP_BUF_SIZE
	
//+3V3: MCP1700 ±3%, we will use ±4% (±132mV, 3.168-3.432V)
#define M_3V3_LOW			2595
#define M_3V3_NORMAL		2703
#define M_3V3_HIGH			2811	

//+VG: at 600mA its 8.7V, drop of 1.3/10 = 13%. Will use +5%/-13%. 
//Normal is 10V, range is 8.7-10.5V. Gain = 0.43.
#define M_VG_LOW			3064
#define M_VG_NORMAL			3523
#define M_VG_HIGH			3699
	
//+VB: from 15 to 28V. Gain = 0.14493
#define M_VB_LOW			1781
#define M_VB_HIGH			3324

//+VB filtering (for the disconnected battery detection):
#define VB_BUF_SIZE			1024	//10ms/sample, 1024 = 10.24s
#define VB_BUF_SHIFT		10		//2^VB_BUF_SHIFT = VB_BUF_SIZE

//Disconnected battery threshold: 80% of the average
//Approximated by (value*13)>>4 = 81.25% of value
#define DISCON_GAIN			13
#define DISCON_SHIFT		4

//Qualitative:	
#define V_LOW				0
#define V_NORMAL			1
#define V_HIGH				2	
#define T_NORMAL			0
#define T_WARNING			1
#define T_ERROR				2
#define BATT_CONNECTED		0
#define BATT_DISCONNECTED	1
	
#endif	//INC_SAFETY_H
	