#ifndef INC_MISC_H
#define INC_MISC_H
	
#include <project.h>

//Common defines:
#define PACKET_LEN					64
#define QUAD1_INIT					13000
#define USB_ENUM_TIMEOUT			2500	//ms
	
//ADC
#define ADC1_CHANNELS				6
#define ADC1_BUF_LEN				8
	
//I2C
#define BUFFER_SIZE	4
uint8 i2cMasterReadBuf[BUFFER_SIZE];
uint8 i2cMasterWriteBuf[BUFFER_SIZE];
#define I2C_SLAVE_ADDR_MINM			0x09
#define I2C_SLAVE_ADDR_IMU			
#define SET_RGB	'n' 
	
//Prototypes
void init_peripherals(void);
int16 send_usb_packet(uint16 word1, uint16 word2, uint16 word3, uint16 word4);
void send_usb_int32(int payload);
void send_usb_int16(int16 payload);
void send_usb_int8(char payload);
void send_usb_uint8(uint8 payload);
uint8 init_usb(void);
uint16 adc_avg8(uint16 new_data);
uint8 usb_echo_blocking(void);
void rs485_putc(uint8 byte);
void i2c_write_minm_rgb(uint8 cmd, uint8 r, uint8 g, uint8 b);
void filter_adc(void);
	
#endif
	