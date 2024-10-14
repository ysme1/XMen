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
 **  FILENAME    : Rte_SchM.h                                                 **
 **                                                                           **
 **  Created on  :                                                            **
 **  Author      : qinchun.yang                                               **
 **  Vendor      :                                                            **
 **  DESCRIPTION :                                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R1911                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

#ifndef RTE_SCHM_H_
#define RTE_SCHM_H_
#include "Rte.h"
/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/
/*Post build configuration type*/
typedef struct
{
    uint8 reserved;
} SchM_ConfigType;

FUNC(void, RTE_CODE)
SchM_Start(void);

FUNC(void, RTE_CODE)
SchM_Init(P2CONST(SchM_ConfigType, AUTOMATIC, RTE_APPL_DATA) ConfigPtr);

FUNC(void, RTE_CODE)
SchM_Deinit(void);

FUNC(void, RTE_CODE)
SchM_StartTiming(void);

#endif /* RTE_SCHM_H_ */
