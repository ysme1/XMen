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
#ifndef DCMDSL_PROTOCOLMANAGE_H
#define DCMDSL_PROTOCOLMANAGE_H
/*============================================================================*/

/****************************** references *********************************/
#include "Dcm_Types.h"
#include "Rte_Dcm_Type.h"

/****************************** declarations *********************************/
/*********************************************************
 *The operation of the protocol managment data structure
 *********************************************************/
typedef enum
{
    DCM_PROTOCOL_VALID = 1,  /*Protocol "valid" state*/
    DCM_PROTOCOL_INVALID = 0 /*Protocol "Invalid" state*/
} Dcm_ProtocolStateType;

typedef struct
{
    Dcm_ProtocolType ProtocolId;             /*The protocol ID number*/
    uint8 ProtocolPri;                       /*protocol priority*/
    uint8 MsgCtrlIndex;                      /*Message control block index number*/
    uint32 ProtocolPreemptTime;              /*protocol preempt time*/
    uint32 P2ServerMax;                      /*In the current session state P2ServerMax.*/
    uint32 P2ServerMin;                      /*In the current session state P2ServerMin.*/
    uint32 P2StarServerMax;                  /*In the current session state P2*ServerMax.*/
    uint32 P2StarServerMin;                  /*In the current session state P2*ServerMin.*/
    uint32 S3Server;                         /*S3Server value*/
    Dcm_ProtocolStateType Dcm_ProtocolState; /*Protocol state*/
} Dcm_ProtocolCtrlType;

/********************************************************
***************Resource statement************************
********************************************************/

extern VAR(Dcm_ProtocolCtrlType, DCM_VAR_NOINIT) Dcm_ProtocolCtrl[DCM_DSLPROTOCOLROW_NUM_MAX];
/*Protocol control block*/

/*************************************************************************/
/*
 * Brief               <Initializing the corresponding protocol control block>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:Protocol control block index number.>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <Dcm_init()>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_InitProtocolCtrl(uint8 ProtocolCtrlId);

extern FUNC(void, DCM_CODE) DslInternal_InitConnectionCtrl(uint8 ConnectionCtrlId);

/*************************************************************************/
/*
 * Brief               <protocal start>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:Protocol control block index number.>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DCM_CODE) DslInternal_ProtocolStart(uint8 ProtocolCtrlId);

/*************************************************************************/
/*
 * Brief               <protocal stop>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:Protocol control block index number.>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DCM_CODE) DslInternal_ProtocolStop(uint8 ProtocolCtrlId);

/*************************************************************************/
/*
 * Brief               <Set the module support each protocol link layer parameters of time>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <P2ServerTimer:
 *                      P2StarServerTimer:>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
extern FUNC(void, DCM_CODE) DslInternal_SetProtocolLinkLayerTimer(uint32 P2ServerTimer, uint32 P2StarServerTimer);

/*************************************************************************/
/*
 * Brief               <Set the the DCM module supports protocol
 * corresponding to the link layer time>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:Protocol control block index number;
 *                      P2ServerTimer:To be set P2ServerTimer;
 *                      P2StarServerTimer:To be set P2StarServerTimer; >
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
extern FUNC(void, DCM_CODE)
    DslInternal_SetProtocolTimer(uint8 ProtocolCtrlId, uint32 P2ServerTimer, uint32 P2StarServerTimer);

#endif /* DCMDSL_PROTOCOLMANAGE_H_ */
