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
 **  FILENAME    : Dem_FreezeFrame.c                                           **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API definitions of DEM for FreezeFrame                      **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem_Internal.h"

#if ((DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u))
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
/* PRQA S 1504++ */ /* MISRA Rule 8.7 */
VAR(Dem_PreStoreFFInfoType, AUTOMATIC) DemPreStoreFFInfo[DEM_MAX_NUMBER_PRESTORED_FF];
/* PRQA S 1504-- */ /* MISRA Rule 8.7 */
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0u */

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
#if (DEM_DID_CLASS_NUM > 0u)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetGeneralFreezeFrame(uint16 tempRef, uint8* pBuffer);
#endif /* DEM_DID_CLASS_NUM > 0u */

#if (DEM_SPN_CLASS_NUM > 0u)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetJ1939FreezeFrame(uint16 tempRef, uint8* pBuffer);
#endif /* DEM_SPN_CLASS_NUM > 0u */

#if (DEM_PID_CLASS_NUM > 0u)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetObdFreezeFrame(uint8* pBuffer);
#endif /* DEM_PID_CLASS_NUM > 0u */
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
/*************************************************************************/
/*
 * Brief               Dem_FreezeFrameInit
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_FreezeFrameInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Dem_PreStoreFFInfoType* pPreFF = DemPreStoreFFInfo;
    for (uint8 iloop = 0u; iloop < DEM_MAX_NUMBER_PRESTORED_FF; iloop++)
    {
        pPreFF->ExtId = 0x00;
#if (DEM_FREEZE_FRAME_MAX_LEN > 0u)
        Dem_MemSet(pPreFF->FFData, 0xFFu, DEM_FREEZE_FRAME_MAX_LEN);
#endif /* DEM_FREEZE_FRAME_MAX_LEN > 0u */
        pPreFF++;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0u */

/*************************************************************************/
/*
 * Brief               Dem_GetFreezeFrame
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     pBuffer
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetFreezeFrame(Dem_EventIdType IntId, P2VAR(uint8, AUTOMATIC, DEM_VAR) pBuffer)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
#if ((DEM_SPN_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u) || (DEM_SPN_CLASS_NUM > 0u) || (DEM_DID_CLASS_NUM > 0u))
    uint16 tempRef;
#endif /* DEM_SPN_CLASS_NUM > 0u || DEM_PID_CLASS_NUM > 0u || DEM_SPN_CLASS_NUM > 0u || DEM_DID_CLASS_NUM > 0u */
    const Dem_DTCAttributesType* pDTCAttributes = Dem_EventDTCAttributesCfg(IntId);

    Dem_UpdateInternalData(IntId);
/* DTCAttributesRef */
#if (DEM_DID_CLASS_NUM > 0u)
    /* FreezeFrameRef */
    tempRef = pDTCAttributes->DemFreezeFrameClassRef;
    if (tempRef != DEM_FREEZE_FRAME_INVALID)
    {
        Dem_GetGeneralFreezeFrame(tempRef, pBuffer);
    }
    else
    {
        /* WWHOBDFreezeFrameRef */
        tempRef = pDTCAttributes->DemWWHOBDFreezeFrameClassRef;
        if (tempRef != DEM_WWHOBD_FREEZE_FRAME_INVALID)
        {
            Dem_GetGeneralFreezeFrame(tempRef, pBuffer);
        }
        else
        {
#endif /* DEM_DID_CLASS_NUM > 0u */
#if ((DEM_PID_CLASS_NUM > 0u) || (DEM_SPN_CLASS_NUM > 0u))
            uint16 Ref = DemPbCfg.DemEventParameter[IntId].DemDTCRef;
            const Dem_DTCType* pDemDTC = &DemPbCfg.DemDTC[Ref];
            uint16 DemObdDTCRef = pDemDTC->DemObdDTCRef;
            if (DemObdDTCRef != DEM_OBD_DTC_INVALID)
            {
                const DemObdDTCType* DemObdDTC = &DemPbCfg.DemObdDTC[DemObdDTCRef];
#endif /* DEM_PID_CLASS_NUM > 0u) || (DEM_SPN_CLASS_NUM > 0u */
#if (DEM_SPN_CLASS_NUM > 0u)
                uint32 DemJ1939DTCValue = DemObdDTC->DemJ1939DTCValue;
                /* J1939FreezeFrameRef */
                tempRef = pDTCAttributes->DemJ1939FreezeFrameClassRef;
                if ((tempRef != DEM_J1939_FREEZE_FRAME_INVALID) && (DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                {
                    Dem_GetJ1939FreezeFrame(tempRef, pBuffer);
                }
                else
                {
                    /* J1939EXFreezeFrameRef */
                    tempRef = pDTCAttributes->DemJ1939ExpandedFreezeFrameClassRef;
                    if ((tempRef != DEM_J1939_FREEZE_FRAME_INVALID) && (DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                    {
                        Dem_GetJ1939FreezeFrame(tempRef, pBuffer);
                    }
                    else
                    {
#endif /* DEM_SPN_CLASS_NUM > 0u */
#if (DEM_PID_CLASS_NUM > 0u)
                        if (DemObdDTC->DemDtcValue != DEM_OBD_DTC_CFG_INVALID)
                        {
                            /*no other FreezeFrameRef ,take the obd FreezeFrame*/
                            Dem_GetObdFreezeFrame(pBuffer);
                        }
#endif /* DEM_PID_CLASS_NUM > 0u */
#if (DEM_SPN_CLASS_NUM > 0u)
                    }
                }
#endif /* DEM_SPN_CLASS_NUM > 0u */
#if ((DEM_PID_CLASS_NUM > 0u) || (DEM_SPN_CLASS_NUM > 0u))
            }
#endif /* DEM_PID_CLASS_NUM > 0u) || (DEM_SPN_CLASS_NUM > 0u */
#if (DEM_DID_CLASS_NUM > 0u)
        }
    }
#endif /* DEM_DID_CLASS_NUM > 0u */
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_FreezeFrameCopy
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && pEventBuffer
 * Param-Name[out]     pFFBuffer
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE)
    /* PRQA S 1505,3432++ */ /* MISRA Rule 8.7,20.7 */
    Dem_FreezeFrameCopy(Dem_EventIdType IntId, P2VAR(uint8, AUTOMATIC, DEM_VAR) pFFBuffer)
/* PRQA S 1505,3432-- */ /* MISRA Rule 8.7,20.7 */
{
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
    Dem_PreStoreFFInfoType* pPreFF = NULL_PTR;

    if (DemPbCfgPtr->DemEventParameter[IntId].DemFFPrestorageSupported == TRUE)
    {
        pPreFF = Dem_PreStoreFFGet(Dem_GetEventExternalId(IntId));
    }
    if (pPreFF != NULL_PTR)
    {
#if (DEM_FREEZE_FRAME_MAX_LEN > 0u)
        Dem_MemCopy(pFFBuffer, pPreFF->FFData, DEM_FREEZE_FRAME_MAX_LEN);
        Dem_MemSet(pPreFF->FFData, 0xFFu, DEM_FREEZE_FRAME_MAX_LEN);
#endif /* DEM_FREEZE_FRAME_MAX_LEN > 0u */
        pPreFF->ExtId = 0x00;
    }
    else
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0u */
    {
        Dem_GetFreezeFrame(IntId, pFFBuffer);
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_FreezeFrameStorage
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && pEventBuffer && Trigger
 * Param-Name[out]     None
 * Param-Name[in/out]  pEntry
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE)
/* PRQA S 1532,3432++ */ /* MISRA Rule 8.7,20.7 */
Dem_FreezeFrameStorage(
    VAR(Dem_EventIdType, DEM_CODE) IntId,
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    VAR(uint8, DEM_CODE) Trigger)
/* PRQA S 1532,3432-- */ /* MISRA Rule 8.7,20.7 */
{
    Dem_FreezeFrameInfoType* pFF; /* PRQA S 3432 */ /* MISRA Rule 20.7 */
    const Dem_DTCAttributesType* pDTCAttrCfg = Dem_EventDTCAttributesCfg(IntId);
    if (pDTCAttrCfg != NULL_PTR)
    {
#if (DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CONFIGURED)
        uint8 FFRecNumClassRef = pDTCAttrCfg->DemFreezeFrameRecNumClassRef;
        if (FFRecNumClassRef != DEM_FREEZE_FRAME_REC_NUM_INVALID)
        {
#if (DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u)
            const Dem_FreezeFrameRecNumClassType* pDemFFRecNumClass = &DemFreezeFrameRecNumClass[FFRecNumClassRef];
            uint8 RefNum = pDemFFRecNumClass->RefNum;
            const uint8* pFFRecordIndex = &DemFreezeFrameRecordClassRef[pDemFFRecNumClass->StartIndex];
            for (uint8 iloop = 0u; iloop < RefNum; iloop++)
            {
                if ((*pFFRecordIndex) != DEM_FREEZE_FRAME_RECORD_INVALID)
                {
                    const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                    const Dem_FreezeFrameRecordClassType* pFFRecordCfg = &DemFreezeFrameRecordClass[*pFFRecordIndex];
                    if ((pFFRecordCfg->DemFreezeFrameRecordTrigger == Trigger)
                        && ((DEM_EVENT_STATUS_FDC_TRIGGERED != Trigger)
                            || (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED) == 0x00u)))
                    {
#endif /* DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u */
                        pFF = &(pEntry->FFList[iloop]);
                        if (pFF->RecordNum == 0xFFu)
                        {
                            pEntry->FFNum++;
                        }
#if (DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u)
                        if ((pFF->RecordNum == 0xFFu)
                            || (pFFRecordCfg->DemFreezeFrameRecordUpdate == DEM_UPDATE_RECORD_YES))
                        {
#endif /* DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_PID_CLASS_NUM > 0u)
                            uint16 DemDTCRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
                            const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DemDTCRef];
                            uint16 obdDtcRef = pDemDTC->DemObdDTCRef;
                            const Dem_DTCAttributesType* pDemDTCAttributes = Dem_EventDTCAttributesCfg(IntId);
                            if (((obdDtcRef != DEM_OBD_DTC_INVALID)
                                 && ((DemPbCfgPtr->DemObdDTC[obdDtcRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID)))
                                && (pDemDTCAttributes->DemFreezeFrameClassRef == DEM_FREEZE_FRAME_INVALID)
                                && (pDemDTCAttributes->DemWWHOBDFreezeFrameClassRef == DEM_WWHOBD_FREEZE_FRAME_INVALID)
                                && (pDemDTCAttributes->DemJ1939FreezeFrameClassRef == DEM_J1939_FREEZE_FRAME_INVALID)
                                && (pDemDTCAttributes->DemJ1939ExpandedFreezeFrameClassRef
                                    == DEM_J1939_FREEZE_FRAME_INVALID))
                            {
                                Dem_FreezeFrameCopy(IntId, pFF->Data);
                                pFF->RecordNum = 0;
                            }
                            else
#endif /* DEM_PID_CLASS_NUM > 0u */
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
                            {
#if (DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u)
                                /*RecordNum the initialized value should be 0xff*/
                                pFF->RecordNum = pFFRecordCfg->DemFreezeFrameRecordNumber; /*SWS_Dem_00581]*/
#endif /* DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u */
                                Dem_FreezeFrameCopy(IntId, pFF->Data);
                                pEntry->LatestFF = iloop;
                            }
#if (DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0u)
                        }
                    }
                }
                pFFRecordIndex++;
            }
        }
#endif /* DEM_FREEZE_FRAME_RECORD_CLASS_NUM > 0 */

#else  /* DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CONFIGURED */
        if (pDTCAttrCfg->DemMaxNumberFreezeFrameRecords != 0u)
        {
            if (pDTCAttrCfg->DemMaxNumberFreezeFrameRecords == 1u)
            {
                pEntry->FFNum = 1u;
                pFF = &pEntry->FFList[0u];
                pEntry->LatestFF = pEntry->FFNum;
                pFF->RecordNum = pEntry->LatestFF;
                Dem_FreezeFrameCopy(IntId, pFF->Data);
            }
            else
            {
                if (pEntry->FFNum < pDTCAttrCfg->DemMaxNumberFreezeFrameRecords)
                { /*SWS_Dem_00585] */
                    pFF = &pEntry->FFList[pEntry->FFNum];
                    pEntry->LatestFF = pEntry->FFNum;
                    pEntry->FFNum++;
                    pFF->RecordNum = pEntry->FFNum;
                    Dem_FreezeFrameCopy(IntId, pFF->Data);
                }
            }
        }
#endif /* DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CONFIGURED */
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_FreezeFrameGetByRecordNum
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEntry && RecordNum
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_FreezeFrameInfoType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(P2VAR(Dem_FreezeFrameInfoType, AUTOMATIC, DEM_VAR), DEM_CODE) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
/* PRQA S 3432++ */                                                                  /* MISRA Rule 20.7 */
Dem_FreezeFrameGetByRecordNum(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry, uint8 RecordNum)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Dem_FreezeFrameInfoType* ret = NULL_PTR;
    Dem_FreezeFrameInfoType* pFF = pEntry->FFList;
    if (pEntry->FFNum != 0u)
    {
        if (RecordNum == 0xFFu)
        {
            ret = &(pFF[pEntry->LatestFF]);
        }
        else
        {
#if (DEM_MAX_NUMBER_FF_RECORDS > 1u)
            for (uint8 iloop = 0; iloop < DEM_MAX_NUMBER_FF_RECORDS; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
            {
#endif /* DEM_MAX_NUMBER_FF_RECORDS > 1u */
                if (pFF->RecordNum == RecordNum)
                {
                    ret = pFF;
                }
#if (DEM_MAX_NUMBER_FF_RECORDS > 1u)
                pFF++; /* PRQA S 2983 */ /* MISRA Rule 2.2 */
            }
#endif /* DEM_MAX_NUMBER_FF_RECORDS > 1u */
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_FreezeFrameGetFromEntry
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEntry && RecordNum && Did
 * Param-Name[out]     None
 * Param-Name[in/out]  pBuffer && BufSize
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 1532,3432++ */ /* MISRA Rule 8.7,20.7 */
Dem_FreezeFrameGetFromEntry(
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    uint8 RecordNum,
    uint16 Did,
    P2VAR(uint8, AUTOMATIC, DEM_VAR) pBuffer,
    uint16* BufSize)
/* PRQA S 1532,3432-- */ /* MISRA Rule 8.7,20.7 */
{
    Std_ReturnType ret = DEM_E_NODATAAVAILABLE;
    if (pEntry->FFNum != 0u)
    {
#if (DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CALCULATED)
        if (RecordNum == 0xFFu) /*SWS_Dem_00479]*/
        {
#if (DEM_FREEZE_FRAME_MAX_LEN > 0u)
            Dem_MemCopy(pBuffer, pEntry->FFList[pEntry->LatestFF].Data, DEM_FREEZE_FRAME_MAX_LEN);
#endif
            *BufSize = DEM_FREEZE_FRAME_MAX_LEN;
            ret = E_OK;
        }
        else
        {
            ret = E_NOT_OK;
        }
#else
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) || (DEM_DID_CLASS_NUM > 0u))
        Dem_EventIdType EventId = pEntry->EventId;
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        /* DtcRef */
        uint16 DemDTCRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)||(DEM_DID_CLASS_NUM > 0u */
        ret = DEM_E_WRONG_RECORDNUMBER;
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /* SWS_Dem_01194 */
        if ((DemPbCfgPtr->DemDTC[DemDTCRef].DemWWHOBDDTCClass != DEM_DTC_WWHOBD_CLASS_NOCLASS) || (RecordNum != 0u))
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
        {
            const Dem_FreezeFrameInfoType* pFF = Dem_FreezeFrameGetByRecordNum(pEntry, RecordNum);
            if (pFF != NULL_PTR)
            {
#if (DEM_DID_CLASS_NUM > 0u)
                /* DTCAttributesRef */
                uint16 DTCAttrRef = DemPbCfgPtr->DemDTC[DemDTCRef].DemDTCAttributesRef;
                /* FreezeFrameRef */
                uint16 FFRef = DemPbCfgPtr->DemDTCAttributes[DTCAttrRef].DemFreezeFrameClassRef;
                const Dem_FreezeFrameClassType* pFFClass = &DemFreezeFrameClass[FFRef];
                const uint16* pDidIndex = &DemDidClassRef[pFFClass->StartIndex];
                const uint8* pData = pFF->Data;
                uint8 Offset = 0;
                uint8 RefNum = pFFClass->RefNum;

#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                Dem_UpdateInternalData(IntId);
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                for (uint16 didRefNum = 0; didRefNum < RefNum; didRefNum++)
                {
                    const Dem_DidClassType* pDid = &DemDidClass[*pDidIndex];
                    if (pDid->DemDidIdentifier == Did)
                    {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                        uint8 DataSize = pDid->DataSize;
                        Dem_MemCopy(&pBuffer[Offset], &pData[Offset], DataSize);
                        Offset += DataSize;
                        *BufSize = DataSize;
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                        ret = E_OK;
                        break;
                    }
                    else
                    {
                        Offset += pDid->DataSize;
                    }
                    pDidIndex++;
                }
#endif /* DEM_DID_CLASS_NUM > 0u */
            }
        }
#endif /* DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CALCULATED */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
/*************************************************************************/
/*
 * Brief               Dem_PreStoreFF
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ExtId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_PreStoreFF(Dem_EventIdType ExtId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Std_ReturnType ret = E_NOT_OK;
    Dem_PreStoreFFInfoType* pPreFF = Dem_PreStoreFFGet(ExtId);

    if (pPreFF == NULL_PTR)
    {
        pPreFF = Dem_PreStoreFFGet(0x00);
    }
    if (pPreFF != NULL_PTR)
    {
        /*SWS_Dem_00807*/
        Dem_GetFreezeFrame(Dem_GetEventInternalId(ExtId), pPreFF->FFData);
        pPreFF->ExtId = ExtId;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_ClearPreStoreFF
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ExtId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearPreStoreFF(Dem_EventIdType ExtId)
{
    Std_ReturnType res = E_NOT_OK;
    Dem_PreStoreFFInfoType* pPreFF = Dem_PreStoreFFGet(ExtId);
    if (pPreFF != NULL_PTR)
    {
        pPreFF->ExtId = 0x00;
#if (DEM_FREEZE_FRAME_MAX_LEN > 0u)
        Dem_MemSet(pPreFF->FFData, 0xFFu, DEM_FREEZE_FRAME_MAX_LEN);
#endif
        res = E_OK;
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               Dem_PreStoreFFGet
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ExtId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_PreStoreFFInfoType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 1505,3432++ */ /* MISRA Rule 8.7,20.7 */
FUNC(P2VAR(Dem_PreStoreFFInfoType, AUTOMATIC, DEM_VAR), DEM_CODE)
Dem_PreStoreFFGet(Dem_EventIdType ExtId)
/* PRQA S 1505,3432-- */ /* MISRA Rule 8.7,20.7 */
{
    Dem_PreStoreFFInfoType* ret = NULL_PTR;
    Dem_PreStoreFFInfoType* pPreFF = DemPreStoreFFInfo;
    for (uint8 iloop = 0; iloop < DEM_MAX_NUMBER_PRESTORED_FF; iloop++)
    {
        if (pPreFF->ExtId == ExtId)
        {
            ret = pPreFF;
            break;
        }
        pPreFF++;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0u */

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
#if (DEM_DID_CLASS_NUM > 0)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetGeneralFreezeFrame(uint16 tempRef, uint8* pBuffer)
{
    uint8 offset = 0;
    uint16 didRefNum = DemFreezeFrameClass[tempRef].RefNum;
    const uint16* pIndex = &DemDidClassRef[DemFreezeFrameClass[tempRef].StartIndex];
    for (uint16 iloop = 0; iloop < didRefNum; iloop++)
    {
        const Dem_DidClassType* pDid = &DemDidClass[*pIndex];
        uint8 csNum = pDid->RefNum;
        uint16 csStart = pDid->StartIndex;
        for (uint8 csIndex = 0; csIndex < csNum; csIndex++)
        {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0)
            uint8 DataSize = DemDataElementClass[csStart].DemDataElementDataSize;
            uint8* DestBuffer = &pBuffer[offset];
            DemDataElementReadFncType DataReadFnc = DemDataElementClass[csStart].DemDataElementReadFnc;
            Dem_GetFncData(DataReadFnc, DestBuffer, DataSize);
            offset += DataSize;
#endif
            csStart++;
        }
        pIndex++;
    }
}
#endif

#if (DEM_SPN_CLASS_NUM > 0u)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetJ1939FreezeFrame(uint16 tempRef, uint8* pBuffer)
{
    uint8 offset = 0;
    uint16 SpnRefNum = DemJ1939FreezeFrameClass[tempRef].RefNum;
    const uint16* SpnIndex = &DemSPNClassRef[DemJ1939FreezeFrameClass[tempRef].StartIndex];
    for (uint16 iloop = 0; iloop < SpnRefNum; iloop++)
    {
        uint16 index = DemSPNClass[*SpnIndex].StartIndex;
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0)
        uint8 DataSize = DemDataElementClass[index].DemDataElementDataSize;
        uint8* DestBuffer = &pBuffer[offset];
        DemDataElementReadFncType DataReadFnc = DemDataElementClass[index].DemDataElementReadFnc;
        Dem_GetFncData(DataReadFnc, DestBuffer, DataSize);
        offset += DataSize;
#endif
        SpnIndex++;
    }
}
#endif /* DEM_SPN_CLASS_NUM > 0u */

#if (DEM_PID_CLASS_NUM > 0u)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetObdFreezeFrame(uint8* pBuffer)
{
    uint8 offset = 0;
    for (uint16 pPidIndex = 0u; pPidIndex < DEM_PID_CLASS_NUM; pPidIndex++)
    {
        const Dem_PidClassType* pPid = &DemPbCfg.DemPidClass[pPidIndex];
        uint16 pidRefNum = pPid->StartIndex;
        for (uint16 index = 0; index < pPid->RefNum; index++)
        {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0)
            uint8 DataSize = DemDataElementClass[pidRefNum].DemDataElementDataSize;
            uint8* DestBuffer = &pBuffer[offset];
            DemDataElementReadFncType DataReadFnc = DemDataElementClass[pidRefNum].DemDataElementReadFnc;
            Dem_GetFncData(DataReadFnc, DestBuffer, DataSize);
            offset += DataSize;
#endif
            pidRefNum++;
        }
    }
}
#endif /* DEM_PID_CLASS_NUM > 0u */
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
#endif /* DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u */
