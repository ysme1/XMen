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
 **  FILENAME    : Dcm_OBD0x04.c                                               **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION : DCM OBD0x04 API definitions                                 **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "OBD.h"
#include "Dcm_OBDInternal.h"

/******************************************************************************/
/*
 * Brief               <OBD service (0x04):  Clear/reset emission-related diagnostic information>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:current protocol control identifier>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#if (STD_ON == DCM_OBD_SERVICE0X04_ENABLED)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE)
/* PRQA S 1532,3432++ */ /* MISRA Rule 8.7,20.7 */
Dcm_OBD0x04(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
/* PRQA S 1532,3432-- */ /* MISRA Rule 8.7,20.7 */
{
    uint8 MsgCtrlId;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    Std_ReturnType ret = E_OK;

    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    if (OpStatus != DCM_PENDING)
    {
        /*check the massage length*/
        if (Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen != DCM_UDS0X04_REQ_DATA_LENGTH)
        {
            ret = E_NOT_OK;
        }
    }
    if ((E_OK == ret) && (Dcm_DspCfg.pDcmDspClearDTC != NULL_PTR)
        && (Dcm_DspCfg.pDcmDspClearDTC->DcmDsp_ClearDTCCheckFnc != NULL_PTR))
    {
        ret = Dcm_DspCfg.pDcmDspClearDTC->DcmDsp_ClearDTCCheckFnc(DEM_DTC_GROUP_ALL_DTCS, ErrorCode);
    }
    if (E_OK == ret)
    {
        TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
        TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
        Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;
        ret = Dem_DcmClearDTC(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
        if (DEM_CLEAR_OK == ret)
        {
            /*assemble positive response*/
            SchM_Enter_Dcm(Dcm_Channel);
            Dcm_Channel[Offset] = 0x44; /*response SID*/
            SchM_Exit_Dcm(Dcm_Channel);
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = 1u;
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = 1u;
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.pResData = &Dcm_Channel[Offset];
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            DsdInternal_ProcessingDone(ProtocolCtrlId);
            ret = E_OK;
        }
        else if (DEM_CLEAR_PENDING == ret)
        {
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
            SchM_Exit_Dcm(Dcm_MsgCtrl);
        }
        else
        {
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            ret = E_NOT_OK;
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif /*STD_ON == DCM_OBD_SERVICE0X04_ENABLED*/
