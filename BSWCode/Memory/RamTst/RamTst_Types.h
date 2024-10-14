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
 **  FILENAME    : RamTst_Types.h                                              **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : Xin.Liu                                                     **
 **  Vendor      :                                                             **
 **  DESCRIPTION : ram test types                                              **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef RAMTST_TYPES_H_
#define RAMTST_TYPES_H_

#include "Std_Types.h"
#include "RamTst_Cfg.h"

typedef uint8 RamTst_AlgParamsIdType;
typedef uint32 RamTst_NumberOfTestedCellsType;
typedef uint16 RamTst_NumberOfBlocksType;

/**********************************  enum   ****************************************/
typedef enum
{
    RAMTST_EXECUTION_UNINIT = 0x0, /* The RAM Test is not initialized or not usable */
    RAMTST_EXECUTION_STOPPED,      /* The RAM Test is stopped and ready to be started in foreground or to be allowed in
                                      background */
    RAMTST_EXECUTION_RUNNING,      /* The RAM Test is currently running. */
    RAMTST_EXECUTION_SUSPENDED,    /* The RAM Test is currently running. */
} RamTst_ExecutionStatusType;

typedef enum
{
    RAMTST_RESULT_NOT_TESTED = 0x0, /* The RAM Test is not executed. */
    RAMTST_RESULT_OK,               /* The RAM Test has been tested with OK result */
    RAMTST_RESULT_NOT_OK,           /* The RAM Test has been tested with NOTOK result. */
    RAMTST_RESULT_UNDEFINED,        /* The RAM Test is currently running. */
} RamTst_TestResultType;

typedef enum
{
    RAMTST_ALGORITHM_UNDEFINED = 0x0, /* Undefined algorithm (uninitialized value) */
    RAMTST_CHECKERBOARD_TEST,         /* Checkerboard test algorithm */
    RAMTST_MARCH_TEST,                /* March test algorithm */
    RAMTST_WALK_PATH_TEST,            /* Walk path test algorithm */
    RAMTST_GALPAT_TEST,               /* Galpat test algorithm */
    RAMTST_TRANSP_GALPAT_TEST,        /* Transparent Galpat test algorithm */
    RAMTST_ABRAHAM_TEST,              /* Abraham test algorithm */
} RamTst_AlgorithmType;

typedef enum
{
    RAMTEST_DESTRUCTIVE = 0x0, /* RAM test does not restore memory content. */
    RAMTEST_NON_DESTRUCTIVE,   /* RAM test restores memory content. */
} RamTst_Policy;

typedef enum
{
    /*RamTst Uninit*/
    RAMTST_INIT_NOT,
    /*RamTst init*/
    RAMTST_INIT_OK
} RamTst_ModeInitStatusType;

typedef enum
{
    BLOCK_TEST_USED_METHOD_NONE = 0x0, /* no method use */
    BLOCK_TEST_USED_METHOD_FOREGROUND, /* only foreground */
    BLOCK_TEST_USED_METHOD_BACKGROUND, /* only background */
    BLOCK_TEST_USED_METHOD_BOTH,       /* both foreground and background */
} RamTst_BlockTestUseMethod;

typedef enum
{
    BLOCK_NOT_TEST = 0x0,
    BLOCK_HAS_TESTED,
} RamTst_IsBlockTestedFlag;

/**********************************  config types   ****************************************/

typedef struct
{
    RamTst_IsBlockTestedFlag IsBlockTestedFlag;
    RamTst_TestResultType BlockTestResult;
    uint32 NowTestedAddr; /* The address to which the block is currently tested */
    uint32 FinalEndAddr;
    RamTst_Policy TestPolicyUse;
    RamTst_AlgParamsIdType RamTstAlgParamsIdUse;
    RamTst_BlockTestUseMethod
        BlockTestUseMethodUse; /* Block use foreground test or background test  0:foreground  1:background   2:both */
} RamTst_BlockInfoType;

typedef struct
{
    uint16 RamTstBlockId; /* 1 ~ 65535 */
    uint32 RamTstEndAddress;
    uint32 RamTstStartAddress;
    uint32 RamTstFillPattern;
    RamTst_Policy RamTstTestPolicy;
    RamTst_BlockTestUseMethod BlockTestUseMethod; /* Block use foreground test or background test  0：initial
                                                     1:foreground  2:background   3:both */
} RamTst_BlockParams;

typedef struct
{
    RamTst_AlgorithmType RamTstAlgorithm; /* This is the algorithm for which this RamTstAlgParams set is defined.  */
    RamTst_AlgParamsIdType
        RamTstAlgParamsId; /* This is the identifier by which this RamTstAlgParams set can be selected  1 ~ 255*/
    RamTst_NumberOfTestedCellsType RamTstExtNumberOfTestedCells;
    RamTst_NumberOfTestedCellsType RamTstMaxNumberOfTestedCells;
    RamTst_NumberOfBlocksType RamTstNumberOfBlocks;
    RamTst_NumberOfTestedCellsType RamTstNumberOfTestedCells; /* This is the initial value for a RAM variable */
    const RamTst_BlockParams* RamTstBlockParams;
} RamTst_AlgParams;

typedef struct
{
    boolean RamTstAbrahamTestSelected;
    boolean RamTstCheckerboardTestSelected;
    boolean RamTstGalpatTestSelected;
    boolean RamTstMarchTestSelected;
    boolean RamTstTranspGalpatTestSelected;
    boolean RamTstWalkPathTestSelected;
} RamTst_Algorithms;

typedef struct
{
    RamTst_AlgParamsIdType RamTstDefaultAlgParamsId;
    RamTst_NumberOfTestedCellsType RamTstMinNumberOfTestedCells;
    uint8 RamTstNumberOfAlgParamSets;
    const RamTst_AlgParams* RamTstAlgParams;
#if RAMTST_TEST_COMPLETE_NOTIFICATION_API_ENABLE
    void (*RamTst_TestCompletedNotificationPtr)(void);
#endif
#if RAMTST_TEST_ERROR_NOTIFICATION_API_ENABLE
    void (*RamTst_ErrorNotificationPtr)(void);
#endif
} RamTst_ConfigParams;

typedef struct
{
    RamTst_ConfigParams RamTstConfigParams;
    RamTst_Algorithms RamTstAlgorithms;
} RamTst_ConfigType;

#endif /* RAMTST_TYPES_H_ */
