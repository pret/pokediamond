//
// Created by mart on 4/15/20.
//

#ifndef POKEDIAMOND_CONSTS_H
#define POKEDIAMOND_CONSTS_H

#include "mmap.h"

#define HW_PSR_CPU_MODE_MASK       0x1f // CPU mode

#define HW_PSR_FIQ_DISABLE         0x40 // Disable FIQ
#define HW_PSR_IRQ_DISABLE         0x80 // Disable IRQ
#define HW_PSR_IRQ_FIQ_DISABLE     0xc0 // Disable FIQ and IRQ

#define OSi_GetArenaInfo()         (*(OSArenaInfo*)HW_ARENA_INFO_BUF)
#define OSi_TRUNC(n, a)            (((u32) (n)) & ~((a) - 1))
#define OSi_ROUND(n, a)            (((u32) (n) + (a) - 1) & ~((a) - 1))

#endif //POKEDIAMOND_CONSTS_H
