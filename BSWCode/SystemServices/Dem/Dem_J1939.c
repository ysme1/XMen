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
 **  FILENAME    : Dem_J1939.c                                                 **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API definitions of DEM for J1939                            **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem_Internal.h"

#if (DEM_J1939_SUPPORT == STD_ON)
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define DEM_NUMBER_OF_READINESS_GROUPS_FORJ1939 20u /* PRQA S 0791 */ /* MISRA Rule 5.4 */
/* FreezeFrameRecordFilter */
typedef struct
{
    /* Filter */
    Dem_DTCFormatType DTCFormat;

    /* Result */
    uint16 NumberOfFilteredRecords;
    uint16 GetNum;
    uint8 MemDestIndex;
    uint8 EntryIndex;
    uint8 FFIndex;
} Dem_J1939FreezeFrameRecordFilterInfoType;

/* DTC Filter */
typedef struct
{
    Dem_J1939DcmDTCStatusFilterType DTCStatusFilter;
    Dem_DTCKindType DemJ1939DTCFilterInfo;
    uint8 node;
    Dem_DTCOriginType DTCOrigin;
    /* Result */
    boolean IsSet;
    uint16 NumberOfFilteredDTC;
    uint8 GetNum;
    uint8 CurrentIndex;
} Dem_J1939DTCFilterInfoType;

/* Freeze Frame Filter */
typedef struct
{
    Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind;
    uint8 node;
    uint8 CurrentIndex;
    boolean IsSet;
    uint16 SPNIndex;
    uint8 SPNCounter;
    boolean IsOK;
} Dem_J1939DcmFreezeFrameFilterType;

typedef struct
{
    uint8 node;
    uint8 CurrentIndex;
    boolean IsSet;
} DemJ1939DTCGetNodeType;

typedef struct
{
    uint8 node;
    uint8 CurrentIndex;
    boolean IsSet;
} Dem_J1939DcmRatioFilterType;
/* PRQA S 3218++ */ /* MISRA Rule 8.9 */
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(Dem_J1939DcmFreezeFrameFilterType, AUTOMATIC) DemJ1939DcmFreezeFrameFilter;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(Dem_J1939DcmRatioFilterType, AUTOMATIC) DemJ1939DcmRatioFilter;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
/* PRQA S 3218-- */ /* MISRA Rule 8.9 */

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(Dem_J1939DTCFilterInfoType, AUTOMATIC) DemJ1939DTCFilter;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#if (DEM_J1939_DM31_SUPPORT == STD_ON)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
DEM_LOCAL VAR(DemJ1939DTCGetNodeType, AUTOMATIC) DemJ1939DTCGetNode;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif
/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               BRIEF DESCRIPTION
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant/Non Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_J1939Init(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Dem_MemSet((uint8*)&DemJ1939DTCFilter, 0x00u, sizeof(Dem_J1939DTCFilterInfoType));
    Dem_MemSet((uint8*)&DemJ1939DcmFreezeFrameFilter, 0x00u, sizeof(Dem_J1939DcmFreezeFrameFilterType));
    Dem_MemSet((uint8*)&DemJ1939DcmRatioFilter, 0x00u, sizeof(Dem_J1939DcmRatioFilterType));
}

#if (DEM_J1939_NODE_NUM > 0u)
/*************************************************************************/
/*
 * Brief               BRIEF DESCRIPTION
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant/Non Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
FUNC(boolean, DEM_CODE) Dem_J1939CeckNode(uint16 dtcRef, uint8 node)
{
    boolean ret = FALSE;
    uint8 J1939NodeRef =
        DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[dtcRef].DemDTCAttributesRef].DemJ1939DTC_J1939NodeRef;
    const J1939NodeType* pJ1939Node = &DemPbCfgPtr->J1939Node[J1939NodeRef];
    const uint8* nodeIndex = pJ1939Node->NodeIDRef;
    uint8 nodeNum = pJ1939Node->NodeNum;
    for (uint8 index = 0; index < nodeNum; index++)
    {
        if (node == *nodeIndex)
        {
            /* find the node */
            ret = TRUE;
        }
        nodeIndex++;
    }
    return ret;
}
#endif /* DEM_J1939_NODE_NUM > 0u */
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               The function sets the DTC filter for a specific node and returns the composite lamp status of the
 filtered DTCs
 * ServiceId           0x90
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      DTCStatusFilter: The following types are available:
                        DEM_J1939DTC_ACTIVE
                        DEM_J1939DTC_PREVIOUSLY_ACTIVE
                        DEM_J1939DTC_PENDING
                        DEM_J1939DTC_PERMANENT
                        DEM_J1939DTC_CURRENTLY_ACTIVE
 *                      DTCKind: Defines the functional group of DTCs to be reported
 *                      node:Nm node Id
 * Param-Name[out]     LampStatus:Receives the commulated lamp status
 * Param-Name[in/out]  none
 * Return              Status of the operation to (re-)set a DTC filter.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnSetFilterType, DEM_CODE)
Dem_J1939DcmSetDTCFilter(
    Dem_J1939DcmDTCStatusFilterType DTCStatusFilter,
    Dem_DTCKindType DTCKind,
    uint8 node,
    Dem_J1939DcmLampStatusType* LampStatus)
{
    Dem_ReturnSetFilterType ret = DEM_WRONG_FILTER;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMSETDTCFILTER, DEM_E_UNINIT);
    }
    else if (LampStatus == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMSETDTCFILTER, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_DTCOriginType DTCOrigin;
        DemJ1939DTCFilter.DTCStatusFilter = DTCStatusFilter;
        DemJ1939DTCFilter.DemJ1939DTCFilterInfo = DTCKind;
        DemJ1939DTCFilter.node = node;
        DTCOrigin = (DTCStatusFilter == DEM_J1939DTC_PERMANENT) ? DEM_DTC_ORIGIN_PERMANENT_MEMORY
                                                                : DEM_DTC_ORIGIN_PRIMARY_MEMORY;
        DemJ1939DTCFilter.DTCOrigin = Dem_GetInternalMemDest(DTCOrigin);
        DemJ1939DTCFilter.CurrentIndex = 0;
        DemJ1939DTCFilter.NumberOfFilteredDTC = 0;
        DemJ1939DTCFilter.GetNum = 0;
        DemJ1939DTCFilter.IsSet = TRUE;
        *LampStatus = 0x00u;
#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
        /*Composite Malfunction Indicator Lamp Status*/
        if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID) /* PRQA S 2741,2742 */ /* MISRA Rule 14.3 */
        {
            Dem_IndicatorStatusType WIRStatus = DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR];
            if (WIRStatus != DEM_INDICATOR_OFF)
            {
                *LampStatus |= 0x4000u; /*SWS_Dem_00858]*/
            }
            if ((WIRStatus == DEM_INDICATOR_OFF) || (WIRStatus == DEM_INDICATOR_CONTINUOUS))
            {
                *LampStatus |= 0x00C0u; /*SWS_Dem_00859]*/
            }
            if (WIRStatus == DEM_INDICATOR_SLOW_FLASH)
            {
                *LampStatus &= ~0x00C0u; /*SWS_Dem_00860]*/
            }
            if (WIRStatus == DEM_INDICATOR_FAST_FLASH)
            {
                *LampStatus &= ~0x0080u; /*SWS_Dem_00861]*/
            }
        }

        /*Composite Red Stop Lamp Status*/
        if (DEM_RED_STOP_LAMP_INDICATOR != DemIndicator_INVALID) /* PRQA S 2741,2742 */ /* MISRA Rule 14.3 */
        {
            Dem_IndicatorStatusType WIRStatus = DemWIRStatus[DEM_RED_STOP_LAMP_INDICATOR];
            if (WIRStatus != DEM_INDICATOR_OFF)
            {
                *LampStatus |= 0x1000u; /*SWS_Dem_00862]*/
            }
            if ((WIRStatus == DEM_INDICATOR_OFF) || (WIRStatus == DEM_INDICATOR_CONTINUOUS))
            {
                *LampStatus |= 0x0030u; /*SWS_Dem_00863]*/
            }
            if (WIRStatus == DEM_INDICATOR_SLOW_FLASH)
            {
                *LampStatus &= ~0x0030u; /*SWS_Dem_00864]*/
            }
            if (WIRStatus == DEM_INDICATOR_FAST_FLASH)
            {
                *LampStatus &= ~0x0020u; /*SWS_Dem_00865]*/
            }
        }

        /*Composite Amber Warning Lamp Status*/
        if (DEM_AMBER_WARING_LAMP_INDICATOR != DemIndicator_INVALID) /* PRQA S 2741,2742 */ /* MISRA Rule 14.3 */
        {
            Dem_IndicatorStatusType WIRStatus = DemWIRStatus[DEM_AMBER_WARING_LAMP_INDICATOR];
            if (WIRStatus != DEM_INDICATOR_OFF)
            {
                *LampStatus |= 0x0400u; /*SWS_Dem_00866]*/
            }
            if ((WIRStatus == DEM_INDICATOR_OFF) || (WIRStatus == DEM_INDICATOR_CONTINUOUS))
            {
                *LampStatus |= 0x000cu; /*SWS_Dem_00867]*/
            }
            if (WIRStatus == DEM_INDICATOR_SLOW_FLASH)
            {
                *LampStatus &= ~0x000cu; /*SWS_Dem_00868]*/
            }
            if (WIRStatus == DEM_INDICATOR_FAST_FLASH)
            {
                *LampStatus &= ~0x0008u; /*SWS_Dem_00869]*/
            }
        }

        /*Composite Protect Lamp Status*/
        if (DEM_PROTECT_LAMP_INDICATOR != DemIndicator_INVALID) /* PRQA S 2741,2742 */ /* MISRA Rule 14.3 */
        {
            Dem_IndicatorStatusType WIRStatus = DemWIRStatus[DEM_PROTECT_LAMP_INDICATOR];
            if (WIRStatus != DEM_INDICATOR_OFF)
            {
                *LampStatus |= 0x0100u; /*SWS_Dem_00870]*/
            }
            if ((WIRStatus == DEM_INDICATOR_OFF) || (WIRStatus == DEM_INDICATOR_CONTINUOUS))
            {
                *LampStatus |= 0x0003u; /*SWS_Dem_00871]*/
            }
            if (WIRStatus == DEM_INDICATOR_SLOW_FLASH)
            {
                *LampStatus &= ~0x0003u; /*SWS_Dem_00872]*/
            }
            if (WIRStatus == DEM_INDICATOR_FAST_FLASH)
            {
                *LampStatus &= ~0x0002u; /*SWS_Dem_00873]*/
            }
        }
        ret = DEM_FILTER_ACCEPTED;
#else
        *LampStatus = 0x00FFu;
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the number of currently filtered DTCs set by the function Dem_J1939DcmSetDTCFilter
 * ServiceId           0x91
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     NumberOfFilteredDTC: The number of DTCs matching the defined status mask.
 * Param-Name[in/out]  none
 * Return              Status of the operation to retrieve a number of DTC from the Dem
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnGetNumberOfFilteredDTCType, DEM_CODE)
Dem_J1939DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC)
{
    Dem_ReturnGetNumberOfFilteredDTCType ret = DEM_NUMBER_FAILED;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNUMBEROFFILTEREDDTC, DEM_E_UNINIT);
    }
    else if (NumberOfFilteredDTC == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNUMBEROFFILTEREDDTC, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_J1939DTCFilterInfoType* pFilter = &DemJ1939DTCFilter;
        if (pFilter->IsSet == TRUE)
        {
            const Dem_MemDestConfigType* pMemDestCfg = &DemMemDestCfg[pFilter->DTCOrigin];
            uint8 entryNum = pMemDestCfg->EntryNum;
            const Dem_EventMemEntryType* pEntry = pMemDestCfg->EntryList;
            uint32 tempDtcValue[DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY];
            Dem_DTCKindType DTCFilterInfo = pFilter->DemJ1939DTCFilterInfo;
            Dem_J1939DcmDTCStatusFilterType DTCStatusFilter = pFilter->DTCStatusFilter;
            for (uint8 iloop = 0; iloop < entryNum; iloop++)
            {
                Dem_EventIdType EventId = pEntry->EventId;
                if (EventId != 0x00u)
                {
                    Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
                    const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                    uint16 dtcRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
                    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
                    if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                    {
                        uint16 DemObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                        const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
                        /* match kind and J1939DTC */
                        if ((DEM_OBD_DTC_INVALID != DemObdDTCRef)
                            && (pObdDTC[DemObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID)
                            && ((DEM_DTC_KIND_ALL_DTCS == DTCFilterInfo) || (DTCFilterInfo == pDTC[dtcRef].DTCKind)))
                        {
                            boolean IsFind = FALSE;
#if (DEM_J1939_NODE_NUM > 0u)
                            if (Dem_J1939CeckNode(dtcRef, pFilter->node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                            {
                                IsFind = FALSE;
                                /* match the DTCStatusFilter */
                                switch (DTCStatusFilter)
                                {
                                case DEM_J1939DTC_ACTIVE:
                                    /* (ConfirmedDTC == 1 AND TestFailed == 1) OR MIL_ON */
                                    if (((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                                         && (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF)))
#if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
                                        || (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] != DEM_INDICATOR_OFF)
#endif /* DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID */
                                    )
                                    {
                                        IsFind = TRUE;
                                    }
                                    break;
                                case DEM_J1939DTC_PREVIOUSLY_ACTIVE:
                                    /*ConfirmedDTC == 1 AND TestFailed == 0 AND MIL_OFF*/
                                    if ((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                                        && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
#if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
                                        && (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] == DEM_INDICATOR_OFF)
#endif /* DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID */
                                    )
                                    {
                                        IsFind = TRUE;
                                    }
                                    break;
                                case DEM_J1939DTC_PENDING:
                                    /* PendingDTC == 1 */
                                    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC))
                                    {
                                        IsFind = TRUE;
                                    }
                                    break;
                                case DEM_J1939DTC_PERMANENT:
                                    IsFind = TRUE;
                                    break;
                                case DEM_J1939DTC_CURRENTLY_ACTIVE:
                                    /* TestFailed == 1 */
                                    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
                                    {
                                        IsFind = TRUE;
                                    }
                                    break;
                                default:
                                    /*idle*/
                                    break;
                                }
                                if (IsFind == TRUE)
                                {
                                    boolean findSameDTC = FALSE;
                                    uint32 DemJ1939DTCValue = pObdDTC[DemObdDTCRef].DemJ1939DTCValue;
                                    if (DEM_J1939_DTC_CFG_INVALID != DemJ1939DTCValue)
                                    {
                                        for (uint8 J1939Index = 0; J1939Index < iloop; J1939Index++)
                                        {
                                            if (tempDtcValue[J1939Index] == DemJ1939DTCValue)
                                            {
                                                /* find same dtc of diffrence event memory */
                                                findSameDTC = TRUE;
                                                break;
                                            }
                                        }
                                        if (findSameDTC == FALSE)
                                        {
                                            tempDtcValue[iloop] = DemJ1939DTCValue;
                                            pFilter->NumberOfFilteredDTC++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                pEntry++;
            }
            *NumberOfFilteredDTC = pFilter->NumberOfFilteredDTC;
            ret = DEM_NUMBER_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the next filtered J1939 DTC.
 * ServiceId           0x92
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     J1939DTC: Receives the J1939DTC value. If the return value of
                        the function is other than DEM_FILTERED_OK this
                        parameter does not contain valid data.
                        OccurenceCounter:This parameter receives the corresponding occurrence counter. If the return
 value of the function call is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * Param-Name[in/out]  none
 * Return              Status of the operation to retrieve a DTC from the Dem.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextFilteredDTC(uint32* J1939DTC, uint8* OccurenceCounter)
{
    Dem_ReturnGetNextFilteredElementType ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTFILTEREDDTC, DEM_E_UNINIT);
    }
    else if ((OccurenceCounter == NULL_PTR) || (J1939DTC == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTFILTEREDDTC, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00877 */
        ret = DEM_FILTERED_PENDING;
        if (Dem_Pending == FALSE)
        {
            Dem_J1939DTCFilterInfoType* pFilter = &DemJ1939DTCFilter;
            uint8 entryNum = DemMemDestCfg[pFilter->DTCOrigin].EntryNum;
            const Dem_EventMemEntryType* pEntry = &DemMemDestCfg[pFilter->DTCOrigin].EntryList[pFilter->CurrentIndex];
            Dem_J1939DcmDTCStatusFilterType DTCStatusFilter = pFilter->DTCStatusFilter;
            ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
            if (pFilter->IsSet == TRUE)
            {
                /* PRQA S 2472++ */ /* MISRA Rule 14.2 */
                for (; (ret != DEM_FILTERED_OK) && (pFilter->CurrentIndex < entryNum); pFilter->CurrentIndex++)
                /* PRQA S 2472-- */ /* MISRA Rule 14.2 */
                {
                    if (pEntry->EventId != 0x00u)
                    {
                        Dem_EventIdType IntId = Dem_GetEventInternalId(pEntry->EventId);
                        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                        uint16 dtcRef = DemPbCfgPtr->DemEventParameter[IntId].DemDTCRef;
                        const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
                        boolean IsFind = FALSE;
                        if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                        {
                            uint16 DemObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                            const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
                            /* match kind and J1939DTC */
                            if ((DEM_OBD_DTC_INVALID != DemObdDTCRef)
                                && (pObdDTC[DemObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                            {
#if (DEM_J1939_NODE_NUM > 0u)
                                if (Dem_J1939CeckNode(dtcRef, pFilter->node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                                {
                                    IsFind = FALSE;
                                    /* match the DTCStatusFilter */
                                    switch (DTCStatusFilter)
                                    {
                                    case DEM_J1939DTC_ACTIVE:
                                        /* (ConfirmedDTC == 1 AND TestFailed == 1) OR MIL_ON */
                                        if (((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                                             && (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF)))
#if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
                                            || (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] != DEM_INDICATOR_OFF)
#endif /* DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID */
                                        )
                                        {
                                            IsFind = TRUE;
                                        }
                                        break;
                                    case DEM_J1939DTC_PREVIOUSLY_ACTIVE:
                                        /* ConfirmedDTC == 1 AND TestFailed == 0 AND MIL_OFF */
                                        if ((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                                            && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
#if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
                                            && (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] == DEM_INDICATOR_OFF)
#endif /* DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID */
                                        )
                                        {
                                            IsFind = TRUE;
                                        }
                                        break;
                                    case DEM_J1939DTC_PENDING:
                                        /* PendingDTC == 1 */
                                        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_PDTC))
                                        {
                                            IsFind = TRUE;
                                        }
                                        break;
                                    case DEM_J1939DTC_PERMANENT:
                                        IsFind = TRUE;
                                        break;
                                    case DEM_J1939DTC_CURRENTLY_ACTIVE:
                                        /* TestFailed == 1 */
                                        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
                                        {
                                            IsFind = TRUE;
                                        }
                                        break;
                                    default:
                                        /*idle*/
                                        break;
                                    }
                                    /* SWS_Dem_01101 */
                                    if (IsFind == TRUE)
                                    {
                                        /* guarantee the event index the new dtc */
                                        Dem_GetEventDTC(dtcRef, DEM_DTC_FORMAT_J1939, J1939DTC);
                                        /* SWS_Dem_00882 */
                                        *OccurenceCounter =
                                            (pEvent->OccurrenceCounter < 0x7Fu) ? pEvent->OccurrenceCounter : 0x7Fu;
                                        if (0u != *J1939DTC)
                                        {
                                            ret = DEM_FILTERED_OK;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    DemJ1939DTCFilter.IsSet =
        ((DEM_FILTERED_OK == ret) || (DEM_FILTERED_PENDING == ret)) ? DemJ1939DTCFilter.IsSet : FALSE;
    return ret;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

#if (DEM_J1939_DM31_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               The function sets the filter to the first applicable DTC for the DM31 response for a specific
 * node ServiceId           0x93 Sync/Async          Synchronous Reentrancy          Non Reentrant Param-Name[in] Nm
 * node Id of requesting client Param-Name[out]     None Param-Name[in/out]  none Return              Status of the
 * operation to retrieve a DTC from the Dem.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_J1939DcmFirstDTCwithLampStatus(uint8 node)
{
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMFIRSTDTCWITHLAMPSTATUS, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        boolean IsFind = FALSE;
        const Dem_MemDestConfigType* pMemDestCfg =
            &DemMemDestCfg[Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY)];
        uint8 entryNum = pMemDestCfg->EntryNum;
        const Dem_EventMemEntryType* pEntry = pMemDestCfg->EntryList;
        const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
        const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
        const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;

        DemJ1939DTCGetNode.node = node;
        DemJ1939DTCGetNode.IsSet = TRUE;
        for (uint8 iloop = 0; (iloop < entryNum) && (IsFind == FALSE); iloop++)
        {
            if (pEntry->EventId != 0x00u)
            {
                uint16 dtcRef = pEventParameter[Dem_GetEventInternalId(pEntry->EventId)].DemDTCRef;
                if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                {
                    uint16 DemObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                    /* match kind and J1939DTC */
                    if ((DEM_OBD_DTC_INVALID != DemObdDTCRef)
                        && (pObdDTC[DemObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                    {
#if (DEM_J1939_NODE_NUM > 0u)
                        if (Dem_J1939CeckNode(dtcRef, DemJ1939DTCGetNode.node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                        {
                            /* SWS_Dem_01101 */
                            DemJ1939DTCGetNode.CurrentIndex = iloop;
                            IsFind = TRUE;
                        }
                    }
                }
            }
            pEntry++;
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the next filtered J1939 DTC for DM31 including current LampStatus.
 * ServiceId           0x94
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     LampStatus:Receives the lamp status returned by this function.
 *                      If the return value of the function is other than
                        DEM_FILTERED_OK this parameter does not contain valid data.
                        J1939DTC:Receives the J1939DTC value. If the return value of
                        the function is other than DEM_FILTERED_OK this
                        parameter does not contain valid data.
                        OccurenceCounter:This parameter receives the corresponding occurrence counter.
                        If the return value of the function call
                        is other than DEM_FILTERED_OK this parameter
                        does not contain valid data.
 * Param-Name[in/out]  none
 * Return              Status of the operation to retrieve a DTC from the Dem.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
/* PRQA S 2755++ */ /* MISRA CMN 0.4 */
Dem_J1939DcmGetNextDTCwithLampStatus(Dem_J1939DcmLampStatusType* LampStatus, uint32* J1939DTC, uint8* OccurenceCounter)
/* PRQA S 2755-- */ /* MISRA CMN 0.4 */
{
    Dem_ReturnGetNextFilteredElementType ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
    const Dem_EventRelateInformationType* pEvent = NULL_PTR;

#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTDTCWITHLAMPSTATUS, DEM_E_UNINIT);
    }
    else if ((OccurenceCounter == NULL_PTR) || (J1939DTC == NULL_PTR) || (LampStatus == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTDTCWITHLAMPSTATUS, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        ret = DEM_FILTERED_PENDING;
        /* SWS_Dem_00882 */
        if (Dem_Pending == FALSE)
        {
            ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
            if (DemJ1939DTCGetNode.IsSet == TRUE)
            {
                const Dem_MemDestConfigType* pMemDestCfg =
                    &DemMemDestCfg[Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY)];
                uint8 entryNum = pMemDestCfg->EntryNum;
                const Dem_EventMemEntryType* pEntry = &pMemDestCfg->EntryList[DemJ1939DTCGetNode.CurrentIndex];
                const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
                const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
                const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
                /* PRQA S 2461++ */ /* MISRA Rule 14.2 */
                for (; (ret != DEM_FILTERED_OK) && (DemJ1939DTCGetNode.CurrentIndex < entryNum);
                     DemJ1939DTCGetNode.CurrentIndex++)
                /* PRQA S 2461-- */ /* MISRA Rule 14.2*/
                {
                    Dem_EventIdType EventId = pEntry->EventId;
                    pEvent = NULL_PTR;
                    if (EventId != 0x00u)
                    {
                        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
                        uint16 dtcRef = pEventParameter[IntId].DemDTCRef;
                        pEvent = Dem_GetEventInfo(IntId);
                        if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                        {
                            uint16 DemObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                            /* match kind and J1939DTC */
                            if ((DEM_OBD_DTC_INVALID != DemObdDTCRef)
                                && (pObdDTC[DemObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                            {
#if (DEM_J1939_NODE_NUM > 0u)
                                if (Dem_J1939CeckNode(dtcRef, DemJ1939DTCGetNode.node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                                {
                                    /* SWS_Dem_01101 */
                                    /* guarantee the event index the new dtc */
                                    Dem_GetEventDTC(dtcRef, DEM_DTC_FORMAT_J1939, J1939DTC);
                                    /* SWS_Dem_00882 */
                                    *OccurenceCounter =
                                        (pEvent->OccurrenceCounter < 0x7Fu) ? pEvent->OccurrenceCounter : 0x7Fu;
                                    if (0u != *J1939DTC)
                                    {
                                        ret = DEM_FILTERED_OK;
                                    }
                                }
                            }
                        }
                    }
                    pEntry++;
                }
            }
        }
        *LampStatus = 0u;
        if (pEvent != NULL_PTR)
        {
#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
            uint16 iloop;
            const Dem_IndicatorAttributeType* pWIRAttr =
                &DemIndicatorAttribute[DemPbCfgPtr->DemEventParameter[pEvent->IntId].AttrStartIndex];
            for (iloop = 0; iloop < DemPbCfgPtr->DemEventParameter[pEvent->IntId].AttrNum; iloop++)
            {
                uint8 DemIndicatorRef = pWIRAttr->DemIndicatorRef;
                uint8 DemIndicatorBehaviour = pWIRAttr->DemIndicatorBehaviour;
                /* Malfunction Indicator Lamp */
                if (DemIndicatorRef == DEM_MALFUNCTION_LAMP_INDICATOR)
                {
                    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR))
                    {
                        /* SWS_Dem_00883 */
                        *LampStatus |= 0x0040u;
                    }
                    if (DemWIRStatus[DemIndicatorRef] != DEM_INDICATOR_OFF)
                    {
                        if (DemIndicatorBehaviour == DEM_INDICATOR_CONTINUOUS)
                        {
                            /* SWS_Dem_00884 */
                            *LampStatus |= 0xC000u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_SLOW_FLASH)
                        {
                            /* SWS_Dem_00860 */
                            *LampStatus |= 0x0000u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_FAST_FLASH)
                        {
                            /* SWS_Dem_00861 */
                            *LampStatus |= 0x4000u;
                        }
                    }
                }

                /* Red Stop Lamp */
                if (DemIndicatorRef == DEM_RED_STOP_LAMP_INDICATOR)
                {
                    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR))
                    {
                        /* SWS_Dem_00887 */
                        *LampStatus |= 0x0010u;
                    }
                    if (DemWIRStatus[DemIndicatorRef] != DEM_INDICATOR_OFF)
                    {
                        if (DemIndicatorBehaviour == DEM_INDICATOR_CONTINUOUS)
                        {
                            /* SWS_Dem_00888 */
                            *LampStatus |= 0x3000u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_SLOW_FLASH)
                        {
                            /* SWS_Dem_00889 */
                            *LampStatus |= 0x0000u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_FAST_FLASH)
                        {
                            /* SWS_Dem_00890 */
                            *LampStatus |= 0x1000u;
                        }
                    }
                }

                /* Amber Warning Lamp */
                if (DemIndicatorRef == DEM_AMBER_WARING_LAMP_INDICATOR)
                {
                    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR))
                    {
                        /* SWS_Dem_00891 */
                        *LampStatus |= 0x0004u;
                    }
                    if (DemWIRStatus[DemIndicatorRef] != DEM_INDICATOR_OFF)
                    {
                        if (DemIndicatorBehaviour == DEM_INDICATOR_CONTINUOUS)
                        {
                            /* SWS_Dem_00892 */
                            *LampStatus |= 0x0C00u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_SLOW_FLASH)
                        {
                            /* SWS_Dem_00893 */
                            *LampStatus |= 0x0000u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_FAST_FLASH)
                        {
                            /* SWS_Dem_00894 */
                            *LampStatus |= 0x0400u;
                        }
                    }
                }

                /* Protect Lamp */
                if (DemIndicatorRef == DEM_PROTECT_LAMP_INDICATOR)
                {
                    if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR))

                    {
                        /* SWS_Dem_00895 */
                        *LampStatus |= 0x0001u;
                    }
                    if (DemWIRStatus[DemIndicatorRef] != DEM_INDICATOR_OFF)
                    {
                        if (DemIndicatorBehaviour == DEM_INDICATOR_CONTINUOUS)
                        {
                            /* SWS_Dem_00896 */
                            *LampStatus |= 0x0300u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_SLOW_FLASH)
                        {
                            /* SWS_Dem_00897 */
                            *LampStatus |= 0x0000u;
                        }
                        if (DemIndicatorBehaviour == DEM_INDICATOR_FAST_FLASH)
                        {
                            /* SWS_Dem_00898 */
                            *LampStatus |= 0x0100u;
                        }
                    }
                }
                pWIRAttr++;
            }
#else
            *LampStatus = 0x00FFu;
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
        }
    }
    DemJ1939DTCGetNode.IsSet =
        ((DEM_FILTERED_OK == ret) || (DEM_FILTERED_PENDING == ret)) ? DemJ1939DTCGetNode.IsSet : FALSE;
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_DM31_SUPPORT == STD_ON */

#if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Clears active DTCs as well as previously active DTCs
 * ServiceId           0x95
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      DTCTypeFilter:The following types are available:
                        DEM_J1939DTC_CLEAR_ALL
                        DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE
 *                      node: Nm node Id of requesting client
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Status of the operation of type Dem_ReturnClearDTCType.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnClearDTCType, DEM_CODE)
Dem_J1939DcmClearDTC(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node)
{
    Dem_ReturnClearDTCType ret = DEM_CLEAR_FAILED;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMCLEARDTC, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        boolean ProcessOn = TRUE;
        Dem_ClearDTCInfoType* pClr = &DemClearDTCInfo;
        if (Dem_ClearDTCLock == DEM_CLEAR_LOCK)
        {
            /* SWS_Dem_00662 SWS_Dem_00664 */
            ret = DEM_CLEAR_BUSY;
            if ((pClr->DTCTypeFilter == DTCTypeFilter) && (pClr->SID == DEM_SID_J1939DCMCLEARDTC)
                && (pClr->node == node))
            {
                /* SWS_Dem_00663 */
                ret = DEM_CLEAR_PENDING;
            }
            ProcessOn = FALSE;
        }
        else if (Dem_ClearDTCLock == DEM_CLEAR_NOT_LOCK)
        {
            /* SWS_Dem_00661 */
            Dem_ClearDTCLock = DEM_CLEAR_LOCK;
            pClr->DTCTypeFilter = DTCTypeFilter;
            pClr->SID = DEM_SID_J1939DCMCLEARDTC;
            pClr->node = node;
        }
        else
        {
            /* idle */
        }
        if (TRUE == ProcessOn)
        {
            pClr->ClearAllGroup = TRUE;
            pClr->memDest = Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY);
            Dem_Pending = TRUE;
            Dem_ClearDTCProcess();
            Dem_ResetDemClearDTCInfo();
            ret = DEM_CLEAR_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON */

#if (DEM_J1939_EXPANDED_FREEZE_FRAME_SUPPORT == STD_ON)
#if (DEM_J1939_FREEZE_FRAME_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               The function sets the FreezeFrame filter for a specific node
 * ServiceId           0x96
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      FreezeFrameKind: The following types are available:
                        DEM_J1939DCM_FREEZEFRAME
                        DEM_J1939DCM_EXPANDED_FREEZEFRAME
                        DEM_J1939DCM_SPNS_IN_EXPANDED_
                        FREEZEFRAME
                        node:Nm node Id of requesting client
 * Param-Name[out]     None
 * Param-Name[in/out]  none
 * Return              Status of the operation to (re-)set a FreezeFrame filter.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnSetFilterType, DEM_CODE)
Dem_J1939DcmSetFreezeFrameFilter(Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind, uint8 node)
{
    Dem_ReturnSetFilterType ret = DEM_WRONG_FILTER;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMSETFREEZEFRAMEFILTER, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        DemJ1939DcmFreezeFrameFilter.IsSet = TRUE;
        DemJ1939DcmFreezeFrameFilter.FreezeFrameKind = FreezeFrameKind;
        DemJ1939DcmFreezeFrameFilter.node = node;
        DemJ1939DcmFreezeFrameFilter.SPNIndex = 0;
        DemJ1939DcmFreezeFrameFilter.CurrentIndex = 0;
        ret = DEM_FILTER_ACCEPTED;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets next freeze frame data. The function stores the data in the provided DestBuffer
 * ServiceId           0x97
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     J1939DTC:Receives the J1939DTC value. If the return value of
                        the function is other than DEM_FILTERED_OK this
                        parameter does not contain valid data
                        OccurenceCounter:This parameter receives the corresponding occurrence counter.
                        If the return value of the function call
                        is other than DEM_FILTERED_OK this parameter
                        does not contain valid data.
 * Param-Name[in/out]  DestBuffer:This parameter contains a byte pointer that points
                        to the buffer, to which the freeze frame data record
                        shall be written to.
                        BufSize:When the function is called this parameter contains
                        the maximum number of data bytes that can be written to the buffer.
 * Return              Status of the operation to retrieve freeze frame data by DTC.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextFreezeFrame(uint32* J1939DTC, uint8* OccurenceCounter, uint8* DestBuffer, uint16* BufSize)
{
    Dem_ReturnGetNextFilteredElementType ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTFREEZEFRAME, DEM_E_UNINIT);
    }
    else if (
        (OccurenceCounter == NULL_PTR) || (J1939DTC == NULL_PTR) || (DestBuffer == NULL_PTR) || (BufSize == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTFREEZEFRAME, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_MemSet(DestBuffer, 0u, *BufSize);
        ret = DEM_FILTERED_PENDING;
        /* SWS_Dem_00902 */
        if (Dem_Pending == FALSE)
        {
            ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
            if (DemJ1939DcmFreezeFrameFilter.IsSet == TRUE)
            {
                const Dem_MemDestConfigType* pMemDestCfg =
                    &DemMemDestCfg[Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY)];
                uint8 entryNum = pMemDestCfg->EntryNum;
                const Dem_EventMemEntryType* pEntry =
                    &pMemDestCfg->EntryList[DemJ1939DcmFreezeFrameFilter.CurrentIndex];
                const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
                const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
                const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
                /* PRQA S 2461 ++*/ /* MISRA Rule 14.2 */
                for (; (DEM_FILTERED_NO_MATCHING_ELEMENT == ret)
                       && (DemJ1939DcmFreezeFrameFilter.CurrentIndex < entryNum);
                     DemJ1939DcmFreezeFrameFilter.CurrentIndex++)
                /* PRQA S 2461 ++*/ /* MISRA Rule 14.2 */
                {
                    Dem_EventIdType EventId = pEntry->EventId;
                    if (EventId != 0x00u)
                    {
                        if (pEntry->FFNum != 0u)
                        {
                            Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
                            const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                            uint16 dtcRef = pEventParameter[IntId].DemDTCRef;
                            if ((dtcRef != DEM_DTC_REF_INVALID)
                                && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                            {
                                uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                                /* match J1939DTC */
                                if ((DEM_OBD_DTC_INVALID != ObdDTCRef)
                                    && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                                {
                                    /* SWS_Dem_01101 */
                                    /* guarantee the event index the new dtc */
                                    *J1939DTC = pObdDTC[ObdDTCRef].DemJ1939DTCValue;
#if (DEM_J1939_NODE_NUM > 0u)
                                    if (Dem_J1939CeckNode(dtcRef, DemJ1939DcmFreezeFrameFilter.node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                                    {
                                        const Dem_DTCAttributesType* pDTCAttr =
                                            &DemPbCfgPtr->DemDTCAttributes[pDTC[dtcRef].DemDTCAttributesRef];
                                        uint8 DemJ1939FFClassRef = pDTCAttr->DemJ1939FreezeFrameClassRef;
                                        uint8 DemJ1939EFFClassRef = pDTCAttr->DemJ1939ExpandedFreezeFrameClassRef;
                                        /* SWS_Dem_00882 */
                                        *OccurenceCounter =
                                            (pEvent->OccurrenceCounter < 0x7Fu) ? pEvent->OccurrenceCounter : 0x7Fu;
                                        /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                                        for (uint8 iloop = 0; iloop < DEM_MAX_NUMBER_FF_RECORDS; iloop++)
                                        /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                                        {
#if (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u)
                                            const uint8* pFF = pEntry->FFList[iloop].Data;
#endif /* DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u */
                                            switch (DemJ1939DcmFreezeFrameFilter.FreezeFrameKind)
                                            {
#if (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u)
                                            case DEM_J1939DCM_FREEZEFRAME:
                                                if (DemJ1939FFClassRef != DEM_J1939_FREEZE_FRAME_INVALID)
                                                {
                                                    uint16 DataSize =
                                                        DemJ1939FreezeFrameClass[DemJ1939FFClassRef].DataSize;
                                                    ret = DEM_FILTERED_BUFFER_TOO_SMALL;
                                                    if (*BufSize >= DataSize)
                                                    {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                                                        Dem_MemCopy(DestBuffer, pFF, DataSize);
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                                                        *BufSize = DataSize;
                                                        ret = DEM_FILTERED_OK;
                                                    }
                                                }
                                                break;
                                            case DEM_J1939DCM_EXPANDED_FREEZEFRAME:
                                                if (DemJ1939EFFClassRef != DEM_J1939_FREEZE_FRAME_INVALID)
                                                {
                                                    uint16 DataSize =
                                                        DemJ1939FreezeFrameClass[DemJ1939EFFClassRef].DataSize;
                                                    ret = DEM_FILTERED_BUFFER_TOO_SMALL;
                                                    if (*BufSize >= DataSize)
                                                    {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                                                        Dem_MemCopy(DestBuffer, pFF, DataSize);
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                                                        *BufSize = DataSize;
                                                        ret = DEM_FILTERED_OK;
                                                    }
                                                }
                                                break;
#endif /* DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u */
                                            case DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME:
                                            default:
#if (STD_ON == DEM_DEV_ERROR_DETECT)
                                                DEM_DET_REPORT(
                                                    DEM_SID_J1939DCMGETNEXTFREEZEFRAME,
                                                    DEM_E_WRONG_CONDITION);
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            ret = DEM_E_NODATAAVAILABLE;
                        }
                    }
                    pEntry++;
                }
            }
        }
    }
    DemJ1939DcmFreezeFrameFilter.IsSet =
        ((DEM_FILTERED_OK == ret) || (DEM_FILTERED_PENDING == ret)) ? DemJ1939DcmFreezeFrameFilter.IsSet : FALSE;
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_FREEZE_FRAME_SUPPORT == STD_ON */

/*************************************************************************/
/*
 * Brief               Gets next SPN.
 * ServiceId           0x98
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     SPNSupported: This parameter contains the next SPN in the ExpandedFreezeFrame
                        SPNDataLength: This parameter contains the corresponding dataLength of the SPN
 * Param-Name[in/out]  None
 * Return              Status of the operation to retrieve freeze frame data by DTC.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(uint32* SPNSupported, uint8* SPNDataLength)
{
    Dem_ReturnGetNextFilteredElementType ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTSPNINFREEZEFRAME, DEM_E_UNINIT);
    }
    else if ((SPNSupported == NULL_PTR) || (SPNDataLength == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTSPNINFREEZEFRAME, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        *SPNSupported = 0;
        *SPNDataLength = 0;
        /* SWS_Dem_00905 */
        ret = DEM_FILTERED_PENDING;
        if (Dem_Pending == FALSE)
        {
            ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
            if (DemJ1939DcmFreezeFrameFilter.IsSet == TRUE)
            {
                const Dem_MemDestConfigType* pMemDestCfg =
                    &DemMemDestCfg[Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY)];
                uint8 entryNum = pMemDestCfg->EntryNum;
                const Dem_EventMemEntryType* pEntry =
                    &pMemDestCfg->EntryList[DemJ1939DcmFreezeFrameFilter.CurrentIndex];
                const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
                const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
                const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
                const Dem_DTCAttributesType* pDTCAttr = DemPbCfgPtr->DemDTCAttributes;
                /* PRQA S 2461 ++ */ /* MISRA Rule 14.2 */
                for (; (ret == DEM_FILTERED_NO_MATCHING_ELEMENT)
                       && (DemJ1939DcmFreezeFrameFilter.CurrentIndex < entryNum);
                     DemJ1939DcmFreezeFrameFilter.CurrentIndex++)
                /* PRQA S 2461 -- */ /* MISRA Rule 14.2 */
                {
                    Dem_EventIdType EventId = pEntry[DemJ1939DcmFreezeFrameFilter.CurrentIndex].EventId;
                    if (EventId != 0x00u)
                    {
                        if (pEntry->FFNum != 0u)
                        {
                            Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
                            uint16 dtcRef = pEventParameter[IntId].DemDTCRef;
                            if ((dtcRef != DEM_DTC_REF_INVALID)
                                && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                            {
                                uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                                /* match J1939DTC */
                                if ((DEM_OBD_DTC_INVALID != ObdDTCRef)
                                    && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                                {
#if (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u)
                                    uint8 DemJ1939ExFFClassRef =
                                        pDTCAttr[pDTC[dtcRef].DemDTCAttributesRef].DemJ1939ExpandedFreezeFrameClassRef;
#endif /* DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u */
#if (DEM_J1939_NODE_NUM > 0)
                                    if (Dem_J1939CeckNode(dtcRef, DemJ1939DcmFreezeFrameFilter.node) == TRUE)
#endif
                                    {
#if (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u)
                                        /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                                        for (uint8 iloop = 0; iloop < DEM_MAX_NUMBER_FF_RECORDS; iloop++)
                                        /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                                        {
#endif /* DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u */
                                            switch (DemJ1939DcmFreezeFrameFilter.FreezeFrameKind)
                                            {
#if (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u)
                                            case DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME:
                                                if (DemJ1939ExFFClassRef != DEM_J1939_FREEZE_FRAME_INVALID)
                                                {
                                                    const Dem_J1939FreezeFrameClassType* pDemJ1939FFClass =
                                                        &DemJ1939FreezeFrameClass[DemJ1939ExFFClassRef];
                                                    uint8 RefNum = pDemJ1939FFClass->RefNum;
                                                    if (DemJ1939DcmFreezeFrameFilter.IsOK == FALSE)
                                                    {
                                                        DemJ1939DcmFreezeFrameFilter.SPNIndex =
                                                            pDemJ1939FFClass->StartIndex;
                                                        DemJ1939DcmFreezeFrameFilter.SPNCounter = 0;
                                                        DemJ1939DcmFreezeFrameFilter.IsOK = TRUE;
                                                    }
                                                    if (DemJ1939DcmFreezeFrameFilter.SPNCounter < RefNum)
                                                    {
                                                        const Dem_SPNClassType* pSPNClass =
                                                            &DemSPNClass[DemJ1939DcmFreezeFrameFilter.SPNIndex];
                                                        *SPNSupported = pSPNClass->DemSPNIdentifier;
                                                        *SPNDataLength = pSPNClass->DataSize;
                                                        DemJ1939DcmFreezeFrameFilter.SPNCounter++;
                                                        DemJ1939DcmFreezeFrameFilter.SPNIndex++;
                                                        ret = DEM_FILTERED_OK;
                                                    }
                                                    else
                                                    {
                                                        DemJ1939DcmFreezeFrameFilter.IsOK = FALSE;
                                                    }
                                                }
                                                break;
#endif /* DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u */
                                            case DEM_J1939DCM_FREEZEFRAME:
                                            case DEM_J1939DCM_EXPANDED_FREEZEFRAME:
                                            default:
#if (STD_ON == DEM_DEV_ERROR_DETECT)
                                                DEM_DET_REPORT(
                                                    DEM_SID_J1939DCMGETNEXTSPNINFREEZEFRAME,
                                                    DEM_E_WRONG_CONDITION);
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
                                                break;
                                            }
#if (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u)
                                        }
#endif /* DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u */
                                    }
                                }
                            }
                        }
                        else
                        {
                            ret = DEM_E_NODATAAVAILABLE;
                        }
                    }
                }
            }
        }
    }
    DemJ1939DcmFreezeFrameFilter.IsSet =
        ((DEM_FILTERED_OK == ret) || (DEM_FILTERED_PENDING == ret)) ? DemJ1939DcmFreezeFrameFilter.IsSet : FALSE;
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_EXPANDED_FREEZE_FRAME_SUPPORT == STD_ON */

#if (DEM_J1939_RATIO_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               The function sets the Ratio filter for a specific node and returns the
 * corresponding Ignition Cycle Counter and General Denominator.
 * ServiceId           0x99
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      node:Nm node Id of requesting client
 * Param-Name[out]     IgnitionCycleCounter: Ignition Cycle Counter
                        OBDMonitoringConditionsEncountered: OBD Monitoring Conditions Encountered
 * Param-Name[in/out]  None
 * Return              Status of the operation to (re-)set a DTC filter.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnSetFilterType, DEM_CODE)
Dem_J1939DcmSetRatioFilter(uint16* IgnitionCycleCounter, uint16* OBDMonitoringConditionsEncountered, uint8 node)
{
    Dem_ReturnSetFilterType ret = DEM_WRONG_FILTER;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMSETRATIOFILTER, DEM_E_UNINIT);
    }
    else if ((IgnitionCycleCounter == NULL_PTR) || (OBDMonitoringConditionsEncountered == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMSETRATIOFILTER, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        *IgnitionCycleCounter = IgnUpCycleCounter;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_RATIO_NUM > 0u)
        *OBDMonitoringConditionsEncountered = IUMPRValue[0].General_Denominator;
#endif /* DEM_RATIO_NUM > 0u */
        DemJ1939DcmRatioFilter.node = node;
        DemJ1939DcmRatioFilter.IsSet = TRUE;
        DemJ1939DcmRatioFilter.CurrentIndex = 0;
        ret = DEM_FILTER_ACCEPTED;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               The function sets the Ratio filter for a specific node and returns the
 * corresponding Ignition Cycle Counter and General Denominator.
 * ServiceId           0x9a
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     SPN:Receives the SPN of the applicaple system monitor. If the return value of the function is
 other than DEM_FILTERED_OK this parameter does not contain valid data. Numerator:Receives the Numerator of the
 applicable system monitor. If the return value of the function is other than DEM_FILTERED_OK this parameter does not
                        contain valid data.
                        Denominator:Receives the Denominator of the applicable system
                        monitor. If the return value of the function is other
                        than DEM_FILTERED_OK this parameter does not
                        contain valid data.
 * Param-Name[in/out]  None
 * Return              Status of the operation to (re-)set a DTC filter.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnGetNextFilteredElementType, DEM_CODE)
Dem_J1939DcmGetNextFilteredRatio(uint16* SPN, uint16* Numerator, uint16* Denominator)
{
    Dem_ReturnGetNextFilteredElementType ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTFILTEREDRATIO, DEM_E_UNINIT);
    }
    else if ((SPN == NULL_PTR) || (Numerator == NULL_PTR) || (Denominator == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMGETNEXTFILTEREDRATIO, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        ret = DEM_FILTERED_PENDING;
        /* SWS_Dem_00913 */
        if (Dem_Pending == FALSE)
        {
            const Dem_MemDestConfigType* pMemDestCfg =
                &DemMemDestCfg[Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY)];
            uint8 entryNum = pMemDestCfg->EntryNum;
            const Dem_EventMemEntryType* pEntry = pMemDestCfg->EntryList;
            const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
            const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
            const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
            ret = DEM_FILTERED_NO_MATCHING_ELEMENT;
            if (DemJ1939DcmRatioFilter.IsSet == TRUE)
            {
                /* PRQA S 2461++ */ /* MISRA Rule 14,2 */
                for (; (DemJ1939DcmRatioFilter.CurrentIndex < entryNum) && (ret != DEM_FILTERED_OK);
                     DemJ1939DcmRatioFilter.CurrentIndex++)
                /* PRQA S 2461++ */ /* MISRA Rule 14,2 */
                {
                    Dem_EventIdType EventId = pEntry[DemJ1939DcmRatioFilter.CurrentIndex].EventId;
                    if (EventId != 0x00u)
                    {
                        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
                        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                        uint16 dtcRef = pEventParameter[pEvent->IntId].DemDTCRef;
                        if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                        {
                            uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                            /* match kind and J1939DTC */
                            if ((DEM_OBD_DTC_INVALID != ObdDTCRef)
                                && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                            {
#if (DEM_J1939_NODE_NUM > 0u)
                                if (Dem_J1939CeckNode(dtcRef, DemJ1939DcmRatioFilter.node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                                {
#if (DEM_RATIO_NUM > 0u)
                                    uint32 DemJ1939DTCValue = pObdDTC[ObdDTCRef].DemJ1939DTCValue;

                                    /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                                    for (uint16 index = 0; index < DEM_RATIO_NUM; index++)
                                    /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                                    {
                                        /* SWS_Dem_01104 */
                                        if ((DemRatio[index].DemDiagnosticEventRef == IntId)
                                            && (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE)))
                                        {
                                            const IUMPRType* pIUMPRValue = &IUMPRValue[index];
                                            /*version 4 shall be used TODO:SPN in 1939-73 is 19 bits, and there only
                                             * 16bits to reported*/
                                            *SPN = (uint16)(((DemJ1939DTCValue & 0xff0000u) >> 16u)
                                                            | (DemJ1939DTCValue & 0x00ff00u));
                                            *Numerator = pIUMPRValue->Numerator;
                                            *Denominator = pIUMPRValue->Denominator;
                                            ret = DEM_FILTERED_OK;
                                            break;
                                        }
                                    }
#endif /* DEM_RATIO_NUM > 0u */
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    DemJ1939DcmRatioFilter.IsSet =
        ((DEM_FILTERED_OK == ret) || (DEM_FILTERED_PENDING == ret)) ? DemJ1939DcmRatioFilter.IsSet : FALSE;
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

#if (DEM_J1939_READINESS1_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Service to report the value of Diagnostic Readiness 1 (DM05) computed by the Dem.
 * ServiceId           0x9b
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      node:Nm node Id of requesting client
 * Param-Name[out]     DataValue:Buffer of 8 bytes containing the contents of Diagnostic Readiness 1 (DM05) computed by
 the Dem.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful
                        E_NOT_OK: Operation failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 2755++ */ /* MISRA CMN 0.4 */
Dem_J1939DcmReadDiagnosticReadiness1(Dem_J1939DcmDiagnosticReadiness1Type* DataValue, uint8 node)
/* PRQA S 2755-- */ /* MISRA CMN 0.4 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMREADDIAGNOSTICREADINESS1, DEM_E_UNINIT);
    }
    else if (DataValue == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMREADDIAGNOSTICREADINESS1, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const Dem_MemDestConfigType* pMemDestCfg =
            &DemMemDestCfg[Dem_GetInternalMemDest(DEM_DTC_ORIGIN_PRIMARY_MEMORY)];
        uint8 entryNum = pMemDestCfg->EntryNum;
        const Dem_EventMemEntryType* pEntry = pMemDestCfg->EntryList;
        const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
        const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
        const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;

        uint8 supportedGroups[3] = {0, 0, 0};
        uint8 notCompletedGroups[3] = {0, 0, 0};
        DataValue->ActiveTroubleCodes = 0;
        DataValue->PreviouslyActiveDiagnosticTroubleCodes = 0;
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        DataValue->OBDCompliance = DemGeneralOBD.DemOBDCompliancy;
#endif
        for (uint8 iloop = 0; iloop < entryNum; iloop++)
        {
            Dem_EventIdType EventId = pEntry->EventId;
            if (EventId != 0x00u)
            {
                Dem_EventIdType IntId = Dem_GetEventInternalId(pEntry->EventId);
                const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
                uint16 dtcRef = pEventParameter[IntId].DemDTCRef;
                if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                {
                    uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                    /* match J1939DTC */
                    if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                        && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                    {
#if (DEM_J1939_NODE_NUM > 0u)
                        if (Dem_J1939CeckNode(dtcRef, node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                        {
                            if (((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                                 && (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF)))
#if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
                                || (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] != DEM_INDICATOR_OFF)
#endif /* DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID */
                            )
                            {
                                DataValue->ActiveTroubleCodes += 1u;
                            }
                            if ((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                                && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
#if (DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
                                && (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] == DEM_INDICATOR_OFF)
#endif /* DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID */
                            )
                            {
                                DataValue->PreviouslyActiveDiagnosticTroubleCodes += 1u;
                            }
                        }
                    }
                }
            }
            pEntry++;
        }
        for (uint8 Index = 0; Index < DEM_NUMBER_OF_READINESS_GROUPS_FORJ1939; Index++)
        {
            for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
            {
                uint16 dtcRef = pEventParameter[iloop].DemDTCRef;
                if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                {
                    uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                    /* match J1939DTC */
                    if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                        && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID)
                        && (pObdDTC[ObdDTCRef].DemEventOBDReadinessGroup == Index))
                    {
#if (DEM_J1939_NODE_NUM > 0u)
                        if (Dem_J1939CeckNode(dtcRef, node) == TRUE)
#endif /* DEM_J1939_NODE_NUM > 0u */
                        {
                            uint8 UdsStatus = DemEventRelateInformation[iloop].UdsStatus;
                            DEM_BITS_SET(supportedGroups, Index);
                            if (((0x00u != DEM_FLAGS_ISSET(UdsStatus, DEM_UDS_STATUS_TF))
                                 || (0x00u != DEM_FLAGS_ISSET(UdsStatus, DEM_UDS_STATUS_TNCSLC)))
                                && (0x00u == DEM_FLAGS_ISSET(UdsStatus, DEM_UDS_STATUS_WIR)))
                            {
                                DEM_BITS_SET(notCompletedGroups, Index);
                            }
                        }
                    }
                }
            }
        }
        DataValue->ContinuouslyMonitoredSystemsSupport_Status =
            ((supportedGroups[0u] & 0xFu) | ((uint8)((notCompletedGroups[0u] & 0xFu) << 4u)));
        DataValue->NonContinuouslyMonitoredSystemsSupport =
            (((uint16)(((uint16)supportedGroups[0] & 0xF0u) >> 4u)) | (uint16)((uint16)supportedGroups[1u] << 4u)
             | (uint16)(((uint16)supportedGroups[2u] << 12u)));
        DataValue->NonContinuouslyMonitoredSystemsStatus =
            ((((uint16)notCompletedGroups[0u] & 0xF0u) >> 4u) | (uint16)((uint16)notCompletedGroups[1u] << 4u)
             | ((uint16)((uint16)notCompletedGroups[2u] << 12u)));
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_READINESS1_SUPPORT == STD_ON */

#if (DEM_J1939_READINESS2_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Service to report the value of Diagnostic Readiness 2 (DM21) computed by the Dem.
 * ServiceId           0x9c
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      node:Nm node Id of requesting client
 * Param-Name[out]     DataValue:Buffer of 8 bytes containing the contents of Diagnostic Readiness 2 (DM21) computed by
 the Dem.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful
                        E_NOT_OK: Operation failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmReadDiagnosticReadiness2(Dem_J1939DcmDiagnosticReadiness2Type* DataValue, uint8 node)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMREADDIAGNOSTICREADINESS2, DEM_E_UNINIT);
    }
    else if (DataValue == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMREADDIAGNOSTICREADINESS2, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        uint16 DistWithMilOn = 0U;
        uint16 currentDistanceInformation = Dem_ReadDistanceInformation();
        uint16 TimeWithMilOn = 0U;
        uint16 CurrentTimeInformation = Dem_ReadTimeInformation();
#endif
        DataValue->DistanceSinceDTCsCleared = 0;
        DataValue->DistanceTraveledWhileMILisActivated = 0;
        DataValue->MinutesRunbyEngineWhileMILisActivated = 0;
        DataValue->TimeSinceDiagnosticTroubleCodesCleared = 0;
        DEM_UNUSED(node);
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /* MinutesRunbyEngineWhileMILisActivated */
        if (DEM_INDICATOR_OFF != OBDMilStatus) /*the indicator is on*/
        {
            if (CurrentTimeInformation > OBDTimeMILLastOn)
            {
                TimeWithMilOn = CurrentTimeInformation - OBDTimeMILLastOn;
                OBDTimeMILLastOn = CurrentTimeInformation;
            }
        }
        if ((OBDTimeMILOn + TimeWithMilOn) < 0xFFFFu)
        {
            OBDTimeMILOn += TimeWithMilOn;
        }
        else
        {
            OBDTimeMILOn = 0xFFFFu;
        }
        /* J1939-73 */
        DataValue->MinutesRunbyEngineWhileMILisActivated = (OBDTimeMILOn < 0xFAFFu) ? OBDTimeMILOn : 0xFAFFu;
        /*TimeSinceDiagnosticTroubleCodesCleared*/
        if (CurrentTimeInformation > OBDTimeDTCLastClear)
        {
            OBDTimeDTCClear = CurrentTimeInformation - OBDTimeDTCLastClear;
        }
        /* J1939-73 */
        DataValue->TimeSinceDiagnosticTroubleCodesCleared = (OBDTimeDTCClear < 0xFAFFu) ? OBDTimeDTCClear : 0xFAFFu;
        /*DistanceSinceDTCsCleared*/
        if (currentDistanceInformation > OBDDistanceDTCClear)
        {
            DistSinceDtcCleared = currentDistanceInformation - OBDDistanceDTCClear;
        }
        /* J1939-73 */
        DataValue->DistanceSinceDTCsCleared = (DistSinceDtcCleared < 0xFAFFu) ? DistSinceDtcCleared : 0xFAFFu;
        /*DistanceTraveledWhileMILisActivated*/
        if (DEM_INDICATOR_OFF != OBDMilStatus) /*the indicator is on*/
        {
            if (currentDistanceInformation > OBDDistanceMILLastOn)
            {
                DistWithMilOn = currentDistanceInformation - OBDDistanceMILLastOn;
                OBDDistanceMILLastOn = currentDistanceInformation;
            }
        }
        if ((OBDDistanceMILOn + DistWithMilOn) < 0xFFFFu)
        {
            OBDDistanceMILOn += DistWithMilOn;
        }
        else
        {
            OBDDistanceMILOn = 0xFFFFu;
        }
        /* J1939-73 */
        DataValue->DistanceTraveledWhileMILisActivated = (OBDDistanceMILOn < 0xFAFFu) ? OBDDistanceMILOn : 0xFAFFu;
        ret = E_OK;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_READINESS2_SUPPORT == STD_ON */

#if (DEM_J1939_READINESS3_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Service to report the value of Diagnostic Readiness 3 (DM26) computed by the Dem.
 * ServiceId           0x9d
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      node:Nm node Id of requesting client
 * Param-Name[out]     DataValue:Buffer of 8 bytes containing the contents of Diagnostic Readiness 3 (DM26) computed by
 the Dem.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful
                        E_NOT_OK: Operation failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmReadDiagnosticReadiness3(Dem_J1939DcmDiagnosticReadiness3Type* DataValue, uint8 node)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMREADDIAGNOSTICREADINESS3, DEM_E_UNINIT);
    }
    else if (DataValue == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_J1939DCMREADDIAGNOSTICREADINESS3, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        uint8 enabledGroups[3] = {0xffu, 0xffu, 0xffu};
        uint8 notCompletedGroups[3] = {0, 0, 0};
        const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
        const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
        const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;

        DEM_UNUSED(node);
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        DataValue->TimeSinceEngineStart = Dem_ReadTimeInformation();
        DataValue->NumberofWarmupsSinceDTCsCleared = WarmUpCycleCounter;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
        for (uint8 Index = 0; Index < DEM_NUMBER_OF_READINESS_GROUPS_FORJ1939; Index++)
        {
            for (uint8 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
            {
                const Dem_EventParameterType* pEventCfg = &pEventParameter[iloop];
                uint16 dtcRef = pEventParameter[iloop].DemDTCRef;
                if ((dtcRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[dtcRef].SuppressionStatus == FALSE))
                {
                    uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
                    /* match J1939DTC */
                    if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                        && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID)
                        && (pObdDTC[ObdDTCRef].DemEventOBDReadinessGroup == Index))
                    {
                        /* Only include emission related DTCs */
                        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
                        uint8 DemOperationCycleRef = pEventCfg->DemOperationCycleRef;
                        if ((DEM_BITS_ISSET(DemOperationCycleStatus, DemOperationCycleRef))
                            && (DemOperationCycle[DemOperationCycleRef].DemOperationCycleType == DEM_OPCYC_POWER))
                        {
                            if (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
                            {
                                /* SWS_Dem_00356 SWS_Dem_00348 */
                                DEM_BITS_CLR(enabledGroups, Index);
                            }
                        }
                        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC))
                        {
                            /* SWS_Dem_00355 */
                            DEM_BITS_SET(notCompletedGroups, Index);
                        }
                    }
                }
            }
        }
        DataValue->ContinuouslyMonitoredSystemsEnableCompletedStatus =
            ((enabledGroups[0u] & 0xFu) | (uint8)((notCompletedGroups[0u] & 0xFu) << 4u));
        DataValue->NonContinuouslyMonitoredSystemsEnableStatus =
            ((uint16)(((uint16)enabledGroups[0u] & 0xF0u) >> 4u) | (uint16)(((uint16)enabledGroups[1u] << 4u))
             | (uint16)(((uint16)enabledGroups[2u] << 12u)));
        DataValue->NonContinuouslyMonitoredSystems =
            ((uint16)(((uint16)notCompletedGroups[0u] & 0xF0u) >> 4u) | (uint16)((uint16)notCompletedGroups[1u] << 4u)
             | (uint16)((uint16)notCompletedGroups[2u] << 12u));
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_J1939_READINESS3_SUPPORT == STD_ON */

#endif /* DEM_J1939_SUPPORT == STD_ON */
/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
