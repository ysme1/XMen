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
 **  FILENAME    : Dem_Internal.h                                              **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      : i-soft                                                      **
 **  DESCRIPTION : API declaration of DEM for internal                         **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef DEM_INTERNAL_H_
#define DEM_INTERNAL_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem.h"

/*******************************************************************************
**                      macros                                                **
*******************************************************************************/
/* Dem InitState Define  */
typedef enum
{
    DEM_STATE_UNINIT = 0u,
    DEM_STATE_PRE_INIT,
    DEM_STATE_INIT,
    DEM_STATE_SHUTDOWN
} Dem_StateType;

typedef enum
{
    DEM_CLEAR_LOCK = 0u,
    DEM_CLEAR_NOT_LOCK
} Dem_ClearLockStatus;

typedef enum
{
    DEM_ClEAR_NONVOLATILE_FINISHED = 0u,
    DEM_ClEAR_NONVOLATILE_FAILED,
    DEM_ClEAR_NONVOLATILE_INIT,
    DEM_CLEAR_NONVOLATILE_PROCESSING,
    DEM_CLEAR_NONVOLATILE_START
} Dem_ClearNonvolatileStatusType;

typedef struct
{
    uint16 DTCIndex;
    uint16 SaveDTCIndex;
    boolean ClearAllGroup;
    uint8 DTCGroupIndex;
    uint8 memDest;
    uint32 DTC;
    Dem_DTCFormatType DTCFormat;
    Dem_DTCFormatType SaveDTCFormat;
    Dem_DTCOriginType DTCOrigin;
    Dem_DTCOriginType SaveDTCOrigin;
    uint16 SID;
    Dem_J1939DcmSetClearFilterType DTCTypeFilter;
    uint8 node;
} Dem_ClearDTCInfoType;

typedef struct
{
    uint8 Occctr;
    uint8 AgingUpCnt;
    uint8 AgingDownCnt;
    uint8 Ovflind;
    uint8 Significance;
    uint8 CurrentFDC;
#if (DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON)
    uint8 MaxFDCSinceLastClear;
#endif /* DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON */
    uint8 MaxFDCDuringCurrentCycle;
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
    uint8 CyclesSinceLastFailed;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
    uint8 CyclesSinceFirstFailed;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
    uint8 FailedCycles;
#if (DEM_OCC6EANLE == STD_ON)
    uint8 OCC6;
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
    uint8 OCC4;
#endif /* DEM_OCC4EANLE == STD_ON */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    uint8 StatusIndicator30;
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
} Dem_InternalDataType;

typedef struct
{
    Dem_EventIdType IntId;
    uint8 Status;
    uint8 EventStatusFlag;
    uint8 UdsStatus;
    uint8 OldUdsStatus;
    /* Counters */
    uint8 OccurrenceCounter; /*SWS_Dem_00011] */
    uint8 FailureCounter;
#if (DEM_OCC6EANLE == STD_ON)
    uint8 OCC6;
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
    uint8 OCC4;
#endif /* DEM_OCC4EANLE == STD_ON */
    uint8 AgingCounter;
    uint8 HealingCounter;
    /* Operation Cycle Counter */
#if (DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON)
    uint8 CyclesSinceFirstFailed;
#endif /* DEM_CYCLESSINCEFRISTFAILEDEANLE == STD_ON */
#if (DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON)
    uint8 CyclesSinceLastFailed;
#endif /* DEM_CYCLESSINCELASTFAILEDEANLE == STD_ON */
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    uint8 StatusIndicator30;
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
} Dem_EventRelateInformationType;

typedef struct
{
    uint8 CbUdsStatus;
    boolean SuppressionStatus;
} Dem_DTCGeneralStatusType;

typedef struct
{
    uint8 RecordNum;
    uint8 DisableDTCRecordUpdate[DEM_DTC_NUM_BYTE]; /* 1, Disable, 0:Enable */
    boolean OverFlow;
} Dem_MemDestInfoType;

#if (DEM_NVRAM_BLOCKID_NUM > 0)
typedef struct
{
    uint8 UdsStatus[DEM_EVENT_PARAMETER_NUM];
#if (DEM_MAXFDCSINCELASTCLEAR_EANLE == STD_ON)
    uint8 MaxFDCSinceLastClear[DEM_DTC_NUM];
#endif
    sint16 DebounceCounter[DEM_EVENT_PARAMETER_NUM];
#if (DEM_OPERATION_CYCLE_STATUS_STORAGE == STD_ON)
    uint8 DemOperationCycleStatus[DEM_OPERATION_CYCLE_NUM_BYTE]; /*SWS_Dem_00577]*/
#endif
    Dem_EventIdType FirstFailed;
    Dem_EventIdType MostRecentFailed;
    Dem_EventIdType FirstDtcConfirmed;
    Dem_EventIdType MostRecDtcConfirmed;
#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    uint8 StatusIndicator30[DEM_EVENT_PARAMETER_NUM];
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */
} Dem_EventRelateInformationStorageType;

typedef struct
{
    uint16 IgnUpCycleCounter;
    uint8 WarmUpCycleCounter;
    uint16 OBDDistanceMILOn;
    uint16 DistSinceDtcCleared;
    uint16 OBDTimeMILOn;
    uint16 OBDTimeDTCClear;
    uint16 ContinuousMICounter;
    uint16 OBDB1Counter;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
    uint16 MasterContinuousMICounter;
#endif
} DemOBDDataStorageType;
#endif /* DEM_NVRAM_BLOCKID_NUM > 0 */

typedef struct
{
    boolean Status;
    uint8 FailurePriority;
    boolean availability;
} DemComponentStatusType;

typedef struct
{
    boolean IUMPRDenStatus;
    boolean IUMPRNumStatus;
    uint16 Denominator; /*the number of times the vehicle operation conditions have been fulfilled */
    uint16 Numerator;   /*the number of times a fault could have been found*/
    uint16 General_Denominator;
} IUMPRType;

typedef struct
{
    sint32 TestResult;
    sint32 LowerLimit;
    sint32 UpperLimit;
} DTRInfoType;

typedef struct
{
    /* EventId, Status: Dem_ReportErrorStatus/Dem_SetEventStatus()*/
    Dem_EventIdType ExtId;
    Dem_EventStatusType Status;
} Dem_EventDataBufferType;

/* Debounce Counter Base Info Define */
typedef struct
{
    sint16 InternalDebounceCounter;
} Dem_DebounceCounterInfoType;

/* Debounce Time Base Info Define */
typedef struct
{
    uint64 Timeout;
    boolean Triggered;
    Dem_EventIdType IntId;
    Dem_EventStatusType CurStatus;
    boolean IsFreezing;
} Dem_DebounceTimeInfoType;

typedef struct
{
    sint8 FDC;
    uint8 MaxFDCSinceLastClear;
    uint8 MaxFDCDuringCurrentCycle;
} FDCInfoType;

typedef struct
{
    Dem_EventIdType ExtId;
    uint8 FFData[DEM_FREEZE_FRAME_MAX_LEN];
} Dem_PreStoreFFInfoType;

/* DTCByOccurrenceTime */
typedef struct
{
    Dem_EventIdType FirstFailed;
    Dem_EventIdType MostRecentFailed;
    Dem_EventIdType FirstDtcConfirmed;
    Dem_EventIdType MostRecDtcConfirmed;
} Dem_DTCByOccurrenceTimeType;

/*
 * Function Pointer type define, with void return value.
 */
typedef P2FUNC(void, NVM_CODE, Dem_ProcessEventPtr)(Dem_EventRelateInformationType* pEvent);

/* Check Event Lock Status */
#define DEM_CHECK_ELOCK_ALL                  0xFFu
#define DEM_CHECK_ELOCK_OPCYC                0x01u
#define DEM_CHECK_ELOCK_ENABLECOND           0x02u
#define DEM_CHECK_ELOCK_DTCSETTING           0x04u
#define DEM_CHECK_ELOCK_AVAILABLE            0x08u
#define DEM_CHECK_ELOCK_COMPONENT            0x10u

#define DEM_CHECK_ELOCK_EXP_OPCYC            0xFEu
#define DEM_CHECK_ELOCK_EXP_ENABLECOND       0xFDu
#define DEM_CHECK_ELOCK_EXP_OPCYC_ENABLECOND 0xFCu

static inline Dem_EventIdType Dem_GetEventInternalId(Dem_EventIdType ExtId)
{
    return ((ExtId)-1u);
}
static inline Dem_EventIdType Dem_GetEventExternalId(Dem_EventIdType ExtId)
{
    return ((ExtId) + 1u);
}

#if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER)
#define DEM_EVENT_QUEUE_SIZE DEM_BSW_ERROR_BUFFER_SIZE
#else
#define DEM_EVENT_QUEUE_SIZE DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER
#endif

static inline uint8 DEM_FLAGS_ISSET(uint8 status, uint8 val)
{
    return ((status) & (val));
}
/* FLAGS*/
#define DEM_FLAGS_SET(status, val) (status) |= (val)
#define DEM_FLAGS_CLR(status, val) (status) &= (uint8)(~(val))

/* Status Bits Functions */
/* p = &uint8_array[0] */
static inline void DEM_BITS_SET(uint8* p, uint32 n)
{
    ((p)[((n) >> 3u)] |= ((uint8)(1u << ((n) & 7u))));
}
static inline void DEM_BITS_CLR(uint8* p, uint32 n)
{
    ((p)[((n) >> 3u)] &= ((uint8)(~((uint8)(1u << ((n) & 7u))))));
}
static inline boolean DEM_BITS_ISSET(const uint8* p, uint32 n)
{
    return (0x0u != ((p)[((n) >> 3u)] & ((uint8)(1u << ((n) & 7u)))));
}

static inline boolean DEM_BITS_ISNSET(const uint8* p, uint32 n)
{
    return (0x0u == ((p)[((n) >> 3u)] & ((uint8)(1u << ((n) & 7u)))));
}

#define DEM_NUMBER_OF_READINESS_GROUPS_FOROBD 12u

/*Dem_EventRelateInformationType Status*/
#define DEM_EVENT_STATUS_DTC_SETTING        0x01u
#define DEM_EVENT_STATUS_FDC_TRIGGERED      0x02u
#define DEM_EVENT_STATUS_ENABLED_CONDICTION 0x04u
#define DEM_EVENT_STATUS_STORAGE_CONDICTION 0x08u
#define DEM_EVENT_STATUS_AVAILABLE          0x10u
#define DEM_EVENT_STATUS_TFBITCHANGE        0x20u
#define DEM_EVENT_STATUS_CONSECUTIVE_FAULT  0x40u
#define DEM_EVENT_STATUS_ACTIVE             0x80u

/*Dem_EventRelateInformationType Status*/
#define DEM_EVENT_FLAGS_FDC_TRIGGER    0x01u
#define DEM_EVENT_FLAGS_THISOPISFAILED 0x02u
#define DEM_EVENT_FLAGS_CYCLECOUNTER   0x04u
#define DEM_EVENT_FLAGS_OCC6CLR        0x08u

#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
#define DEM_SI30_DTC_UC     0x01u /*bit 0: UnconfirmedDTC*/
#define DEM_SI30_DTC_UCTOC  0x02u /*bit 1: UnconfirmedDTCThisOperationCyle*/
#define DEM_SI30_DTC_UCSLC  0x04u /*bit 2: UnconfirmedDTCSinceLastClear*/
#define DEM_SI30_DTC_AGED   0x08u /*bit 3: AgedDTC*/
#define DEM_SI30_DTC_SSLC   0x10u /*bit 4: SymptomSinceLastClear*/
#define DEM_SI30_DTC_WIRSLC 0x20u /*bit 5: WarningIndicatorRequestedSinceLastClear*/
#define DEM_SI30_DTC_ER     0x40u /*bit 6: EmissionRelatedDTC*/
#define DEM_SI30_DTC_TSFLC  0x80u /*bit 7: TestFailedSinceLastClear/Aged*/
#endif                            /* DEM_STATUSINDICATOR30ENABLE == STD_ON */

/* total length = priEntry + perEntry + eventdata + obddata + crc*/
#define ENTRY_STORAGE_LEN       (sizeof(Dem_EventMemEntryType))
#define ENTRY_STORAGE_NUM       (DEM_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT)
#define TOTAL_ENTRY_STORAGE_LEN (ENTRY_STORAGE_LEN * ENTRY_STORAGE_NUM) /*ENTRY_STORAGE_LEN * ENTRY_STORAGE_NUM*/

#if !defined(DEM_LOCAL)
#define DEM_LOCAL static
#endif

#if !defined(DEM_LOCAL_INLINE)
#define DEM_LOCAL_INLINE static inline
#endif

/*******************************************************************************
**                      Global Variable declaration                           **
*******************************************************************************/

extern P2CONST(Dem_ConfigType, AUTOMATIC, DEM_CONST_PBCFG) DemPbCfgPtr;

extern VAR(boolean, AUTOMATIC) Dem_Pending;

extern VAR(Dem_StateType, AUTOMATIC) Dem_InitState;

extern VAR(FDCInfoType, AUTOMATIC) FDCInfo[DEM_DTC_NUM];
extern VAR(Dem_InternalDataType, AUTOMATIC) DemInternalData;
extern VAR(Dem_ClearDTCInfoType, AUTOMATIC) DemClearDTCInfo;
extern VAR(Dem_MemDestInfoType, AUTOMATIC) DemMemDestInfo[DEM_MEM_DEST_TOTAL_NUM];
extern VAR(Dem_EventRelateInformationType, AUTOMATIC) DemEventRelateInformation[DEM_EVENT_PARAMETER_NUM];
extern VAR(Dem_DTCGeneralStatusType, AUTOMATIC) DemDTCGeneralStatus[DEM_DTC_NUM];
#if (DEM_STORAGE_CONDITION_NUM > 0)
extern VAR(uint8, AUTOMATIC)
    DemStorageConditionStatus[DEM_STORAGE_CONDITION_NUM_BYTE]; /* Storage Conditions Status Define */
#endif
#if (DEM_ENABLE_CONDITION_NUM > 0)
extern VAR(uint8, AUTOMATIC)
    DemEnableConditionStatus[DEM_ENABLE_CONDITION_NUM_BYTE]; /* Enable Conditions Status Define */
#endif
#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
extern VAR(Dem_DebounceTimeInfoType, AUTOMATIC) DemDebounceTimerInfo[DEM_DEBOUNCE_TIME_BASED_EVENT_NUM];
#endif
#if (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0)
extern VAR(Dem_DebounceCounterInfoType, AUTOMATIC) DemDebounceCounterInfo[DEM_DEBOUNCE_COUNTER_BASED_EVENT_NUM];
#endif
#if (DEM_INDICATOR_NUM > 0)
extern VAR(Dem_IndicatorStatusType, AUTOMATIC) DemWIRStatus[DEM_INDICATOR_NUM];
#endif
#if (DEM_COMPONENT_NUM > 0)
extern VAR(DemComponentStatusType, AUTOMATIC) DemComponentStatus[DEM_COMPONENT_NUM];
#endif
#if (DEM_RATIO_NUM > 0)
extern IUMPRType IUMPRValue[DEM_RATIO_NUM];
#endif

extern VAR(boolean, AUTOMATIC) Dem_DTCStatusChangedInd;

extern VAR(uint8, AUTOMATIC) DemOperationCycleStatus[DEM_OPERATION_CYCLE_NUM_BYTE]; /* OperationCycleStatus */

extern VAR(Dem_ClearLockStatus, AUTOMATIC) Dem_ClearDTCLock;

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)

extern Dem_IndicatorStatusType OBDMilStatus;
extern uint16 OBDDistanceMILOn;
extern uint16 OBDTimeMILOn;
extern uint16 OBDTimeDTCClear;
extern uint16 DistSinceDtcCleared;
extern uint16 IgnUpCycleCounter;
extern uint16 OBDDistanceMILLastOn;
extern uint16 OBDTimeMILLastOn;
extern uint16 OBDDistanceDTCClear;
extern uint16 OBDTimeDTCLastClear;

extern uint8 WarmUpCycleCounter;

extern boolean CurrentPTOStatus;

extern uint16 ContinuousMICounter;
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
extern uint16 MasterContinuousMICounter;
#endif
extern uint16 OBDB1Counter;

#endif

extern VAR(Dem_ClearNonvolatileStatusType, AUTOMATIC) Dem_ClearNonvolatileStatus;

extern VAR(uint8, AUTOMATIC) Dem_AgingCycle;

#if ((DEM_FREEZE_FRAME_CLASS_NUM > 0) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0) || (DEM_PID_CLASS_NUM > 0))
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0)

extern VAR(Dem_PreStoreFFInfoType, AUTOMATIC) DemPreStoreFFInfo[DEM_MAX_NUMBER_PRESTORED_FF];

#endif
#endif

extern VAR(Dem_DTCByOccurrenceTimeType, AUTOMATIC) DemDTCByOccurrenceTimeInfo;

/*******************************************************************************
**                      Global Function declaration                           **
*******************************************************************************/
/*************************************************************************/
/*
 * Brief               MemSet
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Val && Size
 * Param-Name[out]     none
 * Param-Name[in/out]  Dest
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
static inline FUNC(void, DEM_CODE) Dem_MemSet(P2VAR(uint8, AUTOMATIC, DEM_VAR) Dest, uint8 Val, uint32 Size)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    for (uint32 iloop = 0; iloop < Size; iloop++)
    {
        Dest[iloop] = Val;
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 *  Brief               Dem_UpdateCombinedDtcStatus
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      IntId
 *  Param-Name[out]     None
 *  Param-Name[in/out]  None
 *  Return              None
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_UpdateCombinedDtcStatus(Dem_EventIdType IntId);

/*************************************************************************/
/*
 * Brief               Dem_EventQueueAddDebounceFailed
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
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
static inline FUNC(void, DEM_CODE)
    Dem_EventQueueAddDebounceFailed(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Dem_EventIdType IntId = pEvent->IntId;
    if (0x00u == (pEvent->UdsStatus & DEM_UDS_STATUS_TF))
    {
        const uint8* pMemDest =
            DemPbCfg.DemDTCAttributes[DemPbCfg.DemDTC[DemPbCfg.DemEventParameter[IntId].DemDTCRef].DemDTCAttributesRef]
                .DemMemoryDestinationRef;
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
        for (uint8 iloop = 0; iloop < DEM_MEM_DEST_MAX_NUM_OF_DTC; iloop++)
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
        {
            if (DemMemDestCfg[*pMemDest].ExtId == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
            {
                if (DemDTCByOccurrenceTimeInfo.FirstFailed == DEM_EVENT_PARAMETER_INVALID)
                {
                    DemDTCByOccurrenceTimeInfo.FirstFailed = IntId;
                }
                DemDTCByOccurrenceTimeInfo.MostRecentFailed = IntId;
            }
#if (DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u)
            pMemDest++;
#endif /* DEM_MEM_DEST_MAX_NUM_OF_DTC > 1u */
        }
        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
    }
    /*  SWS_Dem_00036 */
    /* bit 0 1 5*/
    DEM_FLAGS_SET(pEvent->UdsStatus, DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TFSLC);
    /* bit4 6 */
    DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TNCSLC);
    DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_ACTIVE);

#if (DEM_STATUSINDICATOR30ENABLE == STD_ON)
    /*The bit is set to 1 when the FDC10 reach a value in the range[unconfirmedDTCLimit, +127]*/
    DEM_FLAGS_SET(
        pEvent->StatusIndicator30,
        DEM_SI30_DTC_UC | DEM_SI30_DTC_UCTOC | DEM_SI30_DTC_UCSLC | DEM_SI30_DTC_SSLC); /*bit 0,1,2,4*/
    /*bit 7: The bit is set to 1 when the FDC10 reach the value +127.*/
    DEM_FLAGS_SET(pEvent->StatusIndicator30, DEM_SI30_DTC_TSFLC);
#endif /* DEM_STATUSINDICATOR30ENABLE == STD_ON */

#if ((DEM_OCC6EANLE == STD_ON) || (DEM_OCC4EANLE == STD_ON))
    if (0x00u == DEM_FLAGS_ISSET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_THISOPISFAILED))
    {
        DEM_FLAGS_SET(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_THISOPISFAILED);
#if (DEM_OCC6EANLE == STD_ON)
        /* In each operation cycle the counter shall be incremented as soon as FDC10 has reached the value +127 for the
         * ﬁrst time. */
        if (pEvent->OCC6 < 0xFFu)
        {
            pEvent->OCC6++;
        }
        /* Do not clear OCC6 in this cycle if fail occured. */
        DEM_FLAGS_CLR(pEvent->EventStatusFlag, DEM_EVENT_FLAGS_OCC6CLR);
#endif /* DEM_OCC6EANLE == STD_ON */
#if (DEM_OCC4EANLE == STD_ON)
        /* In each operaƟon cycle the counter shall be incremented as soon as FDC10 has reached a value that is equal to
         * or greater than its unconﬁrmedDTCLimit for the ﬁrst Ɵme. */
        if (pEvent->OCC4 < 0xFFu)
        {
            pEvent->OCC4++;
        }
#endif /* DEM_OCC4EANLE == STD_ON */
    }
#endif /* DEM_OCC6EANLE == STD_ON) || (DEM_OCC4EANLE == STD_ON */
    Dem_UpdateCombinedDtcStatus(IntId);
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_EventQueueAddDebouncePassed
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
/* PRQA S 3432,1532++ */ /* MISRA Rule 20.7,8.7 */
static inline FUNC(void, DEM_CODE)
    Dem_EventQueueAddDebouncePassed(P2VAR(Dem_EventRelateInformationType, AUTOMATIC, DEM_VAR) pEvent)
/* PRQA S 3432,1532-- */ /* MISRA Rule 20.7,8.7 */
{
    Dem_EventIdType IntId = pEvent->IntId;
#if (DEM_EXTENDED_DATA_CLASS_NUM > 0u)
    if (0x00u != (pEvent->UdsStatus & DEM_UDS_STATUS_TF))
    {
        DEM_FLAGS_SET(pEvent->Status, DEM_EVENT_STATUS_TFBITCHANGE);
    }
#endif                                                                           /* DEM_EXTENDED_DATA_CLASS_NUM > 0u */
    DEM_FLAGS_CLR(pEvent->UdsStatus, DEM_UDS_STATUS_TF | DEM_UDS_STATUS_TNCTOC); /* bit 0 6*/
    DEM_FLAGS_CLR(pEvent->Status, DEM_EVENT_STATUS_ACTIVE);
    Dem_UpdateCombinedDtcStatus(IntId);
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               MemCopy
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Src && Size
 * Param-Name[out]     Dest
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/

/*************************************************************************/
/*
 * Brief               MemCopy
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Src && Size
 * Param-Name[out]     Dest
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(void, DEM_CODE) Dem_MemCopy(uint8* Dest, const uint8* Src, uint32 Size)
{
    for (uint32 iloop = 0; iloop < Size; iloop++)
    {
        Dest[iloop] = Src[iloop];
    }
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               CheckCondictionFulfilled
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      cond && group && len
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              boolean
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(boolean, DEM_CODE) Dem_CheckCondictionFulfilled(
    P2CONST(uint8, AUTOMATIC, DEM_VAR) cond,
    P2CONST(uint8, AUTOMATIC, DEM_VAR) group,
    uint8 len)
{
    boolean res = TRUE;
    for (uint8 iloop = 0; iloop < len; iloop++)
    {
        if (((cond[iloop]) & (group[iloop])) != group[iloop])
        {
            res = FALSE;
        }
    }
    return res;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_DTC_ATTRIBUTES_NUM > 0u)
/*************************************************************************/
/*
 * Brief               Get EventDTCAttributesCfg
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              const Dem_DTCAttributesType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(P2CONST(Dem_DTCAttributesType, AUTOMATIC, DEM_CONST), DEM_CODE)
    Dem_EventDTCAttributesCfg(Dem_EventIdType IntId)
{
    const Dem_DTCAttributesType* pRes = NULL_PTR;
    /* DtcRef */
    uint16 Ref = DemPbCfg.DemEventParameter[IntId].DemDTCRef;
    if (Ref != DEM_DTC_REF_INVALID)
    {
        /* DTCAttributesRef */
        Ref = DemPbCfg.DemDTC[Ref].DemDTCAttributesRef;
        pRes = &DemPbCfg.DemDTCAttributes[Ref];
    }
    return pRes;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#else
#define Dem_EventDTCAttributesCfg(x) NULL_PTR
#endif /* DEM_DTC_ATTRIBUTES_NUM > 0u */
/*************************************************************************/
/*
 * Brief               GetInternalMemDest
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      DTCOrigin
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              uint8
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(uint8, DEM_CODE) Dem_GetInternalMemDest(Dem_DTCOriginType DTCOrigin)
{
    uint8 ret = DEM_MEM_DEST_INVALID;
    for (uint8 iloop = 0; iloop < DEM_MEM_DEST_TOTAL_NUM; iloop++)
    {
        if (DemMemDestCfg[iloop].ExtId == DTCOrigin)
        {
            ret = iloop;
            break;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

/*************************************************************************/
/*
 * Brief               Dem_ClearDTCProcess
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_ClearDTCProcess(void);

/*************************************************************************/
/*
 * Brief               Dem_DcmInit
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_DcmInit(void);

/*************************************************************************/
/*
 * Brief               Dem_GetEventDTC
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && DTCFormat
 * Param-Name[out]     DTC
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE)
    Dem_GetEventDTC(uint16 DTCRef, Dem_DTCFormatType DTCFormat, P2VAR(uint32, AUTOMATIC, DEM_VAR) DTC);

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

extern FUNC(uint16, DEM_CODE) Dem_GetDTCIndex(uint32 DTC, Dem_DTCFormatType DTCFormat);

#if (DEM_GROUP_OF_DTC_NUM > 0u)
/*************************************************************************/
/*
 * Brief               GetDTCGroupIndex
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant/Non Reentrant
 * Param-Name[in]      Id
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              DTCGroupIndex
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(uint8, DEM_CODE) Dem_GetDTCGroupIndex(uint32 Id)
{
    uint8 ret = DEM_GROUP_OF_DTC_INVALID;
    for (uint8 iloop = 0; iloop < DEM_GROUP_OF_DTC_NUM; iloop++) /* PRQA S 2877 */ /* MISRA Dir 4.1 */
    {
        if (DemGroupOfDTC[iloop] == Id)
        {
            ret = iloop;
        }
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#endif /* DEM_GROUP_OF_DTC_NUM > 0u */

/*************************************************************************/
/*
 * Brief               Dem_ResetDemClearDTCInfo
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant/Non Reentrant
 * Param-Name[in]      Id
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(void, DEM_CODE) Dem_ResetDemClearDTCInfo(void)
{
    Dem_ClearDTCInfoType* pClr = &DemClearDTCInfo;
    pClr->DTCIndex = DEM_DTC_REF_INVALID;
    pClr->DTCGroupIndex = DEM_GROUP_OF_DTC_INVALID;
    pClr->ClearAllGroup = FALSE;
    Dem_ClearDTCLock = DEM_CLEAR_NOT_LOCK;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

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

extern FUNC(void, DEM_CODE) Dem_UpdateFDC(Dem_EventIdType IntId);

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

extern FUNC(Std_ReturnType, DEM_CODE)
    Dem_DTCGetFaultDetectionCounter(Dem_EventIdType EventId, sint8* FaultDetectionCounter);

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
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

extern FUNC(void, DEM_CODE) Dem_ClearOBDInfo(void);

#endif

#if (DEM_J1939_SUPPORT == STD_ON)
/*************************************************************************/
/*
 * Brief               Dem_DcmInit
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      none
 * Param-Name[out]     none
 * Param-Name[in/out]  none
 * Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_J1939Init(void);

#endif /* DEM_J1939_SUPPORT == STD_ON */

/*******************************************************************************
**                      EventDebounce                                         **
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

extern FUNC(void, DEM_CODE) Dem_DebounceInit(void);

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

extern FUNC(void, DEM_CODE) Dem_DebounceReset(Dem_EventIdType IntId);

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

extern FUNC(Std_ReturnType, DEM_CODE)
    Dem_GetInteralFDC(Dem_EventIdType IntId, P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter);

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

extern FUNC(Dem_EventStatusType, DEM_CODE) Dem_DebounceProcess(Dem_EventDataBufferType pEventBuffer);

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

extern FUNC(void, DEM_CODE) Dem_DebounceFreeze(Dem_EventIdType IntId);
#else
#define Dem_DebounceFreeze(x)
#endif /* DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0u) || (DEM_DEBOUNCE_COUNTER_BASED_CLASS_NUM > 0u */

#if (DEM_DEBOUNCE_TIME_BASE_CLASS_NUM > 0)
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

extern FUNC(void, DEM_CODE) Dem_DebounceTimerMain(void);

#else
#define Dem_DebounceTimerMain()
#endif

#if ((DEM_FREEZE_FRAME_CLASS_NUM > 0) || (DEM_J1939_FREEZE_FRAME_CLASS_NUM > 0) || (DEM_PID_CLASS_NUM > 0))
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

extern FUNC(void, DEM_CODE) Dem_FreezeFrameStorage(
    Dem_EventIdType IntId,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint8 Trigger);

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

extern FUNC(Std_ReturnType, DEM_CODE) Dem_FreezeFrameGetFromEntry(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    uint8 RecordNum,
    uint16 Did,
    P2VAR(uint8, AUTOMATIC, DEM_VAR) pBuffer,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint16* BufSize);

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
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
extern FUNC(P2VAR(Dem_FreezeFrameInfoType, AUTOMATIC, DEM_VAR), DEM_CODE)
    Dem_FreezeFrameGetByRecordNum(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry, uint8 RecordNum);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0)
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

extern FUNC(void, DEM_CODE) Dem_FreezeFrameInit(void);

/*************************************************************************/
/*
 * Brief               Dem_PreStoreFF
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ExtId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DEM_CODE) Dem_PreStoreFF(Dem_EventIdType ExtId);

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

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ClearPreStoreFF(Dem_EventIdType ExtId);

#else
#define Dem_FreezeFrameInit()
#define Dem_PreStoreFF(x)      E_NOT_OK
#define Dem_ClearPreStoreFF(x) E_OK
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0)
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
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
extern FUNC(P2VAR(Dem_PreStoreFFInfoType, AUTOMATIC, DEM_VAR), DEM_CODE) Dem_PreStoreFFGet(Dem_EventIdType ExtId);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#endif
#endif
/*******************************************************************************
**                      OBD                                                   **
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

extern FUNC(void, DEM_CODE) Dem_OBDInit(void);

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

FUNC(void, DEM_CODE) Dem_UpdateOBDMilStatus(uint8 indicatorRef, uint16 IntID);

#if (DEM_DTR_NUM > 0)
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

FUNC(void, DEM_CODE) Dem_DTRInit(void);

#endif

#if (DEM_RATIO_NUM > 0)
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

FUNC(void, DEM_CODE) Dem_IUMPRInit(void);

#endif

#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) || (DEM_J1939_SUPPORT == STD_ON))
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

FUNC(void, DEM_CODE) Dem_CalOBDRelatedValue(uint8 OperationId);

#endif

#if (DEM_DTR_NUM > 0)
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

extern FUNC(void, DEM_CODE) Dem_ClearDTRInfoByEventID(Dem_EventIdType IntId);

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

extern FUNC(void, DEM_CODE) Dem_ClearDTRInfoByDTRID(uint16 DTRID);

#endif

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

extern FUNC(uint16, DEM_CODE) Dem_ReadDistanceInformation(void);

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

extern FUNC(uint16, DEM_CODE) Dem_ReadTimeInformation(void);

#endif
/*******************************************************************************
**                      EventQueue                                            **
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

extern FUNC(void, DEM_CODE) Dem_EventQueueInit(void);

/*************************************************************************/
/*
 * Brief               Dem_EventQueueAdd
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ExtId && Status
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DEM_CODE) Dem_EventQueueAdd(Dem_EventIdType ExtId, Dem_EventStatusType Status);

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

extern FUNC(void, DEM_CODE) Dem_EventQueueProcess(void);

/*******************************************************************************
**                      EventMemory                                           **
*******************************************************************************/
/*************************************************************************/
/*
 *  Brief               Dem_EventMemInit
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Non Reentrant
 *  Param-Name[in]      none
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_EventMemInit(Std_ReturnType NvmResult);

/*************************************************************************/
/*
 *  Brief               Dem_GetEventInfo
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      IntId
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              Dem_EventRelateInformationType*
 */
/*************************************************************************/
extern FUNC(Dem_EventRelateInformationType*, DEM_CODE) Dem_GetEventInfo(Dem_EventIdType IntId);
/*************************************************************************/
/*
 *  Brief               Dem_EventTestFailed
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      IntId && pEventBuffer
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_EventTestFailed(Dem_EventIdType IntId);

/*************************************************************************/
/*
 *  Brief               Dem_ResponseOnDtcStatusChange
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      IntId
 *  Param-Name[out]     None
 *  Param-Name[in/out]  None
 *  Return              None
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_ResponseOnDtcStatusChange(Dem_EventIdType IntId);

/*************************************************************************/
/*
 *  Brief               Dem_EventTestPassed
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      IntId && pEventBuffer
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_EventTestPassed(Dem_EventIdType IntId);

/*************************************************************************/
/*
 *  Brief               Dem_CheckEventMemEntryExistsAlready
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      IntId
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              Dem_EventMemEntryType*
 */
/*************************************************************************/
extern FUNC(Dem_EventMemEntryType*, DEM_CODE) Dem_CheckEventMemEntryExistsAlready(Dem_EventIdType IntId);
/*************************************************************************/
/*
 *  Brief               Dem_MemEntryGet
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      ExtId && memDest
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              Dem_EventMemEntryType*
 */
/*************************************************************************/

/*************************************************************************/
/*
 * Brief               Dem_MemEntryGet
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ExtId && MemDestIndex
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Dem_EventMemEntryType*
 */
/*************************************************************************/
#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
static inline FUNC(Dem_EventMemEntryType*, DEM_CODE) Dem_MemEntryGet(Dem_EventIdType ExtId, uint8 memDest)
{
    Dem_EventMemEntryType* ret = NULL_PTR;
    Dem_EventMemEntryType* pEntry = DemMemDestCfg[memDest].EntryList;
    const uint8 EntryNum = DemMemDestCfg[memDest].EntryNum;
    for (uint16 iloop = 0; (iloop < EntryNum) && (ret == NULL_PTR); iloop++) /*primary total number such as 7 */
    {
        if (pEntry->EventId == ExtId)
        {
            ret = pEntry;
        }
        pEntry++;
    }
    return ret;
}
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
/*************************************************************************/
/*
 *  Brief               Dem_MemEntryDelete
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      none
 *  Param-Name[out]     none
 *  Param-Name[in/out]  pEntry
 *  Return              none
 */
/*************************************************************************/
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
extern FUNC(void, DEM_CODE) Dem_MemEntryDelete(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry, uint8 memDest);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
/*************************************************************************/
/*
 *  Brief               Dem_OperationCycleStart
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      OpId && IsRestart
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_OperationCycleStart(uint8 OpId, boolean IsRestart);

/*************************************************************************/
/*
 *  Brief               Dem_OperationCycleEnd
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      OpId
 *  Param-Name[out]     none
 *  Param-Name[in/out]  none
 *  Return              none
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_OperationCycleEnd(uint8 OpId);

#if (DEM_NVRAM_BLOCKID_NUM > 0)
/*************************************************************************/
/*
 *  Brief               Dem_IntWriteNvRAM
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      None
 *  Param-Name[out]     None
 *  Param-Name[in/out]  pEvent
 *  Return              None
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_IntWriteNvRAM(void);

/*************************************************************************/
/*
 *  Brief               Dem_IntReadNvRAM
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      None
 *  Param-Name[out]     None
 *  Param-Name[in/out]  pEvent
 *  Return              None
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DEM_CODE) Dem_IntReadNvRAM(void);

#endif

/*************************************************************************/
/*
 *  Brief               Dem_StorageInit
 *  ServiceId           --
 *  Sync/Async          Synchronous
 *  Reentrancy          Reentrant
 *  Param-Name[in]      None
 *  Param-Name[out]     None
 *  Param-Name[in/out]  None
 *  Return              None
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_EntryInit(void);

#if (DEM_EXTENDED_DATA_CLASS_NUM > 0)
/*************************************************************************/
/*
 * Brief               Dem_ExtendedDataGetFromEntry
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEntry && RecordNum
 * Param-Name[out]     pBuffer
 * Param-Name[in/out]  BufSize
 * Return              pBuffer
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ExtendedDataGetFromEntry(
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2CONST(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    uint8 RecordNum,
    P2VAR(uint8, AUTOMATIC, DEM_VAR) pBuffer,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint16* BufSize);

/*************************************************************************/
/*
 * Brief               Dem_ExtendedDataStorage
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      IntId && pEventBuffer && Trigger
 * Param-Name[out]     pEntry
 * Param-Name[in/out]  None
 * Return              None
 */
/*************************************************************************/

extern FUNC(void, DEM_CODE) Dem_ExtendedDataStorage(
    Dem_EventIdType IntId,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR) pEntry,
    /* PRQA S 3432-- */ /* MISRA Rule 20.7 */
    uint8 Trigger);

#endif
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
extern FUNC(void, DEM_CODE) Dem_EventDataStorageTrigger(Dem_EventIdType IntId, uint8 Trigger);

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
FUNC(P2VAR(Dem_EventMemEntryType, AUTOMATIC, DEM_VAR), DEM_CODE) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
Dem_MemEntryAllocate(Dem_EventIdType IntId, uint8 memDest); /* PRQA S 1505 */      /* MISRA Rule 8.7 */

#if (DEM_INDICATOR_ATTRIBUTE_TOTAL_NUM > 0)
/*************************************************************************/
/*
 * Brief               Dem_CheckEventAllIndicator
 * ServiceId           --
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      pEvent
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              boolean
 */
/*************************************************************************/
extern FUNC(boolean, DEM_CODE) Dem_CheckEventAllIndicator(uint16 IntId);
#endif
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
extern FUNC(void, DEM_CODE) Dem_GetFncData(DemDataElementReadFncType DataReadFnc, uint8* pBuffer, uint8 DataSize);
#endif /* DEM_DATA_ELEMENT_CLASS_NUM > 0u */

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
FUNC(boolean, DEM_CODE) Dem_J1939CeckNode(uint16 dtcRef, uint8 node);
#endif /* DEM_J1939_NODE_NUM > 0u */

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
FUNC(void, DEM_CODE) Dem_UpdateInternalData(uint16 IntId);
/*******************************************************************************
**                      end of file                                           **
*******************************************************************************/

#endif
