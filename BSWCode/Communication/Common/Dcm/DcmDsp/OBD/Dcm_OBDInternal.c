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
 **  FILENAME    : Dcm_OBDInternal.c                                           **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION : DCM OBD Internal API definitions                            **
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

#if (DCM_DSP_PID_FUNC_ENABLED == STD_ON)
/******************************************************************************/
/*
 * Brief               <Read PID values>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ObdMidCfgIndex && ptxPos && pnoFindPIDsNum>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    OBD_ReadPidValues_0x01(uint8 pid, uint8 ctrlIndex, P2VAR(uint32, AUTOMATIC, DCM_VAR) pBufOffset, boolean UDSCall)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint32 txOffset = *pBufOffset;
    uint32 Offset = 0;
    uint8 iloop;
    uint8 Buffer[DCM_TEMP_BUFFER_LENGTH] = {0};
    uint8 txBuffer[DCM_TEMP_BUFFER_LENGTH] = {0};
    Std_ReturnType ret = E_NOT_OK;
    P2CONST(Dcm_DspPidDataType, AUTOMATIC, DCM_VAR) pDcmDspPidData;
    P2CONST(Dcm_DspPidSupportInfoType, AUTOMATIC, DCM_VAR) DcmDspPidSupportInfo;
    uint8 pPidDataNum;
    const Dcm_DspPidType* pPid;

    pPid = &(Dcm_DspCfg.pDcmDspPid[ctrlIndex]);
    pDcmDspPidData = pPid->pDcmDspPidData;
    pPidDataNum = pPid->pDcmDspPidDataNum;
    if (pDcmDspPidData != NULL_PTR)
    {

        for (iloop = 0; iloop < pPidDataNum; iloop++)
        {
            if (pDcmDspPidData->DcmDspPidService01->DcmDspPidDataReadFnc != NULL_PTR)
            {
                ret = (pDcmDspPidData->DcmDspPidService01->DcmDspPidDataReadFnc)(&Buffer[Offset]);
                if (E_OK == ret)
                {
                    if (pDcmDspPidData->pDcmDspPidDataSupportInfo != NULL_PTR)
                    {
                        DcmDspPidSupportInfo = pDcmDspPidData->pDcmDspPidDataSupportInfo->DcmDspPidDataSupportInfoRef;
                        OBD_BITS_SET(txBuffer, pDcmDspPidData->pDcmDspPidDataSupportInfo->DcmDspPidDataSupportInfoBit);
                        Dcm_MemoryCopy(
                            &Buffer[Offset],
                            &txBuffer[DcmDspPidSupportInfo->DcmDspPidSupportInfoPos],
                            DcmDspPidSupportInfo->DcmDspPidSupportInfoLen);
                    }
                    else
                    {
                        Dcm_MemoryCopy(&Buffer[Offset], &txBuffer[Offset], pDcmDspPidData->DcmDspPidDataSize);
                    }
                }
                else
                {
                    if (pDcmDspPidData->pDcmDspPidDataSupportInfo != NULL_PTR)
                    {
                        DcmDspPidSupportInfo = pDcmDspPidData->pDcmDspPidDataSupportInfo->DcmDspPidDataSupportInfoRef;
                        OBD_BITS_SET(txBuffer, pDcmDspPidData->pDcmDspPidDataSupportInfo->DcmDspPidDataSupportInfoBit);
                        OBD_MemSet(
                            &txBuffer[DcmDspPidSupportInfo->DcmDspPidSupportInfoPos],
                            0x00,
                            DcmDspPidSupportInfo->DcmDspPidSupportInfoLen);
                    }
                    else
                    {
                        OBD_MemSet(&txBuffer[Offset], 0x00, pDcmDspPidData->DcmDspPidDataSize);
                    }
                }
            }
            Offset += (uint32)pDcmDspPidData->DcmDspPidDataSize;
            pDcmDspPidData++;
        }
    }
    if (Offset <= (uint32)pPid->DcmDspPidSize)
    {
        SchM_Enter_Dcm(Dcm_Channel);
        if (TRUE == UDSCall)
        {
            Dcm_Channel[txOffset] = 0xFF;
            txOffset++;
        }
        Dcm_Channel[txOffset] = pid;
        txOffset++;
        Dcm_MemoryCopy(txBuffer, &Dcm_Channel[txOffset], pPid->DcmDspPidSize);
        SchM_Exit_Dcm(Dcm_Channel);
        txOffset += (uint32)pPid->DcmDspPidSize;
        *pBufOffset = txOffset;
        ret = E_OK;
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
/******************************************************************************/
/*
 * Brief               <Read PID values>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ObdMidCfgIndex && ptxPos && pnoFindPIDsNum>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE)
OBD_ReadPidValues(const OBD_ReadPidValuesTypes* OBD_ReadPid, uint32* pBufOffset, uint8* pNoFindPidNum)
{
    uint32 txOffset = *pBufOffset;
    uint32 Offset = 0;
    uint32 SumOffset = 0;
    uint32 BufferOffset = 0;
    boolean Find = FALSE;
    uint8 iloop;
    uint8 ctrlIndex = 0;
    uint8 Buffer[DCM_TEMP_BUFFER_LENGTH] = {0};
    uint8 txBuffer[DCM_TEMP_BUFFER_LENGTH] = {0};
    uint16 buffersize = 0;
    Std_ReturnType ret = E_NOT_OK;
    const Dcm_DspPidDataType* pDcmDspPidData;
    const Dcm_DspPidType* pDcmDspPid;

    for (iloop = 0; (FALSE == Find) && (iloop < Dcm_DspCfg.DcmDspPidNum); iloop++)
    {
        pDcmDspPid = &(Dcm_DspCfg.pDcmDspPid[iloop]);
        if ((OBD_ReadPid->pid == pDcmDspPid->DcmDspPidIdentifier)
            && ((((pDcmDspPid->DcmDspPidService == DCM_SERVICE_01)
                  || (pDcmDspPid->DcmDspPidService == DCM_SERVICE_01_02))
                 && (OBD_ReadPid->SID == SID_REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA))
                || (((pDcmDspPid->DcmDspPidService == DCM_SERVICE_02)
                     || (pDcmDspPid->DcmDspPidService == DCM_SERVICE_01_02))
                    && (OBD_ReadPid->SID == SID_REQUEST_POWERTRAIN_FREEZE_FRAME_DATA)))
            && (TRUE == pDcmDspPid->DcmDspPidUsed))
        {
            Find = TRUE;
            ctrlIndex = iloop;
        }
    }

    if (TRUE == Find)
    {
        pDcmDspPid = &(Dcm_DspCfg.pDcmDspPid[ctrlIndex]);
        OBD_MemSet(&txBuffer[Offset], 0x00, pDcmDspPid->DcmDspPidSize);
        switch (OBD_ReadPid->SID)
        {
        case SID_REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA:
            ret = OBD_ReadPidValues_0x01(OBD_ReadPid->pid, ctrlIndex, pBufOffset, OBD_ReadPid->UDSCall);
            break;
#if (STD_ON == DCM_OBD_SERVICE0X02_ENABLED)
        case SID_REQUEST_POWERTRAIN_FREEZE_FRAME_DATA:
            pDcmDspPidData = pDcmDspPid->pDcmDspPidData;
            if (pDcmDspPidData != NULL_PTR)
            {
                for (iloop = 0; iloop < pDcmDspPid->pDcmDspPidDataNum; iloop++)
                {
                    Offset = BufferOffset;
                    if (E_OK
                        == Dem_DcmReadDataOfOBDFreezeFrame(
                            OBD_ReadPid->pid,
                            (uint8)((pDcmDspPidData->DcmDspPidDataPos + 7u) >> 3u),
                            &Buffer[Offset],
                            &buffersize))
                    {
                        SumOffset += (uint32)buffersize;
                    }
                    Dcm_MemoryCopy(&Buffer[BufferOffset], &txBuffer[BufferOffset], buffersize);
                    BufferOffset += (uint32)buffersize;
                    pDcmDspPidData++;
                }
            }
            if ((BufferOffset <= (uint32)pDcmDspPid->DcmDspPidSize) && (SumOffset != 0u))
            {
                SchM_Enter_Dcm(Dcm_Channel);
                if (TRUE == OBD_ReadPid->UDSCall)
                {
                    Dcm_Channel[txOffset] = 0xFF;
                    txOffset++;
                }
                Dcm_Channel[txOffset] = OBD_ReadPid->pid;
                txOffset++;
                Dcm_Channel[txOffset] = 0x00;
                txOffset++;
                Dcm_MemoryCopy(txBuffer, &Dcm_Channel[txOffset], Dcm_DspCfg.pDcmDspPid[ctrlIndex].DcmDspPidSize);
                SchM_Exit_Dcm(Dcm_Channel);
                txOffset += (uint32)Dcm_DspCfg.pDcmDspPid[ctrlIndex].DcmDspPidSize;
                *pBufOffset = txOffset;
                ret = E_OK;
            }
            break;
#endif /* DCM_OBD_SERVICE0X02_ENABLED */
        default:
            /*idle*/
            break;
        }
    }
    else
    {
        (*pNoFindPidNum)++;
        ret = E_OK; /* can not find pid,return E_OK */
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/******************************************************************************/
/*
 * Brief               <Check supported Parameter id>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pDataBuf>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(void, DCM_CODE) OBD_CheckSupportedPIDs(uint8 pid, P2VAR(uint32, AUTOMATIC, DCM_VAR) pDataBuf, uint8 SID)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint8 iloop;
    boolean Find = FALSE;
    const Dcm_DspPidType* pDcmDspPid;

    /* check parameter */
    if (NULL_PTR != pDataBuf)
    {
        *pDataBuf = 0;
#if (STD_ON == DCM_DSP_PID_FUNC_ENABLED)
        for (iloop = 0; iloop < Dcm_DspCfg.DcmDspPidNum; iloop++)
        {
            pDcmDspPid = &(Dcm_DspCfg.pDcmDspPid[iloop]);
            if (((pDcmDspPid->DcmDspPidIdentifier >= (pid + 0x01u))
                 && (pDcmDspPid->DcmDspPidIdentifier <= (pid + 0x20u)))
                && ((((pDcmDspPid->DcmDspPidService == DCM_SERVICE_01)
                      || (pDcmDspPid->DcmDspPidService == DCM_SERVICE_01_02))
                     && (SID == SID_REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA))
                    || (((pDcmDspPid->DcmDspPidService == DCM_SERVICE_02)
                         || (pDcmDspPid->DcmDspPidService == DCM_SERVICE_01_02))
                        && (SID == SID_REQUEST_POWERTRAIN_FREEZE_FRAME_DATA)))
                && (TRUE == pDcmDspPid->DcmDspPidUsed))

            {
                *pDataBuf |= (uint32)1u << (0x20u - (pDcmDspPid->DcmDspPidIdentifier - pid));
            }

            if (((pid == pDcmDspPid->DcmDspPidIdentifier) || (pid == 0x0u))
                && ((((pDcmDspPid->DcmDspPidService == DCM_SERVICE_01)
                      || (pDcmDspPid->DcmDspPidService == DCM_SERVICE_01_02))
                     && (SID == SID_REQUEST_CURRENT_POWERTRAIN_DIAGNOSTIC_DATA))
                    || (((pDcmDspPid->DcmDspPidService == DCM_SERVICE_02)
                         || (pDcmDspPid->DcmDspPidService == DCM_SERVICE_01_02))
                        && (SID == SID_REQUEST_POWERTRAIN_FREEZE_FRAME_DATA)))
                && (TRUE == pDcmDspPid->DcmDspPidUsed))
            {
                Find = TRUE;
            }
        }

        if (Find == FALSE)
        {
            *pDataBuf = 0;
        }
#endif
    }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

/******************************************************************************/
/*
 * Brief               <Check supported test id>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pDataBuf>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <none>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#if (DCM_DSP_REQUESTCONTROL_FUNC_ENABLED == STD_ON)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(void, DCM_CODE) OBD_CheckSupportedTIDs(uint8 Tid, P2VAR(uint32, AUTOMATIC, DCM_VAR) pDataBuf)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint8 iloop;
    boolean Find = FALSE;
    const Dcm_DspRequestControlType* pRequestControl;

    /* check parameter */
    if (NULL_PTR != pDataBuf)
    {
        *pDataBuf = 0;
        for (iloop = 0; iloop < Dcm_DspCfg.DcmDspRequestControlNum; iloop++)
        {
            pRequestControl = &(Dcm_DspCfg.pDcmDspRequestControl[iloop]);
            if ((pRequestControl->DcmDspRequestControlTestId >= (Tid + 0x01u))
                && (pRequestControl->DcmDspRequestControlTestId <= (Tid + 0x20u)))
            {
                *pDataBuf |= (uint32)1u << (0x20u - (pRequestControl->DcmDspRequestControlTestId - Tid));
            }

            if ((pRequestControl->DcmDspRequestControlTestId == Tid) || (Tid == 0x0u))
            {
                Find = TRUE;
            }
        }

        if (Find == FALSE)
        {
            *pDataBuf = 0;
        }
    }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/******************************************************************************/
/*
 * Brief               <find config index number of TID>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pCfgIndex>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(Std_ReturnType, DCM_CODE) OBD_FindCfgIndexOfTestID(uint8 testID, P2VAR(uint8, AUTOMATIC, DCM_VAR) pCfgIndex)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint8 iloop;
    Std_ReturnType ret = E_NOT_OK;

    /* check parameter */
    if (NULL_PTR != pCfgIndex)
    {
        for (iloop = 0; (iloop < Dcm_DspCfg.DcmDspRequestControlNum) && (ret == E_NOT_OK); iloop++)
        {
            if (testID == Dcm_DspCfg.pDcmDspRequestControl[iloop].DcmDspRequestControlTestId)
            {
                (*pCfgIndex) = iloop;
                ret = E_OK;
            }
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#if (DCM_DSP_VEHINFO_FUNC_ENABLED == STD_ON)
/******************************************************************************/
/*
 * Brief               <Set Availability InfoType Value>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <InfoType && pDataBuf>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(void, DCM_CODE) OBD_SetAvailabilityInfoTypeValue(uint8 InfoType, P2VAR(uint32, AUTOMATIC, DCM_VAR) pDataBuf)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint8 iloop;
    boolean Find = FALSE;
    uint8 VehInfoInfoType;

    /* check parameter */
    if (NULL_PTR != pDataBuf)
    {
        *pDataBuf = 0;
        for (iloop = 0; iloop < Dcm_DspCfg.DcmDspVehInfoNum; iloop++)
        {
            VehInfoInfoType = Dcm_DspCfg.pDcmDspVehInfo[iloop].DcmDspVehInfoInfoType;
            if ((VehInfoInfoType >= (InfoType + 0x01u)) && (VehInfoInfoType <= (InfoType + 0x20u)))
            {
                *pDataBuf |= (uint32)1u << (0x20u - (VehInfoInfoType - InfoType));
            }

            if ((VehInfoInfoType == InfoType) || (InfoType == 0x0u))
            {
                Find = TRUE;
            }
        }

        if (Find == FALSE)
        {
            *pDataBuf = 0;
        }
    }
    return;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/******************************************************************************/
/*
 * Brief               <find config index number of VehInfo>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pCfgIndex>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
/* PRQA S 3432,1532++ */ /* MISRA Rule 20.7,8.7 */
FUNC(Std_ReturnType, DCM_CODE) OBD_FindCfgIndexOfVehInfo(uint8 vehInfo, P2VAR(uint8, AUTOMATIC, DCM_VAR) pCfgIndex)
/* PRQA S 3432,1532-- */ /* MISRA Rule 20.7,8.7 */
{
    uint8 iloop;
    Std_ReturnType ret = E_NOT_OK;

    /* check parameter */
    if (NULL_PTR != pCfgIndex)
    {
        for (iloop = 0; (iloop < Dcm_DspCfg.DcmDspVehInfoNum) && (E_NOT_OK == ret); iloop++)
        {
            if (vehInfo == Dcm_DspCfg.pDcmDspVehInfo[iloop].DcmDspVehInfoInfoType)
            {
                (*pCfgIndex) = iloop;
                ret = E_OK;
            }
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
