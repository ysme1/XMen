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
 **  FILENAME    : SchM_NvM.h                                                 **
 **                                                                           **
 **  Created on  :                                                            **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION :                                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

/*======================[R E V I S I O N   H I S T O R Y]=====================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *   V1.0.0     20150312     SDu       Initial version
 *
 *   V1.0.1     20150408     SDu       Add compiler abstrct
 *                                     Improve code effiency
 *                                     Fix bug
 */
/*============================================================================*/
#ifndef SCHM_NVM_H
#define SCHM_NVM_H

/*===================[V E R S I O N  I N F O R M A T I O N]===================*/

#define SCHM_NVM_H_AR_MAJOR_VERSION 2U
#define SCHM_NVM_H_AR_MINOR_VERSION 3U
#define SCHM_NVM_H_AR_PATCH_VERSION 0U
#define SCHM_NVM_H_SW_MAJOR_VERSION 1U
#define SCHM_NVM_H_SW_MINOR_VERSION 0U
#define SCHM_NVM_H_SW_PATCH_VERSION 1U

/*==========================[M A C R O  D E F I N E]==========================*/
#define INTERRUPT_PROTECTION_AREA 0U
#define EXCLUSIVE_AREA_1          1U
#define NVM_AREA                  2U

#define SchM_Enter_NvM_Queue()
#define SchM_Exit_NvM_Queue()

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /*************************************************************************/
    /*
     * Brief               Service for performing the processing of the NvM jobs
     * ServiceId           0x0e
     * Timing              VARIABLE_CYCLIC
     * Param-Name[in]      None
     * Param-Name[out]   None
     * Param-Name[in/out]  None
     * Return              None
     * PreCondition        None
     * CallByAPI           Up layer
     */
    /*************************************************************************/
    extern FUNC(void, NVM_CODE) NvM_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* End of SCHM_NVM_H*/
/*==========================[E N D   O F   F I L E]===========================*/
