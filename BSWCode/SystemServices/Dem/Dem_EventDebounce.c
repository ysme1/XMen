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
 **  FILENAME    : Dem_EventDebounce.c                                         **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : DEM EventDebounce API definitions                           **
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

/*******************************************************************************
**                      macros  define                                        **
*******************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(FDCInfoType, AUTOMATIC) FDCInfo[DEM_DTC_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0)
/* Debounce Counter Base Info Define */
VAR(Dem_DebounceCounterInfoType, AUTOMATIC) DemDebounceCounterInfo[DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM];
#endif
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
VAR(Dem_DebounceTimeInfoType, AUTOMATIC) DemDebounceTimerInfo[DEM_DEBOUNCE_TIME_BASED_EVENT_NUM];
#endif
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0)
DEM_LOCAL FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebounceProcessCounter(
    Dem_EventDataBufferType pEventBuffer,
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg);
#endif
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
DEM_LOCAL FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebounceProcessTimer(
    Dem_EventDataBufferType pEventBuffer,
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg);
#endif
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               Dem_DebounceInit
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_DebounceInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
    for (uint16 iloop = 0; iloop < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM; iloop++)
    {
        Dem_DebounceCounterInfoType* pDemDebounceCounterInfo = &DemDebounceCounterInfo[iloop];
        pDemDebounceCounterInfo->InternalDebounceCounter = 0;
    }
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
    for (uint16 iloop = 0; iloop < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM; iloop++)
    {
        Dem_DebounceTimeInfoType* pDemDebounceTimerInfo = &DemDebounceTimerInfo[iloop];
        pDemDebounceTimerInfo->Timeout = 0x00;
        pDemDebounceTimerInfo->Triggered = FALSE;
        pDemDebounceTimerInfo->CurStatus = DEM_EVENT_STATUS_PREPASSED;
    }
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
    Dem_MemSet((uint8*)FDCInfo, 0x00u, (sizeof(FDCInfoType) * DEM_DTC_NUM));
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_DebounceReset
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_DebounceReset(Dem_EventIdType IntId)
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];

#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
    Dem_DebounceCounterInfoType* pCounter;
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
    Dem_DebounceTimeInfoType* pTimer;
#endif /*DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
#if ((DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u) || (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u))
    const uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)||(DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
    switch (pEventCfg->AlgorithmType)
    {
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0)
    case DEM_DEBOUNCE_COUNTER_BASED:
        if (AlgorithmIndex < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM)
        {
            pCounter = &DemDebounceCounterInfo[AlgorithmIndex];
            pCounter->InternalDebounceCounter = 0;
        }
        break;
#endif
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
    case DEM_DEBOUNCE_TIME_BASE:
        if (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM)
        {
            pTimer = &DemDebounceTimerInfo[AlgorithmIndex];
            pTimer->Timeout = 0;
            pTimer->Triggered = FALSE;
            pTimer->CurStatus = DEM_EVENT_STATUS_PREPASSED;
        }
        break;
#endif
    default:
        /*idle*/
        break;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_GetInteralFDC
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              sint8
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_GetInteralFDC(Dem_EventIdType IntId, P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
    Std_ReturnType ret = E_NOT_OK;
#if (                                                                                      \
    (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u) || (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u) \
    || (DEM_DEBOUNCE_MONITOR_INTERNAL_EVENT_NUM > 0u))
    uint16 AlgorithmRef = pEventCfg->AlgorithmRef;
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u || DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u || \
          DEM_DEBOUNCE_MONITOR_INTERNAL_EVENT_NUM > 0u */
    switch (pEventCfg->AlgorithmType)
    {
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
    case DEM_DEBOUNCE_COUNTER_BASED: /*SWS_Dem_00415*/
        if ((AlgorithmRef < DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM)
            && ((pEventCfg->AlgorithmIndex) < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM))
        {
            const Dem_DebounceCounterBasedClassType* pCfgCounter =
                &DemPbCfgPtr->DemDebounceCounterBasedClass[AlgorithmRef];
            const Dem_DebounceCounterInfoType* pCounter = &DemDebounceCounterInfo[pEventCfg->AlgorithmIndex];
            sint16 InternalDebounceCounter = pCounter->InternalDebounceCounter;
            if (InternalDebounceCounter > 0)
            {
                *FaultDetectionCounter =
                    (sint8)((InternalDebounceCounter * 127) / pCfgCounter->DemDebounceCounterFailedThreshold);
            }
            else
            {
                *FaultDetectionCounter =
                    (sint8)((InternalDebounceCounter * (-128)) / pCfgCounter->DemDebounceCounterPassedThreshold);
            }
            ret = E_OK;
        }
        break;
#endif
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
    case DEM_DEBOUNCE_TIME_BASE: /*SWS_Dem_00427*/
        if ((AlgorithmRef < DEM_DEBOUNCE_TIME_BASE_CLASS_NUM)
            && ((pEventCfg->AlgorithmIndex) < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM))
        {
            const Dem_DebounceTimeInfoType* pTimer = &DemDebounceTimerInfo[pEventCfg->AlgorithmIndex];
            const Dem_DebounceTimeBaseClassType* pTimerCfg = &DemPbCfgPtr->DemDebounceTimeBaseClass[AlgorithmRef];
            uint64 Timeout = pTimer->Timeout;

            /* PRQA S 4394++ */ /* MISRA Rule 10.8 */
            switch (pTimer->CurStatus)
            {
            case DEM_EVENT_STATUS_FAILED:
            case DEM_EVENT_STATUS_PREFAILED:
                *FaultDetectionCounter = (sint8)((Timeout * 127UL) / (uint64)pTimerCfg->DemDebounceTimeFailedThreshold);
                break;
            default:
                *FaultDetectionCounter =
                    ((sint8)(-1)) * ((sint8)((Timeout * 128UL) / (uint64)pTimerCfg->DemDebounceTimePassedThreshold));
                break;
            }
            /* PRQA S 4394-- */ /* MISRA Rule 10.8 */
            ret = E_OK;
        }
        break;
#endif
#if (DEM_DEBOUNCE_MONITOR_INTERNAL_EVENT_NUM > 0u)
    case DEM_DEBOUNCE_MONITOR_INTERNAL: /*SWS_Dem_00264] */
        if (AlgorithmRef < DEM_DEBOUNCE_MONITOR_INTERNAL_EVENT_NUM)
        {
            Dem_GetFDCFncType GetFnc = DemGetFDCFncs[AlgorithmRef];
            *FaultDetectionCounter = 0;
            if (GetFnc != NULL_PTR)
            { /*SWS_Dem_00439] */
                ret = GetFnc(FaultDetectionCounter);
                if (E_OK != ret)
                {
                    *FaultDetectionCounter = 0;
                }
            }
            else
            {
                ret = DEM_E_NO_FDC_AVAILABLE;
            }
        }
        break;
#endif
    default:
        *FaultDetectionCounter = 0;
        break;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_DebounceProcess
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEventBuffer
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Dem_EventStatusType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_EventStatusType, DEM_CODE)
/* PRQA S 1532, 3432++ */ /* MISRA Rule 8.7, Rule 20.7 */
Dem_DebounceProcess(Dem_EventDataBufferType pEventBuffer)
/* PRQA S 1532, 3432-- */ /* MISRA Rule 8.7, Rule 20.7 */
{
    Dem_EventIdType IntId = Dem_GetEventInternalId(pEventBuffer.ExtId);
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
    Dem_EventStatusType Status = pEventBuffer.Status;
    Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
    uint8 AlgorithmType = pEventCfg->AlgorithmType;
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
    const Dem_DebounceTimeInfoType* pTimer = &DemDebounceTimerInfo[pEventCfg->AlgorithmIndex];
#endif /*  DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0*/
#if (DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON)
    uint16 DemDTCRef = pEventCfg->DemDTCRef;
    sint8 FDC;
#endif /* DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON */
    switch (AlgorithmType)
    {
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
    case DEM_DEBOUNCE_COUNTER_BASED:
        Status = Dem_DebounceProcessCounter(pEventBuffer, pEventCfg);
        break;
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
    case DEM_DEBOUNCE_TIME_BASE:
        Status = Dem_DebounceProcessTimer(pEventBuffer, pEventCfg);
        break;
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
    default:
        /*idle*/
        break;
    }

#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    if ((DEM_EVENT_STATUS_FAILED != Status) && (0x00u != DEM_FLAGS_ISSET(pEvent->StatusIndicator30, DEM_SI30_DTC_AGED)))
    {
        /*bit 6: A DTC is not emission related as long as the FDC10 has not reached the value
         * +127 since DTC information was last cleared and when it is aged*/
        uint16 DemDTCRef = pEventCfg->DemDTCRef;
        const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DemDTCRef];
        if ((pDemDTC->DTCKind != DEM_DTC_KIND_EMISSION_REL_DTCS))
        {
            DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_ER);
        }
    }
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */

    /* if event failed clear anging counter*/
    if (DEM_EVENT_STATUS_FAILED == Status)
    {
        pEvent->AgingCounter = 0u;
        Dem_EventQueueAddDebounceFailed(pEvent);
    }
    else if (DEM_EVENT_STATUS_PASSED == Status)
    {
        if (0x00u != (pEvent->UdsStatus & DEM_UDS_STATUS_TF))
        {
            DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
        }
    }
    else
    {
        /* do nothing */
    }
#if (DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON)
    Dem_UpdateFDC(IntId);
    FDC = FDCInfo[DemDTCRef].FDC;
    if ((DemDTCRef != DEM_DTC_REF_INVALID) && (FDC > 0)
        && (DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[DemDTCRef].DemDTCAttributesRef]
                .DemEventMemoryEntryFdcThresholdStorageValue
            <= (uint8)FDC)
        && ((DEM_DEBOUNCE_COUNTER_BASED == AlgorithmType)
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
            || ((DEM_DEBOUNCE_TIME_BASE == AlgorithmType) && (pTimer->Triggered == FALSE))
#endif
                ))
    {
        /*SWS_Dem_00799]*/
        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED);
        Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_FDC_THRESHOLD);
    }
#endif /* DEM_TRIGGERONFDCTHRESHOLDEANLE == STD_ON */
    return Status;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if ((DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u) || (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u))
/*************************************************************************/
/*
 * Brief               Dem_DebounceFreeze
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_DebounceFreeze(Dem_EventIdType IntId)
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfg.DemEventParameter[IntId];
    uint8 AlgorithmType = pEventCfg->AlgorithmType;
    uint16 AlgorithmRef = pEventCfg->AlgorithmRef;
    uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
    if ((AlgorithmType == DEM_DEBOUNCE_TIME_BASE) && (AlgorithmRef < DEM_DEBOUNCE_TIME_BASE_CLASS_NUM)
        && (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM))
    {
        Dem_DebounceTimeInfoType* pDemDebounceTimerInfo = &DemDebounceTimerInfo[AlgorithmIndex];
        if (DemPbCfg.DemDebounceTimeBaseClass[AlgorithmRef].DemDebounceBehavior == DEM_DEBOUNCE_FREEZE)
        {
            pDemDebounceTimerInfo->IsFreezing = TRUE;
        }
        else
        {
            pDemDebounceTimerInfo->CurStatus = DEM_EVENT_STATUS_PREPASSED;
            pDemDebounceTimerInfo->Timeout = 0;
            pDemDebounceTimerInfo->Triggered = FALSE;
        }
    }
    else
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0 */
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
        if ((AlgorithmType == DEM_DEBOUNCE_COUNTER_BASED) && (AlgorithmRef < DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM)
            && (AlgorithmIndex < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM))
    {
        if (DemPbCfg.DemDebounceCounterBasedClass[AlgorithmRef].DemDebounceBehavior == DEM_DEBOUNCE_RESET)
        {
            DemDebounceCounterInfo[AlgorithmIndex].InternalDebounceCounter = 0;
        }
    }
    else
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
    {
        /*idle*/
    }
    return;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u) && (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */

#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Dem_DebounceTimerMain
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_DebounceTimerMain(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    sint8 FDC;
    uint16 DemDTCRef;
    const Dem_EventParameterType* pEventCfg;
    Dem_EventRelateInformationType* pEvent;
    for (uint16 iloop = 0; (iloop < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM); iloop++)
    {
        Dem_DebounceTimeInfoType* pTimer = &DemDebounceTimerInfo[iloop];
        if ((pTimer->Triggered == TRUE) && (pTimer->IsFreezing == FALSE))
        {
            Dem_EventIdType IntId = pTimer->IntId;
            Dem_EventStatusType CurStatus = pTimer->CurStatus;
            const Dem_EventParameterType* pEventParameter = &DemPbCfgPtr->DemEventParameter[IntId];
            uint16 AlgorithmRef = pEventParameter->AlgorithmRef;
            const Dem_DebounceTimeBaseClassType* pTimerCfg = &DemPbCfgPtr->DemDebounceTimeBaseClass[AlgorithmRef];
            uint8 DemOperationCycleRef = pEventParameter->DemOperationCycleRef;
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
            uint8 OldStatus = pTimer->CurStatus;
            uint8 NewStatus;
#endif
            if ((CurStatus != DEM_EVENT_STATUS_FAILED) && (CurStatus != DEM_EVENT_STATUS_PASSED))
            {
                pTimer->Timeout += DEM_TASK_TIME;
            }
            if ((CurStatus == DEM_EVENT_STATUS_PREFAILED)
                && (pTimer->Timeout >= pTimerCfg->DemDebounceTimeFailedThreshold))
            {
                pTimer->CurStatus = DEM_EVENT_STATUS_FAILED;
                pTimer->Triggered = FALSE;
                if ((DEM_BITS_ISSET(DemOperationCycleStatus, DemOperationCycleRef))
                    || (DemOperationCycle[DemOperationCycleRef].DemOperationCycleType == DEM_OPCYC_OBD_DCY))
                {
                    Dem_EventQueueAddDebounceFailed(Dem_GetEventInfo(IntId));
                    Dem_EventTestFailed(IntId);
                }
            }
            else if (
                (CurStatus == DEM_EVENT_STATUS_PREPASSED)
                && (pTimer->Timeout >= pTimerCfg->DemDebounceTimePassedThreshold))
            {
                pTimer->CurStatus = DEM_EVENT_STATUS_PASSED;
                pTimer->Triggered = FALSE;
                if ((DEM_BITS_ISSET(DemOperationCycleStatus, DemOperationCycleRef))
                    || (DemOperationCycle[DemOperationCycleRef].DemOperationCycleType == DEM_OPCYC_OBD_DCY))
                {
                    Dem_EventTestPassed(IntId);
                }
            }
            else
            {
                /*idle*/
            }
            Dem_UpdateFDC(IntId);
            pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
            DemDTCRef = pEventCfg->DemDTCRef;
            FDC = FDCInfo[DemDTCRef].FDC;
            pEvent = Dem_GetEventInfo(IntId);
            if ((DemDTCRef != DEM_DTC_REF_INVALID) && (FDC > 0)
                && (DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[DemDTCRef].DemDTCAttributesRef]
                        .DemEventMemoryEntryFdcThresholdStorageValue
                    <= (uint8)FDC))
            {
                /*SWS_Dem_00799]*/
                DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED);
                Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_FDC_THRESHOLD);
            }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
            NewStatus = pTimer->CurStatus;
            if (OldStatus != NewStatus)
            {
                (void)FiM_DemTriggerOnEventStatus(Dem_GetEventExternalId(IntId), OldStatus, NewStatus);
            }
#endif
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)

DEM_LOCAL FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebouceProcessPrePassedCounter(
    P2CONST(Dem_DebounceCounterBasedClassType, AUTOMATIC, DEM_CONST) pCfgCounter,
    P2VAR(Dem_DebounceCounterInfoType, AUTOMATIC, DEM_VAR) pCounter) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Dem_EventStatusType status = DEM_EVENT_STATUS_PREPASSED;
    sint16 JumpDownValue = pCfgCounter->DemDebounceCounterJumpDownValue;
    sint16* InternalCounter = &pCounter->InternalDebounceCounter;
    sint16 PassedThreshold = pCfgCounter->DemDebounceCounterPassedThreshold;
    uint16 StepSize = pCfgCounter->DemDebounceCounterDecrementStepSize;
    if (*InternalCounter > JumpDownValue)
    {
        if (pCfgCounter->DemDebounceCounterJumpDown == TRUE) /*SWS_Dem_00423*/
        {
            *InternalCounter = JumpDownValue;
        }
    }
    if ((PassedThreshold + (sint16)StepSize) >= *InternalCounter)
    {
        *InternalCounter = PassedThreshold;
        status = DEM_EVENT_STATUS_PASSED;
    }
    else
    {
        *InternalCounter -= (sint16)StepSize;
    }
    return status;
}

DEM_LOCAL FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebouceProcessPreFailedCounter(
    P2CONST(Dem_DebounceCounterBasedClassType, AUTOMATIC, DEM_CONST) pCfgCounter,
    P2VAR(Dem_DebounceCounterInfoType, AUTOMATIC, DEM_VAR) pCounter) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Dem_EventStatusType status = DEM_EVENT_STATUS_PREFAILED;
    sint16 JumpUpValue = pCfgCounter->DemDebounceCounterJumpUpValue;
    sint16* InternalCounter = &pCounter->InternalDebounceCounter;
    sint16 FailedThreshold = pCfgCounter->DemDebounceCounterFailedThreshold;
    uint16 StepSize = pCfgCounter->DemDebounceCounterIncrementStepSize;
    if (*InternalCounter < JumpUpValue)
    {
        if (pCfgCounter->DemDebounceCounterJumpUp == TRUE) /*SWS_Dem_00425*/
        {
            *InternalCounter = JumpUpValue;
        }
    }
    if ((FailedThreshold - (sint16)StepSize) <= *InternalCounter)
    {
        *InternalCounter = FailedThreshold;
        status = DEM_EVENT_STATUS_FAILED;
    }
    else
    {
        *InternalCounter += (sint16)StepSize;
    }
    return status;
}

/*************************************************************************/
/*
 * Brief               Dem_DebounceProcessCounter
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEventBuffer && pEventCfg
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Dem_EventStatusType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebounceProcessCounter(
    Dem_EventDataBufferType pEventBuffer,
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    const Dem_DebounceCounterBasedClassType* pCfgCounter =
        &DemPbCfgPtr->DemDebounceCounterBasedClass
             [DemPbCfgPtr->DemEventParameter[Dem_GetEventInternalId(pEventBuffer.ExtId)].AlgorithmRef];
    Dem_DebounceCounterInfoType* pCounter = &DemDebounceCounterInfo[pEventCfg->AlgorithmIndex];
    Dem_EventStatusType Status = pEventBuffer.Status;

    switch (Status)
    {
    case DEM_EVENT_STATUS_PASSED: /*SWS_Dem_00421*/
        pCounter->InternalDebounceCounter = pCfgCounter->DemDebounceCounterPassedThreshold;
        break;
    case DEM_EVENT_STATUS_FAILED: /*SWS_Dem_00420] */
        pCounter->InternalDebounceCounter = pCfgCounter->DemDebounceCounterFailedThreshold;
        break;
    case DEM_EVENT_STATUS_PREPASSED:
        Status = Dem_DebouceProcessPrePassedCounter(pCfgCounter, pCounter);
        break;
    default: /* DEM_EVENT_STATUS_PREFAILED */
        Status = Dem_DebouceProcessPreFailedCounter(pCfgCounter, pCounter);
        break;
    }
    return Status;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */

#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Dem_DebounceProcessTimer
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEventBuffer && pEventCfg
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Dem_EventStatusType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebounceProcessTimer(
    Dem_EventDataBufferType pEventBuffer,
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Dem_EventIdType IntId = Dem_GetEventInternalId(pEventBuffer.ExtId);
    Dem_EventStatusType Status = pEventBuffer.Status;
    Dem_DebounceTimeInfoType* pTimer = &DemDebounceTimerInfo[pEventCfg->AlgorithmIndex];
    const Dem_DebounceTimeBaseClassType* pTimerCfg = &DemPbCfgPtr->DemDebounceTimeBaseClass[pEventCfg->AlgorithmRef];
    const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
    Dem_EventStatusType CurStatus = pTimer->CurStatus;
    if (pTimer->IsFreezing != FALSE)
    {
        /*SWS_Dem_00656*/
        if (0x00u
            != DEM_FLAGS_ISSET(pEvent->Status, (DEM_EVENT_STATUS_ENABLED_CONDICTION | DEM_EVENT_STATUS_DTC_SETTING)))
        {
            pTimer->IsFreezing = FALSE;
        }
    }
    switch (Status)
    {
    case DEM_EVENT_STATUS_PASSED:
        pTimer->CurStatus = DEM_EVENT_STATUS_PASSED; /*SWS_Dem_00435*/
        pTimer->Timeout = pTimerCfg->DemDebounceTimePassedThreshold;
        break;
    case DEM_EVENT_STATUS_FAILED:
        pTimer->CurStatus = DEM_EVENT_STATUS_FAILED; /*SWS_Dem_00431*/
        pTimer->Timeout = pTimerCfg->DemDebounceTimeFailedThreshold;
        break;
    case DEM_EVENT_STATUS_PREPASSED: /*SWS_Dem_00432*/
        if ((CurStatus == DEM_EVENT_STATUS_FAILED) || (CurStatus == DEM_EVENT_STATUS_PREFAILED)
            || (CurStatus == DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED) || (pTimer->Triggered == FALSE)) /*SWS_Dem_00433*/
        {
            pTimer->CurStatus = DEM_EVENT_STATUS_PREPASSED;
            pTimer->Triggered = TRUE;
            pTimer->Timeout = 0;
        }
        break;
    case DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED:
        break;
    case DEM_EVENT_STATUS_PREFAILED: /* Prefailed */
        if ((CurStatus == DEM_EVENT_STATUS_PASSED) || (CurStatus == DEM_EVENT_STATUS_PREPASSED)
            || (pTimer->Triggered == FALSE)) /*SWS_Dem_00429*/
        {
            pTimer->CurStatus = DEM_EVENT_STATUS_PREFAILED;
            pTimer->Triggered = TRUE;
            pTimer->Timeout = 0;
        }
        break;
    default:
        /*idle*/
        break;
    }
    return Status;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Dem_UpdateFDC
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Dem_EventStatusType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_UpdateFDC(Dem_EventIdType IntId)
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfg.DemEventParameter[IntId];
#if ((DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u) || (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u))
    uint16 AlgorithmRef = pEventCfg->AlgorithmRef;
    uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
    sint8 FDC = 0;
    uint16 DemDTCRef = pEventCfg->DemDTCRef;

    switch (pEventCfg->AlgorithmType)
    {
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
    case DEM_DEBOUNCE_COUNTER_BASED:

        if ((AlgorithmRef < DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM)
            && (AlgorithmIndex < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM))
        {
            const Dem_DebounceCounterBasedClassType* pCfgCounter = &DemPbCfg.DemDebounceCounterBasedClass[AlgorithmRef];
            const Dem_DebounceCounterInfoType* pCounter = &DemDebounceCounterInfo[AlgorithmIndex];
            if (pCounter->InternalDebounceCounter == 0)
            {
                FDC = 0;
            }
            else if (pCounter->InternalDebounceCounter > 0)
            {
                FDC =
                    (sint8)((pCounter->InternalDebounceCounter * 127) / pCfgCounter->DemDebounceCounterFailedThreshold);
            }
            else
            {
                FDC = (sint8)((pCounter->InternalDebounceCounter * ((sint8)(-128)))
                              / pCfgCounter->DemDebounceCounterPassedThreshold);
            }
        }
        break;
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
    case DEM_DEBOUNCE_TIME_BASE:
        if ((AlgorithmRef < DEM_DEBOUNCE_TIME_BASE_CLASS_NUM) && (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM))
        {
            const Dem_DebounceTimeInfoType* pTimer = &DemDebounceTimerInfo[AlgorithmIndex];
            const Dem_DebounceTimeBaseClassType* pTimerCfg = &DemPbCfg.DemDebounceTimeBaseClass[AlgorithmRef];
            switch (pTimer->CurStatus)
            {
            case DEM_EVENT_STATUS_PASSED:
                FDC = -128;
                break;
            case DEM_EVENT_STATUS_FAILED:
                FDC = 127;
                break;
            case DEM_EVENT_STATUS_PREFAILED:
                FDC = (sint8)((pTimer->Timeout * 127UL) /* PRQA S 4394 */ /* MISRA Rule 10.8 */
                              / (uint64)pTimerCfg->DemDebounceTimeFailedThreshold);
                break;
            default:
                FDC = ((sint8)(-1))
                      * ((sint8)((pTimer->Timeout * 128UL) /* PRQA S 4394 */ /* MISRA Rule 10.8 */
                                 / (uint64)pTimerCfg->DemDebounceTimePassedThreshold));
                break;
            }
        }
        break;
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
    default:
        /*idle*/
        break;
    }
    if (DemDTCRef != DEM_DTC_REF_INVALID)
    {
        FDCInfoType* pFDCInfo = &FDCInfo[DemDTCRef];
        if (FDC > 0) /* SWS_Dem_00795 */
        {
            uint8 CurFDC = (uint8)FDC;
            if (CurFDC > pFDCInfo->MaxFDCSinceLastClear)
            {
                pFDCInfo->MaxFDCSinceLastClear = CurFDC;
            }
            if (CurFDC > pFDCInfo->MaxFDCDuringCurrentCycle)
            {
                pFDCInfo->MaxFDCDuringCurrentCycle = CurFDC;
            }
        }
        pFDCInfo->FDC = FDC;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
/*************************************************************************/
/*
 * Brief               Dem_DTCCombinedGroupGetFDC
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pDemDTC
 * Param-Name[out]     FaultDetectionCounter
 * Param-Name[in/out]  none
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
    Dem_DTCCombinedGroupGetFDC(const Dem_DTCType* pDemDTC, sint8* FaultDetectionCounter)
{
    const Dem_EventIdType* pDTCMapping;
    Dem_EventIdType EventRefStart;
    Dem_EventIdType EventId;
    Std_ReturnType ret;
    sint8 Fdc;
    sint8 MaxFdc = -128;

    EventRefStart = pDemDTC->EventRefStart;
    pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];

    for (uint8 loop = 0; loop < pDemDTC->EventRefNum; loop++)
    {
        EventId = Dem_GetEventExternalId(*pDTCMapping);
        ret = Dem_GetFaultDetectionCounter(EventId, &Fdc);
        if ((ret == E_OK) && (MaxFdc < Fdc))
        {
            MaxFdc = Fdc;
        }

        if (ret != E_OK)
        {
            break;
        }
        pDTCMapping++;
    }
    if (ret == E_OK)
    {
        *FaultDetectionCounter = MaxFdc;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

/*************************************************************************/
/*
 * Brief               Dem_DTCGetFaultDetectionCounter
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId
 * Param-Name[out]     FaultDetectionCounter
 * Param-Name[in/out]  none
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DTCGetFaultDetectionCounter(Dem_EventIdType EventId, sint8* FaultDetectionCounter)
{
    Std_ReturnType ret;

#if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
    Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
    uint16 DTCRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
    const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DTCRef];
    Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
    if (EventRefNum != 1u)
    {
        ret = Dem_DTCCombinedGroupGetFDC(pDemDTC, FaultDetectionCounter);
    }
    else
#endif /* DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED */
    {
        ret = Dem_GetFaultDetectionCounter(EventId, FaultDetectionCounter);
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
