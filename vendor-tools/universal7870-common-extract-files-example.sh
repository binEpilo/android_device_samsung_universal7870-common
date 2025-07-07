#!/bin/bash

COMMON_A6LTE_PATH="/media/flominator/40810d67-1e17-42cc-8147-8500cdc3df4b/phoenix_firmware_dumper-main/SAMFW.COM_SM-A600F_AFG_A600FJXU9CVB1_fac"
COMMON_A6LTE_P_PATH="/media/flominator/40810d67-1e17-42cc-8147-8500cdc3df4b/phoenix_firmware_dumper-main/Samfw.com_SM-A600F_PAK_A600FJXU9CUH3_fac"
COMMON_A7Y17LTE_PATH="/media/flominator/40810d67-1e17-42cc-8147-8500cdc3df4b/phoenix_firmware_dumper-main/Samfw.com_SM-A720S_SKC_A720SKSU5CTL2_fac"
COMMON_M10LTE_PATH="/media/flominator/40810d67-1e17-42cc-8147-8500cdc3df4b/phoenix_firmware_dumper-main/Samfw.com_SM-M105F_BKD_M105FDDS4CVB1_fac"
COMMON_STARLTE_PATH="/media/flominator/40810d67-1e17-42cc-8147-8500cdc3df4b/phoenix_firmware_dumper-main/SAMFW.COM_SM-G960F_DBT_G960FXXUHFVG4_fac"

./../extract-files.sh \
-pfs proprietary-files_a6lte.txt "${COMMON_A6LTE_PATH}" \
-pfs proprietary-files_a6lte_p.txt "${COMMON_A6LTE_P_PATH}" \
-pfs proprietary-files_a7y17lte.txt "${COMMON_A7Y17LTE_PATH}" \
-pfs proprietary-files_m10lte.txt "${COMMON_M10LTE_PATH}" \
-pfs proprietary-files_starlte.txt "${COMMON_STARLTE_PATH}" \
