/*******************************************************************************
* File Name: raw_vid.h  
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

#if !defined(CY_PINS_raw_vid_H) /* Pins raw_vid_H */
#define CY_PINS_raw_vid_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "raw_vid_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 raw_vid__PORT == 15 && ((raw_vid__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    raw_vid_Write(uint8 value);
void    raw_vid_SetDriveMode(uint8 mode);
uint8   raw_vid_ReadDataReg(void);
uint8   raw_vid_Read(void);
void    raw_vid_SetInterruptMode(uint16 position, uint16 mode);
uint8   raw_vid_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the raw_vid_SetDriveMode() function.
     *  @{
     */
        #define raw_vid_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define raw_vid_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define raw_vid_DM_RES_UP          PIN_DM_RES_UP
        #define raw_vid_DM_RES_DWN         PIN_DM_RES_DWN
        #define raw_vid_DM_OD_LO           PIN_DM_OD_LO
        #define raw_vid_DM_OD_HI           PIN_DM_OD_HI
        #define raw_vid_DM_STRONG          PIN_DM_STRONG
        #define raw_vid_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define raw_vid_MASK               raw_vid__MASK
#define raw_vid_SHIFT              raw_vid__SHIFT
#define raw_vid_WIDTH              1u

/* Interrupt constants */
#if defined(raw_vid__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in raw_vid_SetInterruptMode() function.
     *  @{
     */
        #define raw_vid_INTR_NONE      (uint16)(0x0000u)
        #define raw_vid_INTR_RISING    (uint16)(0x0001u)
        #define raw_vid_INTR_FALLING   (uint16)(0x0002u)
        #define raw_vid_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define raw_vid_INTR_MASK      (0x01u) 
#endif /* (raw_vid__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define raw_vid_PS                     (* (reg8 *) raw_vid__PS)
/* Data Register */
#define raw_vid_DR                     (* (reg8 *) raw_vid__DR)
/* Port Number */
#define raw_vid_PRT_NUM                (* (reg8 *) raw_vid__PRT) 
/* Connect to Analog Globals */                                                  
#define raw_vid_AG                     (* (reg8 *) raw_vid__AG)                       
/* Analog MUX bux enable */
#define raw_vid_AMUX                   (* (reg8 *) raw_vid__AMUX) 
/* Bidirectional Enable */                                                        
#define raw_vid_BIE                    (* (reg8 *) raw_vid__BIE)
/* Bit-mask for Aliased Register Access */
#define raw_vid_BIT_MASK               (* (reg8 *) raw_vid__BIT_MASK)
/* Bypass Enable */
#define raw_vid_BYP                    (* (reg8 *) raw_vid__BYP)
/* Port wide control signals */                                                   
#define raw_vid_CTL                    (* (reg8 *) raw_vid__CTL)
/* Drive Modes */
#define raw_vid_DM0                    (* (reg8 *) raw_vid__DM0) 
#define raw_vid_DM1                    (* (reg8 *) raw_vid__DM1)
#define raw_vid_DM2                    (* (reg8 *) raw_vid__DM2) 
/* Input Buffer Disable Override */
#define raw_vid_INP_DIS                (* (reg8 *) raw_vid__INP_DIS)
/* LCD Common or Segment Drive */
#define raw_vid_LCD_COM_SEG            (* (reg8 *) raw_vid__LCD_COM_SEG)
/* Enable Segment LCD */
#define raw_vid_LCD_EN                 (* (reg8 *) raw_vid__LCD_EN)
/* Slew Rate Control */
#define raw_vid_SLW                    (* (reg8 *) raw_vid__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define raw_vid_PRTDSI__CAPS_SEL       (* (reg8 *) raw_vid__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define raw_vid_PRTDSI__DBL_SYNC_IN    (* (reg8 *) raw_vid__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define raw_vid_PRTDSI__OE_SEL0        (* (reg8 *) raw_vid__PRTDSI__OE_SEL0) 
#define raw_vid_PRTDSI__OE_SEL1        (* (reg8 *) raw_vid__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define raw_vid_PRTDSI__OUT_SEL0       (* (reg8 *) raw_vid__PRTDSI__OUT_SEL0) 
#define raw_vid_PRTDSI__OUT_SEL1       (* (reg8 *) raw_vid__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define raw_vid_PRTDSI__SYNC_OUT       (* (reg8 *) raw_vid__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(raw_vid__SIO_CFG)
    #define raw_vid_SIO_HYST_EN        (* (reg8 *) raw_vid__SIO_HYST_EN)
    #define raw_vid_SIO_REG_HIFREQ     (* (reg8 *) raw_vid__SIO_REG_HIFREQ)
    #define raw_vid_SIO_CFG            (* (reg8 *) raw_vid__SIO_CFG)
    #define raw_vid_SIO_DIFF           (* (reg8 *) raw_vid__SIO_DIFF)
#endif /* (raw_vid__SIO_CFG) */

/* Interrupt Registers */
#if defined(raw_vid__INTSTAT)
    #define raw_vid_INTSTAT            (* (reg8 *) raw_vid__INTSTAT)
    #define raw_vid_SNAP               (* (reg8 *) raw_vid__SNAP)
    
	#define raw_vid_0_INTTYPE_REG 		(* (reg8 *) raw_vid__0__INTTYPE)
#endif /* (raw_vid__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_raw_vid_H */


/* [] END OF FILE */
