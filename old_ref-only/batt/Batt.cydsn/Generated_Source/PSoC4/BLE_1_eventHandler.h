/*******************************************************************************
File Name: CYBLE_eventHandler.h
Version 1.20

Description:
 Contains the prototypes and constants used in the Event Handler State Machine
 of the BLE Component.

********************************************************************************
Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
You may use this file only in accordance with the license, terms, conditions,
disclaimers, and limitations in the end user license agreement accompanying
the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CYBLE_EH_H)
#define CY_BLE_CYBLE_EH_H


/***************************************
##Service specific includes
***************************************/

#include "BLE_1_gatt.h"

#ifdef CYBLE_ANS
    #include "BLE_1_ans.h"
#endif /* CYBLE_ANS */
#ifdef CYBLE_BAS
    #include "BLE_1_bas.h"
#endif /* CYBLE_BAS */
#ifdef CYBLE_BLS
    #include "BLE_1_bls.h"
#endif /* CYBLE_BLS */
#ifdef CYBLE_CGMS
    #include "BLE_1_cgms.h"
#endif /* CYBLE_CGMS */
#ifdef CYBLE_CPS
    #include "BLE_1_cps.h"
#endif /* CYBLE_CPS */
#ifdef CYBLE_CSCS
    #include "BLE_1_cscs.h"
#endif /* CYBLE_CSCS */
#ifdef CYBLE_CTS
    #include "BLE_1_cts.h"
#endif /* CYBLE_CTS */
#ifdef CYBLE_DIS
    #include "BLE_1_dis.h"
#endif /* CYBLE_DIS */
#ifdef CYBLE_GLS
    #include "BLE_1_gls.h"
#endif /* CYBLE_GLS */
#ifdef CYBLE_HIDS
    #include "BLE_1_hids.h"
#endif /* CYBLE_HIDS */
#ifdef CYBLE_HRS
    #include "BLE_1_hrs.h"
#endif /* CYBLE_HRS */
#ifdef CYBLE_HTS
    #include "BLE_1_hts.h"
#endif /* CYBLE_HTS */
#ifdef CYBLE_IAS
    #include "BLE_1_ias.h"
#endif /* CYBLE_IAS */
#ifdef CYBLE_LLS
    #include "BLE_1_lls.h"
#endif /* CYBLE_LLS */
#ifdef CYBLE_LNS
    #include "BLE_1_lns.h"
#endif /* CYBLE_LNS */
#ifdef CYBLE_NDCS
    #include "BLE_1_ndcs.h"
#endif /* CYBLE_NDCS */
#ifdef CYBLE_PASS
    #include "BLE_1_pass.h"
#endif /* CYBLE_PASS */
#ifdef CYBLE_RSCS
    #include "BLE_1_rscs.h"
#endif /* CYBLE_RSCS */
#ifdef CYBLE_RTUS
    #include "BLE_1_rtus.h"
#endif /* CYBLE_RTUS */
#ifdef CYBLE_SCPS
    #include "BLE_1_scps.h"
#endif /* CYBLE_SCPS */
#ifdef CYBLE_TPS
    #include "BLE_1_tps.h"
#endif /* CYBLE_TPS */
#ifdef CYBLE_CUSTOM
    #include "BLE_1_custom.h"
#endif /* CYBLE_CUSTOM */
#ifdef CYBLE_UDS
    #include "BLE_1_uds.h"
#endif /* CYBLE_UDS */


/***************************************
##Definitions
***************************************/

/* cyBle_eventHandlerFlag defines */
#define CYBLE_CALLBACK                          (0x01u)
#define CYBLE_AUTO_DISCOVERY                    (0x02u)
#define CYBLE_START_FLAG                        (0x04u)
#define CYBLE_STOP_FLAG                         (0x08u)
#define CYBLE_ENABLE_ALL_EVENTS                 (0x10u)
#define CYBLE_DISABLE_AUTOMATIC_AUTH            (0x20u)

#if(CYBLE_GATT_ROLE_CLIENT)
#define CYBLE_DISC_SRVC_INFO_LEN                (4u + CYBLE_GATT_16_BIT_UUID_SIZE)
#define CYBLE_DISC_SRVC_INFO_128_LEN            (4u + CYBLE_GATT_128_BIT_UUID_SIZE)
#define CYBLE_DISC_INCL_INFO_LEN                (6u + CYBLE_GATT_16_BIT_UUID_SIZE)
#define CYBLE_DISC_INCL_INFO_128_LEN            (6u)
#define CYBLE_DISC_CHAR_INFO_LEN                (5u + CYBLE_GATT_16_BIT_UUID_SIZE)
#define CYBLE_DISC_CHAR_INFO_128_LEN            (5u + CYBLE_GATT_128_BIT_UUID_SIZE)
#define CYBLE_DISC_DESCR_INFO_LEN               (2u + CYBLE_GATT_16_BIT_UUID_SIZE)
#define CYBLE_DISC_DESCR_INFO_128_LEN           (2u + CYBLE_GATT_128_BIT_UUID_SIZE)
#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
##Type Definitions
***************************************/

/* Service specific events  */
typedef enum
{
    /***************************************
    ##Security Events
    ***************************************/
    /* DOM-IGNORE-BEGIN */
    CYBLE_AUTHENTICATION_REQUEST_REPLY = CYBLE_EVT_MAX + 1, /* 0x100 */
    CYBLE_PASSKEY_ENTRY_REQUEST_REPLY,
    CYBLE_LONG_TERM_KEY_REQUEST_REPLY,
    CYBLE_KEY_EXCHANGE_INFO_REQUEST_REPLY,
    /* DOM-IGNORE-END */
    
    /***************************************
    ##GATT Service Events
    ***************************************/
    
    /* GATT Server - Notifications for GATT Service's "Service Changed"
        Characteristic were enabled. The parameter of this event is a structure of
        CYBLE_GATTS_WRITE_REQ_PARAM_T type.
    */
    CYBLE_EVT_GATTS_INDICATION_ENABLED,
    
    /* GATT Server - Notifications for GATT Service's "Service Changed"
        Characteristic were disabled. The parameter of this event is a structure of
        CYBLE_GATTS_WRITE_REQ_PARAM_T type.
    */
    CYBLE_EVT_GATTS_INDICATION_DISABLED,
    
    /* GATT Client - GATT Service's "Service Changed" Characteristic Indications 
        were received. The parameter of this event is a structure
        of CYBLE_ANS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GATTC_INDICATION,
    
    
    /***************************************
    ##Service Discovery Events
    ***************************************/
    
    /* GATT Client - Service discovery procedure failed. This event may
        be generated on calling CyBle_GattcDiscoverAllPrimaryServices().
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_SRVC_DISCOVERY_FAILED,
    
    /* GATT Client - Discovery of included services failed. This event may
        be generated on calling CyBle_GattcFindIncludedServices().
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_INCL_DISCOVERY_FAILED,
    
    /* GATT Client - Discovery of service's characteristics failed. This event may
        be generated on calling CyBle_GattcDiscoverAllCharacteristics() or
        CyBle_GattcReadUsingCharacteristicUuid(). 
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_CHAR_DISCOVERY_FAILED,
    
    /* GATT Client - Discovery of service's characteristics failed. This event may
        be generated on calling CyBle_GattcDiscoverAllCharacteristicDescriptors().
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_DESCR_DISCOVERY_FAILED,
    
    /* GATT Client - Duplicate service record was found during server device
        discovery. The parameter of this event is a structure of uint16 (UUID16)
        type.
    */
    CYBLE_EVT_GATTC_SRVC_DUPLICATION,
    
    /* GATT Client - Duplicate service's characteristic record was found during 
        server device discovery. The parameter of this event is a structure
        of uint16 (UUID16) type.
    */
    CYBLE_EVT_GATTC_CHAR_DUPLICATION,
    
    /* GATT Client - Duplicate service's characteristic descriptor record was found
        during server device discovery. The parameter of this event is a structure
        of uint16 (UUID16) type.
    */
    CYBLE_EVT_GATTC_DESCR_DUPLICATION,
    
    /* GATT Client - Service discovery procedure completed successfully. This
        event may be generated on calling CyBle_GattcDiscoverAllPrimaryServices().
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_SRVC_DISCOVERY_COMPLETE,
    
    /* GATT Client - Included services discovery is completed
        successfully. This event may be generated on calling
        CyBle_GattcFindIncludedServices().
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_INCL_DISCOVERY_COMPLETE,
    
    /* GATT Client - Discovery of service's characteristics discovery is completed
        successfully. This event may be generated on calling
        CyBle_GattcDiscoverAllCharacteristics() or
        CyBle_GattcReadUsingCharacteristicUuid().
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_CHAR_DISCOVERY_COMPLETE,
    
    /* GATT Client - Discovery of remote device completed successfully.
        No parameters passed for this event.
    */
    CYBLE_EVT_GATTC_DISCOVERY_COMPLETE,
    
    
    /***************************************
    ##ANS Service Events
    ***************************************/
    
    /* ANS Server - Notifications for Alert Notification Service Characteristic
        were enabled. The parameter of this event is a structure of
        CYBLE_ANS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_ANSS_NOTIFICATION_ENABLED,
    
    /* ANS Server - Notifications for Alert Notification Service Characteristic
        were disabled. The parameter of this event is a structure of
        CYBLE_ANS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_ANSS_NOTIFICATION_DISABLED,

    /* ANS Server - Write Request for Alert Notification Service Characteristic 
        was received. The parameter of this event is a structure
        of CYBLE_ANS_CHAR_VALUE_T type.
    */  
    CYBLE_EVT_ANSS_CHAR_WRITE,
    
    /* ANS Client - Alert Notification Characteristic Service Notification 
        was received. The parameter of this event is a structure
        of CYBLE_ANS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_ANSC_NOTIFICATION,
    
    /* ANS Client - Read Response for Alert Notification Service Characteristic
        Value. The parameter of this event is a structure of 
        CYBLE_ANS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_ANSC_READ_CHAR_RESPONSE,

    /* ANS Client - Write Response for Write Request for Alert Notification Service
        Characteristic Value. The parameter of this event is a structure of 
        CYBLE_ANS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_ANSC_WRITE_CHAR_RESPONSE,

    /* ANS Client - Read Response for Read Request for Alert Notification Service
        Characteristic Descriptor Read Request. The parameter of this event is a
        structure of CYBLE_ANS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_ANSC_READ_DESCR_RESPONSE,

    /* ANS Client - Write Response for Write Request for Alert Notification Service
        Client Characteristic Configuration Descriptor Value. The parameter of
        this event is a structure of CYBLE_ANS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_ANSC_WRITE_DESCR_RESPONSE,

    
    /***************************************
    ##BAS Service Events
    ***************************************/
    
    /* BAS Server - Notifications for Battery Level Characteristic were enabled. The
        parameter of this event is a structure of CYBLE_BAS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_BASS_NOTIFICATION_ENABLED,
    
    /* BAS Server - Notifications for Battery Level Characteristic were disabled. The
        parameter of this event is a structure of CYBLE_BAS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_BASS_NOTIFICATION_DISABLED,
    
    /* BAS Client - Battery Level Characteristic Notification was received. The 
        parameter of this event is a structure of CYBLE_BAS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_BASC_NOTIFICATION,
    
    /* BAS Client - Read Response for Battery Level Characteristic Value. The 
        parameter of this event is a structure of CYBLE_BAS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_BASC_READ_CHAR_RESPONSE,
    
    /* BAS Client - Read Response for Battery Level Characteristic Descriptor Read 
        Request. The parameter of this event is a structure of 
        CYBLE_BAS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_BASC_READ_DESCR_RESPONSE,
    
    /* BAS Client - Write Response for Battery Level Client Characteristic 
        Configuration Descriptor Value. The parameter of this event is a structure of 
        CYBLE_BAS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_BASC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##Blood Pressure Service Events
    ***************************************/
    
    /* BLS Server - Indication for Blood Pressure Service Characteristic was enabled.
        The parameter of this event is a structure of CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSS_INDICATION_ENABLED,
    
    /* BLS Server - Indication for Blood Pressure Service Characteristic was 
        disabled. The parameter of this event is a structure of 
        CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSS_INDICATION_DISABLED,

    /* BLS Server - Blood Pressure Service Characteristic Indication was confirmed.
        The parameter of this event is a structure of CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSS_INDICATION_CONFIRMED,
 
    /* BLS Server - Notifications for Blood Pressure Service Characteristic
        were enabled. The parameter of this event is a structure of
        CYBLE_BLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_BLSS_NOTIFICATION_ENABLED,
    
    /* BLS Server - Notifications for Blood Pressure Service Characteristic
        were disabled. The parameter of this event is a structure of
        CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSS_NOTIFICATION_DISABLED,
    
    /* BLS Client - Blood Pressure Service Characteristic Indication was received. 
        The parameter of this event is a structure of CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSC_INDICATION,
    
    /* BLS Client - Blood Pressure Service Characteristic Notification was received.
        The parameter of this event is a structure of CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSC_NOTIFICATION,
    
    /* BLS Client - Read Response for Read Request of Blood Pressure Service 
        Characteristic value. The parameter of this event is a structure of
        CYBLE_BLS_CHAR_VALUE_T type
    */
    CYBLE_EVT_BLSC_READ_CHAR_RESPONSE,
    
    /* BLS Client - Read Response for Read Request of Blood Pressure Service 
        Characteristic Descriptor Read request. The parameter of this event is a
        structure of CYBLE_BLS_DESCR_VALUE_T type
    */
    CYBLE_EVT_BLSC_READ_DESCR_RESPONSE,
    
    /* BLS Client - Write Response for Write Request of Blood Pressure Service
        Characteristic Configuration Descriptor value. The parameter of this event
        is a structure of CYBLE_BLS_DESCR_VALUE_T type
    */
    CYBLE_EVT_BLSC_WRITE_DESCR_RESPONSE,
    

    /***************************************
    ##CGM Service Events
    ***************************************/
    
    /* CGMS Server - Indication for Glucose Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSS_INDICATION_ENABLED,
    
    /* CGMS Server - Indication for Glucose Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSS_INDICATION_DISABLED,
    
    /* CGMS Server - Glucose Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSS_INDICATION_CONFIRMED,
    
    /* CGMS Server - Notifications for Glucose Service Characteristic
        was enabled. The parameter of this event is a structure of
        CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSS_NOTIFICATION_ENABLED,
    
    /* CGMS Server - Notifications for Glucose Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSS_NOTIFICATION_DISABLED,
    
    /* CGMS Server - Write Request for Glucose Service 
        was received. The parameter of this event is a structure
        of CYBLE_CGMS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_CGMSS_WRITE_CHAR,
    
    /* CGMS Client - Glucose Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSC_INDICATION,
    
    /* CGMS Client - Glucose Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSC_NOTIFICATION,
    
    /* CGMS Client - Read Response for Read Request of Glucose 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSC_READ_CHAR_RESPONSE,
    
    /* CGMS Client - Write Response for Write Request of Glucose
        Service Characteristic value. The 
        parameter of this event is a structure of
        CYBLE_CGMS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CGMSC_WRITE_CHAR_RESPONSE,
    
    /* CGMS Client - Read Response for Read Request of Glucose
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_CGMS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CGMSC_READ_DESCR_RESPONSE,
    
    /* CGMS Client - Write Response for Write Request of Glucose
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_CGMS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CGMSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##CPS Service Events
    ***************************************/
    
    /* CPS Server - Notifications for Cycling Power Service Characteristic
        was enabled. The parameter of this event is a structure of
        CYBLE_CPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CPSS_NOTIFICATION_ENABLED,
    
    /* CPS Server - Notifications for Cycling Power Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSS_NOTIFICATION_DISABLED,
    
    /* CPS Server - Indication for Cycling Power Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSS_INDICATION_ENABLED,
    
    /* CPS Server - Indication for Cycling Power Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSS_INDICATION_DISABLED,
    
    /* CPS Server - Cycling Power Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSS_INDICATION_CONFIRMED,
    
    /* CPS Server - Broadcast for Cycling Power Service Characteristic
        was enabled. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSS_BROADCAST_ENABLED,
    
    /* CPS Server - Broadcast for Cycling Power Service Characteristic
        was disabled. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSS_BROADCAST_DISABLED,
    
    /* CPS Server - Write Request for Cycling Power Service Characteristic 
        was received. The parameter of this event is a structure
        of CYBLE_CPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CPSS_CHAR_WRITE,
    
    /* CPS Client - Cycling Power Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSC_NOTIFICATION,
    
    /* CPS Client - Cycling Power Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSC_INDICATION,
    
    /* CPS Client - Read Response for Read Request of Cycling Power Service
        Characteristic value. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type
    */
    CYBLE_EVT_CPSC_READ_CHAR_RESPONSE,

    /* CPS Client - Write Response for Write Request of Cycling Power Service
        Characteristic value. The parameter of this event
        is a structure of CYBLE_CPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CPSC_WRITE_CHAR_RESPONSE,
    
    /* CPS Client - Read Response for Read Request of Cycling Power
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_CPS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CPSC_READ_DESCR_RESPONSE,
    
    /* CPS Client - Write Response for Write Request of Cycling Power
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_CPS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CPSC_WRITE_DESCR_RESPONSE,

    /* CPS Client - This event is triggered every time a device receive
        non-connectable undirected advertising event.
        The parameter of this event is a structure of 
        CYBLE_CPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CPSC_SCAN_PROGRESS_RESULT,
    
    /***************************************
    ##Cycling Speed and Cadence Service Events
    ***************************************/
    
    /* CSCS Server - Notifications for Cycling Speed and Cadence Service
        Characteristic were enabled. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSS_NOTIFICATION_ENABLED,

    /* CSCS Server - Notifications for Cycling Speed and Cadence Service
        Characteristic were disabled. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSS_NOTIFICATION_DISABLED,

    /* CSCS Server - Indication for Cycling Speed and Cadence Service Characteristic
        was enabled. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSS_INDICATION_ENABLED,

    /* CSCS Server - Indication for Cycling Speed and Cadence Service Characteristic
        was disabled. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSS_INDICATION_DISABLED,

    /* CSCS Server - Cycling Speed and Cadence Service Characteristic
        Indication was confirmed. The parameter of this event is a structure of 
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSS_INDICATION_CONFIRMATION,

    /* CSCS Server - Write Request for Cycling Speed and Cadence Service
        Characteristic was received. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_CSCSS_CHAR_WRITE,

    /* CSCS Client - Cycling Speed and Cadence Service Characteristic
        Notification was received. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSC_NOTIFICATION,

    /* CSCS Client - Cycling Speed and Cadence Service Characteristic
        Indication was received. The parameter of this event is a structure of 
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSC_INDICATION,

    /* CSCS Client - Read Response for Read Request of Cycling Speed and Cadence 
        Service Characteristic value. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSC_READ_CHAR_RESPONSE,
    
    /* CSCS Client - Write Response for Write Request of Cycling Speed and Cadence 
        Service Characteristic value. The parameter of this event is a structure of
        CYBLE_CSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CSCSC_WRITE_CHAR_RESPONSE,
    
    /* CSCS Client - Read Response for Read Request of Cycling Speed and Cadence
        Service Characteristic Descriptor Read request. The parameter of this event
        is a structure of CYBLE_CSCS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CSCSC_READ_DESCR_RESPONSE,

    /* CSCS Client - Write Response for Write Request of Cycling Speed and Cadence
        Service Characteristic Configuration Descriptor value. The parameter of
        this event is a structure of  CYBLE_CSCS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CSCSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##Current Time Service Events
    ***************************************/
    
    /* CTS Server - Notification for Current Time Characteristic was enabled. The
        parameter of this event is a structure of CYBLE_CTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CTSS_NOTIFICATION_ENABLED,
    
    /* CTS Server - Notification for Current Time Characteristic was disabled. The
        parameter of this event is a structure of CYBLE_CTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CTSS_NOTIFICATION_DISABLED,
    
    /* CTS Client - Current Time Characteristic Notification was received. The
        parameter of this event is a structure of CYBLE_CTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CTSC_NOTIFICATION,
    
    /* CTS Client - Read Response for Current Time Characteristic
        Value Read Request. The parameter of this event is a 
        structure of CYBLE_CTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_CTSC_READ_CHAR_RESPONSE,
    
    /* CTS Client - Read Response for Current Time Client
        Characteristic Configuration Descriptor Value Read 
        Request. The parameter of this event is a 
        structure of CYBLE_CTS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CTSC_READ_DESCR_RESPONSE,
    
    /* CTS Client - Write Response for Current Time Characteristic
        Configuration Descriptor Value. The parameter of this 
        event is a structure of CYBLE_CTS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_CTSC_WRITE_DESCR_RESPONSE,

    
    /***************************************
    ##DIS Service Events
    ***************************************/
    
    /* DIS Client - Read Response for a Read Request for a
        Device Service Characteristic. The parameter of this 
        event is a structure of CYBLE_DIS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_DISC_READ_CHAR_RESPONSE,
    
    
    /***************************************
    ##Glucose Service Events
    ***************************************/
    
    /* GLS Server - Indication for Glucose Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSS_INDICATION_ENABLED,
    
    /* GLS Server - Indication for Glucose Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSS_INDICATION_DISABLED,
    
    /* GLS Server - Glucose Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSS_INDICATION_CONFIRMED,
    
    /* GLS Server - Notifications for Glucose Service Characteristic
        was enabled. The parameter of this event is a structure of
        CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSS_NOTIFICATION_ENABLED,
    
    /* GLS Server - Notifications for Glucose Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSS_NOTIFICATION_DISABLED,
    
    /* GLS Server - Write Request for Glucose Service 
        was received. The parameter of this event is a structure
        of CYBLE_GLS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_GLSS_WRITE_CHAR,
    
    /* GLS Client - Glucose Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSC_INDICATION,
    
    /* GLS Client - Glucose Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSC_NOTIFICATION,
    
    /* GLS Client - Read Response for Read Request of Glucose 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSC_READ_CHAR_RESPONSE,
    
    /* GLS Client - Write Response for Write Request of Glucose
        Service Characteristic value. The 
        parameter of this event is a structure of
        CYBLE_GLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_GLSC_WRITE_CHAR_RESPONSE,
    
    /* GLS Client - Read Response for Read Request of Glucose
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_GLS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_GLSC_READ_DESCR_RESPONSE,
    
    /* GLS Client - Write Response for Write Request of Glucose
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_GLS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_GLSC_WRITE_DESCR_RESPONSE,

    
    /***************************************
    ##HIDS Service Events
    ***************************************/
    
    /* HIDS Server - Notifications for HID service were
        enabled. The parameter of this event is a 
        structure of CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_NOTIFICATION_ENABLED,
    
    /* HIDS Server - Notifications for HID service were
        disabled. The parameter of this event is a 
        structure of CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_NOTIFICATION_DISABLED,
    
    /* HIDS Server - Enter boot mode request. The
        parameter of this event is a structure of
        CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_BOOT_MODE_ENTER,
    
    /* HIDS Server - Enter report mode request. The
        parameter of this event is a structure of
        CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_REPORT_MODE_ENTER,
    
    /* HIDS Server - Enter suspend mode request. The
        parameter of this event is a structure of
        CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_SUSPEND,
    
    /* HIDS Server - Exit suspend mode request. The
        parameter of this event is a structure of
        CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_EXIT_SUSPEND,
    
    /* HIDS Server - Write Report characteristic 
        request. The parameter of this event is a
        structure of CYBLE_HIDSS_REPORT_VALUE_T type.
    */
    CYBLE_EVT_HIDSS_REPORT_CHAR_WRITE,
    
    /* HIDS Client - HID Service Characteristic
        Notification was received. The parameter of this
        event is a structure of CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSC_NOTIFICATION,
    
    /* HIDS Client - Read Response for Read Request of HID
        Service Characteristic value. The parameter of this
        event is a structure of CYBLE_HIDS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_HIDSC_READ_CHAR_RESPONSE,
    
    /* HIDS Client - Write Response for Write Request of
        HID Service Characteristic value. The parameter
        of this event is a structure of 
        CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSC_WRITE_CHAR_RESPONSE,
    
    /* HIDS Client - Read Response for Read Request of HID
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of 
        CYBLE_HIDS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_HIDSC_READ_DESCR_RESPONSE,
    
    /* HIDS Client - Write Response for Write Request of HID
        Service Characteristic Configuration Descriptor value. 
        The parameter of this event is a structure of 
        CYBLE_HIDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HIDSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##HRS Service Events
    ***************************************/
    
    /* HRS Server - Reset Energy Expended. The parameter of 
        this event is a structure of CYBLE_HRS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HRSS_ENERGY_EXPENDED_RESET,
    
    /* HRS Server - Notification for Heart Rate Measurement
        Characteristic was enabled. The parameter of this 
        event is a structure of CYBLE_HRS_CHAR_VALUE_T type.
    */

    CYBLE_EVT_HRSS_NOTIFICATION_ENABLED,
    
    /* HRS Server - Notification for Heart Rate Measurement
        Characteristic was disabled. The parameter of this 
        event is a structure of CYBLE_HRS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_HRSS_NOTIFICATION_DISABLED,
    
    /* HRS Client - Heart Rate Measurement Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_HRS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HRSC_NOTIFICATION,
    
    /* HRS Client - Read Response for Read Request of HRS 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_HRS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HRSC_READ_CHAR_RESPONSE,
    
    /* HRS Client - Write Response for Write Request of HRS 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_HRS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HRSC_WRITE_CHAR_RESPONSE,
    
    /* HRS Client - Read Response for Read Request of HRS
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_HRS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HRSC_READ_DESCR_RESPONSE,
    
    /* HRS Client - Write Response for Write Request of HRS
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_HRS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HRSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##HTS Service Events
    ***************************************/

    /* HTS Server - Notifications for Health Thermometer Service Characteristic
        were enabled. The parameter of this event is a structure of
        CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSS_NOTIFICATION_ENABLED,

    /* HTS Server - Notifications for Health Thermometer Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSS_NOTIFICATION_DISABLED,

    /* HTS Server - Indication for Health Thermometer Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSS_INDICATION_ENABLED,

    /* HTS Server - Indication for Health Thermometer Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSS_INDICATION_DISABLED,

    /* HTS Server - Health Thermometer Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSS_INDICATION_CONFIRMED,

    /* HTS Server - Write Request for Health Thermometer Service Characteristic
        was received. The parameter of this event is a structure
        of CYBLE_HTS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_HTSS_CHAR_WRITE,

    /* HTS Client - Health Thermometer Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSC_NOTIFICATION,

    /* HTS Client - Health Thermometer Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSC_INDICATION,

    /* HTS Client - Read Response for Read Request of Health Thermometer 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSC_READ_CHAR_RESPONSE,

    /* HTS Client - Write Response for Write Request of Health Thermometer 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_HTS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_HTSC_WRITE_CHAR_RESPONSE,

    /* HTS Client - Read Response for Read Request of Health Thermometer
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_HTS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_HTSC_READ_DESCR_RESPONSE,

    /* HTS Client - Write Response for Write Request of Health Thermometer
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_HTS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_HTSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##Immediate Alert Service Events
    ***************************************/
    
    /* IAS Server - Write command request for Alert Level
        Characteristic. The parameter of this event
        is a structure of CYBLE_IAS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_IASS_WRITE_CHAR_CMD,
    
    
    /***************************************
    ##Link Loss Service Events
    ***************************************/
    
    /* LLS Server - Write request for Alert Level Characteristic. 
        The parameter of this event is a structure of 
        CYBLE_LLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LLSS_WRITE_CHAR_REQ,
    
    /* LLS Client - Read response for Alert Level Characteristic.
        The parameter of this event is a structure of 
        CYBLE_LLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LLSC_READ_CHAR_RESPONSE,
    
    /* LLS Client - Write response for write request of Alert
        Level Characteristic. The parameter of this event is a
        structure of CYBLE_LLS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LLSC_WRITE_CHAR_RESPONSE,
    
    
    /***************************************
    ##Location and Navigation Service Events
    ***************************************/

    /* LNS Server - Indication for Location and Navigation Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSS_INDICATION_ENABLED,

    /* LNS Server - Indication for Location and Navigation Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSS_INDICATION_DISABLED,

    /* LNS Server - Location and Navigation Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSS_INDICATION_CONFIRMED,

    /* LNS Server - Notifications for Location and Navigation Service Characteristic
        were enabled. The parameter of this event is a structure of
        CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSS_NOTIFICATION_ENABLED,

    /* LNS Server - Notifications for Location and Navigation Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSS_NOTIFICATION_DISABLED,

    /* LNS Server - Write Request for Location and Navigation Service Characteristic 
        was received. The parameter of this event is a structure
        of CYBLE_LNS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_LNSS_WRITE_CHAR,

    /* LNS Client - Location and Navigation Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSC_INDICATION,

    /* LNS Client - Location and Navigation Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSC_NOTIFICATION,

    /* LNS Client - Read Response for Read Request of Location and Navigation 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSC_READ_CHAR_RESPONSE,

    /* LNS Client - Write Response for Write Request of Location and Navigation 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_LNS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_LNSC_WRITE_CHAR_RESPONSE,

    /* LNS Client - Read Response for Read Request of Location and Navigation
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_LNS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_LNSC_READ_DESCR_RESPONSE,

    /* LNS Client - Write Response for Write Request of Location and Navigation
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_LNS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_LNSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##Next DST Change Service Events
    ***************************************/
    CYBLE_EVT_NDCSC_READ_CHAR_RESPONSE,
    
    
    /***************************************
    ##Phone Alert Status Service Events
    ***************************************/

    /* PASS Server - Notifications for Phone Alert Status Service Characteristic
        were enabled. The parameter of this event is a structure of
        CYBLE_PASS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_PASSS_NOTIFICATION_ENABLED,

    /* PASS Server - Notifications for Phone Alert Status Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_PASS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_PASSS_NOTIFICATION_DISABLED,

    /* PASS Server - Write Request for Phone Alert Status Service Characteristic 
        was received. The parameter of this event is a structure
        of CYBLE_PASS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_PASSS_WRITE_CHAR,

    /* PASS Client - Phone Alert Status Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_PASS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_PASSC_NOTIFICATION,

    /* PASS Client - Read Response for Read Request of Phone Alert Status 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_PASS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_PASSC_READ_CHAR_RESPONSE,

    /* PASS Client - Write Response for Write Request of Phone Alert Status 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_PASS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_PASSC_WRITE_CHAR_RESPONSE,

    /* PASS Client - Read Response for Read Request of Phone Alert Status
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_PASS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_PASSC_READ_DESCR_RESPONSE,

    /* PASS Client - Write Response for Write Request of Phone Alert Status
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_PASS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_PASSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##Running Speed and Cadence Service Events
    ***************************************/

    /* RSCS Server - Notifications for Running Speed and Cadence Service
        Characteristic were enabled. The parameter of this event is a structure of
        CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSS_NOTIFICATION_ENABLED,

    /* RSCS Server - Notifications for Running Speed and Cadence Service
        Characteristic was disabled. The parameter of this event is a structure 
        of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSS_NOTIFICATION_DISABLED,

    /* RSCS Server - Indication for Running Speed and Cadence Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSS_INDICATION_ENABLED,

    /* RSCS Server - Indication for Running Speed and Cadence Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSS_INDICATION_DISABLED,

    /* RSCS Server - Running Speed and Cadence Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSS_INDICATION_CONFIRMATION,

    /* RSCS Server - Write Request for Running Speed and Cadence Service
        Characteristic was received. The parameter of this event is a structure
        of CYBLE_RSCS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_RSCSS_CHAR_WRITE,

    /* RSCS Client - Running Speed and Cadence Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSC_NOTIFICATION,

    /* RSCS Client - Running Speed and Cadence Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSC_INDICATION,

    /* RSCS Client - Read Response for Read Request of Running Speed and Cadence 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSC_READ_CHAR_RESPONSE,

    /* RSCS Client - Write Response for Write Request of Running Speed and Cadence 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_RSCS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RSCSC_WRITE_CHAR_RESPONSE,

    /* RSCS Client - Read Response for Read Request of Running Speed and Cadence
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_RSCS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_RSCSC_READ_DESCR_RESPONSE,

    /* RSCS Client - Write Response for Write Request of Running Speed and Cadence
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_RSCS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_RSCSC_WRITE_DESCR_RESPONSE,

    
    /***************************************
    ##Reference Time Update Service Events
    ***************************************/
    
    /* RTUS Server - Write command request for Reference Time Update
        Characteristic value. The parameter of this event
        is a structure of CYBLE_RTUS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RTUSS_WRITE_CHAR_CMD,
    
    /* RTUS Client - Read Response for Read Request of Reference Time Update
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_RTUS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_RTUSC_READ_CHAR_RESPONSE,
    
    
    /***************************************
    ##Scan Parameters Service Events
    ***************************************/
    
    /* ScPS Server - Notifications for Scan Refresh Characteristic
        were enabled. The parameter of this event is a structure 
        of CYBLE_SCPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_SCPSS_NOTIFICATION_ENABLED,
    
    /* ScPS Server - Notifications for Scan Refresh Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_SCPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_SCPSS_NOTIFICATION_DISABLED,
    
    /* ScPS Client - Read Response for Scan Interval Window 
        Characteristic Value of Scan Parameters Service. The 
        parameter of this event is a structure 
        of CYBLE_SCPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_SCPSS_SCAN_INT_WIN_CHAR_WRITE,
    
    /* ScPS Client - Scan Refresh Characteristic Notification 
        was received. The parameter of this event is a 
        structure of CYBLE_SCPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_SCPSC_NOTIFICATION,
    
    /* ScPS Client - Read Response for Scan Refresh Characteristic
        Descriptor Read Request. The parameter of this event is a
        structure of CYBLE_SCPS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_SCPSC_READ_DESCR_RESPONSE,
    
    /* ScPS Client - Write Response for Scan Refresh Client 
        Characteristic Configuration Descriptor Value. The
        parameter of this event is a structure of
        CYBLE_SCPS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_SCPSC_WRITE_DESCR_RESPONSE,

    
    /***************************************
    ##Tx Power Service Events
    ***************************************/
    
    /* TPS Server - Notification for Tx Power Level Characteristic
        was enabled. The parameter of this event is a structure of
        CYBLE_TPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_TPSS_NOTIFICATION_ENABLED,
    
    /* TPS Server - Notification for Tx Power Level Characteristic
        was disabled. The parameter of this event is a structure of
        CYBLE_TPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_TPSS_NOTIFICATION_DISABLED,
    
    /* TPS Client - Tx Power Level Characteristic Notification. 
        The parameter of this event is a structure of
        CYBLE_TPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_TPSC_NOTIFICATION,
    
    /* TPS Client - Read Response for Tx Power Level Characteristic
        Value Read Request. The parameter of this event is a 
        structure of CYBLE_TPS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_TPSC_READ_CHAR_RESPONSE,
    
    /* TPS Client - Read Response for Tx Power Level Client 
        Characteristic Configuration Descriptor Value Read Request. 
        The parameter of this event is a structure of 
        CYBLE_TPS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_TPSC_READ_DESCR_RESPONSE,
    
    /* TPS Client - Write Response for Tx Power Level Characteristic
        Descriptor Value Write Request. The parameter of this event
        is a structure of CYBLE_TPS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_TPSC_WRITE_DESCR_RESPONSE,
    
    
    /***************************************
    ##User Data Service Events
    ***************************************/

    /* UDS Server - Indication for User Data Service Characteristic
        was enabled. The parameter of this event is a structure 
        of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSS_INDICATION_ENABLED,

    /* UDS Server - Indication for User Data Service Characteristic
        was disabled. The parameter of this event is a structure 
        of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSS_INDICATION_DISABLED,

    /* UDS Server - User Data Service Characteristic
        Indication was confirmed. The parameter of this event
        is a structure of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSS_INDICATION_CONFIRMED,

    /* UDS Server - Notifications for User Data Service Characteristic
        were enabled. The parameter of this event is a structure of
        CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSS_NOTIFICATION_ENABLED,

    /* UDS Server - Notifications for User Data Service Characteristic
        were disabled. The parameter of this event is a structure 
        of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSS_NOTIFICATION_DISABLED,

    /* UDS Server - Write Request for User Data Service Characteristic 
        was received. The parameter of this event is a structure
        of CYBLE_UDS_CHAR_VALUE_T type.
    */    
    CYBLE_EVT_UDSS_WRITE_CHAR,

    /* UDS Client - User Data Service Characteristic
        Indication was received. The parameter of this event
        is a structure of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSC_INDICATION,

    /* UDS Client - User Data Service Characteristic
        Notification was received. The parameter of this event
        is a structure of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSC_NOTIFICATION,

    /* UDS Client - Read Response for Read Request of User Data 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSC_READ_CHAR_RESPONSE,

    /* UDS Client - Write Response for Write Request of User Data 
        Service Characteristic value. The parameter of this event
        is a structure of CYBLE_UDS_CHAR_VALUE_T type.
    */
    CYBLE_EVT_UDSC_WRITE_CHAR_RESPONSE,

    /* UDS Client - Read Response for Read Request of User Data
        Service Characteristic Descriptor Read request. The 
        parameter of this event is a structure of
        CYBLE_UDS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_UDSC_READ_DESCR_RESPONSE,

    /* UDS Client - Write Response for Write Request of User Data
        Service Characteristic Configuration Descriptor value.
        The parameter of this event is a structure of 
        CYBLE_UDS_DESCR_VALUE_T type.
    */
    CYBLE_EVT_UDSC_WRITE_DESCR_RESPONSE,

    
    /***************************************
    ##Debug Events
    ***************************************/
    
    CYBLE_DEBUG_EVT_BLESS_INT = 0xE000u,

}CYBLE_EVT_T;

/* Event handler state machine type */
typedef enum
{
    CYBLE_STATE_STOPPED,                        /* BLE is turned off */
    CYBLE_STATE_INITIALIZING,                   /* Initializing state */
    CYBLE_STATE_CONNECTED,                      /* Peer device is connected */
#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)
    CYBLE_STATE_ADVERTISING,                    /* Advertising process */
#endif /* CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER */
#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER)
    CYBLE_STATE_SCANNING,                       /* Scanning process */
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */
#if(CYBLE_GAP_ROLE_CENTRAL)
    CYBLE_STATE_CONNECTING,                     /* Connecting */
#endif /* CYBLE_GAP_ROLE_CENTRAL */
    CYBLE_STATE_DISCONNECTED                    /* Essentially idle state */
} CYBLE_STATE_T;

#if (CYBLE_GATT_ROLE_CLIENT)

/* Client State type */
typedef enum
{
    CYBLE_CLIENT_STATE_CONNECTED,               /* Server device is connected */
    CYBLE_CLIENT_STATE_SRVC_DISCOVERING,        /* Server services are being discovered */
    CYBLE_CLIENT_STATE_INCL_DISCOVERING,        /* Server included services are being discovered */
    CYBLE_CLIENT_STATE_CHAR_DISCOVERING,        /* Server characteristics are being discovered */
    CYBLE_CLIENT_STATE_DESCR_DISCOVERING,       /* Server char. descriptors are being discovered */
    CYBLE_CLIENT_STATE_DISCOVERED,              /* Server is discovered */
    CYBLE_CLIENT_STATE_DISCONNECTING,           /* Server is disconnecting */
    CYBLE_CLIENT_STATE_DISCONNECTED_DISCOVERED, /* Server is disconnected but discovered */
    CYBLE_CLIENT_STATE_DISCONNECTED             /* Essentially initial client state */
} CYBLE_CLIENT_STATE_T;

/* GAP Service characteristics server's GATT DB handles structure type */
typedef struct
{
    /* Handle of the GAPS Device Name Characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T deviceNameCharHandle;
    /* Handle of the GAPS Appearance Characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T appearanceCharHandle;
    /* Handle of the GAPS Peripheral Privacy Flag Parameters Characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T periphPrivacyCharHandle;
    /* Handle of the GAPS Reconnection Address Characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T reconnAddrCharHandle;
    /* Handle of the GAPS Peripheral Preferred Connection Parameters 
       Characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T prefConnParamCharHandle;
}CYBLE_GAPC_T;

/* Service indexes (SRVI) */
typedef enum
{
    CYBLE_SRVI_GAP,
    CYBLE_SRVI_GATT,
    
#ifdef CYBLE_ANS_CLIENT
    CYBLE_SRVI_ANS,
#endif /* CYBLE_ANS_CLIENT */
#ifdef CYBLE_BAS_CLIENT
    CYBLE_SRVI_BAS,
    CYBLE_SRVI_BAS_END = CYBLE_SRVI_BAS + CYBLE_BASC_SERVICE_COUNT - 1u,
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    CYBLE_SRVI_BLS,
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    CYBLE_SRVI_CGMS,
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    CYBLE_SRVI_CPS,
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    CYBLE_SRVI_CSCS,
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_CTS_CLIENT
    CYBLE_SRVI_CTS,
#endif /* CYBLE_CTS_CLIENT */
#ifdef CYBLE_DIS_CLIENT
    CYBLE_SRVI_DIS,
#endif /* CYBLE_DIS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    CYBLE_SRVI_GLS,
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HIDS_CLIENT
    CYBLE_SRVI_HIDS,
    CYBLE_SRVI_HIDS_END = CYBLE_SRVI_HIDS + CYBLE_HIDSC_SERVICE_COUNT - 1u,
#endif /* CYBLE_HIDS_CLIENT */
#ifdef CYBLE_HRS_CLIENT
    CYBLE_SRVI_HRS,
#endif /* CYBLE_HRS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    CYBLE_SRVI_HTS,
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_IAS_CLIENT
    CYBLE_SRVI_IAS,
#endif /* CYBLE_IAS_CLIENT */
#ifdef CYBLE_LLS_CLIENT
    CYBLE_SRVI_LLS,
#endif /* CYBLE_LLS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    CYBLE_SRVI_LNS,
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_NDCS_CLIENT
    CYBLE_SRVI_NDCS,
#endif /* CYBLE_NDCS_CLIENT */
#ifdef CYBLE_PASS_CLIENT
    CYBLE_SRVI_PASS,
#endif /* CYBLE_PASS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    CYBLE_SRVI_RSCS,
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_RTUS_CLIENT
    CYBLE_SRVI_RTUS,
#endif /* CYBLE_RTUS_CLIENT */
#ifdef CYBLE_SCPS_CLIENT
    CYBLE_SRVI_SCPS,
#endif /* CYBLE_SCPS_CLIENT */
#ifdef CYBLE_TPS_CLIENT
    CYBLE_SRVI_TPS,
#endif /* CYBLE_TPS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    CYBLE_SRVI_UDS,
#endif /* CYBLE_UDS_CLIENT */

    CYBLE_SRVI_COUNT /* Total count of services */
}CYBLE_SRVI_T;

/* Service Characteristic indexes for Descriptors discovery (SCDI) */
typedef enum
{
    CYBLE_SCDI_GATT_SERVICE_CHANGED,                        /* Service Changed characteristic */

#ifdef CYBLE_ANS_CLIENT
    CYBLE_SCDI_ANS_SUPPORTED_NEW_ALERT_CAT,                 /* Supported New Alert Characteristic */
    CYBLE_SCDI_ANS_NEW_ALERT,                               /* New Alert Characteristic */
    CYBLE_SCDI_ANS_SUPPORTED_UNREAD_ALERT_CAT,              /* Supported Unread Alert Characteristic */
    CYBLE_SCDI_ANS_UNREAD_ALERT_STATUS,                     /* Unread Alert Status Characteristic */
    CYBLE_SCDI_ANS_ALERT_NTF_CONTROL_POINT,                 /* Alert Notification Control Point Characteristic */
#endif /* CYBLE_ANS_CLIENT */
#ifdef CYBLE_BAS_CLIENT
    CYBLE_SCDI_BAS_LEVEL,                                   /* Battery level Characteristic */
    CYBLE_SCDI_BAS_LEVEL_END = CYBLE_SCDI_BAS_LEVEL + CYBLE_BASC_SERVICE_COUNT - 1u,
#endif /* CYBLE_BAS_CLIENT */
#ifdef CYBLE_BLS_CLIENT
    CYBLE_SCDI_BLS_BPM,                                     /* Blood Pressure Measurement Characteristic */
    CYBLE_SCDI_BLS_ICP,                                     /* Intermediate Cuff Pressure Characteristic */
#endif /* CYBLE_BLS_CLIENT */
#ifdef CYBLE_CGMS_CLIENT
    CYBLE_SCDI_CGMS_CGMT,                                   /* CGM Measurement Characteristic */
    CYBLE_SCDI_CGMS_RACP,                                   /* Record Access Control Point Characteristic */
    CYBLE_SCDI_CGMS_SOCP,                                   /* CGM Specific Ops Control Point Characteristic */
#endif /* CYBLE_CGMS_CLIENT */
#ifdef CYBLE_CPS_CLIENT
    CYBLE_SCDI_CPS_POWER_MEASURE,                           /* Cycling Power Measurement characteristic */ 
    CYBLE_SCDI_CPS_POWER_FEATURE,                           /* Cycling Power Feature characteristic */ 
    CYBLE_SCDI_CPS_SENSOR_LOCATION,                         /* Sensor Location characteristic */ 
    CYBLE_SCDI_CPS_POWER_VECTOR,                            /* Cycling Power Vector characteristic */ 
    CYBLE_SCDI_CPS_POWER_CP,                                /* Cycling Power Control Point characteristic */ 
#endif /* CYBLE_CPS_CLIENT */
#ifdef CYBLE_CSCS_CLIENT
    CYBLE_SCDI_CSCS_CSC_MEASUREMENT,                        /*  Cycling Speed and Cadence Measurement Characteristic */
    CYBLE_SCDI_CSCS_CSC_FEATURE,                            /*  Cycling Speed and Cadence CSC Feature Characteristic */
    CYBLE_SCDI_CSCS_SENSOR_LOCATION,                        /*  Cycling Speed and Cadence Sensor Location
                                                                Characteristic */
    CYBLE_SCDI_CSCS_SC_CONTROL_POINT,                       /*  SC Control Point Characteristic */
#endif /* CYBLE_CSCS_CLIENT */
#ifdef CYBLE_CTS_CLIENT
    CYBLE_SCDI_CTS_CURRENT_TIME,                            /* Current Time Characteristic */
#endif /* CYBLE_CTS_CLIENT */
#ifdef CYBLE_GLS_CLIENT
    CYBLE_SCDI_GLS_GLMT,                                    /* Glucose Measurement Characteristic */
    CYBLE_SCDI_GLS_GLMC,                                    /* Glucose Measurement Context Characteristic */
    CYBLE_SCDI_GLS_RACP,                                    /* Record Access Control Point Characteristic */
#endif /* CYBLE_GLS_CLIENT */
#ifdef CYBLE_HIDS_CLIENT
    CYBLE_SCDI_HIDS_REPORT_MAP,                             /* Report Map Characteristic index */
    CYBLE_SCDI_HIDS_BOOT_KYBRD_IN_REP,                      /* Boot Keyboard Input Report Characteristic index */
    CYBLE_SCDI_HIDS_BOOT_KYBRD_OUT_REP,                     /* Boot Keyboard Output Report Characteristic index */
    CYBLE_SCDI_HIDS_BOOT_MOUSE_IN_REP,                      /* Boot Mouse Input Report Characteristic index */
    CYBLE_SCDI_HIDS_REPORT,                                 /* Report Characteristic index */
    CYBLE_SCDI_HIDS_REPORT_END = CYBLE_SCDI_HIDS_REPORT + CYBLE_HIDSC_REPORT_COUNT - 1u,
#endif /* CYBLE_HIDS_CLIENT */
#ifdef CYBLE_HRS_CLIENT
    CYBLE_SCDI_HRS_HRM,                                     /* Heart Rate Measurement Characteristic */
#endif /* CYBLE_HRS_CLIENT */
#ifdef CYBLE_HTS_CLIENT
    CYBLE_SCDI_HTS_TEMP_MEASURE,                            /* Temperature Measurement characteristic index */
    CYBLE_SCDI_HTS_TEMP_TYPE,                               /* Temperature Type characteristic index */
    CYBLE_SCDI_HTS_INTERM_TEMP,                             /* Intermediate Temperature characteristic index*/
    CYBLE_SCDI_HTS_MEASURE_INTERVAL,                        /* Measurement Interval characteristic index */
#endif /* CYBLE_HTS_CLIENT */
#ifdef CYBLE_LNS_CLIENT
    CYBLE_SCDI_LNS_LS,                                      /* Location and Speed characteristic index */
    CYBLE_SCDI_LNS_CP,                                      /* L&N Control Point characteristic index */
    CYBLE_SCDI_LNS_NV,                                      /* Navigation characteristic index */
#endif /* CYBLE_LNS_CLIENT */
#ifdef CYBLE_PASS_CLIENT
    CYBLE_SCDI_PASS_AS,                                     /* Alert Status characteristic index */
    CYBLE_SCDI_PASS_RS,                                     /* Ringer Settings characteristic index */
#endif /* CYBLE_PASS_CLIENT */
#ifdef CYBLE_RSCS_CLIENT
    CYBLE_SCDI_RSCS_RSC_MEASUREMENT,                        /*  Running Speed and Cadence Measurement Characteristic */
    CYBLE_SCDI_RSCS_RSC_FEATURE,                            /*  Running Speed and Cadence RSC Feature Characteristic */
    CYBLE_SCDI_RSCS_SENSOR_LOCATION,                        /*  Running Speed and Cadence Sensor Location
                                                                Characteristic */
    CYBLE_SCDI_RSCS_SC_CONTROL_POINT,                       /*  SC Control Point Characteristic */
#endif /* CYBLE_RSCS_CLIENT */
#ifdef CYBLE_SCPS_CLIENT
    CYBLE_SCDI_SCPS_SCAN_REFRESH,                           /*  Scan Refresh Characteristic */
#endif /* CYBLE_SCPS_CLIENT */
#ifdef CYBLE_TPS_CLIENT
    CYBLE_SCDI_TPS_TX_PWR_LEVEL,
#endif /* CYBLE_TPS_CLIENT */
#ifdef CYBLE_UDS_CLIENT
    CYBLE_SRVI_UDS_DCI,                                     /*  Database Change Increment Characteristic */
    CYBLE_SRVI_UDS_UCP,                                     /*  User Control Point Characteristic */
#endif /* CYBLE_UDS_CLIENT */

    CYBLE_SCDI_COUNT /* Total count of descriptors */
}CYBLE_SCDI_T;

#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
##Function Prototypes
***************************************/

/* Event Handler functions */
void CyBle_EventHandler(uint8 eventCode, void *eventParam);
void CyBle_ReadByGroupEventHandler(CYBLE_GATTC_READ_BY_GRP_RSP_PARAM_T *eventParam);
void CyBle_ReadByTypeEventHandler(CYBLE_GATTC_READ_BY_TYPE_RSP_PARAM_T *eventParam);
void CyBle_FindInfoEventHandler(CYBLE_GATTC_FIND_INFO_RSP_PARAM_T *eventParam);
void CyBle_ErrorResponseEventHandler(const CYBLE_GATTC_ERR_RSP_PARAM_T *eventParam);
CYBLE_API_RESULT_T CyBle_NextInclDiscovery(void);
CYBLE_API_RESULT_T CyBle_NextCharDiscovery(void);
CYBLE_API_RESULT_T CyBle_NextCharDscrDiscovery(void);

#if(CYBLE_GATT_ROLE_SERVER)
    CYBLE_API_RESULT_T CyBle_GapSetLocalName(const char8 name[]);
    CYBLE_API_RESULT_T CyBle_GapGetLocalName(char8 name[]);
#endif /* (CYBLE_GATT_ROLE_SERVER) */


/***************************************
##Exported Functions (MACROS)
***************************************/

/******************************************************************************
##Function Name: CyBle_SetState
*******************************************************************************

Summary:
 Used to set the Event Handler State Machine's state.

Parameters:
 CYBLE_STATE_T state: The desired state that the event handler's state machine
                       should be set to.

Return:
 None

******************************************************************************/
#define CyBle_SetState(state) (cyBle_state = (state))


/******************************************************************************
##Function Name: CyBle_GetState
*******************************************************************************
Summary:
 This function is used to determine the current state of the Event Handler
 state machine.

Parameters:
 None

Return:
 CYBLE_STATE_T state - The current state.

******************************************************************************/
#define CyBle_GetState() (cyBle_state)


/****************************************************************************** 
##Function Name: CyBle_GattGetBusyStatus
*******************************************************************************

Summary:
 This function returns the status of BLE stack(busy or not busy).

Parameters:
 None

Return:
 uint8: Busy status 
  * CYBLE_STACK_STATE_BUSY - BLE stack busy
  * CYBLE_STACK_STATE_FREE - BLE stack not busy

******************************************************************************/
#define CyBle_GattGetBusyStatus() (cyBle_busyStatus)


/* DOM-IGNORE-BEGIN */

/* Deprecated macro name. Not recommended for use in new design */
#define CyBle_GattGetBusStatus  CyBle_GattGetBusyStatus
#define cyBle_busStatus         cyBle_busyStatus

#if(CYBLE_GATT_ROLE_CLIENT)


/******************************************************************************    
##Function Name: CyBle_SetClientState
*******************************************************************************

Summary:
 Used to set the Event Handler GATT Client State Machine's state

Parameters:
 CYBLE_STATE_T state:  The state which is desired to be set

Return:
 None

******************************************************************************/
#define CyBle_SetClientState(state) (cyBle_clientState = (state))
    

/******************************************************************************     
##Function Name: CyBle_GetClientState
*******************************************************************************
Summary:
 This function is used to determine the current state of the Event Handler 
 GATT Client State Machine's state

Parameters:
 None

Return:
 CYBLE_CLIENT_STATE_T state - The current state.

******************************************************************************/
#define CyBle_GetClientState() (cyBle_clientState)
    


#define CYBLE_GapcCheckCharHandle(handle, discCharInfo)\
    do {\
        if((handle) == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)\
        {\
            (handle) = (discCharInfo)->valueHandle;\
        }\
        else\
        {\
            CyBle_ApplCallback(CYBLE_EVT_GATTC_CHAR_DUPLICATION,\
                                          &((discCharInfo)->uuid.uuid16));\
        }\
    } while(0)

#define CyBle_CheckStoreCharHandle(handle)\
    do {\
        if((handle).valueHandle == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)\
        {\
            (handle).valueHandle = discCharInfo->valueHandle;\
            (handle).properties = discCharInfo->properties;\
        }\
        else\
        {\
            CyBle_ApplCallback((uint32)CYBLE_EVT_GATTC_CHAR_DUPLICATION,\
                                          &(discCharInfo->uuid.uuid16));\
        }\
    } while(0)

#define CyBle_CheckStoreCharDescrHandle(handle)\
    do {\
        if((handle) == CYBLE_GATT_INVALID_ATTR_HANDLE_VALUE)\
        {\
            (handle) = discDescrInfo->descrHandle;\
        }\
        else\
        {\
            CyBle_ApplCallback((uint32)CYBLE_EVT_GATTC_CHAR_DUPLICATION,\
                                          &(discDescrInfo->uuid.uuid16));\
        }\
    } while(0)

#endif /* CYBLE_GATT_ROLE_CLIENT */


/* DOM-IGNORE-END */




/***************************************
##External data references
***************************************/

extern CYBLE_STATE_T            cyBle_state;
extern CYBLE_CONN_HANDLE_T      cyBle_connHandle;
extern volatile uint8           cyBle_busyStatus;

#if(CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER) 
    extern uint8 cyBle_advertisingIntervalType;
#endif /* (CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_BROADCASTER)  */

#if(CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER) 
    extern uint8 cyBle_scanningIntervalType;
#endif /* CYBLE_GAP_ROLE_CENTRAL || CYBLE_GAP_ROLE_OBSERVER */

#if (CYBLE_GATT_ROLE_CLIENT)
extern CYBLE_CLIENT_STATE_T     cyBle_clientState;
extern uint8                    cyBle_disCount;
extern CYBLE_GAPC_T             cyBle_gapc;
extern CYBLE_DISC_SRVC_INFO_T   cyBle_serverInfo[CYBLE_SRVI_COUNT];
#endif /* CYBLE_GATT_ROLE_CLIENT */

#endif /* CY_BLE_CYBLE_EH_H  */


/* [] END OF FILE */
