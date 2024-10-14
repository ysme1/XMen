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
 **  FILENAME    :  Os_Extened.h                                               **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      :  i-soft-os                                                  **
 **  Vendor      :                                                             **
 **  DESCRIPTION :  Extended functions                                         **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef OS_EXTEND_H
#define OS_EXTEND_H

/*=======[I N C L U D E S]====================================================*/
#include "Os_Types.h"
#include "Os_Internal.h"
#include "Arch_Extend.h"

/*=======[M A C R O S]========================================================*/
/* Types of stack usage. */
typedef uint32 osStackUsageType;

/* Enumeration type of stack object. */
typedef enum
{
    OS_STACK_SYSTEM = 0U,
    OS_STACK_TASK = 1U,
    OS_STACK_ISR2 = 2U
} osStackObject;

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[F U N C T I O N   D E C L A R A T I O N S]========*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"
/********************************************************************/
/*
 * Brief                <Provide Version information to user.>
 * Service ID           <0xfd>
 * Sync/Async           <none>
 * Reentrancy           <Yes>
 * param-eventId[in]    <Versioninfo>
 * Param-Name[out]      <no>
 * Param-Name[in/out]   <None>
 * return               <None>
 * PreCondition         <None>
 * REQ ID               <None>
 */
/********************************************************************/
FUNC(void, OS_CODE) OSGetVersionInfo(Std_VersionInfoType* osVerInfoPtr);

#if (CHECK_STACK_USAGE > 0)
/********************************************************************/
/*
 * Brief                <Get max usage of system,task,ISR2 stack.>
 * Service ID           <0xfe>
 * Sync/Async           <none>
 * Reentrancy           <Yes>
 * param-eventId[in]    <id>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <osStackUsageType>
 * PreCondition         <None>
 * REQ ID               <None>
 */
/********************************************************************/
FUNC(osStackUsageType, OS_CODE) OSGetStackUsage(osStackObject stack, uint16 id);
#endif

/********************************************************************/
/*
 * Brief                <check ISR source>
 * Service ID           <0xd8>
 * Sync/Async           <none>
 * Reentrancy           <Yes>
 * param-eventId[in]    <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * REQ ID               <None>
 */
/********************************************************************/
extern FUNC(StatusType, OS_CODE) OSCheckISRSource(uint32 Source);

/********************************************************************/
/*
 * Brief                <check whether CPU information is correct.>
 * Service ID           <0xff>
 * Sync/Async           <none>
 * Reentrancy           <Yes>
 * param-eventId[in]    <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * return               <StatusType>
 * PreCondition         <None>
 * REQ ID               <None>
 */
/********************************************************************/
FUNC(void, OS_CODE) OSCheckCPUInformation(void);

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"
#endif /* OS_EXTEND_H */

/*=======[E N D   O F   F I L E]==============================================*/
