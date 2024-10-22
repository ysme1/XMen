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
 **  FILENAME    : Arch_Irq.c                                                  **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Deal with operations related to processor interrupts        **
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

/*=======[I N T E R N A L   D A T A]=========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]=======*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]===================*/

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Installation interrupted>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchInitCPU>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_InterruptInstall /* PRQA S 3006 */ /* MISRA Rule 4.3 */ /* ARCH_IRQ_C_INLINE_ASM_001 */
(
    uint8 id,
    uint8 prio,
    uint32 srcType,
    Os_isrhnd isrProc
)
{
	uint32 * pVectorRam = (uint32 *)(OS_REG32(OS_NVIC_VTOR_ADDRESS)) ; /* PRQA S 0306 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_003 */
    (void)srcType;
    if (id >= 16u)
    {
        OS_INTERRUPT_INSTALL(id, prio, srcType); /* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
    }
    else
    {
        OS_INTERRUPT_SYS_INSTALL(id, prio, srcType); /* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
    }
    

    /* Save the former handler pointer */
    if (isrProc != NULL_PTR)
    {
        /* Set handler into vector table */
    	pVectorRam[((uint32)id)] = (uint32)isrProc;/* PRQA S 0305 */ /* MISRA Rule 11.1 */ 
    }
    ASM("dsb");
    ASM("isb");
    /* Invalidate ICache */
    OS_REG32(OS_SCB_ICIALLU_ADDRESS) = 0UL; /* PRQA S 0306 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_003 */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Installation interrupt by default>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchInitCPU>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_InterruptInit(void)
{
    /* reference link file */
	uint32* pVector = (uint32*)(OS_REG32(OS_NVIC_VTOR_ADDRESS));
    uint32 index;

    pVector[OS_SRC_PendSV_ADDR] = (uint32)PendSV_Handler;
    pVector[OS_SRC_HardFault_ADDR] = (uint32)HardFault_Handler;
    OS_INTERRUPT_SYS_SET_PRIO(OS_SRC_SVCall_ADDR, OS_INT_PRIO_LOG_TO_PHY(OS_NVIC_PRIO_MAX));/* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
    OS_INTERRUPT_SYS_SET_PRIO(OS_SRC_PendSV_ADDR, OS_INT_PRIO_LOG_TO_PHY(OS_NVIC_PRIO_MAX));/* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */

    for (index = 16; index < OS_NVIC_NUM; index++)
    {
        OS_INTERRUPT_DISABLE(index);/* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
        OS_INTERRUPT_CLEAR_PENDING(index);/* PRQA S 0303,3469,3432 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_MULTI_VIO_005 */
        OS_INTERRUPT_SET_PRIO(index, OS_INT_PRIO_LOG_TO_PHY(OS_NVIC_PRIO_MIN)); /* Set interrupt priority to MIN */ /* PRQA S 0303 */ /* MISRA Rule 11.4 */
        pVector[index] = (uint32)Os_IntHandler;
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Disable the given interrupt source>
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-vIsrSrc[in]    <Interrupt source>
 * param-vIsrSrcType[in]<Type of Interrupt source>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <DisableInterruptSource>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_DisableInterruptSource(uint32 vIsrSrc, uint32 vIsrSrcType)
{
    UNUSED_PARAMETER(vIsrSrcType); 
    OS_INTERRUPT_DISABLE(vIsrSrc); /* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Clear the pending status of the given interrupt>
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-vIsrSrc[in]    <Interrupt source>
 * param-vIsrSrcType[in]<Type of Interrupt source>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * CallByAPI            <EnableInterruptSource><ClearPendingInterrupt>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ClearPendingInterrupt(uint32 vIsrSrc, uint32 vIsrSrcType)
{
    UNUSED_PARAMETER(vIsrSrcType);
    OS_INTERRUPT_CLEAR_PENDING(vIsrSrc); /* PRQA S 0303,3469,3432 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_MULTI_VIO_005 */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Get the status of the given interrupt.>
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Reentrant>
 * param[in]            <srcAddr,prio,srcType,isrProc>
 * param[out]           <None>
 * param[in/out]        <None>
 * return               <None>
 * CallByAPI            <None>
 * REQ ID               <>
 */
/******************************************************************************/
FUNC(Os_IsrStateType, OS_CODE) Os_GetIsrSourceState(uint32 vIsrSrc, uint32 vIsrSrcType)
{
    UNUSED_PARAMETER(vIsrSrcType);
    Os_IsrStateType isrSourceState = OS_ISR_DISABLED;
    if(1U == OS_INTERRUPT_CHECK_STATUS(vIsrSrc))/* PRQA S 0303,3469,3432 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_MULTI_VIO_005 */
    {
        isrSourceState = OS_ISR_ENABLED;
    }
    return isrSourceState;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Enable the given interrupt source vIsrSrc.>
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Reentrant>
 * param[in]            <srcAddr,prio,srcType,isrProc>
 * param[out]           <None>
 * param[in/out]        <None>
 * return               <None>
 * CallByAPI            <None>
 * REQ ID               <>
 */
FUNC(void, OS_CODE) Os_EnableInterruptSource(uint32 vIsrSrc, uint32 vIsrSrcType)
{
    UNUSED_PARAMETER(vIsrSrcType);
    OS_INTERRUPT_ENABLE(vIsrSrc);/* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Scheduling tasks in PendSV interrupts>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_TaskSchedule(void)
{
    #if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
    sint32 SysIrqn = (sint32)OS_SRC_PendSV_ADDR;
    #endif

    if(NULL_PTR != Os_SCB.sysRunningTCB)
    {
        Os_TaskCBExt[Os_SCB.sysRunningTaskID] = Os_ArchTempSp;
    }
    #if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
    if (TRUE == Os_TprotTerminateTask)
    {
    	OS_INTERRUPT_SYS_SET_PRIO(SysIrqn, OS_INT_PRIO_LOG_TO_PHY(OS_NVIC_PRIO_MAX));/* PRQA S 0303 */ /* MISRA Rule 11.4 */ /* ARCH_IRQ_VTYPE_CAST_002 */
        Os_TprotTerminateTask = FALSE;
    }
    #endif
    Os_SwitchTask();
    Os_ArchTempSp = Os_TaskCBExt[Os_SCB.sysRunningTaskID];
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
/*=======[E N D   O F   F I L E]==============================================*/
