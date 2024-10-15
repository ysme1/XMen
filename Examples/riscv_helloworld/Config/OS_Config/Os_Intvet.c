/*============================================================================*/
/*  Copyright (C) iSOFT   (2022), iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Os_Intvet.c>
 *  @brief      <>
 *  
 *  <MCU:RISC-V>
 *  
 *  @author     <>
 *  @date       <2024-04-23 09:25:31>
 */
/*============================================================================*/

/*=======[I N C L U D E S]====================================================*/
#include "Os_Cfg.h"
#include "Os_Internal.h"
#include "Arch_Processor.h"

/*=======[V E R S I O N   I N F O R M A T I O N]===============================*/
#define     OS_VECTOR_C_AR_MAJOR_VERSION              19U
#define     OS_VECTOR_C_AR_MINOR_VERSION              11U
#define     OS_VECTOR_C_AR_PATCH_VERSION              0U
#define     OS_VECTOR_C_SW_MAJOR_VERSION              2U
#define     OS_VECTOR_C_SW_MINOR_VERSION              0U
#define     OS_VECTOR_C_SW_PATCH_VERSION              0U

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (OS_VECTOR_C_AR_MAJOR_VERSION != OS_CFG_H_AR_MAJOR_VERSION)
    #error "Os_Intvet.c:Mismatch in Specification Major Version"
#endif
#if (OS_VECTOR_C_AR_MINOR_VERSION != OS_CFG_H_AR_MINOR_VERSION)
    #error "Os_Intvet.c:Mismatch in Specification Minor Version"
#endif
#if (OS_VECTOR_C_AR_PATCH_VERSION != OS_CFG_H_AR_PATCH_VERSION)
    #error "Os_Intvet.c:Mismatch in Specification Patch Version"
#endif
#if (OS_VECTOR_C_SW_MAJOR_VERSION != OS_CFG_H_SW_MAJOR_VERSION)
    #error "Os_Intvet.c:Mismatch in Specification Major Version"
#endif
#if (OS_VECTOR_C_SW_MINOR_VERSION != OS_CFG_H_SW_MINOR_VERSION)
    #error "Os_Intvet.c:Mismatch in Specification Minor Version"
#endif

/*=======[M A C R O S]========================================================*/
#define     OS_ARCH_INT_CORE0                  OS_ARCH_INT_CPU0

/*==========[I S R]===========================================================*/
/* PRQA S 3408,0303,0306,3006 ++ */ /* MISRA Rule 8.4 11.4 11.4 4.3 */
/* --------------------CORE0-------------------- */
#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_SysTick_Handler0(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_SYS_TIMER_CORE0_ID));
    Os_SystickIsrClearFlag();
    Os_ArchSystemTimerCore0();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_SYS_TIMER_CORE0_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_1_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_1_IRQn_ID));
    ISR_CPU_1();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_1_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_2_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_2_IRQn_ID));
    ISR_CPU_2();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_2_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_4_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_4_IRQn_ID));
    ISR_CPU_4();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_4_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_5_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_5_IRQn_ID));
    ISR_CPU_5();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_5_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_6_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_6_IRQn_ID));
    ISR_CPU_6();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_6_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_8_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_8_IRQn_ID));
    ISR_CPU_8();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_8_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_9_IRQn(void)
{
    OS_ARCH_ISR2_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_9_IRQn_ID));
    ISR_CPU_9();
    OS_ARCH_ISR2_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_9_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_12_IRQn(void)
{
    OS_ARCH_ISR1_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_12_IRQn_ID));
    ISR_CPU_12();
    OS_ARCH_ISR1_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_12_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_13_IRQn(void)
{
    OS_ARCH_ISR1_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_13_IRQn_ID));
    ISR_CPU_13();
    OS_ARCH_ISR1_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_13_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_14_IRQn(void)
{
    OS_ARCH_ISR1_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_14_IRQn_ID));
    ISR_CPU_14();
    OS_ARCH_ISR1_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_14_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
FUNC(void, OS_CODE_FAST) Os_ISR_OS_INT_CPU_15_IRQn(void)
{
    OS_ARCH_ISR1_PROLOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_15_IRQn_ID));
    ISR_CPU_15();
    OS_ARCH_ISR1_EPILOGUE(Os_GetObjLocalId(CFG_ISR_OS_INT_CPU_15_IRQn_ID));
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

/* PRQA S 3408,0303,0306,3006 -- */ /* MISRA Rule 8.4 11.4 11.4 4.3 */

#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h"
/* ------------------Interrupt install-------------------- */
FUNC(void, OS_CODE) Os_IntHandler(void)
{
    /* Just ignore this interrupt.  */
    while(1){}
}
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h"

#define OS_START_SEC_CODE
#include "Os_MemMap.h"
FUNC(void, OS_CODE) Os_ArchInitIntPrio(void)
{
    Os_CoreIdType coreID = Os_SCB.sysCore;
    switch(coreID)
    {
        case 0:
                Os_InterruptInstall(OS_INT_CPU_MTI_IRQn, 10U, Os_SysTick_Handler0);
                Os_InterruptInstall(OS_INT_CPU_1_IRQn, 1U, Os_ISR_OS_INT_CPU_1_IRQn);
                Os_InterruptInstall(OS_INT_CPU_2_IRQn, 2U, Os_ISR_OS_INT_CPU_2_IRQn);
                Os_InterruptInstall(OS_INT_CPU_4_IRQn, 4U, Os_ISR_OS_INT_CPU_4_IRQn);
                Os_InterruptInstall(OS_INT_CPU_5_IRQn, 5U, Os_ISR_OS_INT_CPU_5_IRQn);
                Os_InterruptInstall(OS_INT_CPU_6_IRQn, 6U, Os_ISR_OS_INT_CPU_6_IRQn);
                Os_InterruptInstall(OS_INT_CPU_8_IRQn, 8U, Os_ISR_OS_INT_CPU_8_IRQn);
                Os_InterruptInstall(OS_INT_CPU_9_IRQn, 9U, Os_ISR_OS_INT_CPU_9_IRQn);
                Os_InterruptInstall(OS_INT_CPU_12_IRQn, 12U, Os_ISR_OS_INT_CPU_12_IRQn);
                Os_InterruptInstall(OS_INT_CPU_13_IRQn, 13U, Os_ISR_OS_INT_CPU_13_IRQn);
                Os_InterruptInstall(OS_INT_CPU_14_IRQn, 14U, Os_ISR_OS_INT_CPU_14_IRQn);
                Os_InterruptInstall(OS_INT_CPU_15_IRQn, 15U, Os_ISR_OS_INT_CPU_15_IRQn);
        break;
        default:
        while(1)
        {
            /*nothing to do*/
        }
        break;
    }
    return;
}
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/

