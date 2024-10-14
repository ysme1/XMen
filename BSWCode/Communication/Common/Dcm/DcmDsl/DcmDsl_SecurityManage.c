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
 **  FILENAME    :                                                            **
 **                                                                           **
 **  Created on  : 2020/5/6 14:29:43                                          **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION :                                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

/******************************* references ************************************/
#include "Dcm_Internal.h"
#include "UDS.h"

#if (STD_ON == DCM_SECURITY_FUNC_ENABLED)

/********************************************************
 *******************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
VAR(Dcm_SecCtrlType, DCM_VAR_NOINIT) Dcm_SecCtrl; /*Security level management control block*/
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"

/*************************************************************************/
/*
 * Brief               <initial of Security level control block>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <Dcm_Init()>
 */
/*************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) DslInternal_InitSecCtrl(void) /* PRQA S 1532 */ /* MISRA Rule 8.7 */
{

    SchM_Enter_Dcm(Dcm_SecCtrl);
    Dcm_SecCtrl.Dcm_SubfunctionForSeed = 0u;
    Dcm_SecCtrl.Dcm_ActiveSec = DCM_SEC_LEV_LOCKED;
    Dcm_SecCtrl.Dcm_NewSec = DCM_SEC_LEV_LOCKED;
    Dcm_SecCtrl.Dcm_SecServiceState = DCM_SERVICE_IDLE;
    Dcm_SecCtrl.Dcm_SecFlag = (Dcm_SecCtrl.Dcm_SecFlag & 0x00u) | DCM_SEC_RESUMECALL_MASK;
    Dcm_SecCtrl.Dcm_MaxReadoutTime = 0u;
    Dcm_SecCtrl.Dcm_SecCfgIndex = 0u;
    Dcm_SecCtrl.Dcm_OpStatus = DCM_INITIAL;
    for (uint8 index = 0; index < DCM_SECURITY_NUM; index++)
    {
        Dcm_SecCtrl.Dcm_FalseAcessCount[index] = 0;
    }
    SchM_Exit_Dcm(Dcm_SecCtrl);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/*************************************************************************/
/*
 * Brief               <Setting the security level>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <NewSec:To be changed the security level>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) DslInternal_SetSecurityLevel(Dcm_SecLevelType NewSec)
{
    SchM_Enter_Dcm(Dcm_SecCtrl);
    Dcm_SecCtrl.Dcm_ActiveSec = NewSec;
    SchM_Exit_Dcm(Dcm_SecCtrl);

    SchM_Enter_Dcm(Dcm_MkCtrl);
    Dcm_MkCtrl.Dcm_ActiveSec = NewSec;
    SchM_Exit_Dcm(Dcm_MkCtrl);

#if (STD_ON == DCM_UDS_SERVICE0X2A_ENABLED)
    /*check 2A is supported in NewSec*/
    Dcm_UDS0x2ACheckNewSecurity();
#endif

#if ((DCM_DSP_DID_FOR_2F_NUM > 0) && (STD_ON == DCM_UDS_SERVICE0X2F_ENABLED))
    /*check 2F is supported in NewSec*/
    Dcm_UDS0x2FCheckNewSecurity(NewSec);
#endif
    DslInternal_InitDspProgramInfo();
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/*************************************************************************/
/*
 * Brief               <Set SecurityAccess service process ,receives seed/key status>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Status:State to be modified>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <>
 * CallByAPI           <APIName>
 */
/*************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(void, DCM_CODE) DslInternal_SetSecurityAccessStatus(Dcm_SecServiceStateType Status)
{
    SchM_Enter_Dcm(Dcm_SecCtrl);
    Dcm_SecCtrl.Dcm_SecServiceState = Status;
    SchM_Exit_Dcm(Dcm_SecCtrl);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
FUNC(Std_ReturnType, DCM_CODE)
/* PRQA S 3432++ */ /* MISRA Rule 20.7 */
DslInternal_GetSecurityCfgBySecLevel(Dcm_SecLevelType Dcm_SecLevel, P2VAR(uint8, AUTOMATIC, AUTOMATIC) SecCfgIndex)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    uint8 Index;
    Std_ReturnType ret = E_NOT_OK;
    uint8 SecurityRow_Num = Dcm_DspCfg.pDcm_DspSecurity->DcmDspSecurityRow_Num;

    for (Index = 0; (Index < SecurityRow_Num) && (E_NOT_OK == ret); Index++)
    {
        if (Dcm_SecLevel == (Dcm_DspCfg.pDcm_DspSecurity->pDcm_DspSecurityRow)[Index].DcmDspSecurityLevel)
        {
            *SecCfgIndex = Index;
            ret = E_OK;
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
