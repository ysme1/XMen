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
 **  FILENAME    : Dem_ExtendedData.c                                          **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API definitions of DEM for ExtendedData                     **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem_Internal.h"

#if (DEM_EXTENDED_DATA_CLASS_NUM > 0u)
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Dem_GetExtendedData>
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
DEM_LOCAL FUNC(void, DEM_CODE) Dem_GetExtendedData(const Dem_ExtendedDataRecordClassType* pExtRecord, uint8* pBuffer)
{
    uint16 DataIndex = pExtRecord->DemDataElementClassIndex;
    uint8 cnt = pExtRecord->DemDataElementClassNum;
    uint8 offset = 0;
    for (uint16 index = 0; index < cnt; index++)
    {
        const DemDataElementClassTypes* pDataElementClass = &DemDataElementClass[DataIndex];
        uint8 DataSize = pDataElementClass->DemDataElementDataSize;
        uint8* DestBuffer = &pBuffer[offset];
        DemDataElementReadFncType DataReadFnc = pDataElementClass->DemDataElementReadFnc;
        Dem_GetFncData(DataReadFnc, DestBuffer, DataSize);
        offset += DataSize;
        DataIndex++;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Dem_ExtendedDataGetFromEntry
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  BufSize
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_ExtendedDataGetFromEntry(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    uint8 RecordNum,
    P2VAR(uint8, AUTOMATIC, DEM_VAR) pBuffer,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint16* BufSize)
{
    Std_ReturnType ret = DEM_RECORD_WRONG_NUMBER;
    Dem_EventIdType IntId = Dem_GetEventInternalId(pEntry->EventId);

    const Dem_DTCAttributesType* pDTCAttrCfg = Dem_EventDTCAttributesCfg(IntId);
    const uint16 EDClassRef = pDTCAttrCfg->DemExtendedDataClassRef;
    if (DEM_EXTENDED_DATA_INVALID != EDClassRef)
    {
        const Dem_ExtendedDataClassType* pEDClass = &DemExtendedDataClass[EDClassRef];
        uint8 RefNum = pEDClass->RefNum;
        const uint8* pExtIndex = &DemExtendedDataRecordClassRef[pEDClass->StartIndex];
        const uint8* ExtData = pEntry->ExtData;
        uint8 SrcOffset = 0;
        uint8 DstOffset = 0;
        for (uint8 index = 0; index < RefNum; index++)
        {
            if (*pExtIndex != DEM_EXTENDED_DATA_RECORD_INVALID)
            {
                const Dem_ExtendedDataRecordClassType* pExtRecord = &DemExtendedDataRecordClass[*pExtIndex];
                if (pExtRecord->DemExtendedDataRecordNumber == RecordNum)
                {
                    ret = DEM_E_NODATAAVAILABLE;
                    if (DEM_BITS_ISSET(pEntry->ExtStatus, index))
                    {
                        uint8 DataSize = pExtRecord->DataSize;
                        ret = DEM_RECORD_WRONG_BUFFERSIZE;
                        if ((uint16)(SrcOffset + DataSize) <= (*BufSize)) /* PRQA S 4391 */ /* MISRA Rule 10.8 */
                        {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                            uint8 ElementDataSize;
                            uint8 cnt = pExtRecord->DemDataElementClassNum;
                            const DemDataElementClassTypes* pDemDataElementClass =
                                &DemDataElementClass[pExtRecord->DemDataElementClassIndex];
                            Dem_UpdateInternalData(IntId);
                            for (uint8 iloop = 0; iloop < cnt; iloop++)
                            {
                                ElementDataSize = pDemDataElementClass->DemDataElementDataSize;
                                if (FALSE == pDemDataElementClass->DemInterFlag)
                                {
                                    Dem_MemCopy(&pBuffer[DstOffset], &ExtData[SrcOffset], ElementDataSize);
                                }
                                else
                                {
                                    /* get inter data now */
                                    pDemDataElementClass->DemDataElementReadFnc(&pBuffer[DstOffset]);
                                }
                                SrcOffset += ElementDataSize;
                                DstOffset += ElementDataSize;
                                pDemDataElementClass++;
                            }
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                            ret = E_OK;
                        }
                    }
                }
                else
                {
                    SrcOffset += pExtRecord->DataSize;
                }
            }
            pExtIndex++;
        }
        *BufSize = DstOffset;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_ExtendedDataStorage
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
Dem_ExtendedDataStorage(Dem_EventIdType IntId, P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry, uint8 Trigger)
/* PRQA S 1532,3432-- */ /* MISRA Rule 8.7,20.7 */
{
    const Dem_DTCAttributesType* pDTCAttrCfg = Dem_EventDTCAttributesCfg(IntId);
    if (pDTCAttrCfg != NULL_PTR)
    {
        Dem_UpdateInternalData(IntId);
        uint16 DemExtendedDataClassRef = pDTCAttrCfg->DemExtendedDataClassRef;
        if (DemExtendedDataClassRef != DEM_EXTENDED_DATA_INVALID)
        {
            const Dem_ExtendedDataClassType* pDemExtendedDataClass = &DemExtendedDataClass[DemExtendedDataClassRef];
            uint16 StartIndex = pDemExtendedDataClass->StartIndex;
            uint8 RefNum = pDemExtendedDataClass->RefNum;
            uint8 Offset = 0;
            for (uint8 iloop = 0; iloop < RefNum; iloop++)
            {
                uint8 pExtIndex = DemExtendedDataRecordClassRef[StartIndex];
                if (pExtIndex != DEM_EXTENDED_DATA_RECORD_INVALID)
                {
                    const Dem_ExtendedDataRecordClassType* pExtRecord = &DemExtendedDataRecordClass[pExtIndex];
                    const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                    uint8 RecordTrigger = pExtRecord->DemExtendedDataRecordTrigger;
                    uint8 Update = pExtRecord->DemExtendedDataRecordUpdate;
                    boolean ExtStatusFlag = DEM_BITS_ISNSET(pEntry->ExtStatus, iloop);
                    if ((RecordTrigger == Trigger)
                        && ((DEM_EVENT_STATUS_FDC_TRIGGERED != Trigger)
                            || (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED) == 0u))
                        && ((Update == DEM_UPDATE_RECORD_YES) || (ExtStatusFlag)))
                    {
                        /*set the corresponding bit*/
                        DEM_BITS_SET(pEntry->ExtStatus, iloop);
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                        Dem_GetExtendedData(pExtRecord, &(pEntry->ExtData[Offset]));
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                    }
#if (DEM_TRIGGERONMIRROREANLE == STD_ON)
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0u)
                    if ((RecordTrigger == DEM_TRIGGER_ON_MIRROR)
                        && ((Update == DEM_UPDATE_RECORD_YES) || (DEM_BITS_ISNSET(pEntry->ExtStatus, iloop))))
                    {
                        Dem_DTCOriginType pMemDest = Dem_GetInternalMemDest(DEM_DTC_ORIGIN_MIRROR_MEMORY);
                        if (pMemDest != DEM_MEM_DEST_INVALID)
                        {
                            pEntry = Dem_MemEntryAllocate(IntId, pMemDest);
                            if ((pEntry != NULL_PTR)
                                && (DEM_BITS_ISNSET(
                                    DemMemDestInfo[pMemDest].DisableDTCRecordUpdate,
                                    DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef)))
                            {
                                /*set the corresponding bit*/
                                DEM_BITS_SET(pEntry->ExtStatus, iloop);
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                                Dem_GetExtendedData(pExtRecord, &(pEntry->ExtData[Offset]));
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                            }
                        }
                    }
#endif /* DEM_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0u */
#endif /* DEM_TRIGGERONMIRROREANLE == STD_ON */
                    Offset += pExtRecord->DataSize;
                }
                StartIndex++;
            }
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
#endif /* DEM_EXTENDED_DATA_CLASS_NUM > 0u */
