/*******************************************************************************
* File Name: P_back.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P_back_H) /* Pins P_back_H */
#define CY_PINS_P_back_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P_back_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P_back__PORT == 15 && ((P_back__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P_back_Write(uint8 value);
void    P_back_SetDriveMode(uint8 mode);
uint8   P_back_ReadDataReg(void);
uint8   P_back_Read(void);
void    P_back_SetInterruptMode(uint16 position, uint16 mode);
uint8   P_back_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P_back_SetDriveMode() function.
     *  @{
     */
        #define P_back_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P_back_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P_back_DM_RES_UP          PIN_DM_RES_UP
        #define P_back_DM_RES_DWN         PIN_DM_RES_DWN
        #define P_back_DM_OD_LO           PIN_DM_OD_LO
        #define P_back_DM_OD_HI           PIN_DM_OD_HI
        #define P_back_DM_STRONG          PIN_DM_STRONG
        #define P_back_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P_back_MASK               P_back__MASK
#define P_back_SHIFT              P_back__SHIFT
#define P_back_WIDTH              1u

/* Interrupt constants */
#if defined(P_back__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P_back_SetInterruptMode() function.
     *  @{
     */
        #define P_back_INTR_NONE      (uint16)(0x0000u)
        #define P_back_INTR_RISING    (uint16)(0x0001u)
        #define P_back_INTR_FALLING   (uint16)(0x0002u)
        #define P_back_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P_back_INTR_MASK      (0x01u) 
#endif /* (P_back__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P_back_PS                     (* (reg8 *) P_back__PS)
/* Data Register */
#define P_back_DR                     (* (reg8 *) P_back__DR)
/* Port Number */
#define P_back_PRT_NUM                (* (reg8 *) P_back__PRT) 
/* Connect to Analog Globals */                                                  
#define P_back_AG                     (* (reg8 *) P_back__AG)                       
/* Analog MUX bux enable */
#define P_back_AMUX                   (* (reg8 *) P_back__AMUX) 
/* Bidirectional Enable */                                                        
#define P_back_BIE                    (* (reg8 *) P_back__BIE)
/* Bit-mask for Aliased Register Access */
#define P_back_BIT_MASK               (* (reg8 *) P_back__BIT_MASK)
/* Bypass Enable */
#define P_back_BYP                    (* (reg8 *) P_back__BYP)
/* Port wide control signals */                                                   
#define P_back_CTL                    (* (reg8 *) P_back__CTL)
/* Drive Modes */
#define P_back_DM0                    (* (reg8 *) P_back__DM0) 
#define P_back_DM1                    (* (reg8 *) P_back__DM1)
#define P_back_DM2                    (* (reg8 *) P_back__DM2) 
/* Input Buffer Disable Override */
#define P_back_INP_DIS                (* (reg8 *) P_back__INP_DIS)
/* LCD Common or Segment Drive */
#define P_back_LCD_COM_SEG            (* (reg8 *) P_back__LCD_COM_SEG)
/* Enable Segment LCD */
#define P_back_LCD_EN                 (* (reg8 *) P_back__LCD_EN)
/* Slew Rate Control */
#define P_back_SLW                    (* (reg8 *) P_back__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P_back_PRTDSI__CAPS_SEL       (* (reg8 *) P_back__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P_back_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P_back__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P_back_PRTDSI__OE_SEL0        (* (reg8 *) P_back__PRTDSI__OE_SEL0) 
#define P_back_PRTDSI__OE_SEL1        (* (reg8 *) P_back__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P_back_PRTDSI__OUT_SEL0       (* (reg8 *) P_back__PRTDSI__OUT_SEL0) 
#define P_back_PRTDSI__OUT_SEL1       (* (reg8 *) P_back__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P_back_PRTDSI__SYNC_OUT       (* (reg8 *) P_back__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P_back__SIO_CFG)
    #define P_back_SIO_HYST_EN        (* (reg8 *) P_back__SIO_HYST_EN)
    #define P_back_SIO_REG_HIFREQ     (* (reg8 *) P_back__SIO_REG_HIFREQ)
    #define P_back_SIO_CFG            (* (reg8 *) P_back__SIO_CFG)
    #define P_back_SIO_DIFF           (* (reg8 *) P_back__SIO_DIFF)
#endif /* (P_back__SIO_CFG) */

/* Interrupt Registers */
#if defined(P_back__INTSTAT)
    #define P_back_INTSTAT            (* (reg8 *) P_back__INTSTAT)
    #define P_back_SNAP               (* (reg8 *) P_back__SNAP)
    
	#define P_back_0_INTTYPE_REG 		(* (reg8 *) P_back__0__INTTYPE)
#endif /* (P_back__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P_back_H */


/* [] END OF FILE */
