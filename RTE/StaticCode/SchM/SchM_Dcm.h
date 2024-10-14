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
 **  FILENAME    : SchM_Dcm.h                                                  **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : Xinrun.Wang                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Dcm Schedule Manager                                        **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef SCHM_DCM_H
#define SCHM_DCM_H

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* PRQA S 0342++ */ /* MISRA Rule 20.10 */
#define SchM_Switch_DcmDiagnosticSessionControl(Session)      SchM_Switch_##bsnp##_DcmDiagnosticSessionControl(Session)
#define SchM_Switch_DcmControlDTCSetting(Setting)             SchM_Switch_##bsnp##_DcmControlDTCSetting(Setting)
#define SchM_Switch_DcmEcuReset(Reset)                        SchM_Switch_##bsnp##_DcmEcuReset(Reset)

#define SchM_Switch_bsnp_DcmDiagnosticSessionControl(Session) (Session)
#define SchM_Switch_bsnp_DcmControlDTCSetting(Setting)
#define SchM_Switch_bsnp_DcmEcuReset(Reset) SchM_PerformReset(Reset)

#define SchM_Enter_Dcm(exclusiveArea)       SchM_Enter_Dcm_##exclusiveArea
#define SchM_Exit_Dcm(exclusiveArea)        SchM_Exit_Dcm_##exclusiveArea
/* PRQA S 0342-- */ /* MISRA Rule 20.10 */

#define SchM_Enter_Dcm_Dcm_ChannelCtrl
#define SchM_Exit_Dcm_Dcm_ChannelCtrl

#define SchM_Enter_Dcm_Dcm_MsgCtrl
#define SchM_Exit_Dcm_Dcm_MsgCtrl

#define SchM_Enter_Dcm_Dcm_ConnectionCtrl
#define SchM_Exit_Dcm_Dcm_ConnectionCtrl

#define SchM_Enter_Dcm_Dcm_ProtocolCtrl
#define SchM_Exit_Dcm_Dcm_ProtocolCtrl

#define SchM_Enter_Dcm_Dcm_ProtocolPreemptCtrl
#define SchM_Exit_Dcm_Dcm_ProtocolPreemptCtrl

#define SchM_Enter_Dcm_Dcm_MkCtrl
#define SchM_Exit_Dcm_Dcm_MkCtrl

#define SchM_Enter_Dcm_Dcm_SesCtrl
#define SchM_Exit_Dcm_Dcm_SesCtrl

#define SchM_Enter_Dcm_Dcm_SecCtrl
#define SchM_Exit_Dcm_Dcm_SecCtrl

#define SchM_Enter_Dcm_Dcm_Channel
#define SchM_Exit_Dcm_Dcm_Channel

#define SchM_Enter_Dcm_Dcm_CommCtrl
#define SchM_Exit_Dcm_Dcm_CommCtrl

#define SchM_Enter_Dcm_Dcm_LinkControlCtrl
#define SchM_Exit_Dcm_Dcm_LinkControlCtrl

#define SchM_Enter_Dcm_Dcm_DspProgram
#define SchM_Exit_Dcm_Dcm_DspProgram

#define SchM_Enter_Dcm_Dcm_PageBufferData
#define SchM_Exit_Dcm_Dcm_PageBufferData

#define SchM_Enter_Dcm_Dcm_RoutineControlState
#define SchM_Exit_Dcm_Dcm_RoutineControlState
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /*
     * Brief               <This service is used for processing the tasks of the main loop. >
     * ServiceId           <0x25>
     * Sync/Async          <Synchronous>
     * Reentrancy          <Non Reentrant>
     * Param-Name[in]      <None>
     * Param-Name[out]     <None>
     * Param-Name[in/out]  <None>
     * Return              <None>
     * PreCondition        <None>
     * CallByAPI           <APIName>
     */
    /*************************************************************************/
    /* PRQA S 3449,3451++ */ /* MISRA Rule 8.5 */
    extern FUNC(void, DCM_CODE) Dcm_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_DCM_H_ */
