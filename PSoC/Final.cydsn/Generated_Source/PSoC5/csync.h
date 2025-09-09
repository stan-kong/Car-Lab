/*******************************************************************************
* File Name: csync.h  
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

#if !defined(CY_PINS_csync_H) /* Pins csync_H */
#define CY_PINS_csync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "csync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 csync__PORT == 15 && ((csync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    csync_Write(uint8 value);
void    csync_SetDriveMode(uint8 mode);
uint8   csync_ReadDataReg(void);
uint8   csync_Read(void);
void    csync_SetInterruptMode(uint16 position, uint16 mode);
uint8   csync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the csync_SetDriveMode() function.
     *  @{
     */
        #define csync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define csync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define csync_DM_RES_UP          PIN_DM_RES_UP
        #define csync_DM_RES_DWN         PIN_DM_RES_DWN
        #define csync_DM_OD_LO           PIN_DM_OD_LO
        #define csync_DM_OD_HI           PIN_DM_OD_HI
        #define csync_DM_STRONG          PIN_DM_STRONG
        #define csync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define csync_MASK               csync__MASK
#define csync_SHIFT              csync__SHIFT
#define csync_WIDTH              1u

/* Interrupt constants */
#if defined(csync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in csync_SetInterruptMode() function.
     *  @{
     */
        #define csync_INTR_NONE      (uint16)(0x0000u)
        #define csync_INTR_RISING    (uint16)(0x0001u)
        #define csync_INTR_FALLING   (uint16)(0x0002u)
        #define csync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define csync_INTR_MASK      (0x01u) 
#endif /* (csync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define csync_PS                     (* (reg8 *) csync__PS)
/* Data Register */
#define csync_DR                     (* (reg8 *) csync__DR)
/* Port Number */
#define csync_PRT_NUM                (* (reg8 *) csync__PRT) 
/* Connect to Analog Globals */                                                  
#define csync_AG                     (* (reg8 *) csync__AG)                       
/* Analog MUX bux enable */
#define csync_AMUX                   (* (reg8 *) csync__AMUX) 
/* Bidirectional Enable */                                                        
#define csync_BIE                    (* (reg8 *) csync__BIE)
/* Bit-mask for Aliased Register Access */
#define csync_BIT_MASK               (* (reg8 *) csync__BIT_MASK)
/* Bypass Enable */
#define csync_BYP                    (* (reg8 *) csync__BYP)
/* Port wide control signals */                                                   
#define csync_CTL                    (* (reg8 *) csync__CTL)
/* Drive Modes */
#define csync_DM0                    (* (reg8 *) csync__DM0) 
#define csync_DM1                    (* (reg8 *) csync__DM1)
#define csync_DM2                    (* (reg8 *) csync__DM2) 
/* Input Buffer Disable Override */
#define csync_INP_DIS                (* (reg8 *) csync__INP_DIS)
/* LCD Common or Segment Drive */
#define csync_LCD_COM_SEG            (* (reg8 *) csync__LCD_COM_SEG)
/* Enable Segment LCD */
#define csync_LCD_EN                 (* (reg8 *) csync__LCD_EN)
/* Slew Rate Control */
#define csync_SLW                    (* (reg8 *) csync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define csync_PRTDSI__CAPS_SEL       (* (reg8 *) csync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define csync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) csync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define csync_PRTDSI__OE_SEL0        (* (reg8 *) csync__PRTDSI__OE_SEL0) 
#define csync_PRTDSI__OE_SEL1        (* (reg8 *) csync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define csync_PRTDSI__OUT_SEL0       (* (reg8 *) csync__PRTDSI__OUT_SEL0) 
#define csync_PRTDSI__OUT_SEL1       (* (reg8 *) csync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define csync_PRTDSI__SYNC_OUT       (* (reg8 *) csync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(csync__SIO_CFG)
    #define csync_SIO_HYST_EN        (* (reg8 *) csync__SIO_HYST_EN)
    #define csync_SIO_REG_HIFREQ     (* (reg8 *) csync__SIO_REG_HIFREQ)
    #define csync_SIO_CFG            (* (reg8 *) csync__SIO_CFG)
    #define csync_SIO_DIFF           (* (reg8 *) csync__SIO_DIFF)
#endif /* (csync__SIO_CFG) */

/* Interrupt Registers */
#if defined(csync__INTSTAT)
    #define csync_INTSTAT            (* (reg8 *) csync__INTSTAT)
    #define csync_SNAP               (* (reg8 *) csync__SNAP)
    
	#define csync_0_INTTYPE_REG 		(* (reg8 *) csync__0__INTTYPE)
#endif /* (csync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_csync_H */


/* [] END OF FILE */
