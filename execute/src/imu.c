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
// Variable(s)
//****************************************************************************

uint8 i2c_tmp_buf[IMU_MAX_BUF_SIZE];
volatile uint8 i2c_r_buf[16];
uint8 imu_last_request = IMU_RQ_GYRO;

struct imu_s imu;

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static void store_imu_data(uint8 newdata[7]);

//****************************************************************************
// Public Function(s)
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
	uint8 tmp_data[7] = {0,0,0,0,0,0};	
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_ACCEL_XOUT_H, tmp_data, 7);	
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
	
	//According to the documentation it's X_H, X_L, Y_H, ...
	imu_read(IMU_GYRO_XOUT_H, tmp_data, 7);
	//Note: reading 6 bytes causes a bad reading on Z ([6] always 0).	
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

//Manual I2C [Write - Restart - Read n bytes] function
//Takes around 90us (400kHz) to run, then the ISR takes care of everything.
int imu_read(uint8 internal_reg_addr, uint8 *pData, uint16 length)
{
	uint8 status = 0, i = 0;
	
	//Currently having trouble detecting the flags to know when data is ready.
	//For now I'll transfer the previous buffer.
	for(i = 0; i < length; i++)
	{
		pData[i] = i2c_r_buf[i];
	}
	
	//Store data:
	store_imu_data(i2c_r_buf);
	
	//Clear status:
	//I2C_1_MasterClearStatus();
	
	//Start, address, Write mode
	status = I2C_1_MasterSendStart(IMU_ADDR, 0);		
	if(status != I2C_1_MSTR_NO_ERROR)
		return 1;
	
	//Write to register
	status = I2C_1_MasterWriteByteTimeOut(internal_reg_addr, 500);
	if(status != I2C_1_MSTR_NO_ERROR)
	{
		//Release bus:
		I2C_1_BUS_RELEASE;
		
		return 2;
	}

	//Repeat start, read then stop (all by ISR):
	I2C_1_MasterReadBuf(IMU_ADDR, (uint8 *)i2c_r_buf, length, (I2C_1_MODE_COMPLETE_XFER | I2C_1_MODE_REPEAT_START));
	
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

//Simplified version of I2C_1_MasterWriteByte() (single master only) with timeouts
//timeout is in us
uint8 I2C_1_MasterWriteByteTimeOut(uint8 theByte, uint32 timeout)
{
    uint8 errStatus;
	uint32 t = 0;	//For the timeout

    errStatus = I2C_1_MSTR_NOT_READY;

    /* Check if START condition was generated */
    if(I2C_1_CHECK_MASTER_MODE(I2C_1_MCSR_REG))
    {
        I2C_1_DATA_REG = theByte;                        /* Write DATA register */
		t = 0;
		
		
        //I2C_1_TRANSMIT_DATA_MANUAL_TIMEOUT;                      /* Set transmit mode */
		
        I2C_1_TRANSMIT_DATA;								
        while(I2C_1_CHECK_BYTE_COMPLETE(I2C_1_CSR_REG))		
        {													
            /* Wait when byte complete is cleared */		
			t++;											
			if(t > timeout)									
				break;										
			else											
				CyDelayUs(1);								
        }	
		
		
        I2C_1_state = I2C_1_SM_MSTR_WR_DATA;  /* Set state WR_DATA */

        /* Make sure the last byte has been transfered first */
		t = 0;
        while(I2C_1_WAIT_BYTE_COMPLETE(I2C_1_CSR_REG))
        {
			/*
           //Wait for byte to be written
			t++;
			if(t > timeout)	
				break;
			else
				CyDelayUs(1);
			*/
        }


        if(I2C_1_CHECK_DATA_ACK(I2C_1_CSR_REG))
        {
            I2C_1_state = I2C_1_SM_MSTR_HALT;     /* Set state to HALT */
            errStatus = I2C_1_MSTR_NO_ERROR;                 /* The LRB was ACKed */
        }
        else
        {
            I2C_1_state = I2C_1_SM_MSTR_HALT;     /* Set state to HALT */
            errStatus = I2C_1_MSTR_ERR_LB_NAK;               /* The LRB was NACKed */
        }
    }

    return(errStatus);
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//Associate data with the right structure
static void store_imu_data(uint8 newdata[7])
{
	uint16 tmp = 0;
	
	if(imu_last_request == IMU_RQ_GYRO)
	{
		//Gyro X:
		tmp = ((uint16)newdata[0] << 8) | ((uint16) newdata[1]);
		imu.gyro.x = (int16)tmp;
		
		//Gyro Y:
		tmp = ((uint16)newdata[2] << 8) | ((uint16) newdata[3]);
		imu.gyro.y = (int16)tmp;
		
		//Gyro Z:
		tmp = ((uint16)newdata[4] << 8) | ((uint16) newdata[5]);
		imu.gyro.z = (int16)tmp;		
	}
	else if(imu_last_request == IMU_RQ_ACCEL)
	{
		//Accel X:
		tmp = ((uint16)newdata[0] << 8) | ((uint16) newdata[1]);
		imu.accel.x = (int16)tmp;
		
		//Accel Y:
		tmp = ((uint16)newdata[2] << 8) | ((uint16) newdata[3]);
		imu.accel.y = (int16)tmp;
		
		//Accel Z:
		tmp = ((uint16)newdata[4] << 8) | ((uint16) newdata[5]);
		imu.accel.z = (int16)tmp;		
	}
}
