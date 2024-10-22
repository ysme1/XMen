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
 **  FILENAME    : Dem.c                                                       **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : Implementation for DEM                                      **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/**
  \page ISOFT_MISRA_Exceptions  MISRA-C:2012 Compliance Exceptions
    ModeName:Dem<br>
  RuleSorce:puhua-rule.rcf 2.3.1

    \li PRQA S 3432 MISRA Rule 20.7 .<br>
    Reason:Function-like macros are used to allow more efficient code.

    \li PRQA S 0777 MISRA Rule 5.1 .<br>
    Reason:function name, design needs, namelength set to 63 in C99.

    \li PRQA S 0779 MISRA Rule 5.2 .<br>
    Reason:parameter name, design needs, namelength set to 63 in C99.

    \li PRQA S 0791 MISRA Rule 5.2 .<br>
    Reason:Memmap section, design needs, namelength set to 63 in C99.

    \li PRQA S 1532 MISRA Rule 8.7 .<br>
    Reason:Functions may be used in other projects.

    \li PRQA S 1505 MISRA Rule 8.7 .<br>
    Reason:Functions may be used in other projects.

    \li PRQA S 2985 MISRA Rule 2.2 .<br>
    Reason:StatusMaskType is not necessarily u8 for every project.

    \li PRQA S 2983 MISRA Rule 2.2 .<br>
    Reason:for loop condition is a macro definition, which varies in different projs.

    \li PRQA S 3415 MISRA Rule 13.5 .<br>
    Reason:function in && comparison does not need to be called when the first condition fails.

    \li PRQA S 2877 MISRA Dir 4.1 .<br>
    Reason:for loop condition is a macro definition, which varies in different projs.

    \li PRQA S 2812 MISRA Dir 4.1 .<br>
    Reason:Configuration Parameter varies in different projs.

    \li PRQA S 2995 MISRA Rule 2.2 .<br>
    Reason:If statement may be optimized, but kept for better Readability.

    \li PRQA S 2996 MISRA Rule 2.2 .<br>
    Reason:If statement may be optimized, but kept for better Readability.

    \li PRQA S 4394 MISRA Rule 10.8 .<br>
    Reason:Data conversion to a different range is necessary for design purpose.

    \li PRQA S 2003 MISRA Rule 16.3 .<br>
    Reason:Switch case is designed to skip over for design purpose.

    \li PRQA S 2981 MISRA Rule 2.2 .<br>
    Reason:Init may be necessary for different macro definition.

    \li PRQA S 2982 MISRA Rule 2.2 .<br>
    Reason:for loop condition is a macro definition, which varies in different projs.

    \li PRQA S 2741 MISRA Rule 14.3 .<br>
    Reason:Macro definition varies in different projs.

    \li PRQA S 2742 MISRA Rule 14.3 .<br>
    Reason:Macro definition varies in different projs.

    \li PRQA S 2755 MISRA CMN 0.4 .<br>
    Reason:Functions name is by design purpose.

    \li PRQA S 1330 MISRA Rule 8.3 .<br>
    Reason:Different configurations produce variations

    \li PRQA S 2461 MISRA Rule 14.2 .<br>
    Reason:Functions is by design purpose

    \li PRQA S 3218 MISRA Rule 8.9 .<br>
    Reason:Design required.

    \li PRQA S 3219 MISRA Rule 2.1 .<br>
    Reason:Design required.

    \li PRQA S 2469 MISRA Rule 14.2 .<br>
    Reason:For loop variant is designed to manually be change, design needs.
 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem.h"
#include "Dem_Dcm.h"
#include "Dem_Internal.h"
#include "SchM_Dem.h"
#if (DEM_NVRAM_BLOCKID_NUM > 0u)
#include "NvM.h"
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
#if (STD_ON == DEM_TRIGGER_FIM_REPORTS)
#include "FiM.h"
#endif /* STD_ON == DEM_TRIGGER_FIM_REPORTS */
#if (STD_ON == DEM_J1939_SUPPORT)
#include "J1939Dcm_Types.h"
#endif /* STD_ON == DEM_J1939_SUPPORT */

/*******************************************************************************
**                       Version  Check                                       **
*******************************************************************************/
#ifndef DEM_AR_RELEASE_MAJOR_VERSION
#error " Dem version miss"
#endif
#ifndef DEM_AR_RELEASE_MINOR_VERSION
#error " Dem version miss"
#endif
#ifndef DEM_AR_RELEASE_PATCH_VERSION
#error " Dem version miss"
#endif
#if ((1 != DEM_CFG_SW_MAJOR_VERSION) || (0 != DEM_CFG_SW_MINOR_VERSION) || (1 != DEM_CFG_SW_PATCH_VERSION))
#error " cfg version mismatching"
#endif
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#define DEM_START_SEC_VAR_INIT_PTR
#include "Dem_MemMap.h"
P2CONST(Dem_ConfigType, AUTOMATIC, DEM_CONST_PBCFG) DemPbCfgPtr = NULL_PTR;
#define DEM_STOP_SEC_VAR_INIT_PTR
#include "Dem_MemMap.h"

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define DEM_START_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
VAR(Dem_StateType, AUTOMATIC) Dem_InitState = DEM_STATE_UNINIT;
#define DEM_STOP_SEC_VAR_INIT_8
#include "Dem_MemMap.h"

/* OperationCycleStatus */
#define DEM_START_SEC_VAR_NO_INIT_8
#include "Dem_MemMap.h"
VAR(uint8, AUTOMATIC) DemOperationCycleStatus[DEM_OPERATION_CYCLE_NUM_BYTE];
#define DEM_STOP_SEC_VAR_NO_INIT_8
#include "Dem_MemMap.h"

#if (DEM_ENABLE_CONDITION_NUM > 0)
/* Enable Conditions Status Define */
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(uint8, AUTOMATIC) DemEnableConditionStatus[DEM_ENABLE_CONDITION_NUM_BYTE];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
DEM_LOCAL VAR(boolean, AUTOMATIC) Dem_CheckEnableCondition = FALSE;
#define DEM_STOP_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
#endif

#if (DEM_STORAGE_CONDITION_NUM > 0)
/* Storage Conditions Status Define */
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"
VAR(uint8, AUTOMATIC) DemStorageConditionStatus[DEM_STORAGE_CONDITION_NUM_BYTE];
#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
DEM_LOCAL VAR(boolean, AUTOMATIC) Dem_CheckStorageCondition = FALSE;
#define DEM_STOP_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
#endif

#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
#define DEM_START_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
DEM_LOCAL VAR(boolean, AUTOMATIC) Dem_FirstStartUp = FALSE; /* PRQA S 3218*/ /* MISRA Rule 8.9 */
#define DEM_STOP_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
#endif

#if ((DEM_NVRAM_BLOCKID_NUM > 0u) && (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH))
#define DEM_START_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
DEM_LOCAL VAR(uint8, AUTOMATIC) Dem_ClearCnt = 0u;
#define DEM_STOP_SEC_VAR_INIT_8
#include "Dem_MemMap.h"
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u && DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH */
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#if (DEM_ENABLE_CONDITION_NUM > 0)
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_SetEnableCondictionProcess(void);
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

#if (DEM_STORAGE_CONDITION_NUM > 0)
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_SetStorageCondictionProcess(void);
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ProcessEventStatus(
    Dem_EventStatusType EventStatus,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_NVRAM_BLOCKID_NUM > 0u)
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearNonvolatile(void);
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/******************************************************************************/
/*
 * Brief               Initializes the internal states necessary to process events reported by BSW-modules.
 * ServiceId           0x01
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_PreInit(void)
{
    /* OperationCycleStatus */
    Dem_MemSet(DemOperationCycleStatus, 0x00u, DEM_OPERATION_CYCLE_NUM_BYTE);
#if (DEM_ENABLE_CONDITION_NUM > 0)
    /* Init Enable Conditions */
    Dem_MemCopy(DemEnableConditionStatus, DemEnableCondition, DEM_ENABLE_CONDITION_NUM_BYTE);
#endif
#if (DEM_STORAGE_CONDITION_NUM > 0)
    /* Init Storage Conditions */
    Dem_MemSet(DemStorageConditionStatus, 0x00u, DEM_STORAGE_CONDITION_NUM_BYTE);

    for (uint16 iloop = 0; iloop < DEM_STORAGE_CONDITION_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        if (DemStorageCondition[iloop].DemStorageConditionStatus == TRUE)
        {
            DEM_BITS_SET(DemStorageConditionStatus, iloop);
        }
    }
#endif
    /* SWS_Dem_00180 */
    Dem_MemSet(
        (uint8*)DemEventRelateInformation,
        0x00u,
        (sizeof(Dem_EventRelateInformationType) * DEM_EVENT_PARAMETER_NUM));
    /*SWS_Dem_00167*/
    Dem_EventQueueInit();
    /*SWS_Dem_00180*/ /*SWS_Dem_00438*/
    Dem_DebounceInit();
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) || (DEM_J1939_SUPPORT == STD_ON))
#if (DEM_RATIO_NUM > 0)
    Dem_IUMPRInit();
#endif
#if (DEM_DTR_NUM > 0)
    Dem_DTRInit();
#endif
    Dem_OBDInit();
#endif
    Dem_InitState = DEM_STATE_PRE_INIT;
    return;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Initializes or reinitializes this module.
 * ServiceId           0x02
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ConfigPtr:Pointer to the configuration set in VARIANT-POSTBUILD.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_Init(P2CONST(Dem_ConfigType, AUTOMATIC, DEM_CONST_PBCFG) ConfigPtr)
{
    /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
    P2CONST(Dem_EventParameterType, AUTOMATIC, DEM_CONST) pEventCfg;
#endif

    DemPbCfgPtr = ConfigPtr;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (NULL_PTR == ConfigPtr)
    {
        DEM_DET_REPORT(DEM_SID_INIT, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (DEM_NVRAM_BLOCKID_NUM > 0u)
        Std_ReturnType NvmResult = E_NOT_OK;
#else
        Std_ReturnType NvmResult;
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
        Dem_DcmInit();
        Dem_EntryInit();
#if (DEM_NVRAM_BLOCKID_NUM > 0u)
        NvmResult = Dem_IntReadNvRAM();
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
        Dem_EventMemInit(NvmResult);

        /*SWS_Dem_00854 */
        for (uint8 iloop = 0u; iloop < DEM_OPERATION_CYCLE_NUM; iloop++)
        {
            if (DemOperationCycle[iloop].DemOperationCycleAutostart == TRUE)
            {
#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)
                if ((DEM_BITS_ISSET(DemOperationCycleStatus, iloop)))
                {
                    Dem_OperationCycleStart((uint8)iloop, TRUE);
                }
                else
#endif /* DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON */
                {
                    /* req SWS_Dem_00853 */
                    DEM_BITS_SET(DemOperationCycleStatus, iloop);
                    Dem_OperationCycleStart(iloop, FALSE);
                }
            }
        }
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
        pEventCfg = DemPbCfgPtr->DemEventParameter;
        for (uint16 iloop = 0u; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
        {
            uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
            if ((pEventCfg->AlgorithmType == DEM_DEBOUNCE_TIME_BASE)
                && (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM))
            {
                DemDebounceTimerInfo[AlgorithmIndex].IntId = iloop;
            }
            pEventCfg++;
        }
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
        Dem_FreezeFrameInit();
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0u */
        Dem_ResetDemClearDTCInfo();
#if (DEM_J1939_SUPPORT == STD_ON)
        Dem_J1939Init();
#endif /* DEM_J1939_SUPPORT == STD_ON */
        Dem_InitState = DEM_STATE_INIT;
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
        if (Dem_FirstStartUp == FALSE) /*SWS_Fim_00103*/
        {
            (void)FiM_DemInit();
            Dem_FirstStartUp = TRUE;
        }
#endif /* DEM_TRIGGER_FIM_REPORTS == STD_ON */
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_VERSION_INFO_API == STD_ON)
/*************************************************************************/
/*
 * Brief               Provide Version information to other BSWs
 * ServiceId           0x00
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     versionInfo
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
FUNC(void, DEM_CODE)
Dem_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (NULL_PTR == (versionInfo))
    {
        DEM_DET_REPORT(DEM_SID_GETVERSIONINFO, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        versionInfo->vendorID = DEM_VENDOR_ID;
        versionInfo->moduleID = DEM_MODULE_ID;
        versionInfo->sw_major_version = DEM_SW_MAJOR_VERSION;
        versionInfo->sw_minor_version = DEM_SW_MINOR_VERSION;
        versionInfo->sw_patch_version = DEM_SW_PATCH_VERSION;
    }
}
#endif

/*************************************************************************/
/*
 * Brief               Shuts down this module.
 * ServiceId           0x03
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
FUNC(void, DEM_CODE) Dem_Shutdown(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SHUTDOWN, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        /* OperationCycleStatus */
        for (uint8 iloop = 0; iloop < DEM_OPERATION_CYCLE_NUM; iloop++)
        {
            /*SWS_Dem_00697*/
            if (
#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)
                (DemOperationCycle[iloop].DemOperationCycleAutomaticEnd == TRUE) &&
#endif
                (DEM_BITS_ISSET(DemOperationCycleStatus, iloop)))
            {
                Dem_OperationCycleEnd(iloop);
                DEM_BITS_CLR(DemOperationCycleStatus, iloop);
            }
        }
#if (DEM_NVRAM_BLOCKID_NUM > 0)
        Dem_IntWriteNvRAM();
#endif
        Dem_InitState = DEM_STATE_SHUTDOWN;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Queues the reported events from the BSW modules (API is only used by
                        BSW modules). The interface has an asynchronous behavior, because
                        the processing of the event is done within the Dem main function.
                        OBD Events Suppression shall be ignored for this computation.
 * ServiceId           0x0f
 * Sync/Async          Asynchronous
 * Reentrancy          Reentrant for different EventIds. Non reentrant for the same EventId.
 * Param-Name[in]      EventId: Identification of an event by assigned Event ID.
 *                       EventStatus: Monitor test result
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(void, DEM_CODE) Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState == DEM_STATE_UNINIT)
    {
        DEM_DET_REPORT(DEM_SID_REPORTERRORSTATUS, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (0u == EventId))
    {
        DEM_DET_REPORT(DEM_SID_REPORTERRORSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventParameterType* pEventCfg = &DemPbCfg.DemEventParameter[IntId];
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        if (pEventCfg->DemEventKind != DEM_EVENT_KIND_BSW)
        {
            DEM_DET_REPORT(DEM_SID_REPORTERRORSTATUS, DEM_E_WRONG_CONFIGURATION);
        }
        else if (
            (pEventCfg->AlgorithmType == DEM_DEBOUNCE_MONITOR_INTERNAL) && (EventStatus != DEM_EVENT_STATUS_FAILED)
            && (EventStatus != DEM_EVENT_STATUS_PASSED))
        {
            DEM_DET_REPORT(DEM_SID_REPORTERRORSTATUS, DEM_E_WRONG_CONFIGURATION);
        }
        else if ((Dem_InitState == DEM_STATE_PRE_INIT) && (pEventCfg->DemReportBehavior != REPORT_BEFORE_INIT))
        {
            DEM_DET_REPORT(DEM_SID_REPORTERRORSTATUS, DEM_E_WRONG_CONFIGURATION);
        }
        else if (
            (Dem_InitState != DEM_STATE_INIT)
            && (DemPbCfg.DemDebounceCounterBasedClass[pEventCfg->AlgorithmRef].DemDebounceCounterStorage == TRUE))
        {
            DEM_DET_REPORT(DEM_SID_REPORTERRORSTATUS, DEM_E_WRONG_CONDITION);
        }
        else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        {
            Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
#if (DEM_ENABLE_SOFT_FILTER_OF_PASS == STD_ON)
            if ((EventStatus == DEM_EVENT_STATUS_PASSED)
                && (0x00u
                    == DEM_FLAGS_ISSET(
                        pEvent->UdsStatus,
                        (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC))))
            {
                /*soft filter when pass,if TF/TNCLSC or TNCTOC is flaged then return e_ok whith no deal*/
            }
            else
#endif
            {
                boolean doadd = TRUE;
                if (Dem_InitState != DEM_STATE_PRE_INIT)
                {
                    uint8 OperationCycleId;
#if (DEM_ENABLE_CONDITION_NUM > 0)
                    if (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
                    {
                        /*In case of Dem-internal debouncing the related fault detection counter will be frozen or
                         * reset*/
                        Dem_DebounceFreeze(IntId);
                        doadd = FALSE;
                    }
#endif
                    OperationCycleId = pEventCfg->DemOperationCycleRef;
                    if (((DEM_BITS_ISNSET(DemOperationCycleStatus, OperationCycleId))
                         && (DEM_OPCYC_OBD_DCY != DemOperationCycle[OperationCycleId].DemOperationCycleType))
                        || (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_DTC_SETTING))
                        || (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE)))
                    {
                        doadd = FALSE;
                    }
                }
                if (TRUE == doadd)
                {
                    Dem_ProcessEventStatus(EventStatus, pEvent);
                    (void)Dem_EventQueueAdd(Dem_GetEventExternalId(IntId), EventStatus);
                }
            }
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY) /*SWS_Dem_00687*/
/*************************************************************************/
/*
 * Brief               Set the available status of a specific Event.
 * ServiceId           0x37
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      EventId : Identification of an event by assigned EventId.
 *                       AvailableStatus: This parameter specifies whether the respective
 *                       Event shall be available (TRUE) or not (FALSE).
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful.
 *                       E_NOT_OK:change of available status not accepted
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* req SWS_Dem_01106 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState == DEM_STATE_UNINIT)
    {
        DEM_DET_REPORT(DEM_SID_SETEVENTAVAILABLE, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (0u == EventId))
    {
        DEM_DET_REPORT(DEM_SID_SETEVENTAVAILABLE, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
        Dem_UdsStatusByteType oldStatus = pEvent->UdsStatus;
#endif
        /*SWS_Dem_01109*/
        if ((NULL_PTR == Dem_CheckEventMemEntryExistsAlready(IntId))
            && (DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF) == 0x00u))
        {
            const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
            uint16 dtcIndex = pDemEventParameter[IntId].DemDTCRef;
            if (AvailableStatus == TRUE)
            {
                DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE);
                /*SWS_Dem_01111*/ /* bit 4 6 the initialized value 0x50 */
                DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC);
                DemDTCGeneralStatus[dtcIndex].SuppressionStatus = FALSE;
            }
            else
            {
                const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[dtcIndex];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
                const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
                DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE);
                /*SWS_Dem_01110 */
                pEvent->UdsStatus = 0x00;
                /*SWS_Dem_00915 */
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                for (uint16 iloop = 0u; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                {
                    if (DEM_FLAGS_ISSET(DemEventRelateInformation[*pDTCMapping].Status, DEM_EVENT_STATUS_AVAILABLE)
                        != 0x00u)
                    {
                        dtcIndex = DEM_DTC_REF_INVALID;
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                        break;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                    }
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                    pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                }
                if (dtcIndex != DEM_DTC_REF_INVALID)
                {
                    DemDTCGeneralStatus[dtcIndex].SuppressionStatus = TRUE;
                }
            }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
            (void)FiM_DemTriggerOnEventStatus(Dem_GetEventExternalId(IntId), oldStatus, pEvent->UdsStatus);
#endif
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif

/*************************************************************************/
/*
 * Brief               Processes the events reported by SW-Cs via RTE.
 * ServiceId           0x04
 * Sync/Async          Synchronous/Asynchronous
 * Reentrancy          Reentrant for different EventIds.
 *                       Non reentrant for the same EventId.
 * Param-Name[in]      EventId:Identification of an event by assigned EventId.
 *                       EventStatus: Monitor test result
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: set of event status was successful
 *                       E_NOT_OK: set of event status failed or could not be accepted
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETEVENTSTATUS, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (0u == EventId))
    {
        DEM_DET_REPORT(DEM_SID_SETEVENTSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        if (pEventCfg->DemEventKind != DEM_EVENT_KIND_SWC)
        {
            DEM_DET_REPORT(DEM_SID_SETEVENTSTATUS, DEM_E_WRONG_CONFIGURATION);
        }
        else if (
            (pEventCfg->AlgorithmType == DEM_DEBOUNCE_MONITOR_INTERNAL) && (EventStatus != DEM_EVENT_STATUS_FAILED)
            && (EventStatus != DEM_EVENT_STATUS_PASSED))
        {
            DEM_DET_REPORT(DEM_SID_SETEVENTSTATUS, DEM_E_WRONG_CONFIGURATION);
        }
        else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        {
            Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
#if (DEM_ENABLE_SOFT_FILTER_OF_PASS == STD_ON)
            if ((EventStatus == DEM_EVENT_STATUS_PASSED)
                && (0x00u
                    == DEM_FLAGS_ISSET(
                        pEvent->UdsStatus,
                        (DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC))))
            {
                /*soft filter when pass,if TF/TNCLSC or TNCTOC is flaged then return e_ok whith no deal*/
                ret = E_OK;
            }
            else
#endif /* DEM_ENABLE_SOFT_FILTER_OF_PASS == STD_ON */
            {
#if (DEM_ENABLE_CONDITION_NUM > 0u)
                if (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
                {
                    /*SWS_Dem_00447 SWS_Dem_00449 */
                    /*In case of Dem-internal debouncing the related fault detection counter will be frozen or reset*/
                    Dem_DebounceFreeze(IntId);
                    ret = E_NOT_OK;
                }
                else
#endif /* DEM_ENABLE_CONDITION_NUM > 0u */
#if (DEM_STORAGE_CONDITION_NUM > 0u)
                {
                    ret = E_OK;
                    if ((EventStatus == DEM_EVENT_STATUS_FAILED)
                        && (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION)))
                    {
                        ret = E_NOT_OK;
                        const uint8 DemStorageConditionGroupRef = pEventCfg->DemStorageConditionGroupRef;
                        uint8 Conditionindex = 0;
                        /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                        for (uint8 index = 0; (index < DEM_STORAGE_CONDITION_NUM_BYTE) && (E_NOT_OK == ret); index++)
                        /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                        {
                            uint8 Counter = 0;
                            uint8 Mask = 0x01;
                            /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                            for (; (Conditionindex < DEM_STORAGE_CONDITION_NUM) && (E_NOT_OK == ret) && (Counter < 8u);
                                 Conditionindex++)
                            /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                            {                   /*SWS_Dem_01086*/
                                if (((DemStorageConditionGroup[DemStorageConditionGroupRef][index] & Mask) != 0u)
                                    && (DemStorageCondition[Conditionindex].DemStorageConditionReplacementEventRef
                                        != DEM_EVENT_PARAMETER_INVALID))
                                {
                                    IntId = DemStorageCondition[Conditionindex].DemStorageConditionReplacementEventRef;
                                    pEvent = Dem_GetEventInfo(IntId); /*SWS_Dem_01086*/
                                    pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
                                    ret = E_OK;
                                }
                                Counter++; /* PRQA S 2983 */         /* MISRA Rule 2.2 */
                                Mask = Mask << 1u; /* PRQA S 2983 */ /* MISRA Rule 2.2 */
                            }
                        }
                    }
                }
                if (E_OK == ret)
#endif /* DEM_STORAGE_CONDITION_NUM > 0u */
                {
                    uint8 OperationCycleId = pEventCfg->DemOperationCycleRef;
                    if (((DEM_BITS_ISNSET(DemOperationCycleStatus, OperationCycleId))
                         && (DemOperationCycle[OperationCycleId].DemOperationCycleType != DEM_OPCYC_OBD_DCY))
                        || (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_DTC_SETTING))
                        || (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE)))
                    {
                        ret = E_NOT_OK;
                    }
                    else
                    {
                        Dem_ProcessEventStatus(EventStatus, pEvent);
                        ret = Dem_EventQueueAdd(Dem_GetEventExternalId(IntId), EventStatus);
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
 * Brief               Control the internal debounce counter/timer by BSW modules and SW-Cs.
 * ServiceId           0x09
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different EventIds.
 *                       Non reentrant for the same EventId.
 * Param-Name[in]      EventId:Identification of an event by assigned EventId.
 *                       DebounceResetStatus :  Freeze or reset the internal debounce counter
 *                       /timer of the specified event.
 * Param-Name[out]     None...
 * Param-Name[in/out]  None...
 * Return              None...
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventDebounceStatus(Dem_EventIdType EventId, Dem_DebounceResetStatusType DebounceResetStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState < DEM_STATE_PRE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_RESETEVENTDEBOUNCESTATUS, DEM_E_UNINIT);
    }
    else if ((EventId >= DEM_EVENT_PARAMETER_NUM) || (0u == EventId))
    {
        DEM_DET_REPORT(DEM_SID_RESETEVENTDEBOUNCESTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
        /*SWS_Dem_00676*/
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        if ((Dem_InitState != DEM_STATE_INIT)
            && (DemPbCfgPtr->DemDebounceCounterBasedClass[pEventCfg->AlgorithmRef].DemDebounceCounterStorage == TRUE))
        {
            DEM_DET_REPORT(DEM_SID_RESETEVENTDEBOUNCESTATUS, DEM_E_WRONG_CONDITION);
        }
        else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        {
            const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
            if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
            {
                const uint16 AlgorithmIndex = pEventCfg->AlgorithmIndex;
                if (DebounceResetStatus == DEM_DEBOUNCE_STATUS_RESET)
                {
                    /*SWS_Dem_00684*/
                    const uint8 AlgorithmType = pEventCfg->AlgorithmType;
                    if (AlgorithmType == DEM_DEBOUNCE_COUNTER_BASED)
                    {
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0)
                        if (AlgorithmIndex < DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM)
                        {
                            Dem_DebounceCounterInfoType* pDebounceCounter = &DemDebounceCounterInfo[AlgorithmIndex];
                            pDebounceCounter->InternalDebounceCounter = 0;
                        }
#endif
                    }
                    else if (AlgorithmType == DEM_DEBOUNCE_TIME_BASE)
                    {
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
                        if (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM)
                        {
                            Dem_DebounceTimeInfoType* pDebounceTimer = &DemDebounceTimerInfo[AlgorithmIndex];
                            pDebounceTimer->Timeout = 0u;
                            pDebounceTimer->Triggered = FALSE;
                            pDebounceTimer->CurStatus = DEM_EVENT_STATUS_PREPASSED;
                        }
#endif
                    }
                    else
                    {
                        /*idle*/
                    }
                }
                else if (DebounceResetStatus == DEM_DEBOUNCE_STATUS_FREEZE)
                {
                    /*SWS_Dem_00685*/
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
                    if (AlgorithmIndex < DEM_DEBOUNCE_TIME_BASED_EVENT_NUM)
                    {
                        DemDebounceTimerInfo[AlgorithmIndex].IsFreezing = TRUE;
                    }
#endif
                }
                else
                {
                    /*idle*/
                }
                ret = E_OK;
            }
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Resets the event failed status.
 * ServiceId           0x05
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different EventIds.
 *                       Non reentrant for the same EventId.
 * Param-Name[in]      EventId Identification of an event by assigned EventId.
 * Param-Name[out]     None...
 * Param-Name[in/out]  None...
 * Return              E_OK: reset of event status was successful
 *                       E_NOT_OK: reset of event status failed or is not allowed,
 *                       because the event is already tested in this operation cycle
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventStatus(Dem_EventIdType EventId)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState < DEM_STATE_PRE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_RESETEVENTSTATUS, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_RESETEVENTSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        /* SWS_Dem_00638*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, (DEM_UDS_STATUS_TNCTOC | DEM_EVENT_STATUS_AVAILABLE)))
        {
            /*SWS_Dem_00187*/
            DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TF);
            /* update the combination event dtc status*/
            Dem_UpdateCombinedDtcStatus(IntId);
            Dem_ResponseOnDtcStatusChange(IntId);
            Dem_DebounceReset(IntId);
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_FFPRESTORAGE_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Captures the freeze frame data for a specific event.
 * ServiceId           0x06
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different EventIds.
 *                       Non reentrant for the sameEventId.
 * Param-Name[in]      EventId:Identification of an event by assigned EventId
 * Param-Name[out]     None...
 * Param-Name[in/out]  None...
 * Return              None...
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_PrestoreFreezeFrame(Dem_EventIdType EventId)
{
    Std_ReturnType ret = E_NOT_OK;
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState < DEM_STATE_PRE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_PRESTOREFREEZEFRAME, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_PRESTOREFREEZEFRAME, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        if (pEventCfg->DemFFPrestorageSupported == FALSE)
        {
            DEM_DET_REPORT(DEM_SID_PRESTOREFREEZEFRAME, DEM_E_WRONG_CONFIGURATION);
        }
        else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        {
            const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
            /*SWS_Dem_01108*/
            if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
            {
                ret = Dem_PreStoreFF(EventId);
            }
        }
    }
#else
    DEM_UNUSED(EventId);
#endif
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Clears a prestored freeze frame of a specific event.
 * ServiceId           0x07
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different EventIds.
 *                       Non reentrant for the same EventId.
 * Param-Name[in]      EventId : Identification of an event by assigned EventId.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId)
{
    Std_ReturnType ret;
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState < DEM_STATE_PRE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_CLEARPRESTOREDFREEZEFRAME, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_CLEARPRESTOREDFREEZEFRAME, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        if (DemPbCfgPtr->DemEventParameter[IntId].DemFFPrestorageSupported == FALSE)
        {
            DEM_DET_REPORT(DEM_SID_CLEARPRESTOREDFREEZEFRAME, DEM_E_WRONG_CONFIGURATION);
        }
        else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        {
            ret = Dem_ClearPreStoreFF(EventId);
        }
    }
#else
    ret = E_NOT_OK;
    DEM_UNUSED(EventId);
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0 */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_FFPRESTORAGE_SUPPORT == STD_ON */

/*************************************************************************/
/*
 * Brief               Sets an operation cycle state.
 * ServiceId           0x08
 * Sync/Async          Asynchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OperationCycleId: Identification of operation cycle, like power cycle,
 *                                         driving cycle.
 *                       CycleState: New operation cycle state: (re-)start or end
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: set of operation cycle was accepted and will be handled asynchronously
 *                       E_NOT_OK: set of operation cycle was rejected>
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetOperationCycleState(uint8 OperationCycleId, Dem_OperationCycleStateType CycleState)
{
    Std_ReturnType ret;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState == DEM_STATE_UNINIT)
    {
        DEM_DET_REPORT(DEM_SID_SETOPERATIONCYCLESTATE, DEM_E_UNINIT);
    }
    else if (OperationCycleId >= DEM_OPERATION_CYCLE_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        if (CycleState == DEM_CYCLE_STATE_START)
        {
            boolean IsRestart = FALSE;                                                       /*SWS_Dem_00853*/
            if (DEM_BITS_ISSET(DemOperationCycleStatus, OperationCycleId)) /* PRQA S 2985 */ /* MISRA Rule 2.2 */
            {
                IsRestart = TRUE; /*SWS_Dem_00483*/
            }
            else
            {
                DEM_BITS_SET(DemOperationCycleStatus, OperationCycleId); /* PRQA S 2985 */ /* MISRA Rule 2.2 */
            }
            Dem_OperationCycleStart(OperationCycleId, IsRestart);
        }
        else
        {
            if (DEM_BITS_ISSET(DemOperationCycleStatus, OperationCycleId)) /* PRQA S 2985 */ /* MISRA Rule 2.2 */
            {
                Dem_OperationCycleEnd(OperationCycleId);
                DEM_BITS_CLR(DemOperationCycleStatus, OperationCycleId); /* PRQA S 2985 */ /* MISRA Rule 2.2 */
            }
        }
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets information about the status of a specific operation cycle.
 * ServiceId           0x9e
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OperationCycleId : Identification of operation cycle, like power cycle,
 *                                          driving cycle.
 * Param-Name[out]     CycleState : Cycle status information
 * Param-Name[in/out]  None
 * Return              E_OK: read out of operation cycle was successful
 *                       E_NOT_OK: read out of operation cycle failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOperationCycleState(
    uint8 OperationCycleId,
    P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_APPL_DATA) CycleState) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState == DEM_STATE_UNINIT)
    {
        DEM_DET_REPORT(DEM_SID_GETOPERATIONCYCLESTATE, DEM_E_UNINIT);
    }
    else if (OperationCycleId >= DEM_OPERATION_CYCLE_NUM)
    {
        DEM_DET_REPORT(DEM_SID_GETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
    }
    else if (CycleState == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETOPERATIONCYCLESTATE, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        if (DEM_BITS_ISNSET(DemOperationCycleStatus, OperationCycleId)) /* PRQA S 2985 */ /* MISRA Rule 2.2 */
        {
            *CycleState = DEM_CYCLE_STATE_END;
        }
        else
        {
            *CycleState = DEM_CYCLE_STATE_START;
        }
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Triggers the next aging cycle state.
 * ServiceId           0x11
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      OperationCycleId:Identification of aging cycle.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: set of aging cycle was successful
 *                       E_NOT_OK: set of aging cycle failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetAgingCycleState(uint8 OperationCycleId)
{
    Std_ReturnType ret;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState == DEM_STATE_UNINIT)
    {
        DEM_DET_REPORT(DEM_SID_SETAGINGCYCLESTATE, DEM_E_UNINIT);
    }
    else if (OperationCycleId >= DEM_OPERATION_CYCLE_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETAGINGCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_AgingCycle = OperationCycleId;
        ret = E_OK;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Sets the WIR status bit via failsafe SW-Cs.
 * ServiceId           0x7a
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different EventIds.
 *                       Non reentrant for the same EventId.
 * Param-Name[in]      EventId: Identification of an event by assigned EventId.
 *                       WIRStatus: Requested status of event related WIR-bit
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: The request is accepted
 *                       E_NOT_OK: not be accepted
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetWIRStatus(Dem_EventIdType EventId, boolean WIRStatus)
{
    Std_ReturnType ret = E_NOT_OK;
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent; /* PRQA S 3432 */ /* MISRA Rule 20.7 */
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState < DEM_STATE_PRE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETWIRSTATUS, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_SETWIRSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        pEvent = Dem_GetEventInfo(IntId);
        /*SWS_Dem_01108 */
        if ((0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
            && (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_DTC_SETTING)))
        {
            if (WIRStatus == TRUE)
            {
                DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_WIR); /*SWS_Dem_00833*/
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
                /*The bit is set to 1 when DTC status bit no 7 is set to 1. In all cases, FDC10 has reached the value
                 * +127, since DTC information was latest cleared, before the bit is set to 1 and warring indicator is
                 * requested*/
                if (0x00u != DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
                {
                    DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_WIRSLC); /*bit 5*/
                }
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
            }
            else
            {
                DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_WIR); /*SWS_Dem_00834*/
            }
            Dem_UpdateCombinedDtcStatus(IntId); /* update the combination event dtc status*/
            Dem_ResponseOnDtcStatusChange(IntId);
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the failed status of a DemComponent.
 * ServiceId           0x2a
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ComponentId:Identification of a DemComponent
 * Param-Name[out]     ComponentFailed: TRUE: failed FALSE: not failed
 * Param-Name[in/out]  None
 * Return              E_OK: getting "ComponentFailed" was successful
 *                       E_NOT_OK: getting "ComponentFailed" was not successful
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432,1532,3673++ */ /* MISRA Rule 20.7,8.7,8.13 */
Dem_GetComponentFailed(Dem_ComponentIdType ComponentId, P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) ComponentFailed)
/* PRQA S 3432,1532,3673-- */ /* MISRA Rule 20.7,8.7,8.13 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (DEM_COMPONENT_NUM > 0)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETCOMPONENTFAILED, DEM_E_UNINIT);
    }
    else if ((ComponentId > DEM_COMPONENT_NUM) || (0u == ComponentId))
    {
        DEM_DET_REPORT(DEM_SID_GETCOMPONENTFAILED, DEM_E_WRONG_RECORDNUMBER);
    }
    else if (ComponentFailed == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETCOMPONENTFAILED, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const DemComponentStatusType* pDemComponentStatus = &DemComponentStatus[Dem_GetEventInternalId(ComponentId)];
        /*SWS_Dem_01134 */
        if (pDemComponentStatus->availability == TRUE)
        {
            /*SWS_Dem_01131 */
            *ComponentFailed = pDemComponentStatus->Status;
            ret = E_OK;
        }
    }
#else
    DEM_UNUSED(ComponentId);
    DEM_UNUSED(ComponentFailed);
#endif
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the current extended event status of an event.
 * ServiceId           0x0a
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId:Identification of an event by assigned EventId.
 * Param-Name[out]     EventStatusByte:UDS DTC status byte of the requested event
 * Param-Name[in/out]  None
 * Return              E_OK: get of event status was successful
 *                       E_NOT_OK: get of event status failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432,1532++ */ /* MISRA Rule 20.7,8.7 */
Dem_GetEventStatus(Dem_EventIdType EventId, P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) EventStatusByte)
/* PRQA S 3432,1532-- */ /* MISRA Rule 20.7,8.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTSTATUS, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else if (EventStatusByte == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTSTATUS, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(Dem_GetEventInternalId(EventId));
        /*SWS_Dem_01108*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            *EventStatusByte = pEvent->UdsStatus;
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the event failed status of an event.
 * ServiceId           0x0b
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId: Identification of an event by assigned EventId.
 * Param-Name[out]     EventFailed: TRUE - Last Failed FALSE - not Last Failed
 * Param-Name[in/out]  None
 * Return              E_OK: get of "EventFailed" was successful
 *                       E_NOT_OK: get of "EventFailed" was not successful
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_GetEventFailed(Dem_EventIdType EventId, P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventFailed)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTFAILED, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTFAILED, DEM_E_WRONG_CONFIGURATION);
    }
    else if (EventFailed == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTFAILED, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(Dem_GetEventInternalId(EventId));
        /*SWS_Dem_01108*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF))
            {
                *EventFailed = FALSE;
            }
            else
            {
                *EventFailed = TRUE;
            }
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the event tested status of an event.
 * ServiceId           0x0c
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId:Identification of an event by assigned EventId.
 * Param-Name[out]     EventTested: TRUE - event tested this cycle
 *                                    FALSE - event not tested this cycle
 * Param-Name[in/out]  None
 * Return              E_OK: get of event state "tested" successful
 *                       E_NOT_OK: get of event state "tested" failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_GetEventTested(Dem_EventIdType EventId, P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventTested)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTTESTED, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTTESTED, DEM_E_WRONG_CONFIGURATION);
    }
    else if (EventTested == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTTESTED, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(Dem_GetEventInternalId(EventId));
        /*SWS_Dem_01108*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            if (0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC))
            {
                *EventTested = TRUE;
            }
            else
            {
                *EventTested = FALSE;
            }
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the debouncing status of an event.
 * ServiceId           0x9f
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId:Identification of an event by assigned EventId.
 * Param-Name[out]     DebouncingState
 * Param-Name[in/out]  None
 * Return              E_OK: get of debouncing status per event state successful
 *                       E_NOT_OK: get of debouncing per event state failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDebouncingOfEvent(
    Dem_EventIdType EventId,
    P2VAR(Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA) DebouncingState) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)

    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETDEBOUNCINGOFEVENT, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETDEBOUNCINGOFEVENT, DEM_E_WRONG_CONFIGURATION);
    }
    else if (DebouncingState == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETDEBOUNCINGOFEVENT, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        sint8 FDC = 0;
        /*SWS_Dem_01108*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            (void)Dem_GetInteralFDC(IntId, &FDC);
            *DebouncingState = 0x00;
            /*SWS_Dem_00844*/
            if ((FDC < 127) && (FDC > 0))
            {
                *DebouncingState |= DEM_TEMPORARILY_DEFECTIVE;
            }
            if (FDC == 127)
            {
                *DebouncingState |= DEM_FINALLY_DEFECTIVE;
            }
            if ((FDC < 0) && (FDC > -128))
            {
                *DebouncingState |= DEM_TEMPORARILY_HEALED;
            }
            if ((FDC == -128) || (FDC == 127))
            {
                *DebouncingState |= DEM_TEST_COMPLETE;
            }
            if ((0x00u == DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC))
                && ((0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
                    || (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION))))
            {
                *DebouncingState |= DEM_DTR_UPDATE;
            }
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the DTC of an event.
 * ServiceId           0x0d
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId:Identification of an event by assigned EventId.
 *                       DTCFormat: Defines the output-format of the requested DTCvalue.>
 * Param-Name[out]     DTCOfEvent: Receives the DTC value in respective format returned
 *                                   by this function.
 * Param-Name[in/out]  None
 * Return              E_OK: get of DTC was successful
 *                       E_NOT_OK: the call was not successful
 *                       DEM_E_NO_DTC_AVAILABLE: there is no DTC configured in the requested format
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCOfEvent(
    Dem_EventIdType EventId,
    Dem_DTCFormatType DTCFormat,
    P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) DTCOfEvent) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETDTCOFEVENT, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETDTCOFEVENT, DEM_E_WRONG_CONFIGURATION);
    }
    else if (DTCOfEvent == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETDTCOFEVENT, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        /*SWS_Dem_01108*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            const Dem_EventParameterType* pEventCfg = &DemPbCfgPtr->DemEventParameter[IntId];
            const uint16 DTCRef = pEventCfg->DemDTCRef;
            *DTCOfEvent = 0x00u;
            if (DTCRef != DEM_DTC_REF_INVALID)
            {
                /*SWS_Dem_00269*/
                const uint16 ObdDTCRef = DemPbCfgPtr->DemDTC[DTCRef].DemObdDTCRef;
                const DemObdDTCType* pDemObdDTC = DemPbCfgPtr->DemObdDTC;
                switch (DTCFormat)
                {
                case DEM_DTC_FORMAT_OBD:
                    if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                        && (pDemObdDTC[ObdDTCRef].DemDtcValue != DEM_OBD_DTC_CFG_INVALID))
                    {
                        *DTCOfEvent = pDemObdDTC[ObdDTCRef].DemDtcValue;
                        ret = E_OK;
                    }
                    break;
                case DEM_DTC_FORMAT_UDS:
                    if (DemPbCfgPtr->DemDTC[DTCRef].DemDtcValue != DEM_DTC_CFG_INVALID)
                    {
                        *DTCOfEvent = DemPbCfgPtr->DemDTC[DTCRef].DemDtcValue;
                        ret = E_OK;
                    }
                    break;
                case DEM_DTC_FORMAT_J1939:
                    if ((ObdDTCRef != DEM_OBD_DTC_INVALID)
                        && (pDemObdDTC[ObdDTCRef].DemJ1939DTCValue != DEM_J1939_DTC_CFG_INVALID))
                    {
                        *DTCOfEvent = pDemObdDTC[ObdDTCRef].DemJ1939DTCValue;
                        ret = E_OK;
                    }
                    break;
                default:
                    ret = DEM_E_NO_DTC_AVAILABLE;
                    break;
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
 * Brief               Sets an enable condition.
 * ServiceId           0x39
 * Sync/Async          Asynchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EnableConditionID:This parameter identifies the enable condition.
 *                       ConditionFulfilled: This parameter specifies whether the enable condition
 *                       assigned to the EnableConditionID is fulfilled
 *                       (TRUE) or not fulfilled (FALSE).
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              In case the enable condition could be set successfully the API call returns E_OK.
 *                      If the setting of the enable condition failed the return value of the
 *                      function is E_NOT_OK.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEnableCondition(uint8 EnableConditionID, boolean ConditionFulfilled)
{
    Std_ReturnType ret;
#if (DEM_ENABLE_CONDITION_NUM > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETENABLECONDITION, DEM_E_UNINIT);
    }
    else if (EnableConditionID >= DEM_ENABLE_CONDITION_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETENABLECONDITION, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        if (ConditionFulfilled == FALSE)
        {
            DEM_BITS_CLR(DemEnableConditionStatus, EnableConditionID);
        }
        else
        {
            DEM_BITS_SET(DemEnableConditionStatus, EnableConditionID);
        }
        Dem_CheckEnableCondition = TRUE;
        ret = E_OK;
    }
#else
    ret = E_NOT_OK;
    DEM_UNUSED(EnableConditionID);
    DEM_UNUSED(ConditionFulfilled);
#endif /* DEM_ENABLE_CONDITION_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Sets a storage condition.
 * ServiceId           0x38
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      StorageConditionID: This parameter identifies the storage condition.
 *                       ConditionFulfilled: This parameter specifies whether the storage condition
 *                       assigned to the StorageConditionID is fulfilled (TRUE) or not
 *                       fulfilled (FALSE).
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              In case the storage condition could be set successfully the API call
 *                      returns E_OK. If the setting of the storage condition failed the
 *                      return value of the function is E_NOT_OK.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetStorageCondition(uint8 StorageConditionID, boolean ConditionFulfilled)
{
    Std_ReturnType ret;
#if (DEM_STORAGE_CONDITION_NUM > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETSTORAGECONDITION, DEM_E_UNINIT);
    }
    else if (StorageConditionID >= DEM_STORAGE_CONDITION_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETSTORAGECONDITION, DEM_E_WRONG_CONFIGURATION);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        if (ConditionFulfilled == FALSE)
        {
            DEM_BITS_CLR(DemStorageConditionStatus, StorageConditionID);
        }
        else
        {
            DEM_BITS_SET(DemStorageConditionStatus, StorageConditionID);
        }
        Dem_CheckStorageCondition = TRUE;
        ret = E_OK;
    }
#else
    ret = E_NOT_OK;
    DEM_UNUSED(StorageConditionID);
    DEM_UNUSED(ConditionFulfilled);
#endif /* DEM_STORAGE_CONDITION_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the fault detection counter of an event.
 * ServiceId           0x3e
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      EventId : Identification of an event by assigned EventId.>
 * Param-Name[out]     FaultDetectionCounter: This parameter receives the Fault Detection Counter
 *                      information of the requested EventId. If the return value of the function
 *                      call is other than E_OK this parameter does not contain valid data.
 *                      -128dec...127dec PASSED... FAILED according to ISO 14229-1
 * Param-Name[in/out]  None
 * Return              E_OK: request was successful
 *                       E_NOT_OK: request failed
 *                       DEM_E_NO_FDC_AVAILABLE: there is no fault detection counter available
 *                       for the requested event
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_GetFaultDetectionCounter(Dem_EventIdType EventId, P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETFAULTDETECTIONCOUNTER, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETFAULTDETECTIONCOUNTER, DEM_E_WRONG_CONFIGURATION);
    }
    else if (FaultDetectionCounter == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETFAULTDETECTIONCOUNTER, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        /*SWS_Dem_01108*/
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            ret = Dem_GetInteralFDC(IntId, FaultDetectionCounter);
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the indicator status derived from the event status.
 * ServiceId           0x29
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      IndicatorId: Number of indicator
 * Param-Name[out]     IndicatorStatus: Status of the indicator, like off, on, or blinking.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful E_NOT_OK: Operation failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_GetIndicatorStatus(uint8 IndicatorId, P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret;
#if (DEM_INDICATOR_NUM > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETINDICATORSTATUS, DEM_E_UNINIT);
    }
    else if (IndicatorId >= DEM_INDICATOR_NUM)
    {
        DEM_DET_REPORT(DEM_SID_GETINDICATORSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else if (IndicatorStatus == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETINDICATORSTATUS, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        *IndicatorStatus = DemWIRStatus[IndicatorId];
        ret = E_OK;
    }
#else
    ret = E_NOT_OK;
    DEM_UNUSED(IndicatorId);
    DEM_UNUSED(IndicatorStatus);
#endif /* DEM_INDICATOR_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Sets the indicator status included in the event status.
 * ServiceId           0xa1
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      IndicatorId : Number of indicator
 *                      IndicatorStatus Status of the indicator, like off, on, or blinking.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful
 *                       E_NOT_OK: Operation failed or is not supported
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432,3673++ */ /* MISRA Rule 20.7,8.13 */
Dem_SetIndicatorStatus(uint8 IndicatorId, P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus)
/* PRQA S 3432,3673-- */ /* MISRA Rule 20.7,8.13 */
{
    Std_ReturnType ret;
#if (DEM_INDICATOR_NUM > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETINDICATORSTATUS, DEM_E_UNINIT);
    }
    else if (IndicatorId >= DEM_INDICATOR_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETINDICATORSTATUS, DEM_E_WRONG_CONFIGURATION);
    }
    else if (IndicatorStatus == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_SETINDICATORSTATUS, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        DemWIRStatus[IndicatorId] = *IndicatorStatus;
        ret = E_OK;
    }
#else
    ret = E_NOT_OK;
    DEM_UNUSED(IndicatorId);
    DEM_UNUSED(IndicatorStatus);
#endif /* DEM_INDICATOR_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
DEM_LOCAL Dem_EventMemEntryType* Dem_GetEVCOMBEntry(const uint8* pMemDest, uint16 dtcRef)
{
    const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
    Dem_EventMemEntryType* pEntry = NULL_PTR;
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
    for (uint8 index = 0; (index < DEM_MEM_DEST_MAX_NUM_OF_DTC) && (pEntry == NULL_PTR); index++)
#else
    uint8 index = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
    {
        const uint8 MemDest = pMemDest[index];
        if (MemDest != DEM_MEM_DEST_INVALID)
        {
            const Dem_EventMemEntryType* Entry = DemMemDestCfg[MemDest].EntryList;
            const uint8 EntryNum = DemMemDestCfg[MemDest].EntryNum;
            for (uint8 iloop = 0; (iloop < EntryNum) && (pEntry == NULL_PTR); iloop++)
            {
                Dem_EventIdType MemEventId = Entry[iloop].EventId;
                if ((MemEventId != 0u) && (pDemEventParameter[Dem_GetEventInternalId(MemEventId)].DemDTCRef == dtcRef))
                {
                    pEntry = Dem_MemEntryGet(MemEventId, MemDest);
                }
            }
        }
    }
    return pEntry;
}
#endif /* DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE */

/*************************************************************************/
/*
 * Brief               Gets the data of a freeze frame by event.
 * ServiceId           0x6e
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId: Identification of an event by assigned EventId.
 *                       RecordNumber: This parameter is a unique identifier for a freeze
 *                       frame record as defined in ISO15031-5 and ISO14229-1.
 *                       0xFF means most recent freeze frame record is returned.
 *                       DataId : This parameter specifies the PID (ISO15031-5 mapped in UDS range
 *                       0xF400 - 0xF4FF) or DID (ISO14229-1) that shall be copied to
 *                       the destination buffer.
 * Param-Name[out]     DestBuffer : This parameter contains a byte pointer that points to the
 *                       buffer, to which the freeze frame data record shall be written to.
 *                       The format is raw hexadecimal values and contains no header-information.
 * Param-Name[in/out]   BufSize: When the function is called this parameter contains
                            the maximum number of data bytes that can be written to the buffer.
                            The function returns the actual number of written
                            data bytes in this parameter
 * Return              E_OK: Operation was successful
 *                       DEM_E_NODATAAVAILABLE: The requested event data is not currently stored
 *                                              (but the request was valid)
 *                       DEM_E_WRONG_RECORDNUMBER: The requested record number is not supported
 *                                              by the event
 *                       DEM_E_WRONG_DIDNUMBER: The requested DID is not supported by the freeze frame
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 0624++ */ /* MISRA Rule 8.3 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFreezeFrameDataEx(
    Dem_EventIdType EventId,
    uint8 RecordNumber,
    uint16 DataId,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint16* BufSize)
/* PRQA S 0624-- */ /* MISRA Rule 8.3 */
{
    Std_ReturnType ret = E_NOT_OK;
#if ((DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u))
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTFREEZEFRAMEDATAEX, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTFREEZEFRAMEDATAEX, DEM_E_WRONG_CONFIGURATION);
    }
    else if (DestBuffer == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTFREEZEFRAMEDATAEX, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
            uint16 dtcRef = pDemEventParameter[IntId].DemDTCRef;
            const uint8* pMemDest =
                DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[dtcRef].DemDTCAttributesRef].DemMemoryDestinationRef;
            Dem_EventMemEntryType* pEntry = NULL_PTR;
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
            pEntry = Dem_GetEVCOMBEntry(pMemDest, dtcRef);
#else
            pEntry = Dem_CheckEventMemEntryExistsAlready(IntId);
#endif /* DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE */
            if (pEntry != NULL_PTR)
            {
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
                for (uint8 iloop = 0; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#else
                uint8 iloop = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
                {
                    const uint8 MemDest = pMemDest[iloop];
                    if ((MemDest != DEM_MEM_DEST_INVALID) && (MemDest != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
                        && (MemDest != DEM_DTC_ORIGIN_MIRROR_MEMORY)) /*SWS_Dem_01062 */
                    {
                        ret = Dem_FreezeFrameGetFromEntry(pEntry, RecordNumber, DataId, DestBuffer, BufSize);
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
                        break;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
                    }
                }
            }
        }
    }
#else
    DEM_UNUSED(EventId);
    DEM_UNUSED(RecordNumber);
    DEM_UNUSED(DataId);
    DEM_UNUSED(DestBuffer);
    DEM_UNUSED(BufSize);
#endif /* DEM_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0u) || (DEM_PID_CLASS_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 * Brief               Gets the data of an extended data record by event.
 * ServiceId           0x6d
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      EventId : Identification of an event by assigned EventId.
 *                       RecordNumber: Identification of requested Extended data record.
 *                       Valid values are between 0x01 and 0xEF as defined in ISO14229-1.
 * Param-Name[out]     DestBuffer: This parameter contains a byte pointer that points
 *                          to the buffer, to which the extended data shall bewritten to.
 *                          The format is raw hexadecimal values and contains no header-information.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful
 *                       DEM_E_NODATAAVAILABLE: The requested event data is not currently
 *                              stored (but the request was valid)
 *                       DEM_E_WRONG_RECORDNUMBER: The requested record number is not supported by the event
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 0624++ */ /* MISRA Rule 8.3 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventExtendedDataRecordEx(
    Dem_EventIdType EventId,
    uint8 RecordNumber,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint16* BufSize)
/* PRQA S 0624-- */ /* MISRA Rule 8.3 */
{
    Std_ReturnType ret = E_NOT_OK;
#if (DEM_EXTENDED_DATA_CLASS_NUM > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTEXTENDEDDATARECORDEX, DEM_E_UNINIT);
    }
    else if ((EventId > DEM_EVENT_PARAMETER_NUM) || (EventId == 0u))
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTEXTENDEDDATARECORDEX, DEM_E_WRONG_CONFIGURATION);
    }
    else if (DestBuffer == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTEXTENDEDDATARECORDEX, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_EventIdType IntId = Dem_GetEventInternalId(EventId);
        const Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(IntId);
        if (0x00u != DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE))
        {
            const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
            uint16 dtcRef = pDemEventParameter[IntId].DemDTCRef;
            const uint8* pMemDest =
                DemPbCfgPtr->DemDTCAttributes[DemPbCfgPtr->DemDTC[dtcRef].DemDTCAttributesRef].DemMemoryDestinationRef;
            const Dem_EventMemEntryType* pEntry = NULL_PTR;
#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_ONSTORAGE)
            pEntry = Dem_GetEVCOMBEntry(pMemDest, dtcRef);
#else
            pEntry = Dem_CheckEventMemEntryExistsAlready(IntId);
#endif
            if (pEntry != NULL_PTR)
            {
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
                for (uint8 iloop = 0; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#else
                uint8 iloop = 0;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
                {
                    const uint8 MemDest = pMemDest[iloop];
                    if ((MemDest != DEM_MEM_DEST_INVALID) && (MemDest != DEM_DTC_ORIGIN_PERMANENT_MEMORY)
                        && (MemDest != DEM_DTC_ORIGIN_MIRROR_MEMORY)) /*SWS_Dem_01062 */
                    {
                        ret = Dem_ExtendedDataGetFromEntry(pEntry, RecordNumber, DestBuffer, BufSize);
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
                        break;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
                    }
                }
            }
        }
    }
#else
    DEM_UNUSED(EventId);
    DEM_UNUSED(RecordNumber);
    DEM_UNUSED(DestBuffer);
    DEM_UNUSED(BufSize);
#endif /* DEM_EXTENDED_DATA_CLASS_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Gets the event memory overflow indication status.
 * ServiceId           0x32
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DTCOrigin: If the Dem supports more than one event memory this parameter
 *                          is used to select the source memory the overflow indication shall be read from.>
 * Param-Name[out]     OverflowIndication: This parameter returns TRUE if the according
 *                          event memory was overflowed, otherwise it returns FALSE.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful
 *                       E_NOT_OK: Operation failed or is not supported
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
Dem_GetEventMemoryOverflow(Dem_DTCOriginType DTCOrigin, P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) OverflowIndication)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTMEMORYOVERFLOW, DEM_E_UNINIT);
    }
    else if (OverflowIndication == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETEVENTMEMORYOVERFLOW, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        uint8 memDest = Dem_GetInternalMemDest(DTCOrigin);
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        if (memDest == DEM_MEM_DEST_INVALID)
        {
            DEM_DET_REPORT(DEM_SID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONFIGURATION);
        }
        else
#endif    /* STD_ON == DEM_DEV_ERROR_DETECT */
        { /*SWS_Dem_00398*/
            *OverflowIndication = DemMemDestInfo[memDest].OverFlow;
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Returns the number of entries currently stored in the requested event memory.
 * ServiceId           0x35
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DTCOrigin: If the Dem supports more than one event memory
 *                          this parameter is used to select the source memory
 *                          the number of entries shall be read from.
 * Param-Name[out]     NumberOfEventMemoryEntries: Number of entries currently stored in the
 *                          requested event memory.
 * Param-Name[in/out]  None
 * Return              E_OK: Operation was successful E_NOT_OK: Operation failed
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfEventMemoryEntries(
    Dem_DTCOriginType DTCOrigin,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) NumberOfEventMemoryEntries) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_GETNUMBEROFEVENTMEMORYENTRIES, DEM_E_UNINIT);
    }
    else if (NumberOfEventMemoryEntries == NULL_PTR)
    {
        DEM_DET_REPORT(DEM_SID_GETNUMBEROFEVENTMEMORYENTRIES, DEM_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        uint8 memDest = Dem_GetInternalMemDest(DTCOrigin);
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        if (memDest == DEM_MEM_DEST_INVALID)
        {
            DEM_DET_REPORT(DEM_SID_GETNUMBEROFEVENTMEMORYENTRIES, DEM_E_WRONG_CONFIGURATION);
        }
        else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
        {
            /*SWS_Dem_00651*/
            *NumberOfEventMemoryEntries = DemMemDestInfo[memDest].RecordNum;
            ret = E_OK;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Set the availability of a specific DemComponent.
 * ServiceId           0x2b
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ComponentId: Identification of a DemComponent.
 *                       AvailableStatus: This parameter specifies whether the respective
 *                          Component shall be available (TRUE) or not (FALSE).
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              E_OK: Operation was successful
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE) Dem_SetComponentAvailable(Dem_ComponentIdType ComponentId, boolean AvailableStatus)
{
    Std_ReturnType ret;
#if (DEM_COMPONENT_NUM > 0u)
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETCOMPONENTAVAILABLE, DEM_E_UNINIT);
    }
    else if (ComponentId > DEM_COMPONENT_NUM)
    {
        DEM_DET_REPORT(DEM_SID_SETCOMPONENTAVAILABLE, DEM_E_WRONG_RECORDNUMBER);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_ComponentIdType InComponentId = Dem_GetEventInternalId(ComponentId);
        /*SWS_Dem_01135 */
        DemComponentStatus[InComponentId].availability = AvailableStatus;
        /*SWS_Dem_01136*/
        if (AvailableStatus == FALSE)
        {
            const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
            for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
            {
                Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
                if (pDemEventParameter[iloop].DemComponentClassRef == InComponentId)
                {
                    if ((NULL_PTR == Dem_CheckEventMemEntryExistsAlready(iloop))
                        && (DEM_FLAGS_ISSET(pEvent->UdsStatus, DEM_UDS_STATUS_TF) == 0x00u))
                    {
                        DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_AVAILABLE);
                    }
                }
            }
        }
        ret = E_OK;
    }
#else
    ret = E_NOT_OK;
    DEM_UNUSED(ComponentId);
    DEM_UNUSED(AvailableStatus);
#endif /* DEM_COMPONENT_NUM > 0u */
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
/*************************************************************************/
/*
 * Brief               Set the suppression status of a specific DTC.
 * ServiceId           0x33
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      DTC: Diagnostic Trouble Code
 *                       DTCFormat: Defines the input-format of the provided DTC value.
 *                       SuppressionStatus: This parameter specifies whether the respective
 *                       DTC shall be disabled (TRUE) or enabled (FALSE).
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              E_OK (Operation was successful)
 *                       E_NOT_OK (operation failed or event entry for this DTC still exists)
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCSuppression(uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus)
{
    Std_ReturnType res = E_NOT_OK;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_SETDTCSUPPRESSION, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        uint16 DTCRef = Dem_GetDTCIndex(DTC, DTCFormat);
        if (DEM_DTC_REF_INVALID != DTCRef)
        {
            const Dem_DTCType* pDemDTC = &DemPbCfgPtr->DemDTC[DTCRef];
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
            const Dem_EventIdType EventRefNum = pDemDTC->EventRefNum;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
            const Dem_EventIdType EventRefStart = pDemDTC->EventRefStart;
            const Dem_EventIdType* pDTCMapping = &DemPbCfgPtr->DemDTCMapping[EventRefStart];
            res = E_OK;
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
            for (uint16 iloop = 0u; iloop < EventRefNum; iloop++)
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
            {
                if (NULL_PTR != Dem_CheckEventMemEntryExistsAlready(*pDTCMapping))
                {
                    res = E_NOT_OK;
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                    break;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
                }
#if (DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON)
                pDTCMapping++;
#endif /* DEM_ONEDTCMAPPINGMUTILEVENT == STD_ON */
            }
            if (E_OK == res)
            {
                DemDTCGeneralStatus[DTCRef].SuppressionStatus = SuppressionStatus;
            }
        }
#if (STD_ON == DEM_DEV_ERROR_DETECT)
        else
        {
            DEM_DET_REPORT(DEM_SID_SETDTCSUPPRESSION, DEM_E_WRONG_RECORDNUMBER);
        }
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif

/*************************************************************************/
/*
 * Brief               Clears single DTCs, as well as groups of DTCs. This API is intended
                       for complex device driver. It can only be used through the RTE (due
                       to work-around described below SWS_Dem_00659), and therefore no
                       declaration is exported via Dem.h.
 * ServiceId           0x23
 * Sync/Async          Asynchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DTC:Defines the DTC in respective format, that shall be
 *                          cleared from the event memory. If the DTC fits to a
 *                          DTC group number, all DTCs of the group shall be cleared.
 *                       DTCFormat:Defines the input-format of the provided DTC value.
 *                       DTCOrigin:If the Dem supports more than one event memory
 *                          this parameter is used to select the source memory
 *                          the DTCs shall be read from.
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              Status of the operation of type Dem_ReturnClearDTCType.
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 0624++ */ /* MISRA Rule 8.3 */
FUNC(Dem_ReturnClearDTCType, DEM_CODE)
Dem_ClearDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
/* PRQA S 0624-- */ /* MISRA Rule 8.3 */
{
    Dem_ReturnClearDTCType ret = DEM_CLEAR_FAILED;
#if (STD_ON == DEM_DEV_ERROR_DETECT)
    if (Dem_InitState != DEM_STATE_INIT)
    {
        DEM_DET_REPORT(DEM_SID_CLEARDTC, DEM_E_UNINIT);
    }
    else
#endif /* STD_ON == DEM_DEV_ERROR_DETECT */
    {
        Dem_ClearDTCInfoType* pClr = &DemClearDTCInfo;
        uint16 DTCRef = Dem_GetDTCIndex(DTC, DTCFormat);
        if (Dem_ClearDTCLock == DEM_CLEAR_LOCK)
        {
            ret = ((pClr->SaveDTCIndex == DTCRef) && (pClr->SaveDTCFormat == DTCFormat)
                   && (pClr->SaveDTCOrigin == DTCOrigin) && (pClr->SID == DEM_SID_CLEARDTC))
                      ? DEM_CLEAR_PENDING
                      : DEM_CLEAR_BUSY;
        }
        else
        {
            if (Dem_ClearDTCLock == DEM_CLEAR_NOT_LOCK)
            {
                Dem_ClearDTCLock = DEM_CLEAR_LOCK; /*SWS_Dem_00661*/
                pClr->DTCIndex = DTCRef;
                pClr->DTCFormat = DTCFormat;
                pClr->DTCOrigin = DTCOrigin;
                pClr->SaveDTCIndex = DTCRef;
                pClr->SaveDTCFormat = DTCFormat;
                pClr->SaveDTCOrigin = DTCOrigin;
                pClr->SID = DEM_SID_CLEARDTC;
            }
            /*SWS_Dem_00670 */
#if (DEM_CLEAR_DTCLIMITATION == DEM_ONLY_CLEAR_ALL_DTCS)
            if ((DTCFormat != DEM_DTC_FORMAT_UDS) || (DTC != 0xFFFFFFuL))
            {
                Dem_ResetDemClearDTCInfo();
                ret = DEM_CLEAR_WRONG_DTC;
            }
            else
#endif /* DEM_CLEAR_DTCLIMITATION == DEM_ONLY_CLEAR_ALL_DTCS */
            {
                uint8 lDTCOrigin = Dem_GetInternalMemDest(DTCOrigin);
                if (lDTCOrigin == DEM_MEM_DEST_INVALID)
                {
                    Dem_ResetDemClearDTCInfo();
                    ret = DEM_CLEAR_WRONG_DTCORIGIN;
                }
                else
                {
                    boolean rocessOn = TRUE;
                    if (DTC == 0xFFFFFFUL)
                    {
                        pClr->ClearAllGroup = TRUE;
                    }
#if (DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS)
                    else
                    {
                        pClr->ClearAllGroup = FALSE;
#if (DEM_GROUP_OF_DTC_NUM > 0u)
                        pClr->DTCGroupIndex = Dem_GetDTCGroupIndex(DTC);
                        if (pClr->DTCGroupIndex == DEM_GROUP_OF_DTC_INVALID)
#endif /* DEM_GROUP_OF_DTC_NUM > 0u */
                        {
                            pClr->DTCIndex = DTCRef;
                            if (pClr->DTCIndex == DEM_DTC_REF_INVALID)
                            {
                                Dem_ResetDemClearDTCInfo();
                                rocessOn = FALSE;
                                ret = DEM_CLEAR_WRONG_DTC;
                            }
                        }
                    }
#endif /* DEM_CLEAR_DTCLIMITATION == DEM_ALL_SUPPORTED_DTCS */
                    if (TRUE == rocessOn)
                    {
                        pClr->memDest = lDTCOrigin;
                        Dem_Pending = TRUE;
                        Dem_ClearDTCProcess();
#if (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_VOLATILE)
                        /*SWS_Dem_00570*/
                        Dem_ResetDemClearDTCInfo();
                        ret = DEM_CLEAR_OK;
#elif (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
                        /*SWS_Dem_00571*/
                        Dem_ClearNonvolatileStatus = DEM_CLEAR_NONVOLATILE_START;
                        Dem_ResetDemClearDTCInfo();
                        ret = DEM_CLEAR_OK;
#elif (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
                        /*SWS_Dem_00663*/
                        Dem_ClearNonvolatileStatus = DEM_CLEAR_NONVOLATILE_START;
                        ret = DEM_CLEAR_PENDING;
#endif /* DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_VOLATILE */
                    }
                }
            }
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_NVRAM_BLOCKID_NUM > 0u)
/*************************************************************************/
/*
 * Brief               check if non-volatile event memory data cleared.
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
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ClearNonvolatile(void)
{
#if (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    uint8 blockIndex;
    NvM_RequestResultType RequestResult;
#endif

    if (Dem_ClearNonvolatileStatus == DEM_CLEAR_NONVOLATILE_START)
    {
        /*clear done ,to write*/
        Dem_IntWriteNvRAM();
#if (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
        Dem_ClearNonvolatileStatus = DEM_CLEAR_NONVOLATILE_PROCESSING;
#else
        Dem_ClearNonvolatileStatus = DEM_ClEAR_NONVOLATILE_INIT;
#endif
    }
#if (DEM_CLEAR_DTCBEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    if (Dem_ClearNonvolatileStatus == DEM_CLEAR_NONVOLATILE_PROCESSING)
    {
        for (blockIndex = Dem_ClearCnt; blockIndex < DEM_NVRAM_BLOCKID_NUM; blockIndex++)
        {
            NvM_GetErrorStatus(DemNvRamBlockId[blockIndex], &RequestResult);
            if (RequestResult == NVM_REQ_OK)
            {
                Dem_ClearCnt++;
            }
            else if (RequestResult == NVM_REQ_PENDING)
            {
                break;
            }
            else
            {
                Dem_ClearCnt = 0;
                Dem_ClearNonvolatileStatus = DEM_ClEAR_NONVOLATILE_FAILED;
                break;
            }
        }
        if (Dem_ClearCnt == DEM_NVRAM_BLOCKID_NUM)
        {
            Dem_ClearCnt = 0;
            Dem_ClearNonvolatileStatus = DEM_ClEAR_NONVOLATILE_FINISHED;
        }
    }
#endif
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */

/********[Scheduled functions]*********/
/*************************************************************************/
/*
 * Brief               Processes all not event based Dem internal functions.
 * ServiceId           0x55
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
FUNC(void, DEM_CODE) Dem_MainFunction(void)
{
    if (Dem_InitState == DEM_STATE_INIT)
    {
#if (DEM_ENABLE_CONDITION_NUM > 0u)
        if (Dem_CheckEnableCondition != FALSE)
        {
            Dem_CheckEnableCondition = FALSE;
            Dem_SetEnableCondictionProcess();
        }
#endif /* DEM_ENABLE_CONDITION_NUM > 0u */
#if (DEM_STORAGE_CONDITION_NUM > 0u)
        if (Dem_CheckStorageCondition != FALSE)
        {
            Dem_CheckStorageCondition = FALSE;
            Dem_SetStorageCondictionProcess();
        }
#endif /* DEM_STORAGE_CONDITION_NUM > 0u */
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u)
        Dem_DebounceTimerMain();
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u */
        Dem_EventQueueProcess();
#if (DEM_NVRAM_BLOCKID_NUM > 0u)
        Dem_ClearNonvolatile();
#endif /* DEM_NVRAM_BLOCKID_NUM > 0u */
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/********[I N T E R N A L F U N C T I O N   I M P L E M E N T A T I O N S]*****/
#if (DEM_ENABLE_CONDITION_NUM > 0)
/*************************************************************************/
/*
 * Brief               BRIEF DESCRIPTION
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_SetEnableCondictionProcess(void)
{
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
        boolean IsFulfilled = TRUE;
        const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
        const uint8 DemEnableConditionGroupRef = pDemEventParameter[iloop].DemEnableConditionGroupRef;
        if (DemEnableConditionGroupRef != DEM_ENABLE_CONDITION_GROUP_INVALID)
        {
            const uint8* pGroup = &DemEnableConditionGroup[DemEnableConditionGroupRef][0];
            IsFulfilled = Dem_CheckCondictionFulfilled(DemEnableConditionStatus, pGroup, DEM_ENABLE_CONDITION_NUM_BYTE);
        }
        if (IsFulfilled == TRUE)
        {
            if (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION))
            {
                /* req SWS_Dem_00681 Monitor re-initialization  */
                const Dem_CallbackInitMForEType InitMForEFnc = pDemEventParameter[iloop].DemCallbackInitMForE;
                DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION);
                if (InitMForEFnc != NULL_PTR)
                {
                    (void)InitMForEFnc(DEM_INIT_MONITOR_REENABLED);
                }
            }
        }
        else
        {
            DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_ENABLED_CONDICTION);
            Dem_DebounceFreeze(iloop); /*SWS_Dem_00655*/
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif
#if (DEM_STORAGE_CONDITION_NUM > 0)
/*************************************************************************/
/*
 * Brief               Dem_SetStorageCondictionProcess
 * ServiceId           --
 * Sync/Async          Synchronous-
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_SetStorageCondictionProcess(void)
{
    for (uint16 iloop = 0; iloop < DEM_EVENT_PARAMETER_NUM; iloop++)
    {
        Dem_EventRelateInformationType* pEvent = Dem_GetEventInfo(iloop);
        boolean IsFulfilled = TRUE;
        const Dem_EventParameterType* pDemEventParameter = DemPbCfgPtr->DemEventParameter;
        const uint8 GroupRef = pDemEventParameter[iloop].DemStorageConditionGroupRef;
        if (GroupRef != DEM_STORAGE_CONDITION_GROUP_INVALID)
        {
            const uint8* pGroup = &DemStorageConditionGroup[GroupRef][0];
            IsFulfilled =
                Dem_CheckCondictionFulfilled(DemStorageConditionStatus, pGroup, DEM_STORAGE_CONDITION_NUM_BYTE);
        }
        if (IsFulfilled == TRUE)
        {
            if (0x00u == DEM_FLAGS_ISSET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION))
            {
                boolean IsReplacement = FALSE;
                uint8 Conindex = 0;
                DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION);
                /*SWS_Dem_01089 */
                /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                for (uint8 index = 0; (index < DEM_STORAGE_CONDITION_NUM_BYTE) && (IsReplacement == FALSE); index++)
                /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                {
                    uint8 Counter = 0;
                    uint8 Mask = 0x01;
                    /* PRQA S 2877++ */ /* MISRA Dir 4.1 */
                    for (; (Conindex < DEM_STORAGE_CONDITION_NUM) && (IsReplacement == FALSE) && (Counter < 8u);
                         Conindex++)
                    /* PRQA S 2877-- */ /* MISRA Dir 4.1 */
                    {
                        const uint16 EventRef = DemStorageCondition[Conindex].DemStorageConditionReplacementEventRef;
                        if (((DemStorageConditionGroup[GroupRef][index] & Mask) != 0u)
                            && (EventRef != DEM_EVENT_PARAMETER_INVALID))
                        {
                            const Dem_CallbackInitMForEType InitMForE = pDemEventParameter[iloop].DemCallbackInitMForE;
                            (void)Dem_EventQueueAdd(Dem_GetEventExternalId(EventRef), DEM_EVENT_STATUS_PASSED);
                            /* SWS_Dem_01113  Monitor re-initialization  */
                            if (InitMForE != NULL_PTR)
                            {
                                (void)InitMForE(DEM_INIT_MONITOR_STORAGE_REENABLED);
                            }
                            IsReplacement = TRUE; /* PRQA S 2982 */ /* MISRA Rule 2.2 */
                        }
                        Counter++; /* PRQA S 2982 */         /* MISRA Rule 2.2 */
                        Mask = Mask << 1u; /* PRQA S 2982 */ /* MISRA Rule 2.2 */
                    }
                }
            }
        }
        else
        {
            DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_STORAGE_CONDICTION);
        }
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif

/*************************************************************************/
/*
 * Brief               Dem_ProcessEventStatus
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEvent
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ProcessEventStatus(
    Dem_EventStatusType EventStatus,
    P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
    uint8 OldStatus = pEvent->UdsStatus;
    uint8 NewStatus;
#endif /* DEM_TRIGGER_FIM_REPORTS == STD_ON */
    const Dem_ProcessEventPtr Dem_ProcessEventFuncMatrix[] = {
        &Dem_EventQueueAddDebouncePassed,
        &Dem_EventQueueAddDebounceFailed,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    };
    /* SWS_Dem_00036 */
    Dem_ProcessEventPtr processFnc = Dem_ProcessEventFuncMatrix[EventStatus];
    if (NULL_PTR != processFnc)
    {
        (*processFnc)(pEvent);
    }
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
    NewStatus = pEvent->UdsStatus;
    if (OldStatus != NewStatus)
    {
        (void)FiM_DemTriggerOnEventStatus(Dem_GetEventExternalId(pEvent->IntId), OldStatus, NewStatus);
    }
#endif /* DEM_TRIGGER_FIM_REPORTS == STD_ON */
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/
