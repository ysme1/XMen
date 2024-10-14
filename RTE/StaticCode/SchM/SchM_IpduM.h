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
 **  FILENAME    : SchM_IpduM.h                                               **
 **                                                                           **
 **  Created on  :                                                            **
 **  Author      :                                                            **
 **  Vendor      :                                                            **
 **  DESCRIPTION : IPDUM                                                      **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */
#ifndef SCHM_IPDUM_H_
#define SCHM_IPDUM_H_
/*=======[I N C L U D E S]====================================================*/

#define SchM_Enter_IpduM_MsgContext() // SuspendAllInterrupts()
#define SchM_Exit_IpduM_MsgContext()  // ResumeAllInterrupts()
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /*
    Scheduled functions
    */
    /**
     * Performs the processes of the activities that are not directly
        initiated by the calls from PDU-R.
     * Service ID: 0x10
     * Sync/Async: NA
     * Reentrancy: NA
     * Parameters(IN): TNA
     * Parameters(INOUT):  NA
     * Parameters(OUT): NA
     * Return value: NA
     *  SWS_IpduM_00101
     */
    extern FUNC(void, IPDUM_CODE) IpduM_MainFunction(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SCHM_IPDUM_H_ */
