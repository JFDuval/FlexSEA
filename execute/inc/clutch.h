#ifndef INC_CLUTCH_H
#define INC_CLUTCH_H
	
#include <project.h>

//Common defines:
#define CLUTCH_OFF	0
#define CLUTCH_10V	1
#define CLUTCH_24V	2
	
//Prototypes
void clutch_output(uint8 value);
void clutch_test(void);

	
#endif
	