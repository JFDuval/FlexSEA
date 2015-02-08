//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "misc.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Safety-CoP Data:
struct scop
{
	uint16 v_vb, v_vg, v_3v3;
	uint8 temperature;
	uint8 status1;
}safetycop;

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

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
	
	//I2C1 (internal, potentiometers & IMU)
	#ifdef USE_I2C_INT	
	I2C_1_Init();
	I2C_1_EnableInt();
	I2C_1_Enable();
	I2C_1_Start();	
	#endif	//USE_I2C_INT
	
	//I2C2 (external)
	#ifdef USE_I2C_EXT
	I2C_2_Init();
	I2C_2_Enable();
	I2C_2_Start();
	#endif	//USE_I2C_EXT
	
	//Analog amplifiers & multiplexer(s):
	PGA_1_Start();
	Opamp_1_Start();
	Opamp_2_Start();
	Opamp_3_Start();
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
	
	//VR2 DAC:
	VDAC8_3_Start();

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
	#ifdef USE_RS485
	UART_2_Init();
	UART_2_Enable();
	UART_2_Start();		
	NOT_RE_Write(0);			//Enable RS-485 Receiver
	#endif	//USE_RS485
	
	//RGB LED (all colors OFF)
	LED_R_Write(1);
	LED_G_Write(1);
	LED_B_Write(1);
	
	//MPU-6500 IMU:
	#ifdef USE_I2C_INT	
		#ifdef USE_IMU
		init_imu();
		#endif	//USE_IMU
	#endif	//USE_I2C_INT
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

//Update the global variables from the array
void decode_psoc4_values(uint8 *psoc4_data)
{
	safetycop.v_vb = (psoc4_data[MEM_R_VB_SNS_MSB] << 8) + psoc4_data[MEM_R_VB_SNS_LSB];
	safetycop.v_vg = (psoc4_data[MEM_R_VG_SNS_MSB] << 8) + psoc4_data[MEM_R_VG_SNS_LSB];
	safetycop.v_3v3 = (psoc4_data[MEM_R_3V3_SNS_MSB] << 8) + psoc4_data[MEM_R_3V3_SNS_LSB];
	safetycop.temperature = psoc4_data[MEM_R_TEMPERATURE];
	safetycop.status1 = psoc4_data[MEM_R_STATUS1];
}

//Update the sensor structures:
void update_sensors(void)
{
	//IMU:
	#ifdef USE_I2C_INT
		
		#ifdef USE_IMU
			
			get_accel_xyz();
			get_gyro_xyz();
			//We could also get temperature
			
		#endif	//USE_IMU
		
	#endif	//USE_I2C_INT	
}
