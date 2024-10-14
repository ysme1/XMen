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

#ifndef DCMDSL_COMMMANAGE_H
#define DCMDSL_COMMMANAGE_H
/*============================================================================*/

/**************************************************************/
#include "Dcm_Types.h"

/***************************************************************************************
 *************Communication Management sub-function data structure*****
 **************************************************************************************/
typedef enum
{
    DCM_COMM_NO_COMMUNICATION = 0,     /* conmmunication is "NO Communication"status */
    DCM_COMM_SILENT_COMMUNICATION = 1, /* conmmunication is "Silent Communication"status */
    DCM_COMM_FULL_COMMUNICATION = 2    /* conmmunication is "Full Communication"status*/
} Dcm_CommStateType;

typedef enum
{
    DCM_COMM_ACTIVE = 0,
    DCM_COMM_NOT_ACTIVE = 1,
} Dcm_ActiveDiagnosticType;

typedef struct
{
    Dcm_CommStateType Dcm_CommState;
    Dcm_ActiveDiagnosticType Dcm_ActiveDiagnostic;
    NetworkHandleType DcmDslProtocolComMChannelId;
} Dcm_CommCtrlType;

extern VAR(Dcm_CommCtrlType, DCM_VAR_NOINIT) Dcm_CommCtrl[DCM_MAINCONNECTION_NUM];
/*Diagnostic Communication Control*/

/*********************************************************************************
 *****************Communication Management function declarations******************
 ********************************************************************************/
/*************************************************************************/
/*
 * Brief               <initialization of Comm Submodule>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/*************************************************************************/

extern FUNC(void, DCM_CODE) DslInternal_InitComMCtrl(void);

#endif /* DCMDSL_COMMMANAGE_H_ */
