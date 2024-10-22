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
**  FILENAME    : Arch_PendSV.s                                               **
**                                                                            **
**  Created on  :                                                             **
**  Author      : i-soft-os                                                   **
**  Vendor      :                                                             **
**  DESCRIPTION : PendSV_Handler for task Switch                              **
**                                                                            **
**  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
**  Version :   AUTOSAR classic Platform R19--Function Safety                 **
**                                                                            **
*******************************************************************************/
/*****************************************************************************/
/*
 * Brief                <Switch tasks>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <System services>
 * REQ ID               <None>
 */
/*****************************************************************************/
	.syntax unified
    .arch armv7-m

.global PendSV_Handler
.thumb
.thumb_func
PendSV_Handler:
	cpsid i                            
    ldr r0, =Os_SCB     
    ldr r0, [r0]
    cbz r0, lable   

    ldr r1, =Os_ArchTempSp

    mrs r0, psp
    isb
    
    /* Is the task using the FPU context?  If so, push high vfp registers. */
    tst r14,#0x10
    it eq
    vstmdbeq r0!, {s16-s31}
    
    /* Save the CONTROL and other core registers. */
    mrs r3,control
    stmdb r0!, {r3-r11, r14}
    
    str r0, [r1]
    
lable:                               
    dsb                               
    isb                                

    bl Os_TaskSchedule

    cpsid i                
    ldr r0, =Os_ArchTempSp
    ldr r0, [r0]   
    
    ldmia r0!, {r3-r11, r14}
    msr control,r3    /*CONTROL register*/
    
    /* Is the task using the FPU context?  If so, pop the high vfp registers
    too.*/
    tst r14, #0x10
    it eq
    vldmiaeq r0!, {s16-s31}
           
    msr psp, r0                      
    dsb                 
    isb                 
    cpsie i 
    bx lr

/*****************************************************************************/
/*
 * Brief                <terminate isr>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <System services>
 * REQ ID               <None>
 */
/*****************************************************************************/
.global TerminateISR
TerminateISR:
	push {r0}
    ldr r0, =Os_IsrTempIPSR
    ldr r0, [r0]
    orr  r0, r0,#0x01000000
    push {r0}  /*xpsr*/   
	ldr r0, =TERMINATEISR_ISR_1
	push {r0}
	push {R14}
	push {R12}
	push {R3}
	push {R2}
	push {R1}
	push {R0}
	ldr lr,=0xfffffff1
	bx lr
	pop {r0}
    bx lr

/*****************************************************************************/
/*
 * Brief                <terminate isr cat1>
 * ServiceId            <None>
 * Sync/Async           <Synchronous>
 * Reentrancy           <Non Reentrant>
 * Param-Name[in]       <None>
 * Param-Name[out]      <None>
 * Param-Name[in/out]   <None>
 * Return               <None>
 * PreCondition         <None>
 * CallByAPI            <System services>
 * REQ ID               <None>
 */
/*****************************************************************************/
TERMINATEISR_ISR_1:
    pop {r0}
    bx lr



/*=======[E N D   O F   F I L E]==============================================*/
