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
 **  FILENAME    : Com.h                                                       **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : zhengfei.li                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : API declaration and type definitions of COM                 **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
#ifndef COM_H
#define COM_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Com_Types.h"
#include "PduR_Com.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define COM_VENDOR_ID             62u
#define COM_MODULE_ID             50u
#define COM_H_AR_MAJOR_VERSION    4u
#define COM_H_AR_MINOR_VERSION    2u
#define COM_H_AR_PATCH_VERSION    2u
#define COM_H_SW_MAJOR_VERSION    2u
#define COM_H_SW_MINOR_VERSION    0u
#define COM_H_SW_PATCH_VERSION    17u

#define COM_SERVICE_NOT_AVAILABLE ((uint8)0x80u)
#define COM_BUSY                  ((uint8)0x81u)
#define COM_INSTANCE_ID           ((uint8)0x00u)
#if (STD_ON == COM_DEV_ERROR_DETECT)
/*Service ID*/
#define COM_INIT_ID                        ((uint8)0x01u)
#define COM_DEINIT_ID                      ((uint8)0x02u)
#define COM_IPDUGROUPCONTROL_ID            ((uint8)0x03u)
#define COM_RECEPTIONDMCONTROL_ID          ((uint8)0x06u)
#define COM_GETSTATUS_ID                   ((uint8)0x07u)
#define COM_GETVERSIONINFO_ID              ((uint8)0x09u)
#define COM_CLEARIPDUGROUPVECTOR_ID        ((uint8)0x1Cu)
#define COM_SETIPDUGROUP_ID                ((uint8)0x1Du)
#define COM_SENDSIGNAL_ID                  ((uint8)0x0Au)
#define COM_SENDDYNSIGNAL_ID               ((uint8)0x21u)
#define COM_RECEIVESIGNAL_ID               ((uint8)0x0Bu)
#define COM_RECEIVEDYNSIGNAL_ID            ((uint8)0x22u)
#define COM_UPDATESHADOWSIGNAL_ID          ((uint8)0x0Cu)
#define COM_SENDSIGNALGROUP_ID             ((uint8)0x0Du)
#define COM_RECEIVESIGNALGROUP_ID          ((uint8)0x0Eu)
#define COM_SENDSIGNALGROUPARRAY_ID        ((uint8)0x23u)
#define COM_RECEIVESIGNALGROUPARRAY_ID     ((uint8)0x24u)
#define COM_INVALIDATESIGNAL_ID            ((uint8)0x10u)
#define COM_INVALIDATESHADOWSIGNAL_ID      ((uint8)0x16u)
#define COM_INVALIDATESIGNALGROUP_ID       ((uint8)0x1Bu)
#define COM_TRIGGERIPDUSEND_ID             ((uint8)0x17u)
#define COM_TRIGGERIPDUSENDWITHMETADATA_ID ((uint8)0x28u)
#define COM_SWITCHIPDUTXMODE_ID            ((uint8)0x27u)
#define COM_TRIGGERTRANSMIT_ID             ((uint8)0x41u)
#define COM_RXINDICATION_ID                ((uint8)0x42u)
#define COM_TPRXINDICATION_ID              ((uint8)0x45u)
#define COM_TXCONFIRMATION_ID              ((uint8)0x40u)
#define COM_TPTXCONFIRMATION_ID            ((uint8)0x48u)
#define COM_STARTOFRECEPTION_ID            ((uint8)0x46u)
#define COM_COPYRXDATA_ID                  ((uint8)0x44u)
#define COM_COPYTXDATA_ID                  ((uint8)0x43u)
#define COM_MAINFUNCTIONRX_ID              ((uint8)0x18u)
#define COM_MAINFUNCTIONROUTESIGNALS_ID    ((uint8)0x1Au)
/* Error detection */
#define COM_E_PARAM         ((uint8)0x01u)
#define COM_E_UNINIT        ((uint8)0x02u)
#define COM_E_PARAM_POINTER ((uint8)0x03u)
#define COM_E_INIT_FAILED   ((uint8)0x04u)
#endif /*STD_ON == COM_DEV_ERROR_DETECT*/
#define COM_MAINFUNCTIONTX_ID      ((uint8)0x19u)
#define COM_E_SKIPPED_TRANSMISSION ((uint8)0x05u)

/*the Private Macro Definition*/
#define COM_UNUSED_UINT8     (0xFFu)
#define COM_UNUSED_UINT16    (0xFFFFu)
#define COM_UNUSED_UINT32    (0xFFFFFFFFu)
#define COM_UNUSED_UINT64    (0xFFFFFFFFFFFFFFFFu)
#define COM_NOUSED(paramter) (void)(paramter)

/* the initState for RxIPdu */
#define Com_RX_ACTIVE_EN       0x1u
#define Com_RX_DM_EN           0x2u
#define Com_RX_RECEIVING_EN    0x4u
#define Com_RX_INDICATION_EN   0x8u
#define Com_RX_COUNTER_PDU_EN  0x10u

#define Com_RX_ACTIVE_DIS      0xFEu
#define Com_RX_DM_DIS          0xFDu
#define Com_RX_RECEIVING_DIS   0xFBu
#define Com_RX_INDICATION_DIS  0xF7u
#define Com_RX_COUNTER_PDU_DIS 0xEFu

/* the initState for TxIPdu */
#define Com_TX_ACTIVE_EN                     0x1u
#define Com_TX_CONFIRM_EN                    0x2u
#define Com_TX_TMS_EN                        0x4u
#define Com_TX_TRANSMITING_EN                0x8u
#define Com_TX_DELAY_EN                      0x10u

#define Com_TX_ACTIVE_DIS                    0xFEu
#define Com_TX_CONFIRM_DIS                   0xFDu
#define Com_TX_TMS_DIS                       0xFBu
#define Com_TX_TRANSMITING_DIS               0xF7u
#define Com_TX_DELAY_DIS                     0xEFu

#define COM_NTIMESTRANSMITNEED_EN            0x1u
#define COM_WITHOUTREPETITION_EN             0x2u

#define COM_NTIMESTRANSMITNEED_DIS           0xFEu
#define COM_WITHOUTREPETITION_DIS            0xFDu

#define COM_TX_SIGNAL_NOTIFICATION_NONE      0x0u
#define COM_TX_SIGNAL_NOTIFICATION_EN        0x1u
#define COM_TX_SIGNAL_ERROR_NOTIFICATION_EN  0x2u
#define COM_TX_SIGNAL_ERROR_AND_NOTIFICATION 0x3u
/*******************************************************************************
**                      Internal Macro Define                                 **
*******************************************************************************/
#define COM_UNUSED_RXIPDUCOUNTERID            (Com_RxIPduCounterIdType)(-1)
#define COM_UNUSED_RXIPDUGWID                 (Com_RxIpduGWIdType)(-1)
#define COM_UNUSED_RXIPDUGROUPID              (Com_RxIpduGroupIdType)(-1)
#define COM_UNUSED_TXIPDUGROUPID              (Com_TxIpduGroupIdType)(-1)
#define COM_UNUSED_RXSIGTIMEOUTID             (Com_RxSigTimeoutIdType)(-1)
#define COM_UNUSED_RXSIGGRPTIMEOUTID          (Com_RxSigGrpTimeoutIdType)(-1)
#define COM_UNUSED_GWSOURCEDESCRIPTIONID      (Com_GwSourceDescriptionIdType)(-1)
#define COM_UNUSED_RXSIGNALID                 (Com_RxSignalIdType)(-1)
#define COM_UNUSED_RXSIGNALGROUPID            (Com_RxSignalGroupIdType)(-1)
#define COM_UNUSED_GWDESTINATIONDESCRIPTIONID (Com_GwDestinationDescriptionIdType)(-1)
#define COM_UNUSED_TXSIGNALID                 (Com_TxSignalIdType)(-1)
#define COM_UNUSED_TXSIGNALGROUPID            (Com_TxSignalGroupIdType)(-1)
#define COM_UNUSED_TXIPDUCOUNTERID            (Com_TxIPduCounterIdType)(-1)
#define COM_UNUSED_RXSIGNALINVALIDID          (Com_RxSignalInvalidIdType)(-1)
#define COM_UNUSED_RXSIGNALFILTERID           (Com_RxSignalFilterIdType)(-1)
#define COM_UNUSED_SIGNALPOSITION             (Com_SignalPositionType)(-1)
#define COM_UNUSED_TXSIGNALINVALIDID          (Com_TxSignalInvalidIdType)(-1)
#define COM_UNUSED_TXSIGNALFILTERID           (Com_TxSignalFilterIdType)(-1)
#define COM_UNUSED_TXSIGERRANDNOTIFYID        (Com_TxSigErrAndNotifyIdType)(-1)
#define COM_UNUSED_TXSIGNALTIMEOUTID          (Com_TxSignalTimeoutIdType)(-1)
#define COM_UNUSED_RXGROUPSIGNALID            (Com_RxGroupSignalIdType)(-1)
#define COM_UNUSED_TXGROUPSIGNALID            (Com_TxGroupSignalIdType)(-1)
#define COM_UNUSED_TXSIGGRPERRANDNOTIFYID     (Com_TxSigGrpErrAndNotifyIdType)(-1)
#define COM_UNUSED_TXSIGGRPTIMEOUTID          (Com_TxSigGrpTimeoutIdType)(-1)
#define COM_UNUSED_RXGRPSIGFILTERID           (Com_RxGrpSigFilterIdType)(-1)
#define COM_UNUSED_TXGRPSIGFILTERID           (Com_TxGrpSigFilterIdType)(-1)
#define COM_UNUSED_DESTSIGNALFILTERID         (Com_DestSignalFilterIdType)(-1)
#define COM_UNUSED_COM_RXIPDUBUFID            (Com_RxIpduBufIdType)(-1)
#define COM_UNUSED_COM_TXIPDUBUFID            (Com_TxIpduBufIdType)(-1)
#define COM_UNUSED_COM_SIGNALGROUPARRYID      (Com_SignalGroupArryIdType)(-1)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*define in Com.c*/
extern P2CONST(Com_ConfigType, COM_VAR, COM_CONST) Com_ConfigStd;
/*define in Com_Cfg.c*/
extern CONST(Com_ConfigType, COM_CONST_PBCFG) Com_PBConfigData;
/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/
BEGIN_C_DECLS
/******************************************************************************/
/*
 * Brief               Returns the version information of this module.
 * ServiceId           0x09
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     versioninfo: Pointer to where to store the version information of this module.
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/******************************************************************************/
#if (STD_ON == COM_VERSION_INFO_API)
#if (STD_ON == COM_DEV_ERROR_DETECT)
#define Com_GetVersionInfo(VersionInfo)                                                                        \
    do                                                                                                         \
    {                                                                                                          \
        if (NULL_PTR == (VersionInfo))                                                                         \
        {                                                                                                      \
            (void)Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, COM_GETVERSIONINFO_ID, COM_E_PARAM_POINTER); \
        }                                                                                                      \
        else                                                                                                   \
        {                                                                                                      \
            (VersionInfo)->vendorID = COM_VENDOR_ID;                                                           \
            (VersionInfo)->moduleID = COM_MODULE_ID;                                                           \
            (VersionInfo)->sw_major_version = COM_H_SW_MAJOR_VERSION;                                          \
            (VersionInfo)->sw_minor_version = COM_H_SW_MINOR_VERSION;                                          \
            (VersionInfo)->sw_patch_version = COM_H_SW_PATCH_VERSION;                                          \
        }                                                                                                      \
    } while (0)
#else
#define Com_GetVersionInfo(VersionInfo)                           \
    do                                                            \
    {                                                             \
        (VersionInfo)->vendorID = COM_VENDOR_ID;                  \
        (VersionInfo)->moduleID = COM_MODULE_ID;                  \
        (VersionInfo)->sw_major_version = COM_H_SW_MAJOR_VERSION; \
        (VersionInfo)->sw_minor_version = COM_H_SW_MINOR_VERSION; \
        (VersionInfo)->sw_patch_version = COM_H_SW_PATCH_VERSION; \
    } while (0)
#endif
#endif
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
extern FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST_PBCFG) config);
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
extern FUNC(void, COM_CODE) Com_DeInit(void);
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
extern FUNC(void, COM_CODE) Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize);
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
extern FUNC(void, COM_CODE) Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector);
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
extern FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void);
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
extern FUNC(void, COM_CODE) Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector);
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
extern FUNC(void, COM_CODE)
    Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval);
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
extern FUNC(uint8, COM_CODE)
    Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr);
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
extern FUNC(uint8, COM_CODE)
    Com_SendDynSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr, uint16 Length);
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
extern FUNC(uint8, COM_CODE)
    Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr);
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
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
extern FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(
    Com_SignalIdType SignalId,
    P2VAR(void, AUTOMATIC, COM_APPL_CONST) SignalDataPtr,
    P2VAR(uint16, AUTOMATIC, COM_APPL_CONST) Length);
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
extern FUNC(uint8, COM_CODE) Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId);
/******************************************************************************/
/*
 * Brief               The service Com_ReceiveSignalGroup copies the received signal group from the I-PDU to the shadow
 *                     buffer.
 * ServiceId           0x0e
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be received.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY)
 *                     E_OK: service has been accepted
 *                     COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to
 *                     development error)
 *                     COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId);
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
#if (STD_ON == COM_ENABLE_SIGNAL_GROUP_ARRAY_API)
extern FUNC(uint8, COM_CODE) Com_SendSignalGroupArray(
    Com_SignalGroupIdType SignalGroupId,
    P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) SignalGroupArrayPtr);
#endif
/******************************************************************************/
/*
 * Brief               The service Com_ReceiveSignalGroupArray copies the received signal group
 *                     array representation from the PDU to the location designated by SignalGroupArrayPtr.
 * ServiceId           0x24
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant for the same signal group. Reentrant for different signal groups.
 * Param-Name[in]      SignalGroupId: Id of signal group to be received.
 * Param-Name[out]     SignalGroupArrayPtr: reference to the location where the received signal group array shall be
 * stored. Param-Name[in/out]  None Return              uint8(E_OK,COM_SERVICE_NOT_AVAILABLE,COM_BUSY) E_OK: service has
 * been accepted COM_SERVICE_NOT_AVAILABLE: corresponding I-PDU group was stopped (or service failed due to development
 * error) COM_BUSY: in case the TP-Buffer is locked for large data types handling
 */
/******************************************************************************/
#if (STD_ON == COM_ENABLE_SIGNAL_GROUP_ARRAY_API)
/* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray(
    Com_SignalGroupIdType SignalGroupId,
    P2VAR(uint8, AUTOMATIC, COM_APPL_CONST) SignalGroupArrayPtr);
/* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
#endif
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
extern FUNC(uint8, COM_CODE) Com_InvalidateSignal(Com_SignalIdType SignalId);
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
extern FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId);
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
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType PduId);
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
extern Std_ReturnType Com_TriggerIPDUSendWithMetaData(PduIdType PduId, uint8* MetaData);

/******************************************************************************/
/*
 * Brief               The service Com_SwitchIpduTxMode sets the transmission mode of the I-PDU referenced by PduId to
 * Mode. In case the transmission mode changes, the new mode shall immediately be effective. In case the requested
 * transmission mode was already active for this I-PDU, the call will have no effect. ServiceId           0x27
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant for different PduIds. Non reentrant for the same PduId.
 * Param-Name[in]      PduId: Id of the I-PDU of which the transmission mode shall be changed.
 *                     Mode: the transmission mode that shall be set.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
extern FUNC(void, COM_CODE) Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode);

END_C_DECLS

#endif /*end of COM_H*/
/*******************************************************************************
**                      End of file                                           **
*******************************************************************************/
