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
 **  FILENAME    : SchM_LinIf.h                                               **
 **                                                                           **
 **  Created on  :                                                            **
 **  Author      :                                                            **
 **  Vendor      :                                                            **
 **  DESCRIPTION : LinIf                                                      **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2/R19-11               **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */
#ifndef SCHM_LINIF_H
#define SCHM_LINIF_H

#include "Std_Types.h"

#define SCHM_ENTER_LINIF(x, y)
#define SCHM_EXIT_LINIF(x, y)
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /******************************************************************************/
    /*
     * Brief               The main processing function of the LIN Interface.
     * ServiceId           0x80
     * Sync/Async          Synchronous
     * Reentrancy          Non Reentrant
     * Param-Name[in]      N/A
     * Param-Name[in/out]  N/A
     * Param-Name[out]     N/A
     * Return              N/A
     */
    /******************************************************************************/
    extern FUNC(void, LINIF_CODE) LinIf_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_LINIF_H */
