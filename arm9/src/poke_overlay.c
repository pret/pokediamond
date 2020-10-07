#include "global.h"
#include "nitro.h"
#include "FS_file.h"
#include "FS_rom.h"
#include "poke_overlay.h"

static struct LoadedOverlay gLoadedOverlays[3][8];

THUMB_FUNC void FreeOverlayAllocation(struct LoadedOverlay * loaded)
{
    if (loaded->active != TRUE)
        ErrorHandling();
    if (FS_UnloadOverlay(MI_PROCESSOR_ARM9, loaded->id) != TRUE)
        ErrorHandling();
    loaded->active = FALSE;
}

THUMB_FUNC void UnloadOverlayByID(FSOverlayID id)
{
    struct LoadedOverlay * loaded = GetLoadedOverlaysInRegion(GetOverlayLoadDestination(id));
    int i;
    for (i = 0; i < 8; i++)
    {
        if (loaded[i].active == TRUE && loaded[i].id == id)
        {
            FreeOverlayAllocation(&loaded[i]);
            break;
        }
    }
}

THUMB_FUNC s32 GetOverlayLoadDestination(FSOverlayID id)
{
    FSOverlayInfo info;
    u8 *end;
    u8 *start;
    if (FS_LoadOverlayInfo(&info, MI_PROCESSOR_ARM9, id) != TRUE)
        ErrorHandling();
    start = (u8 *)HW_ITCM_IMAGE;
    end = (u8 *)HW_ITCM_END;
    if (info.header.ram_address <= end && info.header.ram_address >= start)
        return OVERLAY_LOAD_ITCM;
    start = (u8 *)HW_DTCM;
    end = start + HW_DTCM_SIZE;
    if (info.header.ram_address <= end && info.header.ram_address >= start)
        return OVERLAY_LOAD_DTCM;
    return OVERLAY_LOAD_WRAM;
}

THUMB_FUNC BOOL HandleLoadOverlay(FSOverlayID id, s32 a1)
{
    u32 sp0 = FS_DMA_NOT_USE;
    struct LoadedOverlay *r3;
    int r7;
    int r6;
    BOOL result;

    if (!CanOverlayBeLoaded(id))
        return FALSE;
    r7 = GetOverlayLoadDestination(id);
    r3 = GetLoadedOverlaysInRegion(r7);
    for (r6 = 0; r6 < 8; r6++)
    {
        if (!r3[r6].active)
        {
            struct LoadedOverlay * ovly;
            ovly = &r3[r6];
            ovly->active = TRUE;
            ovly->id = id;
            break;
        }
    }
    if (r6 >= 8)
    {
        ErrorHandling();
        return FALSE;
    }
    if (r7 == OVERLAY_LOAD_ITCM || r7 == OVERLAY_LOAD_DTCM)
    {
        sp0 = FS_SetDefaultDMA(FS_DMA_NOT_USE);
    }
    switch (a1)
    {
    case 0:
        result = LoadOverlayNormal(MI_PROCESSOR_ARM9, id);
        break;
    case 1:
        result = LoadOverlayNoInit(MI_PROCESSOR_ARM9, id);
        break;
    case 2:
        result = LoadOverlayNoInitAsync(MI_PROCESSOR_ARM9, id);
        break;
    default:
        ErrorHandling();
        return FALSE;
    }
    if (r7 == OVERLAY_LOAD_ITCM || r7 == OVERLAY_LOAD_DTCM)
    {
        FS_SetDefaultDMA(sp0);
    }
    if (result == 0)
    {
        ErrorHandling();
        return FALSE;
    }
    return TRUE;
}

THUMB_FUNC BOOL CanOverlayBeLoaded(FSOverlayID id)
{
    void *start, *end, *start2, *end2;
    struct LoadedOverlay *r5;
    int i;
    if (!GetOverlayRamBounds(id, &start, &end))
        return FALSE;
    r5 = GetLoadedOverlaysInRegion(GetOverlayLoadDestination(id));
    for (i = 0; i < 8; i++)
    {
        if (r5[i].active == TRUE && GetOverlayRamBounds(r5[i].id, &start2, &end2) == TRUE)
        {
            if ((start >= start2 && start < end2) || (end > start2 && end <= end2) || (start <= start2 && end >= end2))
            {
                ErrorHandling();
                return FALSE;
            }
        }
    }
    return TRUE;
}

THUMB_FUNC struct LoadedOverlay* GetLoadedOverlaysInRegion(s32 a0)
{
    switch (a0)
    {
    case OVERLAY_LOAD_WRAM:
    default:
        return gLoadedOverlays[0];
    case OVERLAY_LOAD_ITCM:
        return gLoadedOverlays[1];
    case OVERLAY_LOAD_DTCM:
        return gLoadedOverlays[2];
    }
}

THUMB_FUNC BOOL GetOverlayRamBounds(FSOverlayID id, void ** start, void ** end)
{
    FSOverlayInfo info;
    if (!FS_LoadOverlayInfo(&info, MI_PROCESSOR_ARM9, id)) {
        ErrorHandling();
        return FALSE;
    }
    *start = (void *)info.header.ram_address;
    *end = (char *)*start + (info.header.ram_size + info.header.bss_size);
    return TRUE;
}

THUMB_FUNC BOOL LoadOverlayNormal(MIProcessor target, FSOverlayID id)
{
    return FS_LoadOverlay(target, id);
}

THUMB_FUNC BOOL LoadOverlayNoInit(MIProcessor target, FSOverlayID id)
{
    FSOverlayInfo info;
    if (!FS_LoadOverlayInfo(&info, target, id))
        return FALSE;
    if (!FS_LoadOverlayImage(&info))
        return FALSE;
    FS_StartOverlay(&info);
    return TRUE;
}

THUMB_FUNC BOOL LoadOverlayNoInitAsync(MIProcessor target, FSOverlayID id)
{
    FSOverlayInfo info;
    FSFile file;
    if (!FS_LoadOverlayInfo(&info, target, id))
        return FALSE;
    FS_InitFile(&file);
    FS_LoadOverlayImageAsync(&info, &file);
    FS_WaitAsync(&file);
    FS_CloseFile(&file);
    FS_StartOverlay(&info);
    return TRUE;
}
