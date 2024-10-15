/*============================================================================*/
/*  Copyright (C) iSOFT   (2022), iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Os_CfgData.h>
 *  @brief      <>
 *  
 *  <MCU:RISC-V>
 *  
 *  @author     <>
 *  @date       <2024-04-24 13:52:07>
 */
/*============================================================================*/
/*============================================================================*/
#ifndef OS_CFGDATA_H
#define OS_CFGDATA_H
/*=======[I N C L U D E S]====================================================*/
#include "Os_Cfg.h"
#include "Os_Types.h"

/*=======[F I L E  V E R S I O N   I N F O R M A T I O N]===============================*/
#define     OS_CFGDATA_H_AR_MAJOR_VERSION              19U
#define     OS_CFGDATA_H_AR_MINOR_VERSION              11U
#define     OS_CFGDATA_H_AR_PATCH_VERSION              0U
#define     OS_CFGDATA_H_SW_MAJOR_VERSION              2U
#define     OS_CFGDATA_H_SW_MINOR_VERSION              0U
#define     OS_CFGDATA_H_SW_PATCH_VERSION              0U
/*=======[M A C R O S]========================================================*/
/* DD_1_0396 */
extern CONST(Os_CounterCfgType, OS_CONST) Os_CounterCfgCore0[CFG_COUNTER_MAX_CORE0];
extern CONST(Os_AlarmCfgType, OS_CONST) Os_AlarmCfgCore0[CFG_ALARM_MAX_CORE0];
/* ------------------------ OS_OsScheduleTable beginning ---------------------- */
/* ------------------------ OS_OsScheduleTable end ---------------------- */
extern VAR(Os_ECBType volatile, OS_VAR) Os_ECB[CFG_EXTENDED_TASK_MAX];
extern VAR(Os_SCBType, OS_VAR)  Os_SCB;
/* 
 * DeclarePanicHandler
 */
extern FUNC(void, OS_CODE) Arch_PanicHandler(void);

/* 
 * Declare Os_ArchSystemTimer
 */ 
extern FUNC(void, OS_CODE) Os_ArchSystemTimerCore0(void);

/*
 * Declare Alarm Callback
 */ 

/*
 * Declare Trusted Function
 */ 

/*
 * Declare Os_App hooks
 */ 
/* the core default execute start address. reference ld. */
extern uint8 _start;
/* 
 * Declare interface
 */ 
extern CONSTP2CONST(Os_AlarmCfgType, AUTOMATIC, OS_VAR)  Os_AlarmCfg_Inf[OS_AUTOSAR_CORES];
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
extern CONSTP2VAR(Os_ACBType, AUTOMATIC, OS_VAR)  Os_ACB_Inf[OS_AUTOSAR_CORES];
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
extern CONST(Os_AlarmType, OS_CONST)  Os_CfgAlarmMax_Inf[OS_AUTOSAR_CORES];
extern CONSTP2CONST(Os_CounterCfgType, AUTOMATIC, OS_VAR) Os_CounterCfg_Inf[OS_AUTOSAR_CORES];
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
extern CONSTP2VAR(Os_CCBType, AUTOMATIC, OS_VAR) Os_CCB_Inf[OS_AUTOSAR_CORES];
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
extern CONST(Os_CounterType, OS_CONST) Os_CfgCounterMax_Inf[OS_AUTOSAR_CORES];
/*  OS_Service_Protection  beginning */
/*  OS_Service_Protection end  */
extern CONST (OsPeripheralAreaCfgType, OS_CONST) Os_PeriAreaCfg[CFG_PERIPHERAL_MAX];
/* ++ OsIsr Configuration ++ */
extern CONST(Os_IsrType, OS_CONST) Os_CfgIsrMax_Inf[OS_AUTOSAR_CORES];
extern CONST(Os_IsrType, OS_CONST) Os_CfgIsr2Max_Inf[OS_AUTOSAR_CORES];
extern CONSTP2VAR(Os_ICBType, AUTOMATIC, OS_VAR) Os_ICB_Inf[OS_AUTOSAR_CORES];
extern CONSTP2CONST(Os_StackType, AUTOMATIC, OS_VAR) Os_Isr2Stack_Inf[OS_AUTOSAR_CORES];
extern CONSTP2CONST(Os_IsrCfgType, AUTOMATIC, OS_VAR) Os_IsrCfg_Inf[OS_AUTOSAR_CORES];
extern CONST(Os_IPLType, OS_CONST) Os_CfgIsr2TplMax_Inf[OS_AUTOSAR_CORES];

extern CONSTP2VAR(Os_IsrType, AUTOMATIC, OS_VAR) Os_SysIsrNestQueue_Inf[OS_AUTOSAR_CORES];

/* 
 * DeclareISR
 */ 
DeclareISR(ISR_CPU_1);
DeclareISR(ISR_CPU_2);
DeclareISR(ISR_CPU_4);
DeclareISR(ISR_CPU_5);
DeclareISR(ISR_CPU_6);
DeclareISR(ISR_CPU_8);
DeclareISR(ISR_CPU_9);
DeclareISR(ISR_CPU_12);
DeclareISR(ISR_CPU_13);
DeclareISR(ISR_CPU_14);
DeclareISR(ISR_CPU_15);

/* -- OsIsr Configuration -- */

/* ++ OsResource Configuration ++ */
extern CONST(Os_ResourceType, OS_CONST) Os_CfgStdResourceMax_Inf[OS_AUTOSAR_CORES];

extern CONSTP2VAR(Os_ResourceType, AUTOMATIC, OS_VAR) Os_ICBIsrC2ResourceStack_Inf[OS_AUTOSAR_CORES];

extern CONST(Os_ResourceType, OS_CONST) Os_ResScheduler_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(Os_ResourceCfgType, AUTOMATIC, OS_VAR) Os_ResourceCfg_Inf[OS_AUTOSAR_CORES];

extern CONSTP2VAR(Os_RCBType, AUTOMATIC, OS_VAR) Os_RCB_Inf[OS_AUTOSAR_CORES];

extern CONST(Os_ResourceType, OS_CONST) Os_CfgResourceMax_Inf[OS_AUTOSAR_CORES];

extern CONST(TaskResourceStackType, OS_CONST) Os_TCBTaskResourceStack_Inf[OS_AUTOSAR_CORES];

/* -- OsResource Configuration -- */

/* ++ OsScheduleTable Configuration ++ */
extern CONSTP2CONST(Os_SchedTblCfgType, AUTOMATIC, OS_CONST) Os_SchedTblCfg_Inf[OS_AUTOSAR_CORES];

extern CONST(Os_ScheduleTableType, OS_CONST) Os_CfgSchedTblMax_Inf[OS_AUTOSAR_CORES];

/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
extern CONSTP2VAR(Os_STCBType, AUTOMATIC, OS_VAR) Os_STCB_Inf[OS_AUTOSAR_CORES];
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */

/* -- OsScheduleTable Configuration -- */

/* ++ OsTask Configuration ++ */
#define READY_MAP_SIZE(CFG_PRIORITY_MAX)        (((CFG_PRIORITY_MAX-1u) >> 4u) + 1u)

/* 
 * DeclareTask
 */  
DeclareTask(OsTask_100ms);
DeclareTask(OsTask_10ms);
DeclareTask(OsTask_1ms);
DeclareTask(OsTask_1s);
DeclareTask(OsTask_5ms);
DeclareTask(OsTask_event);
DeclareTask(OsTask_init);
DeclareTask(IdleCore0);

extern CONST(uint16, OS_CONST) Os_CfgPriorityMax_Inf[OS_AUTOSAR_CORES];

extern CONSTP2VAR(Os_PriorityType, AUTOMATIC, OS_VAR) Os_ReadyMap_Inf[OS_AUTOSAR_CORES]; /* PRQA S 3432 */ /* MISRA Rule 20.7 */

extern CONSTP2VAR(Os_ReadyQueueType, AUTOMATIC, OS_VAR) Os_ReadyQueueMark_Inf[OS_AUTOSAR_CORES]; /* PRQA S 3432 */ /* MISRA Rule 20.7 */

extern CONSTP2CONST(uint32, AUTOMATIC, OS_VAR) Os_ActivateQueueSize_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(Os_TaskRefType, AUTOMATIC, OS_VAR) Os_ReadyQueue_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(Os_PriorityType, AUTOMATIC, OS_VAR) Os_PrioGroup_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(Os_PriorityType, AUTOMATIC, OS_VAR) Os_PrioMask_Inf[OS_AUTOSAR_CORES];

extern CONST(uint8, OS_CONST) Os_CfgPriorityGroup_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(Os_StackType, AUTOMATIC,OS_VAR) Os_SystemStack_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(Os_TaskCfgType, AUTOMATIC, OS_CONST) Os_TaskCfg_Inf[OS_AUTOSAR_CORES];
extern CONSTP2CONST(Os_StackType, AUTOMATIC, OS_CONST) Os_TaskStack_Inf[OS_AUTOSAR_CORES];
extern CONSTP2VAR(Os_TCBType, AUTOMATIC, OS_VAR) Os_TCB_Inf[OS_AUTOSAR_CORES]; /* PRQA S 3432 */ /* MISRA Rule 20.7 */
extern CONST(uint16, OS_CONST) Os_CfgTaskMax_Inf[OS_AUTOSAR_CORES];
extern CONST(uint16, OS_CONST) Os_TASK_IDLE_Inf[OS_AUTOSAR_CORES];

extern CONST(Os_TaskType, OS_CONST) Os_CfgExtendTaskMax_Inf[OS_AUTOSAR_CORES];

/* -- OsTask Configuration -- */

/* ++ ServiceProtection Configuration ++ */
extern CONSTP2CONST(uint32* const, AUTOMATIC, OS_VAR) Os_TaskEventAccessMask_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(uint16* const, AUTOMATIC,OS_VAR) Os_TaskResourceAccessMask_Inf[OS_AUTOSAR_CORES];

extern CONSTP2CONST(uint16* const, AUTOMATIC,OS_VAR) Os_IsrResourceAccessMask_Inf[OS_AUTOSAR_CORES];

/* -- ServiceProtection Configuration -- */
#endif /* #define OS_CFGDATA_H */
/*=======[E N D   O F   F I L E]==============================================*/
