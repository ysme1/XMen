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
 **  FILENAME    : Rte_SecOC.c                                                 **
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
/* <VERSION>   <DATE>     <AUTHOR>   <REVISION LOG>
 * V1.0.0      20200818   HuRongbo   Initial version
 * V2.0.0      20210617   HuRongbo   Fix bug find in Test
 */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "SecOC.h"
#include "Rte_SecOC_Type.h"

#if (SECOC_RTE == SECOC_QUERY_FRESHNESS_VALUE)
/*******************************************************************************
**                       Version  Check                                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define SECOC_START_SEC_CALLOUT_CODE
#include "SecOC_MemMap.h"

/* This interface is used by the SecOC to obtain the current freshness value.
 * This operation provides also a part of the Authentic-PDU data if configured*/
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetRxFreshness(
    uint16 freshnessValueId,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) truncatedFreshnessValue,
    uint32 truncatedFreshnessValueLength,
    uint16 authVerifyAttempts,
    /* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength
    /* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
)
{
    return E_OK;
}

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
    /* PRQA S 3432 ++ */ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength
    /* PRQA S 3432 -- */ /* MISRA Rule 20.7 */
)
{
    return E_OK;
}

/* Returns the freshness value from the Most Significant Bits in the first byte
 * in the array (SecOCFreshnessValue), in big endian format. */
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetTxFreshness(
    uint16 freshnessValueId,
    /* PRQA S 3432 ++*/ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength
    /* PRQA S 3432 --*/ /* MISRA Rule 20.7 */
)
{
    return E_OK;
}

/* This operation is used by the SecOC to obtain the freshness that corresponds
 * to the freshnessValueId. The operation provides the freshness and also the
 * truncated freshness that shall be placed into the Secured-IPDU. */
FUNC(Std_ReturnType, SECOC_CODE)
FreshnessManagement_GetTxFreshnessTruncData(
    uint16 freshnessValueId,
    /* PRQA S 3432 ++*/ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_CONST) freshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) freshnessValueLength,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_CONST) truncatedFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) truncatedFreshnessValueLength
    /* PRQA S 3432 --*/ /* MISRA Rule 20.7 */
)
{
    return E_OK;
}

/* This operation is used by the SecOC to indicate that the Secured I-PDU has
 * been initiated for transmission. */
FUNC(Std_ReturnType, SECOC_CODE) FreshnessManagement_SPduTxConfirmation(uint16 freshnessValueId)
{
    return E_OK;
}

#define SECOC_STOP_SEC_CALLOUT_CODE
#include "SecOC_MemMap.h"

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

#endif /* SECOC_RTE == SECOC_QUERY_FRESHNESS_VALUE */
