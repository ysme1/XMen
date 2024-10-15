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
 **  FILENAME    : Arch_Mpu.h                                                  **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Mpu driver                                                  **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef Arch_Mpu_H
#define Arch_Mpu_H

/*=======[I N C L U D E S]====================================================*/
#include "Os_Types.h"

/*=======[M A C R O S]========================================================*/
/* Data */
#define    dsram2_START                           (uint8*)(0x0)
#define    dsram2_END                             (uint8*)(0x0)
#define    dsram1_START                           (uint8*)(0x0)
#define    dsram1_END                             (uint8*)(0x0)
#define    dsram0_START                           (uint8*)(0x0)
#define    dsram0_END                             (uint8*)(0x0)
#define    LMU_SRAM_START                         (uint8*)(0x0)
#define    LMU_SRAM_END                           (uint8*)(0x0)
#define    DFLASH_START                           (uint8*)(0x0)
#define    DFLASH_END                             (uint8*)(0x0)
#define    DMI_DSPR_START                         (uint8*)(0x0)
#define    DMI_DSPR_END                           (uint8*)(0x0)
#define    PERIPHERAL_START                       (uint8*)(0x0)
#define    PERIPHERAL_END                         (uint8*)(0x0)
#define    RODATA_START                           (uint8*)(0x0)
#define    RODATA_END                             (uint8*)(0x0)
/* Code */
#define    PFLASH_START                           (uint8*)(0x0)
#define    PFLASH_END                             (uint8*)(0x0)

/* the region of mpu. */
#define MPU_REGION_0                   (uint8)(0)
#define MPU_REGION_1                   (uint8)(1)
#define MPU_REGION_2                   (uint8)(2)
#define MPU_REGION_3                   (uint8)(3)
#define MPU_REGION_4                   (uint8)(4)
#define MPU_REGION_5                   (uint8)(5)
#define MPU_REGION_6                   (uint8)(6)
#define MPU_REGION_7                   (uint8)(7)
#define MPU_REGION_8                   (uint8)(8)
#define MPU_REGION_9                   (uint8)(9)
#define MPU_REGION_10                  (uint8)(10)
#define MPU_REGION_11                  (uint8)(11)
#define MPU_REGION_12                  (uint8)(12)
#define MPU_REGION_13                  (uint8)(13)
#define MPU_REGION_14                  (uint8)(14)
#define MPU_REGION_15                  (uint8)(15)
#define MPU_REGION_ALL                 (uint8)(16)

#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
/* Set access rights for memory protection. */
/* DD_1_0378 */
/* Set up areas that can be accessed by a trusted APP. */
/* DD_1_0379 */
#define Os_ArchSetTruReg()
/* Set memory protection map for isr of non-trusted app */
/* DD_1_0380 */
#define Os_ArchSetNonTruIsrReg(IsrId, HostAppId)

/* Set memory protection map for isr of trusted app */
/* DD_1_0381 */
#define Os_ArchSetTruIsrProtReg(IsrId, HostAppId)

/* Set memory protection map for task of non-trusted app. */
/* DD_1_0382 */
#define Os_ArchSetNonTruTskReg(TaskId, HostAppId)

/* Set memory protection map for task of trusted app. */
/* DD_1_0383 */
#define Os_ArchSetTruTskProtReg(TaskId, HostAppId)

/* Enable the enable bits for memory protection in PSW and SYSCON. */
/* DD_1_0384 */
#define Os_ArchMemProtEnable()
/* Enable the enable bits for memory protection in PSW. */
/* DD_1_0385 */
#define Os_ArchMemProtSwithToSystem()
#else /* FALSE == CFG_MEMORY_PROTECTION_ENABLE */
/* Enable the enable bits for memory protection in PSW. */
/* DD_1_0385 */
#define Os_ArchMemProtSwithToSystem()
#endif /* TRUE == CFG_MEMORY_PROTECTION_ENABLE */

/*=======[T Y P E   D E F I N I T I O N S]====================================*/


/*=======[E X T E R N A L   D A T A]==========================================*/
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
extern P2CONST(OS_ISR_ADDR, AUTOMATIC, OS_VAR)    Os_IsrDAddr;
extern P2CONST(OS_TASK_ADDR, AUTOMATIC, OS_VAR)   Os_TaskDAddr;
#endif

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#if (TRUE == CFG_MEMORY_PROTECTION_ENABLE)
FUNC(void, OS_CODE) Os_MemProtTaskCat1Map(void);
FUNC(void, OS_CODE) Os_MemProtTaskCat2Map(void);
FUNC(void, OS_CODE) Os_MemProtIsrMap(void);
extern FUNC(void,OS_CODE) Os_ArchInitKnMemMap(void);
#endif

#endif
/*=======[E N D   O F   F I L E]==============================================*/
