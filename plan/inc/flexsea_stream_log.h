//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// flexsea_stream_log: Stream & Data log
//****************************************************************************

#ifndef INC_FLEXSEA_SLOG_H
#define INC_FLEXSEA_SLOG_H

//****************************************************************************
// Include(s)
//****************************************************************************


//****************************************************************************
// Shared variable(s)
//****************************************************************************


//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void flexsea_console_stream(int experiment);
void flexsea_console_log(int experiment);

void flexsea_stream_print_null(void);
void flexsea_stream_print_1(void);
void flexsea_stream_print_2(void);
void flexsea_stream_print_3(void);
void flexsea_stream_print_4(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Streaming and logging delays:
#define STREAM_DELAY_US			200
#define LOG_DELAY_US			500

//#define SLOW_TERMINAL_DISPLAY
#define SLOW_N_CYCLES			10

#endif
