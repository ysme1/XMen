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
 **  FILENAME    :  Arch_Irq.h                                                 **
 **                                                                            **
 **  Created on  :                                                             **
 **  Author      :  i-soft-os                                                  **
 **  Vendor      :                                                             **
 **  DESCRIPTION : Deal with operations related to processor interrupts        **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform r19                         **
 **  Version :   AUTOSAR classic Platform R19--Function Safety                 **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */
#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

/*=======[M I S R A C  R U L E  V I O L A T I O N]============================*/
/*  <MESSAGE ID>    <CODE LINE>    <REASON>
 */
/*============================================================================*/

/*=======[I N C L U D E S]====================================================*/
#include "Os.h"
/*============================================================================*/
/* Nested Vectored Interrupt Controller(NVIC) */
#define OS_IRQ_ID_OFFSET                    (16u)
#define OS_NVIC_NUM                         (16u + 147u)
/* Core interrupts */
#define OS_SRC_NonMaskableInt_ADDR              (2u)                               /**< Non Maskable Interrupt */
#define OS_SRC_HardFault_ADDR                   (3u)                               /**< Cortex-M7 SV Hard Fault Interrupt */
#define OS_SRC_MemoryManagement_ADDR            (4u)                               /**< Cortex-M7 Memory Management Interrupt */
#define OS_SRC_BusFault_ADDR                    (5u)                               /**< Cortex-M7 Bus Fault Interrupt */
#define OS_SRC_UsageFault_ADDR                  (6u)                               /**< Cortex-M7 Usage Fault Interrupt */
#define OS_SRC_SVCall_ADDR                      (11u)                              /**< Cortex-M7 SV Call Interrupt */
#define OS_SRC_DebugMonitor_ADDR                (12u)                              /**< Cortex-M7 Debug Monitor Interrupt */
#define OS_SRC_PendSV_ADDR                      (14u)                              /**< Cortex-M7 Pend SV Interrupt */
#define OS_SRC_SysTick_ADDR                     (15u)                              /**< Cortex-M7 System Tick Interrupt */
/* Device specific interrupts id */
#define OS_SRC_DMA0_ADDR                    (OS_IRQ_ID_OFFSET + 0)               /**< DMA channel 0 transfer complete */
#define OS_SRC_DMA1_ADDR                    (OS_IRQ_ID_OFFSET + 1)               /**< DMA channel 1 transfer complete */
#define OS_SRC_DMA2_ADDR                    (OS_IRQ_ID_OFFSET + 2)               /**< DMA channel 2 transfer complete */
#define OS_SRC_DMA3_ADDR                    (OS_IRQ_ID_OFFSET + 3)               /**< DMA channel 3 transfer complete */
#define OS_SRC_DMA4_ADDR                    (OS_IRQ_ID_OFFSET + 4)               /**< DMA channel 4 transfer complete */
#define OS_SRC_DMA5_ADDR                    (OS_IRQ_ID_OFFSET + 5)               /**< DMA channel 5 transfer complete */
#define OS_SRC_DMA6_ADDR                    (OS_IRQ_ID_OFFSET + 6)               /**< DMA channel 6 transfer complete */
#define OS_SRC_DMA7_ADDR                    (OS_IRQ_ID_OFFSET + 7)               /**< DMA channel 7 transfer complete */
#define OS_SRC_DMA8_ADDR                    (OS_IRQ_ID_OFFSET + 8)               /**< DMA channel 8 transfer complete */
#define OS_SRC_DMA9_ADDR                    (OS_IRQ_ID_OFFSET + 9)               /**< DMA channel 9 transfer complete */
#define OS_SRC_DMA10_ADDR                   (OS_IRQ_ID_OFFSET + 10)              /**< DMA channel 10 transfer complete */
#define OS_SRC_DMA11_ADDR                   (OS_IRQ_ID_OFFSET + 11)              /**< DMA channel 11 transfer complete */
#define OS_SRC_DMA12_ADDR                   (OS_IRQ_ID_OFFSET + 12)              /**< DMA channel 12 transfer complete */
#define OS_SRC_DMA13_ADDR                   (OS_IRQ_ID_OFFSET + 13)              /**< DMA channel 13 transfer complete */
#define OS_SRC_DMA14_ADDR                   (OS_IRQ_ID_OFFSET + 14)              /**< DMA channel 14 transfer complete */
#define OS_SRC_DMA15_ADDR                   (OS_IRQ_ID_OFFSET + 15)              /**< DMA channel 15 transfer complete */
#define OS_SRC_DMA_Error_ADDR               (OS_IRQ_ID_OFFSET + 16)              /**< DMA error interrupt channels 0-15 */
#define OS_SRC_MCM_ADDR                     (OS_IRQ_ID_OFFSET + 17)              /**< FPU sources */
#define OS_SRC_FTFC_CMD_ADDR                (OS_IRQ_ID_OFFSET + 18)              /**< FTFC Command complete */
#define OS_SRC_FTFC_Read_Collision_ADDR     (OS_IRQ_ID_OFFSET + 19)              /**< FTFC Read collision */
#define OS_SRC_LVD_LVW_ADDR                 (OS_IRQ_ID_OFFSET + 20)              /**< PMC Low voltage detect interrupt */
#define OS_SRC_FTFC_Fault_ADDR              (OS_IRQ_ID_OFFSET + 21)              /**< FTFC Double bit fault detect */
#define OS_SRC_WDOG_EWM_ADDR                (OS_IRQ_ID_OFFSET + 22)              /**< Interrupt request out before WDOG reset out, EWM output as interrupt */
#define OS_SRC_RCM_ADDR                     (OS_IRQ_ID_OFFSET + 23)              /**< RCM Asynchronous Interrupt */
#define OS_SRC_LPI2C0_Master_ADDR           (OS_IRQ_ID_OFFSET + 24)              /**< LPI2C0 Master Interrupt */
#define OS_SRC_LPI2C0_Slave_ADDR            (OS_IRQ_ID_OFFSET + 25)              /**< LPI2C0 Slave Interrupt */
#define OS_SRC_LPSPI0_ADDR                  (OS_IRQ_ID_OFFSET + 26)              /**< LPSPI0 Interrupt */
#define OS_SRC_LPSPI1_ADDR                  (OS_IRQ_ID_OFFSET + 27)              /**< LPSPI1 Interrupt */
#define OS_SRC_LPSPI2_ADDR                  (OS_IRQ_ID_OFFSET + 28)              /**< LPSPI2 Interrupt */
#define OS_SRC_LPI2C1_Master_ADDR           (OS_IRQ_ID_OFFSET + 29)              /**< LPI2C1 Master Interrupt */
#define OS_SRC_LPI2C1_Slave_ADDR            (OS_IRQ_ID_OFFSET + 30)              /**< LPI2C1 Slave Interrupt */
#define OS_SRC_LPUART0_RxTx_ADDR            (OS_IRQ_ID_OFFSET + 31)              /**< LPUART0 Transmit / Receive Interrupt / Error / Overrun */
#define OS_SRC_LPUART1_RxTx_ADDR            (OS_IRQ_ID_OFFSET + 33)              /**< LPUART1 Transmit / Receive Interrupt / Error / Overrun */
#define OS_SRC_LPUART2_RxTx_ADDR            (OS_IRQ_ID_OFFSET + 35)              /**< LPUART2 Transmit / Receive Interrupt / Error / Overrun */
#define OS_SRC_ADC0_ADDR                    (OS_IRQ_ID_OFFSET + 39)              /**< ADC0 interrupt request */
#define OS_SRC_ADC1_ADDR                    (OS_IRQ_ID_OFFSET + 40)              /**< ADC1 interrupt request */
#define OS_SRC_CMP0_ADDR                    (OS_IRQ_ID_OFFSET + 41)              /**< CMP0 interrupt request */
#define OS_SRC_ERM_single_fault_ADDR        (OS_IRQ_ID_OFFSET + 44)              /**< ERM single bit error correction */
#define OS_SRC_ERM_double_fault_ADDR        (OS_IRQ_ID_OFFSET + 45)              /**< ERM double bit error non-correctable */
#define OS_SRC_RTC_ADDR                     (OS_IRQ_ID_OFFSET + 46)              /**< RTC alarm interrupt */
#define OS_SRC_RTC_Seconds_ADDR             (OS_IRQ_ID_OFFSET + 47)              /**< RTC seconds interrupt */
#define OS_SRC_LPIT0_Ch0_ADDR               (OS_IRQ_ID_OFFSET + 48)              /**< LPIT0 channel 0 overflow interrupt */
#define OS_SRC_LPIT0_Ch1_ADDR               (OS_IRQ_ID_OFFSET + 49)              /**< LPIT0 channel 1 overflow interrupt */
#define OS_SRC_LPIT0_Ch2_ADDR               (OS_IRQ_ID_OFFSET + 50)              /**< LPIT0 channel 2 overflow interrupt */
#define OS_SRC_LPIT0_Ch3_ADDR               (OS_IRQ_ID_OFFSET + 51)              /**< LPIT0 channel 3 overflow interrupt */
#define OS_SRC_PDB0_ADDR                    (OS_IRQ_ID_OFFSET + 52)              /**< PDB0 interrupt */
#define OS_SRC_SAI1_TX_SYNC_ADDR            (OS_IRQ_ID_OFFSET + 55)              /**< Transmit Synchronous interupt (for interrupt controller) */
#define OS_SRC_SAI1_RX_SYNC_ADDR            (OS_IRQ_ID_OFFSET + 56)              /**< Transmit Synchronous interupt (for interrupt controller) */
#define OS_SRC_SCG_ADDR                     (OS_IRQ_ID_OFFSET + 57)              /**< SCG bus interrupt request */
#define OS_SRC_LPTMR0_ADDR                  (OS_IRQ_ID_OFFSET + 58)              /**< LPTIMER interrupt request */
#define OS_SRC_PORTA_ADDR                   (OS_IRQ_ID_OFFSET + 59)              /**< Port A pin detect interrupt */
#define OS_SRC_PORTB_ADDR                   (OS_IRQ_ID_OFFSET + 60)              /**< Port B pin detect interrupt */
#define OS_SRC_PORTC_ADDR                   (OS_IRQ_ID_OFFSET + 61)              /**< Port C pin detect interrupt */
#define OS_SRC_PORTD_ADDR                   (OS_IRQ_ID_OFFSET + 62)              /**< Port D pin detect interrupt */
#define OS_SRC_PORTE_ADDR                   (OS_IRQ_ID_OFFSET + 63)              /**< Port E pin detect interrupt */
#define OS_SRC_SWI_ADDR                     (OS_IRQ_ID_OFFSET + 64)              /**< Software interrupt */
#define OS_SRC_QSPI_Ored_ADDR               (OS_IRQ_ID_OFFSET + 65)              /**< All interrupts ORed output */
#define OS_SRC_PDB1_ADDR                    (OS_IRQ_ID_OFFSET + 68)              /**< PDB1 interrupt */
#define OS_SRC_FLEXIO_ADDR                  (OS_IRQ_ID_OFFSET + 69)              /**< Software interrupt */
#define OS_SRC_SAI0_TX_SYNC_ADDR            (OS_IRQ_ID_OFFSET + 70)              /**< Transmit Synchronous interupt (for interrupt controller) */
#define OS_SRC_SAI0_RX_SYNC_ADDR            (OS_IRQ_ID_OFFSET + 71)              /**< Transmit Synchronous interupt (for interrupt controller) */
#define OS_SRC_ENET_Timer_ADDR              (OS_IRQ_ID_OFFSET + 72)              /**< 1588 Timer Interrupt - synchronous, Period EventTimer Overflow, Time stamp available */
#define OS_SRC_ENET_TX_Buffer_ADDR          (OS_IRQ_ID_OFFSET + 73)              /**< Data transfer done, Transmit Buffer Done for Ring/Queue 0, Transmit Frame Done for Ring/Queue 0 */
#define OS_SRC_ENET_RX_Buffer_ADDR          (OS_IRQ_ID_OFFSET + 74)              /**< Receive Buffer Done for Ring/Queue 0, Receive Frame Done for Ring/Queue 0 */
#define OS_SRC_ENET_PRE_ADDR                (OS_IRQ_ID_OFFSET + 75)              /**< Payload receive error, Collision retry limit reached, Late collision detected, AXI Bus Error detected, Babbling transmit error, Babbling receive error, Transmit FIFO underrun */
#define OS_SRC_ENET_STOP_ADDR               (OS_IRQ_ID_OFFSET + 76)              /**< ENET Graceful stop */
#define OS_SRC_ENET_WAKE_ADDR               (OS_IRQ_ID_OFFSET + 77)              /**< ENET Wake from sleep. */
#define OS_SRC_CAN0_ORed_ADDR               (OS_IRQ_ID_OFFSET + 78)              /**< CAN0 OR'ed Bus in Off State. */
#define OS_SRC_CAN0_Error_ADDR              (OS_IRQ_ID_OFFSET + 79)              /**< CAN0 Interrupt indicating that errors were detected on the CAN bus */
#define OS_SRC_CAN0_Wake_Up_ADDR            (OS_IRQ_ID_OFFSET + 80)              /**< CAN0 Interrupt asserted when Pretended Networking operation is enabled, and a valid message matches the selected filter criteria during Low Power mode */
#define OS_SRC_CAN0_ORed_0_15_MB_ADDR       (OS_IRQ_ID_OFFSET + 81)              /**< CAN0 OR'ed Message buffer (0-15) */
#define OS_SRC_CAN0_ORed_16_31_MB_ADDR      (OS_IRQ_ID_OFFSET + 82)              /**< CAN0 OR'ed Message buffer (16-31) */
#define OS_SRC_CAN1_ORed_ADDR               (OS_IRQ_ID_OFFSET + 85)              /**< CAN1 OR'ed Bus in Off State */
#define OS_SRC_CAN1_Error_ADDR              (OS_IRQ_ID_OFFSET + 86)              /**< CAN1 Interrupt indicating that errors were detected on the CAN bus */
#define OS_SRC_CAN1_ORed_0_15_MB_ADDR       (OS_IRQ_ID_OFFSET + 88)              /**< CAN1 OR'ed Message buffer (0-15) */
#define OS_SRC_CAN1_ORed_16_31_MB_ADDR      (OS_IRQ_ID_OFFSET + 89)              /**< CAN1 OR'ed Message buffer (16-31) */
#define OS_SRC_CAN2_ORed_ADDR               (OS_IRQ_ID_OFFSET + 92)              /**< CAN2 OR'ed Bus in Off State */
#define OS_SRC_CAN2_Error_ADDR              (OS_IRQ_ID_OFFSET + 93)              /**< CAN2 Interrupt indicating that errors were detected on the CAN bus, Interrupt indicating that errors were detected on the CAN bus for FD messages in the Fast Bit Rate region */
#define OS_SRC_CAN2_ORed_0_15_MB_ADDR       (OS_IRQ_ID_OFFSET + 95)              /**< CAN2 OR'ed Message buffer (0-15) */
#define OS_SRC_CAN2_ORed_16_31_MB_ADDR      (OS_IRQ_ID_OFFSET + 96)              /**< CAN1 OR'ed Message buffer (16-31) */
#define OS_SRC_FTM0_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 99)              /**< FTM0 Channel 0 and 1 interrupt */
#define OS_SRC_FTM0_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 100)              /**< FTM0 Channel 2 and 3 interrupt */
#define OS_SRC_FTM0_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 101)              /**< FTM0 Channel 4 and 5 interrupt */
#define OS_SRC_FTM0_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 102)              /**< FTM0 Channel 6 and 7 interrupt */
#define OS_SRC_FTM0_Fault_ADDR              (OS_IRQ_ID_OFFSET + 103)              /**< FTM0 Fault interrupt */
#define OS_SRC_FTM0_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 104)              /**< FTM0 Counter overflow and Reload interrupt */
#define OS_SRC_FTM1_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 105)              /**< FTM1 Channel 0 and 1 interrupt */
#define OS_SRC_FTM1_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 106)              /**< FTM1 Channel 2 and 3 interrupt */
#define OS_SRC_FTM1_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 107)              /**< FTM1 Channel 4 and 5 interrupt */
#define OS_SRC_FTM1_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 108)              /**< FTM1 Channel 6 and 7 interrupt */
#define OS_SRC_FTM1_Fault_ADDR              (OS_IRQ_ID_OFFSET + 109)              /**< FTM1 Fault interrupt */
#define OS_SRC_FTM1_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 110)              /**< FTM1 Counter overflow and Reload interrupt */
#define OS_SRC_FTM2_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 111)              /**< FTM2 Channel 0 and 1 interrupt */
#define OS_SRC_FTM2_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 112)              /**< FTM2 Channel 2 and 3 interrupt */
#define OS_SRC_FTM2_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 113)              /**< FTM2 Channel 4 and 5 interrupt */
#define OS_SRC_FTM2_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 114)              /**< FTM2 Channel 6 and 7 interrupt */
#define OS_SRC_FTM2_Fault_ADDR              (OS_IRQ_ID_OFFSET + 115)              /**< FTM2 Fault interrupt */
#define OS_SRC_FTM2_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 116)              /**< FTM2 Counter overflow and Reload interrupt */
#define OS_SRC_FTM3_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 117)              /**< FTM3 Channel 0 and 1 interrupt */
#define OS_SRC_FTM3_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 118)              /**< FTM3 Channel 2 and 3 interrupt */
#define OS_SRC_FTM3_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 119)              /**< FTM3 Channel 4 and 5 interrupt */
#define OS_SRC_FTM3_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 120)              /**< FTM3 Channel 6 and 7 interrupt */
#define OS_SRC_FTM3_Fault_ADDR              (OS_IRQ_ID_OFFSET + 121)              /**< FTM3 Fault interrupt */
#define OS_SRC_FTM3_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 122)              /**< FTM3 Counter overflow and Reload interrupt */
#define OS_SRC_FTM4_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 123)              /**< FTM4 Channel 0 and 1 interrupt */
#define OS_SRC_FTM4_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 124)              /**< FTM4 Channel 2 and 3 interrupt */
#define OS_SRC_FTM4_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 125)              /**< FTM4 Channel 4 and 5 interrupt */
#define OS_SRC_FTM4_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 126)              /**< FTM4 Channel 6 and 7 interrupt */
#define OS_SRC_FTM4_Fault_ADDR              (OS_IRQ_ID_OFFSET + 127)              /**< FTM4 Fault interrupt */
#define OS_SRC_FTM4_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 128)              /**< FTM4 Counter overflow and Reload interrupt */
#define OS_SRC_FTM5_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 129)              /**< FTM5 Channel 0 and 1 interrupt */
#define OS_SRC_FTM5_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 130)              /**< FTM5 Channel 2 and 3 interrupt */
#define OS_SRC_FTM5_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 131)              /**< FTM5 Channel 4 and 5 interrupt */
#define OS_SRC_FTM5_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 132)              /**< FTM5 Channel 6 and 7 interrupt */
#define OS_SRC_FTM5_Fault_ADDR              (OS_IRQ_ID_OFFSET + 133)              /**< FTM5 Fault interrupt */
#define OS_SRC_FTM5_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 134)              /**< FTM5 Counter overflow and Reload interrupt */
#define OS_SRC_FTM6_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 135)              /**< FTM6 Channel 0 and 1 interrupt */
#define OS_SRC_FTM6_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 136)              /**< FTM6 Channel 2 and 3 interrupt */
#define OS_SRC_FTM6_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 137)              /**< FTM6 Channel 4 and 5 interrupt */
#define OS_SRC_FTM6_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 138)              /**< FTM6 Channel 6 and 7 interrupt */
#define OS_SRC_FTM6_Fault_ADDR              (OS_IRQ_ID_OFFSET + 139)              /**< FTM6 Fault interrupt */
#define OS_SRC_FTM6_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 140)              /**< FTM6 Counter overflow and Reload interrupt */
#define OS_SRC_FTM7_Ch0_Ch1_ADDR            (OS_IRQ_ID_OFFSET + 141)              /**< FTM7 Channel 0 and 1 interrupt */
#define OS_SRC_FTM7_Ch2_Ch3_ADDR            (OS_IRQ_ID_OFFSET + 142)              /**< FTM7 Channel 2 and 3 interrupt */
#define OS_SRC_FTM7_Ch4_Ch5_ADDR            (OS_IRQ_ID_OFFSET + 143)              /**< FTM7 Channel 4 and 5 interrupt */
#define OS_SRC_FTM7_Ch6_Ch7_ADDR            (OS_IRQ_ID_OFFSET + 144)              /**< FTM7 Channel 6 and 7 interrupt */
#define OS_SRC_FTM7_Fault_ADDR              (OS_IRQ_ID_OFFSET + 145)              /**< FTM7 Fault interrupt */
#define OS_SRC_FTM7_Ovf_Reload_ADDR         (OS_IRQ_ID_OFFSET + 146)              /**< FTM7 Counter overflow and Reload interrupt */

/* BSW Config Tool reference */
#define OS_SRC_SYSTEM_TIMER_CORE0_ADDR      OS_SRC_SysTick_ADDR
#define OS_SRC_TMPROT_TIMER_CORE0_ADDR      OS_SRC_FTM0_Ovf_Reload_ADDR


/* Interrupt Service Provider */
#define	OS_ARCH_INT_CPU0	                (0x00000000u)
#define	OS_ARCH_INT_CPU1	                (0x00000001u)

#define OS_NVIC_ICTR_ADDRESS                (0xE000E004u)                        /* Interrupt Controller Type Register */
#define OS_NVIC_ISER_BASE_ADDRESS           (0xE000E100u)                        /* Interrupt Set-Enable Register0-15:0xE000E100->0xE000E13C */
#define OS_NVIC_ICER_BASE_ADDRESS           (0xE000E180u)                        /* Interrupt Clear-Enable Register0-15:0xE000E180->0xE000E1BC */
#define OS_NVIC_ISPR_BASE_ADDRESS           (0xE000E200u)                        /* Interrupt Set-Pending Register 0-15:0xE000E200->0xE000E23C */
#define OS_NVIC_ICPR_BASE_ADDRESS           (0xE000E280u)                        /* Interrupt Clear-Pending Register 0-15:0xE000E280->0xE000E2BC */
#define OS_NVIC_IABR_BASE_ADDRESS           (0xE000E300u)                        /* Active Bit Register Register 0-15:0xE000E300->0xE000E37C */
#define OS_NVIC_IPR_BASE_ADDRESS            (0xE000E400u)                        /* Interrupt Priority Register 0-123:0xE000E400->0xE000E7EC */
#define OS_NVIC_STIR_ADDRESS                (0xE000EF00u)                        /* Software Trigger Interrupt Register */
#define OS_NVIC_CPUID_ADDRESS               (0xE000ED00u)
#define OS_NVIC_ICSR_ADDRESS                (0xE000ED04u)
#define OS_NVIC_VTOR_ADDRESS                (0xE000ED08u)
#define OS_NVIC_AIRCR_ADDRESS               (0xE000ED0Cu)
#define OS_NVIC_SCR_ADDRESS                 (0xE000ED10u)
#define OS_NVIC_SHPR_BASE_ADDRESS           (0xE000ED18u)

#define OS_NVIC_ICSR_REG                    OS_REG32(OS_NVIC_ICSR_ADDRESS)
#define OS_NIVC_PENDSVSET_BIT               (1u << 28u)

/* Interrupt priority conversion */
#define OS_NVIC_PRIO_BITS                   (4u)
#define OS_NVIC_PRIO_LEVELS                 (1u << OS_NVIC_PRIO_BITS)
#define OS_NVIC_PRIO_SHIFT                  (8u - OS_NVIC_PRIO_BITS)
/* Logic priority */
#define OS_NVIC_PRIO_MIN                    (0x00u)
#define OS_NVIC_PRIO_MAX                    (0x0Fu)
#define OS_ISR1_PRIO_MAX                    (0x0Eu)
#define OS_ISR2_PRIO_MAX                    (0x08u)

/* OS exception priority configuration (logic interrupt priority)*/
#define OS_CM7_PRIO_CFG_PENDSV              (0xEu)

#define OS_INT_PRIO_PHY_TO_LOG(PhyPrio)         (uint8)(((PhyPrio) ^ 0xFFu) >> OS_NVIC_PRIO_SHIFT)
#define OS_INT_PRIO_LOG_TO_PHY(LogPrio)         (uint8)(((LogPrio) ^ 0xFFu) << OS_NVIC_PRIO_SHIFT)

/*-----------------------------Interrupt Macro-------------------------------*/
/* Disable/Enable interrupt X */
/* Disable/Enable interrupt X */
#define OS_INTERRUPT_ENABLE(id)   if ((uint32)(id) >= 16U) OS_REG32(OS_NVIC_ISER_BASE_ADDRESS + ((((uint32)(id)-(uint32)16U)>>(uint32)5U)<<(uint32)2U)) = ((uint32)1u<<(((uint32)(id)-(uint32)16u) & (uint32)0x1Fu))
#define OS_INTERRUPT_DISABLE(id)  if ((uint32)(id) >= 16U) OS_REG32(OS_NVIC_ICER_BASE_ADDRESS + ((((uint32)(id)-(uint32)16U)>>(uint32)5U)<<(uint32)2U)) = ((uint32)1u<<(((uint32)(id)-(uint32)16u) & (uint32)0x1Fu))


/* Set/Clear interrupt pending X */
#define OS_INTERRUPT_SET_PENDING(id)        \
    if ((id) >= 16U) {OS_REG32(OS_NVIC_STIR_ADDRESS) = (((id)-16U) & 0x1FFu);}

#define OS_INTERRUPT_CLEAR_PENDING(id)      \
    {if ((id) >= 16U) OS_REG32(OS_NVIC_ICPR_BASE_ADDRESS + ((((id)-16U)>>(uint32)5U)<<(uint32)2U)) = ((uint32)1u<<((id)-16U)) & 0x1Fu;}

/* Get interrupt X pending/active status */
#define OS_INTERRUPT_PENDING_STATUS(id)     \
    (((id) >= 16U) ? ((OS_REG32(OS_NVIC_ICPR_BASE_ADDRESS + ((((id)-16U)>>(uint32)5U)<<(uint32)2U)) >> (((id)-16U) & 0x1Fu) ) & 0x01u) : (0U))

#define OS_INTERRUPT_ACTIVE_STATUS(id)      \
    (((id) >= 16U) ? ((OS_REG32(OS_NVIC_IABR_BASE_ADDRESS + ((((id)-16U)>>(uint32)5U)<<(uint32)2U)) >> (((id)-16U) & 0x1Fu)) & 0x01u) : 0U)

#define OS_INTERRUPT_PENDING_OR_ACTIVE_STATUS(id)                                                                 \
    (((id) >= 16U) ? (((OS_REG32(OS_NVIC_IABR_BASE_ADDRESS + ((((id)-16U)>>(uint32)5U)<<(uint32)2U)) >> (((id)-16U) & 0x1Fu) ) & 0x01u) |   \
                   ((OS_REG32(OS_NVIC_ICPR_BASE_ADDRESS + ((((id)-16U)>>(uint32)5U)<<(uint32)2U)) >> (((id)-16U) & 0x1Fu) ) & 0x01u)) : 0U)

/* Check interrupt enable status */
#define OS_INTERRUPT_CHECK_STATUS(id)       \
    ((id >= 16U) ? ((OS_REG32(OS_NVIC_ISER_BASE_ADDRESS + ((((id)-16U)>>5U)<<2U)) >> (((id)-16U) & 0x1Fu)) & 0x01u) : 0U)

/* Set interrupt priority */
#define OS_INTERRUPT_SYS_PRIO(id)     (OS_REG8(OS_NVIC_SHPR_BASE_ADDRESS + (uint32)(id)))

#define OS_INTERRUPT_NVIC_PRIO(id)    (OS_REG8(OS_NVIC_IPR_BASE_ADDRESS + (uint32)(id)))

#define OS_INTERRUPT_SET_PRIO(id, prio)              (OS_INTERRUPT_NVIC_PRIO((uint32)(id)-16U) = (uint8)(prio));   
    

#define OS_INTERRUPT_SYS_SET_PRIO(id, prio)          OS_INTERRUPT_SYS_PRIO((uint32)(id)-4U) = (uint8)(prio);  

/* Install interrupt */
#define    OS_INTERRUPT_INSTALL(id, prio, srcType)\
    OS_INTERRUPT_SET_PRIO(id, OS_INT_PRIO_LOG_TO_PHY(prio));\
    OS_INTERRUPT_ENABLE(id)

#define    OS_INTERRUPT_SYS_INSTALL(id, prio, srcType)\
    OS_INTERRUPT_SYS_SET_PRIO(id, OS_INT_PRIO_LOG_TO_PHY(prio));\
    OS_INTERRUPT_ENABLE(id)

#define OS_INTERRUPT_Unload(id, prio, srcType)\
    OS_INTERRUPT_DISABLE(id)
extern FUNC(void, OS_CODE) Os_TaskSchedule(void);
extern FUNC(void, OS_CODE) Os_DisableInterruptSource(uint32 vIsrSrc, uint32 vIsrSrcType);
extern FUNC(void, OS_CODE) Os_ClearPendingInterrupt(uint32 vIsrSrc, uint32 vIsrSrcType);
extern FUNC(Os_IsrStateType, OS_CODE) Os_GetIsrSourceState(uint32 vIsrSrc, uint32 vIsrSrcType);
extern FUNC(void, OS_CODE) Os_EnableInterruptSource(uint32 vIsrSrc, uint32 vIsrSrcType);

/* type of an Interrupt Service Routine (ISR) */
typedef void (*Os_isrhnd)(void);

#endif  /* #ifndef ARCH_IRQ_H */
/*=======[E N D   O F   F I L E]==============================================*/
