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
 *  @file               : aes.h
 *  @version            : V1.0.0
 *  @author             : qinchun.yang
 *  @date               : 2018/10/13
 *  @vendor             : isoft
 *  @description        : Implementation for Crypto
 *  @specification(s)   : AUTOSAR classic Platform R19-11
 *
 */
/* PRQA S 3108-- */
#ifndef AES_H
#define AES_H
#if (CRYPTO_ALGORITHM_AES == STD_ON)
#include "Crypto_Types.h"

typedef struct
{
    int nr;         /*!< The number of rounds. */
    uint32* rk;     /*!< AES round keys. */
    uint32 buf[68]; /*!< Unaligned data buffer. This buffer can
                           hold 32 extra Bytes */
} Crypto_AESData;

#define AES_ENCRYPT 1 /**< AES encryption. */
#define AES_DECRYPT 0 /**< AES decryption. */

FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_setkey_enc(Crypto_AESData* ctx, P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint16 keybits);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_setkey_dec(Crypto_AESData* ctx, P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint16 keybits);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_crypt_ecb(Crypto_AESData* ctx, uint8 mode, const uint8 input[16], uint8 output[16]);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_crypt_cbc(
    Crypto_AESData* ctx,
    uint8 mode,
    uint8 length,
    uint8 iv[16],
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) input,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) output);
FUNC(Std_ReturnType, CRY_CODE) Crypto_AESEncryptECB(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64]);
FUNC(Std_ReturnType, CRY_CODE) Crypto_AESDecryptECB(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64]);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESEncryptCBC(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16], uint8 inputlength);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESDecryptCBC(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[16], uint8 iv[16], uint8 inputlength);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESEncryptCTR(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16]);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESDecryptCTR(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16]);
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_crypt_cbc_CMAC(
    Crypto_AESData* ctx,
    uint8 mode,
    uint8 length,
    uint8 iv[16],
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) input,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) output);
#endif /* CRYPTO_ALGORITHM_AES == STD_ON */
#endif /* aes.h */
