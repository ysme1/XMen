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
 **  FILENAME    : Com_GwInternal.c                                            **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : zhengfei.li                                                 **
 **  Vendor      :                                                             **
 **  DESCRIPTION : internal implementation for COM gateway signal              **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform 4.2.2                       **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Com_Internal.h"

#if ((0u < COM_GWMAPPING_NUMBER) && (0u < COM_RXIPDU_NUMBER) && (0u < COM_TXIPDU_NUMBER))
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                          **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
#if (0u < COM_TMCTXSIGNAL_NUMBER)
/******************************************************************************/
/*
 * Brief               Called by Com_GwNotArraySignal.
 *                     calculate dest signal/group signal/description signal TMC
 * ServiceId
 * Sync/Async          Synchronous
 * Reentrancy          Non Reentrant
 * Param-Name[in]      SignalType,ComFilter,NewSignalValue,OldSignalValue
 * Param-Name[out]     None
 * Param-Name[in/out]  None
 * Return              boolean
 */
/******************************************************************************/
FUNC(boolean, COM_CODE)
Com_DestSignalTMCCalculate(
    Com_SignalType SignalType,
    Com_FilterAlgorithmType FilterType,
    Com_SignalIdType ComFilterIndex,
#if (COM_TXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
    uint64 OldSignalValue,
#endif
    uint64 NewSignalValue)
{
    boolean ret = FALSE;
#if (COM_TXMASKNEWEQUALSX_NUMBER > 0u) || (COM_TXMASKNEWDIFFERX_NUMBER > 0u) || (COM_TXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
    Com_FilterMaskType ComFilterMask;
    Com_FilterXType ComFilterX;
#endif
#if (COM_TXNEWISWITHIN_NUMBER > 0u) || (COM_TXNEWISOUTSIDE_NUMBER > 0u)
    Com_FilterMaxType ComFilterMax;
    Com_FilterMinType ComFilterMin;
#endif
#if (COM_ONEEVERYNFILTERSIGNAL_NUMBER > 0u)
    Com_SignalIdType ComFilterOffset;
    Com_SignalIdType ComFilterPeriod;
#endif

    switch (FilterType)
    {
    case COM_ALWAYS:
        ret = TRUE;
        break;
#if (COM_TXMASKNEWEQUALSX_NUMBER > 0u)
    case COM_MASKED_NEW_EQUALS_X:
        ComFilterMask = Com_TxMaskedNewEqualsX[ComFilterIndex].ComFilterMask;
        ComFilterX = Com_TxMaskedNewEqualsX[ComFilterIndex].ComFilterX;
        if ((NewSignalValue & ComFilterMask) == ComFilterX)
        {
            ret = TRUE;
        }
        break;
#endif
#if (COM_TXMASKNEWDIFFERX_NUMBER > 0u)
    case COM_MASKED_NEW_DIFFERS_X:
        ComFilterMask = Com_TxMaskedNewDiffersX[ComFilterIndex].ComFilterMask;
        ComFilterX = Com_TxMaskedNewDiffersX[ComFilterIndex].ComFilterX;
        if ((NewSignalValue & ComFilterMask) != ComFilterX)
        {
            ret = TRUE;
        }
        break;
#endif
        /*COM_BOOLEAN not support WITHIN and WITHOUT*/
#if (COM_TXNEWISWITHIN_NUMBER > 0u)
    case COM_NEW_IS_WITHIN:
        ComFilterMax = Com_TxNewIsWithin[ComFilterIndex].ComFilterMax;
        ComFilterMin = Com_TxNewIsWithin[ComFilterIndex].ComFilterMin;
        ret = Com_NewIsWInWOtFilterCalculate(SignalType, NewSignalValue, ComFilterMax, ComFilterMin, TRUE);
        break;
#endif
        /*COM_BOOLEAN not support WITHIN and WITHOUT*/
#if (COM_TXNEWISOUTSIDE_NUMBER > 0u)
    case COM_NEW_IS_OUTSIDE:
        ComFilterMax = Com_TxNewIsOutside[ComFilterIndex].ComFilterMax;
        ComFilterMin = Com_TxNewIsOutside[ComFilterIndex].ComFilterMin;
        ret = Com_NewIsWInWOtFilterCalculate(SignalType, NewSignalValue, ComFilterMax, ComFilterMin, FALSE);
        break;
#endif
#if (COM_ONEEVERYNFILTERSIGNAL_NUMBER > 0u)
    case COM_ONE_EVERY_N:
        ComFilterOffset = Com_FilterOneEveryN[ComFilterIndex].ComFilterOffset;
        ComFilterPeriod = Com_FilterOneEveryN[ComFilterIndex].ComFilterPeriod;
        if (ComFilterPeriod == Com_OneEveryNcnt[ComFilterIndex])
        {
            Com_OneEveryNcnt[ComFilterIndex] = 0u;
        }
        if (ComFilterOffset == Com_OneEveryNcnt[ComFilterIndex])
        {
            ret = TRUE;
        }
        Com_OneEveryNcnt[ComFilterIndex]++;
        break;
#endif
#if (COM_TXMASKNEWDIFFERMASKOLD_NUMBER > 0u)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD:
        ComFilterMask = Com_TxMaskedNewDiffersMaskedOld[ComFilterIndex];
        if ((NewSignalValue & ComFilterMask) != (OldSignalValue & ComFilterMask))
        {
            ret = TRUE;
        }
        break;
#endif
    default:
        /*do nothing*/
        break;
    }
    return ret;
}
#endif
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* 0u < COM_GWMAPPING_NUMBER && 0u < COM_RXIPDU_NUMBER && 0u < COM_TXIPDU_NUMBER */
/*******************************************************************************
**                      End of file                                           **
*******************************************************************************/
