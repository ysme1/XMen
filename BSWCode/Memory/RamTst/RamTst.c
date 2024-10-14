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
 **  FILENAME    : RamTst.c                                                    **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : Xin.Liu                                                     **
 **  Vendor      :                                                             **
 **  DESCRIPTION : ram test source code                                        **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/**
  \page ISOFT_MISRA_Exceptions  MISRA-C:2012 Compliance Exceptions
    ModeName:RamTst<br>
  RuleSorce:puhua-rule.rcf 2.3.1

   \li PRQA S 0306 MISRA Rule 11.4 .<br>
    Reason:Necessary type conversions.

   \li PRQA S 2469 MISRA Rule 14.2 .<br>
    Reason:Necessary address updates.

   \li PRQA S 3408 MISRA Rule 8.4 .<br>
    Reason:These two functions are deliberately designed to be empty, there is a unified processing of the main
  function, the function is not affected
 */

/*=======[I N C L U D E S]====================================================*/
#include "RamTst.h"
#include "Schm_RamTst.h"
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
#include "Det.h"
#endif /*STD_ON == RAMTST_DEV_ERROR_DETECT*/

#include "Dem.h"
/*******************************************************************/

#define RAMTST_C_SW_MAJOR_VERSION 2u /*Major Version*/
#define RAMTST_C_SW_MINOR_VERSION 0u /*Minor Version*/
#define RAMTST_C_SW_PATCH_VERSION 1u /*Patch Version*/
#define RAMTST_C_AR_MAJOR_VERSION 4u /*Autosar Major Version*/
#define RAMTST_C_AR_MINOR_VERSION 5u /*Autosar Minor Version*/
#define RAMTST_C_AR_PATCH_VERSION 0u /*Autosar Patch Version*/

/*=======================[V E R S I O N  C H E C K]====================================*/
#if (RAMTST_C_AR_MAJOR_VERSION != RAMTST_H_AR_MAJOR_VERSION)
#error "RAMTST.c : Mismatch in Specification Major Version"
#endif /*RAMTST_C_AR_MAJOR_VERSION != RAMTST_H_AR_MAJOR_VERSION*/
#if (RAMTST_C_AR_MINOR_VERSION != RAMTST_H_AR_MINOR_VERSION)
#error "RAMTST.c : Mismatch in Specification Minor Version"
#endif /*RAMTST_C_AR_MINOR_VERSION != RAMTST_H_AR_MINOR_VERSION*/
#if (RAMTST_C_AR_PATCH_VERSION != RAMTST_H_AR_PATCH_VERSION)
#error "RAMTST.c : Mismatch in Specification Patch Version"
#endif /*RAMTST_C_AR_PATCH_VERSION != RAMTST_H_AR_PATCH_VERSION*/
#if (RAMTST_C_SW_MAJOR_VERSION != RAMTST_H_SW_MAJOR_VERSION)
#error "RAMTST.c : Mismatch in Specification Major Version"
#endif /*RAMTST_C_SW_MAJOR_VERSION != RAMTST_H_SW_MAJOR_VERSION*/
#if (RAMTST_C_SW_MINOR_VERSION != RAMTST_H_SW_MINOR_VERSION)
#error "RAMTST.c : Mismatch in Specification Minor Version"
#endif /*RAMTST_C_SW_MINOR_VERSION != RAMTST_H_SW_MINOR_VERSION*/

/***************************Static variable********************************************/
#define RAMTST_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "RamTst_MemMap.h"
static RamTst_BlockInfoType RamTstAllBlockInfo[RAMTST_BLOCK_NUM + 1u];
#define RAMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "RamTst_MemMap.h"

#define RAMTST_START_SEC_VAR_INIT_PTR
#include "RamTst_MemMap.h"
static const RamTst_ConfigType* RamTstConfig = NULL_PTR;
#define RAMTST_STOP_SEC_VAR_INIT_PTR
#include "RamTst_MemMap.h"

#define RAMTST_START_SEC_VAR_INIT_32
#include "RamTst_MemMap.h"
static uint32 NowBackTestBlockIndex = 1u;
static RamTst_NumberOfTestedCellsType RamTstNumberOfTestedCellsUse = 1u;
static uint32 NowAlgParamTestedBlockNumber = 0u;
#define RAMTST_STOP_SEC_VAR_INIT_32
#include "RamTst_MemMap.h"

#define RAMTST_START_SEC_VAR_INIT_8
#include "RamTst_MemMap.h"
static RamTst_AlgParamsIdType CurRamTstAlgParamsId = 1u;
/* Data type used to identify a set of configuration parameters for a test algorithm */
static RamTst_ModeInitStatusType RamTstDeInitFlag = RAMTST_INIT_NOT;
static RamTst_ExecutionStatusType CurRamTstExecutionStatus = RAMTST_EXECUTION_UNINIT;
static RamTst_TestResultType RamTstOverallTestResult = RAMTST_RESULT_NOT_TESTED;
#define RAMTST_STOP_SEC_VAR_INIT_8
#include "RamTst_MemMap.h"
/***************************I********************************************************/

/***************************Internal  API********************************************/
#define RAMTST_START_SEC_CODE
#include "RamTst_MemMap.h"

static sint32 RamTst_MemcpyAndMemCmp(uint8* buffer1, uint8* buffer2, uint32 count);

static Std_ReturnType RamTest_DoMarchCAlgorithmWithMemcpy(
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CTmpStoreRamStartAddr);

static Std_ReturnType RamTest_DoMarchCAlgorithm(
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CRamTstFillPattern);

static Std_ReturnType RamTst_DoTestWithoutMemcpy(
    RamTst_AlgorithmType UsedAlgorithm,
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CRamTstFillPattern);

static Std_ReturnType RamTst_DoTestWithMemcpy(
    RamTst_AlgorithmType UsedAlgorithm,
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CTmpStoreRamStartAddr);

static Std_ReturnType RamTst_DoSelfCheckTestAction(uint32 u32CStartAddr, uint32 u32CEndAddr);

static Std_ReturnType RamTst_SelfCheck(void);

static void RamTst_InitAllBlockStatus(void);

static Std_ReturnType RamTst_ExecMarchCTestWithMemcpy(
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CTmpStoreRamStartAddr);

static Std_ReturnType RamTst_CheckBlockIDIsOutOfRange(RamTst_NumberOfBlocksType BlockID);

/*************************************************************************/
/*
 * Brief               RamTst Memcpy and then memcmp
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      buffer1:compare data 1
 *                     buffer2:compare data 2
 *                     count:compare data length
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              If the return value is < 0, it means that str1 is less than str2.
 *                     If the return value is > 0, the str2 is less than str1.
 *                     If the return value is equal to 0, it means that str1 is equal to str2
 * CallByAPI           None
 */
/*************************************************************************/
static sint32 RamTst_MemcpyAndMemCmp(uint8* buffer1, uint8* buffer2, uint32 count)
{
    sint32 MemcmpRtn;
    uint32 lcount = count;
    uint8* TempPtr1 = buffer1;
    uint8* TempPtr2 = buffer2;
    /* Memcpy */
    while (0u < count)
    {
        count -= 1u;
        *buffer1 = *buffer2;
        buffer1++;
        buffer2++;
    }

    /* Memcmp */
    if (0u == lcount)
    {
        MemcmpRtn = 0;
    }
    else
    {
        while ((0u < lcount) && (*TempPtr1 == *TempPtr2))
        {
            lcount--;
            if (0u != lcount)
            {
                TempPtr1++;
                TempPtr2++;
            }
        }
        MemcmpRtn = (sint32)(*TempPtr1) - (sint32)(*TempPtr2);
    }

    return MemcmpRtn;
}
/*************************************************************************/
/*
 * Brief               Do March C Algorithm no memcpy
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      u32CRamStartAddr:RAM start addr
 *                     u32CRamEndAddr:RAM end addr
 *                     u32CRamTstFillPattern:the bit pattern value
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/

static Std_ReturnType RamTest_DoMarchCAlgorithm(
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CRamTstFillPattern)
{
    uint32* DoTestRamPtr;
    Std_ReturnType ret = E_OK;
    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
    uint32* DoTestStartAddr = (uint32*)u32CRamStartAddr;
    uint32* DoTestEndAddr = (uint32*)u32CRamEndAddr;
    uint32* EndAddr = (uint32*)(u32CRamEndAddr - 3u);
    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

    /* ---------------------------- STEP 1 ----------------------------------- */
    /* Write background with addresses increasing */
    for (DoTestRamPtr = DoTestStartAddr; DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
    {
        /* Scrambling not important when there's no consecutive verify and write */
        *DoTestRamPtr = BCKGRND;
    }

    /* ---------------------------- STEP 2 ----------------------------------- */
    /* Verify background and write inverted background with addresses increasing */
    for (DoTestRamPtr = DoTestStartAddr; DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
    {
        if (E_OK == ret)
        {
            if (*DoTestRamPtr != BCKGRND)
            {
                ret = E_NOT_OK;
            }
            *DoTestRamPtr = INV_BCKGRND;
        }
        else
        {
            break;
        }
    }

    /* ---------------------------- STEP 3 ----------------------------------- */
    /* Verify inverted background and write background with addresses increasing */
    for (DoTestRamPtr = DoTestStartAddr; DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
    {
        if (E_OK == ret)
        {
            if (*DoTestRamPtr != INV_BCKGRND)
            {
                ret = E_NOT_OK;
            }
            *DoTestRamPtr = BCKGRND;
        }
        else
        {
            break;
        }
    }

    /* ---------------------------- STEP 4 ----------------------------------- */
    /* Verify background and write inverted background with addresses decreasing */
    for (DoTestRamPtr = EndAddr; DoTestRamPtr >= DoTestStartAddr; DoTestRamPtr--)
    {
        if (E_OK == ret)
        {
            if (*DoTestRamPtr != BCKGRND)
            {
                ret = E_NOT_OK;
            }
            *DoTestRamPtr = INV_BCKGRND;
        }
        else
        {
            break;
        }
    }

    /* ---------------------------- STEP 5 ----------------------------------- */
    /* Verify inverted background and write background with addresses decreasing */
    for (DoTestRamPtr = EndAddr; DoTestRamPtr >= DoTestStartAddr; DoTestRamPtr--)
    {
        if (E_OK == ret)
        {
            if (*DoTestRamPtr != INV_BCKGRND)
            {
                ret = E_NOT_OK;
            }
            *DoTestRamPtr = BCKGRND;
        }
        else
        {
            break;
        }
    }

    /* ---------------------------- STEP 6 ----------------------------------- */
    /* Verify background with addresses increasing */
    for (DoTestRamPtr = (DoTestStartAddr); DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
    {
        if (E_OK == ret)
        {
            if (*DoTestRamPtr != BCKGRND)
            {
                ret = E_NOT_OK; /* No need to take into account scrambling here */
            }
            /* SWS_RamTst_00201 */
            *DoTestRamPtr = u32CRamTstFillPattern;
        }
        else
        {
            break;
        }
    }

    return ret;
}

/*************************************************************************/
/*
 * Brief               Do March C Algorithm with memcpy
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      u32CRamStartAddr:RAM start addr
 *                     u32CRamEndAddr:RAM end addr
 *                     u32CTmpStoreRamStartAddr:Tmp Store Ram Start Addr
 *                     u32CTmpStoreRamEndAddr:Tmp Store Ram End Addr
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/

static Std_ReturnType RamTest_DoMarchCAlgorithmWithMemcpy(
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CTmpStoreRamStartAddr)
{
    uint32* DoTestRamPtr;
    Std_ReturnType ret = E_OK;
    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
    uint32* DoTestStartAddr = (uint32*)u32CRamStartAddr;
    uint32* DoTestEndAddr = (uint32*)u32CRamEndAddr;
    uint32* EndAddr = (uint32*)(u32CRamEndAddr - 3u);
    uint8* TmpSaveDoTestStartAddr = (uint8*)u32CTmpStoreRamStartAddr;
    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */
    /* save */
    /* copy data to safe reserve area */
    /* safe reserve area compare to test ram area */
    if (0
        != RamTst_MemcpyAndMemCmp(
            TmpSaveDoTestStartAddr,
            (uint8*)DoTestStartAddr,
            (uint32)(u32CRamEndAddr - u32CRamStartAddr + 1u)))
    {
        ret = E_NOT_OK;
    }

    if (E_OK == ret)
    {
        /* ---------------------------- STEP 1 ----------------------------------- */
        /* Write background with addresses increasing */
        for (DoTestRamPtr = DoTestStartAddr; DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
        {
            /* Scrambling not important when there's no consecutive verify and write */
            *DoTestRamPtr = BCKGRND;
        }

        /* ---------------------------- STEP 2 ----------------------------------- */
        /* Verify background and write inverted background with addresses increasing */
        for (DoTestRamPtr = DoTestStartAddr; DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
        {
            if (E_OK == ret)
            {
                if (*DoTestRamPtr != BCKGRND)
                {
                    ret = E_NOT_OK;
                }
                *DoTestRamPtr = INV_BCKGRND;
            }
            else
            {
                break;
            }
        }

        /* ---------------------------- STEP 3 ----------------------------------- */
        /* Verify inverted background and write background with addresses increasing */
        for (DoTestRamPtr = DoTestStartAddr; DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
        {
            if (E_OK == ret)
            {
                if (*DoTestRamPtr != INV_BCKGRND)
                {
                    ret = E_NOT_OK;
                }
                *DoTestRamPtr = BCKGRND;
            }
            else
            {
                break;
            }
        }

        /* ---------------------------- STEP 4 ----------------------------------- */
        /* Verify background and write inverted background with addresses decreasing */
        for (DoTestRamPtr = EndAddr; DoTestRamPtr >= DoTestStartAddr; DoTestRamPtr--)
        {
            if (E_OK == ret)
            {
                if (*DoTestRamPtr != BCKGRND)
                {
                    ret = E_NOT_OK;
                }
                *DoTestRamPtr = INV_BCKGRND;
            }
            else
            {
                break;
            }
        }

        /* ---------------------------- STEP 5 ----------------------------------- */
        /* Verify inverted background and write background with addresses decreasing */
        for (DoTestRamPtr = EndAddr; DoTestRamPtr >= DoTestStartAddr; DoTestRamPtr--)
        {
            if (E_OK == ret)
            {
                if (*DoTestRamPtr != INV_BCKGRND)
                {
                    ret = E_NOT_OK;
                }
                *DoTestRamPtr = BCKGRND;
            }
            else
            {
                break;
            }
        }

        /* ---------------------------- STEP 6 ----------------------------------- */
        /* Verify background with addresses increasing */
        for (DoTestRamPtr = (DoTestStartAddr); DoTestRamPtr <= DoTestEndAddr; DoTestRamPtr++)
        {
            if (E_OK == ret)
            {
                if (*DoTestRamPtr != BCKGRND)
                {
                    ret = E_NOT_OK; /* No need to take into account scrambling here */
                }
            }
            else
            {
                break;
            }
        }
        /* recover */
        /* copy safe reserve area data back to test ram area */
        /* safe reserve area compare to test ram area */
        if (0
            != RamTst_MemcpyAndMemCmp(
                (uint8*)DoTestStartAddr,
                TmpSaveDoTestStartAddr,
                (uint32)(u32CRamEndAddr - u32CRamStartAddr + 1u)))
        {
            ret = E_NOT_OK;
        }
    }

    return ret;
}

/*************************************************************************/
/*
 * Brief               Do test without memcpy
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      UsedAlgorithm:used Algorithm
 *                     u32CRamStartAddr:RAM start addr
 *                     u32CRamEndAddr:RAM end addr
 *                     u32CRamTstFillPattern:the bit pattern value
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/

static Std_ReturnType RamTst_DoTestWithoutMemcpy(
    RamTst_AlgorithmType UsedAlgorithm,
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CRamTstFillPattern)
{
    Std_ReturnType Rtn = E_NOT_OK;
    switch (UsedAlgorithm)
    {
    case RAMTST_CHECKERBOARD_TEST:
    case RAMTST_WALK_PATH_TEST:
    case RAMTST_GALPAT_TEST:
    case RAMTST_TRANSP_GALPAT_TEST:
    case RAMTST_ABRAHAM_TEST: {
        break;
    }

    case RAMTST_MARCH_TEST: {
        if ((boolean)TRUE == RamTstConfig->RamTstAlgorithms.RamTstMarchTestSelected)
        {
            Rtn = RamTest_DoMarchCAlgorithm(u32CRamStartAddr, u32CRamEndAddr, u32CRamTstFillPattern);
        }
        break;
    }

    default:
        /* empty */
        break;
    }
    return Rtn;
}

/*************************************************************************/
/*
 * Brief               Do ram self check
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      u32CStartAddr: RAM start addr
 *                     u32CEndAddr: RAM end addr
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/
static Std_ReturnType RamTst_DoSelfCheckTestAction(uint32 u32CStartAddr, uint32 u32CEndAddr)
{
    Std_ReturnType Rtn = E_OK;
    uint32* pRamPtr;
    const uint32 u32WriteData = 0xA5A5A5A5u;
    /* PRQA S 0306++ */ /* MISRA Rule 11.4 */
    uint32* StartAddr = (uint32*)u32CStartAddr;
    uint32* EndAddr = (uint32*)u32CEndAddr;
    /* PRQA S 0306-- */ /* MISRA Rule 11.4 */

    /* ---------------------------- STEP 1 ----------------------------------- */
    /* Write data with addresses increasing */
    for (pRamPtr = StartAddr; pRamPtr <= EndAddr; pRamPtr++)
    {
        /* Scrambling not important when there's no consecutive verify and write */
        *pRamPtr = u32WriteData;
    }

    /* ---------------------------- STEP 2 ----------------------------------- */
    /* Verify data with addresses increasing */
    for (pRamPtr = StartAddr; pRamPtr <= EndAddr; pRamPtr++)
    {
        if (*pRamPtr != u32WriteData)
        {
            Rtn = E_NOT_OK;
            break;
        }
        *pRamPtr = 0;
    }
    return Rtn;
}

/*************************************************************************/
/*
 * Brief               exec local var ram and Safe RAM reserve area self check
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/
static Std_ReturnType RamTst_SelfCheck(void)
{
    Std_ReturnType Rtn;
    /* first: test Local var RAM reserve area */
    Rtn = RamTst_DoSelfCheckTestAction(RAM_LOCAL_VAR_AREA_START, RAM_LOCAL_VAR_AREA_END);

    if (E_OK == Rtn)
    {
        /* Second: test Safe RAM reserve area */
        /* The size of the safe reserved area equal to  RAM_SINGLEBLOCKSIZE */
        Rtn = RamTst_DoSelfCheckTestAction(RAM_SAFERESERVEAREA_START, RAM_SAFERESERVEAREA_END);
    }
    return Rtn;
}

/*************************************************************************/
/*
 * Brief               Do march C test with memcpy
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]
 *                     u32CRamStartAddr:RAM start addr
 *                     u32CRamEndAddr:RAM end addr
 *                     u32CTmpStoreRamStartAddr:Tmp Store Ram Start Addr
 *                     u32CTmpStoreRamEndAddr:Tmp Store Ram End Addr
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/

static Std_ReturnType RamTst_ExecMarchCTestWithMemcpy(
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CTmpStoreRamStartAddr)
{
    uint32 StartAddr;
    uint32 EndAddr;
    Std_ReturnType ret;
    for (StartAddr = u32CRamStartAddr; StartAddr < u32CRamEndAddr;)
    {
        /* calc test end ram addr */
        EndAddr = StartAddr + RamTstNumberOfTestedCellsUse - 1u;
        /* check if the end address exceeds RAM_END, and if so, use RAM_END */
        if (u32CRamEndAddr <= EndAddr)
        {
            EndAddr = u32CRamEndAddr;
        }

        /* do March C Test */
        ret = RamTest_DoMarchCAlgorithmWithMemcpy(StartAddr, EndAddr, u32CTmpStoreRamStartAddr);

        /* calc next test ram start addr */
        /* PRQA S 2469++ */ /* MISRA Rule 14.2 */
        if (RAM_LOCAL_VAR_AREA_START == StartAddr)
        {
            StartAddr += (RAM_LOCAL_VAR_AREA_END - RAM_LOCAL_VAR_AREA_START + 1u);
        }
        else
        {
            StartAddr += (EndAddr - StartAddr + 1u);
        }
        /* PRQA S 2469-- */ /* MISRA Rule 14.2 */
    }
    return ret;
}

/*************************************************************************/
/*
 * Brief               Do test with memcpy
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      UsedAlgorithm:used Algorithm
 *                     u32CRamStartAddr:RAM start addr
 *                     u32CRamEndAddr:RAM end addr
 *                     u32CTmpStoreRamStartAddr:Tmp Store Ram Start Addr
 *                     u32CTmpStoreRamEndAddr:Tmp Store Ram End Addr
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/

static Std_ReturnType RamTst_DoTestWithMemcpy(
    RamTst_AlgorithmType UsedAlgorithm,
    uint32 u32CRamStartAddr,
    uint32 u32CRamEndAddr,
    uint32 u32CTmpStoreRamStartAddr)
{
    Std_ReturnType ret = E_NOT_OK;
    switch (UsedAlgorithm)
    {
    case RAMTST_CHECKERBOARD_TEST:
    case RAMTST_WALK_PATH_TEST:
    case RAMTST_GALPAT_TEST:
    case RAMTST_TRANSP_GALPAT_TEST:
    case RAMTST_ABRAHAM_TEST: {
        break;
    }

    case RAMTST_MARCH_TEST: {
        if ((boolean)TRUE == RamTstConfig->RamTstAlgorithms.RamTstMarchTestSelected)
        {
            ret = RamTst_ExecMarchCTestWithMemcpy(u32CRamStartAddr, u32CRamEndAddr, u32CTmpStoreRamStartAddr);
        }
        break;
    }

    default:
        /* empty */
        break;
    }
    return ret;
}

/*************************************************************************/
/*
 * Brief               Init All config Block Status
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * CallByAPI           Up layer
 */
/*************************************************************************/
static void RamTst_InitAllBlockStatus(void)
{
    uint32 Index1;
    uint32 Index2;
    uint32 TmpId;
    const RamTst_BlockParams* pTmpBlock;

    if (NULL_PTR != RamTstConfig)
    {
        for (Index2 = 0; Index2 < RamTstConfig->RamTstConfigParams.RamTstNumberOfAlgParamSets; Index2++)
        {
            for (Index1 = 0; Index1 < RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index2].RamTstNumberOfBlocks;
                 Index1++)
            {
                /* use block id as the buffer index */
                TmpId =
                    RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index2].RamTstBlockParams[Index1].RamTstBlockId;
                pTmpBlock = &RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index2].RamTstBlockParams[Index1];

                RamTstAllBlockInfo[TmpId].BlockTestResult = RAMTST_RESULT_NOT_TESTED;
                RamTstAllBlockInfo[TmpId].IsBlockTestedFlag = BLOCK_NOT_TEST;
                RamTstAllBlockInfo[TmpId].NowTestedAddr = pTmpBlock->RamTstStartAddress;
                RamTstAllBlockInfo[TmpId].FinalEndAddr = pTmpBlock->RamTstStartAddress;
                RamTstAllBlockInfo[TmpId].TestPolicyUse = pTmpBlock->RamTstTestPolicy;
                RamTstAllBlockInfo[TmpId].RamTstAlgParamsIdUse =
                    RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index2].RamTstAlgParamsId;
                RamTstAllBlockInfo[TmpId].BlockTestUseMethodUse = pTmpBlock->BlockTestUseMethod;
            }
        }
    }
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    else
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_INIT_ID, RAMTST_E_PARAM_POINTER);
    }
#endif
}

/*************************************************************************/
/*
 * Brief               Check BlockID Is Out Of Range
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      BlockID:to be checked BlockID
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              Std_ReturnType
 * CallByAPI           Up layer
 */
/*************************************************************************/
static Std_ReturnType RamTst_CheckBlockIDIsOutOfRange(RamTst_NumberOfBlocksType BlockID)
{
    Std_ReturnType Rtn = E_NOT_OK;
    uint32 Index1;
    uint32 Index2;

    if (NULL_PTR != RamTstConfig)
    {
        for (Index2 = 0; Index2 < RamTstConfig->RamTstConfigParams.RamTstNumberOfAlgParamSets; Index2++)
        {
            for (Index1 = 0; Index1 < RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index2].RamTstNumberOfBlocks;
                 Index1++)
            {
                if (BlockID
                    == RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index2].RamTstBlockParams[Index1].RamTstBlockId)
                {
                    Rtn = E_OK;
                    break;
                }
            }
        }
    }
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    else
    {
        (void)Det_ReportError(
            RAMTST_MODULE_ID,
            RAMTST_INSTANCE_ID,
            RAMTST_GETTESTRESULTPERBLOCK_ID,
            RAMTST_E_PARAM_POINTER);
    }
#endif
    return Rtn;
}

/*************************************************************************/
/*
 * Brief               Update Overall Test Result
 * ServiceId           None
 * Sync/Async          synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * CallByAPI           Up layer
 */
/*************************************************************************/
static void RamTst_UpdateOverallTestResult(void)
{
    uint8 UpdateResultFuncUseFlag = 0u;
    uint32 UpdateResultFuncUseIndex;
    const RamTst_AlgParams* UpdateOverallFuncAlgUsePtr;

    /* check if no test started */
    if (NULL_PTR != RamTstConfig)
    {
        UpdateOverallFuncAlgUsePtr =
            &RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)];
        for (UpdateResultFuncUseIndex = 0u; UpdateResultFuncUseIndex < UpdateOverallFuncAlgUsePtr->RamTstNumberOfBlocks;
             UpdateResultFuncUseIndex++)
        {
            if (BLOCK_NOT_TEST
                != RamTstAllBlockInfo[UpdateOverallFuncAlgUsePtr->RamTstBlockParams[UpdateResultFuncUseIndex]
                                          .RamTstBlockId]
                       .IsBlockTestedFlag)
            {
                UpdateResultFuncUseFlag = 1u;
                break;
            }
        }

        if (0u == UpdateResultFuncUseFlag)
        {
            /* no block has tested ,but check if has a block current running */
            for (UpdateResultFuncUseIndex = 0u;
                 UpdateResultFuncUseIndex < UpdateOverallFuncAlgUsePtr->RamTstNumberOfBlocks;
                 UpdateResultFuncUseIndex++)
            {
                if (RAMTST_RESULT_UNDEFINED
                    == RamTstAllBlockInfo[UpdateOverallFuncAlgUsePtr->RamTstBlockParams[UpdateResultFuncUseIndex]
                                              .RamTstBlockId]
                           .BlockTestResult)
                {
                    UpdateResultFuncUseFlag = 5u;
                    break;
                }
            }
            if (5u == UpdateResultFuncUseFlag)
            {
                RamTstOverallTestResult = RAMTST_RESULT_UNDEFINED;
            }
            else
            {
                /* no block start test */
                RamTstOverallTestResult = RAMTST_RESULT_NOT_TESTED;
            }
        }
        else
        {
            for (UpdateResultFuncUseIndex = 0u;
                 UpdateResultFuncUseIndex < UpdateOverallFuncAlgUsePtr->RamTstNumberOfBlocks;
                 UpdateResultFuncUseIndex++)
            {
                if (BLOCK_NOT_TEST
                    == RamTstAllBlockInfo[UpdateOverallFuncAlgUsePtr->RamTstBlockParams[UpdateResultFuncUseIndex]
                                              .RamTstBlockId]
                           .IsBlockTestedFlag)
                {
                    /* check if has block not tested */
                    UpdateResultFuncUseFlag = 2u;
                    break;
                }
            }

            if (2u == UpdateResultFuncUseFlag)
            {
                /* a test was started, not all blocks have yet been tested */
                for (UpdateResultFuncUseIndex = 0u;
                     UpdateResultFuncUseIndex < UpdateOverallFuncAlgUsePtr->RamTstNumberOfBlocks;
                     UpdateResultFuncUseIndex++)
                {
                    if (RAMTST_RESULT_NOT_OK
                        == RamTstAllBlockInfo[UpdateOverallFuncAlgUsePtr->RamTstBlockParams[UpdateResultFuncUseIndex]
                                                  .RamTstBlockId]
                               .BlockTestResult)
                    {
                        UpdateResultFuncUseFlag = 3u;
                        break;
                    }
                }

                if (3u != UpdateResultFuncUseFlag)
                {
                    /* a test was started, not all blocks have yet been tested and no block result is
                     * RAMTST_RESULT_NOT_OK */
                    RamTstOverallTestResult = RAMTST_RESULT_UNDEFINED;
                }
                else
                {
                    RamTstOverallTestResult = RAMTST_RESULT_NOT_OK;
                }
            }
            else
            {
                /* all block has tested */
                /* check ok or not ok */
                for (UpdateResultFuncUseIndex = 0u;
                     UpdateResultFuncUseIndex < UpdateOverallFuncAlgUsePtr->RamTstNumberOfBlocks;
                     UpdateResultFuncUseIndex++)
                {
                    if (RAMTST_RESULT_NOT_OK
                        == RamTstAllBlockInfo[UpdateOverallFuncAlgUsePtr->RamTstBlockParams[UpdateResultFuncUseIndex]
                                                  .RamTstBlockId]
                               .BlockTestResult)
                    {
                        UpdateResultFuncUseFlag = 4u;
                        break;
                    }
                }

                if (4u != UpdateResultFuncUseFlag)
                {
                    RamTstOverallTestResult = RAMTST_RESULT_OK;
                }
                else
                {
                    RamTstOverallTestResult = RAMTST_RESULT_NOT_OK;
                }
            }
        }
    }
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    else
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETTESTRESULT_ID, RAMTST_E_PARAM_POINTER);
    }
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
}

/**********************************                 extern api                  *************************************/
/*************************************************************************/
/* RamTst
 * Brief               Service for RAM Test initialization
 * ServiceId           None
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      ConfigPtr:Pointer to the selected configuration set.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_Init(const RamTst_ConfigType* ConfigPtr)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_EXECUTION_UNINIT != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_INIT_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        /* self check */
#if (STD_ON == RAMTST_SELF_CHECK_ENABLE)
        if (E_OK != RamTst_SelfCheck())
        {
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
            (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_INIT_ID, RAMTST_E_SELF_CHECK_ERR);
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
        }
#endif
        RamTstConfig = ConfigPtr;
        RamTstOverallTestResult = RAMTST_RESULT_NOT_TESTED;
        CurRamTstAlgParamsId = RamTstConfig->RamTstConfigParams.RamTstDefaultAlgParamsId;
        CurRamTstExecutionStatus = RAMTST_EXECUTION_STOPPED;
        RamTstDeInitFlag = RAMTST_INIT_OK;
        RamTstNumberOfTestedCellsUse =
            RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)]
                .RamTstNumberOfTestedCells;
        NowBackTestBlockIndex = RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)]
                                    .RamTstBlockParams[0]
                                    .RamTstBlockId;

        RamTst_InitAllBlockStatus();
    }
}

/*************************************************************************/
/* RamTst
 * Brief               Service for RAM Test deinitialization
 * ServiceId           None
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_DeInit(void)
{
    if (RAMTST_INIT_NOT != RamTstDeInitFlag)
    {
        CurRamTstAlgParamsId = 1u;
        RamTstOverallTestResult = RAMTST_RESULT_NOT_TESTED;
        CurRamTstExecutionStatus = RAMTST_EXECUTION_UNINIT;
        RamTstDeInitFlag = RAMTST_INIT_NOT;
        RamTst_InitAllBlockStatus();
        NowBackTestBlockIndex = 1u;
        RamTstNumberOfTestedCellsUse = 1u;
    }
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    else
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_DEINIT_ID, RAMTST_E_UNINIT);
    }
#endif
}

#if RAMTST_STOP_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service for stopping the RAM Test
 * ServiceId           None
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_Stop(void)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_STOP_ID, RAMTST_E_UNINIT);
    }
    else if (
        (RAMTST_EXECUTION_RUNNING != CurRamTstExecutionStatus)
        && (RAMTST_EXECUTION_SUSPENDED != CurRamTstExecutionStatus))
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_STOP_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        CurRamTstExecutionStatus = RAMTST_EXECUTION_STOPPED;
        /* The test result is retained, but test parameters and loop data are not.  SWS_RamTst_00014 */
        NowBackTestBlockIndex = RamTstConfig->RamTstConfigParams.RamTstAlgParams[CurRamTstAlgParamsId - 1u]
                                    .RamTstBlockParams[0]
                                    .RamTstBlockId;
        RamTst_InitAllBlockStatus();
        CurRamTstAlgParamsId = RamTstConfig->RamTstConfigParams.RamTstDefaultAlgParamsId;
        RamTstOverallTestResult = RAMTST_RESULT_NOT_TESTED;
    }
}
#endif

#if RAMTST_ALLOW_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service for continuing the RAM Test after calling 'RamTst_Stop.
 * ServiceId           None
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_Allow(void)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_ALLOW_ID, RAMTST_E_UNINIT);
    }
    else if (RAMTST_EXECUTION_STOPPED != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_ALLOW_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        CurRamTstExecutionStatus = RAMTST_EXECUTION_RUNNING;
    }
}
#endif

#if RAMTST_SUSPEND_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service for suspending current operation of background RAM Test, until RESUME is called
 * ServiceId           None
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_Suspend(void)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SUSPEND_ID, RAMTST_E_UNINIT);
    }
    else if (RAMTST_EXECUTION_RUNNING != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SUSPEND_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        CurRamTstExecutionStatus = RAMTST_EXECUTION_SUSPENDED;
    }
}
#endif

#if RAMTST_RESUME_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service for allowing to continue the background RAM Test at the point is was suspended.
 * ServiceId           None
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_Resume(void)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RESUME_ID, RAMTST_E_UNINIT);
    }
    else if (RAMTST_EXECUTION_SUSPENDED != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RESUME_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        CurRamTstExecutionStatus = RAMTST_EXECUTION_RUNNING;
    }
}
#endif

#if RAMTST_GET_EXECUTION_STATUS_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the current RAM Test execution status.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              RamTst_ExecutionStatusTyp
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
RamTst_ExecutionStatusType RamTst_GetExecutionStatus(void)
{
    RamTst_ExecutionStatusType Rtn = RAMTST_EXECUTION_UNINIT;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETEXECUTIONSTATUS_ID, RAMTST_E_UNINIT);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        Rtn = CurRamTstExecutionStatus;
    }
    return Rtn;
}
#endif

#if RAMTST_GET_TEST_RESULT_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the current RAM Test result.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              RamTst_TestResultType
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
RamTst_TestResultType RamTst_GetTestResult(void)
{
    RamTst_TestResultType Rtn = RAMTST_RESULT_NOT_TESTED;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETTESTRESULT_ID, RAMTST_E_UNINIT);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        Rtn = RamTstOverallTestResult;
    }
    return Rtn;
}
#endif

#if RAMTST_GET_TEST_RESULT_PER_BLOCK_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the current RAM Test result for the specified block
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      BlockID:Identifies the block
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              RamTst_TestResultType
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
RamTst_TestResultType RamTst_GetTestResultPerBlock(RamTst_NumberOfBlocksType BlockID)
{
    RamTst_TestResultType Rtn = RAMTST_RESULT_NOT_TESTED;

#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    /* SWS_RamTst_00039 */
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETTESTRESULTPERBLOCK_ID, RAMTST_E_UNINIT);
    }
    else if (E_NOT_OK == RamTst_CheckBlockIDIsOutOfRange(BlockID))
    {
        (void)Det_ReportError(
            RAMTST_MODULE_ID,
            RAMTST_INSTANCE_ID,
            RAMTST_GETTESTRESULTPERBLOCK_ID,
            RAMTST_E_OUT_OF_RANGE);

        Rtn = RAMTST_RESULT_UNDEFINED;
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        Rtn = RamTstAllBlockInfo[BlockID].BlockTestResult;
    }

    return Rtn;
}
#endif

#if RAMTST_VERSIONINFO_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the version information of this module
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  versioninfo锛歅ointer to the location / address where to store the version information of this
 * module. Return              None PreCondition        None CallByAPI
 */
/*************************************************************************/
void RamTst_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfo)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETVERSIONINFO_ID, RAMTST_E_PARAM_POINTER);
    }
    else
#endif /*STD_ON == WDGM_DEV_ERROR_DETECT*/
    {
        VersionInfo->vendorID = RAMTST_VENDOR_ID;
        VersionInfo->moduleID = RAMTST_MODULE_ID;
        VersionInfo->sw_major_version = RAMTST_C_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = RAMTST_C_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = RAMTST_C_SW_PATCH_VERSION;
    }
}
#endif

#if RAMTST_GET_ALGPARAMS_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the ID of the current RAM Test algorithm parameter set.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              RamTst_AlgParamsIdType
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
RamTst_AlgParamsIdType RamTst_GetAlgParams(void)
{
    RamTst_AlgParamsIdType Rtn = 0u;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETALGPARAMS_ID, RAMTST_E_UNINIT);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        Rtn = CurRamTstAlgParamsId;
    }
    return Rtn;
}
#endif

#if RAMTST_GET_TEST_ALGORITHM_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the current RAM Test algorithm.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              RamTst_AlgorithmType
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
RamTst_AlgorithmType RamTst_GetTestAlgorithm(void)
{
    RamTst_AlgorithmType Rtn = RAMTST_ALGORITHM_UNDEFINED;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETTESTALGORITHM_ID, RAMTST_E_UNINIT);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        Rtn = RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)].RamTstAlgorithm;
    }
    return Rtn;
}
#endif

#if RAMTST_GET_NUMBER_OF_TESTED_CELLS_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service returns the current number of tested cells per main-function cycle.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              RamTst_NumberOfTestedCellsType:Number of currently tested cells per cycle
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
RamTst_NumberOfTestedCellsType RamTst_GetNumberOfTestedCells(void)
{
    RamTst_NumberOfTestedCellsType Rtn = 0u;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETNUMBEROFTESTEDCELLS_ID, RAMTST_E_UNINIT);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        Rtn = RamTstNumberOfTestedCellsUse;
    }
    return Rtn;
}
#endif

#if RAMTST_SELECT_ALGPARAMS_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service used to set the test algorithm and its parameter set.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      NewAlgParamsId:Identifies the parameter set to be used.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_SelectAlgParams(RamTst_AlgParamsIdType NewAlgParamsId)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    uint8 Flag = 0u;
    uint32 Index = 0u;

    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECTALGPARAMS_ID, RAMTST_E_UNINIT);
    }
    else if (RAMTST_EXECUTION_STOPPED != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECTALGPARAMS_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
    {
        /* MISRC */
    }

    if (NULL_PTR != RamTstConfig)
    {
#if (RAMTST_ALGPARAMS_NUM > 1u)
        for (Index = 0u; Index < RAMTST_ALGPARAMS_NUM; Index++)
#endif /* #if (RAMTST_ALGPARAMS_NUM > 1u) */
        {
            if (NewAlgParamsId == RamTstConfig->RamTstConfigParams.RamTstAlgParams[Index].RamTstAlgParamsId)
            {
                Flag = 1u;
#if (RAMTST_ALGPARAMS_NUM > 1u)
                break;
#endif /* #if (RAMTST_ALGPARAMS_NUM > 1u) */
            }
        }
    }
    else
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECTALGPARAMS_ID, RAMTST_E_PARAM_POINTER);
    }

    if (0u == Flag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECTALGPARAMS_ID, RAMTST_E_OUT_OF_RANGE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        CurRamTstAlgParamsId = NewAlgParamsId;
        /* The function RamTst_SelectAlgParams shall reinitialize all
        RAM Test relevant registers and global variables with the values
        for the鈥淣ewAlgParamsId鈥�.
        SWS_RamTst_00085  */
        RamTst_InitAllBlockStatus();
        RamTstNumberOfTestedCellsUse =
            RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)]
                .RamTstNumberOfTestedCells;
        NowBackTestBlockIndex = RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)]
                                    .RamTstBlockParams[0]
                                    .RamTstBlockId;
        NowAlgParamTestedBlockNumber = 0;
    }
}
#endif

#if RAMTST_CHANGE_NUM_OF_TESTED_CELLS_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service changes the current number of tested cells
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      RamTst_NumberOfTestedCellsType
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_ChangeNumberOfTestedCells(RamTst_NumberOfTestedCellsType NewNumberOfTestedCells)
{
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)
            Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_CHANGENUMBEROFTESTEDCELLS_ID, RAMTST_E_UNINIT);
    }
    else if (RAMTST_EXECUTION_STOPPED != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(
            RAMTST_MODULE_ID,
            RAMTST_INSTANCE_ID,
            RAMTST_CHANGENUMBEROFTESTEDCELLS_ID,
            RAMTST_E_STATUS_FAILURE);
    }
    else if (
        (RamTstConfig->RamTstConfigParams.RamTstMinNumberOfTestedCells > NewNumberOfTestedCells)
        || (RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)]
                .RamTstMaxNumberOfTestedCells
            < NewNumberOfTestedCells))
    {
        (void)Det_ReportError(
            RAMTST_MODULE_ID,
            RAMTST_INSTANCE_ID,
            RAMTST_CHANGENUMBEROFTESTEDCELLS_ID,
            RAMTST_E_OUT_OF_RANGE);
    }
    else if (NewNumberOfTestedCells > ((uint32)RAM_SAFERESERVEAREA_END - (uint32)RAM_SAFERESERVEAREA_START + 1uL))
    {
        /* RamTst_ExecMarchCTestWithMemcpy will use RamTstNumberOfTestedCellsUse, so it must not big than the safe
         * reserve area size */
        (void)Det_ReportError(
            RAMTST_MODULE_ID,
            RAMTST_INSTANCE_ID,
            RAMTST_CHANGENUMBEROFTESTEDCELLS_ID,
            RAMTST_E_OUT_OF_RANGE);
    }
    else if (0u != (NewNumberOfTestedCells % 4u))
    {
        /* NewNumberOfTestedCells Must be Multiple of 4 */
        (void)Det_ReportError(
            RAMTST_MODULE_ID,
            RAMTST_INSTANCE_ID,
            RAMTST_CHANGENUMBEROFTESTEDCELLS_ID,
            RAMTST_E_OUT_OF_RANGE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        RamTstNumberOfTestedCellsUse = NewNumberOfTestedCells;
    }
}
#endif

#if RAMTST_RUN_FULL_TEST_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service for executing the full RAM Test in the foreground.
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_RunFullTest(void)
{
    uint8 RamTestFlag;
    uint32 iloop;
    const RamTst_AlgParams* RamTstAlgParamsPtr;
    const RamTst_BlockParams* RamTstBlockParamsPtr;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNFULLTEST_ID, RAMTST_E_UNINIT);
    }
    else if (RAMTST_EXECUTION_STOPPED != CurRamTstExecutionStatus)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNFULLTEST_ID, RAMTST_E_STATUS_FAILURE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        CurRamTstExecutionStatus = RAMTST_EXECUTION_RUNNING;

        if (NULL_PTR != RamTstConfig)
        {
            RamTstOverallTestResult = RAMTST_RESULT_UNDEFINED;
            RamTstAlgParamsPtr = &RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)];
            /* just test CurRamTstAlgParamsId indicate blocks */
            SchM_Enter_RamTst_RAMTST_EXCLUSIVE_AREA();
            for (iloop = 0; iloop < RamTstAlgParamsPtr->RamTstNumberOfBlocks; iloop++)
            {
                RamTstBlockParamsPtr = &RamTstAlgParamsPtr->RamTstBlockParams[iloop];
                /* Only matched algorithms can be tested  */
                if ((BLOCK_TEST_USED_METHOD_FOREGROUND == RamTstBlockParamsPtr->BlockTestUseMethod)
                    || (BLOCK_TEST_USED_METHOD_BOTH == RamTstBlockParamsPtr->BlockTestUseMethod))
                {
                    if (BLOCK_HAS_TESTED != RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].IsBlockTestedFlag)
                    {
                        RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].BlockTestResult =
                            RAMTST_RESULT_UNDEFINED;
                        if (RAMTEST_DESTRUCTIVE == RamTstBlockParamsPtr->RamTstTestPolicy)
                        {
                            RamTestFlag = RamTst_DoTestWithoutMemcpy(
                                RamTstAlgParamsPtr->RamTstAlgorithm,
                                RamTstBlockParamsPtr->RamTstStartAddress,
                                RamTstBlockParamsPtr->RamTstEndAddress,
                                RamTstBlockParamsPtr->RamTstFillPattern);
                        }
                        else
                        {
                            RamTestFlag = RamTst_DoTestWithMemcpy(
                                RamTstAlgParamsPtr->RamTstAlgorithm,
                                RamTstBlockParamsPtr->RamTstStartAddress,
                                RamTstBlockParamsPtr->RamTstEndAddress,
                                RAM_SAFERESERVEAREA_START);
                        }

                        /* check test result */
                        if (E_OK == RamTestFlag)
                        {
                            RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].BlockTestResult = RAMTST_RESULT_OK;
                        }
                        else
                        {
                            RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].BlockTestResult =
                                RAMTST_RESULT_NOT_OK;
                            RamTstOverallTestResult = RAMTST_RESULT_NOT_OK;
#if RAMTST_DEM_RUNFL_RAM_FAILURE_ENABLE
                            /* report the production error RAMTST_RUNFL_RAM_FAILURE to the DEM */
                            Dem_ReportErrorStatus(RAMTST_RUNFL_RAM_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
                        }
                        RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].IsBlockTestedFlag = BLOCK_HAS_TESTED;
                    }
                }
            }
            SchM_Exit_RamTst_RAMTST_EXCLUSIVE_AREA();
            RamTst_UpdateOverallTestResult();
        }
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
        else
        {
            (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNFULLTEST_ID, RAMTST_E_PARAM_POINTER);
        }
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
        /* set it back to RAMTST_EXECUTION_STOPPED before returning */
        CurRamTstExecutionStatus = RAMTST_EXECUTION_STOPPED;
    }
}
#endif

#if RAMTST_RUN_PARTIAL_TEST_API_ENABLE
/*************************************************************************/
/* RamTst
 * Brief               Service for testing one RAM block in the foreground
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      BlockId锛欼dentifies the single RAM block to be tested in the selected set of RamTstAlgParams.
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_RunPartialTest(RamTst_NumberOfBlocksType BlockId)
{
    uint8 RamTestFlag;
    const RamTst_AlgParams* RamTstAlgParamsPtr;
    const RamTst_BlockParams* RamTstBlockParamsPtr;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNPARTIALTEST_ID, RAMTST_E_UNINIT);
    }
    else if (
        (RAMTST_EXECUTION_STOPPED != CurRamTstExecutionStatus)
        && (RAMTST_EXECUTION_SUSPENDED != CurRamTstExecutionStatus))
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNPARTIALTEST_ID, RAMTST_E_STATUS_FAILURE);
    }
    else if (E_NOT_OK == RamTst_CheckBlockIDIsOutOfRange(BlockId))
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNPARTIALTEST_ID, RAMTST_E_OUT_OF_RANGE);
    }
    else
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        /* save the old test exec status */
        CurRamTstExecutionStatus = RAMTST_EXECUTION_RUNNING;
        if (NULL_PTR != RamTstConfig)
        {
            RamTstAlgParamsPtr = &RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)];
            RamTstBlockParamsPtr = &RamTstAlgParamsPtr->RamTstBlockParams[(uint16)(BlockId - 1u)];
            if (BLOCK_HAS_TESTED != RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].IsBlockTestedFlag)
            {
                /* Only matched algorithms can be tested  */
                if ((BLOCK_TEST_USED_METHOD_FOREGROUND == RamTstBlockParamsPtr->BlockTestUseMethod)
                    || (BLOCK_TEST_USED_METHOD_BOTH == RamTstBlockParamsPtr->BlockTestUseMethod))
                {
                    RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].BlockTestResult = RAMTST_RESULT_UNDEFINED;
                    SchM_Enter_RamTst_RAMTST_EXCLUSIVE_AREA();
                    /* just test CurRamTstAlgParamsId indicate blocks */
                    if (RAMTEST_DESTRUCTIVE == RamTstBlockParamsPtr->RamTstTestPolicy)
                    {
                        RamTestFlag = RamTst_DoTestWithoutMemcpy(
                            RamTstAlgParamsPtr->RamTstAlgorithm,
                            RamTstBlockParamsPtr->RamTstStartAddress,
                            RamTstBlockParamsPtr->RamTstEndAddress,
                            RamTstBlockParamsPtr->RamTstFillPattern);
                    }
                    else
                    {
                        RamTestFlag = RamTst_DoTestWithMemcpy(
                            RamTstAlgParamsPtr->RamTstAlgorithm,
                            RamTstBlockParamsPtr->RamTstStartAddress,
                            RamTstBlockParamsPtr->RamTstEndAddress,
                            RAM_SAFERESERVEAREA_START);
                    }
                    SchM_Exit_RamTst_RAMTST_EXCLUSIVE_AREA();
                    if (E_OK == RamTestFlag)
                    {
                        RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].BlockTestResult = RAMTST_RESULT_OK;
                    }
                    else
                    {
                        RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].BlockTestResult = RAMTST_RESULT_NOT_OK;
                        RamTstOverallTestResult = RAMTST_RESULT_NOT_OK;
#if RAMTST_DEM_PART_RAM_FAILURE_ENABLE
                        /*  report the production error RAMTST_PART_RAM_FAILURE to the DEM */
                        Dem_ReportErrorStatus(RAMTST_PART_RAM_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
                    }

                    RamTstAllBlockInfo[RamTstBlockParamsPtr->RamTstBlockId].IsBlockTestedFlag = BLOCK_HAS_TESTED;
                }
            }
        }
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
        else
        {
            (void)
                Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUNPARTIALTEST_ID, RAMTST_E_PARAM_POINTER);
        }
#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    }
}
#endif

/*************************************************************************/
/* RamTst
 * Brief               Scheduled function for executing the RAM Test in the background
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI
 */
/*************************************************************************/
void RamTst_MainFunction(void)
{
    boolean finish = FALSE;
    boolean flag = FALSE;
    uint8 RamTestFlag;
    const RamTst_AlgParams* RamTstAlgParamsPtr;
    const RamTst_BlockParams* RamTstBlockParamsPtr;
#if (STD_ON == RAMTST_DEV_ERROR_DETECT)
    if (RAMTST_INIT_NOT == RamTstDeInitFlag)
    {
        (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETMAINFUNCTION_ID, RAMTST_E_UNINIT);
    }

    if ((BLOCK_TEST_USED_METHOD_BACKGROUND == RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestUseMethodUse)
        || (BLOCK_TEST_USED_METHOD_BOTH == RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestUseMethodUse))
    {
        if (RAMTEST_DESTRUCTIVE == RamTstAllBlockInfo[NowBackTestBlockIndex].TestPolicyUse)
        {
            (void)
                Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GETMAINFUNCTION_ID, RAMTST_E_OUT_OF_RANGE);
        }
    }

#endif /* STD_ON == RAMTST_DEV_ERROR_DETECT */
    {
        RamTstAlgParamsPtr = &RamTstConfig->RamTstConfigParams.RamTstAlgParams[(uint8)(CurRamTstAlgParamsId - 1u)];

        if (RAMTST_EXECUTION_RUNNING == CurRamTstExecutionStatus)
        {
            if (CurRamTstAlgParamsId == RamTstAllBlockInfo[NowBackTestBlockIndex].RamTstAlgParamsIdUse)
            {
                if (BLOCK_HAS_TESTED != RamTstAllBlockInfo[NowBackTestBlockIndex].IsBlockTestedFlag)
                {
                    /* Only matched algorithms can be tested  */
                    if ((BLOCK_TEST_USED_METHOD_BACKGROUND
                         == RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestUseMethodUse)
                        || (BLOCK_TEST_USED_METHOD_BOTH
                            == RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestUseMethodUse))
                    {
                        flag = TRUE;
                        /* back test must be none destuctive and need save and recover */
                        if (RAMTEST_DESTRUCTIVE == RamTstAllBlockInfo[NowBackTestBlockIndex].TestPolicyUse)
                        {
                            flag = FALSE;
                        }
                    }
                }
            }
            /* match the test conditions */
            if (TRUE == flag)
            {
                RamTstBlockParamsPtr = &RamTstAlgParamsPtr->RamTstBlockParams[(uint16)(NowAlgParamTestedBlockNumber)];
                /* calc now test final addr */
                if ((RamTstBlockParamsPtr->RamTstEndAddress)
                    < (uint32)(RamTstAllBlockInfo[NowBackTestBlockIndex].FinalEndAddr + RamTstNumberOfTestedCellsUse
                               - 1u))
                {
                    RamTstAllBlockInfo[NowBackTestBlockIndex].FinalEndAddr = RamTstBlockParamsPtr->RamTstEndAddress;
                }
                else
                {
                    RamTstAllBlockInfo[NowBackTestBlockIndex].FinalEndAddr +=
                        (uint32)(RamTstNumberOfTestedCellsUse - 1u);
                }
                /* exec test */
                RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestResult = RAMTST_RESULT_UNDEFINED;
                SchM_Enter_RamTst_RAMTST_EXCLUSIVE_AREA();
                RamTestFlag = RamTst_DoTestWithMemcpy(
                    RamTstAlgParamsPtr->RamTstAlgorithm,
                    RamTstAllBlockInfo[NowBackTestBlockIndex].NowTestedAddr,
                    RamTstAllBlockInfo[NowBackTestBlockIndex].FinalEndAddr,
                    RAM_SAFERESERVEAREA_START);
                SchM_Exit_RamTst_RAMTST_EXCLUSIVE_AREA();

                if (E_OK == RamTestFlag)
                {
                    /* here no need to do anything */
                }
                else
                {
                    RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestResult = RAMTST_RESULT_NOT_OK;
                    RamTstOverallTestResult = RAMTST_RESULT_NOT_OK;
                    /* has error, this block not test continue */
                    if ((uint16)(NowAlgParamTestedBlockNumber + 1u) <= RamTstAlgParamsPtr->RamTstNumberOfBlocks)
                    {
                        NowAlgParamTestedBlockNumber++;
                        NowBackTestBlockIndex++;
                    }
                    else
                    {
                        finish = TRUE;
                    }
                    RamTstAllBlockInfo[NowBackTestBlockIndex].IsBlockTestedFlag = BLOCK_HAS_TESTED;
                    /*  report the production error RAMTST_MAIN_RAM_FAILURE to the DEM */
#if RAMTST_DEM_MAIN_RAM_FAILURE_ENABLE
                    Dem_ReportErrorStatus(RAMTST_MAIN_RAM_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
#if RAMTST_TEST_ERROR_NOTIFICATION_API_ENABLE
                    if (NULL_PTR != RamTstConfig->RamTstConfigParams.RamTst_ErrorNotificationPtr)
                    {
                        RamTstConfig->RamTstConfigParams.RamTst_ErrorNotificationPtr();
                    }
#endif
                }

                /* check if test over */
                if (RAMTST_RESULT_NOT_OK != RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestResult)
                {
                    if (RamTstAllBlockInfo[NowBackTestBlockIndex].FinalEndAddr
                        == RamTstBlockParamsPtr->RamTstEndAddress)
                    {
                        /* now block has test over */
                        RamTstAllBlockInfo[NowBackTestBlockIndex].BlockTestResult = RAMTST_RESULT_OK;
                        RamTstAllBlockInfo[NowBackTestBlockIndex].IsBlockTestedFlag = BLOCK_HAS_TESTED;
                        if ((uint16)(NowAlgParamTestedBlockNumber + 1u) <= RamTstAlgParamsPtr->RamTstNumberOfBlocks)
                        {
                            NowAlgParamTestedBlockNumber++;
                            NowBackTestBlockIndex++;
                        }
                        else
                        {
                            finish = TRUE;
                        }
                    }
                }
                if (BLOCK_HAS_TESTED != RamTstAllBlockInfo[NowBackTestBlockIndex].IsBlockTestedFlag)
                {
                    /* calc next test start addr */
                    RamTstAllBlockInfo[NowBackTestBlockIndex].NowTestedAddr += RamTstNumberOfTestedCellsUse;
                    RamTstAllBlockInfo[NowBackTestBlockIndex].FinalEndAddr += (uint32)(1);
                }
                RamTst_UpdateOverallTestResult();
            }
            else
            {
                /* this block not match the test conditions  or this block has tested, test next block */
                if ((uint16)(NowAlgParamTestedBlockNumber + 1u) <= RamTstAlgParamsPtr->RamTstNumberOfBlocks)
                {
                    NowAlgParamTestedBlockNumber++;
                    NowBackTestBlockIndex++;
                }
                else
                {
                    finish = TRUE;
                }
            }
        }
        /* check if all test has finished */
        if (TRUE == finish)
        {
            /* Once you've tested over, start over from the first block */
            NowBackTestBlockIndex = RamTstAlgParamsPtr->RamTstBlockParams[0].RamTstBlockId;
            NowAlgParamTestedBlockNumber = 0;
#if RAMTST_TEST_COMPLETE_NOTIFICATION_API_ENABLE
            if (NULL_PTR != RamTstConfig->RamTstConfigParams.RamTst_TestCompletedNotificationPtr)
            {
                RamTstConfig->RamTstConfigParams.RamTst_TestCompletedNotificationPtr();
            }
#endif
            RamTst_InitAllBlockStatus();
        }
    }
}

#define RAMTST_STOP_SEC_CODE
#include "RamTst_MemMap.h"
