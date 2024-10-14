
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
#include "UDS.h"

/****************************************************************
     UDS:DiagnosticSessionControl (10 hex) service
 ***************************************************************/
#if (STD_ON == DCM_UDS_SERVICE0X10_ENABLED)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE) DspInternalUDS0x10_SessionSubDeal(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    uint8 iloop,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret;
    uint8 MsgCtrlId;
    const Dcm_DspSessionRowType* pSessionRow = &Dcm_DspCfg.pDcm_DspSession->pDcmDspSessionRow[iloop];

    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;

    /*the SchM_Switch_DcmEcuReset need have Std_ReturnType to check NRC 0x22*/
    /* By this mode switch the DCM informs
     *  the BswM to prepare the jump to the bootloader.*/
    ret = SchM_Switch_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER);
    if (ret == E_NOT_OK)
    {
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else if (ret == E_OK)
    {
        if ((Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId].DcmSendRespPendOnTransToBoot == FALSE)
            && ((pSessionRow->DcmDspSessionForBoot == DCM_SYS_BOOT)
                || (pSessionRow->DcmDspSessionForBoot == DCM_OEM_BOOT)))
        {
            ret = Dcm_SetProgConditions(OpStatus, &ProgConditions);
            if (ret == E_OK)
            {
                /* By this mode switch the DCM informs
                 * the BswM to jump to the bootloader.*/
                (void)SchM_Switch_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
            }
            else if (ret == E_NOT_OK)
            {
                *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
            else if (ret == DCM_E_PENDING)
            {
                SchM_Enter_Dcm(Dcm_MsgCtrl);
                Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
                SchM_Exit_Dcm(Dcm_MsgCtrl);
            }
            else
            {
                /*idle*/
            }
        }
    }
    else
    {
        /*idle*/
    }

    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE) DspInternalUDS0x10_SessionDeal(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    uint8 iloop,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_OK;
    uint8 MsgCtrlId;
    Dcm_DspSessionForBootType DcmDspSessionForBoot;

    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    DcmDspSessionForBoot = Dcm_DspCfg.pDcm_DspSession->pDcmDspSessionRow[iloop].DcmDspSessionForBoot;
    if ((DcmDspSessionForBoot == DCM_OEM_BOOT) || (DcmDspSessionForBoot == DCM_OEM_BOOT_RESPAPP))
    {
        /*the SchM_Switch_DcmEcuReset need have Std_ReturnType to check NRC 0x22*/
        /* By this mode switch the DCM informs the BswM to
         * prepare the jump to the bootloader.*/
        ret = SchM_Switch_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER);
        if (ret == E_NOT_OK)
        {
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        }
        else if (ret == E_OK)
        {
            ret = DspInternalUDS0x10_SessionSubDeal(OpStatus, ProtocolCtrlId, iloop, ErrorCode);
        }
        else
        {
            /*idle*/
        }
    }
    else if ((DcmDspSessionForBoot == DCM_SYS_BOOT) || (DcmDspSessionForBoot == DCM_SYS_BOOT_RESPAPP))
    {
        /*the SchM_Switch_DcmEcuReset need have Std_ReturnType to check NRC 0x22*/
        /* By this mode switch the DCM informs
         *  the BswM to prepare the jump to the bootloader.*/
        ret = SchM_Switch_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER);
        if (ret == E_NOT_OK)
        {
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        }
        else if (ret == E_OK)
        {
            ret = DspInternalUDS0x10_SessionSubDeal(OpStatus, ProtocolCtrlId, iloop, ErrorCode);
        }
        else
        {
            /*idle*/
        }
    }
    else
    {
        /*idle*/
    }

    if (ret == E_OK)
    {
        /*check send NCR 0x78 */
        if (Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId].DcmSendRespPendOnTransToBoot == TRUE)
        {
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            if (OpStatus == DCM_PENDING)
            {
                ret = DCM_E_PENDING;
            }
            else
            {
                *ErrorCode = DCM_E_RESPONSE_PENDING;
                ret = E_NOT_OK;
            }
        }
        else
        {
            if ((DcmDspSessionForBoot != DCM_SYS_BOOT_RESPAPP) && (DcmDspSessionForBoot != DCM_OEM_BOOT_RESPAPP))
            {
                /*In case the ModeDeclarationGroupPrototype DcmEcuReset
                   is switched to mode JUMPTOBOOTLOADER or
                   JUMPTOSYSSUPPLIERBOOTLOADER, the configuration parameter
                   DcmSendRespPendOnTransToBoot is set to FALSE and the configuration
                   parameter DcmDspSessionForBoot is set to DCM_OEM_BOOT_RESPAPP or
                   DCM_SYS_BOOT_RESPAPP , the Dcm shall initiate the final response*/
            }
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE) Dcm_UDS0x10_ConditionCheck(
    uint8 ProtocolCtrlId,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, DCM_VAR) SesIndex,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint8 MsgCtrlId;
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    uint8 Subfunction;
    uint8 DspSessionRowNum;
    boolean Flag = FALSE;
    P2CONST(Dcm_DspSessionRowType, AUTOMATIC, DCM_APPL_CONST) pDspSessionRow;
    uint8 iloop;
#endif
    Std_ReturnType ret = E_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */

#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    /*session check,check whether the current session supports the request service*/
    ret = DsdInternal_SesCheck(ProtocolCtrlId, SID_DIAGNOSTIC_SESSION_CONTROL);
    if (E_NOT_OK == ret)
    {
        /*the current session does not support the request service,send NRC = 0x7F*/
        *ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
    }
#endif
#if (STD_ON == DCM_SECURITY_FUNC_ENABLED)
    if (E_OK == ret)
    {
        /*security check,check whether the current security supports the request service*/
        ret = DsdInternal_SecurityCheck(ProtocolCtrlId, SID_DIAGNOSTIC_SESSION_CONTROL);
        if (E_NOT_OK == ret)
        {
            /*the current security does not support the request service,send NRC = 0x33*/
            *ErrorCode = DCM_E_SECURITYACCESSDENIED;
        }
    }
#endif
    if (E_OK == ret)
    {
        /*if the required protocol is configured,get the index of runtime datum*/
        MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
        /*check the message length*/
        if (DCM_UDS_REQ_DATA_MINLENGTH > Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen)
        {
            /*the length of massage is not correct,send NRC 0x13*/
            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            ret = E_NOT_OK;
        }
    }
#if (STD_OFF == DCM_SESSION_FUNC_ENABLED)
    if (E_OK == ret)
    {
        /*if the session function is disabled,send NRC 0x12*/
        *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        ret = E_NOT_OK;
    }
#else
    if (E_OK == ret)
    {
        ret = Dcm_UdsSubServicesCheck(ProtocolCtrlId);
        Subfunction = Dcm_MsgCtrl[MsgCtrlId].Subfunction;
        DspSessionRowNum = Dcm_DspCfg.pDcm_DspSession->DcmDspSessionRow_Num;
        pDspSessionRow = Dcm_DspCfg.pDcm_DspSession->pDcmDspSessionRow;
        /*check whether the required session is configured*/
        for (iloop = 0; (iloop < DspSessionRowNum) && (FALSE == Flag); iloop++)
        {
            if (Subfunction == (pDspSessionRow[iloop].DcmDspSessionLevel))
            {
                Flag = TRUE;
                *SesIndex = iloop;
            }
        }
        /*if not configured,send NRC 0x12*/
        if ((E_NOT_OK == ret) || (FALSE == Flag))
        {
            *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            ret = E_NOT_OK;
        }
    }
#endif
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    if (E_OK == ret)
    {
        ret = DsdInternal_SubSesCheck(ProtocolCtrlId, SID_DIAGNOSTIC_SESSION_CONTROL);
        if (E_NOT_OK == ret)
        {
            /*the current session does not support the request sub service,send NRC = 0x7E*/
            *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
        }
    }
#endif
#if (STD_ON == DCM_SECURITY_FUNC_ENABLED)
    if (E_OK == ret)
    {
        /*security check,check whether the current security supports the request service*/
        ret = DsdInternal_SubSecurityCheck(ProtocolCtrlId, SID_DIAGNOSTIC_SESSION_CONTROL);
        if (E_NOT_OK == ret)
        {
            /*the current security does not support the request service,send NRC = 0x33*/
            *ErrorCode = DCM_E_SECURITYACCESSDENIED;
        }
    }
#endif
    if ((E_OK == ret) && (DCM_UDS0X10_REQ_DATA_LENGTH < Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen))
    {
        /*the length of massage is not correct,send NRC 0x13*/
        *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        ret = E_NOT_OK;
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/*******************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE)
Dcm_UDS0x10(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    uint8 MsgCtrlId;
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    uint8 SesIndex;
    uint8 Subfunction;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    P2CONST(Dcm_DspSessionRowType, AUTOMATIC, DCM_APPL_CONST)
    pDspSessionRow = Dcm_DspCfg.pDcm_DspSession->pDcmDspSessionRow;
#endif
    Std_ReturnType ret;
    uint8 iloop;
    const Dcm_DslBufferType* pDcmChannelCfg;
    const Dcm_DslProtocolRowType* pDcmDslProtocolRow = &Dcm_DslCfg.pDcmDslProtocol->pDcmDslProtocolRow[ProtocolCtrlId];
    const uint8 SessionRow_Num = Dcm_DspCfg.pDcm_DspSession->DcmDspSessionRow_Num;

    /*if the required protocol is configured,get the index of runtime datum*/
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    Subfunction = Dcm_MsgCtrl[MsgCtrlId].Subfunction;
    TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
    TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
    pDcmChannelCfg = &Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex];

    Offset = pDcmChannelCfg->offset;
    ret = Dcm_UDS0x10_ConditionCheck(ProtocolCtrlId, &SesIndex, ErrorCode);
#if ((STD_ON == DCM_SESSION_FUNC_ENABLED) || (STD_ON == DCM_SECURITY_FUNC_ENABLED))
    if (E_OK == ret)
    {
        ret = RTE_PreConditonCheck();
        if (E_OK != ret)
        {
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            ret = E_NOT_OK;
        }
    }
#endif
    if ((E_OK == ret) && (OpStatus == DCM_INITIAL))
    {
        SchM_Enter_Dcm(Dcm_SesCtrl);
        Dcm_SesCtrl.Dcm_NewSes = Subfunction;
        SchM_Exit_Dcm(Dcm_SesCtrl);
        /*assemble and send positive response*/
        /*check program request*/
        for (iloop = 0; iloop < SessionRow_Num; iloop++)
        {
            if ((Subfunction == pDspSessionRow[iloop].DcmDspSessionLevel)
                && (pDspSessionRow[iloop].DcmDspSessionForBoot != DCM_NO_BOOT))
            {
                ret = DspInternalUDS0x10_SessionDeal(OpStatus, ProtocolCtrlId, iloop, ErrorCode);
            }
        }
    }
    if ((E_OK == ret) && (OpStatus == DCM_PENDING) && (pDcmDslProtocolRow->DcmSendRespPendOnTransToBoot == TRUE))
    {
        for (iloop = 0; iloop < SessionRow_Num; iloop++)
        {
            if ((Subfunction == pDspSessionRow[iloop].DcmDspSessionLevel)
                && ((pDspSessionRow[iloop].DcmDspSessionForBoot == DCM_OEM_BOOT)
                    || (pDspSessionRow[iloop].DcmDspSessionForBoot == DCM_SYS_BOOT)))
            {
                ret = Dcm_SetProgConditions(OpStatus, &ProgConditions);
                if (ret == E_OK)
                {
                    /* By this mode switch the DCM informs the BswM to jump to the bootloader.*/
                    (void)SchM_Switch_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
                }
                else if (ret == DCM_E_PENDING)
                {
                    Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
                }
                else
                {
                    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
                    ret = E_NOT_OK;
                }
            }
        }
    }

    if (E_OK == ret)
    {
        /* check tx data length */
        if ((6u) > (Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex].Dcm_DslBufferSize))
        {
            /*Pdu length is bigger than buffer size,ignore the request message */
            *ErrorCode = DCM_E_RESPONSETOOLONG;
            ret = E_NOT_OK;
        }
    }
    if (E_OK == ret)
    {
        SchM_Enter_Dcm(Dcm_Channel);
        Dcm_Channel[Offset] = 0x50u;
        Dcm_Channel[Offset + 1u] = Subfunction;
        Dcm_Channel[Offset + 2u] = (uint8)(pDspSessionRow[SesIndex].DcmDspSessionP2ServerMax >> 8u);
        Dcm_Channel[Offset + 3u] = (uint8)(pDspSessionRow[SesIndex].DcmDspSessionP2ServerMax);
        Dcm_Channel[Offset + 4u] = (uint8)(((pDspSessionRow[SesIndex].DcmDspSessionP2StarServerMax) / 10u) >> 8u);
        Dcm_Channel[Offset + 5u] = (uint8)((pDspSessionRow[SesIndex].DcmDspSessionP2StarServerMax) / 10u);
        SchM_Exit_Dcm(Dcm_Channel);
        SchM_Enter_Dcm(Dcm_MsgCtrl);
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = 6u;
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = 6u;
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.pResData = &Dcm_Channel[Offset];
        SchM_Exit_Dcm(Dcm_MsgCtrl);
        (void)SchM_Switch_DcmDiagnosticSessionControl(Dcm_SesCtrl.Dcm_NewSes);
        DsdInternal_ProcessingDone(ProtocolCtrlId);
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
