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
 **  FILENAME    :  Arch_Processor.h                                           **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      :  i-soft-os                                                  **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef ARCH_PROCESSOR_H
#define ARCH_PROCESSOR_H

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define OS_PROCESSOR_H_VENDOR_ID        62
#define OS_PROCESSOR_H_MODULE_ID        1
#define OS_PROCESSOR_H_AR_MAJOR_VERSION 4
#define OS_PROCESSOR_H_AR_MINOR_VERSION 2
#define OS_PROCESSOR_H_AR_PATCH_VERSION 2
#define OS_PROCESSOR_H_SW_MAJOR_VERSION 1
#define OS_PROCESSOR_H_SW_MINOR_VERSION 0
#define OS_PROCESSOR_H_SW_PATCH_VERSION 0
#define OS_PROCESSOR_H_VENDOR_API_INFIX 0

/*=======[I N C L U D E S]====================================================*/
#include "Arch_Define.h"
#include "Arch_Mpu.h"
#include "Arch_Irq.h"

/*-----------------------------S32K3XX Register-------------------------------*/
/* SysTick Timer */
#define OS_SYSTICK_ENABLE_BIT               (1u << 0u)
#define OS_SYSTICK_INT_BIT                  (1u << 1u)
#define OS_SYSTICK_CLK_BIT                  (1u << 2u)

#define OS_SYSTICK_BASE_ADDRESS             (0xE000E010U)
#define OS_SYSTICK_CTRL_REG                 OS_REG32(OS_SYSTICK_BASE_ADDRESS)
#define OS_SYSTICK_RELOAD_REG               OS_REG32(OS_SYSTICK_BASE_ADDRESS + 0x4u)
#define OS_SYSTICK_COUNTER_REG              OS_REG32(OS_SYSTICK_BASE_ADDRESS + 0x8u)
#define OS_SYSTICK_CHECK_REG                OS_REG32(OS_SYSTICK_BASE_ADDRESS + 0xCu)

#define OS_NVIC_VTOR_ADDRESS                (0xE000ED08u)
#define OS_SCB_ICIALLU_ADDRESS              (0xE000EF50u)
#define OS_SCB_CCR_ADDRESS                  (0xE000ED14u)      /* Configuration and Control Register */
#define OS_SCB_SHCSR_ADDRESS                (0xE000ED24u)      /* System Handler Control and State Register */
#define OS_SCB_MMFSR_ADDRESS                (0xE000ED28u)      /* MemManage Status Register */

/*FPU uint enable or disable.*/
#define CFG_FPU_ENABLE                      TRUE

#define OS_MSR_PRIMASK_BIT0                 0x00000001u
/*=======[Porting Macro]=====================================================*/
/* Common macros */
#define ASM                                 __asm__ volatile
#define OS_ARCH_INT_ENABLE_BIT		        (0x00000100U)
#define OS_MAX_ISR1_LOG_PRIO                (0x00000006U)
#define OS_ARCH_STACK_ALIGN(addr)	        ((addr) & 0xFFFFFFF8u)

/* Msync/Isynch core instruction macros */
#define OS_ARCH_ISYNC()                     ASM("isb")
#define OS_ARCH_DSYNC()				        ASM("dsb")
#define OS_TASK_SWITCH_PROC() Os_ArchDispatch_ISR()
#define OS_START_DISPATCH()  
/* Disable/Enable HW Interrupts */
#define Os_ArchDisableInt()                 ASM("cpsid i")
#define Os_ArchEnableInt()                  ASM("dsb\n cpsie i\n")

#define OS_ARCH_INIT_XPSR                   (0x01000000U)

/* Critical Macro */
#define OS_ARCH_DECLARE_CRITICAL()          Os_ArchMsrType msr
#define OS_ARCH_ENTRY_CRITICAL()            (Os_ArchSuspendAllInt(&msr))
#define OS_ARCH_EXIT_CRITICAL()             Os_ArchRestoreAllInt(msr)

#if (TRUE == CFG_SRV_SHELLOS)
#define OS_ENTER_KERNEL()            Os_ThreadModeType GetCpuInf = Os_GetThreadMode(); \
                                     OS_CHANGCPUMODE();
#define OS_EXIT_KERNEL()             OS_RESUMECPUMODE()
#else
#define OS_ENTER_KERNEL()
#define OS_EXIT_KERNEL()
#endif

#if (TRUE == CFG_SRV_SHELLOS)
/* Macro definition of CPU mode set,*/
/* Choose user mode for the Tricore platform, User0/1*/
/* Indicates which user mode the CPU uses. */
/* DD_1_0174 */
#define OS_CPUMODE_USER        OS_CPUMODE_USER1
/*to change to the user or supervisor mode*/
/* DD_1_0348 */
#define OS_CHANGCPUMODE()                  \
{                                              \
    if (OS_THREAD_MODE_SUPERVISOR == GetCpuInf)\
    {                                          \
        /*nothing to do*/                      \
    }                                          \
    else                                       \
    {                                          \
            Os_ArchSyscall();                  \
    }                                          \
}


#define OS_RESUMECPUMODE()                  \
{                                            \
    if (OS_THREAD_MODE_USER == GetCpuInf)\
    {                                        \
        Os_SetCpuMode(OS_CPUMODE_USER);      \
    }                                        \
    else                                     \
    {                                        \
        /* nothing to do. */                 \
    }                                        \
}
/* Change to the user or supervisor mode */
#endif /* TRUE == CFG_SRV_SHELLOS */

#if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
/* Get/Set special register---control*/
#define Os_ArchGetControl()                 \
    ASM                                     \
    (                                       \
        "push {r0,r1}                  \n"  \
        "ldr r1, =Os_ArchControl       \n"  \
        "mrs r0, control               \n"  \
        "str r0, [r1]                  \n"  \
        "pop {r0,r1}                   \n"  \
    )
#define Os_ArchSetControl()                 \
    ASM                                     \
    (                                       \
        "ldr r0, =Os_ArchControl       \n"  \
        "ldr r0, [r0]                  \n"  \
        "msr control, r0               \n"  \
    )
/* Change CPU mode:User<-->Supervisor */
/* Non-Trusted Application enter service shall change to SV mode */
#define Os_ArchEnterService()               \
{                                           \
    if (FALSE == Os_AppCfg[Os_SCB.sysRunningAppID].OsTrusted)\
    {                                       \
        Os_ArchSyscall();                   \
    }                                       \
}
/* Non-Trusted Application exit service shall change to UM mode */
#define Os_ArchExitService()            

/* Non-Trusted Application enter isr shall change to UM mode */
#define Os_ArchEnterIsr()              
/* Non-Trusted Application exit isr shall change to SV mode */
#define Os_ArchExitIsr()              
#endif

#define Os_ArchPreSwitch2System()

/* Switch msp to system stack*/
#define Os_ArchSwitch2System()              \
    do                                      \
    {                                       \
        Os_ArchTempSp = OS_ARCH_STACK_ALIGN((uint32)Os_SystemStack->stackTop);\
        ASM ("msr msp, %[sysSP]"::[sysSP] "r" (Os_ArchTempSp));\
    }while(0)

#if (CFG_ISR2_MAX > 0U)
#define Os_ArchSwitch2ISR2Stk(isrId)        \
{                                           \
    Os_ArchTempSp = OS_ARCH_STACK_ALIGN((uint32)Os_ISR2Stack[isrId].stackTop);\
    Os_ArchMasterSp_New = &Os_ArchMasterSp_ARRAY[Os_IntNestISR2];\
    ASM                                      \
    (                                        \
    "    ldr r0, = Os_ArchMasterSp_New  \n"  \
    "    ldr r0, [r0]                   \n"  \
    "    mrs r1, msp                    \n"  \
    "    str r1, [r0]                   \n"  \
    "    ldr r0, = Os_ArchTempSp        \n"  \
    "    ldr r1, [r0]                   \n"  \
    "    msr msp, r1                    \n"  \
    );                                       \
}

/* Resume msp */
#define Os_ArchSwitch2MasterStk()           \
{                                           \
    Os_ArchMasterSp_New = &Os_ArchMasterSp_ARRAY[Os_IntNestISR2];\
    ASM                                     \
    (                                       \
    "    ldr r0, = Os_ArchMasterSp_New      \n"  \
    "    ldr r0, [r0]                   \n"  \
    "    ldr r1, [r0]                   \n"  \
    "    msr msp, r1                    \n"  \
    );                                      \
}

#else
#define Os_ArchSwitch2ISR2Stk(isrId)
#define Os_ArchSwitch2MasterStk(isrId)
#endif


/* Reclaim isr_csa in TerminateApplication. */
#define Os_ArchReclaimIsrCsasTermApp(pcx, endPcx)

#define  OS_ARCH_ISR2_EPILOGUE_KILL_ISR()   OS_ARCH_ISR2_EPILOGUE_TERMINATEISR()

/*=======[I N T E R N A L   M A C R O]=======================================*/
/* the ISR1 context save/resume. */
#if (TRUE == CFG_INT_NEST_ENABLE)
#define OS_ARCH_ISR1_PROLOGUE(isrId)            \
{                                               \
    Os_ArchSuspendInt(&Os_ArchIntNestedSaved);  \
    if (0U == Os_IntNestISR1)                   \
    {                                           \
        Os_SaveLevelISR1 = Os_SCB.sysOsLevel;   \
        Os_SCB.sysOsLevel = OS_LEVEL_ISR1;      \
    }                                           \
    Os_EnterISR1();                             \
    Os_IntNestISR1++;                           \
    if (TRUE == Os_IsrCfg[Os_IntCfgIsrId].OsNestedEnable)\
    {                                           \
        Os_ArchRestoreInt(Os_ArchIntNestedSaved);\
    }                                           \
}

#define OS_ARCH_ISR1_EPILOGUE()                 \
{                                               \
    if (TRUE == Os_IsrCfg[Os_IntCfgIsrId].OsNestedEnable)\
    {                                           \
        Os_ArchSuspendInt(&Os_ArchIntNestedSaved);\
    }                                           \
    Os_ExitISR1();                              \
    Os_IntNestISR1--;                           \
    if(0U == Os_IntNestISR1)                    \
    {                                           \
        Os_SCB.sysOsLevel = Os_SaveLevelISR1;   \
    }                                           \
    Os_ArchRestoreInt(Os_ArchIntNestedSaved);   \
}

#else
#define OS_ARCH_ISR1_PROLOGUE(isrId)            \
{                                               \
    Os_ArchSuspendInt(&Os_ArchIntNestedSaved);  \
    Os_SaveLevelISR1 = Os_SCB.sysOsLevel;       \
    Os_SCB.sysOsLevel = OS_LEVEL_ISR1;          \
    Os_EnterISR1();                             \
}

#define OS_ARCH_ISR1_EPILOGUE()                 \
{                                               \
    Os_SCB.sysOsLevel = Os_SaveLevelISR1;       \
    Os_ExitISR1();                              \
    Os_ArchRestoreInt(Os_ArchIntNestedSaved);   \
}
#endif /* #if (TRUE == CFG_INT_NEST_ENABLE) */


/* the ISR2 context save/resume. */
#define OS_ARCH_SAVE_CONTEXT_ISR2()               \
    ASM (                                         \
    "    mrs r0, msp                         \n"  \
    "    isb                                 \n"  \
    "    tst r14, #0x10                      \n"  \
    "    it eq                               \n"  \
    "    vstmdbeq r0!, {s16-s31}             \n"  \
    "    mrs r3, control                     \n"  \
    "    stmdb r0!, {r3-r11, r14}            \n"  \
    "    msr msp, r0                         \n"  \
    "    dsb                                 \n"  \
    "    isb                                 \n"  \
    );

#define OS_ARCH_RESUME_CONTEXT_ISR2()             \
    ASM (                                         \
    "    mrs r0, msp                     \n"      \
    "    isb                             \n"      \
    "    ldmia r0!, {r3-r11, r14}        \n"      \
    "    msr control, r3                 \n"      \
    "    tst r14, #0x10                  \n"      \
    "    it eq                           \n"      \
    "    vldmiaeq r0!, {s16-s31}         \n"      \
    "    msr msp, r0                     \n"      \
    "    dsb                             \n"      \
    "    isb                             \n"      \
     );


#if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
#define OS_TIME_PROT_ENTRE(isrId)                                           \
{                                                                           \
 if (E_OK != Os_TmProtIsrFrameChk(isrId))                                   \
    {                                                                       \
        Os_ArchEnableInt();                                                 \
        return;                                                             \
    }                                                                       \
}

#define OS_TIME_PROT_ISR_EXIT()                                             \
{                                                                           \
    if((TRUE == Os_TprotTerminateIsr) && (Os_IntNestISR2 >= 2u) )           \
    {                                                                       \
        Os_IntNestISR2--;                                                   \
        Os_SCB.sysDispatchLocker = Os_SCB.sysDispatchLocker -1u;            \
        Os_ArchMasterSp_New = &Os_ArchMasterSp_ARRAY[Os_IntNestISR2];       \
        Os_TprotTerminateIsr = FALSE;                                       \
        Os_TprotTerminateTask = TRUE;                                       \
        Os_IsrTempIPSR = Os_IsrIPSR[Os_IntNestISR2-1u];                     \
        TerminateISR();                                                     \
    }                                                                       \
}

#define OS_TIME_PROT_TASK_EXIT()                                            \
{                                                                           \
    if ((TRUE == Os_TprotTerminateTask)&&(Os_IntNestISR2 == 0U))             \
    {                                                                       \
        OS_INTERRUPT_SET_PRIO(OS_SRC_PendSV_ADDR, OS_INT_PRIO_LOG_TO_PHY(12U));\
    }                                                                       \
}
#else
#define OS_TIME_PROT_ENTRE(isrId)
#define OS_TIME_PROT_ISR_EXIT()
#define OS_TIME_PROT_TASK_EXIT()
#endif

#if (TRUE == CFG_INT_NEST_ENABLE)
#define OS_ISR_NEST_ENTER(isrId)                            \
{                                                           \
    if (TRUE == Os_IsrCfg[isrId].OsNestedEnable)            \
    {                                                       \
        Os_ArchRestoreInt(Os_ArchIntNestedSaved);           \
    }                                                       \
}

#define OS_ISR_NEST_EXIT()                                  \
{                                                           \
    if (TRUE == Os_IsrCfg[Os_IntCfgIsrId].OsNestedEnable)   \
    {                                                       \
        Os_ArchSuspendInt(&Os_ArchIntNestedSaved);          \
    }                                                       \
}

#else
#define OS_ISR_NEST_ENTER(isrId)

#define OS_ISR_NEST_EXIT()
#endif

/* Interrupt Entry/Exit Preface */
#define OS_ARCH_ISR2_PROLOGUE(isrId)        \
{                                           \
    Os_ArchSuspendInt(&Os_ArchIntNestedSaved);\
    OS_ARCH_SAVE_CONTEXT_ISR2();            \
    OS_TIME_PROT_ENTRE(isrId);              \
    Os_IntCfgIsrId = isrId;                 \
    Os_ArchSwitch2ISR2Stk(isrId);           \
    Os_SetCpuMode(OS_CPUMODE_SUPERVISOR);   \
    Os_EnterISR2();                         \
    OS_ISR_NEST_ENTER(isrId);               \
}

#define OS_ARCH_ISR2_EPILOGUE()             \
{                                           \
    Os_ArchDisableInt();                    \
    OS_ISR2OCCUPYINTRES();                  \
    OS_ISR_NEST_EXIT();                     \
    OS_HARD_FAULT_ISR2_EXIT();              \
    OS_TIME_PROT_ISR_EXIT();                \
    Os_ExitISR2();                          \
    Os_ArchSwitch2MasterStk();              \
    OS_TIME_PROT_TASK_EXIT();               \
    OS_ARCH_RESUME_CONTEXT_ISR2();          \
    OS_ARCH_ISR2_EXIT()                     \
}

#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
#define OS_ARCH_ISR2_EXIT()                 \
{                                           \
    if (1U == HardFault_Flag)                \
    {                                       \
        HardFault_Flag = 0;                 \
        Os_ArchRestoreInt(Os_ArchIntNestedSaved);\
        Os_ArchEnableInt();                 \
        ASM("ldmia sp!,{r4,r8, pc}");       \
    }                                       \
    else                                    \
    {                                       \
        Os_ArchRestoreInt(Os_ArchIntNestedSaved);\
        Os_ArchEnableInt();                 \
    }                                       \
}

#define OS_HARD_FAULT_ISR2_EXIT()          \
{                                          \
    if (1U == HardFault_Flag)              \
    {                                      \
        TerminateISR();                    \
        Os_ArchMpDefaultConfigSwitch();    \
    }                                      \
}
#else
#define OS_ARCH_ISR2_EXIT()                 \
{                                           \
	Os_ArchRestoreInt(Os_ArchIntNestedSaved);\
	Os_ArchEnableInt();                     \
}

#define OS_HARD_FAULT_ISR2_EXIT()
#endif

#if (TRUE == CFG_TIMING_PROTECTION_ENABLE)   
#define OS_TIME_PROT_TERM_TASK()                                            \
{                                                                           \
    if (TRUE == Os_TprotTerminateTask)                                      \
    {                                                                       \
        OS_INTERRUPT_SET_PRIO(OS_SRC_PendSV_ADDR, OS_INT_PRIO_LOG_TO_PHY(12U)); \
    }                                                                       \
}

#else
#define OS_TIME_PROT_TERM_TASK()
#endif

#define OS_ARCH_RESUME_CONTEXT_ISR2_TERMINATEISR()      \
    OS_ARCH_RESUME_CONTEXT_ISR2();             \
    ASM (                                      \
    "    cpsie i                          \n"  \
    "    ldmia sp!,{r7, pc}               \n"  \
    );                                         \

#define OS_ARCH_TPORT_TERMINATE_ISR()          \
{                                              \
    Os_ArchDisableInt();                       \
    OS_ISR2OCCUPYINTRES();                     \
    Os_ExitISR2();                             \
    Os_ArchRestoreInt(Os_ArchIntNestedSaved);  \
    Os_ArchSwitch2MasterStk();                 \
    OS_TIME_PROT_TERM_TASK();                  \
    OS_ARCH_RESUME_CONTEXT_ISR2_TERMINATEISR();\
}  

#define OS_ARCH_ISR2_EPILOGUE_TERMINATEISR()    \
{                                               \
    if (1U != HardFault_Flag)                   \
    {                                           \
        OS_ARCH_TPORT_TERMINATE_ISR();          \
    }                                           \
    else                                        \
    {                                           \
        OS_ARCH_ISR2_EPILOGUE();                \
    }                                           \
}

#if (TRUE == CFG_SERVICE_PROTECTION_ENABLE)
#define OS_ISR2OCCUPYINTRES() Os_Isr2OccupyIntRes()
#else
#define OS_ISR2OCCUPYINTRES()
#endif /*#if (TRUE == CFG_SERVICE_PROTECTION_ENABLE)*/


#define OS_ADDRESS_IS_IN_ALL_RAM(Address, Size)                                   \
( (((uint32)Os_MemProtKnAddrCfg.OsKernelAddr.pSRamStart <= (Address))             \
&& ((uint32)Os_MemProtKnAddrCfg.OsKernelAddr.pSRamEnd >= ((Address) + (Size))))   \
|| (((uint32)Os_MemProtKnAddrCfg.OsKernelAddr.pDtcmStart <= (Address))            \
&& ((uint32)Os_MemProtKnAddrCfg.OsKernelAddr.pDtcmEnd >= ((Address) + (Size)))) )

#define OS_ADDRESS_IS_IN_OTHER_APP(Address, Size, coreId, appsuborID)        \
(((uint32)Os_MemProtKnAddrCfg.OsKernelAddr.pSRamStart <= (Address))             \
&& ((uint32)Os_Core_App_DAddr[coreId].APP_ADDR_START >= ((Address) + (Size))))           \
|| (((uint32)Os_Core_App_DAddr[coreId].APP_ADDR_END <= (Address))                      \
&& ((uint32)Os_MemProtKnAddrCfg.OsKernelAddr.pPeripheralEnd >= ((Address) + (Size))))    \
|| (((uint32)Os_App_DAddr[appsuborID].APP_ADDR_START <= (Address))                     \
&& ((uint32)Os_App_DAddr[appsuborID].APP_ADDR_END >= ((Address) + (Size))))



/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef uint32   Os_ArchMsrType;
typedef uint32   Os_TaskCBExtType;


/* type of an Trap */
typedef void (*Os_traphnd)(uint16 Os_Tin);



/* Core Mode */
typedef enum
{
    OS_CORE_MODE_HALT		= 0U,
    OS_CORE_MODE_RUN		= 1U,
    OS_CORE_MODE_IDLE		= 2U,
    OS_CORE_MODE_SLEEP		= 3U,
    OS_CORE_MODE_STANDBY	= 4U,
    OS_CORE_MODE_UNKNOWN	= 5U
} Os_CoreModeType;

/* the mode of thread. */
typedef enum
{
    OS_THREAD_MODE_SUPERVISOR       = 0U,
    OS_THREAD_MODE_USER             = 1U
}Os_ThreadModeType;

/*=======[E X T E R N A L   D A T A]==========================================*/
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */ /* ARCH_PROCESSOR_COMPILER_001 */
extern P2VAR(uint32, AUTOMATIC, OS_VAR)             Os_ArchMasterSp_New;
extern P2VAR(uint32, AUTOMATIC, OS_VAR)             Os_ArchTopStkPtr;
extern P2VAR(Os_TaskCBExtType, AUTOMATIC, OS_VAR) 	Os_TaskCBExt;
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
extern VAR(uint32, OS_VAR) 				Os_ArchMasterSp_ARRAY[20];
extern VAR(uint32, OS_VAR)              Os_IsrIPSR[CFG_ISR_MAX_CORE0];
extern VAR(uint32, OS_VAR)              Os_IsrTempIPSR;
extern VAR(volatile uint32, OS_VAR) 			Os_ArchTempSp;
extern VAR(volatile uint32, OS_VAR) 			Os_ArchControl;
extern VAR(uint32, OS_VAR)                         Os_ArchIntNestedSaved;
extern P2CONST(OS_ISR_ADDR, AUTOMATIC, OS_VAR) 		Os_IsrDAddr;
extern P2CONST(OS_TASK_ADDR, AUTOMATIC, OS_VAR) 	Os_TaskDAddr;

#if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
extern VAR(volatile uint32, OS_VAR) Os_TprotTerminateIsr;
extern VAR(volatile uint32, OS_VAR) Os_TprotTerminateTask;
#endif

#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
extern VAR(uint16, OS_VAR) HardFault_Flag;
extern uint8 RODATA_START[];
extern uint8 RODATA_END[];
#endif


#if (CFG_ISR_MAX > 0U)
extern VAR(Os_CallLevelType, OS_VAR) Os_SaveLevelISR1;
#endif

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
extern FUNC(Os_IPLType, OS_CODE) Os_ArchGetIpl(void);
extern FUNC(void, OS_CODE) Os_ArchSetIpl(Os_IPLType ipl, Os_IsrDescriptionType isrdesc);
extern FUNC(void, OS_CODE) Os_ArchSuspendInt(P2VAR(Os_ArchMsrType, AUTOMATIC, OS_VAR) msr);/* PRQA S 3432 */ /* MISRA Rule 20.7 */
extern FUNC(void, OS_CODE) Os_ArchRestoreInt(Os_ArchMsrType msr);
extern FUNC(void, OS_CODE) Os_ArchSuspendAllInt(P2VAR(Os_ArchMsrType, AUTOMATIC, OS_VAR) msr);/* PRQA S 3432 */ /* MISRA Rule 20.7 */
extern FUNC(void, OS_CODE) Os_ArchRestoreAllInt(Os_ArchMsrType msr);
extern FUNC(void, OS_CODE) Os_ArchInitCPU(void);
extern FUNC(void, OS_CODE) Os_ArchFirstEnterTask(void);
extern FUNC(void, OS_CODE) Os_ArchStartScheduler(void);
extern FUNC(void, OS_CODE) Os_ArchDispatch(void);
extern FUNC(void, OS_CODE) Os_ArchDispatch_ISR(void);

extern FUNC(void, OS_CODE) Os_ArchInitSystemTimer(void);
extern FUNC(void, OS_CODE) Os_InterruptInit(void);
extern FUNC(void, OS_CODE) Os_StartSysTimer(void);
extern FUNC(void, OS_CODE) TerminateISR(void);
#if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
extern FUNC(void, OS_CODE) Os_ArchInitTimingProtTimer(void);
#endif /* #if (TRUE == CFG_SYSTEM_TIMER_ENABLE) */

#if (TRUE == CFG_INT_NEST_ENABLE)
extern FUNC(uint32, OS_CODE) Os_GetIsrIPSR(void);
#endif 

/* Shell protection */
#if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
extern FUNC(void, OS_CODE) Os_ArchSyscall(void);
extern FUNC(void, OS_CODE) SVC_Handler(void);
#endif
extern FUNC(void, OS_CODE) HardFault_Handler(void);
extern FUNC(void, OS_CODE) PendSV_Handler(void);
extern FUNC(void, OS_CODE) Os_SetCpuMode(Os_CPUModeType mode);

/* Memory protection. */
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
extern FUNC(void, OS_CODE) Os_ArchMemProtEnable(void);
extern FUNC(void,OS_CODE)  Os_ArchInitKnMemMap(void);
extern FUNC(void, OS_CODE) Os_ArchMpuRegionInit(void);
extern FUNC(void, OS_CODE) Os_ArchAppMemoryInit(void);
extern FUNC(void, OS_CODE) Os_ArchMpDefaultConfigSwitch(void);
#endif/* FALSE == CFG_MEMORY_PROTECTION_ENABLE */


/* Time protection */
#if (TRUE == CFG_TIMING_PROTECTION_ENABLE)
extern FUNC(void, OS_CODE) Os_ArchDisableAllInt_ButTimingProtInt(void);
extern FUNC(void, OS_CODE) Os_ArchEnableAllInt_ButTimingProtInt(void);
#endif /* #if (TRUE == CFG_TIMING_PROTECTION_ENABLE) */

extern FUNC(void, OS_CODE) Os_ArchInitIntPrio(void);

#if ((OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
#if (CFG_ISR_MAX > 0)
extern FUNC(void, OS_CODE) Os_ArchDisableIntInApp
(
    P2CONST(Os_ApplicationCfgType, AUTOMATIC, OS_VAR) posCurAppCfg
);
extern FUNC(void, OS_CODE) Os_ArchAppTerminateIsrProc (Os_IsrType OsIsrID);
#endif
extern FUNC(void, OS_CODE) Os_ArchAppTerminateTaskProc (Os_TaskType OsTaskID);
#endif
extern FUNC(void, OS_CODE)              Os_ArchRemoteCall(CoreIdType respondCoreId);
extern FUNC(void, OS_CODE)              Os_ArchRemoteCallRespond(CoreIdType respondCoreId);
extern FUNC(uint32, OS_CODE)            Os_CmpSwapW(uint32* address, uint32 compareVal, uint32 exchangedVal);
extern FUNC(void, OS_CODE)              Os_InterruptInstall(uint8 id, uint8 prio, uint32 srcType, Os_isrhnd isrProc);
extern FUNC(Os_CoreIdType,OS_CODE)      Os_ArchGetCoreID(void);
extern FUNC(void, OS_CODE)              Os_ArchStartCore(Os_CoreIdType coreId);
extern FUNC(Os_CoreModeType, OS_CODE)   Os_GetCoreMode(Os_CoreIdType coreId);
extern FUNC(boolean, OS_CODE)           Os_SetCoreMode(Os_CoreIdType coreId, Os_CoreModeType coreMode);
extern FUNC(uint32, OS_CODE)            getControlValue(void);
extern FUNC(void, OS_CODE)              Os_ArchClearTmProtTimer(void);
extern FUNC(void, OS_CODE)              Os_ArchAppMemoryInit(void);
extern FUNC(Os_ThreadModeType, OS_CODE) Os_GetThreadMode(void);

extern FUNC(void, OS_APPL_CODE) IdleHook_Core0(void);

extern FUNC(void, OS_CODE) Os_TaskEntry_IdleCore0(void);
extern FUNC(void, OS_CODE) Os_IntHandler(void);

/*============[STACK CHECK]=====================*/
#define OS_FILL_SAFET_STACK()                                                \
{                                                                            \
    *ptr = OS_STACK_FILL_PATTERN;                                            \
    *(ptr + (Os_StackDataType)1) = OS_STACK_FILL_PATTERN;                    \
    *(ptr + (Os_StackDataType)2) = OS_STACK_FILL_PATTERN;                    \
    *(ptr + (Os_StackDataType)3) = OS_STACK_FILL_PATTERN;                    \
}

extern void Flash_ECC_ERROR(void);
#endif  /* #ifndef ARCH_PROCESSOR_H */
/*=======[E N D   O F   F I L E]==============================================*/

