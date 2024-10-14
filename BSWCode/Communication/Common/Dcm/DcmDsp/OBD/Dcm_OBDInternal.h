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
 **  FILENAME    : Dcm_OBDIternal.h                                            **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Internal API declaration of OBD                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef DCM_OBDINTERNAL_H
#define DCM_OBDINTERNAL_H
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Internal.h"
#include "Dcm_Cfg.h"
#include "DcmDsl_ProtocolManage.h"
#include "Dem.h"
#include "Dem_Dcm.h"

/*******************************************************************************
**                      macros                                                **
*******************************************************************************/
#define OBD_DATA_LSB_MASK ((uint32)0x000000FFu)

typedef struct
{
    boolean UDSCall;
    uint8 SID;
    uint8 pid;
} OBD_ReadPidValuesTypes;
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
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
static inline FUNC(void, DCM_CODE) OBD_MemSet(P2VAR(uint8, AUTOMATIC, DCM_VAR) Dest, uint8 Val, uint32 Size)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint32 Cnt = Size;
    while (Cnt > 0u)
    {
        Cnt--;
        Dest[Cnt] = Val;
    }
    return;
}
#if (DCM_DSP_PID_FUNC_ENABLED == STD_ON)
/******************************************************************************/
/*
 * Brief               <Read PID values>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ObdMidCfgIndex && ptxPos && pnoFindPIDsNum>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/

FUNC(Std_ReturnType, DCM_CODE)
OBD_ReadPidValues(const OBD_ReadPidValuesTypes* OBD_ReadPid, uint32* pBufOffset, uint8* pNoFindPidNum);

/******************************************************************************/
/*
 * Brief               <Check supported Parameter id>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pDataBuf>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/

FUNC(void, DCM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
OBD_CheckSupportedPIDs(uint8 pid, P2VAR(uint32, AUTOMATIC, DCM_VAR) pDataBuf, uint8 SID);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#endif
/******************************************************************************/
/*
 * Brief               <Check supported test id>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pDataBuf>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <none>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/

FUNC(void, DCM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
OBD_CheckSupportedTIDs(uint8 Tid, P2VAR(uint32, AUTOMATIC, DCM_VAR) pDataBuf);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#if (DCM_DSP_REQUESTCONTROL_FUNC_ENABLED == STD_ON)
/******************************************************************************/
/*
 * Brief               <find config index number of TID>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pCfgIndex>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(Std_ReturnType, DCM_CODE) OBD_FindCfgIndexOfTestID(uint8 testID, P2VAR(uint8, AUTOMATIC, DCM_VAR) pCfgIndex);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#endif
#if (DCM_DSP_VEHINFO_FUNC_ENABLED == STD_ON)
/******************************************************************************/
/*
 * Brief               <Set Availability InfoType Value>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <InfoType && pDataBuf>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/

FUNC(void, DCM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
OBD_SetAvailabilityInfoTypeValue(uint8 InfoType, P2VAR(uint32, AUTOMATIC, DCM_VAR) pDataBuf);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

/******************************************************************************/
/*
 * Brief               <find config index number of VehInfo>
 * ServiceId           <none>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <testID && pCfgIndex>
 * Param-Name[out]     <none>
 * Param-Name[in/out]  <none>
 * Return              <Std_ReturnType>
 * PreCondition        <none>
 * CallByAPI           <APIName>
 */
/******************************************************************************/
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
FUNC(Std_ReturnType, DCM_CODE) OBD_FindCfgIndexOfVehInfo(uint8 vehInfo, P2VAR(uint8, AUTOMATIC, DCM_VAR) pCfgIndex);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
#endif

extern FUNC(void, DCM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dcm_FillTo4bytes(P2VAR(uint8, AUTOMATIC, DCM_VAR) pDataBuf, P2CONST(uint32, AUTOMATIC, DCM_VAR) pData);
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */

#endif /* DCM_OBDINTERNAL_H */
