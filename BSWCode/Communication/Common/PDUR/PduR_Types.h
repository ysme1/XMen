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
 **  FILENAME    : PduR_Types.h                                                **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : zhengfei.li                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Type definitions of PDUR                                    **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2 and R19_11            **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define PDUR_TYPES_H_AR_MAJOR_VERSION 4u
#define PDUR_TYPES_H_AR_MINOR_VERSION 2u
#define PDUR_TYPES_H_AR_PATCH_VERSION 2u
#define PDUR_TYPES_H_SW_MAJOR_VERSION 2u
#define PDUR_TYPES_H_SW_MINOR_VERSION 1u
#define PDUR_TYPES_H_SW_PATCH_VERSION 0u
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "PduR_PBcfg.h"
#include "PduR_Cfg.h"
#if (STD_OFF == PDUR_ZERO_COST_OPERATION)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef enum
{
    PDUR_DIRECT = 0u,
    PDUR_TRIGGERTRANSMIT
} PduR_DestPduDataProvisionType;

typedef uint16 PduR_PBConfigIdType;
typedef uint16 PduR_RoutingPathGroupIdType;

typedef enum
{
    PDUR_UNINIT = 0u,
    PDUR_ONLINE
} PduR_StateType;

typedef Std_ReturnType (
    *PduR_LoIfTransmit_FuncPtrType)(PduIdType SoAdSrcPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr);

typedef void (*PduR_UpIfTxConfirmation_FuncPtrType)(PduIdType TxPduId);
/*****************************************************************************************************************/
typedef struct
{
    PduLengthType DefaultValueStart;
    PduLengthType DefaultValueLength;
} PduRDefaultValueType;

typedef struct
{
    boolean PduRSrcPduUpTxConf;
    uint8 BswModuleIndex;
#if (STD_ON == PDUR_META_DATA_SUPPORT)
    uint8 MetaDataLength;
#endif /* STD_ON == PDUR_META_DATA_SUPPORT */
    PduIdType UpTxconfirmStateIndex;
    PduIdType PduRDestModulePduIndex;
} PduRSrcPduType;

typedef struct
{
    uint8 BswModuleIndex;
    boolean GateWayRoute;
#if (STD_ON == PDUR_META_DATA_SUPPORT)
    uint8 MetaDataLength;
#endif /* STD_ON == PDUR_META_DATA_SUPPORT */
#if (PDUR_TP_BUFFER_SUM > 0u)
    uint16 PduRTpThreshold;
#endif /* PDUR_TP_BUFFER_SUM > 0u */
#if (PDUR_TX_BUFFER_SUM > 0u)
    uint16 PduRDestTxBufferRef;
#if (PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u)
    PduIdType PduRGatewayDirectTxStateIndex;
#endif /* PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u */
#endif /* PDUR_TX_BUFFER_SUM > 0u */
#if (PDUR_DEST_GATEWAY_TP_PDU_SUM > 0u)
    PduIdType GateWayTpRunTimeIndex;
#endif /* PDUR_DEST_GATEWAY_TP_PDU_SUM > 0u */
    PduIdType PduRSrcPduRef;
    PduIdType PduRDestModulePduIndex;
    PduR_DestPduDataProvisionType PduRDestPduDataProvision;
#if (PDUR_DEFAULT_VALUE_PDU > 0u)
    P2CONST(PduRDefaultValueType, AUTOMATIC, PDUR_CONST_PBCFG) PduRDefaultValueRef;
#endif /* PDUR_DEFAULT_VALUE_PDU > 0u */
} PduRDestPduType;

typedef struct
{
    boolean TpRoute;
#if (PDUR_DEST_GATEWAY_TP_PDU_SUM > 0u)
    boolean GatewayOnTheFly;
#endif /* PDUR_DEST_GATEWAY_TP_PDU_SUM > 0u */
    uint8 PduDestSum;
#if (PDUR_DEST_GATEWAY_TP_PDU_SUM > 0u)
    uint16 PduRTpMaxThreshold;
#endif /* PDUR_DEST_GATEWAY_TP_PDU_SUM > 0u */
    P2CONST(PduIdType, AUTOMATIC, PDUR_CONST_PBCFG) PduRDestPduIdRef;
} PduRRoutingPathType;

typedef struct
{
    P2CONST(PduRRoutingPathType, AUTOMATIC, PDUR_CONST_PBCFG) PduRRoutingPathRef;
} PduRRoutingTableType;
/*****************************************************************************************************************/
typedef struct
{
    boolean PduRIsEnabledAtInit;
    PduR_RoutingPathGroupIdType PduRRoutingPathGroupId;
    PduIdType PduRDestPduRefNumber;
    P2CONST(PduIdType, AUTOMATIC, PDUR_CONST_PBCFG) PduRDestPduIdRef;
} PduRRoutingPathGroupType;
/*****************************************************************************************************************/
typedef struct
{
    PduR_PBConfigIdType PduRConfigId;
    uint16 PduRRoutingPathGroupNum;
    uint16 PduRRoutingPathNum;
    PduIdType PduRDestPduNum;
    P2CONST(PduRRoutingPathGroupType, AUTOMATIC, PDUR_CONST_PBCFG) PduRRoutingPathGroupRef;
    P2CONST(PduRRoutingTableType, AUTOMATIC, PDUR_CONST_PBCFG) PduRRoutingTableRef;
    P2CONST(PduRSrcPduType, AUTOMATIC, PDUR_CONST_PBCFG) PduRSrcPduRef;
    P2CONST(PduRDestPduType, AUTOMATIC, PDUR_CONST_PBCFG) PduRDestPduRef;
} PduR_PBConfigType;

typedef struct
{
    uint8 PduRBswModuleRef;
#if (STD_ON == PDUR_CANCEL_RECEIVE)
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleCancelReceiveApi)(PduIdType RxPduId);
#endif /* STD_ON == PDUR_CANCEL_RECEIVE */
#if (STD_ON == PDUR_CANCEL_TRANSMIT)
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleIfCancelTransmitApi)(PduIdType TxPduId);
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleTpCancelTransmitApi)(PduIdType TxPduId);
#endif /* STD_ON == PDUR_CANCEL_TRANSMIT */
#if (STD_ON == PDUR_CHANGE_PARAMETER)
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleChangeParameterApi)
    (PduIdType id, TPParameterType parameter, uint16 value);
#endif /* STD_ON == PDUR_CHANGE_PARAMETER */
#if (STD_ON == PDUR_TRIGGER_TRANSMIT)
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleTriggertransmitApi)
    (PduIdType TxPduId, PduInfoType* PduInfoPtr);
#endif /* STD_ON == PDUR_TRIGGER_TRANSMIT */
#if (STD_ON == PDUR_TRANSMIT_SUPPORT)
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleIfTransmitApi)(PduIdType id, const PduInfoType* info);
#endif /* STD_ON == PDUR_TRANSMIT_SUPPORT */
#if (STD_ON == PDUR_TX_CONFIRMATION)
    P2FUNC(void, PDUR_APPL_CODE, ModuleTxConfirmationApi)(PduIdType TxPduId);
#endif /* STD_ON == PDUR_TX_CONFIRMATION */
#if (STD_ON == PDUR_RX_INDICATION)
    P2FUNC(void, PDUR_APPL_CODE, ModuleIfRxIndicationApi)(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
#endif /* STD_ON == PDUR_RX_INDICATION */
#if (STD_ON == PDUR_TRANSMIT_SUPPORT)
    P2FUNC(Std_ReturnType, PDUR_APPL_CODE, ModuleTpTransmitApi)(PduIdType id, const PduInfoType* info);
#endif /* STD_ON == PDUR_TRANSMIT_SUPPORT */
#if (STD_ON == PDUR_TP_COPYTXDATA)
    P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, ModuleCopyTxDataApi)
    (PduIdType id, const PduInfoType* info, const RetryInfoType* retry, PduLengthType* availableDataPtr);
#endif /* STD_ON == PDUR_TP_COPYTXDATA */
#if (STD_ON == PDUR_TP_TXCONFIRMATION)
    P2FUNC(void, PDUR_APPL_CODE, ModuleTpTxConfirmationApi)(PduIdType id, Std_ReturnType result);
#endif /* STD_ON == PDUR_TP_TXCONFIRMATION */
#if (STD_ON == PDUR_TP_STARTOFRECEPTION_TRANSMIT)
    P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, ModuleStartOfReceptionApi)
    (PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);
#endif /* STD_ON == PDUR_TP_STARTOFRECEPTION_TRANSMIT */
#if (STD_ON == PDUR_TP_COPYRXDATA)
    P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, ModuleCopyRxDataApi)
    (PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr);
#endif /* STD_ON == PDUR_TP_COPYRXDATA */
#if (STD_ON == PDUR_TP_RXINDICATION)
    P2FUNC(void, PDUR_APPL_CODE, ModuleTpRxIndicationApi)(PduIdType id, Std_ReturnType result);
#endif /* STD_ON == PDUR_TP_RXINDICATION */
} PduRBswModuleType;

typedef struct
{
    boolean used;
    uint8 NextTpBufferId;
    PduLengthType RxBufferOffset;
    PduLengthType TpBufferLength;
    PduLengthType SduLength;
    PduIdType PduHandleId;
    P2VAR(uint8, AUTOMATIC, PDUR_CONST_PBCFG) TpBufferData;
#if (STD_ON == PDUR_META_DATA_SUPPORT)
    uint8* MetaData;
#endif
} PduR_TpBufferTableType;

typedef struct
{
    boolean used;
    PduLengthType SduLength;
    P2VAR(uint8, AUTOMATIC, PDUR_CONST_PBCFG) TxBufferData;
#if (STD_ON == PDUR_META_DATA_SUPPORT)
    uint8* MetaData;
#endif
} PduR_TxBufferType;

typedef struct
{
    uint8 PduRTxBufferDepth;
    PduLengthType PduRPduMaxLength;
    P2VAR(PduR_TxBufferType, AUTOMATIC, PDUR_CONST_PBCFG) PduRTxBufferRef;
} PduR_TxBufferTableType;
#endif /*STD_OFF == PDUR_ZERO_COST_OPERATION*/

#endif /* end of PDUR_TYPES_H */
