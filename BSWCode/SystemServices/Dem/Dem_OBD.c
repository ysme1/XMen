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
 **  FILENAME    : Dem_OBD.c                                                   **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API definitions of DEM for OBD                              **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem_Internal.h"
#include "Dem.h"
#include "Dem_Dcm.h"
#if (STD_ON == DEM_TRIGGER_FIM_REPORTS)
#include "FiM.h"
#endif /* STD_ON == DEM_TRIGGER_FIM_REPORTS */

/*******************************************************************************
**                      macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) || (DEM_J1939_SUPPORT == STD_ON))
#if (DEM_RATIO_NUM > 0u)
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
IUMPRType IUMPRValue[DEM_RATIO_NUM];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#endif /* DEM_RATIO_NUM > 0u */

/* PRQA S 3408++ */ /* MISRA Rule 8.4 */
#define DEM_START_SEC_VAR_NO_INIT_16
#include "Dem_MemMap.h"
Dem_IndicatorStatusType OBDMilStatus;
uint16 OBDDistanceMILOn;
uint16 OBDTimeMILOn;
uint16 OBDTimeDTCClear;
uint16 DistSinceDtcCleared;
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
uint16 IgnUpCycleCounter;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
uint16 OBDDistanceMILLastOn;
uint16 OBDTimeMILLastOn;
uint16 OBDDistanceDTCClear;
uint16 OBDTimeDTCLastClear;
#define DEM_STOP_SEC_VAR_NO_INIT_16
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_8
#include "Dem_MemMap.h"
uint8 WarmUpCycleCounter;
#define DEM_STOP_SEC_VAR_NO_INIT_8
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Dem_MemMap.h"
boolean CurrentPTOStatus;
#define DEM_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT_16
#include "Dem_MemMap.h"
uint16 ContinuousMICounter = 0;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
uint16 MasterContinuousMICounter = 0;
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
uint16 OBDB1Counter = 0;
#define DEM_STOP_SEC_VAR_INIT_16
#include "Dem_MemMap.h"
/* PRQA S 3408-- */ /* MISRA Rule 8.4 */

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define DEM_START_SEC_VAR_INIT_BOOLEAN
#include "Dem_MemMap.h"
DEM_LOCAL boolean PFCStatu = FALSE; /* PRQA S 3218 */       /* MISRA Rule 8.9 */
DEM_LOCAL boolean SetDataOfPid21 = FALSE; /* PRQA S 3218 */ /* MISRA Rule 8.9 */
#define DEM_STOP_SEC_VAR_INIT_BOOLEAN
#include "Dem_MemMap.h"

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#define DEM_START_SEC_VAR_NO_INIT_8
#include "Dem_MemMap.h"
DEM_LOCAL Dem_IumprDenomCondStatusType ConditionStatu[5];
#define DEM_STOP_SEC_VAR_NO_INIT_8
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
#if (DEM_DTR_NUM > 0u)
DEM_LOCAL DTRInfoType DTRInfo[DEM_DTR_NUM];
#endif /* DEM_DTR_NUM > 0u */
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
/* PRQA S 3218 ++ */ /* MISRA Rule 8.9 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
DEM_LOCAL Dem_IndicatorStatusType lastMilStatus = DEM_INDICATOR_OFF;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
DEM_LOCAL uint8 WarmUpCycleCounterForMI = 0;
DEM_LOCAL uint8 CycleCounterForMI = 0;
DEM_LOCAL uint8 CycleCounterForB1 = 0;
DEM_LOCAL uint8 TimeCycleCounterForMI = 0;
/* PRQA S 3218 -- */ /* MISRA Rule 8.9 */
#define DEM_STOP_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
/*******************************************************************************
**                      Private Function Definitions                         **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
#if (DEM_RATIO_NUM > 0u)
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CalIUMPRValue(Dem_RatioIdType Dem_RatioId);
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CalIUMPRDenValue(Dem_RatioIdType Dem_RatioId);
#if ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU)) /* SWS_Dem_00710 */
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CalIUMPRNumValue(Dem_RatioIdType Dem_RatioId);
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU */
DEM_LOCAL FUNC(uint16, DEM_CODE) Dem_GetIUMPRDenValueByGroup(Dem_IUMPRGroupType Dem_IUMPRGroup);
DEM_LOCAL FUNC(uint16, DEM_CODE) Dem_GetIUMPRNumValueByGroup(Dem_IUMPRGroupType Dem_IUMPRGroup);
#endif /* DEM_RATIO_NUM > 0u */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(P2CONST(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR), DEM_CODE)
    Dem_SelectOBDFreezeFrame(P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA) IntId);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#endif              /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
DEM_LOCAL FUNC(void, DEM_CODE) Dem_B1CounterProcess(void);
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               Init the OBD related data.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_OBDInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    WarmUpCycleCounter = 0;
    /*distance related*/
    OBDDistanceMILOn = 0;
    OBDDistanceDTCClear = 0;
    DistSinceDtcCleared = 0;
    OBDDistanceMILLastOn = 0;
    /*time related*/
    OBDTimeMILOn = 0;
    OBDTimeDTCClear = 0;
    OBDTimeDTCLastClear = 0;
    OBDTimeMILLastOn = 0;
    SetDataOfPid21 = FALSE;
    PFCStatu = FALSE;
    OBDMilStatus = DEM_INDICATOR_OFF;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_DTR_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Init the IUMPR.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_DTRInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Dem_MemSet((uint8*)DTRInfo, 0u, (sizeof(DTRInfoType) * DEM_DTR_NUM));
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Init the IUMPR.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_IUMPRInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    IgnUpCycleCounter = 0;
#endif
    for (uint8 iloop = 0; iloop < DEM_RATIO_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        IUMPRValue[iloop].IUMPRDenStatus = TRUE;
        IUMPRValue[iloop].IUMPRNumStatus = FALSE;
        IUMPRValue[iloop].Denominator = 0;
        IUMPRValue[iloop].Numerator = 0;
        IUMPRValue[iloop].General_Denominator = 0;
    }
    ConditionStatu[0] = 3;
    ConditionStatu[1] = 3;
    ConditionStatu[2] = 3;
    ConditionStatu[3] = 3;
    ConditionStatu[4] = 3;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DTR_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Update the Current OBD Mil Status.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_UpdateOBDMilStatus(uint8 indicatorRef, uint16 IntID) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    if (indicatorRef == DEM_MALFUNCTION_LAMP_INDICATOR)
    {
        uint16 DemDTCRef = DemPbCfgPtr->DemEventParameter[IntID].DemDTCRef;
        const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
        const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
#if (DEM_INDICATOR_NUM > 0u)
        Dem_IndicatorStatusType currentMilStatus = DemWIRStatus[indicatorRef];
        if (currentMilStatus != DEM_INDICATOR_OFF)
        {
            /* MIL recently activated */
            if ((DemDTCRef != DEM_DTC_REF_INVALID)
                && ((pDTC[DemDTCRef].DemDtcValue < 0xFFFF33UL)
                    || ((DEM_OBD_DTC_INVALID != pDTC[DemDTCRef].DemObdDTCRef)
                        && (pObdDTC[pDTC[DemDTCRef].DemObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID))))
            {
                /* SWS_Dem_01139 */
                OBDMilStatus = currentMilStatus;
            }
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            /* Read current distance information */
            if (lastMilStatus == DEM_INDICATOR_OFF)
            {
                OBDDistanceMILLastOn = Dem_ReadDistanceInformation();
                OBDTimeMILLastOn = Dem_ReadTimeInformation();
            }
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
        }
        else
#endif /* DEM_INDICATOR_NUM > 0u */
        {
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            uint16 CurrentDistance = Dem_ReadDistanceInformation();
            uint16 CurrentTime = Dem_ReadTimeInformation();
            if (CurrentTime > OBDTimeMILLastOn)
            {
                if ((uint16)(CurrentTime - OBDTimeMILLastOn + OBDTimeMILOn) < 0xFFFFu)
                {
                    OBDTimeMILOn += CurrentTime - OBDTimeMILLastOn;
                    OBDTimeMILLastOn = CurrentTime;
                }
                else
                {
                    OBDTimeMILOn = 0xFFFFu;
                }
            }
            if (CurrentDistance > OBDDistanceMILLastOn)
            {
                if ((uint16)(CurrentDistance - OBDDistanceMILLastOn + OBDDistanceMILOn) < 0xFFFFu)
                {
                    OBDDistanceMILOn += CurrentDistance - OBDDistanceMILLastOn;
                    OBDDistanceMILLastOn = CurrentDistance;
                }
                else
                {
                    OBDDistanceMILOn = 0xFFFFu;
                }
            }
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
            /* MIL recently de-activated */
            if ((DemDTCRef != DEM_DTC_REF_INVALID)
                && ((pDTC[DemDTCRef].DemDtcValue < 0xFFFF33UL)
                    || ((DEM_OBD_DTC_INVALID != pDTC[DemDTCRef].DemObdDTCRef)
                        && (pObdDTC[pDTC[DemDTCRef].DemObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID))))
            { /*SWS_Dem_01139] */
                OBDMilStatus = currentMilStatus;
            }
        }
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_INDICATOR_NUM > 0u)
        lastMilStatus = currentMilStatus;
#else
        lastMilStatus = DEM_INDICATOR_OFF;
#endif /* DEM_INDICATOR_NUM > 0u */
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Clear the OBD Information on clearing dtc.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_ClearOBDInfo(void) /* PRQA S 1532,3408 */ /* MISRA Rule 8.7,Rule 8.4 */
{
    /* Clear counters if all OBD DTCs have been cleared */
    WarmUpCycleCounter = 0;
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    OBDDistanceDTCClear = Dem_ReadDistanceInformation();
    OBDTimeDTCLastClear = Dem_ReadTimeInformation();
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
    OBDTimeDTCClear = 0;
    ContinuousMICounter = 0; /*SWS_Dem_01146]*/
    OBDB1Counter = 0;
    OBDDistanceMILOn = 0;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Calculate the OBD related data.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_CalOBDRelatedValue(uint8 OperationId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
    if (OBDMilStatus == DEM_INDICATOR_OFF)
    {
        if (CycleCounterForMI < 0xFFu)
        {
            CycleCounterForMI++;
        }
    }
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
        uint16 DemDTCRef = pEventCfg->DemDTCRef;
        if ((DemDTCRef != DEM_DTC_REF_INVALID) && (pDTC[DemDTCRef].DemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_B1)
            && ((DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF) != 0x00u)
                && (DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_CDTC) != 0x00u)))
        {
            CycleCounterForB1 = 0;
            break;
        }
        CycleCounterForB1++;
        pEventCfg++;
    }
    if (CycleCounterForB1 > 200u)
    {
        /* SWS_Dem_01157 */
        OBDB1Counter = 190u;
    }
    else if (CycleCounterForB1 > 3u)
    {
        /* SWS_Dem_01156 */
        OBDB1Counter = 0u;
    }
    else
    {
        /*idle*/
    }
    switch (DemOperationCycle[OperationId].DemOperationCycleType)
    {
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    case DEM_OPCYC_IGNITION:
        IgnUpCycleCounter++;
        break;
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_RATIO_NUM > 0u)
    case DEM_OPCYC_OBD_DCY:
        for (uint8 iloop = 0; iloop < DEM_RATIO_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
        {
            uint8 DemDiagnosticEventRef = DemRatio[iloop].DemDiagnosticEventRef;
            uint16 DemDTCRef = DemPbCfgPtr->DemEventParameter[DemDiagnosticEventRef].DemDTCRef;
            const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(DemDiagnosticEventRef);
            /* SWS_Dem_01104 SWS_Dem_00709 */
            if ((DemDTCGeneralStatus[DemDTCRef].SuppressionStatus != TRUE)
                && (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE)))
            {
                Dem_CalIUMPRValue(iloop);
            }
        }
        break;
#endif /* DEM_RATIO_NUM > 0u */
    case DEM_OPCYC_WARMUP:
        if (WarmUpCycleCounter < 0xFFu)
        {
            WarmUpCycleCounter++;
        }
        if (OBDMilStatus == DEM_INDICATOR_OFF)
        {
            if (WarmUpCycleCounterForMI < 40u)
            {
                /* SWS_Dem_01146 */
                WarmUpCycleCounterForMI++;
            }
            else
            {
                WarmUpCycleCounterForMI = 0u;
                ContinuousMICounter = 0u;
            }
        }
        break;
    case DEM_OPCYC_TIME:
        if (OBDMilStatus != DEM_INDICATOR_OFF)
        {
            if (CycleCounterForMI > 3u)
            {
                /* SWS_Dem_01145 SWS_Dem_01144 */
                ContinuousMICounter = 0u;
            }
            if (ContinuousMICounter < 0xFFu)
            {
                /* SWS_Dem_01147 SWS_Dem_01142 */
                ContinuousMICounter++;
            }
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
            if (MasterContinuousMICounter < 0xFFu)
            {
                /* SWS_Dem_01151 SWS_Dem_01152 */
                MasterContinuousMICounter++;
            }
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
            WarmUpCycleCounterForMI = 0u;
            TimeCycleCounterForMI = 0u;
            CycleCounterForMI = 0u;
        }
        else
        {
            if (TimeCycleCounterForMI < 200u)
            {
                /* SWS_Dem_01146 */
                TimeCycleCounterForMI++;
            }
            else
            {
                TimeCycleCounterForMI = 0u;
                ContinuousMICounter = 0u;
            }
        }
        Dem_B1CounterProcess();
        break;
    default:
        /*idle*/
        break;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_RATIO_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Get the IUMPR calculated data.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/*SWS_Dem_01104  IUMPR ratios referring to an unavailable event shall neither be
computed nor reported.*/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CalIUMPRValue(Dem_RatioIdType Dem_RatioId)
{
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
    const DemRatioType* pRatio = &DemRatio[Dem_RatioId];
    boolean permission = TRUE;
    uint8 FimFunctionId = pRatio->DemFunctionIdRef;
    FiM_GetFunctionPermission(FimFunctionId, &permission);
    /*Consider the integration with the FIM*/
    if (permission == TRUE)
    {
        const DemSecondaryFunctionIdType* pSecondaryFIdRef = pRatio->DemSecondaryFunctionIdRef;
        if (pSecondaryFIdRef != NULL_PTR)
        {
            const uint8* FimFunctionIdIndex = pSecondaryFIdRef->DemSecondaryFunctionIdRef;
            uint8 RefNum = pSecondaryFIdRef->DemSecondaryFunctionIdRefNum;
            for (uint16 iloop = 0; iloop < RefNum; iloop++)
            {
                FiM_GetFunctionPermission(*(FimFunctionIdIndex), &permission);
                /*Consider the integration with the FIM*/
                if (permission == FALSE)
                {
                    break;
                }
                FimFunctionIdIndex++;
            }
        }
    }
    /*Numerator and Denominator both are forbidden*/
    if (permission == FALSE)
#endif /* DEM_TRIGGER_FIM_REPORTS == STD_ON */
    {
        Dem_CalIUMPRDenValue(Dem_RatioId);
#if ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU)) /* SWS_Dem_00710 */
        Dem_CalIUMPRNumValue(Dem_RatioId);
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU */
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Get the IUMPR calculated Denominator data.
 * ServiceId           Internal Function>
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CalIUMPRDenValue(Dem_RatioIdType Dem_RatioId)
{
    /*get General Denominator*/
    uint8 Intid = DemRatio[Dem_RatioId].DemDiagnosticEventRef;
    const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(Intid);
    if (0u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
    {
        IUMPRType* pIUMPRValue = &IUMPRValue[Dem_RatioId];
        pIUMPRValue->General_Denominator++;
        /*get Specific Diagnostic Denominator*/
        /* SWS_Dem_00712 */
        if (pIUMPRValue->IUMPRDenStatus == TRUE)
        {
            if (pIUMPRValue->Denominator < 0xFFFFu)
            {
                pIUMPRValue->Denominator++;
            }
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#if ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU)) /* SWS_Dem_00710 */
/*************************************************************************/
/*
 * Brief               Get the IUMPR calculated Numerator data.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_CalIUMPRNumValue(Dem_RatioIdType Dem_RatioId)
{
    const DemRatioType* pRatio = &DemRatio[Dem_RatioId];
    uint8 IntId = pRatio->DemDiagnosticEventRef;
    const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
    IUMPRType* pIUMPRValue = &IUMPRValue[Dem_RatioId];
    if (pRatio->DemRatioKind == DEM_RATIO_OBSERVER) /* SWS_Dem_00359 SWS_Dem_00361 */
    {
        if (DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TFTOC) != 0x00u)
        {
            if (pIUMPRValue->Numerator < 0xFFFFu)
            {
                pIUMPRValue->Numerator++;
            }
        }
    }
    else
    {
        if (pIUMPRValue->IUMPRNumStatus == TRUE)
        {
            if (pIUMPRValue->Numerator < 0xFFFFu)
            {
                pIUMPRValue->Numerator++;
            }
            pIUMPRValue->IUMPRNumStatus = FALSE;
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU */
/*************************************************************************/
/*
 * Brief               Get the IUMPR Group Denomitor data.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(uint16, DEM_CODE) Dem_GetIUMPRDenValueByGroup(Dem_IUMPRGroupType Dem_IUMPRGroup)
{
    uint16 ret = 0;
    for (uint16 iloop = 0; iloop < DEM_RATIO_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        if (DemRatio[iloop].DemIUMPRGroup == Dem_IUMPRGroup)
        {
            ret = IUMPRValue[iloop].Denominator;
            break;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Get the IUMPR calculated Numerator data.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(uint16, DEM_CODE) Dem_GetIUMPRNumValueByGroup(Dem_IUMPRGroupType Dem_IUMPRGroup)
{
    uint16 ret = 0;
    for (uint16 iloop = 0; iloop < DEM_RATIO_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        if (DemRatio[iloop].DemIUMPRGroup == Dem_IUMPRGroup)
        {
            ret = IUMPRValue[iloop].Numerator;
            break;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_RATIO_NUM > 0u */

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/*************************************************************************/
/*
 * Brief               Service is used for requesting IUMPR data according to InfoType 08.
 * ServiceId           0x6b
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      OpStatus Only DCM_INITIAL will appear, because this API
                        behaves synchronous.
 * Param-Name[out]     Iumprdata08 Buffer containing the number of data elements (as
                        defined in ISO-15031-5) and contents of InfoType
                        08. The buffer is provided by the Dcm.
 * Param-Name[in/out]  Iumprdata08BufferSize: The maximum number of data bytes that can be
                        written to the Iumprdata08 Buffer.
 * Return              Always E_OK is returned.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetInfoTypeValue08(Dcm_OpStatusType OpStatus, uint8* Iumprdata08, uint8* Iumprdata08BufferSize)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETINFOTYPEVALUE08, DEM_E_UNINIT);
    }
    else if ((Iumprdata08BufferSize == NULL_PTR) || (Iumprdata08 == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_DCMGETINFOTYPEVALUE08, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        uint8 tempData[32] = {0};
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        tempData[0U] = (uint8)(IgnUpCycleCounter >> 8U);
        tempData[1U] = (uint8)(IgnUpCycleCounter);
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_RATIO_NUM > 0u)
        tempData[2U] = (uint8)(IUMPRValue[0U].General_Denominator >> 8U);
        tempData[3U] = (uint8)(IUMPRValue[0U].General_Denominator);

        tempData[4U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT1) >> 8U);
        tempData[5U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT1));
        tempData[6U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT1) >> 8U);
        tempData[7U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT1));

        tempData[8U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT2) >> 8U);
        tempData[9U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT2));
        tempData[10U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT2) >> 8U);
        tempData[11U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT2));

        tempData[12U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS1) >> 8U);
        tempData[13U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS1));
        tempData[14U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS1) >> 8U);
        tempData[15U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS1));

        tempData[16U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS2) >> 8U);
        tempData[17U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS2));
        tempData[18U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS2) >> 8U);
        tempData[19U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS2));

        tempData[20U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EGR) >> 8U);
        tempData[21U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EGR));
        tempData[22U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EGR) >> 8U);
        tempData[23U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EGR));

        tempData[24U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_SAIR) >> 8U);
        tempData[25U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_SAIR));
        tempData[26U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_SAIR) >> 8U);
        tempData[27U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_SAIR));

        tempData[28U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EVAP) >> 8U);
        tempData[29U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EVAP));
        tempData[30U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EVAP) >> 8U);
        tempData[31U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EVAP));
#endif /* DEM_RATIO_NUM > 0u */
        *Iumprdata08BufferSize = 32U;

        switch (OpStatus)
        {
        case 0x00u:
            Dem_MemCopy(Iumprdata08, tempData, 32U);
            break;
        case 0x01u:
        case 0x02u:
        case 0x03u:
            /*idle*/
            break;
        default:
            /*idle*/
            break;
        }
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service is used for requesting IUMPR data according to InfoType 0B.
 * ServiceId           0x6c
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      OpStatus Only DCM_INITIAL will appear, because this API
                        behaves synchronous.
 * Param-Name[out]     Iumprdata0B Buffer containing the number of data elements (as
                        defined in ISO-15031-5) and contents of InfoType
                        08. The buffer is provided by the Dcm.
 * Param-Name[in/out]  Iumprdata0BBufferSize: The maximum number of data bytes that can be
                        written to the Iumprdata08 Buffer.
 * Return              Always E_OK is returned.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetInfoTypeValue0B(Dcm_OpStatusType OpStatus, uint8* Iumprdata0B, uint8* Iumprdata0BBufferSize)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETINFOTYPEVALUE0B, DEM_E_UNINIT);
    }
    else if ((Iumprdata0BBufferSize == NULL_PTR) || (Iumprdata0B == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_DCMGETINFOTYPEVALUE0B, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        uint8 tempData[32] = {0};
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        tempData[0U] = (uint8)(IgnUpCycleCounter >> 8U);
        tempData[1U] = (uint8)(IgnUpCycleCounter);
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_RATIO_NUM > 0u)
        tempData[2U] = (uint8)(IUMPRValue[0].General_Denominator >> 8U);
        tempData[3U] = (uint8)(IUMPRValue[0].General_Denominator);

        tempData[4U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT1) >> 8U);
        tempData[5U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT1));
        tempData[6U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT1) >> 8U);
        tempData[7U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT1));

        tempData[8U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT2) >> 8U);
        tempData[9U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_CAT2));
        tempData[10U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT2) >> 8U);
        tempData[11U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_CAT2));

        tempData[12U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS1) >> 8U);
        tempData[13U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS1));
        tempData[14U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS1) >> 8U);
        tempData[15U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS1));

        tempData[16U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS2) >> 8U);
        tempData[17U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_OXS2));
        tempData[18U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS2) >> 8U);
        tempData[19U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_OXS2));

        tempData[20U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EGR) >> 8U);
        tempData[21U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EGR));
        tempData[22U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EGR) >> 8U);
        tempData[23U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EGR));

        tempData[24U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_SAIR) >> 8U);
        tempData[25U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_SAIR));
        tempData[26U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_SAIR) >> 8U);
        tempData[27U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_SAIR));

        tempData[28U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EVAP) >> 8U);
        tempData[29U] = (uint8)(Dem_GetIUMPRNumValueByGroup(DEM_IUMPR_EVAP));
        tempData[30U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EVAP) >> 8U);
        tempData[31U] = (uint8)(Dem_GetIUMPRDenValueByGroup(DEM_IUMPR_EVAP));
#endif /* DEM_RATIO_NUM > 0u */
        *Iumprdata0BBufferSize = 32U;

        switch (OpStatus)
        {
        case 0x00u:
            Dem_MemCopy(Iumprdata0B, tempData, 32U);
            break;
        case 0x01u:
        case 0x02u:
        case 0x03u:
            /*idle*/
            break;
        default:
            /*idle*/
            break;
        }
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Reports the value of a requested "availability-OBDMID" to the DCM upon a Service 06 request.
 * ServiceId           0xa3
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Obdmid Availablity OBDMID (00,20, 40...)
 * Param-Name[out]     Obdmidvalue Bit coded information on the support of OBDMIDs.
 * Param-Name[in/out]  None
 * Return              E_OK: Report of DTR result successful
                        E_NOT_OK: Report of DTR result failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetAvailableOBDMIDs(uint8 Obdmid, uint32* Obdmidvalue)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETAVAILABLEOBDMIDS, DEM_E_UNINIT);
    }
    else if (Obdmidvalue == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETAVAILABLEOBDMIDS, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_DTR_NUM > 0u)
        const DTRType* pDTR = DemPbCfgPtr->DTR;
        boolean Find = FALSE;
        *Obdmidvalue = 0;
        for (uint16 iloop = 0; iloop < DEM_DTR_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
        {
            uint8 DemDtrMid = pDTR->DemDtrMid;
            if ((DemDtrMid >= (Obdmid + 0x01u)) && (DemDtrMid <= (Obdmid + 0x20u)))
            {
                *Obdmidvalue |= (uint32)1u << (0x20u - (DemDtrMid - Obdmid)); /*SWS_Dem_00760] */
            }
            if ((DemDtrMid == Obdmid) || (Obdmid == 0x0u))
            {
                Find = TRUE;
            }
            pDTR++;
        }
        if (Find == FALSE)
        {
            *Obdmidvalue = 0;
        }
#else
        *Obdmidvalue = 0;
        DEM_UNUSED(Obdmid);
#endif /* DEM_DTR_NUM > 0u */
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the number of TIDs per (functional) OBDMID.
 * ServiceId           0xa4
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Obdmid OBDMID subject of the request to identify the number of assigned TIDs
 * Param-Name[out]     numberOfTIDs Number of assigned TIDs for the requested OBDMID.
 *                      Used as loop value for the DCM to retrieve all OBD/TID result data
 * Param-Name[in/out]  None
 * Return              E_OK: get number of TIDs successful
                        E_NOT_OK: get number of TIDs failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetNumTIDsOfOBDMID(uint8 Obdmid, uint8* numberOfTIDs)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETNUMTIDSOFOBDMID, DEM_E_UNINIT);
    }
    else if (numberOfTIDs == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETNUMTIDSOFOBDMID, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_DTR_NUM > 0u)
        const DTRType* pDTR = DemPbCfgPtr->DTR;
        *numberOfTIDs = 0u;
        for (uint16 iloop = 0; iloop < DEM_DTR_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
        {
            if (pDTR->DemDtrMid == Obdmid)
            {
                *numberOfTIDs += 1u; /* SWS_Dem_00761 */
            }
            pDTR++;
        }
#else
        *numberOfTIDs = 0u;
        DEM_UNUSED(Obdmid);
#endif /* DEM_DTR_NUM > 0u */
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to report the value of PID 01 computed by the Dem.
 * ServiceId           None
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 01 computed by the Dem.
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
DEM_LOCAL void Dem_DataOfPID01(uint8* PID01value)
{
    uint8 OBDDTCNum = 0;
    uint8 supportedGroups[2] = {0, 0};
    uint8 notCompletedGroups[2] = {0, 0};
    const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
    const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
    /* Byte A */
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        if (pEventCfg->DemEventAvailable == TRUE) /* SWS_Dem_01103 */
        {
            uint16 DTCRef = pEventCfg->DemDTCRef;
            /* SWS_Dem_01101 */
            if ((DTCRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[DTCRef].SuppressionStatus != TRUE))
            {
                uint32 DemDtcValue = pDTC[DTCRef].DemDtcValue;
                /* 0xFFFF33uL <= WWH-OBD <= 0xFFFFFFuL */
                uint16 ObdDTCRef = DemPbCfgPtr->DemDTC[DTCRef].DemObdDTCRef;
                if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                    && (((DemDtcValue < 0xFFFF33UL) && (DemDtcValue > 0UL))
                        || (pObdDTC[ObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID)))
                {
                    /* SWS_Dem_01137 */
                    /* confirmedDTC 0x08 */
                    if ((OBDDTCNum < 0x7Fu)
                        && (0x00U != DEM_FLAGS_ISSET(DemEventRelateInformation[iloop].UdsStatus, DEM_UDS_STATUS_CDTC)))
                    {
                        /* ConfirmedDtcNum : Byte A, bit 0-6 */
                        /* number of OBD confirmed faults SWS_Dem_00351 */
                        OBDDTCNum++;
                    }
                }
            }
        }
        pEventCfg++;
    }
    /* SWS_Dem_00351 */
    PID01value[0] = OBDDTCNum;
    if (OBDMilStatus != DEM_INDICATOR_OFF)
    {
        /* MIL status : Byte A, bit 7 */
        /* SWS_Dem_01138 */
        PID01value[0] |= (uint8)0x80U;
    }
    /* Byte B, C, D*/
    for (uint8 Index = 0; Index < DEM_NUMBER_OF_READINESS_GROUPS_FOROBD; Index++)
    {
        pEventCfg = DemPbCfgPtr->DemEventParameter;
        /* SWS_Dem_00354 */
        for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
        {
            /* SWS_Dem_01103 */
            if (pEventCfg->DemEventAvailable == TRUE)
            {
                uint16 DTCRef = pEventCfg->DemDTCRef;
                /* SWS_Dem_01101 */
                if ((DTCRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[DTCRef].SuppressionStatus == FALSE))
                {
                    uint16 ObdDTCRef = DemPbCfgPtr->DemDTC[DTCRef].DemObdDTCRef;
                    if ((ObdDTCRef != DEM_OBD_DTC_INVALID) && (pObdDTC[ObdDTCRef].DemEventOBDReadinessGroup == Index))
                    {
                        uint16 DemDtcValue = pObdDTC[ObdDTCRef].DemDtcValue;
                        if ((DemDtcValue != 0xFFFFU) && (DemDtcValue != 0u))
                        {
                            const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
                            uint8 UdsStatus = pEvent->UdsStatus;
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
            pEventCfg++;
        }
    }
    PID01value[1] = ((supportedGroups[0u] & 0xFu) | (uint8)((notCompletedGroups[0u] & 0xFu) << 4u));
    PID01value[2] = ((uint8)((supportedGroups[0u] & 0xF0u) >> 4u) | (uint8)((supportedGroups[1u] & 0xFu) << 4u));
    PID01value[3] = ((uint8)((notCompletedGroups[0u] & 0xF0u) >> 4u) | (uint8)((notCompletedGroups[1u] & 0xFu) << 4u));
}
/*************************************************************************/
/*
 * Brief               Service to report the value of PID 01 computed by the Dem.
 * ServiceId           0x61
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 01 computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID01(uint8* PID01value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID01, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID01value)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID01, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_DataOfPID01(PID01value);
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to report the value of PID 1C computed by the Dem.
 * ServiceId           0x63
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 1C computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/*OBD requirements to which vehicle is designed*/
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID1C(uint8* PID1Cvalue)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID1C, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID1Cvalue)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID1C, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00748 */
        PID1Cvalue[0] = DemGeneralOBD.DemOBDCompliancy;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to report the value of PID 21 computed by the Dem.
 * ServiceId           0x64
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 21 computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID21(uint8* PID21value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID21, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID21value)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID21, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00704 */
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
        if (SetDataOfPid21 == TRUE)
        {
            uint16 DistWithMilOn = 0U;
            /* MIL deactivated */
            /* the indicator is on */
            if (DEM_INDICATOR_OFF != OBDMilStatus)
            {
                uint16 currentDistanceInformation = Dem_ReadDistanceInformation();
                if (currentDistanceInformation > OBDDistanceMILLastOn)
                {
                    DistWithMilOn = currentDistanceInformation - OBDDistanceMILLastOn;
                    OBDDistanceMILLastOn = currentDistanceInformation;
                }
            }
            if (OBDDistanceMILOn < (0xFFFFu - DistWithMilOn))
            {
                OBDDistanceMILOn += DistWithMilOn;
            }
            else
            {
                OBDDistanceMILOn = 0xFFFFu;
            }
            PID21value[0] = (uint8)OBDDistanceMILOn;
            PID21value[1] = (uint8)(OBDDistanceMILOn >> 8u);
        }
        else
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
        {
            /* SWS_Dem_01099 */
            PID21value[0] = 0xFFu;
            PID21value[1] = 0xFFu;
        }
        SetDataOfPid21 = FALSE;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Service to report the value of PID30 computed by the Dem.
 * ServiceId           0x65
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 30 computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID30(uint8* PID30value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID30, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID30value)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID30, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        *PID30value = WarmUpCycleCounter;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Service to report the value of PID 31 computed by the Dem.
 * ServiceId           0x66
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 31 computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID31(uint8* PID31value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID31, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID31value)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID31, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) /*SWS_Dem_00704]*/
        /* Read current distance information */
        uint16 currentDistanceInformation = Dem_ReadDistanceInformation();
        if (currentDistanceInformation > OBDDistanceDTCClear)
        {
            DistSinceDtcCleared = currentDistanceInformation - OBDDistanceDTCClear;
        }
        PID31value[0] = (uint8)DistSinceDtcCleared;
        PID31value[1] = (uint8)(DistSinceDtcCleared >> 8u);
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Service to report the value of PID 41 computed by the Dem.
 * ServiceId           0x67
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 41 computed by the Dem.>
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID41(uint8* PID41value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID41, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID41value)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID41, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
        const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;

        uint8 enabledGroups[2] = {0xffu, 0x07u};
        uint8 notCompletedGroups[2] = {0, 0};
        Dem_MemSet(PID41value, 0u, (uint8)4U);

        for (uint8 Index = 0; Index < DEM_NUMBER_OF_READINESS_GROUPS_FOROBD; Index++)
        {
            const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
            for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
            {
                /* SWS_Dem_01103 */
                if (pEventCfg->DemEventAvailable == TRUE)
                {
                    uint16 DTCRef = pEventCfg->DemDTCRef;
                    /* SWS_Dem_01101 */
                    if ((DTCRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[DTCRef].SuppressionStatus != TRUE))
                    {
                        uint16 ObdDTCRef = pDTC[DTCRef].DemObdDTCRef;
                        if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                            && (pObdDTC[ObdDTCRef].DemEventOBDReadinessGroup == Index))
                        {
                            /* Only include emission related DTCs */
                            uint16 DemDtcValue = pObdDTC[ObdDTCRef].DemDtcValue;
                            if ((DemDtcValue != 0xFFFFU) && (DemDtcValue != 0u))
                            {
                                const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
                                uint8 OperationCycleRef = pEventCfg->DemOperationCycleRef;
                                if ((DEM_BITS_ISSET(DemOperationCycleStatus, OperationCycleRef))
                                    && (DemOperationCycle[OperationCycleRef].DemOperationCycleType == DEM_OPCYC_POWER))
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
                pEventCfg++;
            }
        }
        PID41value[0] = 0x00;
        PID41value[1] = ((enabledGroups[0] & 0xFu) | (uint8)((notCompletedGroups[0u] & 0xFu) << 4u));
        PID41value[2] = ((uint8)((enabledGroups[0u] & 0xF0u) >> 4u) | (uint8)((enabledGroups[1u] & 0xFu) << 4u));
        PID41value[3] =
            ((uint8)((notCompletedGroups[0u] & 0xF0u) >> 4u) | (uint8)((notCompletedGroups[1u] & 0xFu) << 4u));
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Service to report the value of PID 4D computed by the Dem.
 * ServiceId           0x68
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Buffer containing the contents of PID 4D computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4D(uint8* PID4Dvalue)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID4D, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID4Dvalue)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID4D, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00704 */
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
        uint16 TimeWithMilOn = 0U;
        /* MIL deactivated */
        /* the indicator is on */
        if (DEM_INDICATOR_OFF != OBDMilStatus)
        {
            uint16 CurrentTimeInformation = Dem_ReadTimeInformation();
            if (CurrentTimeInformation > OBDTimeMILLastOn)
            {
                TimeWithMilOn = CurrentTimeInformation - OBDTimeMILLastOn;
                OBDTimeMILLastOn = CurrentTimeInformation;
            }
        }
        if (OBDTimeMILOn < (0xFFFFu - TimeWithMilOn))
        {
            OBDTimeMILOn += TimeWithMilOn;
        }
        else
        {
            OBDTimeMILOn = 0xFFFFu;
        }
        PID4Dvalue[0] = (uint8)OBDTimeMILOn;
        PID4Dvalue[1] = (uint8)(OBDTimeMILOn >> 8u);
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Service to report the value of PID 4E computed by the Dem.
 * ServiceId           0x69
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID4Evalue Buffer containing the contents of PID 4E
                        computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4E(uint8* PID4Evalue)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID4E, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID4Evalue)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID4E, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) /*SWS_Dem_00704]*/
        /* MIL still activated */
        uint16 CurrentTimeInformation = Dem_ReadTimeInformation();
        if (CurrentTimeInformation > OBDTimeDTCLastClear)
        {
            OBDTimeDTCClear = CurrentTimeInformation - OBDTimeDTCLastClear;
        }
        PID4Evalue[0] = (uint8)OBDTimeDTCClear;
        PID4Evalue[1] = (uint8)(OBDTimeDTCClear >> 8u);
        ret = E_OK;
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to report the value of PID 91 computed by the Dem.
 * ServiceId           0x6a
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID91value Buffer containing the contents of PID 91
                        computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID91(uint8* PID91value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID91, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID91value)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATDOFPID91, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
        /*TODO: ECU OBD System Information (5 byte)*/
        ret = DemReadPID91(PID91value);
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets data element per PID and index of the most important freeze frame
                        being selected for the output of service 02. The function stores the data
                        in the provided DestBuffer.
 * ServiceId           0x52
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      PID: This parameter is an identifier for a PID as defined
                        in ISO15031-5.
                        DataElementIndexOfPID: Data element index of this PID according
                        to the Dcm configuration of service 02. It is zero-based and
                        consecutive, and ordered by the data element  positions
                        (configured in Dcm, refer to SWS_Dem_00597).>
 * Param-Name[out]     None
 * Param-Name[in/out]  DestBuffer: This parameter contains a byte pointer that points to
                        the buffer, to which the data element of the PID shall
                        be written to. The format is raw hexadecimal values
                        and contains no header-information.
                        BufSize: When the function is called this parameter contains
                        the maximum number of data bytes that can be written
                        to the buffer.
                        The function returns the actual number of written
                        data bytes in this parameter.
 * Return              E_OK Freeze frame data was successfully reported
                        E_NOT_OK Freeze frame data was not successfully reported
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 1532++ */ /* MISRA Rule 8.7 */
Dem_DcmReadDataOfOBDFreezeFrame(uint8 PID, uint8 DataElementIndexOfPID, uint8* DestBuffer, uint16* BufSize)
/* PRQA S 1532-- */ /* MISRA Rule 8.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATAOFOBDFREEZEFRAME, DEM_E_UNINIT);
    }
    else if ((DestBuffer == NULL_PTR) || (BufSize == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_DCMREADDATAOFOBDFREEZEFRAME, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_PID_CLASS_NUM > 0u)
        uint16 IntID = 0;
        const Dem_EventMemEntryType* pEntry = Dem_SelectOBDFreezeFrame(&IntID);
        if (pEntry != NULL_PTR)
        {
            uint16 DTCRef = DemPbCfgPtr->DemEventParameter[IntID].DemDTCRef;
            if ((DTCRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[DTCRef].SuppressionStatus == FALSE))
            {
                const Dem_DTCType* pDTC = &DemPbCfgPtr->DemDTC[DTCRef];
                uint16 ObdDTCRef = pDTC->DemObdDTCRef;
                const Dem_DTCAttributesType* pDTCAttr = &DemPbCfgPtr->DemDTCAttributes[pDTC->DemDTCAttributesRef];
                if (((ObdDTCRef != DEM_OBD_DTC_INVALID)
                     && ((DemPbCfgPtr->DemObdDTC[ObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID)))
                    && (pDTCAttr->DemFreezeFrameClassRef == DEM_FREEZE_FRAME_INVALID)
                    && (pDTCAttr->DemWWHOBDFreezeFrameClassRef == DEM_WWHOBD_FREEZE_FRAME_INVALID)
                    && (pDTCAttr->DemJ1939FreezeFrameClassRef == DEM_J1939_FREEZE_FRAME_INVALID)
                    && (pDTCAttr->DemJ1939ExpandedFreezeFrameClassRef == DEM_J1939_FREEZE_FRAME_INVALID))
                {
                    const uint8* pBuffer = &(pEntry->FFList[0]).Data[0];
                    const Dem_PidClassType* pPid = DemPbCfgPtr->DemPidClass;
                    uint16 Offset = 0;
                    for (uint8 iloop = 0; (iloop < DEM_PID_CLASS_NUM) && (ret == E_NOT_OK); iloop++)
                    {
                        if (PID == pPid->DemPidIdentifier)
                        {
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
                            uint8 RefNum = pPid->RefNum;
                            for (uint8 Index = 0; (Index < RefNum) && (ret == E_NOT_OK); Index++)
                            {
                                uint8 DataSize = DemDataElementClass[pPid->StartIndex + Index].DemDataElementDataSize;
                                if (DataElementIndexOfPID == (pPid->StartIndex + Index))
                                {
                                    Dem_MemCopy(DestBuffer, &pBuffer[Offset], DataSize);
                                    *BufSize = DataSize;
                                    ret = E_OK;
                                }
                                Offset += DataSize;
                            }
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
                        }
                        Offset += pPid->DataSize;
                        pPid++;
                    }
                }
            }
        }
#endif /* DEM_PID_CLASS_NUM > 0u */
    }
    return ret;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Gets DTC by freeze frame record number.
 * ServiceId           0x53
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      FrameNumber: Unique identifier for a freeze frame
                        record as defined in ISO 15031-5. The value 0x00
                        indicates the complete OBD freeze frame. Other values
                        are reserved for future functionality.
                        DTCFormat: Output format of the DTC value.
 * Param-Name[out]     DTC Diagnostic Trouble Code in ODB format. If the return
                        value of the function is other than E_OK this
                        parameter does not contain valid data.
 * Param-Name[in/out]  None
 * Return              E_OK: operation was successful E_NOT_OK: no DTC available
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 1532++ */ /* MISRA Rule 8.7 */
Dem_DcmGetDTCOfOBDFreezeFrame(uint8 FrameNumber, uint32* DTC, Dem_DTCFormatType DTCFormat)
/* PRQA S 1532-- */ /* MISRA Rule 8.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETDTCOFOBDFREEZEFRAME, DEM_E_UNINIT);
    }
    else if (DTC == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETDTCOFOBDFREEZEFRAME, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* Only record number 0 is supported, SWS_Dem_00291 */
        if ((0u == FrameNumber) && (DEM_DTC_FORMAT_OBD == DTCFormat))
        {
            Dem_EventIdType IntId = 0;
            *DTC = 0;
            /* SWS_Dem_01172 SWS_Dem_01173 */
            if (Dem_SelectOBDFreezeFrame(&IntId) != NULL_PTR)
            {
                const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
                uint16 DTCRef = pEventCfg->DemDTCRef;
                /* OBD Freeze frame stored, return DTC that caused storage */
                /* SWS_Dem_01101 */
                if ((DTCRef != DEM_DTC_REF_INVALID) && (DemDTCGeneralStatus[DTCRef].SuppressionStatus == FALSE))
                {
                    uint16 ObdDTCRef = DemPbCfgPtr->DemDTC[DTCRef].DemObdDTCRef;
                    if (DEM_OBD_DTC_INVALID != ObdDTCRef)
                    {
                        *DTC = (uint32)DemPbCfgPtr->DemObdDTC[ObdDTCRef].DemDtcValue;
                        ret = E_OK;
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
 * Brief               Reports a DTR data along with TID-value, UaSID, test result with lower and upper limit.
 * ServiceId           0xa5
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Obdmid: Identification of a DTR element by assigned DTRId.
                        TIDindex: Index of the TID within the DEM. Runs from 0
                        to "numberOfTIDs" obtained in the call to Dem_
                        DcmGetNumTIDsOfOBDMID()
 * Param-Name[out]     TIDvalue: TID to be put on the tester reponse
                        UaSID: UaSID to be put on the tester reponse
                        Testvalue:Latest test result
                        Lowlimvalue:Lower limit value associated to the latest test result
                        Upplimvalue:Upper limit value associated to the latest test result
 * Param-Name[in/out]  None
 * Return              E_OK: Report of DTR result successful
                        E_NOT_OK: Report of DTR result failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTRData(
    uint8 Obdmid,
    uint8 TIDindex,
    uint8* TIDvalue,
    uint8* UaSID,
    uint16* Testvalue,
    uint16* Lowlimvalue,
    uint16* Upplimvalue)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETDTCOFOBDFREEZEFRAME, DEM_E_UNINIT);
    }
    else if (
        (TIDvalue == NULL_PTR) || (UaSID == NULL_PTR) || (Testvalue == NULL_PTR) || (Lowlimvalue == NULL_PTR)
        || (Upplimvalue == NULL_PTR))
    {
        DEM_DET_REPORT(DEM_SID_DCMGETDTCOFOBDFREEZEFRAME, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_DTR_NUM > 0u)
        const DTRType* pDTR = DemPbCfgPtr->DTR;
        const DTRInfoType* pDTRInfo = DTRInfo;
        for (uint16 iloop = 0; iloop < DEM_DTR_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
        {
            if ((Obdmid == pDTR->DemDtrMid) && (TIDindex == iloop))
            { /*SWS_Dem_00762]*/
                *TIDvalue = pDTR->DemDtrTid;
                *UaSID = pDTR->DemDtrUasid;
                *Lowlimvalue = (uint16)pDTRInfo->LowerLimit;
                *Testvalue = (uint16)pDTRInfo->TestResult;
                *Upplimvalue = (uint16)pDTRInfo->UpperLimit;
            }
            pDTR++;
            pDTRInfo++;
        }
        ret = E_OK;
#else
        DEM_UNUSED(Obdmid);
        DEM_UNUSED(TIDindex);
#endif /* DEM_DTR_NUM > 0u */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service for reporting the event as disabled to the
                        Dem for the PID 41 computation.
 * ServiceId           0x51
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different EventIds. Non reentrant for the same EventId.
 * Param-Name[in]      Identification of an event by assigned EventId.>
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK set of event to disabled was successfull.
                         E_NOT_OK set of event disabled failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventDisabled(Dem_EventIdType EventId)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETEVENTDISABLED, DEM_E_UNINIT);
    }
    else if (EventId >= DEM_EVENT_PARAMETER_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETEVENTDISABLED, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00294 */
        DEM_FLAGS_CLR(
            DemEventRelateInformation[Dem_GetEventInternalId(EventId)].Status,
            DEM_EVENT_STATUS_ENABLED_CONDICTION);
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service for reporting that faults are possibly found
                        because all conditions are fullfilled.
 * ServiceId           0x73
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      Ratio Identifier reporting that a respective monitor
                        could have found a fault
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK report of IUMPR result was successfully reported
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRFaultDetect(Dem_RatioIdType RatioID)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_REPIUMPRFAULTDETECT, DEM_E_UNINIT);
    }
    else if (RatioID > DEM_RATIO_NUM)
    {
        DEM_DET_REPORT(DEM_SID_REPIUMPRFAULTDETECT, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_RATIO_NUM > 0u)
        if (DemRatio[RatioID].DemRatioKind == DEM_RATIO_API)
        {
            /* malfunction could have been found. */
            IUMPRValue[RatioID].IUMPRNumStatus = TRUE;
        }
        ret = E_OK;
#endif /* DEM_RATIO_NUM > 0u */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               In order to communicate the status of the (additional) denominator
                        conditions among the OBD relevant ECUs, the API is used to forward
                        the condition status to a Dem of a particular ECU
 * ServiceId           0xae
 * Sync/Async          Synchronous /Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ConditionId: Identification of a IUMPR denominator condition ID
                        ConditionStatus:Status of the IUMPR denominator condition
                        (Notreached, reached, not reachable / inhibited)
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: set of IUMPR denominator condition was successful
                        E_NOT_OK: set of IUMPR denominator condition
                        failed or could not be accepted.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRDenCondition(Dem_IumprDenomCondIdType ConditionId, Dem_IumprDenomCondStatusType ConditionStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETIUMPRDENCONDITION, DEM_E_UNINIT);
    }
    else if (ConditionId >= 5u)
    {
        DEM_DET_REPORT(DEM_SID_SETIUMPRDENCONDITION, DEM_E_PARAM_DATA);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00714 */
        ConditionStatu[ConditionId] = ConditionStatus;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               In order to communicate the status of the (additional) denominator
                        conditions among the OBD relevant ECUs, the API is used to retrieve
                        the condition status from the Dem of the ECU where the conditions are
                        computed.
 * ServiceId           0xaf
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ConditionId: Identification of a IUMPR denominator condition ID
 * Param-Name[out]     ConditionStatus:Status of the IUMPR denominator condition
 *                      (Notreached, reached, not reachable / inhibited)
 * Param-Name[in/out]  None
 * Return              E_OK: get of IUMPR denominator condition status was successful
                        E_NOT_OK: get of condition status failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIUMPRDenCondition(Dem_IumprDenomCondIdType ConditionId, Dem_IumprDenomCondStatusType* ConditionStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_GETIUMPRDENCONDITION, DEM_E_UNINIT);
    }
    else if (ConditionId >= 5u)
    {
        DEM_DET_REPORT(DEM_SID_GETIUMPRDENCONDITION, DEM_E_PARAM_DATA);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00966 */
        *ConditionStatus = ConditionStatu[ConditionId];
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service is used to lock a denominator of a specific monitor.
 * ServiceId           0x71
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Ratio Identifier reporting that specific denominator
                        is locked
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK report of IUMPR denominator status was successfully reported
                        E_NOK report of IUMPR denominator status was
                        not successfully reported
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenLock(Dem_RatioIdType RatioID)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_REPIUMPRDENLOCK, DEM_E_UNINIT);
    }
    else if (RatioID > DEM_RATIO_NUM)
    {
        DEM_DET_REPORT(DEM_SID_REPIUMPRDENLOCK, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_RATIO_NUM > 0u)
        /* SWS_Dem_00362 */
        if (DEM_IUMPR_DEN_PHYS_API == DemRatio[RatioID].DemIUMPRDenGroup)
        {
            IUMPRValue[RatioID].IUMPRDenStatus = FALSE;
        }
        ret = E_OK;
#endif /* DEM_RATIO_NUM > 0u */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service is used to release a denominator of a
                        specific monitor.
 * ServiceId           0x72
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Ratio Identifier reporting that specific denominator
                        is released
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK report of IUMPR denominator status was successfully reported
                        E_NOK report of IUMPR denominator status was
                        not successfully reported
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenRelease(Dem_RatioIdType RatioID)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_REPIUMPRDENRELEASE, DEM_E_UNINIT);
    }
    else if (RatioID > DEM_RATIO_NUM)
    {
        DEM_DET_REPORT(DEM_SID_REPIUMPRDENRELEASE, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_RATIO_NUM > 0u)
        /* SWS_Dem_00362 */
        if (DEM_IUMPR_DEN_PHYS_API == DemRatio[RatioID].DemIUMPRDenGroup)
        {
            IUMPRValue[RatioID].IUMPRDenStatus = TRUE;
        }
        ret = E_OK;
#endif /* DEM_RATIO_NUM > 0u */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_PTO_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Set the status of the PTO.
 * ServiceId           0x79
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      PtoStatus sets the status of the PTO
                        TRUE:active    FALSE:inactive
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType Returns E_OK when the new PTO-status has been
                        adopted by the Dem; returns E_NOT_OK in all other cases.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetPtoStatus(boolean PtoStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETPTOSTATUS, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        CurrentPTOStatus = PtoStatus;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_PTO_SUPPORT == STD_ON */
/*************************************************************************/
/*
 * Brief               Service to report the value of PID 01 computed by the Dem.
 * ServiceId           0xb3
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID01value:Buffer containing the contents of PID 01 computed by the Dem.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfPID01(uint8* PID01value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_READDATAOFPID01, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID01value)
    {
        DEM_DET_REPORT(DEM_SID_READDATAOFPID01, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_DataOfPID01(PID01value);
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to set the value of PID 21 in the Dem by a software component.
 * ServiceId           0xa6
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      PID21value:Buffer containing the contents of PID 21.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID21(uint8* PID21value) /* PRQA S 3673 */ /* MISRA Rule 8.13 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_GETDATAOFPID21, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID21value)
    {
        DEM_DET_REPORT(DEM_SID_GETDATAOFPID21, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        OBDDistanceMILOn = (uint16)PID21value[0u] | (uint16)((uint16)PID21value[1u] << 8u);
        SetDataOfPid21 = TRUE;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to set the value of PID 31 in the Dem by a software component
 * ServiceId           0xa7
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID31value:Buffer containing the contents of PID 31.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID31(uint8* PID31value) /* PRQA S 3673 */ /* MISRA Rule 8.13 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETDATAOFPID31, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID31value)
    {
        DEM_DET_REPORT(DEM_SID_SETDATAOFPID31, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        DistSinceDtcCleared = (uint16)PID31value[0] | (uint16)((uint16)PID31value[1] << 8u);
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to set the value of PID 4D in the Dem by a software component.
 * ServiceId           0xa8
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID4Dvalue:Buffer containing the contents of PID 4D.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID4D(uint8* PID4Dvalue) /* PRQA S 3673 */ /* MISRA Rule 8.13 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETDATAOFPID4D, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID4Dvalue)
    {
        DEM_DET_REPORT(DEM_SID_SETDATAOFPID4D, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        OBDTimeMILOn = (uint16)PID4Dvalue[0u] | (uint16)((uint16)PID4Dvalue[1u] << 8u);
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service to set the value of PID 4E in the Dem by a software component.
 * ServiceId           0xa9
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID4Evalue:Buffer containing the contents of PID 4E.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID4E(uint8* PID4Evalue) /* PRQA S 3673 */ /* MISRA Rule 8.13 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETDATAOFPID4E, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID4Evalue)
    {
        DEM_DET_REPORT(DEM_SID_SETDATAOFPID4E, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        OBDTimeDTCClear = (uint16)PID4Evalue[0u] | (uint16)((uint16)PID4Evalue[1u] << 8u);
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Marks the current OBD driving cycle as having met the criteria for the PFC cycle.
 * ServiceId           0xaa
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetPfcCycleQualified(void)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETPFCCYCLEQUALIFIED, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const Dem_OperationCycleType* pDemOperationCycle = DemOperationCycle;
        PFCStatu = FALSE;
        for (uint8 iloop = 0; iloop < DEM_OPERATION_CYCLE_NUM; iloop++)
        {
            if (pDemOperationCycle->DemOperationCycleType == DEM_OPCYC_OBD_DCY)
            {
                PFCStatu = TRUE;
            }
            pDemOperationCycle++;
        }
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Returns TRUE if the criteria for the PFC cycle have been met during the current OBD driving
 cycle.
 * ServiceId           0xab
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     isqualified:TRUE: During the current OBD driving cycle the criteria for the PFC cycle have been
 met. FALSE: During the current OBD driving cycle the criteria for the PFC cycle have not been met.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_GetPfcCycleQualified(boolean* isqualified)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)

    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_GETPFCCYCLEQUALIFIED, DEM_E_UNINIT);
    }
    else if (NULL_PTR == isqualified)
    {
        DEM_DET_REPORT(DEM_SID_GETPFCCYCLEQUALIFIED, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        if ((DEM_MALFUNCTION_LAMP_INDICATOR != DemIndicator_INVALID)
            && (DemWIRStatus[DEM_MALFUNCTION_LAMP_INDICATOR] != DEM_INDICATOR_OFF))
        {
            const Dem_OperationCycleType* pDemOperationCycle = DemOperationCycle;
            for (uint8 iloop = 0; iloop < DEM_OPERATION_CYCLE_NUM; iloop++)
            {
                if ((DEM_BITS_ISSET(DemOperationCycleStatus, iloop))
                    && (pDemOperationCycle->DemOperationCycleType == DEM_OPCYC_OBD_DCY))
                {
                    PFCStatu = TRUE;
                }
                pDemOperationCycle++;
            }
        }
        *isqualified = PFCStatu;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               API to inform the Dem (of a Dependend / Secondary ECU) about the
                       reception of service 04 execution by a software component.
 * ServiceId           0xac
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      DTC:Defines the DTC in respective format, that has been
 *                     cleared from the event memory.
 *                       DTCFormat:Format of the provided DTC value.
 *                       DTCOrigin:Event memory (e.g. MIRROR)
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Return value unused - only for compatibility with according RTE operation.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Dem_ReturnClearDTCType, DEM_CODE)
Dem_SetClearDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    Dem_ReturnClearDTCType ret = DEM_CLEAR_FAILED;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETCLEARDTC, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        boolean ProcessOn = TRUE;
        Dem_ClearDTCInfoType* pClr = &DemClearDTCInfo;
        if (Dem_ClearDTCLock == DEM_CLEAR_LOCK)
        {
            ProcessOn = FALSE;
            /* SWS_Dem_00662 SWS_Dem_00664 */
            ret = DEM_CLEAR_BUSY;
            if ((pClr->SaveDTCIndex == Dem_GetDTCIndex(DTC, DTCFormat)) && (pClr->SaveDTCFormat == DTCFormat)
                && (pClr->SaveDTCOrigin == DTCOrigin) && (pClr->SID == DEM_SID_SETCLEARDTC))
            {
                /* SWS_Dem_00663 */
                ret = DEM_CLEAR_PENDING;
            }
        }
        else if (Dem_ClearDTCLock == DEM_CLEAR_NOT_LOCK)
        {
            /* SWS_Dem_00661 */
            Dem_ClearDTCLock = DEM_CLEAR_LOCK;
            pClr->DTCIndex = Dem_GetDTCIndex(DTC, DTCFormat);
            pClr->DTCFormat = DTCFormat;
            pClr->DTCOrigin = DTCOrigin;
            pClr->SaveDTCIndex = Dem_GetDTCIndex(DTC, DTCFormat);
            pClr->SaveDTCFormat = DTCFormat;
            pClr->SaveDTCOrigin = DTCOrigin;
            pClr->SID = DEM_SID_SETCLEARDTC;
        }
        else
        {
            /*idle*/
        }
        if (ProcessOn == TRUE)
        {
            /*SWS_Dem_00670] */
#if (DEM_CLEAR_DTCLIMITATION == DEM_ONLY_CLEAR_ALL_DTCS)
            if (DTCFormat != DEM_DTC_FORMAT_UDS || (DTC == DEM_DTC_GROUP_ALL_DTCS))
            {
                Dem_ResetDemClearDTCInfo();
                ret = DEM_CLEAR_WRONG_DTC;
            }
            else
#endif /* DEM_CLEAR_DTCLIMITATION == DEM_ONLY_CLEAR_ALL_DTCS */
            {
                Dem_DTCOriginType lDTCOrigin = Dem_GetInternalMemDest(DTCOrigin);
                if (lDTCOrigin == DEM_MEM_DEST_INVALID)
                {
                    Dem_ResetDemClearDTCInfo();
                    ret = DEM_CLEAR_WRONG_DTCORIGIN;
                }
                else
                {
                    /* SWS_Dem_00723 SWS_Dem_01179 */
                    if ((DTC == DEM_DTC_GROUP_ALL_DTCS) || (DTC == 0xFFFF33UL))
                    {
                        pClr->ClearAllGroup = TRUE;
                        pClr->memDest = lDTCOrigin;
                        Dem_Pending = TRUE;
                        Dem_ClearDTCProcess();
                        Dem_ResetDemClearDTCInfo();
                        ret = DEM_CLEAR_OK;
                    }
                    else
                    {
                        Dem_ResetDemClearDTCInfo();
                        ret = DEM_CLEAR_WRONG_DTC;
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
 * Brief              Reports a DTR result with lower and upper limit. The internal eventstatus
                        serves as master whether the DTR values are forwarded or ignored,
                        also taking the DTRUpdateKind into account.
 * ServiceId           0xa2
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DTRId:Identification of a DTR element by assigned DTRId
 *                      TestResult:Test result of DTR
 *                      LowerLimit:Lower limit of DTR
 *                      UpperLimit:Upper limit of DTR
 *                      Ctrlval:Control value of the DTR to support its interpretation Dem-internally.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: Report of DTR result successful
                        E_NOT_OK: Report of DTR result failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTR(uint16 DTRId, sint32 TestResult, sint32 LowerLimit, sint32 UpperLimit, Dem_DTRControlType Ctrlval)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_SETDTR, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_DTR_NUM > 0u)
        const Dem_EventRelateInformationType* pEvent =
            &DemEventRelateInformation[DemPbCfgPtr->DTR[DTRId].DemDtrEventRef];
        uint8 DemDtrUpdateKind = DemPbCfgPtr->DTR[DTRId].DemDtrUpdateKind;

        if ((DemDtrUpdateKind == DEM_DTR_UPDATE_ALWAYS)
            || ((DemDtrUpdateKind == DEM_DTR_UPDATE_STEADY)
                && (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC))))
        {
            switch (Ctrlval)
            {
            case DEM_DTR_CTL_NORMAL:
                DTRInfo[DTRId].TestResult = TestResult;
                DTRInfo[DTRId].LowerLimit = LowerLimit;
                DTRInfo[DTRId].UpperLimit = UpperLimit;
                break;
            case DEM_DTR_CTL_NO_MAX:
                DTRInfo[DTRId].TestResult = TestResult;
                DTRInfo[DTRId].LowerLimit = LowerLimit;
                break;
            case DEM_DTR_CTL_NO_MIN:
                DTRInfo[DTRId].TestResult = TestResult;
                DTRInfo[DTRId].UpperLimit = UpperLimit;
                break;
            case DEM_DTR_CTL_RESET:
                DTRInfo[DTRId].TestResult = 0;
                DTRInfo[DTRId].LowerLimit = 0;
                DTRInfo[DTRId].UpperLimit = 0;
                break;
            default:
                /*idle*/
                break;
            }
            ret = E_OK;
        }
#else
        DEM_UNUSED(DTRId);
        DEM_UNUSED(TestResult);
        DEM_UNUSED(LowerLimit);
        DEM_UNUSED(UpperLimit);
        DEM_UNUSED(Ctrlval);
#endif /* DEM_DTR_NUM > 0u */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Get the event ID of FreezeFrame.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Identification of an event by assigned EventId.
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DEM_LOCAL FUNC(P2CONST(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR), DEM_CODE)
    Dem_SelectOBDFreezeFrame(P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA) IntId)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    const Dem_EventMemEntryType* RetpEntry = NULL_PTR;
    const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
    const Dem_DTCType* pDTC = DemPbCfgPtr->DemDTC;
    const DemObdDTCType* pObdDTC = DemPbCfgPtr->DemObdDTC;
    uint8 SelectTimeA = 0xFF;
    uint8 SelectTimeB1 = 0xFF;
    uint8 SelectTimeB2 = 0xFF;
    uint8 SelectTimeC = 0xFF;
    uint8 SelectTime = 0xFF;
    boolean ClassAFind = FALSE;
    boolean ClassB1Find = FALSE;
    boolean ClassB2Find = FALSE;
    boolean ClassCFind = FALSE;
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        const Dem_EventMemEntryType* pEntry = Dem_CheckEventMemEntryExistsAlready(iloop);
        uint16 DTCRef = pEventCfg->DemDTCRef;
        if ((pEntry != NULL_PTR) && (pDTC[DTCRef].DemObdDTCRef != DEM_OBD_DTC_INVALID)
            && (DEM_OBD_DTC_CFG_INVALID != pObdDTC[pDTC[DTCRef].DemObdDTCRef].DemDtcValue))
        {
            uint8 AbsTime = pEntry->AbsTime;
            uint8 DemWWHOBDDTCClass = pDTC[DTCRef].DemWWHOBDDTCClass;
            if (DemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_A)
            {
                /* SWS_Dem_01173 */
                if (AbsTime < SelectTimeA)
                {
                    SelectTimeA = AbsTime;
                    *IntId = iloop;
                    RetpEntry = pEntry;
                }
                ClassAFind = TRUE;
            }
            if (ClassAFind == FALSE)
            {
                if (DemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_B1)
                {
                    /* SWS_Dem_01173 */
                    if (AbsTime < SelectTimeB1)
                    {
                        SelectTimeB1 = AbsTime;
                        *IntId = iloop;
                        RetpEntry = pEntry;
                    }
                    ClassB1Find = TRUE;
                }
                if (ClassB1Find == FALSE)
                {
                    if (DemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_B2)
                    {
                        /* SWS_Dem_01173 */
                        if (AbsTime < SelectTimeB2)
                        {
                            SelectTimeB2 = AbsTime;
                            *IntId = iloop;
                            RetpEntry = pEntry;
                        }
                        ClassB2Find = TRUE;
                    }
                    if (ClassB2Find == FALSE)
                    {
                        if (DemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_C)
                        {
                            /* SWS_Dem_01173 */
                            if (AbsTime < SelectTimeC)
                            {
                                SelectTimeC = AbsTime;
                                *IntId = iloop;
                                RetpEntry = pEntry;
                            }
                            ClassCFind = TRUE;
                        }
                        /* SWS_Dem_01173 */
                        if ((ClassCFind == FALSE) && (AbsTime < SelectTime))
                        {
                            SelectTime = AbsTime;
                            *IntId = iloop;
                            RetpEntry = pEntry;
                        }
                    }
                }
            }
        }
        pEventCfg++;
    }
    return RetpEntry;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */

#if ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) && (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_ON))
/*************************************************************************/
/*
 * Brief               Service to get the value of PID 21 from the Dem by a software component.
 * ServiceId           0xb1
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     PID21value:Content of PID 21 as raw hex value.
 * Param-Name[in/out]  None
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDataOfPID21(uint8* PID21value)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_GETDATAOFPID21, DEM_E_UNINIT);
    }
    else if (NULL_PTR == PID21value)
    {
        DEM_DET_REPORT(DEM_SID_GETDATAOFPID21, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* SWS_Dem_00704 */
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
        /* SWS_Dem_01098 */
        uint16 DistWithMilOn = 0U;
        /* MIL deactivated */
        /* the indicator is on*/
        if (DEM_INDICATOR_OFF != OBDMilStatus)
        {
            uint16 currentDistanceInformation = Dem_ReadDistanceInformation();
            if (currentDistanceInformation > OBDDistanceMILLastOn)
            {
                DistWithMilOn = currentDistanceInformation - OBDDistanceMILLastOn;
            }
        }
        if (OBDDistanceMILOn < (0xFFFFu - DistWithMilOn))
        {
            OBDDistanceMILOn += DistWithMilOn;
        }
        else
        {
            OBDDistanceMILOn = 0xFFFFu;
        }
        PID21value[0] = (uint8)OBDDistanceMILOn;
        PID21value[1] = (uint8)(OBDDistanceMILOn >> 8);
        ret = E_OK;
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU */
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) && (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_ON */

/*************************************************************************/
/*
 * Brief               Gets the DTC Severity availability mask.
 * ServiceId           0xb2
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     DTCSeverityMask:The value DTCSeverityMask indicates the
 *                      supported DTC severity bits from the Dem.
 * Param-Name[in/out]  none
 * Return              E_OK: get of DTC severity mask was successful
                        E_NOT_OK: get of DTC severity mask failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetDTCSeverityAvailabilityMask(Dem_DTCSeverityType* DTCSeverityMask)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETDTCSEVERITYAVAILABILITYMASK, DEM_E_UNINIT);
    }
    else if (NULL_PTR == DTCSeverityMask)
    {
        DEM_DET_REPORT(DEM_SID_DCMGETDTCSEVERITYAVAILABILITYMASK, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        *DTCSeverityMask = DemDTCFilterInfo.DTCSeverityMask;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_WWWOBD_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Service to report the value of the B1 counter computed by the Dem.
 * ServiceId           0xb4
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     B1Counter:Buffer containing the B1 counter.
 * Param-Name[in/out]  none
 * Return              Always E_OK is returned, as E_NOT_OK will never appear.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_GetB1Counter(uint16* B1Counter)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (DEM_STATE_INIT != Dem_InitState)
    {
        DEM_DET_REPORT(DEM_SID_GETB1COUNTER, DEM_E_UNINIT);
    }
    else if (NULL_PTR == B1Counter)
    {
        DEM_DET_REPORT(DEM_SID_GETB1COUNTER, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        *B1Counter = OBDB1Counter;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_WWWOBD_NUM > 0u */

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/*************************************************************************/
/*
 * Brief               Get the Current Distance Information.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(uint16, DEM_CODE) Dem_ReadDistanceInformation(void) /*read current distance*/
{
    uint8 data[2] = {0, 0};
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
    uint8 ref = DemGeneralOBD.DemOBDInputDistanceInformation;
    if ((ref != DEM_DATA_ELEMENT_CLASS_NUM_INVALID) && (DemDataElementClass[ref].DemDataElementReadFnc != NULL_PTR))
    {
        DemDataElementClass[ref].DemDataElementReadFnc(data);
    }
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
    return ((uint16)data[0u] | (uint16)((uint16)data[1u] << 8u));
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Get the Current Time Since Engine Start.
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(uint16, DEM_CODE) Dem_ReadTimeInformation(void)
{
    uint8 data[2] = {0, 0};
#if (DEM_DATA_ELEMENT_CLASS_NUM > 0u)
    uint8 ref = DemGeneralOBD.DemOBDTimeSinceEngineStart;
    if ((ref != DEM_DATA_ELEMENT_CLASS_NUM_INVALID) && (DemDataElementClass[ref].DemDataElementReadFnc != NULL_PTR))
    {
        DemDataElementClass[ref].DemDataElementReadFnc(data);
    }
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */
    return ((uint16)data[0u] | (uint16)((uint16)data[1u] << 8u));
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */

#if (DEM_DTR_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Clear DTRInfo By Clear Command
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_ClearDTRInfoByEventID(Dem_EventIdType IntId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    const DTRType* pDTR = DemPbCfgPtr->DTR;
    for (uint16 iloop = 0; iloop < DEM_DTR_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        if (IntId == pDTR->DemDtrEventRef)
        {
            Dem_ClearDTRInfoByDTRID(iloop);
        }
        pDTR++;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Clear DTRInfo By Clear Command
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_ClearDTRInfoByDTRID(uint16 DTRID) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    Dem_MemSet((uint8*)&DTRInfo[DTRID], 0u, sizeof(DTRInfoType));
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_DTR_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Process the B1 Counter
 * ServiceId           Internal Function
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_B1CounterProcess(void)
{
    const Dem_EventParameterType* pEventCfg = DemPbCfgPtr->DemEventParameter;
    const Dem_EventRelateInformationType* pEvent = DemEventRelateInformation;

    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        uint16 DTCRef = pEventCfg->DemDTCRef;
        if (DTCRef != DEM_DTC_REF_INVALID)
        {
            uint8 UdsStatus = pEvent->UdsStatus;
            if ((DemPbCfgPtr->DemDTC[DTCRef].DemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_B1)
                && ((DEM_FLAGS_ISSET(UdsStatus, DEM_UDS_STATUS_TF) != 0x00u)
                    && (DEM_FLAGS_ISSET(UdsStatus, DEM_UDS_STATUS_CDTC) != 0x00u)))
            {
                /* SWS_Dem_01154 */
                if (OBDB1Counter < 0xFFu)
                {
                    /* SWS_Dem_01158 */
                    OBDB1Counter++;
                }
                if (OBDB1Counter > 200u)
                {
                    /* SWS_Dem_01141 */
                    ContinuousMICounter = 0u;
                }
                break;
            }
        }
        pEvent++;
        pEventCfg++;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) || (DEM_J1939_SUPPORT == STD_ON */
/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
