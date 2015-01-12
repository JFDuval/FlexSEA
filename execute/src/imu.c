//****************************************************************************
// MIT Media Lab - Biomechatronics
// Erin Main & JFDuval
// ermain@mit.edu, jfduval@mit.edu
// 01/2015
//****************************************************************************
// imu: I2C IMU (MPU-6500)
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <project.h>
#include "imu.h"
#include "main.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

uint8 i2c_tmp_buf[IMU_MAX_BUF_SIZE];

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
	int i = 0;

	//Reset the IMU
	reset_imu();
	while(I2C_1_MasterStatus() != I2C_1_MSTAT_WR_CMPLT);
	//ToDo: add a timeout
	
	// Initialize the config registers.
	uint8_t config[4] = { D_IMU_CONFIG, D_IMU_GYRO_CONFIG, D_IMU_ACCEL_CONFIG, D_IMU_ACCEL_CONFIG2 };
	
	//Send the config sequence
	imu_write(IMU_CONFIG, &config, 4);
	while(I2C_1_MasterStatus() != I2C_1_MSTAT_WR_CMPLT);
	//ToDo: add a timeout
}

// Get accel X
uint16 get_accel_x(void) {
	uint8_t data[2] = { 0, 0 };
	imu_read(IMU_ACCEL_XOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}
// Get accel Y
uint16 get_accel_y(void) {
	uint8_t data[2];
	imu_read(IMU_ACCEL_YOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get accel Z
uint16 get_accel_z(void) {
	uint8_t data[2];
	imu_read(IMU_ACCEL_ZOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro X
uint16 get_gyro_x(void) {
	uint8_t data[2];
	imu_read(IMU_GYRO_XOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro Y
uint16 get_gyro_y(void) {
	uint8_t data[2];
	imu_read(IMU_GYRO_YOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro Z
uint16 get_gyro_z(void) {
	uint8_t data[2];
	imu_read(IMU_GYRO_ZOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Reset the IMU to default settings
void reset_imu(void) {
	uint8_t config = D_DEVICE_RESET;
	imu_write(IMU_PWR_MGMT_1, &config, 1);
}

//// LOW LEVEL FUNCTIONS /////

//write data to an internal register of the IMU.
// you would use this function if you wanted to set configuration values
// for a particular feature of the IMU.
// uint8_t internal_reg_addr: internal register address of the IMU
// uint8_t* pData: pointer to the data we want to send to that address
// uint16_t Size: amount of bytes of data pointed to by pData

/* STM32F4 functions as a reference:
HAL_StatusTypeDef imu_write(uint8_t internal_reg_addr, uint8_t* pData,
		uint16_t Size) {
	return HAL_I2C_Mem_Write(&hi2c1, IMU_ADDR, (uint16_t) internal_reg_addr,
			I2C_MEMADD_SIZE_8BIT, pData, Size, IMU_BLOCK_TIMEOUT);
}

//read data from an internal register of the IMU.
// you would use this function if you wanted to read data from the IMU.
// uint8_t internal_reg_addr: internal register address of the IMU
// uint8_t* pData: pointer to where we want to save the data from the IMU
// uint16_t Size: amount of bytes we want to read
HAL_StatusTypeDef imu_read(uint8_t internal_reg_addr, uint8_t *pData,
		uint16_t Size) {
	return HAL_I2C_Mem_Read(&hi2c1, IMU_ADDR, (uint16_t) internal_reg_addr,
			I2C_MEMADD_SIZE_8BIT, pData, Size, IMU_BLOCK_TIMEOUT);
}
*/

int imu_write(uint8 internal_reg_addr, uint8* pData, uint16 Size) 
{
	int i = 0;
	
	i2c_tmp_buf[0] = internal_reg_addr;
	for(i = 1; i < Size + 1; i++)
	{
		i2c_tmp_buf[i] = pData[i-1];
	}
		
	I2C_1_MasterWriteBuf(IMU_ADDR, (uint8 *) i2c_tmp_buf, Size + 1, I2C_1_MODE_COMPLETE_XFER);

	return 0;
}

//Note: Not as clean as I would like, but functional (see Evernote 01/15/2015)
//ToDo: change some delays by register checks
int imu_read(uint8 internal_reg_addr, uint8 *pData,	uint16 Size) 
{
	uint8 stat = 0;
	uint8 test[8] = {1,1,1,1,1,1,1,1};
	
	i2c_tmp_buf[0] = internal_reg_addr;
	I2C_1_MasterClearStatus();
	stat = I2C_1_MasterWriteBuf(IMU_ADDR, (uint8 *) i2c_tmp_buf, 1, I2C_1_MODE_NO_STOP);
	//while(I2C_1_MasterStatus() == I2C_1_MSTAT_XFER_INP);
	CyDelayUs(200);
	
	I2C_1_MasterSendRestart(IMU_ADDR, 1);
	CyDelayUs(200);
	test[0] = I2C_1_MasterReadByte(1);	//Ack
	test[1] = I2C_1_MasterReadByte(0);	//Nack
	I2C_1_MasterSendStop();
	
	//Data to be returned
	pData[0] = test[0];
	pData[1] = test[1];
	
	return 0;
}
