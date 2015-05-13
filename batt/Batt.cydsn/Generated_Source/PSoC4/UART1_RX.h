/*******************************************************************************
* File Name: UART1_RX.h  
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

#if !defined(CY_PINS_UART1_RX_H) /* Pins UART1_RX_H */
#define CY_PINS_UART1_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UART1_RX_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    UART1_RX_Write(uint8 value) ;
void    UART1_RX_SetDriveMode(uint8 mode) ;
uint8   UART1_RX_ReadDataReg(void) ;
uint8   UART1_RX_Read(void) ;
uint8   UART1_RX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define UART1_RX_DRIVE_MODE_BITS        (3)
#define UART1_RX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UART1_RX_DRIVE_MODE_BITS))

#define UART1_RX_DM_ALG_HIZ         (0x00u)
#define UART1_RX_DM_DIG_HIZ         (0x01u)
#define UART1_RX_DM_RES_UP          (0x02u)
#define UART1_RX_DM_RES_DWN         (0x03u)
#define UART1_RX_DM_OD_LO           (0x04u)
#define UART1_RX_DM_OD_HI           (0x05u)
#define UART1_RX_DM_STRONG          (0x06u)
#define UART1_RX_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define UART1_RX_MASK               UART1_RX__MASK
#define UART1_RX_SHIFT              UART1_RX__SHIFT
#define UART1_RX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UART1_RX_PS                     (* (reg32 *) UART1_RX__PS)
/* Port Configuration */
#define UART1_RX_PC                     (* (reg32 *) UART1_RX__PC)
/* Data Register */
#define UART1_RX_DR                     (* (reg32 *) UART1_RX__DR)
/* Input Buffer Disable Override */
#define UART1_RX_INP_DIS                (* (reg32 *) UART1_RX__PC2)


#if defined(UART1_RX__INTSTAT)  /* Interrupt Registers */

    #define UART1_RX_INTSTAT                (* (reg32 *) UART1_RX__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define UART1_RX_DRIVE_MODE_SHIFT       (0x00u)
#define UART1_RX_DRIVE_MODE_MASK        (0x07u << UART1_RX_DRIVE_MODE_SHIFT)


#endif /* End Pins UART1_RX_H */


/* [] END OF FILE */
