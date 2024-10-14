
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
         UDS:ClearDiagnosticInformation (14 hex) service
 ***************************************************************/
#if (STD_ON == DCM_UDS_SERVICE0X14_ENABLED)
/********************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE) Dcm_UDS0x14_ConditionCheck(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    uint8 MsgCtrlId;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    uint32 groupOfDTC;
    Dem_ReturnClearDTCType returnClearDTC;
    Std_ReturnType ret = E_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */

    /*if the required protocol is configuted,get the index of runtime datum*/
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    /*session check,check whether the current session supports the request service*/
    ret = DsdInternal_SesCheck(ProtocolCtrlId, SID_CLEAR_DIAGNOSTIC_INFORMATION);
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
        ret = DsdInternal_SecurityCheck(ProtocolCtrlId, SID_CLEAR_DIAGNOSTIC_INFORMATION);
        if (E_NOT_OK == ret)
        {
            /*the current security does not support the request service,send NRC = 0x33*/
            *ErrorCode = DCM_E_SECURITYACCESSDENIED;
        }
    }
#endif

    /*check the massage length*/
    if ((E_OK == ret) && (DCM_UDS0X14_REQ_DATA_LENGTH != Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen))
    {
        /*the length of massage is not correct,send NRC 0x13*/
        *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        ret = E_NOT_OK;
    }

    if ((E_OK == ret) && (OpStatus == DCM_INITIAL))
    {
        /*get and assemble DTC, high byte first*/
        groupOfDTC = (((uint32)(Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[1])) << 16u)
                     | (((uint32)(Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[2])) << 8u)
                     | ((uint32)(Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[3]));

        TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
        TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
        Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;

        returnClearDTC = Dem_DcmCheckClearParameter(groupOfDTC, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
        switch (returnClearDTC)
        {
        case DEM_CLEAR_PENDING:
            ret = DCM_E_PENDING;
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            break;
        case DEM_CLEAR_WRONG_DTC:
            /*Server does not support the required groupOfDTC,send NRC 0x31*/
            *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            ret = E_NOT_OK;
            break;
        case DEM_CLEAR_FAILED:
            /*internal conditions within the server prevent the
               clearing of DTC related information stored in the server,sent NRC 0x22*/
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            ret = E_NOT_OK;
            break;
        case DEM_CLEAR_OK:
            if ((Dcm_DspCfg.pDcmDspClearDTC != NULL_PTR)
                && (Dcm_DspCfg.pDcmDspClearDTC->DcmDsp_ClearDTCCheckFnc != NULL_PTR))
            {
                ret = Dcm_DspCfg.pDcmDspClearDTC->DcmDsp_ClearDTCCheckFnc(groupOfDTC, ErrorCode);
            }
            break;
        default:
            /*idle*/
            break;
        }
    }
    return ret;
}

/********************************/
FUNC(Std_ReturnType, DCM_CODE)
Dcm_UDS0x14(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    uint8 MsgCtrlId;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    uint32 groupOfDTC;
    Dem_ReturnClearDTCType returnClearDTC;
    Std_ReturnType ret;

    /*if the required protocol is configuted,get the index of runtime datum*/
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    /*get and assemble DTC, high byte first*/
    groupOfDTC = (((uint32)(Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[1])) << 16u)
                 | (((uint32)(Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[2])) << 8u)
                 | ((uint32)(Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[3]));

    TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
    TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
    Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;
    ret = Dcm_UDS0x14_ConditionCheck(OpStatus, ProtocolCtrlId, ErrorCode);
    if (E_OK == ret)
    {
        /*invoke the corresponding API provided by DEM*/
        returnClearDTC = Dem_DcmClearDTC(groupOfDTC, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
        switch (returnClearDTC)
        {
        case DEM_CLEAR_OK:
            /*clear is successful,assemble and send the positive response*/
            /* check tx data length */
            if ((0x01u) > (Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex].Dcm_DslBufferSize))
            {
                /*Pdu length is bigger than buffer size,ignore the request message */
                *ErrorCode = DCM_E_RESPONSETOOLONG;
                ret = E_NOT_OK;
            }
            if (E_OK == ret)
            {
                SchM_Enter_Dcm(Dcm_Channel);
                Dcm_Channel[Offset] = 0x54; /*response SID*/
                SchM_Exit_Dcm(Dcm_Channel);
                SchM_Enter_Dcm(Dcm_MsgCtrl);
                Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = 0x01;
                Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = 0x01;
                Dcm_MsgCtrl[MsgCtrlId].MsgContext.pResData = &Dcm_Channel[Offset];
                SchM_Exit_Dcm(Dcm_MsgCtrl);
                DsdInternal_ProcessingDone(ProtocolCtrlId);
            }
            break;
        case DEM_CLEAR_WRONG_DTC:
            /*Server does not support the required groupOfDTC,send NRC 0x31*/
            *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            ret = E_NOT_OK;
            break;
        case DEM_CLEAR_PENDING:
            ret = DCM_E_PENDING;
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            break;
        case DEM_CLEAR_MEMORY_ERROR:
            *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
            ret = E_NOT_OK;
            break;
        case DEM_CLEAR_BUSY:
        case DEM_CLEAR_FAILED:
            /*internal conditions within the server prevent the
               clearing of DTC related information stored in the server,sent NRC 0x22*/
        default:
            /*the unexpected return value is present,send NRC 0x22*/
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            ret = E_NOT_OK;
            break;
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
