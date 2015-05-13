/*******************************************************************************
* File Name: UART1_TX.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_UART1_TX_H) /* Pins UART1_TX_H */
#define CY_PINS_UART1_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UART1_TX_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    UART1_TX_Write(uint8 value) ;
void    UART1_TX_SetDriveMode(uint8 mode) ;
uint8   UART1_TX_ReadDataReg(void) ;
uint8   UART1_TX_Read(void) ;
uint8   UART1_TX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define UART1_TX_DRIVE_MODE_BITS        (3)
#define UART1_TX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UART1_TX_DRIVE_MODE_BITS))

#define UART1_TX_DM_ALG_HIZ         (0x00u)
#define UART1_TX_DM_DIG_HIZ         (0x01u)
#define UART1_TX_DM_RES_UP          (0x02u)
#define UART1_TX_DM_RES_DWN         (0x03u)
#define UART1_TX_DM_OD_LO           (0x04u)
#define UART1_TX_DM_OD_HI           (0x05u)
#define UART1_TX_DM_STRONG          (0x06u)
#define UART1_TX_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define UART1_TX_MASK               UART1_TX__MASK
#define UART1_TX_SHIFT              UART1_TX__SHIFT
#define UART1_TX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UART1_TX_PS                     (* (reg32 *) UART1_TX__PS)
/* Port Configuration */
#define UART1_TX_PC                     (* (reg32 *) UART1_TX__PC)
/* Data Register */
#define UART1_TX_DR                     (* (reg32 *) UART1_TX__DR)
/* Input Buffer Disable Override */
#define UART1_TX_INP_DIS                (* (reg32 *) UART1_TX__PC2)


#if defined(UART1_TX__INTSTAT)  /* Interrupt Registers */

    #define UART1_TX_INTSTAT                (* (reg32 *) UART1_TX__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define UART1_TX_DRIVE_MODE_SHIFT       (0x00u)
#define UART1_TX_DRIVE_MODE_MASK        (0x07u << UART1_TX_DRIVE_MODE_SHIFT)


#endif /* End Pins UART1_TX_H */


/* [] END OF FILE */
