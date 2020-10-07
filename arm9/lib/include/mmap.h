#ifndef POKEDIAMOND_ARM9_MMAP_H
#define POKEDIAMOND_ARM9_MMAP_H

#include "nitro/types.h"
#include "nitro/mmap_shared.h"

extern u32 SDK_AUTOLOAD_DTCM_START[];

#define HW_MAIN_MEM_EX_SIZE     0x00800000
#define HW_MAIN_MEM_DEBUGGER_OFFSET     0x00700000

#define HW_ITCM_IMAGE 0x01000000
#define HW_ITCM                 0x01FF8000
#define HW_ITCM_SIZE            0x00008000
#define HW_ITCM_END (HW_ITCM + HW_ITCM_SIZE)

#define HW_IOREG                0x04000000
#define HW_CTRDG_ROM            0x08000000
#define HW_BIOS                 0xffff0000

#define HW_DTCM                 ((u32)SDK_AUTOLOAD_DTCM_START)
#define HW_DTCM_SIZE            0x00004000

#define HW_DTCM_SYSRV           (HW_DTCM + 0x00003fc0)
#define HW_INTR_CHECK_BUF       (HW_DTCM_SYSRV + 0x38)
#define HW_EXCP_VECTOR_BUF      (HW_DTCM_SYSRV + 0x1C)


#define HW_CARD_ROM_HEADER_SIZE 0x00000160
#define HW_DOWNLOAD_PARAMETER_SIZE      0x00000020

#define HW_CARD_ROM_HEADER      (HW_MAIN_MEM + 0x007ffa80)
#define HW_RESET_PARAMETER_BUF  (HW_MAIN_MEM + 0x007ffc20)
#define HW_ROM_BASE_OFFSET_BUF  (HW_MAIN_MEM + 0x007ffc2c)
#define HW_ROM_HEADER_BUF       (HW_MAIN_MEM + 0x007ffe00)      // ROM registration area data buffer
#define HW_RED_RESERVED         (HW_MAIN_MEM + 0x007ff800)      // Some kind of reserved data for shared memory
#define HW_MAIN_MEM_EX_END      (HW_MAIN_MEM + HW_MAIN_MEM_EX_SIZE)
#define HW_MAIN_MEM_SHARED      (HW_MAIN_MEM_EX_END - HW_MAIN_MEM_SHARED_SIZE)
#define HW_DTCM_SVC_STACK_END   (HW_DTCM + 0x00003fc0)
#define HW_DTCM_SVC_STACK       (HW_DTCM_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_DTCM_IRQ_STACK_END   (HW_DTCM_SVC_STACK)

#define HW_MAIN_MEM_SUB         (HW_MAIN_MEM_MAIN_END + 0x400000)

#define HW_BIOS_EXCP_STACK_MAIN (HW_MAIN_MEM + 0x007ffd80)
#define HW_EXCP_VECTOR_MAIN     (HW_MAIN_MEM + 0x007ffd9c)

#define HW_PXI_SIGNAL_PARAM_ARM9        (HW_MAIN_MEM + 0x007fff80)

#define HW_WM_RSSI_POOL         (HW_MAIN_MEM + 0x007fff98)

#define HW_COMPONENT_PARAM      (HW_MAIN_MEM + 0x007fff9c)

#define HW_LOCK_ID_FLAG_MAIN    (HW_MAIN_MEM + 0x007fffb0)
#define HW_SHARED_LOCK_BUF      (HW_MAIN_MEM + 0x007fffc0)
#define HW_CARD_LOCK_BUF        (HW_MAIN_MEM + 0x007fffe0)

#define OSi_MAIN_ARENA_HI_DEFAULT       (HW_MAIN_MEM_MAIN_END)
#define OSi_MAINEX_ARENA_HI_DEFAULT     (HW_MAIN_MEM + HW_MAIN_MEM_DEBUGGER_OFFSET)
#define HW_ITCM_ARENA_HI_DEFAULT        (HW_ITCM + HW_ITCM_SIZE)
#define HW_SHARED_ARENA_HI_DEFAULT      (HW_RED_RESERVED - HW_CARD_ROM_HEADER_SIZE - HW_DOWNLOAD_PARAMETER_SIZE)
#define HW_SHARED_ARENA_LO_DEFAULT      (HW_MAIN_MEM_SHARED)
#define OSi_WRAM_MAIN_ARENA_HI_DEFAULT  (HW_WRAM)
#define OSi_WRAM_MAIN_ARENA_LO_DEFAULT  (HW_WRAM)

#define HW_BG_PLTT              0x05000000
#define HW_BG_PLTT_END          0x05000200
#define HW_BG_PLTT_SIZE         (HW_BG_PLTT_END-HW_BG_PLTT)
#define HW_OBJ_PLTT             0x05000200
#define HW_OBJ_PLTT_END         0x05000400
#define HW_OBJ_PLTT_SIZE        (HW_OBJ_PLTT_END-HW_OBJ_PLTT)
#define HW_PLTT                 HW_BG_PLTT
#define HW_PLTT_END             HW_OBJ_PLTT_END
#define HW_PLTT_SIZE            (HW_PLTT_END-HW_PLTT)
#define HW_DB_BG_PLTT           0x05000400
#define HW_DB_BG_PLTT_END       0x05000600
#define HW_DB_BG_PLTT_SIZE      (HW_DB_BG_PLTT_END-HW_DB_BG_PLTT)
#define HW_DB_OBJ_PLTT          0x05000600
#define HW_DB_OBJ_PLTT_END      0x05000800
#define HW_DB_OBJ_PLTT_SIZE     (HW_DB_OBJ_PLTT_END-HW_DB_OBJ_PLTT)
#define HW_DB_PLTT              HW_DB_BG_PLTT
#define HW_DB_PLTT_END          HW_DB_OBJ_PLTT_END
#define HW_DB_PLTT_SIZE         (HW_DB_PLTT_END-HW_DB_PLTT)
#define HW_LCDC_VRAM            0x6800000
#define HW_LCDC_VRAM_END        0x68a4000
#define HW_LCDC_VRAM_SIZE       (HW_LCDC_VRAM_END - HW_LCDC_VRAM)
#define HW_OAM                  0x07000000
#define HW_OAM_END              0x07000400
#define HW_OAM_SIZE             (HW_OAM_END-HW_OAM)
#define HW_DB_OAM               0x07000400
#define HW_DB_OAM_END           0x07000800
#define HW_DB_OAM_SIZE          (HW_DB_OAM_END-HW_DB_OAM)

#define HW_DTCM_SYSRV_OFS_INTR_VECTOR   0x3c
#define HW_RESET_VECTOR         0xffff0000

#endif //POKEDIAMOND_ARM9_MMAP_H
