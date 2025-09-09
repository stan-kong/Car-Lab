/*******************************************************************************
* File Name: STOP_PM.c
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

#include "STOP.h"

/* Check for removal by optimization */
#if !defined(STOP_Sync_ctrl_reg__REMOVED)

static STOP_BACKUP_STRUCT  STOP_backup = {0u};

    
/*******************************************************************************
* Function Name: STOP_SaveConfig
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
void STOP_SaveConfig(void) 
{
    STOP_backup.controlState = STOP_Control;
}


/*******************************************************************************
* Function Name: STOP_RestoreConfig
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
void STOP_RestoreConfig(void) 
{
     STOP_Control = STOP_backup.controlState;
}


/*******************************************************************************
* Function Name: STOP_Sleep
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
void STOP_Sleep(void) 
{
    STOP_SaveConfig();
}


/*******************************************************************************
* Function Name: STOP_Wakeup
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
void STOP_Wakeup(void)  
{
    STOP_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
