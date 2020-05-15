#include "FS_rom.h"
#include "FS_archive.h"
#include "FS_file.h"
#include "CARD_pullOut.h"
#include "CARD_rom.h"
#include "CARD_common.h"
#include "MB_mb.h"
#include "OS_printf.h"

static u32 fsi_default_dma_no;
s32 fsi_card_lock_id;
CARDRomRegion fsi_ovt9;
CARDRomRegion fsi_ovt7;
FSArchive fsi_arc_rom;

ARM_FUNC void FSi_OnRomReadDone(void * p_arc)
{
    FS_NotifyArchiveAsyncEnd(p_arc, CARD_IsPulledOut() ? FS_RESULT_ERROR : FS_RESULT_SUCCESS);
}

ARM_FUNC FSResult FSi_ReadRomCallback(FSArchive * p_arc, void * dst, u32 src, u32 len)
{
    CARD_ReadRomAsync(fsi_default_dma_no, (const void *)src, dst, len, FSi_OnRomReadDone, p_arc);
    return FS_RESULT_PROC_ASYNC;
}

ARM_FUNC FSResult FSi_WriteDummyCallback(FSArchive * p_arc, const void *src, u32 dst, u32 len)
{
    return FS_RESULT_FAILURE;
}

ARM_FUNC FSResult FSi_RomArchiveProc(FSFile * p_arc, FSCommandType cmd)
{
    switch (cmd)
    {
    case FS_COMMAND_ACTIVATE:
        CARD_LockRom(fsi_card_lock_id);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_IDLE:
        CARD_UnlockRom(fsi_card_lock_id);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_WRITEFILE:
        return FS_RESULT_UNSUPPORTED;
    default:
        return FS_RESULT_PROC_UNKNOWN;
    }
}

ARM_FUNC FSResult FSi_ReadDummyCallback(FSArchive *p_arc, void *dst, u32 src, u32 len)
{
    return FS_RESULT_FAILURE;
}

ARM_FUNC FSResult FSi_EmptyArchiveProc(FSFile *p_file, FSCommandType cmd)
{
    return FS_RESULT_UNSUPPORTED;
}

ARM_FUNC void FSi_InitRom(u32 default_dma_no)
{
    fsi_default_dma_no = default_dma_no;
    fsi_card_lock_id = OS_GetLockID();
    fsi_ovt9.offset = 0;
    fsi_ovt9.length = 0;
    fsi_ovt7.offset = 0;
    fsi_ovt7.length = 0;

    CARD_Init();

    FS_InitArchive(&fsi_arc_rom);
    FS_RegisterArchiveName(&fsi_arc_rom, "rom", 3);

    if (MB_IsMultiBootChild())
    {
        fsi_ovt9.offset = (u32)~0;
        fsi_ovt9.length = 0;
        fsi_ovt7.offset = (u32)~0;
        fsi_ovt7.length = 0;
        FS_SetArchiveProc(&fsi_arc_rom, FSi_EmptyArchiveProc, (u32)FS_ARCHIVE_PROC_ALL);
        FS_LoadArchive(&fsi_arc_rom, 0x00000000, 0, 0, 0, 0, FSi_ReadDummyCallback, FSi_WriteDummyCallback);
    }
    else
    {
        const CARDRomRegion *const fnt = CARD_GetRomRegionFNT();
        const CARDRomRegion *const fat = CARD_GetRomRegionFAT();

        FS_SetArchiveProc(&fsi_arc_rom, FSi_RomArchiveProc,
                          FS_ARCHIVE_PROC_WRITEFILE |
                          FS_ARCHIVE_PROC_ACTIVATE | FS_ARCHIVE_PROC_IDLE);

        if ((fnt->offset == 0xFFFFFFFF) || (fnt->offset == 0x00000000) ||
            (fat->offset == 0xFFFFFFFF) || (fat->offset == 0x00000000))
        {
            OS_Warning("file-system : no MAKEROM-information in rom header.");
        }
        else
        {
            FS_LoadArchive(&fsi_arc_rom, 0x00000000,
                                 fat->offset, fat->length,
                                 fnt->offset, fnt->length,
                                 FSi_ReadRomCallback, FSi_WriteDummyCallback);
        }
    }
}

ARM_FUNC u32 FS_SetDefaultDMA(u32 dma_no)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();
    u32 bak_dma_no = fsi_default_dma_no;
    BOOL bak_stat = FS_SuspendArchive(&fsi_arc_rom);
    fsi_default_dma_no = dma_no;
    if (bak_stat)
        FS_ResumeArchive(&fsi_arc_rom);
    OS_RestoreInterrupts(bak_psr);
    return bak_dma_no;
}

ARM_FUNC u32 FS_TryLoadTable(void * p_mem, u32 size)
{
    return FS_LoadArchiveTables(&fsi_arc_rom, p_mem, size);
}

