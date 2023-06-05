#include "global.h"
#include "unk_02021590.h"
#include "filesystem.h"
#include "heap.h"
#include "string_control_code.h"
#include "string_util.h"

static const u8 sGlyphShapes[][2] = {
    { 0, 1 },
    { 2, 3 },
};

static void (*const sAllocators[])(struct FontData *, u32) = {
    InitFontResources_FromPreloaded,
    InitFontResources_LazyFromNarc,
};

static void (*const sDestructors[])(struct FontData *) = {
    FreeLoadedFontResources_FromPreloaded,
    FreeLoadedFontResources_LazyFromNarc,
};

THUMB_FUNC struct FontData *FontData_New(NarcId narcId, s32 fileId, u32 unk2, BOOL unk3, u32 heap_id)
{
    struct FontData * ret = (struct FontData *)AllocFromHeap(heap_id, sizeof(struct FontData));
    if (ret != NULL)
    {
        FontData_Init(ret, narcId, fileId, unk3, heap_id);
        InitFontResources(ret, unk2, heap_id);
    }
    return ret;
}

THUMB_FUNC void FontData_Delete(struct FontData * ptr)
{
    FreeLoadedFontResources(ptr);
    FontData_FreeWidthsAndNarc(ptr);
    FreeToHeap(ptr);
}

THUMB_FUNC void FontData_ModeSwitch(struct FontData * ptr, u32 a1, u32 heap_id)
{
    if (ptr->glyphAccessMode != a1)
    {
        FreeLoadedFontResources(ptr);
        InitFontResources(ptr, a1, heap_id);
    }
}

THUMB_FUNC void FontData_Init(struct FontData *ptr, NarcId narcId, s32 fileId, BOOL unk, u32 heap_id)
{
    ptr->narc = NARC_ctor(narcId, heap_id);
    if (ptr->narc != NULL)
    {
        NARC_ReadFromMember(ptr->narc, (u32)fileId, 0, 16, &ptr->gfxHeader);
        ptr->isFixedWidthFont = unk;
        if (unk)
        {
            ptr->glyphWidths = NULL;
            ptr->glyphWidthFunc = GetGlyphWidth_FixedWidth;
        }
        else
        {
            GF_ASSERT(ptr->gfxHeader.widthDataStart != 0);
            ptr->glyphWidths = AllocFromHeap(heap_id, ptr->gfxHeader.numGlyphs);
            ptr->glyphWidthFunc = GetGlyphWidth_VariableWidth;
            NARC_ReadFromMember(ptr->narc, (u32)fileId, ptr->gfxHeader.widthDataStart, ptr->gfxHeader.numGlyphs, ptr->glyphWidths);
        }
        GF_ASSERT(ptr->gfxHeader.glyphWidth <= 2 && ptr->gfxHeader.glyphHeight <= 2);
        ptr->glyphShape = sGlyphShapes[ptr->gfxHeader.glyphWidth - 1][ptr->gfxHeader.glyphHeight - 1];
        ptr->glyphSize = (u32)(16 * ptr->gfxHeader.glyphWidth * ptr->gfxHeader.glyphHeight);
        ptr->fileId = (u32)fileId;
    }
}

THUMB_FUNC void FontData_FreeWidthsAndNarc(struct FontData * ptr)
{
    if (ptr->glyphWidths != NULL)
        FreeToHeap(ptr->glyphWidths);
    if (ptr->narc != NULL)
        NARC_dtor(ptr->narc);
}

THUMB_FUNC void InitFontResources(struct FontData * ptr, u32 a1, u32 heap_id)
{
    ptr->glyphAccessMode = a1;
    sAllocators[a1](ptr, heap_id);
}

THUMB_FUNC void InitFontResources_FromPreloaded(struct FontData * ptr, u32 heap_id)
{
    u32 r4 = ptr->glyphSize * ptr->gfxHeader.numGlyphs;
    ptr->narcReadBuf = AllocFromHeap(heap_id, r4);
    ptr->uncompGlyphFunc = DecompressGlyphTiles_FromPreloaded;
    NARC_ReadFromMember(ptr->narc, ptr->fileId, ptr->gfxHeader.headerSize, r4, ptr->narcReadBuf);
}

THUMB_FUNC void InitFontResources_LazyFromNarc(struct FontData * ptr, u32 heap_id)
{
#pragma unused(heap_id)
    ptr->uncompGlyphFunc = DecompressGlyphTiles_LazyFromNarc;
}

THUMB_FUNC void FreeLoadedFontResources(struct FontData * ptr)
{
    sDestructors[ptr->glyphAccessMode](ptr);
}

THUMB_FUNC void FreeLoadedFontResources_FromPreloaded(struct FontData * ptr)
{
    FreeToHeap(ptr->narcReadBuf);
    ptr->narcReadBuf = NULL;
}

THUMB_FUNC void FreeLoadedFontResources_LazyFromNarc(struct FontData * ptr)
{
#pragma unused(ptr)
}

THUMB_FUNC void TryLoadGlyph(struct FontData * ptr, u32 param1, struct UnkStruct_02002C14_sub * ptr2)
{
    if (param1 <= ptr->gfxHeader.numGlyphs)
        ptr->uncompGlyphFunc(ptr, (u16)(param1 - 1), ptr2);
    else
    {
        ptr2->width = 0;
        ptr2->height = 0;
    }
}

THUMB_FUNC void DecompressGlyphTiles_FromPreloaded(struct FontData * ptr, u16 param1, struct UnkStruct_02002C14_sub * param2)
{
    u8 *r4 = &((u8 *)ptr->narcReadBuf)[param1 * ptr->glyphSize];
    switch (ptr->glyphShape)
    {
    case 0:
        DecompressGlyphTile((void *)(r4), (void *)param2->buf);
        break;
    case 1:
        DecompressGlyphTile((void *)(r4), (void *)param2->buf);
        DecompressGlyphTile((void *)(r4 + 0x10), (void *)(param2->buf + 0x40));
        break;
    case 2:
        DecompressGlyphTile((void *)(r4), (void *)param2->buf);
        DecompressGlyphTile((void *)(r4 + 0x10), (void *)(param2->buf + 0x20));
        break;
    case 3:
        DecompressGlyphTile((void *)(r4), (void *)param2->buf);
        DecompressGlyphTile((void *)(r4 + 0x10), (void *)(param2->buf + 0x20));
        DecompressGlyphTile((void *)(r4 + 0x20), (void *)(param2->buf + 0x40));
        DecompressGlyphTile((void *)(r4 + 0x30), (void *)(param2->buf + 0x60));
        break;
    }
    param2->width = (u8)ptr->glyphWidthFunc(ptr, param1);
    param2->height = ptr->gfxHeader.fixedHeight;
}

THUMB_FUNC void DecompressGlyphTiles_LazyFromNarc(struct FontData * ptr, u16 param1, struct UnkStruct_02002C14_sub * param2)
{
    NARC_ReadFromMember(ptr->narc, ptr->fileId, ptr->gfxHeader.headerSize + param1 * ptr->glyphSize, ptr->glyphSize, ptr->glyphReadBuf);
    switch (ptr->glyphShape)
    {
    case 0:
        DecompressGlyphTile((void *)(ptr->glyphReadBuf), (void *)param2->buf);
        break;
    case 1:
        DecompressGlyphTile((void *)(ptr->glyphReadBuf), (void *)param2->buf);
        DecompressGlyphTile((void *)(ptr->glyphReadBuf + 0x10), (void *)(param2->buf + 0x40));
        break;
    case 2:
        DecompressGlyphTile((void *)(ptr->glyphReadBuf), (void *)param2->buf);
        DecompressGlyphTile((void *)(ptr->glyphReadBuf + 0x10), (void *)(param2->buf + 0x20));
        break;
    case 3:
        DecompressGlyphTile((void *)(ptr->glyphReadBuf), (void *)param2->buf);
        DecompressGlyphTile((void *)(ptr->glyphReadBuf + 0x10), (void *)(param2->buf + 0x20));
        DecompressGlyphTile((void *)(ptr->glyphReadBuf + 0x20), (void *)(param2->buf + 0x40));
        DecompressGlyphTile((void *)(ptr->glyphReadBuf + 0x30), (void *)(param2->buf + 0x60));
        break;
    }
    param2->width = (u8)ptr->glyphWidthFunc(ptr, param1);
    param2->height = ptr->gfxHeader.fixedHeight;
}

THUMB_FUNC u32 GetStringWidth(struct FontData * ptr, const u16 * str, u32 letterSpacing)
{
    u32 width = 0;

    while (*str != EOS)
    {
        if (*str == 0xFFFE)
        {
            str = MsgArray_SkipControlCode(str);
            if (*str == EOS)
                break;
        }
        width += ptr->glyphWidthFunc(ptr, (*str) - 1) + letterSpacing;
        str++;
    }
    return width - letterSpacing;
}

THUMB_FUNC int GetGlyphWidth_VariableWidth(struct FontData * ptr, int a1)
{
    return ptr->glyphWidths[a1];
}

THUMB_FUNC int GetGlyphWidth_FixedWidth(struct FontData * ptr, int a1)
{
#pragma unused(a1)
    return ptr->gfxHeader.fixedWidth;
}

THUMB_FUNC s32 GetStringWidthMultiline(struct FontData * r7, const u16 * arr, u32 r6)
{
    s32 ret = 0;
    u32 r4 = 0;
    while (*arr != 0xFFFF)
    {
        if (*arr == 0xFFFE)
        {
            arr = MsgArray_SkipControlCode(arr);
        }
        else if (*arr == 0xE000) // newline
        {
            if (ret < r4 - r6)
                ret = (int)(r4 - r6);
            r4 = 0;
            arr++;
        }
        else
        {
            r4 += (r6 + r7->glyphWidthFunc(r7, *arr - 1));
            arr++;
        }
    }
    if (ret < r4 - r6)
        ret = (int)(r4 - r6);
    return ret;
}

THUMB_FUNC s32 StringGetWidth_SingleLine_HandleClearToControlCode(struct FontData * r6, const u16 * arr)
{
    s32 ret = 0;
    while (*arr != 0xFFFF)
    {
        if (*arr == 0xFFFE)
        {
            if (MsgArray_GetControlCode(arr) == 515)
            {
                ret = MsgArray_ControlCodeGetField(arr, 0) - 12;
            }
            arr = MsgArray_SkipControlCode(arr);
        }
        else
        {
            ret += r6->glyphWidthFunc(r6, *arr - 1);
            arr++;
        }
    }
    return ret;
}
