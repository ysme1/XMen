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
 **  FILENAME    : SchM_Xcp.h                                                  **
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
/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>      <AUTHOR>        <REVISION LOG>
 *  V0.0.0       2020-01-20  qinchun.yang    Initial version.
 */
/*============================================================================*/

#ifndef SCHM_XCP_H_
#define SCHM_XCP_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /******************************************************************************/
    /*
     * @brief               <Xcp Module scheduled Function>
     *
     * <Scheduled function of the XCP module> .
     * Service ID   :       <(0x04)>
     * Sync/Async   :       <Synchronous>
     * Reentrancy           <Non Reentrant>
     * @param[in]           <Xcp_ConfigPtr (IN)>
     * @param[out]          <None>
     * @param[in/out]       <None>
     * @return              <None>
     */
    /******************************************************************************/
    extern FUNC(void, XCP_CODE) Xcp_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_XCP_H_ */
