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
 **  FILENAME    : Dcm_OBD0x0A.c                                               **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION : DCM OBD0x0A API definitions                                 **
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
 * Brief               <OBD service (0x0A):   Request emission-related diagnostic
 *                                              trouble codes with permanent status>
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
#if (STD_ON == DCM_OBD_SERVICE0X0A_ENABLED)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE)
/* PRQA S 3432,1532,3673++ */ /* MISRA Rule 20.7,8.7,8.13 */
Dcm_OBD0x0A(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
/* PRQA S 3432,1532,3673-- */ /* MISRA Rule 20.7,8.7,8.13 */
{
    uint32 dtc = 0;
    Dem_UdsStatusByteType dtcStatus = DCM_INVALID_UINT8;
    uint32 TxOffset;
    uint16 DTCNumber = 0;
    uint8 MsgCtrlId;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    Std_ReturnType ret = E_OK;
    Dem_ReturnSetFilterType DemRet;

    DCM_UNUSED(OpStatus);
    DCM_UNUSED(ErrorCode);
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
    TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
    Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;
    TxOffset = Offset + 2u;
    /*check the massage length*/
    if (Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen != DCM_UDS0X0A_REQ_DATA_LENGTH)
    {
        ret = E_NOT_OK;
    }
    else
    {
        DemRet = Dem_DcmSetDTCFilter(
            0,
            DEM_DTC_KIND_EMISSION_REL_DTCS,
            DEM_DTC_FORMAT_OBD,
            DEM_DTC_ORIGIN_PERMANENT_MEMORY,
            DEM_FILTER_WITH_SEVERITY_NO,
            DEM_SEVERITY_NO_SEVERITY,
            DEM_FILTER_FOR_FDC_NO);
    }
    if ((E_OK == ret) && (DEM_FILTER_ACCEPTED == DemRet))
    {
        if (DEM_NUMBER_OK == Dem_DcmGetNumberOfFilteredDTC(&DTCNumber))
        {
            for (uint16 index = 0; index < DTCNumber; index++)
            {
                if (DEM_FILTERED_OK == Dem_DcmGetNextFilteredDTC(&dtc, &dtcStatus))
                {
                    if ((TxOffset - Offset) > (Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex].Dcm_DslBufferSize))
                    {
                        /*Pdu length is bigger than buffer size,ignore the request message */
                        ret = E_NOT_OK;
                        break;
                    }
                    else
                    {
                        SchM_Enter_Dcm(Dcm_Channel);
                        Dcm_Channel[TxOffset] = (uint8)((dtc & (OBD_DATA_LSB_MASK << 8u)) >> 8u);
                        TxOffset++;
                        Dcm_Channel[TxOffset] = (uint8)(dtc & OBD_DATA_LSB_MASK);
                        SchM_Exit_Dcm(Dcm_Channel);
                        TxOffset++;
                    }
                }
            }
        }
        if (E_OK == ret)
        {
            SchM_Enter_Dcm(Dcm_Channel);
            Dcm_Channel[Offset] = 0x4A;
            Dcm_Channel[Offset + 1u] = (uint8)DTCNumber;
            SchM_Exit_Dcm(Dcm_Channel);
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = (Dcm_MsgLenType)TxOffset - Offset;
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = (Dcm_MsgLenType)TxOffset - Offset;
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.pResData = &Dcm_Channel[Offset];
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            DsdInternal_ProcessingDone(ProtocolCtrlId);
        }
    }
    else
    {
        /*the condition is not correct,ignore the request message */
        ret = E_NOT_OK;
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif /*STD_ON == DCM_OBD_SERVICE0X0A_ENABLED*/
