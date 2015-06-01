/*******************************************************************************
* File Name: T2_RESET.h  
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

#if !defined(CY_CONTROL_REG_T2_RESET_H) /* CY_CONTROL_REG_T2_RESET_H */
#define CY_CONTROL_REG_T2_RESET_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} T2_RESET_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    T2_RESET_Write(uint8 control) ;
uint8   T2_RESET_Read(void) ;

void T2_RESET_SaveConfig(void) ;
void T2_RESET_RestoreConfig(void) ;
void T2_RESET_Sleep(void) ; 
void T2_RESET_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define T2_RESET_Control        (* (reg8 *) T2_RESET_Sync_ctrl_reg__CONTROL_REG )
#define T2_RESET_Control_PTR    (  (reg8 *) T2_RESET_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_T2_RESET_H */


/* [] END OF FILE */
