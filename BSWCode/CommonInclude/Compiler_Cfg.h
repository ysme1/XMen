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
 **  FILENAME    :Compiler_Cfg.h                                               **
 **                                                                            **
 **  Created on  : 2020-03-24                                                  **
 **  Author      : qinchun.yang                                                **
 **  Vendor      :                                                             **
 **  DESCRIPTION :                                                             **
 **                                                                            **
 **  SPECIFICATION(S) :   AUTOSAR classic Platform R19-11                      **
 **                                                                            **
 *******************************************************************************/
/* PRQA S 3108-- */

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#ifdef __cplusplus
#define BEGIN_C_DECLS \
    extern "C"        \
    {
#define END_C_DECLS }
#else
#define BEGIN_C_DECLS
#define END_C_DECLS
#endif

/* eth */
#define ETH_VAR

/* ethif */
#define ETHIF_CODE
#define ETHIF_VAR

#define ETHIF_APPL_DATA

/* tcpip */
#define TCPIP_CODE
#define TCPIP_VAR

#define TCPIP_APPL_CONST
#define TCPIP_APPL_VAR
#define TCPIP_CONST

#define TCPIP_CONFIG_DATA

#define TCPIP_APPL_DATA
#define TCPIP_APPL_CODE
#define TCPIP_VAR_ZERO_INIT

/* csm */
#define CSM_APPL_DATA
#define CSM_CONST
#define CSM_CODE

/* keym */
#define KEYM_CONST_PBCFG
#define KEYM_APPL_CONST

#define KEYM_APPL_CODE
#define KEYM_CODE

#define KEYM_APPL_DATA
#define KEYM_CONST

/* det */
#define DET_CODE

/* ethsm */
#define ETHSM_CODE

/* StbM */
#define STBM_CODE
#define STBM_APPL_DATA
#define STBM_CONST_PBCFG
#define STBM_VAR_CLEARED_BOOLEAN
#define STBM_VAR
#define STBM_CONST

/* CanTSyn */
#define CANTSYN_CODE
#define CANTSYN_APPL_CONST
#define CANTSYN_VAR_NOINIT
#define CANTSYN_VAR_POWER_ON_INIT
#define CANTSYN_APPL_DATA
#define CANTSYN_CONST_PBCFG
#define CANTSYN_CONST

/* EthTSyn */
#define ETHTSYN_CODE
#define ETHTSYN_VAR
#define ETHTSYN_APPL_DATA
#define ETHTSYN_VAR_CLEARED_BOOLEAN

/* Tm */
#define TM_APPL_DATA
#define TM_APPL_CONST
#define TM_CODE

/* CanTrcv */
#define CANTRCV_CODE
#define CANTRCV_VAR_NOINIT
#define CANTRCV_CONST_PBCFG
#define CANTRCV_VAR_POWER_ON_INIT
#define CANTRCV_APPL_DATA

/* LinIf */
#define LINIF_CODE
#define LINIF_VAR
#define LINIF_APPL_CONST
#define LINIF_APPL_DATA
#define LINIF_CONST
#define LINIF_DATA

/* LinSM */
#define LINSM_CODE
#define LINSM_VAR_POWER_ON_INIT
#define LINSM_VAR
#define LINSM_CONST
#define LINSM_CONST_PBCFG
#define LinSM_APPL_DATA

/* SecOC */
#define SECOC_APPL_CONST
#define SECOC_APPL_DATA
#define SECOC_CFG_CONST
#define SECOC_CFG_VAR
#define SECOC_CODE
#define SECOC_CONST
#define SECOC_VAR_POWER_ON_INIT

/* Sd */
#define SD_CFG_CONST
#define SD_CFG_VAR
#define SD_CODE
#define SD_VAR
#define SD_CONST

/* SomeIpTp */
#define SOMEIPTP_APPL_CONST
#define SOMEIPTP_APPL_DATA
#define SOMEIPTP_CODE
#define SOMEIPTP_CONST
#define SOMEIPTP_VAR
#define SOMEIPTP_VAR_POWER_ON_INIT

/* EthSM */
#define ETHSM_APPL_DATA
#define ETHSM_CODE
#define ETHSM_CONST
#define ETHSM_VAR
#define ETHSM_VAR_POWER_ON_INIT

/* UdpNm */
#define UDPNM_APPL_CONST
#define UDPNM_APPL_DATA
#define UDPNM_CODE
#define UDPNM_VAR
#define UDPNM_VAR_POWER_ON_INIT

/* cantp */
#define CANTP_VAR_POWER_ON_INIT
#define CANTP_CODE
#define CANTP_CONST
#define CANTP_APPL_CONST
#define CANTP_APPL_DATA
#define CANTP_APPL_CODE
#define CANTP_VAR_NOINIT
#define CANTP_VAR

/* dcm */
#define DCM_VAR_POWER_ON_INIT
#define DCM_CODE
#define DCM_CONST_PBCFG
#define DCM_VAR
#define DCM_APPL_CODE
#define DCM_CONST
#define DCM_VAR_NOINIT
#define DCM_APPL_CONST
#define DCM_APPL_DATA

/* Dlt */
#define DLT_VAR_POWER_ON_INIT
#define DLT_CODE
#define DLT_CONST_PBCFG
#define DLT_VAR
#define DLT_APPL_CODE
#define DLT_CONST
#define DLT_VAR_NOINIT
#define DLT_APPL_CONST
#define DLT_APPL_DATA

/* Det */
#define DET_VAR_POWER_ON_INIT
#define DET_CODE
#define DET_CONST_PBCFG
#define DET_VAR
#define DET_APPL_CODE
#define DET_CONST
#define DET_VAR_NOINIT
#define DET_APPL_CONST
#define DET_APPL_DATA

/* Wdg */
#define WDG_VAR_POWER_ON_INIT
#define WDG_CODE
#define WDG_CONST_PBCFG
#define WDG_VAR
#define WDG_APPL_CODE
#define WDG_CONST
#define WDG_VAR_NOINIT
#define WDG_APPL_CONST
#define WDG_APPL_DATA

/* WdgIf */
#define WDGIF_VAR_POWER_ON_INIT
#define WDGIF_CODE
#define WDGIF_CONST_PBCFG
#define WDGIF_VAR
#define WDGIF_APPL_CODE
#define WDGIF_CONST
#define WDGIF_VAR_NOINIT
#define WDGIF_APPL_CONST
#define WDGIF_APPL_DATA

/* doip */
#define DOIP_VAR
#define DOIP_CODE
#define DOIP_VAR_CLEARED
#define DOIP_VAR_INIT
#define DOIP_APPL_CONST
#define DOIP_CONST
#define DOIP_APPL_CODE

/* nvm */
#define NVM_CODE
#define NVM_VAR
#define NVM_CONST
#define NVM_VAR_NOINIT
#define NVM_APPL_DATA
#define NVM_VAR_POWER_ON_INIT
#define NVM_APPL_CODE

/* MemIf */
#define MEMIF_CODE
#define MEMIF_VAR
#define MEMIF_CONST
#define MEMIF_VAR_NOINIT
#define MEMIF_APPL_DATA
#define MEMIF_VAR_POWER_ON_INIT
#define MEMIF_APPL_CODE

/* Fee */
#define FEE_CODE
#define FEE_VAR
#define FEE_CONST
#define FEE_VAR_NOINIT
#define FEE_APPL_DATA
#define FEE_VAR_POWER_ON_INIT
#define FEE_APPL_CODE

/* Fls */
#define FLS_CODE
#define FLS_VAR
#define FLS_CONST
#define FLS_VAR_NOINIT
#define FLS_APPL_DATA
#define FLS_VAR_POWER_ON_INIT
#define FLS_APPL_CODE

/* EA */
#define EA_CODE
#define EA_VAR
#define EA_CONST
#define EA_VAR_NOINIT
#define EA_APPL_DATA
#define EA_VAR_POWER_ON_INIT
#define EA_APPL_CODE

/* Eep */
#define EEP_CODE
#define EEP_VAR
#define EEP_CONST
#define EEP_VAR_NOINIT
#define EEP_APPL_DATA
#define EEP_VAR_POWER_ON_INIT
#define EEP_APPL_CODE

/* dem */
#define DEM_CODE
#define DEM_CONST
#define DEM_VAR
#define DEM_CONST_PBCFG
#define DEM_APPL_DATA

/* fim */
#define FIM_VAR_INIT_8
#define FIM_APPL_DATA
#define FIM_VAR_NO_INIT_UNSPECIFIED
#define FIM_CODE

/* canif */
#define CANIF_VAR_POWER_ON_INIT
#define CANIF_CONST
#define CANIF_VAR
#define CANIF_CODE
#define CANIF_APPL_DATA
#define CANIF_CONST_PBCFG
#define CANIF_APPL_CONST
#define CANIF_APPL_CODE

/* com */
#define COM_VAR_POWER_ON_INIT
#define COM_VAR
#define COM_CODE
#define COM_APPL_CONST
#define COM_APPL_DATA
#define COM_CONST_PBCFG
#define COM_CONST
#define COM_APPL_CODE

/* comxf */
#define COMXF_CODE
#define COMXF_CONST
#define COMXF_VAR
#define COMXF_VAR_POWER_ON_INIT
#define COMXF_CONST_PBCFG

/* ipdum */
#define IPDUM_VAR_POWER_ON_INIT
#define IPDUM_CONST
#define IPDUM_VAR_NOINIT
#define IPDUM_CODE
#define IPDUM_APPL_DATA
#define IPDUM_APPL_CONST
#define IPDUM_RXINDICATION_CODE
#define IPDUM_TXCONFIRMATION_CODE
#define IPDUM_TRIGGERTRANSMIT_CODE

/* ldcom */
#define LDCOM_VAR_POWER_ON_INIT
#define LDCOM_CONST
#define LDCOM_APPL_DATA
#define LDCOM_CODE
#define LDCOM_COPYTXDATA_CODE
#define LDCOM_TPTXCONFIRMATION_CODE
#define LDCOM_STARTOFRECEPTION_CODE
#define LDCOM_COPYRXDATA_CODE
#define LDCOM_TPRXINDICATION_CODE
#define LDCOM_RXINDICATION_CODE
#define LDCOM_TXCONFIRMATION_CODE
#define LDCOM_TRIGGERTRANSMIT_CODE
#define LDCOM_APPL_CODE
#define LDCOM_CONST_PBCFG

/* pdur */
#define PDUR_VAR_POWER_ON_INIT
#define PDUR_VAR
#define PDUR_APPL_DATA
#define PDUR_CODE
#define PDUR_CONST
#define PDUR_CONST_PBCFG
#define PDUR_APPL_CODE

/* soad */
#define SOAD_APPL_DATA
#define SOAD_APPL_CONST
#define SOAD_VAR_POWER_ON_INIT
#define SOAD_VAR
#define SOAD_CODE
#define SOAD_CONST
#define SOAD_CALLBACK_CODE
#define SOAD_APPL_CODE
#define SOAD_CONST_PBCFG

/* comm */
#define COMM_VAR_POWER_ON_INIT
#define COMM_APPL_CONST
#define COMM_APPL_DATA
#define COMM_CODE
#define COMM_COM_CODE
#define COMM_DCM_CODE
#define COMM_ECUM_USED
#define COMM_CONST
#define COMM_VAR
#define COMM_NM_CODE
#define ComM_CONFIG_DATA

/*nm*/
#define NM_CODE
#define NM_APPL_DATA
#define NM_VAR_CLEARED_BOOLEAN
#define NM_VAR_NO_INIT_UNSPECIFIED

/*cannm*/
#define CANNM_APPL_CONST
#define CANNM_APPL_DATA
#define CANNM_CODE
#define CANNM_VAR
#define CANNM_VAR_POWER_ON_INIT

/*cansm*/
#define CANNM_VAR_POWER_ON_INIT
#define CANSM_CONFIG_DATA
#define CANSM_VAR
#define CANSM_CODE
#define CANSM_COMM_CODE
#define CANSM_ECUM_CODE
#define CANSM_CONTROLLERBUSOFF_CODE
#define CANSM_CONTROLLERNODEINDICATION_CODE
#define CANSM_TRANSCEIVERMODEINDICATION_CODE
#define CANSM_CLEARTRCVWUFFLAGINDICATION_CODE
#define CANSM_CHECKTRANSCEIVERWAKEFLAGINDICATION_CODE
#define CANSM_CONFIRMPNAVAILABILITY_CODE
#define CANSM_CURRENTICOMCONFIGURATION_CODE
#define CANSM_TXTIMEOUTEXCEPTION_CODE

/*EthTrcv*/
#define ETHTRCV_VAR_NOINIT
#define ETHTRCV_VAR_ZERO_INIT
#define ETHTRCV_CODE
#define ETHTRCV_CONFIG_DATA
#define ETHTRCV_CONST
#define ETHTRCV_APPL_DATA

/*crc*/
#define CRC_CODE
#define CRC_APPL_CONST

/*e2e*/
#define E2E_APPL_DATA
#define E2E_CODE

/*e2exf*/
#define E2EXF_CONST
#define E2EXF_CODE
#define E2EXF_VAR_POWER_ON_INIT
#define E2EXF_VAR

/* IoHwAbDrv */
#define IOHWABDRV_VAR_POWER_ON_INIT
#define IOHWABDRV_APPL_DATA
#define IOHWABDRV_CODE
#define IOHWABDRV_COM_CODE
#define IOHWABDRV_DCM_CODE
#define IOHWABDRV_ECUM_USED
#define IOHWABDRV_CONST
#define IOHWABDRV_VAR
#define IOHWABDRV_NM_CODE
#define IOHWABDRV_CONFIG_DATA

/* IoHwAb */
#define IOHWAB_VAR_POWER_ON_INIT
#define IOHWAB_APPL_DATA
#define IOHWAB_CODE
#define IOHWAB_COM_CODE
#define IOHWAB_DCM_CODE
#define IOHWAB_ECUM_USED
#define IOHWAB_CONST
#define IOHWAB_VAR
#define IOHWAB_NM_CODE
#define IOHWAB_CONFIG_DATA

/* Rte_IoHwAb */
#define RTEIOHWAB_VAR_POWER_ON_INIT
#define RTEIOHWAB_APPL_DATA
#define RTEIOHWAB_CODE
#define RTEIOHWAB_COM_CODE
#define RTEIOHWAB_DCM_CODE
#define RTEIOHWAB_ECUM_USED
#define RTEIOHWAB_CONST
#define RTEIOHWAB_VAR
#define RTEIOHWAB_NM_CODE
#define RTEIOHWAB_CONFIG_DATA

/* J193DCM */
#define J1939DCM_CONST_UNSPECIFIED
#define J1939DCM_CONST_BOOLEAN
#define J1939DCM_CONST_16
#define J1939DCM_VAR_NO_INIT_UNSPECIFIED
#define J1939DCM_APPL_DATA

/* J1939RM */
#define J1939RM_APPL_DATA
#define J1939RM_VAR_NO_INIT_UNSPECIFIED
#define J1939RM_VAR_CLEARED_UNSPECIFIED
#define J1939RM_CONFIG_DATA
#define J1939RM_CONST_UNSPECIFIED
#define J1939RM_CONST_16
#define J1939RM_CONST_BOOLEAN
#define J1939RM_PBCFG

/* J1939Nm */
#define J1939NM_APPL_DATA
#define J1939NM_CONST_BOOLEAN
#define J1939NM_CONST_8
#define J1939NM_CONST_16
#define J1939NM_CONST_BOOLEAN
#define J1939NM_CONST_UNSPECIFIED
#define J1939NM_VAR_CLEARED_32
#define J1939NM_VAR_UNSPECIFIED

/* J1939TP */
#define J1939TP_APPL_DATA
#define J1939TP_CONST_UNSPECIFIED
#define J1939TP_CONST_UNSPECIFIED
#define J1939TP_CONST_8

#endif /* COMPILER_CFG_H */
