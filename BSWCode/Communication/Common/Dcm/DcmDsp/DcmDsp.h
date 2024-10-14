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

#ifndef DCMDSP_H
#define DCMDSP_H

/****************************** declarations *********************************/
#if ((STD_ON == DCM_DSP_ROUTINE_FUNC_ENABLED) && (DCM_DSP_ROUTINE_MAX_NUM > 0))

extern VAR(Dcm_RoutineControlStateType, DCM_VAR_NOINIT) Dcm_RoutineControlState[DCM_DSP_ROUTINE_MAX_NUM];

#endif

/*************************************************************************/
/*
 * Brief               <The Dsp layer response to the confirmation>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ProtocolCtrlId:The corresponding protocol control block ID number>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DspInternal_DcmConfirmation(uint8 ProtocolCtrlId);

#if ((STD_ON == DCM_DSP_ROUTINE_FUNC_ENABLED) && (DCM_DSP_ROUTINE_MAX_NUM > 0))

extern FUNC(void, DCM_CODE) Dsp_InitRoutineStates(void);

#endif

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_UdsSubServicesCheck(uint8 ProtocolCtrlId);

#if (STD_ON == DCM_PAGEDBUFFER_ENABLED)

extern FUNC(void, DCM_CODE) DspInternal_DcmUpdatePage(uint8 ProtocolCtrlId);

#endif
/****************************** definitions *********************************/
#endif /* DCMDSP_H_ */
