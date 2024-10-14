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
 **  FILENAME    : EthIf_Types.h                                               **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : YangBo                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/

#ifndef ETHIF_TYPES_H
#define ETHIF_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Eth_GeneralTypes.h"
#include "EcuM.h"
#include "Platform_Types.h"
#include "ComStack_Types.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* 3 version types: R19, 4.2, 4.4*/
#if !defined(ETHIF_ETH_MAIJORVERSION)
#define ETHIF_ETH_MAIJORVERSION 42u
#endif /* !defined ETHIF_ETH_MAIJORVERSION */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @req SWS_EthIf_00150 */
typedef enum
{
    ETHIF_STATE_UNINIT, /* Ethernet Interface is not yet configured*/
    ETHIF_STATE_INIT,   /* Ethernet Interface is configured*/
} EthIf_StateType;

typedef void (*EthIfULRxIndicationType)(
    uint8 CtrlIdx,
    Eth_FrameType FrameType,
    boolean IsBroadcast,
    const uint8* PhysAddrPtr,
    const uint8* DataPtr,
    uint16 LenByte);
#if (42u == ETHIF_ETH_MAIJORVERSION)
typedef void (*EthIfULTxConfirmationType)(uint8 CtrlIdx, Eth_BufIdxType BufIdx);
#elif (44u == ETHIF_ETH_MAIJORVERSION) || (19u == ETHIF_ETH_MAIJORVERSION)
typedef void (*EthIfULTxConfirmationType)(uint8 CtrlIdx, Eth_BufIdxType BufIdx, Std_ReturnType Result);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
/* Function pointer for User defined TrcvLinkState callback */
typedef void (*EthIfTrcvLinkStateChgType)(uint8 CtrlIdx, EthTrcv_LinkStateType TrcvLinkState);

typedef struct
{
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_SetControllerMode)
    (uint8 CtrlIdx, Eth_ModeType CtrlMode);
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_GetControllerMode)
    (uint8 CtrlIdx, Eth_ModeType* CtrlModePtr);
#if (42u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(BufReq_ReturnType, ETHIF_APPL_CODE, Eth_ProvideTxBuffer)
    (uint8 CtrlIdx, Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr);
#elif (44u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(BufReq_ReturnType, ETHIF_APPL_CODE, Eth_ProvideTxBuffer)
    (uint8 CtrlIdx, uint8 Priority, Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(BufReq_ReturnType, ETHIF_APPL_CODE, Eth_ProvideTxBuffer)
    (uint8 CtrlIdx, uint8 Priority, Eth_BufIdxType* BufIdxPtr, uint8** BufPtr, uint16* LenBytePtr);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_Transmit)
    (uint8 CtrlIdx,
     Eth_BufIdxType BufIdx,
     Eth_FrameType FrameType,
     boolean TxConfirmation,
     uint16 LenByte,
     const uint8* PhysAddrPtr);
    P2FUNC(void, ETHIF_APPL_CODE, Eth_SetPhysAddr)(uint8 CtrlIdx, const uint8* PhysAddrPtr);
    P2FUNC(void, ETHIF_APPL_CODE, Eth_GetPhysAddr)(uint8 CtrlIdx, uint8* PhysAddrPtr);
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_UpdatePhysAddrFilter)
    (uint8 CtrlIdx, const uint8* PhysAddrPtr, Eth_FilterActionType Action);
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_GetCurrentTime)
    (uint8 CtrlIdx, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
    P2FUNC(void, ETHIF_APPL_CODE, Eth_EnableEgressTimeStamp)(uint8 CtrlIdx, Eth_BufIdxType BufIdx);
#if (42u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(void, ETHIF_APPL_CODE, Eth_GetEgressTimeStamp)
    (uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#elif (44u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_GetEgressTimeStamp)
    (uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_GetEgressTimeStamp)
    (uint8 CtrlIdx, uint8 BufIdx, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
#if (42u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(void, ETHIF_APPL_CODE, Eth_GetIngressTimeStamp)
    (uint8 CtrlIdx, Eth_DataType* DataPtr, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#elif (44u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_GetIngressTimeStamp)
    (uint8 CtrlIdx, const Eth_DataType* DataPtr, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, Eth_GetIngressTimeStamp)
    (uint8 CtrlIdx, const Eth_DataType* DataPtr, Eth_TimeStampQualType* timeQualPtr, Eth_TimeStampType* timeStampPtr);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
#if (42u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(void, ETHIF_APPL_CODE, Eth_Receive)(uint8 CtrlIdx, Eth_RxStatusType* RxStatusPtr);
#elif (44u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(void, ETHIF_APPL_CODE, Eth_Receive)
    (uint8 CtrlIdx, uint8 FifoIdx, Eth_RxStatusType* RxStatusPtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(void, ETHIF_APPL_CODE, Eth_Receive)
    (uint8 CtrlIdx, uint8 FifoIdx, Eth_RxStatusType* RxStatusPtr);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
    P2FUNC(void, ETHIF_APPL_CODE, Eth_TxConfirmation)(uint8 CtrlIdx);
} EthIf_EthDriverApiType;

typedef struct
{
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_SetTransceiverWakeupMode)
    (uint8 TrcvIdx, EthTrcv_WakeupModeType TrcvWakeupMode);
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_GetTransceiverWakeupMode)
    (uint8 TrcvIdx, EthTrcv_WakeupModeType* TrcvWakeupModePtr);
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_TransceiverLinkStateRequest)
    (uint8 TrcvIdx, EthTrcv_LinkStateType LinkState);
#if (42u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_GetTransceiverMode)
    (uint8 TrcvIdx, EthTrcv_ModeType* TrcvModePtr);
#elif (44u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_GetTransceiverMode)
    (uint8 TrcvIdx, EthTrcv_ModeType* TrcvModePtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_GetTransceiverMode)
    (uint8 TrcvIdx, Eth_ModeType* TrcvModePtr);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_GetLinkState)
    (uint8 TrcvIdx, EthTrcv_LinkStateType* LinkStatePtr);
#if (42u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_SetTransceiverMode)
    (uint8 TrcvIdx, EthTrcv_ModeType CtrlMode);
#elif (44u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_SetTransceiverMode)
    (uint8 TrcvIdx, EthTrcv_ModeType CtrlMode);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_SetTransceiverMode)
    (uint8 TrcvIdx, Eth_ModeType TrcvMode);
#endif /* 42u == ETHIF_ETH_MAIJORVERSION */
    P2FUNC(Std_ReturnType, ETHIF_APPL_CODE, EthTrcv_CheckWakeup)(uint8 TrcvIdx);
} EthIf_EthTrcvDriverApiType;

typedef struct
{
    uint8 EthIfCtrlIdx;
    uint16 EthIfCtrlMtu;
    uint8 EthIfMaxTxBufsTotal;
    uint16 EthIfVlanId;
    uint8 EthIfPhysControllerIdRef;
    uint8 EthIfEthTrcvId;
    uint8 EthIfSwitchRefOrPortGroupRef;
} EthIf_ControllerCfgType;

typedef struct
{
    uint16 EthIfFrameType;
    uint8 EthIfOwner;
} EthIf_FrameOwnerCfgType;

typedef struct
{
    uint8 EthIfSwitchIdx;
    uint8 EthIfSwitchRef;
} EthIf_SwitchType;

typedef struct
{
    uint8 EthIfEthTrcvIdx; /*to identify the different Ethtrcv channel*/
    uint8 EthTrcvDriverId; /*to identify the different Trcv API*/
    EcuM_WakeupSourceType WakeUpSource;
} EthIfEthTrcvRefType;

typedef struct
{
    uint8 EthIfTrcvIdx;
    const EthIfEthTrcvRefType* EthIfEthTrcvRef;
} EthIf_TrcvType;

typedef struct
{
    uint8 EthIfEthCtrlId; /*to identify the different Eth channel*/
    uint8 EthDriverId;    /*to identify the different driver API*/
} EthIfEthCtrlRefType;

typedef struct
{
    uint8 EthIfPhysControllerIdx;
    const EthIfEthCtrlRefType* EthIfEthCtrlRef;
} EthIf_PhysControllerType;

/* @req SWS_EthIf_00149 */
typedef struct
{
    P2CONST(EthIf_ControllerCfgType, AUTOMATIC, ETHIF_APPL_CONST)
    EthIfCtrlCfg; /*pointer to hold controller config data*/
    P2CONST(EthIf_FrameOwnerCfgType, AUTOMATIC, ETHIF_APPL_CONST) EthIfOwnerCfg; /* pointer to hold Owner config data */
    P2CONST(EthIf_TrcvType, AUTOMATIC, ETHIF_APPL_CONST) EthIfTrcvCfg;           /*pointer to holad trcv config data*/
    P2CONST(EthIf_PhysControllerType, AUTOMATIC, ETHIF_APPL_CONST)
    EthIf_PhysControllerCfg; /*pointer to hold PhysController config data*/
    P2CONST(EthIf_SwitchType, AUTOMATIC, ETHIF_APPL_CONST) EthIfSwitchCfg; /* pointer to hold switches config data */
    P2CONST(EthIfULTxConfirmationType, AUTOMATIC, ETHIF_APPL_CONST)
    EthIfULTxConfirmation; /* pointer to hold Tx confirmation functions list */
    P2CONST(EthIfULRxIndicationType, AUTOMATIC, ETHIF_APPL_CONST)
    EthIfULRxIndication; /* Ptr to Rx indication function list */
    P2CONST(EthIfTrcvLinkStateChgType, AUTOMATIC, ETHIF_APPL_CONST)
    EthIfTrcvLink;                    /*pointer to hold Trcv Link state functions list */
    uint8 EthIfCtrlCount;             /* No of If Controllers configure */
    uint8 EthIfTrcvCount;             /* No of Trcv configured */
    uint8 EthIfSwitchCount;           /* No of Switches configured */
    uint8 EthIfOwnersCount;           /* No of Owners configured */
    uint8 EthIfPhysControllerCount;   /* No of Eth */
    uint8 EthIfTrcvLinkStateChgCount; /* No of EthIfTrcvLinkStateChgConfig configured*/
} EthIf_ConfigType;
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/

#endif
