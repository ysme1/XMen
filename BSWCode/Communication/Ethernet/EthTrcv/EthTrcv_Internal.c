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
 **  FILENAME    : EthTrcv_Internal.c                                          **
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

/**
  \page ISOFT_MISRA_Exceptions  MISRA-C:2012 Compliance Exceptions
    ModeName:EthTrcv_Internal<br>
  RuleSorce:puhua-rule2024-2.rcf 2.3.5

    \li PRQA S 1503 MISRA Dir 2.1 .<br>
    Reason:No impact was assessed and the status quo was maintained.

 */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EthTrcv.h"
#include "EthTrcv_Internal.h"
#include "SchM_EthTrcv.h"
/*******************************************************************************
**                       Version  Check                                       **
*******************************************************************************/
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#define ETHTRCV_START_SEC_CODE
#include "EthTrcv_MemMap.h"
#if (42u == ETHTRCV_MAJORVERSION)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetTrcvModeHandle(uint8 TrcvIdx, P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModeValue)
#elif (44u == ETHTRCV_MAJORVERSION)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetTrcvModeHandle(uint8 TrcvIdx, P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModeValue)
#elif (19u == ETHTRCV_MAJORVERSION)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetTrcvModeHandle(uint8 TrcvIdx, P2VAR(Eth_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModeValue)
#endif /* 42u == ETHTRCV_MAJORVERSION */
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    *TrcvModeValue = EthIf_ReqTrcvMode[TrcvIdx];
    return E_OK;
}

#if (ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetWakeupReasonHandle(
    uint8 TrcvIdx,
    P2VAR(EcuM_WakeupSourceType, AUTOMATIC, ETHTRCV_APPL_DATA) EcuMWakeupSource)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    *EcuMWakeupSource = ECUM_WKSOURCE_POWER;
    return E_OK;
}

FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_ClearWakeupReasonsHandle(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return E_OK;
}
#endif /*ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED*/

FUNC(boolean, ETHTRCV_CODE) EthTrcv_IsTrcvAccessOk(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return TRUE;
}

FUNC(void, ETHTRCV_CODE) EthTrcv_InitCfgHandle(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return;
}

#if (ETHTRCV_SET_TRCV_MODE == STD_ON)
FUNC(void, ETHTRCV_CODE) EthTrcv_SetTrcvModeHandle(uint8 TrcvIdx, uint16 RequestMode)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)RequestMode;
    return;
}
#if (ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED)
FUNC(boolean, ETHTRCV_CODE) EthTrcv_PhyModeIsSleep(uint8 TrcvIdx)
{
    (void)TrcvIdx;
    return FALSE;
}

FUNC(void, ETHTRCV_CODE) EthTrcv_LocalWakeupHandle(uint8 TrcvIdx)
{
    /*change the WAKE_IN_OUT pin voltage level to wake up the PHY,
      or issuing a standby mode command to wake up the PHY(now use the way).*/
    EthTrcv_SetTrcvModeHandle(TrcvIdx, ECR_STANDBY_MODE);
    return;
}
#endif /*ETHTRCV_WAKEUP_SUPPORT != ETHTRCV_WAKEUP_NOT_SUPPORTED*/
#endif /*ETHTRCV_SET_TRCV_MODE == STD_ON*/

#if (ETHTRCV_GET_LINK_STATE == STD_ON)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetLinkStateHandle(uint8 TrcvIdx, P2VAR(boolean, AUTOMATIC, ETHTRCV_APPL_DATA) LinkOk)
{
    (void)TrcvIdx;
    *LinkOk = TRUE;
    return E_OK;
}
#endif

#if (ETHTRCV_GET_BAUD_RATE == STD_ON)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetBaudRateHandle(uint8 TrcvIdx, P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_APPL_DATA) BaudRatePtr)
{
    (void)TrcvIdx;
    (void)BaudRatePtr;
    return E_OK;
}
#endif

#if (ETHTRCV_GET_DUPLEX_MODE == STD_ON)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetDuplexModeHandle(uint8 TrcvIdx, P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_APPL_DATA) DuplexModePtr)
{
    (void)TrcvIdx;
    *DuplexModePtr = ETHTRCV_DUPLEX_MODE_FULL;
    return E_OK;
}
#endif

#if (ETHTRCV_START_AUTO_NEG == STD_ON)
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_StartAutoNegotiationHandle(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return E_OK;
}
#endif

FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_LinkStateActiveHandle(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return E_OK;
}

FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_LinkStateDownHandle(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return E_OK;
}

#if (STD_ON == ETHTRCV_SET_PHYTESTMODE_API)
/*check set PhyTestMode is supported by the hardware or not*/
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_CheckPhyTestModeSupport(uint8 TrcvIdx, EthTrcv_PhyTestModeType Mode)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)Mode;
    return E_OK;
}
#endif /* STD_ON == ETHTRCV_SET_PHYTESTMODE_API*/

#if (STD_ON == ETHTRCV_SET_PHYTESTMODE_API)
/*set PhyTestMode for the given Ethernet transceiver*/
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyTestModeHandle(uint8 TrcvIdx, EthTrcv_PhyTestModeType Mode)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)Mode;
    return E_OK;
}
#endif /* STD_ON == ETHTRCV_SET_PHYTESTMODE_API*/

/*check set PhyLoopBackMode is supported by the hardware or not*/
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_CheckPhyLoopBackSupport(uint8 TrcvIdx, EthTrcv_PhyLoopbackModeType Mode)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)Mode;
    return E_OK;
}

/*set PhyLoopBackMode for the given Ethernet transceiver*/
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_SetPhyLoopBackModeHandle(uint8 TrcvIdx, EthTrcv_PhyLoopbackModeType Mode)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)Mode;
    return E_OK;
}

#if (STD_ON == ETHTRCV_GET_PHYSIGNALQUALITY_API)
/*get PhySignalQuality for the given Ethernet transceiver*/
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetPhySQHandle(uint8 TrcvIdx, uint32* SignalQualityPtr)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)SignalQualityPtr;
    return E_OK;
}
#endif /* STD_ON == ETHTRCV_GET_PHYSIGNALQUALITY_API*/

/*check PhyTxMode is supported by the hardware or not*/
FUNC(Std_ReturnType, ETHTRCV_CODE)
/* PRQA S 1503 ++ */ /* MISRA Rule 2.1 */
EthTrcv_CheckPhyTxModeSupport(uint8 TrcvIdx, EthTrcv_PhyTxModeType Mode)
/* PRQA S 1503 -- */ /* MISRA Rule 2.1 */
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)Mode;
    return E_OK;
}

/*set PhyTxMode for the given Ethernet transceiver*/
FUNC(Std_ReturnType, ETHTRCV_CODE)
/* PRQA S 1503 ++ */ /* MISRA Rule 2.1 */
EthTrcv_SetPhyTxModeHandle(uint8 TrcvIdx, EthTrcv_PhyTxModeType Mode)
/* PRQA S 1503 -- */ /* MISRA Rule 2.1 */
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)Mode;
    return E_OK;
}

/*Trigger the cable diagnostics for the given Ethernet transceiver*/
#if (STD_ON == ETHTRCV_ENABLE_CABLEDIAGNOSTIC_API)
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_RunCableDiagHandle(uint8 TrcvIdx)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    return E_OK;
}
#endif /* STD_ON == ETHTRCV_ENABLE_CABLEDIAGNOSTIC_API*/

/*Trigger the cable diagnostics for the given Ethernet transceiver*/
#if (STD_ON == ETHTRCV_GET_CABLEDIAGNOSTICS_RESULT_API)
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetCableDiagRsHandle(uint8 TrcvIdx, EthTrcv_CableDiagResultType* ResultPtr)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)ResultPtr;
    return E_OK;
}
#endif /* STD_ON == ETHTRCV_GET_CABLEDIAGNOSTICS_RESULT_API*/

#if (STD_ON == ETHTRCV_GET_PHYIDENTIFIER_API)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetPhyIDHandle(uint8 TrcvIdx, uint32* OrgUniqueIdPtr, uint8* ModelNrPtr, uint8* RevisionNrPtr)
{
    /*handle reserved for specific chips*/
    (void)TrcvIdx;
    (void)OrgUniqueIdPtr;
    (void)ModelNrPtr;
    (void)RevisionNrPtr;
    return E_OK;
}
#endif /* STD_ON == ETHTRCV_GET_PHYIDENTIFIER_API*/

#define ETHTRCV_STOP_SEC_CODE
#include "EthTrcv_MemMap.h"
