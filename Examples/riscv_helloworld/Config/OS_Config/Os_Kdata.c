/*============================================================================*/
/*  Copyright (C) iSOFT   (2022), iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Os_Kdata.c>
 *  @brief      <>
 *  
 *  <MCU:RISC-V>
 *  
 *  @author     <>
 *  @date       <2024-04-23 18:14:06>
 */
/*============================================================================*/

/*=======[I N C L U D E S]====================================================*/
#include "Os_Cfg.h"
#include "Os_CfgData.h"
#include "Os.h"
#include "Arch_Processor.h"
#include "Os_Internal.h"

/*=======[V E R S I O N   I N F O R M A T I O N]===============================*/
#define     OS_CFG_C_AR_MAJOR_VERSION              19U
#define     OS_CFG_C_AR_MINOR_VERSION              11U
#define     OS_CFG_C_AR_PATCH_VERSION              0U
#define     OS_CFG_C_SW_MAJOR_VERSION              2U
#define     OS_CFG_C_SW_MINOR_VERSION              0U
#define     OS_CFG_C_SW_PATCH_VERSION              0U

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (OS_CFG_C_AR_MAJOR_VERSION != OS_CFG_H_AR_MAJOR_VERSION)
    #error "Os_Cfg.c:Mismatch in Specification Major Version"
#endif
#if (OS_CFG_C_AR_MINOR_VERSION != OS_CFG_H_AR_MINOR_VERSION)
    #error "Os_Cfg.c:Mismatch in Specification Minor Version"
#endif
#if (OS_CFG_C_AR_PATCH_VERSION != OS_CFG_H_AR_PATCH_VERSION)
    #error "Os_Cfg.c:Mismatch in Specification Patch Version"
#endif
#if (OS_CFG_C_SW_MAJOR_VERSION != OS_CFG_H_SW_MAJOR_VERSION)
    #error "Os_Cfg.c:Mismatch in Specification Major Version"
#endif
#if (OS_CFG_C_SW_MINOR_VERSION != OS_CFG_H_SW_MINOR_VERSION)
    #error "Os_Cfg.c:Mismatch in Specification Minor Version"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/

/* -----------------Control block definition--------------------- */
/*
 * Private data,be accessed by own core.
 */

#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_CCBType, OS_VAR) Os_CCBCore0[CFG_COUNTER_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_ACBType, OS_VAR) Os_ACBCore0[CFG_ALARM_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#include "Os_MemMap.h"
VAR(Os_ECBType volatile, OS_VAR) Os_ECB[CFG_EXTENDED_TASK_MAX];
#define OS_STOP_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_RCBType, OS_VAR) Os_RCBCore0[CFG_STD_RESOURCE_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

/* ------------------------ _OS_ISR_E3420 beginning ---------------------- */
#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_ICBType,  OS_VAR) Os_ICBCore0[CFG_ISR2_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * Private data, be accessed by own core.
 */
#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_IsrType,  OS_VAR) Os_SysIsrNestQueueCore0[CFG_ISR_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "Os_MemMap.h"
static Os_ResourceType Os_ICBIsrC2ResourceStackCore0[CFG_ISR2_MAX_CORE0][CFG_STD_RESOURCE_MAX_CORE0];
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONSTP2VAR(Os_ICBType, AUTOMATIC, OS_VAR) Os_ICB_Inf[OS_AUTOSAR_CORES] = /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Os_ICBCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONSTP2VAR(Os_IsrType, AUTOMATIC, OS_VAR) Os_SysIsrNestQueue_Inf[OS_AUTOSAR_CORES] = /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Os_SysIsrNestQueueCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONSTP2VAR(Os_ResourceType, AUTOMATIC, OS_VAR) Os_ICBIsrC2ResourceStack_Inf[OS_AUTOSAR_CORES] = /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Os_ICBIsrC2ResourceStackCore0[0]
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* ------------------------ _OS_ISR_E3420 end ---------------------- */

/*
 * Global data, be accessed by all core.
 */

#define OS_START_SEC_VAR_CLEARED_GLOBAL_UNSPECIFIED
#include "Os_MemMap.h"
VAR(Os_CoreCBType volatile, OS_VAR)  Os_CoreCB;
#define OS_STOP_SEC_VAR_CLEARED_GLOBAL_UNSPECIFIED
#include "Os_MemMap.h"

/*
 * Clone data, Each core has a copy.
 */
#define OS_START_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#include "Os_MemMap.h"
VAR(Os_SCBType, OS_VAR)    Os_SCB;
#define OS_STOP_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_PriorityType, OS_VAR)Os_ReadyMap_Core0[READY_MAP_SIZE(CFG_PRIORITY_MAX_CORE0)]; /* PRQA S 3432 */ /* MISRA Rule 20.7 */
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
CONSTP2VAR(Os_ACBType, AUTOMATIC, OS_VAR) Os_ACB_Inf[OS_AUTOSAR_CORES] =
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
{
    Os_ACBCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
CONSTP2VAR(Os_CCBType, AUTOMATIC, OS_VAR) Os_CCB_Inf[OS_AUTOSAR_CORES] =
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
{
    Os_CCBCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONSTP2VAR(Os_RCBType, AUTOMATIC, OS_VAR) Os_RCB_Inf[OS_AUTOSAR_CORES] = /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Os_RCBCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* ------------------------ _OS_Task beginning ---------------------- */
#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_TCBType, OS_VAR) Os_TCBCore0[CFG_TASK_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "Os_MemMap.h"
static Os_ResourceType Os_TCBTaskResourceStackCore0[CFG_TASK_MAX_CORE0][CFG_STD_RESOURCE_MAX_CORE0];
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONSTP2VAR(Os_TCBType, AUTOMATIC, OS_VAR) Os_TCB_Inf[OS_AUTOSAR_CORES] = /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Os_TCBCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONSTP2VAR(Os_PriorityType, AUTOMATIC, OS_VAR) Os_ReadyMap_Inf[OS_AUTOSAR_CORES] = /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Os_ReadyMap_Core0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
CONST(TaskResourceStackType, OS_CONST) Os_TCBTaskResourceStack_Inf[OS_AUTOSAR_CORES] =
{
    {Os_TCBTaskResourceStackCore0[0],
        CFG_STD_RESOURCE_MAX_CORE0
    }
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* ------------------------ _OS_Task end ---------------------- */

/* ------------------------ _OS_OsScheduleTable beginning ---------------------- */
#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"
static VAR(Os_STCBType, OS_VAR) Os_STCBCore0[CFG_SCHEDTBL_MAX_CORE0];
#define OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#include "Os_MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
CONSTP2VAR(Os_STCBType, AUTOMATIC, OS_VAR) Os_STCB_Inf[OS_AUTOSAR_CORES] =
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
{
    Os_STCBCore0
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h"

/* ------------------------ OS_OsScheduleTable end ---------------------- */

/*=======[E N D   O F   F I L E]==============================================*/

