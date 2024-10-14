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
 **  FILENAME    : BswM_Swc.h                                                  **
 **                                                                            **
 **  Created on  : 2020-03-24                                                  **
 **  Author      : qinchun.yang                                                **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef BSWM_SWC_H
#define BSWM_SWC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "BswM_Internal.h"
#if (BSWM_RTE_ENABLED == STD_ON)
#include "Rte_BswM.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Declaration                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/

/**
 * This is a notification that an error occurred because the partition containing
 * the mode users of the Mode Declaration Group Prototype was restarted by the
 * RTE. Because the Mode Machine Instance holding the current mode can reside on
 * that terminated partition, the Mode Manager has to be informed about the loss
 * of this partition.
 * Service ID:
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters(IN): portId, the id of switch port
 * Parameters(INOUT): NA
 * Parameters(OUT): NA
 * Return value: NA
 */
FUNC(void, BSWM_SWC_CODE)
BswM_SwcModeSwitchErrorNotification(uint16 portId);

/**
 * Function called when a SWC has switched a mode.
 * Service ID: 0x
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters(IN): modeGroup, the mode group in that the mode was switched
 *                 mode, the mode that was switched to.
 * Parameters(INOUT): NA
 * Parameters(OUT): NA
 * Return value: NA
 */
FUNC(void, BSWM_SWC_CODE)
BswM_SwcModeNotification(BswM_ModeGroupType modeGroup, BswM_ModeType mode);

/**
 * Function called when a SWC request a mode.
 * Service ID: 0x
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters(IN): modeGroup, the mode group in that the mode was requested
 *                 mode, the mode that was request
 * Parameters(INOUT): NA
 * Parameters(OUT): NA
 * Return value: NA
 */
FUNC(void, BSWM_SWC_CODE)
BswM_SwcModeRequest(BswM_ModeGroupType modeGroup, BswM_ModeType mode);

#endif /* BSWM_RTE_ENABLED == STD_ON */
#endif /* BSWM_SWC_H */
