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
 **  FILENAME    : Rte_KeyM_Type.h                                             **
 **                                                                            **
 **  Created on  : **
 **  Author      : yuzhe.zhang                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Type declaration of KeyM                                    **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef RTE_KEYM_TYPE_H_
#define RTE_KEYM_TYPE_H_
#include "Std_Types.h"
#include "Compiler.h"
#include "Platform_Types.h"

#define KEYM_CRYPTO_INVALID_KEYID 0xFFFFFFFFu
#define KEYM_CERT_INVALID_CERTID  0xFFFFu

typedef uint16 KeyM_CertElementIdType; /* Certificate Element handle. */

typedef uint8 KeyM_KeyCertNameDataType;    /* SWS_KeyM_91000 */
typedef uint8 KeyM_KeyCertificateDataType; /* SWS_KeyM_91001 */
typedef uint8 KeyM_CertificateElementType;
typedef uint16 KeyM_CryptoKeyDataType;
typedef uint64 KeyM_CertificateDataType;

typedef enum
{
    /* Key operation starts in OEM production mode*/
    KEYM_START_OEM_PRODUCTIONMODE = 1u,
    /* Key operation starts in workshop mode */
    KEYM_START_WORKSHOPMODE = 2u,
    /* The range from 0x80-0x9F is reserved for user specific */
    KEYM_START_USER_BEGIN = 0x80u,
    KEYM_START_USER_END = 0x9Fu
} KeyM_StartType;

/* This type specifies the requested service operation and what information is provided
with this function */
typedef enum
{
    /* Key server requests to generate a certificate from the key client. */
    KEYM_SERVICE_CERT_REQUEST_CSR = 0x01u,
    /* Key server returns a previously received certificate and has been
     * now signed by the CA.*/
    KEYM_SERVICE_CERT_UPDATE_SIGNED_CSR = 0x02u,
    /* Key server wants to add a new root certificate. */
    KEYM_SERVICE_CERT_SET_ROOT = 0x03u,
    /* Key server wants to update an existing root certificate. */
    KEYM_SERVICE_CERT_UPDATE_ROOT = 0x04u,
    /* Key server wants to add a new CA certificate.
     * pre-requisite: Root certificate shall have been stored before for
     * a successful verification.*/
    KEYM_SERVICE_CERT_SET_INTERMEDIATE = 0x05u,
    /* Key server wants to update an existing CA certificate. */
    KEYM_SERVICE_CERT_UPDATE_INTERMEDIATE = 0x06u,
    /* Provide or update a certificate revocation list. */
    KEYM_SERVICE_CERT_UPDATE_CRL = 0x07u,
    /* The range from 0x80- 0x9F is reserved for user specific extensions */
    KEYM_SERVICE_CERT_USER_BEGIN = 0x80u,
    KEYM_SERVICE_CERT_USER_END = 0x9Fu
} KeyM_ServiceCertificateType;

/* SWS_KeyM_91002 */
/* This structure is used to exchange certificate data through interface functions. */
typedef struct
{
    uint32 certDataLength; /* Length of the certificate data. */
    /* Pointer references the data for a certificate on a local data area of the caller.*/
    P2CONST(KeyM_CertificateDataType, KEYM_CONST, KEYM_CONST_PBCFG) certData;
} KeyM_CertificateType;

/* SWS_KeyM_91003: the result type of verification operations */
typedef enum
{
    /* Certificate successfully parsed and verified. */
    KEYM_CERTIFICATE_VALID = 0x00u,
    /* The certificate is invalid (unspedified failure) */
    KEYM_CERTIFICATE_INVALID = 0x01u,
    /* Certificate has not been parsed so far. */
    KEYM_CERTIFICATE_NOT_PARSED = 0x02u,
    /* Certificate parsed but not yet validated */
    KEYM_CERTIFICATE_PARSED_NOT_VALIDATED = 0x03u,
    /* Certificate not set */
    KEYM_CERTIFICATE_NOT_AVAILABLE = 0x04u,
    /* Certificate verification failed - Invalid Time Period */
    KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL = 0x05u,
    /* Certificate verification failed - Invalid Signature */
    KEYM_E_CERTIFICATE_SIGNATURE_FAIL = 0x06u,
    /* Certificate verification failed - Invalid Chain of Trust */
    KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST = 0x07u,
    /* Certificate verification failed - Invalid Type */
    KEYM_E_CERTIFICATE_INVALID_TYPE = 0x08u,
    /* Certificate verification failed - Invalid Format */
    KEYM_E_CERTIFICATE_INVALID_FORMAT = 0x09u,
    /* Certificate verification failed - Invalid Content */
    KEYM_E_CERTIFICATE_INVALID_CONTENT = 0x0Au,
    /* Certificate verification failed - Invalid Scope */
    KEYM_E_CERTIFICATE_REVOKED = 0x0Bu
} KeyM_CertificateStatusType;

/* SWS_KeyM_91008��Specifies the result type of an asynchronous key management function.*/
typedef enum
{
    /* Key management operation successful. */
    KEYM_RT_OK = 0x00u,
    /* General error occured during key management operation.*/
    KEYM_RT_NOT_OK = 0x01u,
    /* Key or certificate is invalid and cannot be used for the operation. */
    KEYM_RT_KEY_CERT_INVALID = 0x02u,
    /* Key or certificate could not be written to designated storage. */
    KEYM_RT_KEY_CERT_WRITE_FAIL = 0x03u,
    /* General failure while updating a key or certificate(error code could not be precised by one of the
    other error codes) */
    KEYM_RT_KEY_CERT_UPDATE_FAIL = 0x04u,
    /* Certificate verification failed - Invalid Chain of Trust */
    KEYM_RT_CERT_INVALID_CHAIN_OF_TRUST = 0x05u,
} KeyM_ResultType;

typedef uint16 KeyM_CertificateIdType;
#endif /* RTE_KEYM_TYPE_H_ */
