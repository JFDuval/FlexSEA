//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval, Luke Mooney & Jake Mooney
// jfduval@media.mit.edu, lmooney@mit.edu, mooneyj@mit.edu
// 05/2016
//****************************************************************************
// sensor_commut: Angle Sensor Motor Commutation
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "sensor_commut.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 hall_conv[6] = {5,4,6,2,3,1};
//uint16 anglemap[126] = {109,250,378,517,656,782,911,1045,1177,1306,1453,1580,1711,1846,1968,2101,2239,2372,2502,2635,2758,2882,3022,3144,3280,3413,3535,3658,3789,3914,4040,4179,4303,4424,4558,4672,4802,4933,5064,5188,5319,5437,5558,5694,5818,5951,6085,6203,6328,6458,6586,6713,6856,6981,7107,7243,7363,7496,7635,7769,7902,8038,8164,8289,8434,8562,8703,8843,8970,9098,9236,9367,9500,9647,9778,9906,10047,10165,10301,10438,10574,10705,10841,10963,11087,11226,11352,11489,11625,11745,11872,12000,12127,12253,12396,12519,12644,12776,12892,13019,13154,13283,13410,13539,13661,13779,13916,14036,14171,14304,14425,14549,14679,14801,14929,15071,15196,15323,15458,15574,15707,15843,15977,16107,16244,16367};
//uint16 anglemap[126] = {5,109,252,385,510,637,765,928,1033,1174,1298,1432,1554,1681,1843,1944,2080,2216,2337,2457,2583,2743,2842,2982,3107,3232,3353,3478,3635,3737,3873,3993,4125,4246,4370,4530,4629,4766,4887,5018,5139,5264,5423,5523,5662,5781,5914,6041,6165,6327,6432,6572,6690,6832,6959,7087,7255,7362,7503,7631,7770,7900,8031,8200,8307,8458,8584,8720,8853,8980,9145,9255,9400,9523,9661,9792,9913,10078,10182,10321,10445,10580,10706,10828,10987,11090,11227,11350,11480,11610,11729,11885,11988,12123,12241,12377,12502,12622,12778,12880,13012,13134,13264,13389,13510,13666,13767,13902,14019,14152,14279,14400,14557,14662,14796,14917,15053,15178,15302,15468,15570,15707,15837,15970,16093,16224};
uint16 anglemap[126] = {53,164,305,436,561,690,814,969,1081,1221,1348,1478,1603,1727,1882,1991,2128,2262,2387,2511,2635,2790,2898,3039,3167,3294,3420,3544,3697,3808,3946,4072,4202,4329,4450,4606,4714,4852,4979,5106,5231,5355,5507,5616,5755,5879,6006,6137,6256,6411,6521,6660,6782,6918,7046,7169,7327,7439,7578,7709,7840,7972,8096,8255,8367,8513,8641,8772,8906,9027,9183,9299,9439,9567,9699,9831,9949,10106,10217,10355,10484,10614,10743,10864,11017,11128,11266,11394,11521,11655,11773,11926,12036,12174,12296,12429,12558,12678,12830,12940,13073,13200,13326,13455,13575,13727,13835,13971,14093,14221,14350,14468,14619,14731,14865,14990,15119,15246,15367,15524,15633,15770,15901,16029,16154,16281};
uint16 polemap[126] = {4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5, 4, 6, 2, 3, 1, 5};
uint8 hallmap_map2[6] = {2, 6, 4, 5, 1, 3};

uint8 hallmap_map[6] = {6, 4, 5, 1, 3, 2};
uint8 findingpoles = 0;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************	


//****************************************************************************
// Public Function(s)
//****************************************************************************

//Use before main while() as a basic test
void motor_stepper_test_blocking_1(int spd)
{
	uint8 hall_code_0 = 0, hall_code = 0;
	
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	//Brake
	motor_open_speed_1(spd);
	
	while(1)
	{
		hall_code_0++;
		hall_code_0 %= 6;
		hall_code = hall_conv[hall_code_0];
		
		Virtual_Hall_Write(hall_code);

		
		LED_R_Write(hall_code & 0x01);
		LED_G_Write((hall_code & 0x02)>>1);
		LED_B_Write((hall_code & 0x04)>>2);
		
		CyDelay(10);
	}
}

//To test with the full stack, use this init...
void motor_stepper_test_init(int spd)
{
	ctrl.active_ctrl = CTRL_OPEN;	
	Coast_Brake_Write(1);	
	motor_open_speed_1(spd);	
}

//...and this runtime function
void motor_stepper_test_runtime(int div)
{
	//Call this function at 1ms intervals. The divider will
	//allow longer delays between steps.
	
	static uint8 hall_code_0 = 0, hall_code = 0;
	static int delay_cnt = 0;
	
	delay_cnt++;
	if(delay_cnt >= div)
	{
		delay_cnt = 0;
	
		hall_code_0++;
		hall_code_0 %= 6;
		hall_code = hall_conv[hall_code_0];
		
		//Hall_Write(hall_code);	//ToDo Enable
	}	
}

//motor commutation with SPI encoder
void motor_spi_block_commutation(int angle)
{
    static int16 lastangle, lastcomindx=1;
    int16 deadband = 10; 
    int16 comindx,tempangle;
    int16 offset;
    
    /*
    //offset = deadband-anglemap[0];
    //angle = angle+offset;
    //angle = angle+(angle-lastangle)/5;
    
    if (lastcomindx==0)
    {
        //tempangle = angle;
        //if (tempangle>16000)
        //{
        //    tempangle = tempangle-16384;
        //}
        if (angle>anglemap[0]+offset+deadband)
        {comindx = 1;}
        else if (angle<anglemap[125]-16384+offset-deadband)
        {comindx = 5;}
        else
        {comindx = 0;}
    }
    else
    {
        int16 lo=0, hi = 126, mid=0;
        while (lo<hi){
            mid = (lo+hi)/2;
            if (((anglemap[mid]+offset))>=angle)
                hi = mid;
            else
                lo = mid+1;
        }
        comindx = lo%126;

        
        //if (comindx>lastcomindx && angle<(anglemap[lastcomindx]+deadband))
        //{comindx = lastcomindx;}
        //else if (comindx<lastcomindx && angle>(anglemap[comindx]-deadband))
        //{comindx = lastcomindx;}

    }
    */
    
    
    
    
    int16 lo=0, hi = 126, mid=0;
    while (lo<hi){
        mid = (lo+hi)/2;
        if (((anglemap[mid]))>=angle)
            hi = mid;
        else
            lo = mid+1;
    }
    comindx = lo%126;
    
    if (comindx!=lastcomindx)
    {
        if (lastcomindx == 0)
        {
            if (angle<anglemap[0]+deadband)
            {
                comindx = 0;
            }
            else if (angle>anglemap[125]-deadband)
            {
                comindx = 0;
            }
            
        }
        else if (lastcomindx == 1)
        {
            if (comindx == 0)
            {
                if (angle<anglemap[1]+deadband)
                {
                    comindx = 1;
                }
                if (angle >anglemap[124])
                {
                    if (angle-16384> (int16)anglemap[0]-deadband)
                    {comindx = 1;}
                }
                
                else
                {
                    if (angle>(int16)anglemap[0]-deadband)
                    {comindx = 1;}
                }
            }
            else if (comindx == 2 &&(angle<anglemap[1]+deadband))
            {
                comindx = 1;
            }

        }
        else if (lastcomindx == 125)
        {
            if (comindx == 0)
            {
                if (angle <= anglemap[0])
                {
                    if (angle+16384<anglemap[125]+deadband)
                    {comindx = 125;}
                }
                else
                {
                    if (angle < anglemap[125]+deadband)
                    {comindx = 125;}
                }
            }
            else if (comindx == 124 &&(angle>anglemap[124]-deadband))
            {
                comindx = 125;
            }

        }
        else
        {
            if (comindx>lastcomindx)
            {
                if (angle<anglemap[lastcomindx]+deadband)
                {comindx = lastcomindx;}
            }
            else
            {
                if (angle>anglemap[comindx]-deadband)
                {comindx = lastcomindx;}
            }
        }
    }
        
        
    if (findingpoles == 0)
    {Virtual_Hall_Write(hallmap_map2[comindx%6]);}
    
    lastangle = angle; 
    lastcomindx = comindx;
     
}

void motor_spi_block_commutation_triangletest(){
    static int32 offsetcount = 1;
    //Swap between equation and mapping functions
    static int16 switchmode = 0;
    if (offsetcount%50000==0){
        switchmode++;
    }

    //Triangle wave speed
    static int16 comm_spd = 0;   
    if (offsetcount%100 == 0)
    {
            if (switchmode%4 == 0 || switchmode%4 == 3){comm_spd++;}
            else{comm_spd--;}
    }   
    motor_open_speed_1(comm_spd);
    offsetcount++;
}

//Stepper code to map all of the pole positions run at 10000 Hz
void motor_spi_findpoles(int angle){   
    static int32 curangle = 0, offsetcount = 1;
    static int16 polecounter = 0; 
    static int16 mincomang = 30000, mincomangindx = -1;
    static int32 stepperiod = 4000, numavgsamples = 1000, actnumsamples = 0, lsamp = 0, hsamp = 0, lang = 0, hang = 0;
    if (polecounter<130)
    {
        findingpoles = 1;
        motor_open_speed_1(100);
        Virtual_Hall_Write(hallmap_map[polecounter%6]);
        if (offsetcount%stepperiod == 0)
        {
            if (hsamp == 0 || lsamp || 0)
            {
                polemap[polecounter%126] = (uint16)(curangle/actnumsamples);
            }
            else
            {
                polemap[polecounter%126] = (uint16)(((lang+16384*lsamp+hang)/(lsamp+hsamp))%16384);
            }
            if (polemap[polecounter%126]<mincomang)
            {
                mincomang = polemap[polecounter%126];
                mincomangindx = polecounter%126;
            }
            polecounter++;
            curangle = 0;
            actnumsamples = 0;
            lsamp = 0;
            hsamp = 0;
            lang = 0;
            hang = 0;
        }
        
        if (offsetcount%stepperiod >= stepperiod-numavgsamples)
        {
            curangle = curangle+(int32)angle;
            actnumsamples++;
            
            if (angle<1000)
            {
                lsamp++;
                lang = lang+(int32)angle;
            }
            else if (angle>15000)
            {
                hsamp++;
                hang = hang+(int32)angle;
            }
        }
    }
    else if (polecounter == 130)
    {
        polecounter++;
        int16 polemapindx = mincomangindx;
        int16 anglemapindx = 0;
        
        int16 hallmapindx = (mincomangindx-2)%6;
        hallmap_map2[0] = hallmap_map[hallmapindx];
        hallmap_map2[1] = hallmap_map[(hallmapindx+1)%6];
        hallmap_map2[2] = hallmap_map[(hallmapindx+2)%6];
        hallmap_map2[3] = hallmap_map[(hallmapindx+3)%6];
        hallmap_map2[4] = hallmap_map[(hallmapindx+4)%6];
        hallmap_map2[5] = hallmap_map[(hallmapindx+5)%6];
        
        while (polemapindx <126)
        {
            anglemap[anglemapindx] = polemap[polemapindx];
            polemapindx++;
            anglemapindx++;
        }
        polemapindx = 0;
        while (anglemapindx<126)
        {
            anglemap[anglemapindx] = polemap[polemapindx];
            polemapindx++;
            anglemapindx++;
        }
    }
    else 
    {
        findingpoles = 0;
        motor_open_speed_1(0);
    }
    
    
    offsetcount++;
}

//Call this function at 10kHz, in the main FSM:
void sensor_commut_1(void)
{
	static int16 mot_spins = 0;
	int32 tempangle;
	tempangle = (as5047_read_single(AS5047_REG_ANGLECOM));//%16384;
	if (tempangle<1000 && as5047.angle>15000)
	{
	    mot_spins++;  
	}
	else if ((tempangle>15000 && as5047.angle<1000))
	{
	    mot_spins--;
	}
	as5047.angle_cont = mot_spins*16384+tempangle;
	as5047.angle = tempangle;

	motor_spi_block_commutation(as5047.angle);

	//motor_spi_block_commutation_triangletest();
	//motor_open_speed_1(300);
	//motor_spi_findpoles(mot_enc_angle);
}

//****************************************************************************
// Private Function(s)
//****************************************************************************
