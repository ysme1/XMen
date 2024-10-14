
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
 **                                                                           **
 **  FILENAME    :  Dcm.h                                                     **
 **                                                                           **
 **  Created on  : 2020/5/6 14:29:43                                          **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION : declaration of Dcm                                         **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

#ifndef DCM_H
#define DCM_H
/*=======[R E V I S I O N   H I S T O R Y]====================================*
*  <VERSION>    <DATE>       <AUTHOR>     <REVISION LOG>
*  V1.0.0       2018-3-20    shushi       Initial version
*  V1.0.1       2019-12-24   tao.yu       QAC check fix
*  V1.0.2       2020-1-7     tao.yu       Commercial project problem modification
*  V2.0.0       2021-8-25    tao.yu       release version
*  V2.0.1       2022-4-1     xinrun.wang  move out timing function as callback
*  V2.0.2       2022-8-30    tao.yu       change Dcm_StartRoutineFncType/
    Dcm_StopRoutineFncType/Dcm_RequestResultsRoutineFncType,add Dcm_OpStatusType OpStatus
*  V2.0.3       2023-1-9     tong.zhao
*    1> Change the initialization flag conditions of Dcm_SecCtrl.Dcm_SecFlag
*  V2.0.4       2023-3-29    Xinrun.Wang/tao.yu  Modify 0x31 to match uint32 req/res length,fix 2A data size check
    without prior 2C,Modify Dcm_MsgState processing mechanism
*  V2.0.5       2023-4-13    Xinrun.Wang  Move CheckProtocol behaivor to RxIndication
*  V2.0.6       2023-5-9     Xinrun.Wang  1.Modify 0x36 to check reqlength and sequence to match 0x38
                                          2.Change Dcm_CommunicationModeType Macros to unsigned
*  V2.0.7       2023-6-7     Xinrun.Wang  1.Adjust P2Server timeout calculation by adding a tasktime offset
                                          2.Modify 0x31 return position
                                          3.Modify 0x2F controlEnableMask position
*  V2.0.8       2023-6-13    tao.yu       1.add option Function: in default session, delay S3 time release network
                                          2.change version type
*  V2.0.9       2023-6-29    peng.wu      1.Modified the nrc priority order of 0x10 0x11 0x19 0x22 0x27 0x28 0x2c 0x2f
                                          0x3e 0x85 0x86
*  V2.0.10      2023-7-17    xue.han      fix CPT-6157,fix function request causes a data error while the previous
                                          request is still being processed
*  V2.0.11      2023-8-7     Xinrun.Wang  1. Do not change current reqLen for functional req until tpRxIndication
                                          2. Adjust dynamic req/res length for routine control
*  V2.0.12      2023-8-10    xue.han      fix UDS0x86 Dcm_Uds0X86EventWindowTimeCheck() return value
*  V2.0.13      2023-8-11    xue.han      QAC change
*  V2.0.14      2023-8-18    Xinrun.Wang  Add queued reqeust functionality
*  V2.0.15      2023-8-23    peng.wu      1.CPT-6467 fix Big Endian and little Endian conversion
                                          2.CPT-5999 Fix Dcm_UDS0x19_06SubDeal when DtcExtendedDataRecordNumber is 0xFE
*  V2.0.16      2023-8-24    Xinrun.Wang  check result E_OK for queued request with tpRxIndication
*  V2.0.17      2023-8-25    Xinrun.Wang  Fix Functional Reqeust handle at startOfReception
*  V2.0.18      2023-8-28    peng.wu      add the validation of nrc 7E,33, Update length check in 0x86 service
*  V2.0.19      2023-8-28    Xinrun.Wang  Check if functional request processing at startOfReception
*  V2.0.20      2023-8-31    Xinrun.Wang  Check queued request for functional address req
                             peng.wu      Fix 0x36 service not responding to NRC73 CPT-6718
*  V2.0.21      2023-9-07    xue.han      CPT-6812 Fix OBD0x06 Service SupportBuffer param Initial value
                                          and OBD_ReadPidValues when OBD0x02 Service is enable
                2023-9-11    tao.yu       fix 0x36 service NRC
                2023-9-22    xue.han      fix 0x2A service PeriodicTransmission Rate
                2023-10-25   peng.wu      CPT-7315, Fixed Dcm_0x22DidReadNvmFlag variable assignment in the 22 service
                2023-11-07   peng.wu      CPT-7315, Reset Dcm_0x22DidReadNvmFlag after it is used
*  V2.0.22      2023-11-13   tao.yu       CPT-6467 fix Big Endian and little Endian conversion
                2023-11-14   xue.han      CPT-7595, avoid Dcm_CheckProtocol to use released protocol
                2023-11-15   xue.han      CPT-7613,fix Det error in Dcm_TpRxIndication()
*               2023-11-16   xue.han      CPT-7528, Fixed DcmDsdSubServiceUsed
*               2023-11-17   xue.han      QAC
*  V2.0.23      2023-11-23   xue.han      code performance optimization
*               2023-11-24   xue.han      1、CPT-7683, Fix DtcStatus in Service 19 04、19 06
*                                         2、CPT-7707, Fix macro condition for Dcm_UDS0x2C_Init()
*               2023-11-30   xue.han      1、CPT-7747, Fix 0x22 service NRC13
                                          2、CPT-7653, Delete redundant Attempt Counter process
                2023-12-06   xue.han      1、CPT-7779, Fix 0x22 service sessioncheck 2、QAC
                2023-12-12   xue.han      CPT-7811, Fix 0x10、0x27 service NRC12
                2023-12-06   xue.han      Fix performance optimization ：wrong Dcm_BufferCunrentPosition
                2023-12-08   xue.han      Fix performance optimization ：wrong Dcm_BufferCunrentPosition,UDS0x2C,OBD0x09
                2023-12-12   xue.han      (optimize regression)1、CPT-7747, Fix 0x22 service NRC13
                                          2、CPT-7653, Delete redundant Attempt Counter process
                                          3、CPT-7779, Fix 0x22 service sessioncheck
                                          4、CPT-7811, Fix 0x10、0x27 service NRC12
                2023-12-26   xue.han      QAC
*  V2.0.24      2024-01-03   peng.wu      Add DCM_DDDID_STORAGE_BLOCKID macro condition for Dcm_UDS0x2C_Init(), CPT-7707
                2024-01-04   xinrun.wang  CPT-8017, Fix protocol switch, avoid unnecessary ComM notification
                2024-01-08   xue.han      Add Dem_DcmGetNumberOfFilteredDTC function call in OBD0x03,0x07,0x0A
                2024-01-22   tao.yu       QAC
                2024-01-30   xue.han      Fix OBD_MemSet Array overflow and add inline function.
                2024-01-31   xue.han      CPT-8175,CPT-8239 Fix 0x2F DcmDspDidSignalNum index error and NRC33
                                          CPT-7547,Fix 0x31 ReqLen Type Cast
                2024-03-05   xue.han      CPT-8381,Redesigned how to get Dcm_FalseAcessCount at initialization.
 * V2.0.25      2024-03-29   xue.han      CPT-8405/8406,Add handling of NRC24 and repeat request in service 0x36.
 *                                        CPT-8606/8625,Add handling of NRC71 and address offset in service 0x36.
 *              2024-04-11   xinrun.wang  CPT-8728, data consistency check for queued request process
 *              2024-04-12   xue.han      CPT-8512, Stop 0x2A transfer when DCM_0x2C clear DDDID.
 *              2024-04-23   xue.han      CPT-8405/8625, fix repeat request and NRC71 in service 0x36.
 *              2024-04-28   xue.han      CPT-8731, delete Redundant variable in DslInternal_InitSecCtrl
 *              2024-05-29   xinrun.wang  fix AvailableBufferSize calculation for queued request in copyRxData.
 *              2024-07-16   xue.han      CPT-9354,change DDDID range,including boundary value
 *              2024-07-18   xue.han      CPT-8823,fix UDS0x14 pending response
 *              2024-07-24   xinrun.wang  fix functional address handling for queued request
 *              2024-08-08   xue.han      add mainfunction timer
 * V2.0.26      2024-08-23   xue.han      CPT-10156, fix Dcm_SetProgConditions when programsession
 *                                        CPT-10148, fix Dcm_ActiveNetwork in RX ISR
 *                                        CPT-10250, fix Nrc72 in UDS service 0x2
 *              2024-08-26   xue.han      CPT-10221,fix Subnet handling in UDS service 0x28
 *              2024-08-29   xue.han      delete redundant condition check
 *              2024-09-12   xue.han      fix Dcm_UDS0x2A_DDDidStop,UDS0x28 NRC31
 *              2024-09-27   xue.han      QAC
 *                           peng.wu      CPT-9403, fix DemFreezeFrameRecordNumber range
============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define DCM_AR_RELEASE_MAJOR_VERSION (0x04u)
#define DCM_AR_RELEASE_MINOR_VERSION (0x02u)
#define DCM_AR_RELEASE_PATCH_VERSION (0x02u)
#define DCM_SW_MAJOR_VERSION         (0x02u) /*Major Version*/
#define DCM_SW_MINOR_VERSION         (0x00u) /*Minor Version*/
#define DCM_SW_PATCH_VERSION         (0x1Au) /*Patch version*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Internal.h"
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/
/*
 * Brief                <initialization of DCM module.>
 * ServiceId            <0x01>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) Dcm_Init(P2CONST(Dcm_CfgType, DCM_CONST, DCM_CONST_PBCFG) ConfigPtr);

/*************************************************************************/
/*
 * Brief               <Returns the version information of this module>
 * ServiceId           <0x24>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <VersionInfo:Pointer to where to store
 * the version information of this module>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/*************************************************************************/
#if (STD_ON == DCM_VERSION_INFO_API)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
extern FUNC(void, DCM_CODE) Dcm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_VAR) VersionInfo);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#endif
/*************************************************************************/
/*
 * Brief               <Function to get the VIN (as defined in SAE J1979-DA)>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <Data: Pointer to where to store the VIN>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType:E_OK: The Data pointer has been filled with valid VIN
                                       E_NOT_OK: The default VIN will be used in the DoIP>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/*************************************************************************/
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetVin(P2VAR(uint8, AUTOMATIC, DCM_VAR) Data);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
/*************************************************************************/
/*
 * Brief               <Triggers on changes of the UDS DTC status byte.
 *                      Allows to trigger on ROE Event for subservice OnDTCStatusChanged.>
 * ServiceId           <0x2B>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <DTC: This is the DTC the change trigger is assigned to.
                        DTCStatusOld: DTC status before change
                        DTCStatusNew: DTC status after change>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType E_OK: this value is always returned>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DCM_CODE)
    Dcm_DemTriggerOnDTCStatus(uint32 DTC, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew);

/*************************************************************************/
/*
 * Brief               <This function provides the active security level value.>
 * ServiceId           <0x0d>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <SecLevel:Pointer to Active Security Level value >
 * Param-Name[in/out]   <None>
 * Return               <E_OK:
 *                      E_NOT_OK:>
 * PreCondition         <...>
 * CallByAPI            <APIName>
 */
/*************************************************************************/
/* PRQA S 3432,3449,3451++ */ /* MISRA Rule 20.7,8.5 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_VAR) SecLevel);
/* PRQA S 3432,3449,3451-- */ /* MISRA Rule 20.7,8.5 */
/*************************************************************************/
/*
 * Brief               <This function provides the active session control type value. >
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <SesType:Active Session Control Type value>
 * Param-Name[in/out]  <None>
 * Return              <E_OK,E_NOT_OK>
 * PreCondition        <>
 * CallByAPI           <>
 */
/*************************************************************************/
/* PRQA S 3432,1330,3449,3451++ */ /* MISRA Rule 20.7,8.3,8.5 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_VAR) SesType);
/* PRQA S 3432,1330,3449,3451-- */ /* MISRA Rule 20.7,8.3,8.5 */
/*************************************************************************/
/*
 * Brief               <This function returns the active protocol name. >
 * ServiceId           <0x0f>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <description...>
 * Param-Name[out]     <ActiveProtocol:Active protocol type value >
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <>
 * CallByAPI           <>
 */
/*************************************************************************/
/* PRQA S 3432,3449,3451++ */ /* MISRA Rule 20.7,8.5 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_VAR) ActiveProtocol);
/* PRQA S 3432,3449,3451-- */ /* MISRA Rule 20.7,8.5 */
/*************************************************************************/
/*
 * Brief               <The call to this function allows the application
 *                      to reset the current session to Default session.>
 * ServiceId           <0x2a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <>
 * CallByAPI           <>
 */
/*************************************************************************/
/* PRQA S 3449,3451++ */ /* MISRA Rule 8.5 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(void);
/* PRQA S 3449,3451-- */ /* MISRA Rule 8.5 */
/*************************************************************************/
/*
 * Brief               <The call to this function allows to trigger an
 *                      event linked to a ResponseOnEvent request.>
 * ServiceId           <0x2D>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <RoeEventId: Identifier of the event that is triggered>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <>
 * CallByAPI           <>
 */
/*************************************************************************/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_TriggerOnEvent(uint8 RoeEventId);

/*************************************************************************/
/*
 * Brief               <Allows to activate and deactivate the call
 *                      of ComM_DCM_ActiveDiagnostic() function.>
 * ServiceId           <0x56>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <active If false Dcm shall not call ComM_DCM_ActiveDiagnostic().
 *                      If true Dcm will call ComM_DCM_ActiveDiagnostic().>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>
 * PreCondition        <>
 * CallByAPI           <>
 */
/*************************************************************************/
/* PRQA S 0624,3449,3451++ */ /* MISRA Rule 8.3,8.5 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SetActiveDiagnostic(boolean active);
/* PRQA S 0624,3449,3451-- */ /* MISRA Rule 8.3,8.5 */
/*************************************************************************/

/* PRQA S 3449,3451-- */ /* MISRA Rule 8.5 */
extern Dcm_EcuStartModeType Dcm_GetProgConditions(Dcm_ProgConditionsType* ProgConditions);

#endif /* CANTP_H */
