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
 **  DESCRIPTION : functions related to the Memory Protection Unit (MPU)       **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef ARCH_MPU_H_
#define ARCH_MPU_H_

/*=======[I N C L U D E S]====================================================*/
#include "Os.h"
/*=======[M A C R O S]========================================================*/
/* MPU Register */
#define OS_MPU_CESR_ADDR        (0x4000D000u)

#define OS_MPU_RGD0_WORD0_ADDR  (0x4000D400u)
#define OS_MPU_RGD0_WORD1_ADDR  (0x4000D404u)
#define OS_MPU_RGD0_WORD2_ADDR  (0x4000D408u)
#define OS_MPU_RGD0_WORD3_ADDR  (0x4000D40Cu)
#define OS_MPU_RGD1_WORD0_ADDR  (0x4000D410u)
#define OS_MPU_RGD1_WORD1_ADDR  (0x4000D414u)
#define OS_MPU_RGD1_WORD2_ADDR  (0x4000D418u)
#define OS_MPU_RGD1_WORD3_ADDR  (0x4000D41Cu)
#define OS_MPU_RGD2_WORD0_ADDR  (0x4000D420u)
#define OS_MPU_RGD2_WORD1_ADDR  (0x4000D424u)
#define OS_MPU_RGD2_WORD2_ADDR  (0x4000D428u)
#define OS_MPU_RGD2_WORD3_ADDR  (0x4000D42Cu)
#define OS_MPU_RGD3_WORD0_ADDR  (0x4000D430u)
#define OS_MPU_RGD3_WORD1_ADDR  (0x4000D434u)
#define OS_MPU_RGD3_WORD2_ADDR  (0x4000D438u)
#define OS_MPU_RGD3_WORD3_ADDR  (0x4000D43Cu)
#define OS_MPU_RGD4_WORD0_ADDR  (0x4000D440u)
#define OS_MPU_RGD4_WORD1_ADDR  (0x4000D444u)
#define OS_MPU_RGD4_WORD2_ADDR  (0x4000D448u)
#define OS_MPU_RGD4_WORD3_ADDR  (0x4000D44Cu)
#define OS_MPU_RGD5_WORD0_ADDR  (0x4000D450u)
#define OS_MPU_RGD5_WORD1_ADDR  (0x4000D454u)
#define OS_MPU_RGD5_WORD2_ADDR  (0x4000D458u)
#define OS_MPU_RGD5_WORD3_ADDR  (0x4000D45Cu)
#define OS_MPU_RGD6_WORD0_ADDR  (0x4000D460u)
#define OS_MPU_RGD6_WORD1_ADDR  (0x4000D464u)
#define OS_MPU_RGD6_WORD2_ADDR  (0x4000D468u)
#define OS_MPU_RGD6_WORD3_ADDR  (0x4000D46Cu)
#define OS_MPU_RGD7_WORD0_ADDR  (0x4000D470u)
#define OS_MPU_RGD7_WORD1_ADDR  (0x4000D474u)
#define OS_MPU_RGD7_WORD2_ADDR  (0x4000D478u)
#define OS_MPU_RGD7_WORD3_ADDR  (0x4000D47Cu)
#define OS_MPU_RGD8_WORD0_ADDR  (0x4000D480u)
#define OS_MPU_RGD8_WORD1_ADDR  (0x4000D484u)
#define OS_MPU_RGD8_WORD2_ADDR  (0x4000D488u)
#define OS_MPU_RGD8_WORD3_ADDR  (0x4000D48Cu)
#define OS_MPU_RGD9_WORD0_ADDR  (0x4000D490u)
#define OS_MPU_RGD9_WORD1_ADDR  (0x4000D494u)
#define OS_MPU_RGD9_WORD2_ADDR  (0x4000D498u)
#define OS_MPU_RGD9_WORD3_ADDR  (0x4000D49Cu)

#define OS_MPU_RGD10_WORD0_ADDR (0x4000D4A0u)
#define OS_MPU_RGD10_WORD1_ADDR (0x4000D4A4u)
#define OS_MPU_RGD10_WORD2_ADDR (0x4000D4A8u)
#define OS_MPU_RGD10_WORD3_ADDR (0x4000D4ACu)
#define OS_MPU_RGD11_WORD0_ADDR (0x4000D4B0u)
#define OS_MPU_RGD11_WORD1_ADDR (0x4000D4B4u)
#define OS_MPU_RGD11_WORD2_ADDR (0x4000D4B8u)
#define OS_MPU_RGD11_WORD3_ADDR (0x4000D4BCu)
#define OS_MPU_RGD12_WORD0_ADDR (0x4000D4C0u)
#define OS_MPU_RGD12_WORD1_ADDR (0x4000D4C4u)
#define OS_MPU_RGD12_WORD2_ADDR (0x4000D4C8u)
#define OS_MPU_RGD12_WORD3_ADDR (0x4000D4CCu)
#define OS_MPU_RGD13_WORD0_ADDR (0x4000D4D0u)
#define OS_MPU_RGD13_WORD1_ADDR (0x4000D4D4u)
#define OS_MPU_RGD13_WORD2_ADDR (0x4000D4D8u)
#define OS_MPU_RGD13_WORD3_ADDR (0x4000D4DCu)
#define OS_MPU_RGD14_WORD0_ADDR (0x4000D4E0u)
#define OS_MPU_RGD14_WORD1_ADDR (0x4000D4E4u)
#define OS_MPU_RGD14_WORD2_ADDR (0x4000D4E8u)
#define OS_MPU_RGD14_WORD3_ADDR (0x4000D4ECu)
#define OS_MPU_RGD15_WORD0_ADDR (0x4000D4F0u)
#define OS_MPU_RGD15_WORD1_ADDR (0x4000D4F4u)
#define OS_MPU_RGD15_WORD2_ADDR (0x4000D4F8u)
#define OS_MPU_RGD15_WORD3_ADDR (0x4000D4FCu)

#define OS_MPU_RGDAAC0_ADDR     (0x4000D800u)
#define OS_MPU_RGDAAC1_ADDR     (0x4000D804u)
#define OS_MPU_RGDAAC2_ADDR     (0x4000D808u)
#define OS_MPU_RGDAAC3_ADDR     (0x4000D80Cu)
#define OS_MPU_RGDAAC4_ADDR     (0x4000D810u)
#define OS_MPU_RGDAAC5_ADDR     (0x4000D814u)
#define OS_MPU_RGDAAC6_ADDR     (0x4000D818u)
#define OS_MPU_RGDAAC7_ADDR     (0x4000D81Cu)
#define OS_MPU_RGDAAC8_ADDR     (0x4000D820u)
#define OS_MPU_RGDAAC9_ADDR     (0x4000D824u)
#define OS_MPU_RGDAAC10_ADDR    (0x4000D828u)
#define OS_MPU_RGDAAC11_ADDR    (0x4000D82Cu)
#define OS_MPU_RGDAAC12_ADDR    (0x4000D830u)
#define OS_MPU_RGDAAC13_ADDR    (0x4000D834u)
#define OS_MPU_RGDAAC14_ADDR    (0x4000D838u)
#define OS_MPU_RGDAAC15_ADDR    (0x4000D83Cu)


/* MPU Register Mask */
#define OS_MPU_VALID_BIT        (0x00000001u)
#define OS_MPU_SPERR_BIT        (0xF8000000u)


/* Master 0,1(Core,Debug) (bit[0:11])*/
#define OS_MPU_AP_RWX_RWX       ((0x7)|(0x7<<6))   /* 111b */
#define OS_MPU_AP_RWX_RW        ((0x6)|(0x7<<6))   /* 110b */
#define OS_MPU_AP_RWX_R         ((0x4)|(0x7<<6))   /* 100b */
#define OS_MPU_AP_RWX_RX        ((0x5)|(0x7<<6))   /* 101b */
#define OS_MPU_AP_RWX_NONE      ((0x0)|(0x7<<6))   /* 000b */
#define OS_MPU_AP_RX_RX         ((0x5)|(0x1<<3)|(0x7<<6))   /* 101b */
#define OS_MPU_AP_RX_NONE       ((0x0)|(0x1<<3)|(0x7<<6))   /* 000b */
/* Master 2,3 (bit[12:23]) */
#define OS_MPU_M23_AP_RW        (0x0061F000u)
#define OS_MPU_M23_AP_NONE      (0x00000000u)

#define OS_MPU_REGION_ENABLE    (0x00000001u)
#define OS_MPU_REGION_DISABLE   (0x00000000u)

/* Peripheral address */
#define PERIPHERAL_START        ((uint8*)0x40000000u)
#define PERIPHERAL_END          ((uint8*)0x400FFFFFu)

#define OS_DFLASH_START         ((uint8*)0x01400000u)
#define OS_DFLASH_END           ((uint8*)0x01600000u)

#define OS_PFLASH_START         (0x00000000u)
#define OS_PFLASH_END           (0x0017FFFFu)
#define OS_FLEXNVM_START        (0x10000000u)
#define OS_FLEXNVM_END          (0x1007FFFFu)
#define OS_FLEXRAM_START        (0x14000000u)
#define OS_FLEXRAM_END          (0x14000FFFu)

#define OS_SRAM_START           (0x1FFE0000u)
#define OS_SRAM_END             (0x2001EFFFu)

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/*=======[I N T E R N A L   D A T A]==========================================*/
/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#endif /* Arch_MPU_H */
/*=======[E N D   O F   F I L E]==============================================*/
