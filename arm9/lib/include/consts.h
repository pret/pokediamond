#ifndef POKEDIAMOND_ARM9_CONSTS_H
#define POKEDIAMOND_ARM9_CONSTS_H

#include "nitro/consts_shared.h"
#include "mmap.h"
#include "registers.h"
#include "systemWork.h"

#define HW_C6_PR_4KB               0x16
#define HW_C6_PR_8KB               0x18
#define HW_C6_PR_16KB              0x1a
#define HW_C6_PR_32KB              0x1c
#define HW_C6_PR_64KB              0x1e
#define HW_C6_PR_128KB             0x20
#define HW_C6_PR_256KB             0x22
#define HW_C6_PR_512KB             0x24
#define HW_C6_PR_1MB               0x26
#define HW_C6_PR_2MB               0x28
#define HW_C6_PR_4MB               0x2a
#define HW_C6_PR_8MB               0x2c
#define HW_C6_PR_16MB              0x2e
#define HW_C6_PR_32MB              0x30
#define HW_C6_PR_64MB              0x32
#define HW_C6_PR_128MB             0x34
#define HW_C6_PR_256MB             0x36
#define HW_C6_PR_512MB             0x38
#define HW_C6_PR_1GB               0x3a
#define HW_C6_PR_2GB               0x3c
#define HW_C6_PR_4GB               0x3e

#define HW_C6_PR_ENABLE            1

#define HW_C9_TCMR_16KB            0x0a
#define HW_C9_TCMR_32MB            0x20

#define HW_CACHE_LINE_SIZE         32

#define PXI_PROC_ARM7              0x01

#define OSi_CONSOLE_NOT_DETECT     0xffffffff

#define OS_CONSOLE_NITRO           0x80000000
#define OS_CONSOLE_DEV_CARD        0x02000000
#define OS_CONSOLE_SIZE_MASK       0x00000003
#define OS_CONSOLE_SIZE_4MB        0x00000001

#define OSi_TCM_REGION_BASE_MASK   0xfffff000

#define OS_IE_V_BLANK              (1UL << 0)

#endif //POKEDIAMOND_ARM9_CONSTS_H
