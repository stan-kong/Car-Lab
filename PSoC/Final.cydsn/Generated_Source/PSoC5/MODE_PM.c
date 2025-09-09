/*******************************************************************************
* File Name: MODE_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MODE.h"

/* Check for removal by optimization */
#if !defined(MODE_Sync_ctrl_reg__REMOVED)

static MODE_BACKUP_STRUCT  MODE_backup = {0u};

    
/*******************************************************************************
* Function Name: MODE_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MODE_SaveConfig(void) 
{
    MODE_backup.controlState = MODE_Control;
}


/*******************************************************************************
* Function Name: MODE_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void MODE_RestoreConfig(void) 
{
     MODE_Control = MODE_backup.controlState;
}


/*******************************************************************************
* Function Name: MODE_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MODE_Sleep(void) 
{
    MODE_SaveConfig();
}


/*******************************************************************************
* Function Name: MODE_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MODE_Wakeup(void)  
{
    MODE_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
