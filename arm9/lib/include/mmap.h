#ifndef NITRO_MMAP_H
#define NITRO_MMAP_H

#include "types.h"

extern u32 SDK_AUTOLOAD_DTCM_START[];

#define HW_MAIN_MEM             0x02000000
#define HW_MAIN_MEM_SIZE        0x00400000
#define HW_MAIN_MEM_EX_SIZE     0x00800000
#define HW_MAIN_MEM_MAIN_SIZE   0x003E0000
#define HW_MAIN_MEM_SHARED_SIZE 0x00001000
#define HW_MAIN_MEM_DEBUGGER_OFFSET     0x00700000

#define HW_ITCM_IMAGE 0x01000000
#define HW_ITCM                 0x01FF8000
#define HW_ITCM_SIZE            0x00008000
#define HW_ITCM_END (HW_ITCM + HW_ITCM_SIZE)

#define HW_WRAM                 0x037F8000

#define HW_DTCM                 ((u32)SDK_AUTOLOAD_DTCM_START)
#define HW_DTCM_SIZE            0x00004000

#define HW_DTCM_SYSRV           (HW_DTCM + 0x00003fc0)
#define HW_INTR_CHECK_BUF       (HW_DTCM_SYSRV + 0x38)

#define HW_CARD_ROM_HEADER_SIZE 0x00000160
#define HW_DOWNLOAD_PARAMETER_SIZE      0x00000020

#define HW_RESET_PARAMETER_BUF  (HW_MAIN_MEM + 0x007ffc20)
#define HW_ROM_BASE_OFFSET_BUF  (HW_MAIN_MEM + 0x007ffc2c)
#define HW_WM_BOOT_BUF          (HW_MAIN_MEM + 0x007ffc40)
#define HW_ARENA_INFO_BUF       (HW_MAIN_MEM + 0x007ffda0)      // Arena data structure
#define HW_ROM_HEADER_BUF       (HW_MAIN_MEM + 0x007ffe00)      // ROM registration area data buffer
#define HW_RED_RESERVED         (HW_MAIN_MEM + 0x007ff800)      // Some kind of reserved data for shared memory
#define HW_MAIN_MEM_SYSTEM      (HW_MAIN_MEM + 0x007ffc00)
#define HW_MAIN_MEM_MAIN_END    (HW_MAIN_MEM + HW_MAIN_MEM_MAIN_SIZE)
#define HW_MAIN_MEM_EX_END      (HW_MAIN_MEM + HW_MAIN_MEM_EX_SIZE)
#define HW_MAIN_MEM_SHARED      (HW_MAIN_MEM_EX_END - HW_MAIN_MEM_SHARED_SIZE)
#define HW_DTCM_SVC_STACK_END   (HW_DTCM + 0x00003fc0)
#define HW_SVC_STACK_SIZE       0x00000040
#define HW_DTCM_SVC_STACK       (HW_DTCM_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_DTCM_IRQ_STACK_END   (HW_DTCM_SVC_STACK)

#define HW_BIOS_EXCP_STACK_MAIN (HW_MAIN_MEM + 0x007ffd80)
#define HW_EXCP_VECTOR_MAIN     (HW_MAIN_MEM + 0x007ffd9c)

#define HW_PXI_SIGNAL_PARAM_ARM9        (HW_MAIN_MEM + 0x007fff80)

#define HW_WM_RSSI_POOL         (HW_MAIN_MEM + 0x007fff98)

#define HW_COMPONENT_PARAM      (HW_MAIN_MEM + 0x007fff9c)

#define HW_LOCK_ID_FLAG_MAIN    (HW_MAIN_MEM + 0x007fffb0)
#define HW_SHARED_LOCK_BUF      (HW_MAIN_MEM + 0x007fffc0)
#define HW_CARD_LOCK_BUF        (HW_MAIN_MEM + 0x007fffe0)
#define HW_CTRDG_LOCK_BUF       (HW_MAIN_MEM + 0x007fffe8)

#define HW_BUTTON_XY_BUF        (HW_MAIN_MEM + 0x007fffa8)

#define OSi_MAIN_ARENA_HI_DEFAULT       (HW_MAIN_MEM_MAIN_END)
#define OSi_MAINEX_ARENA_HI_DEFAULT     (HW_MAIN_MEM + HW_MAIN_MEM_DEBUGGER_OFFSET)
#define HW_ITCM_ARENA_HI_DEFAULT        (HW_ITCM + HW_ITCM_SIZE)
#define HW_SHARED_ARENA_HI_DEFAULT      (HW_RED_RESERVED - HW_CARD_ROM_HEADER_SIZE - HW_DOWNLOAD_PARAMETER_SIZE)
#define HW_SHARED_ARENA_LO_DEFAULT      (HW_MAIN_MEM_SHARED)
#define OSi_WRAM_MAIN_ARENA_HI_DEFAULT  (HW_WRAM)
#define OSi_WRAM_MAIN_ARENA_LO_DEFAULT  (HW_WRAM)

#include "OS_thread.h" //not ideal but it's necessary
#include "OS_spinLock.h"

typedef struct {
    u8      bootCheckInfo[0x20];       // 000-01f:   32byte boot check info
    u32     resetParameter;            // 020-023:    4byte reset parameter
    u8      padding5[0x8];             // 024-02c:  (8byte)
    u32     romBaseOffset;             // 02c-02f:    4byte ROM offset of own program
    u8      cartridgeModuleInfo[12];   // 030-03b:   12byte cartridge module info
    u32     vblankCount;               // 03c-03f:    4byte V-Blank Count
    u8      wmBootBuf[0x40];           // 040-07f:   64byte WM multiboot buffer
    u8      nvramUserInfo[0x100];      // 080-17f: 256bytes NVRAM user info
    u8      isd_reserved1[0x20];       // 180-19f:  32bytes ISDebugger reserved
    u8      arenaInfo[0x48];           // 1a0-1e7:  72byte Arena information
    u8      real_time_clock[8];        // 1e8-1ef:   8bytes RTC
    u32     dmaClearBuf[4];            // 1f0-1ff:  16bytes DMA clear information buffer (for ARM9-TEG)
    u8      rom_header[0x160];         // 200-35f: 352bytes ROM registration area info storage buffer
    u8      isd_reserved2[32];         // 360-37f:  32bytes ISDebugger reserved
    u32     pxiSignalParam[2];         // 380-387:   8bytes Param for PXI Signal
    u32     pxiHandleChecker[2];       // 388-38f:   8bytes Flag  for PXI Command Handler Installed
    u32     mic_last_address;          // 390-393:   4bytes MIC latest sampling result storage address
    u16     mic_sampling_data;         // 394-395:   2bytes MIC sampling result
    u16     wm_callback_control;       // 396-397:   2bytes Parameter for WM callback synchronization
    u16     wm_rssi_pool;              // 398-399:   2bytes Random number source depends on WM received signal intensity
    u8      padding3[2];               // 39a-39b: (2bytes)
    u32     component_param;           // 39c-39f:   4bytes Parameter for Component synchronization
    OSThreadInfo *threadinfo_mainp;    // 3a0-3a3:   4bytes Verify that the pointer to ARM9 thread information is initial value 0
    OSThreadInfo *threadinfo_subp;     // 3a4-3a7:   4bytes Verify that the pointer to ARM7 thread information is initial value 0
    u16     button_XY;                 // 3a8-3a9:   2bytes XY button information storage location
    u8      touch_panel[4];            // 3aa-3ad:   4bytes Touch Screen information storage location
    u16     autoloadSync;              // 3ae-3af:   2bytes autoload sync between processors
    u32     lockIDFlag_mainp[2];       // 3b0-3b7:   8bytes lockID management flag (ARM9)
    u32     lockIDFlag_subp[2];        // 3b8-3bf:   8bytes lockID management flag (ARM7)
    struct OSLockWord lock_VRAM_C;     // 3c0-3c7:   8bytes           C - lock buffer
    struct OSLockWord lock_VRAM_D;     // 3c8-3cf:   8bytes VRAM-D - lock buffer
    struct OSLockWord lock_WRAM_BLOCK0; // 3d0-3d7:   8bytes   Block0 - lock buffer
    struct OSLockWord lock_WRAM_BLOCK1; // 3d8-3df:   8bytes CPU internal work RAM - Block1 - lock buffer
    struct OSLockWord lock_CARD;       // 3e0-3e7:   8bytes Game Card - lock buffer
    struct OSLockWord lock_CARTRIDGE;  // 3e8-3ef:   8bytes DS Pak - lock buffer
    struct OSLockWord lock_INIT;       // 3f0-3f7:   8bytes Initialization lock buffer
    u16     mmem_checker_mainp;        // 3f8-3f9:   2bytes MainMomory Size Checker for Main processor
    u16     mmem_checker_subp;         // 3fa-3fb:   2bytes MainMomory Size Checker for Sub processor
    u8      padding4[2];               // 3fc-3fd: (2bytes)
    u16     command_area;              // 3fe-3ff:   2bytes Command Area
} OSSystemWork; //0x027FFC00

#define OS_GetSystemWork()      ((OSSystemWork *)HW_MAIN_MEM_SYSTEM)

#endif