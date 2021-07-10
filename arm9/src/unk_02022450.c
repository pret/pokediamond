#include "global.h"
#include "FS_file.h"
#include "OS_terminate_proc.h"
#include "CARD_rom.h"
#include "MI_memory.h"

#include "unk_02022450.h"

static const char string_saying_rom[] = "rom";

/*Replacing (HW_MAIN_MEM_SHARED + 0xC) or (HW_MAIN_MEM_SHARED + 0x10) or defining ADAJ or 01 constants causes match failure*/
THUMB_FUNC void FUN_02022450 () {
    if (!FS_IsAvailable()) {
        OS_Terminate();
    }
    else {
        struct CARD_Header* card_header_buffer = (struct CARD_Header*)HW_MAIN_MEM_SHARED;
        
        if (!*(u32*)(HW_MAIN_MEM_SHARED + 0xC)) {
            CARD_Init();
            MI_CpuCopy8((u8*)HW_ROM_HEADER_BUF, (u8*)card_header_buffer, HW_CARD_ROM_HEADER_SIZE);
            MI_CpuCopy8((u8*)HW_ROM_HEADER_BUF, (u8*)HW_CARD_ROM_HEADER, HW_CARD_ROM_HEADER_SIZE);
            *(u32*)(HW_MAIN_MEM_SHARED + 0xC) = 0x4A414441 /*"ADAJ" LE*/;
        }
        FSArchive * const r0 = FS_FindArchive(string_saying_rom, 3);
        r0->fat = card_header_buffer->header_48;
        r0->fat_size = card_header_buffer->header_4C;
        r0->fnt = card_header_buffer->header_40;
        r0->fnt_size = card_header_buffer->header_44;
        if (*(u32*)(HW_MAIN_MEM_SHARED + 0xC) != 0x4A414441 /*"ADAJ" LE*/ || *(u16*)(HW_MAIN_MEM_SHARED + 0x10) != 0x3130 /*"01" LE*/) {
            OS_Terminate();
        }
    }
    return;
}

THUMB_FUNC void Reset_To_File (const char* path) {
    FSFile file;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path)) {
        *(u32*)HW_ROM_BASE_OFFSET_BUF = file.prop.file.top;
        OS_ResetSystem(0);
    }
    return;
}
