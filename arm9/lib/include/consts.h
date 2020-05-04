//
// Created by mart on 4/15/20.
//

#ifndef POKEDIAMOND_CONSTS_H
#define POKEDIAMOND_CONSTS_H

#include "mmap.h"

#define HW_PSR_CPU_MODE_MASK       0x1f // CPU mode

#define HW_PSR_DISABLE_FIQ         0x40 // Disable FIQ
#define HW_PSR_DISABLE_IRQ         0x80 // Disable IRQ
#define HW_PSR_DISABLE_IRQ_FIQ     0xc0 // Disable FIQ and IRQ

#define HW_REG_BASE                0x04000000
#define REG_VCOUNT_OFFSET          0x006
#define REG_VCOUNT_ADDR            (HW_REG_BASE + REG_VCOUNT_OFFSET)
#define reg_GX_VCOUNT              (*(REGType16v *)REG_VCOUNT_ADDR)

#define REG_KEYINPUT_OFFSET        0x130
#define REG_KEYINPUT_ADDR          (HW_REG_BASE + REG_KEYINPUT_OFFSET)
#define reg_PAD_KEYINPUT           (*(REGType16v *)REG_KEYINPUT_ADDR)

#define REG_GXSTAT_OFFSET          0x600
#define REG_GXSTAT_ADDR            (HW_REG_BASE + REG_GXSTAT_OFFSET)
#define reg_G3X_GXSTAT             (*(REGType32v *)REG_GXSTAT_ADDR)

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

#define OS_CONSOLE_SIZE_MASK       0x00000003
#define OS_CONSOLE_SIZE_4MB        0x00000001

#define OSi_GetArenaInfo()         (*(OSArenaInfo*)HW_ARENA_INFO_BUF)
#define OSi_TRUNC(n, a)            (((u32) (n)) & ~((a) - 1))
#define OSi_ROUND(n, a)            (((u32) (n) + (a) - 1) & ~((a) - 1))

#define OS_IE_V_BLANK       (1UL << 0)

#endif //POKEDIAMOND_CONSTS_H
