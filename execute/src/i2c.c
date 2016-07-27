//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
//****************************************************************************
// i2c: I2C functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "i2c.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 i2c_last_request = 0;
volatile uint8 i2c_0_r_buf[24];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	


//****************************************************************************
// Public Function(s)
//****************************************************************************

void i2c_0_fsm(void)
{
	static uint8 i2c_time_share = 0;
	static uint8 minm_i2c = 0;
	
	i2c_time_share++;
	i2c_time_share %= 4;

	#ifdef USE_I2C_0 

	//Subdivided in 4 slots (250Hz)
	switch(i2c_time_share)
	{
		//Case 0.0: Accelerometer
		case 0:
		
			#ifdef USE_IMU							
			get_accel_xyz();
			i2c_last_request = I2C_RQ_ACCEL;
			#endif 	//USE_IMU
		
			break;
		
		//Case 0.1: Gyroscope
		case 1:
			
			#ifdef USE_IMU							
			get_gyro_xyz();		
			i2c_last_request = I2C_RQ_GYRO;
			#endif 	//USE_IMU
			
			break;
		
		//Case 0.2: AS5048B position sensor
		case 2:
			#ifdef USE_AS5048B
			get_as5048b_position();
			i2c_last_request = I2C_RQ_AS5048B;		
			#endif //USE_AS5048B
			break;
		
		//Case 0.3: MinM RGB LED & external strain amplifier
		case 3:
			
			//I2C RGB LED
			#ifdef USE_MINM_RGB
			//minm_test_code();	
			minm_i2c = update_minm_rgb();
			#else
			minm_i2c = 0;	
			#endif 	//USE_MINM_RGB
			
			//External strain gauge amplifier
			#ifdef USE_EXT_I2C_STRAIN
			if(!minm_i2c)
			{
				//If the MinM was refreshed we skip one measurement.
				get_6ch_strain();
				i2c_last_request = I2C_RQ_EXT_STRAIN;
			}
			#endif //USE_EXT_I2C_STRAIN
			
			//Battery Board -- ToDo clean & unify solution (this is a quick test)
			get_battery_board();
			i2c_last_request = I2C_RQ_BATT_BOARD;			
			
			break;
		
		default:
			break;
	}
	
	#endif //USE_I2C_0
}

//I2C0 - 3V3, IMU & Expansion.
void init_i2c_0(void)
{
	I2C_0_EnableInt();
	I2C_0_Start();	
}

//I2C1 - 5V, Safety-CoP & strain gauge pot
void init_i2c_1(void)
{
	I2C_1_EnableInt();
	I2C_1_Start();
}

//Manual I2C [Write - Restart - Read n bytes] function
//Takes around xus (400kHz) to run, then the ISR takes care of everything.
int i2c0_read(uint8 slave_addr, uint8 reg_addr, uint8 *pdata, uint16 length)
{
	uint8 status = 0, i = 0;
	
	//Currently having trouble detecting the flags to know when data is ready.
	//For now I'll transfer the previous buffer.
	for(i = 0; i < length; i++)
	{
		pdata[i] = i2c_0_r_buf[i];
	}
	
	//Store data:
	assign_i2c_data(&i2c_0_r_buf);
	
	//Clear status:
	//I2C_0_MasterClearStatus();
	
	//Start, address, Write mode
	status = I2C_0_MasterSendStart(slave_addr, 0);		
	if(status != I2C_0_MSTR_NO_ERROR)
		return 1;
	
	//Write to register
	status = I2C_0_MasterWriteByteTimeOut(reg_addr, 500);
	if(status != I2C_0_MSTR_NO_ERROR)
	{
		//Release bus:
		I2C_0_BUS_RELEASE;
		
		return 2;
	}

	//Repeat start, read then stop (all by ISR):
	I2C_0_MasterReadBuf(slave_addr, (uint8 *)i2c_0_r_buf, length, (I2C_0_MODE_COMPLETE_XFER | I2C_0_MODE_REPEAT_START));
	
	return 0;
}

//Simplified version of I2C_0_MasterWriteByte() (single master only) with timeouts
//timeout is in us
uint8 I2C_0_MasterWriteByteTimeOut(uint8 theByte, uint32 timeout)
{
    uint8 errStatus;
	uint32 t = 0;	//For the timeout

    errStatus = I2C_0_MSTR_NOT_READY;

    /* Check if START condition was generated */
    if(I2C_0_CHECK_MASTER_MODE(I2C_0_MCSR_REG))
    {
        I2C_0_DATA_REG = theByte;                        /* Write DATA register */
		t = 0;
		
		
        //I2C_0_TRANSMIT_DATA_MANUAL_TIMEOUT;                      /* Set transmit mode */
		
        I2C_0_TRANSMIT_DATA;								
        while(I2C_0_CHECK_BYTE_COMPLETE(I2C_0_CSR_REG))		
        {													
            /* Wait when byte complete is cleared */		
			t++;											
			if(t > timeout)									
				break;										
			else											
				CyDelayUs(1);								
        }	
		
		
        I2C_0_state = I2C_0_SM_MSTR_WR_DATA;  /* Set state WR_DATA */

        /* Make sure the last byte has been transfered first */
		t = 0;
        while(I2C_0_WAIT_BYTE_COMPLETE(I2C_0_CSR_REG))
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


        if(I2C_0_CHECK_DATA_ACK(I2C_0_CSR_REG))
        {
            I2C_0_state = I2C_0_SM_MSTR_HALT;     /* Set state to HALT */
            errStatus = I2C_0_MSTR_NO_ERROR;                 /* The LRB was ACKed */
        }
        else
        {
            I2C_0_state = I2C_0_SM_MSTR_HALT;     /* Set state to HALT */
            errStatus = I2C_0_MSTR_ERR_LB_NAK;               /* The LRB was NACKed */
        }
    }

    return(errStatus);
}

//Associate data with the right structure. We need that because of the way the ISR-based
//I2C works (we always get data from the last request)
void assign_i2c_data(uint8 *newdata)
{
	uint16 tmp = 0;
	
	if(i2c_last_request == I2C_RQ_GYRO)
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
	else if(i2c_last_request == I2C_RQ_ACCEL)
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
	else if(i2c_last_request == I2C_RQ_AS5048B)
	{
			as5048b.angle_raw = (newdata[0]<<6) + (newdata[1]&0x3F);
			as5048b.angle_ctrl = CTRL_ENC_FCT(as5048b.angle_raw);
	}
	else if(i2c_last_request == I2C_RQ_EXT_STRAIN)
	{
		strain_6ch_bytes_to_words(newdata);
	}	
	else if(i2c_last_request == I2C_RQ_BATT_BOARD)
	{
		decode_battery_board(newdata);
	}
}



//****************************************************************************
// Private Function(s)
//****************************************************************************


//****************************************************************************
// Test Function(s) - Use with care!
//****************************************************************************
