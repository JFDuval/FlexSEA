/*******************************************************************************
File Name: CYBLE_StackGap.h
Version 1.20

Description:
 This file contains the GAP APIs of the BLE Host Stack IP

Related Document:
 BLE Standard Spec - CoreV4.1, CSS, CSAs, ESR05, ESR06

********************************************************************************
Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
You may use this file only in accordance with the license, terms, conditions,
disclaimers, and limitations in the end user license agreement accompanying
the software package with which this file was provided.
*******************************************************************************/


#ifndef CY_BLE_CYBLE_GAP_H
#define CY_BLE_CYBLE_GAP_H


/***************************************
##Common stack includes
***************************************/

#include "BLE_1_Stack.h"


/***************************************
##GAP Constants
***************************************/


/* BD Address type flag*/
#define CYBLE_GAP_ADDR_TYPE_PUBLIC              0x00u
#define CYBLE_GAP_ADDR_TYPE_RANDOM              0x01u

/* Max data length size  */
#define CYBLE_GAP_MAX_ADV_DATA_LEN              31u

/* Max data length size  */
#define CYBLE_GAP_MAX_SCAN_RSP_DATA_LEN         31u

/* Security modes  */
#define CYBLE_GAP_SEC_MODE_1                    0x10u
#define CYBLE_GAP_SEC_MODE_2                    0x20u
#define CYBLE_GAP_SEC_MODE_MASK                 0xF0u

/* Broadcaster and discoverable mode  */
#define CYBLE_GAPP_NONE_DISC_BROADCAST_MODE     0x00u
#define CYBLE_GAPP_LTD_DISC_MODE                0x01u
#define CYBLE_GAPP_GEN_DISC_MODE                0x02u

/* Limited Discoverable mode timeout max. */
#define CYBLE_GAPP_LTD_DISC_MODE_TIME_MAX       180u

/* Observation and discovery procedure */
#define CYBLE_GAPC_OBSER_PROCEDURE              0x00u
#define CYBLE_GAPC_LTD_DISC_PROCEDURE           0x01u
#define CYBLE_GAPC_GEN_DISC_PROCEDURE           0x02u

/* Type of discovery procedure use in CYBLE_GAPC_DISC_INFO_T*/
#define CYBLE_GAPC_PASSIVE_SCANNING				0x00u	
#define CYBLE_GAPC_ACTIVE_SCANNING				0x01u
#define CYBLE_GAPC_ADV_ACCEPT_ALL_PKT 			0x00u
#define CYBLE_GAPC_ADV_ACCEPT_WHITELIST_PKT 	0x01u
#define CYBLE_GAPC_FILTER_DUP_DISABLE 			0x00u
#define CYBLE_GAPC_FILTER_DUP_ENABLE			0x01u

/* Advertising filter policy*/
#define CYBLE_GAPP_SCAN_ANY_CONN_ANY 			0x00u
#define CYBLE_GAPP_SCAN_WHITELIST_CONN_ANY 		0x01u
#define CYBLE_GAPP_SCAN_ANY_CONN_WHITELIST 		0x02u
#define CYBLE_GAPP_SCAN_CONN_WHITELIST_ONLY 	0x03u

/* Initiator filter policy*/
#define CYBLE_GAPC_CONN_ALL 					0x00u
#define CYBLE_GAPC_CONN_WHITELIST 				0x01u

/* Maximum number of Remote Devices */
#define CYBLE_GAP_MAX_BONDED_DEVICE             4u

/* Out Of Band (OOB) flag*/
#define CYBLE_GAP_OOB_ENABLE                    0x01u
#define CYBLE_GAP_OOB_DISABLE                   0x00u

#define CYBLE_GAP_SMP_LTK_SIZE                  0x10u 
#define CYBLE_GAP_SMP_IRK_SIZE                  0x10u
#define CYBLE_GAP_SMP_CSRK_SIZE                 0x10u
#define CYBLE_GAP_SMP_IDADDR_DATA_SIZE          0x07u

#define CYBLE_GAP_SMP_MID_INFO_SIZE             0x0Au

#define CYBLE_GAP_SMP_INIT_ENC_KEY_DIST         0x01u
#define CYBLE_GAP_SMP_INIT_IRK_KEY_DIST         0x02u
#define CYBLE_GAP_SMP_INIT_CSRK_KEY_DIST        0x04u

#define CYBLE_GAP_SMP_RESP_ENC_KEY_DIST         0x10u
#define CYBLE_GAP_SMP_RESP_IRK_KEY_DIST         0x20u
#define CYBLE_GAP_SMP_RESP_CSRK_KEY_DIST        0x40u

/* Passkey Response */
#define CYBLE_GAP_REJECT_PASSKEY_REQ            0x00u
#define CYBLE_GAP_ACCEPT_PASSKEY_REQ            0x01u


/***************************************
##Bonding definitions
***************************************/

/* No Bonding support */
#define CYBLE_GAP_BONDING_NONE                          0x00u

/* Bonding support */
#define CYBLE_GAP_BONDING                               0x01u

/* Encryption key size   */
#define CYBLE_GAP_ENCRYP_KEY_MIN                        7u
#define CYBLE_GAP_ENCRYP_KEY_MAX                        16u

/* User Passkey size */
#define CYBLE_GAP_USER_PASSKEY_SIZE                     6u

#define CYBLE_GAP_RANDOM_PRIV_RESOLVABLE_ADDR_MASK      0x40u
#define CYBLE_GAP_RANDOM_PRIV_NON_RESOLVABLE_ADDR_MASK  0x00u
#define CYBLE_GAP_PUBLIC_ADDR_MASK                      0x80u
#define CYBLE_GAP_RANDOM_STATIC_ADDR_MASK               0xC0u


/***************************************
##Enumerated Types
***************************************/

/* Advertisement type  */
typedef enum
{
	/* Connectable undirected advertising */
	CYBLE_GAPP_CONNECTABLE_UNDIRECTED_ADV = 0x00u,

	/* Connectable high duty cycle directed advertising */
	CYBLE_GAPP_CONNECTABLE_HIGH_DC_DIRECTED_ADV,

	/* Scannable undirected advertising */
	CYBLE_GAPP_SCANNABLE_UNDIRECTED_ADV,

	/* Non connectable undirected advertising */
	CYBLE_GAPP_NON_CONNECTABLE_UNDIRECTED_ADV,

	/* Connectable low duty cycle directed advertising */
	CYBLE_GAPP_CONNECTABLE_LOW_DC_DIRECTED_ADV
	
}CYBLE_GAPP_ADV_T;

/* Advertisement event type  */
typedef enum
{
	/* Connectable undirected advertising */
	CYBLE_GAPC_CONN_UNDIRECTED_ADV = 0x00u,

	/* Connectable directed advertising */
	CYBLE_GAPC_CONN_DIRECTED_ADV,

	/* Scannable undirected advertising */
	CYBLE_GAPC_SCAN_UNDIRECTED_ADV,

	/* Non connectable undirected advertising */
	CYBLE_GAPC_NON_CONN_UNDIRECTED_ADV,

	/* Scan Response*/
	CYBLE_GAPC_SCAN_RSP
	
}CYBLE_GAPC_ADV_EVENT_T;
 
/* Security Levels  */
typedef enum
{
	/* Level 1
	    * Mode 1 - No Security (No Authentication & No Encryption)
	    * Mode 2 - N/A
	 */
	CYBLE_GAP_SEC_LEVEL_1 =	0x00u,
	
	/* Level 2
	    * Mode 1 - Unauthenticated pairing with encryption (No MITM)
	    * Mode 2 - Unauthenticated pairing with data signing (No MITM)
	 */
	CYBLE_GAP_SEC_LEVEL_2,
	
	/* Level 3
	    * Mode 1 - Authenticated pairing with encryption (With MITM)
	    * Mode 2 - Authenticated pairing with data signing (With MITM)
	 */
	CYBLE_GAP_SEC_LEVEL_3,
	
	/* LE Security Level Mask */
	CYBLE_GAP_SEC_LEVEL_MASK =0x0Fu

}CYBLE_GAP_SEC_LEVEL_T;

/* IO capability  */
typedef enum
{
	/* Platform supports only a mechanism to display or convey only 6 digit number to user.*/
	CYBLE_GAP_IOCAP_DISPLAY_ONLY=0x00u, 
	
	/* The device has a mechanism whereby the user can indicate 'yes' or 'no'.*/	
	CYBLE_GAP_IOCAP_DISPLAY_YESNO, 
	
	/* Platform supports a numeric keyboard that can input the numbers '0' through '9' 
	    and a confirmation key(s) for  'yes' and 'no'. */
	CYBLE_GAP_IOCAP_KEYBOARD_ONLY,	

	/* Platform does not have the ability to display or communicate a 6 digit decimal number.*/
	CYBLE_GAP_IOCAP_NOINPUT_NOOUTPUT,	

	/* Platform supports a mechanism through which 6 digit numeric value can be displayed 
	    and numeric keyboard that can input the numbers '0' through '9'. */
	CYBLE_GAP_IOCAP_KEYBOARD_DISPLAY
	
} CYBLE_GAP_IOCAP_T;

/* Authentication Failed Error Codes */
typedef enum
{
	/* No Error */
	CYBLE_GAP_AUTH_ERROR_NONE  = 0x00u,

	/* User input of passkey failed, for example, the user cancelled the operation */
	CYBLE_GAP_AUTH_ERROR_PASSKEY_ENTRY_FAILED,

	/* Out Of Band data is not available, applicable if NFC is supported */
	CYBLE_GAP_AUTH_ERROR_OOB_DATA_NOT_AVAILABLE,

	/* Pairing procedure cannot be performed as authentication
       requirements cannot be met due to IO capabilities of one or both devices. */
	CYBLE_GAP_AUTH_ERROR_AUTHENTICATION_REQ_NOT_MET,

	/* Confirm value does not match the calculated compare value  */
	CYBLE_GAP_AUTH_ERROR_CONFIRM_VALUE_NOT_MATCH,

	/* Pairing is not supported by the device */
	CYBLE_GAP_AUTH_ERROR_PAIRING_NOT_SUPPORTED,

	/* Insufficient key size for the security requirements of this device */
	CYBLE_GAP_AUTH_ERROR_INSUFFICIENT_ENCRYPTION_KEY_SIZE,

	/* command received is not supported */
	CYBLE_GAP_AUTH_ERROR_COMMAND_NOT_SUPPORTED,

	/* Pairing failed due to an unspecified reason */
	CYBLE_GAP_AUTH_ERROR_UNSPECIFIED_REASON,

	/* Pairing or authentication procedure is disallowed because too little time
 	   has elapsed since last pairing request or security request. */
	CYBLE_GAP_AUTH_ERROR_REPEATED_ATTEMPTS,

	/* Invalid Parameters in Request - Invalid Command length and Parameter value outside range */
	CYBLE_GAP_AUTH_ERROR_INVALID_PARAMETERS = 0x0Au,

	/* Authentication process timeout, if pairing timeout happens for first time, 
	    application can choose to re-initiate the pairing procedure. If timeout occurs again, 
	    app may choose to disconnect peer device. */
	CYBLE_GAP_AUTH_ERROR_AUTHENTICATION_TIMEOUT = 0x15u,

	/* Link disconnected */
	CYBLE_GAP_AUTH_ERROR_LINK_DISCONNECTED = 0x18u
	
}CYBLE_GAP_AUTH_FAILED_REASON_T;

/* GAP address type */
typedef enum
{
    /* Random private non-resolvable address */
    CYBLE_GAP_RANDOM_PRIV_NON_RESOLVABLE_ADDR = 0x00u,
    
    /* Random private resolvable address */
    CYBLE_GAP_RANDOM_PRIV_RESOLVABLE_ADDR = 0x01u,
    
    /* Public address */
    CYBLE_GAP_PUBLIC_ADDR = 0x02u,
    
    /* Random static address */
    CYBLE_GAP_RANDOM_STATIC_ADDR = 0x03u
    
} CYBLE_GAP_ADDR_TYPE_T;


/***************************************
##Exported structures and unions
***************************************/

/* Authentication Parameters Information  */
typedef struct 
{
	/* Security Mode setting will be as follows:
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_1)
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_2)
	    * (CYBLE_GAP_SEC_MODE_1 | CYBLE_GAP_SEC_LEVEL_3)
	    * (CYBLE_GAP_SEC_MODE_2 | CYBLE_GAP_SEC_LEVEL_2)
	    * (CYBLE_GAP_SEC_MODE_2 | CYBLE_GAP_SEC_LEVEL_3)
	 */
    uint8    						security;     

	/* Bonding type setting:
	     * CYBLE_GAP_BONDING_NONE
	     * CYBLE_GAP_BONDING
	 */
    uint8    						bonding;      

	/* Encryption Key Size (octets)
	     * Minimum = 7 
	     * maximum = 16
     */
	uint8    						ekeySize;  

 	/* Parameter to say it authentication is accepted or rejected with reason.
	   accepted = CYBLE_GAP_AUTH_ERROR_NONE or error code CYBLE_GAP_AUTH_FAILED_REASON_T. */	
	CYBLE_GAP_AUTH_FAILED_REASON_T    	authErr;	    
	
} CYBLE_GAP_AUTH_INFO_T;


/* Bluetooth Bonded Device Address list */
typedef struct
{
	/* Number of bonded devices */
    uint8     				count;

	/* Pointer to list of bluetooth device addresses of bonded devices, of type 
        'CYBLE_GAP_BD_ADDR_T'. 'CYBLE_GAP_MAX_BONDED_DEVICE' is a '#define' to
        be defined during build-time. */
    CYBLE_GAP_BD_ADDR_T     bdAddrList[CYBLE_GAP_MAX_BONDED_DEVICE];
	
}CYBLE_GAP_BONDED_DEV_ADDR_LIST_T;


/* Security Manager Key Distribution data */
typedef struct
{
    /* Long Term Key */
    uint8 ltkInfo[CYBLE_GAP_SMP_LTK_SIZE];

    /* Encrypted Diversifier and Randdom Number */
    uint8 midInfo[CYBLE_GAP_SMP_MID_INFO_SIZE];

    /* Identity Resolving Key */
    uint8 irkInfo[CYBLE_GAP_SMP_IRK_SIZE];

    /* Public device/Static Random address type */
    uint8 idAddrInfo[CYBLE_GAP_SMP_IDADDR_DATA_SIZE];

    /* Connection Signature Resolving Key */
    uint8 csrkInfo[CYBLE_GAP_SMP_CSRK_SIZE];

} CYBLE_GAP_SMP_KEY_DIST_T;

/* Advertising parameters   */
typedef struct
{
	/* Minimum advertising interval for undirected 
	   and low duty cycle directed advertising.
	   	 - Time Range: 20 ms to 10.24 sec
	 */
	uint16     				advIntvMin; 

	/* Maximum advertising interval for undirected 
	   and low duty cycle directed advertising.
	   	- Time Range: 20 ms to 10.24 sec
	 */	
	uint16     				advIntvMax; 

	/* Type of advertisement
	   	- Connectable undirected advertising (0x00)
	   	- Connectable high duty cycle directed advertising (0x01)
	   	- Scannable undirected advertising (0x02)
	   	- Non connectable undirected advertising (0x03)
	   	- Connectable low duty cycle directed advertising (0x04)
	 */	
	CYBLE_GAPP_ADV_T      	advType;		

	/* Own BD Address Type											
		- CYBLE_GAP_ADDR_TYPE_PUBLIC (Public device address)
		- CYBLE_GAP_ADDR_TYPE_RANDOM (Random device address)
     */	
	uint8      				ownAddrType;	

	/* Address type of the Bluetooth device address being used for 
	   directed advertising, not applicable otherwise
	    - CYBLE_GAP_ADDR_TYPE_PUBLIC (Public device address)
        - CYBLE_GAP_ADDR_TYPE_RANDOM (Random device address)
	 */
	uint8      				directAddrType;	

	/* 	This parameter specifies Bluetooth device address of the 
	  	device to be connected while using directed advertising.
	  	In case of none direct advertising, parameter will be 0 
	 */	
	uint8     				directAddr[CYBLE_GAP_BD_ADDR_SIZE];		

	/* Advertising channels that shall be used when transmitting advertising packets. 
	   Channel map selection:
		- Enable channel 37 = bitmask. xxxxxxx1b
		- Enable channel 38 = bitmask. xxxxxx1xb
		- Enable channel 39 = bitmask. xxxxx1xxb 
	 */
	uint8      				advChannelMap;

	/* Advertising Filter Policy
	   	- CYBLE_GAPP_SCAN_ANY_CONN_ANY (Allow Scan Request from Any, Allow Connect Request
           from Any (Default))
	   	- CYBLE_GAPP_SCAN_WHITELIST_CONN_ANY (Allow Scan Request from White List Only, 
           Allow Connect Request)
	   	- CYBLE_GAPP_SCAN_ANY_CONN_WHITELIST (Allow Scan Request from Any, Allow Connect
           Request from White List Only)
	   	- CYBLE_GAPP_SCAN_CONN_WHITELIST_ONLY (Allow Scan Request from White List Only, 
           Allow Connect Request from White List Only)
	 */	
	uint8      				advFilterPolicy;
	
}CYBLE_GAPP_DISC_PARAM_T;

/* Advertising data   */
typedef struct
{
	/*GAP Advertisement Parameters which includes Flags, Service UUIDs and short name*/
	uint8      advData[CYBLE_GAP_MAX_ADV_DATA_LEN]; 

	/*length of the advertising data. This should be made zero if there is no data */
	uint8      advDataLen;	
	
} CYBLE_GAPP_DISC_DATA_T;

/* Scan response data   */
typedef struct
{
	/* Static user data transmitted in scan response. This should be made NULL if 
    there is no data. Maximum length of the data is equal to 31 bytes */
	uint8     scanRspData[CYBLE_GAP_MAX_SCAN_RSP_DATA_LEN];

	/* Length of the scan response data. This should be made zero if there is no data */
	uint8     scanRspDataLen; 	
	
} CYBLE_GAPP_SCAN_RSP_DATA_T;

/* Advertising information   */
typedef struct
{
	/* Broadcaster and discoverable mode 
	    - CYBLE_GAPP_NONE_DISC_BROADCAST_MODE
           (Applicable for Broadcaster or non-discoverable mode)
	    - CYBLE_GAPP_LTD_DISC_MODE (Limited discovery mode)
	    - CYBLE_GAPP_GEN_DISC_MODE (General discovery mode)
	 */
	uint8      						discMode;

	/* Advertisement parameters */
	CYBLE_GAPP_DISC_PARAM_T   		* advParam;
    /* Advertisement data */
	CYBLE_GAPP_DISC_DATA_T    		* advData;
    /* Scan Response data */
	CYBLE_GAPP_SCAN_RSP_DATA_T	 	* scanRspData;

	/* Advertisement timeout is in seconds. If timeout is set to 0,
        then there will not be any timeout. Parameter 'advTo' can 
        be used for all GAP timeouts related to peripheral operation.
        For General discoverable mode, this timer will be ignored.
        Application is expected to exit from discoverable mode
        explicitly by calling CyBle_GappExitDiscoveryMode() function.
        For Limited discoverable mode, 'advTo' should not exceed 180 Sec.
	 */
	uint16 							advTo; 
	
} CYBLE_GAPP_DISC_MODE_INFO_T;

/* Discovery information collected by Client  */
typedef struct
{
	/* Observation and discovery procedure.
	   	 - CYBLE_GAPC_OBSER_PROCEDURE (Observation procedure)
	   	 - CYBLE_GAPC_LTD_DISC_PROCEDURE (Limited discovery procedure)
	   	 - CYBLE_GAPC_GEN_DISC_PROCEDURE (General discovery procedure)
	 */
	uint8      discProcedure;

	/* Type of scan to perform
	   	 - CYBLE_GAPC_PASSIVE_SCANNING (Passive Scanning)
	   	 - CYBLE_GAPC_ACTIVE_SCANNING (Active scanning)
	 */
	uint8      scanType;			

	/* The time interval from when last LE scan is started until 
	   next subsequent LE scan.
		- Time Range: 2.5 ms to 10.24 sec. 
     */
	uint16     scanIntv;		

	/* The time duration of scanning to be performed 
		- Time Range: 2.5 ms to 10.24 sec										 
	 */
	uint16     scanWindow;			

	/* Own BD Address Type
		- CYBLE_GAP_ADDR_TYPE_PUBLIC (Public device address)
		- CYBLE_GAP_ADDR_TYPE_RANDOM (Random device address)
	 */
	uint8      ownAddrType;		

	/* Filter policies to be applied during scanning procedure
		- CYBLE_GAPC_ADV_ACCEPT_ALL_PKT (Accept all advertisement packets)
		- CYBLE_GAPC_ADV_ACCEPT_WHITELIST_PKT (Ignore advertisement packets 
		from devices not in the White List)
	 */
	uint8      scanFilterPolicy;	

  	/* Scan timeout. Timeout is in seconds and none zero.
 	   If timeout is set as 0, then there will not be any timeout 
 	   scanTo can be used for all GAP timeouts related to Central operation.
	 */
	uint16 	   scanTo; 		

	/* Filter Duplicate Advertisement. The Filter Duplicates parameter controls whether
	   the Link Layer shall filter duplicate advertising reports to the Host, or if the
	   Link Layer should generate advertising reports for each packet received.
 	     - CYBLE_GAPC_FILTER_DUP_DISABLE (Duplicate filtering disabled)
 	     - CYBLE_GAPC_FILTER_DUP_ENABLE (Duplicate filtering enabled)

 	   By default, duplicate filtering is enabled
	 */
	uint8 	   filterDuplicates; 

} CYBLE_GAPC_DISC_INFO_T;

/* Connection parameters at the GAP Central end */
typedef struct
{
	/* The time interval from when last LE scan is started until next 
	   subsequent LE scan.
        - Time Range: 2.5 ms to 10.24 sec. 
     */
    uint16      scanIntv;                     	

	/* The time duration of scanning to be performed 
	    - Time Range: 2.5 ms to 10.24 sec										 
	 */
	uint16      scanWindow;						

	/* Filter policies to be applied during connection procedure
	    - CYBLE_GAPC_CONN_ALL (White list is not used to determine 
           which advertiser to connect. Peer address is used)
	    - CYBLE_GAPC_CONN_WHITELIST (White list is used to determine
           which advertiser to connect to. Peer address shall be ignored)
	 */
	uint8       initiatorFilterPolicy;			

	/* Peer's bd address with whom connection to be established */
	uint8       peerBdAddr[CYBLE_GAP_BD_ADDR_SIZE];	

	/* Peer's bd address type 
	    - CYBLE_GAP_ADDR_TYPE_PUBLIC (Public device address)
        - CYBLE_GAP_ADDR_TYPE_RANDOM (Random device address)
     */
	uint8       peerAddrType;						

	/* Own bd address type 
	    - CYBLE_GAP_ADDR_TYPE_PUBLIC (Public device address)
        - CYBLE_GAP_ADDR_TYPE_RANDOM (Random device address)
     */
	uint8       ownAddrType;						

	/* Minimum value for the connection event interval. This shall be less than
	   or equal to conn_Interval_Max. Minimum connection interval will be 
		 connIntvMin * 1.25 ms
        * Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMin;					

	/* Maximum value for the connection event interval. This shall be greater
	   than or equal to conn_Interval_Min. Maximum connection interval will be 
		 connIntvMax * 1.25 ms
	   	* Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMax;					

	/* Slave latency for the connection in number of connection events. 
	   	* Range: 0x0000 to 0x01F4 									 
	 */
    uint16      connLatency;						

	/* Supervision timeout for the LE Link. Supervision timeout will be  
	   supervisionTO * 10 ms
        * Time Range: 100 msec to 32 secs 									 
	 */
	uint16      supervisionTO;				

	/* Minimum length of connection needed for this LE connection.
	   	* Range: 0x0000 - 0xFFFF										 
	 */
	uint16      minCeLength;						

	/* Maximum length of connection needed for this LE connection.
	   	* Range: 0x0000 - 0xFFFF										 
	 */
    uint16      maxCeLength;						

}CYBLE_GAPC_CONN_PARAM_T;

/* Advertisement report received by GAP Central */
typedef struct
{
	/* Advertisement event type
	    - Connectable undirected advertising = 0x00
	    - Connectable directed advertising = 0x01
 	    - Scannable undirected advertising = 0x02
 	    - Non connectable undirected advertising = 0x03
 	    - Scan Response = 0x04
   	 */
	CYBLE_GAPC_ADV_EVENT_T		eventType;  

	/* bd address type of the device advertising.
	    - CYBLE_GAP_ADDR_TYPE_PUBLIC (Public device address)
        - CYBLE_GAP_ADDR_TYPE_RANDOM (Random device address)
	 */
    uint8  	    				peerAddrType;	

	/* Public Device Address or Random Device Address for
	   each device which responded to scanning. */
    uint8*	    				peerBdAddr;		

	/* length of the data for each device that responded to scanning */
    uint8       				dataLen;								

	/* Pointer to advertising or scan response data */
    uint8* 	    				data;				

	/* Rssi of the responding device.
				 * Range: -85 <= N <= 0
				 * Units: dBm */
    int8	    				rssi;	
	
} CYBLE_GAPC_ADV_REPORT_T;

/* Passkey display information */
typedef struct
{
	/* bd handle of the remote device */
    uint8	bdHandle; 

	/* size = 6, not null terminated */
    uint32 	passkey;  
	
}CYBLE_GAP_PASSKEY_DISP_INFO_T;

/* GAP Connection Update parameters  */
typedef struct
{
	/* Minimum value for the connection event interval. This shall be less than
	   or equal to conn_Interval_Max. Minimum connection interval will be 
		 connIntvMin * 1.25 ms
        * Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMin;					

	/* Maximum value for the connection event interval. This shall be greater
	   than or equal to conn_Interval_Min. Maximum connection interval will be 
		 connIntvMax * 1.25 ms
	   	* Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntvMax;					

	/* Slave latency for the connection in number of connection events. 
	 	* Range: 0x0000 to 0x01F4 									 
	 */
    uint16      connLatency;						

	/* Supervision timeout for the LE Link. Supervision timeout will be  
	   supervisionTO * 10 ms
	   	* Time Range: 100 msec to 32 secs 									 
	 */
	uint16      supervisionTO;								

}CYBLE_GAP_CONN_UPDATE_PARAM_T;

/* Current Connection Parameters used by controller */
typedef struct
{
	/* status corresponding to this event will be HCI error code 
    as defined in BLE spec 4.1 */
    uint8      status;					

	/* Connection interval used on this connection. 
	  	* Range: 0x0006 to 0x0C80
	  	* Time Range: 7.5 ms to 4 sec 									 
	 */
    uint16      connIntv;					

	/* Slave latency for the connection in number of connection events. 
	 	* Range: 0x0000 to 0x01F4 									 
	 */
    uint16      connLatency;						

	/* Supervision timeout for the LE Link. Supervision timeout will be  
	   supervisionTO * 10 ms
	   	* Time Range: 100 msec to 32 secs 									 
	 */
	uint16      supervisionTO;								

}CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T;


/***************************************
##Exported APIs
***************************************/

/******************************************************************************
##Function Name: CyBle_GapSetIoCap
*******************************************************************************

Summary:
 This function sets the input and output capability of the BLE Device that is
 used during authentication procedure. This is a blocking function. No event
 is generated on calling this function. The input capabilities are described
 in the following table:
 <table>
  Capability        Description
  -----------       -----------
  No input          Device does not have the ability to indicate "yes" or "no"
  Yes/No            Device has at least two buttons that can be easily mapped
                     to "yes" and "no" or the device has a mechanism whereby 
                     the user can indicate either "yes" or "no".
  Keyboard          Device has a numeric keyboard that can input the numbers
                     "0" through "9" and a confirmation. Device also has at 
                     least two buttons that can be easily mapped to "yes" and
                     "no" or the device has a mechanism whereby the user can
                     indicate either "yes" or "no".
 </table>

 The output capabilities are described in the following table:
 <table>
  Capability        Description
  -----------       -----------
  No output         Device does not have the ability to display or communicate
                     a 6 digit decimal number.
  Numeric output    Device has the ability to display or communicate a 6 digit
                     decimal number.
 </table>
 
 Combined capability is defined in the following table:
 <table>
  Input Capability      No Output           Numeric Output
  -----------           -----------         ------------
  No input              NoInputNoOutput     DisplayOnly
  Yes/No                NoInputNoOutput     DisplayYesNo
  Keyboard              KeyboardOnly        KeyboardDisplay
 </table>
 
 Refer Bluetooth 4.1 core specification, Volume 3, Part C, section 5.2.2.4 for
 more details on the IO capabilities. IO capabilities of the BLE devices are
 used to determine the pairing method. Please refer Bluetooth 4.1 core
 specification, Volume 3, Part H, section 2.3.5.1 for more details on the
 impact of IO capabilities on the pairing method chosen.
    
Parameters:
	io_cap:  IO Capability of type CYBLE_GAP_IOCAP_T. 
	
Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as 
                                     input parameter
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetIoCap(CYBLE_GAP_IOCAP_T ioCap);


/******************************************************************************
##Function Name: CyBle_GapSetOobData
*******************************************************************************

Summary:
 This function sets OOB presence flag and data. This function should be used 
 by the application layer if it wants to enable OOB bonding procedure for any
 specific device identified by "bdHandle". This function should be called
 before initiating authentication or before responding to authentication
 request to set OOB flag and data. For more details on OOB, please refer
 Bluetooth 4.1 core specification, Volume 1, Part A, section 5.2.4.3. This is
 a blocking function. No event is generated on calling this function.
    
Parameters:
 bdHandle: Peer device for which the Out Of Band signalling (OOB) configuration
            is to be used.
 oobFlag: OOB data presence flag. Allowed value are,
           * CYBLE_GAP_OOB_DISABLE
           * CYBLE_GAP_OOB_ENABLE
 key: 16 Octet Temporary Key, to be used for OOB authentication.
 oobData: Pointer to OOB data.
 oobDataLen: Pointer to a variable to store OOB data length.
		
Return Value:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input
                                     parameter
  CYBLE_ERROR_NO_DEVICE_ENTITY      'bdHandle' does not represent
                                     known device entity
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapSetOobData 
					(
					   uint8 	bdHandle,
					   uint8	oobFlag,
					   uint8	* key,
					   uint8	* oobData,
					   uint8	* oobDataLen
					);


/******************************************************************************
##Function Name: CyBle_GapGetPeerBdAddr
*******************************************************************************

Summary:
 This function reads the peer Bluetooth device address which has already been
 fetched by the BLE Stack. 'peerBdAddr' stores the peer's Bluetooth device
 address identified with 'bdHandle'. This is a blocking function. No event is
 generated on calling this function.
    
Parameters:	
 bdHandle: Peer device handle.
 peerBdAddr: Empty buffer where the Bluetooth device address gets stored.

Return Value:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input
                                     parameter for 'peerBdAddr'.
  CYBLE_ERROR_NO_DEVICE_ENTITY      Specified device handle does not
                                     map to any device handle entry
                                     in BLE stack.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerBdAddr(uint8 bdHandle, CYBLE_GAP_BD_ADDR_T* peerBdAddr);


/******************************************************************************
##Function Name: CyBle_GapGetPeerBdHandle
*******************************************************************************

Summary:
 This function reads the device handle of the remote Bluetooth device using 
 'peerBdAddr', which has already been fetched by the BLE Stack. 'bdHandle'
 stores the peer device handle. This is a blocking function. No event is
 generated on calling this function.
    
Parameters:
 bdHandle: Pointer to a variable to store peer device handle
 peerBdAddr: Pointer to Bluetooth device address of peer device of type
              CYBLE_GAP_BD_ADDR_T, to be provided to this function as an input

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                        	-----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'peerBdAddr'
                                         or 'bdHandle'.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
  CYBLE_ERROR_NO_DEVICE_ENTITY          Specified device handle does
                                         not map to any device handle
                                         entry in BLE stack.
 </table>
			
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerBdHandle(uint8* bdHandle, CYBLE_GAP_BD_ADDR_T*   peerBdAddr);


/******************************************************************************
##Function Name: CyBle_GapGetPeerDevSecurity
*******************************************************************************

Summary:
 This function enables the application to get the device security of the peer
 device, which has already been fetched by the BLE Stack, identified using 
 'bdHandle' when the peer device is in the trusted list. This is a blocking
 function. No event is generated on calling this function.

Parameters:
 bdHandle: Peer device handle
 security: Pointer to a buffer into which security information will be written.

Return Value:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                        	-----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'security'.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
  CYBLE_ERROR_NO_DEVICE_ENTITY          Specified device handle does
                                         not map to any device handle
                                         entry in BLE stack.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerDevSecurity (uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T* security);


#ifdef GAP_PERIPHERAL

/******************************************************************************
##Function Name: CyBle_GappEnterDiscoveryMode
*******************************************************************************

Summary:
 This function sets the device into discoverable mode. In the discoverable
 mode, based on the parameters passed to this function, the BLE Device starts
 advertisement and can respond to scan requests. This is a non-blocking 
 function. It is to be used by the device in 'GAP Peripheral' mode of operation
 to set parameters essential for starting advertisement procedure.

 On start of advertisement, the GAP Peripheral receives 
 CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP event. The following two events can
 occur on invoking this function.

 * CYBLE_EVT_GAP_DEVICE_CONNECTED - If the device connects to a GAP Central.

 * CYBLE_EVT_TIMEOUT - If no device in 'GAP Central' mode connects to this 
    device within the specified timeout limit. This event can occur if
    'advInfo ->discMode' is equal to CYBLE_GAPP_LTD_DISC_MODE or
    CYBLE_GAPP_GEN_DISC_MODE. 'advInfo-> advTo' specifies the timeout duration.
    Set the 'advInfo-> advTo' to 0 when 'advInfo -> discMode' is set to
    CYBLE_GAPP_GEN_DISC_MODE so that the timeout event does not occur and the
    advertisement continues until the CyBle_GappExitDiscoveryMode() function
    is invoked.

Parameters:
 advInfo: Structure of type CYBLE_GAPP_DISC_MODE_INFO_T, which contains the
           advertisement parameters
	
Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying null pointer for
                                     'advInfo' or if any of the
                                     elements of this structure have
                                     invalid values.
</table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GappEnterDiscoveryMode (CYBLE_GAPP_DISC_MODE_INFO_T* advInfo);


/******************************************************************************
##Function Name: CyBle_GappExitDiscoveryMode
*******************************************************************************

Summary:
 This function is used to exit from discoverable mode. This is a non-blocking
 function. After the execution of this function, the device stops advertising.

 On stopping advertising, GAP Peripheral receives 
 CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP event. It is expected that the
 application layer keeps track of the function call performed before occurrence
 of this event, as this event can occur on making a call to the
 CyBle_GappEnterDiscoveryMode () function as well.

Parameters:
 None
			
Return:
 None

******************************************************************************/
void CyBle_GappExitDiscoveryMode (void);


#endif /*GAP_PERIPHERAL*/

#ifdef GAP_CENTRAL

/******************************************************************************
##Function Name: CyBle_GapcStartDiscovery
*******************************************************************************

Summary:
 This function starts the discovery of devices which are advertising. This is a 
 non-blocking function. As soon as the discovery operation starts, 
 CYBLE_EVT_GAPC_SCAN_START_STOP event is generated.

 Every Advertisement / Scan response packet received results in a new event,
 CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT. If 'scanInfo->scanTo' is a non-zero value,
 upon commencement of discovery procedure and elapsed time = 'scanInfo->scanTo',
 CYBLE_EVT_TIMEOUT event is generated with the event parameter indicating 
 CYBLE_GAP_SCAN_TO.

 If 'scanInfo->scanTo' is equal to zero, the scanning operation is performed
 until the CyBle_GapcStopDiscovery() function is invoked.
 
 There are three discovery procedures that can be specified as a parameter to
 this function.

 # Observation procedure #
  A device performing the observer role receives only advertisement data from
  devices irrespective of their discoverable mode settings. Advertisement data
  received is provided by the event,
  
  CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
  
  'scanInfo->scanType' should be set as passive scanning (0x00).
    
 # Limited Discovery procedure #
  A device performing the limited discovery procedure receives advertisement
  data and scan response data from devices in the limited discoverable mode only.
  Received data is provided by the event,
  
  CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
  
  'scanInfo->scanType' should be set as active scanning (0x01).

 # General Discovery procedure #
  A device performing the general discovery procedure receives the advertisement
  data and scan response data from devices in both limited discoverable mode and
  the general discoverable mode. Received data is provided by the event,

  CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT 
  
  'scanInfo->scanType' should be set as active scanning (0x01).

Parameters:
	scanInfo:  Pointer to a variable of type CYBLE_GAPC_DISC_INFO_T,
		
Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'scanInfo' or
                                         if any element within 
                                         'scanInfo' has an invalid
                                         value.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcStartDiscovery(CYBLE_GAPC_DISC_INFO_T* scanInfo);


/******************************************************************************
##Function Name: CyBle_GapcStopDiscovery
*******************************************************************************

Summary:
 This function stops the discovery of devices. This is a non-blocking function.
 On stopping discovery operation, CYBLE_EVT_GAPC_SCAN_START_STOP event is
 generated. Application layer needs to keep track of the function call made
 before receiving this event to associate this event with either the start or
 stop discovery function.

Parameters:
 None
			
Return:
 None

******************************************************************************/
void CyBle_GapcStopDiscovery(void);


/******************************************************************************
##Function Name: CyBle_GapcInitConnection
*******************************************************************************

Summary:
 This function sends a connection request to the remote device with required 
 connection parameters. On successful connection, the following events are
 generated at the GAP Central end (as well as the GAP Peripheral end), in order.
  * CYBLE_EVT_GATT_CONNECT_IND
  * CYBLE_EVT_GAP_DEVICE_CONNECTED

 This is a non-blocking function. This function needs to be called after
 successfully stopping scanning. Scanning is successfully stopped on invoking
 the CyBle_GapcStopDiscovery() function and receiving the event
 CYBLE_EVT_GAPC_SCAN_START_STOP with the event data of '0x01',
 indicating success.

 For details related to connection modes and procedures, refer to Bluetooth
 4.1 Core Specification, Volume 3, Part C, Section 9.3.
    
Parameters:
 connParam: Structure of type 'CYBLE_GAPC_CONN_PARAM_T' which contains the
             connection parameters.

            <b>Note</b> Any parameter of structure type CYBLE_GAPC_CONN_PARAM_T,
            if not required by a specific Bluetooth Low Energy profile, may
            be ignored.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'connParam'or
                                         if any element within 
                                         'connParam' has an invalid
                                         value.
  CYBLE_ERROR_INVALID_OPERATION         Device already connected.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcInitConnection(CYBLE_GAPC_CONN_PARAM_T* connParam);


/******************************************************************************
##Function Name: CyBle_GapcCancelConnection
*******************************************************************************

Description:
 This function cancels a previously initiated connection with the peer device.
 This is a blocking function. No event is generated on calling this function.

 If the devices are already connected, then this function should not be used.
 To disconnect from an existing connection, use the function 
 CyBle_GapDisconnect().

Parameters:
 None

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                              Description
  ------------                              -----------
  CYBLE_ERROR_OK                            On successful operation.
  CYBLE_ERROR_INVALID_OPERATION             Device already connected.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED      Memory allocation failed.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcCancelConnection(void);

#endif /* GAP_CENTRAL */


/******************************************************************************
##Function Name: CyBle_GapDisconnect
*******************************************************************************

Summary:
 This function disconnects the peer device. It is to be used by the device in
 GAP Central mode and may be used by a GAP Peripheral device to send a
 disconnect request. This is a non-blocking function. On disconnection, the
 following events are generated, in order.
 * CYBLE_EVT_GATT_DISCONNECT_IND
 * CYBLE_EVT_GAP_DEVICE_DISCONNECTED
    
Parameters:
 bdHandle:  Peer device handle

Return Value:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         No device to be disconnected.
                                         The specified device handle
                                         does not map to any device
                                         entry in the BLE Stack.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapDisconnect (uint8 bdHandle);


#ifdef GAP_CENTRAL
#ifdef HOST_RESOLVE_PVT_ADDR

/******************************************************************************
##Function Name: CyBle_GapcResolveDevice
*******************************************************************************

Summary:
 This function enables the application to start resolution procedure for a
 device that is connected using resolvable private address. This is a blocking function. 
 Application should use this function when in GAP Central mode.

 Refer to Bluetooth 4.1 Core specification, Volume 3, Part C, section 10.8.2.3
 Resolvable Private Address Resolution Procedure to understand the usage of 
 Private addresses.

Parameters:
 bdAddr: Pointer to peer bluetooth device address of length 6 bytes, not
          NULL terminated.
 irk: Pointer to 128-bit IRK to be used for resolving the peer's private
       resolvable address.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input
                                     parameter for 'bdAddr' or 'irk'.
  CYBLE_ERROR_INVALID_OPERATION     No device to be resolved. The
                                     specified device handle does not
                                     map to any device entry in the
                                     BLE Stack.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcResolveDevice(const uint8 *bdAddr, const uint8 *irk);

#endif /* HOST_RESOLVE_PVT_ADDR */
#endif /* GAP_CENTRAL */


/******************************************************************************
##Function Name: CyBle_GapGetPeerDevSecurity
*******************************************************************************

Summary:
 This API enables the application to get the device security of the peer device
 identified by the bdHandle, when in the trusted list.

 # Security #
  The security requirement of a device is expressed in terms of a security mode
  and security level. A physical connection between two devices shall operate
  in only one security mode.

  There are two LE security modes. For details refer to section Part C, 10.2
  of BLE Spec 4.0. 
  * LE security mode 1
  * LE security mode 2 

  Security of the device is set as,
  * Security = Le security Mode (X) | Security level (level(mode X))
     * X = mode 1 or mode 2
     * level(mode 1)) = Security level 1 or Security level 2 or Security level 3
     * level(mode 2)) = Security level 1 or Security level 2

 # Bonding #
  Bonding will be set to 1 if bonding is required for the device. The purpose
  of bonding (Bonding = 1) is to create a relation between two Bluetooth devices
  based on a common link key (a bond). The link key is created and exchanged
  (pairing) during the bonding procedure and is expected to be stored by both
  Bluetooth devices, to be used for future authentication.

 # ekeySize #
  Each device shall have maximum and minimum encryption key length parameters
  which defines the maximum and minimum size of the encryption key allowed in
  octets. The maximum and minimum encryption key length parameters is between
  7 octets (56 bits) and 16 octets (128 bits). This is defined by the profile
  or device application. 
  
  The smaller value of the initiating and responding devices' maximum encryption
  key length parameters is used as the encryption key size. Both the initiating
  and responding devices will check that the resultant encryption key size is
  not smaller than the minimum key size parameter for that device and if it is,
  the device will send the Pairing Failed event. i.e. Host stack IP will send 
  CYBLE_EVT_PAIRING_FAILED event to the profile.

Parameters:
 bdHandle: Peer device handle.
 security: Buffer to where Security information will be written.

Return Value:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'bdAddr' 
                                         or 'irk'.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
  CYBLE_ERROR_NO_DEVICE_ENTITY          Specified device handle does
                                         not map to any device handle
                                         entry in BLE stack.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerDevSecurity (uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T* security);


/******************************************************************************
##Function Name: CyBle_GapGetPeerDevSecurityKeyInfo
*******************************************************************************

Summary:
 This function enables the application to know the keys shared by a given peer 
 device upon completion of the security sequence (already fetched by the BLE
 Stack). The keys are shared by the peer device on initiation of authentication
 which is performed using the CyBle_GapAuthReq() or CyBle_GappAuthReqReply()
 function.

 This is a blocking function. No event is generated on calling this function.
    
Parameters:
 bdHandle: Peer device handle.
 *keysFlag: Indicates the keys to be retrieved from peer device. The following
             bit fields indicate the presence or absence of the keys distributed.
             
             <b>Negotiated Local/Peer Key distribution</b>
              * Bit 0. Encryption information (LTK and MID Information)
              * Bit 1. Identity information
              * Bit 2. Signature Key
              * Bit 3-7. Reserved
 *key_info:  Pointer to variable of type CYBLE_GAP_SMP_KEY_DIST_T to copy the
              stored keys of the peer device identified by 'bdHandle'

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input
                                     parameter for 'keyInfo'.
  CYBLE_ERROR_INVALID_OPERATION	    An error occurred in BLE stack.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetPeerDevSecurityKeyInfo
                (
                    uint8 bdHandle,
                    uint8 *keysFlag,
                    CYBLE_GAP_SMP_KEY_DIST_T *keyInfo
                );


/******************************************************************************
##Function Name: CyBle_GapGenerateDeviceAddress
*******************************************************************************

Summary:
 This function generates either public or random address based on 'type' field
 of CYBLE_GAP_BD_ADDR_T structure. It uses BLE Controller's random number
 generator to generate the random part of the Bluetooth device address.

 The parameter 'addrType' specifies further sub-classification within the
 public and random address types.
 
 This is a blocking function. No event is generated on calling this function.

Parameters:
 bdAddr: Bluetooth device address is generated and populated in the structure
          pointed to by this pointer. The structure is of type 
          CYBLE_GAP_BD_ADDR_T.
 addrType: Specifies the type of address. This can take one of the values 
            from the enumerated data type CYBLE_GAP_ADDR_TYPE_T.
 irk: Pointer to buffer containing 128-bit 'IRK' data. This parameter is only
       used when CYBLE_GAP_RANDOM_PRIV_RESOLVABLE_ADDR is the value set to
       'addrType'. For other values of 'addrType', this parameter is not used.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input
                                     parameter.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGenerateDeviceAddress
                (
                    CYBLE_GAP_BD_ADDR_T*	bdAddr,
                    CYBLE_GAP_ADDR_TYPE_T	addrType,
                    uint8 *irk
                );


/******************************************************************************
##Function Name: CyBle_GapSetSecurityKeys
*******************************************************************************

Summary:
 This function sets the security keys that are to be exchanged with peer
 device during key exchange stage of authentication procedure and sets it in the 
 BLE Stack. This is a blocking function. No event is generated on calling this function.
    
Parameters:              
 keysFlag: This parameter indicates which keys get exchanged with peer device.
            The following is the bit field mapping for the keys.

             <b>First 4 bits. Initiator's Key distribution</b>
                 * Bit 0. Encryption information (LTK and MID Information)
                 * Bit 1. Identity information
                 * Bit 2. Signature Key
                 * Bit 3. Reserved
             
             <b>Next 4 bits. Responder's Key distribution</b>
                 * Bit 4. Encryption information (LTK and MID Information)
                 * Bit 5. Identity information
                 * Bit 6. Signature Key
                 * Bit 7. Reserved
 keyInfo: Pointer to a variable containing the keys to be set, of type 
           'CYBLE_GAP_SMP_KEY_DIST_T'. idAddrInfo param of 'CYBLE_GAP_SMP_KEY_DIST_T'
           will be ignored. 'CyBle_SetDeviceAddress' api needs to be used to set bd address.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'keyInfo'
 </table>

******************************************************************************/    
CYBLE_API_RESULT_T CyBle_GapSetSecurityKeys(uint8 keysFlag, CYBLE_GAP_SMP_KEY_DIST_T *keyInfo);


/******************************************************************************
##Function Name: CyBle_GapGenerateKeys
*******************************************************************************

Summary:
 This function generates the security keys that are to be exchanged with peer
 device during key exchange stage of authentication procedure and sets it in the 
 BLE Stack. This is a blocking function. No event is generated on calling this function.
    
Parameters:              
 keysFlag: This parameter indicates which keys get exchanged with peer device.
            The following is the bit field mapping for the keys.

             <b>First 4 bits. Initiator's Key distribution</b>
                 * Bit 0. Encryption information (LTK and MID Information)
                 * Bit 1. Identity information
                 * Bit 2. Signature Key
                 * Bit 3. Reserved
             
             <b>Next 4 bits. Responder's Key distribution</b>
                 * Bit 4. Encryption information (LTK and MID Information)
                 * Bit 5. Identity information
                 * Bit 6. Signature Key
                 * Bit 7. Reserved
 keyInfo: Pointer to a variable containing the returned keys, of type 
           'CYBLE_GAP_SMP_KEY_DIST_T'

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'keyInfo'
 </table>

******************************************************************************/    
CYBLE_API_RESULT_T CyBle_GapGenerateKeys(uint8 keysFlag, CYBLE_GAP_SMP_KEY_DIST_T *keyInfo);


/******************************************************************************
##Function Name: CyBle_GapAuthReq
*******************************************************************************

Summary:
 This function starts authentication/pairing procedure with the peer device. 
 It is a non-blocking function.
 
 If the local device is a GAP Central, the pairing request is sent to the GAP
 Peripheral device. On receiving CYBLE_EVT_GAP_AUTH_REQ event, the GAP
 Peripheral is expected to respond by invoking the CyBle_GappAuthReqReply()
 function.

 If the local device is GAP Peripheral, a Security Request is sent to GAP
 Central device. On receiving CYBLE_EVT_GAP_AUTH_REQ event, the GAP Central
 device is expected to respond by invoking 'CyBle_GapAuthReq ()' function.

Parameters:
 bdHandle: Peer device handle
 authInfo: Pointer to security information of the device of type 
            CYBLE_GAP_AUTH_INFO_T. The 'authErr' parameter in 
            CYBLE_GAP_AUTH_INFO_T should be ignored as it is not used in 
            this function.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'authInfo' or
                                         assigning an invalid value
                                         to one of the elements of
                                         'authInfo'.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
  CYBLE_ERROR_NO_DEVICE_ENTITY          No device entry in the BLE
                                         stack to run this operation.
  CYBLE_ERROR_INSUFFICIENT_RESOURCES 	On bonded device is full 
  							and application tries to initiate pairing with 
  							bonding enable.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAuthReq(uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T *authInfo);


#ifdef GAP_PERIPHERAL

/******************************************************************************
##Function Name: CyBle_GappAuthReqReply
*******************************************************************************

Summary:
 This function is used to pass security information for authentication in reply
 to an authentication request from the master device. It should be invoked on
 receiving CYBLE_EVT_GAP_AUTH_REQ event. Events shown in the following table
 may be received by the application based on the authentication result.
 <table>
  Event                         Parameter Description
  -----                         ---------------------
  CYBLE_EVT_TIMEOUT             With error code CYBLE_GAP_PAIRING_PROCESS_TO
                                 on invoking CyBle_GappAuthReqReply() or 
                                 CyBle_GapAuthReq() if there is no response 
                                 from the peer device.

  CYBLE_EVT_GAP_AUTH_COMPLETE   Pointer to structure of type 
                                 'CYBLE_GAP_AUTH_INFO_T' is returned as 
                                 parameter to both the peer devices on 
                                 successful authentication.

  CYBLE_EVT_GAP_AUTH_FAILED     Received by both GAP Central and Peripheral
                                 devices (peers) on authentication failure.
                                 Data is of type CYBLE_GAP_AUTH_FAILED_REASON_T.
 </table>

Parameters:
 bdHandle: Peer device handle.
 authInfo: Pointer to a variable containing security information of the device
            of type CYBLE_GAP_AUTH_INFO_T.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying null pointer
                                         for 'advInfo' or if any of
                                         the element of this structure
                                         has an invalid value.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed
  CYBLE_ERROR_NO_DEVICE_ENTITY          Device identified using 
                                         'bdHandle' does not exist.
  CYBLE_ERROR_INSUFFICIENT_RESOURCES 	On bonded device is full 
  							and application tries to initiate pairing with 
  							bonding enable.                                         
</table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GappAuthReqReply(uint8 bdHandle, CYBLE_GAP_AUTH_INFO_T *authInfo);


#endif /* GAP_PERIPHERAL */

/******************************************************************************
##Function Name: CyBle_GapAuthPassKeyReply
*******************************************************************************

Summary:
 This function sends passkey for authentication. It is a non-blocking function.

 It should be invoked in reply to the authentication request event
 CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST received by the BLE Stack. This function
 is used to accept the passkey request and send the passkey or reject the
 passkey request.
 
 * If the authentication operation succeeds, CYBLE_EVT_GAP_AUTH_COMPLETE is
    generated. If the authentication process times out, CYBLE_EVT_TIMEOUT 
    event is generated.
 * If the authentication fails, CYBLE_EVT_GAP_AUTH_FAILED event is generated.

Parameters:
 bdHandle: Peer device handle
 passkey: 6-digit decimal number (authentication passkey)
 accept: Accept or reject passkey entry request. Allowed values are,
          * CYBLE_GAP_REJECT_PASSKEY_REQ
          * CYBLE_GAP_ACCEPT_PASSKEY_REQ

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         Invalid parameter.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
  CYBLE_ERROR_NO_DEVICE_ENTITY          Device identified using
                                         'bdHandle' does not exist.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAuthPassKeyReply(uint8 bdHandle, uint32 passkey, uint8 accept);


/******************************************************************************
##Function Name: CyBle_GapRemoveDeviceFromWhiteList
*******************************************************************************

Summary:
 This function marks the device specified by the handle as untrusted. It removes the bonding information
 of the device and removes it from the white list. More details on 'bonding' and 'trusted devices' is
 available in Bluetooth 4.1 core specification, Volume 3, Part C, section 9.4.4.

 This is a blocking function. No event is generated on calling this function.

Parameters:
 bdAddr: Pointer to peer device address, of type CYBLE_GAP_BD_ADDR_T. If device
          address is set to 0, then all devices shall be removed from trusted
          list and white list.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input 
                                     parameter for 'bdAddr'.
  CYBLE_ERROR_INVALID_OPERATION     Whitelist is already in use.	
  CYBLE_ERROR_NO_DEVICE_ENTITY      Device does not exist in the
                                     whitelist.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapRemoveDeviceFromWhiteList(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
##Function Name: CyBle_GapAddDeviceToWhiteList
*******************************************************************************

Summary:
 This function adds the device to the whitelist. Maximum number of devices that
 can be added to the whitelist is eight including CYBLE_GAP_MAX_BONDED_DEVICE.
 Refer to Bluetooth 4.1 core specification, Volume 3, Part C, section 9.3.5 for more details on whitelist.

 This is a blocking function. No event is generated on calling this function.
    
Parameters:
 bdAddr: Peer device address, of type CYBLE_GAP_BD_ADDR_T.

Return Value:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'bdAddr' or
                                         'bdAddr->type' has an 
                                         invalid value
  CYBLE_ERROR_INVALID_OPERATION         Whitelist is already in use
  CYBLE_ERROR_INSUFFICIENT_RESOURCES    Whitelist memory is full
  CYBLE_ERROR_DEVICE_ALREADY_EXISTS     Matching device already exists
                                         in the whitelist    
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapAddDeviceToWhiteList(CYBLE_GAP_BD_ADDR_T* bdAddr);


/******************************************************************************
##Function Name: CyBle_GapGetBondedDevicesList
*******************************************************************************

Summary:
 This function returns the count and Bluetooth device address of the devices in
 the bonded device list. This is a blocking function. No event is generated on
 calling this function.

 Application invoking this function should allocate sufficient memory for the
 structure CYBLE_GAP_BONDED_DEV_ADDR_LIST_T, where the complete list of bonded
 devices along with count can be written. Maximum devices bonded are specified
 by CYBLE_GAP_MAX_BONDED_DEVICE, which is a pre processing time parameter for
 the BLE Stack. Hence, the bonded device count will be less than or equal to
 CYBLE_GAP_MAX_BONDED_DEVICE.

 Refer Bluetooth 4.1 core specification, Volume 3, Part C, section 9.4.4 for
 details on bonded devices.
    
Parameters:	
 bondedDevList: Buffer to which list of bonded device list will be stored of 
                 type CYBLE_GAP_BONDED_DEV_ADDR_LIST_T.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                      Description
  ------------                      -----------
  CYBLE_ERROR_OK                    On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER     On specifying NULL as input
                                     parameter.
 </table>
			
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetBondedDevicesList(CYBLE_GAP_BONDED_DEV_ADDR_LIST_T* bondedDevList);


/******************************************************************************
##Function Name: CyBle_GapRemoveOldestDeviceFromBondedList
*******************************************************************************

Summary:
 This function removes the oldest device from the bonded list.

Parameters:	
 None.

Return:
	CYBLE_API_RESULT_T : Return value indicates if the function succeeded (0x0000) or failed.
	Following are the possible error codes returned -
	<table>
	Errors codes						Description
	------------                        -----------
	CYBLE_ERROR_OK						On successful operation.
	CYBLE_ERROR_NO_DEVICE_ENTITY 		If no device is present bonded list
	</table>
			
*/
CYBLE_API_RESULT_T CyBle_GapRemoveOldestDeviceFromBondedList (void);

#ifdef GAP_CENTRAL

/******************************************************************************
##Function Name: CyBle_GapcConnectionParamUpdateRequest
*******************************************************************************

Summary:
 This function sends the connection parameter update command to local controller. 
 This function can only be used from device connected in GAP Central role.
 Note: Connection parameter update procedure, defined as part of Bluetooth spec 4.1, is not supported.
         This function will allow GAP Central application to update connection parameter for local controller
         and local controller will follow the procedure as defined in Bluetooth Core specification 4.0.
 

Parameters:
 bdHandle: Peer device handle
 connParam: Pointer to a structure of type CYBLE_GAP_CONN_UPDATE_PARAM_T
            containing connection parameter updates

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.	
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation
  CYBLE_ERROR_INVALID_PARAMETER         'connParam' is NULL
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcConnectionParamUpdateRequest
           (
               	uint8  	     		 			bdHandle,
				CYBLE_GAP_CONN_UPDATE_PARAM_T	*connParam
           );


/******************************************************************************
##Function Name: CyBle_GapcSetHostChannelClassification
*******************************************************************************

Summary:
 This function sets channel classification for data channels. This
 classification persists until it is overwritten by a subsequent call to this
 function or the controller is reset. If this command is used, updates should
 be sent within 10 seconds of the BLE Host knowing that the channel
 classification has changed. The interval between two successive commands sent
 will be at least one second. This command will only be used when the local
 device supports the Master role. 
 
 For details, refer to Bluetooth core specification 4.1, Volume 2, part E,
 section 7.8.19.

 This is a blocking function. No event is generated on calling this function.

Parameters:
 channelMap: This parameter contains five octet byte stream (Least Significant
              Byte having the bit fields 0 to 7, most significant byte having
              the bit fields 32 to 36). The nth such field (in the range 0 to
              36) contains the value for the link layer channel index n. 
              Allowed values and their interpretation are,
              * Channel 'n' is bad = 0x00u
              * Channel 'n' is unknown = 0x01u
                
              The most significant bits (37 to 39) are reserved and will be 
              set to 0. At least one channel will be marked as unknown.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input
                                         parameter for 'channelMap'.
  CYBLE_ERROR_MEMORY_ALLOCATION_FAILED  Memory allocation failed.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcSetHostChannelClassification
           (
               	uint8*   channelMap
           );

           
#endif /* GAP_CENTRAL */

/******************************************************************************
##Function Name: CyBle_GapGetDevSecurityKeyInfo
*******************************************************************************

Summary:
 This function gets the local device's Keys and key flags. The IRK received from
 this function should be used as the input IRK for the function 
 'CyBle_GapGenerateDeviceAddress' to generate Random Private Resolvable address.
 This is a blocking function. No event is generated on calling this function.

Parameters:
 keyFlags:	Pointer to a byte where the key flags are stored. Based
			 on the flag bits, the calling application can determine if
			 the returned value is valid (1) or not (0).
			 Key distribution flag
			 * Bit 0: Local Encryption information
			 * Bit 1: Local Identity information
			 * Bit 2: Local Signature Key
			 * Bit 3 - Bit 7: Reserved
 keys:		Pointer to a structure of type CYBLE_GAP_SMP_KEY_DIST_T
			 where the keys get stored

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.
 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         On specifying NULL as input parameters
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapGetDevSecurityKeyInfo
(
   uint8  					* keyFlags,
   CYBLE_GAP_SMP_KEY_DIST_T	* keys
);

#ifdef GAP_PERIPHERAL
/******************************************************************************
##Function Name: CyBle_GapUpdateAdvData
*******************************************************************************

Summary:
 This function allows changing the ADV data and SCAN response data while 
 advertising is going on. Application shall preserve Bluetooth Spec 4.1
 mandated AD flags fields corresponding to the type of GAP discovery mode and
 only change the rest of the data.
 
Parameters:
 advData:	   Pointer to a structure of CYBLE_GAPP_DISC_DATA_T. It has two fields
               advData field representing the data and advDataLen indicating the
               length of present data. Application can pass this parameter as
               NULL for if the ADV data doesn't need to be changed.
 
 scanRespData: Pointer to a structure of type CYBLE_GAPP_SCAN_RSP_DATA_T. It 
               has two fields scanRspData field representing the data and 
               scanRspDataLen indicating the the length of present data. 
               Application can pass this parameter as NULL if the SCAN RESP
               data doesn't need to be changed.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.

 <table>
  Errors codes                          Description
  ------------                          -----------
  CYBLE_ERROR_OK                        On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER         Data length in input
                                        parameter exceeds 31 bytes.
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapUpdateAdvData
(
   CYBLE_GAPP_DISC_DATA_T   	* advDiscData,
   CYBLE_GAPP_SCAN_RSP_DATA_T	* advScanRespData
);
#endif /* GAP_PERIPHERAL */

#ifdef GAP_CENTRAL
/******************************************************************************
##Function Name: CyBle_GapcSetRemoteAddr
*******************************************************************************

Summary:
 This function allows application to set the new address of remote device identified by bdHandle.
 This API should be used when-
 1. If peer device is previously bonded with public address and changes its bd address to resolvable private address. 
     Application should resolve the device by calling 'CyBle_GapcResolveDevice()' api and set the 
     new address if successfully resolved.
 2. If device is previously bonded with random, application should call this api to set the new address(public/random).

Parameters:
 bdHandle: Peer device handle

 remoteAddr: Peer device address, of type CYBLE_GAP_BD_ADDR_T.

Return:
 CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
 failed. Following are the possible error codes.

 <table>
  Errors codes                          		Description
  ------------                         		    -----------
  CYBLE_ERROR_OK                        		On successful operation.
  CYBLE_ERROR_INVALID_PARAMETER                 On invalid bdHandle
                                        
 </table>

******************************************************************************/
CYBLE_API_RESULT_T CyBle_GapcSetRemoteAddr
(
   uint8     			bdHandle,
   CYBLE_GAP_BD_ADDR_T  remoteAddr
);
#endif  /* GAP_CENTRAL */

#endif /* CY_BLE_CYBLE_GAP_H */


/*EOF*/
