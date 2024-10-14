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
 **                                                                           **
 **  FILENAME    : CDD_FOTA.c                                                 **
 **                                                                           **
 **  Created on  : 2020/5/11 16:59:43                                         **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION : function define                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                     **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

/**
  \page ISOFT_MISRA_Exceptions  MISRA-C:2012 Compliance Exceptions
    ModeName:CDD_FOTA<br>
  RuleSorce:puhua-rule.rcf 2.3.1

    \li PRQA S 3432 MISRA Rule 20.7 .<br>
    Reason:Function-like macros are used to allow more efficient code.

    \li PRQA S 1532 MISRA Rule 8.7 .<br>
    Reason:In order to make the module code structure clear, the functions are classified.

    \li PRQA S 0791 MISRA Rule 5.4 .<br>
    Reason:Configuration data design is required.

    \li PRQA S 1533 MISRA Rule 8.9 .<br>
    Reason:Configuration data design is required.

    \li PRQA S 1531 MISRA Rule 8.7 .<br>
    Reason:Configuration data design is required.

    \li PRQA S 3218 MISRA Rule 8.9 .<br>
    Reason:Variable information needs to be stored and used later.

    \li PRQA S 3673 MISRA Rule 8.13 .<br>
    Reason:autosar require.
 */

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "CDD_FOTA.h"
#include "NvM.h"
#include "CDD_FOTA_Callout.h"
#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
#include "Crc.h"
#endif /* CDD_FOTA_CRC != CDD_FOTA_NONE_CRC */

/*******************************************************************************
**                       Version  Check                                       **
*******************************************************************************/
#ifndef CDD_FOTA_AR_RELEASE_MAJOR_VERSION
#error : "CDD_FOTA miss version"
#endif
#ifndef CDD_FOTA_AR_RELEASE_MINOR_VERSION
#error : "CDD_FOTA miss version"
#endif
#ifndef CDD_FOTA_AR_RELEASE_PATCH_VERSION
#error : "CDD_FOTA miss version"
#endif
#if (                                                                              \
    (1u != CDD_FOTA_CFG_SW_MAJOR_VERSION) || (0u != CDD_FOTA_CFG_SW_MINOR_VERSION) \
    || (1u != CDD_FOTA_CFG_SW_PATCH_VERSION))
#error : "CDD_FOTA mismatch cfg version"
#endif

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
typedef enum
{
    CDD_FOTA_UNCOMPRESS_IDLE,
    CDD_FOTA_UNCOMPRESS_NEEDCALL,
    CDD_FOTA_UNCOMPRESS_NEEDRET,
    CDD_FOTA_UNCOMPRESS_NEEDTRANS,
} CDD_FOTA_UncompressTypes;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
/* PRQA S 0791++ */ /* MISRA Rule 5.4 */
#define CDD_FOTA_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "CDD_FOTA_MemMap.h"
CDD_FOTA_LOCAL CDD_FOTA_ModeType CDD_FOTA_Mode = CDD_FOTA_MODE_UNINIT;
#define CDD_FOTA_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "CDD_FOTA_MemMap.h"

#define CDD_FOTA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CDD_FOTA_MemMap.h"
CDD_FOTA_LOCAL CDD_FOTA_ProgramInfoType CDD_FOTA_ProgramInfo;
CDD_FOTA_LOCAL CDD_FOTA_StatusType CDD_FOTA_RunTimeStatus;
#define CDD_FOTA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CDD_FOTA_MemMap.h"

#define CDD_FOTA_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "CDD_FOTA_MemMap.h"
CDD_FOTA_LOCAL boolean CDD_FOTA_NeedStoreFlag = FALSE;
CDD_FOTA_LOCAL boolean CDD_FOTA_StopProtocolFlag = FALSE;
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
CDD_FOTA_LOCAL CDD_FOTA_UncompressTypes CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
#define CDD_FOTA_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "CDD_FOTA_MemMap.h"
/* PRQA S 0791-- */ /* MISRA Rule 5.4 */

#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
#define CDD_FOTA_START_SEC_VAR_CLEARED_8
#include "CDD_FOTA_MemMap.h"
/* PRQA S 3218++ */ /* MISRA Rule 8.9 */
CDD_FOTA_LOCAL uint8 CDD_FOTA_Buffer[CDD_FOTA_UNCOMPRESS_BUF_SIZE];
/* PRQA S 3218-- */ /* MISRA Rule 8.9 */
#define CDD_FOTA_STOP_SEC_VAR_CLEARED_8
#include "CDD_FOTA_MemMap.h"
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/
#define CDD_FOTA_START_SEC_CODE
#include "CDD_FOTA_MemMap.h"
CDD_FOTA_LOCAL void CDD_FOTA_StoreProgramInfo(void);

CDD_FOTA_LOCAL void CDD_FOTA_Program(void);

#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
CDD_FOTA_LOCAL void CDD_FOTA_CRCCalculate(void);
#endif

CDD_FOTA_LOCAL void CDD_FOTA_EraseCancelInstall(void);

CDD_FOTA_LOCAL void CDD_FOTA_CheckStoreFlag(void);

CDD_FOTA_LOCAL uint32 CDD_FOTA_GetCurrentBreakPoint(void);

#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
CDD_FOTA_LOCAL void CDD_FOTA_Uncompress(void);
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
#define CDD_FOTA_STOP_SEC_CODE
#include "CDD_FOTA_MemMap.h"

/******************************************************************************
**                      Global Variable Definitions                         **
******************************************************************************/
#define CDD_FOTA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CDD_FOTA_MemMap.h"
CDD_FOTA_ProgramRunTimeInfoType CDD_FOTA_ProgramRunTimeInfo;
#define CDD_FOTA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CDD_FOTA_MemMap.h"

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
/*
 * Brief               CDD_FOTA pre initialize
 * ServiceId           0x00
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 * PreCondition        N/A
 * CallByAPI           EcuM mode
 */
#define CDD_FOTA_START_SEC_CODE
#include "CDD_FOTA_MemMap.h"
void CDD_FOTA_PreInit(void)
{
    NvM_RequestResultType RequestResult;
    CDD_FOTA_MemSet(((uint8*)(&CDD_FOTA_ProgramInfo)), 0x0u, sizeof(CDD_FOTA_ProgramInfoType));
    if (E_OK == NvM_GetErrorStatus(CDD_FOTA_NVM_BLOCKID, &RequestResult))
    {
        if (NVM_REQ_OK == RequestResult)
        {
            /*get ProgramInfo from NvM*/
            CDD_FOTA_MemCopy(
                (uint8*)&CDD_FOTA_ProgramInfo,
                (const uint8*)NvM_BlockDescriptor[CDD_FOTA_NVM_BLOCKID - 1u].NvmRamBlockDataAddress,
                sizeof(CDD_FOTA_ProgramInfoType));
        }
    }
    /*first to write another app ,need set ProcessedAddress to another app jump address*/
    CDD_FOTA_GetProcessedAddress_Callout(&CDD_FOTA_ProgramInfo);
    CDD_FOTA_ProgramRunTimeInfo.CancelInstall = CDD_FOTA_NO_ERASE;
    CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
    CDD_FOTA_RunTimeStatus = CDD_FOTA_IDLE;
    CDD_FOTA_Mode = CDD_FOTA_MODE_INIT;
}

/*
 * Brief               CDD_FOTA Complete initialization
 * ServiceId           0x01
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     FOTAStatus:CDD_FOTA Status
 *                     ErrorCode:NRC
 * Param-Name[in/out]  N/A
 * Return              N/A
 * PreCondition        CDD_FOTA_PreInit
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_Init(CDD_FOTA_StatusType* FOTAStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_INIT, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == FOTAStatus)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_INIT, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
    {
        if ((CDD_FOTA_RunTimeStatus == CDD_FOTA_IDLE) || (CDD_FOTA_RunTimeStatus == CDD_FOTA_ERROR))
        {
            CDD_FOTA_RunTimeStatus = CDD_FOTA_INIT;
            CDD_FOTA_ProgramRunTimeInfo.Erased = FALSE;
        }
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
        CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
        CDD_FOTA_StopProtocolFlag = FALSE;
        CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_OK;
        CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
        CDD_FOTA_ProgramRunTimeInfo.LastBreakPoint = CDD_FOTA_GetCurrentBreakPoint();
        CDD_FOTA_Init_Callout();
        *FOTAStatus = CDD_FOTA_RunTimeStatus;
        ret = E_OK;
    }
    return ret;
}

/*
 * Brief               get CDD_FOTA Status
 * ServiceId           0x02
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     FOTAStatus:CDD_FOTA Status
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_GetFOTAStatus(CDD_FOTA_StatusType* FOTAStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETFOTASTATUS, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == FOTAStatus)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETFOTASTATUS, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
    {
        *FOTAStatus = CDD_FOTA_RunTimeStatus;
        ret = E_OK;
    }
    return ret;
}

/*
 * Brief               get AppVersion
 * ServiceId           0x10
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     AppVersion: AppVersion
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_GetAppVersion(uint8* AppVersion)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETAPPVERSION, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == AppVersion)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETAPPVERSION, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
    {
        ret = CDD_FOTA_GetAppVersion_Callout(AppVersion);
    }
    return ret;
}

/*
 * Brief               set AppVersion
 * ServiceId           0x11
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     AppVersion: AppVersion
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_SetAppVersion(const uint8* AppVersion)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_SETAPPVERSION, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == AppVersion)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_SETAPPVERSION, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
    {
        ret = CDD_FOTA_SetAppVersion_Callout(AppVersion);
    }
    return ret;
}

/*
 * Brief               get CDD_FOTA last program successed address info
 * ServiceId           0x03
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     MemoryAddress:program successed address
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_GetFOTAProcessedInfo(uint32* MemoryAddress)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETFOTAPROCESSEDINFO, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == MemoryAddress)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETFOTAPROCESSEDINFO, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
    {
        *MemoryAddress = CDD_FOTA_ProgramInfo.ProcessedAddress;
        ret = E_OK;
    }
    return ret;
}

/*
 * Brief               get CDD_FOTA last default breakpoint
 * ServiceId           0x0F
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     MemoryAddress:program successed address
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_GetFOTAbreakpointInfo(uint32* MemoryAddress)
{
    Std_ReturnType ret;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    ret = E_NOT_OK;
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETBREAKPOINT, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == MemoryAddress)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETBREAKPOINT, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
    {
        *MemoryAddress = CDD_FOTA_GetCurrentBreakPoint();
        CDD_FOTA_RunTimeStatus = CDD_FOTA_INIT;
        ret = E_OK;
    }
    return ret;
}

/*
 * Brief               CDD_FOTA Process download
 * ServiceId           0x0A
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      MemoryAddress:program address
 *                     MemorySize:program size
 * Param-Name[out]     ErrorCode:NRC
 *                     BlockLength:buffer length
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_Processdownload(
    uint32 MemoryAddress,
    uint32 MemorySize,
    uint32* BlockLength,
    Dcm_NegativeResponseCodeType* ErrorCode)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_PROCESSDOWNLOAD, CDD_FOTA_E_UNINIT);
    }
    else if ((NULL_PTR == BlockLength) || (NULL_PTR == ErrorCode))
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_PROCESSDOWNLOAD, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
        if ((CDD_FOTA_RunTimeStatus != CDD_FOTA_INIT)
            || ((FALSE == CDD_FOTA_ProgramRunTimeInfo.Erased)
#if (STD_ON == CDD_FOTA_SBL_ENABLE)
                && (TRUE == CDD_FOTA_CheckSblDownload())
#endif /* STD_ON == CDD_FOTA_SBL_ENABLE */
                    ))
    {
        *ErrorCode = DCM_E_UPLOADDOWNLOADNOTACCEPTED;
        CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
    }
    else if (CDD_FOTA_ProgramRunTimeInfo.CancelInstall != CDD_FOTA_NO_ERASE)
    {
        *ErrorCode = DCM_E_RESPONSE_PENDING;
        ret = DCM_E_PENDING;
    }
    else
    {
        uint32 TempMemoryAddress = CDD_FOTA_ConvertAddress(MemoryAddress);
        uint32 blockstartAddress;
        uint32 blocklen;
        uint32 blockend;
        boolean Find = FALSE;

#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
        CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
        for (uint8 iloop = 0; ((iloop < (CDD_FOTA_APP_B_BOLCK_NUM + CDD_FOTA_APP_A_BOLCK_NUM)) && (Find == FALSE));
             iloop++)
        {
            blockstartAddress = CDD_FOTA_ConvertAddress(CDD_FOTA_WriteMemoryRange[iloop].WriteMemoryRangeLow);
            blocklen = CDD_FOTA_WriteMemoryRange[iloop].length;
            blockend = CDD_FOTA_ConvertAddress(CDD_FOTA_WriteMemoryRange[iloop].WriteMemoryRangeHigh);
            if ((TempMemoryAddress >= blockstartAddress) && (TempMemoryAddress <= blockend)
                && ((TempMemoryAddress + MemorySize) <= (blockstartAddress + blocklen)) && (MemorySize <= blocklen)
                && (MemorySize > 0u))
            {
                Find = TRUE;
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
                if (CDD_FOTA_WriteMemoryRange[iloop].UncompressEnable == TRUE)
                {
                    CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_NEEDCALL;
                    CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize = 0;
                    CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize = 0;
                    CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize = 0;
                }
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
            }
        }
#if (STD_ON == CDD_FOTA_SBL_ENABLE)
        blockstartAddress = CDD_FOTA_ConvertAddress(CDD_FOTA_SBLMemoryRange.WriteMemoryRangeLow);
        blocklen = CDD_FOTA_SBLMemoryRange.length;
        blockend = CDD_FOTA_ConvertAddress(CDD_FOTA_SBLMemoryRange.WriteMemoryRangeHigh);
        if ((Find == FALSE) && (TempMemoryAddress >= blockstartAddress) && (TempMemoryAddress <= blockend)
            && ((TempMemoryAddress + MemorySize) <= (blockstartAddress + blocklen)) && (MemorySize <= blocklen)
            && (MemorySize > 0u))
        {
            Find = TRUE;
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
            if (CDD_FOTA_SBLMemoryRange.UncompressEnable == TRUE)
            {
                CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_NEEDCALL;
                CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize = 0;
                CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize = 0;
                CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize = 0;
            }
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
        }
#endif /* STD_ON == CDD_FOTA_SBL_ENABLE */
        if (Find == TRUE)
        {
            ret = CDD_FOTA_ProcessdownloadCallout(TempMemoryAddress, MemorySize, ErrorCode);
            if (E_OK == ret)
            {
                CDD_FOTA_ProgramRunTimeInfo.StartProcessAddress = TempMemoryAddress;
                CDD_FOTA_ProgramRunTimeInfo.TotalMemorySize = MemorySize;
                CDD_FOTA_ProgramRunTimeInfo.TranSize = 0;
                CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = 0;
                CDD_FOTA_ProgramRunTimeInfo.Remainsize = 0;
                CDD_FOTA_ProgramRunTimeInfo.TotalProcessedSize = 0;
#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
                CDD_FOTA_ProgramRunTimeInfo.CRC = 0;
#endif
                *BlockLength = CDD_FOTA_PROGRAM_SIZE_ONE_REQUEST;
                CDD_FOTA_RunTimeStatus = CDD_FOTA_WAIT;
            }
            else
            {
                CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
                CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
            }
        }
        else
        {
            *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
        }
    }
    return ret;
}

/*
 * Brief               CDD_FOTA Process Erase
 * ServiceId           0x0E
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      OpStatus:Operating actions type
 *                     MemoryAddress:Erase successed address
 *                     MemorySize:Erase successed size
 * Param-Name[out]     ErrorCode:NRC
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                                E_NOT_OK:failed
 *                                                DCM_E_PENDING:pending
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_Erase(const uint8* InBuffer, Dcm_NegativeResponseCodeType* ErrorCode)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_ERASE, CDD_FOTA_E_UNINIT);
    }
    else
#endif
        if (InBuffer[0] != 0x44u)
    {
        *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        uint8 index;
        boolean Find = FALSE;
        uint32 MemoryAddress = 0;
        uint32 MemorySize = 0;

        if (CDD_FOTA_ProgramRunTimeInfo.ErasePending == FALSE)
        {
            /*caculate the MemoryAddress of the request message*/
            for (index = 0; index < 4u; index++)
            {
                MemoryAddress = MemoryAddress << 8u;
                MemoryAddress = MemoryAddress | (uint32)(InBuffer[1u + index]);
            }
            for (index = 0; index < 4u; index++)
            {
                MemorySize = MemorySize << 8u;
                MemorySize = MemorySize | (uint32)InBuffer[5u + index];
            }
            for (index = 0; index < (CDD_FOTA_APP_B_BOLCK_NUM + CDD_FOTA_APP_A_BOLCK_NUM); index++)
            {
                uint32 blockstartAddress =
                    CDD_FOTA_ConvertAddress(CDD_FOTA_WriteMemoryRange[index].WriteMemoryRangeLow);
                uint32 blocklength = CDD_FOTA_WriteMemoryRange[index].length;
                uint32 blockend = CDD_FOTA_ConvertAddress(CDD_FOTA_WriteMemoryRange[index].WriteMemoryRangeHigh);
                MemoryAddress = CDD_FOTA_ConvertAddress(MemoryAddress);
                /* check if download address range of data is in flash driver block range */
                if ((MemoryAddress >= blockstartAddress) && (MemoryAddress <= blockend)
                    && ((MemoryAddress + MemorySize) <= (blockstartAddress + blocklength))
                    && (MemorySize <= blocklength) && (MemorySize > 0u))
                {
                    /* execute erase routine */
                    Find = TRUE;
                    break;
                }
            }
        }
        else
        {
            Find = TRUE;
        }
        if (TRUE == Find)
        {
            if (CDD_FOTA_RunTimeStatus != CDD_FOTA_INIT)
            {
                *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
            }
            else
            {
                uint32 Length;
                if (CDD_FOTA_ProgramRunTimeInfo.ErasePending == FALSE)
                {
                    CDD_FOTA_ProgramRunTimeInfo.EraseSize = MemorySize;
                    CDD_FOTA_ProgramRunTimeInfo.EraseAddress = MemoryAddress;
                    CDD_FOTA_ProgramRunTimeInfo.CurErasedBlockNum = index;
                    Length = MemorySize;
                    if (CDD_FOTA_ERASE_SIZE < Length)
                    {
                        Length = CDD_FOTA_ERASE_SIZE;
                    }
                    /* The return value of the callback interface is not considered here, and is processed through the
                     * result callback interface */
                    ret = CDD_FOTA_Erase_Callout(MemoryAddress, Length, ErrorCode);
                    CDD_FOTA_ProgramRunTimeInfo.ErasePending = TRUE;
                    CDD_FOTA_ProgramRunTimeInfo.LastEraseSize = Length;
                }
                CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_GetJobResult_Callout();
                switch (CDD_FOTA_ProgramRunTimeInfo.JobResult)
                {
                case CDD_FOTA_JOB_PENDING:
                    ret = DCM_E_PENDING;
                    break;
                case CDD_FOTA_JOB_OK:
                    if (CDD_FOTA_ProgramRunTimeInfo.ErasePending == TRUE)
                    {
                        CDD_FOTA_ProgramRunTimeInfo.EraseSize -= CDD_FOTA_ProgramRunTimeInfo.LastEraseSize;
                        if (CDD_FOTA_ProgramRunTimeInfo.EraseSize > 0u)
                        {
                            CDD_FOTA_ProgramRunTimeInfo.EraseAddress += CDD_FOTA_ProgramRunTimeInfo.LastEraseSize;
                            if (CDD_FOTA_ERASE_SIZE < CDD_FOTA_ProgramRunTimeInfo.EraseSize)
                            {
                                Length = CDD_FOTA_ERASE_SIZE;
                            }
                            else
                            {
                                Length = CDD_FOTA_ProgramRunTimeInfo.EraseSize;
                            }
                            CDD_FOTA_ProgramRunTimeInfo.LastEraseSize = Length;
                            ret = CDD_FOTA_Erase_Callout(CDD_FOTA_ProgramRunTimeInfo.EraseAddress, Length, ErrorCode);
                            if (E_OK == ret)
                            {
                                ret = DCM_E_PENDING;
                            }
                        }
                        else
                        {
                            CDD_FOTA_ProgramRunTimeInfo.ErasePending = FALSE;
                            CDD_FOTA_ProgramRunTimeInfo.Erased = TRUE;
                            ret = E_OK;
                        }
                    }
                    else
                    {
                        ret = E_OK;
                    }
                    break;
                default:
                    CDD_FOTA_ProgramRunTimeInfo.ErasePending = FALSE;
                    break;
                }
            }
        }
        else
        {
            *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    return ret;
}

/*
 * Brief               CDD_FOTA Process Transfer Data write
 * ServiceId           0x04
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      OpStatus:Operating actions type
 *                     MemoryIdentifier:program address format
 *                     MemoryAddress:program successed address
 *                     MemorySize:program successed size
 *                     MemoryData:program data
 * Param-Name[out]     ErrorCode:NRC
 * Param-Name[in/out]  N/A
 * Return              Dcm_ReturnWriteMemoryType: DCM_WRITE_OK: successful
 *                                                DCM_WRITE_FAILED:failed
 *                                                DCM_WRITE_PENDING:pending
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
/* PRQA S 3673++ */ /* MISRA Rule 8.13 */
Dcm_ReturnWriteMemoryType CDD_FOTA_ProcessTransferDataWrite(
    Dcm_OpStatusType OpStatus,
    uint32 MemoryAddress,
    uint32 MemorySize,
    uint8* MemoryData,
    Dcm_NegativeResponseCodeType* ErrorCode)
/* PRQA S 3673-- */ /* MISRA Rule 8.13 */
{
    Std_ReturnType ret = DCM_WRITE_FAILED;

#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_PROCESSTRANSFERDATAWRITE, CDD_FOTA_E_UNINIT);
    }
    else if ((NULL_PTR == MemoryData) || (NULL_PTR == ErrorCode))
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_PROCESSTRANSFERDATAWRITE, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
        if (((CDD_FOTA_RunTimeStatus != CDD_FOTA_WAIT) && (CDD_FOTA_RunTimeStatus != CDD_FOTA_PROCESSING))
            || ((OpStatus == DCM_INITIAL) && (0u != CDD_FOTA_ProgramRunTimeInfo.TranSize)
                && (CDD_FOTA_ProgramRunTimeInfo.TotalMemorySize <= CDD_FOTA_ProgramRunTimeInfo.TranSize)))
    {
        *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
    }
    else
    {
        if (OpStatus == DCM_INITIAL)
        {
            uint32 Address = CDD_FOTA_ConvertAddress(MemoryAddress);
            if ((Address == (CDD_FOTA_ProgramRunTimeInfo.StartProcessAddress + CDD_FOTA_ProgramRunTimeInfo.TranSize))
                && (MemorySize <= (CDD_FOTA_ProgramRunTimeInfo.TotalMemorySize - CDD_FOTA_ProgramRunTimeInfo.TranSize)))
            {
                CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = MemorySize;
                CDD_FOTA_ProgramRunTimeInfo.Remainsize = MemorySize;
                CDD_FOTA_ProgramRunTimeInfo.ProcessData = MemoryData;
                CDD_FOTA_ProgramRunTimeInfo.TranSize += MemorySize;
                *ErrorCode = DCM_E_RESPONSE_PENDING;
                ret = DCM_WRITE_PENDING;
                CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_NEED_WRITE;
                CDD_FOTA_RunTimeStatus = CDD_FOTA_PROCESSING;
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
                CDD_FOTA_ProgramRunTimeInfo.UncompressProcessData = MemoryData;
                if (CDD_FOTA_UNCOMPRESS_NEEDTRANS == CDD_FOTA_UncompressFlag)
                {
                    CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_NEEDCALL;
                }

                if (CDD_FOTA_UncompressFlag == CDD_FOTA_UNCOMPRESS_NEEDCALL)
                {
                    CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize = MemorySize;
                    CDD_FOTA_ProgramRunTimeInfo.TranUncompressProcessSize = MemorySize;
                    CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize = 0;
                }
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
            }
            else
            {
                *ErrorCode = DCM_E_TRANSFERDATASUSPENDED;
                CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
            }
        }
        else if (OpStatus == DCM_PENDING)
        {
            if (CDD_FOTA_WRITE_OK == CDD_FOTA_ProgramRunTimeInfo.WriteDone)
            {
                if (CDD_FOTA_JOB_OK == CDD_FOTA_ProgramRunTimeInfo.JobResult)
                {
                    ret = DCM_WRITE_OK;
                    CDD_FOTA_RunTimeStatus = CDD_FOTA_WAIT;
                }
                else
                {
                    *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
                    CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
                }
            }
            else
            {
                *ErrorCode = DCM_E_RESPONSE_PENDING;
                ret = DCM_WRITE_PENDING;
            }
        }
        else if (DCM_CANCEL == OpStatus)
        {
            CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
            ret = DCM_WRITE_OK;
        }
        else
        {
            /*idle*/
        }
    }
    return ret;
}

/*
 * Brief               CDD_FOTA Process Transfer Data Exit
 * ServiceId           0x0B
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      OpStatus:Operating actions type
 *                     transferRequestParameterRecord:Request Parameter Record
 *                     transferRequestParameterRecordSize:Request Parameter Record size
 * Param-Name[out]     ErrorCode:NRC
 *                     transferResponseParameterRecord:Response Parameter Record
 *                     transferResponseParameterRecordSize:Response Parameter Record size
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_ProcessExit(
    const uint8* transferRequestParameterRecord,
    uint32 transferRequestParameterRecordSize,
    uint32* transferResponseParameterRecordSize,
    Dcm_NegativeResponseCodeType* ErrorCode)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_PROCESSEXIT, CDD_FOTA_E_UNINIT);
    }
    else if (
        (NULL_PTR == transferRequestParameterRecord) || (NULL_PTR == ErrorCode)
        || (NULL_PTR == transferResponseParameterRecordSize))
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_PROCESSEXIT, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
        if ((CDD_FOTA_RunTimeStatus != CDD_FOTA_WAIT)
            || (CDD_FOTA_ProgramRunTimeInfo.TotalMemorySize != CDD_FOTA_ProgramRunTimeInfo.TranSize))
    {

        *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
    }
    else
#if (CDD_FOTA_CRC_BY_37 == STD_OFF)
        if (transferRequestParameterRecordSize > 0u)
    {
        *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
    }
    else
#endif
    {
        CDD_FOTA_CheckStoreFlag();
        *transferResponseParameterRecordSize = 0;
        CDD_FOTA_RunTimeStatus = CDD_FOTA_INIT;
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
        CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
#if (CDD_FOTA_CRC_BY_37 == STD_ON)
        if (E_NOT_OK
            == CDD_FOTA_CRCCompare(transferRequestParameterRecord, transferRequestParameterRecordSize, ErrorCode))
        {
            CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
        }
#else
        (void)(transferRequestParameterRecord);
#endif
        ret = E_OK;
    }
    return ret;
}

/*
 * Brief               Set CDD_FOTA active new app flag
 * ServiceId           0x05
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_SetFOTAActivate(void)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_SETFOTAACTIVATE, CDD_FOTA_E_UNINIT);
    }
    else
#endif
    {
        if ((CDD_FOTA_RunTimeStatus == CDD_FOTA_READY) || (CDD_FOTA_RunTimeStatus == CDD_FOTA_VERIFY))
        {
            ret = CDD_FOTA_SetFOTAActivate_Callout();
            if (ret == E_OK)
            {
                CDD_FOTA_RunTimeStatus = CDD_FOTA_ACTIVATE;
                if (CDD_FOTA_ProgramInfo.ProgramConter < 0xFFFFFFFFu)
                {
                    CDD_FOTA_ProgramInfo.ProgramConter++;
                }
                CDD_FOTA_NeedStoreFlag = TRUE;
            }
        }
        else
        {
            CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
        }
    }
    return ret;
}

/*
 * Brief               Set CDD_FOTA roll back old app flag
 * ServiceId           0x06
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_SetFOTARollback(void)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_SETFOTAROLLBACK, CDD_FOTA_E_UNINIT);
    }
    else
#endif
    {
        ret = CDD_FOTA_SetFOTARollback_Callout();
    }
    return ret;
}

/*
 * Brief               Set CDD_FOTA to Verification
 * ServiceId           0x07
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     VerificationStatus:Verification Status
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_Verification(boolean* VerificationStatus)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_VERIFICATION, CDD_FOTA_E_UNINIT);
    }
    else if (NULL_PTR == VerificationStatus)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_VERIFICATION, CDD_FOTA_E_PARAM_POINTER);
    }
    else
#endif
        if (CDD_FOTA_RunTimeStatus != CDD_FOTA_READY)
    {
        CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
    }
    else
    {
        ret = CDD_FOTA_CheckProgDependenciesCallout(&CDD_FOTA_ProgramInfo);
        if (E_OK == ret)
        {
            /*Verification is opt,if need please fill in callout*/
#if (STD_OFF == CDD_FOTA_VERIFIC_CALLOUT)
            CDD_FOTA_RunTimeStatus = CDD_FOTA_VERIFY;
            *VerificationStatus = TRUE;
            ret = E_OK;
#else
            if (E_OK == CDD_FOTA_VERIFICCALLOUT_FUN())
            {
                CDD_FOTA_RunTimeStatus = CDD_FOTA_VERIFY;
                *VerificationStatus = TRUE;
                ret = E_OK;
            }
#endif
        }
    }
    return ret;
}

/*
 * Brief               CDD_FOTA Stop Protocol
 * ServiceId           0x0c
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      ProtocolID
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_StopProtocol(Dcm_ProtocolType ProtocolID)
{
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_STOPPROCOCOL, CDD_FOTA_E_UNINIT);
    }
    else
#endif
    {
        if (CDD_FOTA_PROTOCOL_ID == ProtocolID)
        {
            CDD_FOTA_StopProtocolFlag = TRUE;
            CDD_FOTA_RunTimeStatus = CDD_FOTA_IDLE;
        }
    }
    return E_OK;
}

/*
 * Brief               CDD_FOTA cancel install
 * ServiceId           0x0D
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
Std_ReturnType CDD_FOTA_CancelInstall(void)
{
    Std_ReturnType ret = E_NOT_OK;
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
    if (CDD_FOTA_Mode != CDD_FOTA_MODE_INIT)
    {
        CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_CANCELINSTALL, CDD_FOTA_E_UNINIT);
    }
    else
#endif
        if ((CDD_FOTA_RunTimeStatus != CDD_FOTA_IDLE) && (CDD_FOTA_RunTimeStatus != CDD_FOTA_ERROR)
            && (CDD_FOTA_RunTimeStatus != CDD_FOTA_INIT))
    {
        /*idle*/
    }
    else
    {
        CDD_FOTA_ProgramRunTimeInfo.CancelInstall = CDD_FOTA_CancelInstall_Callout();
        CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum = 0;
        ret = E_OK;
    }
    return ret;
}

#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
/*
 * Brief               CDD_FOTA CRC Compare
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 * PreCondition        CDD_FOTA_Init
 */
Std_ReturnType CDD_FOTA_CRCCompare(const uint8* CRCIn, uint32 CRCSize, Dcm_NegativeResponseCodeType* ErrorCode)
{
    Std_ReturnType ret = E_NOT_OK;
    if (CDD_FOTA_ProgramRunTimeInfo.TotalMemorySize != CDD_FOTA_ProgramRunTimeInfo.TranSize)
    {
        *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        CDD_FOTA_RunTimeStatus = CDD_FOTA_ERROR;
    }
    else
    {
#if ((CDD_FOTA_CRC == CDD_FOTA_CRC8) || (CDD_FOTA_CRC == CDD_FOTA_CRC8H2F))
        if (CRCSize != 1u)
        {
            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else if (*CRCIn == CDD_FOTA_ProgramRunTimeInfo.CRC)
        {
            ret = E_OK;
        }
        else
        {
            *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
        }
#elif ((CDD_FOTA_CRC == CDD_FOTA_CRC16) || (CDD_FOTA_CRC == CDD_FOTA_CRC16ARC))
        if (CRCSize != 2u)
        {
            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
            uint16 Crc = CRCIn[1];
            Crc |= (uint16)((uint16)CRCIn[0] << 8u);
            if (Crc == CDD_FOTA_ProgramRunTimeInfo.CRC)
            {
                ret = E_OK;
            }
            else
            {
                *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
            }
        }
#elif ((CDD_FOTA_CRC == CDD_FOTA_CRC32) || (CDD_FOTA_CRC == CDD_FOTA_CRC32P4))
        if (CRCSize != 4u)
        {
            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
            uint32 Crc = CRCIn[3];
            Crc |= (uint32)((uint32)CRCIn[2] << 8u);
            Crc |= (uint32)((uint32)CRCIn[1] << 16u);
            Crc |= (uint32)((uint32)CRCIn[0] << 24u);
            if (Crc == CDD_FOTA_ProgramRunTimeInfo.CRC)
            {
                ret = E_OK;
            }
            else
            {
                *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
            }
        }
#elif (CDD_FOTA_CRC == CDD_FOTA_CRC64)
        if (CRCSize != 8u)
        {
            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
            uint64 Crc = CRCIn[7];
            Crc |= (uint64)((uint64)CRCIn[6] << 8u);
            Crc |= (uint64)((uint64)CRCIn[5] << 16u);
            Crc |= (uint64)((uint64)CRCIn[4] << 24u);
            Crc |= (uint64)((uint64)CRCIn[3] << 32u);
            Crc |= (uint64)((uint64)CRCIn[2] << 40u);
            Crc |= (uint64)((uint64)CRCIn[1] << 48u);
            Crc |= (uint64)((uint64)CRCIn[0] << 56u);
            if (Crc == CDD_FOTA_ProgramRunTimeInfo.CRC)
            {
                ret = E_OK;
            }
            else
            {
                *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
            }
        }
#else
        *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
#endif
        if (E_OK == ret)
        {
            /* CRC check ok, call callout function to set some information*/
            ret = CDD_FOTA_CRCCheckOKCallout(&CDD_FOTA_RunTimeStatus, &CDD_FOTA_ProgramInfo);
        }
    }
    return ret;
}
#endif

/*
 * Brief               CDD_FOTA MainFunction
 * ServiceId           0x08
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           SchM
 */
void CDD_FOTA_MainFunction(void)
{
    if (CDD_FOTA_Mode == CDD_FOTA_MODE_INIT)
    {
        if (CDD_FOTA_StopProtocolFlag == TRUE)
        {
            CDD_FOTA_Cancel_Callout();
            CDD_FOTA_StopProtocolFlag = FALSE;
        }
        if (CDD_FOTA_RunTimeStatus == CDD_FOTA_PROCESSING)
        {
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
            if ((CDD_FOTA_UNCOMPRESS_IDLE != CDD_FOTA_UncompressFlag)
                && (CDD_FOTA_UNCOMPRESS_NEEDTRANS != CDD_FOTA_UncompressFlag))
            {
                CDD_FOTA_Uncompress();
            }
            else
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
            {
                CDD_FOTA_Program();
            }
        }
#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
        CDD_FOTA_CRCCalculate();
#endif
        CDD_FOTA_StoreProgramInfo();
        CDD_FOTA_EraseCancelInstall();
    }
}

/*
 * Brief               CDD_FOTA_MemCopy
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
void CDD_FOTA_MemCopy(uint8* Dest, const uint8* Src, uint32 Size)
{
    for (uint32 Cnt = 0; Cnt < Size; Cnt++)
    {
        Dest[Cnt] = Src[Cnt];
    }
}

/*
 * Brief               CDD_FOTA_MemSet
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      Val/Size
 * Param-Name[out]     N/A
 * Param-Name[in/out]  Dest
 * Return              N/A
 */
void CDD_FOTA_MemSet(uint8* Dest, uint8 Val, uint32 Size)
{
    for (uint32 Cnt = 0; Cnt < Size; Cnt++)
    {
        Dest[Cnt] = Val;
    }
}

/*
 * Brief               CDD_FOTA_StoreProgramInfo
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL void CDD_FOTA_StoreProgramInfo(void)
{
    NvM_RequestResultType RequestResult;
    if (CDD_FOTA_NeedStoreFlag == TRUE)
    {
        if (E_OK == NvM_GetErrorStatus(CDD_FOTA_NVM_BLOCKID, &RequestResult))
        {
            if (RequestResult != NVM_REQ_PENDING)
            {
                CDD_FOTA_MemCopy(
                    (uint8*)NvM_BlockDescriptor[CDD_FOTA_NVM_BLOCKID - 1u].NvmRamBlockDataAddress,
                    (const uint8*)&CDD_FOTA_ProgramInfo,
                    sizeof(CDD_FOTA_ProgramInfoType));
                (void)NvM_WriteBlock(CDD_FOTA_NVM_BLOCKID, NULL_PTR);
                CDD_FOTA_NeedStoreFlag = FALSE;
            }
        }
    }
}

/*
 * Brief               CDD_FOTA_ProgramProcess
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL void CDD_FOTA_ProgramProcess(void)
{
    boolean ProcessOn = TRUE;
    CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_GetJobResult_Callout();
    switch (CDD_FOTA_ProgramRunTimeInfo.JobResult)
    {
    case CDD_FOTA_JOB_PENDING:
        ProcessOn = FALSE;
        break;
    case CDD_FOTA_JOB_OK:
        /*idle*/
        break;
    default:
        ProcessOn = FALSE;
        CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = 0u;
        CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
        CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_FAILED;
        break;
    }
    if ((ProcessOn == TRUE) && (CDD_FOTA_ProgramRunTimeInfo.Remainsize != 0u))
    {
        uint32 ProcesseAddress =
            CDD_FOTA_ProgramRunTimeInfo.StartProcessAddress + CDD_FOTA_ProgramRunTimeInfo.TotalProcessedSize;
        uint32 ProgramSize = CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize - CDD_FOTA_ProgramRunTimeInfo.Remainsize;
        const uint8* Data = &CDD_FOTA_ProgramRunTimeInfo.ProcessData[ProgramSize];
        if (CDD_FOTA_ProgramRunTimeInfo.Remainsize > CDD_FOTA_PROGRAM_SIZE)
        {
            ProgramSize = CDD_FOTA_PROGRAM_SIZE;
        }
        else
        {
            ProgramSize = CDD_FOTA_ProgramRunTimeInfo.Remainsize;
        }
        if (E_OK == CDD_FOTA_Write_Callout(ProcesseAddress, Data, &ProgramSize))
        {
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_NEED_WRITE;
            CDD_FOTA_RunTimeStatus = CDD_FOTA_PROCESSING;
            CDD_FOTA_ProgramRunTimeInfo.TotalProcessedSize += ProgramSize;
            CDD_FOTA_ProgramRunTimeInfo.Remainsize -= ProgramSize;
        }
        else
        {
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_FAILED;
            CDD_FOTA_ProgramRunTimeInfo.Remainsize = 0;
        }
    }
}

/*
 * Brief               CDD_FOTA_Program
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL void CDD_FOTA_Program(void)
{
    CDD_FOTA_ProgramProcess();
    if ((CDD_FOTA_ProgramRunTimeInfo.Remainsize == 0u)
        && (CDD_FOTA_ProgramRunTimeInfo.WriteDone == CDD_FOTA_NEED_WRITE))
    {
        CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_GetJobResult_Callout();
        switch (CDD_FOTA_ProgramRunTimeInfo.JobResult)
        {
        case CDD_FOTA_JOB_PENDING:
            /*idle*/
            break;
        case CDD_FOTA_JOB_OK:
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
            if (CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize > 0u)
            {
                CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_NEEDCALL;
            }
            else
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
            {
#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
                CDD_FOTA_UpdatingSegment();
                uint32 readSize = CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize;
#else
                uint32 readSize = CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize;
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */
                uint32 ProcesseAddress = CDD_FOTA_ProgramRunTimeInfo.StartProcessAddress
                                         + CDD_FOTA_ProgramRunTimeInfo.TotalProcessedSize - readSize;
#if (CDD_FOTA_CRC_BY_37 == STD_OFF)
                uint32 RemainSize = CDD_FOTA_CheckRemainSize(ProcesseAddress, readSize);
                readSize -= RemainSize;
#endif /* CDD_FOTA_CRC_BY_37 == STD_OFF */
                if (E_OK == CDD_FOTA_Read_Callout(ProcesseAddress, CDD_FOTA_ProgramRunTimeInfo.ProcessedData, readSize))
                {
                    CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_NEED_CRC;
                    CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = readSize;
                }
                else
                {
                    CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
                    CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_FAILED;
                }
#else
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = 0u;
            CDD_FOTA_ProgramInfo.ProcessedAddress =
                CDD_FOTA_ProgramRunTimeInfo.StartProcessAddress + CDD_FOTA_ProgramRunTimeInfo.TranSize;
#endif
            }
            break;
        default:
            CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = 0u;
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_FAILED;
            break;
        }
    }
}

/*
 * Brief               CDD_FOTA_CRCCalculate
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
#if (CDD_FOTA_CRC != CDD_FOTA_NONE_CRC)
CDD_FOTA_LOCAL void CDD_FOTA_CRCCalculate(void)
{
    if (CDD_FOTA_ProgramRunTimeInfo.WriteDone == CDD_FOTA_NEED_CRC)
    {
        boolean IsFirstCall = TRUE;
        CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_GetJobResult_Callout();
        switch (CDD_FOTA_ProgramRunTimeInfo.JobResult)
        {
        case CDD_FOTA_JOB_PENDING:
            /*idle*/
            break;
        case CDD_FOTA_JOB_OK:
            if (CDD_FOTA_ProgramRunTimeInfo.TotalProcessedSize != 0u)
            {
                IsFirstCall = FALSE;
            }
            CDD_FOTA_CRCCalculateCallout(
                CDD_FOTA_ProgramRunTimeInfo.ProcessedData,
                CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize,
                CDD_FOTA_ProgramRunTimeInfo.CRC,
                IsFirstCall);
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = 0u;
            CDD_FOTA_ProgramInfo.ProcessedAddress =
                CDD_FOTA_ProgramRunTimeInfo.StartProcessAddress + CDD_FOTA_ProgramRunTimeInfo.TranSize;
            break;
        default:
            CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = 0u;
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            break;
        }
    }
}
#endif

/*
 * Brief               CDD_FOTA_EraseCancelInstall
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL void CDD_FOTA_EraseCancelInstall(void)
{
    uint32 TargetAddress;
    uint32 Length;
    uint32 WriteMemoryRangeHigh;
    uint8 index;
    Dcm_NegativeResponseCodeType ErrorCode;
    if (CDD_FOTA_ProgramRunTimeInfo.CancelInstall == CDD_FOTA_ERASE_A)
    {
        index = CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum;
        TargetAddress = CDD_FOTA_WriteMemoryRange[index].WriteMemoryRangeLow;
        WriteMemoryRangeHigh = CDD_FOTA_WriteMemoryRange[index].WriteMemoryRangeHigh;
        Length = WriteMemoryRangeHigh - TargetAddress;
        if (CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum == 0u)
        {
            (void)CDD_FOTA_Erase_Callout(TargetAddress, Length, &ErrorCode);
            CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum++;
        }
        else
        {
            CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_GetJobResult_Callout();
            switch (CDD_FOTA_ProgramRunTimeInfo.JobResult)
            {
            case CDD_FOTA_JOB_PENDING:
                /*idle*/
                break;
            case CDD_FOTA_JOB_OK:
                (void)CDD_FOTA_Erase_Callout(TargetAddress, Length, &ErrorCode);
                CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum++;
                if (CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum == (CDD_FOTA_APP_A_BOLCK_NUM + 1u))
                {
                    CDD_FOTA_ProgramRunTimeInfo.CancelInstall = CDD_FOTA_NO_ERASE;
                    CDD_FOTA_ProgramRunTimeInfo.Erased = TRUE;
                }
                break;
            default:
                /*idle*/
                break;
            }
        }
    }
    else if (CDD_FOTA_ProgramRunTimeInfo.CancelInstall == CDD_FOTA_ERASE_B)
    {
        index = CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum + CDD_FOTA_APP_A_BOLCK_NUM;
        TargetAddress = CDD_FOTA_WriteMemoryRange[index].WriteMemoryRangeLow;
        WriteMemoryRangeHigh = CDD_FOTA_WriteMemoryRange[index].WriteMemoryRangeHigh;
        Length = WriteMemoryRangeHigh - TargetAddress;
        if (CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum == 0u)
        {
            (void)CDD_FOTA_Erase_Callout(TargetAddress, Length, &ErrorCode);
            CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum++;
        }
        else
        {
            CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_GetJobResult_Callout();
            switch (CDD_FOTA_ProgramRunTimeInfo.JobResult)
            {
            case CDD_FOTA_JOB_PENDING:
                /*idle*/
                break;
            case CDD_FOTA_JOB_OK:
                (void)CDD_FOTA_Erase_Callout(TargetAddress, Length, &ErrorCode);
                CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum++;
                if (CDD_FOTA_ProgramRunTimeInfo.ErasedBlockNum == (CDD_FOTA_APP_B_BOLCK_NUM + 1u))
                {
                    CDD_FOTA_ProgramRunTimeInfo.CancelInstall = CDD_FOTA_NO_ERASE;
                    CDD_FOTA_ProgramRunTimeInfo.Erased = TRUE;
                }
                break;
            default:
                /*idle*/
                break;
            }
        }
    }
    else
    {
        /*idle*/
    }
}

/*
 * Brief               CDD_FOTA_CheckStoreFlag
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL void CDD_FOTA_CheckStoreFlag(void)
{
    uint32 CurrentBreakPoint = CDD_FOTA_GetCurrentBreakPoint();
    if (CurrentBreakPoint != CDD_FOTA_ProgramRunTimeInfo.LastBreakPoint)
    {
        CDD_FOTA_NeedStoreFlag = TRUE;
        CDD_FOTA_ProgramRunTimeInfo.LastBreakPoint = CurrentBreakPoint;
    }
}

/*
 * Brief               CDD_FOTA_GetCurrentBreakPoint
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL uint32 CDD_FOTA_GetCurrentBreakPoint(void)
{
    uint32 MemoryAddress;
    uint16 i = 0;
#if (CDD_FOTA_BREAKPOINT_NUM > 0u) /* PRQA S 3332 */ /* MISRA Rule 20.9 */
    MemoryAddress = CDD_FOTA_Breakpoint[0];
#if (CDD_FOTA_BREAKPOINT_NUM > 1u)
    for (; i < CDD_FOTA_BREAKPOINT_NUM; i++)
#endif /* CDD_FOTA_BREAKPOINT_NUM > 1u */
    {
        uint32 CurAdd = CDD_FOTA_ProgramInfo.ProcessedAddress;
        if (CurAdd >= CDD_FOTA_Breakpoint[i])
        {
            MemoryAddress = CDD_FOTA_Breakpoint[i];
        }
    }
#else /* CDD_FOTA_BREAKPOINT_NUM > 0u */
    MemoryAddress = CDD_FOTA_WriteMemoryRange[0].WriteMemoryRangeLow;
#if ((CDD_FOTA_APP_A_BOLCK_NUM + CDD_FOTA_APP_B_BOLCK_NUM) > 1u)
    for (; i < (CDD_FOTA_APP_A_BOLCK_NUM + CDD_FOTA_APP_B_BOLCK_NUM); i++)
#endif /* CDD_FOTA_BREAKPOINT_NUM > 1u */
    {
        uint32 CurAdd = CDD_FOTA_ProgramInfo.ProcessedAddress;
        if (CurAdd >= CDD_FOTA_WriteMemoryRange[i].WriteMemoryRangeLow)
        {
            MemoryAddress = CDD_FOTA_WriteMemoryRange[i].WriteMemoryRangeLow;
        }
    }
#endif /* CDD_FOTA_BREAKPOINT_NUM > 0u */
    return MemoryAddress;
}

#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
/*
 * Brief               CDD_FOTA_Uncompress
 * ServiceId           N/A
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              N/A
 */
CDD_FOTA_LOCAL void CDD_FOTA_Uncompress(void)
{
    Std_ReturnType ret;
    if (CDD_FOTA_UNCOMPRESS_NEEDCALL == CDD_FOTA_UncompressFlag)
    {
        uint32 UncompressSize = (CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize > CDD_FOTA_UNCOMPRESS_SIZE)
                                    ? CDD_FOTA_UNCOMPRESS_SIZE
                                    : CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize;
        const uint8* UncompressData = &CDD_FOTA_ProgramRunTimeInfo.UncompressProcessData
                                           [CDD_FOTA_ProgramRunTimeInfo.TranUncompressProcessSize
                                            - CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize];
        CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize -= UncompressSize;
        ret = CDD_FOTA_UncompressCallout(
            UncompressData,
            UncompressSize,
            CDD_FOTA_Buffer,
            &CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize);
        if (E_OK == ret)
        {
            CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_NEEDRET;
        }
        else
        {
            CDD_FOTA_ProgramRunTimeInfo.Remainsize = 0;
            CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize = 0;
            CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize = 0;
            CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize = 0;
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_FAILED;
            CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
        }
    }
    if (CDD_FOTA_UNCOMPRESS_NEEDRET == CDD_FOTA_UncompressFlag)
    {
        ret = CDD_FOTA_GetUncompressResCallout();
        if ((E_OK == ret) && (CDD_FOTA_UNCOMPRESS_BUF_SIZE >= CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize))
        {
            CDD_FOTA_ProgramRunTimeInfo.NeedToProcessSize = CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize;
            CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize += CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize;
            CDD_FOTA_ProgramRunTimeInfo.Remainsize = CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize;
            CDD_FOTA_ProgramRunTimeInfo.ProcessData = CDD_FOTA_Buffer;
            CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize = 0;
            CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_NEEDTRANS;
        }
        else if (
            (E_NOT_OK == ret) || (CDD_FOTA_UNCOMPRESS_BUF_SIZE < CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize))
        {
            CDD_FOTA_ProgramRunTimeInfo.Remainsize = 0;
            CDD_FOTA_ProgramRunTimeInfo.UncompressProcessSize = 0;
            CDD_FOTA_ProgramRunTimeInfo.UncompressRemainsize = 0;
            CDD_FOTA_ProgramRunTimeInfo.TotalUncompressSize = 0;
            CDD_FOTA_ProgramRunTimeInfo.WriteDone = CDD_FOTA_WRITE_OK;
            CDD_FOTA_ProgramRunTimeInfo.JobResult = CDD_FOTA_JOB_FAILED;
            CDD_FOTA_UncompressFlag = CDD_FOTA_UNCOMPRESS_IDLE;
        }
        else
        {
            /*pending*/
        }
    }
}
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */

#define CDD_FOTA_STOP_SEC_CODE
#include "CDD_FOTA_MemMap.h"
