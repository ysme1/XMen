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
 **  FILENAME    :  Os.h                                                       **
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

#ifndef OS_H
#define OS_H
/*=======[I N C L U D E S]====================================================*/
#include "Os_Err.h"
#include "Os_CfgData.h"

/*=======[M A C R O S]========================================================*/
#define OS_VENDOR_ID 62
#define OS_MODULE_ID 1

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
#if (CFG_TASK_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <The task<TaskID> is transferred from the  suspended
 *                      state into the  ready  state>
 * ServiceId           <0xde>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <TaskID: Task reference>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <StatusType:>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID);

/******************************************************************************/
/*
 * Brief                <Asynchronous version of the ActivateTask() function.>
 * Service ID           <0xde>
 * Sync/Async           <Asynchronous>
 * Reentrancy           <Reentrant>
 * param-TaskID[in]     <Reference to the task>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ActivateTaskAsyn(TaskType TaskID);

/******************************************************************************/
/*
 * Brief               <This service causes the termination of the calling task. The
                        calling task is transferred from the  running state into the
                        suspended  state>
 * ServiceId           <0xdf>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <StatusType:>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) TerminateTask(void);

/******************************************************************************/
/*
 * Brief               <This service causes the  termination of the calling task. After
                        termination of the calling task  a succeeding task <TaskID> is
                        activated>
 * ServiceId           <0xe0>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <StatusType:>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID);

/******************************************************************************/
/*
 * Brief               <If a higher-priority task is ready , the internal resource
 *                      of the task is released, the current task is put into the
 *                      ready  state, its context is saved and the highe r-priority
 *                      task is executed. Otherwise the calling task is continued.>
 * ServiceId           <0xe1>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) Schedule(void);

/******************************************************************************/
/*
 * Brief               <GetTaskID  returns the information about the TaskID of
 *                      the task which is currently  running>
 * ServiceId           <0xe2>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID);

/******************************************************************************/
/*
 * Brief               <Returns the state of a task (running, ready, waiting,
 *                      suspended)at the time of calling GetTaskState.>
 * ServiceId           <0xe3>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetTaskState(TaskType TaskID, TaskStateRefType State);
#endif /* CFG_TASK_MAX > 0U */

#if (CFG_STD_RESOURCE_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <This call serves to enter critical sections in the code
 *                      that are assigned to the resource referenced by <ResID>.
 *                      A critical section shall always be left using ReleaseResource.>
 * ServiceId           <0xea>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetResource(ResourceType ResID);

/******************************************************************************/
/*
 * Brief               <ReleaseResource  is the counterpart of  GetResource  and
 *                      serves to leave critical sections in the code that are
 *                      assigned to the resource referenced by <ResID>.>
 * ServiceId           <0xeb>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResID);
#endif /* CFG_STD_RESOURCE_MAX > 0U */

#if (CFG_EXTENDED_TASK_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <The events of task <TaskID> are set according to the event
 *                      mask <Mask>. Calling SetEvent causes the task <TaskID> to
 *                      be transferred to the  ready  state, if it was waiting for
 *                      at least one of the events specified in <Mask>.>
 * ServiceId           <0xec>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask);

/******************************************************************************/
/*
 * Brief                <Asynchronous version of the SetEvent() function.>
 * Service ID           <0xec>
 * Sync/Async           <Asynchronous>
 * Reentrancy           <Reentrant>
 * param-TaskID[in]     <Reference to the task for which one or several events are to be set.>
 * param-Mask[in]       <Mask of the events to be set>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) SetEventAsyn(TaskType TaskID, EventMaskType Mask);

/******************************************************************************/
/*
 * Brief               <The events of the extended task calling ClearEvent are
 *                      cleared according to the event mask <Mask>.>
 * ServiceId           <0xed>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask);

/******************************************************************************/
/*
 * Brief               <This service returns the current state of all event bits
 *                      of the task <TaskID>, not the events that the task is
 *                      waiting for.>
 * ServiceId           <0xee>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID, EventMaskRefType Event);

/******************************************************************************/
/*
 * Brief               <The state of the calling task is set to waiting, unless
 *                      at least one of the events specified in <Mask> has
 *                      already been set.>
 * ServiceId           <0xef>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask);

/******************************************************************************/
/*
 * Brief               <The state of the calling task is set to waiting, must
 *                      all the events specified in <Mask> has already been set.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) WaitAllEvents(EventMaskType Mask);
#endif /* CFG_EXTENDED_TASK_MAX > 0U */

#if (CFG_ALARM_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <The system service GetAlarm returns the relative value in
 *                     ticks before the alarm <AlarmID> expires.>
 * ServiceId           <0xf1>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Tick);

/******************************************************************************/
/*
 * Brief               <The system service  GetAlarmBase  reads the alarm base
 *                      characteristics. The return value  <Info> is a structure
 *                      in which the information of data type AlarmBaseType
 *                      is stored.>
 * ServiceId           <0xf0>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);

/******************************************************************************/
/*
 * Brief               <The system service cancels the alarm <AlarmID>.>
 * ServiceId           <0xf4>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID);

/******************************************************************************/
/*
 * Brief               <The system service occupies the alarm <AlarmID> element.
 *                      After <increment> ticks have elapsed, the task assigned
 *                      to the alarm <AlarmID> is activated or  the assigned event
 *                      (only for extended tasks) is set or the alarm-callback
 *                      routine is called.>
 * ServiceId           <0xf2>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle);

/******************************************************************************/
/*
 * Brief               <The system service occupies the alarm <AlarmID> element.
 *                      When <start> ticks are reached, the task assigned to the
 *                      alarm <AlarmID> is activated or the assigned event (only
 *                      for extended tasks) is set or the alarm-callback routine
 *                      is called.>
 * ServiceId           <0xf3>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle);
#endif /* CFG_ALARM_MAX > 0U */

#if (CFG_COUNTER_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <>
 * ServiceId           <0x0f>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) IncrementCounter(CounterType CounterID);

/******************************************************************************/
/*
 * Brief               <>
 * ServiceId           <0x10>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetCounterValue(CounterType CounterID, TickRefType Value);

/******************************************************************************/
/*
 * Brief               <>
 * ServiceId           <0x11>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);
#endif /* CFG_COUNTER_MAX > 0U */

/******************************************************************************/
/*
 * Brief               <This service returns t he current application mode. It
 *                      may be used to write mode dependent code.>
 * ServiceId           <0xf5>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(AppModeType, OS_CODE) GetActiveApplicationMode(void);

/******************************************************************************/
/*
 * Brief               <This service disables  all interrupts for which the hardware
 *                      supports disabling. The state before is saved for the
 *                      EnableAllInterrupts call.>
 * ServiceId           <0xe5>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) DisableAllInterrupts(void);

/******************************************************************************/
/*
 * Brief               <This service restores the state saved by  DisableAllInterrupts.>
 * ServiceId           <0xe4>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) EnableAllInterrupts(void);

/******************************************************************************/
/*
 * Brief               <This service restores t he recognition status of all
 *                      interrupts saved by the  SuspendAllInterrupts service.>
 * ServiceId           <0xe6>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) ResumeAllInterrupts(void);

/******************************************************************************/
/*
 * Brief               <This service saves the re cognition status of all
 *                      interrupts and disables all interrupts for which the
 *                      hardware supports.>
disabling.
 * ServiceId           <0xe7>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) SuspendAllInterrupts(void);

/******************************************************************************/
/*
 * Brief               <>
 * ServiceId           <0xe8>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) ResumeOSInterrupts(void);

/******************************************************************************/
/*
 * Brief               <This service restores the recognition status of interrupts
 *                     saved by the SuspendOSInterrupts service.>
 * ServiceId           <0xe9>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) SuspendOSInterrupts(void);

/******************************************************************************/
/*
 * Brief                <Enables the interrupt source by modifying the interrupt
 *                       controller registers. Additionally it may clear the
 *                       interrupt pending flag>
 * Service ID           <0x31>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <ISRID: The ID of a category 2 ISR.>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) EnableInterruptSource(ISRType ISRID, boolean ClearPending);

/******************************************************************************/
/*
 * Brief                <Disables the interrupt source by modifying the interrupt
 *                       controller registers.>
 * Service ID           <0x30>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <ISRID: The ID of a category 2 ISR.>
 * @param[in]           <ClearPending: Defines whether the pending flag shall be
 *                       cleared (TRUE) or not (FALSE).>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) DisableInterruptSource(ISRType ISRID);

/******************************************************************************/
/*
 * Brief                <Clears the interrupt pending flag by modifying the interrupt
 *                       controller registers.>
 * Service ID           <0x32>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * @param[in]           <ISRID: The ID of a category 2 ISR.>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>
 * PreCondition         <None>
 * CallByAPI            <None>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ClearPendingInterrupt(ISRType ISRID);

/******************************************************************************/
/*
 * Brief               <The user can call this  system service to start the
 *                      operating system in a specific mode.>
 * ServiceId           <0xf6>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) StartOS(AppModeType Mode);

/******************************************************************************/
/*
 * Brief               <The user can call this system service to abort the overall
 *                      system (e.g. emergency off).>
 * ServiceId           <0xf7>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) ShutdownOS(StatusType Error);

#if (CFG_SCHEDTBL_MAX > 0U)
#if ((OS_SC2 == CFG_SC) || (OS_SC4 == CFG_SC))
/******************************************************************************/
/*
 * Brief               <Start schedule table before getting sync counter.>
 * ServiceId           <0x0b>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) StartScheduleTableSynchron(ScheduleTableType ScheduleTableID);

/******************************************************************************/
/*
 * Brief               <Set sync counter value to schedule table.>
 * ServiceId           <0x0c>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID, value>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType value);

/******************************************************************************/
/*
 * Brief               <Stop schedule table explicit sync and set state to running.>
 * ServiceId           <0x0d>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) SetScheduleTableAsync(ScheduleTableType ScheduleTableID);
#endif /* OS_SC2 == CFG_SC || OS_SC4 == CFG_SC */

/******************************************************************************/
/*
 * Brief               <Stop schedule table and set state to stop.>
 * ServiceId           <0x09>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) StopScheduleTable(ScheduleTableType ScheduleTableID);

/******************************************************************************/
/*
 * Brief               <Start schedule table using abs tick value.>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID, Start>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start);

/******************************************************************************/
/*
 * Brief               <Start schedule table using relative tick value.>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID, Offset>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);

/******************************************************************************/
/*
 * Brief               <Set next schedule table of ScheduleTableID_From.>
 * ServiceId           <0x0a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID_From, ScheduleTableID_To>
 * Param-Name[out]     <StatusType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE)
    NextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To);

/******************************************************************************/
/*
 * Brief               <Get status of schedule table.>
 * ServiceId           <0x0e>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ScheduleTableID>
 * Param-Name[out]     <ScheduleStatus>
 * Param-Name[in/out]  <None>
 * Return              <StatusType>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE)
    GetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);
#endif /* CFG_SCHEDTBL_MAX > 0U */

/******************************************************************************/
/*
 * Brief               <Get ID of ISR.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <ISRType>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(ISRType, OS_CODE) GetISRID(void);

/******************************************************************************/
/*
 * Brief               <This hook routine is called  by the operating system  at
 *                      the end of a system service which return s StatusType not
 *                      equal E_OK. It is called before returning to the task level>
 * ServiceId           <0xf8>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
#if (TRUE == CFG_ERRORHOOK)
extern FUNC(void, OS_APPL_CODE) ErrorHook(StatusType Error);
#endif

/******************************************************************************/
/*
 * Brief               <This hook routine is  called by the operat ing system before
 *                      executing a new task, but after t he transition of the task to
 *                      the running state (to allow evaluation of the TaskID by
 *                      GetTaskID).>
 * ServiceId           <0xf9>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
#if (TRUE == CFG_PRETASKHOOK)
extern FUNC(void, OS_APPL_CODE) PreTaskHook(void);
#endif

/******************************************************************************/
/*
 * Brief               <This hook routine is called by the operating system after
 *                      executing the current task, but before leaving the task's
 *                      running state (to allow evaluation of the TaskID by
 *                      GetTaskID).>
 * ServiceId           <0xfa>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
#if (TRUE == CFG_POSTTASKHOOK)
extern FUNC(void, OS_APPL_CODE) PostTaskHook(void);
#endif

/******************************************************************************/
/*
 * Brief               <This hook routine is called  by the operating system at
 *                      the end of the operating system in itialisation and before
 *                      the scheduler is running. At this time the application
 *                      can initialise device drivers etc.>
 * ServiceId           <0xfb>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
#if (TRUE == CFG_STARTUPHOOK)
extern FUNC(void, OS_APPL_CODE) StartupHook(void);
#endif

/******************************************************************************/
/*
 * Brief               <This hook routine is ca lled by the operating system when
 *                      the OS service ShutdownOS  has been called. This routine is
 *                      called during the operating system shut down.>
 * ServiceId           <0xfc>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
#if (TRUE == CFG_SHUTDOWNHOOK)
extern FUNC(void, OS_APPL_CODE) ShutdownHook(StatusType Error);
#endif

/******************************************************************************/
/*
 * Brief               <This hook routine is called by the operating system when
 *                      the OS service protection functions.>
 * ServiceId           <0xda>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
#if ((OS_SC2 == CFG_SC) || (OS_SC3 == CFG_SC) || (OS_SC4 == CFG_SC))
#if (TRUE == CFG_PROTECTIONHOOK)
extern FUNC(ProtectionReturnType, OS_CODE) ProtectionHook(StatusType Fatalerror);
#endif
#endif

#if (CFG_OSAPPLICATION_MAX > 0)
/******************************************************************************/
/*
 * Brief               <This service determines the currently running
                        OS-Application (a unique identifierhas to be
                        allocated to each application)>
 * Service ID          <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <OS-Application>
                       <INVALID_OSAPPLICATION>
 * Caveats             <None>
 * Configuration       <SC3 and SC4>
 */
/******************************************************************************/
extern FUNC(ApplicationType, OS_CODE) GetApplicationID(void);

/******************************************************************************/
/*
 * Brief               <This service determines the currently running
 *                      OS-Application (a unique identifier has to be
 *                      allocated to each application)>
 * Service ID          <0x27>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Return              <OS-Application id>
 * PreCondition        <SC3 and SC4>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID(void);

/******************************************************************************/
/*
 * Brief               <This service sets the own state of an OS-Application
 *                      from APPLICATION_RESTARTING to APPLICATION_ACCESSIBLE.>
 * Service ID          <0x13>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Return              <StatusType>
 * PreCondition        <SC3 and SC4>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) AllowAccess(void);

/******************************************************************************/
/*
 * Brief               <This service returns the current state of an OS-Application.>
 * Service ID          <0x14>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Return              <StatusType>
 * PreCondition        <SC3 and SC4>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetApplicationState(ApplicationType Application, ApplicationStateRefType Value);

/******************************************************************************/
/*
 * Brief               <This service determines if the OS-Applications,
                        given by ApplID, is allowed to use the IDs of a
                        Task, ISR, Resource,Counter, Alarm or Schedule
                        Table in API calls.>
 * Service ID          <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          < Reentrant>
 * param-Name[in]      <ApplID>
                       <ObjectType>
                       <...>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <ACCESS>
                       <NO_ACCESS>
 * Caveats             <None>
 * Configuration       <SC3 and SC4>
 */
/******************************************************************************/
extern FUNC(ObjectAccessType, OS_CODE)
    CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, AppObjectId ObjectID);

/******************************************************************************/
/*
 * Brief               <This service determines to which OS-Application
                        a given Task, ISR, Resource, Counter, Alarm or
                        Schedule Table belongs>
 * Service ID          <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * param-Name[in]      <ObjectType>
                       <...>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <OS-Application>
                       <INVALID_APPLICATION>
 * Cavests             <None>
 * Configuration       <SC3 and SC4>
 */
/******************************************************************************/
extern FUNC(ApplicationType, OS_CODE) CheckObjectOwnership(ObjectTypeType ObjectType, AppObjectId ObjectID);

/******************************************************************************/
/*
 * Brief               <Terminate Application>
 * ServiceId           <0x12>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Yes>
 * Param-Name[in]      <RestartOption>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <E_OS_CALLEVEL>
 *                     <E_OS_VALUE>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
FUNC(StatusType, OS_CODE) TerminateApplication(ApplicationType Application, RestartType RestartOption);
#endif /* CFG_OSAPPLICATION_MAX > 0 */

#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
/******************************************************************************/
/*
 * Brief               <This service determines some ISR can or not access some memory range>
 * Service ID          <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * param-Name[in]      <ISRID>
 *                     <Address>
 *                     <Size>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <NO_ACCESS>
                       <ACCESS>
 * Caveats             <None>
 * Configuration       <SC3 and SC4>
 */
/******************************************************************************/
extern FUNC(AccessType, OS_CODE)
    CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);

/******************************************************************************/
/*
 * Brief               <This service determines some task can or not access some memory range>
 * Service ID          <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * param-Name[in]      <TaskID>
 *                     <Address>
 *                     <Size>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <NO_ACCESS>
                       <ACCESS>
 * Caveats             <None>
 * Configuration       <SC3 and SC4>
 */
/******************************************************************************/
extern FUNC(AccessType, OS_CODE)
    CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
#endif /* TRUE == CFG_MEMORY_PROTECTION_ENABLE */

#if (CFG_TRUSTED_SYSTEM_SERVICE_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <This service call trusted function>
 * Service ID          <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * param-Name[in]      <FunctionIndex>
 *                     <FunctionParams>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <E_OK>
                       <E_OS_SERVICEID>
 * Caveats             <None>
 * Configuration       <SC3 and SC4>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE)
    CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
#endif

#if (CFG_SPINLOCK_MAX > 0U)
/******************************************************************************/
/*
 * Brief               <GetSpinlock>
 * ServiceId           <0x19>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <SpinlockId>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <StatusType>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) GetSpinlock(SpinlockIdType SpinlockId);

/******************************************************************************/
/*
 * Brief               <ReleaseSpinlock>
 * ServiceId           <0x1a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <SpinlockId>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <StatusType>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ReleaseSpinlock(SpinlockIdType SpinlockId);

/******************************************************************************/
/*
 * Brief               <TryToGetSpinlock>
 * ServiceId           <0x1b>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <SpinlockId>
 * Param-Name[out]     <Success>
 * Param-Name[in/out]  <None>
 * Return              <StatusType>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) TryToGetSpinlock(SpinlockIdType SpinlockId, TryToGetSpinlockType* Success);
#endif /* CFG_SPINLOCK_MAX > 0U */

/******************************************************************************/
/*
 * Brief               <The function starts the core specified by the CoreID. >
 * Service ID          <0x17>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * param-CoreID[in]    <Reference to the core>
 * Param-Status[out]   <Return value of the function>
 * return              <StatusType>
 * PreCondition        <Not support calling the API after calling StartOS.>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) StartCore(CoreIdType CoreID, StatusType* Status);

/******************************************************************************/
/*
 * Brief               <The function starts the core specified by the parameter
 *                      CoreID. It is allowed to call this function after StartOS().>
 * Service ID          <0x18>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * param-CoreID[in]    <Reference to the core>
 * Param-Status[out]   <Return value of the function>
 * return              <StatusType>
 * PreCondition        <None>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) StartNonAutosarCore(CoreIdType CoreID, StatusType* Status);

/******************************************************************************/
/*
 * Brief               <This API allows the caller to select the idle mode
 *                      action which is performed during idle time of the OS>
 * Service ID          <0x1d>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * param-CoreID[in]    <selects the core which idle mode is set>
 * param-IdleMode[in]  <the mode which shall be performed during idle time>
 * return              <StatusType, Return result of the function>
 * PreCondition        <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ControlIdle(CoreIdType CoreID, IdleModeType IdleMode);

/******************************************************************************/
/*
 * Brief               <The function returns the number of cores activated by
 *                      the StartCore function.>
 * Service ID           <0x15>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * return              <Number of cores activated by the StartCore function.>
 * PreCondition        <None>
 */
/******************************************************************************/
extern FUNC(uint32, OS_CODE) GetNumberOfActivatedCores(void);

/******************************************************************************/
/*
 * Brief               <The function returns a unique core identifier.>
 * Service ID           <0x16>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * return              <CoreIdType, The return value is the unique ID of the core.>
 * PreCondition        <None>
 */
/******************************************************************************/
extern FUNC(CoreIdType, OS_CODE) GetCoreID(void);

/******************************************************************************/
/*
 * Brief               <After this service the OS on all AUTOSAR cores is shut down.>
 * Service ID           <0x1c>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * param-Error[in]     <needs to be a valid error code supported by the AUTOSAR OS.>
 * return              <None>
 * PreCondition        <Allowed at TASK and ISR level and internally by the OS.>
 */
/******************************************************************************/
extern FUNC(void, OS_CODE) ShutdownAllCores(StatusType Error);

#if (CFG_PERIPHERAL_MAX > 0U)
/******************************************************************************/
/*
 * Brief                <ReadPeripheral8>
 * Service ID           <0x28>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ReadPeripheral8(AreaIdType Area, const uint8* Address, uint8* ReadValue);

/******************************************************************************/
/*
 * Brief                <ReadPeripheral16>
 * Service ID           <0x29>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ReadPeripheral16(AreaIdType Area, const uint16* Address, uint16* ReadValue);

/******************************************************************************/
/*
 * Brief                <ReadPeripheral32>
 * Service ID           <0x2a>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ReadPeripheral32(AreaIdType Area, const uint32* Address, uint32* ReadValue);

/******************************************************************************/
/*
 * Brief                <WritePeripheral8>
 * Service ID           <0x2b>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) WritePeripheral8(AreaIdType Area, uint8* Address, uint8 WriteValue);

/******************************************************************************/
/*
 * Brief                <WritePeripheral16>
 * Service ID           <0x2c>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) WritePeripheral16(AreaIdType Area, uint16* Address, uint16 WriteValue);

/******************************************************************************/
/*
 * Brief                <WritePeripheral32>
 * Service ID           <0x2d>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) WritePeripheral32(AreaIdType Area, uint32* Address, uint32 WriteValue);

/******************************************************************************/
/*
 * Brief                <ModifyPeripheral8>
 * Service ID           <0x2e>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ModifyPeripheral8(AreaIdType Area, uint8* Address, uint8 Clearmask, uint8 Setmask);

/******************************************************************************/
/*
 * Brief                <ModifyPeripheral16>
 * Service ID           <0x35>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ModifyPeripheral16(AreaIdType Area, uint16* Address, uint16 Clearmask, uint16 Setmask);

/******************************************************************************/
/*
 * Brief                <ModifyPeripheral32>
 * Service ID           <0x2f>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Reentrant>
 * return               <StatusType>
 * PreCondition         <None>
 * CallByAPI            <>
 * REQ ID               <None>
 */
/******************************************************************************/
extern FUNC(StatusType, OS_CODE) ModifyPeripheral32(AreaIdType Area, uint32* Address, uint32 Clearmask, uint32 Setmask);
#endif

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* OS_H */

/*=======[E N D   O F   F I L E]==============================================*/
