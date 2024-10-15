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
 **  FILENAME    : RV_PortASM.S                                                **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      : i-soft-os                                                   **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/

.extern Os_ArchTempSp
.extern Os_SwitchTask
.extern OS_GetTaskStackPointer
.extern OS_SaveTaskStackPointer
.extern Os_SysTick_Handler0
.extern Os_PLIC_Handler
.extern Os_CPU_Handler

.align 8
.global rv_trap_handler
.weak rv_trap_handler
rv_trap_handler:
    addi sp, sp, -(29 * 4)
    sw x1,  1  * 4(sp)
    sw x5,  2  * 4(sp)
    sw x6,  3  * 4(sp)
    sw x7,  4  * 4(sp)
    sw x8,  5  * 4(sp)
    sw x9,  6  * 4(sp)
    sw x10, 7  * 4(sp)
    sw x11, 8  * 4(sp)
    sw x12, 9  * 4(sp)
    sw x13, 10 * 4(sp)
    sw x14, 11 * 4(sp)
    sw x15, 12 * 4(sp)
    sw x16, 13 * 4(sp)
    sw x17, 14 * 4(sp)
    sw x18, 15 * 4(sp)
    sw x19, 16 * 4(sp)
    sw x20, 17 * 4(sp)
    sw x21, 18 * 4(sp)
    sw x22, 19 * 4(sp)
    sw x23, 20 * 4(sp)
    sw x24, 21 * 4(sp)
    sw x25, 22 * 4(sp)
    sw x26, 23 * 4(sp)
    sw x27, 24 * 4(sp)
    sw x28, 25 * 4(sp)
    sw x29, 26 * 4(sp)
    sw x30, 27 * 4(sp)
    sw x31, 28 * 4(sp)
    
    /* push mstatus*/
    /*
    csrr t0, mstatus
    sw t0,  29 * 4(sp)
    */

    /* push mepc */
    # csrr t0, mepc
    sw t0, 0(sp)
    /* save sp */
    mv t0, sp
    la t1, Os_ArchTempSp
    sw t0, 0(t1)

    /*meip*/
    # csrr a0, mip
    li  a1, 0x00000800u
    and a2, a1, a0
    bnez a2, plic_irq

    /*mtip*/  
    # csrr a0, mip
    li  a1, 0x00000080u
    and a2, a1, a0
    bnez a2, systick

    /*other*/
    # csrr a0, mip
    li  a1, 0xfffff777u
    and a2, a1, a0
    bnez a2, cpu_irq

    /*msip*/
    # csrr a0, mip
    li  a1, 0x00000008u
    and a2, a1, a0
    bnez a2, dispatch
    j resume

plic_irq:
    jal Os_PLIC_Handler
    j resume

systick:
    # csrc mip, a1
    jal Os_SysTick_Handler0
    j resume

cpu_irq:
    jal Os_CPU_Handler
    j resume

dispatch:
    # csrc mip, a1

    jal OS_SaveTaskStackPointer
    
    /* Store sp to system stack */
    jal OS_GetSystemStackPointer
    lw t0, Os_ArchTempSp
    mv sp, t0

    jal Os_SwitchTask
    
    jal OS_GetTaskStackPointer

resume:
    /* resume sp*/
    
    lw t0, Os_ArchTempSp
    mv sp, t0   
              
    /* pop mepc */
    lw t0,  0  * 4(sp)
    # csrw mepc, t0
    /* pop mstatus*/
    /*
    lw t0,  29 * 4(sp)
    csrw mstatus, t0
    */

    lw x1,  1  * 4(sp)
    lw x5,  2  * 4(sp)
    lw x6,  3  * 4(sp)
    lw x7,  4  * 4(sp)
    lw x8,  5  * 4(sp)
    lw x9,  6  * 4(sp)
    lw x10, 7  * 4(sp)
    lw x11, 8  * 4(sp)
    lw x12, 9  * 4(sp)
    lw x13, 10 * 4(sp)
    lw x14, 11 * 4(sp)
    lw x15, 12 * 4(sp)
    lw x16, 13 * 4(sp)
    lw x17, 14 * 4(sp)
    lw x18, 15 * 4(sp)
    lw x19, 16 * 4(sp)
    lw x20, 17 * 4(sp)
    lw x21, 18 * 4(sp)
    lw x22, 19 * 4(sp)
    lw x23, 20 * 4(sp)
    lw x24, 21 * 4(sp)
    lw x25, 22 * 4(sp)
    lw x26, 23 * 4(sp)
    lw x27, 24 * 4(sp)
    lw x28, 25 * 4(sp)
    lw x29, 26 * 4(sp)
    lw x30, 27 * 4(sp)
    lw x31, 28 * 4(sp)

    addi sp, sp, (29 * 4)
    mret


/* Default Handler for Exceptions / Interrupts */
default_handler:
    # csrc mip, a1
    1:
        j 1b



.align 8
.global Os_StartUpResumeContext
.weak Os_StartUpResumeContext
Os_StartUpResumeContext:
    lw t0, Os_ArchTempSp
    mv sp, t0

    /* Pop PC from stack and set MEPC */
    lw t0,  0  * 4(sp)
    # csrw mepc, t0    
    /* Pop mstatus from stack and set it */
    /*
    lw t0,  29  * 4(sp)
    csrw mstatus, t0
    */

    /* Restore Registers from Stack */
    lw x1,  1  * 4(sp)    /* RA */
    lw x5,  2  * 4(sp)
    lw x6,  3  * 4(sp)
    lw x7,  4  * 4(sp)
    lw x8,  5  * 4(sp)
    lw x9,  6  * 4(sp)
    lw x10, 7  * 4(sp)
    lw x11, 8  * 4(sp)
    lw x12, 9  * 4(sp)
    lw x13, 10 * 4(sp)
    lw x14, 11 * 4(sp)
    lw x15, 12 * 4(sp)
    lw x16, 13 * 4(sp)
    lw x17, 14 * 4(sp)
    lw x18, 15 * 4(sp)
    lw x19, 16 * 4(sp)
    lw x20, 17 * 4(sp)
    lw x21, 18 * 4(sp)
    lw x22, 19 * 4(sp)
    lw x23, 20 * 4(sp)
    lw x24, 21 * 4(sp)
    lw x25, 22 * 4(sp)
    lw x26, 23 * 4(sp)
    lw x27, 24 * 4(sp)
    lw x28, 25 * 4(sp)
    lw x29, 26 * 4(sp)
    lw x30, 27 * 4(sp)
    lw x31, 28 * 4(sp)

    addi sp, sp, (29 * 4)
    /*enble isr*/
    # csrrsi  zero, mstatus, 0x8

    mret













