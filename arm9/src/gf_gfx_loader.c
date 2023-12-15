#include "global.h"
#include "filesystem.h"
#include "NNS_g2d.h"
#include "gf_gfx_loader.h"

u32 GfGfxLoader_LoadCharData(NarcId narcId, s32 memberNo, struct BgConfig * unkStruct02016B94_2, u32 layer, u32 numTiles, u32 szByte, BOOL isCompressed, HeapID heapId)
{
    NNSG2dCharacterData * pCharData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberNo, isCompressed, heapId, FALSE);
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

void GfGfxLoader_LoadScrnData(NarcId narcId, s32 memberNo, struct BgConfig * unkStruct02016B94_2, u32 layer, u32 tileOffset, u32 szByte, BOOL isCompressed, HeapID heapId)
{
    NNSG2dScreenData * pScreenData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberNo, isCompressed, heapId, TRUE);
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

void GfGfxLoader_GXLoadPal(NarcId narcId, s32 memberNo, enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 szByte, HeapID heapId)
{
    GfGfxLoader_GXLoadPalWithSrcOffset(narcId, memberNo, location, 0, palSlotOffset, szByte, heapId);
}

void GfGfxLoader_GXLoadPalWithSrcOffset(NarcId narcId, s32 memberNo, enum GFPalLoadLocation location, u32 srcOffset, enum GFPalSlotOffset palSlotOffset, u32 szByte, HeapID heapId)
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
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberNo, FALSE, heapId, TRUE);
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedPaletteData(pFile, &pPltData))
        {
            pPltData->pRawData = (void *)((u32)pPltData->pRawData + srcOffset);
            if (szByte == 0)
                szByte = pPltData->szByte - srcOffset;
            DC_FlushRange(pPltData->pRawData, szByte);
            switch (location)
            {
            case GF_PAL_LOCATION_MAIN_BGEXT:
                GX_BeginLoadBGExtPltt();
                load_funcs[location](pPltData->pRawData, palSlotOffset, szByte);
                GX_EndLoadBGExtPltt();
                break;
            case GF_PAL_LOCATION_SUB_BGEXT:
                GXS_BeginLoadBGExtPltt();
                load_funcs[location](pPltData->pRawData, palSlotOffset, szByte);
                GXS_EndLoadBGExtPltt();
                break;
            case GF_PAL_LOCATION_MAIN_OBJEXT:
                GX_BeginLoadOBJExtPltt();
                load_funcs[location](pPltData->pRawData, palSlotOffset, szByte);
                GX_EndLoadOBJExtPltt();
                break;
            case GF_PAL_LOCATION_SUB_OBJEXT:
                GXS_BeginLoadOBJExtPltt();
                load_funcs[location](pPltData->pRawData, palSlotOffset, szByte);
                GXS_EndLoadOBJExtPltt();
                break;
            default:
                load_funcs[location](pPltData->pRawData, palSlotOffset, szByte);
                break;
            }
        }
        FreeToHeap(pFile);
    }
}

u32 GfGfxLoader_LoadWholePalette(NarcId narcId, s32 memberId, u32 layer, u32 baseAddr, u32 szByte, BOOL isCompressed, HeapID heapId) //todo: change this to new format
{
    static void (*const load_funcs[])(void *, u32, u32) = {
        GX_LoadOBJ,
        GXS_LoadOBJ
    };

    NNSG2dCharacterData* pCharData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, TRUE);
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

void GfGfxLoader_PartiallyLoadPalette(NarcId narcId, s32 memberId, NNS_G2D_VRAM_TYPE vramType, u32 baseAddr, HeapID heapId, NNSG2dImagePaletteProxy * pPltProxy)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, FALSE, heapId, TRUE);
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

u32 GfGfxLoader_LoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, HeapID heapId, NNSG2dImageProxy *pImgProxy)
{
    static void (*const load_funcs[])(const NNSG2dCharacterData *, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy *) = {
        NNS_G2dLoadImage1DMapping,
        NNS_G2dLoadImage2DMapping
    };

    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, TRUE);
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

void GfGfxLoader_SetObjCntFlagsAndLoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, HeapID heapId, NNSG2dImageProxy * pImageProxy)
{
    static void (*const load_funcs[])(const NNSG2dCharacterData *, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy *) = {
        NNS_G2dLoadImage1DMapping,
        NNS_G2dLoadImage2DMapping
    };
    NNSG2dCharacterData * pCharacterData;
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, TRUE);
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

void * GfGfxLoader_GetCharData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCharacterData ** ppCharData, HeapID heapId)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, FALSE);
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

void * GfGfxLoader_GetScrnData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dScreenData ** ppScrData, HeapID heapId)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, FALSE);
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

void * GfGfxLoader_GetPlttData(NarcId narcId, s32 memberId, NNSG2dPaletteData ** ppPltData, HeapID heapId)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, FALSE, heapId, FALSE);
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

void * GfGfxLoader_GetCellBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCellDataBank ** ppCellBank, HeapID heapId)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, FALSE);
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

void * GfGfxLoader_GetAnimBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dAnimBankData ** ppAnimBank, HeapID heapId)
{
    void * pFile = GfGfxLoader_LoadFromNarc(narcId, memberId, isCompressed, heapId, FALSE);
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

void * GfGfxLoader_UncompressFromNarc(NarcId narcId, s32 memberId, HeapID heapId)
{
    return GfGfxLoader_LoadFromNarc(narcId, memberId, TRUE, heapId, FALSE);
}

void * GfGfxLoader_LoadFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, HeapID heapId, BOOL allocAtEnd)
{
    void * dest;
    void * dest2;
    if (isCompressed || allocAtEnd == TRUE)
    {
        u32 size = GetNarcMemberSizeByIdPair(narcId, memberNo);
        dest = AllocFromHeapAtEnd(heapId, size);
    }
    else
    {
        u32 size = GetNarcMemberSizeByIdPair(narcId, memberNo);
        dest = AllocFromHeap(heapId, size);
    }
    if (dest != NULL)
    {
        ReadWholeNarcMemberByIdPair(dest, narcId, memberNo);
        if (isCompressed)
        {
            if (allocAtEnd == FALSE)
            {
                dest2 = AllocFromHeap(heapId, (*(u32 *)dest) >> 8);
            }
            else
            {
                dest2 = AllocFromHeapAtEnd(heapId, (*(u32 *)dest) >> 8);
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

void * GfGfxLoader_LoadFromNarc_GetSizeOut(NarcId narcId, s32 memberNo, BOOL isCompressed, HeapID heapId, BOOL allocAtEnd, u32 *size_p)
{
    void * dest;
    void * dest2;
    *size_p = GetNarcMemberSizeByIdPair(narcId, memberNo);
    if (isCompressed || allocAtEnd == TRUE)
    {
        dest = AllocFromHeapAtEnd(heapId, *size_p);
    }
    else
    {
        dest = AllocFromHeap(heapId, *size_p);
    }
    if (dest != NULL)
    {
        ReadWholeNarcMemberByIdPair(dest, narcId, memberNo);
        if (isCompressed)
        {
            *size_p = (*(u32 *)dest) >> 8;
            if (allocAtEnd == FALSE)
            {
                dest2 = AllocFromHeap(heapId, *size_p);
            }
            else
            {
                dest2 = AllocFromHeapAtEnd(heapId, *size_p);
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
