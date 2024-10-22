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
 **  DESCRIPTION : functions related to the Memory Protection Unit (MPU)       **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*=======[I N C L U D E S]===================================================*/
#include "Os_Internal.h"

/*=======[V E R S I O N  C H E C K]==========================================*/


/*=======[M A C R O S]=======================================================*/


/*=======[E X T E R N A L   D A T A]=========================================*/
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
/* Address space of kernel view. */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONST(Os_MemProtKnCfgType, OS_CONST) Os_MemProtKnAddrCfg =
{
    {
        /*Data*/
        /* PRQA S 0306 ++*/ /* MISRA Rule 11.4 */
        (uint8 *)OS_SRAM_START,
        (uint8 *)OS_SRAM_END,
        (uint8 *)PERIPHERAL_START,
        (uint8 *)PERIPHERAL_END,
        /*Code*/
        (uint8 *)OS_PFLASH_START,
        (uint8 *)OS_PFLASH_END,
        /* PRQA S 0306 --*/ /* MISRA Rule 11.4 */
    }
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CLONE_16
#include "Os_MemMap.h"
static VAR(Os_ApplicationType, OS_VAR)      Os_ArchMpCurAppId = INVALID_OSAPPLICATION;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_16
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
static FUNC(void, OS_CODE) Os_ArchMpuTaskSwitch(TaskType TaskId, ApplicationType HostAppId);
static FUNC(void, OS_CODE) Os_ArchMpuEnable(void);
static FUNC(void, OS_CODE) Os_ArchMpuDisable(void);
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*=======[E X C I P T I O N]==================================================*/
/* For memory protection. */
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Initialize memory protection related registers>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_MemProtTaskCat1Map and so on>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchInitKnMemMap(void)
{
    Os_ArchMpuDisable();
    /* 0:Background */
    OS_REG32(OS_MPU_RGDAAC0_ADDR) = (OS_MPU_AP_RX_NONE | OS_MPU_M23_AP_RW);

    /* 1:FlexRAM/PFLASH */
    OS_REG32(OS_MPU_RGDAAC1_ADDR) = (OS_MPU_AP_RX_RX | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD1_WORD0_ADDR) = OS_PFLASH_START;
    OS_REG32(OS_MPU_RGD1_WORD1_ADDR) = OS_PFLASH_END;
    OS_REG32(OS_MPU_RGD1_WORD3_ADDR) = OS_MPU_REGION_ENABLE;

    /* 2:FlexNVM */
    OS_REG32(OS_MPU_RGDAAC2_ADDR) = (OS_MPU_AP_RWX_RX | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD2_WORD0_ADDR) = (uint32)OS_FLEXNVM_START;
    OS_REG32(OS_MPU_RGD2_WORD1_ADDR) = (uint32)OS_FLEXNVM_END;
    OS_REG32(OS_MPU_RGD2_WORD3_ADDR) = OS_MPU_REGION_ENABLE;

    /* 3:FlexRAM */
    OS_REG32(OS_MPU_RGDAAC3_ADDR) = (OS_MPU_AP_RWX_RX | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD3_WORD0_ADDR) = (uint32)OS_FLEXRAM_START;
    OS_REG32(OS_MPU_RGD3_WORD1_ADDR) = (uint32)OS_FLEXRAM_END;
    OS_REG32(OS_MPU_RGD3_WORD3_ADDR) = OS_MPU_REGION_ENABLE;

    /* 2:SRAM */
    OS_REG32(OS_MPU_RGDAAC4_ADDR) = (OS_MPU_AP_RWX_NONE | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD4_WORD0_ADDR) = OS_SRAM_START;
    OS_REG32(OS_MPU_RGD4_WORD1_ADDR) = OS_SRAM_END;
    OS_REG32(OS_MPU_RGD4_WORD3_ADDR) = OS_MPU_REGION_ENABLE;

    /* 5:Peripheral */
    OS_REG32(OS_MPU_RGDAAC5_ADDR) = (OS_MPU_AP_RWX_NONE | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD5_WORD0_ADDR) = (uint32)PERIPHERAL_START;
    OS_REG32(OS_MPU_RGD5_WORD1_ADDR) = (uint32)PERIPHERAL_END;
    OS_REG32(OS_MPU_RGD5_WORD3_ADDR) = OS_MPU_REGION_ENABLE;

    /* 6:SEGMENT15 */
    OS_REG32(OS_MPU_RGDAAC6_ADDR) = (OS_MPU_AP_RWX_NONE | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD6_WORD0_ADDR) = (uint32)PERIPHERAL_START;
    OS_REG32(OS_MPU_RGD6_WORD1_ADDR) = (uint32)PERIPHERAL_END;
    OS_REG32(OS_MPU_RGD6_WORD3_ADDR) = OS_MPU_REGION_ENABLE;

    Os_ArchMpuEnable();
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Initialize memory protection related registers>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <StartOS>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchMemProtEnable(void)
{
    /* Reserved */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Memory protection unit enable>
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchMpTrustIsrThreadSwitch and so on>
 * REQ ID               <None>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchMpuEnable(void)
{
    /* Enable Global MPU,Clear Slave Port Error */
    OS_REG32(OS_MPU_CESR_ADDR) |= OS_MPU_VALID_BIT;
    OS_ARCH_DSYNC();
    OS_ARCH_ISYNC();
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Memory protection unit disable>
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchMpTrustIsrThreadSwitch and so on>
 * REQ ID               <None>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchMpuDisable(void)
{
    OS_ARCH_DSYNC();
    OS_ARCH_ISYNC();
    /* Disable Global MPU,Clear Slave Port Error */
    OS_REG32(OS_MPU_CESR_ADDR) &= (~OS_MPU_VALID_BIT);
    OS_ARCH_DSYNC();
    OS_ARCH_ISYNC();
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <In MPU Trust or NO Task Configuration, All permissions are
 *  					allowed in privilege mode ,but in user mode,Peripheral is restrict>
 * Service ID           <Os_ArchMpuTaskSwitch>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchMpuTaskSwitch(TaskType TaskId, ApplicationType HostAppId)
{
    Os_ArchMpuDisable();
    /* Task Data */
    OS_REG32(OS_MPU_RGDAAC7_ADDR) = (OS_MPU_AP_RWX_RWX | OS_MPU_M23_AP_RW);
    OS_REG32(OS_MPU_RGD7_WORD0_ADDR) = (uint32)Os_TaskDAddr[TaskId].Task_ADDR_START;
    OS_REG32(OS_MPU_RGD7_WORD1_ADDR) = (uint32)Os_TaskDAddr[TaskId].Task_ADDR_END;
    OS_REG32(OS_MPU_RGD7_WORD3_ADDR) = OS_MPU_REGION_ENABLE;
    if (Os_ArchMpCurAppId != HostAppId)
    {
        /* Application All Data */
        OS_REG32(OS_MPU_RGDAAC8_ADDR) = (OS_MPU_AP_RWX_RX | OS_MPU_M23_AP_RW);
        OS_REG32(OS_MPU_RGD8_WORD0_ADDR) = (uint32)Os_App_DAddr[HostAppId].APP_ADDR_START;
        OS_REG32(OS_MPU_RGD8_WORD1_ADDR) = ((uint32)Os_App_DAddr[HostAppId].APP_ADDR_END - 1);
        OS_REG32(OS_MPU_RGD8_WORD3_ADDR) = OS_MPU_REGION_ENABLE;
        /* Application All Code */
        if(Os_App_CAddr[HostAppId].APP_ADDR_END - Os_App_CAddr[HostAppId].APP_ADDR_START > 0)
        {
            OS_REG32(OS_MPU_RGDAAC9_ADDR) = (OS_MPU_AP_RWX_RWX | OS_MPU_M23_AP_RW);
            OS_REG32(OS_MPU_RGD9_WORD0_ADDR) = (uint32)Os_App_CAddr[HostAppId].APP_ADDR_START;
            OS_REG32(OS_MPU_RGD9_WORD1_ADDR) = ((uint32)Os_App_CAddr[HostAppId].APP_ADDR_END - 1);
            OS_REG32(OS_MPU_RGD9_WORD3_ADDR) = OS_MPU_REGION_ENABLE;
        }
        else
        {
        	OS_REG32(OS_MPU_RGDAAC9_ADDR) = (OS_MPU_AP_RWX_NONE | OS_MPU_M23_AP_RW);
        }
        /* Application Private Data */
        if(Os_AppPriDataAddr[HostAppId].APP_ADDR_END - Os_AppPriDataAddr[HostAppId].APP_ADDR_START > 0)
        {
            OS_REG32(OS_MPU_RGDAAC10_ADDR) = (OS_MPU_AP_RWX_RWX | OS_MPU_M23_AP_RW);
            OS_REG32(OS_MPU_RGD10_WORD0_ADDR) = (uint32)Os_AppPriDataAddr[HostAppId].APP_ADDR_START;
            OS_REG32(OS_MPU_RGD10_WORD1_ADDR) = ((uint32)Os_AppPriDataAddr[HostAppId].APP_ADDR_END - 1);
            OS_REG32(OS_MPU_RGD10_WORD3_ADDR) = OS_MPU_REGION_ENABLE;
        }
        else
        {
        	OS_REG32(OS_MPU_RGDAAC10_ADDR) = (OS_MPU_AP_RWX_NONE | OS_MPU_M23_AP_RW);
        }
    }
    Os_ArchMpCurAppId = HostAppId;
    Os_ArchMpuEnable();
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
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_SwitchTask>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_MemProtTaskCat1Map(void)
{
    TaskType TaskId = Os_GetObjLocalId(Os_SCB.sysRunningTaskID); /* PRQA S 3469 */ /* MISRA Dir 4.9 */ /* ARCH_MPU_DATA_DEFINE_001 */
    ApplicationType HostAppId = Os_SCB.sysRunningAppID;

    if (Os_SCB.sysAppId == Os_SCB.sysRunningAppID)
    {
        /*SYS_APP, as OS kernel, have all access rights*/
        Os_ArchMpDefaultConfigSwitch();
    }
    else if ((TRUE == Os_AppCfg[HostAppId].OsTrusted) && (TRUE != Os_AppCfg[HostAppId].OsTrustedAppWithProtection))
    {
        /*Trusted APP and no memory protection*/
        Os_ArchMpDefaultConfigSwitch();
    }
    else
    {
        /*Non trusted apps or trusted apps protected by MPU*/
        Os_ArchMpuTaskSwitch(TaskId, HostAppId);
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
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_SwitchTask>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_MemProtTaskCat2Map(void)
{
    TaskType TaskId = Os_GetObjLocalId(Os_SCB.sysRunningTaskID); /* PRQA S 3469 */ /* MISRA Dir 4.9 */
    ApplicationType HostAppId = Os_SCB.sysRunningAppID;

    if (Os_SCB.sysAppId == Os_SCB.sysRunningAppID)
    {
        /*SYS_APP, as OS kernel, have all access rights*/
        Os_ArchMpDefaultConfigSwitch();
    }
    else if ((TRUE == Os_AppCfg[HostAppId].OsTrusted) && (TRUE != Os_AppCfg[HostAppId].OsTrustedAppWithProtection))
    {
        /*Trusted APP and no memory protection*/
        Os_ArchMpDefaultConfigSwitch();
    }
    else
    {
        /*Non trusted apps or trusted apps protected by MPU*/
        Os_ArchMpuTaskSwitch(TaskId, HostAppId);
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
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_EnterISR2><Os_ExitISR2>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_MemProtIsrMap(void)
{
    /* This Platform not support. */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Initialize the MPU configuration and calculate the
 *  					configuration table for each OsApplication>
 * Service ID           <Os_ArchMpuRegionInit>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE)Os_ArchMpuRegionInit(void)
{
    /* NO Need */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <In MPU default Configuration, All permissions are
 *  					allowed in privilege mode and User mode>
 * Service ID           <Os_ArchMpDefaultConfigSwitch>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchMpDefaultConfigSwitch(void)
{
    /* Do Nothing */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Memory initialization. Copy data from ROM to RAM.>
 * Service ID           <OsMemoryInit>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchAppMemoryInit(void)
{
	/* To be continue */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* (TRUE == CFG_MEMORY_PROTECTION_ENABLE) */ /* PRQA S 2053 */ /* MISRA Rule 18.8 */ 
