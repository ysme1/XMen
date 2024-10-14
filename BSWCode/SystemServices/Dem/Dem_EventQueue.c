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
 **  FILENAME    : Dem_EventQueue.c                                            **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API definitions of DEM for EventQueue                       **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem_Internal.h"
#if (STD_ON == DEM_TRIGGER_FIM_REPORTS)
#include "FiM.h"
#endif
#include "SchM_Dem.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
typedef struct
{
    Dem_EventDataBufferType Queue[DEM_EVENT_QUEUE_SIZE];
    uint8 ReadIndex;
    uint8 WriteIndex;
} Dem_EventQueueType;

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(Dem_EventQueueType, AUTOMATIC) DemEventQueue;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               Dem_EventQueueInit
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
FUNC(void, DEM_CODE) Dem_EventQueueInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Dem_EventQueueType* pQueue = &DemEventQueue;
    Dem_EventDataBufferType* pBuffer = pQueue->Queue;

    pQueue->ReadIndex = 0x00;
    pQueue->WriteIndex = 0x00;

    for (uint16 iloop = 0; iloop < DEM_EVENT_QUEUE_SIZE; iloop++)
    {
        pBuffer->ExtId = 0x00;
        pBuffer->Status = 0x00;
        pBuffer++;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventQueueAdd
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ExtId && Status
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 1532++ */ /* MISRA Rule 8.7 */
FUNC(Std_ReturnType, DEM_CODE) Dem_EventQueueAdd(Dem_EventIdType ExtId, Dem_EventStatusType Status)
/* PRQA S 1532-- */ /* MISRA Rule 8.7 */
{
    Std_ReturnType res = E_NOT_OK;
    SchM_Enter_Dem_DemQueue();
    Dem_EventQueueType* pQueue = &DemEventQueue;
    Dem_EventDataBufferType* pBuffer = &(pQueue->Queue[pQueue->WriteIndex]);

    if (pBuffer->ExtId == 0x00u)
    {
        pQueue->WriteIndex++;
        if (pQueue->WriteIndex >= DEM_EVENT_QUEUE_SIZE)
        {
            pQueue->WriteIndex = 0x00;
        }
        SchM_Exit_Dem_DemQueue();
        pBuffer->Status = Status;
        pBuffer->ExtId = ExtId;
        res = E_OK;
    }
    else
    {
        SchM_Exit_Dem_DemQueue();
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventQueueProcess
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
FUNC(void, DEM_CODE) Dem_EventQueueProcess(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Dem_EventQueueType* pQueue = &DemEventQueue;
    Dem_EventDataBufferType* pBuffer = &(pQueue->Queue[pQueue->ReadIndex]);
#if (DEM_DEAL_MAINFUNCTION_ENABLE == STD_ON)
    uint8 Deal_Cnt = 0;
#endif /* DEM_DEAL_MAINFUNCTION_ENABLE == STD_ON */
    /* Proccess Event */
    while ((pBuffer->ExtId != 0x00u)
#if (DEM_DEAL_MAINFUNCTION_ENABLE == STD_ON)
           && (Deal_Cnt < DEM_DEAL_MAINFUNCTION_COUNTER)
#endif /* DEM_DEAL_MAINFUNCTION_ENABLE == STD_ON */
    )
    {
#if (DEM_DEAL_MAINFUNCTION_ENABLE == STD_ON)
        Deal_Cnt++;
#endif /* DEM_DEAL_MAINFUNCTION_ENABLE == STD_ON */
        Dem_EventIdType EventId = pBuffer->ExtId;
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
#if (DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON)
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
#else
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
#endif /* DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON */
        const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
        uint8 OperationCycleId = pEventCfg->DemOperationCycleRef;
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
        uint8 OldStatus = pEvent->UdsStatus;
#endif /* DEM_TRIGGER_FIM_REPORTS == STD_ON */
        if ((0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_DTC_SETTING))
            && (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
#if (DEM_ENABLE_CONDITION_NUM > 0u)
            && (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
#endif /* DEM_ENABLE_CONDITION_NUM > 0u */
        )
        {
            uint8 AlgorithmType = pEventCfg->AlgorithmType;
            /* SWS_Dem_00854 SWS_Dem_00700 */
            if (((DEM_BITS_ISSET(DemOperationCycleStatus, OperationCycleId))
                 || (DemOperationCycle[OperationCycleId].DemOperationCycleType == DEM_OPCYC_OBD_DCY)))
            {
#if (DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON)
                if ((0x00u == DEM_FLAGS_ISSET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_FDC_TRIGGER))
                    && (pBuffer->Status == DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED))
                {
                    /* SWS_Dem_01068, SWS_Dem_01069 */
                    DEM_FLAGS_SET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_FDC_TRIGGER);
                    Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_FDC_THRESHOLD);
                }
                else
#endif /* DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON */
                {
#if (DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON)
                    uint16 DemDTCRef = pEventCfg->DemDTCRef;
                    sint8 FDC;
#endif /* DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON */
                    /* Debounce */
                    switch (Dem_DebounceProcess(*pBuffer))
                    {
                    case DEM_EVENT_STATUS_PASSED:
                        Dem_EventTestPassed(IntId);
                        break;
                    case DEM_EVENT_STATUS_FAILED:
                        Dem_EventTestFailed(IntId);
                        break;
                    default:
                        /*idle*/
                        break;
                    }
#if (DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON)
                    Dem_UpdateFDC(IntId);
                    FDC = FDCInfo[DemDTCRef].FDC;
                    /* SWS_Dem_00786 SWS_Dem_01068 SWS_Dem_00811 SWS_Dem_01069 */
                    if ((DemDTCRef != DEM_DTC_REF_INVALID) && (FDC > 0)
                        && (DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[DemDTCRef].DemDTCAttributesRef]
                                .DemEventMemoryEntryFdcThresholdStorageValue
                            <= (uint8)FDC)
                        && (DEM_DEBOUNCE_COUNTER_BASED == AlgorithmType))
                    {
                        /* SWS_Dem_00799 */
                        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED);
                        Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_FDC_THRESHOLD);
                    }
#endif /* DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON */
                }
            }
#if ((DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u) || (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u))
            else
            {
                uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
                /*debounce counter shall be reset to zero*/
                switch (AlgorithmType)
                {
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
                case DEM_DEBOUNCE_COUNTER_BASED:
                    if (AlgorithmIndex < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM)
                    {
                        DemDebounceCounterInfo[AlgorithmIndex].InternalDebounceCounter = 0;
                    }
                    break;
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
                case DEM_DEBOUNCE_TIME_BASE:
                    if (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM)
                    {
                        Dem_DebounceTimeInfoType* pTimerInfo = &DemDebounceTimerInfo[AlgorithmIndex];
                        pTimerInfo->Timeout = 0u;
                        pTimerInfo->Triggered = FALSE;
                        pTimerInfo->CurStatus = DEM_EVENT_STATUS_PREPASSED;
                    }
                    break;
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
                default:
                    /*idle*/
                    break;
                }
            }
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u) || (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
        }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
        if (OldStatus != pEvent->UdsStatus)
        {
            (void)FiM_DemTriggerOnEventStatus(EventId, OldStatus, pEvent->UdsStatus);
        }
#endif /* DEM_TRIGGER_FIM_REPORTS == STD_ON */
        /* Clear Buffer */
        pBuffer->ExtId = 0x00;
        pBuffer->Status = 0x00;
        /* Move ReadIndex */
        pQueue->ReadIndex++;
        if (pQueue->ReadIndex >= DEM_EVENT_QUEUE_SIZE)
        {
            pQueue->ReadIndex = 0x00;
        }
        pBuffer = &(pQueue->Queue[pQueue->ReadIndex]);
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
