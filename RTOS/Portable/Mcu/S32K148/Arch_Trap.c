/* PRQA S 3108++ */
/**
 * Copyright (C) 2024 Isoft Infrastructure Software Co., Ltd.
 * SPDX-License-Identifier: LGPL-2.1-only-with-exception OR  LicenseRef-Commercial-License
 *
 * This library is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation; version 2.1.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with this library;
 * if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * or see <https://www.gnu.org/licenses/>.
 *
 * Alternatively, this file may be used under the terms of the Isoft Infrastructure Software Co., Ltd.
 * Commercial License, in which case the provisions of the Isoft Infrastructure Software Co., Ltd.
 * Commercial License shall apply instead of those of the GNU Lesser General Public License.
 *
 * You should have received a copy of the Isoft Infrastructure Software Co., Ltd.  Commercial License
 * along with this program. If not, please find it at <https://EasyXMen.com/xy/reference/permissions.html>
 *
 ********************************************************************************
 **                                                                            **
 **  FILENAME    : Arch_Trap.c                                                 **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : functions related to the processor exception.               **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*=======[I N C L U D E S]====================================================*/
#include "Os_Internal.h"
/*=======[V E R S I O N  C H E C K]==========================================*/

/*=======[M A C R O S]=======================================================*/

/*=======[E X T E R N A L   D A T A]=========================================*/
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
#define OS_START_SEC_VAR_CLEARED_CLONE_16
#include "Os_MemMap.h"
VAR(uint16, OS_VAR)      HardFault_Flag         = 0U;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_16
#include "Os_MemMap.h"
#endif
/*=======[I N T E R N A L   D A T A]=========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]=======*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]===================*/


#if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
#define OS_START_SEC_CODE
#include "Os_MemMap.h"  
/*****************************************************************************/
/*
 * Brief                <SVC_Handler>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <System services>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) SVC_Handler(void)
{
    Os_SetCpuMode(OS_CPUMODE_SUPERVISOR);
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif

#define OS_START_SEC_CODE
#include "Os_MemMap.h"    
FUNC(void, OS_CODE) HardFault_Handler(void)
{
    uint32 i = 1;
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
    uint32 WhoHook = OS_TMPROT_HOOK_OSAPP;
    uint32 isMpuError = OS_REG32(OS_MPU_CESR_ADDR) & OS_MPU_SPERR_BIT;
    OS_REG32(OS_MPU_CESR_ADDR) = OS_MPU_SPERR_BIT;
    HardFault_Flag = 1U;
    if (0 != isMpuError)
    {
        if (OS_LEVEL_TASK == Os_SCB.sysOsLevel)
        {
            WhoHook = OS_TMPROT_HOOK_TASK;
        }
        else if (OS_LEVEL_ISR2 == Os_SCB.sysOsLevel)
        {
            WhoHook = OS_TMPROT_HOOK_ISR;
            Os_IsrTempIPSR = Os_IsrIPSR[Os_IntNestISR2 - 1u];
        }
        else
        {
            /* Do nothing. */
        }
        (void)Os_CallProtectionHook(E_OS_PROTECTION_MEMORY, WhoHook);
    }
    else
    {
        while (i);
    }
    HardFault_Flag = 0;
#else
    while (i);
#endif
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

