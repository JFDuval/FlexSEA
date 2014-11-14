#include <project.h>
#include "main.h"
#include "misc.h"
#include "../../common/inc/flexsea.h"

#define BUFFER_LEN		64
uint8 buffer[BUFFER_LEN];

//ADC
unsigned int adc_res[ADC_CHANNELS][ADC_BUF_LEN];
unsigned int adc_res_filtered[ADC_CHANNELS];

//Initialize and enables all the general peripherals
void init_peripherals(void)
{
	//Timer 1: 1ms (LEDs, PID)
	Timer_1_Init();
	Timer_1_Start();
	isr_t1_Start();
	
	//Timer 2: 50ms (safety)
	Timer_2_Init();
	Timer_2_Start();
	isr_t2_Start();
	
	//Timer 3: one-shot 20us (current controller)
	Timer_3_Init();
	Timer_3_Start();
	isr_t3_Start();
	
	//I²C 2 (external)
	I2C_2_Init();
	I2C_2_Enable();
	I2C_2_Start();
	
	//Analog amplifiers & multiplexer(s):
	PGA_1_Start();
	Opamp_1_Start();
	//Opamp_2_Start();
	AMux_1_Start();
	AMux_1_Select(0);
	
	//ADC1: Absolute encoder + force sensor
	ADC_SAR_1_Start();
	ADC_SAR_1_IRQ_Enable();
	ADC_SAR_1_StartConvert();
	
	//ADC2: Motor current
	ADC_SAR_2_Start();
	ADC_SAR_2_IRQ_Enable();
	ADC_SAR_2_StartConvert();
	
	//VDAC8: Debug only 
	VDAC8_1_Start();

	//Quadrature 1: Motor shaft encoder
	QuadDec_1_Start();
	QuadDec_1_Enable();
	QuadDec_1_SetCounter(QUAD1_INIT);
	
	//PWM1: BLDC
	PWM_1_Start();
	PWM_1_WriteCompare(0);	//Start at 0%
	isr_pwm_Start();
	
	//PWM2: Clutch
	PWM_2_Start();
	PWM_2_WriteCompare(0);	//Start at 0%
	//isr_pwm_Start();	
	
	//UART 2 - RS-485
	UART_2_Init();
	UART_2_Enable();
	UART_2_Start();		
	NOT_RE_Write(0);			//Enable RS-485 Receiver
}

//Initialize the USB peripheral
//Returns 0 is success, 1 if timeout (happens when the cable is unplugged)
uint8 init_usb(void)
{
	uint16 cnt = 0, flag = 0;
	
	//Start USBFS Operation with 3V operation
    USBUART_1_Start(0u, USBUART_1_3V_OPERATION);
	
	//Wait for Device to enumerate */
    //while(!USBUART_1_GetConfiguration());
	for(cnt = 0; cnt < USB_ENUM_TIMEOUT; cnt++)
	{
		if(USBUART_1_GetConfiguration())
		{
			flag = 1;
			break;
		}
		CyDelay(1);
	}

	if(flag)	
	{
	    //Enumeration is done, enable OUT endpoint for receive data from Host
	    USBUART_1_CDC_Init();	
		return 1;		//Success
	}
	
	return 0;	//Timeout	
}

//Send 4 uint16 to the terminal
int16 send_usb_packet(uint16 word1, uint16 word2, uint16 word3, uint16 word4)
{
	static uint8 cnt = 0;
	char8 packet[18];

	cnt++;
	
	packet[0] = 0xAA;	//Start byte
	

	packet[2] = ((word1 & 0xFF00) >> 8);
	packet[3] = ((word1 & 0x00FF));
	
	packet[4] = ((word2 & 0xFF00) >> 8);
	packet[5] = ((word2 & 0x00FF));
	
	packet[6] = ((word3 & 0xFF00) >> 8);
	packet[7] = ((word3 & 0x00FF));
	
	packet[8] = ((word4 & 0xFF00) >> 8);
	packet[9] = ((word4 & 0x00FF));
	

	packet[15] = 0xCC;	//End byte
	packet[16] = '\n';
	packet[17] = '\0';
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)packet, 18);

	return 0;
}

//Chops a int32 in 4 bytes and send them through USB - ho headers, raw data
void send_usb_int32(int payload)
{
	int tmp = 0;
	char8 packet[4];
	
	//MSB first
	tmp = (payload >> 24) & 0xFF;
	packet[0] = (uint8) tmp;
	tmp = (payload >> 16) & 0xFF;
	packet[1] = (uint8) tmp;
	tmp = (payload >> 8) & 0xFF;
	packet[2] = (uint8) tmp;
	tmp = (payload) & 0xFF;
	packet[3] = (uint8) tmp;
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)packet, 4);

	return;
}

//Chops a int16 in 2 bytes and send them through USB - ho headers, raw data
//Works with Matlab
void send_usb_int16(int16 payload)
{
	int tmp = 0;
	char8 packet[4];
	
	//MSB first
	tmp = (payload >> 8) & 0xFF;
	packet[1] = (uint8) tmp;
	tmp = (payload) & 0xFF;
	packet[0] = (uint8) tmp;
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)packet, 2);

	return;
}

//1 byte through USB - ho headers, raw data
void send_usb_int8(char payload)
{
	char8 tmp[16]; 
	tmp[0] = (payload & 0xFF);
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)tmp, 1);

	return;
}

//1 byte through USB - ho headers, raw data
void send_usb_uint8(uint8 payload)
{
	uint8 tmp[16]; 
	tmp[0] = (payload & 0xFF);
	
	//Make sure that the peripheral is ready
	while(USBUART_1_CDCIsReady() == 0u);	//ToDo Add timeout!
	USBUART_1_PutData((const uint8*)tmp, 1);

	return;
}

uint16 adc_avg8(uint16 new_data)
{
	uint32 sum = 0;
	static uint16 adc_avg_bug[8] = {0,0,0,0,0,0,0,0};
	static uint8 cnt = 0;
	uint16 avg = 0;
	
	//Shift buffer and sum 7/8 terms
	for(cnt = 1; cnt < 8; cnt++)
	{
		adc_avg_bug[cnt-1] = adc_avg_bug[cnt];
		sum += adc_avg_bug[cnt-1];
	}
	adc_avg_bug[7] = new_data;
	sum += new_data;
		
	//Average
	avg = (uint16)(sum >> 3);
	
	return avg;	
}

//Returns chars to PC. ToDo: make it non-blocking!
uint8 usb_echo_blocking(void)
{
	static 	int16 count = 0;
	uint16 i = 0;
	
	//USB Data
	if(USBUART_1_DataIsReady() != 0u)               	//Check for input data from PC
	{   
		count = USBUART_1_GetAll(buffer);           	//Read received data and re-enable OUT endpoint
		if(count != 0u)
		{
			while(USBUART_1_CDCIsReady() == 0u);    	//Wait till component is ready to send more data to the PC
			USBUART_1_PutData(buffer, count);   		//Send data back to PC

			//Store all bytes in rx buf:			
			for(i = 0; i < count; i++)
		    {
		        comm_update_rx_buffer(buffer[i]);
		    }			
			
			return 1;	//Got byte(s)
		}
    } 
	
	return 0;	//No byte
}

void rs485_putc(uint8 byte)
{
	NOT_RE_Write(1);			//Disable Receiver
	UART_2_PutChar(byte);		//Send byte
	//NOT_RE_Write(0);			//Enable Receiver
}

//Write to MinM RGB LED
void i2c_write_minm_rgb(uint8 cmd, uint8 r, uint8 g, uint8 b)
{
	// Write data to the slave : address pointer
	i2cMasterWriteBuf[0] = cmd;
	i2cMasterWriteBuf[1] = r;
	i2cMasterWriteBuf[2] = g;
	i2cMasterWriteBuf[3] = b;

    I2C_2_MasterWriteBuf(I2C_SLAVE_ADDR_MINM, (uint8 *) i2cMasterWriteBuf,
                             4, I2C_2_MODE_COMPLETE_XFER);

    while(0u == (I2C_2_MasterStatus() & I2C_2_MSTAT_WR_CMPLT))
    {
        // Wait until master complete write
    }    
  
    // Clear I2C master status 
    (void) I2C_2_MasterClearStatus();
	
	return;	
}

//Filters the ADC buffer
//ToDo: generalize & optimize
void filter_adc(void)
{
	uint16 i = 0;
	uint16 tmp_ch0 = 0, tmp_ch1 = 0;
	
	for(i = 0; i < 8; i++)
	{
		tmp_ch0 += adc_res[0][i];
		tmp_ch1 += adc_res[1][i];
	}
	adc_res_filtered[0] = tmp_ch0 >> 3;
	adc_res_filtered[1] = tmp_ch1 >> 3;
}
