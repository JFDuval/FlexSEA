//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 08/2014
//****************************************************************************
// usbtool_serial: Serial port driver
//****************************************************************************

#ifndef INC_USBTOOL_SERIAL_H
#define INC_USBTOOL_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************


//****************************************************************************
// Prototype(s):
//****************************************************************************

int read_port_name_from_file(void);
int flexsea_serial_open(unsigned int tries, unsigned int delay);
int flexsea_serial_open_2(char *port, unsigned int tries, unsigned int delay);
void flexsea_serial_close(void);
void flexsea_serial_transmit(char bytes_to_send, unsigned char *serial_tx_data, unsigned char verbal);
void flexsea_serial_putc(char *bytes_to_write);
void flexsea_serial_read(uint8_t *buffer);

//****************************************************************************
// Definition(s):
//****************************************************************************

#ifdef __cplusplus
}
#endif

#endif

