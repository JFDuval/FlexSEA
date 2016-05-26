//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// ext_input: External Input Devices/Sensors
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "ext_input.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//Encoders:
struct enc_s encoder;
struct as504x_s as5047, as5048b;

//Magnetic encoder, AS5047:
uint16 spidata_mosi[WORDS_IN_FRAME] = {0,0,0,0,0,0,0};
uint16 spidata_miso[WORDS_IN_FRAME] = {0,0,0,0,0,0,0};
uint16 spidata_mosi2[WORDS_IN_FRAME];
uint8 spistatus = 0;
uint16 angleunc = 0;
uint16 as5047_angle = 0;

//Magnetic encoder, AS5048B:
uint8 as5048b_bytes[10] = {0,0,0,0,0,0,0,0,0,0};
uint8 as5048b_agc = 0, as5048b_diag = 0;
uint16 as5048b_mag = 0, as5048b_angle = 0;

//6-ch Strain Amplifier:
uint16 ext_strain[6] = {0,0,0,0,0,0};
uint8 ext_strain_bytes[12];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	

static uint16 add_even_parity_msb(uint16 word);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Initialize the quadrature encoder input (QEI) 
void init_qei(void)
{
	QuadDec_1_Start();
	QuadDec_1_Enable();
	QuadDec_1_SetCounter(QUAD1_INIT);
}

/* Deprecated
//Updates the structure with the latest encoder value
int32 encoder_read(void)
{
	//Count: actual, last, difference
	encoder.count_last = encoder.count;
	encoder.count = QuadDec_1_GetCounter();
	encoder.count_dif = encoder.count - encoder.count_last;
	
	//For the position & impedance controllers we use the last count
	ctrl.position.pos = encoder.count;
	ctrl.impedance.actual_val = encoder.count;
	
	return encoder.count;
}
//Warning: encoder.count seems to be interpreted as a uint... casting (int32) before using it works.
*/

//Updates the structure with the latest encoder value
//Only deals with the Controller encoder (no commutation)
int32 refresh_enc_control(void)
{
	//Count: actual, last, difference
	encoder.count_last = encoder.count;
	
	#if(ENC_CONTROL == ENC_QUADRATURE)
		encoder.count = QuadDec_1_GetCounter();
	#elif(ENC_CONTROL == ENC_ANALOG)
		encoder.count = get_analog_pos();	
	#elif(ENC_CONTROL == ENC_AS5047)
		encoder.count = as5047.angle_cont;
	#elif(ENC_CONTROL == ENC_AS5048B)
		encoder.count = as5048b.angle;
	#endif
		
	encoder.count_dif = encoder.count - encoder.count_last;
	
	//For the position & impedance controllers we use the last count
	ctrl.position.pos = encoder.count;
	ctrl.impedance.actual_val = encoder.count;
	
	return encoder.count;
}
//Warning: encoder.count seems to be interpreted as a uint... casting (int32) before using it works.

//Encoder displayed in the GUI
int32 refresh_enc_display(void)
{
	int32 tmp_enc = 0;
	
	#if(ENC_DISPLAY == ENC_QUADRATURE)
		tmp_enc = QuadDec_1_GetCounter();
	#elif(ENC_DISPLAY == ENC_ANALOG)
		tmp_enc = get_analog_pos();
	#elif(ENC_DISPLAY == ENC_AS5047)
		tmp_enc = as5047.angle_cont;
	#elif(ENC_DISPLAY == ENC_AS5048B)
		tmp_enc = as5048b.angle;
	#endif
	
	return tmp_enc;
}

void qei_write(int32 enc)
{
	#ifdef USE_QEI
	//encoder.count = enc;
	QuadDec_1_SetCounter(enc);
	#endif
}

int32 qei_read(void)
{
	int32 retval = 0;
	
	#ifdef USE_QEI
	retval = QuadDec_1_GetCounter();
	#endif
	
	return retval;
}

void init_as5047(void)
{
	//Init SPIM module:
    SPIM_1_Start();
}

//Read a single word
uint16 as5047_read_single(uint16 reg)
{
	//Clear buffers to start in a known state:
	SPIM_1_ClearTxBuffer();
	SPIM_1_ClearRxBuffer();
    CyDelayUs(10);

	//Send 1st byte (reg addr)
	spidata_mosi2[0] = add_even_parity_msb(AS5047_READ | reg);
	SPIM_1_PutArray(spidata_mosi2, 1);	
	CyDelayUs(10);
    spidata_miso[0] = SPIM_1_ReadRxData();
	
	//Send 2nd byte (empty, used to read)
	spidata_mosi2[0] = add_even_parity_msb(AS5047_READ | AS5047_REG_NOP);
	SPIM_1_PutArray(spidata_mosi2, 1);	
	CyDelayUs(10);
    spidata_miso[1] = SPIM_1_ReadRxData();	
	
	//spidata_miso[1] contains the answer. Remove parity and return value
	//ToDo: ignore word if wrong parity

	last_as5047_word = (spidata_miso[1] & 0x3FFF);
	as5047_angle = last_as5047_word;
	return last_as5047_word;
}

//Reassembles the bytes we read in words
void strain_6ch_bytes_to_words(uint8 *buf)
{
	ext_strain[0] = ((((uint16)buf[0] << 8) & 0xFF00) | (uint16)buf[1]);
	ext_strain[1] = ((((uint16)buf[2] << 8) & 0xFF00) | (uint16)buf[3]);
	ext_strain[2] = ((((uint16)buf[4] << 8) & 0xFF00) | (uint16)buf[5]);
	ext_strain[3] = ((((uint16)buf[6] << 8) & 0xFF00) | (uint16)buf[7]);
	ext_strain[4] = ((((uint16)buf[8] << 8) & 0xFF00) | (uint16)buf[9]);
	ext_strain[5] = ((((uint16)buf[10] << 8) & 0xFF00) | (uint16)buf[11]);
}

//Get latest readings from the 6-ch strain sensor
void get_6ch_strain(void) 
{
	i2c0_read(I2C_SLAVE_ADDR_6CH, MEM_R_CH1_H, ext_strain_bytes, 12);
	//strain_6ch_bytes_to_words();
}

//Get latest readings from the AS5048B position sensor
void get_as5048b_position(void) 
{
	i2c0_read(I2C_ADDR_AS5048B, AD5048B_REG_ANGLE_H, as5048b_bytes, 2);
}

//Converts from ADC reading to position
int16 get_analog_pos(void)
{
	int16 retval = 0;
	
	#if(ACTIVE_PROJECT == PROJECT_CSEA_KNEE)
		retval = -((int16)adc1_res_filtered[0] - CSEA_FULL_EXT_RAW);
		return retval;
	#else
		return 0;
	#endif
}


//****************************************************************************
// Private Function(s)
//****************************************************************************

//When writing to the AS5047, MSB has to be an Even parity bit
static uint16 add_even_parity_msb(uint16 word)
{
	uint16 ret = 0;
	
	//__builtin_parity() returns 0 for even, 1 for odd
	// MSB = 1 when it's odd
	if(__builtin_parity((int)word))
	{
		ret = (word | PARITY_1);
	}
	else
	{
		ret = (word & PARITY_0);
	}
	
	return ret;
}

//****************************************************************************
// Test Function(s) - Use with care!
//****************************************************************************

void as5047_test_code_blocking(void)
{
    //uint8 i = 0;
   
    //Init SPIM module:
    SPIM_1_Start();
    CyDelay(10);   
	
    //Build the mosi packet:
    spidata_mosi[0] = add_even_parity_msb(AS5047_READ | AS5047_REG_ERRFL);
    spidata_mosi[1] = add_even_parity_msb(AS5047_READ | AS5047_REG_PROG);
    spidata_mosi[2] = add_even_parity_msb(AS5047_READ | AS5047_REG_DIAAGC);
    spidata_mosi[3] = add_even_parity_msb(AS5047_READ | AS5047_REG_MAG);
    spidata_mosi[4] = add_even_parity_msb(AS5047_READ | AS5047_REG_ANGLEUNC);
    spidata_mosi[5] = add_even_parity_msb(AS5047_READ | AS5047_REG_ANGLECOM);
    spidata_mosi[6] = add_even_parity_msb(AS5047_READ | AS5047_REG_NOP);
    
    while(1)
    {
		//Read all the fields:
		/*
		SPIM_1_ClearTxBuffer();
		SPIM_1_ClearRxBuffer();
        CyDelay(1);
       
        for(i = 0; i < WORDS_IN_FRAME ; i++)
        {
			spidata_mosi2[0] = spidata_mosi[i];
			SPIM_1_PutArray(spidata_mosi2, 1);
			
			CyDelayUs(15);
            spidata_miso[i] = SPIM_1_ReadRxData();
        }
        CyDelay(4);
       
        //Notes: delays only present for early debugging. Minimize/remove.
       
        //We could commutate the motor here.
		*/
		
		//Single word:
		angleunc = as5047_read_single(AS5047_REG_ANGLEUNC);
    }
}

void strain_amp_6ch_test_code_blocking(void)
{
	while(1)
	{
		i2c0_read(I2C_SLAVE_ADDR_6CH, MEM_R_CH1_H, ext_strain_bytes, 12);
		strain_6ch_bytes_to_words(ext_strain_bytes);
		CyDelay(100);
	}
}

void as5048b_test_code_blocking(void)
{
	while(1)
	{
		i2c0_read(I2C_ADDR_AS5048B, AD5048B_REG_AGC, as5048b_bytes, 6);
		
		as5048b_agc = as5048b_bytes[0];
		as5048b_diag = as5048b_bytes[1] & 0x0F;
		as5048b_mag = (as5048b_bytes[2]<<6) + (as5048b_bytes[3]&0x3F); 
		as5048b_angle = (as5048b_bytes[4]<<6) + (as5048b_bytes[5]&0x3F);
		
		CyDelay(100);
	}
}
