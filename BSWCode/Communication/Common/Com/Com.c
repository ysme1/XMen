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
 **  FILENAME    : Com.c                                                       **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : zhengfei.li                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Implementation for COM                                      **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      REVISION   HISTORY                                    **
*******************************************************************************/
/* <VERSION>  <DATE>    <AUTHOR>      <REVISION LOG>
 *  V2.0.0    20200706  zhengfei.li   Initial version
 *                                    (Upgrade according to the R19_11 standards)
 *  V2.0.1    20211108  zhengfei.li   Optimize enumeration element names, macro names
 *  V2.0.2    20230506  fupeng.yu     Do not copy or handle additional received data
 *                                    If the received I-PDU length is greater than the
 *                                    configured/expected I-PDU length
 *  V2.0.3    20230912  rongbo.hu/fupeng.yu  Com module execution efficiency optimization
 *  V2.0.4    20230919  tong.zhao
 *    1> QAC check,code update
 *    2> Fix bug of rx signal unpack and signal gateway (JIRA: CPT-6970,CPT-6971)
 *  V2.0.5    20231204  sunshengnan  Add (COM_BOOLEAN == signalType) to Com_TxSignalPack
 *                                   and Com_TxGroupSignalPack
 *  V2.0.5    20231117  shengnan.sun  Resolve memory alignment issues.
 *  V2.0.6    20231018  tong.zhao     CPP-423,CPT-6532
 *    Signal and signal group time out optimize.
 *  V2.0.7    20231222  shengnan.sun  CPT-7831 COM_E_SKIPPED_TRANSMISSION is runtime error.
 *  V2.0.8    20231228  shengnan.sun  Resolve QAC warnings.
 *  V2.0.9    20240226  shengnan.sun  Com module execution efficiency optimization
 *                                    and QAC_PH_2024 check.
 *  V2.0.10   20240306  shengnan.sun  support ComRxDataTimeoutAction seted to SUBSTITUTE.
 *  V2.0.11   20240320  shengnan.sun  Modify Com_SetTxSignalBuff and Com_GetTxSignalValue.
 *  V2.0.12   20240411  shengnan.sun  Resolve ComTxModeRepetitionPeriod is error after the
 *                                    ComMinimumDelayTime timer timeout, when ComTxModeMode is DIRECT or MIXED.
 *  V2.0.13   20240423  shengnan.sun  Com module execution efficiency optimization.
 *  V2.0.14   20240516  shengnan.sun  Add Com critical areas.
 *  V2.0.15   20240521  shengnan.sun  Modify Com_StartOfReception to copy data.
 *  V2.0.16   20240521  shengnan.sun  1.Resolve RxGroupSignal gateway error.
 *                                    2.ComDataInvalidAction is NOTIFY, do not repalce InitValue.
 *  V2.0.17   20240906  shengnan.sun  Generated code optimization.
 *  V2.0.18   20240924  shengnan.sun  Modify Com_SwitchIpduTxMode to judge
 *******************************************************************************/

/**
  \page ISOFT_MISRA_Exceptions  MISRA-C:2012 Compliance Exceptions
    ModeName:Com<br>
  RuleSorce:puhua-rule.rcf 2.3.1

    \li PRQA S 3432 MISRA Rule 20.7 .<br>
    Reason:Function-like macros are used to allow more efficient code.

    \li PRQA S 2981 MISRA Rule 2.2 .<br>
    Reason:Init may be necessary for return variant.

    \li PRQA S 1532 MISRA Rule 8.7 .<br>
    Reason:In order to make the module code structure clear, the functions are classified.

    \li PRQA S 4502 MISRA Rule 10.1 .<br>
    Reason:Necessary type conversions.

    \li PRQA S 4340 MISRA Rule 10.5 .<br>
    Reason:Necessary type conversions.

    \li PRQA S 4304 MISRA Rule 10.5 .<br>
    Reason:Necessary type conversions.

    \li PRQA S 3206 MISRA Rule 2.7 .<br>
    Reason:Parameter may be used in other Configuration projects.

    \li PRQA S 3673 MISRA Rule 8.13 .<br>
    Reason:The "input" parameter is defined from AUTOSAR Communication Services API.

    \li PRQA S 0310 MISRA Rule 11.3 .<br>
    Reason:Necessary type conversions.

    \li PRQA S 4391 MISRA Rule 10.8 .<br>
    Reason:Data conversion to a wider range is necessary for accumulation.

    \li PRQA S 1340 MISRA Rule 17.8 .<br>
    Reason:The const "RxDynSignalLength" parameter will not lead to modification.

 */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Com_Internal.h"
#include "Com_Cbk.h"
#include "Det.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#define COM_C_AR_MAJOR_VERSION 4u
#define COM_C_AR_MINOR_VERSION 2u
#define COM_C_AR_PATCH_VERSION 2u
#define COM_C_SW_MAJOR_VERSION 2u
#define COM_C_SW_MINOR_VERSION 0u
#define COM_C_SW_PATCH_VERSION 17u
/*******************************************************************************
**                       Version  Check                                       **
*******************************************************************************/
#if (COM_C_AR_MAJOR_VERSION != COM_H_AR_MAJOR_VERSION)
#error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_AR_MINOR_VERSION != COM_H_AR_MINOR_VERSION)
#error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_AR_PATCH_VERSION != COM_H_AR_PATCH_VERSION)
#error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_SW_MAJOR_VERSION != COM_H_SW_MAJOR_VERSION)
#error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_SW_MINOR_VERSION != COM_H_SW_MINOR_VERSION)
#error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_SW_PATCH_VERSION != COM_H_SW_PATCH_VERSION)
#error "Com.c : Mismatch in Specification Major Version"
#endif
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define COM_START_SEC_VAR_INIT_8
#include "Com_MemMap.h"
static VAR(Com_StatusType, COM_VAR_POWER_ON_INIT) Com_Status = COM_UNINIT;
#define COM_STOP_SEC_VAR_INIT_8
#include "Com_MemMap.h"
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#define COM_START_SEC_VAR_INIT_PTR
#include "Com_MemMap.h"
P2CONST(Com_ConfigType, COM_VAR, COM_CONST)
Com_ConfigStd = NULL_PTR;
#define COM_STOP_SEC_VAR_INIT_PTR
#include "Com_MemMap.h"
#if (COM_IPDUGROUP_NUMBER > 0u)
#define COM_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Com_MemMap.h"
VAR(boolean, COM_VAR) Com_IpduGroupDMEnable[COM_IPDUGROUP_NUMBER];
#define COM_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Com_MemMap.h"
VAR(boolean, COM_VAR) Com_IpduGroupEnable[COM_IPDUGROUP_NUMBER];
#define COM_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Com_MemMap.h"
#endif
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/*Disable all Tx/Rx Pdu state*/
#if (0u < COM_RXIPDU_NUMBER) || (0u < COM_TXIPDU_NUMBER)
static FUNC(void, COM_CODE) Com_SetAllPduRToDisableState(void);
#endif
/* called by Com_Init
 * Init the Pdu Runtime Manager and Buffer*/
static FUNC(void, COM_CODE) Com_PduRTAndBufferInit(void);
/* called by Com_Init
 * Init the Runtime RxSignal/RxGroupSignal Buffer*/
static FUNC(void, COM_CODE) Com_SignalBufferInit(void);
/* RxSignal receive timeout handle*/
#if ((0u < COM_RXIPDU_NUMBER) && (COM_RXSIGNAL_NUMBER > 0u) && (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE))
static FUNC(void, COM_CODE)
    Com_RxSignalTimeOutHandle(Com_RxIPduRunTimeStateType* RxIpduStatePtr, const Com_RxIPduType* RxIpduPtr);
#endif
/* called by Com_MainFunctionTx.
 * tx pdu DM timeout notification*/
#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_NOTIFICATION_ENABLE)
static FUNC(void, COM_CODE) Com_TxDMTimeOutNotification(const Com_TxIPduType* TxIpduPtr);
#endif
/*MaskNewDifferMaskOld filter RxTimeout Init handle*/
#if (0u < COM_RXMASKNEWDIFFERMASKOLD_NUMBER)
static FUNC(void, COM_CODE) Com_RxMaskNewDifferMaskOldTimeOutInit(void);
#endif
/*RxTimeout init handle*/
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE)
static FUNC(void, COM_CODE) Com_RxTimeOutInit(void);
#endif
/*Init the counter of ONE_EVERY_N filter*/
#if (0u < COM_ONEEVERYNFILTERSIGNAL_NUMBER)
static FUNC(void, COM_CODE) Com_OneEveryNCntInit(void);
#endif
/*Send the tx pdu in Com_MainFunctionTx*/
#if (0u < COM_TXIPDU_NUMBER)
static FUNC(void, COM_CODE) Com_MainFunction_SendPdu(PduIdType TxIpduId);
#endif
/* called by Com_MainFunctionTx.
 * the handle of Com_MainFunctionTx,when the tx mode is direct.
 * return the boolean value for the tx pdu need to transmit or not*/
#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER) || (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER)                              \
    || (0u < COM_TX_MODE_TRUE_DIRECT_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_DIRECT_NOREPETITION_NUMBER) \
    || ((0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)                            \
        || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER))
static FUNC(boolean, COM_CODE)
    Com_MainFuncTxDirect(Com_TxIPduRunTimeStateType* TxIpduStatePtr, const Com_TxIPduType* TxIpduPtr, boolean MDTRun);
#endif
/* called by Com_MainFunctionTx.
 * the handle of Com_MainFunctionTx,when the tx mode is period.
 * return the boolean value for the tx pdu need to transmit or not*/
#if (0u < COM_TX_MODE_TRUE_PERIOD_NUMBER) || (0u < COM_TX_MODE_FALSE_PERIOD_NUMBER)  \
    || (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
static FUNC(boolean, COM_CODE)
    Com_MainFuncTxPeriod(Com_TxIPduRunTimeStateType* TxIpduStatePtr, const Com_TxIPduType* TxIpduPtr, boolean MDTRun);
#endif
/* called by Com_MainFunctionTx.
 * the handle of Com_MainFunctionTx,when the tx mode is mixed.
 * return the boolean value for the tx pdu need to transmit or not*/
#if (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
static FUNC(boolean, COM_CODE)
    Com_MainFuncTxMixed(Com_TxIPduRunTimeStateType* TxIpduStatePtr, const Com_TxIPduType* TxIpduPtr, boolean MDTRun);
#endif
/* called by Com_MainFunctionRouteSignals.
 * gateway signal/group signal/signal group/description signal*/
#if ((0u < COM_GWMAPPING_NUMBER) && (0u < COM_RXIPDU_NUMBER) && (0u < COM_TXIPDU_NUMBER))
static FUNC(void, COM_CODE) Com_GwSignal(
    Com_SignalIdType GWMappingId,
    Com_SignalConfigType GWSourceSignalType,
    Com_SignalIdType GWSourceSignalId);
#endif
/* called by Com_GwSignal.
 * gateway signal/group signal/description signal which signal type is COM_UINT8_DYN*/
#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)                                                                               \
    && ((STD_ON == COM_RX_SIGNAL_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE)            \
        || (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE) \
        || (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_DYN_ENABLE))
static FUNC(void, COM_CODE) Com_GwUint8NDYNSignal(
    Com_SignalType SignalType,
    uint16 SignalBufferId,
    uint16 SignalLength,
    Com_SignalConfigType DestSignalType,
    Com_SignalIdType DestSignalId);
#endif
/* gateway signal/group signal/description signal
 * which signal type isn't COM_UINT8_N and COM_UINT8_DYN*/
static void Com_GwNotArraySignal(
    Com_SignalType SignalType,
    uint16 GWSignalBufferId,
    Com_SignalConfigType DestSignalType,
    Com_SignalIdType DestSignalId);
#if (                                                                            \
    ((0u < COM_TXSIGNAL_NUMBER) || (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)) \
    || ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER)))
/*gateway pdu(which include gateway signal and group signal) handle*/
static FUNC(void, COM_CODE) Com_GwSignalOfPduHandle(
    Com_TxIPduRunTimeStateType* TxIpduStatePtr,
    Com_TransferPropertyType SignalTxProperty,
    uint16 RptNum,
    boolean ValueChanged);
#endif
/*Get the GW Signal's New value and Old value*/
static FUNC(uint64, COM_CODE) Com_GwSignalNewOldValueGet(
    Com_SignalType SignalType,
    uint16 GWSignalBufferId,
    uint16 TxSignalValueId,
    uint64* SourceSignalValue);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               This service initializes internal and external interfaces and
 *                     variables of the AUTOSAR COM module layer for the further processing.
 *                     After calling this function the inter-ECU communication is still disabled.
 * ServiceId           0x01
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      Config: Pointer to the COM configuration data.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
void Com_Init(const Com_ConfigType* config) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (NULL_PTR == config)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INIT_ID, COM_E_PARAM_POINTER);
    }
    else if (COM_UNINIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INIT_ID, COM_E_INIT_FAILED);
    }
    else
#endif
    {
        Com_ConfigStd = config;
        Com_PduRTAndBufferInit();
        Com_SignalBufferInit();
        Com_TxSignalTMCStateInit();
#if (0u < COM_IPDUGROUP_NUMBER)
        /*set the IPdu Group to default disable state,DM disable state*/
        (void)ILib_memset(&Com_IpduGroupEnable[0], 0, COM_IPDUGROUP_NUMBER);
        (void)ILib_memset(&Com_IpduGroupDMEnable[0], 0, COM_IPDUGROUP_NUMBER);
#endif /* 0u < COM_IPDUGROUP_NUMBER */
/*set all tx signal group state to don't need to trigger transmit*/
#if (0u < COM_TXSIGNALGROUP_NUMBER)
        Com_TxSignalGroupTriggerFlagInit();
#endif /*0u < COM_TXSIGNALGROUP_NUMBER*/
/*set all rx signal,rx signal group's DM timeout counter to 0*/
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE)
        Com_RxTimeOutInit();
#endif
/*used for signal filter ONE_EVERY_N Mode(Rx and Tx)*/
#if (0u < COM_ONEEVERYNFILTERSIGNAL_NUMBER)
        /*used for signal filter ONE_EVERY_N Mode(Rx and Tx)*/
        Com_OneEveryNCntInit();
#endif /* 0u < COM_ONEEVERYNFILTERSIGNAL_NUMBER */
/*used for signal filter MASKED_NEW_DIFFERS_MASKED_OLD Mode(Rx Signals)*/
#if (0u < COM_RXMASKNEWDIFFERMASKOLD_NUMBER)
        /*used for signal filter MASKED_NEW_DIFFERS_MASKED_OLD Mode(Rx Signals)*/
        Com_RxMaskNewDifferMaskOldTimeOutInit();
#endif /* 0u < COM_RXMASKNEWDIFFERMASKOLD_NUMBER */
        Com_Status = COM_INIT;
    }
    return;
}
/******************************************************************************/
/*
 * Brief               This service stops the inter-ECU communication. All started
 *                     I-PDU groups are stopped and have to be started again, if
 *                     needed, after Com_Init is called. By a call to Com_DeInit
 *                     the AUTOSAR COM module is put into an not initialized state.
 * ServiceId           0x02
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
void Com_DeInit(void) /* PRQA S 1532,1503 */ /* MISRA Rule 8.7,2.1 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_DEINIT_ID, COM_E_UNINIT);
    }
    else
#endif
    {
#if (0u < COM_IPDUGROUP_NUMBER)
        /* clear All IPduGroup Active Flag */
        (void)ILib_memset(&Com_IpduGroupEnable[0], 0, sizeof(Com_IpduGroupEnable));
#endif
#if (0u < COM_RXIPDU_NUMBER) || (0u < COM_TXIPDU_NUMBER)
        Com_SetAllPduRToDisableState();
#endif
        /* set Com_Status */
        Com_Status = COM_UNINIT;
    }
    return;
}

#if (COM_IPDUGROUP_NUMBER > 0u)
/******************************************************************************/
/*
 * Brief               This service starts I-PDU groups.
 * ServiceId           0x03
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ipduGroupVector: I-PDU group vector containing the activation
 *                     state (stopped = 0/started = 1) for all I-PDU groups.
 *                     initialize: flag to request initialization of the I-PDUs which are newly started
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
/* PRQA S 1532,3677 ++ */ /* MISRA Rule 8.7,8.13 */
void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize)
/* PRQA S 1532,3677 -- */ /* MISRA Rule 8.7,8.13 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_IPDUGROUPCONTROL_ID, COM_E_UNINIT);
    }
    else
#endif
    {
        uint8 value;
        /*base ipduGroupVector,set the all i-pdu group to enable or disable */
        for (Com_IpduGroupIdType ipduGroupCnt = 0u; ipduGroupCnt < COM_IPDUGROUP_NUMBER; ++ipduGroupCnt)
        {
            /* PRQA S 2985 ++ */ /* MISRA Rule 2.2 */
            value = ((ipduGroupVector[ipduGroupCnt >> 3u]) >> (ipduGroupCnt & 7u)) & 1u;
            /* PRQA S 2985 -- */ /* MISRA Rule 2.2 */
            Com_IpduGroupEnable[ipduGroupCnt] = 0x01u == value;
        }
/*base i-pdu group state,set all rx pdu to enable or disable.
 * base initialize,select if or not init the rx pdu when state change from disable to enable*/
#if (COM_RXIPDUGROUP_NUMBER > 0u)
        Com_RxIpduController(initialize);
#endif
/*base i-pdu group state,set all tx pdu to enable or disable.
 * base initialize,select if or not init the tx pdu when state change from disable to enable*/
#if (COM_TXIPDUGROUP_NUMBER > 0u)
        Com_TxIpduController(initialize);
#endif
    }
    return;
}
#endif /*COM_IPDUGROUP_NUMBER > 0u*/
/******************************************************************************/
/*
 * Brief               This service enables or disables I-PDU group Deadline Monitoring.
 * ServiceId           0x06
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ipduGroupVector: I-PDU group vector containing the activation
 *                     state (stopped = 0/started = 1) for all I-PDU groups.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#if (COM_IPDUGROUP_NUMBER > 0u)
/* PRQA S 1532,3677 ++ */ /* MISRA Rule 8.7,8.13 */
FUNC(void, COM_CODE)
Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector)
/* PRQA S 1532,3677 -- */ /* MISRA Rule 8.7,8.13 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEPTIONDMCONTROL_ID, COM_E_UNINIT);
    }
    else
#endif
    {
        uint8 value;
        /*base ipduGroupVector,set the all i-pdu group's Rx DM to enable or disable */
        for (Com_IpduGroupIdType ipduGroupCnt = 0u; ipduGroupCnt < COM_IPDUGROUP_NUMBER; ++ipduGroupCnt)
        {
            /* PRQA S 2985 ++ */ /* MISRA Rule 2.2 */
            value = ((ipduGroupVector[ipduGroupCnt >> 3u]) >> (ipduGroupCnt & 7u)) & 1u;
            /* PRQA S 2985 -- */ /* MISRA Rule 2.2 */
            Com_IpduGroupDMEnable[ipduGroupCnt] = 0x01u == value;
        }
/*Set all RxPdu deadline monitoring State and parameter*/
#if (COM_RXIPDUGROUP_NUMBER > 0u) && (0u < COM_RXIPDU_NUMBER)
        Com_RxPduDMCtrHandle();
#endif
    }
    return;
}
#endif /*COM_IPDUGROUP_NUMBER > 0u*/
/******************************************************************************/
/*
 * Brief               Returns the status of the AUTOSAR COM module.
 * ServiceId           0x07
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Com_StatusType(COM_UNINIT and COM_INIT)
 *                     COM_UNINIT: the AUTOSAR COM module is not initialized and not usable
 *                     COM_INIT: the AUTOSAR COM module is initialized and usable
 */
/******************************************************************************/
FUNC(Com_StatusType, COM_CODE)
Com_GetStatus(void) /* PRQA S 1503 */ /* MISRA Rule 2.1 */
{
    return Com_Status;
}
/******************************************************************************/
/*
 * Brief               This service sets all bits of the given Com_IpduGroupVector to 0.
 * ServiceId           0x1c
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     ipduGroupVector: I-PDU group vector to be cleared
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#if (COM_IPDUGROUP_NUMBER > 0u)
FUNC(void, COM_CODE)
Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector) /* PRQA S 1503 */ /* MISRA Rule 2.1 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_CLEARIPDUGROUPVECTOR_ID, COM_E_UNINIT);
    }
    else
#endif
    {
        uint8 vectorByteLength = ((COM_IPDUGROUP_NUMBER - 1u) >> 3u) + 1u;
        (void)ILib_memset(&ipduGroupVector[0], 0, vectorByteLength);
    }
    return;
}
#endif /*COM_IPDUGROUP_NUMBER > 0u*/
/******************************************************************************/
/*
 * Brief               This service sets the value of a bit in an I-PDU group vector.
 * ServiceId           0x1d
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ipduGroupId: ipduGroup used to identify the corresponding bit in the I-PDU group vector
 *                     bitval: New value of the corresponding bit
 * Param-Name[out]     None
 * Param-Name[in/out]  ipduGroupVector: I-PDU group vector to be modified
 * Return              None
 */
/******************************************************************************/
#if (COM_IPDUGROUP_NUMBER > 0u)
/* PRQA S 1532 ++ */ /* MISRA Rule 8.7 */
void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SETIPDUGROUP_ID, COM_E_UNINIT);
    }
    else
#if (0u < COM_IPDUGROUP_NUMBER)
        if (ipduGroupId >= COM_IPDUGROUP_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SETIPDUGROUP_ID, COM_E_PARAM);
    }
    else
#endif
#endif
    {
        /* PRQA S 2985 ++ */ /* MISRA Rule 2.2 */
        uint8 bitValue = 0x01u << (ipduGroupId & 7u);
        /* PRQA S 2985 -- */ /* MISRA Rule 2.2 */
        if (bitval)
        {
            ipduGroupVector[ipduGroupId >> 3u] |= bitValue;
        }
        else
        {
            ipduGroupVector[ipduGroupId >> 3u] &= (uint8)(~bitValue);
        }
    }
    return;
}
#endif /*COM_IPDUGROUP_NUMBER > 0u*/
/*******************************************************************************
**                      Communication Services                                **
*******************************************************************************/
/******************************************************************************/
/*
 * Brief               The service Com_SendSignal updates the signal(include group signal) object
 *                     identified by SignalId with the signal referenced by the SignalDataPtr parameter.
 * ServiceId           0x0a
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant for the same signal. Reentrant for different signals.
 * Param-Name[in]      SignalId: Id of signal to be sent.
 *                     SignalDataPtr: Reference to the signal data to be transmitted.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped
 *                     (or service failed due to development error)
 *                     COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr)
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNAL_ID, COM_E_UNINIT);
    }
    else if (SignalId >= (COM_TXSIGNAL_NUMBER + COM_TXGROUPSIGNAL_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNAL_ID, COM_E_PARAM);
    }
    else if (NULL_PTR == SignalDataPtr)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNAL_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
        /*the signal is Tx Signal*/
#if (((COM_TXSIGNAL_NUMBER > 0u) || (COM_TXGROUPSIGNAL_NUMBER > 0u)) && (0u < COM_TXIPDU_NUMBER))
        ret = Com_SendSignalHandle(SignalId, SignalDataPtr);
#endif
    }
    COM_NOUSED(SignalId);
    COM_NOUSED(SignalDataPtr);
    return ret;
}
/******************************************************************************/
/*
 * Brief               The service Com_SendDynSignal updates the signal object identified by SignalId
 *                     with the signal referenced by the SignalDataPtr parameter.
 * ServiceId           0x21
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant for the same signal. Reentrant for different signals.
 * Param-Name[in]      SignalId: Id of signal to be sent.
 *                     SignalDataPtr: Reference to the signal data to be transmitted.
 *                     Length: Length of the dynamic length signal
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,E_NOT_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     E_NOT_OK: in case the Length is greater than the configured ComSignalLength of this sent signal
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 * development error) COM_BUSY: in case the TP-Buffer is locked
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
Com_SendDynSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr, uint16 Length)
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDDYNSIGNAL_ID, COM_E_UNINIT);
    }
    else if (SignalId >= (COM_TXSIGNAL_NUMBER + COM_TXGROUPSIGNAL_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDDYNSIGNAL_ID, COM_E_PARAM);
    }
    else if (NULL_PTR == SignalDataPtr)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDDYNSIGNAL_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
        /*the signal is Tx Signal*/
#if (((COM_TXSIGNAL_NUMBER > 0u) || (COM_TXGROUPSIGNAL_NUMBER > 0u)) && (0u < COM_TXIPDU_NUMBER))
        ret = Com_SendDynSignalHandle(SignalId, SignalDataPtr, Length);
#endif
    }
    COM_NOUSED(SignalId);
    COM_NOUSED(SignalDataPtr);
    COM_NOUSED(Length);
    return ret;
}
/******************************************************************************/
/*
 * Brief               Com_ReceiveSignal copies the data of the signal identified by SignalId to the location specified
 * by SignalDataPtr. ServiceId           0x0b Sync/Async          Synchronous Reentrancy          Non Reentrant for the
 * same signal. Reentrant for different signals. Param-Name[in]      SignalId: Id of signal to be received.
 * Param-Name[out]     SignalDataPtr: Reference to the location where the received signal data shall be stored
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 * development error) COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr)
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNAL_ID, COM_E_UNINIT);
    }
    else if (SignalId >= (COM_RXSIGNAL_NUMBER + COM_RXGROUPSIGNAL_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNAL_ID, COM_E_PARAM);
    }
    else if (NULL_PTR == SignalDataPtr)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNAL_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (0u < COM_RXIPDU_NUMBER)
        /*the signal is Rx Signal*/
        if (SignalId < COM_RXSIGNAL_NUMBER)
        {
#if (0u < COM_RXSIGNAL_NUMBER)
            ret = Com_ReceiveSignalHandle(SignalId, SignalDataPtr);
#endif /*0u < COM_RXSIGNAL_NUMBER*/
        }
        /*the signal is Rx Group Signal*/
        else
        {
#if (COM_RXSIGNALGROUP_NUMBER > 0u) && (COM_RXGROUPSIGNAL_NUMBER > 0u)
            ret = Com_ReceiveGroupSignalHandle(SignalId, SignalDataPtr);
#endif
        }
#endif /*0u < COM_RXIPDU_NUMBER*/
    }
    COM_NOUSED(SignalId);
    COM_NOUSED(SignalDataPtr);
    return ret;
}
/******************************************************************************/
/*
 * Brief               Com_ReceiveDynSignal copies the data of the signal identified by SignalId to the
 *                     location specified by SignalDataPtr and stores the length of the dynamical length
 *                     signal at the position given by the Length parameter.
 * ServiceId           0x22
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant for the same signal. Reentrant for different signals.
 * Param-Name[in]      SignalId: Id of signal to be received.
 * Param-Name[out]     SignalDataPtr: reference to the location where the received signal data shall be stored
 * Param-Name[in/out]  Length
 *                     in: maximum length that could be received
 *                     out: length of the dynamic length signal
 * Return              uint8(E_OK,E_NOT_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     E_NOT_OK: in case the Length (as in-parameter) is smaller than the received length of the dynamic
 * length signal COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to development
 * error) COM_BUSY: in case the TP-Buffer is locked
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
Com_ReceiveDynSignal(
    Com_SignalIdType SignalId,
    P2VAR(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr,
    /* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
    P2VAR(uint16, AUTOMATIC, COM_APPL_CONST) Length)
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVEDYNSIGNAL_ID, COM_E_UNINIT);
    }
    else if (SignalId >= (COM_RXSIGNAL_NUMBER + COM_RXGROUPSIGNAL_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVEDYNSIGNAL_ID, COM_E_PARAM);
    }
    else if (NULL_PTR == SignalDataPtr)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVEDYNSIGNAL_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (0u < COM_RXIPDU_NUMBER)
        /*the signal is Rx Signal*/
        if (SignalId < COM_RXSIGNAL_NUMBER)
        {
#if ((0u < COM_RXSIGNAL_NUMBER) && (0u < COM_SIGNAL_8BITBUFF_SIZE) && (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE))
            ret = Com_ReceiveDynSignalHandle(SignalId, SignalDataPtr, Length);
#endif /* 0u < COM_RXSIGNAL_NUMBER) && (0u < COM_SIGNAL_8BITBUFF_SIZE) && (STD_ON == \
          COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE */
        }
        /*the signal is Rx Group Signal*/
        else
        {
#if (((COM_RXSIGNALGROUP_NUMBER > 0u) && (COM_RXGROUPSIGNAL_NUMBER > 0u)) && (0u < COM_RXGROUPSIGNAL_8BITBUFF_SIZE)) \
    && (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE)
            ret = Com_ReceiveDynGroupSignalHandle(SignalId, SignalDataPtr, Length);
#endif /* 0u < COM_RXSIGNALGROUP_NUMBER) && (0u < COM_RXGROUPSIGNAL_8BITBUFF_SIZE) && (STD_ON == \
          COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE */
        }
#endif /*0u < COM_RXIPDU_NUMBER*/
    }
    COM_NOUSED(SignalId);
    COM_NOUSED(SignalDataPtr);
    COM_NOUSED(Length);
    return ret;
}
/******************************************************************************/
/*
 * Brief               The service Com_SendSignalGroup copies the content of the associated shadow buffer to the
 *                     associated I-PDU.
 * ServiceId           0x0d
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be sent.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK:service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 *                     development error)
 *                     COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNALGROUP_ID, COM_E_UNINIT);
    }
    else if (SignalGroupId >= COM_TXSIGNALGROUP_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNALGROUP_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if ((0u < COM_TXSIGNALGROUP_NUMBER) && (0u < COM_TXIPDU_NUMBER))
        ret = Com_SendSignalGroupHandle(SignalGroupId);
#endif
    }
    COM_NOUSED(SignalGroupId);
    return ret;
}
/******************************************************************************/
/*
 * Brief               The service Com_ReceiveSignalGroup copies the received signal group from the I-PDU to the
 *                     shadow buffer.
 * ServiceId           0x0e
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be received.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 *                     development error) COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
/* PRQA S 1532,1503 ++ */ /* MISRA Rule 8.7,2.1 */
Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if ((0u < COM_RXSIGNALGROUP_NUMBER) && (0u < COM_RXIPDU_NUMBER))
    PduIdType ipduRef = Com_ConfigStd->ComRxSignalGroup[SignalGroupId].ComIpduRefIndex;
    const Com_RxIPduRunTimeStateType* rxIpduStatePtr = &Com_RxIPduRunTimeState[ipduRef];
#endif
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNALGROUP_ID, COM_E_UNINIT);
    }
    else if (SignalGroupId >= COM_RXSIGNALGROUP_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNALGROUP_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if ((0u < COM_RXSIGNALGROUP_NUMBER) && (0u < COM_RXIPDU_NUMBER))
        uint8 Receiving = rxIpduStatePtr->RxIpduRTStFlag & Com_RX_RECEIVING_EN;
        /*IPDU is receiving data*/
        if (Com_RX_RECEIVING_EN == Receiving)
        {
            ret = COM_BUSY;
        }
        else
        {
            Com_ReceiveSignalGroupHandle(ipduRef, SignalGroupId);
            uint8 activeEnable = rxIpduStatePtr->RxIpduRTStFlag & Com_RX_ACTIVE_EN;
            if (Com_RX_ACTIVE_EN == activeEnable)
            {
                ret = E_OK;
            }
        }
#endif /* 0u < COM_RXSIGNALGROUP_NUMBER) && (0u < COM_RXIPDU_NUMBER */
    }
    COM_NOUSED(SignalGroupId);
    return ret;
}
#if (STD_ON == COM_ENABLE_SIGNAL_GROUP_ARRAY_API)
/******************************************************************************/
/*
 * Brief               The service Com_SendSignalGroupArray copies the content of the provided
 *                     SignalGroupArrayPtr to the associated I-PDU. The provided data shall
 *                     correspond to the array representation of the signal group.
 * ServiceId           0x23
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be sent.
 *                     SignalGroupArrayPtr: Reference to the signal group array.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 * development error) COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
/* PRQA S 1532 ++ */ /* MISRA Rule 8.7 */
Com_SendSignalGroupArray(
    Com_SignalGroupIdType SignalGroupId,
    P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) SignalGroupArrayPtr)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNALGROUPARRAY_ID, COM_E_UNINIT);
    }
    else if (SignalGroupId >= COM_TXSIGNALGROUP_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNALGROUPARRAY_ID, COM_E_PARAM);
    }
    else if (NULL_PTR == SignalGroupArrayPtr)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SENDSIGNALGROUPARRAY_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if ((0u < COM_TXSIGNALGROUP_NUMBER) && (0u < COM_TXIPDU_NUMBER))
        ret = Com_SendSignalGroupArrayHandle(SignalGroupId, SignalGroupArrayPtr);
#endif
    }
    COM_NOUSED(SignalGroupId);
    COM_NOUSED(SignalGroupArrayPtr);
    return ret;
}
#endif /* STD_ON == COM_ENABLE_SIGNAL_GROUP_ARRAY_API */
/******************************************************************************/
/*
 * Brief               The service Com_ReceiveSignalGroupArray copies the received signal group
 *                     array representation from the PDU to the location designated by SignalGroupArrayPtr.
 * ServiceId           0x24
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be received.
 * Param-Name[out]     SignalGroupArrayPtr: reference to the location where the received signal group array shall be
 * stored.
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 *                     development error)
 *                     COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
#if (STD_ON == COM_ENABLE_SIGNAL_GROUP_ARRAY_API)
FUNC(uint8, COM_CODE)
/* PRQA S 3432,1532 ++ */ /* MISRA Rule 20.7,8.7 */
Com_ReceiveSignalGroupArray(
    Com_SignalGroupIdType SignalGroupId,
    P2VAR(uint8, AUTOMATIC, COM_APPL_CONST) SignalGroupArrayPtr)
/* PRQA S 3432,1532 -- */ /* MISRA Rule 20.7,8.7 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNALGROUPARRAY_ID, COM_E_UNINIT);
    }
    else if (SignalGroupId >= COM_RXSIGNALGROUP_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNALGROUPARRAY_ID, COM_E_PARAM);
    }
    else if (NULL_PTR == SignalGroupArrayPtr)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RECEIVESIGNALGROUPARRAY_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if ((0u < COM_RXSIGNALGROUP_NUMBER) && (0u < COM_RXIPDU_NUMBER))
        ret = Com_ReceiveSignalGroupArrayHandle(SignalGroupId, SignalGroupArrayPtr);
#endif
    }
    COM_NOUSED(SignalGroupId);
    COM_NOUSED(SignalGroupArrayPtr);
    return ret;
}
#endif /*STD_ON == COM_ENABLE_SIGNAL_GROUP_ARRAY_API*/
/******************************************************************************/
/*
 * Brief               The service Com_InvalidateSignal invalidates the signal with the given SignalId
 *                     by setting its value to its configured ComSignalDataInvalidValue.
 * ServiceId           0x10
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant for the same signal. Reentrant for different signals.
 * Param-Name[in]      SignalId: Id of signal to be invalidated.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group is stopped, no ComSignalDataInvalidValue
 *                     is configured for the given signalId or service fails due to development error
 *                     COM_BUSY: in case the TP-Buffer is locked
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
/* PRQA S 1532,1503 ++ */ /* MISRA Rule 8.7,2.1 */
Com_InvalidateSignal(Com_SignalIdType SignalId)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INVALIDATESIGNAL_ID, COM_E_UNINIT);
    }
    else if (SignalId >= COM_TXSIGNAL_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INVALIDATESIGNAL_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if ((COM_TXSIGNAL_NUMBER > 0u) || (COM_TXGROUPSIGNAL_NUMBER > 0u)) && (0u < COM_TXIPDU_NUMBER)
        ret = Com_InvalidateSignalHandle(SignalId);
#endif
    }
    COM_NOUSED(SignalId);
    return ret;
}
/******************************************************************************/
/*
 * Brief               The service Com_InvalidateSignalGroup invalidates all group signals of the signal
 *                     group with the given SignalGroupId by setting their values to their configured
 *                     ComSignalDataInvalidValues.
 * ServiceId           0x1b
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be invalidated.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group is stopped, no ComSignalDataInvalidValue
 *                     is configured for any of the group signals or service fails due to development error
 *                     COM_BUSY: in case the TP-Buffer is locked
 */
/******************************************************************************/
FUNC(uint8, COM_CODE)
Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId) /* PRQA S 1503 -- */ /* MISRA Rule 2.1 */
{
    uint8 ret = COM_SERVICE_NOT_AVAILABLE; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INVALIDATESIGNALGROUP_ID, COM_E_UNINIT);
    }
    else if (SignalGroupId >= COM_TXSIGNALGROUP_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_INVALIDATESIGNALGROUP_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if (0u < COM_TXIPDU_NUMBER) && ((COM_TXSIGNAL_NUMBER > 0u) || (COM_TXGROUPSIGNAL_NUMBER > 0u))
        ret = Com_InvalidateSignalGroupHandle(SignalGroupId);
#endif
    }
    COM_NOUSED(SignalGroupId);
    return ret;
}
/******************************************************************************/
/*
 * Brief               By a call to Com_TriggerIPDUSend the I-PDU with the given ID is triggered for transmission.
 * ServiceId           0x17
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      PduId: The I-PDU-ID of the I-PDU that shall be triggered for sending
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 *                     E_OK: I-PDU was triggered for transmission
 *                     E_NOT_OK: I-PDU is stopped, the transmission could not be triggered
 */
/******************************************************************************/
FUNC(Std_ReturnType, COM_CODE)
/* PRQA S 1532 ++ */ /* MISRA Rule 8.7 */
Com_TriggerIPDUSend(PduIdType PduId)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
    Std_ReturnType returnValue = E_NOT_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERIPDUSEND_ID, COM_E_UNINIT);
    }
    else if ((PduId >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (PduId < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERIPDUSEND_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if (0u < COM_TXIPDU_NUMBER)
        returnValue = Com_TriggerIPDUSendHandle(PduId);
#endif
    }
    COM_NOUSED(PduId);
    return returnValue;
}
#if (STD_ON == COM_METADATA_SUPPORT)
/******************************************************************************/
/*
 * Brief               By a call to Com_TriggerIPDUSendWithMetaData the AUTOSAR COM module
 *                     updates its internal metadata for the I-PDU with the given ID by copying the
 *                     metadata from the given position and with respect to the globally configured metadata
 *                     length of the I-PDU. Then the I-PDU is triggered for transmission.
 * ServiceId           0x28
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      PduId: The I-PDU-ID of the I-PDU that shall be triggered for sending
 *                     MetaData: A pointer to the metadata for the triggered send-request
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 *                     E_OK: I-PDU was triggered for transmission
 *                     E_NOT_OK: I-PDU is stopped, the transmission could not be triggered
 */
/******************************************************************************/
FUNC(Std_ReturnType, COM_CODE)
/* PRQA S 3432,1532,3673 ++ */ /* MISRA Rule 20.7,8.7,8.13 */
Com_TriggerIPDUSendWithMetaData(PduIdType PduId, P2VAR(uint8, AUTOMATIC, COM_APPL_CONST) MetaData)
/* PRQA S 3432,1532 -- */ /* MISRA Rule 20.7,8.7 */
{
    Std_ReturnType returnValue = E_NOT_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERIPDUSENDWITHMETADATA_ID, COM_E_UNINIT);
    }
    else if ((PduId >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (PduId < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERIPDUSENDWITHMETADATA_ID, COM_E_PARAM);
    }
    else if ((0u == Com_ConfigStd->ComTxIPdu[PduId - COM_RXIPDU_NUMBER].MetaDataLength) || (NULL_PTR == MetaData))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERIPDUSENDWITHMETADATA_ID, COM_E_PARAM);
    }
    else
#endif
    {
        /*Trigger IPDU(with metadata) send handle*/
#if (0u < COM_TXIPDU_NUMBER)
        returnValue = Com_TriggerIPDUSendWithMetaDataHandle(PduId, MetaData);
#endif
    }
    COM_NOUSED(PduId);
    COM_NOUSED(MetaData);
    return returnValue;
}
#endif /*STD_ON == COM_METADATA_SUPPORT*/
/******************************************************************************/
/*
 * Brief               The service Com_SwitchIpduTxMode sets the transmission mode of the I-PDU referenced by PduId
 * to Mode. In case the transmission mode changes, the new mode shall immediately be effective. In case the
 * requested transmission mode was already active for this I-PDU, the call will have no effect. ServiceId 0x27
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different PduIds. Non reentrant for the same PduId.
 * Param-Name[in]      PduId: Id of the I-PDU of which the transmission mode shall be changed.
 *                     Mode: the transmission mode that shall be set.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
FUNC(void, COM_CODE)
Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SWITCHIPDUTXMODE_ID, COM_E_UNINIT);
    }
    else if ((PduId >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (PduId < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_SWITCHIPDUTXMODE_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if (0u < COM_TXIPDU_NUMBER) && (STD_ON == COM_TMS_ENABLE)
        Com_SwitchIpduTxModeHandle(PduId, Mode);
#endif
    }
    COM_NOUSED(PduId);
    COM_NOUSED(Mode);
    return;
}
/******************************************************************************/
/*
 * Brief               This function performs the processing of the AUTOSAR COM module's receive processing that
 *                     are not directly handled within the COM's functions invoked by the PDU-R, for example *
 * Com_RxIndication.
 * ServiceId           0x18
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different mainFunctionId. Non reentrant for the same instance.
 * Param-Name[in]      mainFunctionId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
FUNC(void, COM_CODE)
Com_MainFunctionRx(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    if (COM_INIT == Com_Status)
    {
#if (0u < COM_RXIPDU_NUMBER)
        PduIdType rxIpduId;
        Com_RxIPduRunTimeStateType* rxIpduStatePtr;
        const Com_RxIPduType* rxIpduPtr;
        uint8 DMEnable;
        uint8 activeEnable;
        uint8 RxIndication;
        for (rxIpduId = 0u; rxIpduId < COM_RXIPDU_NUMBER; ++rxIpduId)
        {
            rxIpduStatePtr = &Com_RxIPduRunTimeState[rxIpduId];
            rxIpduPtr = &Com_ConfigStd->ComRxIPdu[rxIpduId];
            DMEnable = rxIpduStatePtr->RxIpduRTStFlag & Com_RX_DM_EN;
            activeEnable = rxIpduStatePtr->RxIpduRTStFlag & Com_RX_ACTIVE_EN;
            RxIndication = rxIpduStatePtr->RxIpduRTStFlag & Com_RX_INDICATION_EN;
            if (Com_RX_ACTIVE_EN == activeEnable)
            {
                /*signal/signal group RxIndication is DEFERRED in the MainFunctionRx*/
                if (Com_RX_INDICATION_EN == RxIndication)
                {
#if (COM_GWMAPPING_NUMBER > 0u)
                    if (COM_UNUSED_RXIPDUGWID != rxIpduPtr->IpduGwIndex)
                    {
                        Com_RxIpduNeedGw[rxIpduPtr->IpduGwIndex] = TRUE;
                    }
#endif /* COM_GWMAPPING_NUMBER > 0u */
                    /*rx indication handle*/
                    Com_IndicationProcess(rxIpduStatePtr, rxIpduPtr);
                    rxIpduStatePtr->RxIpduRTStFlag &= Com_RX_INDICATION_DIS;
                    /*the rx pdu include signal/signal group which need gateway*/
                }
                /*if the rx DM is enabled*/
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE)
                if (Com_RX_DM_EN == DMEnable)
                {
#if (COM_RXSIGNAL_NUMBER > 0u) && (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE)
                    Com_RxSignalTimeOutHandle(rxIpduStatePtr, rxIpduPtr);
#endif /* COM_RXSIGNAL_NUMBER > 0u) && (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE */

#if (COM_RXSIGNALGROUP_NUMBER > 0u) && (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE)
                    Com_RxSignalGroupTimeOutHandle(rxIpduStatePtr, rxIpduPtr);
#endif /* COM_RXSIGNALGROUP_NUMBER > 0u) && (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE */
                }
#endif /* STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE */
            }
        }
#endif /*0u < COM_RXIPDU_NUMBER*/
    }
    return;
}
/******************************************************************************/
/*
 * Brief               This function performs the processing of the AUTOSAR COM module's transmission activities
 * that are not directly handled within the COM's function invoked by the RTE, for example Com_SendSignal. ServiceId
 * 0x19 Sync/Async          None Reentrancy          None Param-Name[in]      None Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
FUNC(void, COM_CODE)
Com_MainFunctionTx(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    if (COM_INIT == Com_Status)
    {
#if (0u < COM_TXIPDU_NUMBER)
        PduIdType txIpduId;
        const Com_TxIPduType* txIpduPtr;
        Com_TxIPduRunTimeStateType* txIpduStatePtr;
        uint8 activeEnable;
        uint8 TxConfirm;
        uint8 Transmiting;
        for (txIpduId = 0u; txIpduId < COM_TXIPDU_NUMBER; ++txIpduId)
        {
            txIpduStatePtr = &Com_TxIPduRunTimeState[txIpduId];
            activeEnable = txIpduStatePtr->TxIpduRTStFlag & Com_TX_ACTIVE_EN;
            if (Com_TX_ACTIVE_EN == activeEnable)
            {
                boolean ipduMDTRun = FALSE;
                boolean txSendFlag = FALSE;
                txIpduPtr = &Com_ConfigStd->ComTxIPdu[txIpduId];
                /*Tx notification for all signals/signal groups of the Tx Pdu is DEFERRED in the MainFunctionTx*/
#if (STD_ON == COM_TX_SIGNAL_NOTIFICATION_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_NOTIFICATION_ENABLE)
                TxConfirm = txIpduStatePtr->TxIpduRTStFlag & Com_TX_CONFIRM_EN;
                if (Com_TX_CONFIRM_EN == TxConfirm)
                {
                    /*Tx notification for all signals/signal groups of the Tx Pdu*/
                    Com_ConfirmationProcess(txIpduPtr);
                    txIpduStatePtr->TxIpduRTStFlag &= Com_TX_CONFIRM_DIS;
                }
#endif          /* STD_ON == COM_TX_SIGNAL_NOTIFICATION_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_NOTIFICATION_ENABLE */
                /* Calculate DM, if DM > 0u, DM-- every mainfunction */
#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_ENABLE)
                if (txIpduStatePtr->DMCnt > 0u)
                {
                    (txIpduStatePtr->DMCnt) -= 1u;
                    /* DM_TimeOut */
                    if (0u == txIpduStatePtr->DMCnt)
                    {
#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_NOTIFICATION_ENABLE)
                        /* ToutNotification*/
                        Com_TxDMTimeOutNotification(txIpduPtr);
#endif /* STD_ON == COM_TX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE) || (STD_ON == \
          COM_TX_SIG_GROUP_TIMEOUT_NOTIFICATION_ENABLE */
                        /* CancelTx(Direct/N component */
                        txIpduStatePtr->RptNum = 0u;
                        txIpduStatePtr->NTimeCnt = 0u;
                        txIpduStatePtr->TxIpduRTStFlag &= Com_TX_TRANSMITING_DIS;
/*cancel the transmitting tx pdu*/
#if (STD_ON == COM_CANCELLATION_SUPPORT)
                        if (txIpduPtr->ComIPduCancellationSupport)
                        {
                            (void)PduR_ComCancelTransmit(txIpduPtr->ComPduIdRef);
                        }
#endif /* STD_ON == COM_CANCELLATION_SUPPORT */
                    }
                }
#endif /* STD_ON == COM_TX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_ENABLE */
#if (STD_ON == COM_MDT_ENABLE)
                /* Calculate MDT, if MDT > 0u, MDT-- every mainfunction  */
                if (txIpduStatePtr->MDTCnt > 0u)
                {
                    (txIpduStatePtr->MDTCnt) -= 1u;
                    /* MDT Timer > 0u, set MDT running flag */
                    if (txIpduStatePtr->MDTCnt != 0u)
                    {
                        ipduMDTRun = TRUE;
                    }
                }
#endif /* STD_ON == COM_MDT_ENABLE */
                switch (txIpduStatePtr->ipduTxMode)
                {
#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER) || (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_DIRECT_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_DIRECT_NOREPETITION_NUMBER)
                case COM_TX_MODE_DIRECT:
                case COM_TX_MODE_DIRECT_WITHOUT_REPETITION:
                    txSendFlag = Com_MainFuncTxDirect(txIpduStatePtr, txIpduPtr, ipduMDTRun);
                    break;
#endif
#if (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
                case COM_TX_MODE_MIXED:
                case COM_TX_MODE_MIXED_WITHOUT_REPETITION:
                    txSendFlag = Com_MainFuncTxMixed(txIpduStatePtr, txIpduPtr, ipduMDTRun);
                    break;
#endif
#if (0u < COM_TX_MODE_TRUE_PERIOD_NUMBER) || (0u < COM_TX_MODE_FALSE_PERIOD_NUMBER)  \
    || (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
                case COM_TX_MODE_PERIODIC:
                    txSendFlag = Com_MainFuncTxPeriod(txIpduStatePtr, txIpduPtr, ipduMDTRun);
                    break;
#endif
                default:
                    /*do nothing*/
                    break;
                }
                if (txSendFlag)
                {
#if (STD_ON == COM_TXTPPDU_SUPPORT)
                    Transmiting = txIpduStatePtr->TxIpduRTStFlag & Com_TX_TRANSMITING_EN;
                    if ((COM_PDU_TP == txIpduPtr->ComIPduType) && (Com_TX_TRANSMITING_EN == Transmiting))
                    {
                        /* in case a large I-PDU is currently transmitted and the same I-PDU is triggered for
                         * transmission again*/
                        (void)Det_ReportRuntimeError(
                            COM_MODULE_ID,
                            COM_INSTANCE_ID,
                            COM_MAINFUNCTIONTX_ID,
                            COM_E_SKIPPED_TRANSMISSION);
                    }
                    /*this MainFunctionTx need send the tx ipdu */
                    else
#endif /* STD_ON == COM_TXTPPDU_SUPPORT */
                    {
                        Com_MainFunction_SendPdu(txIpduId);
                    }
                }
            }
        }
#endif /*0u < COM_TXIPDU_NUMBER*/
    }
    return;
}
/******************************************************************************/
/*
 * Brief               Calls the signal gateway part of the AUTOSAR COM module to forward received signals to be
 * routed. ServiceId           0x1a Sync/Async          None Reentrancy          None Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
FUNC(void, COM_CODE)
Com_MainFunctionRouteSignals(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (COM_GWMAPPING_NUMBER > 0u)
    if (COM_INIT == Com_Status)
    {
#if ((0u < COM_GWMAPPING_NUMBER) && (0u < COM_RXIPDU_NUMBER) && (0u < COM_TXIPDU_NUMBER))
        const Com_GwMappingType* gwMappingPtr;
        Com_SignalConfigType gwSourceSignalType;
        Com_SignalIdType gwSourceSignalId;
        for (uint16 cnt = 0u; cnt < COM_RXIPDU_GW_NUMBER; ++cnt)
        {
            if (!Com_RxIpduNeedGw[cnt])
            {
                continue;
            }
            uint16 gwMappingEndIndex =
                (cnt == (COM_RXIPDU_GW_NUMBER - 1u)) ? COM_GWMAPPING_NUMBER : Com_RxIpduGwStartId[cnt + 1u];
            for (uint16 index = Com_RxIpduGwStartId[cnt]; index < gwMappingEndIndex; ++index)
            {
                gwMappingPtr = &Com_ConfigStd->ComGwMapping[index];
                gwSourceSignalType = gwMappingPtr->ComGwSourceSignalType;
                gwSourceSignalId = gwMappingPtr->ComGwSourceSignalId;
                Com_GwSignal(index, gwSourceSignalType, gwSourceSignalId);
            }
            Com_RxIpduNeedGw[cnt] = FALSE;
        }
#endif /* 0u < COM_GWMAPPING_NUMBER) && (0u < COM_RXIPDU_NUMBER) && (0u < COM_TXIPDU_NUMBER */
    }
#endif /* COM_GWMAPPING_NUMBER > 0u */
    return;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               Within this API, the upper layer module (called module) shall check whether the
 *                     available data fits into the buffer size reported by PduInfoPtr->SduLength.
 *                     If it fits, it shall copy its data into the buffer provided by PduInfoPtr->SduDataPtr
 *                     and update the length of the actual copied data in PduInfoPtr->SduLength.
 *                     If not, it returns E_NOT_OK without changing PduInfoPtr.
 * ServiceId           0x41
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different PduIds. Non reentrant for the same PduId.
 * Param-Name[in]      TxPduId: ID of the SDU that is requested to be transmitted.
 * Param-Name[out]     None
 * Param-Name[in/out]  PduInfoPtr: Contains a pointer to a buffer (SduDataPtr) to where the SDU
 *                     data shall be copied, and the available buffer size in SduLengh.
 *                     On return, the service will indicate the length of the copied SDU
 *                     data in SduLength.
 * Return              Std_ReturnType
 *                     E_OK: SDU has been copied and SduLength indicates the number of copied bytes.
 *                     E_NOT_OK: No SDU data has been copied. PduInfoPtr must not
 *                     be used since it may contain a NULL pointer or point to invalid data.
 */
/******************************************************************************/
#define COM_START_SEC_COMTRIGGERTRANSMIT_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(Std_ReturnType, COM_CODE)
/* PRQA S 3432,1532 ++ */ /* MISRA Rule 20.7,8.7 */
Com_TriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
/* PRQA S 3432,1532 -- */ /* MISRA Rule 20.7,8.7 */
{
    Std_ReturnType returnValue = E_NOT_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERTRANSMIT_ID, COM_E_UNINIT);
    }
    else if ((TxPduId >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (TxPduId < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERTRANSMIT_ID, COM_E_PARAM);
    }
    else if ((NULL_PTR == PduInfoPtr) || (NULL_PTR == PduInfoPtr->SduDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERTRANSMIT_ID, COM_E_PARAM_POINTER);
    }
    else if (
        (0u < Com_ConfigStd->ComTxIPdu[TxPduId - COM_RXIPDU_NUMBER].MetaDataLength)
        && (NULL_PTR == PduInfoPtr->MetaDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TRIGGERTRANSMIT_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (0u < COM_TXIPDU_NUMBER)
        returnValue = Com_TriggerTransmitHandle(TxPduId, PduInfoPtr);
#endif
    }
    COM_NOUSED(TxPduId);
    COM_NOUSED(PduInfoPtr);
    return returnValue;
}
#define COM_STOP_SEC_COMTRIGGERTRANSMIT_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               Indication of a received I-PDU from a lower layer communication interface module.
 * ServiceId           0x42
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different PduIds. Non reentrant for the same PduId.
 * Param-Name[in]      RxPduId: ID of the received I-PDU.
 *                     PduInfoPtr: Contains the length (SduLength) of the received I-PDU and a pointer to
 *                     a buffer (SduDataPtr) containing the I-PDU.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#define COM_START_SEC_COMRXINDICATION_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE)
/* PRQA S 1532 ++ */ /* MISRA Rule 8.7 */
Com_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RXINDICATION_ID, COM_E_UNINIT);
    }
    else if (RxPduId >= COM_RXIPDU_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RXINDICATION_ID, COM_E_PARAM);
    }
    else if (COM_PDU_NORMAL != Com_ConfigStd->ComRxIPdu[RxPduId].ComIPduType)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RXINDICATION_ID, COM_E_PARAM);
    }
    else if ((NULL_PTR == PduInfoPtr) || (NULL_PTR == PduInfoPtr->SduDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RXINDICATION_ID, COM_E_PARAM_POINTER);
    }
    else if ((0u < Com_ConfigStd->ComRxIPdu[RxPduId].MetaDataLength) && (NULL_PTR == PduInfoPtr->MetaDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_RXINDICATION_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (0u < COM_RXIPDU_NUMBER)
        Com_RxIndicationHandle(RxPduId, PduInfoPtr);
#endif
    }
    COM_NOUSED(RxPduId);
    COM_NOUSED(PduInfoPtr);
    return;
}
#define COM_STOP_SEC_COMRXINDICATION_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               Called after an I-PDU has been received via the TP API,
 *                     the result indicates whether the transmission was successful or not.
 * ServiceId           0x45
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      id: Identification of the received I-PDU.
 *                     result: Result of the reception.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#define COM_START_SEC_COMTPRXINDICATION_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE)
/* PRQA S 1532 ++ */ /* MISRA Rule 8.7 */
Com_TpRxIndication(PduIdType id, Std_ReturnType result)
/* PRQA S 1532 -- */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TPRXINDICATION_ID, COM_E_UNINIT);
    }
    else if (id >= COM_RXIPDU_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TPRXINDICATION_ID, COM_E_PARAM);
    }
    else if (COM_PDU_TP != Com_ConfigStd->ComRxIPdu[id].ComIPduType)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TPRXINDICATION_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if (STD_ON == COM_RXTPPDU_SUPPORT) && (0u < COM_RXIPDU_NUMBER)
        Com_TpRxIndicationHandle(id, result);
#endif /* STD_ON == COM_RXTPPDU_SUPPORT */
    }
    COM_NOUSED(id);
    COM_NOUSED(result);
    return;
}
#define COM_STOP_SEC_COMTPRXINDICATION_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               The lower layer communication interface module confirms the transmission of an IPDU.
 * ServiceId           0x40
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different PduIds. Non reentrant for the same PduId.
 * Param-Name[in]      TxPduId: ID of the I-PDU that has been transmitted.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#define COM_START_SEC_COMTXCONFIRMATION_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE)
Com_TxConfirmation(PduIdType TxPduId) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TXCONFIRMATION_ID, COM_E_UNINIT);
    }
    else if ((TxPduId >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (TxPduId < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TXCONFIRMATION_ID, COM_E_PARAM);
    }
    else if (COM_PDU_NORMAL != Com_ConfigStd->ComTxIPdu[TxPduId - COM_RXIPDU_NUMBER].ComIPduType)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TXCONFIRMATION_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if (0u < COM_TXIPDU_NUMBER)
        Com_TxConfirmationHandle(TxPduId);
#endif
    }
    COM_NOUSED(TxPduId);
    return;
}
#define COM_STOP_SEC_COMTXCONFIRMATION_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               This function is called after the I-PDU has been transmitted on its network, the
 *                     result indicates whether the transmission was successful or not.
 * ServiceId           0x48
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      id: Identification of the transmitted I-PDU.
 *                     result: Result of the transmission of the I-PDU.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#define COM_START_SEC_COMTPTXCONFIRMATION_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE)
Com_TpTxConfirmation(PduIdType id, Std_ReturnType result) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TPTXCONFIRMATION_ID, COM_E_UNINIT);
    }
    else if ((id >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (id < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TPTXCONFIRMATION_ID, COM_E_PARAM);
    }
    else if (COM_PDU_TP != Com_ConfigStd->ComTxIPdu[id - COM_RXIPDU_NUMBER].ComIPduType)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_TPTXCONFIRMATION_ID, COM_E_PARAM);
    }
    else
#endif
    {
#if ((0u < COM_TXIPDU_NUMBER) && (STD_ON == COM_TXTPPDU_SUPPORT))
        Com_TpTxConfirmationHandle(id, result);
#endif
    }
    COM_NOUSED(id);
    COM_NOUSED(result);
    return;
}
#define COM_STOP_SEC_COMTPTXCONFIRMATION_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               This function is called at the start of receiving an N-SDU. The N-SDU might be
 *                     fragmented into multiple N-PDUs (FF with one or more following CFs) or might
 *                     consist of a single N-PDU (SF).
 * ServiceId           0x46
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      id: Identification of the I-PDU.
 *                     info: Pointer to a PduInfoType structure containing the payload
 *                     data (without protocol information) and payload length of the
 *                     first frame or single frame of a transport protocol I-PDU reception.
 *                     Depending on the global parameter MetaDataLength, additional bytes containing
 *                     MetaData (e.g. the CAN ID) are appended after the payload data, increasing the length
 *                     accordingly. If neither first/single frame data nor MetaData
 *                     are available, this parameter is set to NULL_PTR.
 *                     TpSduLength: Total length of the N-SDU to be received.
 * Param-Name[out]     bufferSizePtr: Available receive buffer in the receiving module. This parameter will
 *                     be used to compute the Block Size (BS) in the transport protocol module.
 * Param-Name[in/out]  None
 * Return              BufReq_ReturnType(BUFREQ_OK,BUFREQ_E_NOT_OK,BUFREQ_E_OVFL)
 *                     BUFREQ_OK: Connection has been accepted. bufferSizePtr
 *                     indicates the available receive buffer; reception is continued.
 *                     If no buffer of the requested size is available, a receive buffer
 *                     size of 0 shall be indicated by bufferSizePtr.
 *                     BUFREQ_E_NOT_OK: Connection has been rejected; reception is aborted. bufferSizePtr remains
 * unchanged. BUFREQ_E_OVFL: No buffer of the required length can be provided; reception is aborted. bufferSizePtr
 * remains unchanged.
 */
/******************************************************************************/
#define COM_START_SEC_COMSTARTOFRECEPTION_CALLBACK_CODE
#include "Com_MemMap.h"
/* PRQA S 1532,3432 ++ */ /* MISRA Rule 8.7,20.7 */
FUNC(BufReq_ReturnType, COM_CODE)
Com_StartOfReception(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, COM_APPL_DATA) bufferSizePtr)
/* PRQA S 1532,3432 -- */ /* MISRA Rule 8.7,20.7 */
{
    BufReq_ReturnType bufReq = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_STARTOFRECEPTION_ID, COM_E_UNINIT);
    }
    else if ((id >= COM_RXIPDU_NUMBER) || (COM_PDU_TP != Com_ConfigStd->ComRxIPdu[id].ComIPduType))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_STARTOFRECEPTION_ID, COM_E_PARAM);
    }
    else if (
        ((0u < Com_ConfigStd->ComRxIPdu[id].MetaDataLength) && ((NULL_PTR == info) || (NULL_PTR == info->MetaDataPtr)))
        || (((NULL_PTR != info) && (0u < info->SduLength)) && (NULL_PTR == info->SduDataPtr))
        || (NULL_PTR == bufferSizePtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_STARTOFRECEPTION_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (STD_ON == COM_RXTPPDU_SUPPORT) && (0u < COM_RXIPDU_NUMBER)
        bufReq = Com_StartOfReceptionHandle(id, info, TpSduLength, bufferSizePtr);
#endif
    }
    COM_NOUSED(id);
    COM_NOUSED(info);
    COM_NOUSED(TpSduLength);
    COM_NOUSED(bufferSizePtr);
    return bufReq;
}
#define COM_STOP_SEC_COMSTARTOFRECEPTION_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               This function is called to provide the received data of an I-PDU segment (N-PDU) to the upper
 * layer. Each call to this function provides the next part of the I-PDU data. The size of the remaining data is written
 * to the position indicated by bufferSizePtr. ServiceId           0x44 Sync/Async          Synchronous Reentrancy
 * Reentrant Param-Name[in]      id: Identification of the received I-PDU. info: Provides the source buffer (SduDataPtr)
 * and the number of bytes to be copied (SduLength). An SduLength of 0 can be used to query the current amount of
 * available buffer in the upper layer module. In this case, the SduDataPtr may be a NULL_PTR. Param-Name[out]
 * bufferSizePtr: Available receive buffer after data has been copied. Param-Name[in/out]  None Return BufReq_ReturnType
 *                     BUFREQ_OK: Data copied successfully
 *                     BUFREQ_E_NOT_OK: Data was not copied because an error occurred.
 */
/******************************************************************************/
#define COM_START_SEC_COMCOPYRXDATA_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(BufReq_ReturnType, COM_CODE)
/* PRQA S 3432,1532 ++ */ /* MISRA Rule 20.7,8.7 */
Com_CopyRxData(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, COM_APPL_DATA) bufferSizePtr)
/* PRQA S 3432,1532 -- */ /* MISRA Rule 20.7,8.7 */
{
    BufReq_ReturnType bufReq = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYRXDATA_ID, COM_E_UNINIT);
    }
    else if (id >= COM_RXIPDU_NUMBER)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYRXDATA_ID, COM_E_PARAM);
    }
    else if (COM_PDU_TP != Com_ConfigStd->ComRxIPdu[id].ComIPduType)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYRXDATA_ID, COM_E_PARAM);
    }
    else if ((NULL_PTR == info) || (NULL_PTR == bufferSizePtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYRXDATA_ID, COM_E_PARAM_POINTER);
    }
    else if ((0u < Com_ConfigStd->ComRxIPdu[id].MetaDataLength) && (NULL_PTR == info->MetaDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYRXDATA_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (STD_ON == COM_RXTPPDU_SUPPORT) && (0u < COM_RXIPDU_NUMBER)
        bufReq = Com_CopyRxDataHandle(id, info, bufferSizePtr);
#endif
    }
    COM_NOUSED(id);
    COM_NOUSED(info);
    COM_NOUSED(bufferSizePtr);
    return bufReq;
}
#define COM_STOP_SEC_COMCOPYRXDATA_CALLBACK_CODE
#include "Com_MemMap.h"
/******************************************************************************/
/*
 * Brief               This function is called to acquire the transmit data of an I-PDU segment (N-PDU).
 *                     Each call to this function provides the next part of the I-PDU data unless retry->TpDataState
 *                     is TP_DATARETRY. In this case the function restarts to copy the data beginning at the offset
 *                     from the current position indicated by retry->TxTpDataCnt. The size of the remaining data is
 *                     written to the position indicated by availableDataPtr.
 * ServiceId           0x43
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      id: Identification of the transmitted I-PDU.
 *                     retry: This parameter is used to acknowledge transmitted data or to retransmit data after
 * transmission problems. Param-Name[out]     availableDataPtr: Indicates the remaining number of bytes that are
 * available in the upper layer module's Tx buffer. availableDataPtr can be used by TP modules that support dynamic
 * payload lengths (e.g. FrIsoTp) to determine the size of the following CFs. Param-Name[in/out]  None Return
 * BufReq_ReturnType BUFREQ_OK: Data has been copied to the transmit buffer completely as requested. BUFREQ_E_BUSY:
 * Request could not be fulfilled, because the required amount of Tx data is not available. The lower layer module may
 * retry this call later on. No data has been copied. BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
 */
/******************************************************************************/
#define COM_START_SEC_COMCOPYTXDATA_CALLBACK_CODE
#include "Com_MemMap.h"
FUNC(BufReq_ReturnType, COM_CODE)
/* PRQA S 3432,1532 ++ */ /* MISRA Rule 20.7,8.7 */
Com_CopyTxData(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) info,
    P2CONST(RetryInfoType, AUTOMATIC, COM_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, COM_APPL_DATA) availableDataPtr)
/* PRQA S 3432,1532 ++ */ /* MISRA Rule 20.7,8.7 */
{
    BufReq_ReturnType bufReq = BUFREQ_E_NOT_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
#if (STD_ON == COM_DEV_ERROR_DETECT)
    if (COM_INIT != Com_Status)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYTXDATA_ID, COM_E_UNINIT);
    }
    else if ((id >= (COM_RXIPDU_NUMBER + COM_TXIPDU_NUMBER)) || (id < COM_RXIPDU_NUMBER))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYTXDATA_ID, COM_E_PARAM);
    }
    else if (COM_PDU_TP != Com_ConfigStd->ComTxIPdu[id - COM_RXIPDU_NUMBER].ComIPduType)
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYTXDATA_ID, COM_E_PARAM);
    }
    else if ((NULL_PTR == info) || (NULL_PTR == availableDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYTXDATA_ID, COM_E_PARAM_POINTER);
    }
    else if ((0u < info->SduLength) && (NULL_PTR == info->SduDataPtr))
    {
        (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_COPYTXDATA_ID, COM_E_PARAM_POINTER);
    }
    else
#endif
    {
#if ((0u < COM_TXIPDU_NUMBER) && (STD_ON == COM_TXTPPDU_SUPPORT))
        bufReq = Com_CopyTxDataHandle(id, info, retry, availableDataPtr);
#endif
    }
    COM_NOUSED(id);
    COM_NOUSED(info);
    COM_NOUSED(retry);
    COM_NOUSED(availableDataPtr);
    return bufReq;
}
#define COM_STOP_SEC_COMCOPYTXDATA_CALLBACK_CODE
#include "Com_MemMap.h"
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
#if (0u < COM_RXIPDU_NUMBER) || (0u < COM_TXIPDU_NUMBER)
/******************************************************************************/
/*
 * Brief               Disable all Tx/Rx Pdu state
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_SetAllPduRToDisableState(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    uint16 cirCnt;
#if (0u < COM_RXIPDU_NUMBER)
    /* clear All Rx IPdu Active Flag */
    Com_RxIPduRunTimeStateType* rxIpduStatePtr;
    for (cirCnt = 0u; cirCnt < COM_RXIPDU_NUMBER; ++cirCnt)
    {
        rxIpduStatePtr = &Com_RxIPduRunTimeState[cirCnt];
        rxIpduStatePtr->RxIpduRTStFlag &= Com_RX_ACTIVE_DIS;
    }
#endif /* 0u < COM_RXIPDU_NUMBER */
#if (0u < COM_TXIPDU_NUMBER)
    /* clear All Tx IPdu Active Flag */
    Com_TxIPduRunTimeStateType* txIpduStatePtr;
    for (cirCnt = 0u; cirCnt < COM_TXIPDU_NUMBER; ++cirCnt)
    {
        txIpduStatePtr = &Com_TxIPduRunTimeState[cirCnt];
        txIpduStatePtr->TxIpduRTStFlag &= Com_TX_ACTIVE_DIS;
    }
#endif /* 0u < COM_TXIPDU_NUMBER */
}
#endif
/******************************************************************************/
/*
 * Brief               Init the Pdu Runtime Manager and Buffer
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_PduRTAndBufferInit(void)
{
#if (0u < COM_RXIPDU_NUMBER)
    /* Rx IPdu's RunTimeState init */
    (void)ILib_memcpy(&Com_RxIPduRunTimeState[0], &Com_RxIPduInitState[0], sizeof(Com_RxIPduRunTimeState));
#endif
#if (0u < COM_TXIPDU_NUMBER)
    /* Tx IPdu's RunTimeState init */
    (void)ILib_memcpy(&Com_TxIPduRunTimeState[0], &Com_TxIPduInitState[0], sizeof(Com_TxIPduRunTimeState));
#endif
#if (0u < COM_TXIPDUBUFF_SIZE)
    /* TxIPdu Init value, based on signal or group signal init value */
    (void)ILib_memcpy(&Com_TxIPduRuntimeBuff[0], &Com_TxIPduInitValue[0], sizeof(Com_TxIPduRuntimeBuff));
#endif
#if (0u < COM_RXIPDUBUFF_SIZE)
    /* RxIPdu Init value, based on signal or group signal init value */
    (void)ILib_memcpy(&Com_RxIPduRuntimeBuff[0], &Com_RxIPduInitValue[0], sizeof(Com_RxIPduRuntimeBuff));
#endif
#if (COM_GWMAPPING_NUMBER > 0u)
    (void)ILib_memset(&Com_RxIpduNeedGw[0], 0, COM_RXIPDU_GW_NUMBER);
#endif
    return;
}

/* called by Com_Init
 * Init the Runtime RxSignal/RxGroupSignal Buffer*/
static FUNC(void, COM_CODE) Com_SignalBufferInit(void)
{
#if (0u < COM_SIGNAL_BOOLBUFF_SIZE)
    /* Bool signal Runtime value, based on bool signals or dest description(source description signals are not
     * included) signals init value */
#if (0u < COM_RXGROUPSIGNAL_BOOLBUFF_SIZE)
    (void)ILib_memcpy(
        &Com_RxGroupSignalBoolShadowBuff[0],
        &Com_SignalBoolInitValue[0],
        sizeof(Com_RxGroupSignalBoolShadowBuff));
#endif /*0u < COM_RXGROUPSIGNAL_BOOLBUFF_SIZE*/
    (void)ILib_memcpy(&Com_SignalBoolRuntimeBuff[0], &Com_SignalBoolInitValue[0], sizeof(Com_SignalBoolRuntimeBuff));
#endif /* 0u < COM_SIGNAL_BOOLBUFF_SIZE */
#if (0u < COM_SIGNAL_8BITBUFF_SIZE)
    /* 8Bit signal Runtime value, based on uint8, sint8, uint8N,uint8DYN signals or dest description(source
     * description signals are not included) init value */
#if (0u < COM_RXGROUPSIGNAL_8BITBUFF_SIZE)
    (void)
        ILib_memcpy(&Com_RxGroupSignal8BitShadowBuff[0], &Com_Signal8BitInitValue[0], COM_RXGROUPSIGNAL_8BITBUFF_SIZE);
#endif /* 0u < COM_RXGROUPSIGNAL_8BITBUFF_SIZE */
    (void)ILib_memcpy(&Com_Signal8BitRuntimeBuff[0], &Com_Signal8BitInitValue[0], COM_SIGNAL_8BITBUFF_SIZE);
#endif /* 0u < COM_SIGNAL_8BITBUFF_SIZE */
#if (0u < COM_SIGNAL_16BITBUFF_SIZE)
    /* 16Bit signal Runtime value, based on uint16, sint16 signals or dest description(source description signals
     * are not included) signals init value */
#if (0u < COM_RXGROUPSIGNAL_16BITBUFF_SIZE)
    (void)ILib_memcpy(
        &Com_RxGroupSignal16BitShadowBuff[0],
        &Com_Signal16BitInitValue[0],
        sizeof(Com_RxGroupSignal16BitShadowBuff));
#endif /* 0u < COM_RXGROUPSIGNAL_16BITBUFF_SIZE */
    (void)ILib_memcpy(&Com_Signal16BitRuntimeBuff[0], &Com_Signal16BitInitValue[0], sizeof(Com_Signal16BitRuntimeBuff));
#endif /* 0u < COM_SIGNAL_16BITBUFF_SIZE */
#if (0u < COM_SIGNAL_32BITBUFF_SIZE)
    /* 32Bit signal Runtime value, based on uint32, sint32,float32 signals or dest description(source description
     * signals are not included) signals init value */
#if (0u < COM_RXGROUPSIGNAL_32BITBUFF_SIZE)
    (void)ILib_memcpy(
        &Com_RxGroupSignal32BitShadowBuff[0],
        &Com_Signal32BitInitValue[0],
        sizeof(Com_RxGroupSignal32BitShadowBuff));
#endif /* 0u < COM_RXGROUPSIGNAL_32BITBUFF_SIZE */
    (void)ILib_memcpy(&Com_Signal32BitRuntimeBuff[0], &Com_Signal32BitInitValue[0], sizeof(Com_Signal32BitRuntimeBuff));
#endif /* 0u < COM_SIGNAL_32BITBUFF_SIZE */
#if (0u < COM_SIGNAL_64BITBUFF_SIZE)
    /* 64Bit signal Runtime value, based on uint64, sint64,float64 signals or dest description(source description
     * signals are not included) signals init value */
#if (0u < COM_RXGROUPSIGNAL_64BITBUFF_SIZE)
    (void)ILib_memcpy(
        &Com_RxGroupSignal64BitShadowBuff[0],
        &Com_Signal64BitInitValue[0],
        sizeof(Com_RxGroupSignal64BitShadowBuff));
#endif /* 0u < COM_RXGROUPSIGNAL_32BITBUFF_SIZE */
    (void)ILib_memcpy(&Com_Signal64BitRuntimeBuff[0], &Com_Signal64BitInitValue[0], sizeof(Com_Signal64BitRuntimeBuff));
#endif /* 0u < COM_SIGNAL_64BITBUFF_SIZE */
    return;
}
#if ((0u < COM_RXIPDU_NUMBER) && (COM_RXSIGNAL_NUMBER > 0u) && (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE))
/******************************************************************************/
/*
 * Brief               RxSignal receive timeout handle
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      rxIpduId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              boolean
 */
/******************************************************************************/
static FUNC(void, COM_CODE)
    Com_RxSignalTimeOutHandle(Com_RxIPduRunTimeStateType* RxIpduStatePtr, const Com_RxIPduType* RxIpduPtr)
{
    Com_RxSigTimeoutIdType ipduSignalTimeoutRefNumber, cnt;
    Com_SignalIdType rxSignalId;
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ACTION_REPLACE_ENABLE) \
    || (STD_ON == COM_RX_SIGNAL_TIMEOUT_ACTION_SUBSTITUTE_ENABLE)
    Com_RxDataTimeoutActionType timeoutAction;
    Com_SignalType signalType;
    uint16 initValueLength;
    uint16 initValueId;
    uint16 substituteBufId = COM_UNUSED_UINT16;
#endif
    uint16* rxSignalTimeoutCnt;
    const Com_RxSignalType* rxSignalPtr;
#if (COM_RXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
    Com_SignalIdType maskNewDifferMaskOldId;
#endif

    ipduSignalTimeoutRefNumber = RxIpduPtr->ComIPduSignalsTimeoutRefNumber;
    cnt = RxIpduPtr->ComIPduSignalsTimeoutRefStartId;
    for (; cnt < ipduSignalTimeoutRefNumber; ++cnt)
    {
        rxSignalId = Com_TimeoutRxSignalRef[cnt];
        /* PRQA S 2983 ++ */ /* MISRA Rule 2.2*/
        rxSignalPtr = &Com_ConfigStd->ComRxSignal[rxSignalId];
        /* PRQA S 2983 -- */ /* MISRA Rule 2.2*/
        rxSignalTimeoutCnt = &Com_RxSignalTimeOutCnt[cnt];
        if (*rxSignalTimeoutCnt > 0u)
        {
            *rxSignalTimeoutCnt -= 1u;
            if (0u == *rxSignalTimeoutCnt)
            {
/*let pass any value for the filter MASKED_NEW_DIFFERS_MASKED_OLD after an RX deadline timeout*/
#if (COM_RXMASKNEWDIFFERMASKOLD_NUMBER > 0u) && (COM_RXSIGNAL_FILTERTYPE_MAX_NUMBER > 0u)
                if ((COM_UNUSED_RXSIGNALFILTERID != rxSignalPtr->ComFilterIndex)
                    && (COM_MASKED_NEW_DIFFERS_MASKED_OLD == rxSignalPtr->ComFilterAlgorithm))
                {
                    maskNewDifferMaskOldId = rxSignalPtr->ComFilterIndex;
                    Com_MaskNewDifferMaskOldTimeOut[maskNewDifferMaskOldId] = TRUE;
                }
#endif
                /*handle the timeout replace action*/
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ACTION_REPLACE_ENABLE) \
    || (STD_ON == COM_RX_SIGNAL_TIMEOUT_ACTION_SUBSTITUTE_ENABLE)
                timeoutAction = Com_RxSignalDataTimeoutActionCfg[cnt];
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ACTION_SUBSTITUTE_ENABLE)
                substituteBufId = Com_RxSignalSubstituteValueIdRef[cnt];
#endif
                Com_RxDataTimeOutActionHandle(
                    RxIpduStatePtr,
                    RxIpduPtr,
                    timeoutAction,
                    (const void*)rxSignalPtr,
                    TRUE,
                    substituteBufId);
#endif /* STD_ON == COM_RX_SIGNAL_TIMEOUT_ACTION_REPLACE_ENABLE || STD_ON == \
          COM_RX_SIGNAL_TIMEOUT_ACTION_SUBSTITUTE_ENABLE */
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE)
                if (NULL_PTR != Com_RxSignalTimeoutNotificationCfg[cnt])
                {
                    Com_RxSignalTimeoutNotificationCfg[cnt]();
                }
#endif /* STD_ON == COM_RX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE */
                *rxSignalTimeoutCnt = Com_RxSignalTimeoutVal[cnt];
            }
        }
    }
    COM_NOUSED(RxIpduStatePtr);
    return;
}
#endif

#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE) || (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_NOTIFICATION_ENABLE)
/******************************************************************************/
/*
 * Brief               Called by Com_MainFunctionTx.
 *                     tx pdu DM timeout notification.
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      TxIpduPtr
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_TxDMTimeOutNotification(const Com_TxIPduType* TxIpduPtr)
{
#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE)
    Com_TxSignalIdType txSignalNumber, cnt;
    const Com_TxSignalType* txSignalPtr;
    txSignalNumber = TxIpduPtr->ComIPduSignalsRefNumber;
    cnt = TxIpduPtr->ComIpduSignalRefStartId;
    Com_TxSignalTimeoutIdType txSigTimeoutIndex;
    for (; cnt < txSignalNumber; ++cnt)
    {
        txSignalPtr = &Com_ConfigStd->ComTxSignal[cnt];
        txSigTimeoutIndex = txSignalPtr->ComTimeoutIndex;
        if (NULL_PTR != Com_TxSignalTimeoutNotificationCfg[txSigTimeoutIndex])
        {
            Com_TxSignalTimeoutNotificationCfg[txSigTimeoutIndex]();
        }
    }
#endif /* STD_ON == COM_TX_SIGNAL_TIMEOUT_NOTIFICATION_ENABLE */
#if (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_NOTIFICATION_ENABLE)
    Com_TxSignalGroupIdType signalGroupNumber, signalGroupId;
    signalGroupNumber = TxIpduPtr->ComIPduSignalGroupsRefNumber;
    signalGroupId = TxIpduPtr->ComIPduSignalGroupsRefStartId;
    const Com_TxSignalGroupType* txSignalGroupPtr;
    Com_TxSigGrpTimeoutIdType timeoutIndex;
    for (; signalGroupId < signalGroupNumber; ++signalGroupId)
    {
        txSignalGroupPtr = &Com_ConfigStd->ComTxSignalGroup[signalGroupId];
        timeoutIndex = txSignalGroupPtr->ComTimeoutIndex;
        if (NULL_PTR != Com_TxSigGrpTimeoutNotificationCfg[timeoutIndex])
        {
            Com_TxSigGrpTimeoutNotificationCfg[timeoutIndex]();
        }
    }
#endif /* STD_ON == COM_TX_SIG_GROUP_TIMEOUT_NOTIFICATION_ENABLE */
    return;
}
#endif

#if (0u < COM_RXMASKNEWDIFFERMASKOLD_NUMBER)
/******************************************************************************/
/*
 * Brief               MaskNewDifferMaskOld filter RxTimeout Init handle
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_RxMaskNewDifferMaskOldTimeOutInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    (void)ILib_memset(&Com_MaskNewDifferMaskOldTimeOut[0], 0, COM_RXMASKNEWDIFFERMASKOLD_NUMBER);
}
#endif
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE) || (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE)
/******************************************************************************/
/*
 * Brief               RxTimeout init handle
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_RxTimeOutInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    /*set all rx signal,rx signal group's DM timeout counter to 0*/
#if (STD_ON == COM_RX_SIGNAL_TIMEOUT_ENABLE)
    (void)ILib_memset(&Com_RxSignalTimeOutCnt[0], 0, sizeof(Com_RxSignalTimeOutCnt));
#endif /*COM_RXSIGNAL_NUMBER > 0u*/
#if (STD_ON == COM_RX_SIG_GROUP_TIMEOUT_ENABLE)
    (void)ILib_memset(&Com_RxSignalGroupTimeOutCnt[0], 0, sizeof(Com_RxSignalGroupTimeOutCnt));
#endif
}
#endif

#if (0u < COM_ONEEVERYNFILTERSIGNAL_NUMBER)
/******************************************************************************/
/*
 * Brief               Init the counter of ONE_EVERY_N filter
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
FUNC(void, COM_CODE)
static Com_OneEveryNCntInit(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{
    (void)ILib_memset(&Com_OneEveryNcnt[0], 0, sizeof(Com_OneEveryNcnt));
}
#endif

#if (0u < COM_TXIPDU_NUMBER)
/******************************************************************************/
/*
 * Brief               Send the tx pdu in Com_MainFunctionTx
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      TxIpduId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_MainFunction_SendPdu(PduIdType TxIpduId)
{
    Com_TxIPduRunTimeStateType* txIpduStatePtr = &Com_TxIPduRunTimeState[TxIpduId];
    const Com_TxIPduType* txIpduPtr = &Com_ConfigStd->ComTxIPdu[TxIpduId];
    PduInfoType pduInfo;
    Com_TxIpduBufIdType ipduBufferId = txIpduPtr->ComTxIPduBufIndex;
    uint16 ipduLength = txIpduStatePtr->TxIpduLength;

#if (STD_ON == COM_TX_IPDU_COUNTER_ENABLE)
    uint8 txPduCounter = 0u;
    if (COM_UNUSED_TXIPDUCOUNTERID != txIpduPtr->ComIPduCounterIndex)
    {
        /*Pack the counter value in the pdu buffer*/
        Com_PackCounterValue(txIpduStatePtr, txIpduPtr);
        /*recover the active counter value if the transmit is E_NOT_OK*/
        txPduCounter = txIpduStatePtr->TxIpduCounter;
        /*Increase the counter value by +1*/
        Com_PduCounterIncrease(TRUE, TxIpduId);
    }
#endif /* STD_ON == COM_TX_IPDU_COUNTER_ENABLE */
    pduInfo.SduDataPtr = &Com_TxIPduRuntimeBuff[ipduBufferId];
    pduInfo.SduLength = ipduLength;
#if (STD_ON == COM_METADATA_SUPPORT)
    uint8 metaDataLength = txIpduPtr->MetaDataLength;
    if (0u < metaDataLength)
    {
        PduLengthType metaDataPos =
            txIpduPtr->IPduNoDynSignalLength + txIpduPtr->IPduMaxDynSignalLength + (PduLengthType)ipduBufferId;
        pduInfo.MetaDataPtr = &Com_TxIPduRuntimeBuff[metaDataPos];
    }
    else
#endif
    {
        pduInfo.MetaDataPtr = NULL_PTR;
    }
#if (STD_ON == COM_TX_IPDU_CALLOUT_ENABLE)
    boolean ret = TRUE;
    /*invoke the callout API*/
    if (NULL_PTR != txIpduPtr->ComIPduCallout)
    {
        ret = txIpduPtr->ComIPduCallout(TxIpduId + COM_RXIPDU_NUMBER, &pduInfo);
    }
    if (ret)
#endif /* STD_ON == COM_TX_IPDU_CALLOUT_ENABLE */
    {
#if (STD_ON == COM_TXTPPDU_SUPPORT)
        if (COM_PDU_TP == txIpduPtr->ComIPduType)
        {
            pduInfo.SduDataPtr = NULL_PTR;
        }
#endif /* STD_ON == COM_TXTPPDU_SUPPORT */
        /*Set the Transmiting flag before call PduR_Transmit,
         *avoid the TxConfirmation come before set the Transmiting flag*/
        txIpduStatePtr->TxIpduRTStFlag |= Com_TX_TRANSMITING_EN;
        if (E_OK == PduR_ComTransmit(txIpduPtr->ComPduIdRef, &pduInfo))
        {
            uint8 TxDelay = txIpduStatePtr->TxIpduRTStFlag & Com_TX_DELAY_EN;
            if (Com_TX_DELAY_EN == TxDelay)
            {
                txIpduStatePtr->TxIpduRTStFlag &= Com_TX_DELAY_DIS;
            }
/*Reset Tx_IPduMDT*/
#if (STD_ON == COM_MDT_ENABLE)
            Com_ResetTxIpduMDT(txIpduStatePtr, txIpduPtr);
#endif
#if (STD_ON == COM_TX_SIG_GROUP_UPDATE_BIT_ENABLE) || (STD_ON == COM_TX_SIGNAL_UPDATE_BIT_ENABLE) \
    || (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
            if (COM_TRANSMIT == txIpduPtr->ComTxIPduClearUpdateBit)
            {
                /*clear all signal group/signal/dest description signal update bit of the Tx Pdu*/
                Com_ClearTxIPduUpdates(txIpduPtr);
            }
#endif /* STD_ON == COM_TX_SIG_GROUP_UPDATE_BIT_ENABLE) || (STD_ON == COM_TX_SIGNAL_UPDATE_BIT_ENABLE) || (STD_ON == \
COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */
            txIpduStatePtr->TxOffset = 0u;
        }
        else
        {
            txIpduStatePtr->TxIpduRTStFlag &= Com_TX_TRANSMITING_DIS;
#if (STD_ON == COM_TX_IPDU_COUNTER_ENABLE)
            if (COM_UNUSED_TXIPDUCOUNTERID != txIpduPtr->ComIPduCounterIndex)
            {
                /*transmit not OK,recover the old counter value*/
                txIpduStatePtr->TxIpduCounter = txPduCounter;
            }
#endif /* STD_ON == COM_TX_IPDU_COUNTER_ENABLE */
/*ComRetryFailedTransmitRequests*/
#if (STD_ON == COM_RETRY_FAILED_TRANSMIT_REQUESTS)
            txIpduStatePtr->TxIpduRTStFlag |= Com_TX_DELAY_EN;
#else
/*Reset Tx_IPduMDT*/
#if (STD_ON == COM_MDT_ENABLE)
            Com_ResetTxIpduMDT(txIpduStatePtr, txIpduPtr);
#endif
#endif /*STD_ON == COM_RETRY_FAILED_TRANSMIT_REQUESTS*/
        }
    }
#if (STD_ON == COM_TX_IPDU_CALLOUT_ENABLE) && (STD_ON == COM_TX_IPDU_COUNTER_ENABLE)
    else
    {
        if (COM_UNUSED_TXIPDUCOUNTERID != txIpduPtr->ComIPduCounterIndex)
        {
            /*transmit not OK,recover the old counter value*/
            txIpduStatePtr->TxIpduCounter = txPduCounter;
        }
    }
#endif /* STD_ON == COM_TX_IPDU_CALLOUT_ENABLE && STD_ON == COM_TX_IPDU_COUNTER_ENABLE */
    return;
}
#endif

#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER) || (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER)                              \
    || (0u < COM_TX_MODE_TRUE_DIRECT_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_DIRECT_NOREPETITION_NUMBER) \
    || ((0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)                            \
        || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER))
/******************************************************************************/
/*
 * Brief               Called by Com_MainFunctionTx.
 *                     the handle of Com_MainFunctionTx,when the tx mode is direct.
 *                     return the boolean value for the tx pdu need to transmit or not.
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      TxIpduStatePtr,TxIpduPtr,MDTRun
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(boolean, COM_CODE)
    Com_MainFuncTxDirect(Com_TxIPduRunTimeStateType* TxIpduStatePtr, const Com_TxIPduType* TxIpduPtr, boolean MDTRun)
{
    boolean ret = FALSE;
    /* PRQA S 2983,2995 ++ */ /* MISRA Rule 2.2*/
    PduIdType txModeIndex;
    Com_TxModeModeType txMode;
    uint8 TxDelay = TxIpduStatePtr->TxIpduRTStFlag & Com_TX_DELAY_EN;

#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER) || (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)
    Com_TxModeNumberOfRepetitionsType numOfRepetition;
    if ((!MDTRun) && (Com_TX_DELAY_EN == TxDelay))
    {
        TxIpduStatePtr->NTimeCnt = 0u;
    }
    if (TxIpduStatePtr->NTimeCnt > 0u)
    {
        (TxIpduStatePtr->NTimeCnt) -= 1u;
    }
#endif
    uint8 Transmiting = TxIpduStatePtr->TxIpduRTStFlag & Com_TX_TRANSMITING_EN;
    if ((0u == TxIpduStatePtr->NTimeCnt) && (TxIpduStatePtr->RptNum > 0u) && (Com_TX_TRANSMITING_EN != Transmiting))
    {
/*delay transmit of the MDT */
#if (STD_ON == COM_MDT_ENABLE)
        if (MDTRun)
        {
            TxIpduStatePtr->TxIpduRTStFlag |= Com_TX_DELAY_EN;
        }
        else
#endif /* STD_ON == COM_MDT_ENABLE */
        {
            ret = TRUE;
        }

#if (STD_ON == COM_TMS_ENABLE)
        uint8 TMS = TxIpduStatePtr->TxIpduRTStFlag & Com_TX_TMS_EN;
        if (TMS != Com_TX_TMS_EN)
        {
            txModeIndex = TxIpduPtr->ComTxModeFalseRefId;
            txMode = TxIpduPtr->ComTxFalseModeMode;
            switch (txMode)
            {
            case COM_TX_MODE_DIRECT:
#if (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER)
                numOfRepetition = Com_TxModeFalseDirectRepetitions[txModeIndex].ComTxModeNumberOfRepetitions;
                if (numOfRepetition <= 1u)
#endif
                {
                    TxIpduStatePtr->RptNum = 0u;
                }
#if (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER)
                else
                {
                    TxIpduStatePtr->NTimeCnt = Com_TxModeFalseDirectRepetitions[txModeIndex].ComTxModeRepetitionPeriod;
                }
#endif
                break;
            case COM_TX_MODE_MIXED:
#if (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)
                numOfRepetition = Com_TxModeFalseMixedRepetitions[txModeIndex].ComTxModeNumberOfRepetitions;
                if (numOfRepetition <= 1u)
#endif
                {
                    TxIpduStatePtr->RptNum = 0u;
                }
#if (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)
                else
                {
                    TxIpduStatePtr->NTimeCnt = Com_TxModeFalseMixedRepetitions[txModeIndex].ComTxModeRepetitionPeriod;
                }
#endif
                break;
            default:
                /* do nothing */
                break;
            }
        }
        else
#endif
        {
            txModeIndex = TxIpduPtr->ComTxModeTrueRefId;
            txMode = TxIpduPtr->ComTxTrueModeMode;
            switch (txMode)
            {
            case COM_TX_MODE_DIRECT:
#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER)
                numOfRepetition = Com_TxModeTrueDirectRepetitions[txModeIndex].ComTxModeNumberOfRepetitions;
                if (numOfRepetition <= 1u)
#endif
                {
                    TxIpduStatePtr->RptNum = 0u;
                }
#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER)
                else
                {
                    TxIpduStatePtr->NTimeCnt = Com_TxModeTrueDirectRepetitions[txModeIndex].ComTxModeRepetitionPeriod;
                }
#endif
                break;
            case COM_TX_MODE_MIXED:
#if (0u < COM_TX_MODE_TRUE_MIXED_NUMBER)
                numOfRepetition = Com_TxModeTrueMixedRepetitions[txModeIndex].ComTxModeNumberOfRepetitions;
                if (numOfRepetition <= 1u)
#endif
                {
                    TxIpduStatePtr->RptNum = 0u;
                }
#if (0u < COM_TX_MODE_TRUE_MIXED_NUMBER)
                else
                {
                    TxIpduStatePtr->NTimeCnt = Com_TxModeTrueMixedRepetitions[txModeIndex].ComTxModeRepetitionPeriod;
                }
#endif
                break;
            default:
                /* do nothing */
                break;
            }
        }
    }
    if ((!MDTRun) && (Com_TX_DELAY_EN == TxDelay))
    {
        ret = TRUE;
    }
    /* PRQA S 2983,2995 -- */ /* MISRA Rule 2.2*/
    return ret;
}
#endif

#if (0u < COM_TX_MODE_TRUE_PERIOD_NUMBER) || (0u < COM_TX_MODE_FALSE_PERIOD_NUMBER)  \
    || (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
/******************************************************************************/
/*
 * Brief               Called by Com_MainFunctionTx.
 *                     the handle of Com_MainFunctionTx,when the tx mode is period.
 *                     return the boolean value for the tx pdu need to transmit or not.
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      TxIpduStatePtr,TxIpduPtr,MDTRun
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(boolean, COM_CODE)
    Com_MainFuncTxPeriod(Com_TxIPduRunTimeStateType* TxIpduStatePtr, const Com_TxIPduType* TxIpduPtr, boolean MDTRun)
{
    boolean ret = FALSE;
    PduIdType txModeIndex;
    if (TxIpduStatePtr->PeriodCnt > 0u)
    {
        (TxIpduStatePtr->PeriodCnt) -= 1u;
    }
    if (0u == TxIpduStatePtr->PeriodCnt)
    {
/*delay transmit of the MDT */
#if (STD_ON == COM_MDT_ENABLE)
        if (MDTRun)
        {
            TxIpduStatePtr->TxIpduRTStFlag |= Com_TX_DELAY_EN;
        }
        else
#endif /* STD_ON == COM_MDT_ENABLE */
        {
            ret = TRUE;
        }

#if (STD_ON == COM_TMS_ENABLE)
        uint8 TMS = (TxIpduStatePtr->TxIpduRTStFlag & Com_TX_TMS_EN);
        if (TMS != Com_TX_TMS_EN)
        {
            txModeIndex = TxIpduPtr->ComTxModeFalseRefId;
            if (COM_TX_MODE_MIXED == TxIpduStatePtr->ipduTxMode)
            {
#if (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)
                TxIpduStatePtr->PeriodCnt = Com_TxModeFalseMixedRepetitions[txModeIndex].ComTxModeTimePeriod;
#endif
            }
            else
            {
#if ((0u < COM_TX_MODE_FALSE_PERIOD_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER))
                TxIpduStatePtr->PeriodCnt = Com_TxModeFalsePeriod[txModeIndex].ComTxModeTimePeriod;
#endif
            }
        }
        else
#endif
        {
            txModeIndex = TxIpduPtr->ComTxModeTrueRefId;
            if (COM_TX_MODE_MIXED == TxIpduStatePtr->ipduTxMode)
            {
#if (0u < COM_TX_MODE_TRUE_MIXED_NUMBER)
                TxIpduStatePtr->PeriodCnt = Com_TxModeTrueMixedRepetitions[txModeIndex].ComTxModeTimePeriod;
#endif
            }
            else
            {
#if (0u < COM_TX_MODE_TRUE_PERIOD_NUMBER) || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER)
                TxIpduStatePtr->PeriodCnt = Com_TxModeTruePeriod[txModeIndex].ComTxModeTimePeriod;
#endif
            }
        }
    }
    uint8 TxDelay = TxIpduStatePtr->TxIpduRTStFlag & Com_TX_DELAY_EN;
    if ((!MDTRun) && (Com_TX_DELAY_EN == TxDelay))
    {
        ret = TRUE;
    }
    if (ret && (0u == TxIpduStatePtr->DMCnt))
    {
        /*reset the tx MD counter*/
        TxIpduStatePtr->DMCnt = TxIpduPtr->ComTxIpduDM;
    }
    return ret;
}
#endif

#if (0u < COM_TX_MODE_TRUE_MIXED_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER) \
    || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
/******************************************************************************/
/*
 * Brief               Called by Com_MainFunctionTx.
 *                     the handle of Com_MainFunctionTx,when the tx mode is mixed.
 *                     return the boolean value for the tx pdu need to transmit or not
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      TxIpduStatePtr,TxIpduPtr,MDTRun
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(boolean, COM_CODE)
    Com_MainFuncTxMixed(Com_TxIPduRunTimeStateType* TxIpduStatePtr, const Com_TxIPduType* TxIpduPtr, boolean MDTRun)
{
    boolean transmitRequest = FALSE;
    boolean directTransmitRequest = Com_MainFuncTxDirect(TxIpduStatePtr, TxIpduPtr, MDTRun);
    boolean periodTransmitRequest = Com_MainFuncTxPeriod(TxIpduStatePtr, TxIpduPtr, MDTRun);

    if (directTransmitRequest || periodTransmitRequest)
    {
        transmitRequest = TRUE;
    }
    return transmitRequest;
}
#endif

#if ((0u < COM_GWMAPPING_NUMBER) && (0u < COM_RXIPDU_NUMBER) && (0u < COM_TXIPDU_NUMBER))
/******************************************************************************/
/*
 * Brief               gateway signal/group signal/signal group/description signal
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      GWMappingId,GWSourceSignalType,GWSourceSignalId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static void Com_GwSignal(
    Com_SignalIdType GWMappingId,
    Com_SignalConfigType GWSourceSignalType,
    Com_SignalIdType GWSourceSignalId)
{
    Com_SignalIdType gwDestNumber;
    Com_SignalIdType gwDestCounter;
    Com_SignalType signalType;
    uint16 gwSignalBufferId;
    Com_SignalConfigType gwDestSignalType;
    Com_SignalIdType gwDestSignalId;
    boolean gwSigIsTrue;
#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)
    uint16 signalLength = 0u;
#endif
#if (0u < COM_RXGROUPSIGNAL_NUMBER)
    const Com_RxGroupSignalType* rxGroupSignalPtr;
#endif
    const Com_GwDestType* gwDestPtr;
#if (0u < COM_GW_SOURCE_DESCRIPTION_NUMBER)
    const Com_GwSourceSignalType* gwSourceSignalPtr;
#endif /*0u < COM_GW_SOURCE_DESCRIPTION_NUMBER*/
    const Com_RxSignalType* rxSignalPtr;
    const Com_GwMappingType* gwMappingPtr = &Com_ConfigStd->ComGwMapping[GWMappingId];

    switch (GWSourceSignalType)
    {
#if (0u < COM_RXSIGNAL_NUMBER)
    case COM_RX_SIGNAL:
        rxSignalPtr = &Com_ConfigStd->ComRxSignal[GWSourceSignalId];
        signalType = rxSignalPtr->ComSignalType;
        gwSignalBufferId = rxSignalPtr->GWSignalBufferId;
#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)
#if (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_N_ENABLE)
        if (COM_UINT8_N == signalType)
        {
            signalLength = rxSignalPtr->ComSignalLength;
        }
#endif
#if (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE)
        if (COM_UINT8_DYN == signalType)
        {
            (void)ILib_memcpy(&signalLength, &Com_GWSignal8BitBuff[gwSignalBufferId], sizeof(signalLength));
        }
#endif
#endif
        gwSigIsTrue = TRUE;
        break;

#endif
#if (0u < COM_RXGROUPSIGNAL_NUMBER)
    case COM_RX_GROUP_SIGNAL:
        rxGroupSignalPtr = &Com_ConfigStd->ComRxGroupSignal[GWSourceSignalId];
        signalType = rxGroupSignalPtr->ComSignalType;
        gwSignalBufferId = rxGroupSignalPtr->GWSignalBufferId;
#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)
#if (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_N_ENABLE)
        if (COM_UINT8_N == signalType)
        {
            signalLength = rxGroupSignalPtr->ComSignalLength;
        }
#endif
#if (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE)
        if (COM_UINT8_DYN == signalType)
        {
            (void)ILib_memcpy(&signalLength, &Com_GWSignal8BitBuff[gwSignalBufferId], sizeof(signalLength));
        }
#endif
#endif
        gwSigIsTrue = TRUE;
        break;
#endif /* 0u < COM_RXGROUPSIGNAL_NUMBER */
#if (0u < COM_GW_SOURCE_DESCRIPTION_NUMBER)
    case COM_RX_DESCRIPTION:
        gwSourceSignalPtr = &Com_ConfigStd->ComSourceSignal[GWSourceSignalId];
        signalType = gwSourceSignalPtr->ComSignalType;
        gwSignalBufferId = gwSourceSignalPtr->GWSignalBufferId;

#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)
#if (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_N_ENABLE)
        if (COM_UINT8_N == signalType)
        {
            signalLength = gwSourceSignalPtr->ComSignalLength;
        }
#endif
#if (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_DYN_ENABLE)
        if (COM_UINT8_DYN == signalType)
        {
            (void)ILib_memcpy(&signalLength, &Com_GWSignal8BitBuff[gwSignalBufferId], sizeof(signalLength));
        }
#endif
#endif
        gwSigIsTrue = TRUE;
        break;
#endif /*0u < COM_GW_SOURCE_DESCRIPTION_NUMBER*/
    default:
        gwSigIsTrue = FALSE;
        break;
    }

    if (gwSigIsTrue)
    {
        gwDestCounter = gwMappingPtr->ComGwDestSignalStartId;
        gwDestNumber = gwMappingPtr->ComGwDestNumber;
        for (; gwDestCounter < gwDestNumber; ++gwDestCounter)
        {
            gwDestPtr = &Com_GwDest[gwDestCounter];
            gwDestSignalType = gwDestPtr->ComGwDestSignalType;
            gwDestSignalId = gwDestPtr->ComGwDestSignalId;
/*Except COM_UINT8_N,COM_UINT8_DYN Type Signal*/
#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)                                                                               \
    && ((STD_ON == COM_RX_SIGNAL_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE)            \
        || (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE) \
        || (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_DYN_ENABLE))
            if ((COM_UINT8_N == signalType) || (COM_UINT8_DYN == signalType))
            {
                Com_GwUint8NDYNSignal(signalType, gwSignalBufferId, signalLength, gwDestSignalType, gwDestSignalId);
            }
            else
#endif /* 0u < COM_GWSIGNAL_8BITBUFF_SIZE                                                                          \
    and (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_N_ENABLE || STD_ON == COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE              \
        or STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_N_ENABLE || STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE    \
        or STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_N_ENABLE || STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_DYN_ENABLE) \
  */
            {
                Com_GwNotArraySignal(signalType, gwSignalBufferId, gwDestSignalType, gwDestSignalId);
            }
        }
    }
    COM_NOUSED(GWSourceSignalId);
    return;
}
#endif

/******************************************************************************/
/*
 * Brief               Called by Com_GwSignal.
 *                     gateway signal/group signal/description signal which
 *                     signal type is COM_UINT8_DYN,UINT8_N
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      SignalType,SignalBufferId,SignalLength,DestSignalType,DestSignalId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
#if (0u < COM_GWSIGNAL_8BITBUFF_SIZE)                                                                               \
    && ((STD_ON == COM_RX_SIGNAL_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_RX_SIGNAL_TYPE_UINT8_DYN_ENABLE)            \
        || (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_RX_GRP_SIGNAL_TYPE_UINT8_DYN_ENABLE) \
        || (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_N_ENABLE) || (STD_ON == COM_GW_SRC_DSP_SIG_TYPE_UINT8_DYN_ENABLE))
static FUNC(void, COM_CODE) Com_GwUint8NDYNSignal(
    Com_SignalType SignalType,
    uint16 SignalBufferId,
    uint16 SignalLength,
    Com_SignalConfigType DestSignalType,
    Com_SignalIdType DestSignalId)
{
#if (0u < COM_TXIPDUBUFF_SIZE)
    boolean valueChanged = FALSE;
    PduIdType txPduId;
    uint16 rptNum = 1u;
    Com_SignalPositionType sigLsbBytePos;
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
    uint32 updateBitPosition;
    uint8 updateBitMask;
#endif
    Com_TransferPropertyType signalTxProperty;
#if ((0u < COM_TXSIGNAL_NUMBER) || (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER))
    const Com_TxSignalType* txSignalPtr;
    const Com_GwDestSignalType* gwDestSignalPtr;
#endif
#if ((0u < COM_TXGROUPSIGNAL_NUMBER) && (COM_TXSIGNALGROUP_NUMBER))
    Com_TxSignalGroupIdType txSignalGroupId;
    const Com_TxSignalGroupType* txSignalGroupPtr;
    const Com_TxGroupSignalType* txGroupSignalPtr;
#endif

    switch (DestSignalType)
    {
#if (0u < COM_TXSIGNAL_NUMBER)
    case COM_TX_SIGNAL:
        txSignalPtr = &Com_ConfigStd->ComTxSignal[DestSignalId];
        signalTxProperty = txSignalPtr->ComTransferProperty;
        txPduId = txSignalPtr->ComIpduRefIndex;
        sigLsbBytePos = txSignalPtr->ComSigLsbBytePos;
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        updateBitPosition = txSignalPtr->ComUpdateLsbBytePos;
        updateBitMask = txSignalPtr->ComUpdateBitMask;
#endif
        break;
#endif
#if ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER))
    case COM_TX_GROUP_SIGNAL:
        txGroupSignalPtr = &Com_ConfigStd->ComTxGroupSignal[DestSignalId];
        txSignalGroupId = txGroupSignalPtr->ComSignalGroupRef;
        txSignalGroupPtr = &Com_ConfigStd->ComTxSignalGroup[txSignalGroupId];
        txPduId = txSignalGroupPtr->ComIpduRefIndex;
        sigLsbBytePos = txGroupSignalPtr->ComSigLsbBytePos;
        signalTxProperty = (COM_GROUPSIGNAL_TMC_NONE != txGroupSignalPtr->ComTransferProperty)
                               ? txGroupSignalPtr->ComTransferProperty
                               : txSignalGroupPtr->ComTransferProperty;
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        updateBitPosition = txSignalGroupPtr->ComUpdateLsbBytePos;
        updateBitMask = txSignalGroupPtr->ComUpdateBitMask;
#endif
        break;
#endif
#if (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)
    case COM_TX_DESCRIPTION:
        gwDestSignalPtr = &Com_ConfigStd->ComDestSignal[DestSignalId];
        txPduId = gwDestSignalPtr->ComGwIPduRef;
        sigLsbBytePos = gwDestSignalPtr->ComSigLsbBytePos;
        signalTxProperty = gwDestSignalPtr->ComTransferProperty;
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        updateBitPosition = gwDestSignalPtr->ComUpdateLsbBytePos;
        updateBitMask = gwDestSignalPtr->ComUpdateBitMask;
#endif
        break;
#endif
    default:
        /*do nothing*/
        break;
    }
#if (0u < COM_TXSIGNAL_NUMBER) || ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER)) \
    || (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)
    /* PRQA S 2962 ++ */ /* MISRA Rule 9.1 */
    const Com_TxIPduType* txIpduPtr = &Com_ConfigStd->ComTxIPdu[txPduId];
    Com_TxIPduRunTimeStateType* txIpduStatePtr = &Com_TxIPduRunTimeState[txPduId];
    Com_TxIpduBufIdType txIPduBufId = txIpduPtr->ComTxIPduBufIndex + (Com_TxIpduBufIdType)sigLsbBytePos;
    /* PRQA S 2962 -- */ /* MISRA Rule 9.1 */
    uint16 SigBufId = (COM_UINT8_DYN == SignalType) ? (SignalBufferId + (uint16)sizeof(SignalLength)) : SignalBufferId;
    SchM_Enter_Com_MultiCore_Lock();
    if (0 != ILib_memcmp(&Com_TxIPduRuntimeBuff[txIPduBufId], &Com_GWSignal8BitBuff[SigBufId], SignalLength))
    {
        (void)ILib_memcpy(&Com_TxIPduRuntimeBuff[txIPduBufId], &Com_GWSignal8BitBuff[SigBufId], SignalLength);
        valueChanged = TRUE;
    }
    SchM_Exit_Com_MultiCore_Lock();
    if (COM_UINT8_DYN == SignalType)
    {
        uint16 destSignalLength = txIpduStatePtr->TxIpduLength - (uint16)txIpduPtr->IPduNoDynSignalLength;
        if (SignalLength != destSignalLength)
        {
            valueChanged = TRUE;
            txIpduStatePtr->TxIpduLength = (uint16)txIpduPtr->IPduNoDynSignalLength + SignalLength;
        }
    }
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
    /*if configuration update bit,set update bit to 1*/
    Com_SetSignalUpdateBit(txIPduBufId, updateBitPosition, updateBitMask);
#endif /* STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */
    /*calculate the TMS,store new Tx mode,get rptNum value for DIRECT/MIXED tx mode,if TMS changed will
     * reset periodic mode counter.*/
    Com_TxIpduTMSHandle(txIpduStatePtr, txIpduPtr, &rptNum);
#endif

    switch (DestSignalType)
    {
#if (0u < COM_TXSIGNAL_NUMBER)
    case COM_TX_SIGNAL:
        /*handle the tx pdu (which include the gateway signal) transmit parameter*/
        Com_GwSignalOfPduHandle(txIpduStatePtr, signalTxProperty, rptNum, valueChanged);
/*the tx signal configuration timeout*/
#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_ENABLE)
        if (COM_UNUSED_TXSIGNALTIMEOUTID != txSignalPtr->ComTimeoutIndex)
        {
            if ((0u == txIpduStatePtr->DMCnt) || (1u < txIpduStatePtr->RptNum))
            {
                txIpduStatePtr->DMCnt = txIpduPtr->ComTxIpduDM;
            }
        }
#endif /* STD_ON == COM_TX_SIGNAL_TIMEOUT_ENABLE */
        break;
#endif
#if ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER))
    case COM_TX_GROUP_SIGNAL:
        /*handle the tx pdu (which include the gateway group signal) transmit parameter*/
        Com_GwSignalOfPduHandle(txIpduStatePtr, signalTxProperty, rptNum, valueChanged);
/*the tx signal group(include the gateway group signal)configuration timeout*/
#if (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_ENABLE)
        if (COM_UNUSED_TXSIGGRPTIMEOUTID != txSignalGroupPtr->ComTimeoutIndex)
        {
            if ((0u == txIpduStatePtr->DMCnt) || (1u < txIpduStatePtr->RptNum))
            {
                txIpduStatePtr->DMCnt = txIpduPtr->ComTxIpduDM;
            }
        }
#endif /* STD_ON == COM_TX_SIG_GROUP_TIMEOUT_ENABLE */
        break;
#endif
#if (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)
    case COM_TX_DESCRIPTION:
        /*handle the tx pdu (which include the gateway description signal) transmit parameter*/
        Com_GwSignalOfPduHandle(txIpduStatePtr, signalTxProperty, rptNum, valueChanged);
        break;
#endif
    default:
        /*do nothing*/
        break;
    }
#endif /*0u < COM_TXIPDUBUFF_SIZE*/
    return;
}
#endif

/******************************************************************************/
/*
 * Brief               Called by Com_GwSignal.
 *                     gateway signal/group signal/description signal which
 *                     signal type isn't COM_UINT8_N and COM_UINT8_DYN
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      SignalType,GWSignalBufferId,DestSignalType,DestSignalId
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static void Com_GwNotArraySignal(
    Com_SignalType SignalType,
    uint16 GWSignalBufferId,
    Com_SignalConfigType DestSignalType,
    Com_SignalIdType DestSignalId)
{
    const Com_TxIPduType* txIpduPtr;
    Com_TxIPduRunTimeStateType* txIpduStatePtr;
    boolean valueChanged = FALSE;
    uint64 sourceSignalValue = 0u;
    uint64 destSignalValue;
    PduIdType txPduId;
    uint16 txSignalValueId;
    Com_TxIpduBufIdType ipduBufferIndex;
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
    Com_SignalPositionType updateBitPosition;
    uint8 updateBitMask;
#endif /* STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */
    Com_TransferPropertyType signalTxProperty;
    uint16 rptNum = 1u;
#if ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER))
    Com_TxSignalGroupIdType txSignalGroupId;
    const Com_TxGroupSignalType* txGroupSignalPtr;
    const Com_TxSignalGroupType* txSignalGroupPtr;
#endif
#if ((0u < COM_TXSIGNAL_NUMBER) || (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER))
    const Com_TxSignalType* txSignalPtr;
    const Com_GwDestSignalType* gwDestSignalPtr;
#endif
    boolean notArrSigIsTrue = FALSE;

    switch (DestSignalType)
    {
#if (0u < COM_TXSIGNAL_NUMBER)
    case COM_TX_SIGNAL:
        txSignalPtr = &Com_ConfigStd->ComTxSignal[DestSignalId];
        txSignalValueId = txSignalPtr->ComSignalInitValueId;
        txPduId = txSignalPtr->ComIpduRefIndex;
        txIpduPtr = &Com_ConfigStd->ComTxIPdu[txPduId];
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        updateBitPosition = txSignalPtr->ComUpdateLsbBytePos;
        updateBitMask = txSignalPtr->ComUpdateBitMask;
#endif /* STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */
        signalTxProperty = txSignalPtr->ComTransferProperty;
        ipduBufferIndex = txIpduPtr->ComTxIPduBufIndex;
        SchM_Enter_Com_MultiCore_Lock();
        destSignalValue = Com_GwSignalNewOldValueGet(SignalType, GWSignalBufferId, txSignalValueId, &sourceSignalValue);
        SchM_Exit_Com_MultiCore_Lock();
        if (sourceSignalValue != destSignalValue)
        {
            valueChanged = TRUE;
/*pack the new value*/
#if (0u < COM_TXIPDUBUFF_SIZE)
            Com_TxSignalPackHandle(
                COM_TX_SIGNAL,
                txSignalPtr,
                sourceSignalValue,
                &Com_TxIPduRuntimeBuff[ipduBufferIndex]);
#endif
        }
        notArrSigIsTrue = TRUE;
        break;
#endif
#if ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER))
    case COM_TX_GROUP_SIGNAL:
        txGroupSignalPtr = &Com_ConfigStd->ComTxGroupSignal[DestSignalId];
        txSignalValueId = txGroupSignalPtr->ComSignalInitValueId;
        txSignalGroupId = txGroupSignalPtr->ComSignalGroupRef;
        txSignalGroupPtr = &Com_ConfigStd->ComTxSignalGroup[txSignalGroupId];
        txPduId = txSignalGroupPtr->ComIpduRefIndex;
        txIpduPtr = &Com_ConfigStd->ComTxIPdu[txPduId];
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        updateBitPosition = txSignalGroupPtr->ComUpdateLsbBytePos;
        updateBitMask = txSignalPtr->ComUpdateBitMask;
#endif /* STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */
        ipduBufferIndex = txIpduPtr->ComTxIPduBufIndex;
        signalTxProperty = (COM_GROUPSIGNAL_TMC_NONE != txGroupSignalPtr->ComTransferProperty)
                               ? txGroupSignalPtr->ComTransferProperty
                               : txSignalGroupPtr->ComTransferProperty;
        SchM_Enter_Com_MultiCore_Lock();
        destSignalValue = Com_GwSignalNewOldValueGet(SignalType, GWSignalBufferId, txSignalValueId, &sourceSignalValue);
        SchM_Exit_Com_MultiCore_Lock();
        if (sourceSignalValue != destSignalValue)
        {
            valueChanged = TRUE;
/*pack the new value*/
#if (0u < COM_TXIPDUBUFF_SIZE)
            Com_TxSignalPackHandle(
                COM_TX_GROUP_SIGNAL,
                txGroupSignalPtr,
                sourceSignalValue,
                &Com_TxIPduRuntimeBuff[ipduBufferIndex]);
#endif
        }
        notArrSigIsTrue = TRUE;
        break;
#endif
#if (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)
    case COM_TX_DESCRIPTION:
        gwDestSignalPtr = &Com_ConfigStd->ComDestSignal[DestSignalId];
        txSignalValueId = gwDestSignalPtr->ComSignalInitValueId;
        txPduId = gwDestSignalPtr->ComGwIPduRef;
        txIpduPtr = &Com_ConfigStd->ComTxIPdu[txPduId];
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        updateBitPosition = gwDestSignalPtr->ComUpdateLsbBytePos;
        updateBitMask = gwDestSignalPtr->ComUpdateBitMask;
#endif /* STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */
        signalTxProperty = gwDestSignalPtr->ComTransferProperty;
        ipduBufferIndex = txIpduPtr->ComTxIPduBufIndex;
        SchM_Enter_Com_MultiCore_Lock();
        destSignalValue = Com_GwSignalNewOldValueGet(SignalType, GWSignalBufferId, txSignalValueId, &sourceSignalValue);
        SchM_Exit_Com_MultiCore_Lock();
        if (sourceSignalValue != destSignalValue)
        {
            valueChanged = TRUE;
/*pack the new value*/
#if (0u < COM_TXIPDUBUFF_SIZE)
            Com_TxSignalPackHandle(
                COM_TX_DESCRIPTION,
                gwDestSignalPtr,
                sourceSignalValue,
                &Com_TxIPduRuntimeBuff[ipduBufferIndex]);
#endif
        }
        notArrSigIsTrue = TRUE;
        break;
#endif
    default:
        /* do nothing */
        break;
    }

    if (notArrSigIsTrue)
    {
#if (STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE)
        /*if configuration update bit,set update bit to 1*/
        Com_SetSignalUpdateBit(ipduBufferIndex, updateBitPosition, updateBitMask);
#endif /* STD_ON == COM_GW_DEST_SIG_UPDATE_BIT_ENABLE */

        txIpduStatePtr = &Com_TxIPduRunTimeState[txPduId];
        switch (DestSignalType)
        {
#if (0u < COM_TXSIGNAL_NUMBER)
        case COM_TX_SIGNAL:
#if (COM_TXSIGNAL_FILTERTYPE_MAX_NUMBER > 0u)
            if (COM_UNUSED_TXSIGNALFILTERID != txSignalPtr->ComFilterIndex)
            {
                Com_TxSignalTMCRunTime[txSignalPtr->ComTMCBufferId] = Com_DestSignalTMCCalculate(
                    SignalType,
                    txSignalPtr->ComFilterAlgorithm,
                    (Com_SignalIdType)txSignalPtr->ComFilterIndex,
#if (COM_TXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
                    destSignalValue,
#endif
                    sourceSignalValue);
            }
#endif
            /*calculate the TMS,store new Tx mode,get rptNum value for DIRECT/MIXED tx mode,if TMS changed
             * will reset periodic mode counter.*/
            Com_TxIpduTMSHandle(txIpduStatePtr, txIpduPtr, &rptNum);
            /*handle the tx pdu (which include the gateway signal) transmit parameter*/
            Com_GwSignalOfPduHandle(txIpduStatePtr, signalTxProperty, rptNum, valueChanged);
/*the tx signal configuration timeout*/
#if (STD_ON == COM_TX_SIGNAL_TIMEOUT_ENABLE)
            if (COM_UNUSED_TXSIGNALTIMEOUTID != txSignalPtr->ComTimeoutIndex)
            {
                if ((0u == txIpduStatePtr->DMCnt) || (1u < txIpduStatePtr->RptNum))
                {
                    txIpduStatePtr->DMCnt = Com_ConfigStd->ComTxIPdu[txPduId].ComTxIpduDM;
                }
            }
#endif /* STD_ON == COM_TX_SIGNAL_TIMEOUT_ENABLE */
            break;
#endif /* 0u < COM_TXSIGNAL_NUMBER */
#if (0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER)
        case COM_TX_GROUP_SIGNAL:
#if (COM_TXGRPSIG_FILTERTYPE_MAX_NUMBER > 0u)
            if (COM_UNUSED_TXGRPSIGFILTERID != txGroupSignalPtr->ComFilterIndex)
            {
                Com_TxSignalTMCRunTime[txGroupSignalPtr->ComTMCBufferId] = Com_DestSignalTMCCalculate(
                    SignalType,
                    txGroupSignalPtr->ComFilterAlgorithm,
                    (Com_SignalIdType)txGroupSignalPtr->ComFilterIndex,
#if (COM_TXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
                    destSignalValue,
#endif
                    sourceSignalValue);
            }
#endif
            /*calculate the TMS,store new Tx mode,get rptNum value for DIRECT/MIXED tx mode,if TMS changed
             * will reset periodic mode counter.*/
            Com_TxIpduTMSHandle(txIpduStatePtr, txIpduPtr, &rptNum);
            /*handle the tx pdu (which include the gateway group signal) transmit parameter*/
            Com_GwSignalOfPduHandle(txIpduStatePtr, signalTxProperty, rptNum, valueChanged);
/*the tx signal group(include the gateway group signal)configuration timeout*/
#if (STD_ON == COM_TX_SIG_GROUP_TIMEOUT_ENABLE)
            if (COM_UNUSED_TXSIGGRPTIMEOUTID != txSignalGroupPtr->ComTimeoutIndex)
            {
                if ((0u == txIpduStatePtr->DMCnt) || (1u < txIpduStatePtr->RptNum))
                {
                    txIpduStatePtr->DMCnt = txIpduPtr->ComTxIpduDM;
                }
            }
#endif /* STD_ON == COM_TX_SIG_GROUP_TIMEOUT_ENABLE */
            break;
#endif /* 0u < COM_TXGROUPSIGNAL_NUMBER && 0u < COM_TXSIGNALGROUP_NUMBER */
#if (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)
        case COM_TX_DESCRIPTION:
#if (COM_DESTSIG_FILTERTYPE_MAX_NUMBER > 0u)
            if (COM_UNUSED_DESTSIGNALFILTERID != gwDestSignalPtr->ComFilterIndex)
            {
                Com_TxSignalTMCRunTime[gwDestSignalPtr->ComTMCBufferId] = Com_DestSignalTMCCalculate(
                    SignalType,
                    gwDestSignalPtr->ComFilterAlgorithm,
                    (Com_SignalIdType)gwDestSignalPtr->ComFilterIndex,
#if (COM_TXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
                    destSignalValue,
#endif
                    sourceSignalValue);
            }
#endif
            /*calculate the TMS,store new Tx mode,get rptNum value for DIRECT/MIXED tx mode,if TMS changed
             * will reset periodic mode counter.*/
            Com_TxIpduTMSHandle(txIpduStatePtr, txIpduPtr, &rptNum);
            /*handle the tx pdu (which include the gateway signal) transmit parameter*/
            Com_GwSignalOfPduHandle(txIpduStatePtr, signalTxProperty, rptNum, valueChanged);
            break;
#endif /* 0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER */
        default:
            /*do nothing*/
            break;
        }
    }
    return;
}

#if (                                                                            \
    ((0u < COM_TXSIGNAL_NUMBER) || (0u < COM_GW_DESTINATION_DESCRIPTION_NUMBER)) \
    || ((0u < COM_TXGROUPSIGNAL_NUMBER) && (0u < COM_TXSIGNALGROUP_NUMBER)))
/******************************************************************************/
/*
 * Brief               gateway pdu(which include gateway signal and group signal) handle
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      TxPduId,SignalTxProperty,RptNum,ValueChanged
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
static FUNC(void, COM_CODE) Com_GwSignalOfPduHandle(
    Com_TxIPduRunTimeStateType* TxIpduStatePtr,
    Com_TransferPropertyType SignalTxProperty,
    uint16 RptNum,
    boolean ValueChanged)
{
    Com_TxModeModeType ipduTxMode = TxIpduStatePtr->ipduTxMode;

#if (0u < COM_TX_MODE_TRUE_DIRECT_NUMBER) || (0u < COM_TX_MODE_TRUE_MIXED_NUMBER)                              \
    || (0u < COM_TX_MODE_FALSE_DIRECT_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NUMBER)                         \
    || (0u < COM_TX_MODE_TRUE_DIRECT_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_TRUE_MIXED_NOREPETITION_NUMBER) \
    || (0u < COM_TX_MODE_FALSE_DIRECT_NOREPETITION_NUMBER) || (0u < COM_TX_MODE_FALSE_MIXED_NOREPETITION_NUMBER)
    if ((COM_TX_MODE_DIRECT == ipduTxMode) || (COM_TX_MODE_MIXED == ipduTxMode)
        || (COM_TX_MODE_DIRECT_WITHOUT_REPETITION == ipduTxMode)
        || (COM_TX_MODE_MIXED_WITHOUT_REPETITION == ipduTxMode))
    {
        switch (SignalTxProperty)
        {
        case COM_TRIGGERED:
            TxIpduStatePtr->NTimeCnt = 0u;
            TxIpduStatePtr->RptNum = RptNum;
            break;
        case COM_TRIGGERED_ON_CHANGE:
            if (ValueChanged)
            {
                TxIpduStatePtr->NTimeCnt = 0u;
                TxIpduStatePtr->RptNum = RptNum;
            }
            break;
        case COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
            if (ValueChanged)
            {
                TxIpduStatePtr->NTimeCnt = 0u;
                TxIpduStatePtr->RptNum = 1u;
            }
            break;
        case COM_TRIGGERED_WITHOUT_REPETITION:
            TxIpduStatePtr->NTimeCnt = 0u;
            TxIpduStatePtr->RptNum = 1u;
            break;
        default:
            /*do nothing*/
            break;
        }
    }
    else
#endif
    {
        TxIpduStatePtr->NTimeCnt = 0u;
        TxIpduStatePtr->RptNum = 0u;
    }
    COM_NOUSED(SignalTxProperty);
    COM_NOUSED(ValueChanged);
    return;
}
#endif

/******************************************************************************/
/*
 * Brief               Get the GW Signal's New value and Old value
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      SignalType,GWSignalBufferId,TxSignalValueId
 * Param-Name[out]     SourceSignalValue
 * Param-Name[in/out]  None
 * Return              uint64
 */
/******************************************************************************/
static FUNC(uint64, COM_CODE) Com_GwSignalNewOldValueGet(
    Com_SignalType SignalType,
    uint16 GWSignalBufferId,
    uint16 TxSignalValueId,
    uint64* SourceSignalValue)
{
    uint64 destSignalValue = 0u;
    switch (SignalType)
    {
#if (0u < COM_SIGNAL_BOOLBUFF_SIZE) && (0u < COM_GWSIGNAL_BOOLBUFF_SIZE)
    case COM_BOOLEAN:
        *SourceSignalValue = Com_GWSignalBoolBuff[GWSignalBufferId] ? 1u : 0u;
        destSignalValue = Com_SignalBoolRuntimeBuff[TxSignalValueId] ? 1u : 0u;
        Com_SignalBoolRuntimeBuff[TxSignalValueId] = Com_GWSignalBoolBuff[GWSignalBufferId];
        break;
#endif /* 0u < COM_SIGNAL_BOOLBUFF_SIZE && 0u < COM_GWSIGNAL_BOOLBUFF_SIZE */
#if (0u < COM_SIGNAL_8BITBUFF_SIZE) && (0u < COM_GWSIGNAL_8BITBUFF_SIZE)
    case COM_UINT8:
    case COM_SINT8:
        *SourceSignalValue = (uint64)Com_GWSignal8BitBuff[GWSignalBufferId];
        destSignalValue = (uint64)Com_Signal8BitRuntimeBuff[TxSignalValueId];
        Com_Signal8BitRuntimeBuff[TxSignalValueId] = Com_GWSignal8BitBuff[GWSignalBufferId];
        break;
#endif /* 0u < COM_SIGNAL_8BITBUFF_SIZE && 0u < COM_GWSIGNAL_8BITBUFF_SIZE */
#if (0u < COM_SIGNAL_16BITBUFF_SIZE) && (0u < COM_GWSIGNAL_16BITBUFF_SIZE)
    case COM_UINT16:
    case COM_SINT16:
        *SourceSignalValue = (uint64)Com_GWSignal16BitBuff[GWSignalBufferId];
        destSignalValue = (uint64)Com_Signal16BitRuntimeBuff[TxSignalValueId];
        Com_Signal16BitRuntimeBuff[TxSignalValueId] = Com_GWSignal16BitBuff[GWSignalBufferId];
        break;
#endif /* 0u < COM_SIGNAL_16BITBUFF_SIZE && 0u < COM_GWSIGNAL_16BITBUFF_SIZE */
#if (0u < COM_SIGNAL_32BITBUFF_SIZE) && (0u < COM_GWSIGNAL_32BITBUFF_SIZE)
    case COM_UINT32:
    case COM_SINT32:
    case COM_FLOAT32:
        *SourceSignalValue = (uint64)Com_GWSignal32BitBuff[GWSignalBufferId];
        destSignalValue = (uint64)Com_Signal32BitRuntimeBuff[TxSignalValueId];
        Com_Signal32BitRuntimeBuff[TxSignalValueId] = Com_GWSignal32BitBuff[GWSignalBufferId];
        break;
#endif /* 0u < COM_SIGNAL_32BITBUFF_SIZE && 0u < COM_GWSIGNAL_32BITBUFF_SIZE */
#if (0u < COM_SIGNAL_64BITBUFF_SIZE) && (0u < COM_GWSIGNAL_64BITBUFF_SIZE)
    case COM_UINT64:
    case COM_SINT64:
    case COM_FLOAT64:
        *SourceSignalValue = Com_GWSignal64BitBuff[GWSignalBufferId];
        destSignalValue = Com_Signal64BitRuntimeBuff[TxSignalValueId];
        Com_Signal64BitRuntimeBuff[TxSignalValueId] = Com_GWSignal64BitBuff[GWSignalBufferId];
        break;
#endif /* 0u < COM_SIGNAL_64BITBUFF_SIZE && 0u < COM_GWSIGNAL_64BITBUFF_SIZE */
    default:
        /*do nothing*/
        break;
    }
    COM_NOUSED(GWSignalBufferId);
    COM_NOUSED(TxSignalValueId);
    COM_NOUSED(SourceSignalValue);
    return destSignalValue;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/*******************************************************************************
**                      End of file                                           **
*******************************************************************************/
