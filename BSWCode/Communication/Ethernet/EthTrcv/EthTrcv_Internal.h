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
 **  FILENAME    : EthTrcv_Internal.h                                          **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : wanglili                                                    **
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
/*  <VERSION>    <DATE>      <AUTHOR>        <REVISION LOG>
 *  V2.0.0       2020-08-18  wanglili        R19_11 initial version.
 */
#ifndef ETHTRCV_INTERNAL_H_
#define ETHTRCV_INTERNAL_H_
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EthTrcv.h"
#if (STD_ON == ETHTRCV_DEFINE_MIIRXINDICATION)
#include "EthTrcv_Cbk.h"
#endif /*STD_ON == ETHTRCV_DEFINE_MIIRXINDICATION*/
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*Modify according to the state machine and registers of the chip*/
#define ECR_NORMAL_MODE        (0x0000U)
#define ECR_SLEEP_REQUEST_MODE (0x0000U)
#define ECR_STANDBY_MODE       (0x0000U)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                      Global Data Declaration                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/

#if (42u == ETHTRCV_MAJORVERSION)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetTrcvModeHandle(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModeValue); /* PRQA S 3432 */
#elif (44u == ETHTRCV_MAJORVERSION)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetTrcvModeHandle(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModeValue); /* PRQA S 3432 */
#elif (19u == ETHTRCV_MAJORVERSION)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetTrcvModeHandle(
    uint8 TrcvIdx,
    P2VAR(Eth_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModeValue); /* PRQA S 3432 */
#endif /* 42u == ETHTRCV_MAJORVERSION */

#if (ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetWakeupReasonHandle(
    uint8 TrcvIdx,
    P2VAR(EcuM_WakeupSourceType, AUTOMATIC, ETHTRCV_APPL_DATA) EcuMWakeupSource);

extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_ClearWakeupReasonsHandle(uint8 TrcvIdx);
#endif /*ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED*/

extern FUNC(boolean, ETHTRCV_CODE) EthTrcv_IsTrcvAccessOk(uint8 TrcvIdx);

extern FUNC(void, ETHTRCV_CODE) EthTrcv_InitCfgHandle(uint8 TrcvIdx);

#if (ETHTRCV_SET_TRCV_MODE == STD_ON)
#if (ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED)
extern FUNC(boolean, ETHTRCV_CODE) EthTrcv_PhyModeIsSleep(uint8 TrcvIdx);

extern FUNC(void, ETHTRCV_CODE) EthTrcv_LocalWakeupHandle(uint8 TrcvIdx);
#endif /*ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED*/

extern FUNC(void, ETHTRCV_CODE) EthTrcv_SetTrcvModeHandle(uint8 TrcvIdx, uint16 RequestMode);
#endif /*ETHTRCV_SET_TRCV_MODE == STD_ON*/

#if (ETHTRCV_GET_LINK_STATE == STD_ON)
extern FUNC(Std_ReturnType, ETHTRCV_CODE)
    EthTrcv_GetLinkStateHandle(uint8 TrcvIdx, P2VAR(boolean, AUTOMATIC, ETHTRCV_APPL_DATA) LinkOk); /*PRQA S 3432*/
#endif /*ETHTRCV_GET_LINK_STATE == STD_ON*/

#if (ETHTRCV_GET_BAUD_RATE == STD_ON)
extern FUNC(Std_ReturnType, ETHTRCV_CODE)
    EthTrcv_GetBaudRateHandle(uint8 TrcvIdx, P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_APPL_DATA) BaudRatePtr);
#endif /*ETHTRCV_GET_BAUD_RATE == STD_ON*/

#if (ETHTRCV_GET_DUPLEX_MODE == STD_ON)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetDuplexModeHandle(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_APPL_DATA) DuplexModePtr);
#endif /*ETHTRCV_GET_DUPLEX_MODE == STD_ON*/

#if (ETHTRCV_START_AUTO_NEG == STD_ON)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_StartAutoNegotiationHandle(uint8 TrcvIdx);
#endif

extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_LinkStateActiveHandle(uint8 TrcvIdx);

extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_LinkStateDownHandle(uint8 TrcvIdx);

#if (STD_ON == ETHTRCV_SET_PHYTESTMODE_API)
/*check set PhyTestMode is supported by the hardware or not*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_CheckPhyTestModeSupport(uint8 TrcvIdx, EthTrcv_PhyTestModeType Mode);
#endif /* STD_ON == ETHTRCV_SET_PHYTESTMODE_API*/

#if (STD_ON == ETHTRCV_SET_PHYTESTMODE_API)
/*set PhyTestMode for the given Ethernet transceiver*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyTestModeHandle(uint8 TrcvIdx, EthTrcv_PhyTestModeType Mode);
#endif /* STD_ON == ETHTRCV_SET_PHYTESTMODE_API*/

/*check set PhyLoopBackMode is supported by the hardware or not*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE)
    EthTrcv_CheckPhyLoopBackSupport(uint8 TrcvIdx, EthTrcv_PhyLoopbackModeType Mode);

/*set PhyLoopBackMode for the given Ethernet transceiver*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE)
    EthTrcv_SetPhyLoopBackModeHandle(uint8 TrcvIdx, EthTrcv_PhyLoopbackModeType Mode);

#if (STD_ON == ETHTRCV_GET_PHYSIGNALQUALITY_API)
/*get PhySignalQuality for the given Ethernet transceiver*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetPhySQHandle(uint8 TrcvIdx, uint32* SignalQualityPtr);
#endif /* STD_ON == ETHTRCV_GET_PHYSIGNALQUALITY_API*/

/*check PhyTxMode is supported by the hardware or not*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_CheckPhyTxModeSupport(uint8 TrcvIdx, EthTrcv_PhyTxModeType Mode);

/*set PhyTxMode for the given Ethernet transceiver*/
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyTxModeHandle(uint8 TrcvIdx, EthTrcv_PhyTxModeType Mode);

/*Trigger the cable diagnostics for the given Ethernet transceiver*/
#if (STD_ON == ETHTRCV_ENABLE_CABLEDIAGNOSTIC_API)
extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_RunCableDiagHandle(uint8 TrcvIdx);
#endif /* STD_ON == ETHTRCV_ENABLE_CABLEDIAGNOSTIC_API*/

/*Trigger the cable diagnostics for the given Ethernet transceiver*/
#if (STD_ON == ETHTRCV_GET_CABLEDIAGNOSTICS_RESULT_API)
extern FUNC(Std_ReturnType, ETHTRCV_CODE)
    EthTrcv_GetCableDiagRsHandle(uint8 TrcvIdx, EthTrcv_CableDiagResultType* ResultPtr);
#endif /* STD_ON == ETHTRCV_GET_CABLEDIAGNOSTICS_RESULT_API*/

#if (STD_ON == ETHTRCV_GET_PHYIDENTIFIER_API)
extern FUNC(Std_ReturnType, ETHTRCV_CODE)
    EthTrcv_GetPhyIDHandle(uint8 TrcvIdx, uint32* OrgUniqueIdPtr, uint8* ModelNrPtr, uint8* RevisionNrPtr);
#endif /* STD_ON == ETHTRCV_GET_PHYIDENTIFIER_API*/

#endif /* ETHTRCV_INTERNAL_H_ */
