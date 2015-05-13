#include <project.h>
#include "main.h"
#include "sensors.h"

//Variables

uint16 read_battery_voltage(){
    return (uint16)(((ADC_SAR_Seq_1_GetResult16(1) * 3.3 / 2048.0) * 10.106  - 1.3278) * 1000.0);
}