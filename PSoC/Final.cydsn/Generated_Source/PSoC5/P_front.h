/*******************************************************************************
* File Name: P_front.h  
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

#if !defined(CY_PINS_P_front_H) /* Pins P_front_H */
#define CY_PINS_P_front_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P_front_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P_front__PORT == 15 && ((P_front__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P_front_Write(uint8 value);
void    P_front_SetDriveMode(uint8 mode);
uint8   P_front_ReadDataReg(void);
uint8   P_front_Read(void);
void    P_front_SetInterruptMode(uint16 position, uint16 mode);
uint8   P_front_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P_front_SetDriveMode() function.
     *  @{
     */
        #define P_front_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P_front_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P_front_DM_RES_UP          PIN_DM_RES_UP
        #define P_front_DM_RES_DWN         PIN_DM_RES_DWN
        #define P_front_DM_OD_LO           PIN_DM_OD_LO
        #define P_front_DM_OD_HI           PIN_DM_OD_HI
        #define P_front_DM_STRONG          PIN_DM_STRONG
        #define P_front_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P_front_MASK               P_front__MASK
#define P_front_SHIFT              P_front__SHIFT
#define P_front_WIDTH              1u

/* Interrupt constants */
#if defined(P_front__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P_front_SetInterruptMode() function.
     *  @{
     */
        #define P_front_INTR_NONE      (uint16)(0x0000u)
        #define P_front_INTR_RISING    (uint16)(0x0001u)
        #define P_front_INTR_FALLING   (uint16)(0x0002u)
        #define P_front_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P_front_INTR_MASK      (0x01u) 
#endif /* (P_front__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P_front_PS                     (* (reg8 *) P_front__PS)
/* Data Register */
#define P_front_DR                     (* (reg8 *) P_front__DR)
/* Port Number */
#define P_front_PRT_NUM                (* (reg8 *) P_front__PRT) 
/* Connect to Analog Globals */                                                  
#define P_front_AG                     (* (reg8 *) P_front__AG)                       
/* Analog MUX bux enable */
#define P_front_AMUX                   (* (reg8 *) P_front__AMUX) 
/* Bidirectional Enable */                                                        
#define P_front_BIE                    (* (reg8 *) P_front__BIE)
/* Bit-mask for Aliased Register Access */
#define P_front_BIT_MASK               (* (reg8 *) P_front__BIT_MASK)
/* Bypass Enable */
#define P_front_BYP                    (* (reg8 *) P_front__BYP)
/* Port wide control signals */                                                   
#define P_front_CTL                    (* (reg8 *) P_front__CTL)
/* Drive Modes */
#define P_front_DM0                    (* (reg8 *) P_front__DM0) 
#define P_front_DM1                    (* (reg8 *) P_front__DM1)
#define P_front_DM2                    (* (reg8 *) P_front__DM2) 
/* Input Buffer Disable Override */
#define P_front_INP_DIS                (* (reg8 *) P_front__INP_DIS)
/* LCD Common or Segment Drive */
#define P_front_LCD_COM_SEG            (* (reg8 *) P_front__LCD_COM_SEG)
/* Enable Segment LCD */
#define P_front_LCD_EN                 (* (reg8 *) P_front__LCD_EN)
/* Slew Rate Control */
#define P_front_SLW                    (* (reg8 *) P_front__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P_front_PRTDSI__CAPS_SEL       (* (reg8 *) P_front__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P_front_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P_front__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P_front_PRTDSI__OE_SEL0        (* (reg8 *) P_front__PRTDSI__OE_SEL0) 
#define P_front_PRTDSI__OE_SEL1        (* (reg8 *) P_front__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P_front_PRTDSI__OUT_SEL0       (* (reg8 *) P_front__PRTDSI__OUT_SEL0) 
#define P_front_PRTDSI__OUT_SEL1       (* (reg8 *) P_front__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P_front_PRTDSI__SYNC_OUT       (* (reg8 *) P_front__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P_front__SIO_CFG)
    #define P_front_SIO_HYST_EN        (* (reg8 *) P_front__SIO_HYST_EN)
    #define P_front_SIO_REG_HIFREQ     (* (reg8 *) P_front__SIO_REG_HIFREQ)
    #define P_front_SIO_CFG            (* (reg8 *) P_front__SIO_CFG)
    #define P_front_SIO_DIFF           (* (reg8 *) P_front__SIO_DIFF)
#endif /* (P_front__SIO_CFG) */

/* Interrupt Registers */
#if defined(P_front__INTSTAT)
    #define P_front_INTSTAT            (* (reg8 *) P_front__INTSTAT)
    #define P_front_SNAP               (* (reg8 *) P_front__SNAP)
    
	#define P_front_0_INTTYPE_REG 		(* (reg8 *) P_front__0__INTTYPE)
#endif /* (P_front__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P_front_H */


/* [] END OF FILE */
