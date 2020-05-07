#include "nitro.h"
#include "DGT_common.h"
#include "DGT_dgt.h"
#include "OS_cache.h"
#include "OS_system.h"
#include "MI_memory.h"
#include "MI_uncompress.h"
#include "FS_rom.h"
#include "FS_overlay.h"
#include "FS_mw_dtor.h"
#include "MB_mb.h"

#define FS_OVERLAY_FLAG_COMP    0x0001
#define FS_OVERLAY_FLAG_AUTH    0x0002
#define FS_OVERLAY_DIGEST_SIZE  DGT_HASH2_DIGEST_SIZE

u32 FSi_GetOverlayBinarySize(FSOverlayInfo * p_ovi)
{
    u32 size = (p_ovi->header.flag & FS_OVERLAY_FLAG_COMP)
        ? p_ovi->header.compressed
        : p_ovi->header.ram_size;
    return size;
}

void FS_ClearOverlayImage(FSOverlayInfo * p_ovi)
{
    u8 * const im_start = FS_GetOverlayAddress(p_ovi);
    u32 const ram_size = FS_GetOverlayImageSize(p_ovi);
    u32 const total_size = FS_GetOverlayTotalSize(p_ovi);

    IC_InvalidateRange(im_start, total_size);
    DC_InvalidateRange(im_start, total_size);
    MI_CpuFill8(im_start + ram_size, 0, total_size - ram_size);
}

FSFileID FS_GetOverlayFileID(FSOverlayInfo * p_ovi)
{
    FSFileID ret;
    ret.arc = &fsi_arc_rom;
    ret.file_id = p_ovi->header.file_id;
    return ret;
}

BOOL FSi_LoadOverlayInfoCore(FSOverlayInfo * p_ovi, MIProcessor target, FSOverlayID id, FSArchive * arc, u32 offset_arm9, u32 len_arm9, u32 offset_arm7, u32 len_arm7)
{
    CARDRomRegion pr[1];
    u32 pos;
    if (target == MI_PROCESSOR_ARM9)
    {
        pr->offset = offset_arm9;
        pr->length = len_arm9;
    }
    else
    {
        pr->offset = offset_arm7;
        pr->length = len_arm7;
    }
    pos = (u32) id * sizeof(FSOverlayInfoHeader);
    if (pos >= pr->length)
        return FALSE;

    FSFile file[1];
    FS_InitFile(file);
    // BOOL FS_OpenFileDirect(FSFile * p_file, FSArchive * p_arc, u32 image_top, u32 image_bottom, u32 file_index)
    if (!FS_OpenFileDirect(file, arc, pr->offset + pos, pr->offset + pr->length, (u32)~0))
        return FALSE;
    if (FS_ReadFile(file, p_ovi, sizeof(FSOverlayInfoHeader)) != sizeof(FSOverlayInfoHeader))
    {
        FS_CloseFile(file);
        return FALSE;
    }
    FS_CloseFile(file);
    p_ovi->target = target;
    if (!FS_OpenFileFast(file, FS_GetOverlayFileID(p_ovi)))
        return FALSE;
    p_ovi->file_pos.offset = FS_GetFileImageTop(file);
    p_ovi->file_pos.length = FS_GetLength(file);
    FS_CloseFile(file);
    return TRUE;
}

BOOL FS_LoadOverlayInfo(FSOverlayInfo * p_ovi, MIProcessor target, FSOverlayID id)
{
    CARDRomRegion * const pr = (target == MI_PROCESSOR_ARM9) ? &fsi_ovt9 : &fsi_ovt7;
    if (pr->offset)
    {
        FSFile file[1];
        const u32 pos = id * sizeof(FSOverlayInfoHeader);
        if (pos >= pr->length)
            return FALSE;
        MI_CpuCopy8((const void *)(pr->offset + pos), p_ovi, sizeof(FSOverlayInfoHeader));
        p_ovi->target = target;
        FS_InitFile(file);
        if (!FS_OpenFileFast(file, FS_GetOverlayFileID(p_ovi)))
            return FALSE;
        p_ovi->file_pos.offset = FS_GetFileImageTop(file);
        p_ovi->file_pos.length = FS_GetLength(file);
        FS_CloseFile(file);
        return TRUE;
    }
    else
    {
        const CARDRomRegion * const p_ovt9 = CARD_GetRomRegionOVT(MI_PROCESSOR_ARM9);
        const CARDRomRegion * const p_ovt7 = CARD_GetRomRegionOVT(MI_PROCESSOR_ARM7);
        return FSi_LoadOverlayInfoCore(p_ovi, target, id, &fsi_arc_rom, p_ovt9->offset, p_ovt9->length, p_ovt7->offset, p_ovt7->length);
    }
}

BOOL FS_LoadOverlayImageAsync(FSOverlayInfo * p_ovi, FSFile * p_file)
{
    FS_InitFile(p_file);
    if (!FS_OpenFileFast(p_file, FS_GetOverlayFileID(p_ovi)))
        return FALSE;
    else
    {
        s32 size = FSi_GetOverlayBinarySize(p_ovi);
        FS_ClearOverlayImage(p_ovi);
        if (FS_ReadFileAsync(p_file, FS_GetOverlayAddress(p_ovi), size) != size)
        {
            FS_CloseFile(p_file);
            return FALSE;
        }
        return TRUE;
    }
}

BOOL FS_LoadOverlayImage(FSOverlayInfo * p_ovi)
{
    FSFile file[1];
    FS_InitFile(file);
    if (!FS_OpenFileFast(file, FS_GetOverlayFileID(p_ovi)))
        return FALSE;
    else
    {
        s32 size = FSi_GetOverlayBinarySize(p_ovi);
        FS_ClearOverlayImage(p_ovi);
        if (FS_ReadFile(file, FS_GetOverlayAddress(p_ovi), size) != size)
        {
            FS_CloseFile(file);
            return FALSE;
        }
        FS_CloseFile(file);
        return TRUE;
    }
}

const void *fsi_digest_key_ptr;
u32 fsi_digest_key_len;

BOOL FSi_CompareDigest(const u8 *spec_digest, void *src, int len)
{
    int i;
    u8 digest[FS_OVERLAY_DIGEST_SIZE];
    u8 digest_key[64];

    MI_CpuClear8(digest, sizeof(digest));
    MI_CpuCopy8(fsi_digest_key_ptr, digest_key, fsi_digest_key_len);
    DGT_Hash2CalcHmac(digest, src, len, digest_key, fsi_digest_key_len);
    for (i = 0; i < sizeof(digest); i += sizeof(u32))
    {
        if (*(const u32 *)(digest + i) != *(const u32 *)(spec_digest + i))
            break;
    }
    return i == sizeof(digest);
}

extern u8 SDK_OVERLAY_DIGEST[];
extern u8 SDK_OVERLAY_DIGEST_END[];

void FS_StartOverlay(FSOverlayInfo * p_ovi)
{
    u32 rare_size = FSi_GetOverlayBinarySize(p_ovi);
    if (MB_IsMultiBootChild())
    {
        BOOL ret = FALSE;

        if (p_ovi->header.flag & FS_OVERLAY_FLAG_AUTH)
        {
            const u32 odt_max = (u32)((SDK_OVERLAY_DIGEST_END - SDK_OVERLAY_DIGEST) / FS_OVERLAY_DIGEST_SIZE);
            if (p_ovi->header.id < odt_max)
            {
                const u8 * spec_digest = SDK_OVERLAY_DIGEST + FS_OVERLAY_DIGEST_SIZE * p_ovi->header.id;
                ret = FSi_CompareDigest(spec_digest, p_ovi->header.ram_address, (int)rare_size);
            }
        }
        if (!ret)
        {
            MI_CpuClear8(p_ovi->header.ram_address, rare_size);
            OS_TPanic("FS_StartOverlay() failed! (invalid overlay-segment data)");
            return;
        }
    }
    if (p_ovi->header.flag & FS_OVERLAY_FLAG_COMP)
    {
        MIi_UncompressBackward(p_ovi->header.ram_address + rare_size);
    }
    DC_FlushRange(p_ovi->header.ram_address, p_ovi->header.ram_size);

    {
        FSOverlayInitFunc *p = p_ovi->header.sinit_init;
        FSOverlayInitFunc *q = p_ovi->header.sinit_init_end;
        for (; p < q; ++p)
        {
            if (*p)
                (**p)();
        }
    }
}

void FS_EndOverlay(FSOverlayInfo *p_ovi)
{
    for (;;)
    {
        MWiDestructorChain *head = NULL, *tail = NULL;
        const u32 region_top = (u32)FS_GetOverlayAddress(p_ovi);
        const u32 region_bottom = region_top + FS_GetOverlayTotalSize(p_ovi);

        {
            OSIntrMode bak_psr = OS_DisableInterrupts();
            MWiDestructorChain *prev = NULL;
            MWiDestructorChain *base = __global_destructor_chain;
            MWiDestructorChain *p = base;
            while (p)
            {
                MWiDestructorChain *next = p->next;
                const u32 dtor = (u32)p->dtor;
                const u32 obj = (u32)p->obj;
                if (((obj == 0) && (dtor >= region_top) && (dtor < region_bottom)) ||
                    ((obj >= region_top) && (obj < region_bottom)))
                {
                    /* If appropriate, extract*/
                    if (!tail)
                    {
                        head = p;
                    }
                    else
                    {
                        tail->next = p;
                    }
                    if (base == p)
                    {
                        base = __global_destructor_chain = next;
                    }
                    tail = p, p->next = NULL;
                    if (prev)
                    {
                        prev->next = next;
                    }
                }
                else
                {
                    prev = p;
                }
                p = next;
            }
            OS_RestoreInterrupts(bak_psr);
        }

        if (!head)
        {
            break;
        }
        do
        {
            MWiDestructorChain *next = head->next;
            if (head->dtor)
            {
                (*head->dtor) (head->obj);
            }
            head = next;
        }
        while (head);
    }
}

BOOL FS_UnloadOverlayImage(FSOverlayInfo * p_ovi)
{
    FS_EndOverlay(p_ovi);
    return TRUE;
}

BOOL FS_LoadOverlay(MIProcessor target, FSOverlayID id)
{
    FSOverlayInfo ovi;
    if (!FS_LoadOverlayInfo(&ovi, target, id) || !FS_LoadOverlayImage(&ovi))
        return FALSE;
    FS_StartOverlay(&ovi);
    return TRUE;
}

BOOL FS_UnloadOverlay(MIProcessor target, FSOverlayID id)
{
    FSOverlayInfo ovi;
    if (!FS_LoadOverlayInfo(&ovi, target, id) || !FS_UnloadOverlayImage(&ovi))
        return FALSE;
    return TRUE;
}
