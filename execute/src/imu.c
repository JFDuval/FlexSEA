//****************************************************************************
// MIT Media Lab - Biomechatronics
// Erin Main & JFDuval
// ermain@mit.edu, jfduval@mit.edu
// 02/2015
//****************************************************************************
// imu: I2C IMU (MPU-6500)
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "imu.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

uint8 i2c_tmp_buf[IMU_MAX_BUF_SIZE];

//Inner structure for the gyro and the accelero
struct xyz
{
     int16 x;
     int16 y;
     int16 z;
};

//IMU data & config
struct imu_struct
{
     struct xyz accel;
     struct xyz gyro;
     uint32_t config;
}imu;

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//// HIGH LEVEL FUNCTIONS ////
// Initialize the IMU w/ default values in config registers
void init_imu() 
{
	//Reset the IMU
	reset_imu();
	while(I2C_1_MasterStatus() != I2C_1_MSTAT_WR_CMPLT);
	//ToDo: add a timeout
	
	// Initialize the config registers.
	uint8_t config[4] = { D_IMU_CONFIG, D_IMU_GYRO_CONFIG, D_IMU_ACCEL_CONFIG, D_IMU_ACCEL_CONFIG2 };
	
	//Send the config sequence
	imu_write(IMU_CONFIG, config, 4);
	while(I2C_1_MasterStatus() != I2C_1_MSTAT_WR_CMPLT);
	//ToDo: add a timeout
}

// Get accel X
int16 get_accel_x(void) 
{
	uint8 data[2] = { 0, 0 };
	imu_read(IMU_ACCEL_XOUT_H, data, 2);
	return (int16)((uint16) data[0] << 8) | (data[1]);
}
// Get accel Y
int16 get_accel_y(void)
{
	uint8 data[2];
	imu_read(IMU_ACCEL_YOUT_H, data, 2);
	return (int16)((uint16) data[0] << 8) | (data[1]);
}

// Get accel Z
int16 get_accel_z(void)
{
	uint8 data[2];
	imu_read(IMU_ACCEL_ZOUT_H, data, 2);
	return (int16)((uint16) data[0] << 8) | (data[1]);
}

//Puts all the accelerometer values in the structure:
void get_accel_xyz(void)
{
	uint8 tmp_data[6] = {0,0,0,0,0,0};
	uint16 tmp = 0;
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_ACCEL_XOUT_H, tmp_data, 6);
	
	//Accel X:
	tmp = ((uint16)tmp_data[0] << 8) | ((uint16) tmp_data[1]);
	imu.accel.x = (int16)tmp;
	
	//Accel Y:
	tmp = ((uint16)tmp_data[2] << 8) | ((uint16) tmp_data[3]);
	imu.accel.x = (int16)tmp;
	
	//Accel Z:
	tmp = ((uint16)tmp_data[4] << 8) | ((uint16) tmp_data[5]);
	imu.accel.x = (int16)tmp;
}

// Get gyro X
int16 get_gyro_x(void)
{
	uint8 data[2];
	imu_read(IMU_GYRO_XOUT_H, data, 2);
	return (int16)((uint16) data[0] << 8) | (data[1]);
}

// Get gyro Y
int16 get_gyro_y(void)
{
	uint8 data[2];
	imu_read(IMU_GYRO_YOUT_H, data, 2);
	return (int16)((uint16) data[0] << 8) | (data[1]);
}

// Get gyro Z
int16 get_gyro_z(void)
{
	uint8 data[2];
	imu_read(IMU_GYRO_ZOUT_H, data, 2);
	return (int16)((uint16) data[0] << 8) | (data[1]);
}

//Puts all the gyroscope values in the structure:
void get_gyro_xyz(void)
{
	uint8 tmp_data[6] = {0,0,0,0,0,0};
	uint16 tmp = 0;
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_GYRO_XOUT_H, tmp_data, 6);
	
	//Gyro X:
	tmp = ((uint16)tmp_data[0] << 8) | ((uint16) tmp_data[1]);
	imu.gyro.x = (int16)tmp;
	
	//Gyro Y:
	tmp = ((uint16)tmp_data[2] << 8) | ((uint16) tmp_data[3]);
	imu.gyro.x = (int16)tmp;
	
	//Gyro Z:
	tmp = ((uint16)tmp_data[4] << 8) | ((uint16) tmp_data[5]);
	imu.gyro.x = (int16)tmp;
}

// Reset the IMU to default settings
void reset_imu(void) 
{
	uint8 config = D_DEVICE_RESET;
	imu_write(IMU_PWR_MGMT_1, &config, 1);
}

//// LOW LEVEL FUNCTIONS /////

//write data to an internal register of the IMU.
// you would use this function if you wanted to set configuration values
// for a particular feature of the IMU.
// uint8_t internal_reg_addr: internal register address of the IMU
// uint8_t* pData: pointer to the data we want to send to that address
// uint16_t Size: amount of bytes of data pointed to by pData

int imu_write(uint8 internal_reg_addr, uint8* pData, uint16 length) 
{
	int i = 0;
	
	i2c_tmp_buf[0] = internal_reg_addr;
	for(i = 1; i < length + 1; i++)
	{
		i2c_tmp_buf[i] = pData[i-1];
	}
		
	I2C_1_MasterWriteBuf(IMU_ADDR, (uint8 *) i2c_tmp_buf, length + 1, I2C_1_MODE_COMPLETE_XFER);

	return 0;
}

//Note: Not as clean as I would like, but functional (see Evernote 01/15/2015)
//Note 2: improved on 02/08/2015. To be tested.
//ToDo: replace delays by register checks
int imu_read(uint8 internal_reg_addr, uint8 *pData,	uint16 length) 
{
	uint8 stat = 0;
	uint8 i = 0;
	
	i2c_tmp_buf[0] = internal_reg_addr;
	I2C_1_MasterClearStatus();
	stat = I2C_1_MasterWriteBuf(IMU_ADDR, (uint8 *) i2c_tmp_buf, 1, I2C_1_MODE_NO_STOP);
	//while(I2C_1_MasterStatus() == I2C_1_MSTAT_XFER_INP);
	CyDelayUs(200);
	
	I2C_1_MasterSendRestart(IMU_ADDR, 1);
	CyDelayUs(200);
	for(i = 0; i < (length-1); i++)
	{
		pData[i] = I2C_1_MasterReadByte(1);	//Ack byte(s)
	}
	pData[i+1] = I2C_1_MasterReadByte(0);	//Nack the last byte
	I2C_1_MasterSendStop();	

	return 0;
}

//Copy of the test code used in main.c to test the hardware:
void imu_test_code_blocking(void)
{
	//IMU test code
	
	uint8 ledg_state = 0;
	int16 imu_accel_x = 0;

	while(1)
	{
		imu_accel_x = get_accel_x();
		send_usb_int16(imu_accel_x);
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(75);		
	}
}
