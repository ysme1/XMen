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
 **  FILENAME    : Arch_Mpu.c                                                  **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Mpu driver                                                  **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*=======[I N C L U D E S]====================================================*/
#include "Os_Internal.h"

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
#define OS_START_SEC_VAR_CLEARED_CLONE_PTR
#include "Os_MemMap.h"
P2CONST(OS_TASK_ADDR, AUTOMATIC, OS_VAR)   Os_TaskDAddr;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_PTR
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CLONE_PTR
#include "Os_MemMap.h"
P2CONST(OS_ISR_ADDR, AUTOMATIC, OS_VAR)    Os_IsrDAddr;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_PTR
#include "Os_MemMap.h"
#endif

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[I N T E R N A L   D A T A]==========================================*/

#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
#define OS_START_SEC_VAR_CLEARED_CLONE_32
#include "Os_MemMap.h"
static VAR(uint32, OS_VAR)                 Os_PSW_PRS;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_32
#include "Os_MemMap.h"
#endif

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Set the memory protection properties>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Reentrant>
 * param[in]            <MpSetIdx>
 * param[out]           <None>
 * param[in/out]        <None>
 * return               <None>
 * CallByAPI            <Os_ArchInitKnMemMap and so on>
 * REQ ID               <DD_1_0752, DD_1_0753>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchSetMemProtSet(uint32 MpSetIdx)
{
    Os_PSW_PRS = MpSetIdx << 12u;
    if (0x00U == MpSetIdx)
    {
       Os_ArchSetTruReg();
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Gets the memory protection property>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Reentrant>
 * param[in]            <None>
 * param[out]           <None>
 * param[in/out]        <None>
 * return               <None>
 * CallByAPI            <Os_ArchSetIsrMemMap,Os_ArchSetTaskMemMap>
 * REQ ID               <DD_1_0754, DD_1_0755>
 */
/******************************************************************************/
static FUNC(uint32, OS_CODE) Os_ArchGetMemProtSet(void)
{
    return Os_PSW_PRS;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Os_ArchSetIsrMemMap>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <Os_EnterISR2,Os_ExitISR2>
 * REQ ID               <DD_1_0758, DD_1_0759, DD_1_1308, DD_1_1309, DD_1_1310>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchSetIsrMemMap
(
    ISRType         IsrId, 
    ApplicationType HostAppId, 
    uint32          isTrusted
)
{
    VAR(uint32,OS_VAR) temp = (Os_ArchGetMemProtSet() & 0x00003000U) >> 12u;

    /* Find out which register set in use  register 0 should not be used here */
    if (0x02U == temp)
    {
        /*set 2: OS_DPR_7~OS_DPR_12, OS_CPR_4~OS_CPR_6*/
        if (TRUE != isTrusted) /* Non-trusted app running. */
        {
            Os_ArchSetNonTruIsrReg(IsrId, HostAppId);/* PRQA S 0306 */ /* MISRA Rule 11.4 */
        }
        else  /* Trusted app or os_kernel running. */
        {
            /*OSTrustedApplicationWithProtection != TRUE*/
            if (Os_AppCfg[HostAppId].OsTrustedAppWithProtection != TRUE)
            {
                Os_ArchSetTruReg();
            }
            else
            {
                Os_ArchSetTruIsrProtReg(IsrId, HostAppId);/* PRQA S 0306 */ /* MISRA Rule 11.4 */  
            }
        }
    }
    else
    {
        #if (TRUE == CFG_PROTECTIONHOOK)
        (void)Os_CallProtectionHook(E_OS_PROTECTION_MEMORY,
                OS_TMPROT_HOOK_OSAPP);
        #endif /* TRUE == CFG_PROTECTIONHOOK */
    }

    return;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <MemMap for Memory Protection Settings Task>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ExitISR2, Os_SwitchTask>
 * REQ ID               <DD_1_0760, DD_1_0761, DD_1_1311, DD_1_1312, DD_1_1313>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchSetTaskMemMap
(
    TaskType        TaskId, 
    ApplicationType HostAppId, 
    uint32          isTrusted
)
{
    VAR(uint32,OS_VAR) temp = (Os_ArchGetMemProtSet() & 0x00003000U) >> 12u;

    /* Find out which register set in use  register 0 should not be used here */
    if (0x01U == temp)
    {
        if (TRUE != isTrusted) /* Non-trusted app running. */
        {
            Os_ArchSetNonTruTskReg(TaskId, HostAppId);/* PRQA S 0306 */ /* MISRA Rule 11.4 */
        }
        else  /* Trusted app or os_kernel running. */
        {
            /*OSTrustedApplicationWithProtection != TRUE*/
            if (Os_AppCfg[HostAppId].OsTrustedAppWithProtection != TRUE)
            {
                Os_ArchSetTruReg();
            }
            else
            {
                Os_ArchSetTruTskProtReg(TaskId, HostAppId);/* PRQA S 0306 */ /* MISRA Rule 11.4 */
            }
        }
    }
    else
    {
        #if (TRUE == CFG_PROTECTIONHOOK)
        (void)Os_CallProtectionHook(E_OS_PROTECTION_MEMORY, OS_TMPROT_HOOK_OSAPP);
        #endif /* TRUE == CFG_PROTECTIONHOOK */
    }

    return;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Initialize the memory protection mapping for the os>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Reentrant>
 * param[in]            <None>
 * param[out]           <None>
 * param[in/out]        <None>
 * return               <None>
 * CallByAPI            <Os_InitMemProt>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchInitKnMemMap(void)
{
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Cat1 MemMap for Memory Protection Settings Task>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_MemProtTaskCat1Map(void)
{
    VAR(ApplicationType,OS_VAR) sysAppId = Os_SCB.sysAppId;
    VAR(Os_ApplicationType,OS_VAR) sysRunningAppID = Os_SCB.sysRunningAppID;

    if (sysAppId != sysRunningAppID)
    {
        /* Memory protection: Set memory map according to new running task. */
        /*new task,default set register 03*/
        Os_ArchSetMemProtSet(0x01U);
        Os_ArchSetTaskMemMap(Os_GetObjLocalId(Os_SCB.sysRunningTaskID),
                        sysRunningAppID,
                        (uint32)Os_AppCfg[sysRunningAppID].OsTrusted);
    }
    else
    {
        /*SYS_APP, as OS kernel, have all access rights*/
        Os_ArchSetMemProtSet(0x00U);
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Cat2 MemMap for Memory Protection Settings Task>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_MemProtTaskCat2Map(void)
{
    VAR(ApplicationType,OS_VAR) sysAppId = Os_SCB.sysAppId;
    VAR(Os_ApplicationType,OS_VAR) sysRunningAppID = Os_SCB.sysRunningAppID;
    
    if (sysAppId != sysRunningAppID)
    {
        /* Memory protection: Set memory map according to new running task. */
        Os_ArchSetMemProtSet(0x01U);
        Os_ArchSetTaskMemMap(Os_GetObjLocalId(Os_SCB.sysRunningTaskID),
                        sysRunningAppID,
                        (uint32)Os_AppCfg[sysRunningAppID].OsTrusted);
    }
    else
    {
        /*SYS_APP, as OS kernel, have all access rights*/
        Os_ArchSetMemProtSet(0x00U);
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <MemMap for Memory Protection Settings ISR>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_MemProtIsrMap(void)
{
    /*if memory protection is configured*/
    /*Preparing to enter the ISR2 outside with its memory region table*/
    VAR(Os_IsrType, OS_VAR) epilogueISR = Os_SCB.sysRunningIsrCat2Id;
    VAR(Os_ApplicationType, OS_VAR) epilogueapp = Os_SCB.sysRunningAppID;

    /*find pre ISR's PSW*/
    if (Os_SCB.sysAppId != epilogueapp)
    {
        Os_ArchSetMemProtSet(0x02U);
        Os_ArchSetIsrMemMap(epilogueISR, epilogueapp,
                (uint32)Os_AppCfg[epilogueapp].OsTrusted);
    }
    else
    {
        /*SYS_APP, as OS kernel, have all access rights*/
        Os_ArchSetMemProtSet(0x00U);
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* TRUE == CFG_MEMORY_PROTECTION_ENABLE */
/*=======[E N D   O F   F I L E]==============================================*/
