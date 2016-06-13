/*******************************************************************************
File Name: CYBLE_gatt.h
Version 1.20

Description:
 Contains the prototypes and constants used in the BLE GATT profile.

********************************************************************************
Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
You may use this file only in accordance with the license, terms, conditions,
disclaimers, and limitations in the end user license agreement accompanying
the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CYBLE_GATT_H)
#define CY_BLE_CYBLE_GATT_H

#include "BLE_1.h"


/***************************************
##Conditional Compilation Parameters
***************************************/

#define CYBLE_GATT_ROLE                              (0x01u)
#define CYBLE_GATT_SERVER                            (0x01u)
#define CYBLE_GATT_CLIENT                            (0x02u)
#define CYBLE_GATT_BOTH                              (CYBLE_GATT_SERVER | CYBLE_GATT_CLIENT)

#define CYBLE_GATT_ROLE_SERVER (0u != (CYBLE_GATT_ROLE & CYBLE_GATT_SERVER))
#define CYBLE_GATT_ROLE_CLIENT (0u != (CYBLE_GATT_ROLE & CYBLE_GATT_CLIENT))


#if(CYBLE_GATT_ROLE_SERVER)

#define CYBLE_GATT_DB_INDEX_COUNT                    (0x000Eu)
#define CYBLE_GATT_DB_CCCD_COUNT                     (0x02u)
#define CYBLE_GATT_DB_MAX_VALUE_LEN                  (0x000Cu)

#endif /* CYBLE_GATT_ROLE_SERVER */

#define CYBLE_IAS
#define CYBLE_IAS_SERVER

/***************************************
##Common constants for LLS and IAS services
***************************************/

#if (defined(CYBLE_IAS) || defined(CYBLE_LLS))

#define CYBLE_NO_ALERT                              (0u)
#define CYBLE_MILD_ALERT                            (1u)
#define CYBLE_HIGH_ALERT                            (2u)

#endif /* (defined(CYBLE_IAS) || defined(CYBLE_LLS)) */


/***************************************
##Type Definitions
***************************************/

/* Service data received with read by group type response during discovery process */
typedef struct
{
    CYBLE_GATT_ATTR_HANDLE_RANGE_T      range;
    uint16                              uuid;
}CYBLE_DISC_SRVC_INFO_T;

/* Included service data received with read by type response during discovery process */
typedef struct
{
    CYBLE_GATT_DB_ATTR_HANDLE_T    inclDefHandle;   /* Included definition handle */
    CYBLE_GATT_ATTR_HANDLE_RANGE_T inclHandleRange; /* Included declaration handle range */
    CYBLE_UUID_T                   uuid;            /* Included UUID */
    uint8                          uuidFormat;      /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */
}CYBLE_DISC_INCL_INFO_T;

/* Characteristic data received with read by type response during discovery process */
typedef struct
{
    CYBLE_GATT_DB_ATTR_HANDLE_T charDeclHandle; /* Handle for characteristic declaration */
    uint8                       properties;     /* Properties for value field */
    CYBLE_GATT_DB_ATTR_HANDLE_T valueHandle;    /* Handle to server database attribute value entry */
    CYBLE_UUID_T                uuid;           /* Characteristic UUID */
    uint8                       uuidFormat;     /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */
}CYBLE_DISC_CHAR_INFO_T;

/* Characteristic Attribute handle + properties structure */
typedef struct
{
    /* Properties for value field */
    uint8  properties;

    /* Handle of server database attribute value entry */
    CYBLE_GATT_DB_ATTR_HANDLE_T        valueHandle;
}CYBLE_SRVR_CHAR_INFO_T;

/* Characteristic descriptor data received with find info response during discovery process */
typedef struct
{
    CYBLE_CONN_HANDLE_T         connHandle;     /* Handle to server database attribute entry */
    CYBLE_GATT_DB_ATTR_HANDLE_T descrHandle;    /* Descriptor handle */
    CYBLE_UUID_T                uuid;           /* Descriptor UUID */
    uint8                       uuidFormat;     /* UUID Format - 16-bit (0x01) or 128-bit (0x02) */
}CYBLE_DISC_DESCR_INFO_T;

#if(CYBLE_GATT_ROLE_SERVER)

/* Structure with Generic Attribute Service (GATTS) attribute handles */
typedef struct
{
    CYBLE_GATT_DB_ATTR_HANDLE_T serviceHandle;              /* Service handle*/
    CYBLE_GATT_DB_ATTR_HANDLE_T serviceChangedHandle;       /* Handle of the Service Changed characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T cccdHandle;                 /* Client Characteristic Configuration descriptor handle */
} CYBLE_GATTS_T;

#endif /* CYBLE_GATT_ROLE_SERVER */

#if(CYBLE_GATT_ROLE_CLIENT)

/* Structure with discovered attributes information of Generic Attribute 
   Service (GATTS) */
typedef struct
{
    CYBLE_SRVR_CHAR_INFO_T serviceChanged;                  /* Handle of the Service Changed characteristic */
    CYBLE_GATT_DB_ATTR_HANDLE_T cccdHandle;                 /* Client Characteristic Configuration descriptor handle */
} CYBLE_GATTC_T;

#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
##Function Prototypes
***************************************/

#if(CYBLE_GATT_ROLE_SERVER)
    
CYBLE_API_RESULT_T CyBle_GattsReInitGattDb(void);
    
#endif /* CYBLE_GATT_ROLE_SERVER */

#if(CYBLE_GATT_ROLE_CLIENT)
    
CYBLE_API_RESULT_T CyBle_GattcStartDiscovery(CYBLE_CONN_HANDLE_T connHandle);

#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
##Private Function Prototypes
***************************************/

/* DOM-IGNORE-BEGIN */
#if (CYBLE_GATT_ROLE_SERVER)
    
CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteEventHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam);

#endif /* CYBLE_GATT_ROLE_SERVER */

#if(CYBLE_GATT_ROLE_CLIENT)
    
void CyBle_GattcDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo);
void CyBle_GattcDiscoverCharDescriptorsEventHandler(CYBLE_DISC_DESCR_INFO_T *discDescrInfo);
void CyBle_GattcIndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam);

#endif /* CYBLE_GATT_ROLE_CLIENT */
/* DOM-IGNORE-END */


/***************************************
##Variables with external linkage
***************************************/

#if (CYBLE_GATT_ROLE_SERVER)
    
extern const CYBLE_GATTS_T cyBle_gatts;
extern const CYBLE_GATTS_DB_T cyBle_gattDB[CYBLE_GATT_DB_INDEX_COUNT];

#if(CYBLE_GATT_DB_CCCD_COUNT != 0u)
extern uint8 cyBle_attValuesCCCD[CYBLE_GATT_DB_CCCD_COUNT];
extern const uint8 cyBle_attValuesCCCDFlashMemory[CYBLE_GAP_MAX_BONDED_DEVICE + 1u][CYBLE_GATT_DB_CCCD_COUNT];
#endif /* CYBLE_GATT_DB_CCCD_COUNT != 0u */

#endif /* CYBLE_GATT_ROLE_SERVER */

#if(CYBLE_GATT_ROLE_CLIENT)
    
extern CYBLE_GATTC_T cyBle_gattc;
    
#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
##API Constants
***************************************/


/***************************************
##Universal Unique Identifier (UUID): BLE Services
***************************************/

/* Generic Access Profile */
#define CYBLE_UUID_GAP_SERVICE                       (0x1800u)
/* Generic Attribute Profile */
#define CYBLE_UUID_GATT_SERVICE                      (0x1801u)

/* UUID: BLE Other Services */
#define CYBLE_UUID_IMMEDIATE_ALERT_SERVICE           (0x1802u)
#define CYBLE_UUID_LINK_LOSS_SERVICE                 (0x1803u)
#define CYBLE_UUID_TX_POWER_SERVICE                  (0x1804u)
#define CYBLE_UUID_CURRENT_TIME_SERVICE              (0x1805u)
#define CYBLE_UUID_REF_TIME_UPDATE_SERVICE           (0x1806u)
#define CYBLE_UUID_NEXT_DST_CHANGE_SERVICE           (0x1807u)
#define CYBLE_UUID_GLUCOSE_SERVICE                   (0x1808u)
#define CYBLE_UUID_HEALTH_THERMOMETER_SERVICE        (0x1809u)
#define CYBLE_UUID_DEVICE_INFO_SERVICE               (0x180Au)
#define CYBLE_UUID_NWA_SERVICE                       (0x180Bu)
#define CYBLE_UUID_WATCH_DOG_SERVICE                 (0x180Cu)
#define CYBLE_UUID_HEART_RATE_SERVICE                (0x180Du)
#define CYBLE_UUID_PHONE_ALERT_STATUS_SERVICE        (0x180Eu)
#define CYBLE_UUID_BAS_SERVICE                       (0x180Fu)
#define CYBLE_UUID_BLOOD_PRESSURE_SERVICE            (0x1810u)
#define CYBLE_UUID_ALERT_NOTIFICATION_SERVICE        (0x1811u)
#define CYBLE_UUID_HIDS_SERVICE                      (0x1812u)
#define CYBLE_UUID_SCAN_PARAM_SERVICE                (0x1813u)
#define CYBLE_UUID_RUNNING_SPEED_AND_CADENCE_SERVICE (0x1814u)
#define CYBLE_UUID_CYCLING_SPEED_AND_CADENCE_SERVICE (0x1816u)
#define CYBLE_UUID_PULSE_OXIMETER_SERVICE            (0x1817u)
#define CYBLE_UUID_CPS_SERVICE                       (0x1818u)
#define CYBLE_UUID_LOCATION_AND_NAVIGATION_SERVICE   (0x1819u)
#define CYBLE_UUID_ENVIRONMENTAL_SENSING_SERVICE     (0x181Au)
#define CYBLE_UUID_BODY_COMPOSITION_SERVICE          (0x181Bu)
#define CYBLE_UUID_USER_DATA_SERVICE                 (0x181Cu)
#define CYBLE_UUID_WEIGHT_SCALE_SERVICE              (0x181Du)
#define CYBLE_UUID_BOND_MANAGEMENT_SERVICE           (0x181Eu)
#define CYBLE_UUID_CGM_SERVICE                       (0x181Fu)
#define CYBLE_UUID_FIND_ME_SERVICE                   (0x18A3u)


/***************************************
##UUID: GATT Attribute Types defined by GATT Profile 
***************************************/

/* Primary Service Declaration */
#define CYBLE_UUID_PRIMARY_SERVICE                   (0x2800u)
/* Secondary Service Declaration */
#define CYBLE_UUID_SECONDARY_SERVICE                 (0x2801u)
/* Include Declaration */
#define CYBLE_UUID_INCLUDE                           (0x2802u)
/* Characteristic Declaration */
#define CYBLE_UUID_CHARACTERISTIC                    (0x2803u)


/***************************************
##UUID: GATT Characteristic Descriptors
***************************************/

/* Characteristic Extended Properties */
#define CYBLE_UUID_CHAR_EXTENDED_PROPERTIES          (0x2900u)
/* Characteristic User Description Descriptor */
#define CYBLE_UUID_CHAR_USER_DESCRIPTION             (0x2901u)
/* Client Characteristic Configuration Descriptor */
#define CYBLE_UUID_CHAR_CLIENT_CONFIG                (0x2902u)
/* Server Characteristic Configuration Descriptor */
#define CYBLE_UUID_CHAR_SERVER_CONFIG                (0x2903u)
/* Characteristic Format Descriptor */
#define CYBLE_UUID_CHAR_FORMAT                       (0x2904u)
/* Characteristic Aggregate Format Descriptor */
#define CYBLE_UUID_CHAR_AGGREGATE_FORMAT             (0x2905u)
/* Characteristic Valid Range */
#define CYBLE_UUID_CHAR_VALID_RANGE                  (0x2906u)


/***************************************
##UUID: External Report Reference
***************************************/

#define CYBLE_UUID_CHAR_EXTERNAL_REPORT_REF          (0x2907u)
#define CYBLE_UUID_CHAR_REPORT_REFERENCE             (0x2908u)


/***************************************
##UUID: Commonly used GATT Characteristic Types
***************************************/

/* Device Name Characteristic */
#define CYBLE_UUID_CHAR_DEVICE_NAME                  (0x2A00u)
/* Appearance Characteristic */
#define CYBLE_UUID_CHAR_APPEARANCE                   (0x2A01u)
/* Peripheral Privacy Flag Characteristic */
#define CYBLE_UUID_CHAR_PERIPH_PRIVCY_FLAG           (0x2A02u)
/* Reconnection Address Characteristic */
#define CYBLE_UUID_CHAR_RECONNECTION_ADDR            (0x2A03u)
/* Peripheral Preferred Connection Parameters Characteristic */
#define CYBLE_UUID_CHAR_PRFRRD_CNXN_PARAM            (0x2A04u)
/* Service Changed Characteristic */
#define CYBLE_UUID_CHAR_SERVICE_CHANGED              (0x2A05u)


/***************************************
##UUID: Other Characteristic Types
***************************************/

#define CYBLE_UUID_CHAR_ALERT_LEVEL                  (0x2A06u)
#define CYBLE_UUID_CHAR_TX_POWER_LEVEL               (0x2A07u)
#define CYBLE_UUID_CHAR_DATE_TIME                    (0x2A08u)
#define CYBLE_UUID_CHAR_DAY_OF_WEEK                  (0x2A09u)
#define CYBLE_UUID_CHAR_DAY_DATE_TIME                (0x2A0Au)
#define CYBLE_UUID_CHAR_EXACT_TIME_100               (0x2A0Bu)
#define CYBLE_UUID_CHAR_EXACT_TIME_256               (0x2A0Cu)
#define CYBLE_UUID_CHAR_DST_OFFSET                   (0x2A0Du)
#define CYBLE_UUID_CHAR_TIME_ZONE                    (0x2A0Eu)
#define CYBLE_UUID_CHAR_LOCAL_TIME_INFO              (0x2A0Fu)
#define CYBLE_UUID_CHAR_SEC_TIME_ZONE                (0x2A10u)
#define CYBLE_UUID_CHAR_TIME_WITH_DST                (0x2A11u)
#define CYBLE_UUID_CHAR_TIME_ACCURACY                (0x2A12u)
#define CYBLE_UUID_CHAR_TIME_SOURCE                  (0x2A13u)
#define CYBLE_UUID_CHAR_REF_TIME_INFO                (0x2A14u)
#define CYBLE_UUID_CHAR_TIME_BROADCAST               (0x2A15u)
#define CYBLE_UUID_CHAR_TIME_UPDATE_CONTROL_POINT    (0x2A16u)
#define CYBLE_UUID_CHAR_TIME_UPDATE_STATE            (0x2A17u)
#define CYBLE_UUID_CHAR_GLUCOSE_MSRMNT               (0x2A18u)
#define CYBLE_UUID_CHAR_BATTERY_LEVEL                (0x2A19u)
#define CYBLE_UUID_CHAR_TEMPERATURE_MSMNT            (0x2A1Cu)
#define CYBLE_UUID_CHAR_TEMPERATURE_TYPE             (0x2A1Du)
#define CYBLE_UUID_CHAR_INTERMEDIATE_TEMP            (0x2A1Eu)
#define CYBLE_UUID_CHAR_MSMNT_INTERVAL               (0x2A21u)
#define CYBLE_UUID_CHAR_HIDS_BOOT_KEYBOARD_IN_RPT    (0x2A22u)
#define CYBLE_UUID_CHAR_SYSTEM_ID                    (0x2A23u)
#define CYBLE_UUID_CHAR_MODEL_NUMBER                 (0x2A24u)
#define CYBLE_UUID_CHAR_SERIAL_NUMBER                (0x2A25u)
#define CYBLE_UUID_CHAR_FIRMWARE_REV                 (0x2A26u)
#define CYBLE_UUID_CHAR_HARDWARE_REV                 (0x2A27u)
#define CYBLE_UUID_CHAR_SOFTWARE_REV                 (0x2A28u)
#define CYBLE_UUID_CHAR_MANUFACTURER_NAME            (0x2A29u)
#define CYBLE_UUID_CHAR_REG_CERT_DATA                (0x2A2Au)
#define CYBLE_UUID_CHAR_CURRENT_TIME                 (0x2A2Bu)
#define CYBLE_UUID_CHAR_SCAN_REFRESH                 (0x2A31u)
#define CYBLE_UUID_CHAR_HIDS_BOOT_KEYBOARD_OUT_RPT   (0x2A32u)
#define CYBLE_UUID_CHAR_HIDS_BOOT_MOUSE_IN_RPT       (0x2A33u)
#define CYBLE_UUID_CHAR_GL_MSRMT_CTX                 (0x2A34u)
#define CYBLE_UUID_CHAR_BP_MSRMT                     (0x2A35u)
#define CYBLE_UUID_CHAR_INTRMDT_CUFF_PRSR            (0x2A36u)
#define CYBLE_UUID_CHAR_HR_MSRMT                     (0x2A37u)
#define CYBLE_UUID_CHAR_BODY_SENSOR_LOC              (0x2A38u)
#define CYBLE_UUID_CHAR_HR_CNTRL_POINT               (0x2A39u)
#define CYBLE_UUID_CHAR_NWA                          (0x2A3Eu)
#define CYBLE_UUID_CHAR_ALERT_STATUS                 (0x2A3Fu)
#define CYBLE_UUID_CHAR_RINGER_CONTROL_POINT         (0x2A40u)
#define CYBLE_UUID_CHAR_RINGER_SETTING               (0x2A41u)
#define CYBLE_UUID_CHAR_ALERT_ID_BIT_MASK            (0x2A42u)
#define CYBLE_UUID_CHAR_ALERT_ID                     (0x2A43u)
#define CYBLE_UUID_CHAR_ALERT_NTF_CONTROL_POINT      (0x2A44u)
#define CYBLE_UUID_CHAR_UNREAD_ALRT_STATUS           (0x2A45u)
#define CYBLE_UUID_CHAR_NEW_ALERT                    (0x2A46u)
#define CYBLE_UUID_CHAR_SPRTD_NEW_ALRT_CTGRY         (0x2A47u)
#define CYBLE_UUID_CHAR_SPRT_UNRD_ALRT_CTGRY         (0x2A48u)
#define CYBLE_UUID_CHAR_BP_FEATURE                   (0x2A49u)
#define CYBLE_UUID_CHAR_HIDS_INFORMATION             (0x2A4Au)
#define CYBLE_UUID_CHAR_HIDS_REPORT_MAP              (0x2A4Bu)
#define CYBLE_UUID_CHAR_HIDS_CONTROL_POINT           (0x2A4Cu)
#define CYBLE_UUID_CHAR_HIDS_REPORT                  (0x2A4Du)
#define CYBLE_UUID_CHAR_HIDS_PROTOCOL_MODE           (0x2A4Eu)
#define CYBLE_UUID_CHAR_SCAN_WINDOW                  (0x2A4Fu)
#define CYBLE_UUID_CHAR_PNP_ID                       (0x2A50u)
#define CYBLE_UUID_CHAR_GL_FEATURE                   (0x2A51u)
#define CYBLE_UUID_CHAR_RACP                         (0x2A52u) /* Record Access Control Point */
#define CYBLE_UUID_CHAR_RSC_MSRMT                    (0x2A53u)
#define CYBLE_UUID_CHAR_RSC_FEATURE                  (0x2A54u)
#define CYBLE_UUID_CHAR_SC_CONTROL_POINT             (0x2A55u)
#define CYBLE_UUID_CHAR_CSC_MSRMT                    (0x2A5Bu)
#define CYBLE_UUID_CHAR_CSC_FEATURE                  (0x2A5Cu)
#define CYBLE_UUID_CHAR_SENSOR_LOCATION              (0x2A5Du)
#define CYBLE_UUID_CHAR_CPS_MSRMT                    (0x2A63u)
#define CYBLE_UUID_CHAR_CPS_VECTOR                   (0x2A64u)
#define CYBLE_UUID_CHAR_CPS_FEATURE                  (0x2A65u)
#define CYBLE_UUID_CHAR_CPS_CP                       (0x2A66u)
#define CYBLE_UUID_CHAR_LOCATION_AND_SPEED           (0x2A67u)
#define CYBLE_UUID_CHAR_NAVIGATION                   (0x2A68u)
#define CYBLE_UUID_CHAR_POSITION_QUALITY             (0x2A69u)
#define CYBLE_UUID_CHAR_LN_FEATURE                   (0x2A6Au)
#define CYBLE_UUID_CHAR_LN_CONTROL_POINT             (0x2A6Bu)
#define CYBLE_UUID_CHAR_AEL                          (0x2A7Eu) /* Aerobic Heart Rate Lower Limit */
#define CYBLE_UUID_CHAR_AEROBIC_THRESHOLD            (0x2A7Fu)
#define CYBLE_UUID_CHAR_AGE                          (0x2A80u)
#define CYBLE_UUID_CHAR_ANL                          (0x2A81u) /* Anaerobic Heart Rate Lower Limit */
#define CYBLE_UUID_CHAR_ANU                          (0x2A82u) /* Anaerobic Heart Rate Upper Limit */
#define CYBLE_UUID_CHAR_ANAEROBIC_THRESHOLD          (0x2A83u)
#define CYBLE_UUID_CHAR_AEU                          (0x2A84u) /* Anaerobic Heart Rate Upper Limit */
#define CYBLE_UUID_CHAR_DATE_OF_BIRTH                (0x2A85u)
#define CYBLE_UUID_CHAR_DATE_OF_THRESHOLD_ASSESSMENT (0x2A86u)
#define CYBLE_UUID_CHAR_EMAIL_ADDRESS                (0x2A87u)
#define CYBLE_UUID_CHAR_FBL                          (0x2A88u) /* Fat Burn Heart Rate Lower Limit */
#define CYBLE_UUID_CHAR_FBU                          (0x2A89u) /* Fat Burn Heart Rate Upper Limit */
#define CYBLE_UUID_CHAR_FIRST_NAME                   (0x2A8Au)
#define CYBLE_UUID_CHAR_FIVE_ZONE_HEART_RATE_LIMITS  (0x2A8Bu)
#define CYBLE_UUID_CHAR_GENDER                       (0x2A8Cu)
#define CYBLE_UUID_CHAR_HEART_RATE_MAX               (0x2A8Du)
#define CYBLE_UUID_CHAR_HEIGHT                       (0x2A8Eu)
#define CYBLE_UUID_CHAR_HIP_CIRCUNFERENCE            (0x2A8Fu)
#define CYBLE_UUID_CHAR_LAST_NAME                    (0x2A90u)
#define CYBLE_UUID_CHAR_MRH                          (0x2A91u) /* Maximum Recommended Heart Rate */
#define CYBLE_UUID_CHAR_RESTING_HEART_RATE           (0x2A92u)
#define CYBLE_UUID_CHAR_STP                          (0x2A93u) /* Sport Type for Aerobic and Anaerobic Thresholds */
#define CYBLE_UUID_CHAR_THREE_ZONE_HEART_RATE_LIMITS (0x2A94u)
#define CYBLE_UUID_CHAR_TWO_ZONE_HEART_RATE_LIMIT    (0x2A95u)
#define CYBLE_UUID_CHAR_VO2_MAX                      (0x2A96u)
#define CYBLE_UUID_CHAR_WAIST_CIRCUMFERENCE          (0x2A97u)
#define CYBLE_UUID_CHAR_WEIGHT                       (0x2A98u)
#define CYBLE_UUID_CHAR_DATABASE_CHANGE_INCREMENT    (0x2A99u)
#define CYBLE_UUID_CHAR_USER_INDEX                   (0x2A9Au)
#define CYBLE_UUID_CHAR_USER_CONTROL_POINT           (0x2A9Fu)
#define CYBLE_UUID_CHAR_LANGUAGE                     (0x2AA2u)
#define CYBLE_UUID_CHAR_CGM_MEASUREMENT              (0x2AA7u)
#define CYBLE_UUID_CHAR_CGM_FEATURE                  (0x2AA8u)
#define CYBLE_UUID_CHAR_CGM_STATUS                   (0x2AA9u)
#define CYBLE_UUID_CHAR_CGM_SESSION_START_TIME       (0x2AAAu)
#define CYBLE_UUID_CHAR_CGM_SESSION_RUN_TIME         (0x2AABu)
#define CYBLE_UUID_CHAR_CGM_SOCP                     (0x2AACu) /* CGM Specific Ops Control Point */

/* Pulse Oximeter Characteristics defines */
#define CYBLE_UUID_CHAR_POX_SPOT_CHK_MSRMT           (0x2A5Eu)
#define CYBLE_UUID_CHAR_POX_CONTINUOUS_MSRMT         (0x2A5Fu)
#define CYBLE_UUID_CHAR_POX_PULSATILE_EVENT          (0x2A60u)
#define CYBLE_UUID_CHAR_POX_FEATURES                 (0x2A61u)
#define CYBLE_UUID_CHAR_POX_CONTROL_POINT            (0x2A62u)
/* CPM Characteristics Measurements */
#define CYBLE_UUID_CHAR_CPM_MSRMT                    (0x2A63u)
#define CYBLE_UUID_CHAR_CPM_VECTOR                   (0x2A64u)
#define CYBLE_UUID_CHAR_CPM_FEATURE                  (0x2A65u)
#define CYBLE_UUID_CHAR_CPM_CNTRL_PNT                (0x2A66u)
/* Location and Navigation Characteristics */
#define CYBLE_UUID_CHAR_LOCATION_AND_SPEED           (0x2A67u)
#define CYBLE_UUID_CHAR_NAVIGATION                   (0x2A68u)
#define CYBLE_UUID_CHAR_LN_POSITION_QUALITY          (0x2A69u)
#define CYBLE_UUID_CHAR_LN_FEATURE                   (0x2A6Au)
#define CYBLE_UUID_CHAR_LN_CNTRL_PNT                 (0x2A6Bu)

/* GATT Characteristic Properties bit field */
#define CYBLE_CHAR_PROP_BROADCAST                    (0x01u)
#define CYBLE_CHAR_PROP_READ                         (0x02u)
#define CYBLE_CHAR_PROP_WRITE_WITHOUT_RSP            (0x04u)   /* Write Without Response */
#define CYBLE_CHAR_PROP_WRITE                        (0x08u)
#define CYBLE_CHAR_PROP_NOTIFY                       (0x10u)
#define CYBLE_CHAR_PROP_INDICATE                     (0x20u)
#define CYBLE_CHAR_PROP_SIGNED_WRITE                 (0x40u)   /* Authenticated Signed Writes */
#define CYBLE_CHAR_PROP_EXTENDED_PROPERTIES          (0x80u)

/* Client Characteristic Configuration Descriptor values */
#define CYBLE_CCCD_DEFAULT                           (0x0000u)
#define CYBLE_CCCD_NOTIFICATION                      (0x0001u)
#define CYBLE_CCCD_INDICATION                        (0x0002u)
#define CYBLE_CCCD_LEN                               (0x02u)

/* Server Characteristic Configuration Descriptor values */
#define CYBLE_SCCD_DEFAULT                           (0x0000u)
#define CYBLE_SCCD_BROADCAST                         (0x0001u)
#define CYBLE_SCCD_LEN                               (0x02u)

/* Characteristic Presentation Format Descriptor values */
#define CYBLE_CPFD_BOOLEAN                           (0x01u)
#define CYBLE_CPFD_UINT2                             (0x02u)
#define CYBLE_CPFD_UINT4                             (0x03u)
#define CYBLE_CPFD_UINT8                             (0x04u)
#define CYBLE_CPFD_UINT12                            (0x05u)
#define CYBLE_CPFD_UINT16                            (0x06u)
#define CYBLE_CPFD_UINT24                            (0x07u)
#define CYBLE_CPFD_UINT32                            (0x08u)
#define CYBLE_CPFD_UINT48                            (0x09u)
#define CYBLE_CPFD_UINT64                            (0x0au)
#define CYBLE_CPFD_UINT128                           (0x0bu)
#define CYBLE_CPFD_INT8                              (0x0cu)
#define CYBLE_CPFD_INT12                             (0x0du)
#define CYBLE_CPFD_INT16                             (0x0eu)
#define CYBLE_CPFD_INT24                             (0x0fu)
#define CYBLE_CPFD_INT32                             (0x10u)
#define CYBLE_CPFD_INT48                             (0x11u)
#define CYBLE_CPFD_INT64                             (0x12u)
#define CYBLE_CPFD_INT128                            (0x13u)
#define CYBLE_CPFD_IEEE754_FP32                      (0x14u)
#define CYBLE_CPFD_IEEE754_FP64                      (0x15u)
#define CYBLE_CPFD_IEEE11073_SFLOAT16                (0x16u)
#define CYBLE_CPFD_IEEE11073_FLOAT32                 (0x17u)
#define CYBLE_CPFD_IEEE20601_FORMAT                  (0x18u)
#define CYBLE_CPFD_UTF8_STRING                       (0x19u)
#define CYBLE_CPFD_UTF16_STRING                      (0x1au)
#define CYBLE_CPFD_OPAQUE_STRUCTURE                  (0x1bu)
#define CYBLE_CPFD_LEN                               (0x01u)

#define CYBLE_ATTR_HANDLE_LEN                        (0x02u)
#define CYBLE_DB_ATTR_HANDLE_LEN                     (0x02u)

/* GATT Server Configuration values */
#define CYBLE_GATT_SER_CNFG_BROADCAST                (0x0001u)   /* Broadcasts enabled */
#define CYBLE_GATT_SER_CNFG_DEFAULT                  (0x0000u)

#define CYBLE_CHAR_EXT_PRPTS_DESCR_RLWR              (0x0001u)  /* Reliable Write enabled */
#define CYBLE_CHAR_EXT_PRPTS_DESCR_WRAUX             (0x0002u)  /* Writable Auxiliaries enabled */

/* PDU data length */
#define CYBLE_PDU_DATA_LEN_ZERO                      (0x00u)
#define CYBLE_PDU_DATA_LEN_ONE_BYTE                  (0x01u)
#define CYBLE_PDU_DATA_LEN_TWO_BYTES                 (0x02u)
#define CYBLE_PDU_DATA_LEN_THREE_BYTES               (0x03u)
#define CYBLE_PDU_DATA_LEN_FOUR_BYTES                (0x04u)
#define CYBLE_PDU_DATA_LEN_FIVE_BYTES                (0x05u)
#define CYBLE_PDU_DATA_LEN_SIX_BYTES                 (0x06u)
#define CYBLE_PDU_DATA_LEN_SEVEN_BYTES               (0x07u)
#define CYBLE_PDU_DATA_LEN_EIGHT_BYTES               (0x08u)
#define CYBLE_PDU_DATA_LEN_NINE_BYTES                (0x09u)


/***************************************
##Bluetooth Appearance values
***************************************/

#define CYBLE_APPEARANCE_UNKNOWN                            (0u) /* Unknown */
#define CYBLE_APPEARANCE_GENERIC_PHONE                      (64u) /* Generic Phone */
#define CYBLE_APPEARANCE_GENERIC_COMPUTER                   (128u) /* Generic Computer */
#define CYBLE_APPEARANCE_GENERIC_WATCH                      (192u) /* Generic Watch */
#define CYBLE_APPEARANCE_WATCH_SPORTS_WATCH                 (193u) /* Watch: Sports Watch */
#define CYBLE_APPEARANCE_GENERIC_CLOCK                      (256u) /* Generic Clock */
#define CYBLE_APPEARANCE_GENERIC_DISPLAY                    (320u) /* Generic Display */
#define CYBLE_APPEARANCE_GENERIC_REMOTE_CONTROL             (384u) /* Generic Remote Control */
#define CYBLE_APPEARANCE_GENERIC_EYE_GLASSES                (448u) /* Generic Eye-glasses */
#define CYBLE_APPEARANCE_GENERIC_TAG                        (512u) /* Generic Tag */
#define CYBLE_APPEARANCE_GENERIC_KEYRING                    (576u) /* Generic Keyring */
#define CYBLE_APPEARANCE_GENERIC_MEDIA_PLAYER               (640u) /* Generic Media Player */
#define CYBLE_APPEARANCE_GENERIC_BARCODE_SCANNER            (704u) /* Generic Barcode Scanner */
#define CYBLE_APPEARANCE_GENERIC_THERMOMETER                (768u) /* Generic Thermometer */
#define CYBLE_APPEARANCE_THERMOMETER_EAR                    (769u) /* Thermometer: Ear */
#define CYBLE_APPEARANCE_GENERIC_HEART_RATE_SENSOR          (832u) /* Generic Heart rate Sensor */
#define CYBLE_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT  (833u) /* Heart Rate Sensor: Heart Rate Belt */
#define CYBLE_APPEARANCE_GENERIC_BLOOD_PRESSURE             (896u) /* Generic Glucose */
#define CYBLE_APPEARANCE_BLOOD_PRESSURE_ARM                 (897u) /* Glucose: Arm */
#define CYBLE_APPEARANCE_BLOOD_PRESSURE_WRIST               (898u) /* Glucose: Wrist */
#define CYBLE_APPEARANCE_GENERIC_HID                        (960u) /* Human Interface Device (HID) */
#define CYBLE_APPEARANCE_HIDS_KEYBOARD                      (961u) /* Keyboard (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_MOUSE                         (962u) /* Mouse (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_JOYSTICK                      (963u) /* Joystiq (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_GAMEPAD                       (964u) /* Gamepad (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_DIGITIZERSUBTYPE              (965u) /* Digitizer Tablet (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_CARD_READER                   (966u) /* Card Reader (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_DIGITAL_PEN                   (967u) /* Digital Pen (HID Subtype) */
#define CYBLE_APPEARANCE_HIDS_BARCODE                       (968u) /* Barcode Scanner (HID Subtype) */
#define CYBLE_APPEARANCE_GENERIC_GLUCOSE_METER              (1024u) /* Generic Glucose Meter */
#define CYBLE_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR     (1088u) /* Generic Running Walking Sensor */
#define CYBLE_APPEARANCE_RUNNING_WALKING_SENSOR_IN_SHOE     (1089u) /* Running Walking Sensor: In-Shoe */
#define CYBLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_SHOE     (1090u) /* Running Walking Sensor: On-Shoe */
#define CYBLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_HIP      (1091u) /* Running Walking Sensor: On-Hip */
#define CYBLE_APPEARANCE_GENERIC_CYCLING                    (1152u) /* Generic Cycling */
#define CYBLE_APPEARANCE_CYCLING_CYCLING_COMPUTER           (1153u) /* Cycling: Cycling Computer */
#define CYBLE_APPEARANCE_CYCLING_SPEED_SENSOR               (1154u) /* Cycling: Speed Sensor */
#define CYBLE_APPEARANCE_CYCLING_CADENCE_SENSOR             (1155u) /* Cycling: Cadence Sensor */
#define CYBLE_APPEARANCE_CYCLING_POWER_SENSOR               (1156u) /* Cycling: Power Sensor */
#define CYBLE_APPEARANCE_CYCLING_SPEED_CADENCE_SENSOR       (1157u) /* Cycling: Speed and Cadence Sensor */


/***************************************
##SMP Key size constants
***************************************/

#define CYBLE_SMP_USER_PASSKEY_SIZE                  (6u)    /* User Passkey size */
#define CYBLE_SMP_IDADDR_SIZE                        (7u)    /* Identity Address data size */
#define CYBLE_SMP_IRK_SIZE                           (16u)   /* Identity Resolving Key size */
#define CYBLE_SMP_CSRK_SIZE                          (16u)   /* Connection Signature Resolving key size */
#define CYBLE_SMP_LTK_SIZE                           (16u)   /* Long Term Key Size size */
#define CYBLE_SMP_EDIV_SIZE                          (2u)    /* Encrypted Diversifier size */
#define CYBLE_SMP_RAND_24B_SIZE                      (3u)    /* 24 Bit Random Number size */
#define CYBLE_SMP_RAND_64B_SIZE                      (8u)    /* 64 Bit Random Number size */
#define CYBLE_SMP_RAND_128B_SIZE                     (16u)   /* 128 Bit Random Number size */

#define CYBLE_GATT_16_BIT_UUID_LO_IDX                (3u)
#define CYBLE_GATT_16_BIT_UUID_HI_IDX                (2u)

#define CYBLE_8_BIT                                  (8u)
#define CYBLE_TWO_BYTES_SHIFT                        (2u)
#define CYBLE_NULL_CHARCTER                          ((char8) (0))


#if (CYBLE_GATT_ROLE_SERVER)

    #define CYBLE_GAP_DEVICE_NAME_INDEX                  (0x0002u)

    /* Characteristic value offsets */
    #define CYBLE_CHAR_LEN_HI_OFFSET                     (1u)
    #define CYBLE_CHAR_LEN_LO_OFFSET                     (0u)
    #define CYBLE_CHAR_VALUE_OFFSET                      (0x02u)

    #define CYBLE_GATT_IMPL_PERMISSION_MASK              (0xFFFF0000ul)
    #define CYBLE_GATT_CHAR_PERMISSION_MASK              (0x0000FF00ul)
    #define CYBLE_GATT_ATTR_PERMISSION_MASK              (0x000000FFul)

    #define CYBLE_GATT_ATT_TYPE_UUIT_128                 (0x00010000ul)
    #define CYBLE_GATT_ATT_VALUE_UUIT_128                (0x00020000ul)

    #define CYBLE_GATT_DB_SUPPORT_128_BIT_UUID           (GATT_DB_SUPPORT_128_BIT_UUID)

    #define CYBLE_DB_TYPE_SERVICE                        (0x00u)
    #define CYBLE_DB_TYPE_OTHER                          (0x01u)

    /* Implementation specific permission: GATT DB record type */
    #define CYBLE_DB_RECORD_MASK                         (0x001C0000ul)
    #define CYBLE_DB_SERVICE_RECORD                      (0x00000000ul)
    #define CYBLE_DB_INCLUDE_RECORD                      (0x00040000ul)
    #define CYBLE_DB_CHARACTERISTIC_RECORD               (0x00080000ul)
    #define CYBLE_DB_CHAR_VALUE_RECORD                   (0x000C0000ul)
    #define CYBLE_DB_CHAR_DESCRIPTOR_RECORD              (0x00100000ul)

#endif /* CYBLE_GATT_ROLE_SERVER */

#if (CYBLE_GATT_ROLE_CLIENT)
    #define CYBLE_GATT_EXECUTE_WRITE                     (0x01u)
    #define CYBLE_GATT_CANCEL_WRITE                      (0x00u)
#endif /* CYBLE_GATT_ROLE_CLIENT */


/***************************************
##Database macro
***************************************/

/* Get permission field of attribute handle */
#define CYBLE_GATT_DB_GET_ATTR_PERMISSION(handle)\
        (uint32)(cyBle_gattDB[(handle)-1u].permission)

/* Compare permission field of attribute entry to
    check desired permission property
 */
#define CYBLE_GATT_DB_ATTR_CHECK_PRPTY(handle,prpty)\
        ((0ul) != (CYBLE_GATT_DB_GET_ATTR_PERMISSION(handle) & (prpty)))

/* Macro to set generic value of attribute */
#define CYBLE_GATT_DB_ATTR_SET_GEN_VALUE(handle,src,length)\
        (void) memcpy\
        (\
            (void *)(cyBle_gattDB[(handle)-1u].attValue.attFormatValue.attGenericVal), \
            (const void *)(src),\
            (uint16) (length)\
        )

/* Macro to get generic value of attribute */
#define CYBLE_GATT_DB_ATTR_GET_GEN_VALUE(dst,handle,length)\
        (void) memcpy\
        (\
            (void *)(dst),\
            (const void *)(cyBle_gattDB[(handle)-1u].attValue.attFormatValue.attGenericVal), \
            (uint16)(length)\
        )

/* Macro to get start handle of attribute
   Start handle is only meaningful for characteristic and
   service declaration */
#define CYBLE_GATT_DB_GET_START_HANDLE(handle)\
        cyBle_gattDB[(handle)-1u].connHandle

/* Macro to get end handle of attribute
   Start handle is only meaningful for characteristic and
   service declaration */
#define CYBLE_GATT_DB_GET_END_HANDLE(handle)\
        cyBle_gattDB[(handle)-1u].attEndHandle


/* Macro to get attribute type (UUID) for handle */
#define CYBLE_GATT_DB_GET_UUID(handle)\
        cyBle_gattDB[(handle)-1u].attType

/* Macro to get attribute value UUID for handle */
#define CYBLE_GATT_DB_GET_ATTR_VALUE_UUID(handle)\
        cyBle_gattDB[(handle)-1u].attValue.attValueUuid

/* Macro to get length of characteristic generic value */
#define CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_LEN(handle)\
          cyBle_gattDB[(handle)-1u].attValue.attFormatValue.length

/* Macro to get pointer to characteristic generic value */
#define CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_PTR(handle)\
          (uint8 *)(cyBle_gattDB[(handle)-1u].attValue.attFormatValue.attGenericVal)
        
/* Checks Notification properties in permission field of attribute entry */
#define CYBLE_IS_NOTIFICATION_SUPPORTED(handle)\
        CYBLE_GATT_DB_ATTR_CHECK_PRPTY(handle, CYBLE_GATT_DB_CH_PROP_NOTIFY)

/* Checks Notification bit in attribute value referenced by pointer */
#define CYBLE_IS_NOTIFICATION_ENABLED_IN_PTR(valPtr)\
        ((0u) != (CYBLE_CCCD_NOTIFICATION & CyBle_Get16ByPtr(valPtr)))

/* Checks Notification bit in attribute value referenced by handle */
#define CYBLE_IS_NOTIFICATION_ENABLED(handle)\
        CYBLE_IS_NOTIFICATION_ENABLED_IN_PTR(CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_PTR(handle))
        
/* Checks Indication properties in permission field of attribute entry */
#define CYBLE_IS_INDICATION_SUPPORTED(handle)\
        CYBLE_GATT_DB_ATTR_CHECK_PRPTY(handle, CYBLE_GATT_DB_CH_PROP_INDICATE)

/* Checks Indication bit in attribute value referenced by pointer */
#define CYBLE_IS_INDICATION_ENABLED_IN_PTR(valPtr)\
        ((0u) != (CYBLE_CCCD_INDICATION & CyBle_Get16ByPtr(valPtr)))
        
/* Checks Indication bit in attribute value referenced by handle */
#define CYBLE_IS_INDICATION_ENABLED(handle)\
        CYBLE_IS_INDICATION_ENABLED_IN_PTR(CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_PTR(handle))
        
/* Checks Broadcast properties in permission field of attribute entry */
#define CYBLE_IS_BROADCAST_SUPPORTED(handle)\
        CYBLE_GATT_DB_ATTR_CHECK_PRPTY(handle, CYBLE_GATT_DB_CH_PROP_BROADCAST)

/* Checks Broadcast bit in attribute value referenced by pointer */
#define CYBLE_IS_BROADCAST_ENABLED_IN_PTR(valPtr)\
        ((0u) != (CYBLE_SCCD_BROADCAST & CyBle_Get16ByPtr(valPtr)))
        
/* Checks Broadcast bit in attribute value referenced by handle */
#define CYBLE_IS_BROADCAST_ENABLED(handle)\
        CYBLE_IS_BROADCAST_ENABLED_IN_PTR(CYBLE_GATT_DB_ATTR_GET_ATTR_GEN_PTR(handle))

#endif /* CY_BLE_CYBLE_GATT_H  */


/* [] END OF FILE */
