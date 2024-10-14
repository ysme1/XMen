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
 **  FILENAME    : Dem_Internal.c                                              **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API definitions of DEM for internal                         **
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
#include "Dem.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#define DEM_START_SEC_VAR_POWER_ON_INIT_8
#include "Dem_MemMap.h"
VAR(Dem_ClearLockStatus, AUTOMATIC) Dem_ClearDTCLock = DEM_CLEAR_NOT_LOCK;
#define DEM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_POWER_ON_INIT_8
#include "Dem_MemMap.h"
VAR(Dem_ClearNonvolatileStatusType, AUTOMATIC)
Dem_ClearNonvolatileStatus = DEM_ClEAR_NONVOLATILE_INIT;
#define DEM_STOP_SEC_VAR_POWER_ON_INIT_8
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(Dem_ClearDTCInfoType, AUTOMATIC) DemClearDTCInfo;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(Dem_InternalDataType, AUTOMATIC) DemInternalData;
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT_BOOLEAN
#include "Dem_MemMap.h"
VAR(boolean, AUTOMATIC) Dem_Pending = FALSE;
#define DEM_STOP_SEC_VAR_INIT_BOOLEAN
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/

#if (DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS)
#if (DEM_GROUP_OF_DTC_NUM > 0)
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearGroupDTC(uint8 memDest, uint8 GroupIndex);
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearOneDTC(uint8 memDest, uint16 DTCIndex);
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

DEM_LOCAL FUNC(void, DEM_CODE)
    Dem_Clear(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent, uint8 memDest);
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*************************************************************************/
/*
 * Brief               ClearAllDTC
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant/Non Reentrant
 * Param-Name[in]      memDest
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearAllDTC(uint8 memDest)
{
    Dem_EventRelateInformationType* pEvent = DemEventRelateInformation;
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
    const Dem_ClearDTCInfoType* pClr = &DemClearDTCInfo;
    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
    const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;

    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        boolean DoClear = TRUE;
        uint16 dtcRef = pEventParameter->DemDTCRef;
        if (dtcRef != DEM_DTC_REF_INVALID)
        {
            uint16 ObdDTCRef = pDTC[dtcRef].DemObdDTCRef;
            if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                && (pObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
            {
                DoClear = FALSE;
#if (DEM_J1939_NODE_NUM > 0u)
                if ((pClr->SID == DEM_SID_J1939DCMCLEARDTC)
                    && (((pClr->DTCTypeFilter == DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE)
                         && ((0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC))
                             && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))))
                        || ((pClr->DTCTypeFilter == DEM_J1939DTC_CLEAR_ALL)
                            && (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF)))))
                {
                    DoClear = Dem_J1939CeckNode(dtcRef, pClr->node);
                }
                else
#endif /* DEM_J1939_NODE_NUM > 0u */
                    if (pClr->SID != DEM_SID_J1939DCMCLEARDTC)
                    {
                        DoClear = TRUE;
                    }
                    else
                    {
                        /* do nothing */
                    }
            }
        }
        if (DoClear == TRUE)
        {
            Dem_Clear(pEvent, memDest);
        }
        pEvent++;
        pEventParameter++;
    }
    /*SWS_Dem_00399] */
    if (DemMemDestInfo[memDest].RecordNum == 0u)
    {
        DemMemDestInfo[memDest].OverFlow = FALSE;
    }
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    Dem_ClearOBDInfo();
#endif
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS)
#if (DEM_GROUP_OF_DTC_NUM > 0u)
/*************************************************************************/
/*
 * Brief               ClearGroupDTC
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
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearGroupDTC(uint8 memDest, uint8 GroupIndex)
{
    const Dem_EventParameterType* pEventParameter = DemPbCfgPtr->DemEventParameter;
    Dem_EventRelateInformationType* pEvent = DemEventRelateInformation;
    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        uint16 Ref = pEventParameter->DemDTCRef;
        if ((Ref != DEM_DTC_REF_INVALID) && (pDTC[Ref].GroupRef == GroupIndex)
            && (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION)))
        {
            Dem_Clear(pEvent, memDest);
        }
        pEvent++;
        pEventParameter++;
    }
    /*SWS_Dem_00399] */
    if (DemMemDestInfo[memDest].RecordNum == 0u)
    {
        DemMemDestInfo[memDest].OverFlow = FALSE;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_GROUP_OF_DTC_NUM > 0u */
/*************************************************************************/
/*
 * Brief               ClearOneDTC
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
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearOneDTC(uint8 memDest, uint16 DTCIndex)
{
    const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DTCIndex];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
    const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
    const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
    const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
    for (uint16 iloop = 0u; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(*pDTCMapping);
        Dem_Clear(pEvent, memDest);
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
        pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
    }
    /*SWS_Dem_00399] */
    if (DemMemDestInfo[memDest].RecordNum == 0u)
    {
        DemMemDestInfo[memDest].OverFlow = FALSE;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS */

/*************************************************************************/
/*
 * Brief               ClearDTCProcess
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
FUNC(void, DEM_CODE) Dem_ClearDTCProcess(void)
{
    const Dem_ClearDTCInfoType* pClr = &DemClearDTCInfo;
    uint8 memDest = pClr->memDest;
    /* SWS_Dem_00171 */
    if (memDest != DEM_MEM_DEST_INVALID)
    {
        if (pClr->ClearAllGroup == TRUE)
        {
            Dem_ClearAllDTC(memDest);
        }
#if (DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS)
        else
        {
#if (DEM_GROUP_OF_DTC_NUM > 0u)
            uint8 DTCGroupIndex = pClr->DTCGroupIndex;
            if (DTCGroupIndex != DEM_GROUP_OF_DTC_INVALID)
            {
                Dem_ClearGroupDTC(memDest, DTCGroupIndex);
            }
            else
#endif /* DEM_GROUP_OF_DTC_NUM > 0u */
            {
                uint16 DTCIndex = pClr->DTCIndex;
                if (DTCIndex != DEM_DTC_REF_INVALID)
                {
                    Dem_ClearOneDTC(memDest, DTCIndex);
                }
            }
        }
#endif /* DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS */
        Dem_Pending = FALSE;
#if (DEM_CLEAR_DTCBEHAVIOR != DEM_CLRRESP_NONVOLATILE_FINISH)
        Dem_ClearDTCLock = DEM_CLEAR_NOT_LOCK;
#endif
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               BRIEF DESCRIPTION
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DTC && DTCFormat
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              DTC Index
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(uint16, DEM_CODE) Dem_GetDTCIndex(uint32 DTC, Dem_DTCFormatType DTCFormat)
{
    uint16 ret = DEM_DTC_REF_INVALID;
    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
    const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;

    switch (DTCFormat)
    {
    case DEM_DTC_FORMAT_UDS:
        for (uint16 index = 0; index < DEM_DTC_NUM; index++)
        {
            if (pDTC->DemDtcValue == DTC)
            {
                ret = index;
                break;
            }
            pDTC++;
        }
        break;
    case DEM_DTC_FORMAT_OBD:
        for (uint16 index = 0; index < DEM_DTC_NUM; index++)
        {
            uint16 ObdDTCRef = pDTC->DemObdDTCRef;
            if ((ObdDTCRef != DEM_OBD_DTC_INVALID) && (pObdDTC[ObdDTCRef].DemDtcValue == DTC))
            {
                ret = index;
                break;
            }
            pDTC++;
        }
        break;
    case DEM_DTC_FORMAT_J1939:
        for (uint16 index = 0; index < DEM_DTC_NUM; index++)
        {
            uint16 ObdDTCRef = pDTC->DemObdDTCRef;
            if ((ObdDTCRef != DEM_OBD_DTC_INVALID) && (pObdDTC[ObdDTCRef].DemJ1939DTCValue == DTC))
            {
                ret = index;
                break;
            }
            pDTC++;
        }
        break;
    default:
        /*idle*/
        break;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_Clear
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      memDest && pEntry && pEvent
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432,1505++ */ /* MISRA Rule 20.7,8.7 */
DEM_LOCAL FUNC(void, DEM_CODE)
    Dem_Clear(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent, uint8 memDest)
/* PRQA S 3432,1505-- */ /* MISRA Rule 20.7,8.7 */
{
    boolean clear = FALSE;
    Dem_EventIdType IntId = pEvent->IntId;
    const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
    const Dem_CallbackInitMForEType InitMForE = pEventCfg->DemCallbackInitMForE;
    const Dem_CallbackClearEventAllowedType* pClearEventAllowed = pEventCfg->DemCallbackClearEventAllowed;
    boolean allowed = FALSE;
#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
    const Dem_IndicatorAttributeType* pWIRAttr = &DemIndicatorAttribute[pEventCfg->AttrStartIndex];
    uint8 AttrNum = pEventCfg->AttrNum;
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
    uint8 OldStatus = pEvent->UdsStatus;
#endif

#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[pEventCfg->DemDTCRef];
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */

    /* SWS_Dem_00514 SWS_Dem_00515 */
    /* req SWS_Dem_00680 Monitor re-initialization  */
    if (InitMForE != NULL_PTR)
    {
        (*InitMForE)(DEM_INIT_MONITOR_CLEAR);
    }

    if ((pClearEventAllowed != NULL_PTR) && (pClearEventAllowed->ClearEventAllowed != NULL_PTR))
    {
        if (E_OK == pClearEventAllowed->ClearEventAllowed(&allowed))
        {
            if (allowed == TRUE)
            {
                /* SWS_Dem_00385 */
                pEvent->UdsStatus = 0x00;
                /* bit 4 6 the initialized value 0x50 */
                DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
            }
            else
            {
                /* SWS_Dem_00667 */
                clear = TRUE;
                if (pClearEventAllowed->DemClearEventAllowedBehavior == DEM_ONLY_THIS_CYCLE_AND_READINESS)
                {
                    /* SWS_Dem_00669 SWS_Dem_00668 */
                    /* bit 4 6 reset */
                    DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
                    /* bit 1 5 reset */
                    DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TFSLC);
                }
            }
        }
        /* SWS_Dem_00516 */
        else
        {
            /* SWS_Dem_00385 */
            pEvent->UdsStatus = 0x00;
            /* bit 4 6 the initialized value 0x50 */
            DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
        }
    }
    else
    {
        /* SWS_Dem_00385 */
        /* All other bits are set to 0 */
        pEvent->UdsStatus = 0x00;
        /* bit 4 6 set to 1 */
        DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
    }
    /* update the combination event dtc status*/
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    /* All other bits are set to 0 */
    DEM_FLAGS_CLR(
        pEvent->StatusIndicator30,
        DEM_SI30_DTC_UCSLC | DEM_SI30_DTC_SSLC | DEM_SI30_DTC_WIRSLC); /*bit 2,4,5*/

    /*bit 6: The bit is set to 0 when the DTC is not emission related.The bit is set to 1 when the DTC is emission
     * related.*/
    if ((pDemDTC->DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS))
    {
        DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_ER);
    }
    else
    {
        DEM_FLAGS_CLR(pEvent->StatusIndicator30, DEM_SI30_DTC_ER);
    }
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
    Dem_UpdateCombinedDtcStatus(IntId);
    Dem_ResponseOnDtcStatusChange(IntId);
    if (clear == FALSE)
    {
        Dem_EventMemEntryType* pEntry;
        uint16 DTCRef = pEventCfg->DemDTCRef;
#if ((DEM_OCC6EANLE == STD_ON) || (DEM_OCC4EANLE == STD_ON))
        DEM_FLAGS_CLR(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_THISOPISFAILED);
#endif /* DEM_OCC6EANLE == STD_ON) || (DEM_OCC4EANLE == STD_ON */
        /* SWS_Dem_00343 */
        Dem_DebounceReset(IntId);
        if (DTCRef != DEM_DTC_REF_INVALID)
        {
            /* SWS_Dem_00794 */
            FDCInfo[DTCRef].MaxFDCSinceLastClear = 0;
            FDCInfo[DTCRef].MaxFDCDuringCurrentCycle = 0;
        }
#if (DEM_DTR_NUM > 0u)
        /* SWS_Dem_00763 */
        Dem_ClearDTRInfoByEventID(IntId);
#endif /* DEM_DTR_NUM > 0u */
#if ((DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u))
        allowed = TRUE;
        for (uint8 kloop = 0; (kloop < AttrNum) && (TRUE == allowed); kloop++)
        {
            uint8 DemIndicatorRef = pWIRAttr->DemIndicatorRef;
            const Dem_EventRelateInformationType* EventPtr = DemEventRelateInformation;
            const Dem_EventParameterType* pEventCfg2 = DemPbCfgPtr->DemEventParameter;
            for (uint16 iloop = 0; (iloop < DEM_EVENT_PARAMETER_NUM) && (TRUE == allowed); iloop++)
            {
                const Dem_IndicatorAttributeType* pIndicatorAttr = &DemIndicatorAttribute[pEventCfg2->AttrStartIndex];
                for (uint8 jloop = 0; (jloop < pEventCfg2->AttrNum) && (TRUE == allowed); jloop++)
                {
                    if ((DemIndicatorRef == pIndicatorAttr->DemIndicatorRef)
                        && (0x00u != DEM_FLAGS_ISSET(EventPtr->UdsStatus, DEM_UDS_STATUS_WIR)))
                    {
                        allowed = FALSE;
                    }
                    pIndicatorAttr++;
                }
                EventPtr++;
                pEventCfg2++;
            }
            if (TRUE == allowed)
            {
                DemWIRStatus[DemIndicatorRef] = DEM_INDICATOR_OFF;
            }
            pWIRAttr++;
        }
#endif /* DEM_INDICATOR_NUM > 0u) && (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */
        /*SWS_Dem_00667]*/
        pEntry = Dem_MemEntryGet(Dem_GetEventExternalId(IntId), memDest);
        if (pEntry != NULL_PTR)
        {
            Dem_MemEntryDelete(pEntry, memDest); /*SWS_Dem_00660] */
        }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
        (void)FiM_DemTriggerOnEventStatus(Dem_GetEventExternalId(IntId), OldStatus, pEvent->UdsStatus);
#endif
    }
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u)
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Dem_CheckEventAllIndicator
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              boolean
 */
/*************************************************************************/
FUNC(boolean, DEM_CODE) Dem_CheckEventAllIndicator(uint16 IntId)
{
    const Dem_EventParameterType* pEventParameter = &DemPbCfgPtr->DemEventParameter[IntId];
    uint8 num = pEventParameter->AttrNum;
    uint16 start = pEventParameter->AttrStartIndex;
    const Dem_IndicatorAttributeType* pIndicatorAttr = &DemIndicatorAttribute[start];
    boolean ret = TRUE;

    for (uint16 iloop = 0; iloop < num; iloop++)
    {
        if (DemWIRStatus[pIndicatorAttr->DemIndicatorRef] != DEM_INDICATOR_OFF)
        {
            ret = FALSE;
            break;
        }
        pIndicatorAttr++;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0u */

#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Dem_GetFncData>
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DataReadFnc,DataSize
 * Param-Name[out]     pBuffer
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_GetFncData(DemDataElementReadFncType DataReadFnc, uint8* pBuffer, uint8 DataSize)
{
    if (DataReadFnc != NULL_PTR)
    {
        if (DataReadFnc(pBuffer) != E_OK)
        {
            Dem_MemSet(pBuffer, 0xFFu, DataSize);
#if (STD_ON == DEM_DEV_ERROR_DETECT)
            DEM_DET_REPORT(DEM_SID_MAINFUNCTION, DEM_E_NODATAAVAILABLE);
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Dem_UpdateInternalData
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
FUNC(void, DEM_CODE) Dem_UpdateInternalData(uint16 IntId)
{
    const Dem_EventParameterType* pEventCfg = &DemPbCfg.DemEventParameter[IntId];
    const Dem_EventRelateInformationType* pEvent = &DemEventRelateInformation[IntId];
    uint16 DTCRef = pEventCfg->DemDTCRef;
    sint8 FDC;
    Dem_EventIdType EventId = Dem_GetEventExternalId(IntId);

    Dem_UpdateFDC(IntId);
    (void)Dem_DTCGetFaultDetectionCounter(EventId, &FDC);
    /* SWS_Dem_00471 */
    DemInternalData.Occctr = pEvent->OccurrenceCounter;
    if (DTCRef != DEM_DTC_REF_INVALID)
    {
        const uint8* pMemDest;
        const Dem_DTCAttributesType* pDTCAttrCfg =
            &DemPbCfg.DemDTCAttributes[DemPbCfg.DemDTC[DTCRef].DemDTCAttributesRef];
        uint8 AgingCounter = pEvent->AgingCounter;
        const FDCInfoType* pFDCInfo = &FDCInfo[DTCRef];
        uint8 iloop = 0;

        if (pDTCAttrCfg->DemAgingAllowed == FALSE)
        {
            /* SWS_Dem_01044 */
            DemInternalData.AgingUpCnt = 0;
        }
        else
        {
            /* SWS_Dem_00643 */
            DemInternalData.AgingUpCnt = AgingCounter;
        }
        if (pDTCAttrCfg->DemAgingAllowed == FALSE)
        {
            /* SWS_Dem_01043 */
            DemInternalData.AgingDownCnt = pDTCAttrCfg->DemAgingCycleCounterThreshold;
        }
        else
        {
            /* SWS_Dem_00673 */
            DemInternalData.AgingDownCnt = pDTCAttrCfg->DemAgingCycleCounterThreshold - AgingCounter;
        }
        pMemDest = pDTCAttrCfg->DemMemoryDestinationRef;
        DemInternalData.Ovflind = 0; /* means FALSE*/
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
        for (; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
        {
            if (pMemDest[iloop] != DEM_MEM_DEST_INVALID)
            {
                if (DemMemDestInfo[pMemDest[iloop]].OverFlow == TRUE)
                {
                    /*if the memDest have one OverFlow is true, then the internal OverFlow is true*/
                    DemInternalData.Ovflind = 1; /* means TRUE*/
                }
            }
        }
        /* SWS_Dem_01084 */
        DemInternalData.Significance = pDTCAttrCfg->DemDTCSignificance;

        /* SWS_Dem_00819 */
        DemInternalData.MaxFDCDuringCurrentCycle = pFDCInfo->MaxFDCDuringCurrentCycle;
#if (DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON)
        /* SWS_Dem_00818 */
        DemInternalData.MaxFDCSinceLastClear = pFDCInfo->MaxFDCSinceLastClear;
#endif /* DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON */
        /* SWS_Dem_01084 */
        if (FDC < 0)
        {
            DemInternalData.CurrentFDC = (uint8)(0xFFu + (uint8)FDC + 1u);
        }
        else
        {
            DemInternalData.CurrentFDC = (uint8)FDC;
        }
    }
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
    /* SWS_Dem_00820 */
    DemInternalData.CyclesSinceLastFailed = pEvent->CyclesSinceLastFailed;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
    /* SWS_Dem_00821 */
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
    DemInternalData.CyclesSinceFirstFailed = pEvent->CyclesSinceFirstFailed;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
    /* SWS_Dem_00822 */
    DemInternalData.FailedCycles = pEvent->FailureCounter;
#if (DEM_OCC6EANLE == STD_ON)
    DemInternalData.OCC6 = pEvent->OCC6;
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
    DemInternalData.OCC4 = pEvent->OCC4;
#endif /* DEM_OCC4EANLE == STD_ON */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    DemInternalData.StatusIndicator30 = pEvent->StatusIndicator30;
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
