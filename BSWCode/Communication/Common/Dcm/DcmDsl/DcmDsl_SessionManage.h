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
 **                                                                           **
 **  FILENAME    :                                                            **
 **                                                                           **
 **  Created on  : 2020/5/6 14:29:43                                          **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION :                                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

#ifndef DCMDSL_SESSIONMANAGE_H
#define DCMDSL_SESSIONMANAGE_H

/****************************** references *********************************/
#include "Dcm_Types.h"

#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
/****************************** declarations *********************************/
/*****************************************************************
 **********Session Management sub-function data structure*******
 *****************************************************************/
typedef enum
{
    DCM_S3TIMER_ON = 0,
    DCM_S3TIMER_OFF = 1
} Dcm_S3StateType;

typedef struct
{
    uint32 Dcm_S3CurTimer;
    uint32 Dcm_S3ExpiredTimer;   /*S3Timer,timeout Timer*/
    Dcm_S3StateType Dcm_S3State; /*S3timer status */
} Dcm_S3CtrlType;

typedef enum
{
    DCM_SESSION_DEFAULT = 0,  /*default session*/
    DCM_SESSION_UNDEFAULT = 1 /*undefault session*/
} Dcm_SesStateType;

typedef struct
{
    Dcm_SesCtrlType Dcm_ActiveSes; /*Module current session-state values;*/
    Dcm_SesCtrlType Dcm_NewSes;
    /*The session control value of the module to be changed;*/
    Dcm_S3CtrlType Dcm_S3Ctrl;         /*S3Timer control block*/
    Dcm_SesStateType Dcm_SessionState; /*DCM module session state*/
} Dcm_SesCtrlCBType;

/********************************************************
 *******************resource statement*******************
 ********************************************************/

extern VAR(Dcm_SesCtrlCBType, DCM_VAR_NOINIT) Dcm_SesCtrl; /*Session management control block*/

/*******************************************************************************
 **************Session Management sub-function function declaration*************
 *******************************************************************************/
/*************************************************************************/
/*
 * Brief               <The initialization of session management control block>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_InitSesCtrl(void);

/*************************************************************************/
/*
 * Brief               <start S3Timer>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_S3ServerStart(void);

/*************************************************************************/
/*
 * Brief               <stop S3Timer>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_S3ServerStop(void);

/*************************************************************************/
/*
 * Brief               <timeout of S3Timer>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_S3ServerTimeout(void);

/*************************************************************************/
/*
 * Brief               <Refresh session>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <NewSes:Session control state to be refreshed>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_SesRefresh(Dcm_SesCtrlType NewSes);

#endif

#endif /* DCMDSL_SESSIONMANAGE_H_ */
