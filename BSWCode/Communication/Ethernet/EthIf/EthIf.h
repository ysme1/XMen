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
 **  FILENAME    : EthIf.h                                                     **
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
* V2.0.5 [2022/05/17] [zhiqiang.huang] Add null pointer check for eth trcv API.
*******************************************************************************/

#ifndef ETHIF_H
#define ETHIF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EthIf_Types.h"
#include "EthIf_Cfg.h"
#if (STD_ON == ETHIF_WAKEUP_SUPPORT)
#include "EcuM_Types.h"
#endif /* STD_ON == ETHIF_WAKEUP_SUPPORT */
#include "EthSM.h"
#include "ComStack_Types.h"

extern const EthIf_ConfigType EthIf_ConfigData;
/*TODO EthIf_RxIndication*/
extern struct netif g_netif;

extern const EthIf_EthDriverApiType Eth_DriverApi[ETHIF_ETH_DRIVER_API_NUM];
#if (STD_ON == ETHIF_USE_ETHTRCV)
extern const EthIf_EthTrcvDriverApiType EthTrcv_DriverApi[ETHIF_ETHTRCV_DRIVER_API_NUM];
#endif /* STD_ON == ETHIF_USE_ETHTRCV */
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* @req SWS_EthIf_00006 */
#define ETHIF_H_AR_RELEASE_MAJOR_VERSION    (4u)
#define ETHIF_H_AR_RELEASE_MINOR_VERSION    (5u)
#define ETHIF_H_AR_RELEASE_REVISION_VERSION (0u)

#define ETHIF_H_SW_MAJOR_VERSION            (2u)
#define ETHIF_H_SW_MINOR_VERSION            (0u)
#define ETHIF_H_SW_PATCH_VERSION            (14u)

#define ETHIF_MODULE_ID                     (65u)
#define ETHIF_INSTANCE_ID                   (0u)
#define ETHIF_VENDOR_ID                     (62u)
/*Error IDs*/
#define ETHIF_E_INV_CTRL_IDX  0x01u
#define ETHIF_E_INV_TRCV_IDX  0x02u
#define ETHIF_E_UNINIT        0x05u
#define ETHIF_E_PARAM_POINTER 0x06u
#define ETHIF_E_INV_PARAM     0x07u
#define ETHIF_E_INIT_FAILED   0x08u

/** Service IDs */
#define ETHIF_SERVICE_ID_INIT                     0x01u
#define ETHIF_SERVICE_ID_SET_CTRL_MODE            0x03u
#define ETHIF_SERVICE_ID_GET_CTRL_MODE            0x04u
#define ETHIF_SERVICE_ID_SET_TRCV_MODE            0x06u
#define ETHIF_SERVICE_ID_GET_TRCV_MODE            0x07u
#define ETHIF_SERVICE_ID_SET_TRCV_WAKEUP_MODE     0x2Eu
#define ETHIF_SERVICE_ID_GET_TRCV_WAKEUP_MODE     0x2Fu
#define ETHIF_SERVICE_ID_CHECK_WAKE_UP            0x30u
#define ETHIF_SERVICE_ID_GET_PHY_ADDR             0x08u
#define ETHIF_SERVICE_ID_SET_PHY_ADDR             0x0Du
#define ETHIF_SERVICE_ID_UPDATE_PHY_ADDR_FILTER   0x0Cu
#define ETHIF_SERVICE_ID_GET_PORT_MAC_ADDR        0x28u
#define ETHIF_SERVICE_ID_GET_ARL_TABEL            0x29u
#define ETHIF_SERVICE_ID_GET_BUF_LEVEL            0x2Au
#define ETHIF_SERVICE_ID_GET_DROP_COUNT           0x2Bu
#define ETHIF_SERVICE_ID_STORE_CONFIG             0x2Cu
#define ETHIF_SERVICE_ID_RESET_CONFIG             0x2Du
#define ETHIF_SERVICE_ID_GET_CURRENT_TIME         0x22u
#define ETHIF_SERVICE_ID_ENABLE_EGRESS_TIME_STAMP 0x23u
#define ETHIF_SERVICE_ID_GET_EGRESS_TIME_STAMP    0x24u
#define ETHIF_SERVICE_ID_GET_INGRESS_TIME_STAMP   0x25u
#define ETHIF_SERVICE_ID_SET_CORRECTION_TIME      0x26u
#define ETHIF_SERVICE_ID_SET_GLOBAL_TIME          0x27u
#define ETHIF_SERVICE_ID_PROVIDE_TX_BUFFER        0x09u
#define ETHIF_SERVICE_ID_TRANSMIT                 0x0Au
#define ETHIF_SERVICE_ID_GET_VERSION_INFO         0x0Bu
#define ETHIF_SERVICE_ID_GET_CTRL_IDXLIST         0x44u
/* Callback notifications function service Ids */
#define ETHIF_SERVICE_ID_RX_INDICATION        0x10u
#define ETHIF_SERVICE_ID_TX_CONFIRMATION      0x11u
#define ETHIF_SERVICE_ID_CTRL_MODE_INDICATION 0x0Eu
#define ETHIF_SERVICE_ID_TRCV_MODE_INDICATION 0x0Fu

/* Scheduled functions service IDs */
#define ETHIF_SERVICE_ID_MAIN_FUNCTION_RX    0x20u /* PRQA S 0791 */
#define ETHIF_SERVICE_ID_MAIN_FUNCTION_TX    0x21u /* PRQA S 0791 */
#define ETHIF_SERVICE_ID_MAIN_FUNCTION_STATE 0x05u /* PRQA S 0791 */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/
/* @req SWS_EthIf_00024 */
FUNC(void, ETHIF_CODE)
EthIf_Init(P2CONST(EthIf_ConfigType, ETHIF_APPL_DATA, ETHIF_VAR) CfgPtr); /** Init function for ETHIF */
/* @req SWS_EthIf_00034 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_SetControllerMode(VAR(uint8, ETHIF_VAR) CtrlIdx, VAR(Eth_ModeType, ETHIF_VAR) CtrlMode);
/* @req SWS_EthIf_00039 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetControllerMode(VAR(uint8, ETHIF_VAR) CtrlIdx, P2VAR(Eth_ModeType, ETHIF_APPL_DATA, ETHIF_VAR) CtrlModePtr);
/* @req SWS_EthIf_00055 */
#if (42u == ETHIF_ETH_MAIJORVERSION) || (44u == ETHIF_ETH_MAIJORVERSION)
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetTransceiverMode(
    VAR(uint8, ETHIF_VAR) TrcvIdx,
    P2VAR(EthTrcv_ModeType, ETHIF_APPL_DATA, ETHIF_VAR) TrcvModePtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetTransceiverMode(VAR(uint8, ETHIF_VAR) TrcvIdx, P2VAR(Eth_ModeType, ETHIF_APPL_DATA, ETHIF_VAR) TrcvModePtr);
#endif
#if (STD_ON == ETHIF_WAKEUP_SUPPORT)
/* @req SWS_EthIf_00233 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_SetTransceiverWakeupMode(VAR(uint8, ETHIF_VAR) TrcvIdx, VAR(EthTrcv_WakeupModeType, ETHIF_VAR) TrcvWakeupMode);
/* @req SWS_EthIf_00238 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetTransceiverWakeupMode(
    VAR(uint8, ETHIF_VAR) TrcvIdx,
    P2VAR(EthTrcv_WakeupModeType, ETHIF_APPL_DATA, ETHIF_VAR) TrcvWakeupModePtr);
/* @req SWS_EthIf_00244 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_CheckWakeup(VAR(EcuM_WakeupSourceType, ETHIF_VAR) WakeupSource);
#endif
/* @req SWS_EthIf_00061 */
FUNC(void, ETHIF_CODE)
EthIf_GetPhysAddr(VAR(uint8, ETHIF_VAR) CtrlIdx, P2VAR(uint8, ETHIF_APPL_DATA, ETHIF_VAR) PhysAddrPtr);
/* @req SWS_EthIf_00132 */
FUNC(void, ETHIF_CODE)
EthIf_SetPhysAddr(VAR(uint8, ETHIF_VAR) CtrlIdx, P2CONST(uint8, ETHIF_APPL_DATA, ETHIF_VAR) PhysAddrPtr);
/* @req SWS_EthIf_00139 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_UpdatePhysAddrFilter(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    P2CONST(uint8, ETHIF_APPL_DATA, ETHIF_VAR) PhysAddrPtr,
    VAR(Eth_FilterActionType, ETHIF_VAR) Action);
/* @req SWS_EthIf_00154 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetCurrentTime(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    P2VAR(Eth_TimeStampQualType, ETHIF_APPL_DATA, ETHIF_VAR) timeQualPtr,
    P2VAR(Eth_TimeStampType, ETHIF_APPL_DATA, ETHIF_VAR) timeStampPtr);
/* @req SWS_EthIf_00160 */
FUNC(void, ETHIF_CODE)
EthIf_EnableEgressTimeStamp(VAR(uint8, ETHIF_VAR) CtrlIdx, VAR(Eth_BufIdxType, ETHIF_VAR) BufIdx);
/* @req SWS_EthIf_00166 */
#if (42u == ETHIF_ETH_MAIJORVERSION)
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetEgressTimeStamp(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    VAR(uint8, ETHIF_VAR) BufIdx,
    P2VAR(Eth_TimeStampQualType, ETHIF_APPL_DATA, ETHIF_VAR) timeQualPtr,
    P2VAR(Eth_TimeStampType, ETHIF_APPL_DATA, ETHIF_VAR) timeStampPtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetEgressTimeStamp(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    VAR(Eth_BufIdxType, ETHIF_VAR) BufIdx,
    P2VAR(Eth_TimeStampQualType, ETHIF_APPL_DATA, ETHIF_VAR) timeQualPtr,
    P2VAR(Eth_TimeStampType, ETHIF_APPL_DATA, ETHIF_VAR) timeStampPtr);
#endif
/* @req SWS_EthIf_00172 */
#if (42u == ETHIF_ETH_MAIJORVERSION)
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetIngressTimeStamp(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    P2VAR(Eth_DataType, ETHIF_APPL_DATA, ETHIF_VAR) DataPtr,
    P2VAR(Eth_TimeStampQualType, ETHIF_APPL_DATA, ETHIF_VAR) timeQualPtr,
    P2VAR(Eth_TimeStampType, ETHIF_APPL_DATA, ETHIF_VAR) timeStampPtr);
#elif (19u == ETHIF_ETH_MAIJORVERSION)
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_GetIngressTimeStamp(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    P2CONST(Eth_DataType, ETHIF_APPL_DATA, ETHIF_VAR) DataPtr,
    P2VAR(Eth_TimeStampQualType, ETHIF_APPL_DATA, ETHIF_VAR) timeQualPtr,
    P2VAR(Eth_TimeStampType, ETHIF_APPL_DATA, ETHIF_VAR) timeStampPtr);
#endif
/* @req SWS_EthIf_00067 */
FUNC(BufReq_ReturnType, ETHIF_CODE)
EthIf_ProvideTxBuffer(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    VAR(Eth_FrameType, ETHIF_VAR) FrameType,
    VAR(uint8, ETHIF_VAR) Priority,
    P2VAR(Eth_BufIdxType, ETHIF_APPL_DATA, ETHIF_VAR) BufIdxPtr,
    P2VAR(uint8*, ETHIF_APPL_DATA, ETHIF_VAR) BufPtr,
    P2VAR(uint16, ETHIF_APPL_DATA, ETHIF_VAR) LenBytePtr);
/* @req SWS_EthIf_00075 */
FUNC(Std_ReturnType, ETHIF_CODE)
EthIf_Transmit(
    VAR(uint8, ETHIF_VAR) CtrlIdx,
    VAR(Eth_BufIdxType, ETHIF_VAR) BufIdx,
    VAR(Eth_FrameType, ETHIF_VAR) FrameType,
    VAR(boolean, ETHIF_VAR) TxConfirmation,
    VAR(uint16, ETHIF_VAR) LenByte,
    P2CONST(uint8, ETHIF_APPL_DATA, ETHIF_VAR) PhysAddrPtr);
#if (ETHIF_VERSION_INFO_API == STD_ON)
FUNC(void, ETHIF_CODE) EthIf_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr);
#endif
#if (STD_ON == ETH_GET_CTRLIDX_LIST)
FUNC(Std_ReturnType, Std_ReturnType)
EthIf_GetCtrlIdxList(
    P2VAR(uint8, ETHIF_APPL_DATA, ETHIF_VAR) NumberOfCtrlIdx,
    P2VAR(uint8, ETHIF_APPL_DATA, ETHIF_VAR) CtrlIdxListPtr);
#endif
#if (ETHIF_ENABLE_RX_INTERRUPT == STD_OFF)
/* @req SWS_EthIf_00097 */
FUNC(void, ETHIF_CODE) EthIf_MainFunctionRx(void);
#endif
#if (ETHIF_ENABLE_TX_INTERRUPT == STD_OFF)
/* @req  SWS_EthIf_00113 */
FUNC(void, ETHIF_CODE) EthIf_MainFunctionTx(void);
#endif

FUNC(void, ETHIF_CODE) EthIf_MainFunctionState(void);
#endif
