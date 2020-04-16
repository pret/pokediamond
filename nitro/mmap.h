#ifndef NITRO_MMAP_H
#define NITRO_MMAP_H

#define HW_MAIN_MEM             0x02000000
#define HW_MAIN_MEM_SIZE        0x00400000
#define HW_MAIN_MEM_EX_SIZE     0x00800000

#define HW_ARENA_INFO_BUF       (HW_MAIN_MEM + 0x007ffda0)      // Arena data structure
#define HW_ROM_HEADER_BUF       (HW_MAIN_MEM + 0x007ffe00)      // ROM registration area data buffer


#endif