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

struct imu_s imu;

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
	//while(I2C_1_MasterStatus() != I2C_1_MSTAT_WR_CMPLT);
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
	imu.accel.y = (int16)tmp;
	
	//Accel Z:
	tmp = ((uint16)tmp_data[4] << 8) | ((uint16) tmp_data[5]);
	imu.accel.z = (int16)tmp;
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
	uint8 tmp_data[7] = {0,0,0,0,0,0, 0};
	uint16 tmp = 0;
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_GYRO_XOUT_H, tmp_data, 7);
	//Note: reading 6 bytes causes a bad reading on Z ([6] always 0).
	
	//Gyro X:
	tmp = ((uint16)tmp_data[0] << 8) | ((uint16) tmp_data[1]);
	imu.gyro.x = (int16)tmp;
	
	//Gyro Y:
	tmp = ((uint16)tmp_data[2] << 8) | ((uint16) tmp_data[3]);
	imu.gyro.y = (int16)tmp;
	
	//Gyro Z:
	tmp = ((uint16)tmp_data[4] << 8) | ((uint16) tmp_data[5]);
	imu.gyro.z = (int16)tmp;
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
	uint8_t stat = 0;
	
	i2c_tmp_buf[0] = internal_reg_addr;
	for(i = 1; i < length + 1; i++)
	{
		i2c_tmp_buf[i] = pData[i-1];
	}
	
	//Try to write it up to 5 times
	for(i = 0; i < 5; i++)
	{
		stat = I2C_1_MasterWriteBuf(IMU_ADDR, (uint8 *) i2c_tmp_buf, length + 1, I2C_1_MODE_COMPLETE_XFER);
		
		if(stat == I2C_1_MSTR_NO_ERROR)
		{
			break;
		}
		
		CyDelay(10);
	}

	return 0;
}

//Manual I2C [Write - Restart - Read n] function
int imu_read(uint8 internal_reg_addr, uint8 *pData, uint16 length)
{
	uint8 status = 0, i = 0;
	
	//Start, address, Write mode
	status = I2C_1_MasterSendStart(IMU_ADDR, 0);		
	if(status != I2C_1_MSTR_NO_ERROR)
		return 1;
	
	//Write to register
	status = I2C_1_MasterWriteByte(internal_reg_addr);
	if(status != I2C_1_MSTR_NO_ERROR)
		return 2;
	
	//Restart, address, Read mode
	status = I2C_1_MasterSendRestart(IMU_ADDR, 1);		
	if(status != I2C_1_MSTR_NO_ERROR)
		return 3;
	
	//Read 'length' bytes:
	for(i = 0; i < (length-1); i++)
	{
		pData[i] = I2C_1_MasterReadByte(1);	//Ack byte(s)
	}
	pData[i+1] = I2C_1_MasterReadByte(0);	//Nack the last byte
	
	//Send stop
	/*
	status = I2C_1_MasterSendStop();
	if(status != I2C_1_MSTR_NO_ERROR)
		return 4;
	*/
	//I2C_1_MasterSendStop() is blocking, and it blocked me every few seconds. This seems to work better:
	I2C_1_GENERATE_STOP_MANUAL;		//Generate STOP
    I2C_1_state = I2C_1_SM_IDLE;	//Reset state to IDLE
	//Scopped the bus, all clean.
	
	return 0;
}

//Copy of the test code used in main.c to test the hardware:
void imu_test_code_blocking(void)
{
	//IMU test code
	
	uint8 ledg_state = 0;
	int16 imu_accel_x = 0;

	/*
	//Single channel test:
	while(1)
	{
		imu_accel_x = get_accel_x();
		send_usb_int16(imu_accel_x);
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(75);		
	}
	*/
	
	// 3 channels test (only one displayed)
	while(1)
	{
		get_accel_xyz();
		//get_gyro_xyz();
		#ifdef USE_USB
		send_usb_int16(imu.gyro.z);
		#endif	//USE_USB
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		CyDelay(75);		
	}
}
