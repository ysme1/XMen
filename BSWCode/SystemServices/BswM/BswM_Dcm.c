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
 **  FILENAME    : BswM_Dcm.c                                                  **
 **                                                                            **
 **  Created on  : 2020-03-24                                                  **
 **  Author      : qinchun.yang                                                **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "BswM_Dcm.h"
#if (BSWM_DCM_ENABLED == STD_ON)
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"
/*Initialize BswMDcmComModeRequest request port*/
FUNC(void, BSWM_DCM_CODE)
BswM_InitDcmRequestPorts(void)
{
    P2CONST(BswM_ModeRqstPortPCCfgType, AUTOMATIC, BSWM_CONST) modeRqstPCfgPtr;
    P2CONST(BswM_ModeRqstPortRuntimeType, AUTOMATIC, BSWM_VAR_CLEARED) modeRqstPtr;
    P2CONST(BswM_PartitionPCCfgType, TYPEDEF, BSWM_CONST) bswmPartPCCfgs;
    NetworkHandleType numOfDcmCh;
    NetworkHandleType idx;
    ApplicationType partIdx;
    boolean result;

    result = BswM_GetPartitionIdx(&partIdx);
    if ((boolean)TRUE == result)
    {
        bswmPartPCCfgs = &(BswM_RuntimeStatus.bswmPartPCCfgs[partIdx]);
        modeRqstPCfgPtr = bswmPartPCCfgs->modeRqstPCCfg;
        modeRqstPtr = bswmPartPCCfgs->modeRqstPortRunPtr;
        numOfDcmCh = modeRqstPCfgPtr->numOfDcmComModeReq;
        for (idx = 0u; idx < numOfDcmCh; idx++)
        {
            if (NULL_PTR != modeRqstPCfgPtr->dcmInitMode)
            {
                modeRqstPtr->dcmComModeReqStatus[idx] = *(modeRqstPCfgPtr->dcmInitMode);
            }
            else
            {
                break;
            }
        }
    }
#if (BSWM_DEV_ERROR_DETECT == STD_ON)
    else
    {
        (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID, BSWM_API_ID_INIT, BSWM_E_INIT_FAILED);
    }
#endif /* BSWM_DEV_ERROR_DETECT == STD_ON */
}

/**
 * This function is called by the DCM in order to report an updated application.
 * Service ID: 0x14
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters(IN): NA
 * Parameters(INOUT): NA
 * Parameters(OUT): NA
 * Return value: NA
 */
FUNC(void, BSWM_DCM_CODE)
BswM_Dcm_ApplicationUpdated(void)
{
#if (BSWM_EVENT_RQSTPORT_ENABLE == STD_ON)
    P2CONST(BswM_EventRqstPortLCfgType, AUTOMATIC, BSWM_CONST) evRqstLCfgPtr;
    /* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
    P2VAR(BswM_EventRquestPortRuntimeType, AUTOMATIC, BSWM_VAR_CLEARED) evRqstPtr;
    /* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
    P2CONST(BswM_RuleLcCfgType, AUTOMATIC, BSWM_CONST) ruleLCfgPtr;
    P2CONST(BswM_PartitionPCCfgType, TYPEDEF, BSWM_CONST) bswmPartPCCfgs;
    P2CONST(BswM_PartitionLCfgType, TYPEDEF, BSWM_CONST) bswmPartLCfgs;
    BswM_RuleIndexType numOfRules;
    BswM_RuleIndexType idx;
    BswM_RuleIndexType ruleIdx;
    BswM_EventRqstPortIdxType evIdx;
    ApplicationType partIdx;
    boolean result;

#if (BSWM_DEV_ERROR_DETECT == STD_ON)
    if ((Std_ReturnType)E_OK == BswM_DetChkDcmUpdate())
#endif /* BSWM_DEV_ERROR_DETECT == STD_ON */
    {
        result = BswM_GetPartitionIdx(&partIdx);
        if ((boolean)TRUE == result)
        {
            bswmPartPCCfgs = &(BswM_RuntimeStatus.bswmPartPCCfgs[partIdx]);
            bswmPartLCfgs = &(BswM_RuntimeStatus.bswmPartLCfgs[partIdx]);
            evRqstPtr = bswmPartPCCfgs->eventRqstPortRunPtr;
            evIdx = *(bswmPartPCCfgs->evRqstPCCfg->dcmAppUpdateIndIdxPtr);
            evRqstPtr[evIdx] = BSWM_EVENT_IS_SET;
            evRqstLCfgPtr = bswmPartLCfgs->evRqstLCfg;
            if (BSWM_IMMEDIATE == evRqstLCfgPtr->dcmAppUpdate->process)
            {
                numOfRules = evRqstLCfgPtr->dcmAppUpdate->belongToRlueNum;
                ruleLCfgPtr = bswmPartLCfgs->ruleLCfg;
                for (idx = 0u; idx < numOfRules; idx++)
                {
                    ruleIdx = evRqstLCfgPtr->dcmAppUpdate->belongToRlue[idx];
                    if ((boolean)FALSE == ruleLCfgPtr[ruleIdx].isNestExe)
                    {
                        /* An Independent rule,to be evaluated each time applicable*/
                        BswM_ArbitrateRule(ruleIdx, partIdx);
                    }
                }
            }
        }
    }
#endif /* BSWM_EVENT_RQSTPORT_ENABLE == STD_ON */
}

/**
 * Function called by DCM to inform the BswM about the current state of the
 * communication mode.
 * Service ID: 0x06
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters(IN): Network, the communication channel that the diagnostic mode
 *                          corresponds to
 *                 RequestedMode, the requested diagnostic communication mode
 * Parameters(INOUT): NA
 * Parameters(OUT): NA
 * Return value: NA
 */
FUNC(void, BSWM_DCM_CODE)
BswM_Dcm_CommunicationMode_CurrentState(NetworkHandleType Network, Dcm_CommunicationModeType RequestedMode)
{
    P2CONST(BswM_ModeRqstPortPCCfgType, AUTOMATIC, BSWM_CONST) modeRqstPCfgPtr;
    P2CONST(BswM_ModeRqstPortLCfgType, AUTOMATIC, BSWM_CONST) modeRqstLCfgPtr;
    P2CONST(BswM_ModeRqstPortRuntimeType, AUTOMATIC, BSWM_VAR_CLEARED) modeRqstPtr;
    P2CONST(BswM_RuleLcCfgType, AUTOMATIC, BSWM_CONST) ruleLCfgPtr;
    P2CONST(BswM_PartitionPCCfgType, TYPEDEF, BSWM_CONST) bswmPartPCCfgs;
    P2CONST(BswM_PartitionLCfgType, TYPEDEF, BSWM_CONST) bswmPartLCfgs;
    BswM_RuleIndexType numOfRules;
    BswM_RuleIndexType idx;
    BswM_RuleIndexType ruleIdx;
    ApplicationType partIdx;
    boolean result;
    NetworkHandleType numOfDcmCh;
    NetworkHandleType chIdx;

#if (BSWM_DEV_ERROR_DETECT == STD_ON)
    if ((Std_ReturnType)E_OK == BswM_DetChkDcmModeCurState(RequestedMode))
#endif /* BSWM_DEV_ERROR_DETECT == STD_ON */
    {
        result = BswM_GetPartitionIdx(&partIdx);
        if ((boolean)TRUE == result)
        {
            bswmPartPCCfgs = &(BswM_RuntimeStatus.bswmPartPCCfgs[partIdx]);
            bswmPartLCfgs = &(BswM_RuntimeStatus.bswmPartLCfgs[partIdx]);
            modeRqstPCfgPtr = bswmPartPCCfgs->modeRqstPCCfg;
            modeRqstLCfgPtr = bswmPartLCfgs->modeRqstLCfg;
            numOfDcmCh = modeRqstPCfgPtr->numOfDcmComModeReq;
            for (chIdx = 0u; chIdx < numOfDcmCh; chIdx++)
            {
                if (Network == modeRqstLCfgPtr->dcmChRef[chIdx])
                {
                    modeRqstPtr = bswmPartPCCfgs->modeRqstPortRunPtr;
                    modeRqstPtr->dcmComModeReqStatus[chIdx] = RequestedMode;
                    if (BSWM_IMMEDIATE == modeRqstLCfgPtr->dcmComModeRqst[chIdx].process)
                    {
                        numOfRules = modeRqstLCfgPtr->dcmComModeRqst[chIdx].belongToRlueNum;
                        ruleLCfgPtr = bswmPartLCfgs->ruleLCfg;
                        for (idx = 0u; idx < numOfRules; idx++)
                        {
                            ruleIdx = modeRqstLCfgPtr->dcmComModeRqst[chIdx].belongToRlue[idx];
                            if ((boolean)FALSE == ruleLCfgPtr[ruleIdx].isNestExe)
                            {
                                /* An Independent rule,to be evaluated each time applicable*/
                                BswM_ArbitrateRule(ruleIdx, partIdx);
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

#if (BSWM_EVENT_RQSTPORT_ENABLE == STD_ON)
/*Get BswM_Dcm_ApplicationUpdated status*/
FUNC(BswM_EventRquestPortRuntimeType, BSWM_DCM_CODE)
BswM_GetDcmAppUpdatedStatus(void)
{
    P2CONST(BswM_PartitionPCCfgType, TYPEDEF, BSWM_CONST) bswmPartPCCfgs;
    BswM_EventRquestPortRuntimeType dcmAppStatus = BSWM_INVALID_U8;
    BswM_EventRqstPortIdxType evIdx;
    ApplicationType partIdx;
    boolean result;

    result = BswM_GetPartitionIdx(&partIdx);
    if ((boolean)TRUE == result)
    {
        bswmPartPCCfgs = &(BswM_RuntimeStatus.bswmPartPCCfgs[partIdx]);
        evIdx = *(bswmPartPCCfgs->evRqstPCCfg->dcmAppUpdateIndIdxPtr);
        dcmAppStatus = bswmPartPCCfgs->eventRqstPortRunPtr[evIdx];
    }
    return dcmAppStatus;
}
#endif /* BSWM_EVENT_RQSTPORT_ENABLE == STD_ON */

/*Get BswM_Dcm_CommunicationMode_CurrentState status*/
FUNC(Dcm_CommunicationModeType, BSWM_DCM_CODE)
BswM_GetDcmCurModeStatus(NetworkHandleType dcmChIdx)
{
    Dcm_CommunicationModeType dcmComMode = BSWM_INVALID_U8;
    ApplicationType partIdx;
    boolean result;

    result = BswM_GetPartitionIdx(&partIdx);
    if ((boolean)TRUE == result)
    {
        dcmComMode = BswM_RuntimeStatus.bswmPartPCCfgs[partIdx].modeRqstPortRunPtr->dcmComModeReqStatus[dcmChIdx];
    }
    return dcmComMode;
}
#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

#endif /* BSWM_DCM_ENABLED == STD_ON */
