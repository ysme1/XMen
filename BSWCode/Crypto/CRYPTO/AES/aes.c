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
 *  @file               : aes.c
 *  @version            : V1.0.0
 *  @author             : qinchun.yang
 *  @date               : 2018/10/13
 *  @vendor             : isoft
 *  @description        : Implementation for Crypto
 *  @specification(s)   : AUTOSAR classic Platform R19-11
 *
 */
/* PRQA S 3108-- */
/* PRQA S 0342 ++ */                    /* MISRA Rule 20.10 */
/* PRQA S 3432 ++ */                    /* MISRA Rule 20.7 */
/* PRQA S 0488 ++ */                    /* MISRA Rule 18.4 */
/* PRQA S 2016,2002 ++ */               /* MISRA Rule 16.4 */
/* PRQA S 2212 ++ */                    /* MISRA Rule 15.6 */
/* PRQA S 2463,2462 ++ */               /* MISRA Rule 14.2 */
/* PRQA S 3226 ++ */                    /* MISRA Rule 13.4 */
/* PRQA S 3440 ++ */                    /* MISRA Rule 13.3 */
/* PRQA S 3418 ++ */                    /* MISRA Rule 12.3 */
/* PRQA S 1864,1863,1862,1860,1841 ++*/ /* MISRA Rule 10.4 */
/* PRQA S 3218 ++ */                    /* MISRA Rule 8.9 */
/* PRQA S 4542 ++ */                    /* MISRA Rule 10.1 */
/* PRQA S 1532,1505 ++ */               /* MISRA Rule 8.7 */
/* PRQA S 5209 ++ */                    /* MISRA Dir 4.6 */
/* PRQA S 2985,2982 ++ */               /* MISRA Rule 2.2 */
#include "aes.h"
#include "Crypto_Types.h"
#include "Crypto_internal.h"
#define CRYPTO_START_SEC_CODE
#include "Crypto_MemMap.h"
#if (CRYPTO_ALGORITHM_AES == STD_ON)
FUNC(Std_ReturnType, CRY_CODE) internal_aes_encrypt(Crypto_AESData* ctx, const uint8 input[16], uint8 output[16]);
FUNC(Std_ReturnType, CRY_CODE) internal_aes_decrypt(Crypto_AESData* ctx, const uint8 input[16], uint8 output[16]);

#define GET_UINT32_LE(n, b, i)                                                                \
    {                                                                                         \
        (n) = ((uint32)(b)[(i)]) | ((uint32)(b)[(i) + 1] << 8) | ((uint32)(b)[(i) + 2] << 16) \
              | ((uint32)(b)[(i) + 3] << 24);                                                 \
    }

#define PUT_UINT32_LE(n, b, i)                      \
    {                                               \
        (b)[(i)] = (uint8)(((n)) & 0xFF);           \
        (b)[(i) + 1] = (uint8)(((n) >> 8) & 0xFF);  \
        (b)[(i) + 2] = (uint8)(((n) >> 16) & 0xFF); \
        (b)[(i) + 3] = (uint8)(((n) >> 24) & 0xFF); \
    }

/*
 * Forward S-box
 */
static const uint8 FSb[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9,
    0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F,
    0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15, 0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07,
    0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3,
    0x29, 0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58,
    0xCF, 0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8, 0x51, 0xA3,
    0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC, 0x5F,
    0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, 0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC,
    0x62, 0x91, 0x95, 0xE4, 0x79, 0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A,
    0xAE, 0x08, 0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, 0x70,
    0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11,
    0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, 0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42,
    0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};

/*
 * Forward tables
 */
#define FT                                                                                                             \
                                                                                                                       \
    ISoft(A5, 63, 63, C6), ISoft(84, 7C, 7C, F8), ISoft(99, 77, 77, EE), ISoft(8D, 7B, 7B, F6), ISoft(0D, F2, F2, FF), \
        ISoft(BD, 6B, 6B, D6), ISoft(B1, 6F, 6F, DE), ISoft(54, C5, C5, 91), ISoft(50, 30, 30, 60),                    \
        ISoft(03, 01, 01, 02), ISoft(A9, 67, 67, CE), ISoft(7D, 2B, 2B, 56), ISoft(19, FE, FE, E7),                    \
        ISoft(62, D7, D7, B5), ISoft(E6, AB, AB, 4D), ISoft(9A, 76, 76, EC), ISoft(45, CA, CA, 8F),                    \
        ISoft(9D, 82, 82, 1F), ISoft(40, C9, C9, 89), ISoft(87, 7D, 7D, FA), ISoft(15, FA, FA, EF),                    \
        ISoft(EB, 59, 59, B2), ISoft(C9, 47, 47, 8E), ISoft(0B, F0, F0, FB), ISoft(EC, AD, AD, 41),                    \
        ISoft(67, D4, D4, B3), ISoft(FD, A2, A2, 5F), ISoft(EA, AF, AF, 45), ISoft(BF, 9C, 9C, 23),                    \
        ISoft(F7, A4, A4, 53), ISoft(96, 72, 72, E4), ISoft(5B, C0, C0, 9B), ISoft(C2, B7, B7, 75),                    \
        ISoft(1C, FD, FD, E1), ISoft(AE, 93, 93, 3D), ISoft(6A, 26, 26, 4C), ISoft(5A, 36, 36, 6C),                    \
        ISoft(41, 3F, 3F, 7E), ISoft(02, F7, F7, F5), ISoft(4F, CC, CC, 83), ISoft(5C, 34, 34, 68),                    \
        ISoft(F4, A5, A5, 51), ISoft(34, E5, E5, D1), ISoft(08, F1, F1, F9), ISoft(93, 71, 71, E2),                    \
        ISoft(73, D8, D8, AB), ISoft(53, 31, 31, 62), ISoft(3F, 15, 15, 2A), ISoft(0C, 04, 04, 08),                    \
        ISoft(52, C7, C7, 95), ISoft(65, 23, 23, 46), ISoft(5E, C3, C3, 9D), ISoft(28, 18, 18, 30),                    \
        ISoft(A1, 96, 96, 37), ISoft(0F, 05, 05, 0A), ISoft(B5, 9A, 9A, 2F), ISoft(09, 07, 07, 0E),                    \
        ISoft(36, 12, 12, 24), ISoft(9B, 80, 80, 1B), ISoft(3D, E2, E2, DF), ISoft(26, EB, EB, CD),                    \
        ISoft(69, 27, 27, 4E), ISoft(CD, B2, B2, 7F), ISoft(9F, 75, 75, EA), ISoft(1B, 09, 09, 12),                    \
        ISoft(9E, 83, 83, 1D), ISoft(74, 2C, 2C, 58), ISoft(2E, 1A, 1A, 34), ISoft(2D, 1B, 1B, 36),                    \
        ISoft(B2, 6E, 6E, DC), ISoft(EE, 5A, 5A, B4), ISoft(FB, A0, A0, 5B), ISoft(F6, 52, 52, A4),                    \
        ISoft(4D, 3B, 3B, 76), ISoft(61, D6, D6, B7), ISoft(CE, B3, B3, 7D), ISoft(7B, 29, 29, 52),                    \
        ISoft(3E, E3, E3, DD), ISoft(71, 2F, 2F, 5E), ISoft(97, 84, 84, 13), ISoft(F5, 53, 53, A6),                    \
        ISoft(68, D1, D1, B9), ISoft(00, 00, 00, 00), ISoft(2C, ED, ED, C1), ISoft(60, 20, 20, 40),                    \
        ISoft(1F, FC, FC, E3), ISoft(C8, B1, B1, 79), ISoft(ED, 5B, 5B, B6), ISoft(BE, 6A, 6A, D4),                    \
        ISoft(46, CB, CB, 8D), ISoft(D9, BE, BE, 67), ISoft(4B, 39, 39, 72), ISoft(DE, 4A, 4A, 94),                    \
        ISoft(D4, 4C, 4C, 98), ISoft(E8, 58, 58, B0), ISoft(4A, CF, CF, 85), ISoft(6B, D0, D0, BB),                    \
        ISoft(2A, EF, EF, C5), ISoft(E5, AA, AA, 4F), ISoft(16, FB, FB, ED), ISoft(C5, 43, 43, 86),                    \
        ISoft(D7, 4D, 4D, 9A), ISoft(55, 33, 33, 66), ISoft(94, 85, 85, 11), ISoft(CF, 45, 45, 8A),                    \
        ISoft(10, F9, F9, E9), ISoft(06, 02, 02, 04), ISoft(81, 7F, 7F, FE), ISoft(F0, 50, 50, A0),                    \
        ISoft(44, 3C, 3C, 78), ISoft(BA, 9F, 9F, 25), ISoft(E3, A8, A8, 4B), ISoft(F3, 51, 51, A2),                    \
        ISoft(FE, A3, A3, 5D), ISoft(C0, 40, 40, 80), ISoft(8A, 8F, 8F, 05), ISoft(AD, 92, 92, 3F),                    \
        ISoft(BC, 9D, 9D, 21), ISoft(48, 38, 38, 70), ISoft(04, F5, F5, F1), ISoft(DF, BC, BC, 63),                    \
        ISoft(C1, B6, B6, 77), ISoft(75, DA, DA, AF), ISoft(63, 21, 21, 42), ISoft(30, 10, 10, 20),                    \
        ISoft(1A, FF, FF, E5), ISoft(0E, F3, F3, FD), ISoft(6D, D2, D2, BF), ISoft(4C, CD, CD, 81),                    \
        ISoft(14, 0C, 0C, 18), ISoft(35, 13, 13, 26), ISoft(2F, EC, EC, C3), ISoft(E1, 5F, 5F, BE),                    \
        ISoft(A2, 97, 97, 35), ISoft(CC, 44, 44, 88), ISoft(39, 17, 17, 2E), ISoft(57, C4, C4, 93),                    \
        ISoft(F2, A7, A7, 55), ISoft(82, 7E, 7E, FC), ISoft(47, 3D, 3D, 7A), ISoft(AC, 64, 64, C8),                    \
        ISoft(E7, 5D, 5D, BA), ISoft(2B, 19, 19, 32), ISoft(95, 73, 73, E6), ISoft(A0, 60, 60, C0),                    \
        ISoft(98, 81, 81, 19), ISoft(D1, 4F, 4F, 9E), ISoft(7F, DC, DC, A3), ISoft(66, 22, 22, 44),                    \
        ISoft(7E, 2A, 2A, 54), ISoft(AB, 90, 90, 3B), ISoft(83, 88, 88, 0B), ISoft(CA, 46, 46, 8C),                    \
        ISoft(29, EE, EE, C7), ISoft(D3, B8, B8, 6B), ISoft(3C, 14, 14, 28), ISoft(79, DE, DE, A7),                    \
        ISoft(E2, 5E, 5E, BC), ISoft(1D, 0B, 0B, 16), ISoft(76, DB, DB, AD), ISoft(3B, E0, E0, DB),                    \
        ISoft(56, 32, 32, 64), ISoft(4E, 3A, 3A, 74), ISoft(1E, 0A, 0A, 14), ISoft(DB, 49, 49, 92),                    \
        ISoft(0A, 06, 06, 0C), ISoft(6C, 24, 24, 48), ISoft(E4, 5C, 5C, B8), ISoft(5D, C2, C2, 9F),                    \
        ISoft(6E, D3, D3, BD), ISoft(EF, AC, AC, 43), ISoft(A6, 62, 62, C4), ISoft(A8, 91, 91, 39),                    \
        ISoft(A4, 95, 95, 31), ISoft(37, E4, E4, D3), ISoft(8B, 79, 79, F2), ISoft(32, E7, E7, D5),                    \
        ISoft(43, C8, C8, 8B), ISoft(59, 37, 37, 6E), ISoft(B7, 6D, 6D, DA), ISoft(8C, 8D, 8D, 01),                    \
        ISoft(64, D5, D5, B1), ISoft(D2, 4E, 4E, 9C), ISoft(E0, A9, A9, 49), ISoft(B4, 6C, 6C, D8),                    \
        ISoft(FA, 56, 56, AC), ISoft(07, F4, F4, F3), ISoft(25, EA, EA, CF), ISoft(AF, 65, 65, CA),                    \
        ISoft(8E, 7A, 7A, F4), ISoft(E9, AE, AE, 47), ISoft(18, 08, 08, 10), ISoft(D5, BA, BA, 6F),                    \
        ISoft(88, 78, 78, F0), ISoft(6F, 25, 25, 4A), ISoft(72, 2E, 2E, 5C), ISoft(24, 1C, 1C, 38),                    \
        ISoft(F1, A6, A6, 57), ISoft(C7, B4, B4, 73), ISoft(51, C6, C6, 97), ISoft(23, E8, E8, CB),                    \
        ISoft(7C, DD, DD, A1), ISoft(9C, 74, 74, E8), ISoft(21, 1F, 1F, 3E), ISoft(DD, 4B, 4B, 96),                    \
        ISoft(DC, BD, BD, 61), ISoft(86, 8B, 8B, 0D), ISoft(85, 8A, 8A, 0F), ISoft(90, 70, 70, E0),                    \
        ISoft(42, 3E, 3E, 7C), ISoft(C4, B5, B5, 71), ISoft(AA, 66, 66, CC), ISoft(D8, 48, 48, 90),                    \
        ISoft(05, 03, 03, 06), ISoft(01, F6, F6, F7), ISoft(12, 0E, 0E, 1C), ISoft(A3, 61, 61, C2),                    \
        ISoft(5F, 35, 35, 6A), ISoft(F9, 57, 57, AE), ISoft(D0, B9, B9, 69), ISoft(91, 86, 86, 17),                    \
        ISoft(58, C1, C1, 99), ISoft(27, 1D, 1D, 3A), ISoft(B9, 9E, 9E, 27), ISoft(38, E1, E1, D9),                    \
        ISoft(13, F8, F8, EB), ISoft(B3, 98, 98, 2B), ISoft(33, 11, 11, 22), ISoft(BB, 69, 69, D2),                    \
        ISoft(70, D9, D9, A9), ISoft(89, 8E, 8E, 07), ISoft(A7, 94, 94, 33), ISoft(B6, 9B, 9B, 2D),                    \
        ISoft(22, 1E, 1E, 3C), ISoft(92, 87, 87, 15), ISoft(20, E9, E9, C9), ISoft(49, CE, CE, 87),                    \
        ISoft(FF, 55, 55, AA), ISoft(78, 28, 28, 50), ISoft(7A, DF, DF, A5), ISoft(8F, 8C, 8C, 03),                    \
        ISoft(F8, A1, A1, 59), ISoft(80, 89, 89, 09), ISoft(17, 0D, 0D, 1A), ISoft(DA, BF, BF, 65),                    \
        ISoft(31, E6, E6, D7), ISoft(C6, 42, 42, 84), ISoft(B8, 68, 68, D0), ISoft(C3, 41, 41, 82),                    \
        ISoft(B0, 99, 99, 29), ISoft(77, 2D, 2D, 5A), ISoft(11, 0F, 0F, 1E), ISoft(CB, B0, B0, 7B),                    \
        ISoft(FC, 54, 54, A8), ISoft(D6, BB, BB, 6D), ISoft(3A, 16, 16, 2C)

#define ISoft(a, b, c, d) 0x##a##b##c##d##u
static const uint32 FT0[256] = {FT};
#undef ISoft

#if !defined(CRYPTO_AES_FEWER_TABLES)

#define ISoft(a, b, c, d) 0x##b##c##d##a##u
static const uint32 FT1[256] = {FT};
#undef ISoft

#define ISoft(a, b, c, d) 0x##c##d##a##b##u
static const uint32 FT2[256] = {FT};
#undef ISoft

#define ISoft(a, b, c, d) 0x##d##a##b##c##u
static const uint32 FT3[256] = {FT};
#undef ISoft

#endif /* !CRYPTO_AES_FEWER_TABLES */

#undef FT

/*
 * Reverse S-box
 */
static const uint8 RSb[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB, 0x7C, 0xE3, 0x39,
    0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB, 0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2,
    0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E, 0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76,
    0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25, 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC,
    0x5D, 0x65, 0xB6, 0x92, 0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D,
    0x84, 0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06, 0xD0, 0x2C,
    0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B, 0x3A, 0x91, 0x11, 0x41, 0x4F,
    0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73, 0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E, 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62,
    0x0E, 0xAA, 0x18, 0xBE, 0x1B, 0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD,
    0x5A, 0xF4, 0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F, 0x60,
    0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF, 0xA0, 0xE0, 0x3B, 0x4D,
    0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61, 0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6,
    0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D};

/*
 * Reverse tables
 */
#define RT                                                                                                             \
                                                                                                                       \
    ISoft(50, A7, F4, 51), ISoft(53, 65, 41, 7E), ISoft(C3, A4, 17, 1A), ISoft(96, 5E, 27, 3A), ISoft(CB, 6B, AB, 3B), \
        ISoft(F1, 45, 9D, 1F), ISoft(AB, 58, FA, AC), ISoft(93, 03, E3, 4B), ISoft(55, FA, 30, 20),                    \
        ISoft(F6, 6D, 76, AD), ISoft(91, 76, CC, 88), ISoft(25, 4C, 02, F5), ISoft(FC, D7, E5, 4F),                    \
        ISoft(D7, CB, 2A, C5), ISoft(80, 44, 35, 26), ISoft(8F, A3, 62, B5), ISoft(49, 5A, B1, DE),                    \
        ISoft(67, 1B, BA, 25), ISoft(98, 0E, EA, 45), ISoft(E1, C0, FE, 5D), ISoft(02, 75, 2F, C3),                    \
        ISoft(12, F0, 4C, 81), ISoft(A3, 97, 46, 8D), ISoft(C6, F9, D3, 6B), ISoft(E7, 5F, 8F, 03),                    \
        ISoft(95, 9C, 92, 15), ISoft(EB, 7A, 6D, BF), ISoft(DA, 59, 52, 95), ISoft(2D, 83, BE, D4),                    \
        ISoft(D3, 21, 74, 58), ISoft(29, 69, E0, 49), ISoft(44, C8, C9, 8E), ISoft(6A, 89, C2, 75),                    \
        ISoft(78, 79, 8E, F4), ISoft(6B, 3E, 58, 99), ISoft(DD, 71, B9, 27), ISoft(B6, 4F, E1, BE),                    \
        ISoft(17, AD, 88, F0), ISoft(66, AC, 20, C9), ISoft(B4, 3A, CE, 7D), ISoft(18, 4A, DF, 63),                    \
        ISoft(82, 31, 1A, E5), ISoft(60, 33, 51, 97), ISoft(45, 7F, 53, 62), ISoft(E0, 77, 64, B1),                    \
        ISoft(84, AE, 6B, BB), ISoft(1C, A0, 81, FE), ISoft(94, 2B, 08, F9), ISoft(58, 68, 48, 70),                    \
        ISoft(19, FD, 45, 8F), ISoft(87, 6C, DE, 94), ISoft(B7, F8, 7B, 52), ISoft(23, D3, 73, AB),                    \
        ISoft(E2, 02, 4B, 72), ISoft(57, 8F, 1F, E3), ISoft(2A, AB, 55, 66), ISoft(07, 28, EB, B2),                    \
        ISoft(03, C2, B5, 2F), ISoft(9A, 7B, C5, 86), ISoft(A5, 08, 37, D3), ISoft(F2, 87, 28, 30),                    \
        ISoft(B2, A5, BF, 23), ISoft(BA, 6A, 03, 02), ISoft(5C, 82, 16, ED), ISoft(2B, 1C, CF, 8A),                    \
        ISoft(92, B4, 79, A7), ISoft(F0, F2, 07, F3), ISoft(A1, E2, 69, 4E), ISoft(CD, F4, DA, 65),                    \
        ISoft(D5, BE, 05, 06), ISoft(1F, 62, 34, D1), ISoft(8A, FE, A6, C4), ISoft(9D, 53, 2E, 34),                    \
        ISoft(A0, 55, F3, A2), ISoft(32, E1, 8A, 05), ISoft(75, EB, F6, A4), ISoft(39, EC, 83, 0B),                    \
        ISoft(AA, EF, 60, 40), ISoft(06, 9F, 71, 5E), ISoft(51, 10, 6E, BD), ISoft(F9, 8A, 21, 3E),                    \
        ISoft(3D, 06, DD, 96), ISoft(AE, 05, 3E, DD), ISoft(46, BD, E6, 4D), ISoft(B5, 8D, 54, 91),                    \
        ISoft(05, 5D, C4, 71), ISoft(6F, D4, 06, 04), ISoft(FF, 15, 50, 60), ISoft(24, FB, 98, 19),                    \
        ISoft(97, E9, BD, D6), ISoft(CC, 43, 40, 89), ISoft(77, 9E, D9, 67), ISoft(BD, 42, E8, B0),                    \
        ISoft(88, 8B, 89, 07), ISoft(38, 5B, 19, E7), ISoft(DB, EE, C8, 79), ISoft(47, 0A, 7C, A1),                    \
        ISoft(E9, 0F, 42, 7C), ISoft(C9, 1E, 84, F8), ISoft(00, 00, 00, 00), ISoft(83, 86, 80, 09),                    \
        ISoft(48, ED, 2B, 32), ISoft(AC, 70, 11, 1E), ISoft(4E, 72, 5A, 6C), ISoft(FB, FF, 0E, FD),                    \
        ISoft(56, 38, 85, 0F), ISoft(1E, D5, AE, 3D), ISoft(27, 39, 2D, 36), ISoft(64, D9, 0F, 0A),                    \
        ISoft(21, A6, 5C, 68), ISoft(D1, 54, 5B, 9B), ISoft(3A, 2E, 36, 24), ISoft(B1, 67, 0A, 0C),                    \
        ISoft(0F, E7, 57, 93), ISoft(D2, 96, EE, B4), ISoft(9E, 91, 9B, 1B), ISoft(4F, C5, C0, 80),                    \
        ISoft(A2, 20, DC, 61), ISoft(69, 4B, 77, 5A), ISoft(16, 1A, 12, 1C), ISoft(0A, BA, 93, E2),                    \
        ISoft(E5, 2A, A0, C0), ISoft(43, E0, 22, 3C), ISoft(1D, 17, 1B, 12), ISoft(0B, 0D, 09, 0E),                    \
        ISoft(AD, C7, 8B, F2), ISoft(B9, A8, B6, 2D), ISoft(C8, A9, 1E, 14), ISoft(85, 19, F1, 57),                    \
        ISoft(4C, 07, 75, AF), ISoft(BB, DD, 99, EE), ISoft(FD, 60, 7F, A3), ISoft(9F, 26, 01, F7),                    \
        ISoft(BC, F5, 72, 5C), ISoft(C5, 3B, 66, 44), ISoft(34, 7E, FB, 5B), ISoft(76, 29, 43, 8B),                    \
        ISoft(DC, C6, 23, CB), ISoft(68, FC, ED, B6), ISoft(63, F1, E4, B8), ISoft(CA, DC, 31, D7),                    \
        ISoft(10, 85, 63, 42), ISoft(40, 22, 97, 13), ISoft(20, 11, C6, 84), ISoft(7D, 24, 4A, 85),                    \
        ISoft(F8, 3D, BB, D2), ISoft(11, 32, F9, AE), ISoft(6D, A1, 29, C7), ISoft(4B, 2F, 9E, 1D),                    \
        ISoft(F3, 30, B2, DC), ISoft(EC, 52, 86, 0D), ISoft(D0, E3, C1, 77), ISoft(6C, 16, B3, 2B),                    \
        ISoft(99, B9, 70, A9), ISoft(FA, 48, 94, 11), ISoft(22, 64, E9, 47), ISoft(C4, 8C, FC, A8),                    \
        ISoft(1A, 3F, F0, A0), ISoft(D8, 2C, 7D, 56), ISoft(EF, 90, 33, 22), ISoft(C7, 4E, 49, 87),                    \
        ISoft(C1, D1, 38, D9), ISoft(FE, A2, CA, 8C), ISoft(36, 0B, D4, 98), ISoft(CF, 81, F5, A6),                    \
        ISoft(28, DE, 7A, A5), ISoft(26, 8E, B7, DA), ISoft(A4, BF, AD, 3F), ISoft(E4, 9D, 3A, 2C),                    \
        ISoft(0D, 92, 78, 50), ISoft(9B, CC, 5F, 6A), ISoft(62, 46, 7E, 54), ISoft(C2, 13, 8D, F6),                    \
        ISoft(E8, B8, D8, 90), ISoft(5E, F7, 39, 2E), ISoft(F5, AF, C3, 82), ISoft(BE, 80, 5D, 9F),                    \
        ISoft(7C, 93, D0, 69), ISoft(A9, 2D, D5, 6F), ISoft(B3, 12, 25, CF), ISoft(3B, 99, AC, C8),                    \
        ISoft(A7, 7D, 18, 10), ISoft(6E, 63, 9C, E8), ISoft(7B, BB, 3B, DB), ISoft(09, 78, 26, CD),                    \
        ISoft(F4, 18, 59, 6E), ISoft(01, B7, 9A, EC), ISoft(A8, 9A, 4F, 83), ISoft(65, 6E, 95, E6),                    \
        ISoft(7E, E6, FF, AA), ISoft(08, CF, BC, 21), ISoft(E6, E8, 15, EF), ISoft(D9, 9B, E7, BA),                    \
        ISoft(CE, 36, 6F, 4A), ISoft(D4, 09, 9F, EA), ISoft(D6, 7C, B0, 29), ISoft(AF, B2, A4, 31),                    \
        ISoft(31, 23, 3F, 2A), ISoft(30, 94, A5, C6), ISoft(C0, 66, A2, 35), ISoft(37, BC, 4E, 74),                    \
        ISoft(A6, CA, 82, FC), ISoft(B0, D0, 90, E0), ISoft(15, D8, A7, 33), ISoft(4A, 98, 04, F1),                    \
        ISoft(F7, DA, EC, 41), ISoft(0E, 50, CD, 7F), ISoft(2F, F6, 91, 17), ISoft(8D, D6, 4D, 76),                    \
        ISoft(4D, B0, EF, 43), ISoft(54, 4D, AA, CC), ISoft(DF, 04, 96, E4), ISoft(E3, B5, D1, 9E),                    \
        ISoft(1B, 88, 6A, 4C), ISoft(B8, 1F, 2C, C1), ISoft(7F, 51, 65, 46), ISoft(04, EA, 5E, 9D),                    \
        ISoft(5D, 35, 8C, 01), ISoft(73, 74, 87, FA), ISoft(2E, 41, 0B, FB), ISoft(5A, 1D, 67, B3),                    \
        ISoft(52, D2, DB, 92), ISoft(33, 56, 10, E9), ISoft(13, 47, D6, 6D), ISoft(8C, 61, D7, 9A),                    \
        ISoft(7A, 0C, A1, 37), ISoft(8E, 14, F8, 59), ISoft(89, 3C, 13, EB), ISoft(EE, 27, A9, CE),                    \
        ISoft(35, C9, 61, B7), ISoft(ED, E5, 1C, E1), ISoft(3C, B1, 47, 7A), ISoft(59, DF, D2, 9C),                    \
        ISoft(3F, 73, F2, 55), ISoft(79, CE, 14, 18), ISoft(BF, 37, C7, 73), ISoft(EA, CD, F7, 53),                    \
        ISoft(5B, AA, FD, 5F), ISoft(14, 6F, 3D, DF), ISoft(86, DB, 44, 78), ISoft(81, F3, AF, CA),                    \
        ISoft(3E, C4, 68, B9), ISoft(2C, 34, 24, 38), ISoft(5F, 40, A3, C2), ISoft(72, C3, 1D, 16),                    \
        ISoft(0C, 25, E2, BC), ISoft(8B, 49, 3C, 28), ISoft(41, 95, 0D, FF), ISoft(71, 01, A8, 39),                    \
        ISoft(DE, B3, 0C, 08), ISoft(9C, E4, B4, D8), ISoft(90, C1, 56, 64), ISoft(61, 84, CB, 7B),                    \
        ISoft(70, B6, 32, D5), ISoft(74, 5C, 6C, 48), ISoft(42, 57, B8, D0)

#define ISoft(a, b, c, d) 0x##a##b##c##d##u
static const uint32 RT0[256] = {RT};
#undef ISoft

#if !defined(CRYPTO_AES_FEWER_TABLES)

#define ISoft(a, b, c, d) 0x##b##c##d##a##u
static const uint32 RT1[256] = {RT};
#undef ISoft

#define ISoft(a, b, c, d) 0x##c##d##a##b##u
static const uint32 RT2[256] = {RT};
#undef ISoft

#define ISoft(a, b, c, d) 0x##d##a##b##c##u
static const uint32 RT3[256] = {RT};
#undef ISoft

#endif /* !CRYPTO_AES_FEWER_TABLES */

#undef RT

/*
 * Round constants
 */
static const uint32 RCON[10] = {
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008,
    0x00000010,
    0x00000020,
    0x00000040,
    0x00000080,
    0x0000001B,
    0x00000036};

#define AES_RT0(idx) RT0[idx]
#define AES_RT1(idx) RT1[idx]
#define AES_RT2(idx) RT2[idx]
#define AES_RT3(idx) RT3[idx]

#define AES_FT0(idx) FT0[idx]
#define AES_FT1(idx) FT1[idx]
#define AES_FT2(idx) FT2[idx]
#define AES_FT3(idx) FT3[idx]

/******************************************************************************/
/*
 * Brief               Generate round keys for encryption.
 *
 * Param-Name[in]      key: The original key for encryption.
 *                     keybits: The length of input key in bit.
 * Param-Name[in/out]  ctx: The context of AES.
 * Param-Name[out]     None
 * Return              Std_ReturnType
 */
/******************************************************************************/
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_setkey_enc(Crypto_AESData* ctx, P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint16 keybits)
{
    uint16 i;
    uint32* RK;
    Std_ReturnType ret = E_OK;
    switch (keybits)
    {
    case 128:
        ctx->nr = 10u;
        break;
    case 192:
        ctx->nr = 12u;
        break;
    case 256:
        ctx->nr = 14u;
        break;
    default:
        ret = E_NOT_OK;
        break;
    }

    ctx->rk = RK = ctx->buf;

    for (i = 0; i < (keybits >> 5); i++)
    {
        GET_UINT32_LE(RK[i], key, i << 2);
    }

    switch (ctx->nr)
    {
    case 10:

        for (i = 0; i < 10; i++, RK += 4)
        {
            RK[4] = RK[0] ^ RCON[i] ^ ((uint32)FSb[(RK[3] >> 8) & 0xFF]) ^ ((uint32)FSb[(RK[3] >> 16) & 0xFF] << 8)
                    ^ ((uint32)FSb[(RK[3] >> 24) & 0xFF] << 16) ^ ((uint32)FSb[(RK[3]) & 0xFF] << 24);

            RK[5] = RK[1] ^ RK[4];
            RK[6] = RK[2] ^ RK[5];
            RK[7] = RK[3] ^ RK[6];
        }
        break;

    case 12:

        for (i = 0; i < 8; i++, RK += 6)
        {
            RK[6] = RK[0] ^ RCON[i] ^ ((uint32)FSb[(RK[5] >> 8) & 0xFF]) ^ ((uint32)FSb[(RK[5] >> 16) & 0xFF] << 8)
                    ^ ((uint32)FSb[(RK[5] >> 24) & 0xFF] << 16) ^ ((uint32)FSb[(RK[5]) & 0xFF] << 24);

            RK[7] = RK[1] ^ RK[6];
            RK[8] = RK[2] ^ RK[7];
            RK[9] = RK[3] ^ RK[8];
            RK[10] = RK[4] ^ RK[9];
            RK[11] = RK[5] ^ RK[10];
        }
        break;

    case 14:

        for (i = 0; i < 7; i++, RK += 8)
        {
            RK[8] = RK[0] ^ RCON[i] ^ ((uint32)FSb[(RK[7] >> 8) & 0xFF]) ^ ((uint32)FSb[(RK[7] >> 16) & 0xFF] << 8)
                    ^ ((uint32)FSb[(RK[7] >> 24) & 0xFF] << 16) ^ ((uint32)FSb[(RK[7]) & 0xFF] << 24);

            RK[9] = RK[1] ^ RK[8];
            RK[10] = RK[2] ^ RK[9];
            RK[11] = RK[3] ^ RK[10];

            RK[12] = RK[4] ^ ((uint32)FSb[(RK[11]) & 0xFF]) ^ ((uint32)FSb[(RK[11] >> 8) & 0xFF] << 8)
                     ^ ((uint32)FSb[(RK[11] >> 16) & 0xFF] << 16) ^ ((uint32)FSb[(RK[11] >> 24) & 0xFF] << 24);

            RK[13] = RK[5] ^ RK[12];
            RK[14] = RK[6] ^ RK[13];
            RK[15] = RK[7] ^ RK[14];
        }
        break;
    }

    return ret;
}

/******************************************************************************/
/*
 * Brief               Generate round keys for encryption.
 *
 * Param-Name[in]      key: The original key for encryption.
 *                     keybits: The length of input key in bit.
 * Param-Name[in/out]  ctx: The context of AES.
 * Param-Name[out]     None
 * Return              Std_ReturnType
 */
/******************************************************************************/

FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_setkey_dec(Crypto_AESData* ctx, P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint16 keybits)
{
    int i, j;
    Crypto_AESData cty;
    uint32* RK;
    uint32* SK;
    Std_ReturnType ret;
    (void)ILib_memset(&cty, 0u, sizeof(Crypto_AESData));
    (void)ILib_memset(&cty, 0u, sizeof(Crypto_AESData));
    ctx->rk = RK = ctx->buf;

    /* Also checks keybits */
    ret = Crypto_aes_setkey_enc(&cty, key, keybits);
    ctx->nr = cty.nr;

    SK = cty.rk + cty.nr * 4; /* PRQA S 3395 */ /* MISRA Rule 12.1 */

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;

    for (i = ctx->nr - 1, SK -= 8; i > 0; i--, SK -= 8)
    {
        for (j = 0; j < 4; j++, SK++)
        {
            *RK++ = AES_RT0(FSb[(*SK) & 0xFF]) ^ AES_RT1(FSb[(*SK >> 8) & 0xFF]) ^ AES_RT2(FSb[(*SK >> 16) & 0xFF])
                    ^ AES_RT3(FSb[(*SK >> 24) & 0xFF]);
        }
    }

    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++;
    *RK++ = *SK++; /* PRQA S 2983 */ /* MISRA Rule 2.2 */

    return ret;
}

#define AES_FROUND(X0, X1, X2, X3, Y0, Y1, Y2, Y3)                                                         \
    do                                                                                                     \
    {                                                                                                      \
        (X0) = *RK++ ^ AES_FT0(((Y0)) & 0xFF) ^ AES_FT1(((Y1) >> 8) & 0xFF) ^ AES_FT2(((Y2) >> 16) & 0xFF) \
               ^ AES_FT3(((Y3) >> 24) & 0xFF);                                                             \
                                                                                                           \
        (X1) = *RK++ ^ AES_FT0(((Y1)) & 0xFF) ^ AES_FT1(((Y2) >> 8) & 0xFF) ^ AES_FT2(((Y3) >> 16) & 0xFF) \
               ^ AES_FT3(((Y0) >> 24) & 0xFF);                                                             \
                                                                                                           \
        (X2) = *RK++ ^ AES_FT0(((Y2)) & 0xFF) ^ AES_FT1(((Y3) >> 8) & 0xFF) ^ AES_FT2(((Y0) >> 16) & 0xFF) \
               ^ AES_FT3(((Y1) >> 24) & 0xFF);                                                             \
                                                                                                           \
        (X3) = *RK++ ^ AES_FT0(((Y3)) & 0xFF) ^ AES_FT1(((Y0) >> 8) & 0xFF) ^ AES_FT2(((Y1) >> 16) & 0xFF) \
               ^ AES_FT3(((Y2) >> 24) & 0xFF);                                                             \
    } while (0)

#define AES_RROUND(X0, X1, X2, X3, Y0, Y1, Y2, Y3)                                                         \
    do                                                                                                     \
    {                                                                                                      \
        (X0) = *RK++ ^ AES_RT0(((Y0)) & 0xFF) ^ AES_RT1(((Y3) >> 8) & 0xFF) ^ AES_RT2(((Y2) >> 16) & 0xFF) \
               ^ AES_RT3(((Y1) >> 24) & 0xFF);                                                             \
                                                                                                           \
        (X1) = *RK++ ^ AES_RT0(((Y1)) & 0xFF) ^ AES_RT1(((Y0) >> 8) & 0xFF) ^ AES_RT2(((Y3) >> 16) & 0xFF) \
               ^ AES_RT3(((Y2) >> 24) & 0xFF);                                                             \
                                                                                                           \
        (X2) = *RK++ ^ AES_RT0(((Y2)) & 0xFF) ^ AES_RT1(((Y1) >> 8) & 0xFF) ^ AES_RT2(((Y0) >> 16) & 0xFF) \
               ^ AES_RT3(((Y3) >> 24) & 0xFF);                                                             \
                                                                                                           \
        (X3) = *RK++ ^ AES_RT0(((Y3)) & 0xFF) ^ AES_RT1(((Y2) >> 8) & 0xFF) ^ AES_RT2(((Y1) >> 16) & 0xFF) \
               ^ AES_RT3(((Y0) >> 24) & 0xFF);                                                             \
    } while (0)

/******************************************************************************/
/*
 * Brief               Inner AES encryption on a 128 bits block, so you do not
 *                     need to care about the group mode.
 *
 * Param-Name[in]      ctx: The context of AES.
 *                     input: Buffer filled with 128 bits plaintext.
 * Param-Name[in/out]  None
 * Param-Name[out]     output: Buffer filled with ciphertext corresponded with
 *                             the input.
 * Return              Std_ReturnType:  E_OK: State accepted
 *                                      E_NOT_OK: State not accepted
 */
/******************************************************************************/

FUNC(Std_ReturnType, CRY_CODE) internal_aes_encrypt(Crypto_AESData* ctx, const uint8 input[16], uint8 output[16])
{
    int i;
    Std_ReturnType ret = E_OK;

    uint32 *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

    RK = ctx->rk;

    GET_UINT32_LE(X0, input, 0);
    X0 ^= *RK++;
    GET_UINT32_LE(X1, input, 4);
    X1 ^= *RK++;
    GET_UINT32_LE(X2, input, 8);
    X2 ^= *RK++;
    GET_UINT32_LE(X3, input, 12);
    X3 ^= *RK++;

    for (i = (ctx->nr >> 1) - 1; i > 0; i--)
    {
        AES_FROUND(Y0, Y1, Y2, Y3, X0, X1, X2, X3);
        AES_FROUND(X0, X1, X2, X3, Y0, Y1, Y2, Y3);
    }

    AES_FROUND(Y0, Y1, Y2, Y3, X0, X1, X2, X3);

    X0 = *RK++ ^ ((uint32)FSb[(Y0) & 0xFF]) ^ ((uint32)FSb[(Y1 >> 8) & 0xFF] << 8)
         ^ ((uint32)FSb[(Y2 >> 16) & 0xFF] << 16) ^ ((uint32)FSb[(Y3 >> 24) & 0xFF] << 24);

    X1 = *RK++ ^ ((uint32)FSb[(Y1) & 0xFF]) ^ ((uint32)FSb[(Y2 >> 8) & 0xFF] << 8)
         ^ ((uint32)FSb[(Y3 >> 16) & 0xFF] << 16) ^ ((uint32)FSb[(Y0 >> 24) & 0xFF] << 24);

    X2 = *RK++ ^ ((uint32)FSb[(Y2) & 0xFF]) ^ ((uint32)FSb[(Y3 >> 8) & 0xFF] << 8)
         ^ ((uint32)FSb[(Y0 >> 16) & 0xFF] << 16) ^ ((uint32)FSb[(Y1 >> 24) & 0xFF] << 24);

    X3 = *RK++ ^ ((uint32)FSb[(Y3) & 0xFF]) ^ ((uint32)FSb[(Y0 >> 8) & 0xFF] << 8)
         ^ ((uint32)FSb[(Y1 >> 16) & 0xFF] << 16) ^ ((uint32)FSb[(Y2 >> 24) & 0xFF] << 24);

    PUT_UINT32_LE(X0, output, 0);
    PUT_UINT32_LE(X1, output, 4);
    PUT_UINT32_LE(X2, output, 8);
    PUT_UINT32_LE(X3, output, 12);

    (void)ILib_memset(&X0, 0u, sizeof(X0));
    (void)ILib_memset(&X1, 0u, sizeof(X1));
    (void)ILib_memset(&X2, 0u, sizeof(X2));
    (void)ILib_memset(&X3, 0u, sizeof(X3));

    (void)ILib_memset(&Y0, 0u, sizeof(Y0));
    (void)ILib_memset(&Y1, 0u, sizeof(Y1));
    (void)ILib_memset(&Y2, 0u, sizeof(Y2));
    (void)ILib_memset(&Y3, 0u, sizeof(Y3));

    (void)ILib_memset(&RK, 0u, sizeof(RK));

    return ret;
}
/*
/******************************************************************************/
/*
 * Brief               Inner AES decryption on a 128 bits block, so you do not
 *                     need to care about the group mode.
 *
 * Param-Name[in]      ctx: The context of AES.
 *                     input: Buffer filled with 128 bits ciphertext.
 * Param-Name[in/out]  None
 * Param-Name[out]     output: Buffer filled with plaintext corresponded with
 *                             the input.
 * Return              Std_ReturnType:  E_OK: State accepted
 *                                      E_NOT_OK: State not accepted
 */
/******************************************************************************/

FUNC(Std_ReturnType, CRY_CODE) internal_aes_decrypt(Crypto_AESData* ctx, const uint8 input[16], uint8 output[16])
{
    int i;
    Std_ReturnType ret = E_OK;
    uint32 *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

    RK = ctx->rk;

    GET_UINT32_LE(X0, input, 0);
    X0 ^= *RK++;
    GET_UINT32_LE(X1, input, 4);
    X1 ^= *RK++;
    GET_UINT32_LE(X2, input, 8);
    X2 ^= *RK++;
    GET_UINT32_LE(X3, input, 12);
    X3 ^= *RK++;

    for (i = (ctx->nr >> 1) - 1; i > 0; i--)
    {
        AES_RROUND(Y0, Y1, Y2, Y3, X0, X1, X2, X3);
        AES_RROUND(X0, X1, X2, X3, Y0, Y1, Y2, Y3);
    }

    AES_RROUND(Y0, Y1, Y2, Y3, X0, X1, X2, X3);

    X0 = *RK++ ^ ((uint32)RSb[(Y0) & 0xFF]) ^ ((uint32)RSb[(Y3 >> 8) & 0xFF] << 8)
         ^ ((uint32)RSb[(Y2 >> 16) & 0xFF] << 16) ^ ((uint32)RSb[(Y1 >> 24) & 0xFF] << 24);

    X1 = *RK++ ^ ((uint32)RSb[(Y1) & 0xFF]) ^ ((uint32)RSb[(Y0 >> 8) & 0xFF] << 8)
         ^ ((uint32)RSb[(Y3 >> 16) & 0xFF] << 16) ^ ((uint32)RSb[(Y2 >> 24) & 0xFF] << 24);

    X2 = *RK++ ^ ((uint32)RSb[(Y2) & 0xFF]) ^ ((uint32)RSb[(Y1 >> 8) & 0xFF] << 8)
         ^ ((uint32)RSb[(Y0 >> 16) & 0xFF] << 16) ^ ((uint32)RSb[(Y3 >> 24) & 0xFF] << 24);

    X3 = *RK++ ^ ((uint32)RSb[(Y3) & 0xFF]) ^ ((uint32)RSb[(Y2 >> 8) & 0xFF] << 8)
         ^ ((uint32)RSb[(Y1 >> 16) & 0xFF] << 16) ^ ((uint32)RSb[(Y0 >> 24) & 0xFF] << 24);

    PUT_UINT32_LE(X0, output, 0);
    PUT_UINT32_LE(X1, output, 4);
    PUT_UINT32_LE(X2, output, 8);
    PUT_UINT32_LE(X3, output, 12);

    (void)ILib_memset(&X0, 0u, sizeof(X0));
    (void)ILib_memset(&X1, 0u, sizeof(X1));
    (void)ILib_memset(&X2, 0u, sizeof(X2));
    (void)ILib_memset(&X3, 0u, sizeof(X3));

    (void)ILib_memset(&Y0, 0u, sizeof(Y0));
    (void)ILib_memset(&Y1, 0u, sizeof(Y1));
    (void)ILib_memset(&Y2, 0u, sizeof(Y2));
    (void)ILib_memset(&Y3, 0u, sizeof(Y3));

    (void)ILib_memset(&RK, 0u, sizeof(RK));

    return ret;
}

/*
 * AES-ECB block encryption/decryption
 */
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_crypt_ecb(Crypto_AESData* ctx, uint8 mode, const uint8 input[16], uint8 output[16])
{
    if (mode == AES_ENCRYPT)
        return (internal_aes_encrypt(ctx, input, output));
    else
        return (internal_aes_decrypt(ctx, input, output));
}

/******************************************************************************/
/*
 * Brief               This function is used to perform AES with CBC group mode
 *                     on input.
 *
 * Param-Name[in]      ctx: The context of AES.
 *                     mode: The AES operation: CRYPTO_MODE_DECRYPT or
 *                           CRYPTO_MODE_ENCRYPT.
 *                     length: The length of input, calculated in byte.
 *                     iv: The Initialization vector. It must be a readable and
 *                         writeable buffer of 16 Bytes.
 *                     input: The plaintext needed to be encrypted, or the ciphertext
 *                            needed to be decrypted, depending on the mode.
 * Param-Name[in/out]  None
 * Param-Name[out]     output: The ciphertext or the plaintext corresponded with
 *                             input.
 * Return              Std_ReturnType:  E_OK: State accepted
 *                                      E_NOT_OK: State not accepted
 */
/******************************************************************************/
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_crypt_cbc(
    Crypto_AESData* ctx,
    uint8 mode,
    uint8 length,
    uint8 iv[16],
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) input,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) output)
{
    int i;
    uint8 temp[16];
    Std_ReturnType ret = E_NOT_OK;

    if (mode == AES_DECRYPT)
    {
        while (length > 0)
        {
            (void)ILib_memcpy(temp, input, 16);
            ret = internal_aes_decrypt(ctx, input, output); /* PRQA S 2784 */ /* MISRA Rule 17.5 */

            for (i = 0; i < 16; i++)
            {
                output[i] = (uint8)(input[i] ^ iv[i]);
            }

            (void)ILib_memcpy(iv, temp, 16);

            input += 16;
            output += 16;
            length = (length >= 16) ? (length - 16) : 0;
        }
    }
    else
    {
        while (length > 0)
        {
            for (i = 0; i < 16; i++)
            {
                output[i] = (uint8)(input[i] ^ iv[i]);
            }

            ret = internal_aes_encrypt(ctx, output, output); /* PRQA S 2784 */ /* MISRA Rule 17.5 */

            (void)ILib_memcpy(iv, output, 16);

            input += 16;
            output += 16;
            length = (length >= 16) ? (length - 16) : 0;
        }
    }
    return ret;
}
/******************************************************************************/
/*
 * Brief               This function is used to perform AES on input, as a part
 *                     of CMAC calculation.
 *
 * Param-Name[in]      ctx: The context of AES.
 *                     mode: The AES operation: CRYPTO_MODE_DECRYPT or
 *                           CRYPTO_MODE_ENCRYPT.
 *                     length: The length of input, calculated in byte.
 *                     input: The message needs to be encrypted or decrypted.
 * Param-Name[in/out]  None
 * Param-Name[out]     output: The cipheretxt or plaintext corresponded with input.
 * Return              Std_ReturnType:  E_OK: State accepted
 *                                      E_NOT_OK: State not accepted
 */
/******************************************************************************/
FUNC(Std_ReturnType, CRY_CODE)
Crypto_aes_crypt_cbc_CMAC(
    Crypto_AESData* ctx,
    uint8 mode,
    uint8 length,
    uint8 iv[16],
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) input,
    P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) output)
{
    int i;
    uint8 temp[16];
    Std_ReturnType ret = E_NOT_OK;
    if (mode == AES_DECRYPT)
    {
        while (length > 0)
        {
            (void)ILib_memcpy(temp, input, 16);
            ret = internal_aes_decrypt(ctx, input, output); /* PRQA S 2784 */ /* MISRA Rule 17.5 */
            for (i = 0; i < 16; i++)
            {
                output[i] = input[i]; //^ iv[i]);
            }
            input += 16;
            output += 16;
            length = (length >= 16) ? (length - 16) : 0;
        }
    }
    else
    {
        while (length > 0)
        {
            for (i = 0; i < 16; i++)
            {
                output[i] = input[i]; //^ iv[i]);
            }
            ret = internal_aes_encrypt(ctx, output, output); /* PRQA S 2784 */ /* MISRA Rule 17.5 */
            input += 16;
            output += 16;
            length = (length >= 16) ? (length - 16) : 0;
        }
    }
    return ret;
}
/*
 * Checkup routine
 */

FUNC(Std_ReturnType, CRY_CODE) Crypto_AESEncryptECB(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64])
{
    Crypto_AESData ctx;
    Std_ReturnType ret;
    (void)ILib_memset(&ctx, 0u, sizeof(Crypto_AESData));
    ret = Crypto_aes_setkey_enc(&ctx, key, 128);
    if (E_OK == ret)
    {
        ret = internal_aes_encrypt(&ctx, buf, buf);
    }
    return ret;
}

FUNC(Std_ReturnType, CRY_CODE) Crypto_AESDecryptECB(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64])
{
    Crypto_AESData ctx;
    Std_ReturnType ret;
    (void)ILib_memset(&ctx, 0u, sizeof(Crypto_AESData));

    ret = Crypto_aes_setkey_dec(&ctx, key, 128);
    if (E_OK == ret)
    {
        ret = internal_aes_decrypt(&ctx, buf, buf);
    }
    return ret;
}

FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESEncryptCBC(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16], uint8 inputlength)
{
    Crypto_AESData ctx;
    Std_ReturnType ret;
    uint8 prv[16];
    uint8 tmp[16];
    (void)ILib_memset(&ctx, 0u, sizeof(Crypto_AESData));
    (void)ILib_memset(prv, 0u, 16);
    (void)ILib_memset(tmp, 0u, 16);

    ret = Crypto_aes_setkey_enc(&ctx, key, 128);
    if (E_OK == ret)
    {
        ret = Crypto_aes_crypt_cbc(&ctx, AES_ENCRYPT, inputlength, iv, buf, buf);
    }
    return ret;
}

FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESDecryptCBC(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16], uint8 inputlength)
{
    Crypto_AESData ctx;
    Std_ReturnType ret;
    uint8 prv[16];
    (void)ILib_memset(&ctx, 0u, sizeof(Crypto_AESData));
    (void)ILib_memset(prv, 0u, 16);

    ret = Crypto_aes_setkey_dec(&ctx, key, 128);
    if (E_OK == ret)
    {
        ret = Crypto_aes_crypt_cbc(&ctx, AES_DECRYPT, inputlength, iv, buf, buf);
    }

    return ret;
}

FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESEncryptCTR(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16])
{

    Crypto_AESData ctx;
    Std_ReturnType ret;
    uint8 j;
    (void)ILib_memset(&ctx, 0u, sizeof(Crypto_AESData));

    ret = Crypto_aes_setkey_dec(&ctx, key, 128);

    if (E_OK == ret)
    {
        ret = internal_aes_encrypt(&ctx, iv, iv);
    }

    for (j = 0; j < 16; j++)
    {
        buf[j] = buf[j] ^ iv[j];
    }

    return ret;
}

FUNC(Std_ReturnType, CRY_CODE)
Crypto_AESDecryptCTR(P2VAR(uint8, AUTOMATIC, CRY_APPL_DATA) key, uint8 buf[64], uint8 iv[16])
{

    Crypto_AESData ctx;
    Std_ReturnType ret;
    uint8 j;
    (void)ILib_memset(&ctx, 0u, sizeof(Crypto_AESData));

    ret = Crypto_aes_setkey_dec(&ctx, key, 128);

    if (E_OK == ret)
    {
        ret = internal_aes_encrypt(&ctx, iv, iv);
    }
    for (j = 0; j < 16; j++)
    {
        buf[j] = buf[j] ^ iv[j];
    }

    return ret;
}
#endif /* CRYPTO_ALGORITHM_AES == STD_ON */
#define CRYPTO_STOP_SEC_CODE
#include "Crypto_MemMap.h"

/* PRQA S 0342 -- */                     /* MISRA Rule 20.10 */
/* PRQA S 3432 -- */                     /* MISRA Rule 20.7 */
/* PRQA S 0488 -- */                     /* MISRA Rule 18.4 */
/* PRQA S 2016,2002 -- */                /* MISRA Rule 16.4 */
/* PRQA S 2212 -- */                     /* MISRA Rule 15.6 */
/* PRQA S 2463,2462 -- */                /* MISRA Rule 14.2 */
/* PRQA S 3226 -- */                     /* MISRA Rule 13.4 */
/* PRQA S 3440 -- */                     /* MISRA Rule 13.3 */
/* PRQA S 3418 -- */                     /* MISRA Rule 12.3 */
/* PRQA S 1864,1863,1862,1860,1841 -- */ /* MISRA Rule 10.4 */
/* PRQA S 3218 -- */                     /* MISRA Rule 8.9 */
/* PRQA S 4542 -- */                     /* MISRA Rule 10.1 */
/* PRQA S 1532,1505 -- */                /* MISRA Rule 8.7 */
/* PRQA S 5209 -- */                     /* MISRA Dir 4.6 */
/* PRQA S 2985,2982 -- */                /* MISRA Rule 2.2 */
