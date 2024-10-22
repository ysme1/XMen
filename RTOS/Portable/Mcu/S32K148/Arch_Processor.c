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
 **  FILENAME    : Arch_Processor.c                                            **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Processor Request Managment                                 **
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
#define OS_START_SEC_VAR_CLEARED_CLONE_32
#include "Os_MemMap.h"
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */ /* ARCH_PROCESSOR_COMPILER_001 */
P2VAR(uint32, AUTOMATIC, OS_VAR)            Os_ArchMasterSp_New    = NULL_PTR;
P2VAR(uint32, AUTOMATIC, OS_VAR)            Os_ArchTopStkPtr       = NULL_PTR;
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
VAR(uint32, OS_VAR)                         Os_ArchMasterSp_ARRAY[20] = {0U};
VAR(uint32, OS_VAR)                         Os_IsrIPSR[CFG_ISR_MAX_CORE0] = {0U};
VAR(uint32, OS_VAR)                         Os_IsrTempIPSR       = 0U;
VAR(volatile uint32, OS_VAR)                Os_ArchTempSp        = 0U;

VAR(volatile uint32, OS_VAR)                Os_ArchControl      = 0U;
VAR(uint32, OS_VAR)                         Os_ArchIntNestedSaved;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_32
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CLONE_PTR
#include "Os_MemMap.h"
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */ /* ARCH_PROCESSOR_COMPILER_001 */
P2VAR(Os_TaskCBExtType, AUTOMATIC, OS_VAR)   Os_TaskCBExt          = NULL_PTR;
P2VAR(uint32, AUTOMATIC, OS_VAR)             Os_IsrNestPcxStack    = NULL_PTR;
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
P2CONST(OS_ISR_ADDR, AUTOMATIC, OS_VAR)      Os_IsrDAddr            = NULL_PTR;
P2CONST(OS_TASK_ADDR, AUTOMATIC, OS_VAR)     Os_TaskDAddr           = NULL_PTR;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_PTR
#include "Os_MemMap.h"
/*=======[I N T E R N A L   D A T A]=========================================*/
#if (TRUE == CFG_CORE0_AUTOSAROS_ENABLE)
#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
VAR(Os_TaskCBExtType, OS_VAR) Os_TaskCBExtCore0[CFG_TASK_MAX_CORE0] = {0u};
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
#endif /* #if (TRUE == CFG_CORE0_AUTOSAROS_ENABLE) */

#if (TRUE == CFG_CORE1_AUTOSAROS_ENABLE)
#define OS_START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#include "Os_MemMap.h"
VAR(Os_TaskCBExtType, OS_VAR) Os_TaskCBExtCore1[CFG_TASK_MAX_CORE1] = {0u};
#define OS_STOP_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#include "Os_MemMap.h"
#endif /* #if (TRUE == CFG_CORE1_AUTOSAROS_ENABLE) */

#if (CFG_ISR_MAX > 0U)
#define OS_START_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#include "Os_MemMap.h"
VAR(Os_CallLevelType, OS_VAR)               Os_SaveLevelISR1 = OS_LEVEL_ISR1;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#include "Os_MemMap.h"
#endif /* #if (CFG_ISR_MAX > 0U) */ /* PRQA S 2053 */ /* MISRA Rule 18.8 */

#if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
#define OS_START_SEC_VAR_CLEARED_CLONE_32
#include "Os_MemMap.h"
VAR(volatile uint32, OS_VAR)                Os_TprotTerminateIsr = FALSE;
VAR(volatile uint32, OS_VAR)                Os_TprotTerminateTask = FALSE;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_32
#include "Os_MemMap.h"
#endif
/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]=======*/

#if (CFG_OSAPPLICATION_MAX > 0 && CFG_ISR_MAX > 0 && TRUE == CFG_INT_NEST_ENABLE)
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
static FUNC(StatusType, OS_CODE) Os_ArchTerminateOneNestIsr(Os_IsrType OsIsrID);
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
static FUNC(Os_ArchMsrType, OS_CODE) Os_ArchGetBasePriReg(void);
static FUNC(void, OS_CODE) Os_ArchSetBasePriReg (register Os_ArchMsrType primask_val);
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]===================*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
FUNC(void, OS_CODE) Os_MultiCoreInitProcessor(void)
{
    switch (Os_SCB.sysCore)
    {
#if (TRUE == CFG_CORE0_AUTOSAROS_ENABLE)
    case 0:
        Os_TaskCBExt = Os_TaskCBExtCore0;
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
        Os_IsrDAddr = Os_Isr_DAddr_Core0;
        Os_TaskDAddr = Os_Task_DAddr_Core0;
#endif
        break;
#endif
#if (TRUE == CFG_CORE1_AUTOSAROS_ENABLE)
    case 1:
        Os_TaskCBExt = Os_TaskCBExtCore1;
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
        Os_IsrDAddr = Os_Isr_DAddr_Core1;
        Os_TaskDAddr = Os_Task_DAddr_Core1;
#endif
        break;
#endif
        /*add comments to pass QAC.*/
    default:
        /* Nothing to do. */
        break;
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Get PRIMASK register>
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <Os_IPLType>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchSuspendInt and so on>
 * REQ ID               <None>
 */
/******************************************************************************/
static FUNC(Os_IPLType, OS_CODE) Os_ArchGetMsr(void)/* PRQA S 3008 */ /* MISRA Rule 4.3 */
{
    register Os_IPLType primask_reg;

    ASM (" mrs %0, primask " : "=r" (primask_reg));

    return primask_reg;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                 <Set PRIMASK register>
 *
 * Service ID            <None>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * param-primask_val[in] <The value of primask register>
 * param-Name[out]       <None>
 * param-Name[in/out]    <None>
 * return                <None>
 * PreCondition          <None>
 * CallByAPI             <Os_ArchSuspendInt and so on>
 * REQ ID                <None>
 */
/******************************************************************************/
static  FUNC(void, OS_CODE) Os_ArchSetMsr (register Os_IPLType primask_val)/* PRQA S 3006 */ /* MISRA Rule 4.3 */
{
    ASM (" msr primask, %0 " : : "r" (primask_val));

    (void)primask_val;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Get PRIMASK register>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <ipl>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchSuspendInt and so on>
 */
/******************************************************************************/
static FUNC(Os_ArchMsrType, OS_CODE) Os_ArchGetBasePriReg(void)
{
    register uint32 basepri;

    ASM(" mrs %0, basepri " : "=r" (basepri));

    return (Os_ArchMsrType)basepri;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Set PRIMASK register>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <ipl>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <Os_ArchSuspendInt and so on>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) Os_ArchSetBasePriReg (register Os_ArchMsrType basepri)/* PRQA S 3206 */ /* MISRA Rule 2.7 */ /* ARCH_PROCESSOR_C_INLINE_ASM_005 */
{
    ASM (" msr basepri, %0 " : : "r" (basepri));
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Ipl greater than 0, disable interrupt otherwise enable interrupt>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <ipl>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <ResumeOSInterrupts and so on>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchSetIpl(Os_IPLType ipl, Os_IsrDescriptionType isrdesc)
{
    /*add comments to pass QAC.*/
    (void)isrdesc;
    /* Disable interrupt prio - 1,CAN open the max OSinterrupt self*/
    register Os_IPLType converted_prio = OS_INT_PRIO_LOG_TO_PHY(ipl);

    ASM ("msr basepri, %0" : : "r" (converted_prio));
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Get current IPL>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <0>
 * PreCondition         <None>
 * CallByAPI            <SuspendOSInterrupts and so on>
 */
/******************************************************************************/
FUNC(Os_IPLType, OS_CODE) Os_ArchGetIpl(void)
{
    register Os_IPLType result;

    ASM ("MRS %0, basepri_max" : "=r" (result));

    result = OS_INT_PRIO_PHY_TO_LOG(result);

    return (result);
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Save ccr to variable msr and disable maskable interrupt>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <SuspendAllInterrupts>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchSuspendInt(P2VAR(Os_ArchMsrType, AUTOMATIC, OS_VAR) msr) /* PRQA S 3432 */ /* MISRA Rule 20.7 */ /* ARCH_PROCESSOR_COMPILER_001 */ 
{
	uint32 basepri;
	basepri = Os_ArchGetBasePriReg();

	Os_ArchSetBasePriReg(OS_INT_PRIO_LOG_TO_PHY(OS_ISR1_PRIO_MAX));
    *msr  = (Os_ArchMsrType)basepri;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <transfer variable msr back to ccr>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <ResumeAllInterrupts>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchRestoreInt(Os_ArchMsrType msr)
{
    OS_ARCH_DSYNC();

    Os_ArchSetBasePriReg(msr);
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"


#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Save ccr to variable msr and disable maskable interrupt>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <SuspendAllInterrupts>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchSuspendAllInt(P2VAR(Os_ArchMsrType, AUTOMATIC, OS_VAR) msr) /* PRQA S 3432 */ /* MISRA Rule 20.7 */ /* ARCH_PROCESSOR_COMPILER_001 */
{
    *msr = Os_ArchGetMsr();

    Os_ArchSetMsr((Os_IPLType )(*msr)|OS_MSR_PRIMASK_BIT0);
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <transfer variable msr back to ccr>
 *
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <ResumeAllInterrupts>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchRestoreAllInt(Os_ArchMsrType msr)
{
    OS_ARCH_DSYNC();

    Os_ArchSetMsr((Os_IPLType )msr);
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"




#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <First entry task>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <Os_PreTask>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_ArchFirstEnterTask(void)
{
    /* PRQA S 0306,3469 ++*/ /* MISRA Rule 11.4 */ /* ARCH_PROCESSOR_MULTI_VIO_006 */
    Os_ArchTopStkPtr = (uint32 *)OS_ARCH_STACK_ALIGN((uint32)Os_SCB.sysRunningTCB->taskTop); 
    /* PRQA S 0306,3469 --*/ /* MISRA Rule 11.4 */
    /*registers stacked as if auto-saved on exception.
     * The follow registers will automatic restore when exiting an exception.
     * --xPSR, PC, LR, R12, R3, R2, R1, R0--*/
    /* PRQA S 3440,3387 ++*/ /* MISRA Rule 13.3 */ /* ARCH_PROCESSOR_TYPE_CAST_002 */
    *(--Os_ArchTopStkPtr) = 0x01000000U;              /* xPSR *//* PRQA S 0305 */ /* MISRA Rule 11.1 */ /* ARCH_PROCESSOR_TYPE_CAST_003 */
    *(--Os_ArchTopStkPtr) = (uint32)Os_TaskCfg[Os_SCB.sysRunningTaskID].osTaskEntry - 1;/* PRQA S 0305 */ /* MISRA Rule 11.1 */
    *(--Os_ArchTopStkPtr) = (uint32)Os_TaskErrBack + 2;   /* R14(LR) */ /* PRQA S 0305 */ /* MISRA Rule 11.1 */ /* ARCH_PROCESSOR_TYPE_CAST_003 */

    *(--Os_ArchTopStkPtr) = 12U;                       /* R12 */
    *(--Os_ArchTopStkPtr) = 3U;                       /* R3 */
    *(--Os_ArchTopStkPtr) = 2U;                       /* R2 */
    *(--Os_ArchTopStkPtr) = 1U;                       /* R1 */
    *(--Os_ArchTopStkPtr) = 0U;                       /* R0 */
    *(--Os_ArchTopStkPtr) = 0xFFFFFFFDUL;             /* R14:EXEC_RETURN; */
    /*remaining registers saved on process stack*/
    *(--Os_ArchTopStkPtr) = 11U;                       /* R11 */
    *(--Os_ArchTopStkPtr) = 10U;                       /* R10 */
    *(--Os_ArchTopStkPtr) = 9U;                       /* R9 */
    *(--Os_ArchTopStkPtr) = 8U;                       /* R8 */
    *(--Os_ArchTopStkPtr) = 7U;                       /* R7 */
    *(--Os_ArchTopStkPtr) = 6U;                       /* R6 */
    *(--Os_ArchTopStkPtr) = 5U;                       /* R5 */
    *(--Os_ArchTopStkPtr) = 4U;                       /* R4 */
    /* PRQA S 3440 --*/ /* MISRA Rule 13.3 */
    /*CONTROL register*/
    #if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
    if((TRUE == Os_AppCfg[Os_SCB.sysRunningAppID].OsTrusted) &&
            (TRUE != Os_AppCfg[Os_SCB.sysRunningAppID].OsTrustedAppWithProtection))
    {
        *--Os_ArchTopStkPtr = 0x00000000;
    }
    else
    {
        *--Os_ArchTopStkPtr = 0x00000001;
    }
    #else
    *--Os_ArchTopStkPtr = 0x00000000u;
    #endif
    
    
    Os_TaskCBExt[Os_SCB.sysRunningTaskID] = (uint32)Os_ArchTopStkPtr; /* PRQA S 0306 */ /* MISRA Rule 11.4 */ /* ARCH_PROCESSOR_TYPE_CAST_006 */
    
    /* PRQA S 0303 ++*/ /* MISRA Rule 11.4 */ /* ARCH_PROCESSOR_TYPE_CAST_006 */
    OS_INTERRUPT_SYS_SET_PRIO(OS_SRC_PendSV_ADDR, OS_INT_PRIO_LOG_TO_PHY(OS_NVIC_PRIO_MIN));
    /* PRQA S 0303 --*/ /* MISRA Rule 11.4 */ 
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Os_ArchDispatch>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_ArchDispatch(void)
{
    /* Call PendSV to switch task */
    ASM(
    " cpsid i               \n"
    " ldr r0, =0xE000ED04   \n"
    " ldr r1, =0x10000000   \n"
    " str r1, [r0]          \n"
    " dsb                   \n"
    " cpsie	i				\n"
    );
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Os_ArchDispatch_ISR>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_ArchDispatch_ISR(void)
{
    ASM
    (
    " cpsid i               \n"
    " ldr r0, =0xE000ED04   \n"
    " ldr r1, =0x10000000   \n"
    " str r1, [r0]          \n"
    " dsb                   \n"
    );
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Os_ArchSyscall>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_ArchSyscall(void)
{

	ASM
    (
        " svc 0                                \n"
        " nop                                  \n"
    );
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Os_ArchStartScheduler>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <ShutdownOS>
 */
/*****************************************************************************/
FUNC(void, OS_CODE) Os_ArchStartScheduler(void)
{
    /*notes: the code of start system timer must be lightweight, otherwise the
     * previous step 'synchronization' will not make sense*/
    Os_StartSysTimer();
    /*Run the scheduler*/
    Os_Dispatch(); /* System call */ /* PRQA S 3469 */ /* MISRA Rule 4.9 */
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Open FPU auto store function>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <non-reentrant>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <System Init>
 */
/******************************************************************************/
static FUNC(void, OS_CODE) OS_FPUAutoStoreFunctionInit(void)
{
     ASM("LDR.W R0, =0xE000EF34");
     ASM("LDR R1, [R0]");
     ASM("ORR R1, R1, #0xC0000000");
     ASM("STR R1, [R0]");/*  wait for store to complete  */
     ASM("DSB");
     ASM("ISB");
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Os_ArchInitCPU>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <StartOS>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_ArchInitCPU(void)
{
    
	OS_REG32(OS_SCB_CCR_ADDRESS) |=0x01U; /* PRQA S 0306 */ /* MISRA Rule 11.4 */ /* ARCH_PROCESSOR_TYPE_CAST_006 */
    OS_FPUAutoStoreFunctionInit();
    Os_InterruptInit();

    #if(TRUE == CFG_MEMORY_PROTECTION_ENABLE)
	HardFault_Flag = 0;
	Os_ArchMpuRegionInit();
    #endif

    #if (TRUE == CFG_SYSTEM_TIMER_ENABLE)
    Os_ArchInitSystemTimer();
    #endif /* #if (TRUE == CFG_SYSTEM_TIMER_ENABLE) */ /* PRQA S 2053 */ /* MISRA Rule 18.8 */ 

    #if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
    Os_ArchInitTimingProtTimer();
    #endif
    Os_ArchInitIntPrio();
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
#if (CFG_ISR_MAX > 0)
/*****************************************************************************/
/*
 * Brief                <Disable all interrupts in os_app during TerminateApplication.>
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
FUNC(void, OS_CODE) Os_ArchDisableIntInApp(P2CONST(Os_ApplicationCfgType, AUTOMATIC, OS_VAR) posCurAppCfg)
{   
    uint16     i;
    uint16     osIsrRefCnt;
    Os_IsrType osIsrId;
    uint32     osIsrRegVal;
    
    osIsrRefCnt = posCurAppCfg->OsAppIsrRefCnt;

    for (i = 0; i < osIsrRefCnt; i++)
    {
        osIsrId = Os_GetObjLocalId(posCurAppCfg->OsAppObjectRef[OBJECT_ISR][i]); /* PRQA S 3469 */ /* MISRA Rule 4.9 */

        osIsrRegVal  = Os_IsrCfg[osIsrId].OsIsrSrc;
        /* PRQA S 0303 ++*/ /* MISRA Rule 11.4 */ /* ARCH_PROCESSOR_TYPE_CAST_006 */
        OS_INTERRUPT_DISABLE(osIsrRegVal);  
        OS_INTERRUPT_CLEAR_PENDING(osIsrRegVal); /* PRQA S 3469 */ /* MISRA Rule 4.9 */
        /* PRQA S 0303 --*/ /* MISRA Rule 11.4 */
    }
}


#if (TRUE == CFG_INT_NEST_ENABLE)
static FUNC(StatusType, OS_CODE) Os_ArchTerminateOneNestIsr(Os_IsrType OsIsrID)
{
    uint8 i;
    StatusType Status = E_OK;
    for (i = 0; i < Os_IntNestISR2; i++)
    {
        /* find out the Isr nested position and reclaim its context saving area */
        if (OsIsrID == Os_SCB.sysIsrNestQueue[i])
        {
            Os_IsrTempIPSR = Os_IsrIPSR[i];
            TerminateISR();
            break;
        }
    }

    /* Not find out the Isr Id in the IsrStack from the SCB,
        * not include outermost_isr. */
    if (i >= Os_IntNestISR2)
    {
        Status = E_NOT_OK;
    }

    /* Moving the following nested ISR2s to shift one position left */
    while (i < (Os_IntNestISR2 - 1U))
    {
        Os_SCB.sysIsrNestQueue[i] = Os_SCB.sysIsrNestQueue[i + 1U];

        if (i < (Os_IntNestISR2 - 2U))
        {
            Os_ArchMasterSp_ARRAY[i + 1U] = Os_ArchMasterSp_ARRAY[i + 2U];
        }

        i++;
    }

    return Status;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <Terminate Isr2 platform process in TerminateApplication>
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
FUNC(void, OS_CODE) Os_ArchAppTerminateIsrProc(Os_IsrType OsIsrID)
{
    uint32 ulRet = E_OK;

    /* Isr_nest process. */
    /* Just find out the nested corresponding ISR2s(excluding the running one) */
    if ((OsIsrID != Os_SCB.sysRunningIsrCat2Id) && (Os_IntNestISR2 > 0U))
    {
        /* Terminate one isr */
        ulRet = Os_ArchTerminateOneNestIsr(OsIsrID);

        if (E_OK == ulRet)
        {
            Os_IntNestISR2--;

            if (Os_SCB.sysDispatchLocker > 0U)
            {
                Os_SCB.sysDispatchLocker--;
            }
        }
    }

    return;
}
#endif   /* #if (TRUE == CFG_INT_NEST_ENABLE) */ /* PRQA S 2053 */ /* MISRA Rule 18.8 */ 
#endif   /* #if (CFG_ISR_MAX > 0) */ /* PRQA S 2053 */ /* MISRA Rule 18.8 */ 
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/*****************************************************************************/
/*
 * Brief                <TerminateTask arch_process in TerminateApplication.>
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
FUNC(void, OS_CODE) Os_ArchAppTerminateTaskProc(Os_TaskType OsTaskID)
{
    if ((OS_LEVEL_TASK == Os_SCB.sysOsLevel) ||
        ((OS_LEVEL_ERRORHOOK_APP == Os_SCB.sysOsLevel) && (TRUE != Os_SCB.sysInIsrCat2)))
    {
        /* If TerminateApplication is called by task or isr2 or app_error_hook,
         * the csa of running task is reclaimed in the dispatcher at the end of TerminateApplication. */
        if (OsTaskID != Os_SCB.sysRunningTaskID)
        {
            /* nothing to do. */
        }
    }
    else
    {
       /* nothing to do. */
    }

    return;
}

#endif /* #if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC)) */ /* PRQA S 2053 */ /* MISRA Rule 18.8 */ 

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Get the Core Mode>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-core[in]       <selects the core which to get mode>
 * Return               <Os_CoreModeType,the core mode>
 * PreCondition         <None>
 * CallByAPI            <Os_SetCoreMode>
 */
/******************************************************************************/
FUNC(Os_CoreModeType, OS_CODE) Os_GetCoreMode(Os_CoreIdType coreId)
{
    UNUSED_PARAMETER(coreId);
    Os_CoreModeType    coreMode = OS_CORE_MODE_UNKNOWN;
    return coreMode;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Set the Core Mode>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-core[in]       <Selects the core which mode is set>
 * Return               <boolean,the result of setting>
 * PreCondition         <None>
 * CallByAPI            <ControlIdle>
 */
/******************************************************************************/
FUNC(boolean, OS_CODE) Os_SetCoreMode(Os_CoreIdType coreId,  Os_CoreModeType coreMode)
{
    boolean returnCode = TRUE;
    UNUSED_PARAMETER(coreId);
    UNUSED_PARAMETER(coreMode);
    return returnCode;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Set the CPU Mode>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-core[in]       <Selects the core which mode is set>
 * Return               <Os_CPUModeType,the CPU mode>
 * PreCondition         <None>
 * CallByAPI            <ControlIdle>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_SetCpuMode(Os_CPUModeType mode)
{
    if (OS_CPUMODE_SUPERVISOR == mode)
    {
        ASM
        (
            "mrs r0,control               \n"
            "and r0,r0,#0xFFFFFFFE        \n"
            "msr control, r0              \n"
        );
    }
    else
    {
        ASM
        (
            "mrs r0,control               \n"
            "orr r0,r0,#0x01              \n"
            "msr control, r0              \n"
        );
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Set the Control register>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-core[in]       <None>
 * Return               <Control register value>
 * PreCondition         <None>
 * CallByAPI            <ControlIdle>
 */
/******************************************************************************/
FUNC(uint32, OS_CODE) getControlValue(void)
{
    register uint32 result;

    ASM ("MRS %0, control" : "=r" (result));

    return result;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Set the Control register>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-core[in]       <None>
 * Return               <Control register value>
 * PreCondition         <None>
 * CallByAPI            <ControlIdle>
 */
/******************************************************************************/
FUNC(uint32, OS_CODE) getxPSRValue(void)
{
    register uint32 result;

    ASM ("MRS %0, xpsr" : "=r" (result));

    return result;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"




#if (TRUE == CFG_INT_NEST_ENABLE)
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                < Get IPSR Register >
 * Service ID           <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * param-Name[in]       <None>
 * param-Name[out]      <None>
 * param-Name[in/out]   <None>
 * return               <uint32>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(uint32, OS_CODE) Os_GetIsrIPSR(void)/* PRQA S 3008 */ /* MISRA Rule 4.3 *//*ARCH_PROCESSOR_C_INLINE_ASM_004*/
{
    uint32 result;

    ASM ("MRS %0, ipsr" : "=r" (result) );
    
    return(result);
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <Get the Thread Mode>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * param-Name[in]       <None>
 * Param-Name[in/out]   <None>
 * Param-Name[out]      <None>
 * Return               <Os_ThreadModeType>
 * PreCondition         <None>
 * CallByAPI            <OS_CHANGCPUMODE>
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(Os_ThreadModeType, OS_CODE) Os_GetThreadMode(void)
{
    Os_ThreadModeType coreMode = OS_THREAD_MODE_SUPERVISOR;
    uint32 isUser = (getControlValue() & 0x00000001U);
    uint32 irqN = (getxPSRValue() & 0x000001FFU);
    coreMode = ((isUser == 0U)||(irqN != 0))
               ? OS_THREAD_MODE_SUPERVISOR
               : OS_THREAD_MODE_USER;

    return coreMode;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/******************************************************************************/
/*
 * Brief                <idle task>
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <the priority value>
 * PreCondition         <None>
 * CallByAPI            <GetResource and so on >
 * REQ ID               <None>
 */
/******************************************************************************/
FUNC(void, OS_CODE) Os_TaskEntry_IdleCore0(void)
{
    while (1)
    {
        IdleHook_Core0();
    }
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/

