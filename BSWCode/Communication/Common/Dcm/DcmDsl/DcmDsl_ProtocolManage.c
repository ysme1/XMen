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

/******************************* references ************************************/
#include "Dcm_Internal.h"

/********************************************************
***************Resource statement************************
********************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
VAR(Dcm_ProtocolCtrlType, DCM_VAR_NOINIT) Dcm_ProtocolCtrl[DCM_DSLPROTOCOLROW_NUM_MAX];
/*Protocol control block*/
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
/********************/

/*******************public functions******************************/
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
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) DslInternal_InitProtocolCtrl(uint8 ProtocolCtrlId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    uint8 Index;
    boolean Flag = FALSE;
    const Dcm_DspSessionRowType* pSessionRow;
    uint8 SessionRow_Num;
#endif

    SchM_Enter_Dcm(Dcm_ProtocolCtrl);
    Dcm_ProtocolCtrl[ProtocolCtrlId].ProtocolId = DCM_INVALID_UINT8;
    Dcm_ProtocolCtrl[ProtocolCtrlId].ProtocolPri = DCM_INVALID_UINT8;
    Dcm_ProtocolCtrl[ProtocolCtrlId].ProtocolPreemptTime = DCM_INVALID_UINT32;
    Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex = DCM_INVALID_UINT8;
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2ServerMax = 50UL;       /* ms converted to tick */
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2StarServerMax = 5000UL; /* ms converted to tick */
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2ServerMin = 0UL;
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2StarServerMin = 0UL;
    Dcm_ProtocolCtrl[ProtocolCtrlId].S3Server = 5000UL; /* ms converted to tick */
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    SessionRow_Num = Dcm_DspCfg.pDcm_DspSession->DcmDspSessionRow_Num;
    for (Index = 0; (Index < SessionRow_Num) && (FALSE == Flag); Index++)
    {
        pSessionRow = &(Dcm_DspCfg.pDcm_DspSession->pDcmDspSessionRow)[Index];
        if (DCM_DEFAULT_SESSION == pSessionRow->DcmDspSessionLevel)
        {
            /*in DcmDspSessionRow,find the default session*/
            Flag = TRUE;
            Dcm_ProtocolCtrl[ProtocolCtrlId].P2ServerMax = pSessionRow->DcmDspSessionP2ServerMax;
            Dcm_ProtocolCtrl[ProtocolCtrlId].P2StarServerMax = pSessionRow->DcmDspSessionP2StarServerMax;
        }
    }
#endif
    Dcm_ProtocolCtrl[ProtocolCtrlId].Dcm_ProtocolState = DCM_PROTOCOL_INVALID;
    SchM_Exit_Dcm(Dcm_ProtocolCtrl);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) DslInternal_InitConnectionCtrl(uint8 ConnectionCtrlId)
{
    if (ConnectionCtrlId < DCM_CONNECTION_NUM)
    {
        SchM_Enter_Dcm(Dcm_ConnectionCtrl);
        Dcm_ConnectionCtrl[ConnectionCtrlId].Dcm_ConnectionCfgIndex = DCM_INVALID_UINT8;
        Dcm_ConnectionCtrl[ConnectionCtrlId].Dcm_ConnectionActive = FALSE;
        SchM_Exit_Dcm(Dcm_ConnectionCtrl);
    }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
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
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE) DslInternal_ProtocolStart(uint8 ProtocolCtrlId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    boolean Flag;
    uint8 Index;
    uint8 NotOkNum = 0u;
    uint8 NotAllowedNum = 0u;
    Dcm_ProtocolType ProtocolIdx;
    Std_ReturnType ret = E_OK;

    if (DCM_PROTOCOL_INVALID == Dcm_ProtocolCtrl[ProtocolCtrlId].Dcm_ProtocolState)
    {
        ProtocolIdx = Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId].DcmDslProtocolID;
        Flag = FALSE;
        for (Index = 0; (Index < Dcm_DslCfg.DCMCallBackDcmRequest_PortNum) && (FALSE == Flag); Index++)
        {
            if (NULL_PTR == Dcm_DslCfg.pDcmDslCallback_DCMRequestService[Index].StartProtocol)
            {
                Flag = TRUE;
            }
            else
            {
                /*Notify the application, Start Protocol*/
                ret = (*(Dcm_DslCfg.pDcmDslCallback_DCMRequestService[Index].StartProtocol))(ProtocolIdx);
                switch (ret)
                {
                case E_OK:
                    break;
                case E_PROTOCOL_NOT_ALLOWED:
                    NotAllowedNum++;
                    break;
                case E_NOT_OK:
                    NotOkNum++;
                    break;
                default:
                    NotOkNum++;
                    break;
                }
            }
        }
        if ((TRUE == Flag) || (0u != NotOkNum))
        {
            ret = E_NOT_OK;
        }
        else if (0u != NotAllowedNum)
        {
            /*Application does not allow Start Protocol.*/
            ret = E_PROTOCOL_NOT_ALLOWED;
        }
        else
        {
            SchM_Enter_Dcm(Dcm_ProtocolCtrl);
            Dcm_ProtocolCtrl[ProtocolCtrlId].Dcm_ProtocolState = DCM_PROTOCOL_VALID;
            SchM_Exit_Dcm(Dcm_ProtocolCtrl);
            /*Save the valid protocol ID number*/
            SchM_Enter_Dcm(Dcm_MkCtrl);
            Dcm_MkCtrl.Dcm_ActiveProtocolCfgCtrlId = ProtocolCtrlId;
            SchM_Exit_Dcm(Dcm_MkCtrl);
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
            SchM_Enter_Dcm(Dcm_SesCtrl);
            Dcm_SesCtrl.Dcm_NewSes = DCM_DEFAULT_SESSION;
            SchM_Exit_Dcm(Dcm_SesCtrl);
            DslInternal_SesRefresh(Dcm_SesCtrl.Dcm_NewSes);
            (void)SchM_Switch_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
            ret = E_OK;
        }
    }
    else
    {
        /*protocol is already started*/
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

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
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE) DslInternal_ProtocolStop(uint8 ProtocolCtrlId)
{
    boolean Flag;
    uint8 Index;
    uint8 NotOkNum = 0u;
    uint8 NotAllowedNum = 0u;
    Dcm_ProtocolType ProtocolIdx;
    Std_ReturnType ret = E_OK;

    if (DCM_PROTOCOL_VALID == Dcm_ProtocolCtrl[ProtocolCtrlId].Dcm_ProtocolState)
    {
        ProtocolIdx = Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId].DcmDslProtocolID;
        Flag = FALSE;
        for (Index = 0; (Index < Dcm_DslCfg.DCMCallBackDcmRequest_PortNum) && (FALSE == Flag); Index++)
        {
            if (NULL_PTR == Dcm_DslCfg.pDcmDslCallback_DCMRequestService[Index].StopProtocol)
            {
                Flag = TRUE;
            }
            else
            {
                /*Notify the application, Stop Protocol*/
                ret = (*(Dcm_DslCfg.pDcmDslCallback_DCMRequestService[Index].StopProtocol))(ProtocolIdx);
                switch (ret)
                {
                case E_OK:
                    break;
                case E_PROTOCOL_NOT_ALLOWED:
                    NotAllowedNum++;
                    break;
                case E_NOT_OK:
                    NotOkNum++;
                    break;
                default:
                    NotOkNum++;
                    break;
                }
            }
        }
        if ((TRUE == Flag) || (0u != NotOkNum))
        {
            ret = E_NOT_OK;
        }
        else if (0u != NotAllowedNum)
        {
            /*Application does not allow Stop Protocol.*/
            ret = E_PROTOCOL_NOT_ALLOWED;
        }
        else
        {
            SchM_Enter_Dcm(Dcm_ProtocolCtrl);
            Dcm_ProtocolCtrl[ProtocolCtrlId].Dcm_ProtocolState = DCM_PROTOCOL_INVALID;
            SchM_Exit_Dcm(Dcm_ProtocolCtrl);
            ret = E_OK;
        }
    }
    else
    {
        /*protocol is not started*/
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

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
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
/* PRQA S 1532++ */ /* MISRA Rule 8.7 */
FUNC(void, DCM_CODE) DslInternal_SetProtocolLinkLayerTimer(uint32 P2ServerTimer, uint32 P2StarServerTimer)
/* PRQA S 1532-- */ /* MISRA Rule 8.7 */
{
    uint8 Num;
    uint8 ProtocolCtrlId;
    uint32 P2ServerTime;
    uint32 P2StarServerTime;
    uint32 P2ServerTimerBak;
    uint32 P2StarServerTimerBak;
    uint32 P2ServerTimerLimit;
    uint32 P2StarServerTimerLimit;

    P2ServerTimerBak = P2ServerTimer;
    P2StarServerTimerBak = P2StarServerTimer;

    Num = Dcm_DslCfg.pDcmDslProtocol->DcmDslProtocolRow_Num;
    for (ProtocolCtrlId = 0; ProtocolCtrlId < Num; ProtocolCtrlId++)
    {
        P2ServerTime = P2ServerTimerBak;
        P2StarServerTime = P2StarServerTimerBak;
        P2ServerTimerLimit = Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId].DcmTimStrP2ServerAdjust;
        P2StarServerTimerLimit =
            Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId].DcmTimStrP2StarServerAdjust;

        if (P2ServerTime > P2ServerTimerLimit)
        {
            P2ServerTime = P2ServerTime - P2ServerTimerLimit;
        }
        if (P2StarServerTime > P2StarServerTimerLimit)
        {
            P2StarServerTime = P2StarServerTime - P2StarServerTimerLimit;
        }
        DslInternal_SetProtocolTimer(ProtocolCtrlId, P2ServerTime, P2StarServerTime);
    }
}

FUNC(void, DCM_CODE)
DslInternal_SetProtocolTimer(uint8 ProtocolCtrlId, uint32 P2ServerTimer, uint32 P2StarServerTimer)
{
    SchM_Enter_Dcm(Dcm_ProtocolCtrl);
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2ServerMax = P2ServerTimer;
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2StarServerMax = P2StarServerTimer;
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2ServerMin = 0UL;
    Dcm_ProtocolCtrl[ProtocolCtrlId].P2StarServerMin = 0UL;
    Dcm_ProtocolCtrl[ProtocolCtrlId].S3Server = 5000UL; /* ms converted to tick */
    SchM_Exit_Dcm(Dcm_ProtocolCtrl);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
