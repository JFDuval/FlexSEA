//****************************************************************************
// MIT Media Lab - Biomechatronics
// Erin Main
// ermain@mit.edu
// 10/2014
//****************************************************************************
// fm_i2c: I2C IMU (MPU-6500)
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_i2c.h"
#include "fm_imu.h"
#include "fm_i2c.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************


//****************************************************************************
// External variable(s)
//****************************************************************************

extern I2C_HandleTypeDef hi2c1;

//****************************************************************************
// Function(s)
//****************************************************************************

//// HIGH LEVEL FUNCTIONS ////
// Initialize the IMU w/ default values in config registers
void init_imu() {

	// Reset the IMU.
	reset_imu();
	// Initialize the config registers.
	uint8_t config[4] = { D_IMU_CONFIG, D_IMU_GYRO_CONFIG, D_IMU_ACCEL_CONFIG,
			D_IMU_ACCEL_CONFIG2 };
	uint8_t imu_addr = IMU_CONFIG;
	for (int i = 0; i < 4; i++) {
		imu_write(imu_addr + i, &config[i], 1);
	}
}

// Get accel X
uint16_t get_accel_x(void) {
	uint8_t data[2] = { 0, 0 };
	imu_read(IMU_ACCEL_XOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}
// Get accel Y
uint16_t get_accel_y(void) {
	uint8_t data[2];
	imu_read(IMU_ACCEL_YOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get accel Z
uint16_t get_accel_z(void) {
	uint8_t data[2];
	imu_read(IMU_ACCEL_ZOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro X
uint16_t get_gyro_x(void) {
	uint8_t data[2];
	imu_read(IMU_GYRO_XOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro Y
uint16_t get_gyro_y(void) {
	uint8_t data[2];
	imu_read(IMU_GYRO_YOUT_H, data, 2);
	return ((uint16_t) data[0] << 8) | (data[1]);
}

// Get gyro Z
uint16_t get_gyro_z(void) {
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
