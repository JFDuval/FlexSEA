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

//Encoder:
struct enc_s encoder;

//Magnetic encoder, AS5047:
uint16 spidata_mosi[WORDS_IN_FRAME] = {0,0,0,0,0,0,0};
uint16 spidata_miso[WORDS_IN_FRAME] = {0,0,0,0,0,0,0};
uint16 spidata_mosi2[WORDS_IN_FRAME];
uint8 spistatus = 0;
uint16 angleunc = 0;

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

//Updates the structure with the desired value and write it to the encoder
void encoder_write(int32 enc)
{
	encoder.count = enc;
	QuadDec_1_SetCounter(enc);
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
	return last_as5047_word;
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
    uint8 i = 0;
   
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

