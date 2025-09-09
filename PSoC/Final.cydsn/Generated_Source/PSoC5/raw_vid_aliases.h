/*******************************************************************************
* File Name: raw_vid.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_raw_vid_ALIASES_H) /* Pins raw_vid_ALIASES_H */
#define CY_PINS_raw_vid_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define raw_vid_0			(raw_vid__0__PC)
#define raw_vid_0_INTR	((uint16)((uint16)0x0001u << raw_vid__0__SHIFT))

#define raw_vid_INTR_ALL	 ((uint16)(raw_vid_0_INTR))

#endif /* End Pins raw_vid_ALIASES_H */


/* [] END OF FILE */
