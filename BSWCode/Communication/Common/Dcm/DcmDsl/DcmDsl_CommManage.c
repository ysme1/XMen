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

/*=======[I N C L U D E S]====================================================*/
#include "Dcm_Internal.h"

/*******************************************************
 *********************Resource define*******************
 ********************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
VAR(Dcm_CommCtrlType, DCM_VAR_NOINIT) Dcm_CommCtrl[DCM_MAINCONNECTION_NUM];
/*Diagnostic Communication Control*/
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"

/****************************** implementations ********************************/
/*************************************************************************/
/*
 * Brief               <initialization of Comm Submodule>
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
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) DslInternal_InitComMCtrl(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    uint8 index;
    for (index = 0; index < DCM_MAINCONNECTION_NUM; index++)
    {
        SchM_Enter_Dcm(Dcm_CommCtrl);
        Dcm_CommCtrl[index].Dcm_CommState = DCM_COMM_NO_COMMUNICATION;
        Dcm_CommCtrl[index].Dcm_ActiveDiagnostic = DCM_COMM_ACTIVE;
        Dcm_CommCtrl[index].DcmDslProtocolComMChannelId =
            Dsl_Protocol_MainConnectionCfg[index].DcmDslProtocolComMChannelId;
        SchM_Exit_Dcm(Dcm_CommCtrl);
    }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/*************************************************************************/
/*
 * Brief               <ComM module notice DCM modules,
 * network communication mode is DCM_COMM_NO_COMMUNICATION>
 * ServiceId           <0x21>
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
#define DCM_START_SEC_DCMCOMMNOCOMMODEENTERED_CALLBACK_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(uint8 NetworkId)
{
    uint8 index;

#if (STD_ON == DCM_DEV_ERROR_DETECT)
    if (DCM_ON != Dcm_MkCtrl.Dcm_MkState)
    {
        DCM_DET_REPORTERROR(DCM_COMM_NOCOMMODEENTERED, DCM_E_UNINIT);
    }
    else
#endif
    {
        for (index = 0; index < DCM_MAINCONNECTION_NUM; index++)
        {
            if (Dcm_CommCtrl[index].DcmDslProtocolComMChannelId == NetworkId)
            {
                SchM_Enter_Dcm(Dcm_CommCtrl);
                Dcm_CommCtrl[index].Dcm_CommState = DCM_COMM_NO_COMMUNICATION;
                SchM_Exit_Dcm(Dcm_CommCtrl);
            }
        }
    }
}
#define DCM_STOP_SEC_DCMCOMMNOCOMMODEENTERED_CALLBACK_CODE
#include "Dcm_MemMap.h"

/*************************************************************************/
/*
 * Brief               <ComM module notice DCM modules, network
 * communication mode is DCM_COMM_SILENT_COMMUNICATION>
 * ServiceId           <0x22>
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
#define DCM_START_SEC_DCMCOMMSILENTCOMMODEENTERED_CALLBACK_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(uint8 NetworkId)
{
    uint8 index;

#if (STD_ON == DCM_DEV_ERROR_DETECT)
    if (DCM_ON != Dcm_MkCtrl.Dcm_MkState)
    {
        DCM_DET_REPORTERROR(DCM_COMM_SILENTCOMMODEENTERED, DCM_E_UNINIT);
    }
    else
#endif
    {
        for (index = 0; index < DCM_MAINCONNECTION_NUM; index++)
        {
            if (Dcm_CommCtrl[index].DcmDslProtocolComMChannelId == NetworkId)
            {
                SchM_Enter_Dcm(Dcm_CommCtrl);
                Dcm_CommCtrl[index].Dcm_CommState = DCM_COMM_SILENT_COMMUNICATION;
                SchM_Exit_Dcm(Dcm_CommCtrl);
            }
        }
    }
}
#define DCM_STOP_SEC_DCMCOMMSILENTCOMMODEENTERED_CALLBACK_CODE
#include "Dcm_MemMap.h"

/*************************************************************************/
/*
 * Brief               <ComM module notice DCM modules,
 * network communication mode is DCM_COMM_FULL_COMMUNICATION>
 * ServiceId           <0x23>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <>
 */
/*************************************************************************/
#define DCM_START_SEC_DCMCOMMFULLCOMMODEENTERED_CALLBACK_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(uint8 NetworkId)
{
    uint8 index;

#if (STD_ON == DCM_DEV_ERROR_DETECT)
    if (DCM_ON != Dcm_MkCtrl.Dcm_MkState)
    {
        DCM_DET_REPORTERROR(DCM_COMM_FULLCOMMODEENTERED, DCM_E_UNINIT);
    }
    else
#endif
    {
        for (index = 0; index < DCM_MAINCONNECTION_NUM; index++)
        {
            if (Dcm_CommCtrl[index].DcmDslProtocolComMChannelId == NetworkId)
            {
                SchM_Enter_Dcm(Dcm_CommCtrl);
                Dcm_CommCtrl[index].Dcm_CommState = DCM_COMM_FULL_COMMUNICATION;
                SchM_Exit_Dcm(Dcm_CommCtrl);
            }
        }
    }
}
#define DCM_STOP_SEC_DCMCOMMFULLCOMMODEENTERED_CALLBACK_CODE
#include "Dcm_MemMap.h"
