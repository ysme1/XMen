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
 **  FILENAME    : SchM_Com.h                                                  **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : shengnan.sun                                                **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Com critical areas management                               **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*  <VERSION>    <DATE>         <AUTHOR>                    <REVISION LOG>
 *  V1.0.0      20130510        zheng fang                 Initial version
 *  V1.0.1      20150401        dongliang chen             Add COM_AREA_COMPLETE
 *  V1.0.2      20240516        shengnan.sun               Add Com critical areas.
 */
/*============================================================================*/
#ifndef SCHM_COM_H
#define SCHM_COM_H

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define SCHM_COM_H_AR_MAJOR_VERSION 1U
#define SCHM_COM_H_AR_MINOR_VERSION 1U
#define SCHM_COM_H_AR_PATCH_VERSION 2U
#define SCHM_COM_H_SW_MAJOR_VERSION 1U
#define SCHM_COM_H_SW_MINOR_VERSION 0U
#define SCHM_COM_H_SW_PATCH_VERSION 2U

#define WRITE_PROTECTION_AREA       1U

#define COM_AREA_COMPLETE

#define SchM_Enter_Com_MultiCore_Lock()
#define SchM_Exit_Com_MultiCore_Lock()

/* PRQA S 3472 ++ */ /* MISRA Rule Dir 4.9 */
#define SchM_Enter_Com_Context() SuspendAllInterrupts()
#define SchM_Exit_Com_Context()  ResumeAllInterrupts()
/* PRQA S 3472 -- */ /* MISRA Rule Dir 4.9 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /******************************************************************************/
    /*
     * Brief               This function performs the processing of the AUTOSAR COM module's receive processing that
     *                     are not directly handled within the COM's functions invoked by the PDU-R, for example
     * Com_RxIndication. ServiceId           0x18 Sync/Async          None Reentrancy          None Param-Name[in] None
     * Param-Name[out]     None
     * Param-Name[in/out]  None
     * Return              None
     */
    /******************************************************************************/
    extern FUNC(void, COM_CODE) Com_MainFunctionRx(void);
    /******************************************************************************/
    /*
     * Brief               This function performs the processing of the AUTOSAR COM module's transmission activities
     * that are not directly handled within the COM's function invoked by the RTE, for example Com_SendSignal. ServiceId
     * 0x19 Sync/Async          None Reentrancy          None Param-Name[in]      None Param-Name[out]     None
     * Param-Name[in/out]  None
     * Return              None
     */
    /******************************************************************************/
    extern FUNC(void, COM_CODE) Com_MainFunctionTx(void);
    /******************************************************************************/
    /*
     * Brief               Calls the signal gateway part of the AUTOSAR COM module to forward received signals to be
     * routed. ServiceId           0x1a Sync/Async          None Reentrancy          None Param-Name[in]      None
     * Param-Name[out]     None
     * Param-Name[in/out]  None
     * Return              None
     */
    /******************************************************************************/
    extern FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_COM_H */
