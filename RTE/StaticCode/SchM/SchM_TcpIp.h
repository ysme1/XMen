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
 **  FILENAME    : SchM_TcpIp.h                                                **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : darren.zhang                                                **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/***********************************************************************************************************************
**                                          REVISION   HISTORY                                                        **
***********************************************************************************************************************/
/* <VERSION>    <DATE>       <AUTHOR>        <REVISION LOG>
 *  V2.0.0    [20200828]  [pengfei.zhu]   Update to R19-11.
 *  V2.0.1    [20200928]  [pengfei.zhu]   QAC test.
 **********************************************************************************************************************/
#ifndef SCHM_TCPIP_H_
#define SCHM_TCPIP_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#if !defined(TCPIP_USED_SCHM)
#define TCPIP_USED_SCHM 1
#endif /* !defined TCPIP_USED_SCHM */

#if TCPIP_USED_SCHM
#include "Os.h"
#endif /* TCPIP_USED_SCHM */

/***********************************************************************************************************************
**                                          Macro Definitions                                                         **
***********************************************************************************************************************/
#define TCPIP_AREA_TX  (0)
#define TCPIP_AREA_RX  (1)
#define TCPIP_AREA_ALL (2)

#if TCPIP_USED_SCHM
#define SchM_Enter_TcpIp(Instance, Exclusive_Area) SuspendAllInterrupts()
#define SchM_Exit_TcpIp(Instance, Exclusive_Area)  ResumeAllInterrupts()
#else
#define SchM_Enter_TcpIp(Instance, Exclusive_Area)
#define SchM_Exit_TcpIp(Instance, Exclusive_Area)
#endif /* TCPIP_USED_SCHM */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    FUNC(void, TCPIP_CODE) TcpIp_MainFunction(VAR(void, AUTOMATIC));
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_TCPIP_H_ */
