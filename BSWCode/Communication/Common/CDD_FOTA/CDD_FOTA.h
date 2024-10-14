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
 **  FILENAME    : CDD_FOTA.h                                                 **
 **                                                                           **
 **  Created on  : 2020/5/11 16:59:43                                         **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION : function declare                                           **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                     **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */

#ifndef CDD_FOTA_H
#define CDD_FOTA_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*
*  <VERSION>    <DATE>       <AUTHOR>    <REVISION LOG>
*  V2.0.0       2021-04-08    tao.yu      Initial version
*  V2.0.1       2022-08-31    tao.yu      change code style
*  V2.0.2       2022-12-29    tong.zhao   change parameter InBuffer from P2VAR to P2CONST in CDD_FOTA_Erase()
*  V2.0.3       2023-04-17    tao.yu      fix progame process、add breakpoint and uncompress
*  V2.0.4       2023-05-04    tao.yu      fix CPT-127
*  V2.0.5       2023-07-12    tao.yu      fix CPT-6125 CDD_FOTA_ProcessExit status change
*  V2.0.6       2023-08-10    xue.han     QAC Change
*  V2.0.7       2023-08-17    tao.yu      Optimize the implementation to add incremental generation of content and
                                          adaptations in the callback interface
*  V2.0.8       2023-09-08    tao.yu      ConvertAddress in write, write source change,Transfer function NRC change
*  V2.0.9       2024-02-02    xue.han     QAC
*  V2.0.10      2024-03-13    tao.yu      fix CPT-8179, Modifying storage conditions
                                          fix CPT-8177, Add decompression slice execution mechanism
                                          fix CPT-8192, Modify the structure of the interaction with the BootLoader
                                          fix CPT-8181, Adjustment of the mechanism for calculating the CRC
                                          fix CPT-8407, Request to download NRC modification to 0x70 without erasure
============================================================================*/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "CDD_FOTA_Cfg.h"
#include "Dcm.h"
#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
#include "Det.h"
#endif

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define CDD_FOTA_VENDOR_ID                62U
#define CDD_FOTA_MODULE_ID                255U
#define CDD_FOTA_INSTANCE_ID              0u
#define CDD_FOTA_AR_RELEASE_MAJOR_VERSION (0x04u)
#define CDD_FOTA_AR_RELEASE_MINOR_VERSION (0x05u)
#define CDD_FOTA_AR_RELEASE_PATCH_VERSION (0x00u)
#define CDD_FOTA_SW_MAJOR_VERSION         (0x02u) /*Major Version*/
#define CDD_FOTA_SW_MINOR_VERSION         (0x00u) /*Minor Version*/
#define CDD_FOTA_SW_PATCH_VERSION         (0x0Au) /*Patch version*/

#ifndef CDD_FOTA_LOCAL
#define CDD_FOTA_LOCAL static
#endif /* ifndef CDD_FOTA_LOCAL */

#ifndef FOTA_UNUSED
#define FOTA_UNUSED(a) (void)(a)
#endif /* ifndef FOTA_UNUSED */

#if (STD_ON == CDD_FOTA_DEV_ERROR_DETECT)
static inline void CDD_FOTA_DET_REPORTERROR(uint8 ApiId, uint8 ErrorId)
{
    (void)Det_ReportError(CDD_FOTA_MODULE_ID, CDD_FOTA_INSTANCE_ID, (ApiId), (ErrorId));
}
#endif /* STD_ON == CANTP_DEV_ERROR_DETECT */

#if (STD_ON == CDD_FOTA_VERSION_INFO_API)
/*
 * Brief               This service returns the version information of
 *                     this module
 * ServiceId           0x09
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      None
 * Param-Name[out]     Versioninfo: Pointer to where to store the version
 * Param-Name[in/out]  None
 * Return              None
 * PreCondition        None
 * CallByAPI           Up layer
 */
#define CDD_FOTA_GetVersionInfo(VersionInfo)                                                       \
    do                                                                                             \
    {                                                                                              \
        if (NULL_PTR == (VersionInfo))                                                             \
        {                                                                                          \
            CDD_FOTA_DET_REPORTERROR(CDD_FOTA_SERVICEID_GETVERSIONINFO, CDD_FOTA_E_PARAM_POINTER); \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            (VersionInfo)->vendorID = CDD_FOTA_VENDOR_ID;                                          \
            (VersionInfo)->moduleID = CDD_FOTA_MODULE_ID;                                          \
            (VersionInfo)->sw_major_version = CDD_FOTA_SW_MAJOR_VERSION;                           \
            (VersionInfo)->sw_minor_version = CDD_FOTA_SW_MINOR_VERSION;                           \
            (VersionInfo)->sw_patch_version = CDD_FOTA_SW_PATCH_VERSION;                           \
        }                                                                                          \
    } while (0)
#endif /* STD_ON == NVM_VERSION_INFO_API */

/******************************************************************************
**                      Private Type Definitions                             *
******************************************************************************/

/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/

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
extern void CDD_FOTA_PreInit(void);

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
extern Std_ReturnType CDD_FOTA_Init(CDD_FOTA_StatusType* FOTAStatus);

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
extern Std_ReturnType CDD_FOTA_GetFOTAStatus(CDD_FOTA_StatusType* FOTAStatus);

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
extern Std_ReturnType CDD_FOTA_GetAppVersion(uint8* AppVersion);

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
extern Std_ReturnType CDD_FOTA_SetAppVersion(const uint8* AppVersion);

/*
 * Brief               get CDD_FOTA last program successed address info
 * ServiceId           0x03
 * Sync/Async          Synchronous
 * Reentrancy          Reentrant
 * Param-Name[in]      N/A
 * Param-Name[out]     MemoryIdentifier:program address format
 *                     MemoryAddress:program successed address
 *                     MemorySize:program successed size
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
extern Std_ReturnType CDD_FOTA_GetFOTAProcessedInfo(uint32* MemoryAddress);

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
extern Std_ReturnType CDD_FOTA_GetFOTAbreakpointInfo(uint32* MemoryAddress);

/*
 * Brief               CDD_FOTA Process download
 * ServiceId           0x0A
 * Sync/Async          Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      MemoryAddress:program address
 *                     MemorySize:program size
 * Param-Name[out]     ErrorCode:NRC
 *                     BlockLength：buffer length
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        CDD_FOTA_Init
 * CallByAPI           DCM mode
 */
extern Std_ReturnType CDD_FOTA_Processdownload(
    uint32 MemoryAddress,
    uint32 MemorySize,
    uint32* BlockLength,
    Dcm_NegativeResponseCodeType* ErrorCode);

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
extern Std_ReturnType CDD_FOTA_StopProtocol(Dcm_ProtocolType ProtocolID);

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
extern Std_ReturnType CDD_FOTA_CancelInstall(void);

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
extern Dcm_ReturnWriteMemoryType CDD_FOTA_ProcessTransferDataWrite(
    Dcm_OpStatusType OpStatus,
    uint32 MemoryAddress,
    uint32 MemorySize,
    uint8* MemoryData,
    Dcm_NegativeResponseCodeType* ErrorCode);

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
extern Std_ReturnType CDD_FOTA_Erase(const uint8* InBuffer, Dcm_NegativeResponseCodeType* ErrorCode);

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
extern Std_ReturnType CDD_FOTA_ProcessExit(
    const uint8* transferRequestParameterRecord,
    uint32 transferRequestParameterRecordSize,
    uint32* transferResponseParameterRecordSize,
    Dcm_NegativeResponseCodeType* ErrorCode);

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
extern Std_ReturnType CDD_FOTA_SetFOTAActivate(void);

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
extern Std_ReturnType CDD_FOTA_SetFOTARollback(void);

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
extern Std_ReturnType CDD_FOTA_Verification(boolean* VerificationStatus);

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
extern void CDD_FOTA_MainFunction(void);

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
extern Std_ReturnType CDD_FOTA_CRCCompare(const uint8* CRCIn, uint32 CRCSize, Dcm_NegativeResponseCodeType* ErrorCode);
#endif /* CDD_FOTA_CRC != CDD_FOTA_NONE_CRC */

#if (CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON)
/*
 * Brief               CDD_FOTA Uncompress call
 *                     This callback interface is used to request data decompression.
 *                     In the case of synchronization, E_OK is returned directly in the result callback interface.
 *                     In the case of asynchronous, processing is based on the actual execution result
 * ServiceId           N/A
 * Sync/Async          synchronous/Asynchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      InData:Input data that needs to be decompressed
 *                     InSize:Input data size
 * Param-Name[out]     OutData:The output data after decompression
 *                     OutSize:output data size
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 * PreCondition        N/A
 */
extern Std_ReturnType CDD_FOTA_UncompressCallout(const uint8* InData, uint32 InSize, uint8* OutData, uint32* OutSize);

/*
 * Brief               CDD_FOTA Get Uncompress result
 *                     This callback interface is used to obtain the decompressed task result.
 *                     If it is triggered, the return value of this callback interface can be
 *                     set according to the result instead of adding a separate callback interface.
 *                     If necessary, add an interface to set the return value of this function
 * ServiceId           N/A
 * Sync/Async          synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      CDD_FOTA_ProgramInfo
 * Param-Name[out]     N/A
 * Param-Name[in/out]  N/A
 * Return              Std_ReturnType: E_OK: successful
 *                                     E_NOT_OK:failed
 *                                     Other:Pending
 * PreCondition        N/A
 */
extern Std_ReturnType CDD_FOTA_GetUncompressResCallout(void);
#endif /* CDD_FOTA_UNCOMPRESS_ENABLE == STD_ON */

#endif /* CDD_FOTA_H */
