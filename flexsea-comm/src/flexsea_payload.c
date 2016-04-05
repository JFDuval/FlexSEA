//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_payload: deals with the "intelligent" data packaged in a comm_str
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea.h"
#include "../../flexsea-system/inc/flexsea_system.h"
#include "flexsea_board.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t payload_str[PAYLOAD_BUF_LEN];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static uint8_t get_rid(uint8_t *pldata);
static void route_to_slave(uint8_t port, uint8_t *buf, uint32_t len);

//****************************************************************************
// Public Function(s):
//****************************************************************************

//Start a new payload string
void prepare_empty_payload(uint8_t from, uint8_t to, uint8_t *buf, uint32_t len)
{
	//Start fresh:
	fill_uint8_buf(buf, len, 0);

    //Addresses:
    buf[P_XID] = from;
    buf[P_RID] = to;
}

//Add a buffer at the end of a partially filled payload buffer
//Payload is the partially filled buffer, idx is the next position to use, new_data is.. well, the new bytes
//and len is the number of bytes you want to add
uint32_t append_to_payload(uint8_t *payload, uint32_t idx, uint8_t *new_data, uint32_t len)
{
	uint32_t i = 0, cnt = 0;

	//Append the new data:
	for(i = idx; i < (idx+len); i++)
	{
		payload[i] = new_data[cnt++];
	}

	//Index for the next call:
	return i;
}

//Returns one if it was sent from a slave, 0 otherwise
uint8_t sent_from_a_slave(uint8_t *buf)
{
	//Slaves have higher addresses than their master.
	if(buf[P_XID] > buf[P_RID])
	{
		//Slave
		return 1;
	}
	else
	{
		//Master
		return 0;
	}

	//Should not happen
	return 0;
}

//Decode/parse received string
//ToDo fix: for now, supports only one command per string
unsigned int payload_parse_str(unsigned char *cp_str)
{
    unsigned char cmd = 0, cmd_7bits = 0, output = PARSE_SUCCESSFUL, numb = 0;
    unsigned int id = 0;

    //Command
    cmd = cp_str[P_CMD1];		//CMD w/ R/W bit
    cmd_7bits = CMD_7BITS(cmd);	//CMD code, no R/W information

    //First, get RID code
    id = get_rid(cp_str);
    if(id == ID_MATCH)
    {
		output = PARSE_SUCCESSFUL;

        //It's addressed to me. What should I do with it?
        switch(cmd_7bits)
        {
			//0-9:
            case 0:
                flexsea_payload_0(cp_str);
                break;            
            case 1:		//FlexSEA Stack Test
            	rx_cmd_test(cp_str);
            	break;
            case 2:
                flexsea_payload_2(cp_str);
                break;
			case 3:
                flexsea_payload_3(cp_str);
                break;
			case 4:
                flexsea_payload_4(cp_str);
                break;
			case 5:
                flexsea_payload_5(cp_str);
                break;
			case 6:
                flexsea_payload_6(cp_str);
                break;
			case 7:
                flexsea_payload_7(cp_str);
                break;
			case 8:
                flexsea_payload_8(cp_str);
                break;
			case 9:
                flexsea_payload_9(cp_str);
                break;

			//10-19:
            case 10:
            	flexsea_payload_10(cp_str);
            	break;
            case 11:
            	flexsea_payload_11(cp_str);
            	break;
            case 12:
            	flexsea_payload_12(cp_str);
            	break;
            case 13:
            	flexsea_payload_13(cp_str);
            	break;
            case 14:
            	flexsea_payload_14(cp_str);
            	break;
            case 15:
            	flexsea_payload_15(cp_str);
            	break;
            case 16:
            	flexsea_payload_16(cp_str);
            	break;
            case 17:
            	flexsea_payload_17(cp_str);
            	break;
            case 18:
            	flexsea_payload_18(cp_str);
            	break;
            case 19:
            	flexsea_payload_19(cp_str);
            	break;
				
			//20-29:	
            case 20:
            	flexsea_payload_20(cp_str);
            	break;
            case 21:
            	flexsea_payload_21(cp_str);
            	break;
            case 22:
            	flexsea_payload_22(cp_str);
            	break;
            case 23:
            	flexsea_payload_23(cp_str);
            	break;
            case 24:
            	flexsea_payload_24(cp_str);
            	break;
            case 25:
            	flexsea_payload_25(cp_str);
            	break;
            case 26:
            	flexsea_payload_26(cp_str);
            	break;
            case 27:
            	flexsea_payload_27(cp_str);
            	break;
            case 28:
            	flexsea_payload_28(cp_str);
            	break;
            case 29:
            	flexsea_payload_29(cp_str);
            	break;
				
			//30-39:	
            case 30:
            	flexsea_payload_30(cp_str);
            	break;
            case 31:
            	flexsea_payload_31(cp_str);
            	break;
            case 32:
            	flexsea_payload_32(cp_str);
            	break;
            case 33:
            	flexsea_payload_33(cp_str);
            	break;
            case 34:
            	flexsea_payload_34(cp_str);
            	break;
            case 35:
            	flexsea_payload_35(cp_str);
            	break;
            case 36:
            	flexsea_payload_36(cp_str);
            	break;
            case 37:
            	flexsea_payload_37(cp_str);
            	break;
            case 38:
            	flexsea_payload_38(cp_str);
            	break;
            case 39:
            	flexsea_payload_39(cp_str);
            	break;
				
			//40-49:	
            case 40:
            	flexsea_payload_40(cp_str);
            	break;
            case 41:
            	flexsea_payload_41(cp_str);
            	break;
            case 42:
            	flexsea_payload_42(cp_str);
            	break;
            case 43:
            	flexsea_payload_43(cp_str);
            	break;
            case 44:
            	flexsea_payload_44(cp_str);
            	break;
            case 45:
            	flexsea_payload_45(cp_str);
            	break;
            case 46:
            	flexsea_payload_46(cp_str);
            	break;
            case 47:
            	flexsea_payload_47(cp_str);
            	break;
            case 48:
            	flexsea_payload_48(cp_str);
            	break;
            case 49:
            	flexsea_payload_49(cp_str);
            	break;
				
			//50-59:	
            case 50:
            	flexsea_payload_50(cp_str);
            	break;
            case 51:
            	flexsea_payload_51(cp_str);
            	break;
            case 52:
            	flexsea_payload_52(cp_str);
            	break;
            case 53:
            	flexsea_payload_53(cp_str);
            	break;
            case 54:
            	flexsea_payload_54(cp_str);
            	break;
            case 55:
            	flexsea_payload_55(cp_str);
            	break;
            case 56:
            	flexsea_payload_56(cp_str);
            	break;
            case 57:
            	flexsea_payload_57(cp_str);
            	break;
            case 58:
            	flexsea_payload_58(cp_str);
            	break;
            case 59:
            	flexsea_payload_59(cp_str);
            	break;
				
			//60-69:	
            case 60:
            	flexsea_payload_60(cp_str);
            	break;
            case 61:
            	flexsea_payload_61(cp_str);
            	break;
            case 62:
            	flexsea_payload_62(cp_str);
            	break;
            case 63:
            	flexsea_payload_63(cp_str);
            	break;
            case 64:
            	flexsea_payload_64(cp_str);
            	break;
            case 65:
            	flexsea_payload_65(cp_str);
            	break;
            case 66:
            	flexsea_payload_66(cp_str);
            	break;
            case 67:
            	flexsea_payload_67(cp_str);
            	break;
            case 68:
            	flexsea_payload_68(cp_str);
            	break;
            case 69:
            	flexsea_payload_69(cp_str);
            	break;
				
			//70-79:	
            case 70:
            	flexsea_payload_70(cp_str);
            	break;
            case 71:
            	flexsea_payload_71(cp_str);
            	break;
            case 72:
            	flexsea_payload_72(cp_str);
            	break;
            case 73:
            	flexsea_payload_73(cp_str);
            	break;
            case 74:
            	flexsea_payload_74(cp_str);
            	break;
            case 75:
            	flexsea_payload_75(cp_str);
            	break;
            case 76:
            	flexsea_payload_76(cp_str);
            	break;
            case 77:
            	flexsea_payload_77(cp_str);
            	break;
            case 78:
            	flexsea_payload_78(cp_str);
            	break;
            case 79:
            	flexsea_payload_79(cp_str);
            	break;
				
			//80-89:	
            case 80:
            	flexsea_payload_80(cp_str);
            	break;
            case 81:
            	flexsea_payload_81(cp_str);
            	break;
            case 82:
            	flexsea_payload_82(cp_str);
            	break;
            case 83:
            	flexsea_payload_83(cp_str);
            	break;
            case 84:
            	flexsea_payload_84(cp_str);
            	break;
            case 85:
            	flexsea_payload_85(cp_str);
            	break;
            case 86:
            	flexsea_payload_86(cp_str);
            	break;
            case 87:
            	flexsea_payload_87(cp_str);
            	break;
            case 88:
            	flexsea_payload_88(cp_str);
            	break;
            case 89:
            	flexsea_payload_89(cp_str);
            	break;				

			//90-99:	
            case 90:
            	flexsea_payload_90(cp_str);
            	break;
            case 91:
            	flexsea_payload_91(cp_str);
            	break;
            case 92:
            	flexsea_payload_92(cp_str);
            	break;
            case 93:
            	flexsea_payload_93(cp_str);
            	break;
            case 94:
            	flexsea_payload_94(cp_str);
            	break;
            case 95:
            	flexsea_payload_95(cp_str);
            	break;
            case 96:
            	flexsea_payload_96(cp_str);
            	break;
            case 97:
            	flexsea_payload_97(cp_str);
            	break;
            case 98:
            	flexsea_payload_98(cp_str);
            	break;
            case 99:
            	flexsea_payload_99(cp_str);
            	break;
				
			//100-109:	
            case 100:
            	flexsea_payload_100(cp_str);
            	break;
            case 101:
            	flexsea_payload_101(cp_str);
            	break;
            case 102:
            	flexsea_payload_102(cp_str);
            	break;
            case 103:
            	flexsea_payload_103(cp_str);
            	break;
            case 104:
            	flexsea_payload_104(cp_str);
            	break;
            case 105:
            	flexsea_payload_105(cp_str);
            	break;
            case 106:
            	flexsea_payload_106(cp_str);
            	break;
            case 107:
            	flexsea_payload_107(cp_str);
            	break;
            case 108:
            	flexsea_payload_108(cp_str);
            	break;
            case 109:
            	flexsea_payload_109(cp_str);
            	break;
				
			//110-119:	
            case 110:
            	flexsea_payload_110(cp_str);
            	break;
            case 111:
            	flexsea_payload_111(cp_str);
            	break;
            case 112:
            	flexsea_payload_112(cp_str);
            	break;
            case 113:
            	flexsea_payload_113(cp_str);
            	break;
            case 114:
            	flexsea_payload_114(cp_str);
            	break;
            case 115:
            	flexsea_payload_115(cp_str);
            	break;
            case 116:
            	flexsea_payload_116(cp_str);
            	break;
            case 117:
            	flexsea_payload_117(cp_str);
            	break;
            case 118:
            	flexsea_payload_118(cp_str);
            	break;
            case 119:
            	flexsea_payload_119(cp_str);
            	break;
				
			//120-127:	
            case 120:
            	flexsea_payload_120(cp_str);
            	break;
            case 121:
            	flexsea_payload_121(cp_str);
            	break;
            case 122:
            	flexsea_payload_122(cp_str);
            	break;
            case 123:
            	flexsea_payload_123(cp_str);
            	break;
            case 124:
            	flexsea_payload_124(cp_str);
            	break;
            case 125:
            	flexsea_payload_125(cp_str);
            	break;
            case 126:
            	flexsea_payload_126(cp_str);
            	break;
            case 127:
            	flexsea_payload_127(cp_str);
            	break;
			
			//Unknown command:
            default:
                output = PARSE_UNKNOWN_CMD;
                break;
        }

        return output;
    }
    else if(id == ID_SUB1_MATCH)
    {
        //For a slave on bus #1:

    	route_to_slave(PORT_SUB1, cp_str, PAYLOAD_BUF_LEN);
    	//ToDo compute length rather then sending the max
    }
    else if(id == ID_SUB2_MATCH)
    {
    	//For a slave on bus #2:

    	route_to_slave(PORT_SUB2, cp_str, PAYLOAD_BUF_LEN);
    	//ToDo compute length rather then sending the max
    }
    else if(id == ID_UP_MATCH)
    {
        //For my master:

		//Nothing for now, as we have a flat network structure. Leaving the code below
		//as an example for future systems:
		
		/*
		#ifdef BOARD_TYPE_FLEXSEA_MANAGE

    	//Manage is the only board that can receive a package destined to his master

        //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
        numb = comm_gen_str(cp_str, comm_str_spi, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN;    //Fixed length for now
        //flexsea_send_serial_master(0, comm_str, numb);
        //(the SPI driver will grab comm_str_spi directly)

		#endif	//BOARD_TYPE_FLEXSEA_MANAGE
		*/
    }
    else
    {
        return PARSE_ID_NO_MATCH;
    }

    //Shouldn't get here...
    return PARSE_DEFAULT;
}

//****************************************************************************
// Private Function(s):
//****************************************************************************

//Nothing for now, as we have a flat network structure. Leaving the code below
//as an example for future systems:

//ToDo not the greatest function...
static void route_to_slave(uint8_t port, uint8_t *buf, uint32_t len)
{
	/*
	uint32_t numb = 0, i = 0;
	uint8_t *comm_str_ptr = slaves_485_1.xmit.str;

    //Repackages the payload. ToDo: would be more efficient to just resend the comm_str
    numb = comm_gen_str(buf, comm_str_tmp, len);
    //numb = COMM_STR_BUF_LEN;    //Fixed length for now

    //Port specific flags and buffer:
    if(port == PORT_RS485_1)
    {
    	comm_str_ptr = slaves_485_1.xmit.str;
    	slaves_485_1.xmit.cmd = buf[P_CMD1];
    	slaves_485_1.xmit.flag = 1;
    }
    else if(port == PORT_RS485_2)
    {
    	comm_str_ptr = slaves_485_2.xmit.str;
    	slaves_485_2.xmit.cmd = buf[P_CMD1];
    	slaves_485_2.xmit.flag = 1;
    }

    //Copy string:
    for(i = 0; i < numb+1; i++)
    {
    	comm_str_ptr[i] = comm_str_tmp[i];
    }
	*/
}

//Is it addressed to me? To a board "below" me? Or to my Master?
static uint8_t get_rid(uint8_t *pldata)
{
	uint8_t cp_rid = pldata[P_RID];
	uint8_t i = 0;

	if(cp_rid == board_id)				//This board?
	{
		return ID_MATCH;
	}
	else if(cp_rid == board_up_id)		//Master?
	{
		return ID_UP_MATCH;
	}
	else
	{
		//Can be on a slave bus, or can be invalid.

		//Search on slave bus #1:
		for(i = 0; i < SLAVE_BUS_1_CNT; i++)
		{
			if(cp_rid == board_sub1_id[i])
			{
				return ID_SUB1_MATCH;
			}
		}

		//Then on bus #2:
		for(i = 0; i < SLAVE_BUS_1_CNT; i++)
		{
			if(cp_rid == board_sub2_id[i])
			{
				return ID_SUB2_MATCH;
			}
		}
	}

	//If we end up here it's because we didn't get a match:
	return ID_NO_MATCH;
}

#ifdef __cplusplus
}
#endif
