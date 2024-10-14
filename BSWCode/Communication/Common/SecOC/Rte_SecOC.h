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
 **  FILENAME    : Rte_Callout.h                                               **
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

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*  <VERSION>    <DATE>       <AUTHOR>   <REVISION LOG>
 *  V1.0.0       2020-08-19   HuRongbo   R19_11 SecOC initial version.
 *  V1.0.0       2021-06-17   HuRongbo   Fix bug find in Test
 */

#ifndef RTE_SECOC_H
#define RTE_SECOC_H

#include "SecOC.h"
#if (SECOC_RTE == SECOC_QUERY_FRESHNESS_VALUE)
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Declaration                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Functions                                      **
*******************************************************************************/

/* This interface is used by the SecOC to obtain the current freshness value.
 * This operation provides also a part of the Authentic-PDU data if configured*/
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetRxFreshness(
    uint16 freshnessValueId,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) truncatedFreshnessValue,
    uint32 truncatedFreshnessValueLength,
    uint16 authVerifyAttempts,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength);

/* This interface is used by the SecOC to obtain the current freshness value.
 * This operation provides also a part of the Authentic-PDU data if configured*/
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetRxFreshnessAuthData(
    uint16 freshnessValueId,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) truncatedFreshnessValue,
    uint32 truncatedFreshnessValueLength,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) authenticDataFreshnessValue,
    uint16 authenticDataFreshnessValueLength,
    uint16 authVerifyAttempts,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength);

/* Returns the freshness value from the Most Significant Bits in the first byte
 * in the array (SecOCFreshnessValue), in big endian format. */
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetTxFreshness(
    uint16 freshnessValueId,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength);

/* This operation is used by the SecOC to obtain the freshness that corresponds
 * to the freshnessValueId. The operation provides the freshness and also the
 * truncated freshness that shall be placed into the Secured-IPDU. */
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetTxFreshnessTruncData(
    uint16 freshnessValueId,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_CONST) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_CONST) truncatedFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) truncatedFreshnessValueLength);

/* This operation is used by the SecOC to indicate that the Secured I-PDU has
 * been initiated for transmission. */
FUNC(Std_ReturnType, SECOC_CODE) FreshnessManagement_SPduTxConfirmation(uint16 freshnessValueId);

#endif /* #if (SECOC_RTE == SECOC_QUERY_FRESHNESS_VALUE) */

#endif /* RTE_SECOC_H */
