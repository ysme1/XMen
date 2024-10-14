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
 **  FILENAME    : SecOC_Callout.c                                             **
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
 * V2.0.0      20210617   HuRongbo   Bug fix
 * V2.0.1      20210711   HuRongbo   QAC check issue fix
 */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "SecOC.h"

#if (SECOC_CFUNC == SECOC_QUERY_FRESHNESS_VALUE)
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
/******************************************************************************/
/*
 * Brief               This interface is used by the SecOC to obtain the current
 *                     freshness value.
 * ServiceId           0x4f
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      SecOCFreshnessValueID: Holds the identifier of the
 *                                            freshness value.
 *                     SecOCTruncatedFreshnessValue: Holds the truncated
 *                                  freshness value that was contained in the
 *                                  Secured I-PDU.
 *                     SecOCTruncatedFreshnessValueLength: Holds the length in
 *                                  bits of the truncated freshness value.
 *                     SecOCAuthVerifyAttempts:Hold the number of authentication
 *                                  verify attempts of this PDU since the last
 *                                  reception.
 * Param-Name[out]     SecOCFreshnessValue: Holds the freshness value to be used
 *                                  for the calculation of the authenticator.
 * Param-Name[in/out]  SecOCFreshnessValueLength: Holds the length in bits of
 *                                                the freshness value.
 * Return              E_OK: request successful.
 *                     E_NOT_OK: request failed, a freshness value cannot be
 *                               provided due to general issues for freshness orx
 *                               this FreshnessValueId.
 *                     E_BUSY: The freshness information can temporarily not be
 *                             provided.
 */
/******************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE)
SecOC_GetRxFreshness(
    uint16 SecOCFreshnessValueID,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) SecOCTruncatedFreshnessValue,
    uint32 SecOCTruncatedFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,
    /* PRQA S 3432, 3673 ++ */ /* MISRA Rule 20.7, 8.13 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
    /* PRQA S 3432, 3673 -- */ /* MISRA Rule 20.7, 8.13 */
)
{
    (void)(SecOCFreshnessValueID);
    (void)(SecOCTruncatedFreshnessValue);
    (void)(SecOCTruncatedFreshnessValueLength);
    (void)(SecOCAuthVerifyAttempts);
    (void)(SecOCFreshnessValue);
    (void)(SecOCFreshnessValueLength);
    return E_OK;
}

/******************************************************************************/
/*
 * Brief               This interface is used by the SecOC to obtain the current
 *                     freshness value.
 * ServiceId           0x4e
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      SecOCFreshnessValueID: Holds the identifier of the
 *                                            freshness value.
 *                     SecOCTruncatedFreshnessValue: Holds the truncated
 *                                  freshness value that was contained in the
 *                                  Secured I-PDU.
 *                     SecOCTruncatedFreshnessValueLength: Holds the length in
 *                                  bits of the truncated freshness value.
 *                     SecOCAuthDataFreshnessValue: The parameter holds a part
 *                                  of the received, not yet authenticated PDU.
 *                     SecOCAuthDataFreshnessValueLength: This is the length
 *                                  value in bits that holds the freshness from
 *                                  the authentic PDU.
 *                     SecOCAuthVerifyAttempts: Holds the number of
 *                                  authentication verify attempts of this PDU
 *                                  since the last reception.
 * Param-Name[out]     SecOCFreshnessValue: Holds the freshness value to be used
 *                                  for the calculation of the authenticator.
 * Param-Name[in/out]  SecOCFreshnessValueLength: Holds the length in bits of
 *                                                the freshness value.
 * Return              E_OK: request successful.
 *                     E_NOT_OK: request failed, a freshness value cannot be
 *                               provided due to general issues for freshness orx
 *                               this FreshnessValueId.
 *                     E_BUSY: The freshness information can temporarily not be
 *                             provided.
 */
/******************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE)
SecOC_GetRxFreshnessAuthData(
    uint16 SecOCFreshnessValueID,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) SecOCTruncatedFreshnessValue,
    uint32 SecOCTruncatedFreshnessValueLength,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_CONST) SecOCAuthDataFreshnessValue,
    uint16 SecOCAuthDataFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,
    /* PRQA S 3432, 3673 ++ */ /* MISRA Rule 20.7, 8.13 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
    /* PRQA S 3432, 3673 -- */ /* MISRA Rule 20.7, 8.13 */
)
{
    (void)(SecOCFreshnessValueID);
    (void)(SecOCTruncatedFreshnessValue);
    (void)(SecOCTruncatedFreshnessValueLength);
    (void)(SecOCAuthDataFreshnessValue);
    (void)(SecOCAuthDataFreshnessValueLength);
    (void)(SecOCAuthVerifyAttempts);
    (void)(SecOCFreshnessValue);
    (void)(SecOCFreshnessValueLength);
    return E_OK;
}

/******************************************************************************/
/*
 * Brief               This API returns the freshness value from the Most
 *                     Significant Bits in the first byte in the array
 *                     (SecOCFreshnessValue), in big endian format.
 * ServiceId           0x52
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      SecOCFreshnessValueID: Holds the identifier of the
 *                                            freshness value.
 * Param-Name[out]     SecOCFreshnessValue: Holds the freshness value to be used
 *                                     for the calculation of the authenticator.
 * Param-Name[in/out]  SecOCFreshnessValueLength: Holds the length in bits of
 *                                                the freshness value.
 * Return              E_OK: request successful.
 *                     E_NOT_OK: request failed, a freshness value cannot be
 *                               provided due to general issues for freshness orx
 *                               this FreshnessValueId.
 *                     E_BUSY: The freshness information can temporarily not be
 *                             provided.
 */
/******************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE)
SecOC_GetTxFreshness(
    uint16 SecOCFreshnessValueID,
    /* PRQA S 3432, 3673 ++ */ /* MISRA Rule 20.7, 8.13 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength
    /* PRQA S 3432, 3673 -- */ /* MISRA Rule 20.7, 8.13 */
)
{
    (void)(SecOCFreshnessValueID);
    (void)(SecOCFreshnessValue);
    (void)(SecOCFreshnessValueLength);
    return E_OK;
}

/******************************************************************************/
/*
 * Brief               This interface is used by the SecOC to obtain the current
 *                     freshness value. The interface function provides also the
 *                     truncated freshness transmitted in the secured I-PDU.
 * ServiceId           0x51
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      SecOCFreshnessValueID: Holds the identifier of the
 *                                            freshness value.
 * Param-Name[out]     SecOCFreshnessValue: Holds the current freshness value.
 *                     SecOCTruncatedFreshnessValue: Holds the truncated
 *                              freshness to be included into the Secured I-PDU.
 * Param-Name[in/out]  SecOCFreshnessValueLength: Holds the length in bits of
 *                                                the freshness value.
 *                     SecOCTruncatedFreshnessValueLength: Provides the
 *                              truncated freshness length configured for this
 *                              freshness.
 * Return              E_OK: request successful.
 *                     E_NOT_OK: request failed, a freshness value cannot be
 *                               provided due to general issues for freshness orx
 *                               this FreshnessValueId.
 *                     E_BUSY: The freshness information can temporarily not be
 *                             provided.
 */
/******************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE)
SecOC_GetTxFreshnessTruncData(
    uint16 SecOCFreshnessValueID,
    /* PRQA S 3432, 3673 ++ */ /* MISRA Rule 20.7, 8.13 */
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_CONST) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCFreshnessValueLength,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_CONST) SecOCTruncatedFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) SecOCTruncatedFreshnessValueLength
    /* PRQA S 3432, 3673 -- */ /* MISRA Rule 20.7, 8.13 */
)
{
    (void)(SecOCFreshnessValueID);
    (void)(SecOCFreshnessValue);
    (void)(SecOCFreshnessValueLength);
    (void)(SecOCTruncatedFreshnessValue);
    (void)(SecOCTruncatedFreshnessValueLength);
    return E_OK;
}

/******************************************************************************/
/*
 * Brief               This interface is used by the SecOC to indicate that the
 *                     Secured I-PDU has been initiated for transmission.
 * ServiceId           0x4d
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      SecOCFreshnessValueID: Holds the identifier of the
 *                                            freshness value.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 */
/******************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_SPduTxConfirmation(uint16 SecOCFreshnessValueID)
{
    (void)(SecOCFreshnessValueID);
    return E_OK;
}

#define SECOC_STOP_SEC_CALLOUT_CODE
#include "SecOC_MemMap.h"

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

#endif /* SECOC_CFUNC == SECOC_QUERY_FRESHNESS_VALUE */
