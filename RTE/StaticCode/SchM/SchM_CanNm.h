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
 **  FILENAME    : SchM_CanNm.h                                               **
 **                                                                           **
 **  Created on  :                                                            **
 **  Author      : darren.zhang                                               **
 **  Vendor      :                                                            **
 **  DESCRIPTION : Implementation for CanNm                                   **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 ******************************************************************************/
/* PRQA S 3108-- */
#ifndef SCHM_CANNM_H_
#define SCHM_CANNM_H_

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/

#define SchM_Enter_CanNm_Context()
#define SchM_Exit_CanNm_Context()
#define SchM_Enter_CanNm_PnEiraCalc()
#define SchM_Exit_CanNm_PnEiraCalc()

/******************************************************************************/
/*
 * Brief               Main function of the CanNm which processes the algorithm
 *                     describes in that document.
 * ServiceId           0x13
 * Sync/Async          None
 * Reentrancy          None
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
void CanNm_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_CANNM_H_ */
