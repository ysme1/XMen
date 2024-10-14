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
 **  FILENAME    : SchM_CanTp.h                                                **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : tao.yu                                                      **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Schedule entity for CANSM                                   **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef SCHM_CANTP_H
#define SCHM_CANTP_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0
 *
 *
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define SCHM_CANTP_H_AR_MAJOR_VERSION 2
#define SCHM_CANTP_H_AR_MINOR_VERSION 3
#define SCHM_CANTP_H_AR_PATCH_VERSION 0
#define SCHM_CANTP_H_SW_MAJOR_VERSION 1
#define SCHM_CANTP_H_SW_MINOR_VERSION 0
#define SCHM_CANTP_H_SW_PATCH_VERSION 0

/*=======[I N C L U D E S]====================================================*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*=======[M A C R O S]========================================================*/
#if !defined(CANTP_USED_SCHM)
#define CANTP_USED_SCHM 1
#endif /* !defined CANTP_USED_SCHM */

#if CANTP_USED_SCHM
#include "Os.h"
#endif /* CANTP_USED_SCHM */

#define CANTP_EXCLUSIVE_AREA_CHANNEL 0
#define CANTP_EXCLUSIVE_AREA_STATE   1

#ifdef CANTP_USED_SCHM
#define SchM_Enter_CanTp(InstanceID, ExclusiceArea) DisableAllInterrupts()
#define SchM_Exit_CanTp(InstanceID, ExclusiceArea)  EnableAllInterrupts()
#else /* CANTP_USED_SCHM */
#define SchM_Enter_CanTp(InstanceID, ExclusiceArea)
#define SchM_Exit_CanTp(InstanceID, ExclusiceArea)
#endif /* CANTP_USED_SCHM */
    /*=======[T Y P E   D E F I N I T I O N S]====================================*/

    /*=======[E X T E R N A L   D A T A]==========================================*/

    /*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
    /*
     * Brief               The main function for scheduling the CANTP.
     * ServiceId           0x06
     * Sync/Async          Synchronous
     * Reentrancy          Non Reentrant
     * Param-Name[in]      N/A
     * Param-Name[out]     N/A
     * Param-Name[in/out]  N/A
     * Return              N/A
     * PreCondition        CanTp module initialized
     * CallByAPI           SchM
     */
    extern FUNC(void, CANTP_APPL_CODE) CanTp_MainFunction(void);
    /*=======[I N T E R N A L   D A T A]==========================================*/

    /*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SCHM_CANTP_H */

/*=======[E N D   O F   F I L E]==============================================*/
