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
 **  FILENAME    : PduR_Internal.h                                             **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : zhengfei.li                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : PDUR internal header for internal API declarations          **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef PDUR_INTERNAL_H
#define PDUR_INTERNAL_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "PduR.h"
#if (STD_OFF == PDUR_ZERO_COST_OPERATION)
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
typedef struct
{
    boolean NeedGateWayOnTheFly;
    uint8 ActiveTpBufferId;
    boolean TpTxConfirmation;
    PduLengthType TxBufferOffset;
} PduR_GateWayDestTpRunTimeType;

#if (PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u)
typedef enum
{
    PDUR_BUSY = 0u,
    PDUR_IDLE
} PduR_DestStateType;
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (PDUR_TP_BUFFER_SUM > 0u)

extern VAR(PduR_TpBufferTableType, PDUR_VAR_POWER_ON_INIT) PduR_TpBuffer[PDUR_TP_BUFFER_SUM];

#endif

#if (PDUR_TX_BUFFER_SUM > 0u)

extern CONST(PduR_TxBufferTableType, PDUR_CONST) PduR_TxBuffer[PDUR_TX_BUFFER_SUM];

#endif

#if (PDUR_DEFAULT_VALUE_LENGTH > 0u)

extern CONST(uint8, PDUR_CONST) PduR_Default_value[PDUR_DEFAULT_VALUE_LENGTH];

#endif

extern CONST(PduRBswModuleType, PDUR_CONST) PduR_BswModuleConfigData[PDUR_BSW_MODULE_SUM];

/*********************************
** define in PduR_Internal.c   **
**********************************/
/*all route dest pdus is enable or disable*/
#if (PDUR_DEST_PDU_SUM > 0u)

extern VAR(boolean, PDUR_VAR) PduRIsEnabled[PDUR_DEST_PDU_SUM];

#else

extern P2VAR(boolean, PDUR_VAR, PDUR_APPL_DATA) PduRIsEnabled;

#endif

#if (PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u)
extern VAR(PduR_DestStateType, PDUR_VAR) PduR_DestPduState[PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM];
#endif /* PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u */
/*******************************************************************************
**                      External function declarations                        **
*******************************************************************************/

extern FUNC(void, PDUR_CODE) PduR_InitHandle(void);

#if ((0u < PDUR_ROUTING_PATH_GROUP_MAX) && (PDUR_TX_BUFFER_SUM > 0u))
extern FUNC(void, PDUR_CODE) PduR_DestPduDefaultValueSet(PduIdType DestPduId, uint16 TxBufferId);
#endif

#if (STD_ON == PDUR_TX_CONFIRMATION)
extern FUNC(void, PDUR_CODE) PduR_MulticastIfPduTxConfirmationHandle(
    PduIdType TxMPduStateId,
    PduIdType UpPduId,
    PduR_UpIfTxConfirmation_FuncPtrType UpIfTxConfirmationApi);
#endif

#if ((STD_ON == PDUR_TX_CONFIRMATION) && (PDUR_TX_BUFFER_SUM > 0u))
extern FUNC(void, PDUR_CODE) PduR_IfTxConfirmationGatewayHandle(PduIdType TxPduId);
#endif

#if (STD_ON == PDUR_TRANSMIT_SUPPORT)
extern FUNC(void, PDUR_CODE) PduR_MulticastIfPduTxPending(PduIdType TxPduId);
#endif /* STD_ON == PDUR_TRANSMIT_SUPPORT */

#if ((STD_ON == PDUR_RX_INDICATION) && (PDUR_TX_BUFFER_SUM > 0u))
extern FUNC(void, PDUR_CODE) PduR_GateWayDirectBufferHandle(
    PduR_LoIfTransmit_FuncPtrType pduR_LoIfTransmitApi,
    PduIdType DestPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) InfoPtr);
#endif

#if (STD_ON == PDUR_TP_STARTOFRECEPTION_TRANSMIT)
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_StartOfReceptionToOneTpHandle(
    PduIdType SrcPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    PduLengthType Length,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
#endif /*STD_ON == PDUR_TP_STARTOFRECEPTION_TRANSMIT*/

#if (STD_ON == PDUR_TP_COPYRXDATA)
/*Rx Tp Pdu gateway to only one Tp Module Pdu handle,when copy Rx Data*/
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CopyRxDataToOneTpHandle(
#if (0u < PDUR_TP_BUFFER_SUM)
    PduIdType SrcPduId,
#endif
    PduIdType DestPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr);
#endif /*STD_ON == PDUR_TP_COPYRXDATA*/

#if (STD_ON == PDUR_TP_RXINDICATION)
/*Rx Tp Pdu gateway to only one Tp Module Pdu handle,when Rx Indication*/
extern FUNC(void, PDUR_CODE) PduR_RxIndicationToOneTpHandle(PduIdType SrcPduId, PduIdType DestPduId);
#endif /*STD_ON == PDUR_TP_RXINDICATION*/

#if (STD_ON == PDUR_TP_COPYTXDATA)
/*one Tp Pdu route to one Tp Pdu,the dest pdu copy tx data handle*/
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_OneDestCopyTxDataFromTpHandle(
    PduIdType DestPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info,
    P2CONST(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
#endif /*STD_ON == PDUR_TP_COPYTXDATA*/

#if ((0u < PDUR_DEST_GATEWAY_TP_PDU_SUM) || (STD_ON == PDUR_TP_RXINDICATION) || (STD_ON == PDUR_TP_TXCONFIRMATION))
/*clear buffer and gateway state for gateway tp pdu*/
extern FUNC(void, PDUR_CODE) PduR_ClearBufferAndStateOfGateWayTpPdu(PduIdType PduRSrcPduId);
#endif /* 0u < PDUR_DEST_GATEWAY_TP_PDU_SUM || STD_ON == PDUR_TP_RXINDICATION || STD_ON == PDUR_TP_TXCONFIRMATION*/

#if (((STD_ON == PDUR_TRIGGER_TRANSMIT) || (PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u)) && (PDUR_TX_BUFFER_SUM > 0u))
/*clear the buffer(the buffer data have transmit,Whether or not it succeeds)*/
extern FUNC(void, PDUR_CODE) PduR_DeQueueBuffer(PduIdType PduId);
#endif /* STD_ON == PDUR_TRIGGER_TRANSMIT || PDUR_GATEWAY_DIRECT_BUFFER_PDU_SUM > 0u && PDUR_TX_BUFFER_SUM > 0u */

#if ((STD_ON == PDUR_RX_INDICATION) && (PDUR_TX_BUFFER_SUM > 0u))
extern FUNC(void, PDUR_CODE)
    PduR_EnQueueBuffer(PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfo);
#endif /* STD_ON == PDUR_RX_INDICATION && PDUR_TX_BUFFER_SUM > 0u */

#endif /* STD_OFF == PDUR_ZERO_COST_OPERATION */

#endif /* end of PDUR_INTERNAL_H */
/*******************************************************************************
**                      End of file                                           **
*******************************************************************************/
