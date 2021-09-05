#include "global.h"
#include "FS_file.h"
#include "OS_terminate_proc.h"
#include "CARD_rom.h"
#include "MI_memory.h"

#include "unk_02022450.h"

static inline u32 GetBakRomCode(void) {
    return ((CARDRomHeader*)HW_MAIN_MEM_SHARED)->game_code;
}

static inline void SetBakRomCode(u32 newCode) {
    ((CARDRomHeader*)HW_MAIN_MEM_SHARED)->game_code = newCode;
}

static inline u16 GetBakRomMaker(void) {
    return ((CARDRomHeader*)HW_MAIN_MEM_SHARED)->maker_code;
}

static const char arc_name[] = "rom";

// Multichar constants are encoded big-endian,
// but this is a little-endian machine.
#define ROM_CODE_ADAJ_BE     'JADA'
#define MAKER_CODE_01_BE     '01'

/*Replacing (HW_MAIN_MEM_SHARED + 0xC) or (HW_MAIN_MEM_SHARED + 0x10) or defining ADAJ or 01 constants causes match failure*/
THUMB_FUNC void FUN_02022450() {
    if (!FS_IsAvailable()) {
        OS_Terminate();
    }
    else {
        CARDRomHeader* card_header_buffer = (CARDRomHeader*)HW_MAIN_MEM_SHARED;
        
        if (GetBakRomCode() == 0) {
            CARD_Init();
            MI_CpuCopy8((u8*)HW_ROM_HEADER_BUF, (u8*)card_header_buffer, HW_CARD_ROM_HEADER_SIZE);
            MI_CpuCopy8((u8*)HW_ROM_HEADER_BUF, (u8*)HW_CARD_ROM_HEADER, HW_CARD_ROM_HEADER_SIZE);
            SetBakRomCode(ROM_CODE_ADAJ_BE);
        }
        FSArchive * const r0 = FS_FindArchive(arc_name, 3);
        r0->fat = card_header_buffer->fat.offset;
        r0->fat_size = card_header_buffer->fat.length;
        r0->fnt = card_header_buffer->fnt.offset;
        r0->fnt_size = card_header_buffer->fnt.length;
        if (GetBakRomCode() != ROM_CODE_ADAJ_BE || GetBakRomMaker() != MAKER_CODE_01_BE) {
            OS_Terminate();
        }
    }
    return;
}

THUMB_FUNC void Reset_To_File(const char* path) {
    FSFile file;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path)) {
        *(u32*)HW_ROM_BASE_OFFSET_BUF = file.prop.file.top;
        OS_ResetSystem(0);
    }
    return;
}
