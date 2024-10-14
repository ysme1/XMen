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
 **  FILENAME    : SchM_SoAd.h                                                **
 **                                                                           **
 **  Created on  : 12/03/19                                                   **
 **  Author      : darren.zhang and zhengfei.li                               **
 **  Vendor      :                                                            **
 **  DESCRIPTION :      none                                                  **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */
#ifndef SCHM_SOAD_H_
#define SCHM_SOAD_H_
/*=======[I N C L U D E S]====================================================*/
#include "Os.h"
/*=======[M A C R O S]========================================================*/
#define SOAD_AREA_MSGCONTEXT                      (0)

#define SchM_Enter_SoAd(Instance, Exclusive_Area) SuspendAllInterrupts()
#define SchM_Exit_SoAd(Instance, Exclusive_Area)  ResumeAllInterrupts()

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    extern FUNC(void, SOAD_CODE) SoAd_MainFunction(VAR(void, AUTOMATIC));
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_SOAD_H_ */
