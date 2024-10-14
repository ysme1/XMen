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
 **  FILENAME    : Rte_SecOC_Type.h                                            **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : HuRongbo                                                    **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Type definitions of SecOC                                   **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*  <VERSION>    <DATE>      <AUTHOR>    <REVISION LOG>
 *  V1.0.0       2020-08-18  HuRongbo    R19_11 SecOC initial version.
 *  V2.0.0       2021-06-17  HuRongbo    Fix bug find in Test.
 */

#ifndef RTE_SECOC_TYPES_H
#define RTE_SECOC_TYPES_H

#include "SecOC_Cfg.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @req SWS_SecOC_91012 */
typedef uint8 SecOC_FreshnessArrayType[SECOC_MAX_FRESHNESS_SIZE];

/* @req SWS_SecOC_00149 */
/* Enumeration to indicate verification results. */
typedef enum
{
    SECOC_VERIFICATIONSUCCESS,
    SECOC_VERIFICATIONFAILURE,
    SECOC_FRESHNESSFAILURE,
    SECOC_AUTHENTICATIONBUILDFAILURE,
    SECOC_NO_VERIFICATION,
    SECOC_VERIFICATIONFAILURE_OVERWRITTEN
} SecOC_VerificationResultType;

/* @req SWS_SecOC_00160 */
/*
 * Data structure to bundle the status of a verification attempt for a specific
 * Freshness Value and Data ID.
 */
typedef struct
{
    uint16 freshnessValueID;
    SecOC_VerificationResultType verificationStatus;
    uint16 secOCDataId;
} SecOC_VerificationStatusType;

/* @req SWS_SecOC_00991 */
/* Defines possibilities to override the verification status. */
typedef enum
{
    SECOC_OVERRIDE_DROP_UNTIL_NOTICE = 0x00,
    SECOC_OVERRIDE_DROP_UNTIL_LIMIT = 0x01,
    SECOC_OVERRIDE_CANCEL = 0x02,
    SECOC_OVERRIDE_PASS_UNTIL_NOTICE = 0x40,
    SECOC_OVERRIDE_SKIP_UNTIL_LIMIT = 0x41,
    SECOC_OVERRIDE_PASS_UNTIL_LIMIT = 0x42,
    SECOC_OVERRIDE_SKIP_UNTIL_NOTICE = 0x43
} SecOC_OverrideStatusType;

#endif /* SECOC_TYPES_H */
