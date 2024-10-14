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
 **  FILENAME    : SchM_EthTrcv.h                                                **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : HuRongbo                                                    **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef SCHM_ETHTRCV_H_
#define SCHM_ETHTRCV_H_
/*=======[I N C L U D E S]====================================================*/
/*=======[M A C R O S]========================================================*/
#define ETHTRCV_AREA_MSGCONTEXT                      (0)

#define SchM_Enter_EthTrcv(Instance, Exclusive_Area) SuspendAllInterrupts()
#define SchM_Exit_EthTrcv(Instance, Exclusive_Area)  ResumeAllInterrupts()

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /******************************************************************************/
    /*
     * Brief               Used for polling state changes and wakeup reasons.
     * ServiceId           0x0c
     * Sync/Async          Synchronous
     * Reentrancy          NA
     * Param-Name[in]      NA
     * Param-Name[out]     NA
     * Param-Name[in/out]  NA
     * Return              NA
     */
    /******************************************************************************/
    extern FUNC(void, ETHTRCV_CODE) EthTrcv_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_ETHTRCV_H_ */
