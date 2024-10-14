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
 **  FILENAME    : FlsTst.c                                                    **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : yin.Huang                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Containing the entire or parts of Flash test code           **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19_11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/**
  \page ISOFT_MISRA_Exceptions  MISRA-C:2012 Compliance Exceptions
    ModeName:FlsTst<br>
  RuleSorce:puhua-rule.rcf 2.3.1

   \li PRQA S 0306 MISRA Rule 11.4 .<br>
    Reason:Necessary type conversions.

   \li PRQA S 1514 MISRA Rule 8.9 .<br>
    Reason:Global variables that need to be updated by dependent applications.

    \li PRQA S 3432 MISRA Rule 20.7 .<br>
    Reason:Function-like macros are used to allow more efficient code.
 */

/*===================[V E R S I O N  I N F O R M A T I O N]===================*/
#define FLSTST_C_AR_MAJOR_VERSION 4U
#define FLSTST_C_AR_MINOR_VERSION 5U
#define FLSTST_C_AR_PATCH_VERSION 0U
#define FLSTST_C_SW_MAJOR_VERSION 2U
#define FLSTST_C_SW_MINOR_VERSION 0U
#define FLSTST_C_SW_PATCH_VERSION 2U
/*============================================================================*/

/*==============================[I N C L U D E S]=============================*/
#include "FlsTst.h"
#include "SchM_FlsTst.h"
#include "Dem.h"
#include "Det.h"
#include "Crc.h"
/*============================================================================*/

/*==============================[M A C R O S]=================================*/
#if (STD_ON == FLSTST_DEV_ERROR_DETECT)
#define FLSTST_DET_REPORTERROR(ApiId, ErrorId) \
    ((void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID, (ApiId), (ErrorId)))
#else
#define FLSTST_DET_REPORTERROR(ApiId, ErrorId)
#endif /* STD_ON == FLSTST_DEV_ERROR_DETECT */

/*============================================================================*/

/*==========================[V E R S I O N  C H E C K]========================*/

#if (FLSTST_C_AR_MAJOR_VERSION != FLSTST_H_AR_MAJOR_VERSION)
#error "FLSTST.c and FLSTST.h AR major version Mismatch"
#endif

#if (FLSTST_C_AR_MINOR_VERSION != FLSTST_H_AR_MINOR_VERSION)
#error "FLSTST.c and FLSTST.h AR minor version Mismatch"
#endif

#if (FLSTST_C_AR_PATCH_VERSION != FLSTST_H_AR_PATCH_VERSION)
#error "FLSTST.c and FLSTST.h AR patch version Mismatch"
#endif

#if (FLSTST_C_SW_MAJOR_VERSION != FLSTST_H_SW_MAJOR_VERSION)
#error "FLSTST.c and FLSTST.h SW major version Mismatch"
#endif

#if (FLSTST_C_SW_MINOR_VERSION != FLSTST_H_SW_MINOR_VERSION)
#error "FLSTST.c and FLSTST.h SW minor version Mismatch"
#endif

#if (FLSTST_CFG_H_AR_MAJOR_VERSION != FLSTST_H_AR_MAJOR_VERSION)
#error "FLSTST.h and FLSTST_CFG.h AR major version Mismatch"
#endif

#if (FLSTST_CFG_H_AR_MINOR_VERSION != FLSTST_H_AR_MINOR_VERSION)
#error "FLSTST.c and FLSTST_CFG.h AR minor version Mismatch"
#endif

#if (FLSTST_CFG_H_AR_PATCH_VERSION != FLSTST_H_AR_PATCH_VERSION)
#error "FLSTST.c and FLSTST_CFG.h AR patch version Mismatch"
#endif

#if (FLSTST_CFG_H_SW_MAJOR_VERSION != FLSTST_H_SW_MAJOR_VERSION)
#error "FLSTST.c and FLSTST_CFG.h SW major version Mismatch"
#endif

#if (FLSTST_CFG_H_SW_MINOR_VERSION != FLSTST_H_SW_MINOR_VERSION)
#error "FLSTST.c and FLSTST_CFG.h SW minor version Mismatch"
#endif

/*============================================================================*/

/*======================[F U N C  D E C L A R A T I O N]======================*/
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"

#if (0u != FLSTST_BGND_BLOCK_NUM)
static void FlsTst_CalcAtomic(void);
static void FlsTst_InterTest(void);
static void FlsTst_BlockTestFinish(void);
static void FlsTst_CopyBlockInfo(FlsTst_BlockIdType FlsTstBlockID);
#endif
#if (0u != FLSTST_FGND_BLOCK_NUM)
static Std_ReturnType FlsTst_StartFgndInterTest(FlsTst_BlockInfoType* BlockInfoPtr);
static Std_ReturnType FlsTst_CRC32Fgnd(FlsTst_BlockInfoType* BlockInfoPtr);
static Std_ReturnType FlsTst_CRC16Fgnd(FlsTst_BlockInfoType* BlockInfoPtr);
static Std_ReturnType FlsTst_CRC8Fgnd(FlsTst_BlockInfoType* BlockInfoPtr);
static Std_ReturnType FlsTst_ChecksumFgnd(FlsTst_BlockInfoType* BlockInfoPtr);
static Std_ReturnType FlsTst_ECCTestFgnd(FlsTst_BlockInfoType* BlockInfoPtr);
static Std_ReturnType FlsTst_DuplicatedMemoryFgnd(FlsTst_BlockInfoType* BlockInfoPtr);
#endif
#if ((0U != FLSTST_BGND_BLOCK_NUM) || (0U != FLSTST_FGND_BLOCK_NUM))
static Std_ReturnType FlsTst_MemCompare(
    P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) SourceDataPtr,
    P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) DstDataPtr,
    VAR(uint32, AUTOMATIC) Length);
static uint32 FlsTst_CheckSum(
    P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) Checksum_DataPtr,
    VAR(uint32, AUTOMATIC) Checksum_Length,
    VAR(uint32, AUTOMATIC) Checksum_StartValue,
    VAR(boolean, AUTOMATIC) Checksum_IsFirstCall);
#endif
#if (STD_ON == FLSTST_COMPLETED_NOTIFY_SUPPORT)
static void FlsTst_TestCompleted(void);
#endif /* STD_ON == FLSTST_COMPLETED_NOTIFY_SUPPORT */
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
/*============================================================================*/

/*=============================[V A R I A N T S]==============================*/
#define FLSTST_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "FlsTst_MemMap.h"
#if (0u == FLSTST_BGND_BLOCK_NUM)
static FlsTst_BlockInfoType* FlsTst_BlockBgndInfo;
#else
static FlsTst_BlockInfoType FlsTst_BlockBgndInfo[FLSTST_BGND_BLOCK_NUM];
static FlsTst_CurRunningType FlsTst_CurRunning;
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
static FlsTst_SignatureType FlsTst_ParamChecksum;
#endif /* STD_ON == FLSTST_EXTEND_SAFETY_MODE */
#endif
#if (0u == FLSTST_FGND_BLOCK_NUM)
static FlsTst_BlockInfoType* FlsTst_BlockFgndInfo;
#else
static FlsTst_BlockInfoType FlsTst_BlockFgndInfo[FLSTST_FGND_BLOCK_NUM];
#endif
static FlsTst_ModuleTypes FlsTst_Module;
#define FLSTST_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_VAR_NO_INIT_8BIT
#include "FlsTst_MemMap.h"
uint8 CrcCompleted; /* PRQA S 1514 */ /* MISRA Rule 8.9 */
#define FLSTST_STOP_SEC_VAR_NO_INIT_8BIT
#include "FlsTst_MemMap.h"
/*============================================================================*/

/*================[F U N C T I O N   I M P L E M E N T A T I O N S]===========*/
/*************************************************************************/
/*
 * Brief               Service for Flash Test initialization.
 * ServiceId           0x00
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ConfigPtr: Pointer to configuration set.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
/*************************************************************************/
/* req FlsTst_00017  */
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_Init(const FlsTst_ConfigType* ConfigPtr)
{
    uint8 MemBlockIndex;
    uint32 SigntureStoredAddr;
    uint32 TempBlockAddr;
    uint32 TempBlockSize;
    uint32 TempSignature;

#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
    uint32 ExtendAddr;
#endif
    if (NULL_PTR == ConfigPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_INIT_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        if (FLSTST_UNINIT != FlsTst_Module.State)
        {
            FLSTST_DET_REPORTERROR(FLSTST_INIT_ID, FLSTST_E_ALREADY_INITIALIZED);
        }
        else
        {
            SchM_Enter_FlsTst_RAMTST_EXCLUSIVE_AREA();
#if (0u != FLSTST_BGND_BLOCK_NUM)
#if (1u < FLSTST_BGND_BLOCK_NUM)
            for (MemBlockIndex = 0; MemBlockIndex < FLSTST_BGND_BLOCK_NUM; MemBlockIndex++)
#else
            MemBlockIndex = 0;
#endif /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
            {
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
                if ((0U == ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].BlcokLength)
                    || (0U == ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].SignatureAddress))
                {
                    /* Error parameter ,Please check your configuration */
                    FLSTST_DET_REPORTERROR(FLSTST_INIT_ID, FLSTST_E_INIT_FAILED);
                }
                else
                {
                    /*Get signaure's Address of Current configuration Block*/
                    ExtendAddr = ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].SignatureAddress;
                    TempBlockAddr = ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].BlockBaseAddress;
                    TempBlockSize = ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].BlcokLength;
                    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
                    if (((uint8)(TempBlockAddr) != *(uint8*)(ExtendAddr - 8U))
                        && ((uint8)(TempBlockAddr >> 8U) != *(uint8*)(ExtendAddr - 7U))
                        && ((uint8)(TempBlockAddr >> 16U) != *(uint8*)(ExtendAddr - 6U))
                        && ((uint8)(TempBlockAddr >> 24U) != *(uint8*)(ExtendAddr - 5U))
                        && ((uint8)(TempBlockSize) != *(uint8*)(ExtendAddr - 4U))
                        && ((uint8)(TempBlockSize >> 8U) != *(uint8*)(ExtendAddr - 3U))
                        && ((uint8)(TempBlockSize >> 16U) != *(uint8*)(ExtendAddr - 2U))
                        && ((uint8)(TempBlockSize >> 24U) != *(uint8*)(ExtendAddr - 1U)))
                    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */
                    {
                        /* Error parameter stored at fixed address锛孭lease check signature have been stored at correct
                         * address */
                        FLSTST_DET_REPORTERROR(FLSTST_INIT_ID, FLSTST_E_INIT_FAILED);
                    }
                    else
                    {
                        /* empty */
                    }
                }
#endif
                FlsTst_BlockBgndInfo[MemBlockIndex].MemoryBlockID =
                    ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].BgndBlockIndex;
                FlsTst_BlockBgndInfo[MemBlockIndex].TestAlgorithm =
                    ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].TestAlgorithm;
                FlsTst_BlockBgndInfo[MemBlockIndex].MemBlcokStartAddr =
                    ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].BlockBaseAddress;
                FlsTst_BlockBgndInfo[MemBlockIndex].MemBlcokLength =
                    ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].BlcokLength;
                if (FLSTST_DUPLICATED_MEMORY == FlsTst_BlockBgndInfo[MemBlockIndex].TestAlgorithm)
                {
                    /*Duplicated memory start address*/
                    FlsTst_BlockBgndInfo[MemBlockIndex].SignatureStored =
                        ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].SignatureAddress;
                }
                else
                {
                    TempSignature = ConfigPtr->FlsTst_BgndBlockPtr[MemBlockIndex].SignatureAddress;
                    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
                    FlsTst_BlockBgndInfo[MemBlockIndex].SignatureStored = ((uint32)(*(uint8*)(TempSignature)) << 24u);
                    FlsTst_BlockBgndInfo[MemBlockIndex].SignatureStored +=
                        ((uint32)(*(uint8*)(TempSignature + 1U)) << 16u);
                    FlsTst_BlockBgndInfo[MemBlockIndex].SignatureStored +=
                        ((uint32)(*(uint8*)(TempSignature + 2U)) << 8u);
                    FlsTst_BlockBgndInfo[MemBlockIndex].SignatureStored += (uint32)(*(uint8*)(TempSignature + 3U));
                    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */
                }
                FlsTst_BlockBgndInfo[MemBlockIndex].SignatueCalculated = 0u;
                FlsTst_BlockBgndInfo[MemBlockIndex].TestResult = FLSTST_RESULT_NOT_TESTED;
            }
#endif

#if (0u != FLSTST_FGND_BLOCK_NUM)
#if (1u < FLSTST_FGND_BLOCK_NUM)
            for (MemBlockIndex = 0; MemBlockIndex < FLSTST_FGND_BLOCK_NUM; MemBlockIndex++)
#else
            MemBlockIndex = 0;
#endif /* #if (1u < FLSTST_FGND_BLOCK_NUM) */
            {
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
                if ((0U == ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].BlcokLength)
                    || (0U == ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].SignatureAddress))
                {
                    /* Error parameter ,Please check your configuration */
                    FLSTST_DET_REPORTERROR(FLSTST_INIT_ID, FLSTST_E_INIT_FAILED);
                }
                else
                {
                    /*Get signaure's Address of Current configuration Block*/
                    ExtendAddr = ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].SignatureAddress;
                    TempBlockAddr = ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].BlockBaseAddress;
                    TempBlockSize = ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].BlcokLength;
                    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
                    if (((uint8)(TempBlockAddr) != *(uint8*)(ExtendAddr - 8U))
                        && ((uint8)(TempBlockAddr >> 8U) != *(uint8*)(ExtendAddr - 7U))
                        && ((uint8)(TempBlockAddr >> 16U) != *(uint8*)(ExtendAddr - 6U))
                        && ((uint8)(TempBlockAddr >> 24U) != *(uint8*)(ExtendAddr - 5U))
                        && ((uint8)(TempBlockSize) != *(uint8*)(ExtendAddr - 4U))
                        && ((uint8)(TempBlockSize >> 8U) != *(uint8*)(ExtendAddr - 3U))
                        && ((uint8)(TempBlockSize >> 16U) != *(uint8*)(ExtendAddr - 2U))
                        && ((uint8)(TempBlockSize >> 24U) != *(uint8*)(ExtendAddr - 1U)))
                    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */
                    {
                        /* Error parameter stored at fixed address锛孭lease check signature have been stored at correct
                         * address */
                        FLSTST_DET_REPORTERROR(FLSTST_INIT_ID, FLSTST_E_INIT_FAILED);
                    }
                    else
                    {
                        /* empty */
                    }
                }
#endif
                FlsTst_BlockFgndInfo[MemBlockIndex].MemoryBlockID =
                    ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].BgndBlockIndex;
                FlsTst_BlockFgndInfo[MemBlockIndex].TestAlgorithm =
                    ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].TestAlgorithm;
                FlsTst_BlockFgndInfo[MemBlockIndex].MemBlcokStartAddr =
                    ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].BlockBaseAddress;
                FlsTst_BlockFgndInfo[MemBlockIndex].MemBlcokLength =
                    ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].BlcokLength;
                if (FLSTST_DUPLICATED_MEMORY == FlsTst_BlockFgndInfo[MemBlockIndex].TestAlgorithm)
                {
                    /*Duplicated memory start address*/
                    FlsTst_BlockFgndInfo[MemBlockIndex].SignatureStored =
                        ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].SignatureAddress;
                }
                else
                {
                    TempSignature = ConfigPtr->FlsTst_FgndBlockPtr[MemBlockIndex].SignatureAddress;
                    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
                    FlsTst_BlockFgndInfo[MemBlockIndex].SignatureStored = ((uint32)(*(uint8*)(TempSignature)) << 24u);
                    FlsTst_BlockFgndInfo[MemBlockIndex].SignatureStored +=
                        ((uint32)(*(uint8*)(TempSignature + 1U)) << 16u);
                    FlsTst_BlockFgndInfo[MemBlockIndex].SignatureStored +=
                        ((uint32)(*(uint8*)(TempSignature + 2U)) << 8u);
                    FlsTst_BlockFgndInfo[MemBlockIndex].SignatureStored += (uint32)(*(uint8*)(TempSignature + 3U));
                    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */
                }
                FlsTst_BlockFgndInfo[MemBlockIndex].SignatueCalculated = 0u;
                FlsTst_BlockFgndInfo[MemBlockIndex].TestResult = FLSTST_RESULT_NOT_TESTED;
            }
#endif

#if (STD_ON == FLSTST_INIT_ECC)
            REG_WRITE8(FLASH_FERCNFG_ADDR32, FLASH_FERCNFG_DFDIE_U8);
#endif
            FlsTst_Module.State = FLSTST_INIT;
            FlsTst_Module.ErrorInfo.ErrorBlockID = 0xFFu;
            FlsTst_Module.ErrorInfo.Algorithm = FLSTST_16BIT_CRC;
            FlsTst_Module.ErrorInfo.SignatureResult = 0U;
            FlsTst_Module.UserCallBack = ConfigPtr->FlsTstUserCallBack;
            FlsTst_Module.IntervalID = 0U;
            FlsTst_Module.BgndResult = FLSTST_RESULT_NOT_TESTED;
            FlsTst_Module.FgndResult = FLSTST_NOT_TESTED;
            SchM_Exit_FlsTst_RAMTST_EXCLUSIVE_AREA();
        }
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
/*************************************************************************/
/*
 * Brief               Service for Flash Test De-Initialization.
 * ServiceId           0x01
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
/*************************************************************************/
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_DeInit(void)
{
    uint8 MemBlockIndex;

    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_DEINIT_ID, FLSTST_E_STATE_FAILURE);
    }
    SchM_Enter_FlsTst_RAMTST_EXCLUSIVE_AREA();
#if (0 != FLSTST_BGND_BLOCK_NUM)
#if (1u < FLSTST_BGND_BLOCK_NUM)
    for (MemBlockIndex = 0; MemBlockIndex < FLSTST_BGND_BLOCK_NUM; MemBlockIndex++)
#else
    MemBlockIndex = 0;
#endif /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
    {
        FlsTst_BlockBgndInfo[MemBlockIndex].MemoryBlockID = 0u;
        FlsTst_BlockBgndInfo[MemBlockIndex].TestAlgorithm = FLSTST_16BIT_CRC;
        FlsTst_BlockBgndInfo[MemBlockIndex].MemBlcokStartAddr = 0u;
        FlsTst_BlockBgndInfo[MemBlockIndex].MemBlcokLength = 0u;
        FlsTst_BlockBgndInfo[MemBlockIndex].SignatureStored = 0u;
        FlsTst_BlockBgndInfo[MemBlockIndex].SignatueCalculated = 0u;
        FlsTst_BlockBgndInfo[MemBlockIndex].TestResult = FLSTST_RESULT_NOT_TESTED;
    }
#endif

#if (0 != FLSTST_FGND_BLOCK_NUM)
#if (1u < FLSTST_FGND_BLOCK_NUM)
    for (MemBlockIndex = 0; MemBlockIndex < FLSTST_FGND_BLOCK_NUM; MemBlockIndex++)
#else
    MemBlockIndex = 0;
#endif /* #if (1u < FLSTST_FGND_BLOCK_NUM) */
    {
        FlsTst_BlockFgndInfo[MemBlockIndex].MemoryBlockID = 0u;
        FlsTst_BlockFgndInfo[MemBlockIndex].TestAlgorithm = FLSTST_16BIT_CRC;
        FlsTst_BlockFgndInfo[MemBlockIndex].MemBlcokStartAddr = 0u;
        FlsTst_BlockFgndInfo[MemBlockIndex].MemBlcokLength = 0u;
        FlsTst_BlockFgndInfo[MemBlockIndex].SignatureStored = 0u;
        FlsTst_BlockFgndInfo[MemBlockIndex].SignatueCalculated = 0u;
        FlsTst_BlockFgndInfo[MemBlockIndex].TestResult = FLSTST_RESULT_NOT_TESTED;
    }
#endif
#if (STD_ON == FLSTST_INIT_ECC)
    REG_WRITE8(FLASH_FERCNFG_ADDR32, 0u);
#endif
    FlsTst_Module.State = FLSTST_UNINIT;
    SchM_Exit_FlsTst_RAMTST_EXCLUSIVE_AREA();
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

/*************************************************************************/
/*
 * Brief               Service for executing foreground Flash Test.
 * ServiceId           0x02
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      FgndBlockId: Number of the foreground test to be
 *                     executed. This is dependent on configuration.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 *                       E_OK: Foreground test processed
 *                       E_NOT_OK: Foreground test not accepte
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_START_FGND_API) && (0 != FLSTST_FGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
Std_ReturnType FlsTst_StartFgnd(FlsTst_BlockIdFgndType FgndBlockId)
{
    Std_ReturnType testResult = E_NOT_OK;
    uint32 CurentCRC = 0;

    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_UNINIT);
    }
    else
    {
        if (FgndBlockId >= FLSTST_FGND_BLOCK_NUM)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            testResult = FlsTst_StartFgndInterTest(&FlsTst_BlockFgndInfo[FgndBlockId]);
        }
    }
    return testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_START_FGND_API */

/*************************************************************************/
/*
 * Brief               Service for aborting the Flash Test.
 * ServiceId           0x03
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if (0U != FLSTST_BGND_BLOCK_NUM)
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_Abort(void)
{
    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_ABORT_ID, FLSTST_E_UNINIT);
    }
    else if (FLSTST_ABORTED == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_ABORT_ID, FLSTST_E_STATE_FAILURE);
    }
    else
    {
        FlsTst_Module.State = FLSTST_ABORTED;
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif
/*************************************************************************/
/*
 * Brief               Service for suspending current operation of the
 *                     Flash Test, until FlsTst_Resume is called.
 * ServiceId           0x04
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_SUSPEND_RESUME_API) && (0U != FLSTST_BGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_Suspend(void)
{
    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_SUSPEND_ID, FLSTST_E_UNINIT);
    }
    else if (FLSTST_ABORTED == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_SUSPEND_ID, FLSTST_E_STATE_FAILURE);
    }
    else
    {
        FlsTst_Module.State = FLSTST_SUSPENDED;
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_SUSPEND_RESUME_API */

/*************************************************************************/
/*
 * Brief               Service for continuing the Flash Test at the point
 *                     it was suspended.
 * ServiceId           0x05
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_SUSPEND_RESUME_API) && (0U != FLSTST_BGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_Resume(void)
{
    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_RESUME_ID, FLSTST_E_UNINIT);
    }
    else if (FLSTST_SUSPENDED != FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_RESUME_ID, FLSTST_E_STATE_FAILURE);
    }
    else
    {
        FlsTst_Module.State = FLSTST_RUNNING;
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_SUSPEND_RESUME_API */
/*************************************************************************/
/*
 * Brief               Service for continuing the Flash Test at the point
 *                     it was suspended.
 * ServiceId           0x06
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              FlsTst_StateType
 *                  FLSTST_UNINIT:
 *                     The Flash Test is not initialized or not usable.
 *                  FLSTST_INIT:
 *                     The Flash Test is initialized and ready to be started.
 *                  FLSTST_RUNNING:
 *                     The Flash Test is currently running.
 *                  FLSTST_ABORTED锛�
 *                     The Flash Test is aborted.
 *                  FLSTST_SUSPENDED:
 *                     The Flash Test is waiting to be resumed or is waiting
 *                     to start forground mode test.
 * PreCondition        None
 */
/*************************************************************************/
#if (STD_ON == FLSTST_GET_CURRENT_STATE_API)
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
FlsTst_StateType FlsTst_GetCurrentState(void)
{
    return FlsTst_Module.State;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_GET_CURRENT_STATE_API */
/*************************************************************************/
/*
 * Brief               Service returns the Background Flash Test result.
 * ServiceId           0x07
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              FlsTst_TestResultBgndType
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_GET_TEST_RESULT_BGND_API) && (0u != FLSTST_BGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
FlsTst_TestResultBgndType FlsTst_GetTestResultBgnd(void)
{
    FlsTst_TestResultBgndType TestResultBgnd;

    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_GETTESTRESULTBGND_ID, FLSTST_E_UNINIT);
    }
    TestResultBgnd.FlsTstIntervalID = FlsTst_Module.IntervalID;
    TestResultBgnd.result = FlsTst_Module.BgndResult;

    return TestResultBgnd;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_GET_TEST_RESULT_BGND_API */

/*************************************************************************/
/*
 * Brief               Service returns the Foreground Flash Test result.
 * ServiceId           0x0f
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              FlsTst_TestResultFgndType
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_GET_TEST_RESULT_FGND_API) && (0u != FLSTST_FGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
FlsTst_TestResultFgndType FlsTst_GetTestResultFgnd(void)
{
    FlsTst_TestResultFgndType TestResultFgnd;

    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_GETTESTRESULTFGND_ID, FLSTST_E_UNINIT);
    }
    TestResultFgnd = FlsTst_Module.FgndResult;

    return TestResultFgnd;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_GET_TEST_RESULT_FGND_API */
/*************************************************************************/
/*
 * Brief               Service returns the version information of this module.
 * ServiceId           0x08
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     versioninfo:Pointer to where to store the version
 *                     information of this module.
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if (STD_ON == FLSTST_VERSION_INFO_API)
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_GETVERSIONINFO_ID, FLSTST_E_UNINIT);
    }
    else if (NULL_PTR == versionInfo)
    {
        FLSTST_DET_REPORTERROR(FLSTST_GETVERSIONINFO_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        (versionInfo)->vendorID = (uint16)FLSTST_VENDOR_ID;
        (versionInfo)->moduleID = (uint8)FLSTST_MODULE_ID;
        (versionInfo)->sw_major_version = (uint8)FLSTST_C_AR_MAJOR_VERSION;
        (versionInfo)->sw_minor_version = (uint8)FLSTST_C_AR_MINOR_VERSION;
        (versionInfo)->sw_patch_version = (uint8)FLSTST_C_AR_PATCH_VERSION;
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_VERSION_INFO_API */

/*************************************************************************/
/*
 * Brief               Service returns the Flash Test result in background
 *                     mode.
 * ServiceId           0x09
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              FlsTst_TestSignatureBgndType
 * PreCondition        None
 */
/*************************************************************************/

#if ((STD_ON == FLSTST_GET_TEST_SIGNATURE_BGND_API) && (0u != FLSTST_BGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
FlsTst_TestSignatureBgndType FlsTst_GetTestSignatureBgnd(void)
{
    FlsTst_TestSignatureBgndType TestSignatureBgnd;
    FlsTst_BlockIdType MemBlockIndex;

    TestSignatureBgnd.BgndSignature = 0;
    TestSignatureBgnd.FlsTstIntervalID = 0;
    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_UNINIT);
    }
    else
    {
#if (1u < FLSTST_BGND_BLOCK_NUM)
        for (MemBlockIndex = 0; MemBlockIndex < FLSTST_BGND_BLOCK_NUM; MemBlockIndex++)
#else
        MemBlockIndex = 0;
#endif /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
        {
            if (FLSTST_RESULT_OK == FlsTst_BlockBgndInfo[MemBlockIndex].TestResult)
            {
                /* sum of Signature of all blocks */
#if (1u < FLSTST_BGND_BLOCK_NUM)
                TestSignatureBgnd.BgndSignature += FlsTst_BlockBgndInfo[MemBlockIndex].SignatueCalculated;
#else
                TestSignatureBgnd.BgndSignature = FlsTst_BlockBgndInfo[MemBlockIndex].SignatueCalculated;
#endif /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
            }
            else
            {
                /*empty*/
            }
        }
        TestSignatureBgnd.FlsTstIntervalID = FlsTst_Module.IntervalID;
    }
    return TestSignatureBgnd;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_GET_TEST_SIGNATURE_BGND_API */

/*************************************************************************/
/*
 * Brief               Service returns the Flash Test result in background
 *                     mode.
 * ServiceId           0x0a
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              FlsTst_TestSignatureFgndType
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_GET_TEST_SIGNATURE_FGND_API) && (0u != FLSTST_FGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
FlsTst_TestSignatureFgndType FlsTst_GetTestSignatureFgnd(void)
{
    FlsTst_TestSignatureFgndType TestSignatureFgnd;
    FlsTst_BlockIdType MemBlockIndex;

    TestSignatureFgnd.FgndSignature = 0;
    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_GETTESTSIGNATUREFGND_ID, FLSTST_E_UNINIT);
    }
    else
    {
#if (1u < FLSTST_BGND_BLOCK_NUM)
        for (MemBlockIndex = 0; MemBlockIndex < FLSTST_BGND_BLOCK_NUM; MemBlockIndex++)
#else
        MemBlockIndex = 0;
#endif /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
        {
            if (FLSTST_RESULT_OK == FlsTst_BlockFgndInfo[MemBlockIndex].TestResult)
            {
                /* sum of Signature of all blocks */
#if (1u < FLSTST_BGND_BLOCK_NUM)
                TestSignatureFgnd.FgndSignature += FlsTst_BlockFgndInfo[MemBlockIndex].SignatueCalculated;
#else
                TestSignatureFgnd.FgndSignature = FlsTst_BlockFgndInfo[MemBlockIndex].SignatueCalculated;
#endif /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
            }
            else
            {
            }
        }
    }
    return TestSignatureFgnd;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_GET_TEST_SIGNATURE_FGND_API */

/*************************************************************************/
/*
 * Brief               Service returns error detais monitored from the
 *                     Flash module.
 * ServiceId           0x0b
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              FlsTst_ErrorDetailsType
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_GET_ERRORD_ETAILS_API) && ((0U != FLSTST_BGND_BLOCK_NUM) || (0U != FLSTST_FGND_BLOCK_NUM)))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
FlsTst_ErrorDetailsType FlsTst_GetErrorDetails(void)
{
    FlsTst_ErrorDetailsType ErrDetails;

    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_GETERRORDETAILS_ID, FLSTST_E_UNINIT);
    }
    ErrDetails = FlsTst_Module.ErrorInfo;
    return ErrDetails;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_GET_ERRORD_ETAILS_API */

/*************************************************************************/
/*
 * Brief               Service executes a test of ECC hardware. This is
 *                     only applicable in case the hardware provices
 *                     such functionality.
 * ServiceId           0x0c
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * PreCondition        None
 */
/*************************************************************************/
#if ((STD_ON == FLSTST_TEST_ECC_API) && ((0U != FLSTST_BGND_BLOCK_NUM) || (0U != FLSTST_FGND_BLOCK_NUM)))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
Std_ReturnType FlsTst_TestEcc(void)
{
    Std_ReturnType Result = E_NOT_OK;

    if (FLSTST_UNINIT == FlsTst_Module.State)
    {
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_UNINIT);
    }
    /* do not supprort ECC test*/
    return Result;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_TEST_ECC_API */
/*************************************************************************/
/*
 * Brief               Service for executing the Flash Test in background
 *                     mode.
 * ServiceId           0x0d
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if (0U != FLSTST_BGND_BLOCK_NUM)
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
void FlsTst_MainFunction(void)
{
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
    static uint32 FlsTst_SuspendCounter;
#endif
    FlsTst_GetResource();
    switch (FlsTst_Module.State)
    {
    case FLSTST_UNINIT:
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_UNINIT);
        break;

    case FLSTST_INIT:
        /*Auto start*/
        FlsTst_Module.State = FLSTST_RUNNING;
        if (FLSTST_RESULT_NOT_TESTED != FlsTst_Module.BgndResult)
        {
            FlsTst_Module.IntervalID++;
        }
        if (FlsTst_Module.IntervalID > FLSTST_TEST_INTERVALID_END_VALUE)
        {
            FlsTst_Module.IntervalID = 0u;
        }
        FlsTst_CopyBlockInfo(0u);
        FlsTst_InterTest();
        break;

    case FLSTST_RUNNING:
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
        /* clear suspend counter*/
        FlsTst_SuspendCounter = 0;
#endif
        /*Continue Calc*/
        FlsTst_InterTest();
        break;

    case FLSTST_ABORTED:
        /*do nothing*/
        break;

    case FLSTST_SUSPENDED:
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
        /*suspend overtime check*/
        FlsTst_SuspendCounter++;
        if (FlsTst_SuspendCounter > 100U)
        {
            /* suspend time is too long */
            FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_SUSPEND_OVERTIME);
        }
#endif
        break;

    default:
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_PARAM_INVALID);
        break;
    }
    FlsTst_FreeResource();
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif
/*************************************************************************/
/*
 * Brief               The function FlsTst_TestCompletedNotification shall be called
 *                     every time when a complete test cycle had been
 *                     tested.
 * ServiceId           0x0e
 * Sync/Async          Synchronous
 * Reentrancy          Don't care
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if (0u != FLSTST_BGND_BLOCK_NUM)
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
#if (STD_ON == FLSTST_COMPLETED_NOTIFY_SUPPORT)
static void FlsTst_TestCompleted(void)
{
    if (NULL_PTR != FlsTst_Module.UserCallBack)
    {
        FlsTst_Module.UserCallBack();
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif /* STD_ON == FLSTST_COMPLETED_NOTIFY_SUPPORT */

/*************************************************************************/
/*
 * Brief               Internel function to Copy information from
 *                     FlsTst_BlockBgndInfo to FlsTst_CurRunning.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      FlsTstBlockID: Block ID in background test.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
/*************************************************************************/
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static void FlsTst_CopyBlockInfo(FlsTst_BlockIdType FlsTstBlockID)
{
    if (FlsTstBlockID >= FLSTST_BGND_BLOCK_NUM)
    {
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_PARAM_INVALID);
    }
    else
    {
        SchM_Enter_FlsTst_RAMTST_EXCLUSIVE_AREA();
        FlsTst_CurRunning.FirstFlag = 0u;
        FlsTst_CurRunning.CalcResult = 0;
        FlsTst_CurRunning.CurBlockID = FlsTst_BlockBgndInfo[FlsTstBlockID].MemoryBlockID;
        FlsTst_CurRunning.TestAddr = FlsTst_BlockBgndInfo[FlsTstBlockID].MemBlcokStartAddr;
        FlsTst_CurRunning.TestLength = FlsTst_BlockBgndInfo[FlsTstBlockID].MemBlcokLength;
        FlsTst_CurRunning.TestAlgorithm = FlsTst_BlockBgndInfo[FlsTstBlockID].TestAlgorithm;
        SchM_Exit_FlsTst_RAMTST_EXCLUSIVE_AREA();
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
        FlsTst_ParamChecksum = (uint32)FlsTst_CurRunning.TestAddr + (uint32)FlsTst_CurRunning.TestLength
                               + (uint32)FlsTst_CurRunning.CalcResult;
#endif
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

/*************************************************************************/
/*
 * Brief               Internel function in bcakground test,be called when
 *                     a memmory block test finished.  another block wil
 *                     to be tested in current test intervel
 *
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
/*************************************************************************/
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static void FlsTst_BlockTestFinish(void)
{
    FlsTst_BlockIdType BlockID = FlsTst_CurRunning.CurBlockID;
    FlsTst_BlockIdType MemBlockIndex;

    uint8 l_ErrorBlock = 0;
    if (BlockID > (FLSTST_BGND_BLOCK_NUM - 1U))
    {
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_PARAM_INVALID);
    }
#if (1u < FLSTST_BGND_BLOCK_NUM)
    else if (BlockID < (FLSTST_BGND_BLOCK_NUM - 1U))
    {
        FlsTst_BlockBgndInfo[BlockID].SignatueCalculated = FlsTst_CurRunning.CalcResult;
        if (FlsTst_BlockBgndInfo[BlockID].SignatueCalculated == FlsTst_BlockBgndInfo[BlockID].SignatureStored)
        {
            FlsTst_BlockBgndInfo[BlockID].TestResult = FLSTST_RESULT_OK;
        }
        else
        {
            FlsTst_Module.BgndResult = FLSTST_RESULT_NOT_OK;
            FlsTst_BlockBgndInfo[BlockID].TestResult = FLSTST_RESULT_NOT_OK;
            /*at least one block test failed*/
#if FLSTST_DEM_FLSTST_E_FLSTST_FAILURE
            Dem_ReportErrorStatus(FLSTST_E_FLSTST_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
        }
        /* Another block need to be tested*/
        BlockID++;
        FlsTst_CopyBlockInfo(BlockID);
    }
#endif   /* #if (1u < FLSTST_BGND_BLOCK_NUM) */
    else /*the last block test finished*/
    {
        FlsTst_BlockBgndInfo[BlockID].SignatueCalculated = FlsTst_CurRunning.CalcResult;
        if (FlsTst_BlockBgndInfo[BlockID].SignatueCalculated == FlsTst_BlockBgndInfo[BlockID].SignatureStored)
        {
            FlsTst_BlockBgndInfo[BlockID].TestResult = FLSTST_RESULT_OK;
        }
        else
        {
            FlsTst_Module.BgndResult = FLSTST_RESULT_NOT_OK;
            FlsTst_BlockBgndInfo[BlockID].TestResult = FLSTST_RESULT_NOT_OK;
            /*at least one block test failed*/
#if FLSTST_DEM_FLSTST_E_FLSTST_FAILURE
            Dem_ReportErrorStatus(FLSTST_E_FLSTST_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
        }
        /*no more block need to be tested, current test interval finished.*/

#if (1u < FLSTST_BGND_BLOCK_NUM)
        for (MemBlockIndex = 0U; MemBlockIndex < FLSTST_BGND_BLOCK_NUM; MemBlockIndex++)
#else
        MemBlockIndex = 0;
#endif /*#if (1u < FLSTST_BGND_BLOCK_NUM)*/
        {
            if (FLSTST_RESULT_NOT_OK == FlsTst_BlockBgndInfo[MemBlockIndex].TestResult)
            {
                l_ErrorBlock = 1U;
                FlsTst_Module.ErrorInfo.ErrorBlockID = MemBlockIndex;
                FlsTst_Module.ErrorInfo.Algorithm = FlsTst_BlockBgndInfo[MemBlockIndex].TestAlgorithm;
                FlsTst_Module.ErrorInfo.SignatureResult = FlsTst_BlockBgndInfo[MemBlockIndex].SignatueCalculated;
#if (1u < FLSTST_BGND_BLOCK_NUM)
                break;
#endif /*#if (1u < FLSTST_BGND_BLOCK_NUM)*/
            }
        }

        if (0U == l_ErrorBlock)
        {
            FlsTst_Module.BgndResult = FLSTST_RESULT_OK;
#if FLSTST_DEM_FLSTST_E_FLSTST_FAILURE
            Dem_ReportErrorStatus(FLSTST_E_FLSTST_FAILURE, DEM_EVENT_STATUS_PASSED);
#endif
        }
        else
        {
            /* empty */
        }
        FlsTst_Module.State = FLSTST_INIT;
#if (STD_ON == FLSTST_COMPLETED_NOTIFY_SUPPORT)
        FlsTst_TestCompleted();
#endif /* STD_ON == FLSTST_COMPLETED_NOTIFY_SUPPORT */
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

/*************************************************************************/
/*
 * Brief               Internel function in bcakground test, called in one
 *                     Flstst_MainFunctiuon to calculating Flash cells
 *                     in background mode *
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
/*************************************************************************/
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static void FlsTst_InterTest(void)
{
    uint32 Cycletimes;
    uint32 l_Counter;

    if ((FlsTst_CurRunning.TestLength == 0U) && (FLSTST_RUNNING == FlsTst_Module.State))
    {
        /*Current Block Calc Finish*/
        FlsTst_BlockTestFinish();
    }
    else
    {
        /* First calculate CRC*/
        if ((FLSTST_TESTCELLS_NUM * FLSTST_TESTCELL_LENGTH_ATOMIC) < FlsTst_CurRunning.TestLength)
        {
#if (1u < FLSTST_TESTCELLS_NUM)
            for (l_Counter = 0; l_Counter < FLSTST_TESTCELLS_NUM; l_Counter++)
#endif /* #if (1u < FLSTST_TESTCELLS_NUM) */
            {
                if (FLSTST_RUNNING == FlsTst_Module.State)
                {
                    FlsTst_CalcAtomic();
                }
                else if ((FLSTST_SUSPENDED == FlsTst_Module.State) || (FLSTST_ABORTED == FlsTst_Module.State))
                {
#if (1u < FLSTST_TESTCELLS_NUM)
                    break;
#endif /* #if (1u < FLSTST_TESTCELLS_NUM) */
                }
                else
                {
                    FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_STATE_FAILURE);
                }

                if (0U == FlsTst_CurRunning.TestLength)
                {
#if (1u < FLSTST_TESTCELLS_NUM)
                    break;
#endif /* #if (1u < FLSTST_TESTCELLS_NUM) */
                }
            }
        }
        else /* Length smaller than FLSTST_NUMOFTESTEDCELLS,but not 0 */
        {
            Cycletimes = FlsTst_CurRunning.TestLength / FLSTST_TESTCELL_LENGTH_ATOMIC;
            Cycletimes = Cycletimes + 1U;
            for (l_Counter = 0U; l_Counter < Cycletimes; l_Counter++)
            {
                if (FLSTST_RUNNING == FlsTst_Module.State)
                {
                    FlsTst_CalcAtomic();
                }
                else if ((FLSTST_SUSPENDED == FlsTst_Module.State) || (FLSTST_ABORTED == FlsTst_Module.State))
                {
                    break;
                }
                else
                {
                    FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_STATE_FAILURE);
                }

                if (0U == FlsTst_CurRunning.TestLength)
                {
                    break;
                }
            }
        }
    }
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

/*************************************************************************/
/*
 * Brief               Internel function in bcakground test, called to
 *                     calculating Flash cell once.
 *                     in background mode.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
/*************************************************************************/
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static void FlsTst_CalcAtomic(void)
{
    FlsTst_LengthType l_CrcLength;
    boolean l_FirstTimeCalc;

#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
    if ((uint32)FlsTst_ParamChecksum
        != ((uint32)FlsTst_CurRunning.TestAddr + (uint32)FlsTst_CurRunning.TestLength
            + (uint32)FlsTst_CurRunning.CalcResult))
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_DATA_CRRUPTED);
        /* Data of FlsTst_CurRunning is corrupted */
    }
#endif /* STD_ON == FLSTST_EXTEND_SAFETY_MODE */
    SchM_Enter_FlsTst_RAMTST_EXCLUSIVE_AREA();
    /*if a block was First time to calculate CRC*/
    if (0U == FlsTst_CurRunning.FirstFlag)
    {
        FlsTst_CurRunning.FirstFlag = 1U;
        l_FirstTimeCalc = TRUE;
    }
    else
    {
        l_FirstTimeCalc = FALSE;
    }

    if ((FLSTST_TESTCELL_LENGTH_ATOMIC) < FlsTst_CurRunning.TestLength)
    {
        l_CrcLength = FLSTST_TESTCELL_LENGTH_ATOMIC;
    }
    else
    {
        l_CrcLength = FlsTst_CurRunning.TestLength;
    }

    switch (FlsTst_CurRunning.TestAlgorithm)
    {
        /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
    case FLSTST_16BIT_CRC:
        FlsTst_CurRunning.CalcResult = (uint32)Crc_CalculateCRC16(
            (uint8*)FlsTst_CurRunning.TestAddr,
            l_CrcLength,
            (uint16)FlsTst_CurRunning.CalcResult,
            l_FirstTimeCalc);
        break;

    case FLSTST_32BIT_CRC:
        FlsTst_CurRunning.CalcResult = (uint32)Crc_CalculateCRC32(
            (uint8*)FlsTst_CurRunning.TestAddr,
            l_CrcLength,
            (uint32)FlsTst_CurRunning.CalcResult,
            l_FirstTimeCalc);
        break;

    case FLSTST_8BIT_CRC:
        FlsTst_CurRunning.CalcResult = (uint32)Crc_CalculateCRC8(
            (uint8*)FlsTst_CurRunning.TestAddr,
            l_CrcLength,
            (uint8)FlsTst_CurRunning.CalcResult,
            l_FirstTimeCalc);
        break;

    case FLSTST_CHECKSUM:
        FlsTst_CurRunning.CalcResult = (uint32)FlsTst_CheckSum(
            (uint8*)FlsTst_CurRunning.TestAddr,
            l_CrcLength,
            (uint32)FlsTst_CurRunning.CalcResult,
            l_FirstTimeCalc);
        break;
        /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

    case FLSTST_DUPLICATED_MEMORY:
        /* do not support in background test*/
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_PARAM_INVALID);
        break;

    case FLSTST_ECC:
        /* do not support in background test*/
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_PARAM_INVALID);
        break;

    default:
        /* do not support other Algorithm. */
        FLSTST_DET_REPORTERROR(FLSTST_MAINFUNCTION_ID, FLSTST_E_PARAM_INVALID);
        break;
    }
    FlsTst_CurRunning.TestLength -= l_CrcLength;
    FlsTst_CurRunning.TestAddr += l_CrcLength;
    SchM_Exit_FlsTst_RAMTST_EXCLUSIVE_AREA();
#if (STD_ON == FLSTST_EXTEND_SAFETY_MODE)
    FlsTst_ParamChecksum = (uint32)FlsTst_CurRunning.TestAddr + (uint32)FlsTst_CurRunning.TestLength
                           + (uint32)FlsTst_CurRunning.CalcResult;
    /* Data of FlsTst_CurRunning is corrupted */
#endif /* STD_ON == FLSTST_EXTEND_SAFETY_MODE */
    return;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif
/*************************************************************************/
/*
 * Brief               The function FlsTst_StartFgndInterTest shall be
 *                     called by FlsTst_StartFgnd.+
 *                     tested.
 * ServiceId           None, Interel Function
 * Sync/Async          Synchronous
 * Reentrancy          Don't care
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 */
/*************************************************************************/
#if (0u != FLSTST_FGND_BLOCK_NUM)
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_StartFgndInterTest(FlsTst_BlockInfoType* BlockInfoPtr)
{
    Std_ReturnType testResult = E_NOT_OK;
    FlsTst_AlgorithmType Algorithm;
    FlsTst_BlockIdType MemBlockIndex;
    uint8 l_BlockError = 0;
    FlsTst_StateType BgndState;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        BgndState = FlsTst_Module.State;
        FlsTst_Module.State = FLSTST_RUNNING;
        Algorithm = BlockInfoPtr->TestAlgorithm;
        switch (Algorithm)
        {
        case FLSTST_16BIT_CRC:
            testResult = FlsTst_CRC16Fgnd(BlockInfoPtr);
            break;

        case FLSTST_32BIT_CRC:
            testResult = FlsTst_CRC32Fgnd(BlockInfoPtr);
            break;

        case FLSTST_8BIT_CRC:
            testResult = FlsTst_CRC8Fgnd(BlockInfoPtr);
            break;

        case FLSTST_CHECKSUM:
            testResult = FlsTst_ChecksumFgnd(BlockInfoPtr);
            break;

        case FLSTST_DUPLICATED_MEMORY:
            testResult = FlsTst_DuplicatedMemoryFgnd(BlockInfoPtr);
            break;

        case FLSTST_ECC:
            testResult = FlsTst_ECCTestFgnd(BlockInfoPtr);
            break;

        default:
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
            testResult = E_NOT_OK;
            break;
        }

        if (FLSTST_RESULT_NOT_OK == BlockInfoPtr->TestResult)
        {
            /*copy error details info*/
            FlsTst_Module.ErrorInfo.ErrorBlockID = BlockInfoPtr->MemoryBlockID;
            FlsTst_Module.ErrorInfo.Algorithm = BlockInfoPtr->TestAlgorithm;
            FlsTst_Module.ErrorInfo.SignatureResult = BlockInfoPtr->SignatueCalculated;
#if FLSTST_DEM_FLSTST_E_FLSTST_FAILURE
            Dem_ReportErrorStatus(FLSTST_E_FLSTST_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
        }

#if (1u < FLSTST_BGND_BLOCK_NUM)
        for (MemBlockIndex = 0; MemBlockIndex < FLSTST_BGND_BLOCK_NUM; MemBlockIndex++)
#else
        MemBlockIndex = 0;
#endif /*#if (1u < FLSTST_BGND_BLOCK_NUM)*/
        {
            if (FLSTST_RESULT_NOT_OK == FlsTst_BlockFgndInfo[MemBlockIndex].TestResult)
            {
                l_BlockError++;
                FlsTst_Module.FgndResult = FLSTST_NOT_OK;
            }
            else if (FLSTST_RESULT_NOT_TESTED == FlsTst_BlockFgndInfo[MemBlockIndex].TestResult)
            {
                l_BlockError++;
            }
            else
            {
                /* if all block test successfully, l_BlockError should be 0*/
            }
        }
        if (0U == l_BlockError)
        {
            FlsTst_Module.FgndResult = FLSTST_OK;
        }
        if (FLSTST_RUNNING == FlsTst_Module.State)
        {
            FlsTst_Module.State = BgndState;
        }
    }
    return testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_CRC32Fgnd(FlsTst_BlockInfoType* BlockInfoPtr)
{
    FlsTst_AddressType TestAddr;
    FlsTst_LengthType TestLength;
    FlsTst_AlgorithmType Algorithm;
    FlsTst_SignatureType SignatureResult;
    Std_ReturnType l_testResult = E_NOT_OK;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        TestAddr = BlockInfoPtr->MemBlcokStartAddr;
        TestLength = BlockInfoPtr->MemBlcokLength;
        Algorithm = BlockInfoPtr->TestAlgorithm;
        SignatureResult = 0;

        if (FLSTST_32BIT_CRC != Algorithm)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            /* if test method changes,Modify the code below */
            /* Use CRC32  */
            /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
            SignatureResult = (uint32)Crc_CalculateCRC32((uint8*)TestAddr, TestLength, (uint32)SignatureResult, TRUE);
            /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

            BlockInfoPtr->SignatueCalculated = SignatureResult;
            if (BlockInfoPtr->SignatureStored == BlockInfoPtr->SignatueCalculated)
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_OK;
            }
            else
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_NOT_OK;
            }
            l_testResult = E_OK;
        }
    }

    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_CRC16Fgnd(FlsTst_BlockInfoType* BlockInfoPtr)
{
    FlsTst_AddressType TestAddr;
    FlsTst_LengthType TestLength;
    FlsTst_AlgorithmType Algorithm;
    FlsTst_SignatureType SignatureResult;
    Std_ReturnType l_testResult = E_NOT_OK;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        TestAddr = BlockInfoPtr->MemBlcokStartAddr;
        TestLength = BlockInfoPtr->MemBlcokLength;
        Algorithm = BlockInfoPtr->TestAlgorithm;
        SignatureResult = 0;

        if (FLSTST_16BIT_CRC != Algorithm)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            /* if test method changes,Modify the code below */
            /* Use CRC16  */
            /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
            SignatureResult = (uint32)Crc_CalculateCRC16((uint8*)TestAddr, TestLength, (uint16)SignatureResult, TRUE);
            /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

            BlockInfoPtr->SignatueCalculated = SignatureResult;
            if (BlockInfoPtr->SignatureStored == BlockInfoPtr->SignatueCalculated)
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_OK;
            }
            else
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_NOT_OK;
            }
            l_testResult = E_OK;
        }
    }

    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_CRC8Fgnd(FlsTst_BlockInfoType* BlockInfoPtr)
{
    FlsTst_AddressType TestAddr;
    FlsTst_LengthType TestLength;
    FlsTst_AlgorithmType Algorithm;
    FlsTst_SignatureType SignatureResult;
    Std_ReturnType l_testResult = E_NOT_OK;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {

        TestAddr = BlockInfoPtr->MemBlcokStartAddr;
        TestLength = BlockInfoPtr->MemBlcokLength;
        Algorithm = BlockInfoPtr->TestAlgorithm;
        SignatureResult = 0;

        if (FLSTST_8BIT_CRC != Algorithm)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            /* if test method changes,Modify the code below */
            /* Use CRC8  */
            /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
            SignatureResult = Crc_CalculateCRC8((uint8*)TestAddr, TestLength, (uint8)SignatureResult, TRUE);
            /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

            BlockInfoPtr->SignatueCalculated = SignatureResult;
            if (BlockInfoPtr->SignatureStored == BlockInfoPtr->SignatueCalculated)
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_OK;
            }
            else
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_NOT_OK;
            }
            l_testResult = E_OK;
        }
    }
    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_DuplicatedMemoryFgnd(FlsTst_BlockInfoType* BlockInfoPtr)
{
    FlsTst_AddressType TestAddr;
    FlsTst_LengthType TestLength;
    FlsTst_AlgorithmType Algorithm;
    FlsTst_AddressType DuplicateMemoryAddr;
    Std_ReturnType l_testResult = E_NOT_OK;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        TestAddr = BlockInfoPtr->MemBlcokStartAddr;
        TestLength = BlockInfoPtr->MemBlcokLength;
        Algorithm = BlockInfoPtr->TestAlgorithm;
        /*duplicate memory address*/
        DuplicateMemoryAddr = (FlsTst_AddressType)BlockInfoPtr->SignatureStored;

        if (FLSTST_DUPLICATED_MEMORY != Algorithm)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            /* if test method changes,Modify the code below */
            /* FlsTst Duplicated Memory  Foreground  test */
            /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
            l_testResult = FlsTst_MemCompare((uint8*)TestAddr, (uint8*)DuplicateMemoryAddr, TestLength);
            /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

            if ((Std_ReturnType)E_OK == l_testResult)
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_OK;
            }
            else
            {
                BlockInfoPtr->TestResult = FLSTST_RESULT_NOT_OK;
            }
        }
    }
    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_ChecksumFgnd(FlsTst_BlockInfoType* BlockInfoPtr)
{
    FlsTst_AddressType TestAddr;
    FlsTst_LengthType TestLength;
    FlsTst_AlgorithmType Algorithm;
    FlsTst_SignatureType SignatureResult;
    Std_ReturnType l_testResult = E_NOT_OK;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        TestAddr = BlockInfoPtr->MemBlcokStartAddr;
        TestLength = BlockInfoPtr->MemBlcokLength;
        Algorithm = BlockInfoPtr->TestAlgorithm;
        SignatureResult = 0U;
        if (FLSTST_CHECKSUM != Algorithm)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            /* empty */
        }

        /* if test method changes,Modify the code below */
        /* Use CRC8  */
        /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
        SignatureResult = FlsTst_CheckSum((uint8*)TestAddr, TestLength, SignatureResult, TRUE);
        /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

        BlockInfoPtr->SignatueCalculated = SignatureResult;
        if (BlockInfoPtr->SignatureStored == BlockInfoPtr->SignatueCalculated)
        {
            BlockInfoPtr->TestResult = FLSTST_RESULT_OK;
        }
        else
        {
            BlockInfoPtr->TestResult = FLSTST_RESULT_NOT_OK;
        }
        l_testResult = E_OK;
    }
    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"

#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_ECCTestFgnd(FlsTst_BlockInfoType* BlockInfoPtr)
{

    Std_ReturnType l_testResult = E_NOT_OK;
    FlsTst_AlgorithmType Algorithm;

    if (NULL_PTR == BlockInfoPtr)
    {
        FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_POINTER);
    }
    else
    {
        Algorithm = BlockInfoPtr->TestAlgorithm;
        if (FLSTST_ECC != Algorithm)
        {
            FLSTST_DET_REPORTERROR(FLSTST_STARTFGND_ID, FLSTST_E_PARAM_INVALID);
        }
        else
        {
            /* empty */
        }

        BlockInfoPtr->TestResult = FLSTST_RESULT_NOT_OK;
        /* S32K146 do not support Flash ECC test function */
    }
    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif

#if ((0U != FLSTST_BGND_BLOCK_NUM) || (0U != FLSTST_FGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static uint32 FlsTst_CheckSum(
    P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) Checksum_DataPtr,
    VAR(uint32, AUTOMATIC) Checksum_Length,
    VAR(uint32, AUTOMATIC) Checksum_StartValue,
    VAR(boolean, AUTOMATIC) Checksum_IsFirstCall)
{
    uint32 checksumResult;
    uint32 i;

    if ((boolean)TRUE == Checksum_IsFirstCall)
    {
        checksumResult = 0U;
    }
    else
    {
        checksumResult = Checksum_StartValue;
    }

    for (i = 0; i < Checksum_Length; i++)
    {
        checksumResult += Checksum_DataPtr[i];
    }
    return checksumResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif

#if ((0U != FLSTST_BGND_BLOCK_NUM) || (0U != FLSTST_FGND_BLOCK_NUM))
#define FLSTST_START_SEC_CODE
#include "FlsTst_MemMap.h"
static Std_ReturnType FlsTst_MemCompare(
    P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) SourceDataPtr,
    P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) DstDataPtr,
    VAR(uint32, AUTOMATIC) Length)
{
    uint32 i;
    const uint8* pDest = (const uint8*)DstDataPtr;
    const uint8* pSrc = (const uint8*)SourceDataPtr;
    Std_ReturnType l_testResult = E_OK;

    for (i = 0U; i < Length; i++)
    {
        if (pDest[i] != pSrc[i])
        {
            l_testResult = E_NOT_OK;
            break;
        }
    }
    return l_testResult;
}
#define FLSTST_STOP_SEC_CODE
#include "FlsTst_MemMap.h"
#endif
