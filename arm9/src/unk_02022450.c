#include "global.h"
#include "FS_file.h"
#include "OS_terminate_proc.h"
#include "CARD_rom.h"
#include "MI_memory.h"

#include "unk_02022450.h"

static const char string_saying_rom[] = "rom";

THUMB_FUNC void FUN_02022450 () {
    if (!FS_IsAvailable()) {
        OS_Terminate();
    }
    else {
        if (!*(u32*)0x027FF00C) {
            CARD_Init();
            MI_CpuCopy8((u8*)HW_ROM_HEADER_BUF, (u8*)0x027FF000, 22 * 16);
            MI_CpuCopy8((u8*)HW_ROM_HEADER_BUF, (u8*)HW_CARD_ROM_HEADER, 22 * 16);
            *(u32*)0x027FF00C = 0x4A414441;
        }
        FSArchive * const r0 = FS_FindArchive(string_saying_rom, 3);
        u32 *r1 = (u32*)0x027FF000;
        r0->fat = r1[18];
        r0->fat_size = r1[19];
        r0->fnt = r1[16];
        r0->fnt_size = r1[17];
        if (*(u32*)0x027FF00C != 0x4A414441 || *(u16*)0x027FF010 != 0x3130) {
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
