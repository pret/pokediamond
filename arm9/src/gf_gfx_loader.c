#include "global.h"
#include "filesystem.h"
#include "NNS_g2d.h"
#include "gf_gfx_loader.h"

THUMB_FUNC u32 GfGfxLoader_LoadCharData(NarcId narcId, s32 memberNo, struct BgConfig * unkStruct02016B94_2, u32 layer, u32 numTiles, u32 szByte, BOOL isCompressed, u32 heap_id)
{
    NNSG2dCharacterData * pCharData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberNo, isCompressed, heap_id, FALSE);
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedBGCharacterData(pFile, &pCharData))
        {
            if (szByte == 0)
                szByte = pCharData->szByte;
            BG_LoadCharTilesData(unkStruct02016B94_2, (u8)layer, pCharData->pRawData, szByte, numTiles);
        }
        FreeToHeap(pFile);
    }
    return szByte;
}

THUMB_FUNC void GfGfxLoader_LoadScrnData(NarcId narcId, s32 memberNo, struct BgConfig * unkStruct02016B94_2, u32 layer, u32 tileOffset, u32 szByte, BOOL isCompressed, u32 heap_id)
{
    NNSG2dScreenData * pScreenData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberNo, isCompressed, heap_id, TRUE);
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedScreenData(pFile, &pScreenData))
        {
            if (szByte == 0)
                szByte = pScreenData->szByte;
            if (GetBgTilemapBuffer(unkStruct02016B94_2, (u8) layer) != NULL)
                BG_LoadScreenTilemapData(unkStruct02016B94_2, (u8) layer, pScreenData->rawData, szByte);
            BgCopyOrUncompressTilemapBufferRangeToVram(unkStruct02016B94_2, (u8) layer, pScreenData->rawData, szByte, tileOffset);
        }
        FreeToHeap(pFile);
    }
}

THUMB_FUNC void GfGfxLoader_GXLoadPal(NarcId narcId, s32 memberNo, u32 layer, u32 baseAddr, u32 szByte, u32 heap_id)
{
    GfGfxLoader_GXLoadPalWithSrcOffset(narcId, memberNo, layer, 0, baseAddr, szByte, heap_id);
}

THUMB_FUNC void GfGfxLoader_GXLoadPalWithSrcOffset(NarcId narcId, s32 memberNo, u32 layer, u32 srcOffset, u32 baseAddr, u32 szByte, u32 heap_id)
{
    static void (*const load_funcs[])(void *, u32, u32) = {
        GX_LoadBGPltt,
        GX_LoadOBJPltt,
        GX_LoadBGExtPltt,
        GX_LoadOBJExtPltt,
        GXS_LoadBGPltt,
        GXS_LoadOBJPltt,
        GXS_LoadBGExtPltt,
        GXS_LoadOBJExtPltt
    };
    NNSG2dPaletteData * pPltData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberNo, FALSE, heap_id, TRUE);
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedPaletteData(pFile, &pPltData))
        {
            pPltData->pRawData = (void *)((u32)pPltData->pRawData + srcOffset);
            if (szByte == 0)
                szByte = pPltData->szByte - srcOffset;
            DC_FlushRange(pPltData->pRawData, szByte);
            switch (layer)
            {
            case 2:
                GX_BeginLoadBGExtPltt();
                load_funcs[layer](pPltData->pRawData, baseAddr, szByte);
                GX_EndLoadBGExtPltt();
                break;
            case 6:
                GXS_BeginLoadBGExtPltt();
                load_funcs[layer](pPltData->pRawData, baseAddr, szByte);
                GXS_EndLoadBGExtPltt();
                break;
            case 3:
                GX_BeginLoadOBJExtPltt();
                load_funcs[layer](pPltData->pRawData, baseAddr, szByte);
                GX_EndLoadOBJExtPltt();
                break;
            case 7:
                GXS_BeginLoadOBJExtPltt();
                load_funcs[layer](pPltData->pRawData, baseAddr, szByte);
                GXS_EndLoadOBJExtPltt();
                break;
            default:
                load_funcs[layer](pPltData->pRawData, baseAddr, szByte);
                break;
            }
        }
        FreeToHeap(pFile);
    }
}

THUMB_FUNC u32 GfGfxLoader_LoadWholePalette(NarcId narcId, s32 memberId, u32 layer, u32 baseAddr, u32 szByte, BOOL isCompressed, u32 heap_id)
{
    static void (*const load_funcs[])(void *, u32, u32) = {
        GX_LoadOBJ,
        GXS_LoadOBJ
    };

    NNSG2dCharacterData* pCharData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, TRUE);
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedCharacterData(pFile, &pCharData))
        {
            if (szByte == 0)
                szByte = pCharData->szByte;
            DC_FlushRange(pCharData->pRawData, szByte);
            load_funcs[layer](pCharData->pRawData, baseAddr, szByte);
        }
        FreeToHeap(pFile);
    }
    return szByte;
}

THUMB_FUNC void GfGfxLoader_PartiallyLoadPalette(NarcId narcId, s32 memberId, NNS_G2D_VRAM_TYPE vramType, u32 baseAddr, u32 heap_id, NNSG2dImagePaletteProxy * pPltProxy)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, FALSE, heap_id, TRUE);
    NNSG2dPaletteData* pPlttData;
    NNSG2dPaletteCompressInfo* pCompressInfo;
    if (pFile != NULL)
    {
        BOOL isCompressed = NNS_G2dGetUnpackedPaletteCompressInfo(pFile, &pCompressInfo);
        if (NNS_G2dGetUnpackedPaletteData(pFile, &pPlttData))
        {
            if (isCompressed)
            {
                NNS_G2dLoadPaletteEx(pPlttData, pCompressInfo, baseAddr, vramType, pPltProxy);
            }
            else
            {
                NNS_G2dLoadPalette(pPlttData, baseAddr, vramType, pPltProxy);
            }
        }
        FreeToHeap(pFile);
    }
}

THUMB_FUNC u32 GfGfxLoader_LoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, u32 heap_id, NNSG2dImageProxy *pImgProxy)
{
    static void (*const load_funcs[])(const NNSG2dCharacterData *, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy *) = {
        NNS_G2dLoadImage1DMapping,
        NNS_G2dLoadImage2DMapping
    };

    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, TRUE);
    u32 retSize = 0;
    NNSG2dCharacterData * pSrcData;
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedCharacterData(pFile, &pSrcData))
        {
            if (szByte != 0)
                pSrcData->szByte = szByte;
            load_funcs[layer](pSrcData, baseAddr, type, pImgProxy);
            retSize = pSrcData->szByte;
        }
        FreeToHeap(pFile);
    }
    return retSize;
}

THUMB_FUNC void GfGfxLoader_SetObjCntFlagsAndLoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, u32 heap_id, NNSG2dImageProxy * pImageProxy)
{
    static void (*const load_funcs[])(const NNSG2dCharacterData *, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy *) = {
        NNS_G2dLoadImage1DMapping,
        NNS_G2dLoadImage2DMapping
    };
    NNSG2dCharacterData * pCharacterData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, TRUE);
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedCharacterData(pFile, &pCharacterData))
        {
            if (szByte != 0)
                pCharacterData->szByte = szByte;
            switch (type)
            {
            case NNS_G2D_VRAM_TYPE_2DMAIN:
                pCharacterData->mapingType = (GXOBJVRamModeChar)(reg_GX_DISPCNT & (REG_GX_DISPCNT_EXOBJ_CH_MASK | REG_GX_DISPCNT_OBJMAP_CH_MASK));
                break;
            case NNS_G2D_VRAM_TYPE_2DSUB:
                pCharacterData->mapingType = (GXOBJVRamModeChar)(reg_GXS_DB_DISPCNT & (REG_GXS_DB_DISPCNT_EXOBJ_MASK | REG_GXS_DB_DISPCNT_OBJMAP_CH_MASK));
                break;
            default:
                ;
            }
            load_funcs[layer](pCharacterData, baseAddr, type, pImageProxy);
        }
        FreeToHeap(pFile);
    }
}

THUMB_FUNC void * GfGfxLoader_GetCharData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCharacterData ** ppCharData, u32 heap_id)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (pFile != NULL)
    {
        if (!NNS_G2dGetUnpackedBGCharacterData(pFile, ppCharData))
        {
            FreeToHeap(pFile);
            return NULL;
        }
    }
    return pFile;
}

THUMB_FUNC void * GfGfxLoader_GetScrnData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dScreenData ** ppScrData, u32 heap_id)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (pFile != NULL)
    {
        if (!NNS_G2dGetUnpackedScreenData(pFile, ppScrData))
        {
            FreeToHeap(pFile);
            return NULL;
        }
    }
    return pFile;
}

THUMB_FUNC void * GfGfxLoader_GetPlttData(NarcId narcId, s32 memberId, NNSG2dPaletteData ** ppPltData, u32 heap_id)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, FALSE, heap_id, FALSE);
    if (pFile != NULL)
    {
        if (!NNS_G2dGetUnpackedPaletteData(pFile, ppPltData))
        {
            FreeToHeap(pFile);
            return NULL;
        }
    }
    return pFile;
}

THUMB_FUNC void * GfGfxLoader_GetCellBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCellDataBank ** ppCellBank, u32 heap_id)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (pFile != NULL)
    {
        if (!NNS_G2dGetUnpackedCellBank(pFile, ppCellBank))
        {
            FreeToHeap(pFile);
            return NULL;
        }
    }
    return pFile;
}

THUMB_FUNC void * GfGfxLoader_GetAnimBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dAnimBankData ** ppAnimBank, u32 heap_id)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (pFile != NULL)
    {
        if (!NNS_G2dGetUnpackedAnimBank(pFile, ppAnimBank))
        {
            FreeToHeap(pFile);
            return NULL;
        }
    }
    return pFile;
}

THUMB_FUNC void * GfGfxLoader_UncompressFromNarc(NarcId narcId, s32 memberId, u32 heap_id)
{
    return GfGfxLoader_LoadFromNarc(narcId, memberId, TRUE, heap_id, FALSE);
}

THUMB_FUNC void * GfGfxLoader_LoadFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd)
{
    void * dest;
    void * dest2;
    if (isCompressed || allocAtEnd == TRUE)
    {
        u32 size = GetNarcMemberSizeByIdPair(narcId, memberNo);
        dest = AllocFromHeapAtEnd(heap_id, size);
    }
    else
    {
        u32 size = GetNarcMemberSizeByIdPair(narcId, memberNo);
        dest = AllocFromHeap(heap_id, size);
    }
    if (dest != NULL)
    {
        ReadWholeNarcMemberByIdPair(dest, narcId, memberNo);
        if (isCompressed)
        {
            if (allocAtEnd == FALSE)
            {
                dest2 = AllocFromHeap(heap_id, (*(u32 *)dest) >> 8);
            }
            else
            {
                dest2 = AllocFromHeapAtEnd(heap_id, (*(u32 *)dest) >> 8);
            }
            if (dest2 != NULL)
            {
                MI_UncompressLZ8(dest, dest2);
                FreeToHeap(dest);
            }
            dest = dest2; // UB: if dest2 is NULL, dest is never freed
        }
    }
    return dest;
}

THUMB_FUNC void * GfGfxLoader_LoadFromNarc_GetSizeOut(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd, u32 *size_p)
{
    void * dest;
    void * dest2;
    *size_p = GetNarcMemberSizeByIdPair(narcId, memberNo);
    if (isCompressed || allocAtEnd == TRUE)
    {
        dest = AllocFromHeapAtEnd(heap_id, *size_p);
    }
    else
    {
        dest = AllocFromHeap(heap_id, *size_p);
    }
    if (dest != NULL)
    {
        ReadWholeNarcMemberByIdPair(dest, narcId, memberNo);
        if (isCompressed)
        {
            *size_p = (*(u32 *)dest) >> 8;
            if (allocAtEnd == FALSE)
            {
                dest2 = AllocFromHeap(heap_id, *size_p);
            }
            else
            {
                dest2 = AllocFromHeapAtEnd(heap_id, *size_p);
            }
            if (dest2 != NULL)
            {
                MI_UncompressLZ8(dest, dest2);
                FreeToHeap(dest);
            }
            dest = dest2; // UB: if dest2 is NULL, dest is never freed
        }
    }
    return dest;
}
