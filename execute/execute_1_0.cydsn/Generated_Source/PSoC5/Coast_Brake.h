/*******************************************************************************
* File Name: Coast_Brake.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Coast_Brake_H) /* CY_CONTROL_REG_Coast_Brake_H */
#define CY_CONTROL_REG_Coast_Brake_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Coast_Brake_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Coast_Brake_Write(uint8 control) ;
uint8   Coast_Brake_Read(void) ;

void Coast_Brake_SaveConfig(void) ;
void Coast_Brake_RestoreConfig(void) ;
void Coast_Brake_Sleep(void) ; 
void Coast_Brake_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Coast_Brake_Control        (* (reg8 *) Coast_Brake_Sync_ctrl_reg__CONTROL_REG )
#define Coast_Brake_Control_PTR    (  (reg8 *) Coast_Brake_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Coast_Brake_H */


/* [] END OF FILE */
