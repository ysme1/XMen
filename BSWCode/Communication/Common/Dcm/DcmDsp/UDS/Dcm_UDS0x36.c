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
 **  FILENAME    :                                                            **
 **                                                                           **
 **  Created on  : 2020/5/6 14:29:43                                          **
 **  Author      : tao.yu                                                     **
 **  Vendor      :                                                            **
 **  DESCRIPTION :                                                            **
 **                                                                           **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                      **
 **                                                                           **
 **************************************************************************** */
/* PRQA S 3108-- */
#include "UDS.h"

/****************************************************************
     UDS: TransferData (36 hex) service
 ***************************************************************/
#if (STD_ON == DCM_UDS_SERVICE0X36_ENABLED)

/*length of 0x36 header sid and bolckid*/
#define DCM_UDS_0X36_HEADER_LENGTH 0x2u
/**********************************************************************/
/*
 * Brief
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/***********************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE)
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    Dcm_Uds0x36SubCheck(uint8 ProtocolCtrlId, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret = E_OK; /* PRQA S 2981 */ /* MISRA Rule 2.2 */
    uint8 MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;

#if (STD_ON == DCM_SESSION_FUNC_ENABLED)
    /*session check,check whether the current session supports the request service*/
    ret = DsdInternal_SesCheck(ProtocolCtrlId, SID_TRANSFER_DATA);
    if (E_NOT_OK == ret)
    {
        /*the current session does not support the request service,send NRC = 0x7F*/
        *ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
    }
#endif
#if (STD_ON == DCM_SECURITY_FUNC_ENABLED)
    /*security check,check whether the current security supports the request service*/
    if (E_OK == ret)
    {
        ret = DsdInternal_SecurityCheck(ProtocolCtrlId, SID_TRANSFER_DATA);
        if (E_NOT_OK == ret)
        {
            /*the current security does not support the request service,send NRC = 0x33*/
            *ErrorCode = DCM_E_SECURITYACCESSDENIED;
        }
    }
#endif
    if (E_OK == ret)
    {
        /*min-length check*/
        if ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x04)
            || (Dcm_DspProgram.Status == DCM_UDS0X38_0x05))
        {
            if (DCM_UDS0X36_REQ_DATA_UPLOAD_MINLENGTH > Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen)
            {
                /*the min length of message is not correct,send NRC 0x13*/
                *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                ret = E_NOT_OK;
            }
        }
        else if (
            (Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x01)
            || (Dcm_DspProgram.Status == DCM_UDS0X38_0x03))
        {
            if (DCM_UDS0X36_REQ_DATA_DOWNLOAD_MINLENGTH > Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen)
            {
                /*the min length of message is not correct,send NRC 0x13*/
                *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                ret = E_NOT_OK;
            }
        }
        else
        {
            if (DCM_UDS0X36_REQ_DATA_UPLOAD_MINLENGTH > Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen)
            {
                /*the min length of message is not correct,send NRC 0x13*/
                *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                ret = E_NOT_OK;
            }
            else
            {
                /*the request message is not sequence,send NRC 0x24*/
                *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                ret = E_NOT_OK;
            }
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
/***************************/
/**********************************************************************/
/*
 * Brief
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <Dcm_UDS0x36_CheckSameBlock>
 */
/***********************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(boolean, DCM_CODE) Dcm_UDS0x36_CheckSameBlock(uint32* Size)
{
    boolean IsSameBlock;
    if ((Dcm_DspProgram.blockId != Dcm_DspProgram.reqBlockId) || (Dcm_DspProgram.FirstFlag == TRUE))
    {
        *Size = Dcm_DspProgram.MemorySize;
        IsSameBlock = FALSE;
    }
    else
    {
        *Size = Dcm_DspProgram.MemorySize + Dcm_DspProgram.DcmLastloadSize;
        IsSameBlock = TRUE;
    }
    return IsSameBlock;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
/***************************/
/**********************************************************************/
/*
 * Brief
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/***********************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Uds0x36ServiceConditionCheck(
    uint8 ProtocolCtrlId,
    /* PRQA S 3432++ */ /* MISRA Rule 20.7 */
    P2VAR(uint8, AUTOMATIC, DCM_VAR) MemoryIdentifier,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode)
/* PRQA S 3432-- */ /* MISRA Rule 20.7 */
{
    Std_ReturnType ret;
    uint8 MsgCtrlId;
    Dcm_MsgLenType ReqDataLen;
    uint32 MemorySizeRemain = 0;
    boolean IsSameBlockId;

    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    Dcm_DspProgram.reqBlockId = Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[1];
    ReqDataLen = Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen - DCM_UDS_0X36_HEADER_LENGTH;
    IsSameBlockId = Dcm_UDS0x36_CheckSameBlock(&MemorySizeRemain);

    ret = Dcm_Uds0x36SubCheck(ProtocolCtrlId, ErrorCode);
    if ((E_OK == ret)
        && ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD)))
    {
        if (Dcm_DspProgram.MemoryIdInfoIndex != 0xFFu)
        {
            *MemoryIdentifier =
                Dcm_DspCfg.pDcmDspMemory->DcmDspMemoryIdInfo[Dcm_DspProgram.MemoryIdInfoIndex].DcmDspMemoryIdValue;
        }
        else
        {
            /*the MemoryIdInfoIndex is not correct,send NRC 0x22*/
            *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            ret = E_NOT_OK;
        }
    }
    if (E_OK == ret)
    {
        if ((Dcm_DspProgram.Status == DCM_UDS0X36_INIT) || (Dcm_DspProgram.Status > DCM_UDS0X38_0x05))
        {
            *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            ret = E_NOT_OK;
        }
        else if (
            (MemorySizeRemain == 0u)
            && ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD)))
        {
            /* Download/Upload Process is over, send NRC 0x24 */
            *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            ret = E_NOT_OK;
        }
        else if (
            (((Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x01)
              || (Dcm_DspProgram.Status == DCM_UDS0X38_0x03))
             && ((ReqDataLen > (Dcm_DspProgram.BlockLength - DCM_UDS_0X36_HEADER_LENGTH))
                 || ((IsSameBlockId == TRUE) && (ReqDataLen != Dcm_DspProgram.DcmLastloadSize))))
            || ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD) && (MemorySizeRemain < ReqDataLen)))
        {
            /* Downloaed Data Size goes over Required Length, send NRC 0x71 */
            *ErrorCode = DCM_E_TRANSFERDATASUSPENDED;
            ret = E_NOT_OK;
        }
        else if ((IsSameBlockId == FALSE) && (Dcm_DspProgram.reqBlockId != (uint8)(Dcm_DspProgram.blockId + 1u)))
        {
            /* then calculate block index and check block index ,send NRC 0x73 */
            *ErrorCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
            ret = E_NOT_OK;
        }
        else
        {
            /*idle*/
        }
    }
    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

/*******************************/
/**********************************************************************/
/*
 * Brief
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/***********************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
static FUNC(Std_ReturnType, DCM_CODE) Dcm_UDS0x36_TxCheck(
    uint8 ProtocolCtrlId,
    uint32 MemorySize,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    uint8 MsgCtrlId;
    Std_ReturnType ret = E_OK;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;

    /*if the required protocol is configured,get the index of runtime datum*/
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
    TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
    Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;

    /* check tx data length */
    if ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD)
        && ((MemorySize + DCM_UDS_0X36_HEADER_LENGTH) > Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex].Dcm_DslBufferSize))
    {
        /*Pdu length is bigger than buffer size */
        *ErrorCode = DCM_E_RESPONSETOOLONG;
        ret = E_NOT_OK;
    }
    else
    {
        if (DCM_UDS_0X36_HEADER_LENGTH > Dcm_DslCfg.pDcmChannelCfg[TxChannelCfgIndex].Dcm_DslBufferSize)
        {
            /*Pdu length is bigger than buffer size */
            *ErrorCode = DCM_E_RESPONSETOOLONG;
            ret = E_NOT_OK;
        }
    }
    if (E_OK == ret)
    {
        if (((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD))
            && ((Dcm_DspProgram.blockId != Dcm_DspProgram.reqBlockId) || (Dcm_DspProgram.FirstFlag == TRUE)))
        {
            /* calculate address */
            SchM_Enter_Dcm(Dcm_DspProgram);
            Dcm_DspProgram.address += MemorySize;
            Dcm_DspProgram.DcmLastloadSize = MemorySize;
            SchM_Exit_Dcm(Dcm_DspProgram);
        }
        /*the processing is successful,assemble positive response*/
        SchM_Enter_Dcm(Dcm_Channel);
        Dcm_Channel[Offset] = 0x76; /*response SID*/
        Dcm_Channel[Offset + 1u] = Dcm_DspProgram.reqBlockId;
        /*blockSequenceCounter*/
        SchM_Exit_Dcm(Dcm_Channel);

        if ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x04)
            || (Dcm_DspProgram.Status == DCM_UDS0X38_0x05))
        {
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = MemorySize + DCM_UDS_0X36_HEADER_LENGTH;
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = MemorySize + DCM_UDS_0X36_HEADER_LENGTH;
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            if (((Dcm_DspProgram.blockId != Dcm_DspProgram.reqBlockId) || (Dcm_DspProgram.FirstFlag == TRUE))
                && (Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD))
            {
                SchM_Enter_Dcm(Dcm_DspProgram);
                Dcm_DspProgram.MemorySize -= MemorySize;
                SchM_Exit_Dcm(Dcm_DspProgram);
            }
        }
        else if (
            (Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x01)
            || (Dcm_DspProgram.Status == DCM_UDS0X38_0x03))
        {
            SchM_Enter_Dcm(Dcm_MsgCtrl);
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResMaxDataLen = DCM_UDS_0X36_HEADER_LENGTH;
            Dcm_MsgCtrl[MsgCtrlId].MsgContext.ResDataLen = DCM_UDS_0X36_HEADER_LENGTH;
            SchM_Exit_Dcm(Dcm_MsgCtrl);
            if (((Dcm_DspProgram.blockId != Dcm_DspProgram.reqBlockId) || (Dcm_DspProgram.FirstFlag == TRUE))
                && (Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD))
            {
                SchM_Enter_Dcm(Dcm_DspProgram);
                Dcm_DspProgram.MemorySize -= MemorySize;
                SchM_Exit_Dcm(Dcm_DspProgram);
            }
        }
        else
        {
            /*idle*/
        }
        if (TRUE == Dcm_DspProgram.FirstFlag)
        {
            Dcm_DspProgram.FirstFlag = FALSE;
        }
        Dcm_DspProgram.blockId = Dcm_DspProgram.reqBlockId;
        SchM_Enter_Dcm(Dcm_MsgCtrl);
        Dcm_MsgCtrl[MsgCtrlId].MsgContext.pResData = &Dcm_Channel[Offset];
        SchM_Exit_Dcm(Dcm_MsgCtrl);
        DsdInternal_ProcessingDone(ProtocolCtrlId);
    }
    return ret;
}

/**********************************************************************/
/*
 * Brief
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <APIName>
 */
/***********************************************************************/
/*******************************/
FUNC(Std_ReturnType, DCM_CODE)
Dcm_UDS0x36(
    Dcm_OpStatusType OpStatus,
    uint8 ProtocolCtrlId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode) /* PRQA S 3432 */ /* MISRA Rule 20.7 */
{
    uint8 MsgCtrlId;
    Std_ReturnType ret;
    uint8 TxChannelCtrlIndex;
    uint8 TxChannelCfgIndex;
    uint32 Offset;
    uint8 MemoryIdentifier = 0;
    uint32 MemorySize = 0;
    uint32 Address;
    boolean IsSameBlockId;
    uint32 MemorySizeRemain = 0;

    /*if the required protocol is configured,get the index of runtime datum*/
    MsgCtrlId = Dcm_ProtocolCtrl[ProtocolCtrlId].MsgCtrlIndex;
    ret = Dcm_Uds0x36ServiceConditionCheck(ProtocolCtrlId, &MemoryIdentifier, ErrorCode);
    TxChannelCtrlIndex = Dcm_MsgCtrl[MsgCtrlId].Dcm_TxCtrlChannelIndex;
    TxChannelCfgIndex = Dcm_ChannelCtrl[TxChannelCtrlIndex].Dcm_ChannelCfgIndex;
    Offset = (Dcm_DslCfg.pDcmChannelCfg)[TxChannelCfgIndex].offset;
    if (E_OK == ret)
    {
        IsSameBlockId = Dcm_UDS0x36_CheckSameBlock(&MemorySizeRemain);
        /*process is running and the request format is correct,to call the callout Following NRCs
         * shall be the responsibility of the callout function 0x23,0x31,0x71,0x72,0x92,0x93*/
        if ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x04)
            || (Dcm_DspProgram.Status == DCM_UDS0X38_0x05))
        {
            MemorySize = (Dcm_DspProgram.Status == DCM_UDS0X36_TO_UPLOAD)
                             ? ((MemorySizeRemain > (Dcm_DspProgram.BlockLength - DCM_UDS_0X36_HEADER_LENGTH))
                                    ? (Dcm_DspProgram.BlockLength - DCM_UDS_0X36_HEADER_LENGTH)
                                    : MemorySizeRemain)
                             : Dcm_DspProgram.BlockLength;
            Address = (IsSameBlockId == TRUE) ? (Dcm_DspProgram.address - Dcm_DspProgram.DcmLastloadSize)
                                              : Dcm_DspProgram.address;
            ret = Dcm_ReadMemory(
                OpStatus,
                MemoryIdentifier,
                Address,
                MemorySize,
                (&Dcm_Channel[Offset + DCM_UDS_0X36_HEADER_LENGTH]),
                ErrorCode);
            if (DCM_READ_FAILED == ret)
            {
                ret = E_NOT_OK;
            }
#if (STD_ON == DCM_DSLDIAGRESP_FORCERESPENDEN)
            else if (DCM_READ_FORCE_RCRRP == ret)
            {
                /*the processing is pending,send NRC 0x78*/
                DsdInternal_SetNrc(ProtocolCtrlId, DCM_E_RESPONSE_PENDING);
                DsdInternal_ProcessingDone(ProtocolCtrlId);
                SchM_Enter_Dcm(Dcm_MsgCtrl);
                Dcm_MsgCtrl[MsgCtrlId].Dcm_Ret = DCM_E_FORCE_RCRRP;
                SchM_Exit_Dcm(Dcm_MsgCtrl);
            }
#endif
            else if (DCM_READ_PENDING == ret)
            {
                ret = DCM_E_PENDING;
                SchM_Enter_Dcm(Dcm_MsgCtrl);
                Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
                SchM_Exit_Dcm(Dcm_MsgCtrl);
            }
            else
            {
                /*idle*/
            }
        }
        else if (
            ((Dcm_DspProgram.Status == DCM_UDS0X36_TO_DOWNLOAD) && (IsSameBlockId == FALSE))
            || (Dcm_DspProgram.Status == DCM_UDS0X38_0x01) || (Dcm_DspProgram.Status == DCM_UDS0X38_0x03))
        {
            MemorySize = Dcm_MsgCtrl[MsgCtrlId].MsgContext.ReqDataLen - DCM_UDS_0X36_HEADER_LENGTH;
            ret = Dcm_WriteMemory(
                OpStatus,
                MemoryIdentifier,
                Dcm_DspProgram.address,
                MemorySize,
                &Dcm_MsgCtrl[MsgCtrlId].MsgContext.pReqData[DCM_UDS_0X36_HEADER_LENGTH],
                ErrorCode);
            if (DCM_WRITE_FAILED == ret)
            {
                ret = E_NOT_OK;
            }
#if (STD_ON == DCM_DSLDIAGRESP_FORCERESPENDEN)
            else if (DCM_WRITE_FORCE_RCRRP == ret)
            {
                /*the processing is pending,send NRC 0x78*/
                DsdInternal_SetNrc(ProtocolCtrlId, DCM_E_RESPONSE_PENDING);
                DsdInternal_ProcessingDone(ProtocolCtrlId);
                SchM_Enter_Dcm(Dcm_MsgCtrl);
                Dcm_MsgCtrl[MsgCtrlId].Dcm_Ret = DCM_E_FORCE_RCRRP;
                SchM_Exit_Dcm(Dcm_MsgCtrl);
            }
#endif /* STD_ON == DCM_DSLDIAGRESP_FORCERESPENDEN */
            else if (DCM_WRITE_PENDING == ret)
            {
                ret = DCM_E_PENDING;
                SchM_Enter_Dcm(Dcm_MsgCtrl);
                Dcm_MsgCtrl[MsgCtrlId].Dcm_OpStatus = DCM_PENDING;
                SchM_Exit_Dcm(Dcm_MsgCtrl);
            }
            else
            {
                /*idle*/
            }
        }
        else
        {
            /*idle*/
        }
    }

    if (E_OK == ret)
    {
        ret = Dcm_UDS0x36_TxCheck(ProtocolCtrlId, MemorySize, ErrorCode);
    }

    return ret;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
