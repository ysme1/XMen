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
 **  FILENAME    : Arch_Define.h                                               **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Variable definition                                         **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef ARCH_DEFINE_H
#define ARCH_DEFINE_H
/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
/*=======[M A C R O S]========================================================*/

/*---------------------------------Compiler OS--------------------------------*/
#define	OS_REG32(address)	                (*(volatile uint32*)(address))     /* 32-bit register */
#define OS_REG8(address)	                (*(volatile uint8 *)(address))     /*  8-bit register */
#define CHECK_STACK_USAGE                   1U
#define CHAR_BIT                            8U
#define RPC_WAIT_TIME                       3000
/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef struct
{
    uint8 *pSRamStart;            /* SRAM */
    uint8 *pSRamEnd;
    
    uint8 *pPeripheralStart;      /* PERIPHERAL */
    uint8 *pPeripheralEnd;
    
    uint8 *pRomStart;             /* ROM */
    uint8 *pRomEnd;

    uint8 *pDtcmStart;            /* DTCM */
    uint8 *pDtcmEnd;
}Os_MemProtKnAddr;

typedef struct
{
    Os_MemProtKnAddr OsKernelAddr;
}Os_MemProtKnCfgType;


#endif /* ARCH_DEFINE_H */
/*=======[E N D   O F   F I L E]==============================================*/
