//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// safety: Safety-CoP & safety-related functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "safety.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

struct scop safety_cop;
volatile uint8 i2c_1_r_buf[24];
uint8 safety_cop_data[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//****************************************************************************
// Function(s)
//****************************************************************************

//Update the global variables from the array
void decode_psoc4_values(uint8 *psoc4_data)
{
	safety_cop.v_vb = psoc4_data[MEM_R_VB_SNS];
	safety_cop.v_vg = psoc4_data[MEM_R_VG_SNS];
	safety_cop.v_3v3 = psoc4_data[MEM_R_3V3_SNS];
	safety_cop.temperature = psoc4_data[MEM_R_TEMPERATURE];
	safety_cop.status1 = psoc4_data[MEM_R_STATUS1];
	safety_cop.status2 = psoc4_data[MEM_R_STATUS2];
}

//Returns the die temperature.
//ToDo deal with the active_error, or replace with better code
int16 dietemp_read(void)
{
	#ifdef USE_DIETEMP

	static cystatus dietemp = 0;
	int16 temp = 0;	
	uint8 active_error = 0;
				
	//Die temperature too high?
	dietemp = DieTemp_1_Query(&temp);
	if(dietemp == CYRET_SUCCESS)
	{
		DieTemp_1_Start(); 		// start next temp reading
		if(temp > MAX_DIE_TEMP)
			active_error = 1;
		else
			active_error = 0;
	} 
	else if(dietemp == (CYRET_TIMEOUT))
	{
		DieTemp_1_Start(); 		// start next temp reading
	}
	
	return temp;
	
	#else
		
		return 0;
			
	#endif	//USE_DIETEMP		
}

//Manual I2C [Write - Restart - Read n bytes] function
//Takes around xus (400kHz) to run, then the ISR takes care of everything.
int safety_cop_read(uint8 internal_reg_addr, uint8 *pData, uint16 length)
{
	uint8 status = 0, i = 0;
	
	//Currently having trouble detecting the flags to know when data is ready.
	//For now I'll transfer the previous buffer.
	for(i = 0; i < length; i++)
	{
		pData[i] = i2c_1_r_buf[i];
	}
	
	//Clear status:
	//I2C_1_MasterClearStatus();
	
	//Start, address, Write mode
	status = I2C_1_MasterSendStart(SCOP_I2C_ADDR, 0);		
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
	I2C_1_MasterReadBuf(SCOP_I2C_ADDR, (uint8 *)i2c_1_r_buf, length, (I2C_1_MODE_COMPLETE_XFER | I2C_1_MODE_REPEAT_START));
	
	return 0;
}

void safety_cop_get_status(void)
{
	uint8 tmp_buf[4] = {0,0,0,0};
	
	safety_cop_read(MEM_R_STATUS1, tmp_buf, 3);
}

//Reads the most important values, total of 7 bytes
//MEM_R_STATUS1, MEM_R_STATUS2, MEM_R_VB_SNS, MEM_R_VG_SNS, MEM_R_5V_SNS, MEM_R_3V3_SNS & MEM_R_TEMPERATURE
void safety_cop_read_all(void)
{
	uint8 tmp_buf[8] = {0,0,0,0,0,0,0,0};
	uint8 i = 0;
	
	safety_cop_read(MEM_R_STATUS1, tmp_buf, 8);
	
	for(i = MEM_R_STATUS1; i < MEM_R_STATUS1 + 8; i++)
	{
		safety_cop_data[i] = tmp_buf[i - MEM_R_STATUS1];
	}	
	
	decode_psoc4_values(safety_cop_data);
}

void status_error_codes(uint8 sts1, uint8 sts2, uint8 *l0, uint8 *l1, uint8 *l2)
{
	uint8 tmp_l0 = 0, tmp_l1 = 0, tmp_l2 = 0;
	
	//L0 is Yellow, L1 is Red and L2 is (latching) flashing Red
	//STATUS1 = [WDCLK, DISCON, TMPH, TMPL, VBH, VBL, VGH, VGL]
	//STATUS2 = [0, 0, 0, 0, 0, 0, 3V3H, 3V3L]

	//3V3 and VG => L0
	//VB, WDCLK & Temp Warning => L1
	//Temp high and disconnect => L2
	
	tmp_l0 = ((sts1 & 0b11) | (sts2 & 0b11));
	tmp_l1 = (((sts1 & 0b1100) >> 2) | ((sts1 & 0b010000) >> 4) | ((sts1 & 0b10000000) >> 7));
	tmp_l2 = ((sts1 & 0b01100000) >> 5);
	
	if(tmp_l0)
	{
		*l0 = 1;
	}
	else
	{
		*l0 = 0;
	}
	
	if(tmp_l1)
	{
		*l1 = 1;
	}
	else
	{
		*l1 = 0;
	}
	
	if(tmp_l2)
	{
		*l2 = 1;
	}
	else
	{
		*l2 = 0;
	}
}

void overtemp_error(uint8 *eL1, uint8 *eL2)
{
	uint8 temp_status = 0;
	static uint8 err_cnt = 0;
	temp_status = GET_OVERTEMP_FLAG(safety_cop.status1);
	
	if(temp_status == T_WARNING)
	{
		(*eL1) = 1;
		(*eL2) = 0;
	}
	else if(temp_status == T_ERROR)
	{
		err_cnt++;
		if(err_cnt > 25)
		{
			(*eL1) = 0;
			(*eL2) = 1;
			
			//Override PWM:
			motor_open_speed_1(0);
		}
	}
	else
	{
		err_cnt = 0;
		(*eL1) = 0;
		(*eL2) = 0;
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
// Test Function(s) - Use with care!
//****************************************************************************

//Copy of the test code used in main.c to test the hardware:
void safety_cop_comm_test_blocking(void)
{
	//PSoC 4 <=> PSoC 5 I2C Test code
	
	uint8 i2c_test_wbuf[9];
	uint8 i2c_test_rbuf[24];
	uint8 ledg_state = 0;
	
	while(1)
	{
		//Write to slave:
		//I2C_1_MasterWriteBuf(0x11, (uint8 *) i2c_test_wbuf, 9, I2C_1_MODE_COMPLETE_XFER);
		
		//Read from slave:
		i2c_test_wbuf[0] = 0;
		I2C_1_MasterWriteBuf(SCOP_I2C_ADDR, (uint8 *) i2c_test_wbuf, 1, I2C_1_MODE_COMPLETE_XFER);	//Write offset
		CyDelayUs(500);
		I2C_1_MasterReadBuf(SCOP_I2C_ADDR, i2c_test_rbuf, 24, I2C_1_MODE_COMPLETE_XFER);
		CyDelayUs(500);
		decode_psoc4_values(i2c_test_rbuf);
		
		ledg_state ^= 1;
		LED_G_Write(ledg_state);
		
		//Yellow when there is an error:
		if(safety_cop.status1)
		{
			LED_R_Write(ledg_state);
		}
		else
		{
			LED_R_Write(0);
		}
		
		CyDelay(250);	
	}
}

void wdclk_test_blocking(void)
{
	uint8 toggle_wdclk = 0;
	
	while(1)
	{
		toggle_wdclk ^= 1;
		WDCLK_Write(toggle_wdclk);
		CyDelayUs(1200);
	}
}
