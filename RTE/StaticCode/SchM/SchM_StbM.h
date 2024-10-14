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
 **  FILENAME    : SchM_StbM.h                                                 **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : yuzhe.zhang                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : implementation header for StbM                              **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/******************************************************************************
**                      Revision Control History                             **
******************************************************************************/
#ifndef SCHM_STBM_H
#define SCHM_STBM_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Os.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /**
     * This function will be called cyclically by a task body provided by the BSW Schedule.
       It will invoke the triggered customers and synchronize the referenced OS Schedule Tables.
     * Service ID: 0x04
     * Sync/Async: Synchronous
     * Reentrancy: Non Reentrant
     * Parameters(IN): NA
     * Parameters(INOUT): NA
     * Parameters(OUT): NA
     * Return value:    NA
     */
    FUNC(void, STBM_CODE) StbM_MainFunction(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

static inline void SchM_Enter_StbM_Context(void)
{
    SuspendAllInterrupts();
}

static inline void SchM_Exit_StbM_Context(void)
{
    ResumeAllInterrupts();
}

#endif
