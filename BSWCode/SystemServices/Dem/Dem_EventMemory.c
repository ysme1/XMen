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
 **  FILENAME    : Dem_EventMemory.c                                           **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : DEM EventMemory API definitions                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem_Internal.h"
#include "Dem_Dcm.h"
#if (DEM_NVRAM_BLOCKID_NUM > 0u)
#include "NvM.h"
#include "NvM_Types.h"
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
#if (STD_ON == DEM_TRIGGER_FIM_REPORTS)
#include "FiM.h"
#endif /* STD_ON == DEM_TRIGGER_FIM_REPORTS */
#if (STD_ON == DEM_J1939_SUPPORT)
#include "J1939Dcm_Cbk.h"
#endif /* STD_ON == DEM_J1939_SUPPORT */
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
#include "Dcm.h"
#endif

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(Dem_MemDestInfoType, AUTOMATIC) DemMemDestInfo[DEM_MEM_DEST_TOTAL_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(Dem_EventRelateInformationType, AUTOMATIC) DemEventRelateInformation[DEM_EVENT_PARAMETER_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(Dem_DTCGeneralStatusType, AUTOMATIC) DemDTCGeneralStatus[DEM_DTC_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#if (DEM_INDICATOR_NUM > 0)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(Dem_IndicatorStatusType, AUTOMATIC) DemWIRStatus[DEM_INDICATOR_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif

#define DEM_START_SEC_VAR_POWER_ON_INIT_8
#include "Dem_MemMap.h"
VAR(uint8, AUTOMATIC) Dem_AgingCycle = DEM_OPERATION_CYCLE_INVALID;
#define DEM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "Dem_MemMap.h"

#if (DEM_COMPONENT_NUM > 0)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(DemComponentStatusType, AUTOMATIC) DemComponentStatus[DEM_COMPONENT_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif

#if (DEM_NVRAM_BLOCKID_NUM > 0u)
#if (DEM_NVRAM_DIVADED == STD_OFF)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(Dem_EventMemEntryType, AUTOMATIC) DemEventMemoryEntryStorage[ENTRY_STORAGE_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif /* DEM_NVRAM_DIVADED == STD_OFF */

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(Dem_EventRelateInformationStorageType, AUTOMATIC) DemEventRelateInformationStorage;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(DemOBDDataStorageType, AUTOMATIC) DemOBDDataStorage;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF)
static void Dem_CDTCOverFlowCheck(Dem_EventIdType IntId);
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_ON */
#if (DEM_COMPONENT_NUM > 0)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_EventTestFailedProcessOfComponent(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg);
#endif
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE) Dem_CheckEntryAlreadyAllocated(
    Dem_EventIdType IntId,
    uint8 memDest,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
        P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) * pEntry);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(void, DEM_CODE) Dem_EntryChronologicalOrderUpdate(
    Dem_EventIdType IntId,
    uint8 memDest,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#if (DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_DeleteDisplacementEntry(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pResEntry,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    VAR(uint8, DEM_VAR) memDest);
DEM_LOCAL FUNC(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR), DEM_CODE) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
    Dem_EventDisplacementProcess(Dem_EventIdType InternalId, uint8 memDest);
#endif

/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
    Dem_ClearUdsStatusOfPDTC(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

DEM_LOCAL FUNC(void, DEM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dem_EventAgingProcess(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent, uint8 OpId);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(void, DEM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dem_EventHealingProcess(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent, uint8 OpId);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#if ((DEM_INDICATOR_NUM > 0) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0))
DEM_LOCAL FUNC(boolean, DEM_CODE) Dem_CheckWIROn(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg);
DEM_LOCAL FUNC(boolean, DEM_CODE) Dem_CheckWIROff(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg);
#endif
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dem_OperationCycleCounterProcess(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(void, DEM_CODE) Dem_EventStatusProcessByDTC(
    uint16 dtcIndex,
    uint16 iloop,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL void Dem_ClearEventRelateInformation(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#if ((DEM_NVRAM_DIVADED == STD_ON) && (DEM_NVRAM_BLOCKID_NUM > 0))
DEM_LOCAL FUNC(void, DEM_CODE) Dem_IntWriteOneNvRAM(uint16 IntId);
#endif
/* PRQA S 1505 */ /* MISRA Rule 8.7 */
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               Dem_EventMemInit
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
FUNC(void, DEM_CODE) Dem_EventMemInit(Std_ReturnType NvmResult) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
    Dem_MemSet((uint8*)DemMemDestInfo, 0x00u, (sizeof(Dem_MemDestInfoType) * DEM_MEM_DEST_TOTAL_NUM));
#if (DEM_INDICATOR_NUM > 0u)
    Dem_MemSet(DemWIRStatus, DEM_INDICATOR_OFF, DEM_INDICATOR_NUM);
#endif /* DEM_INDICATOR_NUM > 0u */
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
        const Dem_EventParameterType* pEventCfg = &pDemEventParameter[iloop];
#if (DEM_ENABLE_CONDITION_NUM > 0u)
        uint8 DemEnableConditionGroupRef = pEventCfg->DemEnableConditionGroupRef;
#endif /* DEM_ENABLE_CONDITION_NUM > 0u */
#if (DEM_STORAGE_CONDITION_NUM > 0u)
        uint8 DemStorageConditionGroupRef = pEventCfg->DemStorageConditionGroupRef;
#endif /* DEM_STORAGE_CONDITION_NUM > 0u */
        pEvent->IntId = iloop;
#if (DEM_STATUS_BIT_STORAGE_TEST_FAILED == STD_OFF)
        /*SWS_Dem_00525] */
        DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TF); /* clear bit0 */
#else
        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
        {
            DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_ACTIVE);
        }
        else
        {
            DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_ACTIVE);
        }
#endif /* DEM_STATUS_BIT_STORAGE_TEST_FAILED == STD_OFF */
        if ((E_NOT_OK == NvmResult) || (pEvent->Status == 0x00u))
        {
            DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC); /* set bit 6 */
        }
        pEvent->OldUdsStatus = pEvent->UdsStatus;
        Dem_EventStatusProcessByDTC(pEventCfg->DemDTCRef, iloop, pEvent);
#if (DEM_ENABLE_CONDITION_NUM > 0u)
        if (DemEnableConditionGroupRef != DEM_ENABLE_CONDITION_GROUP_INVALID)
        {
            if (Dem_CheckCondictionFulfilled(
                    DemEnableConditionStatus,
                    &DemEnableConditionGroup[DemEnableConditionGroupRef][0],
                    DEM_ENABLE_CONDITION_NUM_BYTE)
                == TRUE)
            {
                DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION);
            }
        }
        else
#endif /* DEM_ENABLE_CONDITION_NUM > 0u */
        {
            DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION);
        }
#if (DEM_STORAGE_CONDITION_NUM > 0u)
        if (DemStorageConditionGroupRef != DEM_STORAGE_CONDITION_GROUP_INVALID)
        {
            if (Dem_CheckCondictionFulfilled(
                    DemStorageConditionStatus,
                    &DemStorageConditionGroup[DemStorageConditionGroupRef][0],
                    DEM_STORAGE_CONDITION_NUM_BYTE)
                == TRUE)
            {
                DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION);
            }
        }
        else
#endif
        {
            DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION);
        }
        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_DTC_SETTING);
        Dem_UpdateCombinedDtcStatus(iloop);
        if (E_NOT_OK == NvmResult)
        {
            Dem_ClearEventRelateInformation(pEvent);
        }
        DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_CONSECUTIVE_FAULT);
        DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED);
        DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
        /*bit 6: The bit is set to 0 when the DTC is not emission related.The bit is set to 1 when the DTC is emission
         * related.*/
        const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[pEventCfg->DemDTCRef];
        if ((pDemDTC->DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS))
        {
            DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_ER);
        }
        else
        {
            DEM_FLAGS_CLR(pEvent->StatusIndicator30, DEM_SI30_DTC_ER);
        }
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
    }
#if (DEM_COMPONENT_NUM > 0u)
    for (uint16 iloop = 0; iloop < DEM_COMPONENT_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        DemComponentStatus[iloop].FailurePriority = 0xFF;
        DemComponentStatus[iloop].Status = FALSE;
        DemComponentStatus[iloop].availability = TRUE;
    }
#endif /* DEM_COMPONENT_NUM > 0u */
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_CheckEventMemEntryExistsAlready
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_EventMemEntryType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_EventMemEntryType*, DEM_CODE) Dem_CheckEventMemEntryExistsAlready(Dem_EventIdType IntId)
{
    uint16 TempRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
    Dem_EventMemEntryType* pEntry = NULL_PTR;
    if (TempRef != DEM_DTC_REF_INVALID)
    {
        const uint8* pMemoryDestinationRef =
            DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[TempRef].DemDTCAttributesRef].DemMemoryDestinationRef;
        Dem_EventIdType EventId = Dem_GetEventExternalId(IntId);
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
        for (uint8 iloop = 0; (iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC) && (pEntry == NULL_PTR); iloop++)
#else
        uint8 iloop = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
        {
            uint8 pMemDest = pMemoryDestinationRef[iloop];
            if (pMemDest != DEM_MEM_DEST_INVALID)
            {
                pEntry = Dem_MemEntryGet(EventId, pMemDest);
            }
        }
    }
    return pEntry;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_GetEventInfo
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_EventRelateInformationType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_EventRelateInformationType*, DEM_CODE) Dem_GetEventInfo(Dem_EventIdType IntId)
{
    return &DemEventRelateInformation[IntId];
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventTestFailed
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && pEventBuffer
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(void, DEM_CODE) Dem_EventTestFailed(Dem_EventIdType IntId)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
    Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
    uint16 DTCRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
    const Dem_DTCAttributesType* pDTCAttr = Dem_EventDTCAttributesCfg(IntId);
#if (DEM_COMPONENT_NUM > 0u)
    Dem_EventTestFailedProcessOfComponent(pEvent, pEventCfg);
#endif /* DEM_COMPONENT_NUM > 0u */
#if (DEM_TRIGGERONTESTFAILEDEANLE == STD_ON)
    if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u)
    {
        Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_TEST_FAILED);
    }
#endif /* DEM_TRIGGERONTESTFAILEDEANLE == STD_ON */
#if (DEM_OCCURRENCE_COUNTER_PROCESSING == DEM_PROCESS_OCCCTR_TF)
    /*SWS_Dem_00524 SWS_Dem_00625 */
    if ((NULL_PTR != Dem_CheckEventMemEntryExistsAlready(IntId)) && (pEvent->OccurrenceCounter < 0xFFu)
        && ((DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF) != 0u)
            && (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0u)))
    {
        pEvent->OccurrenceCounter++;
    }
#endif
    /* if event failed clear anging counter*/
    pEvent->AgingCounter = 0;
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    /*The bit is reset to 0 when the aged DTC reoccurs*/
    if (0x00u != DEM_FLAGS_ISSET(pEvent->StatusIndicator30, DEM_SI30_DTC_AGED))
    {
        DEM_FLAGS_CLR(pEvent->StatusIndicator30, DEM_SI30_DTC_AGED);
    }
#endif                                                                    /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
    if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC)) /* Check PendingDTC bit */
    {
        /* req SWS_Dem_00784 SWS_Dem_00801 SWS_Dem_00813*/
        DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC); /* bit 2*/
#if (DEM_TRIGGERONPENDINGEDEANLE == STD_ON)
        Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_PENDING);
#endif /* DEM_TRIGGERONPENDINGEDEANLE == STD_ON */
    }
#if (DEM_TRIGGER_ON_PENDING == DEM_EVENT_MEMORY_ENTRY_STORAGE_TRIGGER)
#if (DEM_TRIGGERONPENDINGEDEANLE == STD_ON)
    else
    {
        /* req SWS_Dem_00922 */
        if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u)
        {
            Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_PENDING);
        }
    }
#endif /* DEM_TRIGGERONPENDINGEDEANLE == STD_ON */
#endif /* DEM_TRIGGER_ON_PENDING == DEM_EVENT_MEMORY_ENTRY_STORAGE_TRIGGER */
    /* confirmedLevel reached? */
    if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
    {
        if ((pEvent->FailureCounter + 1u) >= pEventCfg->DemEventFailureCycleCounterThreshold) /* SWS_Dem_00528 */
        {
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
            boolean Find = FALSE;
            const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
            if (DTCRef != DEM_DTC_REF_INVALID)
            {
                const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DTCRef];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
                const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                for (uint16 iloop = 0u; (iloop < EventRefNum) && (Find == FALSE); iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                {
                    if ((DTCRef == pEventParameter[*pDTCMapping].DemDTCRef)
                        && (DEM_FLAGS_ISSET(DemEventRelateInformation[*pDTCMapping].UdsStatus, DEM_UDS_STATUS_CDTC)
                            != 0x00u))
                    {
                        Find = TRUE;
                    }
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                    pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                }
            }
            if (Find == FALSE)
#endif /* DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE */
            {
                if (DTCRef != DEM_DTC_REF_INVALID)
                {
                    const uint8* pMemDest = pDTCAttr->DemMemoryDestinationRef;
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
                    for (uint8 index = 0; index < DEM_MEM_DEST_MAX_NUM_OF_DTC; index++)
#else
                    uint8 index = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
                    {
                        if ((pMemDest[index] != DEM_MEM_DEST_INVALID)
                            && (DemMemDestCfg[pMemDest[index]].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY))
                        {
                            if (DemDTCByOccurrenceTimeInfo.FirstDtcConfirmed == DEM_EVENT_PARAMETER_INVALID)
                            {
                                DemDTCByOccurrenceTimeInfo.FirstDtcConfirmed = IntId;
                            }
                            DemDTCByOccurrenceTimeInfo.MostRecDtcConfirmed = IntId; /* SWS_Dem_00219 */
                        }
                    }
                }
                if ((DEM_BITS_ISNSET(DemOperationCycleStatus, pEventCfg->DemOperationCycleRef))
                    && (DemOperationCycle[pEventCfg->DemOperationCycleRef].DemOperationCycleType
                        == DEM_OPCYC_OBD_DCY)) /*SWS_Dem_00700*/
                {
                    /*idle*/
                }
                else
                {
                    DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC); /* bit 3 */
#if (DEM_OCC6EANLE == STD_ON)
                    /*  The counter may also be cleared when the conﬁrmedDTCLimit is reached. */
                    pEvent->OCC6 = 0;
#endif /* DEM_OCC6EANLE == STD_ON */
                }
#if (DEM_TRIGGERONCONFIRMEDEDEANLE == STD_ON)
                /* req SWS_Dem_00785 SWS_Dem_00802 SWS_Dem_00814*/
                Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_CONFIRMED);
#endif /* DEM_TRIGGERONCONFIRMEDEDEANLE == STD_ON */
            }
        }
    }
    else
    {
#if (DEM_TRIGGERONCONFIRMEDEDEANLE == STD_ON)
#if (                                                                    \
    (DEM_TRIGGER_ON_CONFIRMED == DEM_EVENT_MEMORY_ENTRY_STORAGE_TRIGGER) \
    && (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF))
        /* req SWS_Dem_00923 */
        if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u)
        {
            Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_CONFIRMED);
        }
#endif /* DEM_TRIGGER_ON_CONFIRMED == DEM_EVENT_MEMORY_ENTRY_STORAGE_TRIGGER && DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW \
          == STD_OFF */
#endif /* DEM_TRIGGERONCONFIRMEDEDEANLE == STD_ON */
    }
#if (DEM_OCCURRENCE_COUNTER_PROCESSING == DEM_PROCESS_OCCCTR_CDTC)
    /*SWS_Dem_00580 SWS_Dem_00625 */
    if ((pEvent->OccurrenceCounter < 0xFFu) && (NULL_PTR != Dem_CheckEventMemEntryExistsAlready(IntId))
        && ((DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF) != 0u)
            && (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0u))
        && (DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC) != 0u))
    {
        /*  occurrence counter counter by one ,trigger by TF bit transition from 0 to 1 if CDTC is set */
        pEvent->OccurrenceCounter++;
    }
#endif

#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
    /* Check WarningIndicatorOnCondition */
    if (TRUE == Dem_CheckWIROn(pEvent, pEventCfg))
    {
        DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR); /* bit 7 */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
        /*The bit is set to 1 when DTC status bit no 7 is set to 1. In all cases, FDC10 has reached the value +127,
         * since DTC information was latest cleared, before the bit is set to 1 and warring indicator is requested*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
        {
            DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_WIRSLC); /*bit 5*/
        }
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
    }
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
    if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u)
    {
        DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
    }
    Dem_UpdateCombinedDtcStatus(IntId); /* update the combination event dtc status*/
    Dem_ResponseOnDtcStatusChange(IntId);
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_UpdateCombinedDtcStatus
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_UpdateCombinedDtcStatus(Dem_EventIdType IntId)
{
    uint16 dtcRef = DemPbCfg.DemEventParameter[IntId].DemDTCRef;
    if (dtcRef != DEM_DTC_REF_INVALID)
    {
        uint8 CbUdsStatus;
        Dem_DTCGeneralStatusType* pDTCGeneralStatus = &DemDTCGeneralStatus[dtcRef];
        const Dem_DTCType* pDemDTC = &DemPbCfg.DemDTC[dtcRef];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
        const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
        const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
        const Dem_EventIdType* pDTCMapping = &DemPbCfg.DemDTCMapping[EventRefStart];
        pDTCGeneralStatus->CbUdsStatus = 0;

#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
        for (uint16 iloop = 0; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
        /* SWS_Dem_00441*/
        {
            /*bit0 - bit7 or-operation */
            DemDTCGeneralStatus[dtcRef].CbUdsStatus |= DemEventRelateInformation[*pDTCMapping].UdsStatus;
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
            pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
        }
        /* bit4 calculation */
        CbUdsStatus = ~((DemDTCGeneralStatus[dtcRef].CbUdsStatus & DEM_UDS_STATUS_TFSLC) >> 1u);
        DemDTCGeneralStatus[dtcRef].CbUdsStatus &= CbUdsStatus;
        /* bit6 calculation */
        CbUdsStatus = (uint8)(~(uint8)((DemDTCGeneralStatus[dtcRef].CbUdsStatus & DEM_UDS_STATUS_TFTOC) << 5u));
        DemDTCGeneralStatus[dtcRef].CbUdsStatus &= CbUdsStatus;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_ResponseOnDtcStatusChange
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_ResponseOnDtcStatusChange(Dem_EventIdType IntId)
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
    uint16 dtcRef = pEventCfg->DemDTCRef;
    if (dtcRef != DEM_DTC_REF_INVALID)
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        uint8 OldUdsStatus = pEvent->OldUdsStatus;
        uint8 NewUdsStatus = pEvent->UdsStatus;
        if (OldUdsStatus != NewUdsStatus)
        {
#if (DEM_J1939_NODE_NUM > 0u)
            uint16 DemObdDTCRef = DemPbCfgPtr->DemDTC[dtcRef].DemObdDTCRef;
            const DemObdDTCType* pDemObdDTC = DemPbCfgPtr->DemObdDTC;
#endif /* DEM_J1939_NODE_NUM > 0u */

#if (DEM_CALLBACK_EVENT_STATUS_CHANGED_TOTAL_NUM > 0u)
            uint8 StatusChangedCbkNum = pEventCfg->StatusChangedCbkNum;
            const Dem_TriggerOnEventStatusType* pCbk =
                &DemCallbackEventStatusChanged[pEventCfg->StatusChangedCbkStartIndex];
#endif /* DEM_CALLBACK_EVENT_STATUS_CHANGED_TOTAL_NUM > 0u */
            /* SWS_Dem_00828 */
            if (Dem_DTCStatusChangedInd == TRUE)
            {
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
                uint32 DTC = 0x00;
#if (DEM_CALLBACK_DTC_STATUS_CHANGED_NUM > 0u)
                /* SWS_Dem_00284 */
                Dem_GetEventDTC(dtcRef, DEM_DTC_FORMAT_UDS, &DTC);
                if (DTC != 0x00UL)
                {
                    const Dem_TriggerOnDTCStatusType* pDTCStatusChanged = DemCallbackDTCStatusChanged;
                    (void)Dcm_DemTriggerOnDTCStatus(DTC, OldUdsStatus, NewUdsStatus);
                    /* PRQA S 2877++ */ /* MISRA Rule 4.1 */
                    for (uint8 iloop = 0; iloop < DEM_CALLBACK_DTC_STATUS_CHANGED_NUM; iloop++)
                    /* PRQA S 2877-- */ /* MISRA Rule 4.1 */
                    {
                        if (pDTCStatusChanged != NULL_PTR)
                        {
                            (void)(*pDTCStatusChanged)(DTC, OldUdsStatus, NewUdsStatus);
                        }
                        pDTCStatusChanged++;
                    }
                }
#endif /* DEM_CALLBACK_DTC_STATUS_CHANGED_NUM > 0u */
#if (DEM_CALLBACK_OBD_DTC_STATUS_CHANGED_NUM > 0u)
                /* SWS_Dem_00986 */
                Dem_GetEventDTC(dtcRef, DEM_DTC_FORMAT_OBD, &DTC);
                if (DTC != 0x00UL)
                {
                    const Dem_TriggerOnDTCStatusType* pObdDTCStatusChanged = DemCallbackObdDTCStatusChanged;
                    /* PRQA S 2877++ */ /* MISRA Rule 4.1 */
                    for (uint8 iloop = 0; iloop < DEM_CALLBACK_OBD_DTC_STATUS_CHANGED_NUM; iloop++)
                    /* PRQA S 2877-- */ /* MISRA Rule 4.1 */
                    {
                        if (pObdDTCStatusChanged != NULL_PTR)
                        {
                            (void)(*pObdDTCStatusChanged)(DTC, OldUdsStatus, NewUdsStatus);
                        }
                        pObdDTCStatusChanged++;
                    }
                }
#endif /* DEM_CALLBACK_OBD_DTC_STATUS_CHANGED_NUM > 0u */
#if (DEM_CALLBACK_J1939_DTC_STATUS_CHANGED_NUM > 0u)
                /* SWS_Dem_00987 */
                Dem_GetEventDTC(dtcRef, DEM_DTC_FORMAT_J1939, &DTC);
                if (DTC != 0x00UL)
                {
                    const Dem_TriggerOnDTCStatusType* p1939DTCStatusChanged = DemCallbackJ1939DTCStatusChanged;
                    /* PRQA S 2877++ */ /* MISRA Rule 4.1 */
                    for (uint8 iloop = 0; iloop < DEM_CALLBACK_J1939_DTC_STATUS_CHANGED_NUM; iloop++)
                    /* PRQA S 2877-- */ /* MISRA Rule 4.1 */
                    {
                        if (p1939DTCStatusChanged != NULL_PTR)
                        {
                            (void)(*p1939DTCStatusChanged)(DTC, OldUdsStatus, NewUdsStatus);
                        }
                        p1939DTCStatusChanged++;
                    }
                }
#endif /* DEM_CALLBACK_J1939_DTC_STATUS_CHANGED_NUM > 0u */
#endif /* DEM_TRIGGER_DCM_REPORTS == STD_ON */
            }
            /*SWS_Dem_00016] */
#if (DEM_CALLBACK_EVENT_STATUS_CHANGED_TOTAL_NUM > 0u)
            /* PRQA S 2877++ */ /* MISRA Rule 4.1 */
            for (uint8 iloop = 0; iloop < StatusChangedCbkNum; iloop++)
            /* PRQA S 2877-- */ /* MISRA Rule 4.1 */
            {
                if ((*pCbk) != NULL_PTR)
                {
                    (void)(*pCbk)(IntId + 1u, OldUdsStatus, NewUdsStatus);
                }
                pCbk++;
            }
#endif /* DEM_CALLBACK_EVENT_STATUS_CHANGED_TOTAL_NUM > 0u */
#if (DEM_J1939_NODE_NUM > 0u)
            if ((DemObdDTCRef != DEM_OBD_DTC_INVALID)
                && (DEM_J1939_DTC_CFG_INVALID != pDemObdDTC[DemObdDTCRef].DemJ1939DTCValue)
                && ((OldUdsStatus & DEM_UDS_STATUS_TF) != (NewUdsStatus & DEM_UDS_STATUS_TF)))
            {
                uint16 DemDTCAttributesRef = DemPbCfgPtr->DemDTC[dtcRef].DemDTCAttributesRef;
                const uint8 DemJ1939DTC_J1939NodeRef =
                    DemPbCfgPtr->DemDTCAttributes[DemDTCAttributesRef].DemJ1939DTC_J1939NodeRef;
                const J1939NodeType* pJ1939Node = DemPbCfgPtr->J1939Node;
                const uint8* Nodeindex = pJ1939Node[DemJ1939DTC_J1939NodeRef].NodeIDRef;
                uint8 NodeNum = pJ1939Node[DemJ1939DTC_J1939NodeRef].NodeNum;
                for (uint8 iloop = 0; iloop < NodeNum; iloop++)
                {
                    /*SWS_Dem_00971*/
                    J1939Dcm_DemTriggerOnDTCStatus(pDemObdDTC[DemObdDTCRef].DemJ1939DTCValue, *Nodeindex);
                    Nodeindex++;
                }
            }
#endif
            pEvent->OldUdsStatus = NewUdsStatus;
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF)
static void Dem_CDTCOverFlowCheck(Dem_EventIdType IntId)
{
    /* insert a entry that been displaced into entry memory as first entry, so its absolute time is minimum of all
     * entry. And update other absolute time of other entry by increment one  */
    Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
    uint16 TempRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
    if (TempRef != DEM_DTC_REF_INVALID)
    {
        const uint8* pMemDest =
            DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[TempRef].DemDTCAttributesRef].DemMemoryDestinationRef;
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
        for (uint8 iloop = 0; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#else
        uint8 iloop = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
        {
            uint8 MemDest = pMemDest[iloop];
            if ((DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC) != 0x00u)
                && (Dem_MemEntryGet(Dem_GetEventExternalId(IntId), MemDest) == NULL_PTR))
            {
                /*not stored in an event memory entry  UDS status bit 3 (ConfirmedDTC) set   gets qualified as passed*/
                Dem_EventMemEntryType* pEntry = Dem_MemEntryGet(0x00, MemDest);
                /*return NULL_PTR means no idle memory*/
                if (pEntry != NULL_PTR)
                {
                    /*SWS_Dem_00823] */
                    Dem_MemDestInfoType* pDemMemDestInfo = &DemMemDestInfo[MemDest];
                    uint8 EntryNum = DemMemDestCfg[MemDest].EntryNum;
                    const Dem_MemDestConfigType* pDemMemDestCfg = &DemMemDestCfg[MemDest];
                    if (pDemMemDestInfo->RecordNum < EntryNum)
                    {
                        pDemMemDestInfo->RecordNum++;
                    }
                    pEntry->EventId = Dem_GetEventExternalId(IntId);
                    for (uint8 jloop = 0; jloop < EntryNum; jloop++)
                    {
                        Dem_EventMemEntryType* pEntryList = &pDemMemDestCfg->EntryList[jloop];
                        /* Update absolute time of other entry */
                        pEntryList->AbsTime += 1;
                    }
                    pEntry->AbsTime = 1;
                }
            }
        }
    }
}
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF */
/*************************************************************************/
/*
 * Brief               Dem_EventTestPassed
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && pEventBuffer
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(void, DEM_CODE) Dem_EventTestPassed(Dem_EventIdType IntId)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
#if (DEM_COMPONENT_NUM > 0u)
    uint16 ComponentID = pEventCfg->DemComponentClassRef; /* PRQA S 2812 */ /* MISRA Dir 4.1 */
    if (ComponentID != DEM_COMPONENT_INVALID)                               /*check whether event ref the component*/
    {
        DemComponentStatusType* pComponentStatus = &DemComponentStatus[ComponentID];
        if (pComponentStatus->availability == TRUE) /*check the component availability*/
        {
            const DemComponentTypes* pComponent = DemPbCfgPtr->DemComponent;
            boolean allParentComponentpass = TRUE;
            DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_CONSECUTIVE_FAULT);
            if (pComponent[ComponentID].DemParentComponentRef != DEM_COMPONENT_INVALID)
            {
                uint16 LComponentID = ComponentID;
                uint16 DemParentComponentRef = pComponent[LComponentID].DemParentComponentRef;
                while ((DemParentComponentRef != DEM_COMPONENT_INVALID) && (allParentComponentpass == TRUE))
                {
                    if (DemComponentStatus[DemParentComponentRef].Status == TRUE)
                    {
                        allParentComponentpass = FALSE;
                    }
                    LComponentID = DemParentComponentRef; /* next parent component*/
                    DemParentComponentRef = pComponent[LComponentID].DemParentComponentRef;
                }
            }
            if (allParentComponentpass == TRUE)
            {
                /*SWS_Dem_01125*/
                pComponentStatus->Status = FALSE;
                pComponentStatus->FailurePriority = 0xFF;
#if (STD_ON == DEM_TRIGGER_FIM_REPORTS)
                (void)FiM_DemTriggerOnComponentStatus(Dem_GetEventExternalId(ComponentID), FALSE);
#endif /* STD_ON == DEM_TRIGGER_FIM_REPORTS */
            }
        }
    }
#endif /* DEM_COMPONENT_NUM > 0u */

#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    /*The bit is reset to 0 when the FDC10 reach the value -128.*/
    DEM_FLAGS_CLR(pEvent->StatusIndicator30, DEM_SI30_DTC_UC); /*bit 0*/
#endif                                                         /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
    DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC); /* bit 0 6 4*/
    DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_ACTIVE);
#if (DEM_OCC6EANLE == STD_ON)
    if (0x00u == DEM_FLAGS_ISSET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_THISOPISFAILED))
    {
        if (0x00u != DEM_FLAGS_ISSET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_OCC6CLR))
        {
            /* The counter shall be cleared in the beginning of the operation cycle following an operation
             * cycle where FDC10 did not reach the value +127 at any time but -128 (the counter shall
             * maintain its value if did not reach the value -128). */
            pEvent->OCC6 = 0;
        }
    }
#endif /* DEM_OCC6EANLE == STD_ON */

#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
    if ((0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC))
        && (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR)))
    {
        const Dem_IndicatorAttributeType* pWIRAttr;
        boolean allThreshold = FALSE;
        uint8 AttrNum = pEventCfg->AttrNum;
        uint16 AttrStartIndex = pEventCfg->AttrStartIndex;
        for (uint16 iloop = 0; iloop < AttrNum; iloop++)
        {
            pWIRAttr = &DemIndicatorAttribute[AttrStartIndex + iloop];
            if (0x00u != pWIRAttr->DemIndicatorHealingCycleCounterThreshold)
            {
                allThreshold = TRUE;
                break;
            }
        }
        if (FALSE == allThreshold) /* R19-11: SWS_Dem_01233*/
        {
            DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_WIR);
            for (uint8 iloop = 0; iloop < AttrNum; iloop++)
            {
                pWIRAttr = &DemIndicatorAttribute[AttrStartIndex + iloop];
                DemWIRStatus[pWIRAttr->DemIndicatorRef] = DEM_INDICATOR_OFF;
            }
        }
    }
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */

    if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u)
    {
#if (DEM_TRIGGERONPASSEDEANLE == STD_ON)
#if (DEM_EXTENDED_DATA_CLASS_NUM > 0u)
        /*SWS_Dem_01070*/
        Dem_EventDataStorageTrigger(IntId, DEM_TRIGGER_ON_PASSED);
#endif /* DEM_EXTENDED_DATA_CLASS_NUM > 0u */
#endif /* DEM_TRIGGERONPASSEDEANLE == STD_ON */
        DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
    }

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF)
    Dem_CDTCOverFlowCheck(IntId);
#endif                                  /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF */
    Dem_UpdateCombinedDtcStatus(IntId); /* update the combination event dtc status*/
    Dem_ResponseOnDtcStatusChange(IntId);
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
    (void)Dem_ClearPreStoreFF(Dem_GetEventExternalId(IntId)); /*SWS_Dem_00465*/
#endif                                                        /* DEM_MAX_NUMBER_PRESTORED_FF > 0u */
#if ((DEM_COMPONENT_NUM == 0u) && ((DEM_INDICATOR_NUM == 0u) || (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM == 0u)))
    DEM_UNUSED(pEventCfg);
#endif
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_OperationCycleStart
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OpId && IsRestart
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_OperationCycleStart(uint8 OpId, boolean IsRestart) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
        uint16 DemDTCRef = pEventCfg->DemDTCRef;
#if ((DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u) || (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u))
        uint8 AlgorithmType = pEventCfg->AlgorithmType;
        uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)||(DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
        Dem_EventHealingProcess(pEvent, OpId); /*SWS_Dem_00506*/
#if (DEM_OCC6EANLE == STD_ON)
        if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TNCTOC))
        {
            /* In last cycle, no fail occured. */
            DEM_FLAGS_SET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_OCC6CLR);
        }
        else if (
            (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC))
            && (0x00u == DEM_FLAGS_ISSET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_OCC6CLR)))
        {
            /* In last cycle , fail occured and OCC6 is not cleared */
            DEM_FLAGS_SET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_OCC6CLR);
        }
        else
        {
            /* idle */
        }
#endif /* DEM_OCC6EANLE == STD_ON */

        if (IsRestart == TRUE)
        {
            Dem_ClearUdsStatusOfPDTC(pEvent);
            Dem_EventAgingProcess(pEvent, OpId);
        }
        if (pEventCfg->DemOperationCycleRef == OpId)
        {
            /* req SWS_Dem_00679 Monitor re-initialization */
            Dem_CallbackInitMForEType InitMForE = pEventCfg->DemCallbackInitMForE;
            if (InitMForE != NULL_PTR)
            {
                (*InitMForE)(DEM_INIT_MONITOR_RESTART);
            }
            DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_FDC_TRIGGERED);
            DEM_FLAGS_CLR(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_FDC_TRIGGER);
            if (IsRestart == TRUE)
            {
                Dem_OperationCycleCounterProcess(pEvent); /*SWS_Dem_00773 SWS_Dem_00781 SWS_Dem_00777 */
            }
#if ((DEM_OCC6EANLE == STD_ON) || (DEM_OCC4EANLE == STD_ON))
            DEM_FLAGS_CLR(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_THISOPISFAILED);
#endif /* DEM_OCC6EANLE == STD_ON) || (DEM_OCC4EANLE == STD_ON */
            DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC);  /* bit1 1 => 0 SWS_Dem_00389 */
            DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC); /* bit6 0 => 1 SWS_Dem_00394 */
                                                                     /*SWS_Dem_00344*/
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
            /*The bit is reset to 0 at start of an operation cycle.*/
            DEM_FLAGS_CLR(pEvent->StatusIndicator30, DEM_SI30_DTC_UCTOC);
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u)
            if ((AlgorithmType == DEM_DEBOUNCE_COUNTER_BASED)
                && (AlgorithmIndex < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM))
            {
                DemDebounceCounterInfo[AlgorithmIndex].InternalDebounceCounter = 0;
            }
#endif /* DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
            if ((AlgorithmType == DEM_DEBOUNCE_TIME_BASE) && (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM))
            {
                Dem_DebounceTimeInfoType* pDemDebounceTimerInfo = &DemDebounceTimerInfo[AlgorithmIndex];
                pDemDebounceTimerInfo->Timeout = 0;
                pDemDebounceTimerInfo->Triggered = FALSE;
                pDemDebounceTimerInfo->CurStatus = DEM_EVENT_STATUS_PREPASSED;
            }
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
            if (DemDTCRef != DEM_DTC_REF_INVALID)
            {
                FDCInfo[DemDTCRef].MaxFDCDuringCurrentCycle = 0; /*SWS_Dem_00790*/
            }
        }
        /* update the combination event dtc status*/
        Dem_UpdateCombinedDtcStatus(iloop);
        /*first init shall not update and trigger the callback*/
        if (Dem_InitState != DEM_STATE_PRE_INIT)
        {
            Dem_ResponseOnDtcStatusChange(iloop);
        }
        pEventCfg++;
    }
    if (Dem_AgingCycle == OpId)
    {
        Dem_AgingCycle = DEM_OPERATION_CYCLE_INVALID;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_OperationCycleEnd
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OpId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_OperationCycleEnd(uint8 OpId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
        if (pEventCfg->DemOperationCycleRef == OpId)
        {
            /* Process Operation Cycle Counters */
            Dem_OperationCycleCounterProcess(pEvent); /*SWS_Dem_00773 SWS_Dem_00781 SWS_Dem_00777 */
        }
        Dem_EventAgingProcess(pEvent, OpId);
        Dem_ClearUdsStatusOfPDTC(pEvent);
        Dem_UpdateCombinedDtcStatus(iloop);   /*update the combination event dtc status*/
        Dem_ResponseOnDtcStatusChange(iloop); /*trigger ROE invoking*/
        pEventCfg++;
    }
    if (Dem_AgingCycle == OpId)
    {
        Dem_AgingCycle = DEM_OPERATION_CYCLE_INVALID;
    }
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) || (DEM_J1939_SUPPORT == STD_ON))
    Dem_CalOBDRelatedValue(OpId);
#endif
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               Dem_MemEntryAllocate
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && MemDestIndex
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_EventMemEntryType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR), DEM_CODE) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
Dem_MemEntryAllocate(Dem_EventIdType IntId, uint8 memDest) /* PRQA S 1505 */       /* MISRA Rule 8.7 */
{
    Dem_EventMemEntryType* pEntry;
    Dem_EventMemEntryType* ret = NULL_PTR;
    if (E_OK == Dem_CheckEntryAlreadyAllocated(IntId, memDest, &pEntry))
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
#if (DEM_COMPONENT_NUM > 0u)
        /*SWS_Dem_01130*/
        if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_CONSECUTIVE_FAULT) == 0x00u)
#endif /* DEM_COMPONENT_NUM > 0u */
        {
#if (DEM_STORAGE_CONDITION_NUM > 0u)
            if ((0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION))
                && (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u))
            {
                /*SWS_Dem_00458 SWS_Dem_00455 SWS_Dem_00591 */
                DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
            }
            else
#endif /* DEM_STORAGE_CONDITION_NUM > 0u */
            {
                /* SWS_Dem_00242 Defines the group of DTC that shall be disabled to store in event memory*/
                if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_DTC_SETTING))
                {
                    /* Entry already stored */
                    if (pEntry == NULL_PTR)
                    {
                        Dem_MemDestInfoType* pMem = &DemMemDestInfo[memDest];
                        pEntry = Dem_MemEntryGet(0x00, memDest); /*return NULL_PTR means no idle memory*/
                        if (pEntry == NULL_PTR)
                        {
                            pMem->OverFlow = TRUE;
#if (DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE)
                            /* SWS_Dem_00401 SWS_Dem_00402 SWS_Dem_00407 */
                            pEntry = Dem_EventDisplacementProcess(IntId, memDest);
#endif /* DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE */
                        }
#if (DEM_EXTERAL_DATA_ELEMENT_CLASS_NUM > 0u)
                        else
                        {
                            Dem_CallbackEventDataChangedType CallbackEventDataChanged =
                                DemPbCfgPtr->DemEventParameter[IntId].DemCallbackEventDataChanged;
                            /* SWS_Dem_00475 */
                            if (CallbackEventDataChanged != NULL_PTR)
                            {
                                (void)(*CallbackEventDataChanged)(Dem_GetEventExternalId(IntId));
                            }
                        }
#endif /* DEM_EXTERAL_DATA_ELEMENT_CLASS_NUM > 0u */
                        if (pEntry != NULL_PTR)
                        {
                            const Dem_MemDestConfigType* pMemDestCfg = &DemMemDestCfg[memDest];
                            uint8 EntryNum = pMemDestCfg->EntryNum;
                            ret = pEntry;
                            if (pMem->RecordNum < EntryNum)
                            {
                                pMem->RecordNum++;
                            }
                            pEntry->EventId = Dem_GetEventExternalId(IntId);
                            /* SWS_Dem_00412 search the time order,give the newer time order*/
                            pEntry->AbsTime = pMem->RecordNum;
#if ((DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u))
                            pEntry->FFNum = 0;
                            pEntry->LatestFF = 0;
#endif /* DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u */
                            /* req SWS_Dem_00523 */
                            pEvent->OccurrenceCounter = 0;
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
                            pEvent->CyclesSinceFirstFailed = 0; /* SWS_Dem_00776 */
#endif                                                          /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
#if ((DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON) || (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON))
                            DEM_FLAGS_SET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_CYCLECOUNTER);
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)|| (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
                            pEvent->CyclesSinceLastFailed = 0; /* SWS_Dem_00771 */
#endif                                                         /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
                            pEvent->FailureCounter = 0;        /* SWS_Dem_00780 */
                        }
                    }
                    else
                    {
                        ret = pEntry;
                        /* SWS_Dem_00787 */
                        if (DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE) != 0x00u)
                        {
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
                            /* SWS_Dem_00772 */
                            pEvent->CyclesSinceLastFailed = 0;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
                            /*Update the time order*/
                            Dem_EntryChronologicalOrderUpdate(IntId, memDest, pEntry);
                        }
                    }
                }
            }
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_MemEntryDelete
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      memDest
 * Param-Name[out]     None
 * Param-Name[in/out]  pEntry
 * Return              None
 */
/*************************************************************************/
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL void Dem_ClearEventRelateInformation(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    pEvent->FailureCounter = 0;
#if (DEM_OCC6EANLE == STD_ON)
    pEvent->OCC6 = 0;
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
    pEvent->OCC4 = 0;
#endif /* DEM_OCC4EANLE == STD_ON */
    pEvent->OccurrenceCounter = 0;
    pEvent->AgingCounter = 0;
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
    pEvent->CyclesSinceFirstFailed = 0;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
    pEvent->CyclesSinceLastFailed = 0;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if ((DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON) || (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON))
    DEM_FLAGS_CLR(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_CYCLECOUNTER);
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)|| (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
    pEvent->HealingCounter = 0;
    DEM_FLAGS_CLR(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_FDC_TRIGGER);
}

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_MemEntryDelete(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry, uint8 memDest)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    if (pEntry != NULL_PTR)
    {
        Dem_EventIdType EventId = pEntry->EventId;
        Dem_MemDestInfoType* pMemDestInfo = &DemMemDestInfo[memDest];
        const Dem_MemDestConfigType* pMemDestCfg = &DemMemDestCfg[memDest];
        uint8 EntryNum = pMemDestCfg->EntryNum;
        uint8 AbsTime = pEntry->AbsTime;
        Dem_EventMemEntryType* pEntryList = pMemDestCfg->EntryList;

        /*delete the time order and update others*/
        for (uint8 index = 0; index < EntryNum; index++)
        {
            if (AbsTime < pEntryList[index].AbsTime)
            {
                pEntryList[index].AbsTime--;
            }
        }
        pEntry->AbsTime = 0;
#if ((DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u))
        pEntry->FFNum = 0x00;
        pEntry->LatestFF = 0x00;
        Dem_MemSet((uint8*)pEntry->FFList, 0xFFu, sizeof(Dem_FreezeFrameInfoType) * DEM_MAX_NUMBER_FF_RECORDS);
#endif /* DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u */
#if (DEM_EXTENDED_DATA_CLASS_NUM > 0u)
#if (DEM_EXTENDED_DATA_MAX_LEN > 0u)
        Dem_MemSet(pEntry->ExtData, 0xFFu, DEM_EXTENDED_DATA_MAX_LEN);
#endif /* DEM_EXTENDED_DATA_MAX_LEN > 0u */
        Dem_MemSet(pEntry->ExtStatus, 0x00u, DEM_EXTENDED_DATA_MAX_REF_NUM_BYTE);
#endif /* DEM_EXTENDED_DATA_CLASS_NUM > 0u */
        if ((0u != EventId) && (EventId <= DEM_EVENT_PARAMETER_NUM))
        {
            /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
            Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(Dem_GetEventInternalId(EventId));
            /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
            Dem_ClearEventRelateInformation(pEvent);
        }
        pEntry->EventId = 0x00;
        if (pMemDestInfo->RecordNum > 0u)
        {
            pMemDestInfo->RecordNum--;
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (                                                                                                           \
    (((DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u)) \
     && (DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CONFIGURED))                               \
    || (DEM_EXTENDED_DATA_CLASS_NUM > 0u))
/*************************************************************************/
/*
 * Brief               Dem_EventDataStorageTrigger
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && pEventBuffer && Trigger
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(void, DEM_CODE)
Dem_EventDataStorageTrigger(Dem_EventIdType IntId, uint8 Trigger)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint16 TempRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
    if (TempRef != DEM_DTC_REF_INVALID)
    {
        const Dem_DTCAttributesType* pDTCAttr = Dem_EventDTCAttributesCfg(IntId);
        Dem_Pending = TRUE;
        const uint8* pMemDest = pDTCAttr->DemMemoryDestinationRef;
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
        for (uint8 iloop = 0; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#else
        uint8 iloop = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
        {
            uint8 MemDest = pMemDest[iloop];
            /* PRQA S 3415++ */ /* MISRA Rule 13.5 */
            if ((MemDest != DEM_MEM_DEST_INVALID)
                && (DEM_BITS_ISNSET(DemMemDestInfo[MemDest].DisableDTCRecordUpdate, TempRef)))
            /* PRQA S 3415-- */ /* MISRA Rule 13.5 */
            {
                Dem_EventMemEntryType* pEntry;
                if (Trigger == DEM_EVENT_MEMORY_ENTRY_STORAGE_TRIGGER)
                {
                    pEntry = Dem_MemEntryAllocate(IntId, MemDest);
                }
                else
                {
                    pEntry = Dem_MemEntryGet(Dem_GetEventExternalId(IntId), MemDest);
                }
                if (pEntry != NULL_PTR) /*whether get the entry to store*/
                {
#if (                                                                                                          \
    ((DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u)) \
    && (DEM_TYPE_OF_FREEZE_FRAME_RECORD_NUMERATION == DEM_FF_RECNUM_CONFIGURED))
                    Dem_FreezeFrameStorage(IntId, pEntry, Trigger);
#endif
#if (DEM_EXTENDED_DATA_CLASS_NUM > 0u)
                    Dem_ExtendedDataStorage(IntId, pEntry, Trigger);
#endif /* DEM_EXTENDED_DATA_CLASS_NUM > 0u */
#if (DEM_NVRAM_BLOCKID_NUM > 0u)
                    if ((pDTCAttr->DemImmediateNvStorage == TRUE)
                        && (DemEventRelateInformation[IntId].OccurrenceCounter < DEM_IMMEDIATE_NV_STORAGE_LIMIT))
                    {
#if (DEM_NVRAM_DIVADED == STD_ON)
                        Dem_IntWriteOneNvRAM(IntId);
#else
                        Dem_IntWriteNvRAM();
#endif /* DEM_NVRAM_DIVADED == STD_ON */
                    }
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
                }
            }
        }
        Dem_Pending = FALSE;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

#if (DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE)
/*************************************************************************/
/*
 * Brief               Dem_GetEventPriority
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) Dem_GetEventPriority(Dem_EventIdType IntId)
{
    uint8 res = 0xFF;
    uint16 ref = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;

    if (ref != DEM_DTC_REF_INVALID)
    {
        res = DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[ref].DemDTCAttributesRef].DemDTCPriority;
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE */
/*************************************************************************/
/*
 * Brief               Dem_EntryChronologicalOrderUpdate
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_EntryChronologicalOrderUpdate(
    Dem_EventIdType IntId,
    uint8 memDest,
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    uint8 EntryNum = DemMemDestCfg[memDest].EntryNum;
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
#endif
    Dem_EventMemEntryType* EntryList = DemMemDestCfg[memDest].EntryList;

    for (uint8 iloop = 0u; iloop < EntryNum; iloop++)
    {
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
        if (pEventParameter[Dem_GetEventInternalId(EntryList[iloop].EventId)].DemDTCRef
            == pEventParameter[Dem_GetEventInternalId(pEntry->EventId)].DemDTCRef)
#else
        if (pEntry->EventId == EntryList[iloop].EventId)
#endif
        {
            for (uint8 index = 0; index < EntryNum; index++)
            {
                uint8 AbsTime = EntryList[index].AbsTime;
                if (pEntry->AbsTime < AbsTime)
                {
                    EntryList[index].AbsTime--;
                }
            }
            pEntry->AbsTime = DemMemDestInfo[memDest].RecordNum;
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
            /*Update the DEM_EVENT_COMBINATION event new ID*/
            pEntry->EventId = Dem_GetEventExternalId(IntId);
#endif
            break;
        }
    }
#if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_ONSTORAGE)
    DEM_UNUSED(IntId);
#endif
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_CheckEntryAlreadyAllocated
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE) Dem_CheckEntryAlreadyAllocated(
    Dem_EventIdType IntId,
    uint8 memDest,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
        P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) * pEntry)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_OK;
    Dem_EventIdType EventId = Dem_GetEventExternalId(IntId);

#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
    Dem_EventMemEntryType* lEntry = DemMemDestCfg[memDest].EntryList; /* PRQA S 3678 */ /* MISRA Rule 8.13 */
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
    uint16 DemDTCRef = pEventParameter[IntId].DemDTCRef;
    *pEntry = NULL_PTR;
    for (uint8 iloop = 0u; (iloop < DemMemDestCfg[memDest].EntryNum) && (*pEntry == NULL_PTR); iloop++)
    {
        Dem_EventIdType EntryIntId = lEntry->EventId;
        Dem_EventIdType EntryEventId = Dem_GetEventInternalId(EntryIntId);
        /*check if event is already stored*/
        if ((EntryIntId != 0u) && (EntryIntId != EventId) && (DemDTCRef == pEventParameter[EntryEventId].DemDTCRef))
        {
            *pEntry = lEntry;
            /*SWS_Dem_01051*/
            if (DEM_FLAGS_ISSET(DemEventRelateInformation[EntryEventId].UdsStatus, DEM_UDS_STATUS_CDTC) != 0x00u)
            {
                ret = E_NOT_OK;
            }
        }
        if (lEntry->EventId == EventId)
        {
            *pEntry = lEntry;
        }
        lEntry++;
    }
#else
    *pEntry = Dem_MemEntryGet(EventId, memDest);
#endif /* DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_COMPONENT_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Dem_EventTestFailedProcessOfComponent
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_EventTestFailedProcessOfComponent(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg)
{

    uint16 ComponentID = pEventCfg->DemComponentClassRef;
    /*check whether event ref the component*/
    if (ComponentID != DEM_COMPONENT_INVALID)
    {
        /*check the component availability*/
        if (DemComponentStatus[ComponentID].availability == TRUE)
        {
#if (DEM_IMMEDITE_CHILD_COMPONENT_MAX_NUM > 0u)
            P2CONST(uint16, AUTOMATIC, DEM_CONST) pComponentIndex;
#endif /* DEM_IMMEDITE_CHILD_COMPONENT_MAX_NUM > 0u */
            const DemComponentTypes* pComponent = DemPbCfgPtr->DemComponent;
            const DemComponentTypes* OldpComponent = &pComponent[ComponentID];
            DemComponentStatusType* pComponentStatus;
            uint8 DemComponentPriority = pEventCfg->DemComponentPriority;
            uint16 ExtComponentID = Dem_GetEventExternalId(ComponentID);

            if (OldpComponent->DemParentComponentRef != DEM_COMPONENT_INVALID)
            {
                uint16 NewComponentID = ComponentID;
                while (NewComponentID != DEM_COMPONENT_INVALID)
                {
                    const DemComponentTypes* NewpComponent = &pComponent[NewComponentID];
                    pComponentStatus = &DemComponentStatus[NewComponentID];
                    /*SWS_Dem_01126 SWS_Dem_01127 SWS_Dem_01128*/
                    if (((pComponentStatus->Status == TRUE)
                         && (pComponentStatus->FailurePriority < DemComponentPriority)
                         && (NewpComponent->DemComponentIgnoresPriority == FALSE))
                        || ((NewpComponent->DemParentComponentRef != DEM_COMPONENT_INVALID)
                            && (DemComponentStatus[NewpComponent->DemParentComponentRef].Status == TRUE)))
                    {
                        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_CONSECUTIVE_FAULT);
                    }
                    /* next parent component*/
                    NewComponentID = pComponent[NewComponentID].DemParentComponentRef;
                }
                pComponentStatus = &DemComponentStatus[ComponentID];
                if (pComponentStatus->FailurePriority > DemComponentPriority)
                {
                    pComponentStatus->FailurePriority = DemComponentPriority;
                }
                if (pComponentStatus->Status == FALSE)
                {
                    DemComponentFailedCallbackFnc ComponentFailedFnc = OldpComponent->DemComponentFailedCallbackFnc;
                    pComponentStatus->Status = TRUE;
                    /*SWS_Dem_01133*/
                    if (ComponentFailedFnc != NULL_PTR)
                    {
                        (*ComponentFailedFnc)(ExtComponentID, TRUE);
                    }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
                    /*SWS_Dem_01132] */
                    (void)FiM_DemTriggerOnComponentStatus(ExtComponentID, TRUE);
#endif
                }
            }
            else
            {
                pComponentStatus = &DemComponentStatus[ComponentID];
                /*SWS_Dem_01126 SWS_Dem_01128*/
                if ((pComponentStatus->Status == TRUE) && (pComponentStatus->FailurePriority < DemComponentPriority)
                    && (OldpComponent->DemComponentIgnoresPriority == FALSE))
                {
                    DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_CONSECUTIVE_FAULT);
                    pComponentStatus->Status = TRUE;
                }
                else
                {
                    if (pComponentStatus->Status == FALSE)
                    {
                        DemComponentFailedCallbackFnc ComponentFailedFnc = OldpComponent->DemComponentFailedCallbackFnc;
                        pComponentStatus->Status = TRUE;
                        /*SWS_Dem_01133*/
                        if (ComponentFailedFnc != NULL_PTR)
                        {
                            (*ComponentFailedFnc)(ExtComponentID, TRUE);
                        }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
                        /*SWS_Dem_01132] */
                        (void)FiM_DemTriggerOnComponentStatus(ExtComponentID, TRUE);
#endif
                    }
                }
                if (pComponentStatus->FailurePriority > DemComponentPriority)
                {
                    pComponentStatus->FailurePriority = DemComponentPriority;
                }
            }
            /*SWS_Dem_01124*/
#if (DEM_IMMEDITE_CHILD_COMPONENT_MAX_NUM > 0u)
            pComponentIndex = OldpComponent->DemImmediateChildComponentRef;
            for (uint16 iloop = 0u;
                 (iloop < DEM_IMMEDITE_CHILD_COMPONENT_MAX_NUM) && (*pComponentIndex != DEM_COMPONENT_INVALID);
                 iloop++)
            {
                DemComponentStatus[*pComponentIndex].Status = TRUE;
                pComponentIndex++;
            }
#endif /* DEM_IMMEDITE_CHILD_COMPONENT_MAX_NUM > 0u */
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_COMPONENT_NUM > 0u */

#if (DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE)
/*************************************************************************/
/*
 * Brief               Dem_DeleteDisplacementEntry
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      InternalId && MemIndex
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dem_DeleteDisplacementEntry(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pResEntry, VAR(uint8, DEM_VAR) memDest)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Dem_EventIdType IntId = Dem_GetEventInternalId(pResEntry->EventId);
#if (                                                                                                          \
    (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE) || (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_ON) \
    || (DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT))
    Dem_EventRelateInformationType* NewpEvent = Dem_GetEventInfo(IntId);
#endif
    /* SWS_Dem_00409 Reset bit2 bit3 to 0 */
#if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
    uint16 DTCRef = pEventParameter[IntId].DemDTCRef;
    const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DTCRef];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
    const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
    const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
    const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
    for (uint16 iloop = 0; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
    {
        NewpEvent = Dem_GetEventInfo(*pDTCMapping);
#endif /* DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED */
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_ON)
        DEM_FLAGS_CLR(NewpEvent->UdsStatus, (DEM_UDS_STATUS_PDTC | DEM_UDS_STATUS_CDTC));
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_ON */
#if (DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
        DEM_FLAGS_CLR(NewpEvent->UdsStatus, DEM_UDS_STATUS_TFSLC);
#endif /* DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT */
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_DISABLED)
        Dem_ResponseOnDtcStatusChange(IntId);
#endif /* DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_DISABLED */
#if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
        Dem_ResponseOnDtcStatusChange(*pDTCMapping);
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
        pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
    }
#endif /* DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED */

    /* update the combination event dtc status*/
    Dem_UpdateCombinedDtcStatus(IntId);
    Dem_MemEntryDelete(pResEntry, memDest);
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventDisplacementProcess
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      InternalId && MemIndex
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_EventMemEntryType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR), DEM_CODE) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
    Dem_EventDisplacementProcess(Dem_EventIdType InternalId, uint8 memDest)
{
    /* Search entries with lowest priority */
    Dem_EventMemEntryType* pResEntry = NULL_PTR;
    const Dem_MemDestConfigType* pMemDestCfg = &DemMemDestCfg[memDest];
    Dem_EventMemEntryType* pEntry = pMemDestCfg->EntryList;
    uint8 EntryNum = pMemDestCfg->EntryNum;
    uint8 EventNewPriority = Dem_GetEventPriority(InternalId);
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
#if (DEM_EVENT_DISPLACEMENT_STRATEGY == DEM_DISPLACEMENT_FULL)
    boolean PassiveFound = FALSE;
#endif
    boolean LowPriorityFound = FALSE;
    const Dem_MemDestInfoType* pMemDestInfo = &DemMemDestInfo[memDest];

    for (uint16 iloop = 0u; iloop < EntryNum; iloop++)
    {
        /* find the needed entry in the Entry list */
        uint16 TempEventIntId = Dem_GetEventInternalId(pEntry->EventId);
        uint8 EntryPriority = Dem_GetEventPriority(TempEventIntId);
        uint16 DTCRef = pEventParameter[TempEventIntId].DemDTCRef;
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(TempEventIntId);
        /* Check CurrentDTC Disable Record Update */
        if (DEM_BITS_ISSET(pMemDestInfo->DisableDTCRecordUpdate, DTCRef))
        {
            pEntry++;
        }
#if (                                                                                     \
    ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU)) \
    && (DEM_OBD_EVENT_DISPLACEMENT == STD_ON))
        /* SWS_Dem_00695 */
        /* PRQA S 3415++ */ /* MISRA Rule 13.5 */
        else if (
            (DTCRef != DEM_DTC_REF_INVALID) && (DemPbCfgPtr->DemDTC[DTCRef].DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
            && (
#if (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u)
                (Dem_CheckEventAllIndicator(TempEventIntId) == FALSE) ||
#endif /* DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
                ((pEntry->FFNum != 0u) && (EntryPriority <= EventNewPriority))
                || (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC))))
        /* PRQA S 3415-- */ /* MISRA Rule 13.5 */
        {
            pEntry++;
        }
#endif
        else
        {
#if (DEM_EVENT_DISPLACEMENT_STRATEGY == DEM_DISPLACEMENT_FULL)
            /* SWS_Dem_00403 */
            if (EventNewPriority <= EntryPriority)
            {
                /* SWS_Dem_00404*/
                if (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ACTIVE))
                {
                    if (PassiveFound == FALSE)
                    {
                        /* The First Passive Mode Entry Found */
                        pResEntry = pEntry;
                        PassiveFound = TRUE;
                    }
                    else
                    {
                        /* SWS_Dem_00405 Already found  Get The Oldest One */
                        if (pResEntry->AbsTime > pEntry->AbsTime)
                        {
                            pResEntry = pEntry;
                        }
                    }
                }
                /* not found passive */
                if (PassiveFound == FALSE)
                {
#endif
                    if (EventNewPriority < EntryPriority)
                    {
                        /* SWS_Dem_00403 */
                        if (LowPriorityFound == FALSE)
                        {
                            LowPriorityFound = TRUE;
                            pResEntry = pEntry;
                        }
                        /* SWS_Dem_00405 Already found Get The Oldest One*/
                        if (pResEntry->AbsTime > pEntry->AbsTime)
                        {
                            pResEntry = pEntry;
                        }
                    }
                    else
                    {
                        /* SWS_Dem_00692 TestNotCompletedThisOperationCycle bit == 1 */
                        if (LowPriorityFound == FALSE)
                        {
                            if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC))
                            {
                                if (pResEntry == NULL_PTR)
                                {
                                    pResEntry = pEntry;
                                }
                                /* SWS_Dem_00405 Already found  Get The Oldest One*/
                                if (pResEntry->AbsTime > pEntry->AbsTime)
                                {
                                    pResEntry = pEntry;
                                }
                            }
                        }
                    }
#if (DEM_EVENT_DISPLACEMENT_STRATEGY == DEM_DISPLACEMENT_FULL)
                }
            }
#endif
            pEntry++;
        }
    }
    /* SWS_Dem_00408 */
    if ((pResEntry != NULL_PTR)
        && (pEventParameter[Dem_GetEventInternalId(pResEntry->EventId)].DemDTCRef != DEM_DTC_REF_INVALID))
    {
        Dem_DeleteDisplacementEntry(pResEntry, memDest);
    }
    return pResEntry;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_EVENT_DISPLACEMENT_STRATEGY != DEM_DISPLACEMENT_NONE */

#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
/*************************************************************************/
/*
 * Brief               Dem_CheckWIROn
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEvent && pEventCfg
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              boolean
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(boolean, DEM_CODE) Dem_CheckWIROn(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg)
{
    boolean res = FALSE;
    uint8 AttrNum = pEventCfg->AttrNum;
    const Dem_IndicatorAttributeType* pWIRAttr = &DemIndicatorAttribute[pEventCfg->AttrStartIndex];
    uint16 OBDGroupingAssociativeEventsRef = pEventCfg->DemOBDGroupingAssociativeEventsRef;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
    uint16 DemDTCRef = pEventCfg->DemDTCRef;
    const Dem_DTCType* pDTCCfg = DemPbCfgPtr->DemDTC;
    const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
    for (uint16 iloop = 0; iloop < AttrNum; iloop++)
    {
        uint8 FailureThreshold = pWIRAttr->DemIndicatorFailureCycleCounterThreshold;
        /*reach the threshold activate the mil SWS_Dem_00967 SWS_Dem_00501*/
        if ((FailureThreshold <= pEvent->FailureCounter)
            || ((OBDGroupingAssociativeEventsRef != DEM_EVENT_PARAMETER_INVALID)
                && (FailureThreshold <= DemEventRelateInformation[OBDGroupingAssociativeEventsRef].FailureCounter)))
        {
            uint8 DemIndicatorRef = pWIRAttr->DemIndicatorRef;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
            if (DemDTCRef != DEM_DTC_REF_INVALID)
            {
                const Dem_DTCType* pDTC = &pDTCCfg[DemDTCRef];
                uint16 DemObdDTCRef = pDTC->DemObdDTCRef;
                uint32 DtcValue = pDTC->DemDtcValue;
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
                res = TRUE;
                DemWIRStatus[DemIndicatorRef] = pWIRAttr->DemIndicatorBehaviour;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
                if ((((DtcValue < 0xFFFF33uL) && (DtcValue > 0uL))
                     || ((DEM_OBD_DTC_INVALID != DemObdDTCRef)
                         && ((pObdDTC[DemObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID)
                             || (pObdDTC[DemObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID)))))
                {
                    /* SWS_Dem_01139 SWS_Dem_00703 */
                    Dem_UpdateOBDMilStatus(DemIndicatorRef, pEvent->IntId);
                }
            }
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
        }
        pWIRAttr++;
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_CheckWIROff
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEvent && pEventCfg
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              boolean
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(boolean, DEM_CODE) Dem_CheckWIROff(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg)
{
    boolean res = TRUE;
    uint8 AttrNum = pEventCfg->AttrNum;

    const Dem_IndicatorAttributeType* pWIRAttr = &DemIndicatorAttribute[pEventCfg->AttrStartIndex];
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
    uint16 DemDTCRef = pEventCfg->DemDTCRef;
    const Dem_DTCType* pDTCCfg = DemPbCfgPtr->DemDTC;
    const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */

    for (uint16 iloop = 0; iloop < AttrNum; iloop++)
    {
        uint8 HealingThreshold = pWIRAttr->DemIndicatorHealingCycleCounterThreshold;
        if (HealingThreshold <= pEvent->HealingCounter) /*SWS_Dem_00503] */
        {
            uint8 IndicatorRef = pWIRAttr->DemIndicatorRef;
            boolean Find = FALSE;

            for (uint16 index = 0; ((index < DEM_EVENT_PARAMETER_NUM) && (Find == FALSE)); index++)
            {
                for (uint16 cnt = 0; ((cnt < DemPbCfgPtr->DemEventParameter[index].AttrNum) && (Find == FALSE)); cnt++)
                {
                    if ((IndicatorRef
                         == DemIndicatorAttribute[DemPbCfgPtr->DemEventParameter[index].AttrStartIndex + cnt]
                                .DemIndicatorRef)
                        && (0x00u != DEM_FLAGS_ISSET(DemEventRelateInformation[index].UdsStatus, DEM_UDS_STATUS_WIR))
                        && (DemEventRelateInformation[index].HealingCounter
                            < DemIndicatorAttribute[DemPbCfgPtr->DemEventParameter[index].AttrStartIndex + cnt]
                                  .DemIndicatorHealingCycleCounterThreshold))
                    {
                        Find = TRUE;
                    }
                }
            }
            if (Find == FALSE)
            {
                DemWIRStatus[IndicatorRef] = DEM_INDICATOR_OFF;
            }
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
            if (DemDTCRef != DEM_DTC_REF_INVALID)
            {
                const Dem_DTCType* pDTC = &pDTCCfg[DemDTCRef];
                uint16 DemObdDTCRef = pDTC->DemObdDTCRef;
                uint32 DtcValue = pDTC->DemDtcValue;
                if ((((DtcValue < 0xFFFF33uL) && (DtcValue > 0uL))
                     || ((DEM_OBD_DTC_INVALID != DemObdDTCRef)
                         && ((pObdDTC[DemObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID)
                             || (pObdDTC[DemObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID)))))
                {
                    /* SWS_Dem_01139 SWS_Dem_00703 */
                    Dem_UpdateOBDMilStatus(IndicatorRef, pEvent->IntId);
                }
            }
#endif
        }
        else
        {
            res = FALSE;
        }
        pWIRAttr++;
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Dem_ClearUdsStatusOfPDTC
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OpId
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(void, DEM_CODE)
    Dem_ClearUdsStatusOfPDTC(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    if ((0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC))
        && (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC))
        && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC)))
    {
        DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC);
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventAgingProcess
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OpId
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dem_EventAgingProcess(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent, uint8 OpId)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Dem_EventIdType IntId = pEvent->IntId;
    Dem_EventIdType EventId = Dem_GetEventExternalId(IntId);
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
    const Dem_EventParameterType* pEventCfg = &pEventParameter[IntId];

    Dem_Pending = TRUE;
    if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC))
    {
        uint16 DemDTCRef = pEventCfg->DemDTCRef;
        if ((0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR)) && (DemDTCRef != DEM_DTC_REF_INVALID))
        {
            /* SWS_Dem_00698 aging */
            const Dem_DTCAttributesType* pDTCAttrCfg = Dem_EventDTCAttributesCfg(IntId);
            const uint8* pMemDest = pDTCAttrCfg->DemMemoryDestinationRef;
            uint8 DemOperationCycleRef = pEventCfg->DemOperationCycleRef;
            uint8 DemAgingCycleCounterThreshold = pDTCAttrCfg->DemAgingCycleCounterThreshold;
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
            for (uint8 iloop = 0; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#else
            uint8 iloop = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
            {
                uint8 MemDest = pMemDest[iloop];
                Dem_EventMemEntryType* pEntry = NULL_PTR;
                if (MemDest != DEM_MEM_DEST_INVALID)
                {
                    pEntry = Dem_MemEntryGet(EventId, MemDest);
                }
                if (pEntry != NULL_PTR)
                {
                    boolean OCStatusFlag = DEM_BITS_ISNSET(DemOperationCycleStatus, DemOperationCycleRef);
                    if (((pDTCAttrCfg->DemAgingCycleRef == OpId) || (Dem_AgingCycle == OpId)
                         || ((DemOperationCycle[DemOperationCycleRef].DemOperationCycleType == DEM_OPCYC_OBD_DCY)
                             && (OCStatusFlag) && (DemOperationCycle[OpId].DemOperationCycleType == DEM_OPCYC_WARMUP)))
                        && (pDTCAttrCfg->DemAgingAllowed == TRUE)
#if (DEM_AGING_REQUIERES_TESTED_CYCLE == STD_ON)
                        /* SWS_Dem_00490 SWS_Dem_00826 */
                        && (DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC) == 0x00u)
#endif /* DEM_AGING_REQUIERES_TESTED_CYCLE == STD_ON */
                    )
                    {
                        /* SWS_Dem_00985 SWS_Dem_00494 */
                        if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
                        {
                            uint8 AgingCycleCounterThreshold;
                            pEvent->AgingCounter++; /*SWS_Dem_00489*/
#if (DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
                            uint8 DemAgingCycleCounterThresholdForTFSLC =
                                pDTCAttrCfg->DemAgingCycleCounterThresholdForTFSLC;
                            AgingCycleCounterThreshold =
                                (DemAgingCycleCounterThreshold > DemAgingCycleCounterThresholdForTFSLC)
                                    ? DemAgingCycleCounterThreshold
                                    : DemAgingCycleCounterThresholdForTFSLC;
#else
                            AgingCycleCounterThreshold = DemAgingCycleCounterThreshold;
#endif /* DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT */
#if (DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
                            if (pEvent->AgingCounter >= DemAgingCycleCounterThresholdForTFSLC)
                            {
                                /* SWS_Dem_01054 */
                                DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TFSLC);
                            }
#endif /* DEM_STATUS_BIT_HANDLING_TEST_FAILED_SINCE_LAST_CLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT */

                            /* SWS_Dem_00391 */
                            if (pEvent->AgingCounter >= DemAgingCycleCounterThreshold)
                            {
#if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
                                /* clear bit3 at next operation cycle end */
                                /* SWS_Dem_00443 */
                                const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DemDTCRef];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                                const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                                const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
                                const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                                for (uint16 iloop = 0u; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                                {
                                    DEM_FLAGS_CLR(
                                        DemEventRelateInformation[*pDTCMapping].UdsStatus,
                                        DEM_UDS_STATUS_CDTC);
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                                    pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                                }
#endif /* DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
                                /*bit 3: set to 1 when the DTC is aged*/
                                DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_AGED);
                                /*bit 7: The bit is reset to 0 when DTC is aged*/
                                DEM_FLAGS_CLR(pEvent->StatusIndicator30, DEM_SI30_DTC_TSFLC);
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
                                /* SWS_Dem_00498 */
                                DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC);
                            }
                            if (pEvent->AgingCounter >= AgingCycleCounterThreshold)
                            {
                                if (MemDest != DEM_MEM_DEST_INVALID)
                                {
                                    /* SWS_Dem_00493 SWS_Dem_01075 */
                                    Dem_MemEntryDelete(pEntry, MemDest);
                                }
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF)
                                for (uint16 index = 0; index < DEM_EVENT_PARAMETER_NUM; index++)
                                {
                                    /* SWS_Dem_00824 */
                                    Dem_CDTCOverFlowCheck(index);
                                }
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW == STD_OFF */
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        pEvent->HealingCounter = 0;
        pEvent->AgingCounter = 0;
    }
    Dem_Pending = FALSE;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventHealingProcess
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OpId
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dem_EventHealingProcess(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent, uint8 OpId)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC))
    {
        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR))
        {
            /* healing */
            const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[pEvent->IntId];
            uint8 DemOperationCycleRef = pEventCfg->DemOperationCycleRef;
            boolean OCStatusFlag = DEM_BITS_ISNSET(DemOperationCycleStatus, DemOperationCycleRef);
            pEvent->AgingCounter = 0;
            if (((DemOperationCycleRef == OpId)
                 || ((DemOperationCycle[DemOperationCycleRef].DemOperationCycleType == DEM_OPCYC_OBD_DCY)
                     && (OCStatusFlag)
                     && (DemOperationCycle[OpId].DemOperationCycleType == DEM_OPCYC_WARMUP))) /*SWS_Dem_01056]*/
                && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC)))
            {
                pEvent->HealingCounter++;
#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
                if (TRUE == Dem_CheckWIROff(pEvent, pEventCfg))
                {
                    /* SWS_Dem_00533 */
                    DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_WIR);
                }
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
            }
        }
    }
    else
    {
        pEvent->HealingCounter = 0;
        pEvent->AgingCounter = 0;
    }
    return;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Dem_OperationCycleCounterProcess
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_OperationCycleCounterProcess(Dem_EventRelateInformationType* pEvent)
{
    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC))
    {
        if (pEvent->FailureCounter < 0xFFu)
        {
            /* SWS_Dem_00782 */
            pEvent->FailureCounter++;
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
            /* Test Failed This Operation Cycle */
            pEvent->CyclesSinceLastFailed = 0u;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
        }
    }
#if ((DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON) || (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON))
    if (0x00u != (DEM_FLAGS_ISSET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_CYCLECOUNTER)))
    {
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
        if (pEvent->CyclesSinceFirstFailed < 0xFFu)
        {
            /* SWS_Dem_00778 */
            pEvent->CyclesSinceFirstFailed++;
        }
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
        if (pEvent->CyclesSinceLastFailed < 0xFFu)
        {
            /* SWS_Dem_00774 */
            pEvent->CyclesSinceLastFailed++;
        }
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
    }
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)|| (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_EventStatusProcessByDTC(
    uint16 dtcIndex,
    uint16 iloop,
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
    if (pEventParameter[iloop].DemEventAvailable == TRUE)
    {
        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE);
        if (DEM_DTC_REF_INVALID != dtcIndex)
        {
            DemDTCGeneralStatus[dtcIndex].SuppressionStatus = FALSE;
        }
    }
    else
    {
        if (DEM_DTC_REF_INVALID != dtcIndex)
        {
            /* SWS_Dem_00915 */
            const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[dtcIndex];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
            const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
            const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
            const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
            DemDTCGeneralStatus[dtcIndex].SuppressionStatus = TRUE;
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
            for (uint16 iloop = 0u; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
            {
                if (pEventParameter[*pDTCMapping].DemEventAvailable == TRUE)
                {
                    DemDTCGeneralStatus[dtcIndex].SuppressionStatus = FALSE;
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                    break;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                }
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
            }
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_NVRAM_BLOCKID_NUM > 0u)
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Dem_CopyInfoFromEntry
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CopyInfoFromInfo(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventRelateInformationType, AUTOMATIC, DEM_APPL_DATA) Info,
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_APPL_DATA) Entry)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Entry->UdsStatus = Info->UdsStatus;
    Entry->AgingCounter = Info->AgingCounter;
    Entry->OccurrenceCounter = Info->OccurrenceCounter;
    Entry->HealingCounter = Info->HealingCounter;
    Entry->FailureCounter = Info->FailureCounter;
#if (DEM_OCC6EANLE == STD_ON)
    Entry->OCC6 = Info->OCC6;
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
    Entry->OCC4 = Info->OCC4;
#endif /* DEM_OCC4EANLE == STD_ON */
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
    Entry->CyclesSinceFirstFailed = Info->CyclesSinceFirstFailed;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
    Entry->CyclesSinceLastFailed = Info->CyclesSinceLastFailed;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if ((DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON) || (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON))
    Entry->EventStatusFlag = Info->EventStatusFlag;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)|| (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    Entry->StatusIndicator30 = Info->StatusIndicator30;
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
}

#if (DEM_NVRAM_DIVADED == STD_ON)
/*************************************************************************/
/*
 * Brief               Dem_IntWriteOneNvRAM
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_IntWriteOneNvRAM(uint16 IntId)
{
    uint16 blockRef;
    uint8 DemMemDestindex;
    uint16 iloop = 0;
    uint16 tempEventId = 0;
    uint16 blockIndex = 0;
    for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
    {
        if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
        {
            for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY; iloop++)
            {
                tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                if (tempEventId != 0u)
                {
                    tempEventId = tempEventId - 1u;
                    if (IntId == tempEventId)
                    {
                        Dem_CopyInfoFromInfo(
                            &DemEventRelateInformation[tempEventId],
                            &DemMemDestCfg[DemMemDestindex].EntryList[iloop]);
                        blockRef = DemNvRamBlockId[blockIndex];
                        Dem_MemCopy(
                            NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
                            &DemMemDestCfg[DemMemDestindex].EntryList[iloop],
                            ENTRY_STORAGE_LEN);
                        (void)NvM_CancelJobs(blockRef);
                        (void)NvM_WriteBlock(blockRef, NULL_PTR);
                        break;
                    }
                }
                blockIndex++;
            }
            break;
        }
    }
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT > 0)
    for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
    {
        if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
        {
            for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT; iloop++)
            {
                tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                if (tempEventId != 0u)
                {
                    tempEventId = tempEventId - 1u;
                    if (IntId == tempEventId)
                    {
                        Dem_CopyInfoFromInfo(
                            &DemEventRelateInformation[tempEventId],
                            &DemMemDestCfg[DemMemDestindex].EntryList[iloop]);
                        blockRef = DemNvRamBlockId[blockIndex];
                        Dem_MemCopy(
                            NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
                            &DemMemDestCfg[DemMemDestindex].EntryList[iloop],
                            ENTRY_STORAGE_LEN);
                        (void)NvM_CancelJobs(blockRef);
                        (void)NvM_WriteBlock(blockRef, NULL_PTR);
                        break;
                    }
                }
                blockIndex++;
            }
            break;
        }
    }
#endif
}
#endif /* DEM_NVRAM_DIVADED == STD_ON */

/*************************************************************************/
/*
 * Brief               Dem_IntWriteNvRAM
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
FUNC(void, DEM_CODE) Dem_IntWriteNvRAM(void)
{
    uint16 blockRef;
    uint8 DemMemDestindex;
    uint16 iloop;
    uint16 tempEventId = 0;
    uint16 blockIndex = 0;
#if (DEM_NVRAM_DIVADED == STD_ON)
    for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
    {
        if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
        {
            for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY; iloop++)
            {
                tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                if (tempEventId != 0u)
                {
                    tempEventId = tempEventId - 1u;
                    Dem_CopyInfoFromInfo(
                        &DemEventRelateInformation[tempEventId],
                        &DemMemDestCfg[DemMemDestindex].EntryList[iloop]);
                }
                blockRef = DemNvRamBlockId[blockIndex];
                blockIndex++;
                Dem_MemCopy(
                    NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
                    (const uint8*)&DemMemDestCfg[DemMemDestindex].EntryList[iloop],
                    ENTRY_STORAGE_LEN);
                (void)NvM_CancelJobs(blockRef);
                (void)NvM_WriteBlock(blockRef, NULL_PTR);
            }
            break;
        }
    }
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT > 0)
    for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
    {
        if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
        {
            for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT; iloop++)
            {
                tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                if (tempEventId != 0u)
                {
                    tempEventId = tempEventId - 1u;
                    Dem_CopyInfoFromInfo(
                        &DemEventRelateInformation[tempEventId],
                        &DemMemDestCfg[DemMemDestindex].EntryList[iloop]);
                }
                blockRef = DemNvRamBlockId[blockIndex];
                blockIndex++;
                Dem_MemCopy(
                    NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
                    (const uint8*)&DemMemDestCfg[DemMemDestindex].EntryList[iloop],
                    ENTRY_STORAGE_LEN);
                (void)NvM_CancelJobs(blockRef);
                (void)NvM_WriteBlock(blockRef, NULL_PTR);
            }
            break;
        }
    }
#endif
#else
    for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY; iloop++)
    {
        /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
        for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
        /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
        {
            if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
            {
                DemEventMemoryEntryStorage[iloop] = DemMemDestCfg[DemMemDestindex].EntryList[iloop];
                tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
            }
        }
        if (tempEventId != 0u)
        {
            tempEventId = tempEventId - 1u;
            Dem_CopyInfoFromInfo(&DemEventRelateInformation[tempEventId], &DemEventMemoryEntryStorage[iloop]);
        }
    }
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT > 0)
    for (; iloop < ENTRY_STORAGE_NUM; iloop++)
    {
        for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
        {
            if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
            {
                DemEventMemoryEntryStorage[iloop] =
                    DemMemDestCfg[DemMemDestindex].EntryList[iloop - DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY];
                tempEventId =
                    DemMemDestCfg[DemMemDestindex].EntryList[iloop - DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY].EventId;
            }
        }
        if (tempEventId != 0u)
        {
            tempEventId = tempEventId - 1u;
            Dem_CopyInfoFromInfo(&DemEventRelateInformation[tempEventId], &DemEventMemoryEntryStorage[iloop]);
        }
    }
#endif
    blockRef = DemNvRamBlockId[blockIndex];
    blockIndex++;
    Dem_MemCopy(
        NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
        (const uint8*)DemEventMemoryEntryStorage,
        TOTAL_ENTRY_STORAGE_LEN);
    (void)NvM_CancelJobs(blockRef);
    (void)NvM_WriteBlock(blockRef, NULL_PTR);
#endif

    /* req SWS_Dem_00525 SWS_Dem_00389 SWS_Dem_01183 SWS_Dem_00391 SWS_Dem_00392 SWS_Dem_00393
     * SWS_Dem_00394 SWS_Dem_00395*/
    for (iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        DemEventRelateInformationStorage.UdsStatus[iloop] = DemEventRelateInformation[iloop].UdsStatus;
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
        DemEventRelateInformationStorage.StatusIndicator30[iloop] = DemEventRelateInformation[iloop].StatusIndicator30;
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
#if (DEM_DEBOUNCE_COUNTER_STORAGE_NUM > 0)
        /*SWS_Dem_00674*/
        if (DemPbCfgPtr->DemDebounceCounterBasedClass[DemPbCfgPtr->DemEventParameter[iloop].AlgorithmRef]
                .DemDebounceCounterStorage
            == TRUE)
        {
            DemEventRelateInformationStorage.DebounceCounter[iloop] =
                DemDebounceCounterInfo[DemPbCfgPtr->DemEventParameter[iloop].AlgorithmIndex].InternalDebounceCounter;
        }
#endif
    }
#if (DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON)
    for (iloop = 0; iloop < DEM_DTC_NUM; iloop++)
    {
        DemEventRelateInformationStorage.MaxFDCSinceLastClear[iloop] = FDCInfo[iloop].MaxFDCSinceLastClear;
    }
#endif /*DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON  */
#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)
    /* req SWS_Dem_00577*/
    for (iloop = 0; iloop < DEM_OPERATION_CYCLE_NUM_BYTE; iloop++)
    {
        DemEventRelateInformationStorage.DemOperationCycleStatus[iloop] = DemOperationCycleStatus[iloop];
    }
#endif
    DemEventRelateInformationStorage.FirstDtcConfirmed = DemDTCByOccurrenceTimeInfo.FirstDtcConfirmed;
    DemEventRelateInformationStorage.FirstFailed = DemDTCByOccurrenceTimeInfo.FirstFailed;
    DemEventRelateInformationStorage.MostRecDtcConfirmed = DemDTCByOccurrenceTimeInfo.MostRecDtcConfirmed;
    DemEventRelateInformationStorage.MostRecentFailed = DemDTCByOccurrenceTimeInfo.MostRecentFailed;

    blockRef = DemNvRamBlockId[blockIndex];
    Dem_MemCopy(
        NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
        (const uint8*)&DemEventRelateInformationStorage,
        sizeof(Dem_EventRelateInformationStorageType));
    (void)NvM_CancelJobs(blockRef);
    (void)NvM_WriteBlock(blockRef, NULL_PTR);

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    DemOBDDataStorage.IgnUpCycleCounter = IgnUpCycleCounter;
    DemOBDDataStorage.ContinuousMICounter = ContinuousMICounter;
    DemOBDDataStorage.WarmUpCycleCounter = WarmUpCycleCounter;
    DemOBDDataStorage.OBDDistanceMILOn = OBDDistanceMILOn;
    DemOBDDataStorage.DistSinceDtcCleared = DistSinceDtcCleared;
    DemOBDDataStorage.OBDTimeMILOn = OBDTimeMILOn;
    DemOBDDataStorage.OBDTimeDTCClear = OBDTimeDTCClear;
    DemOBDDataStorage.OBDB1Counter = OBDB1Counter;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
    DemOBDDataStorage.MasterContinuousMICounter = MasterContinuousMICounter;
#endif
    blockIndex++;
    blockRef = DemNvRamBlockId[blockIndex];
    Dem_MemCopy(
        NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
        (const uint8*)&DemOBDDataStorage,
        sizeof(DemOBDDataStorageType));
    (void)NvM_CancelJobs(blockRef);
    (void)NvM_WriteBlock(blockRef, NULL_PTR);
#endif
}

/*************************************************************************/
/*
 * Brief               Dem_CopyInfoFromEntry
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CopyInfoFromEntry(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_APPL_DATA) Info,
    P2CONST(Dem_EventMemEntryType, AUTOMATIC, DEM_APPL_DATA) Entry)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Info->UdsStatus = Entry->UdsStatus;
    Info->AgingCounter = Entry->AgingCounter;
    Info->OccurrenceCounter = Entry->OccurrenceCounter;
    Info->HealingCounter = Entry->HealingCounter;
    Info->FailureCounter = Entry->FailureCounter;
#if (DEM_OCC6EANLE == STD_ON)
    Info->OCC6 = Entry->OCC6;
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
    Info->OCC4 = Entry->OCC4;
#endif /* DEM_OCC4EANLE == STD_ON */
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
    Info->CyclesSinceFirstFailed = Entry->CyclesSinceFirstFailed;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
    Info->CyclesSinceLastFailed = Entry->CyclesSinceLastFailed;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if ((DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON) || (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON))
    Info->EventStatusFlag = Entry->EventStatusFlag;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)|| (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    Info->StatusIndicator30 = Entry->StatusIndicator30;
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
}

/*************************************************************************/
/*
 * Brief               Dem_IntReadNvRAM
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  pEvent
 * Return              None
 */
/*************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_IntReadNvRAM(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Std_ReturnType retVal = E_NOT_OK;
    uint16 iloop;
    uint16 tempEventId = 0;
    uint16 blockIndex = 0;
    uint16 blockRef;
    NvM_RequestResultType RequestResultPtr;
    uint8 DemMemDestindex;
#if (DEM_NVRAM_DIVADED == STD_ON)
    /*the NvRAM data should be validated*/
    for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY; iloop++)
    {
        blockRef = DemNvRamBlockId[blockIndex];
        blockIndex++;
        (void)NvM_GetErrorStatus(blockRef, &RequestResultPtr);
        if (RequestResultPtr == NVM_REQ_OK)
        {
            for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
            {
                if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
                {
                    Dem_MemCopy(
                        (uint8*)&DemMemDestCfg[DemMemDestindex].EntryList[iloop],
                        (const uint8*)NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
                        ENTRY_STORAGE_LEN);
                    tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                    break;
                }
            }
            if ((tempEventId != 0u) && (tempEventId <= DEM_EVENT_PARAMETER_NUM))
            {
                tempEventId = tempEventId - 1u;
                Dem_CopyInfoFromEntry(
                    &DemEventRelateInformation[tempEventId],
                    &DemMemDestCfg[DemMemDestindex].EntryList[iloop]);
                retVal = E_OK;
                DemMemDestInfo[DemMemDestindex].RecordNum++;
            }
            else
            {
                DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId = 0u;
            }
        }
    }
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT > 0)
    for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT; iloop++)
    {
        blockRef = DemNvRamBlockId[blockIndex];
        blockIndex++;
        (void)NvM_GetErrorStatus(blockRef, &RequestResultPtr);
        if (RequestResultPtr == NVM_REQ_OK)
        {
            for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
            {
                if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
                {
                    Dem_MemCopy(
                        (uint8*)&DemMemDestCfg[DemMemDestindex].EntryList[iloop],
                        (const uint8*)NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
                        ENTRY_STORAGE_LEN);
                    tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                    break;
                }
            }
            if ((tempEventId != 0u) && (tempEventId <= DEM_EVENT_PARAMETER_NUM))
            {
                tempEventId = tempEventId - 1u;
                Dem_CopyInfoFromEntry(
                    &DemEventRelateInformation[tempEventId],
                    &DemMemDestCfg[DemMemDestindex].EntryList[iloop]);
                retVal = E_OK;
                DemMemDestInfo[DemMemDestindex].RecordNum++;
            }
            else
            {
                DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId = 0u;
            }
        }
    }
#endif
#else
    /*the NvRAM data should be validated*/
    blockRef = DemNvRamBlockId[blockIndex];
    blockIndex++;
    (void)NvM_GetErrorStatus(blockRef, &RequestResultPtr);
    if (RequestResultPtr == NVM_REQ_OK)
    {
        Dem_MemCopy(
            (uint8*)DemEventMemoryEntryStorage,
            (const uint8*)NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
            TOTAL_ENTRY_STORAGE_LEN);
        for (iloop = 0; iloop < DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY; iloop++)
        {
            /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
            for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
            /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
            {
                if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
                {
                    DemMemDestCfg[DemMemDestindex].EntryList[iloop] = DemEventMemoryEntryStorage[iloop];
                    tempEventId = DemMemDestCfg[DemMemDestindex].EntryList[iloop].EventId;
                    break;
                }
            }
            if ((tempEventId != 0u) && (tempEventId <= DEM_EVENT_PARAMETER_NUM))
            {
                tempEventId = tempEventId - 1u;
                Dem_CopyInfoFromEntry(&DemEventRelateInformation[tempEventId], &DemEventMemoryEntryStorage[iloop]);
                DemMemDestInfo[DemMemDestindex].RecordNum++;
            }
            else
            {
                DemEventMemoryEntryStorage[iloop].EventId = 0u;
            }
        }
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT > 0)
        for (; iloop < ENTRY_STORAGE_NUM; iloop++)
        {
            for (DemMemDestindex = 0; DemMemDestindex < DEM_MEM_DEST_TOTAL_NUM; DemMemDestindex++)
            {
                if (DemMemDestCfg[DemMemDestindex].ExtId == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
                {
                    DemMemDestCfg[DemMemDestindex].EntryList[iloop - DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY] =
                        DemEventMemoryEntryStorage[iloop];
                    tempEventId =
                        DemMemDestCfg[DemMemDestindex].EntryList[iloop - DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY].EventId;
                    break;
                }
            }
            if ((tempEventId != 0u) && (tempEventId <= DEM_EVENT_PARAMETER_NUM))
            {
                tempEventId = tempEventId - 1u;
                Dem_CopyInfoFromEntry(&DemEventRelateInformation[tempEventId], &DemEventMemoryEntryStorage[iloop]);
                DemMemDestInfo[DemMemDestindex].RecordNum++;
            }
            else
            {
                DemEventMemoryEntryStorage[iloop].EventId = 0u;
            }
        }
#endif
        retVal = E_OK;
    }
#endif
    blockRef = DemNvRamBlockId[blockIndex];
    (void)NvM_GetErrorStatus(blockRef, &RequestResultPtr);
    if (RequestResultPtr == NVM_REQ_OK)
    {
        Dem_MemCopy(
            (uint8*)&DemEventRelateInformationStorage,
            (const uint8*)NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
            sizeof(Dem_EventRelateInformationStorageType));
        for (iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
        {
            DemEventRelateInformation[iloop].UdsStatus = DemEventRelateInformationStorage.UdsStatus[iloop];
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
            DemEventRelateInformation[iloop].StatusIndicator30 =
                DemEventRelateInformationStorage.StatusIndicator30[iloop];
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
#if (DEM_DEBOUNCE_COUNTER_STORAGE_NUM > 0)
            /*SWS_Dem_00674*/
            if (DemPbCfgPtr->DemDebounceCounterBasedClass[DemPbCfgPtr->DemEventParameter[iloop].AlgorithmRef]
                    .DemDebounceCounterStorage
                == TRUE)
            {
                DemDebounceCounterInfo[DemPbCfgPtr->DemEventParameter[iloop].AlgorithmIndex].InternalDebounceCounter =
                    DemEventRelateInformationStorage.DebounceCounter[iloop];
            }
#endif
        }
#if (DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON)
        for (iloop = 0; iloop < DEM_DTC_NUM; iloop++)
        {
            FDCInfo[iloop].MaxFDCSinceLastClear = DemEventRelateInformationStorage.MaxFDCSinceLastClear[iloop];
        }
#endif
#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON) /* req SWS_Dem_00577 */
        for (iloop = 0; iloop < DEM_OPERATION_CYCLE_NUM_BYTE; iloop++)
        {
            DemOperationCycleStatus[iloop] = DemEventRelateInformationStorage.DemOperationCycleStatus[iloop];
        }
#endif
        retVal = E_OK;
        DemDTCByOccurrenceTimeInfo.FirstDtcConfirmed = DemEventRelateInformationStorage.FirstDtcConfirmed;
        DemDTCByOccurrenceTimeInfo.FirstFailed = DemEventRelateInformationStorage.FirstFailed;
        DemDTCByOccurrenceTimeInfo.MostRecDtcConfirmed = DemEventRelateInformationStorage.MostRecDtcConfirmed;
        DemDTCByOccurrenceTimeInfo.MostRecentFailed = DemEventRelateInformationStorage.MostRecentFailed;
    }
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    blockIndex++;
    blockRef = DemNvRamBlockId[blockIndex];
    (void)NvM_GetErrorStatus(blockRef, &RequestResultPtr);
    if (RequestResultPtr == NVM_REQ_OK)
    {
        Dem_MemCopy(
            (uint8*)&DemOBDDataStorage,
            (const uint8*)NvM_BlockDescriptor[blockRef - 1u].NvmRamBlockDataAddress,
            sizeof(DemOBDDataStorageType));
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        IgnUpCycleCounter = DemOBDDataStorage.IgnUpCycleCounter;
#endif
        WarmUpCycleCounter = DemOBDDataStorage.WarmUpCycleCounter;
        OBDDistanceMILOn = DemOBDDataStorage.OBDDistanceMILOn;
        DistSinceDtcCleared = DemOBDDataStorage.DistSinceDtcCleared;
        OBDTimeMILOn = DemOBDDataStorage.OBDTimeMILOn;
        OBDTimeDTCClear = DemOBDDataStorage.OBDTimeDTCClear;
        ContinuousMICounter = DemOBDDataStorage.ContinuousMICounter;
        OBDB1Counter = DemOBDDataStorage.OBDB1Counter;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
        MasterContinuousMICounter = DemOBDDataStorage.MasterContinuousMICounter;
#endif
        retVal = E_OK;
    }
#endif
    return retVal;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Dem_StorageInit
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
FUNC(void, DEM_CODE) Dem_EntryInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    for (uint8 iloop = 0; iloop < DEM_MEM_DEST_TOTAL_NUM; iloop++)
    {
        Dem_EventMemEntryType* pEntry = DemMemDestCfg[iloop].EntryList;
        for (uint8 entryNum = 0; entryNum < DemMemDestCfg[iloop].EntryNum; entryNum++)
        {
            Dem_MemEntryDelete(pEntry, iloop);
            pEntry++;
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
