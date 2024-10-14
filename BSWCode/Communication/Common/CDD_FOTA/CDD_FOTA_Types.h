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
 **  FILENAME    : CDD_FOTA_Types.h                                           **
 **                                                                           **
 **  Created on  : 2020/5/11 16:59:43                                         **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION : Public type definitions for CDD_FOTA module                **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                     **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */
#ifndef CDD_FOTA_TYPES_H
#define CDD_FOTA_TYPES_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"

/******************************************************************************
**                              Macro Definitions                            **
******************************************************************************/
#define CDD_FOTA_SERVICEID_PREINIT                  0x0U
#define CDD_FOTA_SERVICEID_INIT                     0x1U
#define CDD_FOTA_SERVICEID_GETFOTASTATUS            0x2U
#define CDD_FOTA_SERVICEID_GETFOTAPROCESSEDINFO     0x3U
#define CDD_FOTA_SERVICEID_PROCESSTRANSFERDATAWRITE 0x4U
#define CDD_FOTA_SERVICEID_SETFOTAACTIVATE          0x5U
#define CDD_FOTA_SERVICEID_SETFOTAROLLBACK          0x6U
#define CDD_FOTA_SERVICEID_VERIFICATION             0x7U
#define CDD_FOTA_SERVICEID_MAINFUNCTION             0x8U
#define CDD_FOTA_SERVICEID_GETVERSIONINFO           0x9U
#define CDD_FOTA_SERVICEID_PROCESSDOWNLOAD          0xAU
#define CDD_FOTA_SERVICEID_PROCESSEXIT              0xBU
#define CDD_FOTA_SERVICEID_STOPPROCOCOL             0xCU
#define CDD_FOTA_SERVICEID_CANCELINSTALL            0xDU
#define CDD_FOTA_SERVICEID_ERASE                    0xEU
#define CDD_FOTA_SERVICEID_GETBREAKPOINT            0xFU
#define CDD_FOTA_SERVICEID_GETAPPVERSION            0x10U
#define CDD_FOTA_SERVICEID_SETAPPVERSION            0x11U

#define CDD_FOTA_E_UNINIT                           0x01U
#define CDD_FOTA_E_PARAM_POINTER                    0x02U

#define CDD_FOTA_CRC8                               0x1U
#define CDD_FOTA_CRC8H2F                            0x2U
#define CDD_FOTA_CRC16                              0x3U
#define CDD_FOTA_CRC16ARC                           0x4U
#define CDD_FOTA_CRC32                              0x5U
#define CDD_FOTA_CRC32P4                            0x6U
#define CDD_FOTA_CRC64                              0x7U
#define CDD_FOTA_NONE_CRC                           0x8U

#define CDD_FOTA_NEED_WRITE                         0x1U
#define CDD_FOTA_NEED_CRC                           0x2U
#define CDD_FOTA_WRITE_OK                           0x3U

#define CDD_FOTA_JOB_OK                             0x0u
#define CDD_FOTA_JOB_FAILED                         0x1u
#define CDD_FOTA_JOB_PENDING                        0x2u

#define CDD_FOTA_APP_A                              0x55u
#define CDD_FOTA_APP_B                              0xAAu

/******************************************************************************
**                              Type Definitions                             **
******************************************************************************/
typedef enum
{
    CDD_FOTA_MODE_UNINIT,
    CDD_FOTA_MODE_INIT
} CDD_FOTA_ModeType;

typedef struct
{
    uint32 ProcessedAddress;
    uint32 ProgramConter;
    uint8 CurNeedProgramApp;
} CDD_FOTA_ProgramInfoType;

typedef enum
{
    CDD_FOTA_IDLE,
    CDD_FOTA_INIT,
    CDD_FOTA_WAIT,
    CDD_FOTA_PROCESSING,
    CDD_FOTA_READY,
    CDD_FOTA_VERIFY,
    CDD_FOTA_ACTIVATE,
    CDD_FOTA_ERROR
} CDD_FOTA_StatusType;

typedef struct
{
    uint32 WriteMemoryRangeLow;
    uint32 WriteMemoryRangeHigh;
    uint32 length;
    boolean UncompressEnable;
} CDD_FOTA_WriteMemoryRangeType;

typedef enum
{
    CDD_FOTA_NO_ERASE,
    CDD_FOTA_ERASE_A,
    CDD_FOTA_ERASE_B
} CDD_FOTA_CancelInstallType;

#endif /* CDD_FOTA_TYPES_H */
