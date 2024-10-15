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
 **  FILENAME    : Os_MemmapImp.h                                              **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Memory mapping abstraction declaration of MemMap            **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 * Note: Automatically generated, script version V1.0.0
 */
/*============================================================================*/

/*=======[M E M M A P  S Y M B O L  D E F I N E]==============================*/
#if defined (START_WITH_IF)
/*Index:10  Section name :VAR_CLEARED_CORE0_32*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE0_32
#undef OS_START_SEC_VAR_CLEARED_CORE0_32
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE0_32_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE0_32

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE0_32
#undef OS_STOP_SEC_VAR_CLEARED_CORE0_32
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE0_32_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE0_32_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE0_32

/*Index:11  Section name :VAR_CLEARED_CORE1_32*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE1_32
#undef OS_START_SEC_VAR_CLEARED_CORE1_32
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE1_32_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE1_32

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE1_32
#undef OS_STOP_SEC_VAR_CLEARED_CORE1_32
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE1_32_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE1_32_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE1_32

/*Index:12  Section name :VAR_CLEARED_CORE2_32*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE2_32
#undef OS_START_SEC_VAR_CLEARED_CORE2_32
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE2_32_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE2_32

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE2_32
#undef OS_STOP_SEC_VAR_CLEARED_CORE2_32
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE2_32_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE2_32_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE2_32

/*Index:13  Section name :VAR_CLEARED_CORE3_32*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE3_32
#undef OS_START_SEC_VAR_CLEARED_CORE3_32
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE3_32_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE3_32

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE3_32
#undef OS_STOP_SEC_VAR_CLEARED_CORE3_32
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE3_32_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE3_32_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE3_32

/*Index:14  Section name :VAR_CLEARED_CORE4_32*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE4_32
#undef OS_START_SEC_VAR_CLEARED_CORE4_32
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE4_32_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE4_32

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE4_32
#undef OS_STOP_SEC_VAR_CLEARED_CORE4_32
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE4_32_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE4_32_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE4_32

/*Index:15  Section name :VAR_CLEARED_CORE5_32*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE5_32
#undef OS_START_SEC_VAR_CLEARED_CORE5_32
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE5_32_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE5_32

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE5_32
#undef OS_STOP_SEC_VAR_CLEARED_CORE5_32
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE5_32_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE5_32_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE5_32

/*Index:16  Section name :VAR_CLEARED_CORE0_UNSPECIFIED*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#undef OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#undef OS_STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED

/*Index:17  Section name :VAR_CLEARED_CORE1_UNSPECIFIED*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#undef OS_START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#undef OS_STOP_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE1_UNSPECIFIED

/*Index:18  Section name :VAR_CLEARED_CORE2_UNSPECIFIED*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED
#undef OS_START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE2_UNSPECIFIED
#undef OS_STOP_SEC_VAR_CLEARED_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE2_UNSPECIFIED

/*Index:19  Section name :VAR_CLEARED_CORE3_UNSPECIFIED*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE3_UNSPECIFIED
#undef OS_START_SEC_VAR_CLEARED_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE3_UNSPECIFIED_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE3_UNSPECIFIED

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE3_UNSPECIFIED
#undef OS_STOP_SEC_VAR_CLEARED_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE3_UNSPECIFIED_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE3_UNSPECIFIED_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE3_UNSPECIFIED

/*Index:20  Section name :VAR_CLEARED_CORE4_UNSPECIFIED*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE4_UNSPECIFIED
#undef OS_START_SEC_VAR_CLEARED_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE4_UNSPECIFIED_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE4_UNSPECIFIED

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE4_UNSPECIFIED
#undef OS_STOP_SEC_VAR_CLEARED_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE4_UNSPECIFIED_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE4_UNSPECIFIED_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE4_UNSPECIFIED

/*Index:21  Section name :VAR_CLEARED_CORE5_UNSPECIFIED*/
#elif defined OS_START_SEC_VAR_CLEARED_CORE5_UNSPECIFIED
#undef OS_START_SEC_VAR_CLEARED_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_CLEARED_CORE5_UNSPECIFIED_NO_MATCH
#define START_SEC_VAR_CLEARED_CORE5_UNSPECIFIED

#elif defined OS_STOP_SEC_VAR_CLEARED_CORE5_UNSPECIFIED
#undef OS_STOP_SEC_VAR_CLEARED_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_CLEARED_CORE5_UNSPECIFIED_NO_MATCH
#undef OS_START_SEC_VAR_CLEARED_CORE5_UNSPECIFIED_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_CLEARED_CORE5_UNSPECIFIED

/*Index:22  Section name :VAR_STACK_CORE0*/
#elif defined OS_START_SEC_VAR_STACK_CORE0
#undef OS_START_SEC_VAR_STACK_CORE0
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_STACK_CORE0_NO_MATCH
#define START_SEC_VAR_STACK_CORE0

#elif defined OS_STOP_SEC_VAR_STACK_CORE0
#undef OS_STOP_SEC_VAR_STACK_CORE0
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_STACK_CORE0_NO_MATCH
#undef OS_START_SEC_VAR_STACK_CORE0_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_STACK_CORE0

/*Index:23  Section name :VAR_STACK_CORE1*/
#elif defined OS_START_SEC_VAR_STACK_CORE1
#undef OS_START_SEC_VAR_STACK_CORE1
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_STACK_CORE1_NO_MATCH
#define START_SEC_VAR_STACK_CORE1

#elif defined OS_STOP_SEC_VAR_STACK_CORE1
#undef OS_STOP_SEC_VAR_STACK_CORE1
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_STACK_CORE1_NO_MATCH
#undef OS_START_SEC_VAR_STACK_CORE1_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_STACK_CORE1

/*Index:24  Section name :VAR_STACK_CORE2*/
#elif defined OS_START_SEC_VAR_STACK_CORE2
#undef OS_START_SEC_VAR_STACK_CORE2
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_STACK_CORE2_NO_MATCH
#define START_SEC_VAR_STACK_CORE2

#elif defined OS_STOP_SEC_VAR_STACK_CORE2
#undef OS_STOP_SEC_VAR_STACK_CORE2
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_STACK_CORE2_NO_MATCH
#undef OS_START_SEC_VAR_STACK_CORE2_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_STACK_CORE2

/*Index:25  Section name :VAR_STACK_CORE3*/
#elif defined OS_START_SEC_VAR_STACK_CORE3
#undef OS_START_SEC_VAR_STACK_CORE3
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_STACK_CORE3_NO_MATCH
#define START_SEC_VAR_STACK_CORE3

#elif defined OS_STOP_SEC_VAR_STACK_CORE3
#undef OS_STOP_SEC_VAR_STACK_CORE3
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_STACK_CORE3_NO_MATCH
#undef OS_START_SEC_VAR_STACK_CORE3_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_STACK_CORE3

/*Index:26  Section name :VAR_STACK_CORE4*/
#elif defined OS_START_SEC_VAR_STACK_CORE4
#undef OS_START_SEC_VAR_STACK_CORE4
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_STACK_CORE4_NO_MATCH
#define START_SEC_VAR_STACK_CORE4

#elif defined OS_STOP_SEC_VAR_STACK_CORE4
#undef OS_STOP_SEC_VAR_STACK_CORE4
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_STACK_CORE4_NO_MATCH
#undef OS_START_SEC_VAR_STACK_CORE4_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_STACK_CORE4

/*Index:27  Section name :VAR_STACK_CORE5*/
#elif defined OS_START_SEC_VAR_STACK_CORE5
#undef OS_START_SEC_VAR_STACK_CORE5
#undef MEMMAP_ERROR
#ifndef MEMMAP_ERROR_SEC_NO_MATCH
#define MEMMAP_ERROR_SEC_NO_MATCH
#else
#error "Os_MemMap.h, section is used consecutively many times."
#endif
#define OS_START_SEC_VAR_STACK_CORE5_NO_MATCH
#define START_SEC_VAR_STACK_CORE5

#elif defined OS_STOP_SEC_VAR_STACK_CORE5
#undef OS_STOP_SEC_VAR_STACK_CORE5
#undef MEMMAP_ERROR
#ifdef OS_START_SEC_VAR_STACK_CORE5_NO_MATCH
#undef OS_START_SEC_VAR_STACK_CORE5_NO_MATCH
#else
#error "Os_MemMap.h, no matching section was used."
#endif
#ifdef MEMMAP_ERROR_SEC_NO_MATCH
#undef MEMMAP_ERROR_SEC_NO_MATCH
#endif
#define STOP_SEC_VAR_STACK_CORE5
#endif /* START_WITH_IF */

/*Code*/
#if defined (START_SEC_CODE)
#undef      START_SEC_CODE
#pragma default_function_attributes = @ ".bsw.code.defult"
#endif

/* stop pragma */
#if defined (STOP_SEC_CODE)
#undef      STOP_SEC_CODE
#pragma default_function_attributes =
#endif

/* start pragma */
#if defined (START_SEC_CONST_PTR)
#undef      START_SEC_CONST_PTR
#pragma default_variable_attributes = @ ".bsw.const.ptr"
#endif

/* stop pragma */
#if defined (STOP_SEC_CONST_PTR)
#undef      STOP_SEC_CONST_PTR
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_CONST_UNSPECIFIED)
#undef      START_SEC_CONST_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.const.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_CONST_UNSPECIFIED)
#undef      STOP_SEC_CONST_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CLONE_16)
#undef      START_SEC_VAR_CLEARED_CLONE_16
#pragma default_variable_attributes = @ ".bsw.clear.clone.16bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CLONE_16)
#undef      STOP_SEC_VAR_CLEARED_CLONE_16
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CLONE_32)
#undef      START_SEC_VAR_CLEARED_CLONE_32
#pragma default_variable_attributes = @ ".bsw.clear.clone.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CLONE_32)
#undef      STOP_SEC_VAR_CLEARED_CLONE_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CLONE_8)
#undef      START_SEC_VAR_CLEARED_CLONE_8
#pragma default_variable_attributes = @ ".bsw.clear.clone.8bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CLONE_8)
#undef      STOP_SEC_VAR_CLEARED_CLONE_8
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CLONE_UNSPECIFIED)
#undef      START_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.clear.clone.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CLONE_UNSPECIFIED)
#undef      STOP_SEC_VAR_CLEARED_CLONE_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CLONE_PTR)
#undef      START_SEC_VAR_CLEARED_CLONE_PTR
#pragma default_variable_attributes = @ ".bsw.clear.clone.ptr"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CLONE_PTR)
#undef      STOP_SEC_VAR_CLEARED_CLONE_PTR
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CORE0_32)
#undef      START_SEC_VAR_CLEARED_CORE0_32
#pragma default_variable_attributes = @ ".bsw.clear.core0.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CORE0_32)
#undef      STOP_SEC_VAR_CLEARED_CORE0_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED)
#undef      START_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.clear.core0.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED)
#undef      STOP_SEC_VAR_CLEARED_CORE0_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CORE1_32)
#undef      START_SEC_VAR_CLEARED_CORE1_32
#pragma default_variable_attributes = @ ".bsw.clear.core1.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CORE1_32)
#undef      STOP_SEC_VAR_CLEARED_CORE1_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED)
#undef      START_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.clear.core1.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CORE1_UNSPECIFIED)
#undef      STOP_SEC_VAR_CLEARED_CORE1_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CORE2_32)
#undef      START_SEC_VAR_CLEARED_CORE2_32
#pragma default_variable_attributes = @ ".bsw.clear.core2.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CORE2_32)
#undef      STOP_SEC_VAR_CLEARED_CORE2_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED)
#undef      START_SEC_VAR_CLEARED_CORE2_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.clear.core2.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_CORE2_UNSPECIFIED)
#undef      STOP_SEC_VAR_CLEARED_CORE2_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_GLOBAL_32)
#undef      START_SEC_VAR_CLEARED_GLOBAL_32
#pragma default_variable_attributes = @ ".bsw.clear.global.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_GLOBAL_32)
#undef      STOP_SEC_VAR_CLEARED_GLOBAL_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_CLEARED_GLOBAL_UNSPECIFIED)
#undef      START_SEC_VAR_CLEARED_GLOBAL_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.clear.global.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_CLEARED_GLOBAL_UNSPECIFIED)
#undef      STOP_SEC_VAR_CLEARED_GLOBAL_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CLONE_16)
#undef      START_SEC_VAR_INIT_CLONE_16
#pragma default_variable_attributes = @ ".bsw.init.clone.16bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CLONE_16)
#undef      STOP_SEC_VAR_INIT_CLONE_16
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CLONE_32)
#undef      START_SEC_VAR_INIT_CLONE_32
#pragma default_variable_attributes = @ ".bsw.init.clone.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CLONE_32)
#undef      STOP_SEC_VAR_INIT_CLONE_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CLONE_8)
#undef      START_SEC_VAR_INIT_CLONE_8
#pragma default_variable_attributes = @ ".bsw.init.clone.8bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CLONE_8)
#undef      STOP_SEC_VAR_INIT_CLONE_8
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CLONE_UNSPECIFIED)
#undef      START_SEC_VAR_INIT_CLONE_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.init.clone.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CLONE_UNSPECIFIED)
#undef      STOP_SEC_VAR_INIT_CLONE_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CLONE_PTR)
#undef      START_SEC_VAR_INIT_CLONE_PTR
#pragma default_variable_attributes = @ ".bsw.init.clone.ptr"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CLONE_PTR)
#undef      STOP_SEC_VAR_INIT_CLONE_PTR
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CORE0_32)
#undef      START_SEC_VAR_INIT_CORE0_32
#pragma default_variable_attributes = @ ".bsw.init.core0.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CORE0_32)
#undef      STOP_SEC_VAR_INIT_CORE0_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CORE0_UNSPECIFIED)
#undef      START_SEC_VAR_INIT_CORE0_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.init.core0.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CORE0_UNSPECIFIED)
#undef      STOP_SEC_VAR_INIT_CORE0_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CORE1_32)
#undef      START_SEC_VAR_INIT_CORE1_32
#pragma default_variable_attributes = @ ".bsw.init.core1.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CORE1_32)
#undef      STOP_SEC_VAR_INIT_CORE1_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CORE1_UNSPECIFIED)
#undef      START_SEC_VAR_INIT_CORE1_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.init.core1.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CORE1_UNSPECIFIED)
#undef      STOP_SEC_VAR_INIT_CORE1_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CORE2_32)
#undef      START_SEC_VAR_INIT_CORE2_32
#pragma default_variable_attributes = @ ".bsw.init.core2.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CORE2_32)
#undef      STOP_SEC_VAR_INIT_CORE2_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_CORE2_UNSPECIFIED)
#undef      START_SEC_VAR_INIT_CORE2_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.init.core2.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_CORE2_UNSPECIFIED)
#undef      STOP_SEC_VAR_INIT_CORE2_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_GLOBAL_32)
#undef      START_SEC_VAR_INIT_GLOBAL_32
#pragma default_variable_attributes = @ ".bsw.init.global.32bit"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_GLOBAL_32)
#undef      STOP_SEC_VAR_INIT_GLOBAL_32
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_INIT_GLOBAL_UNSPECIFIED)
#undef      START_SEC_VAR_INIT_GLOBAL_UNSPECIFIED
#pragma default_variable_attributes = @ ".bsw.init.global.unspec"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_INIT_GLOBAL_UNSPECIFIED)
#undef      STOP_SEC_VAR_INIT_GLOBAL_UNSPECIFIED
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_STACK_CORE0)
#undef      START_SEC_VAR_STACK_CORE0
#pragma default_variable_attributes = @ ".Os.stack.core0"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_STACK_CORE0)
#undef      STOP_SEC_VAR_STACK_CORE0
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_STACK_CORE1)
#undef      START_SEC_VAR_STACK_CORE1
#pragma default_variable_attributes = @ ".Os.stack.core1"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_STACK_CORE1)
#undef      STOP_SEC_VAR_STACK_CORE1
#pragma default_variable_attributes =
#endif

/* start pragma */
#if defined (START_SEC_VAR_STACK_CORE2)
#undef      START_SEC_VAR_STACK_CORE2
#pragma default_variable_attributes = @ ".Os.stack.core2"
#endif

/* stop pragma */
#if defined (STOP_SEC_VAR_STACK_CORE2)
#undef      STOP_SEC_VAR_STACK_CORE2
#pragma default_variable_attributes =
#endif
/*=======[E N D   O F   F I L E]==============================================*/
