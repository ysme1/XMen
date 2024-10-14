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
 **  FILENAME    : SchM_EcuM.c                                                 **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : qinchun.yang                                                **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*  <VERSION>    <DATE>      <AUTHOR>        <REVISION LOG>
 *  V1.0.0       2020-06-28  qinchun.yang    R19_11 EcuM initial version.
 *  V2.0.0       2021-04-08  qinchun.yang    R1911 stable version.
 */
#ifndef SCHM_ECUM_H
#define SCHM_ECUM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define SchM_Enter_EcuM_GetPendingWkEv()
#define SchM_Eixt_EcuM_GetPendingWkEv()

#define SchM_Enter_EcuM_ClrWkEv()
#define SchM_Eixt_EcuM_ClrWkEv()

#define SchM_Enter_EcuM_GetValidWkEv()
#define SchM_Exit_EcuM_GetValidWkEv()

#define SchM_Enter_EcuM_GetExpiredWkEv()
#define SchM_Exit_EcuM_GetExpiredWkEv()

#define SchM_Enter_EcuM_SetWkEv()
#define SchM_Exit_EcuM_SetWkEv()

#define SchM_Enter_EcuM_ValidWkEv()
#define SchM_Exit_EcuM_ValidWkEv()
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Declaration                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /**
     * The purpose of this service is to implement all activities of the ECU State
     * Manager while the OS is up and running.
     * Service ID[hex]: 0x18
     * Sync/Async: Synchronous
     * Reentrancy: Reentrant
     * Parameters (in): NA
     * Parameters(INOUT): NA
     * Parameters(OUT):  NA
     * Return value: NA
     */
    FUNC(void, ECUM_CODE) EcuM_MainFunction(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_ECUM_H */
