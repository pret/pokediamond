#ifndef NITRO_MMAP_H
#define NITRO_MMAP_H

#define HW_MAIN_MEM             0x02000000
#define HW_MAIN_MEM_SIZE        0x00400000
#define HW_MAIN_MEM_EX_SIZE     0x00800000
#define HW_MAIN_MEM_MAIN_SIZE   0x003E0000
#define HW_MAIN_MEM_DEBUGGER_OFFSET     0x00700000

#define HW_ITCM                 0x01FF8000
#define HW_ITCM_SIZE            0x00008000

#define HW_WRAM                 0x037F8000

#define HW_CARD_ROM_HEADER_SIZE 0x00000160
#define HW_DOWNLOAD_PARAMETER_SIZE      0x00000020

#define HW_ARENA_INFO_BUF       (HW_MAIN_MEM + 0x007ffda0)      // Arena data structure
#define HW_ROM_HEADER_BUF       (HW_MAIN_MEM + 0x007ffe00)      // ROM registration area data buffer
#define HW_RED_RESERVED         (HW_MAIN_MEM + 0x007ff800)      // Some kind of reserved data for shared memory

#define OSi_MAIN_ARENA_HI_DEFAULT       (HW_MAIN_MEM + HW_MAIN_MEM_MAIN_SIZE)
#define OSi_MAINEX_ARENA_HI_DEFAULT     (HW_MAIN_MEM + HW_MAIN_MEM_DEBUGGER_OFFSET)
#define HW_ITCM_ARENA_HI_DEFAULT        (HW_ITCM + HW_ITCM_SIZE)
#define HW_SHARED_ARENA_HI_DEFAULT      (HW_RED_RESERVED - HW_CARD_ROM_HEADER_SIZE - HW_DOWNLOAD_PARAMETER_SIZE)
#define OSi_WRAM_MAIN_ARENA_HI_DEFAULT  (HW_WRAM)

#endif